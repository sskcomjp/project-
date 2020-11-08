#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
//SoftwareSerial mySerial(14, 12); // RX, TX
//TinyGPSCustom magneticVariation(gps, "GPRMC", 10);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Goodnight moon!");

  Serial2.begin(9600, SERIAL_8N1, 14, 12);
  // set the data rate for the SoftwareSerial port
  //mySerial.begin(9600);
  //mySerial.println("Hello, world?");
}

void loop() { // run over and over
  float lat_data;
  float lng_data;
  while (Serial2.available() > 0) { //(mySerial.available() > 0) {
    char c = Serial2.read();//mySerial.read();
    //Serial.print(c);
    gps.encode(c);
    if (gps.location.isUpdated()) {
      lat_data = gps.location.lat();
      lng_data = gps.location.lng();
      Serial.print("LAT=");
      Serial.println(lat_data, 6);
      Serial.print("LONG=");
      Serial.println(lng_data, 6);
    }
  }

}
