#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include "hetang00.c"
#include "hetang01.c"
#include "hetang02.c"
#include "hetang03.c"
#include "hetang04.c"
#include "hetang05.c"
#include "hetang06.c"
#include "hetang07.c"
#include "hetang08.c"
#include "hetang09.c"
#include "hetang10.c"
#include "hetang11.c"
#include "hetang12.c"
#include "hetang13.c"
#include "hetang14.c"
#include "hetang15.c"
#include "hetang16.c"
#include "hetang17.c"
#include "hetang18.c"

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

void setup(void)
{
  tft.init();
  tft.setRotation(4);

  tft.fillScreen(TFT_BLACK);

  // Set "cursor" at top left corner of display (0,0) and select font 4
  tft.setCursor(0, 0, 4);

  tft.invertDisplay(true);
  tft.setSwapBytes(true);
  tft.pushImage(0, 0, 240, 240, hetang00);
}

void loop()
{
  tft.pushImage(0, 0, 240, 240, hetang00);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang01);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang02);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang03);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang04);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang05);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang06);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang07);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang08);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang09);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang10);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang11);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang12);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang13);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang14);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang15);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang16);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang17);
  delay(100);
  tft.pushImage(0, 0, 240, 240, hetang18);
  delay(100);
}
