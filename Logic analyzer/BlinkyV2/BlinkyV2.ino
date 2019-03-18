void setup() 
{
  DDRB = 0b11111111;
}
void loop() 
{
  PORTB = 0b11111111;
  PORTB = 0b00000000;
}
