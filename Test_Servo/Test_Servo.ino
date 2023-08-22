/**
 * (1) - Code này giúp mình tinh chỉnh cho từng Servo
 * Để xác định được giá trị PWM đúng, giúp Servo "đóng" và "mở" thanh đoạn Segment
 * |
 * Mở Termite hoặc Serial Monitor
 * Chọn Baudrate 115200 và "Append Nothing"
 * |
 * Nếu người dùng nhập đúng cú pháp là...
 * → "H[servo]:[pulse]"
 * → "M[servo]:[pulse]"
 * |
 * Mạch sẽ điều khiển theo thông tin người dùng nhập
 * _ Trong đó, "H" là cho bên "Servo Hour", còn "M" là cho bên "Servo Minute"
 * _ [servo] có giá trị trong khoảng [0-15]
 * _ [pulse] có giá trị trong khoảng [0-4095]
 */

/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */

#include "Adafruit_PWMServoDriver.h"

/* ------------------------------------------------------------------------- */
/*                                   DEFINE                                  */
/* ------------------------------------------------------------------------- */

// Mỗi bo PCA9685 có 1 địa chỉ I2C duy nhất, mặc định ban đầu là 0x40
#define ADDRESS_H 0x40
#define ADDRESS_M 0x41

// Cài đặt tần số PWM tối đa. Đơn vị (Hz).
#define SERVO_FREQ 50

// Cài đặt tần số bộ dao động bên trong, lý thuyết là 25MHz. Đơn vị (Hz).
#define DRIVER_FREQ 27000000

/* ------------------------------------------------------------------------- */
/*                                   OBJECT                                  */
/* ------------------------------------------------------------------------- */

// Cài đặt địa chỉ I2C cho PCA9685
Adafruit_PWMServoDriver pwmH = Adafruit_PWMServoDriver(ADDRESS_H);
Adafruit_PWMServoDriver pwmM = Adafruit_PWMServoDriver(ADDRESS_M);

// Lưu dữ liệu nhận được từ người dùng
String inputData = "";

// Lưu số thứ tự của kênh Servo hiện tại đang chọn
uint16_t servo;

// Mỗi bo mạch PCA9685 điều khiển được 16 kênh Servo
uint16_t pulse_H[16] = {0};
uint16_t pulse_M[16] = {0};

/* ------------------------------------------------------------------------- */
/*                             CONFIG (ONE TIME!)                            */
/* ------------------------------------------------------------------------- */

void setup()
{
  // Khởi động Serial
  Serial.begin(115200);

  // Khởi động PCA9685
  pwmH.begin();
  pwmM.begin();
  pwmH.setOscillatorFrequency(DRIVER_FREQ);
  pwmM.setOscillatorFrequency(DRIVER_FREQ);
  pwmH.setPWMFreq(SERVO_FREQ);
  pwmM.setPWMFreq(SERVO_FREQ);
}

/* ------------------------------------------------------------------------- */
/*                                    MAIN                                   */
/* ------------------------------------------------------------------------- */

void loop()
{
  // Chờ cho đến khi có tín hiệu gửi từ người dùng
  while (Serial.available() == 0)
  {
  }

  // Lưu dữ liệu nhận được
  inputData = Serial.readString();

  /**
   * Nếu người dùng nhập "ok"
   * Sẽ cho in các thông số PWM đang dùng hiện tại
   * Của từng Servo của tất cả các đoạn của Led 7 đoạn
   */
  if (inputData == "ok")
  {
    Serial.print("=== Servo Hour (");
    Serial.print(ADDRESS_H, HEX);
    Serial.println(") ===");
    for (int i = 0; i < 16; i++)
    {
      Serial.print(pulse_H[i]);
      Serial.print(", ");
    }
    Serial.println();

    //

    Serial.print("=== Servo Minute (");
    Serial.print(ADDRESS_M, HEX);
    Serial.println(") ===");
    for (int i = 0; i < 16; i++)
    {
      Serial.print(pulse_M[i]);
      Serial.print(", ");
    }
    Serial.println();
  }
  /**
   * Nếu người dùng nhập đúng cú pháp là...
   * → "H[servo]:[pulse]"
   * → "M[servo]:[pulse]"
   *
   * Mạch sẽ điều khiển theo thông tin người dùng nhập
   * _ Trong đó, "H" là cho bên "Servo Hour", còn "M" là cho bên "Servo Minute"
   * _ [servo] có giá trị trong khoảng [0-15]
   * _ [pulse] có giá trị trong khoảng [0-4095]
   */
  else
  {
    // Xác định vị trí của kí tự ":"
    int blank = inputData.indexOf(":");

    // Hiển thị, cho biết thông tin người dùng vừa nhập
    Serial.print("=== ");
    Serial.println(inputData);

    // Xác định Servo đang đề cập...
    servo = inputData.substring(1, blank).toInt();

    // Xác định số xung PWM sẽ cấp cho Servo đó...
    // Và kích hoạt Servo đó với số xung PWM đã chọn!
    if (inputData[0] == 'H')
    {
      pulse_H[servo] = inputData.substring(blank + 1).toInt();
      pwmH.setPWM(servo, 0, pulse_H[servo]);
    }
    else if (inputData[0] == 'M')
    {
      pulse_M[servo] = inputData.substring(blank + 1).toInt();
      pwmM.setPWM(servo, 0, pulse_M[servo]);
    }
  }

  // Xóa dữ liệu, chuẩn bị cho đợt thiết lập mới
  inputData = "";
}