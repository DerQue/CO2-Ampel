#include <WiFi.h>
#include <PubSubClient.h>

#include "led.h"

class MQTT
{
private:
    int triesWiFi;
    int triesMQTT;

    WiFiClient espClient;
    PubSubClient client;

    void tickWiFi(Led led);
    void tickMQTT(Led led);
public:
    MQTT();
    void tick(Led led);
    void publish(const char *topic, const char *data);
};

