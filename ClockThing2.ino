void setup() {
  // put your setup code here, to run once:

}

void change_minute(int this_minute, int this_second) {
  for (int i = mins[this_minute][0]; i <= mins[this_minute][1]; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 100));
  }
}

void change_hour(int this_hour, int this_minute, int this_second) {
  if (this_minute < intv[7]) {
    for (int i = hrs[this_hour][0]; i <= hrs[this_hour][1]; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 100));
    }
  } else {
    for (int i = hrs[this_hour + 1][0]; i <= hrs[this_hour + 1][1]; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 100));
    }
  }
}

void change_extras(int this_minute) {
  int extra_words;
  if (this_minute > 4) {
    if (this_minute < intv[7]) {
      extra_words = 4;
    } else {
      extra_words = 3;
    }
  } else {
    extra_words = 2;
  }
  for (int i = 0; i <= extra_words; i++) {
    for (int j = extras[i][0]; j <= extras[i][1]; j++) {
      pixels.setPixelColor(j, pixels.Color(0, 0, 100));
    }
  }
  if (this_minute >= intv[7]) {
    for (int i = extras[5][0]; i <= extras[5][1]; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 100));
    }
  }
}

void loop() {
  DateTime now = rtc.now();
  int time_sec = now.second();
  int time_min = now.minute();
  int time_hr = now.hour();
}
