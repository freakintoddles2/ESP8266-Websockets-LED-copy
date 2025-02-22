uint8_t idex = 0;
uint8_t ihue = 0;
uint8_t isat = 255;
uint8_t ibright = 0;
uint16_t TOP_INDEX = uint8_t(LED_COUNT / 2); // center of the stip
uint8_t EVENODD = LED_COUNT % 2;
uint8_t bouncedirection = 0;
int ledsX[LED_COUNT][3]; // array for storing random pixel values

void updateColor (uint8_t r,uint8_t g,uint8_t b) {
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    leds[i].setRGB(r,g,b);
  }
}

void updatePixel (int i, uint8_t r, uint8_t g, uint8_t b) {
  leds[i].setRGB(r,g,b);
}

void setPixel (int Pixel, byte red, byte green, byte blue) {
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
}

void setAll (byte red, byte green, byte blue) {
  for (int i = 0; i < LED_COUNT; i++) {
    setPixel(i, red, green, blue);
  }
  FastLED.show();
}
void fadeall( ) {
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i].nscale8(250); 
  } 
}

// -------------------------------- RAINBOW LOOP FADE -------------------------------------
// smooth color change
void rainbowFade() { 
  ihue++;
  if (ihue > 255){
    ihue = 0;
  }
  for (int idex = 0 ; idex < LED_COUNT; idex++) {
    leds[idex] = CHSV(ihue, isat, 255);
  }
  LEDS.show();
  delay(_delay);
}

// -------------------------------- RAINBOW LOOP -------------------------------------
// rotating rainbow
void rainbowLoop() { 
  idex++;
  ihue = ihue + _step;
  if (idex >= LED_COUNT) {
    idex = 0;
  }
  if (ihue > 255){
    ihue = 0;
  }
  leds[idex] = CHSV(ihue, isat, 255);
  LEDS.show();
  delay(_delay);
}

//------------------------------- SNOW SPARKLE ---------------------------------------
void snowSparkle() {
  uint8_t red = 0x10;
  uint8_t green = 0x10;
  uint8_t blue = 0x10;
  uint8_t sparkleDelay = 40;
  uint8_t speedDelay = random(100, 1000);
  updateColor(red, green, blue);

  int pixel = random(LED_COUNT);
  setPixel(pixel, 0xff, 0xff, 0xff);
  FastLED.show();
  delay(sparkleDelay);
  setPixel(pixel, red, green, blue);
  FastLED.show();
  delay(speedDelay);
}

//------------------------------- RADIATION ---------------------------------------
float rcount = 0.0;
void radiation() {
  updateColor(0,0,0);
  int N3  = int(LED_COUNT / 3);
  int N6  = int(LED_COUNT / 6);
  int N12 = int(LED_COUNT / 12);
  for (int i = 0; i < N6; i++) {
    rcount = rcount + .02;
    if (rcount > 3.14) {
      rcount = 0.0;
    }
    ibright = int(sin(rcount) * 255);
    int j0 = (i + LED_COUNT - N12) % LED_COUNT;
    int j1 = (j0 + N3) % LED_COUNT;
    int j2 = (j1 + N3) % LED_COUNT;
    leds[j0] = CHSV(_hue, _sat, ibright);
    leds[j1] = CHSV(_hue, _sat, ibright);
    leds[j2] = CHSV(_hue, _sat, ibright);
  }
  LEDS.show();
  delay(_delay);
}

// -------------------------------- POP GORIZONTAL -------------------------------------
// pop from left to right up the ring
void popHorizontal() {
  int ix;
  if (bouncedirection == 0) {
    bouncedirection = 1;
    ix = idex;
  }
  else if (bouncedirection == 1) {
    bouncedirection = 0;
    ix = horizontal_index(idex);
    idex++;
    if (idex > TOP_INDEX) {
      idex = 0;
    }
  }
  for (int i = 0; i < LED_COUNT; i++) {
    if (i == ix) {
      leds[i] = CHSV(_hue, _sat, 255);
    }
    else {
      leds[i].r = 0; leds[i].g = 0; leds[i].b = 0;
    }
  }
  LEDS.show();
  delay(_delay);
}

