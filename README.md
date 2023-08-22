# Giới thiệu

Đây là đồng hồ hiển thị thời gian. Sử dụng mạch thời gian thực RTC DS3231 để lưu thời gian. Sử dụng các động cơ RC Servo để điều khiển từng thanh Segment, được điều khiển bởi bo mạch PCA9685.

Bằng cách mô phỏng *"Led 7 đoạn"*. Để hiển thị được **"GIỜ : PHÚT"**, đồng hồ này cần 4 con Led 7 đoạn. Như cái tên, mỗi con Led có 7 thanh đoạn để hiển thị, sẽ cần tương ứng 7 Servo. Như vậy chúng ta sẽ cần tất cả 28 Servo!

## Phần cứng

- [Mạch Điều Khiển 16 Chanel PWM PCA9685](https://hshop.vn/products/mach-xuat-16-xung-pwmgiao-tiep-i2c).
- [Mạch Thời Gian Thực RTC DS3231](https://hshop.vn/products/mach-thoi-gian-thuc-rtc-ds3231).
- [Động Cơ RC Servo 9G](https://hshop.vn/products/dong-co-rc-servo-9g).
- [Mạch Vietduino Uno](https://hshop.vn/products/mach-vietduino-uno-usb-c-arduino-uno-compatible).

## Sơ đồ kết nối

...

## Các bước lắp đặt

...

## Các vấn đề gặp phải

> Thật sự mình kiểm tra kĩ nhiều lần chương trình rồi, mình ko nghĩ vấn đề nằm ở *"giải thuật"* chương trình để làm cho đồng hồ có vấn đề đâu.
>
> ---
>
> Điều này làm mình nhớ lại cái sự kiện vào năm ngoái, năm 2022. Năm mà mình cố gắng hoàn thành cái dự án này trong vòng 2 ngày, để kịp trưng cho buổi sự kiện đầu tiên của MakerLab.
>
> Trước lúc mà làm kịp mình bị gặp vấn đề thỉnh thoảng các Servo chúng nó chạy loạn nhau cả lên, phá hỏng cấu trúc các đoạn Segment ko biết bao nhiêu lần.
>
> Nhớ ko lầm là cái lúc mình cố gắng làm cho chúng nó chạy đếm ngược ở phần khởi động ấy, mình cho chạy tất cả 4 Digit cùng lúc. Và kết quả là thỉnh thoảng chúng nó xảy ra hiện tượng chạy loạn lên.
>
> Sau nhiều lần bị mình rút ra được ấy là do phần nguồn ko đáp ứng ổn định làm cho Driver Servo chạy có vấn đề. Phải hồi sau đó mình thay đổi nguồn khỏe hơn cũng như chỗ cấp nguồn, mọi thứ mới chạy ổn được.
>
> ---
>
> Ở hiện tại (22/88/23), mình đang trong những giai đoạn cuối hoàn thiện nâng cấp dự án này. Thì lại gặp lại vấn đề này, thật sự là bây giờ phần dây kết nối phía sau bảng mạch nhiều quá, đâm ra mình phải tìm cách giải quyết trong chương trình thôi.
>
> <u>Cố gắng đừng để cho quá nhiều tên Servo chạy cùng một lúc</u>. Đấy chính là giải pháp hiện tại mình có thể nghĩ ra.

## Hình ảnh dự án

... hình

... video

## Các tính năng

> ...

## Nguồn tài liệu

- [Adafruit PCA9685 16-Channel Servo Driver](https://learn.adafruit.com/16-channel-pwm-servo-driver).
- [adafruit/RTClib](https://github.com/adafruit/RTClib/tree/master).
- [adafruit/Adafruit-PWM-Servo-Driver-Library](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/tree/master).
