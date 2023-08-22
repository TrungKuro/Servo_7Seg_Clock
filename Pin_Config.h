#ifndef _PIN_CONFIG_H_
#define _PIN_CONFIG_H_

/* ------------------------------------------------------------------------- */
/*                DEBUG (uncomment to open the Debug function)               */
/* ------------------------------------------------------------------------- */

//// Sử dụng Serial
#define ENABLE_DEBUG

#if defined(ENABLE_DEBUG)
#define Debug Serial
#define DEBUG_BEGIN(...) Debug.begin(__VA_ARGS__)
#define DEBUG_AVAILABLE(...) Debug.available(__VA_ARGS__)
#define DEBUG_READ(...) Debug.read(__VA_ARGS__)
#define DEBUG_READ_STRING(...) Debug.readString(__VA_ARGS__)
#define DEBUG_WRITE(...) Debug.write(__VA_ARGS__)
#define DEBUG_PRINT(...) Debug.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...) Debug.println(__VA_ARGS__)
#else
#define DEBUG_BEGIN(...)
#define DEBUG_AVAILABLE(...) -1
#define DEBUG_READ(...) ""
#define DEBUG_READ_STRING(...) ""
#define DEBUG_WRITE(...)
#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)
#endif

/* ------------------------------------------------------------------------- */
/*                                    NOTE                                   */
/* ------------------------------------------------------------------------- */

// DEBUG !!! Cần căn chỉnh PWM cho từng Servo ở cả 2 trạng thái ON (hiện) và OFF (ẩn)
//           Mỗi Servo điều khiển 1 thanh Segment
//           4 biến sau chứa các giá trị PWM thiết lập
//           "segmentHOn", "segmentMOn", "segmentHOff", "segmentMOff"

// DEBUG !!! Cần chỉnh số thứ tự các "#define CHAR_..."
//           Khớp theo biến "digits[][]"

// DEBUG !!! Nếu thêm kí tự nào hiển thị trên mỗi Digit
//           Phải cập nhập lại cho "#define TOTAL_CHAR"

/* ------------------------------------------------------------------------- */
/*                                   BUZZER                                  */
/* ------------------------------------------------------------------------- */

// Chân kết nối với còi báo
#define PIN_BUZZ 9

/* ------------------------------------------------------------------------- */
/*                                  PCA9685                                  */
/* ------------------------------------------------------------------------- */

/**
 * Mỗi bo PCA9685 có 1 địa chỉ I2C duy nhất, mặc định ban đầu là 0x40
 *
 * Tạo 1 đối tượng cho Driver "Hour" → 0x40
 * Tạo 1 đối tượng cho Driver "Minute" (A0 Address Jumper) → 0x41
 */
#define ADDRESS_H 0x40
#define ADDRESS_M 0x41

// Cài đặt tần số PWM tối đa. Đơn vị (Hz)
#define SERVO_FREQ 50

// Cài đặt tần số bộ dao động bên trong, lý thuyết là 25MHz. Đơn vị (Hz)
#define DRIVER_FREQ 27000000

/* ------------------------------------------------------------------------- */
/*                               LED 7 SEGMENT                               */
/* ------------------------------------------------------------------------- */

// [HẰNG SỐ CỨNG] ~ Tổng số các thanh đoạn Segment cho mỗi Digit
#define SEGMENT 7

// [HẰNG SỐ CỨNG] ~ Tổng số các thanh đoạn Segment cho 2 Digit
#define COUPLE_DIGIT 14

// [HẰNG SỐ CỨNG] ~ Tổng số chân của mạch Driver PCA9685
#define PIN_PCA9685 16

// [HẰNG SỐ MỀM] ~ Đệm "trỏ vị trí" chân kết nối các Servo
// Thay đổi dựa theo cấu hình "trỏ" chân bên dưới
#define BUFFER 9

/* -------------- Tất cả thanh Segment cho 2 digit của "Hour" -------------- */

// Hàng đơn vị (unit) của "Hour"
#define HU_A 0
#define HU_B 1
#define HU_C 2
#define HU_D 3
#define HU_E 4
#define HU_F 5
#define HU_G 6
// Hàng chục (ten) của "Hour"
#define HT_A 9
#define HT_B 10
#define HT_C 11
#define HT_D 12
#define HT_E 13
#define HT_F 14
#define HT_G 15

/* ------------- Tất cả thanh Segment cho 2 digit của "Minute" ------------- */

// Hàng đơn vị (unit) của "Minute"
#define MU_A 0
#define MU_B 1
#define MU_C 2
#define MU_D 3
#define MU_E 4
#define MU_F 5
#define MU_G 6
// Hàng chục (ten) của "Minute"
#define MT_A 9
#define MT_B 10
#define MT_C 11
#define MT_D 12
#define MT_E 13
#define MT_F 14
#define MT_G 15

/* ---------- Vị trí thứ tự các thanh Segment trong mảng [segment] --------- */

// Sử dụng cho biến digits[number][segment]
#define SEG_A 0
#define SEG_B 1
#define SEG_C 2
#define SEG_D 3
#define SEG_E 4
#define SEG_F 5
#define SEG_G 6

/* -------------- Vị trí thứ tự các kí tự trong mảng [number] -------------- */

// Tổng số kí tự mỗi Digit có thể hiển thị
#define TOTAL_CHAR 27

// Sử dụng cho biến digits[number][segment]
#define CHAR_H 10
#define CHAR_E 11
#define CHAR_L 12
#define CHAR_F 13
#define CHAR_A 14
////////////////////
#define CHAR_1 15 // '-'
#define CHAR_2 16 // '_'
#define CHAR_3 17 // ' '
#define CHAR_4 18 // '['
#define CHAR_5 19 // ']'
#define CHAR_6 20 // '='
#define CHAR_7 21 // 'º'
/////////////////////
#define CHAR_8 22  // '8'
#define CHAR_9 23  // 'O'
#define CHAR_10 24 // 'I'
/////////////////////
#define CHAR_11 25 // '7' ngược
#define CHAR_12 26 // '_' ngược

/* ----------------------------- Độ PWM bù trừ ----------------------------- */

// Giúp đoạn F và đoạn B "mở cổng" cho đoạn G di chuyển
#define MID_OFFSET 130

/* ------------------------------------------------------------------------- */
/*                                    TIME                                   */
/* ------------------------------------------------------------------------- */

// Khoảng nghỉ giữa phần khởi động và phần hiển thị TIME. Đơn vị (ms)
#define TIME_WAIT 2500

// Khoảng thời gian giữa mỗi lần cập nhập giá trị từ RTC. Đơn vị (ms)
#define TIME_UPDATE 1000

// Khoảng thời gian dừng giữa mỗi Segment. Đơn vị (ms)
#define TIME_FAST 25
#define TIME_SLOW 100

/* ------------------------------------------------------------------------- */

#endif