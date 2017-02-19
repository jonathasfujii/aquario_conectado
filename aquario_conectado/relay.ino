void desligaRacao(){
  if(digitalRead(pinRacao) == HIGH && millis() - lastTimeRacao > bounceTimeRacao){
      digitalWrite(pinAquecedor, LOW); 
  }
}

// proteção de aquecimento, deliga acima de 30 graua e deliga acima de 30 minutos
void desligaAquecedor(){
  if(digitalRead(pinAquecedor) == HIGH && (temp < 1 || temp > 30 || millis() - lastTimeTemp > sleepTemp * 30)){
      digitalWrite(pinAquecedor, LOW); 
  }
}
