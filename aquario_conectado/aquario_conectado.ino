/*
 * Jonathas Eide Fujii
 * jonathasfujii@gmail.com
 * 01/01/2017
 * 
 * Arduino IDE v1.8.0
 */

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h> // https://github.com/bblanchon/ArduinoJson
#include <PubSubClient.h> // http://pubsubclient.knolleary.net/
#include <OneWire.h>
#include <DallasTemperature.h>

const byte pinLedEsp = 2;

//// WIFI ////
const char* ssid = "";
const char* password = "";
const char* senha_ota = "";

//// MQTT ////
const char* mqtt_server = "192.168.1.16";
const char* mqtt_username = "";
const char* mqtt_password = "";
const char* client_id = "esp12-aquario"; // Must be unique on the MQTT network
const char* temperatura_state_topic = "casa/aquario/temperatura";
const char* start_state_topic = "casa/aquario/start";
const char* pir_state_topic = "casa/aquario/pir";
const char* light_state_topic = "casa/aquario/rgb";
const char* light_set_topic = "casa/aquario/rgb/set";
const char* aquecedor_state_topic = "casa/aquario/aquecedor";
const char* aquecedor_set_topic = "casa/aquario/aquecedor/set";
const char* bomba_ar_state_topic = "casa/aquario/bomba_ar";
const char* bomba_ar_set_topic = "casa/aquario/bomba_ar/set";
const char* racao_state_topic = "casa/aquario/racao";
const char* racao_set_topic = "casa/aquario/racao/set";
const char* on_cmd = "ON";
const char* off_cmd = "OFF";
const int BUFFER_SIZE = JSON_OBJECT_SIZE(10);

WiFiClient espClient;
PubSubClient client(espClient);

//// Sensor Temperatura ////
const byte pinTemp = 12;
OneWire oneWire(pinTemp); // Setup a oneWire instance to communicate with any OneWire devices 
DallasTemperature sensors(&oneWire);
long lastTimeTemp = 0;
float temp = 0;
long sleepTemp = 60000; // 1 minuto

//// Sensor PIR ////
const byte pinPir = 13;
byte pirOldState = LOW;
//const int sleepPir = 60;
//long lastTimerPir = 0;

//// Luz RGB ////
const byte pinRed = 5;
const byte pinGreen = 4;
const byte pinBlue = 3;
// Maintained state for reporting to HA
byte red = 255;
byte green = 255;
byte blue = 255;
byte brightness = 255;
// Real values to write to the LEDs (ex. including brightness and state)
byte realRed = 0;
byte realGreen = 0;
byte realBlue = 0;
bool stateOn = false;
// Globals for fade/transitions
bool startFade = false;
unsigned long lastLoop = 0;
int transitionTime = 0;
bool inFade = false;
int loopCount = 0;
int stepR, stepG, stepB;
int redVal, grnVal, bluVal;
// Globals for flash
bool flash = false;
bool startFlash = false;
int flashLength = 0;
unsigned long flashStartTime = 0;
byte flashRed = red;
byte flashGreen = green;
byte flashBlue = blue;
byte flashBrightness = brightness;

//// Atuadores Relay ////
const byte pinAquecedor = 14;
const byte pinBombaAr = 16;
const byte pinRacao = 15;
long lastTimeRacao = 0;
int bounceTimeRacao = 500;


