#include <Adafruit_NeoPixel.h>

#define LED_PIN    6      
#define LED_COUNT  300     // Number of NeoPixels in my strip 

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// === SETTINGS ===
float minBreathBrightness = 0.2; // 30% minimum breathing brightness
float maxBreathBrightness = 1.0; // 100% maximum breathing brightness
unsigned long yearDuration = 5000; // Change this according to how long I want the interaction to last 

unsigned long lastYearChange = 0;
int currentYearIndex = 0;

// Breathing speeds mapped from the Material Footprint data (1970-2024) (that csv file)
float breathSpeeds[] = {
  0.002271, 0.002241, 0.002389, 0.002390, 0.002179, 0.002371, 0.002463, 0.002519,
  0.002540, 0.002580, 0.002517, 0.002459, 0.002447, 0.002454, 0.002561, 0.002642,
  0.002648, 0.002718, 0.002777, 0.002790, 0.002897, 0.002902, 0.002949, 0.002970,
  0.003057, 0.003104, 0.003142, 0.003167, 0.003251, 0.003252, 0.003340, 0.003277,
  0.003275, 0.003348, 0.003389, 0.003466, 0.003479, 0.003494, 0.003460, 0.003374,
  0.003482, 0.003499, 0.003463, 0.003524, 0.003552, 0.003822, 0.004104, 0.004257,
  0.004415, 0.004170, 0.005036, 0.005421, 0.005285, 0.005385, 0.005334, 0.005696,
  0.005543, 0.005647, 0.005592
};
const int totalYears = sizeof(breathSpeeds) / sizeof(breathSpeeds[0]);

// Defining the shades of amber color progression (mapped for 1970-2024)
uint32_t yearColors[] = {
  strip.Color(255, 191, 0), strip.Color(255, 190, 0), strip.Color(255, 185, 0),
  strip.Color(255, 180, 0), strip.Color(255, 175, 0), strip.Color(255, 170, 0),
  strip.Color(255, 165, 0), strip.Color(255, 160, 0), strip.Color(255, 155, 0),
  strip.Color(255, 150, 0), strip.Color(255, 145, 0), strip.Color(255, 140, 0),
  strip.Color(255, 135, 0), strip.Color(255, 130, 0), strip.Color(255, 125, 0),
  strip.Color(255, 120, 0), strip.Color(255, 115, 0), strip.Color(255, 110, 0),
  strip.Color(255, 105, 0), strip.Color(255, 100, 0), strip.Color(255,  95, 0),
  strip.Color(255,  90, 0), strip.Color(255,  85, 0), strip.Color(255,  80, 0),
  strip.Color(255,  75, 0), strip.Color(255,  70, 0), strip.Color(255,  65, 0),
  strip.Color(255,  60, 0), strip.Color(255,  55, 0), strip.Color(255,  50, 0),
  strip.Color(255,  45, 0), strip.Color(255,  40, 0), strip.Color(255,  35, 0),
  strip.Color(255,  30, 0), strip.Color(255,  25, 0), strip.Color(255,  20, 0),
  strip.Color(255,  15, 0), strip.Color(255,  10, 0), strip.Color(255,   5, 0),
  strip.Color(255,   0, 0), strip.Color(250,   0, 0), strip.Color(245,   0, 0),
  strip.Color(240,   0, 0), strip.Color(235,   0, 0), strip.Color(230,   0, 0),
  strip.Color(225,   0, 0), strip.Color(220,   0, 0), strip.Color(215,   0, 0),
  strip.Color(210,   0, 0), strip.Color(205,   0, 0), strip.Color(200,   0, 0),
  strip.Color(195,   0, 0), strip.Color(190,   0, 0), strip.Color(185,   0, 0),
  strip.Color(180,   0, 0)
};

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(255);
  lastYearChange = millis();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastYearChange >= yearDuration) {
    currentYearIndex++;
    if (currentYearIndex >= totalYears) {
      finalFlickerAndOff();
      return;
    }
    lastYearChange = currentMillis;
  }

  float breathSpeed = breathSpeeds[currentYearIndex];
  float breathPhase = sin(currentMillis * breathSpeed);
  float normalizedBreath = (breathPhase + 1.0) / 2.0;
  float breathBrightness = minBreathBrightness + (maxBreathBrightness - minBreathBrightness) * normalizedBreath;

  bool fireFlickerActive = (currentYearIndex >= 46); // 2016 index
  if (fireFlickerActive && random(0, 100) < 5) {
    breathBrightness *= random(90, 110) / 100.0;
  }

  uint8_t r = (uint8_t)(((yearColors[currentYearIndex] >> 16) & 0xFF) * breathBrightness); //pushing this into this sequence to come up with a code 
  uint8_t g = (uint8_t)(((yearColors[currentYearIndex] >> 8) & 0xFF) * breathBrightness);
  uint8_t b = (uint8_t)((yearColors[currentYearIndex] & 0xFF) * breathBrightness);

  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();

  delay(20);
}

void finalFlickerAndOff() // I AM NOT HAPPY WITH THIS BUT WHATEVER
{
  for (int i = 0; i < 10; i++) {
    int flickerBrightness = random(30, 255);
    for (int j = 0; j < strip.numPixels(); j++) {
      strip.setPixelColor(j, flickerBrightness, flickerBrightness * 0.5, 0);
    }
    strip.show();
    delay(random(30, 100));
  }
  strip.clear();
  strip.show();
  delay(2000);

  // Reset to beginning after blackout (for now before attaching the sensor to turn it on)
  currentYearIndex = 0;
  lastYearChange = millis();
}
