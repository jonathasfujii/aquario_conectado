/*
 * Jonathas Eide Fujii
 * jonathasfujii@gmail.com
 * 31/12/2016
 */

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h> // https://github.com/bblanchon/ArduinoJson
#include <PubSubClient.h> // http://pubsubclient.knolleary.net/

//// WIFI ////
const char* ssid = "";
const char* password = "";
const char* senha_ota = "";


const byte pinRelay1 = 14;
const byte pinRelay2 = 16;

const byte pinTrnasistor = 15;

const byte pinTemp = 12;
const byte pinPir = 13;

//// MQTT ////
const char* mqtt_server = "";
const char* mqtt_username = "";
const char* mqtt_password = "";
const char* client_id = "esp12-aquario"; // Must be unique on the MQTT network

//// RGB ////
const byte pinRed = 5;
const byte pinGreen = 4;
const byte pinBlue = 3;

// Topics
const char* light_state_topic = "casa/aquario/rgb";
const char* light_set_topic = "casa/aquario/rgb/set";

const char* on_cmd = "ON";
const char* off_cmd = "OFF";

const int BUFFER_SIZE = JSON_OBJECT_SIZE(10);

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

WiFiClient espClient;
PubSubClient client(espClient);



