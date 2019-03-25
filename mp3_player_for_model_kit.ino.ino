#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include "DFRobotDFPlayerMini.h"

#define INPUTPIN A0
#define BRIGHTNESS 500 // 明るい/暗いの閾値 ( 500>入力値:暗い 500<=入力値:明るい)

int playFlag = 0;     //再生中フラグ
int inPutVal;         //CDSセルからの入力値
int playCount = 0;    //明るさフラグ
int numfile = 0;

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void setup () {
  mySoftwareSerial.begin(9600);
  Serial.begin (9600);

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card or USB drive!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }  
  delay(1);                        // delay 1ms to set volume
  myDFPlayer.volume(20);           // value 0~30
  numfile = myDFPlayer.readFileCounts(DFPLAYER_DEVICE_SD);
}

void loop () {
  inPutVal = analogRead(INPUTPIN);
  Serial.println(inPutVal);

  if (inPutVal > BRIGHTNESS ) {   // 暗いとき
    if (playFlag == 0) {
      if (playCount == 0) {       //周辺が暗いままなら再生しない
        myDFPlayer.play(random(numfile)+1);       //再生
      }
      playFlag = 1;               //再生中フラグON
      playCount = 1;              //再生回数をカウントアップ
      delay(500);
    }
    else {
      if (playCount == 0) {
        //mp3_stop();             //再生ストップ
        myDFPlayer.stop();
      }
      playFlag = 0;             //再生中フラグOFF
      delay(500);
    }
  }
  else {                        //明るいとき
    playCount = 0;              //明るさフラグをOFFする
  }
  delay (1000);
}
