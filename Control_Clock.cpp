/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */

#include "Control_Clock.h"

/* ------------------------------------------------------------------------- */
/*                                  FUNCTION                                 */
/* ------------------------------------------------------------------------- */

/**
 * Giải thích chức năng của hàm...
 *
 * setPWM(uint8_t num, uint16_t on, uint16_t off)
 * 'num'  : một trong các kênh đầu ra PWM, được đánh số từ 0 đến 15
 * 'on'   : tại một thời điểm trong chu kỳ 4096 phần, xung được kích từ LOW lên HIGH
 * 'off'  : tại một thời điểm trong chu kỳ 4096 phần, xung được kích từ HIGH xuống LOW
 */

/* --------------------- Cho "ẩn" tất cả thanh Segment --------------------- */

// Hiển thị "  :  " → Hiệu ứng riêng!
void hide_all_segment(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM)
{
  for (int i = 0; i < PIN_PCA9685; i++)
  {
    ptrH->setPWM(i, 0, segmentHOff[i]);
    delay(TIME_SLOW);
    ptrM->setPWM(i, 0, segmentMOff[i]);
    delay(TIME_SLOW);
  }
  //
  prevHourTens = CHAR_3;
  prevHourUnits = CHAR_3;
  prevMinuteTens = CHAR_3;
  prevMinuteUnits = CHAR_3;
}

/* -------------------- Cho "hiện" tất cả thanh Segment -------------------- */

// Hiển thị "88:88" → Hiệu ứng riêng!
void show_all_segment(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM)
{
  for (int i = (PIN_PCA9685 - 1); i >= 0; i--)
  {
    ptrH->setPWM(i, 0, segmentHOn[i]);
    delay(TIME_SLOW);
    ptrM->setPWM(i, 0, segmentMOn[i]);
    delay(TIME_SLOW);
  }
  //
  prevHourTens = CHAR_8;
  prevHourUnits = CHAR_8;
  prevMinuteTens = CHAR_8;
  prevMinuteUnits = CHAR_8;
}

/* -------------------------- Cho "hiện" chữ "HI" -------------------------- */

// Hiển thị "HI:II"
void show_HI(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM)
{
  displayHT(ptrH, CHAR_H);
  displayHU(ptrH, CHAR_10);
  //
  displayMT(ptrM, CHAR_10);
  displayMU(ptrM, CHAR_10);
}

/* ------------------------- Cho "hiện" chữ "HELLO" ------------------------ */

// Hiển thị "HE:LO"
void show_HELLO(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM)
{
  displayHT(ptrH, CHAR_H);
  displayHU(ptrH, CHAR_E);
  //
  displayMT(ptrM, CHAR_L);
  displayMU(ptrM, CHAR_9);
}

/* -------------------------- Cho "hiện" chữ "FA" -------------------------- */

// Hiển thị "HI:FA"
void show_FA(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM)
{
  displayHT(ptrH, CHAR_H);
  displayHU(ptrH, CHAR_10);
  //
  displayMT(ptrM, CHAR_F);
  displayMU(ptrM, CHAR_A);
}

/* -------------------------- Cho "hiện" chữ "ALO" ------------------------- */

// Hiển thị "_A:LO"
void show_ALO(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM)
{
  displayHT(ptrH, CHAR_2);
  displayHU(ptrH, CHAR_A);
  //
  displayMT(ptrM, CHAR_L);
  displayMU(ptrM, CHAR_9);
}

/* -------------------------- Cho "hiện" chữ "AH" -------------------------- */

// Hiển thị "AH:HH"
void show_AH(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM)
{
  displayHT(ptrH, CHAR_A);
  displayHU(ptrH, CHAR_H);
  //
  displayMT(ptrM, CHAR_H);
  displayMU(ptrM, CHAR_H);
}

/* ----------------------- Cho "hiện" nội dung trống ----------------------- */

// Hiển thị "--:--" → Hiệu ứng riêng!
void show_none(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM)
{
  ptrH->setPWM(HT_G, 0, segmentHOn[HT_G]);
  delay(TIME_SLOW);
  ptrH->setPWM(HU_G, 0, segmentHOn[HU_G]);
  delay(TIME_SLOW);
  ptrM->setPWM(MT_G, 0, segmentMOn[MT_G]);
  delay(TIME_SLOW);
  ptrM->setPWM(MU_G, 0, segmentMOn[MU_G]);
  delay(TIME_SLOW);
  //
  prevHourTens = CHAR_1;
  prevHourUnits = CHAR_1;
  prevMinuteTens = CHAR_1;
  prevMinuteUnits = CHAR_1;
}

