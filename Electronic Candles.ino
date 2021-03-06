// this is an electronic candle made with neopixel


#include <Adafruit_NeoPixel.h>
#include <ColorConverter.h>

const int neoPixelPin = 5;   // control pin
const int pixelCount = 7;    // number of pixels
int change = 1;    
int changehue = 1; 
int delaytime[] = {0,0,0,10,10,10,0,0,0,0,20,50}; //options of delay time 
int chooseside = 1;         

// set up strip:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelCount, neoPixelPin, NEO_GRBW + NEO_KHZ800);
ColorConverter converter;

// divided the neopixel into two parts
int h = 15;         // hue of part one
int h2 = 15;        // hue of part two
int s = 100;        // saturation
int i = 40;        // intensity of part one
int i2 = 80;      //intensity of part two

void setup() {
  strip.begin();    // initialize pixel strip
  strip.clear();    // turn all LEDs off
  strip.show();     // update strip
  Serial.begin(9600);
}

void loop() {
  
  RGBColor color = converter.HSItoRGB(h, s, i);
  RGBColor color2 = converter.HSItoRGB(h2, s, i2);

  // loop over all the pixels:

  for (int pixel = 0; pixel < pixelCount; pixel++) {
    if(pixel <3) strip.setPixelColor(pixel, color.red, color.green, color.blue);   
    if(pixel>=3) strip.setPixelColor(pixel, color2.red, color2.green, color2.blue);  
    strip.show();   
  }
  

  //making the light bouncing between part one and part two
   i = i + change; 
   i2 = i2 - change; 
   int n = random(12);
   delay(delaytime[n]);
  
   if(i>100){
      change = -1*random(4);     
  }
   if(i<10){
    change = random(3);
  }

  //slightly switching the hue of part two 
  h2 = h2 + changehue;
  if (h2 < 14 || h2 > 15) {
    changehue = -changehue;
  }

  //Serial.println(h2);
 
}
