#include <Wire.h>
#include <ds3231.h>

ts t; //ts is a struct findable in ds3231.h

void setup() {
  Wire.begin(); //start i2c (required for connection)
  DS3231_init(DS3231_INTCN); //register the ds3231 (DS3231_INTCN is the default address of ds3231, this is set by macro for no performance loss)
  Serial.begin(9600);
  while(!Serial){} //only need for leonardo
}

void loop() {
  DS3231_get(&t); //get the value and pass to the function the pointer to t, that make an lower memory fingerprint and faster execution than use return
  //DS3231_get() will use the pointer of t to directly change t value (faster, lower memory used)
  Serial.print("Day : ");
  Serial.print(t.mon); //just print some data
  Serial.print("/");
  Serial.print(t.mday);
  Serial.print("/");
  Serial.println(t.year);
  Serial.print("Hour : ");
  Serial.print(t.hour);
  Serial.print(":");
  Serial.print(t.min);
  Serial.print(".");
  Serial.print(t.sec);
  Serial.print(" Day Week: ");
  Serial.println(t.wday);

  delay(1500);

}
