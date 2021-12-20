#include <WiFi.h>
#include <PubSubClient.h>

#include "config.h"
#include "mqtt.h"

MQTT::MQTT() {
    this->triesMQTT = 0;
    this->triesWiFi = 0;

    this->client = PubSubClient(this->espClient);
    this->client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
}

void MQTT::tick(Led led) {
    this->tickWiFi(led);
    this->tickMQTT(led);
}

void MQTT::tickWiFi(Led led) {
    if(WiFi.isConnected()) return;
    if(this->triesWiFi > MAX_WIFI_TRIES) return;
    led.drawRing(LEDS_COLOR_INFO);

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    Serial.print("Verbinde mit Wlan ");
    Serial.print(WIFI_SSID);
    int connectTries = 0;
    while (!(WiFi.status() == WL_CONNECTED || connectTries >= 30)) {
        Serial.print(".");
        connectTries++;
        delay(1000);
    }
    Serial.println();

    if(WiFi.isConnected()) {
        Serial.println("Verbunden.");
        this->triesWiFi = 0;
        return;
    } else {
        Serial.println("Verbinden fehlgeschlagen.");
        this->triesWiFi++;
    }
}

void MQTT::tickMQTT(Led led) {
    if(client.connected()) return;
    if(!WiFi.isConnected()) return;
    if(this->triesMQTT >= MAX_MQTT_TRIES) return;
    
    led.drawRing(LEDS_COLOR_INFO);

    Serial.print("Verbinde mit MQTT-Server ");
    if (!client.connect(MQTT_NAME)) {
        Serial.print("Verbinden fehlgeschlagen.");
        Serial.println(client.state());
        this->triesMQTT++;
        return;
    }

    Serial.print("Verbunden.");
    this->triesMQTT = 0;
}

void MQTT::publish(const char *topic, const char *data) {
    this->client.publish(topic, data);
}