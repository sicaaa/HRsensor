/*

Hardware Assembly

Sensor:               Arduino:
PulseSensor (signal)  A0	  Analog input
PulseSensor (VCC)	    5V	  Power
PulseSensor (GND)	    GND	  Ground
NeoPixel Data In	    6	    Digital output pin
NeoPixel VCC	        5V	  Power
NeoPixel GND	        GND	  Ground

*/


#include <Adafruit_NeoPixel.h>

// ----- Pin Definitions -----
#define PULSE_PIN A0          // PulseSensor connected to Analog Pin A0
#define LED_PIN   6           // NeoPixel data pin
#define NUMPIXELS 1           // Number of NeoPixels

// ----- Objects -----
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

// ----- Variables -----
int pulseValue = 0;           // Analog value from PulseSensor
int threshold = 550;          // Adjust this value based on your sensor
bool heartbeat = false;       // True when a beat is detected

void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.show();              // Initialize all pixels to 'off'
}

void loop() {
  pulseValue = analogRead(PULSE_PIN);
  Serial.println(pulseValue); // For debugging, view in Serial Plotter

  // --- Detect heartbeat ---
  if (pulseValue > threshold && !heartbeat) {
    heartbeat = true;
    pulseFlash();             // Flash the LED
  }

  if (pulseValue < threshold) {
    heartbeat = false;        // Reset after beat
  }

  delay(10); // Small delay for stability
}




// ----- LED Pulse Effect -----
void pulseFlash() {
  // Turn LED bright blue when a heartbeat is detected 
  // pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // Red
  // pixels.setPixelColor(0, pixels.Color(0, 255, 0)); // Green
  // pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // Blue
  // pixels.setPixelColor(0, pixels.Color(255, 255, 255)); // White
  // pixels.setPixelColor(0, pixels.Color(255, 255, 0)); // Yellow (Red + Green)
  pixels.setPixelColor(0, pixels.Color(0, 255, 255)); // Purple (Red + Blue)
  pixels.show();
  delay(100);

  // Turn LED off again
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));  // Off
  pixels.show();
}