// -------------------------------- PACMAN -------------------------------------
// pacman chomping effect
int pcounter = 0;
void pacman() {
  int s = int(LED_COUNT / 4);
  pcounter++;
  if (pcounter > 5) {
    pcounter = 0;
  }
  if (pcounter == 0) {
    for (int i = 0 ; i < LED_COUNT; i++) {
      updatePixel(i, 255, 255, 0);
    }
  }
  if (pcounter == 1 || pcounter == 5) {
    for (int i = 0 ; i < LED_COUNT; i++) {
      updatePixel(i, 255, 255, 0);
    }
    leds[s].r = 0; leds[s].g = 0; leds[s].b = 0;
  }
  if (pcounter == 2 || pcounter == 4) {
    for (int i = 0 ; i < LED_COUNT; i++) {
      updatePixel(i, 255, 255, 0);
    }
    leds[s - 1].r = 0; leds[s - 1].g = 0; leds[s - 1].b = 0;
    leds[s].r = 0; leds[s].g = 0; leds[s].b = 0;
    leds[s + 1].r = 0; leds[s + 1].g = 0; leds[s + 1].b = 0;
  }
  if (pcounter == 3) {
    for (int i = 0 ; i < LED_COUNT; i++) {
      updatePixel(i, 255, 255, 0);
    }
    leds[s - 2].r = 0; leds[s - 2].g = 0; leds[s - 2].b = 0;
    leds[s - 1].r = 0; leds[s - 1].g = 0; leds[s - 1].b = 0;
    leds[s].r = 0; leds[s].g = 0; leds[s].b = 0;
    leds[s + 1].r = 0; leds[s + 1].g = 0; leds[s + 1].b = 0;
    leds[s + 2].r = 0; leds[s + 2].g = 0; leds[s + 2].b = 0;
  }
  LEDS.show();
  delay(_delay);
}

// -------------------------------- RANDOM BURST -------------------------------------
// random color change
void randomBurst() {
  idex = random(0, LED_COUNT);
  ihue = random(0, 255);
  leds[idex] = CHSV(ihue, isat, 255);
  LEDS.show();
  delay(_delay);
}

