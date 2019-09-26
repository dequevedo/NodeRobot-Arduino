#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
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

<<<<<<< HEAD
const char* ssid = "NodeRobot";
const char* password = "noderobot";
boolean alreadyConnected = false; // whether or not the client was connected previously

WiFiServer server(80);

=======
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
>>>>>>> parent of 3eddbe6... Code cleaning

int count = 0;

void setup()
{
  Serial.begin(115200);
  Serial.begin(9600);
  /*myservo.attach(15);
    myservo.write(actualPos);*/

  pinMode(leftSpeed, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);

  pinMode(rightSpeed, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);

  Serial.println();
  delay(1000);

  delay(1000);

  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  delay(1000);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.println("\nStarting server...");
  // start the server:
  server.begin();
}

int num = 0;

void loop()
{
  WiFiClient client = server.available();

  if (client)
  {
    if (!alreadyConnected)
    {
      client.flush();
      Serial.println("We have a new client");
      //client.println("Hello, client!");
      alreadyConnected = true;
    }

    if (client.available() > 0) {
      // read the bytes incoming from the client:
      char thisChar = client.read();
    }
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

<<<<<<< HEAD
        RotateMotors(leSpd, x1, x2, y1, y2, riSpd);
=======
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
>>>>>>> parent of 3eddbe6... Code cleaning
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
