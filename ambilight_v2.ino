/*
* Atmolight for IKEA Dioder
*
* Author: Hugo Chinchilla <hugo@bulma.net>
* Web:    http://www.hugochinchilla.net
* 
* Gamma table and Serial parsing from FUN3MD code.
* http://fun3md.blogspot.com.es/
*/

const int colorR = 9;
const int colorG = 11;
const int colorB = 10;
const byte gammatable[] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,
  3,4,4,4,4,5,5,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,
  10,10,10,11,11,12,12,12,13,13,14,14,14,15,15,16,
  16,17,17,18,18,19,19,20,20,21,22,22,23,23,24,25,
  25,26,26,27,28,28,29,30,31,31,32,33,33,34,35,36,
  36,37,38,39,39,40,41,42,43,44,45,45,46,47,48,49,
  50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,
  66,68,69,70,71,72,73,75,76,77,78,79,81,82,83,85,
  86,87,88,90,91,93,94,95,97,98,99,101,102,104,105,
  107,108,110,111,113,114,116,117,119,121,122,124,
  125,127,129,130,132,134,135,137,139,141,142,144,
  146,148,150,151,153,155,157,159,161,162,164,166,
  168,170,172,174,176,178,180,182,184,186,189,191,
  193,195,197,199,201,203,206,208,210,212,215,217,
  219,221,224,226,228,231,233,235,238,240,243,245,
  247,250,252,255
};

int incoming_atmo[16];
int buffer = 0;
int r,g,b = 0;

void setup() {
  Serial.begin(38400);
  setColor(r,g,b);
}

void loop() {
  if (Serial.available()) {
    buffer = Serial.read();
    if (buffer == 0xff) {
      while( Serial.available() == 0) { /* wait */ }
      buffer = Serial.read();
      if (buffer == 0x00) {
        while ( Serial.available()==0 ) { /* wait */ }
        buffer = Serial.read();
        if ( buffer == 0x00 ) {
          for (int i=0; i<16; i++) {
            while( Serial.available() == 0) { /* wait */ }
            incoming_atmo[i] = Serial.read();
          }

          setColor(incoming_atmo[1], incoming_atmo[2], incoming_atmo[3]);
        }
      }
    }
  }
}

void setColor(int r, int g, int b) {
  analogWrite(colorR, gammatable[r]);
  analogWrite(colorG, gammatable[g]);
  analogWrite(colorB, gammatable[b]);
}
