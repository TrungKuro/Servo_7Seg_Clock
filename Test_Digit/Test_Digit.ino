/**
 * (2) - Code này để kiểm tra khả năng hoạt động
 * Của từng khối Servo Led 7 đoạn, tất cả là 7 Servo
 * |
 * Để xem các Servo có hoạt động "đóng" - "mở" đúng
 * Với các thông số PWM đã thiết lập ko?
 */

/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */

// https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/tree/master
#include "Adafruit_PWMServoDriver.h"

/* ------------------------------------------------------------------------- */
/*                                   DEFINE                                  */
/* ------------------------------------------------------------------------- */

// Mỗi bo PCA9685 có 1 địa chỉ I2C duy nhất, mặc định ban đầu là 0x40
#define ADDRESS 0x40

// Cài đặt tần số PWM tối đa. Đơn vị (Hz)
#define SERVO_FREQ 50

// Cài đặt tần số bộ dao động bên trong, lý thuyết là 25MHz. Đơn vị (Hz)
#define DRIVER_FREQ 27000000

// Vị trí thứ tự các thanh Segment trong mảng [segment]
#define SEG_A 0
#define SEG_B 1 // Sử dụng
#define SEG_C 2
#define SEG_D 3
#define SEG_E 4
#define SEG_F 5 // Sử dụng
#define SEG_G 6 // Sử dụng

/* ------------------------------------------------------------------------- */
/*                                   OBJECT                                  */
/* ------------------------------------------------------------------------- */

// Cài đặt địa chỉ I2C cho PCA9685
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(ADDRESS);

// Giá trị PWM để Servo làm "hiện" các thanh Segment
const uint16_t segmentOn[7] = {290, 290, 300, 300, 300, 300, 310};
// Giá trị PWM để Servo làm "ẩn" các thanh Segment
const uint16_t segmentOff[7] = {500, 100, 480, 100, 130, 470, 120};

/**
 * digits[number][segment]
 * number : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
 * segment: A(0), B(1), C(2), D(3), E(4), F(5), G(6)
 *
 *  --      [A]
 * |  |   [F] [B]
 *  --  →   [G]
 * |  |   [E] [C]
 *  --      [D]
 *
 * Mảng [segment] chỉ có 2 giá trị:
 * 0 → ko cho phép hiện ("ẩn") các thanh Segment
 * 1 → cho phép "hiện" các thanh Segment
 *
 * Khi giá trị [segment] bằng...
 * 0 → sử dụng biến "segmentOff"
 * 1 → sử dụng biến "segmentOn"
 */
const bool digits[10][7] = {
    ////////////////////////////////// A - B - C - D - E - F - G
    {1, 1, 1, 1, 1, 1, 0}, // Digit 0: .   .   .   .   .   .
    {0, 1, 1, 0, 0, 0, 0}, // Digit 1:     .   .
    {1, 1, 0, 1, 1, 0, 1}, // Digit 2: .   .       .   .       .
    {1, 1, 1, 1, 0, 0, 1}, // Digit 3: .   .   .   .           .
    {0, 1, 1, 0, 0, 1, 1}, // Digit 4:     .   .           .   .
    {1, 0, 1, 1, 0, 1, 1}, // Digit 5: .       .   .       .   .
    {1, 0, 1, 1, 1, 1, 1}, // Digit 6: .       .   .   .   .   .
    {1, 1, 1, 0, 0, 0, 0}, // Digit 7: .   .   .
    {1, 1, 1, 1, 1, 1, 1}, // Digit 8: .   .   .   .   .   .   .
    {1, 1, 1, 1, 0, 1, 1}  // Digit 9: .   .   .   .       .   .
};

// Lưu con số hiện tại đang hiển thị
byte prevNumber;

// Độ PWM bù trừ
// Giúp đoạn F và đoạn B mở cổng cho đoạn G di chuyển
uint16_t midOffset = 100;

// Lưu dữ liệu nhận được từ người dùng
char incomingByte;

/* ------------------------------------------------------------------------- */
/*                                  FUNCTION                                 */
/* ------------------------------------------------------------------------- */

