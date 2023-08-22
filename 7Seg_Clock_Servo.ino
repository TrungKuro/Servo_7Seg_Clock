/**
 * (3) - Code hoàn chỉnh của dự án, với các tính năng sau:
 * |
 * Khi mới khởi động, mạch sẽ cho hiển thị ngẫu nhiên một nội dung nào đó
 * Trước khi bắt đầu chạy hiển thị TIME theo RTC
 * |
 * Để bật hoặc tắt tính năng Debug
 * Sử dụng hoặc vô hiệu hóa dòng code "#define ENABLE_DEBUG" ở file "PinConfig.h"
 * Khi mở Serial Monitor, chọn Baudrate 115200, chọn "No line ending"
 * |
 * Tất cả các động cơ Servo sẽ được "thả" hoàn toàn sau mỗi phút
 * Điều này giúp tăng độ bền của động cơ hơn nữa
 * |
 * → Nhập "enter" để [VÀO] chế độ cấu hình
 * → Nhập "exit" để [THOÁT] chế độ cấu hình
 *   |
 *   |  Trong chế độ cấu hình, các lệnh sau đây là phù hợp:
 *   |
 *   |  _ Nhập đúng cú pháp "T-00:00:00" để cài đặt thời gian cho RTC
 *   |  _ Nhập đúng cú pháp "D-0" để hiển thị các nội dung ngẫu nhiên do mình chọn
 */

/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */

#include "Control_Clock.h"

/* ------------------------------------------------------------------------- */
/*                                   OBJECT                                  */
/* ------------------------------------------------------------------------- */

// Khởi tạo Mạch thời gian thực
RTC_DS3231 rtc;

// Cài đặt địa chỉ I2C cho PCA9685
Adafruit_PWMServoDriver pwmH = Adafruit_PWMServoDriver(ADDRESS_H);
Adafruit_PWMServoDriver pwmM = Adafruit_PWMServoDriver(ADDRESS_M);

/* ------------------------------------------------------------------------- */
/*                                  VARIABLE                                 */
/* ------------------------------------------------------------------------- */

// Giá trị PWM để các "Hour Servo" làm "hiện" các thanh Segment
uint16_t segmentHOn[PIN_PCA9685] = {
    /////////////////////////////////////////////////// A -  B -  C -  D -  E -  F -  G
    290, 290, 320, 290, 280, 320, 295, // Hour Units:  00 - 01 - 02 - 03 - 04 - 05 - 06
    0, 0,                              //
    320, 290, 330, 315, 280, 320, 270, // Hour Tens:   09 - 10 - 11 - 12 - 13 - 14 - 15
};

// Giá trị PWM để các "Minute Servo" làm "hiện" các thanh Segment
uint16_t segmentMOn[PIN_PCA9685] = {
    ///////////////////////////////////////////////////// A -  B -  C -  D -  E -  F -  G
    300, 280, 320, 275, 290, 310, 290, // Minute Units:  00 - 01 - 02 - 03 - 04 - 05 - 06
    0, 0,                              //
    310, 275, 305, 290, 300, 300, 270, // Minute Tens:   09 - 10 - 11 - 12 - 13 - 14 - 15
};

// Giá trị PWM để các "Hour Servo" làm "ẩn" các thanh Segment
uint16_t segmentHOff[PIN_PCA9685] = {
    /////////////////////////////////////////////////// A -  B -  C -  D -  E -  F -  G
    110, 110, 490, 460, 110, 480, 470, // Hour Units:  00 - 01 - 02 - 03 - 04 - 05 - 06
    0, 0,                              //
    130, 120, 480, 490, 100, 480, 470, // Hour Tens:   09 - 10 - 11 - 12 - 13 - 14 - 15
};

