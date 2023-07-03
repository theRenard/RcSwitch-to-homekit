
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <RCSwitch.h>
#include "output.h"
RCSwitch sender = RCSwitch();
RCSwitch receiver = RCSwitch();

int sleep = 1000;
int transmit_pin = D1;
int receiver_pin = D3;
int pulseLength = 185;
int repeatTransmit = 5;

const char* ON[] = {
  "0FF00FFF0101",
  "0FF00FFF1001",
  "0FF00FF10001",
  "0FF00F1F0001",
  "0FF001FF0001",
  "0000FFFF010130",
  "0000FFFF100130",
  "0000FFF1000130",
  "0000FF1F000130",
  "0000F1FF000130"
};

const char* getStates[] = {
  "lights/zap1/getState",
  "lights/zap2/getState",
  "lights/zap3/getState",
  "lights/zap4/getState",
  "lights/zap5/getState",
  "lights/zap6/getState",
  "lights/zap7/getState",
  "lights/zap8/getState",
  "lights/zap9/getState",
  "lights/zap10/getState"
};

const char* setStates[] = {
  "lights/zap1/setState",
  "lights/zap2/setState",
  "lights/zap3/setState",
  "lights/zap4/setState",
  "lights/zap5/setState",
  "lights/zap6/setState",
  "lights/zap7/setState",
  "lights/zap8/setState",
  "lights/zap9/setState",
  "lights/zap10/setState"
};

const char* OFF[] = {
  "0FF00FFF0110",
  "0FF00FFF1010",
  "0FF00FF10010",
  "0FF00F1F0010",
  "0FF001FF0010",
  "0000FFFF011030",
  "0000FFFF101030",
  "0000FFF1001030",
  "0000FF1F001030",
  "0000F1FF001030"
};

// MQTT

WiFiClient espClient;
PubSubClient MQTTclient(espClient);

#define mqtt_server "home.local"

unsigned long startMQTTmillis;
unsigned long currentMQTTmillis;
const unsigned long MQTTdelay = 5000;
const size_t capacity = JSON_OBJECT_SIZE(10);

void MQTTcallback(char* topic, byte* payload, unsigned int length) {

  DynamicJsonDocument MQTTSubPayload(capacity);

  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  for (size_t i = 0; i < 10; i++) {          // loop setStates
    bool test = !strcmp(setStates[i], topic);
          // test if in `i` topics are identic
    Serial.println(setStates[i]);
    Serial.println(topic);
    Serial.println(test);
    if (test) {

      deserializeJson(MQTTSubPayload, payload, length);

      if (MQTTSubPayload.containsKey("On")) {

        bool value = MQTTSubPayload["On"];
        if (value) sender.sendTriState(ON[i]);
        else  sender.sendTriState(OFF[i]);

      } else {

        Serial.println("No Valid Payload");

      }
    }
  }
}

boolean reconnect() {

  if (MQTTclient.connect("RCSwitch")) {

    Serial.println("MQTT is connected...");
    MQTTclient.subscribe("lights/zap1/setState");
    MQTTclient.subscribe("lights/zap2/setState");
    MQTTclient.subscribe("lights/zap3/setState");
    MQTTclient.subscribe("lights/zap4/setState");
    MQTTclient.subscribe("lights/zap5/setState");
    MQTTclient.subscribe("lights/zap6/setState");
    MQTTclient.subscribe("lights/zap7/setState");
    MQTTclient.subscribe("lights/zap8/setState");
    MQTTclient.subscribe("lights/zap9/setState");
    MQTTclient.subscribe("lights/zap10/setState");

  }

  return MQTTclient.connected();
}

void sendLightStatusOverMQTT(const char* topic, bool state) {

    DynamicJsonDocument MQTTPubPayload(capacity);

    MQTTPubPayload["On"] = state;

    char buffer[512];
    size_t n = serializeJson(MQTTPubPayload, buffer);
    MQTTclient.publish(topic, buffer, n);
}

void setup() {

  Serial.begin(115200);
  while (!Serial); // wait for serial attach

  Serial.flush();

  Serial.println("Initializing... RC-Switch");
  Serial.println();

  WiFiManager wifiManager;

  //reset saved settings
  //wifiManager.resetSettings();

  wifiManager.autoConnect("RCSwitch");

  // this sets the MQTT client and its callback
  Serial.println("Setting MQTT client...");
  MQTTclient.setServer(mqtt_server, 1883);
  MQTTclient.setCallback(MQTTcallback);
  startMQTTmillis = 0;

  sender.enableTransmit(transmit_pin);
  sender.setPulseLength(pulseLength);
  sender.setRepeatTransmit(repeatTransmit);

  receiver.enableReceive(receiver_pin);
  receiver.setPulseLength(pulseLength);
  receiver.setRepeatTransmit(repeatTransmit);

}

void loop() {

  if (!MQTTclient.connected()) {

    currentMQTTmillis = millis();

    if (currentMQTTmillis - startMQTTmillis > MQTTdelay) {

      Serial.println("MQTT not connected...");
      Serial.println("reconnecting...");
      startMQTTmillis = currentMQTTmillis;

      // Attempt to reconnect
      if (reconnect()) {
        startMQTTmillis = 0;
      }
    }
  } else {

    // Client connected
    MQTTclient.loop();
  }

  if (receiver.available()) {

    for (size_t i = 0; i < 10; i++) {
      bool test = testTristate(receiver.getReceivedValue(), receiver.getReceivedBitlength(), ON[i]);
      if (test) sendLightStatusOverMQTT(getStates[i], true);
      Serial.print(i);
      Serial.print(test);
    }

    for (size_t i = 0; i < 10; i++) {
      bool test = testTristate(receiver.getReceivedValue(), receiver.getReceivedBitlength(), OFF[i]);
      if (test) sendLightStatusOverMQTT(getStates[i], false);
      Serial.print(i);
      Serial.print(test);
    }

    receiver.resetAvailable();

  }
}