/* ------------------------- Cho "hiện" chữ "HELL" ------------------------- */

// Hiển thị "HE:LL"
void show_HELL(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM)
{
  displayHT(ptrH, CHAR_H);
  displayHU(ptrH, CHAR_E);
  //
  displayMT(ptrM, CHAR_L);
  displayMU(ptrM, CHAR_L);
}

/* -------------------------- Cho "hiện" mặt cười -------------------------- */

// Hiển thị " º:º "
void show_smile(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM)
{
  displayHT(ptrH, CHAR_3);
  displayHU(ptrH, CHAR_7);
  //
  displayMT(ptrM, CHAR_7);
  displayMU(ptrM, CHAR_3);
}

/* -------------------------- Cho "hiện" mặt khóc -------------------------- */

// Hiển thị "T_T" = "77:77"
void show_cry(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM)
{
  displayHT(ptrH, CHAR_13);
  displayHU(ptrH, CHAR_11);
  //
  displayMT(ptrM, CHAR_13);
  displayMU(ptrM, CHAR_11);
}

/* ------------------------ Cho "hiện" hình cái hộp ------------------------ */

// Hiển thị "[=:=]"
void show_box(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM)
{
  displayHT(ptrH, CHAR_4);
  displayHU(ptrH, CHAR_6);
  //
  displayMT(ptrM, CHAR_6);
  displayMU(ptrM, CHAR_5);
}

/* -------------------------- Cho "hiện" mặt bị đơ ------------------------- */

// Hiển thị "-_-" = "__:__"
void show_frozen(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM)
{
  displayHT(ptrH, CHAR_12);
  displayHU(ptrH, CHAR_2);
  //
  displayMT(ptrM, CHAR_2);
  displayMU(ptrM, CHAR_12);
}

/* --------- Di chuyển các đoạn liền kề để cho đoạn giữa di chuyển --------- */

void moveMiddle(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM)
{
  /**
   * Di chuyển các thanh đoạn liền kề với đoạn giữa (đoạn G)
   *
   * Nếu con số hiện tại chuẩn bị hiển thị, "number"
   * Với con số hiện tại đang hiển thị lúc này, "prevNumber"
   * Có sự thay đổi ở đoạn giữa (đoạn G)
   *
   * ---
   *
   * Và nếu các đoạn F và đoạn B đang hiển thị
   * Sẽ cho di chuyển chúng để "mở cửa" cho đoạn G di chuyển
   *
   * ---
   *
   * Cho di chuyển đoạn giữa (đoạn G) là "đóng" hoặc "mở"
   */

  /* -------------------- Cho Digit "Minute" hàng đơn vị ------------------- */

  if (digits[minuteUnits][SEG_G] != digits[prevMinuteUnits][SEG_G])
  {
    if (digits[prevMinuteUnits][SEG_B])
      ptrM->setPWM(MU_B, 0, segmentMOn[MU_B] - MID_OFFSET);
    delay(TIME_SLOW);
    if (digits[prevMinuteUnits][SEG_G])
      ptrM->setPWM(MU_F, 0, segmentMOn[MU_F] + MID_OFFSET);
    delay(TIME_SLOW);
  }
  //
  if (digits[minuteUnits][SEG_G])
    ptrM->setPWM(MU_G, 0, segmentMOn[MU_G]);
  else
    ptrM->setPWM(MU_G, 0, segmentMOff[MU_G]);
  delay(TIME_FAST);

  /* --------------------- Cho Digit "Minute" hàng chục -------------------- */

  if (digits[minuteTens][SEG_G] != digits[prevMinuteTens][SEG_G])
  {
    if (digits[prevMinuteTens][SEG_B])
      ptrM->setPWM(MT_B, 0, segmentMOn[MT_B] - MID_OFFSET);
    delay(TIME_SLOW);
    if (digits[prevMinuteTens][SEG_G])
      ptrM->setPWM(MT_F, 0, segmentMOn[MT_F] + MID_OFFSET);
    delay(TIME_SLOW);
  }
  //
  if (digits[minuteTens][SEG_G])
    ptrM->setPWM(MT_G, 0, segmentMOn[MT_G]);
  else
    ptrM->setPWM(MT_G, 0, segmentMOff[MT_G]);
  delay(TIME_FAST);

  /* --------------------- Cho Digit "Hour" hàng đơn vị -------------------- */

  if (digits[hourUnits][SEG_G] != digits[prevHourUnits][SEG_G])
  {
    if (digits[prevHourUnits][SEG_B])
      ptrH->setPWM(HU_B, 0, segmentHOn[HU_B] - MID_OFFSET);
    delay(TIME_SLOW);
    if (digits[prevHourUnits][SEG_G])
      ptrH->setPWM(HU_F, 0, segmentHOn[HU_F] + MID_OFFSET);
    delay(TIME_SLOW);
  }
  //
  if (digits[hourUnits][SEG_G])
    ptrH->setPWM(HU_G, 0, segmentHOn[HU_G]);
  else
    ptrH->setPWM(HU_G, 0, segmentHOff[HU_G]);
  delay(TIME_FAST);

  /* ---------------------- Cho Digit "Hour" hàng chục --------------------- */

  if (digits[hourTens][SEG_G] != digits[prevHourTens][SEG_G])
  {
    if (digits[prevHourTens][SEG_B])
      ptrH->setPWM(HT_B, 0, segmentHOn[HT_B] - MID_OFFSET);
    delay(TIME_SLOW);
    if (digits[prevHourTens][SEG_G])
      ptrH->setPWM(HT_F, 0, segmentHOn[HT_F] + MID_OFFSET);
    delay(TIME_SLOW);
  }
  //
  if (digits[hourTens][SEG_G])
    ptrH->setPWM(HT_G, 0, segmentHOn[HT_G]);
  else
    ptrH->setPWM(HT_G, 0, segmentHOff[HT_G]);
  delay(TIME_FAST);
}

