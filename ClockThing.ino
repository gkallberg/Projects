//12 vs 24 hour
//could be either, need to find how to make distinction in code
#include "RTClib.h"
RTC_PCF8523 rtc;
#define RTC_Control_1 | 1b00000110 // this maybe sets to 12 hr clock? idk
#include <Adafruit_NeoPixel.h>
#define PIN        6
#define NUMPIXELS 132
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500
int leds[11][12] = {
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
  {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23},
  {24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35},
  {36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47},
  {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59},
  {60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71},
  {72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83},
  {84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95},
  {96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107},
  {108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119},
  {120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131}
};

int mins[12][2] = {
  { -1, -1},
  {30, 33}, //five
  {38, 40},
  {15, 21},
  {24, 29},
  {24, 33},
  {42, 47}, //thirty
  {24, 33},
  {24, 29},
  {15, 21},
  {38, 40},
  {30, 33} //five
};

int hrs[24][2] = {
  {109, 111}, //one
  {84, 86}, //two
  {112, 116},
  {61, 64},
  {88, 91},
  {117, 119},
  {72, 76},
  {96, 100},
  {92, 95},
  {120, 122},
  {102, 107},
  {78, 83} //twelve
};

int extras[6][2] = {
  {0, 1}, //it
  {3, 4}, //is
  {126, 131}, //o'clock
  {48, 54}, //minutes
  {68, 71}, //past
  {67, 68} //to
};

int intv[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60};

// it is one o'clock
// it is five minutes past one o'clock
// it is ten minutes past one o'clock
// it is fifteen minutes past one o' clock
// it is twenty minutes past one o'clock
// it is twenty five minutes past one o'clock
// it is thirty past minutes one o'clock
// it is twenty five minutes to two o'clock

void setup() {
  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.flush();
    abort();
  }
  if (! rtc.initialized() || rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  rtc.start();
  float drift = 43;
  float period_sec = (9600);
  float deviation_ppm = (drift / period_sec * 1000000);
  float drift_unit = 4.34;
  int offset = round(deviation_ppm / drift_unit);
  pixels.begin();
  pixels.clear();
  color();
}

int i = 0;
int x = 0;
int y = 0;
int z = 0;
int r = 0;
int g = 0;
int b = 0;
int cleared = 0;

void color() {
  DateTime now = rtc.now();
  pixels.Color(r, g, b);
  if (now.minute() < 20) {
    r = 150 - (now.minute() * 150 / 20);
    g = now.minute() * 150 / 20;
  } else if (now.minute() > 20 || now.minute() < 40) {
    g = 150 - (now.minute() * 150 / 20);
    b = now.minute() * 150 / 20;
  } else {
    b = 150 - (now.minute() * 150 / 20);
    r = now.minute() * 150 / 20;
  }
}

void minu() {
  for (i = mins[x][0]; i <= mins[x][1]; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();
  }
}

void hors() {
  DateTime now = rtc.now();
  for (i = hrs[y][0]; i <= hrs[y][1]; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();
    if (now.minute() < intv[7]) {
      y = now.hour() - 1;
    } else {
      y = now.hour();
    }
  }
}

void extrs() {
  DateTime now = rtc.now();
  for (z = 0; z <= 2; z++) {
    for (i = extras[z][0]; i <= extras[z][1]; i++) {
      pixels.setPixelColor(i, pixels.Color(r, g, b));
      pixels.show();
    }
  }
  if (x > intv[0] && x < intv[12]) {
    for (i = extras[3][0]; i <= extras[3][1]; i++) {
      pixels.setPixelColor(i, pixels.Color(r, g, b));
      pixels.show();
    }
  }
  if (now.minute() < intv[7]) {
    for (i = extras[4][0]; i <= extras[4][1]; i++) {
      pixels.setPixelColor(i, pixels.Color(r, g, b));
      pixels.show();
    }
  } else {
    for (i = extras[5][0]; i <= extras[5][1]; i++) {
      pixels.setPixelColor(i, pixels.Color(r, g, b));
      pixels.show();
    }
  }
}

void loop() {
  DateTime now = rtc.now();
  x = (now.minute() - (now.minute() % 5)) / 5;
  if ((now.minute() % 5) == 0) {
    minu();
    hors();
    extrs();
    color();
  }
  for (i = 0; i <= 12; i++) {
    if (now.minute() == intv[i] && now.second() == 0) {
      pixels.clear();
      cleared = 1;
    }
  }
}
