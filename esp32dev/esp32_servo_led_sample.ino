#include <ESP32Servo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <FastLED.h>


//LEDで使用する変数
#define Neopixel_PIN    26
#define NUM_LEDS    20
char led_judg_value[10] = {0};
CRGB leds[NUM_LEDS]; //LEDの変数宣言

//サーボで使用する変数
Servo servo_1;
char servo_judg_value[10] = {'0'};
int servo_judg_1 = 0;
int servo_age_1 = 0;
int servo_add_1 = 60;


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
    //if(Serial1.read()==1){

    str = Serial1.read();
    //servo_judg_value[0]=str;
    //}



    Serial.print("Aveilable char:");
    //Serial.println(str);

    return str;
  }
}

void servo_control() {
  int TIME = 5000;
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
  Serial1.begin(115200, SERIAL_8N1, 14, 12);
  Serial2.begin(115200); //rx:16,tx:17
  Serial.begin(115200);


  servo_1.attach(25);

  // Neopixel初期化
  FastLED.addLeds<WS2811, Neopixel_PIN>(leds, NUM_LEDS);
  //起動時点灯
  LED_Start_up();
  //Serial1.write('1');
}

void loop() {

  servo_judg_value[0] = unitV_serial();
  Serial.print("サーボ:");
  Serial.println(servo_judg_value[0]);

  servo_control();


  led_judg_value[0] = unitV_serial();
  Serial.print("LED:");
  Serial.println(led_judg_value[0]);

  LED_Blinking();






}
