byte starIcon[8] = {B00100, B00100, B11111, B01110, B01010, B10001, B00000, B00000};

void solveStar(int tones[], int n, int decoys, int answer[]) {
  int last = 4;
  for (int i = 0; i < n; i++) {
    last = last + tones[i] + 1;
    if (last > 4) last = last - 4;
    answer[i] = last;
  }
}

void printAnswer(int stage, int tones[], bool decoy[], int len, int answer[], int n) {
  String names[3] = {"LOW", "MID", "HIGH"};
  Serial.print("Stage ");
  Serial.print(stage + 1);
  Serial.print(": ");
  for (int i = 0; i < len; i++) {
    Serial.print(names[tones[i]]);
    if (decoy[i]) Serial.print("(tick)");
    Serial.print(" ");
  }
  Serial.print("-> ");
  for (int i = 0; i < n; i++) {
    Serial.print(answer[i]);
    Serial.print(" ");
  }
  Serial.println();
}
