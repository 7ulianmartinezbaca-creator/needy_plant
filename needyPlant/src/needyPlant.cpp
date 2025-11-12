/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "IoTClassroom_CNM.h"
#include "adafruit_BME280.h"
#include "Grove_Air_Quality_Sensor.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include <Adafruit_MQTT.h>
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h"
#include "Adafruit_MQTT/Adafruit_MQTT.h"
#include "credentails.h"

SYSTEM_MODE(SEMI_AUTOMATIC);

SYSTEM_THREAD(DISABLED);

TCPClient TheClient;

Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SEVERPORT,AIO_USERNAME,AIO_KEY);
Adafruit_MQTT_Subscribe subFeed = Adafruit_MQTT_Subscribe (&mqtt, AIO_USERNAME "/feeds/");
Adafruit_MQTT_Publish pubFeed = Adafruit_MQTT_Publish (&mqtt, AIO_USERNAME "/feeds/");

const int OLED_RESET=-1;

int status;
int moistureRead;
int subval;
int pubval;

unsigned int last, lastTime;

float tempC;
float tempF;
float pressPa;
float inHg;
float humidRh;
float pascal = 3386.39; 

AirQualitySensor sensor (D11);

Adafruit_BME280 bme;
Adafruit_SSD1306 display(OLED_RESET);

void MQTT_connect();
bool MQTT_ping();

void setup() {
  Serial.begin();
  waitFor(Serial.isConnected,10000);

  status = bme.begin(0x76);
  if(status == false) {
    Serial.printf("BME at adress 0x%02X false to start\n",0X76);
  }

  pinMode(D13,INPUT); //capastive sensor 
  pinMode(D15,OUTPUT); //waterpump

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initalization OLED
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.display();
  display.clearDisplay();
  display.display();

  WiFi.on();
  WiFi.connect();
  while (WiFi.connecting()) {
    Serial.printf(".");
  }
  mqtt.subscribe(&subFeed);
}

void loop() {
  MQTT_connect();
  MQTT_ping();

  Adafruit_MQTT_Subscribe* subscription;
  while ((subscription = mqtt.readSubscription(10000))) {
    if (subscription == &subFeed) {
        subval = atoi((char *)subFeed.lastread);
    }
  }

  if ((millis() - lastTime > 10000)) {
    if (mqtt.Update()) {
        //pubFeed.publish();
    }
    lastTime = millis();
  }

  moistureRead = analogRead(D13);
    
  tempC = bme.readTemperature();
  pressPa = bme.readPressure();
  humidRh = bme.readHumidity();
  inHg = pressPa * (1/pascal);
  tempF = 9/5.0 * tempC + 32;
  display.clearDisplay();
  display.setCursor(0,0);
  display.printf("Temp in Room %0.2f\nPressure of Room %0.2f\nHumity of Room %0.2f\n",tempF,inHg,humidRh);
//   Serial.printf("Temp in Room %0.2f\nPressure of Room %0.2f\nHumity of Room %0.2f\n",tempF,inHg,humidRH);
  display.display();
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;
 
  // Return if already connected.
  if (mqtt.connected()) {
    return;
  }
 
  Serial.print("Connecting to MQTT... ");
 
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.printf("Error Code %s\n",mqtt.connectErrorString(ret));
       Serial.printf("Retrying MQTT connection in 5 seconds...\n");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds and try again
  }
  Serial.printf("MQTT Connected!\n");
}

bool MQTT_ping() {
  static unsigned int last;
  bool pingStatus;

  if ((millis()-last)>120000) {
      Serial.printf("Pinging MQTT \n");
      pingStatus = mqtt.ping();
      if(!pingStatus) {
        Serial.printf("Disconnecting \n");
        mqtt.disconnect();
      }
      last = millis();
  }
  return pingStatus;
}
