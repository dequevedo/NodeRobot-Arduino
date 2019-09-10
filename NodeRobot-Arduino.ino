#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define leftSpeed D5
#define left1 D4
#define left2 D3

#define rightSpeed D1
#define right1 D0
#define right2 D6

const char *ssid = "Desktop_F0712324";
const char *password = "16217053";
int port = 8888;
WiFiServer server(port);

void setup()
{
  Serial.begin(115200);

  pinMode(leftSpeed, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);

  pinMode(rightSpeed, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);

  //pinMode(pino_led, OUTPUT);

  //pinMode(SendKey, INPUT_PULLUP); //Btn to send data
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //Connect to wifi

  Serial.println("Connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.print("Open Telnet and connect to IP:");
  Serial.print(WiFi.localIP());
  Serial.print(" on port ");
  Serial.println(port);
}

void loop()
{
  WiFiClient client = server.available();

  if (client) {
    if (client.connected())
    {
      Serial.println("Client Connected");
    }

    while (client.connected()) {
      while (client.available() > 0) {
        int leitura = client.read();

        if (leitura == 69) {
          int leSpd = client.read() * 8;
          int x1 = client.read();
          int x2 = client.read();

          int y1 = client.read();
          int y2 = client.read();
          int riSpd = client.read() * 8;

          RotateMotors(leSpd, x1, x2, y1, y2, riSpd);
        }
        client.flush();
      }
    }
    client.stop();
    Serial.println("Client disconnected");

    analogWrite(left1, 0);
    analogWrite(left2, 0);
    analogWrite(right1, 0);
    analogWrite(right2, 0);
  }
}
