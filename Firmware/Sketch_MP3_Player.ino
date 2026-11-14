int buttonPrev = 2;
int buttonSelect = 3;
int buttonNext = 4;

bool lastPrev = HIGH;
bool lastSelect = HIGH;
bool lastNext = HIGH;

void setup() {
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
  bool prev = digitalRead(buttonPrev);
  bool select = digitalRead(buttonSelect);
  bool next = digitalRead(buttonNext);

  if (lastPrev == HIGH && prev == LOW) {
    Serial.println("Prev Button Pressed");
  }

  if (lastSelect == HIGH && select == LOW) {
    Serial.println("Select Button Pressed");
  }

  if (lastNext == HIGH && next == LOW) {
    Serial.println("Next Button Pressed");
  }

  lastPrev = prev;
  lastSelect = select;
  lastNext = next;
}



