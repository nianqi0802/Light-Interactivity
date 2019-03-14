#include <SimpleKalmanFilter.h>

#include <Adafruit_NeoPixel.h>
#include <ColorConverter.h>

SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.01);
const long SERIAL_REFRESH_TIME = 100;
long refresh_time;

int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo
long duration, distance; //cm

long last_value;

const int neoPixelPin = 3;  //pin
const int pixelCount = 62;   //number of pixels

// set up strip:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelCount, neoPixelPin, NEO_GRB+ NEO_KHZ800);
ColorConverter converter;


int h = 200;
int s = 40;

int brightness = 50;

int threshold;


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  strip.begin();   //initialize pixel strip
  strip.clear();   //turn off all LEDs
  strip.show();    //refresh strip

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {

  // read a reference value from A0 and map it from 0 to 100
  distance = (duration/2) / 29.1;
  float real_value = (duration/2) / 29.1;;
  if(real_value > 400) real_value = last_value;

 //Serial.println(real_value);
  
  // add a noise to the reference value and use as the measured value
  float measured_value = real_value + random(-100,100)/100.0;

  // calculate the estimated value with Kalman Filter
  float estimated_value = simpleKalmanFilter.updateEstimate(measured_value);

  // send to Serial output every 100ms
  // use the Serial Ploter for a good visualization
  if (millis() > refresh_time) {

    refresh_time = millis() + SERIAL_REFRESH_TIME;
  }

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
   pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  //distance = (duration/2) / 29.1;
  //constrain(distance,0,400);

  brightness = map(estimated_value, 100, 0, 0 , 100);
  //Serial.println(distance);

  last_value = real_value;
  
  RGBColor color = converter.HSItoRGB(h,s,brightness);

  Serial.println(brightness);
  
   //put your main code here, to run repeatedly:
  for (int pixel = 0; pixel < pixelCount; pixel++) {      
    strip.setPixelColor(pixel,color.red,color.green,color.blue);
        
   strip.show();
   }   
  }

  

  