void display(byte number)
{
  /**
   * Di chuyển các thanh đoạn liền kề với đoạn giữa (đoạn G)
   *
   * Nếu con số hiện tại chuẩn bị hiển thị, "number"
   * Với con số hiện tại đang hiển thị lúc này, "prevNumber"
   * Có sự thay đổi ở đoạn giữa (đoạn G)
   *
   * Và nếu các đoạn F và đoạn B đang hiển thị
   * Sẽ cho di chuyển chúng để "mở cửa" cho đoạn G di chuyển
   */
  if (digits[number][SEG_G] != digits[prevNumber][SEG_G])
  {
    if (digits[prevNumber][SEG_B])
    {
      pwm.setPWM(SEG_B, 0, segmentOn[SEG_B] - midOffset);
    }
    if (digits[prevNumber][SEG_G])
    {
      pwm.setPWM(SEG_F, 0, segmentOn[SEG_F] + midOffset);
    }
  }
  delay(100);

  /**
   * Di chuyển thanh đoạn giữa (đoạn G)
   * Nếu con số này cần hiển thị
   */
  if (digits[number][SEG_G])
  {
    pwm.setPWM(SEG_G, 0, segmentOn[SEG_G]);
  }
  else
  {
    pwm.setPWM(SEG_G, 0, segmentOff[SEG_G]);
  }

  /**
   * Di chuyển các thanh đoạn còn lại
   * Từ đoạn A đến đoạn F, gồm (A, B, C, D, E, F)
   */
  for (byte i = SEG_A; i <= SEG_F; i++)
  {
    if (digits[number][i])
    {
      pwm.setPWM(i, 0, segmentOn[i]);
    }
    else
    {
      pwm.setPWM(i, 0, segmentOff[i]);
    }
    delay(10);
  }
}

/* ------------------------------------------------------------------------- */
/*                             CONFIG (ONE TIME!)                            */
/* ------------------------------------------------------------------------- */

void setup()
{
  // Khởi động Serial
  Serial.begin(115200);

  // Khởi động PCA9685
  pwm.begin();
  pwm.setOscillatorFrequency(DRIVER_FREQ);
  pwm.setPWMFreq(SERVO_FREQ);

  /**
   * Cho "hiện" tất cả thanh Segment (hiển thị "8")
   *
   * setPWM(uint8_t num, uint16_t on, uint16_t off)
   * 'num'  : một trong các kênh đầu ra PWM, được đánh số từ 0 đến 15
   * 'on'   : tại một thời điểm trong chu kỳ 4096 phần, xung được kích từ LOW lên HIGH
   * 'off'  : tại một thời điểm trong chu kỳ 4096 phần, xung được kích từ HIGH xuống LOW
   */
  for (int i = 0; i < 7; i++)
  {
    pwm.setPWM(i, 0, segmentOn[i]);
    delay(10);
  }
  prevNumber = 8;

  // Đợi ~2s trước khi vào chương trình chính
  delay(2000);
}

/* ------------------------------------------------------------------------- */
/*                                    MAIN                                   */
/* ------------------------------------------------------------------------- */

void loop()
{
  // Xử lý nếu có tín hiệu gửi từ người dùng
  if (Serial.available() > 0)
  {
    // Lưu dữ liệu nhận được
    incomingByte = Serial.read();

    // Cho biết nội dung dữ liệu đó
    Serial.print("I received: ");
    Serial.println(incomingByte);

    // Xử lý dữ liệu nhận được
    switch (incomingByte)
    {
    case '0':         // Nhập kí tự '0'
      display(0);     // Hiển thị số 0
      prevNumber = 0; // Cho lưu số đang hiển thị hiện tại
      break;
    case '1':
      display(1);
      prevNumber = 1;
      break;
    case '2':
      display(2);
      prevNumber = 2;
      break;
    case '3':
      display(3);
      prevNumber = 3;
      break;
    case '4':
      display(4);
      prevNumber = 4;
      break;
    case '5':
      display(5);
      prevNumber = 5;
      break;
    case '6':
      display(6);
      prevNumber = 6;
      break;
    case '7':
      display(7);
      prevNumber = 7;
      break;
    case '8':
      display(8);
      prevNumber = 8;
      break;
    case '9':
      display(9);
      prevNumber = 9;
    }
  }
}