// Giá trị PWM để các "Minute Servo" làm "ẩn" các thanh Segment
uint16_t segmentMOff[PIN_PCA9685] = {
    ///////////////////////////////////////////////////// A -  B -  C -  D -  E -  F -  G
    130, 120, 490, 450, 120, 470, 480, // Minute Units:  00 - 01 - 02 - 03 - 04 - 05 - 06
    0, 0,                              //
    120, 110, 470, 460, 130, 460, 460, // Minute Tens:   09 - 10 - 11 - 12 - 13 - 14 - 15
};

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
const bool digits[TOTAL_CHAR][SEGMENT] = {
    //////////////////////////////////// A - B - C - D - E - F - G
    {1, 1, 1, 1, 1, 1, 0}, // Digit 0  : .   .   .   .   .   .
    {0, 1, 1, 0, 0, 0, 0}, // Digit 1  :     .   .
    {1, 1, 0, 1, 1, 0, 1}, // Digit 2  : .   .       .   .       .
    {1, 1, 1, 1, 0, 0, 1}, // Digit 3  : .   .   .   .           .
    {0, 1, 1, 0, 0, 1, 1}, // Digit 4  :     .   .           .   .
    {1, 0, 1, 1, 0, 1, 1}, // Digit 5  : .       .   .       .   .
    {1, 0, 1, 1, 1, 1, 1}, // Digit 6  : .       .   .   .   .   .
    {1, 1, 1, 0, 0, 0, 0}, // Digit 7  : .   .   .
    {1, 1, 1, 1, 1, 1, 1}, // Digit 8  : .   .   .   .   .   .   .
    {1, 1, 1, 1, 0, 1, 1}, // Digit 9  : .   .   .   .       .   .
    ////////////////////////////////////
    {0, 1, 1, 0, 1, 1, 1}, // Kí tự 'H':     .   .       .   .   .
    {1, 0, 0, 1, 1, 1, 1}, // Kí tự 'E': .           .   .   .   .
    {0, 0, 0, 1, 1, 1, 0}, // Kí tự 'L':             .   .   .
    {1, 0, 0, 0, 1, 1, 1}, // Kí tự 'F': .   .           .   .   .
    {1, 1, 1, 0, 1, 1, 1}, // Kí tự 'A': .   .   .       .   .   .
    ////////////////////////////////////
    {0, 0, 0, 0, 0, 0, 1}, // Kí tự '-':                         . (CHAR_1)
    {0, 0, 0, 1, 0, 0, 0}, // Kí tự '_':             .             (CHAR_2)
    {0, 0, 0, 0, 0, 0, 0}, // Kí tự ' ':                           (CHAR_3)
    {1, 0, 0, 1, 1, 1, 0}, // Kí tự '[': .           .   .   .     (CHAR_4)
    {1, 1, 1, 1, 0, 0, 0}, // Kí tự ']': .   .   .   .             (CHAR_5)
    {1, 0, 0, 1, 0, 0, 0}, // Kí tự '=': .           .             (CHAR_6)
    {1, 1, 0, 0, 0, 1, 1}, // Kí tự 'º': .   .               .   . (CHAR_7)
    ////////////////////////////////////
    {1, 1, 1, 1, 1, 1, 1}, // Kí tự '8': .   .   .   .   .   .   . (CHAR_8)  - DEBUG
    {1, 1, 1, 1, 1, 1, 0}, // Kí tự 'O': .   .   .   .   .   .     (CHAR_9)  - DEBUG
    {0, 1, 1, 0, 0, 0, 0}, // Kí tự 'I':     .   .                 (CHAR_10) - DEBUG
    ////////////////////////////////////
    {1, 0, 0, 0, 1, 1, 0}, // Kí tự '7': .               .   .     (CHAR_11) - Kí tự '7' ngược
    {1, 0, 0, 0, 0, 0, 0}, // Kí tự '_': .                         (CHAR_12) - Kí tự '_' ngược
};

/* ------------------------------------------------------------------------- */

// Lưu trữ con số sẽ chuẩn bị hiển thị cho mỗi Digit
byte hourTens;
byte hourUnits;
byte minuteTens;
byte minuteUnits;

// Lưu con số hiện tại đang dùng hiển thị cho mỗi Digit
byte prevHourTens;
byte prevHourUnits;
byte prevMinuteTens;
byte prevMinuteUnits;

/* ------------------------------------------------------------------------- */

// Lưu trữ toàn bộ dữ liệu thời gian từ RTC
DateTime now;

// Giúp theo dõi thời gian cho việc thực hiện chu kỳ đọc RTC
unsigned long updateTime = 0;

/* ------------------------------------------------------------------------- */

// Bảng menu hiển thị ngẫu nhiên khi khởi động
enum menuDisplay
{
  FULL = 1, // Hiệu ứng riêng!
  HI,       //
  HELLO,    //
  FA,       //
  ALO,      //
  AH,       //
  NONE,     // Hiệu ứng riêng!
  CRY,      //
  BOX,      //
  HELL,     //
  SMILE,    //
  FROZEN,   //
  QUANTITY, // Tổng số menu
} whatDisplay;

// Cho phép hoặc ko chạy tính năng hiển thị thời gian
bool enableRun = false;

// Lưu dữ liệu nhận được từ người dùng
String inputData = "";

/* ------------------------------------------------------------------------- */
/*                                  FUNCTION                                 */
/* ------------------------------------------------------------------------- */

