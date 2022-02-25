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
String readString, dial1, dial2, dial3;

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

void setLED() {
  Serial.println("setLED");
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(delaytime);
  leds[0] = CRGB::Blue;
  FastLED.show();
}

void scrollDigits() {
  for(int i=0;i<9;i++) {
    lc.setDigit(0,7,i,false);
    lc.setDigit(0,6,i+1,false);
    lc.setDigit(0,5,i+2,false);
    lc.setDigit(0,4,i+3,false);
    lc.setDigit(0,3,i+4,false);
    lc.setDigit(0,2,i+5,false);
    lc.setDigit(0,1,i+6,false);
    lc.setDigit(0,0,i+7,false);
    delay(delaytime);
  }
  lc.clearDisplay(0);
  delay(delaytime);
}
void splitTime (int v) {
  int ones;
  int tens;

  ones=v%10;
  v=v/10;
  tens=v%10;
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
    dial1 = readString.substring(0, ind1);
    ind2 = readString.indexOf(',', ind1+1 );
    dial2 = readString.substring(ind1+1, ind2+1);
    ind3 = readString.indexOf(',', ind2+1 );
    dial3 = readString.substring(ind2+1, ind3+1);

    int n1;
    char carray1[6];
    dial1.toCharArray(carray1, sizeof(carray1));
    n1 = atoi(carray1);

    int n2;
    char carray2[6];
    dial2.toCharArray(carray2, sizeof(carray2));
    n2 = atoi(carray2);

    int n3;
    char carray3[6];
    dial3.toCharArray(carray3, sizeof(carray3));
    n3 = atoi(carray3);

    if (n3 > 10) {
    leds[0] = CRGB::Red;
    leds[1] = CRGB::Red;
    FastLED.show();
    }
    else {
    leds[1] = CRGB::Blue;
    leds[0] = CRGB::Blue;
    FastLED.show();
    }

    int H_ones;
    int H_tens;
    int M_ones;
    int M_tens;
    int S_ones;
    int S_tens;

    S_ones=n3%10;
    n3=n3/10;
    S_tens=n3%10;

    M_ones=n2%10;
    n2=n2/10;
    M_tens=n2%10;

    H_ones=n1%10;
    n1=n1/10;
    H_tens=n1%10;

    lc.setDigit(0,6,(byte)H_tens,false);
    lc.setDigit(0,5,(byte)H_ones,true);
    lc.setDigit(0,4,(byte)M_tens,false);
    lc.setDigit(0,3,(byte)M_ones,true);
    lc.setDigit(0,2,(byte)S_tens,false);
    lc.setDigit(0,1,(byte)S_ones,false);
    //lc.setDigit(0,6,n2,false);
  readString="";
}
}

void loop() {
  //Serial.println("Loop start");
  //setLED();
  //splitTime()
  serial();
  //scrollDigits();
  //Serial.println("Loop end");
}

// DIN 3
// CS 4
// CLK 5