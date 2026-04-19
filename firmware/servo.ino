#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>
#include <math.h>

const char* ssid = "ESP32-Control";
const char* password = "12345678";

AsyncWebServer server(80);
AsyncEventSource events("/events");

Servo servo1;
Servo servo2;

#define SERVO1_PIN 15
#define SERVO2_PIN 16
#define offLed 17
#define onLed 18

volatile float targetAngle  = 90.0f;
float          currentAngle = 90.0f;


float fakeTemp() {
  static float value = 20.0;
  static bool up = true;
  value += (up ? 0.2 : -0.2);
  if (value >= 30.0) up = false;
  if (value <= 20.0) up = true;
  return value;
}

int fakeADC() {
  static int value = 0;
  static bool up = true;
  value += (up ? 20 : -20);
  if (value >= 4095) up = false;
  if (value <= 0) up = true;
  return value;
}

void setup() {
  // -Config-
  Serial.begin(115200);
  Serial.print("[system] Booting...");

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  
  servo1.setPeriodHertz(50); 
  servo2.setPeriodHertz(50);
  
  servo1.attach(SERVO1_PIN, 500, 2400); 
  servo2.attach(SERVO2_PIN, 500, 2400);
  
  pinMode(offLed, OUTPUT);
  pinMode(onLed, OUTPUT);

  // -SoftAP-
  Serial.print("[Wifi] Connecting...");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();

  Serial.println("\n [Wifi] Conected!");
  Serial.print("[Wifi] Server IP: ");
  Serial.println(IP);

  digitalWrite(offLed, LOW);
  digitalWrite(onLed, HIGH);

  // -CORS-
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Content-Type");

  // -SSE-
  events.onConnect([](AsyncEventSourceClient* client) {
    Serial.printf("[SSE] Client connected, id=%u\n", client->lastId());
    client->send("connected", "status", millis());
  });

  server.addHandler(&events);

  server.on("/servo", HTTP_POST,
  [](AsyncWebServerRequest* request){},
  nullptr,
  [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {

    StaticJsonDocument<64> doc;

    if (deserializeJson(doc, data, len)) {
      request->send(400, "application/json", "{\"error\":\"invalid JSON\"}");
      return;
    }

    if(doc.containsKey("servo")){
      targetAngle = constrain((float)doc["servo"], 0.0f, 180.0f);
      Serial.printf("[Servo] -> %.1f\n", targetAngle);
    }

    request->send(200, "application/json", "{\"ok\":true}");
  }
);
  
  server.on("/servo", HTTP_OPTIONS, [](AsyncWebServerRequest* request) {
    request->send(204);
  });

  server.begin();
}

void loop() {
  static unsigned long last = 0;
  if (millis() - last > 20) {
    last = millis();

    float diff = targetAngle - currentAngle;

    if(fabs(diff) > 0.5f)
      currentAngle += diff * 0.15f;
    else
      currentAngle = targetAngle;

    servo1.write((int)currentAngle);
    servo2.write(180 - (int)currentAngle);
  }

  static unsigned long lastTelemetry = 0;
  if (millis() - lastTelemetry > 1000) {
    lastTelemetry = millis();

    StaticJsonDocument<256> doc;
    doc["temp"] = fakeTemp();
    doc["adc"]  = fakeADC();

    String output;
    serializeJson(doc, output);

    events.send(output.c_str(), "telemetry", millis());
  }
}