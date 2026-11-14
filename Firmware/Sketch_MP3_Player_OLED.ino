#include <U8g2lib.h>
#include <SPI.h>

U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ A2, /* dc=*/ A1, /* reset=*/ A0);

int buttonPrev = 2;
int buttonSelect = 3;
int buttonNext = 4;

bool lastPrev = HIGH;
bool lastSelect = HIGH;
bool lastNext = HIGH;

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  Serial.begin(9600);
  pinMode(buttonPrev, INPUT_PULLUP);
  pinMode(buttonSelect, INPUT_PULLUP);
  pinMode(buttonNext, INPUT_PULLUP);
  delay(200);                          // let the pins and 5V settle
  lastPrev = digitalRead(buttonPrev);  // start from the real state
  lastSelect = digitalRead(buttonSelect);
  lastNext = digitalRead(buttonNext);

}

void loop() {
  // put your main code here, to run repeatedly:
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);

  bool prev = digitalRead(buttonPrev);
  bool select = digitalRead(buttonSelect);
  bool next = digitalRead(buttonNext);
  u8g2.clearBuffer();
  if (lastPrev == HIGH && prev == LOW) {
    //toggle left in array
    //if array
    u8g2.drawStr(0, 15, "Prev Button Pressed");
    u8g2.sendBuffer();
    delay(1000);
    u8g2.clearBuffer();
  }

  if (lastSelect == HIGH && select == LOW) {
    u8g2.drawStr(0, 15, "Select Button Pressed");
    u8g2.sendBuffer();
    delay(1000);
    u8g2.clearBuffer();
  }

  if (lastNext == HIGH && next == LOW) {
    u8g2.drawStr(0, 15, "Next Button Pressed");
    u8g2.sendBuffer();
    delay(1000);
    u8g2.clearBuffer();
  }

  lastPrev = prev;
  lastSelect = select;
  lastNext = next;
}
