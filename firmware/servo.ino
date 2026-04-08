#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "";
const char* password = "";

WebServer server(80);

Servo servoA;
Servo servoB;

int pinServoA = 15;
int pinServoB = 16;

void moverON() {
    servoA.write(180);
    servoB.write(0);
    server.send(200, "text/plain", "Mode ON: A=180, B=0");
}

void moverOFF() {
    servoA.write(0);
    servoB.write(180);
    server.send(200, "text/plain", "Mode OFF: A=0, B=180");
}

void setup() {
    Serial.begin(115200);

    servoA.attach(pinServoA, 500, 2400);
    servoB.attach(pinServoB, 500, 2400);

    servoA.write(0);
    servoB.write(180);


    WiFi.begin(ssid, password);
    Serial.print("Conecting");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    server.on("/on", moverON);
    server.on("/off", moverOFF);

    server.begin();
}

void loop() {
    server.handleClient();
}