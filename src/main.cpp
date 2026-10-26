#include <Arduino.h>

// put function declarations here:
#include "ModuleWave.h"
#include "ModuleEye.h"
#include "ModuleSpiral.h"
#include "ModuleStar.h"

// put function definitions here:
byte fangIcon[8] = {B11111, B11111, B10101, B10101, B00100, B00100, B00000, B00000};

void solveFang(int tones[], int n, int decoys, int answer[]) {
  int table[3] = {4, 3, 2};
  for (int i = 0; i < n; i++) {
    if (i > 0 && tones[i] == tones[i - 1]) answer[i] = 1;
    else answer[i] = table[tones[i]];
  }
}

int realCount[5] = {3, 3, 4, 4, 5};
int maxDecoy[5]  = {0, 1, 1, 2, 2};

int order[5];
int strikes;
unsigned long endTime;

int tones[8];
bool decoy[8];
int len;
int answer[8];
int answerLen;

void solve(int symbol, int realTones[], int n, int decoys) {
  if (symbol == 0) solveWave(realTones, n, decoys, answer);
  if (symbol == 1) solveEye(realTones, n, decoys, answer);
  if (symbol == 2) solveFang(realTones, n, decoys, answer);
  if (symbol == 3) solveSpiral(realTones, n, decoys, answer);
  if (symbol == 4) solveStar(realTones, n, decoys, answer);
}

void makeStage(int stage) {
  int decoys = random(0, maxDecoy[stage] + 1);
  len = realCount[stage] + decoys;
  for (int i = 0; i < len; i++) {
    tones[i] = random(3);
    decoy[i] = false;
  }
  for (int d = 0; d < decoys; d++) {
    int p = random(len);
    while (decoy[p]) p = random(len);
    decoy[p] = true;
  }

  int realTones[8];
  answerLen = 0;
  for (int i = 0; i < len; i++) {
    if (!decoy[i]) {
      realTones[answerLen] = tones[i];
      answerLen++;
    }
  }
  solve(order[stage], realTones, answerLen, decoys);
}

long secondsLeft() {
  if (millis() >= endTime) return 0;
  return (endTime - millis()) / 1000;
}

bool playStage(int stage) {
  int pressed = 0;
  unsigned long lastPress = 0;

  while (secondsLeft() > 0) {
    if (pressed == 0) {
      showStage(order[stage], stage, 0, answerLen, strikes);
      delay(800);
      playSignal(tones, decoy, len);
      lastPress = millis();
    }

    int b = 0;
    while (b == 0 && millis() - lastPress < 6000 && secondsLeft() > 0) {
      showTime(secondsLeft());
      b = readButton();
    }
    if (b == 0) {
      pressed = 0;
      continue;
    }

    if (b != answer[pressed]) return false;
    pressed++;
    lastPress = millis();
    beep(1200, 20);
    showStage(order[stage], stage, pressed, answerLen, strikes);
    if (pressed == answerLen) return true;
  }
  return false;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) pinMode(buttonPins[i], INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.createChar(0, waveIcon);
  lcd.createChar(1, eyeIcon);
  lcd.createChar(2, fangIcon);
  lcd.createChar(3, spiralIcon);
  lcd.createChar(4, starIcon);
}

void loop() {
  // put your main code here, to run repeatedly:
  showMessage(TITLE_1, TITLE_2);
  while (readButton() == 0) {}
  randomSeed(millis());

  for (int i = 0; i < 5; i++) order[i] = i;
  for (int i = 4; i > 0; i--) {
    int j = random(i + 1);
    int t = order[i];
    order[i] = order[j];
    order[j] = t;
  }

  strikes = 0;
  endTime = millis() + 300000;
  int stage = 0;

  while (stage < 5 && strikes < 3 && secondsLeft() > 0) {
    makeStage(stage);
    printAnswer(stage, tones, decoy, len, answer, answerLen);
    if (playStage(stage)) {
      beep(523, 100); beep(659, 100); beep(784, 100); beep(1047, 200);
      stage++;
    } else if (secondsLeft() > 0) {
      strikes++;
      beep(200, 250); beep(150, 400);
    }
  }

  if (stage == 5) {
    showMessage(WIN_1, WIN_2);
    beep(523, 150); beep(659, 150); beep(784, 150); beep(1047, 500);
  } else if (strikes >= 3) {
    showMessage(LOSE_1, LOSE_X);
    beep(300, 200); beep(150, 700);
  } else {
    showMessage(LOSE_1, LOSE_TIME);
    beep(300, 200); beep(150, 700);
  }
  while (readButton() == 0) {}
}
