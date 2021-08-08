#include <EEPROM.h>

String input; // for incoming serial data
char terminator = 10;  // newline

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming String:
    input = Serial.readStringUntil(terminator);

    if(input.startsWith("read ")) {
      // parse the int address following "read "
      int address = input.substring(5).toInt();
      
      int result = EEPROM.read(address);

      Serial.println(result);
    }
    else if(input.startsWith("write ")) {
      // trim "write " from the input
      String addrValue = input.substring(6);
      
      // index of the space between the two ints
      int splitIndex = addrValue.indexOf(' ');

      // parse the int before the space
      int address = addrValue.substring(0, splitIndex).toInt();
      
      // parse the int after the space
      int value = addrValue.substring(splitIndex+1).toInt();
      
      EEPROM.write(address, value);
    }
    else {
      // error
      Serial.println("An error occurred.");
    }
  }
}
