void mqtt_loop(){
  //// MQTT ////
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(client_id, mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.subscribe(light_set_topic);
      client.subscribe(aquecedor_set_topic);
      client.subscribe(bomba_ar_set_topic);
      client.subscribe(racao_set_topic);

      char buffer[50];
      sprintf(buffer, "{\"client_id\":\"%s\",\"ip\":\"%s\"}", client_id, WiFi.localIP().toString().c_str());
      client.publish(start_state_topic, buffer);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print(topic);
  
  if(strcmp(topic,light_set_topic)==0) {//// RGB ////  
    char message[length + 1];
    for (int i = 0; i < length; i++) {
      message[i] = (char)payload[i];
    }
    message[length] = '\0';
    if (!processJson(message)) {
      return;
    } 
    if (stateOn) {
      // Update lights
      realRed = map(red, 0, 255, 0, brightness);
      realGreen = map(green, 0, 255, 0, brightness);
      realBlue = map(blue, 0, 255, 0, brightness);
    }
    else {
      realRed = 0;
      realGreen = 0;
      realBlue = 0;
    }  
    startFade = true;
    inFade = false; // Kill the current fade  
    sendState(); 
  } else if (strcmp(topic,aquecedor_set_topic)==0){//// Aquecedor ////
      char msg[length];
      snprintf(msg, length+1, "%s", payload);
      if (strcmp(msg,on_cmd)==0) { 
        digitalWrite(pinAquecedor, HIGH);   
        client.publish(aquecedor_state_topic, on_cmd);
        lastTimeTemp = millis();
      } else {
        digitalWrite(pinAquecedor, LOW);   
        client.publish(aquecedor_state_topic, off_cmd);
      }
  } else if(strcmp(topic,bomba_ar_set_topic)==0){ //// Bomba Ar ////
      char msg[length];
      snprintf(msg, length+1, "%s", payload);
      if (strcmp(msg,on_cmd)==0) { 
        digitalWrite(pinBombaAr, HIGH);   
        client.publish(bomba_ar_state_topic, on_cmd);
      } else {
        digitalWrite(pinBombaAr, LOW);   
        client.publish(bomba_ar_state_topic, off_cmd);
      }      
  } else if(strcmp(topic,racao_set_topic)==0){//// Racao ////
      char msg[length];
      snprintf(msg, length+1, "%s", payload);
      if (strcmp(msg,on_cmd)==0) {
        digitalWrite(pinRacao, HIGH);  
        client.publish(racao_state_topic, on_cmd);
        lastTimeRacao = millis(); 
      } else {
        digitalWrite(pinRacao, LOW);   
        client.publish(racao_state_topic, off_cmd);
      }

  }
}