/* -------------------- Cập nhập hiển thị thời gian mới -------------------- */

void updateDisplay(Adafruit_PWMServoDriver *ptrH, Adafruit_PWMServoDriver *ptrM)
{
  /**
   * Di chuyển các thanh đoạn còn lại của mỗi Digit
   * Từ đoạn A đến đoạn F, gồm (A, B, C, D, E, F)
   *
   * !!! Đoạn "i + BUFFER" giúp trỏ đến vị trí thanh đoạn Segment tương ứng
   *     Giữa bên Digit hàng đơn vị và Digit hàng chục
   */
  for (byte i = SEG_A; i <= SEG_F; i++)
  {
    // Cho Digit "Minute" hàng đơn vị
    if (digits[minuteUnits][i])
      ptrM->setPWM(i, 0, segmentMOn[i]);
    else
      ptrM->setPWM(i, 0, segmentMOff[i]);
    delay(TIME_FAST);

    // Cho Digit "Minute" hàng chục
    if (digits[minuteTens][i])
      ptrM->setPWM(i + BUFFER, 0, segmentMOn[i + BUFFER]);
    else
      ptrM->setPWM(i + BUFFER, 0, segmentMOff[i + BUFFER]);
    delay(TIME_FAST);

    // Cho Digit "Hour" hàng đơn vị
    if (digits[hourUnits][i])
      ptrH->setPWM(i, 0, segmentHOn[i]);
    else
      ptrH->setPWM(i, 0, segmentHOff[i]);
    delay(TIME_FAST);

    // Cho Digit "Hour" hàng chục
    if (digits[hourTens][i])
      ptrH->setPWM(i + BUFFER, 0, segmentHOn[i + BUFFER]);
    else
      ptrH->setPWM(i + BUFFER, 0, segmentHOff[i + BUFFER]);
    delay(TIME_FAST);
  }
}

/* ---------- Nhận giá trị hiển thị cho Digit "Minute" hàng đơn vị --------- */

void displayMU(Adafruit_PWMServoDriver *ptrM, byte number)
{
  if (digits[number][SEG_G] != digits[prevMinuteUnits][SEG_G])
  {
    if (digits[prevMinuteUnits][SEG_B])
      ptrM->setPWM(MU_B, 0, segmentMOn[MU_B] - MID_OFFSET);
    delay(TIME_SLOW);
    if (digits[prevMinuteUnits][SEG_G])
      ptrM->setPWM(MU_F, 0, segmentMOn[MU_F] + MID_OFFSET);
    delay(TIME_SLOW);
  }
  //
  if (digits[number][SEG_G])
    ptrM->setPWM(MU_G, 0, segmentMOn[MU_G]);
  else
    ptrM->setPWM(MU_G, 0, segmentMOff[MU_G]);
  delay(TIME_FAST);
  //
  for (byte i = SEG_A; i <= SEG_F; i++)
  {
    if (digits[number][i])
      ptrM->setPWM(i, 0, segmentMOn[i]);
    else
      ptrM->setPWM(i, 0, segmentMOff[i]);
    delay(TIME_FAST);
  }
  //
  prevMinuteUnits = number;
}