// -------------------------------- COLOR BOUNCE -------------------------------------
// running pixel
void colorBounce() {
  if (bouncedirection == 0) {
    idex = idex + 1;
    if (idex == LED_COUNT) {
      bouncedirection = 1;
      idex = idex - 1;
    }
  }
  if (bouncedirection == 1) {
    idex = idex - 1;
    if (idex == 0) {
      bouncedirection = 0;
    }
  }
  for (int i = 0; i < LED_COUNT; i++) {
    if (i == idex) {
      leds[i] = CHSV(_hue, isat, 255);
    }
    else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  LEDS.show();
  delay(_delay);
}

// -------------------------------- COLOR BOUNCE FADE -------------------------------------
// running train of pixels
void colorBounceFade() {
  if (bouncedirection == 0) {
    idex = idex + 1;
    if (idex == LED_COUNT) {
      bouncedirection = 1;
      idex = idex - 1;
    }
  }
  if (bouncedirection == 1) {
    idex = idex - 1;
    if (idex == 0) {
      bouncedirection = 0;
    }
  }
  int iL1 = adjacent_cw(idex);
  int iL2 = adjacent_cw(iL1);
  int iL3 = adjacent_cw(iL2);
  int iR1 = adjacent_ccw(idex);
  int iR2 = adjacent_ccw(iR1);
  int iR3 = adjacent_ccw(iR2);

  for (int i = 0; i < LED_COUNT; i++ ) {
    if (i == idex) {
      leds[i] = CHSV(_hue, isat, 255);
    }
    else if (i == iL1) {
      leds[i] = CHSV(_hue, isat, 150);
    }
    else if (i == iL2) {
      leds[i] = CHSV(_hue, isat, 80);
    }
    else if (i == iL3) {
      leds[i] = CHSV(_hue, isat, 20);
    }
    else if (i == iR1) {
      leds[i] = CHSV(_hue, isat, 150);
    }
    else if (i == iR2) {
      leds[i] = CHSV(_hue, isat, 80);
    }
    else if (i == iR3) {
      leds[i] = CHSV(_hue, isat, 20);
    }
    else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  LEDS.show();
  delay(_delay);
}

// -------------------------------- RED BLUE BOUNCE -------------------------------------
// rotation of red and blue bounce
void redBlueBounce() {
  idex++;
  if (idex >= LED_COUNT) {
    idex = 0;
  }
  int idexR = idex;
  int idexB = antipodal_index(idexR);
  int thathue =(_hue + 160) % 255;

  for (int i = 0; i < LED_COUNT; i++) {
    if (i == idexR) {
      leds[i] = CHSV(_hue, isat, 255);
    }
    else if (i == idexB) {
      leds[i] = CHSV(thathue, isat, 255);
    }
    else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  LEDS.show();
  delay(_delay);
}

int antipodal_index(int i) {
  int iN = i + TOP_INDEX;
  if (i >= TOP_INDEX) {
    iN =( i + TOP_INDEX ) % LED_COUNT;
  }
  return iN;
}

// -------------------------------- ROTATING RED/BLUE -------------------------------------
// red/blue rotation
void rotatingRedBlue() {
  idex++;
  if (idex >= LED_COUNT) {
    idex = 0;
  }
  int idexR = idex;
  int idexB = antipodal_index(idexR);
  int thathue =(_hue + 160) % 255;
  leds[idexR] = CHSV(_hue, isat, 255);
  leds[idexB] = CHSV(thathue, isat, 255);
  LEDS.show();
  delay(_delay);
}

// -------------------------------- FLICKER -------------------------------------
// random strobe light
void flicker() {
  int random_bright = random(0, 255);
  int random_delay = random(10, 100);
  int random_bool = random(0, random_bright);
  if (random_bool < 10) {
    for (int i = 0 ; i < LED_COUNT; i++) {
      leds[i] = CHSV(160, 50, random_bright);
    }
    LEDS.show();
    delay(random_delay);
  }
}

// -------------------------------- FADE VERTICAL -------------------------------------
// smooth brightness change
void fadeVertical() {
  idex++;
  if (idex > TOP_INDEX) {
    idex = 0;
  }
  int idexA = idex;
  int idexB = horizontal_index(idexA);
  ibright = ibright + 10;
  if (ibright > 255) {
    ibright = 0;
  }
  leds[idexA] = CHSV(_hue, isat, ibright);
  leds[idexB] = CHSV(_hue, isat, ibright);
  LEDS.show();
  delay(_delay);
}

int horizontal_index(int i) {
  if(i == 0) {
    return 0;
  }
  if (i == TOP_INDEX && EVENODD == 1) {
    return TOP_INDEX + 1;
  }
  if (i == TOP_INDEX && EVENODD == 0) {
    return TOP_INDEX;
  }
  return LED_COUNT - i;
}

void random_red() {
  int temprand;
  for (int i = 0; i < LED_COUNT; i++) {
    temprand = random(0, 100);
    if (temprand > 50) {
      leds[i].r = 255;
    }
    if (temprand <= 50) {
      leds[i].r = 0;
    }
    leds[i].b = 0; leds[i].g = 0;
  }
  LEDS.show();
}

// -------------------------------- RULE30 -------------------------------------
// the madness of red LEDs
void rule30() {
  if (bouncedirection == 0) {
    random_red();
    bouncedirection = 1;
  }
  copy_led_array();
  int iCW;
  int iCCW;
  int y = 100;
  for (int i = 0; i < LED_COUNT; i++) {
    iCW = adjacent_cw(i);
    iCCW = adjacent_ccw(i);
    if (ledsX[iCCW][0] > y && ledsX[i][0] > y && ledsX[iCW][0] > y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] > y && ledsX[iCW][0] <= y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] <= y && ledsX[iCW][0] > y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] <= y && ledsX[iCW][0] <= y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] > y && ledsX[iCW][0] > y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] > y && ledsX[iCW][0] <= y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] <= y && ledsX[iCW][0] > y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] <= y && ledsX[iCW][0] <= y) {
      leds[i].r = 0;
    }
  }
  LEDS.show();
  delay(_delay);
}

int adjacent_cw(int i) {
  int r;
  if (i < LED_COUNT - 1) {
    r = i + 1;
  } else {
    r = 0;
  }
  return r;
}

