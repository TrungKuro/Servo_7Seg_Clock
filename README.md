# Giới thiệu

Đây là đồng hồ hiển thị thời gian. Sử dụng mạch thời gian thực RTC DS3231 để lưu thời gian. Sử dụng các động cơ RC Servo để điều khiển từng thanh Segment, được điều khiển bởi bo mạch PCA9685.

Bằng cách mô phỏng *"Led 7 đoạn"*. Để hiển thị được **"GIỜ : PHÚT"**, đồng hồ này cần 4 con Led 7 đoạn. Như cái tên, mỗi con Led có 7 thanh đoạn để hiển thị, sẽ cần tương ứng 7 Servo. Như vậy chúng ta sẽ cần tất cả 28 Servo!

## Phần cứng

- [Mạch Điều Khiển 16 Chanel PWM PCA9685](https://hshop.vn/products/mach-xuat-16-xung-pwmgiao-tiep-i2c).
- [Mạch Thời Gian Thực RTC DS3231](https://hshop.vn/products/mach-thoi-gian-thuc-rtc-ds3231).

## Sơ đồ kết nối

...

## Các bước lắp đặt

...

## Nguồn tài liệu

- [Adafruit PCA9685 16-Channel Servo Driver](https://learn.adafruit.com/16-channel-pwm-servo-driver).
- [adafruit/RTClib](https://github.com/adafruit/RTClib/tree/master).
- [adafruit/Adafruit-PWM-Servo-Driver-Library](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/tree/master).
