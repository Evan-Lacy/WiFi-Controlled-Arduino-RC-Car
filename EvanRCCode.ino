#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <title>Robot Controller</title>
    <style>
      body {
        background: linear-gradient(to bottom, #4568dc, #b06ab3) no-repeat center center fixed;
        background-size: cover;
      }
      table{
        width:500px;
        font-size: 50px;
      }
      td{
        width:33%;
        text-align:center;
      }
      a{
        display: block;
        color: white;
        background-color: rgba(0,0,0,0.6);
        text-decoration: none;
        border-radius: 10px;
      }
      a:hover{
        background-color: rgba(0,0,0,0.3);
        color: black;
      }
    </style>
  </head>
  <body>
    <table>
      <tr>
        <td></td>
        <td><a href=/forward>^</a></td>
        <td></td>
      </tr>
      <tr>
        <td><a href=/left><</a></td>
        <td><a href=/stop>STOP</a></td>
        <td><a href=/right>></a></td>
      </tr>
    </table>
  </body>
</html> )=====";

const char* ssid = "bsuguest";
ESP8266WebServer server(80);
int leftMotorPin = D5;
int rightMotorPin = D6;

void sendHTML() {
  String s = index_html;
  server.send(200, "text/html", s);
}

void handleLeft() {
  digitalWrite(leftMotorPin, LOW);
  digitalWrite(rightMotorPin, HIGH);
  Serial.println("Motors Left...");
  sendHTML();
}

void handleRight() {
  digitalWrite(leftMotorPin, HIGH);
  digitalWrite(rightMotorPin, LOW);
  Serial.println("Motors Right...");
  sendHTML();
}

void handleForward() {
  digitalWrite(leftMotorPin, HIGH);
  digitalWrite(rightMotorPin, HIGH);
  Serial.println("Motors Forward...");
  sendHTML();
}

void handleStop() {
  digitalWrite(leftMotorPin, LOW);
  digitalWrite(rightMotorPin, LOW);
  Serial.println("STOP!");
  sendHTML();
}

void setup() {
  Serial.begin(9600);
  delay(100);
  WiFi.begin(ssid, "");
  Serial.println("Began WiFi!");

  Serial.print("Attempting to connect.");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin, OUTPUT);

  server.on("/", handleStop);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/forward", handleForward);
  server.on("/stop", handleStop);

  server.begin();
  Serial.println("HTTP Server Started!");

}

void loop() {
  server.handleClient();
}
