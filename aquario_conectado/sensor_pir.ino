void pir_loop(){
  int pirState = digitalRead(pinPir);  
  
  if (pirState != pirOldState){
    if(pirState == HIGH){
      client.publish(pir_state_topic, on_cmd,TRUE);
    }
    pirOldState = pirState;
  }
}

