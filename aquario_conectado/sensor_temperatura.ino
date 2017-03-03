void temperatura_loop(){
  long now = millis();
  
  if (now - lastTimeTemp > 120000) {
    lastTimeTemp = now;
    sensors.setResolution(12);
    sensors.requestTemperatures(); // Send the command to get temperatures
    temp = sensors.getTempCByIndex(0);
    //Serial.println(temp);
    if((temp > -20) && (temp <100)){
      client.publish(temperatura_state_topic, String(temp).c_str(),TRUE);
    }
  }
}
