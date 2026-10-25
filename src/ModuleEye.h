byte eyeIcon[8] = {B00000, B01110, B10001, B10101, B10001, B01110, B00000, B00000};

void solveEye(int tones[], int n, int decoys, int answer[]) {
  int table[3] = {3, 1, 4};
  for (int i = 0; i < n; i++) {
    answer[n - 1 - i] = table[tones[i]];
  }
}

int readButton() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      delay(50);
      while (digitalRead(buttonPins[i]) == LOW) {}
      return i + 1;
    }
  }
  return 0;
}

int toneFreq[3] = {262, 523, 1047};

void playSignal(int tones[], bool decoy[], int len) {
  for (int i = 0; i < len; i++) {
    tone(buzzerPin, toneFreq[tones[i]], 350);
    delay(390);
    if (decoy[i]) {
      tone(buzzerPin, 3000, 25);   // tick = fake tone
    }
    delay(300);
  }
}

void beep(int freq, int ms) {
  tone(buzzerPin, freq, ms);
  delay(ms + 20);
}

void showTime(long secondsLeft) {
  lcd.setCursor(12, 0);
  lcd.print(secondsLeft / 60);
  lcd.print(":");
  if (secondsLeft % 60 < 10) lcd.print("0");
  lcd.print(secondsLeft % 60);
}

void showStage(int icon, int stage, int pressed, int total, int strikes) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write((byte)icon);
  lcd.print(" ST");
  lcd.print(stage + 1);
  lcd.print("/5");

  lcd.setCursor(0, 1);
  for (int i = 0; i < total; i++) {
    if (i < pressed) lcd.print("*");
    else lcd.print("-");
  }

  lcd.setCursor(13, 1);
  for (int i = 0; i < 3; i++) {
    if (i < strikes) lcd.print("X");
    else lcd.print("_");
  }
}

void showMessage(const char* line1, const char* line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}
