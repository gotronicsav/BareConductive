#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4

#define firstPin 0
#define lastPin 11

#define Rouge 9
#define Vert 10
#define Bleu 11

int r, v, b;
boolean onoff;

void setup() {

  if (!MPR121.begin(MPR121_ADDR)){}
  MPR121.setInterruptPin(MPR121_INT);
  MPR121.setTouchThreshold(40);
  MPR121.setReleaseThreshold(20);

  pinMode(Rouge, OUTPUT);
  pinMode(Vert, OUTPUT);
  pinMode(Bleu, OUTPUT);

  onoff=true;
  r=v=b=255;
  analogWrite(Rouge, r);
  analogWrite(Vert, v);
  analogWrite(Bleu, b);
}

void loop() {

  if (MPR121.touchStatusChanged()) {

    MPR121.updateTouchData();

    if (MPR121.getNumTouches() <= 1) {
      for (int i = 0; i < 12; i++) {
        if (MPR121.isNewTouch(i)) {

          if(i == 9){
            if(onoff == true){
              r=v=b=0; 
              onoff=0;
            }else{
              r=v=b=255; 
              onoff=1;
            }
          }
          
          if(i == 11){r=v=b=64;}
          if(i == 10){r=v=b=128;}
          if(i == 8){r=v=b=192;}
          if(i == 7){r=v=b=255;}
          
          if (i == 5) {r-=15; if(r<0) {r=0;} }
          if (i == 4) {r+=15; if(r>255) {r=255;} }
          if (i == 3) {v-=15; if(v<0) {v=0;} }
          if (i == 2) {v+=15; if(v>255) {v=255;} }
          if (i == 1) {b-=15; if(b<0) {b=0;} }
          if (i == 0) {b+=15; if(b>255) {b=255;} }

        analogWrite(Rouge, r);
        analogWrite(Vert, v);
        analogWrite(Bleu, b);

        delay(30);

        } else {if (MPR121.isNewRelease(i)) {}}
      }
    }
  }
}