/* ----------- Nhận giá trị hiển thị cho Digit "Minute" hàng chục ---------- */

void displayMT(Adafruit_PWMServoDriver *ptrM, byte number)
{
  if (digits[number][SEG_G] != digits[prevMinuteTens][SEG_G])
  {
    if (digits[prevMinuteTens][SEG_B])
      ptrM->setPWM(MT_B, 0, segmentMOn[MT_B] - MID_OFFSET);
    delay(TIME_SLOW);
    if (digits[prevMinuteTens][SEG_G])
      ptrM->setPWM(MT_F, 0, segmentMOn[MT_F] + MID_OFFSET);
    delay(TIME_SLOW);
  }
  //
  if (digits[number][SEG_G])
    ptrM->setPWM(MT_G, 0, segmentMOn[MT_G]);
  else
    ptrM->setPWM(MT_G, 0, segmentMOff[MT_G]);
  delay(TIME_FAST);
  //
  for (byte i = SEG_A; i <= SEG_F; i++)
  {
    if (digits[number][i])
      ptrM->setPWM(i + BUFFER, 0, segmentMOn[i + BUFFER]);
    else
      ptrM->setPWM(i + BUFFER, 0, segmentMOff[i + BUFFER]);
    delay(TIME_FAST);
  }
  //
  prevMinuteTens = number;
}

/* ----------- Nhận giá trị hiển thị cho Digit "Hour" hàng đơn vị ---------- */

void displayHU(Adafruit_PWMServoDriver *ptrH, byte number)
{
  if (digits[number][SEG_G] != digits[prevHourUnits][SEG_G])
  {
    if (digits[prevHourUnits][SEG_B])
      ptrH->setPWM(HU_B, 0, segmentHOn[HU_B] - MID_OFFSET);
    delay(TIME_SLOW);
    if (digits[prevHourUnits][SEG_G])
      ptrH->setPWM(HU_F, 0, segmentHOn[HU_F] + MID_OFFSET);
    delay(TIME_SLOW);
  }
  //
  if (digits[number][SEG_G])
    ptrH->setPWM(HU_G, 0, segmentHOn[HU_G]);
  else
    ptrH->setPWM(HU_G, 0, segmentHOff[HU_G]);
  delay(TIME_FAST);
  //
  for (byte i = SEG_A; i <= SEG_F; i++)
  {
    if (digits[number][i])
      ptrH->setPWM(i, 0, segmentHOn[i]);
    else
      ptrH->setPWM(i, 0, segmentHOff[i]);
    delay(TIME_FAST);
  }
  //
  prevHourUnits = number;
}

/* ------------ Nhận giá trị hiển thị cho Digit "Hour" hàng chục ----------- */

void displayHT(Adafruit_PWMServoDriver *ptrH, byte number)
{
  if (digits[number][SEG_G] != digits[prevHourTens][SEG_G])
  {
    if (digits[prevHourTens][SEG_B])
      ptrH->setPWM(HT_B, 0, segmentHOn[HT_B] - MID_OFFSET);
    delay(TIME_SLOW);
    if (digits[prevHourTens][SEG_G])
      ptrH->setPWM(HT_F, 0, segmentHOn[HT_F] + MID_OFFSET);
    delay(TIME_SLOW);
  }
  //
  if (digits[number][SEG_G])
    ptrH->setPWM(HT_G, 0, segmentHOn[HT_G]);
  else
    ptrH->setPWM(HT_G, 0, segmentHOff[HT_G]);
  delay(TIME_FAST);
  //
  for (byte i = SEG_A; i <= SEG_F; i++)
  {
    if (digits[number][i])
      ptrH->setPWM(i + BUFFER, 0, segmentHOn[i + BUFFER]);
    else
      ptrH->setPWM(i + BUFFER, 0, segmentHOff[i + BUFFER]);
    delay(TIME_FAST);
  }
  //
  prevHourTens = number;
}

/* --------------------------------- Tick! --------------------------------- */

void tick()
{
  digitalWrite(PIN_BUZZ, HIGH);
  delay(50);
  digitalWrite(PIN_BUZZ, LOW);
}

/* ------------------------------- Tick tick! ------------------------------ */

void tickTick()
{
  digitalWrite(PIN_BUZZ, HIGH);
  delay(50);
  digitalWrite(PIN_BUZZ, LOW);
  delay(50);
  digitalWrite(PIN_BUZZ, HIGH);
  delay(50);
  digitalWrite(PIN_BUZZ, LOW);
}
