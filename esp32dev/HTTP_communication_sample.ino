#include <HTTPClient.h>
#include <stdio.h>
#include <string.h>

//学校用
//char ssid[] = "jikei-open-air";
//char password[] = "open-wifi";
//家用
char ssid[] = "HUMAX-FC4EF-A";
char password[] = "LWN3LEk4MjNaM";

char data_lat[] = "36.3919";
char data_lng[] = "137.2911";
char http_ip[255] = "http://3.112.225.241/entry.php?comment=";
char str2[] = "&comment2=";



void setup() {
  Serial.begin(115200);
  Serial.println("");
  strcat(http_ip, data_lat);
  strcat(http_ip, str2);
  strcat(http_ip, data_lng);


  connectWifi();



  String result = Request(http_ip);
  Serial.println(http_ip);
  //Serial.println(result);
  disconnectWifi();
}

void loop() {

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

void disconnectWifi() {
  WiFi.disconnect();
  Serial.println("disconnected!");
}

String Request(char host[]) {
  HTTPClient http;
  http.begin(host);
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
