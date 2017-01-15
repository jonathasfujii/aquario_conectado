void temperatura(){
  long now = millis();
  if (now - lastMsg > 60000) {
    lastMsg = now;
    sensors.setResolution(12);
    sensors.requestTemperatures(); // Send the command to get temperatures
    temp = sensors.getTempCByIndex(0);
    Serial.println(temp);
    if((temp > -20) && (temp <60))
      {
      client.publish(temperatura_set_topic, String(temp).c_str(),TRUE);
      }
  }
}
