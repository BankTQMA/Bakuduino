#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int buttonPins[4] = {2, 3, 4, 5};
int buzzerPin = 8;

byte waveIcon[8] = {B00000, B01000, B10101, B00010, B01000, B10101, B00010, B00000};

void solveWave(int tones[], int n, int decoys, int answer[]) {
  int table[3] = {1, 2, 3};
  for (int i = 0; i < n; i++) {
    answer[i] = table[tones[i]];
  }
}
