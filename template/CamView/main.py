import serial
import numpy as np
import cv2
import time

SERIAL_PORT = 'COM15'
BAUD_RATE = 2000000

WIDTH = 160
HEIGHT = 120
FRAME_SIZE = WIDTH * HEIGHT

def main():
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"Successfully connected to 1-bit stream on {SERIAL_PORT}")
    except Exception as e:
        print(f"Error: {e}")
        return

    target_header = b"---FRAME_START---"
    header_index = 0
    is_reading_frame = False

    frame_buffer = bytearray(FRAME_SIZE)
    frame_byte_count = 0
    last_time = time.time()

    while True:
        if ser.in_waiting > 0:
            data_chunk = ser.read(ser.in_waiting)
        else:
            data_chunk = ser.read(1)

        for in_byte in data_chunk:
            if not is_reading_frame:
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
                frame_buffer[frame_byte_count] = in_byte
                frame_byte_count += 1

                if frame_byte_count == FRAME_SIZE:
                    frame_raw = np.frombuffer(frame_buffer, dtype=np.uint8).reshape((HEIGHT, WIDTH))

                    frame_zoomed = cv2.resize(frame_raw, (160 * 4, 120 * 4), interpolation=cv2.INTER_NEAREST)

                    # 3. 計算並即時更新 FPS
                    current_time = time.time()
                    time_diff = current_time - last_time
                    fps = 1.0 / time_diff if time_diff > 0 else 0.0
                    last_time = current_time

                    window_title = f"HM01B0 True 1-bit Parallel - FPS: {fps:.2f}"
                    cv2.imshow('HM01B0 1-Bit Parallel Grayscale', frame_zoomed)
                    cv2.setWindowTitle('HM01B0 1-Bit Parallel Grayscale', window_title)

                    is_reading_frame = False

                    if cv2.waitKey(1) & 0xFF == ord('q'):
                        ser.close()
                        cv2.destroyAllWindows()
                        return

if __name__ == '__main__':
    main()