// This sketch flashes the SAMD with a fusee gelee payload launcher
// Arduino upload is the same as dropping a UF2 file onto the emulated flash drive (FIRMWARE, TRINKETBOOT, FEATHERBOOT, GEMMABOOT)
// When compiling, payload bin must be #included as a header file (use bin2header), select the payload by including the desired header (hekate, sx)
// Double click reset to enter bootloader.  Activity led will fade up/down and SAMD will enable flash drive.  
// To flash: Compile and upload using arduino, or just drop a pre-compiled UF2 onto the flash drive.
// To backup your custom arduino build.  Flash via arduino, double click reset and copy the 3 files from the emulated flash drive to your PC


#include <FlashAsEEPROM.h>
#include <FlashStorage.h>
#include <Usb.h>
#include <Arduino.h>
#include "fuseegelee.h"

// Select bin file payload here
// Must contain bin file as fuseeBin array with correct FUSEE_BIN_SIZE
#include "Hekate_Payload_tumger.h"
//#include "hekate_ctcaer_3.2.h"
//#include "hekate_ctcaer_4.0.h"
//#include "SXLauncher.h"
//#include "ReiNX.h"

// Don't use serial LED, just use the onboard activity LED
#define led 13

void setup()
{
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  // Try to bring up USB
  if (usbInit() == -1){
      digitalWrite(led, HIGH);   // LED on full time means usb Init failed
      SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk; /* Enable deepsleep */
      __DSB(); /* Ensure effect of last store takes effect */
      __WFI(); /* Enter sleep mode */
  }
  // OK, USB is up.  Let's party
  // Search for the Tegra.  Blink rapidly (~5 Hz) while searching
  while (!searchTegraDevice())
  {
    digitalWrite(led,HIGH);
    delay(20); //20ms on
    digitalWrite(led,LOW);
    delay(180); //180ms off
  }
  // There is a delay here when Tegra wakes, the fast blinking stops for a moment
  // Next, you will see short/long LED blink (ta daa!) on the LED as the payload is sent and launched
  // When launching SXlauncher, keep holding + for SXOS menu if desired 
  digitalWrite(led, HIGH);                  // Short blink when starting the party (ta)
  delay(20);
  setupTegraDevice();                       // Do USB setup for fusee gelee 
  digitalWrite(led, LOW);                   // LED Off when sending 
  sendPayload(fuseeBin, FUSEE_BIN_SIZE);    // Smash & upload bin file from header
  digitalWrite(led, HIGH);                  // On for a medium flash when launching (daa!)
  launchPayload();                          // Launch bin file

  // Turn off LED and go into deep sleep
  digitalWrite(led,LOW);
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk; /* Enable deepsleep */
  __DSB(); /* Ensure effect of last store takes effect */
  __WFI(); /* Enter sleep mode */
}

void loop()
{
}