void displayRandom(int menuChosen)
{
  /* -------------------- Cho "ẩn" tất cả thanh Segment -------------------- */

  DEBUG_PRINTLN(F("Hide all Segment."));
  hide_all_segment(&pwmH, &pwmM);

  /* ---------- Cho "hiện" các thanh Segment theo cách ngẫu nhiên ---------- */

  switch (menuChosen)
  {
  case FULL:
    DEBUG_PRINTLN(F("Show all Segment."));
    show_all_segment(&pwmH, &pwmM);
    break;
  case HI:
    DEBUG_PRINTLN(F("Show 'HI'."));
    show_HI(&pwmH, &pwmM);
    break;
  case HELLO:
    DEBUG_PRINTLN(F("Show 'HELLO'."));
    show_HELLO(&pwmH, &pwmM);
    break;
  case FA:
    DEBUG_PRINTLN(F("Show 'FA'."));
    show_FA(&pwmH, &pwmM);
    break;
  case ALO:
    DEBUG_PRINTLN(F("Show 'ALO'."));
    show_ALO(&pwmH, &pwmM);
    break;
  case AH:
    DEBUG_PRINTLN(F("Show 'AH'."));
    show_AH(&pwmH, &pwmM);
    break;
  case NONE:
    DEBUG_PRINTLN(F("Show None."));
    show_none(&pwmH, &pwmM);
    break;
  case CRY:
    DEBUG_PRINTLN(F("Show T_T."));
    show_cry(&pwmH, &pwmM);
    break;
  case BOX:
    DEBUG_PRINTLN(F("Show Box."));
    show_box(&pwmH, &pwmM);
    break;
  case HELL:
    DEBUG_PRINTLN(F("Show 'HELL'."));
    show_HELL(&pwmH, &pwmM);
    break;
  case SMILE:
    DEBUG_PRINTLN(F("Show Smile."));
    show_smile(&pwmH, &pwmM);
    break;
  case FROZEN:
    DEBUG_PRINTLN(F("Show Frozen."));
    show_frozen(&pwmH, &pwmM);
    break;
  }
}

/* ------------------------------------------------------------------------- */
/*                             CONFIG (ONE TIME!)                            */
/* ------------------------------------------------------------------------- */

void setup()
{
  // Khởi động Serial (Debug)
  DEBUG_BEGIN(115200);

  // Khởi động RTC
  DEBUG_PRINT(F("Init RTC..."));
  rtc.begin();
  DEBUG_PRINTLN(F("done."));

  // Khởi động còi báo
  DEBUG_PRINT(F("Init Buzz..."));
  pinMode(PIN_BUZZ, OUTPUT);
  digitalWrite(PIN_BUZZ, LOW);
  DEBUG_PRINTLN(F("done."));

  // Khởi động PCA9685
  DEBUG_PRINT(F("Init PCA9685..."));
  pwmH.begin();
  pwmM.begin();
  pwmH.setOscillatorFrequency(DRIVER_FREQ);
  pwmM.setOscillatorFrequency(DRIVER_FREQ);
  pwmH.setPWMFreq(SERVO_FREQ);
  pwmM.setPWMFreq(SERVO_FREQ);
  DEBUG_PRINTLN(F("done."));

  /**
   * Chọn một menu ngẫu nhiên để hiển thị khi mới khởi động
   */
  now = rtc.now();                   // Cập nhập dữ liệu thời gian từ RTC
  randomSeed(now.unixtime());        // Cấy mầm tạo số ngẫu nhiên - "Since midnight 1/1/1970"
  whatDisplay = random(1, QUANTITY); // Lấy số ngẫu nhiên, lần 1 (bỏ qua)
  whatDisplay = random(1, QUANTITY); // Lấy số ngẫu nhiên, lần 2 (sử dụng)
  displayRandom(whatDisplay);        //

  /* ----------------------------------------------------------------------- */

  // Cho phép hiển thị thời gian
  enableRun = true;

  // Đợi khoảng thời gian trước khi vào chương trình chính
  delay(TIME_WAIT);
}

/* ------------------------------------------------------------------------- */
/*                                    MAIN                                   */
/* ------------------------------------------------------------------------- */

