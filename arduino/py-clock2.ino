#include <Wire.h>
#include <FastLED.h>
#include <LedControl.h>

#define NUM_LEDS 16
#define LED_DATA_PIN 6
#define BRIGHTNESS 5
CRGB leds[NUM_LEDS];

LedControl lc=LedControl(3,5,4,1);
unsigned long delaytime=500;

int ind1;
int ind2;
int ind3;
int ind4;
int ind5;
int ind6;
int ind7;
int ind8;
String readString, d1, d2, d3, d4, d5, d6, d7, d8;

void setup() {
  // start serial
  Serial.begin(9600);
  Serial.println("<Arduino is ready -->");
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
  // FastLED
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear(true);
}
}
void serial() {
    while (Serial.available()) {
    delay(5);
    if (Serial.available() >0) {
      char c = Serial.read();
      readString += c;
    }
  }
  if (readString.length() >0) {
    Serial.println(readString);
    ind1 = readString.indexOf(',');
    d1 = readString.substring(0, ind1);
    ind2 = readString.indexOf(',', ind1+1 );
    d2 = readString.substring(ind1+1, ind2+1);
    ind3 = readString.indexOf(',', ind2+1 );
    d3 = readString.substring(ind2+1, ind3+1);
    ind4 = readString.indexOf(',', ind3+1 );
    d4 = readString.substring(ind3+1, ind4+1);
    ind5 = readString.indexOf(',', ind4+1 );
    d5 = readString.substring(ind4+1, ind5+1);
    ind6 = readString.indexOf(',', ind5+1 );
    d6 = readString.substring(ind5+1, ind6+1);
    ind7 = readString.indexOf(',', ind6+1 );
    d7 = readString.substring(ind6+1, ind7+1);
    ind8 = readString.indexOf(',', ind7+1 );
    d8 = readString.substring(ind7+1);

    int n1;
    char carray1[6];
    d1.toCharArray(carray1, sizeof(carray1));
    n1 = atoi(carray1);

    int n2;
    char carray2[6];
    d2.toCharArray(carray2, sizeof(carray2));
    n2 = atoi(carray2);

    int n3;
    char carray3[6];
    d3.toCharArray(carray3, sizeof(carray3));
    n3 = atoi(carray3);

    int n4;
    char carray4[6];
    d4.toCharArray(carray4, sizeof(carray4));
    n4 = atoi(carray4);

    int n5;
    char carray5[6];
    d5.toCharArray(carray5, sizeof(carray5));
    n5 = atoi(carray3);

    int n6;
    char carray6[6];
    d6.toCharArray(carray6, sizeof(carray6));
    n6 = atoi(carray6);

    int n7;
    char carray7[6];
    d7.toCharArray(carray7, sizeof(carray7));
    n7 = atoi(carray7);

    int n8;
    char carray8[6];
    d8.toCharArray(carray8, sizeof(carray8));
    n8 = atoi(carray8);

    lc.setDigit(0,7,(byte)n1,false);
    lc.setDigit(0,6,(byte)n2,false);
    lc.setDigit(0,5,(byte)n3,false);
    lc.setDigit(0,4,(byte)n4,false);
    lc.setDigit(0,3,(byte)n5,false);
    lc.setDigit(0,2,(byte)n6,false);
    lc.setDigit(0,1,(byte)n7,false);
    lc.setDigit(0,0,(byte)n8,false);
  readString="";
}

void loop() {
  serial();
}