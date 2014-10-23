// BLINK on 1MHz

volatile long tSeconds = 0;
volatile long tUnits = 0; //time units
int led = 8;
int sensor = A0;

void setup(){
  //set up Timer0 interrupts
  cli();
  TCCR0A = _BV(WGM01); // turn on CTC
  TCCR0B = _BV(CS01); // set prescaler to 8
  OCR0A = 249; // set number to compare
  TIMSK0 = _BV(OCIE0A); // set interrupt on CTC match
  sei();
  Serial.begin(9600);
  pinMode(led,OUTPUT);
 // delaySeconds(2);
  
}

ISR(TIMER0_COMPA_vect)
{
  tUnits += 1;
  if (tUnits % 500 == 0){
    tSeconds += 1;}
}

void loop(){

  digitalWrite(led,HIGH);
  delaySeconds(1);
  digitalWrite(led,LOW);
  delaySeconds(1);  
  int sensorVal = analogRead(sensor);
  float v = (sensorVal/1024.0) * 3.3;
  float t = (v - .5) *100;
 Serial.println(t);
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
  while (units() - now < t*500){}
  
}  