void loop()
{
  /* --------------- Xử lý nếu có tín hiệu gửi từ người dùng --------------- */

  if (DEBUG_AVAILABLE() > 0)
  {
    // Xóa dữ liệu cũ và lưu chuỗi dữ liệu mới nhận được
    inputData = "";
    inputData = DEBUG_READ_STRING();

    if (inputData == "enter")
    {
      // Vào chế độ cấu hình, ko chạy hiển thị thời gian
      enableRun = false;
      DEBUG_PRINTLN(F("=== ENTER ==="));
    }
    else if (inputData == "exit")
    {
      // Thoát khỏi chế độ cấu hình, quay lại hoạt động như bình thường
      enableRun = true;
      DEBUG_PRINTLN(F("=== EXIT ==="));
    }
  }

  /* ---------------------- Chế độ hiển thị thời gian ---------------------- */

  if (enableRun)
  {
    /**
     * Cập nhập dữ liệu thời gian mới nhất từ RTC
     */
    if (millis() - updateTime >= TIME_UPDATE)
    {
      // Lưu mốc thời gian mới gần nhất
      updateTime = millis();

      // Cập nhập dữ liệu thời gian từ RTC
      now = rtc.now();
      DEBUG_PRINT(F("→ "));
      DEBUG_PRINT(now.hour(), DEC);
      DEBUG_PRINT(F(":"));
      DEBUG_PRINT(now.minute(), DEC);
      DEBUG_PRINT(F(":"));
      DEBUG_PRINTLN(now.second(), DEC);
    }

    /**
     * Nếu phát hiện giá trị PHÚT thay đổi
     * Cho cập nhập hiển thị thời gian mới lên đồng hồ
     */
    if ((now.minute() % 10) != prevMinuteUnits)
    {
      DEBUG_PRINTLN(F("Update Time."));

      // Đánh thức PCA9685 "dậy"
      pwmH.wakeup();
      pwmM.wakeup();
      delay(TIME_SLOW);

      /* ------------------------------------------------------------------- */

      // Tách giá trị "Hour" thành 2 Digit, cho hàng chục (TEN) và hàng đơn vị (UNIT)
      hourTens = now.hour() / 10;
      hourUnits = now.hour() % 10;

      // Tách giá trị "Minute" thành 2 Digit, cho hàng chục (TEN) và hàng đơn vị (UNIT)
      minuteTens = now.minute() / 10;
      minuteUnits = now.minute() % 10;

      /* ------------------------------------------------------------------- */

      // Còi báo các mốc thời gian
      switch (now.minute())
      {
      case 0:
        tickTick(); // Báo sau mỗi (1h) trôi qua
        break;
      case 15:
      case 30:
      case 45:
        tick(); // Báo sau mỗi (15m) trôi qua
        break;
      }

      /* ------------------------------------------------------------------- */

      // Di chuyển các đoạn liền kề (B) và (F) để né đoạn giữa (G), nếu cần thiết
      moveMiddle(&pwmH, &pwmM);

      // Cho hiển thị các đoạn còn lại từ (A), (B), (C), (D), (E), (F)
      updateDisplay(&pwmH, &pwmM);

      // Lưu tạm giá trị các Digit hiện đang dùng
      prevHourTens = hourTens;
      prevHourUnits = hourUnits;
      prevMinuteTens = minuteTens;
      prevMinuteUnits = minuteUnits;

      /* ------------------------------------------------------------------- */

      // Đưa PCA9685 về chế độ "ngủ"
      delay(TIME_SLOW);
      pwmH.sleep();
      pwmM.sleep();
    }
  }

  /* --------------------------- Chế độ cấu hình --------------------------- */

  else
  {
    /* ------------------- Nhập đúng cú pháp "T-00:00:00" ------------------ */
    if (inputData[0] == 'T')
    {
      // Xác định vị trí của một số kí tự
      byte blank_1 = inputData.indexOf("-");
      byte blank_2 = inputData.indexOf(":", blank_1 + 1);
      byte blank_3 = inputData.indexOf(":", blank_2 + 1);

      // Xác định giá trị GIỜ : PHÚT : GIÂY
      DEBUG_PRINT(F("→ "));
      DEBUG_PRINTLN(inputData);
      int hour = inputData.substring(blank_1 + 1, blank_2).toInt();
      DEBUG_PRINT(F("Hour   : "));
      DEBUG_PRINTLN(hour);
      int minute = inputData.substring(blank_2 + 1, blank_3).toInt();
      DEBUG_PRINT(F("Minute : "));
      DEBUG_PRINTLN(minute);
      int second = inputData.substring(blank_3 + 1).toInt();
      DEBUG_PRINT(F("Second : "));
      DEBUG_PRINTLN(second);

      // Cài đặt thời gian cho RTC
      rtc.adjust(DateTime(2023, 8, 21, hour, minute, second));
      DEBUG_PRINTLN(F("Set Time OK!"));
    }
    /* ---------------------- Nhập đúng cú pháp "D-0" ---------------------- */
    else if (inputData[0] == 'D')
    {
      // Xác định vị trí của một số kí tự
      byte blank_1 = inputData.indexOf("-");

      // Xác định giá trị menu
      DEBUG_PRINT(F("→ "));
      DEBUG_PRINTLN(inputData);
      int menu = inputData.substring(blank_1 + 1).toInt();
      DEBUG_PRINT(F("Display: "));
      DEBUG_PRINTLN(menu);

      // Đánh thức PCA9685 "dậy"
      pwmH.wakeup();
      pwmM.wakeup();
      delay(TIME_SLOW);

      // Cho hiển thị theo menu đã chọn
      displayRandom(menu);

      // Đưa PCA9685 về chế độ "ngủ"
      delay(TIME_SLOW);
      pwmH.sleep();
      pwmM.sleep();
    }
    /* ---------------------- Thêm các cú pháp cần... ---------------------- */
    // else if (){}
    /* --------------------------------------------------------------------- */
    inputData = "";
  }
}
