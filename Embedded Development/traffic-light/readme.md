# Simple traffic light

This sample shows the implementation of a simple traffic light: it has a semaphore for cars (red, yellow and green) and another one for pedestrians who wish to cross the street (with green/whit and red lights).

This sample can be solved with several turn led on and off followed by delays, but implemented that way it becomes harder to read, understand and maintain. This is the reason this sample was implemented using a basic state machine. 

The illustration below shows this state machine:

 ![Distance sensor](../../Images/state-machine.png)

## Breadboard setup:

In this setup you'll need 5 LEDS, 3 of them representing the car semaphore and 2 for the pedestrian semaphore. You'll also need a button for pedestrians to push when they wish to cross the street an a buzzer for sound alerts. 

 ![Distance sensor](../../Images/traffic.png)

## State machine 

In this example, the car uses 2 distance sensors the first one points ahead to detect obstacles and objects. The second one points down to detect edges and stop the vehicle before is fall of edges.

```c
YellowToCars();
RedToCars();
GreenForPed();
BlinkForPed();
```

![Distance sensor](../../Images/car.png)
