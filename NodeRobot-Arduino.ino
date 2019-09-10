#include <ESP8266WiFi.h>
//#include <Servo.h>
//#include <Ultrasonic.h>

/*#define pino_trigger 4
  #define pino_echo 5*/

#define pino_led 15

#define leftSpeed D5
#define left1 D4
#define left2 D3

#define rightSpeed D1
#define right1 D0
#define right2 D6

//Ultrasonic ultrasonic(pino_trigger, pino_echo);

//Servo myservo;

int actualPos = 95;
int speed = 1;
int manualSpeed = 5;
int minPos = 50;
int maxPos = 140;
float cmMsec;

const char *ssid = "Desktop_F0712324";
const char *password = "16217053";
int port = 8888;
WiFiServer server(port);

int count = 0;

void setup()
{
  Serial.begin(9600);
  /*myservo.attach(15);
    myservo.write(actualPos);*/

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

int num = 0;

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

        /*if (leitura == 1) {
          int leitura2 = client.read();
          RotateMotors(leitura2);
          } else if (leitura == 2) {
          int leitura2 = client.read();

          if(leitura2 == 0){
            digitalWrite(pino_led, LOW);
            Serial.println("Desligou Farol");
          }else{
            digitalWrite(pino_led, HIGH);
            Serial.println("Ligou Farol");
          }
          }*/
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
