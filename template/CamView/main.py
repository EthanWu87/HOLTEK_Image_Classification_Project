import serial
import numpy as np
import cv2
import time

# 設定序列埠參數
SERIAL_PORT = 'COM15'
BAUD_RATE = 2000000

WIDTH = 160
HEIGHT = 120
FRAME_SIZE = WIDTH * HEIGHT


def main():
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"Connected to {SERIAL_PORT}")
    except Exception as e:
        print(f"Error: {e}")
        return

    target_header = b"---FRAME_START---"
    header_index = 0
    is_reading_frame = False

    frame_buffer = bytearray(FRAME_SIZE)
    frame_byte_count = 0

    last_time = time.time()
    fps = 0.0

    while True:
        if ser.in_waiting > 0:
            data_chunk = ser.read(ser.in_waiting)
        else:
            data_chunk = ser.read(1)

        for in_byte in data_chunk:
            if not is_reading_frame:
                # 狀態機階段 A：尋找標頭
                if in_byte == target_header[header_index]:
                    header_index += 1
                    if header_index == len(target_header):
                        is_reading_frame = True
                        frame_byte_count = 0
                        header_index = 0
                else:
                    header_index = 0
                    if in_byte == target_header[0]:
                        header_index = 1
            else:
                # 狀態機階段 B：填寫影格緩衝區
                frame_buffer[frame_byte_count] = in_byte
                frame_byte_count += 1

                # 當收滿一張圖後，立刻解碼成像並計算 FPS
                if frame_byte_count == FRAME_SIZE:
                    frame_raw = np.frombuffer(frame_buffer, dtype=np.uint8).reshape((HEIGHT, WIDTH))

                    frame_zoomed = cv2.resize(frame_raw, (160 * 4, 120 * 4), interpolation=cv2.INTER_NEAREST)

                    current_time = time.time()
                    time_diff = current_time - last_time

                    if time_diff > 0:
                        fps = 1.0 / time_diff

                    last_time = current_time

                    print(f"當前畫面更新率: {fps:.2f} FPS")
                    window_title = f"HM01B0 Pure 160x120 - FPS: {fps:.2f}"
                    cv2.imshow('HM01B0 Python State-Machine Grayscale', frame_zoomed)
                    cv2.setWindowTitle('HM01B0 Python State-Machine Grayscale', window_title)

                    is_reading_frame = False

                    if cv2.waitKey(1) & 0xFF == ord('q'):
                        ser.close()
                        cv2.destroyAllWindows()
                        return


if __name__ == '__main__':
    main()