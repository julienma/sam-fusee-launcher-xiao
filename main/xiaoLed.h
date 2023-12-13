#include <Arduino.h>

// On the XIAO board:
// - LOW will turn the leds ON
// - HIGH will turn the leds OFF

void ledInit() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

// The built-in led is orange
// The TX / RX leds are blue
void setLedColor(const char color[]) {
  if (color == "orange") {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(PIN_LED_TXL, HIGH);
  } else if (color == "blue") {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(PIN_LED_TXL, LOW);
  } else { // leds off
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(PIN_LED_TXL, HIGH);
  }
}

// Turn off all LEDs and go to sleep. To launch another payload, press the reset button on the device.
void sleepDeep(int errorCode) {
  setLedColor("off");
  if (errorCode == -1) {
    // LED on full time means error
    setLedColor("orange");
  }
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk; /* Enable deepsleep */
  __DSB(); /* Ensure effect of last store takes effect */
  __WFI(); /* Enter sleep mode */
}
