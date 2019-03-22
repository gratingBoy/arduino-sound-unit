#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include "DFRobotDFPlayerMini.h"

#define INPUTPIN A0
#define BRIGHTNESS 500 // 明るい/暗いの閾値 ( 500>入力値:暗い 500<=入力値:明るい)

int playFlag = 0;     //再生中フラグ
int inPutVal;         //CDSセルからの入力値
int playCount = 0;    //明るさフラグ

void setup () {
  Serial.begin (9600);
  mp3_set_serial (Serial);      //set Serial for DFPlayer-mini mp3 module
  delay(1);                      // delay 1ms to set volume
  mp3_set_volume (20);           // value 0~30
}

void loop () {
  inPutVal = analogRead(INPUTPIN);
  Serial.println(inPutVal);

  if (inPutVal > BRIGHTNESS ) {   // 暗いとき
    if (playFlag == 0) {
      if (playCount == 0) {       //周辺が暗いままなら再生しない
        mp3_random_play ();       //再生
      }
      playFlag = 1;               //再生中フラグON
      playCount = 1;              //再生回数をカウントアップ
      delay(500);
    }
    else {
      if (playCount == 0) {
        mp3_stop();             //再生ストップ
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
