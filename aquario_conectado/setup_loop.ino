void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("esp12-aquario");

  // No authentication by default
  ArduinoOTA.setPassword(senha_ota);

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  pinMode(pinLedEsp, OUTPUT);
  digitalWrite(pinLedEsp, LOW);

  //// Sensor Temperatura ////
  pinMode(pinTemp, INPUT);
  sensors.begin();

    //// Temperatura ////
  pinMode(pinPir, INPUT_PULLUP);
  
  //// RGB ////
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  analogWriteRange(255);

  //// Atuadores Relay ////
  pinMode(pinAquecedor, OUTPUT);
  digitalWrite(pinAquecedor, LOW);
  pinMode(pinBombaAr, OUTPUT);
  digitalWrite(pinBombaAr, LOW);
  pinMode(pinRacao, OUTPUT);
  digitalWrite(pinRacao, LOW);
  
  //// MQTT ////
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);


}

void loop() {
  ArduinoOTA.handle();
  mqtt_loop();
  pir_loop();
  rgb_loop();
  temperatura_loop();
  desligaRacao();
  desligaAquecedor();
}
