#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>

const char* ssid = "";
const char* password = "";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

Servo servo1;
Servo servo2;

#define SERVO1_PIN 15
#define SERVO2_PIN 16

#define offLed 17
#define onLed 18

bool prevStat = false;


void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_DATA) {
    JsonDocument doc; 
    DeserializationError error = deserializeJson(doc, data, len);

    if (error) return;

  if (doc.containsKey("servo")) {
    int valorRecibido = doc["servo"].as<int>(); 
    
    int angle = constrain(valorRecibido, 0, 180);
    
    servo1.write(angle);
    servo2.write(180 - angle);
  }
  }
}

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
  Serial.begin(115200);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  
  servo1.setPeriodHertz(50); 
  servo2.setPeriodHertz(50);
  
  servo1.attach(SERVO1_PIN, 500, 2400); 
  servo2.attach(SERVO2_PIN, 500, 2400);
  
  pinMode(offLed, OUTPUT);
  pinMode(onLed, OUTPUT);

  

  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(offLed, prevStat);
    prevStat = !prevStat;
  }

    digitalWrite(offLed, LOW);
    digitalWrite(onLed, HIGH);

    Serial.println("\nConected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  server.begin();
}

void loop() {
  ws.cleanupClients();

  static unsigned long last = 0;
  if (millis() - last > 1000) {
    last = millis();

    JsonDocument doc;
    doc["temp"] = fakeTemp();
    doc["adc"] = fakeADC();

    String output;
    serializeJson(doc, output);
    ws.textAll(output);
  }
}