int adjacent_ccw(int i) {
  int r;
  if (i > 0) {
    r = i - 1;
  }
  else{
    r = LED_COUNT - 1;
  }
  return r;
}

// -------------------------------- RANDOM MARCH -------------------------------------
// the madness of random LEDs
void randomMarch() {
  copy_led_array();
  int iCCW;
  leds[0] = CHSV(random(0, 255), 255, 255);
  for (int idex = 1; idex < LED_COUNT ; idex++) {
    iCCW = adjacent_ccw(idex);
    leds[idex].r = ledsX[iCCW][0];
    leds[idex].g = ledsX[iCCW][1];
    leds[idex].b = ledsX[iCCW][2];
  }
  LEDS.show();
  delay(_delay);
}
void copy_led_array() {
  for(int i = 0; i < LED_COUNT; i++ ) {
    ledsX[i][0] = leds[i].r;
    ledsX[i][1] = leds[i].g;
    ledsX[i][2] = leds[i].b;
  }
}

// -------------------------------- RWB MARCH -------------------------------------
// white blue red run in a circle
void rwbMarch() { 
  copy_led_array();
  int iCCW;
  idex++;
  if (idex > 2) {
    idex = 0;
  }
  switch(idex) {
    case 0:
      leds[0].r = 255;
      leds[0].g = 0;
      leds[0].b = 0;
      break;
    case 1:
      leds[0].r = 255;
      leds[0].g = 255;
      leds[0].b = 255;
      break;
    case 2:
      leds[0].r = 0;
      leds[0].g = 0;
      leds[0].b = 255;
      break;
  }
  for (int i = 1; i < LED_COUNT; i++) {
    iCCW = adjacent_ccw(i);
    leds[i].r = ledsX[iCCW][0];
    leds[i].g = ledsX[iCCW][1];
    leds[i].b = ledsX[iCCW][2];
  }
  LEDS.show();
  delay(_delay);
}

// -------------------------------- FLAME -------------------------------------
// flame effect
void flame() {
  int idelay = random(0, 35);
  float hmin = 0.1; float hmax = 45.0;
  float hdif = hmax - hmin;
  int randtemp = random(0, 3);
  float hinc =(hdif / float(TOP_INDEX)) + randtemp;
  int ihue = hmin;
  for (int i = 0; i <= TOP_INDEX; i++) {
    ihue = ihue + hinc;
    leds[i] = CHSV(ihue, isat, 255);
    int ih = horizontal_index(i);
    leds[ih] = CHSV(ihue, isat, 255);
    leds[TOP_INDEX].r = 255; leds[TOP_INDEX].g = 255; leds[TOP_INDEX].b = 255;
    LEDS.show();
    delay(idelay);
  }
}

// -------------------------------- RANDOM COLOR POP -------------------------------------
// the madness of random flashes
void randomColorPop(){
  idex = random(0, LED_COUNT);
  ihue = random(0, 255);
  updateColor(0, 0, 0);
  leds[idex] = CHSV(ihue, isat, 255);
  LEDS.show();
  delay(_delay);
}
// -------------------------------- RAINBOW VERTICAL -------------------------------------
void rainbowVertical() { 
  idex++;
  if (idex > TOP_INDEX) {
    idex = 0;
  }
  ihue = ihue + _step;
  if (ihue > 255) {
    ihue = 0;
  }
  int idexA = idex;
  int idexB = horizontal_index(idexA);
  leds[idexA] = CHSV(ihue, isat, 255);
  leds[idexB] = CHSV(ihue, isat, 255);
  LEDS.show();
  delay(_delay);
}

// -------------------------------- POLICE BLINKER -------------------------------------
void policeBlinker() {
  int _hue = 0;
  int thathue =(_hue + 160) % 255;
  for (int x = 0 ; x < 5; x++) {
    for (int i = 0 ; i < TOP_INDEX; i++) {
      leds[i] = CHSV(_hue, isat, 255);
    }
    LEDS.show(); delay(_delay);
    updateColor(0, 0, 0);
    LEDS.show(); delay(_delay);
  }
  for (int x = 0 ; x < 5; x++) {
    for (int i = TOP_INDEX ; i < LED_COUNT; i++) {
      leds[i] = CHSV(thathue, isat, 255);
    }
    LEDS.show(); delay(_delay);
    updateColor(0, 0, 0);
    LEDS.show(); delay(_delay);
  }
}

