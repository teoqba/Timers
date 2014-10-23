// BLINK on 32kHz

volatile long tSeconds = 0;
volatile long tUnits = 0; //time units
int led = 8;
int counter = 0;

void setup(){
  //set up Timer0 interrupts
  cli();
  TCCR0A = _BV(WGM01); // turn on CTC
  TCCR0B = _BV(CS02); // set prescaler to 256
  OCR0A = 15; // set number to compare
  TIMSK0 = _BV(OCIE0A); // set interrupt on CTC match
  sei();
  Serial.begin(1024);
  pinMode(led,OUTPUT);
 // delaySeconds(2);
  
}

ISR(TIMER0_COMPA_vect)
{
  tUnits += 1;
  if (tUnits % 8 == 0){
    tSeconds += 1;}
}

void loop(){
/*  if (tSeconds%2 == 0){
    digitalWrite(led,HIGH);
  }
  else{
    digitalWrite(led,LOW);
  }
  */
  digitalWrite(led,HIGH);
  delaySeconds(1);
  digitalWrite(led,LOW);
  delaySeconds(1);  
  counter += 1;
 Serial.println(counter);
}
int seconds(){
  cli();
  long s = tSeconds;
  sei();
  return s;}
  
int units(){
  cli();
  long u = tUnits;
  sei();
  return u;}
  
void delaySeconds(int t){
  long now = seconds();
  while (seconds() - now < t){}
}

void delaySeconds2(int t){
  long now = units();  
  while (units() - now < t*8){}
  
}  
