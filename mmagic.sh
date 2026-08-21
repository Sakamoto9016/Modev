arduino-cli compile --fqbn esp32:esp32:esp32s3 --build-property 'compiler.cpp.extra_flags=-DDevES3C28P' . --verbose
arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 .
#arduino-cli compile --fqbn esp32:esp32:esp32s3 --build-property 'compiler.cpp.extra_flags=-DDevJC4827W543' .
#arduino-cli upload -p /dev/ttyACM1 --fqbn esp32:esp32:esp32s3 .
