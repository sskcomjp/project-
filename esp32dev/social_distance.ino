#include <ESP32Servo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <FastLED.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <HTTPClient.h>

int count_value = 50;
int count = count_value - 1;

//wifi設定
//学校用
//char ssid[] = "";
//char password[] = "";
//家用
char ssid[] = "";
char password[] = "";






//gpsの初期設定
TinyGPSPlus gps;
SoftwareSerial mySerial(14, 12); // RX, TX
float lat_data;
float lng_data;


//LEDで使用する変数
#define Neopixel_PIN    27
#define NUM_LEDS    20
char led_judg_value[10] = {0};
CRGB leds[NUM_LEDS]; //LEDの変数宣言

//サーボで使用する変数
Servo servo_1;
char servo_judg_value[10] = {'0'};
int servo_judg_1 = 0;
int servo_age_1 = 0;
int servo_add_1 = 60;

void gps_function() {


  while (mySerial.available() > 0) {

    char c = mySerial.read();
    //Serial.print(c);
    gps.encode(c);
    if (gps.location.isUpdated()) {

      //Serial.print("LAT=");
      //Serial.println(gps.location.lat());
      //Serial.print("LONG=");
      //Serial.println(gps.location.lng());


      lat_data = gps.location.lat();
      lng_data = gps.location.lng();
      
      Serial.print("LAT=");
      Serial.println(lat_data, 6);
      Serial.print("LONG=");
      Serial.println(lng_data, 6);

    }
  }
}

void connectWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("connected!");
}

String HTTP_Request() {

  char data_lat[7];
  char data_lng[7];

  snprintf(data_lat, 7, "%.7f", lat_data);
  snprintf(data_lng, 7, "%.7f", lng_data);

  char http_ip[255] = "http://3.112.225.241/entry.php?comment=";
  char str2[] = "&comment2=";
  strcat(http_ip, data_lat);
  strcat(http_ip, str2);
  strcat(http_ip, data_lng);


  HTTPClient http;
  http.begin(http_ip);
  int httpCode = http.GET();

  String result = "";

  if (httpCode < 0) {
    result = http.errorToString(httpCode);
  } else if (http.getSize() < 0) {
    result =  "size is invalid";
  } else {
    result = http.getString();
  }
  http.end();

  return result;
}


void LED_Start_up() {
  int Time = 100;
  int i = 0;
  //点灯
  for (i = 0; i < 6; i++) {
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(Time);
  }
  for (i = 5; i < 12; i++) {
    leds[i] = CRGB::Blue;
    FastLED.show();
    delay(Time);
  }
  for (i = 12; i < 20; i++) {
    leds[i] = CRGB::Green;
    FastLED.show();
    delay(Time);
  }
  //消灯
  for (i = 19; i > 11; i--) {
    leds[i] = CRGB(0, 0, 0);
    FastLED.show();
    delay(Time);
  }
  for (i = 11; i > 4; i--) {
    leds[i] = CRGB(0, 0, 0);
    FastLED.show();
    delay(Time);
  }
  for (i = 4; i >= 0; i--) {
    leds[i] = CRGB(0, 0, 0);
    FastLED.show();
    delay(Time);
  }

}

void LED_Blinking() {

  //文字によって点灯パターンを変更
  if (led_judg_value[0] == '1') {
    int Time = 0;
    int i = 0;
    for (i = 0; i < 20; i++) {
      leds[i] = CRGB(0, 255, 0);
      FastLED.show();
      delay(Time);
    }
    for (i = 19; i >= 0; i--) {
      leds[i] = CRGB(0, 0, 0);
      FastLED.show();
      delay(Time);

    }
    gps_function(); //gpsの値取得
    HTTP_Request();
  }
  else if (led_judg_value[0] == '2') {
    int Time = 0;
    int i = 0;
    for (i = 0; i < 20; i++) {
      leds[i] = CRGB(0, 255, 0);
      FastLED.show();
      delay(Time);
      leds[i] = CRGB(0, 0, 0);
      FastLED.show();
    }
    gps_function();
    HTTP_Request();
  }
  else if (led_judg_value[0] == '3') {
    int Time = 0;
    int i = 0;
    for (i = 0; i < 20; i++) {
      leds[i] = CRGB(255, 255, 0);
      FastLED.show();
      delay(Time);
      leds[i] = CRGB(0, 0, 0);
      FastLED.show();
    }
  }
  else {
    int Time = 0;
    int i = 0;
    for (i = 0; i < 20; i++) {
      leds[i] = CRGB(139, 34, 34);
      FastLED.show();
      delay(Time);
      leds[i] = CRGB(0, 0, 0);
      FastLED.show();
    }


  }

}
char unitV_serial() {
  //シリアル通信で文字を受信
  if (Serial1.available() > 0) {
    char str = '0';
    

    str = Serial1.read();




    return str;
  }
}


void servo_control() {
  int TIME = 0;
  if (servo_judg_value[0] == '7') {
    servo_age_1 = servo_age_1 + servo_add_1;
    servo_1.write(servo_age_1);
  } else {
  }

  if (servo_age_1 == 180 || servo_age_1 == 0) {
    servo_add_1 = servo_add_1 * -1;
  }
  delay(TIME);
}




void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 25, 26); //unitV
  mySerial.begin(9600); //gps

  servo_1.attach(13);

  // Neopixel初期化
  FastLED.addLeds<WS2811, Neopixel_PIN>(leds, NUM_LEDS);
  //起動時点灯
  LED_Start_up();

  connectWifi();//wifiと接続
}



void loop() {
  count = count + 1;
  //Serial.print("回数:");
  //Serial.println(count);
  char str;

  led_judg_value[0] = '0';
  str = unitV_serial();



  if (str == '6' or str == '7') {
    servo_judg_value[0] = str;
    Serial.print("サーボ:");
    Serial.println(servo_judg_value[0]);
  }
  else {
    led_judg_value[0] = str;
    Serial.print("LED:");
    Serial.println(led_judg_value[0]);
  }

  if (count == count_value) {
    servo_control();
    count = 0;
  }




  LED_Blinking();






}