// -------------------------------- RGB PROPELLER -------------------------------------
void rgbPropeller() {
  idex++;
  int ghue =(_hue + 80) % 255;
  int bhue =(_hue + 160) % 255;
  int N3  = int(LED_COUNT / 3);
  int N6  = int(LED_COUNT / 6);
  int N12 = int(LED_COUNT / 12);

  for (int i = 0; i < N3; i++) {
    int j0 =(idex + i + LED_COUNT - N12) % LED_COUNT;
    int j1 =(j0 + N3) % LED_COUNT;
    int j2 =(j1 + N3) % LED_COUNT;
    leds[j0] = CHSV(_hue, isat, 255);
    leds[j1] = CHSV(ghue, isat, 255);
    leds[j2] = CHSV(bhue, isat, 255);
  }
  LEDS.show();
  delay(_delay);
}

// -------------------------------- KITT -------------------------------------
// random flashes of red
void kitt() {
  int rand = random(0, TOP_INDEX);
  for (int i = 0; i < rand; i++) {
    leds[TOP_INDEX + i] = CHSV(_hue, isat, 255);
    leds[TOP_INDEX - i] = CHSV(_hue, isat, 255);
    LEDS.show();
    delay(_delay / rand);
  }
  for (int i = rand; i > 0; i--) {
    leds[TOP_INDEX + i] = CHSV(_hue, isat, 0);
    leds[TOP_INDEX - i] = CHSV(_hue, isat, 0);
    LEDS.show();
    delay(_delay / rand);
  }
}

// -------------------------------- MATRIX -------------------------------------
// the greens run around randomly
void matrix() {
  int rand = random(0, 100);
  if (rand > 90) {
    leds[0] = CHSV(_hue, isat, 255);
  }
  else {
    leds[0] = CHSV(_hue, isat, 0);
  }
  copy_led_array();
  for (int i = 1; i < LED_COUNT; i++) {
    leds[i].r = ledsX[i - 1][0];
    leds[i].g = ledsX[i - 1][1];
    leds[i].b = ledsX[i - 1][2];
  }
  LEDS.show();
  delay(_delay);
}

// -------------------------------- RAINBOW LOOP FADE -------------------------------------
// smooth rotating rainbow
void rainbowLoopFade() {
  ihue -= 1;
  fill_rainbow(leds, LED_COUNT, ihue);
  LEDS.show();
  delay(_delay);
}



// -------------------------------- FIRE -------------------------------------
void fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[LED_COUNT];
  int cooldown;

  for (int i = 0; i < LED_COUNT; i++) {
    cooldown = random(0,((Cooling * 10) / LED_COUNT) + 2);

    if (cooldown > heat[i]){
      heat[i] = 0;
    } else{
      heat[i] = heat[i] - cooldown;
    }
  }

  for (int k = LED_COUNT - 1; k >= 2; k--) {
    heat[k] =(heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  if ( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160, 255);
  }

  for ( int j = 0; j < LED_COUNT; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  FastLED.show();
  delay(SpeedDelay);
}

void setPixelHeatColor(int Pixel, byte temperature) {
  byte t192 = round((temperature / 255.0) * 191);
  byte heatramp = t192 & 0x3F;
  heatramp <<= 2;

  if ( t192 > 0x80) {
    setPixel(Pixel, 255, 255, heatramp);
  } else if ( t192 > 0x40 ) {
    setPixel(Pixel, 255, heatramp, 0);
  } else {
    setPixel(Pixel, heatramp, 0, 0);
  }
}

void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i =((LED_COUNT - EyeSize) / 2); i >= 0; i--) {
    setAll(0, 0, 0);

    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);

    setPixel(LED_COUNT - i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(LED_COUNT - i - j, red, green, blue);
    }
    setPixel(LED_COUNT - i - EyeSize - 1, red / 10, green / 10, blue / 10);

    FastLED.show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = 0; i <=((LED_COUNT - EyeSize) / 2); i++) {
    setAll(0, 0, 0);

    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);

    setPixel(LED_COUNT - i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(LED_COUNT - i - j, red, green, blue);
    }
    setPixel(LED_COUNT - i - EyeSize - 1, red / 10, green / 10, blue / 10);

    FastLED.show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = 0; i < LED_COUNT - EyeSize - 2; i++) {
    setAll(0, 0, 0);
    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
    FastLED.show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

// -------------------------------- SPARKLE -------------------------------------
// random flashes of white
void sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(LED_COUNT);
  setPixel(Pixel, red, green, blue);
  FastLED.show();
  delay(SpeedDelay);
  setPixel(Pixel, 0, 0, 0);
}

