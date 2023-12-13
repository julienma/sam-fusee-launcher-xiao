// This sketch flashes the SAMD with a fusee gelee payload launcher
// Arduino upload is the same as dropping a UF2 file onto the emulated flash drive (FIRMWARE, TRINKETBOOT, FEATHERBOOT, GEMMABOOT)
// When compiling, payload bin must be #included as a header file (use bin2header), select the payload by including the desired header (hekate, sx)
// Double click reset to enter bootloader.  Activity led will fade up/down and SAMD will enable flash drive.  
// To flash: Compile and upload using arduino, or just drop a pre-compiled UF2 onto the flash drive.
// To backup your custom arduino build.  Flash via arduino, double click reset and copy the 3 files from the emulated flash drive to your PC

#include <Arduino.h>
#include "xiaoLed.h"
#include "fuseegelee.h"

// Select bin file payload here
// Must contain bin file as fuseeBin array with correct FUSEE_BIN_SIZE
#include "hekate_ctcaer_6.0.7.h"

void setup()
{
  ledInit();

  // Try to bring up USB
  // LED on full time means USB Init failed
  if (usbInit() == -1) sleepDeep(-1);

  // OK, USB is up.  Let's party
  // Search for the Tegra.  Blink rapidly (~5 Hz) while searching
  while (!searchTegraDevice())
  {
    setLedColor("orange");
    delay(20); //20ms on
    setLedColor("off");
    delay(180); //180ms off
  }

  // There is a delay here when Tegra wakes, the fast blinking stops for a moment
  // Next, you will see short/long LED blink (ta daa!) on the LED as the payload is sent and launched
  // When launching SXlauncher, keep holding + for SXOS menu if desired 
  setLedColor("blue");                      // Short blink when starting the party (ta)
  delay(20);
  setupTegraDevice();                       // Do USB setup for fusee gelee

  setLedColor("off");                       // LED Off when sending
  sendPayload(fuseeBin, FUSEE_BIN_SIZE);    // Smash & upload bin file from header

  setLedColor("blue");                      // On for a medium flash when launching (daa!)
  launchPayload();                          // Launch bin file

  // Turn off LED and go into deep sleep
  sleepDeep(1);
}

void loop()
{
}
