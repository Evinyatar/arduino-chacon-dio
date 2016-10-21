int pin = 5;

void setup() {
  pinMode(pin, OUTPUT);  
  Serial.begin(9600);
}

void loop() {
  //1,12325261,1
  if(Serial.available() > 0) {
    String interruptorStr = Serial.readStringUntil(',');
    String senderStr = Serial.readStringUntil(',');
    String stateStr = Serial.readStringUntil('\n');

    unsigned long interruptor = interruptorStr.toInt();
    unsigned long sender = senderStr.toInt();
    unsigned long state = stateStr.toInt();
        
    for (int i = 0; i < 5; i++) {
      transmit(sender, interruptor, state != 0);
      delay(10);
    } 

    Serial.print("Interruptor: ");
    Serial.print(interruptor);
    Serial.print("\n");
    Serial.print("Sender: ");
    Serial.print(sender);
    Serial.print("\n");
    Serial.print("State: ");
    Serial.print(state!=0 ? "On" : "Off");
    Serial.print("\n");
  }
}
 
void sendBit(bool b) {
  if (b) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(310);   //275 originally, but tweaked.
    digitalWrite(pin, LOW);
    delayMicroseconds(1340);  //1225 originally, but tweaked.
  } else {
    digitalWrite(pin, HIGH);
    delayMicroseconds(310);   //275 originally, but tweaked.
    digitalWrite(pin, LOW);
    delayMicroseconds(310);   //275 originally, but tweaked.
  }
}
 
void sendPair(bool b) {
  if (b) {
    sendBit(true);
    sendBit(false);
  } else {
    sendBit(false);
    sendBit(true);
  }
}
 
void transmit(unsigned long sender, int interruptor, int blnOn) {
  int i;
 
  digitalWrite(pin, HIGH);
  delayMicroseconds(275);
  digitalWrite(pin, LOW);
  delayMicroseconds(9900);   // first lock
  digitalWrite(pin, HIGH);   // high again
  delayMicroseconds(275);    // wait
  digitalWrite(pin, LOW);    // second lock
  delayMicroseconds(2675);
  digitalWrite(pin, HIGH);

  // Emiter ID
  for(i = 0; i < 26; i++) {
    sendPair( (sender >> (25 - i)) & 0b1);
  }
 
  // 26th bit -- grouped command
  sendPair(false);
 
  // 27th bit -- On or off
  sendPair(blnOn);
 
  // 4 last bits -- reactor code 0000 -&gt; 0 -- 0001 -&gt; 1
  for (i = 0; i < 4; i++) {
    sendPair( (interruptor >> (3 - i)) & 1 );
  }
 
  digitalWrite(pin, HIGH);   // lock - end of data
  delayMicroseconds(275);    // wait
  digitalWrite(pin, LOW);    // lock - end of signal
}
