# Giới thiệu

Đây là đồng hồ hiển thị thời gian. Sử dụng mạch thời gian thực RTC DS3231 để lưu thời gian. Sử dụng các động cơ RC Servo để điều khiển từng thanh Segment, được điều khiển bởi bo mạch PCA9685.

Bằng cách mô phỏng *"Led 7 đoạn"*. Để hiển thị được **"GIỜ : PHÚT"**, đồng hồ này cần 4 con Led 7 đoạn. Như cái tên, mỗi con Led có 7 thanh đoạn để hiển thị, sẽ cần tương ứng 7 Servo. Như vậy chúng ta sẽ cần tất cả 28 Servo!

## Phần cứng

- [Mạch Điều Khiển 16 Chanel PWM PCA9685](https://hshop.vn/products/mach-xuat-16-xung-pwmgiao-tiep-i2c).
- [Mạch Thời Gian Thực RTC DS3231](https://hshop.vn/products/mach-thoi-gian-thuc-rtc-ds3231).
- [Động Cơ RC Servo 9G](https://hshop.vn/products/dong-co-rc-servo-9g).
- [Mạch Vietduino Uno](https://hshop.vn/products/mach-vietduino-uno-usb-c-arduino-uno-compatible).

## Sơ đồ kết nối

> **Còi Buzzer** hiện đang được kết nối với chân `D9` của bo **Arduino Uno**.
>
> ---
>
> Kết nối một **Nút nhấn** với chân `Reset` của bo **Arduino Uno**.
>
> ---
>
> Địa chỉ I2C mặc định của Driver là `0x40`. Mỗi Driver có 16 kênh. Vậy nên mình cần dùng 2 Driver, để mỗi Driver đảm nhiệm điều khiển 14 Servo, tương ứng 2 Digit 7Seg.
>
> Driver có địa chỉ `0x40` dùng cho ***"Digit Hour"***. Còn Driver có địa chỉ `0x41` (hàn nối **cầu A0**) dùng cho ***"Digit Minute"***.
>
> |Driver|Arduino|
> |------|-------|
> |VCC|5V
> |SDA|SDA - `A4`
> |SCL|SCL - `A5`
> |GND|GND
>
> Chân `OE` của 2 Driver nối với nhau. Chân này mặc định là ở mức **LOW**. Khi chân này được kích lên mức **HIGH**, nó sẽ vô hiệu hóa đầu ra của tất cả các kênh. Mình ko sử dụng, nên cứ để vậy, tức là cho phép sử dụng các kênh.
>
> Chân `V+` của 2 Driver cũng được nối với nhau. Đây là chân dùng để cấp nguồn riêng cho các Servo. Bạn có thể cấp tận 6V hoặc có thể tới 12V, miễn là mức nguồn Servo yêu cầu.
>
> `V+` cũng chính là chân mình cho nhận nguồn trực tiếp, ko phải từ nguồn **5V** trên bo mạch **Arduino Uno**. Đồng thời cũng chính là nguồn cần thêm tụ vào, để giúp cho nguồn cấp được ổn định.

## Các bước lắp đặt

> Tốt nhất trước khi gắn các thanh đoạn Segment vào cho mỗi Servo. Từng Servo phải được *"gắn nóng"*. Tức bạn nên cấp một mức xung 1500, tương ứng góc 90º để trục Servo quay đến góc giữa, lúc này mới gắn trục cánh tay vào Servo và cả thanh đoạn Segment.
>
> <u>Tip</u>: dùng băng keo giấy dán nhãn tên cho từng Servo, hoặc trên dây của nó, để tránh việc cắm sai Servo vào khác kênh điều khiển.

## Các vấn đề gặp phải

Ngày 22/08/23

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

Ngày 23/08/23

> Với sự giúp đỡ của anh Ngọc. Phần cứng đã được hoàn thiện chắc chắn hơn về nguồn cấp. Các dây điện cấp nguồn được thay bằng loại lớn hơn, đảm bảo chịu dòng tốt.
>
> So với cái lúc mà chưa thay dây, điện áp đo được trên Driver lẫn Arduino dao động rất nhiều, mà đấy là đo bằng VOM đấy. Sau đó thì đỡ lại nhiều rồi, cơ mà vẫn còn tình trạng chạy loạn.
>
> Mình đọc lại thông tin kỹ thuật của Driver thì thấy có đề cập đến việc tăng dung tích tụ tương ứng theo số lượng Servo sử dụng. Anh Ngọc hàn thêm mấy con tụ 470uF nâng tổng lên 1470uF cho mỗi Driver.
>
> Theo lời khuyên là 100uF cho mỗi con, tức 14 con thì 1400uF là được. Kết quả phần nguồn đã bớt dao động đi rất nhiều, chỉ còn quanh quẩn khoản 0,1V.
>
> Tuy nhiên vấn đề chạy loạn vẫn còn, và đó là lúc mình nhận thấy chính hàm `sleep()`. Một chức năng có sẵn của thư viện Driver là nguyên nhân gây ra vấn đề này. <u>Mình đã bỏ việc cho Driver ngủ, thay vào đó mình tự xuất các chân với PWM 0% sau mỗi cuối giai đoạn</u>. Cuối cùng vấn đề đã được giải quyết!

## Hình ảnh dự án

> `01` - Ghi chú cho từng Segment
>
> <img src="./Img/01 - Ghi chú cho từng Segment.jpg" width="100%">
>
> `02` - Ghi chú cho từng Servo
>
> <img src="./Img/02 - Ghi chú cho từng Servo.jpg" width="100%">
>
> `03` - Chi tiết khớp nối giữa Servo và thanh đoạn Segment
>
> <img src="./Img/03 - Chi tiết khớp nối giữa Servo và thanh đoạn Segment.jpg" width="100%">
>
> `04` - Lắp đặt 7 Servo cho mỗi Digit
>
> <img src="./Img/04 - Lắp đặt 7 Servo cho mỗi Digit.jpg" width="100%">
>
> `05` - Công tắc nguồn cho hệ thống
>
> <img src="./Img/05 - Công tắc nguồn cho hệ thống.jpg" width="100%">
>
> `06` - Nút Reset ... boom
>
> <img src="./Img/06 - Nút Reset ... boom.jpg" width="100%">
>
> `07` - Tụ hỗ trợ thêm cho nguồn Servo
>
> <img src="./Img/07 - Tụ hỗ trợ thêm cho nguồn Servo.jpg" width="100%">
>
> `08` - Mặt sau, lắp ráp xong
>
> <img src="./Img/08 - Mặt sau, lắp ráp xong.jpg" width="100%">
>
> `09` - Mặt trước, lắp ráp xong
>
> <img src="./Img/09 - Mặt trước, lắp ráp xong.jpg" width="100%">
>
> `10` - Lắp đặt hoàn chỉnh ... chạy
>
> <img src="./Img/10 - Lắp đặt hoàn chỉnh ... chạy.jpg" width="100%">
>

## Video dự án

> `(1)` Test thử tính năng chọn phần hiển thị các nội dung ngẫu nhiên khi mới khởi động.
>
> [Servo 7Seg Clock (1)](https://www.youtube.com/watch?v=wiTqnXfDZhE).
>
> `(2)` Test thử chạy hoạt động hiển thị giờ như bình thường, với thao tác nhấn nút Reset để xem hiệu ứng lúc đầu.
>
> [Servo 7Seg Clock (2)](https://www.youtube.com/watch?v=ybf7xXjfA1A).
>
> `(3)` Test thử tính năng cài đặt thời gian cho RTC và cả phần hiệu ứng âm thanh từ còi.
>
> [Servo 7Seg Clock (3)](https://www.youtube.com/watch?v=_DDI63OU2Bg).

## Các tính năng

> - Khi mới khởi động, sẽ hiển thị ngẫu nhiên nhiều nội dung, rồi mới chạy hiển thị thời gian. Có thể nhấn Reset để trải nghiệm lại cảm giác khởi động ấy.
> - Có thể vào chế độ cấu hình, bằng cách nhập lệnh `"enter"`. Và ngược lại nhập lệnh `"exit"` để thoát chế độ này và quay về chạy hiển thị thời gian.
> - Trong chế độ cấu hình, có thể cài đặt thời gian cho RTC bằng lệnh `"T-0:0:0"`.
> - Bên cạnh có thể xem các phần nội dung hiển thị ngẫu nhiên bằng lệnh `"D-0"`.
> - Ngoài ra khi đồng hồ chạy hiển thị thời gian, cứ mỗi **(1h)**, còi báo *"Tick...tick"* cho biết, còn mỗi **(15m)** báo *"Tick"*.

## Nguồn tài liệu

- [Adafruit PCA9685 16-Channel Servo Driver](https://learn.adafruit.com/16-channel-pwm-servo-driver).
- [adafruit/RTClib](https://github.com/adafruit/RTClib/tree/master).
- [adafruit/Adafruit-PWM-Servo-Driver-Library](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/tree/master).
