//@orga=GoTronic
//@author=Sylvain G.

#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4

#include <SPI.h>
#include <SdFat.h>
#include <FreeStack.h>
#include <SFEMP3Shield.h>

SFEMP3Shield MP3player;
byte resultat;
int sound = 0;

#define firstPin 0
#define lastPin 11

SdFat sd;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  if (!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();

  if (!MPR121.begin(MPR121_ADDR)){}
  MPR121.setInterruptPin(MPR121_INT);

  /* Plus la valeur est basse, plus la peinture conductive
   * détecte un obstacle loin.
   * Par défaut, les valeurs sont 40 et 20.
   * Il faut alors toucher la peinture pour que la détection
   * soit opérationnelle */
  MPR121.setTouchThreshold(40); 
  MPR121.setReleaseThreshold(20);

  resultat = MP3player.begin();
  MP3player.setVolume(50, 50);

}

void loop() {
  readTouchInputs();
}


void readTouchInputs() {
  if (MPR121.touchStatusChanged()) {

    MPR121.updateTouchData();

    if (MPR121.getNumTouches() <= 1) {
      for (int i = 0; i < 12; i++) {
        if (MPR121.isNewTouch(i)) {

          digitalWrite(LED_BUILTIN, HIGH);

          if (i <= lastPin && i >= firstPin) {
            if (MP3player.isPlaying()) {
              if (sound == i) {
                MP3player.stopTrack();
              } else {
                MP3player.stopTrack();
                MP3player.playTrack(i - firstPin);
                sound = i;
              }
            } else {
              MP3player.playTrack(i - firstPin);
              sound = i;
            }
          }
        } else {
          if (MPR121.isNewRelease(i)) {
            digitalWrite(LED_BUILTIN, LOW);
          }
        }
      }
    }
  }
}
