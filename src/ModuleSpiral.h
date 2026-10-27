const char* TITLE_1   = "   SIMON SAYS";
const char* TITLE_2   = " PRESS ANY KEY";
const char* WIN_1     = "    DEFUSED!";
const char* WIN_2     = "SIGNAL RECOVERED";
const char* LOSE_1    = "  *** BOOM ***";
const char* LOSE_X    = "TOO MANY ERRORS";
const char* LOSE_TIME = "   TIME'S  UP";

byte spiralIcon[8] = {B11111, B00001, B11101, B10101, B10001, B11111, B00000, B00000};

void solveSpiral(int tones[], int n, int decoys, int answer[]) {
  int table[3] = {2, 4, 1};
  for (int i = 0; i < n; i++) {
    int b = table[tones[i]];
    if (decoys >= 2) {
      b = b + 1;
      if (b > 4) b = 1;
    }
    answer[i] = b;
  }
}
