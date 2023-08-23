#ifndef _CONTROL_CLOCK_H_
#define _CONTROL_CLOCK_H_

/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */

// https://github.com/adafruit/RTClib/tree/master
#include "RTClib.h"

// https://github.com/adafruit/Adafruit_BusIO
// https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/tree/master
#include "Adafruit_PWMServoDriver.h"

#include "Pin_Config.h"

/* ------------------------------------------------------------------------- */
/*                                  VARIABLE                                 */
/* ------------------------------------------------------------------------- */

extern uint16_t segmentHOn[PIN_PCA9685];
extern uint16_t segmentMOn[PIN_PCA9685];
extern uint16_t segmentHOff[PIN_PCA9685];
extern uint16_t segmentMOff[PIN_PCA9685];

extern const bool digits[TOTAL_CHAR][SEGMENT];

extern byte hourTens;
extern byte hourUnits;
extern byte minuteTens;
extern byte minuteUnits;

extern byte prevHourTens;
extern byte prevHourUnits;
extern byte prevMinuteTens;
extern byte prevMinuteUnits;

/* ------------------------------------------------------------------------- */
/*                                  FUNCTION                                 */
/* ------------------------------------------------------------------------- */

// Cho "ẩn" tất cả thanh Segment
void hide_all_segment(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM);

/* ------------------------------------------------------------------------- */

// Cho "hiện" tất cả thanh Segment
void show_all_segment(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM);

// Cho "hiện" chữ "HI"
void show_HI(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM);

// Cho "hiện" chữ "HELLO"
void show_HELLO(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM);

// Cho "hiện" chữ "FA"
void show_FA(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM);

// Cho "hiện" chữ "ALO"
void show_ALO(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM);

// Cho "hiện" chữ "AH"
void show_AH(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM);

// Cho "hiện" nội dung trống
void show_none(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM);

// Cho "hiện" chữ "HELL"
void show_HELL(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM);

// Cho "hiện" mặt cười
void show_smile(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM);

// Cho "hiện" mặt khóc
void show_cry(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM);

// Cho "hiện" hình cái hộp
void show_box(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM);

// Cho "hiện" mặt bị đơ
void show_frozen(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM);

/* ------------------------------------------------------------------------- */

// Di chuyển các đoạn liền kề để cho đoạn giữa di chuyển
void moveMiddle(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM);

// Cập nhập hiển thị thời gian mới
void updateDisplay(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM);

/* ------------------------------------------------------------------------- */

// Nhận giá trị hiển thị cho Digit "Minute" hàng đơn vị
void displayMU(Adafruit_PWMServoDriver *ptrM, byte number);

// Nhận giá trị hiển thị cho Digit "Minute" hàng chục
void displayMT(Adafruit_PWMServoDriver *ptrM, byte number);

// Nhận giá trị hiển thị cho Digit "Hour" hàng đơn vị
void displayHU(Adafruit_PWMServoDriver *ptrH, byte number);

// Nhận giá trị hiển thị cho Digit "Hour" hàng chục
void displayHT(Adafruit_PWMServoDriver *ptrH, byte number);

/* ------------------------------------------------------------------------- */

// Tick!
void tick();

// Tick tick!
void tickTick();

/* ------------------------------------------------------------------------- */

// Thả lỏng các Servo
void release(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM);

/* ------------------------------------------------------------------------- */

#endif