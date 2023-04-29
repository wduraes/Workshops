#define CARGREEN 4
#define CARRED 6
#define CARYELLOW 5
#define PEDGREEN 2
#define PEDRED 3
#define PEDBUTTON A5
#define BUZZER 8

const int pingPin = 11; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 12; // Echo Pin of Ultrasonic Sensor

#define MIN_TIME_4_CARS 5000  // minimum interval for cars to go, before opening for pedestrians again
unsigned long lastOpened = 0; // when was the traffic light last opened
bool ped = false;             // do we have a request for crossing?

void setup()
{
    pinMode(CARGREEN, OUTPUT);
    pinMode(CARRED, OUTPUT);
    pinMode(CARYELLOW, OUTPUT);
    pinMode(PEDGREEN, OUTPUT);
    pinMode(PEDRED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(PEDBUTTON, INPUT);
    pinMode(pingPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void GreenToCars()
{
    // turn Red light off and green light on
    digitalWrite(CARRED, LOW);
    digitalWrite(CARGREEN, HIGH);
}

void YellowToCars(int duration)
{
    // turn green light off and yellow light on. Wait for [duration in seconds] on that state
    digitalWrite(CARGREEN, LOW);
    digitalWrite(CARYELLOW, HIGH);
    delay(duration * 1000);
}

void RedToCars()
{
    // turn red light on and yellow light off
    digitalWrite(CARRED, HIGH);
    digitalWrite(CARYELLOW, LOW);
}

void GreenForPed(int beeps)
{
    // turn green light for pedestrians on and the red light off
    //  it also beeps for [beeps] number of times, to let pedestrians know it is safe to cross
    digitalWrite(PEDGREEN, HIGH);
    digitalWrite(PEDRED, LOW);
    for (int i = 0; i < beeps; i++)
    {
        tone(8, 400, 50);
        delay(450);
    }
}

void RedForPed()
{
    // turn red light for pedestrians on and the green light off
    digitalWrite(PEDGREEN, LOW);
    digitalWrite(PEDRED, HIGH);
}

void BlinkForPed(int blinks, int safeDelay)
{
    // turn green light for pedestrians off and blinks the red light for [blinks] number of times
    // then waits for additional [safeDelay] before opening for cars
    digitalWrite(PEDGREEN, LOW);
    for (int i = 0; i < blinks; i++)
    {
        digitalWrite(PEDRED, LOW);
        delay(200);
        digitalWrite(PEDRED, HIGH);
        delay(200);
    }
    delay(safeDelay);
}

long microsecondsToInches(long microseconds)
{
    return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
    return microseconds / 29 / 2;
}

void loop()
{
    long duration, inches, cm;
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    inches = microsecondsToInches(duration);
    cm = microsecondsToCentimeters(duration);

    // checks for pedestrian button pressed
    if (digitalRead(PEDBUTTON) == HIGH || cm < 10)
    {
        ped = true;
        tone(8, 1000, 30); // acknowledged the button press with a beep
    }

    // if ped button has been pressed, wait until the minimum interval for cars has been achieved
    if (ped)
    {
        if (millis() > lastOpened + MIN_TIME_4_CARS)
        {
            // state machine
            YellowToCars(2); // duration of yellow in seconds
            RedToCars();
            GreenForPed(6);      // duration in beeps
            BlinkForPed(6, 500); // duration in blinks, safety delay in milliseconds
            ped = false;
            lastOpened = millis(); // update time
        }
    }
    // if the button is not pressed, it will be always green for cars and red for peds.
    else
    {
        RedForPed();
        GreenToCars();
    }
}
