void desligaRacao(){
  if(digitalRead(pinRacao) == HIGH && millis() - lastTimeRacao > 8000){
      digitalWrite(pinRacao, LOW); 
      client.publish(racao_state_topic, off_cmd);
  }
}

// proteção de aquecimento, deliga acima de 30 graua e deliga acima de 30 minutos
void desligaAquecedor(){
  if(digitalRead(pinAquecedor) == HIGH && millis() - lastTimeTemp > 30 * 60000){
      digitalWrite(pinAquecedor, LOW); 
      client.publish(aquecedor_state_topic, off_cmd);
  }
  if(digitalRead(pinAquecedor) == HIGH && (temp < 1 || temp > 30) && millis() - lastTimeTemp > 10000){
      digitalWrite(pinAquecedor, LOW); 
      client.publish(aquecedor_state_topic, off_cmd);
  }
}
