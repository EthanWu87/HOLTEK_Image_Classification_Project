import serial
import numpy as np
import cv2

# 設定序列埠參數
SERIAL_PORT = 'COM15'
BAUD_RATE = 921600
WIDTH = 160
HEIGHT = 120
# 重大修正：現在接收的是 8-bit 灰階資料流 (序列化傳輸)
FRAME_SIZE = WIDTH * HEIGHT  # 19200 Byteqs

def main():
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"Connected to {SERIAL_PORT}")
    except Exception as e:
        print(f"Error: {e}")
        return

    buffer = b''
    while True:
        data = ser.read(ser.in_waiting or 1)
        buffer += data

        header = b'---FRAME_START---'
        if header in buffer:
            start_pos = buffer.find(header) + len(header)
            # 檢查 buffer 長度是否足夠 (19200 資料 + 可能是 \r\n 的位置)
            if len(buffer) >= start_pos + FRAME_SIZE + 2:
                # 測試：如果發現開頭是 \r\n，手動略過這 2 bytes
                # 或者直接從 header 後面尋找第一個真正的影像起始點
                frame_data = buffer[start_pos: start_pos + FRAME_SIZE]

                # 如果畫面依然偏移，試著調整 start_pos，例如 start_pos + 1 或 + 2
                frame = np.frombuffer(frame_data, dtype=np.uint8).reshape((HEIGHT, WIDTH))
                cv2.imshow('HM01B0 Raw Grayscale', frame)
                buffer = buffer[start_pos + FRAME_SIZE:]

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    ser.close()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()