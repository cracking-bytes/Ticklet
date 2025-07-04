#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// === OLED SETTINGS ===
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// === BUTTON PINS ===
const int BTN_START = 0;
const int BTN_STOP  = 1;
const int BTN_RESET = 2;
const int BTN_SET   = 3;

// === LED PINS ===
const int LED_IDLE = 27;     // Red
const int LED_PAUSED = 28;   // Blue
const int LED_RUNNING = 29;  // Green

// === ROTARY ENCODER PINS ===
const int R_CLK = 4;
const int R_DT  = 26;

// === TIMER VARIABLES ===
unsigned long startTime = 0;
unsigned long currentTime = 0;
unsigned long elapsedTime = 0;
bool timerRunning = false;
bool setTimeMode = false;
int setMinutes = 0;
int setSeconds = 0;
bool lastCLKState = HIGH;

void setup() {
  // Serial for debugging (optional)
  Serial.begin(9600);

  // === BUTTON SETUP ===
  pinMode(BTN_START, INPUT_PULLUP);
  pinMode(BTN_STOP, INPUT_PULLUP);
  pinMode(BTN_RESET, INPUT_PULLUP);
  pinMode(BTN_SET, INPUT_PULLUP);

  // === LED SETUP ===
  pinMode(LED_RUNNING, OUTPUT);
  pinMode(LED_PAUSED, OUTPUT);
  pinMode(LED_IDLE, OUTPUT);

  // === ROTARY ENCODER SETUP ===
  pinMode(R_CLK, INPUT);
  pinMode(R_DT, INPUT);
  lastCLKState = digitalRead(R_CLK);

  // === OLED INIT ===
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 init failed"));
    for (;;); // Stop if failed
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Cracking Bytes");
  display.display();
  delay(1000);
  display.clearDisplay();
}

void loop() {
  // === TOGGLE SET MODE ===
  if (digitalRead(BTN_SET) == LOW) {
    delay(200);
    setTimeMode = !setTimeMode;
  }

  // === ROTARY ENCODER HANDLING ===
  if (setTimeMode) {
    bool currentCLK = digitalRead(R_CLK);
    if (currentCLK != lastCLKState && currentCLK == LOW) {
      if (digitalRead(R_DT) != currentCLK) {
        setSeconds += 5;  // Clockwise
      } else {
        setSeconds -= 5;  // Counter-clockwise
      }

      // Normalize time
      if (setSeconds >= 60) {
        setMinutes += 1;
        setSeconds = 0;
      }
      if (setSeconds < 0) {
        if (setMinutes > 0) {
          setMinutes -= 1;
          setSeconds = 55;
        } else {
          setSeconds = 0;
        }
      }
    }
    lastCLKState = currentCLK;
  }

  // === START ===
  if (digitalRead(BTN_START) == LOW && !timerRunning && !setTimeMode) {
    delay(200);
    timerRunning = true;
    startTime = millis();
    elapsedTime = (setMinutes * 60 + setSeconds) * 1000;
  }

  // === STOP ===
  if (digitalRead(BTN_STOP) == LOW && timerRunning) {
    delay(200);
    timerRunning = false;
  }

  // === RESET ===
  if (digitalRead(BTN_RESET) == LOW) {
    delay(200);
    timerRunning = false;
    setMinutes = 0;
    setSeconds = 0;
    elapsedTime = 0;
  }

  // === COUNTDOWN ===
  if (timerRunning) {
    unsigned long timePassed = millis() - startTime;
    if (timePassed >= elapsedTime) {
      timerRunning = false;
      setMinutes = 0;
      setSeconds = 0;
      elapsedTime = 0;
    }
  }

  // === LED FEEDBACK ===
  digitalWrite(LED_IDLE, !timerRunning && elapsedTime == 0);
  digitalWrite(LED_RUNNING, timerRunning);
  digitalWrite(LED_PAUSED, !timerRunning && elapsedTime > 0 && !setTimeMode);

  // === DISPLAY UPDATE ===
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);

  if (setTimeMode) {
    display.println("Set Timer:");
  } else if (timerRunning) {
    display.println("Running...");
  } else if (!timerRunning && elapsedTime > 0) {
    display.println("Paused");
  } else {
    display.println("Idle");
  }

  int showMin = (timerRunning || !setTimeMode) ? (elapsedTime - (millis() - startTime)) / 60000 : setMinutes;
  int showSec = (timerRunning || !setTimeMode) ? ((elapsedTime - (millis() - startTime)) / 1000) % 60 : setSeconds;

  if (showMin < 0) showMin = 0;
  if (showSec < 0) showSec = 0;

  display.setCursor(10, 35);
  display.print(showMin < 10 ? "0" : ""); display.print(showMin);
  display.print(":");
  display.print(showSec < 10 ? "0" : ""); display.print(showSec);
  display.display();

  delay(50);
}
