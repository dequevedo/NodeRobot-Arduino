#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define leftSpeed D5
#define left1 D4
#define left2 D3

#define rightSpeed D1
#define right1 D0
#define right2 D6

const char* ssid = "NodeRobot";
const char* password = "noderobot";
boolean alreadyConnected = false; // whether or not the client was connected previously

WiFiServer server(80);


void setup()
{
  Serial.begin(115200);

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
