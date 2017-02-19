void pir_loop(){
  int pirState = digitalRead(pinPir);  
  
  if (pirState != pirOldState){
    client.publish(pir_state_topic, pirState==HIGH?on_cmd:off_cmd,TRUE);
    pirOldState = pirState;
  }
}

