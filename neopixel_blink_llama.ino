#include <Adafruit_NeoPixel.h>

#define PIN            1
#define NUMPIXELS      1

int led = 2;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100; 

void setup() {
  strip.begin(); 
  pinMode(led, OUTPUT);
}

void loop() {   
  rainbowCycle(20);
  evilFlash(1000);
}

void evilFlash(uint8_t wait){
  while(wait>10){  
    strip.setPixelColor(0, strip.Color(255, 0, 0));
    strip.show();
    delay(wait);
    digitalWrite(led, HIGH);
    
    int twait = (wait*0.1);
    wait = wait - twait;
    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
    delay((twait*10));    
    digitalWrite(led, LOW);
  }

  strip.setPixelColor(0, strip.Color(255, 0, 0));
  strip.show();
  digitalWrite(led, HIGH);
  delay((wait*0.5));
  strip.setPixelColor(0, strip.Color(0, 0, 0));
  strip.show();
  digitalWrite(led, LOW);
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  
  for(j=0; j<256*5; j++) {
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
  
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
