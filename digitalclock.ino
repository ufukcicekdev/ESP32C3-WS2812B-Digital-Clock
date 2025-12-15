#include <WiFi.h>
#include <time.h>
#include <Adafruit_NeoPixel.h>

/* ========= CONFIG ========= */
#define LED_PIN     6
#define NUM_PIXELS  58
#define BRIGHTNESS  40

/* WiFi */
const char* ssid     = "your ssid";
const char* password = "your password";

/* NTP */
const char* ntpServer = "pool.ntp.org";
const long GMT_OFFSET_SEC = 3 * 3600; // TR UTC+3
const int DAYLIGHT_OFFSET_SEC = 0;

Adafruit_NeoPixel strip(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

/* ========= SEGMENTS ========= */
#define SEG_G 0
#define SEG_B 1
#define SEG_A 2
#define SEG_F 3
#define SEG_E 4
#define SEG_D 5
#define SEG_C 6

// Her digit 14 LED
const int segmentLED[7][2] = {
  {0, 1},    // G
  {2, 3},    // B
  {4, 5},    // A
  {6, 7},    // F
  {8, 9},    // E
  {10,11},   // D
  {12,13}    // C
};

// Digit başlangıç indexleri
const int digitStart[4] = {0, 14, 28, 42}; // Saat onlar, saat birler, dakika onlar, dakika birler

// Rakamlara göre hangi segmentler yanacak (A B C D E F G)
const byte digits[10][7] = {
  {1,1,1,1,1,1,0}, //0
  {0,1,1,0,0,0,0}, //1
  {1,1,0,1,1,0,1}, //2
  {1,1,1,1,0,0,1}, //3
  {0,1,1,0,0,1,1}, //4
  {1,0,1,1,0,1,1}, //5
  {1,0,1,1,1,1,1}, //6
  {1,1,1,0,0,0,0}, //7
  {1,1,1,1,1,1,1}, //8
  {1,1,1,1,0,1,1}  //9
};

/* ========= FUNCTIONS ========= */
void syncTime() {
  WiFi.begin(ssid, password);
  int t = 0;
  while (WiFi.status() != WL_CONNECTED && t < 20) {
    delay(500);
    t++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, ntpServer);
    Serial.println("NTP OK (TR saati)");
  } else {
    Serial.println("WiFi baglanamadi");
  }
}

// Belirli segmentleri yak
void lightSegment(int seg, int base) {
  strip.setPixelColor(base + segmentLED[seg][0], 255, 0, 0);
  strip.setPixelColor(base + segmentLED[seg][1], 255, 0, 0);
}

// Rakamı çiz
void drawDigit(int digitIndex, int number) {
  int base = digitStart[digitIndex];
  for (int s = 0; s < 7; s++) {
    if (digits[number][s]) {
      int seg;
      switch(s) {
        case 0: seg = SEG_A; break;
        case 1: seg = SEG_B; break;
        case 2: seg = SEG_C; break;
        case 3: seg = SEG_D; break;
        case 4: seg = SEG_E; break;
        case 5: seg = SEG_F; break;
        case 6: seg = SEG_G; break;
      }
      lightSegment(seg, base);
    }
  }
}

/* ========= SETUP ========= */
void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.clear();
  strip.show();
  syncTime();
}

/* ========= LOOP ========= */
void loop() {
  struct tm t;
  if (!getLocalTime(&t)) return;

  Serial.printf("Saat: %02d:%02d:%02d\n", t.tm_hour, t.tm_min, t.tm_sec);

  strip.clear();

  // Saat ve dakika rakamları
  drawDigit(0, t.tm_hour / 10);
  drawDigit(1, t.tm_hour % 10);
  drawDigit(2, t.tm_min / 10);
  drawDigit(3, t.tm_min % 10);

  // DOT blink (saniye bazlı)
  if (t.tm_sec % 2 == 0) {
    strip.setPixelColor(56, 255, 0, 0);
    strip.setPixelColor(57, 255, 0, 0);
  }

  strip.show();
  delay(200);
}
