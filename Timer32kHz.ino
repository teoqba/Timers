// BLINK on 32kHz

volatile long seconds = 0;
int led = 8;


void setup(){
  //set up Timer0 interrupts
  cli();
  TCCR0A = _BV(WGM01); // turn on CTC
  TCCR0B = _BV(CS02); // set prescaler to 256
  OCR0A = 127; // set number to compare
  TIMSK0 = _BV(OCIE0A); // set interrupt on CTC match
  sei();
  
  pinMode(led,OUTPUT);
  
}

ISR(TIMER0_COMPA_vect)
{
  seconds += 1;
}

void loop(){
  if (seconds%2 == 0){
    digitalWrite(led,HIGH);
  }
  else{
    digitalWrite(led,LOW);
  }
}

