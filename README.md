# GSM Alarm system.
This is a GSM alarm system based on the Arduino Nano and SIM800L boards.
This project is designed for maximum autonomous working time e.g. powered by the `18650` battery. When the system is in IDLE mode, it 'sleeps' and wakes up when the interrupt on pin `3` is triggered.
If you want to get maximum performance, de-solder the led's from the arduino board and disable the voltage regulator.
# Setup
1. Solder all components together (note that the `SIM800L` board works between `3.7V` and `4.2V`, and the interrupt pins on the Arduino Nano are `2, 3`).
2. Edit the values in the `#define` statements at the top of the sketch (phone number, interrupt pins, timeouts).
3. Put the libraries from the `libraries` project directpry in the `C:\Program Files (x86)\Arduino\libraries` directory.
4. Compile, upload and enjoy.
