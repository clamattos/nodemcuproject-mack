#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include "Secrets.h"
#include "DHT.h"

#define DHTPIN 2        // Digital pin connected to the DHT sensor (in NodeMCU = D4) - referenced as GPIO (General Purpose Input/Output) numbers
#define DHTTYPE DHT11   
#define LED_PIN 5       // Digital pin connected to the DHT sensor (in NodeMCU = D1) - referenced as GPIO (General Purpose Input/Output) numbers

DHT dht(DHTPIN, DHTTYPE);

unsigned long lastMillis = 0;
unsigned long previousMillis = 0;
const long interval = 5000;
float h;
float t;

#define AWS_IOT_PUBLISH_TOPIC   "dashboard/data/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "dashboard/data/sub"

WiFiClientSecure net;

BearSSL::X509List cert(cacert);
BearSSL::X509List client_crt(client_cert);
BearSSL::PrivateKey key(privkey);

PubSubClient client(net);

time_t now;
time_t nowbefore = 1510592825;

unsigned int message_id = 0;  

void NTPConnect(void)
{
  Serial.print("Setting time using SNTP");
  configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov"); // Timezone configuration - BRA
  now = time(nullptr);
  while (now < nowbrefore)
  {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("done!");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
}

void messageReceived(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Received [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void connectAWS()
{
  delay(3000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println(String("Connecting to SSID: ") + String(WIFI_SSID));

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }

  NTPConnect();

  net.setTrustAnchors(&cert);
  net.setClientRSACert(&client_crt, &key);

  client.setServer(MQTT_HOST, 8883);
  client.setCallback(messageReceived);

  Serial.println("Connecting to AWS IOT Core");

  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(1000);
  }

  if (!client.connected()) {
    Serial.println("AWS IoT Core timed out! Retrying");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Core is connected!");
}

void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["message_id"] = message_id++; 
  doc["time"] = millis();
  doc["humidity"] = h;
  doc["temperature"] = t;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client a serialized JSON file

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void setup()
{
  Serial.begin(9600);
  connectAWS();
  dht.begin();
  pinMode(LED_PIN, OUTPUT); // Define the LED pin as an output (as said before, GPIO 5 = D1 pin)
  digitalWrite(LED_PIN, HIGH); // Turn on the LED when connected
}


void loop()
{
  delay(3000); // Delay 3 seconds

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity))  // Failed message if temperature / humidity not working
  {
    Serial.println(F("Failed to read from sensor! Retrying"));
    return;
  }

  Serial.print(F("Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C"));

  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.println(F("%"));

  if (temperature >= 23.50) {
    digitalWrite(LED_PIN, HIGH); // Turn on the LED
  } else {
    digitalWrite(LED_PIN, LOW); // Turn off the LED
  }

  h = humidity;
  t = temperature;

  now = time(nullptr);

  if (!client.connected())
  {
    connectAWS();
  }
  else
  {
    client.loop();
    if (millis() - lastMillis > 5000)
    {
      lastMillis = millis();
      publishMessage();
    }
  }
}
