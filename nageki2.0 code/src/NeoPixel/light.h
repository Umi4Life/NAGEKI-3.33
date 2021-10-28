#include <Adafruit_NeoPixel.h>

class Strip
{
public:
  uint8_t   effect;
  uint8_t   effects;
  uint16_t  effStep;
  unsigned long effStart;
  Adafruit_NeoPixel strip;
  Strip(uint16_t leds, uint8_t pin, uint8_t toteffects, uint16_t striptype) : strip(leds, pin, striptype) {
    effect = -1;
    effects = toteffects;
    Reset();
  }
  void Reset(){
    effStep = 0;
    effect = (effect + 1) % effects;
    effStart = millis();
  }
};

struct Loop
{
  uint8_t currentChild;
  uint8_t childs;
  bool timeBased;
  uint16_t cycles;
  uint16_t currentTime;
  Loop(uint8_t totchilds, bool timebased, uint16_t tottime) {currentTime=0;currentChild=0;childs=totchilds;timeBased=timebased;cycles=tottime;}
};

Strip strip_0(12, 21, 12, NEO_GRB + NEO_KHZ800);
struct Loop strip0loop0(1, false, 1);

//[GLOBAL_VARIABLES]


void loop() {

  //Your code here:

  strips_loop();
}

void strips_loop() {
  if(strip0_loop0() & 0x01)
    strip_0.strip.show();
}

uint8_t strip0_loop0() {
  uint8_t ret = 0x00;
  switch(strip0loop0.currentChild) {
    case 0: 
           ret = strip0_loop0_eff0();break;
  }
  if(ret & 0x02) {
    ret &= 0xfd;
    if(strip0loop0.currentChild + 1 >= strip0loop0.childs) {
      strip0loop0.currentChild = 0;
      if(++strip0loop0.currentTime >= strip0loop0.cycles) {strip0loop0.currentTime = 0; ret |= 0x02;}
    }
    else {
      strip0loop0.currentChild++;
    }
  };
  return ret;
}

uint8_t strip0_loop0_eff0() {
    // Strip ID: 0 - Effect: Fade - LEDS: 12
    // Steps: 970 - Delay: 1
    // Colors: 2 (255.0.123, 196.0.0)
    // Options: duration=970, every=1, 
  if(millis() - strip_0.effStart < 1 * (strip_0.effStep)) return 0x00;
  uint8_t r,g,b;
  double e;
  e = (strip_0.effStep * 1) / (double)970;
  r = ( e ) * 196 + 255 * ( 1.0 - e );
  g = ( e ) * 0 + 0 * ( 1.0 - e );
  b = ( e ) * 0 + 123 * ( 1.0 - e );
  for(uint16_t j=0;j<12;j++) {
    if((j % 1) == 0)
      strip_0.strip.setPixelColor(j, r, g, b);
    else
      strip_0.strip.setPixelColor(j, 0, 0, 0);
  }
  if(strip_0.effStep >= 970) {strip_0.Reset(); return 0x03; }
  else strip_0.effStep++;
  return 0x01;
}

