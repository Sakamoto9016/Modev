/*
Compile:
	arduino-cli compile --fqbn "esp32:esp32:esp32s3:PSRAM=opi" --verbose .
	arduino-cli compile --fqbn "esp32:esp32:esp32c6" --verbose .
Execute:
	arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 .
	arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:esp32c6 .
*/
#include"main.h"
/*
	Nothing much to see here lmao
*/