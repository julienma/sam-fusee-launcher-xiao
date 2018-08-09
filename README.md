

# sam-fusee-launcher
Fusee Launcher for the openschemes SAMD21 Loader board. Based on [sam fusee launcher](https://github.com/atlas44/sam-fusee-launcher).

[You can purchase one at Tindie](https://www.tindie.com/products/13711/)

Build and tested with Arduino SDK.

# Install a Pre-built Firmware without Compiling
* Download a firmware zip file from the firmware directory and open
* Plug the SAMD Loader into USB, and double click reset
* Drop the 3 files from inside the zip onto USB.  They will be autoflashed as soon as they are written
* Unplug SAMD Loader, it's now flashed to the new firmware!


# Build
Go through [trinket m0: arduino-ide-setup](https://learn.adafruit.com/adafruit-trinket-m0-circuitpython-arduino/arduino-ide-setup) and [trinket m0: arduino-ide-setup2](https://learn.adafruit.com/adafruit-trinket-m0-circuitpython-arduino/using-with-arduino-ide)

Summary:
* Download and install arduino IDE http://www.arduino.cc/en/Main/Software
* In Arduino: go to "Prefences" and add to "Additional Board Manager URLs" followin URL:
*  `https://adafruit.github.io/arduino-board-index/package_adafruit_index.json`
* go to "Tools > Board > Board Manager" and select Type: All and
* Install "Adafruit SAMD Boards" by Adafruit (not sure if required: Arduino - Boards SAMD)
* Select the Trinket M0 with "Tools > Board > Adafruit Trinket M0"

Go to Sketch > Include Library > Manage Libraries
Install USBHOst, and FlashStorage.

Connect the SAMD Loader to your computer and double Click on the Reset Button.
Your computer should detect the SAMD Loader automatically (On win7 install this [driver](https://github.com/adafruit/Adafruit_Windows_Drivers/releases/download/2.2.0/adafruit_drivers_2.2.0.0.exe))

Got to Tools > Port and select your connected SAMD Loader

Download this Repository, open main/main.ino with Arduino IDE.

Then Verify/Compile (Ctrl + R)
If no errors appear
Upload (Ctrl + U).

The SAMD Loader is ready for use.

LED is:
* Steady Blue - Failed to initialize USB on SAMD, check battery
* Quick, Steady Blinking - Ready to send, searching for Switch.  Insert RCM jig, Hold VOL + and Press Power
* Short/Long (Ta Daa!) Blink - Payload sent and activated.

# Update the Payload
download your favorit [payload](https://github.com/CTCaer/hekate/releases) as a `.bin` file.
run the python script `tools/binConverter.py` with the path to the file as an argument:
`python binConverter.py "C:\pathToMyPayload\hekateNew.bin` or just drag the .bin file on the script

in the same folder as the .bin file is located, a new .h file should appear. Copy the new file to the main folder and in the main.ino go to line 6 `#include "hekate_ctcaer_2.3.h"` and rename it to your new file `#include "hekateNew.h"`

Then just compile and upload.

# Hardware
[SAMD Loader](https://www.tindie.com/products/13711/) 

Power consumption:
* Idle with error and power LED: 2.5mA
* Idle with only power LED: 0.8mA
* Running: 12.7mA

# Finished Dongle
Micro USB to USB C converter

![microUsbToUsbC](./images/microUsbToUsbC.jpg)

[![Test](https://youtu.be/HImP8QRGi0U/0.jpg)](https://youtu.be/HImP8QRGi0U)

# Thanks to:
* [atlas44](https://github.com/atlas44/sam-fusee-launcher)
* [CTCaer](https://github.com/CTCaer/hekate)
* [Ninoh-FOX](https://www.elotrolado.net/hilo_tutorial-crea-tu-propio-dongle-portatil-para-cargar-payloads-it-is-easy_2287822)
* [noemu] (https://github.com/noemu/sam-fusee-launcher)
* and everyone else i forgot