// -------------------------------- THEATER CHASE -------------------------------------
// running every 3 pixels
void theaterChase(byte red, byte green, byte blue, int SpeedDelay) {
  for (int j = 0; j < 10; j++) {
    for (int q = 0; q < 3; q++) {
      for(int i = 0; i < LED_COUNT; i = i + 3) {
        setPixel(i + q, red, green, blue);
      }
      FastLED.show();
      delay(SpeedDelay);
      for (int i = 0; i < LED_COUNT; i = i + 3) {
        setPixel(i + q, 0, 0, 0);
      }
    }
  }
}

// -------------------------------- STROBE -------------------------------------
// stroboscopic effect
void strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause) {
  for (int j = 0; j < StrobeCount; j++) {
    setAll(red, green, blue);
    FastLED.show();
    delay(FlashDelay);
    setAll(0, 0, 0);
    FastLED.show();
    delay(FlashDelay);
  }

  delay(EndPause);
}

// -------------------------------- BLUE FIRE -------------------------------------
// blue line fire
void blueFire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[LED_COUNT];
  int cooldown;

  for (int i = 0; i < LED_COUNT; i++) {
    cooldown = random(0,((Cooling * 10) / LED_COUNT) + 2);

    if (cooldown > heat[i]) {
      heat[i] = 0;
    } else {
      heat[i] = heat[i] - cooldown;
    }
  }
  for (int k = LED_COUNT - 1; k >= 2; k--) {
    heat[k] =(heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
  if(random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160, 255);
  }
  for(int j = 0; j < LED_COUNT; j++) {
    setPixelHeatColorBlue(j, heat[j] );
  }
  FastLED.show();
  delay(SpeedDelay);
}

void setPixelHeatColorBlue(int Pixel, byte temperature) {
  byte t192 = round((temperature / 255.0) * 191);
  byte heatramp = t192 & 0x03;
  heatramp <<= 2;

  if ( t192 > 0x03) {
    setPixel(Pixel, heatramp,255, 255);
  } else if( t192 > 0x40 ) {
    setPixel(Pixel, 255, heatramp, 0);
  } else {
    setPixel(Pixel, 0, 0, heatramp);
  }
}

// -------------------------------- FADE TO CENTER -------------------------------------
// blurring colors
void fadeToCenter() {
 static uint8_t hue;
  for (int i = 0; i < LED_COUNT/2; i++) {   
    leds.fadeToBlackBy(40);
    leds[i] = CHSV(hue++,255,255);
    leds(LED_COUNT/2,LED_COUNT-1) = leds(LED_COUNT/2 - 1 ,0);
    FastLED.delay(33);
  }  
}

// -------------------------------- RUNNER CHAMELEON -------------------------------------
// a steam train running in a circle
void runnerChameleon() {
    static uint8_t hue = 0;
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show(); 
     leds[i] = CRGB::Black;
//    fadeall();
    delay(10);
  }
}

// -------------------------------- BLENDE -------------------------------------
void blende() {
    static uint8_t hue = 0;
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show(); 
//     leds[i] = CRGB::Black;
    fadeall();
    delay(10);
  }

  for (int i = (LED_COUNT)-1; i >= 0; i--) {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
//     leds[i] = CRGB::Black;
    fadeall();
    delay(10);
  }
}

// -------------------------------- BLENDE 2 -------------------------------------
void blende_2() {
    static uint8_t hue = 0;
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show(); 
    leds[i] = CRGB::Black;
    fadeall();
    delay(10);
  }

  for (int i = (LED_COUNT)-1; i >= 0; i--) {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
//     leds[i] = CRGB::Black;
    fadeall();
    delay(10);
  }
}
