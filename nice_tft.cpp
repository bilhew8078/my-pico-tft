#include <stdio.h>

#include "TFT_eSPI.h"
#include "pico/stdlib.h"

TFT_eSPI tft = TFT_eSPI();

int rgb565(unsigned char r, unsigned char g, unsigned char b) {
  unsigned char red = r >> 3;
  unsigned char green = g >> 2;
  unsigned char blue = b >> 3;

  int result = (red << (5 + 6)) | (green << 5) | blue;

  return result;
}

int main() {
  stdio_init_all();
  
  tft.init();
  tft.setRotation(1);
  tft.invertDisplay(true);
  tft.fillScreen(TFT_BLUE);

  long previousMillis = 0;
  long lastFramerate = 0;
  long currentFramerate = 0;
  uint16_t seconds = 0;
  uint16_t fps = 0;
  uint8_t shapeColor = 0;
  uint8_t dir = 1;
  tft.setTextSize(1);

  while (1) {
    unsigned long currentMillis = to_ms_since_boot(get_absolute_time());

    if (currentMillis - previousMillis >= 1000) // every second
    {
      fps = currentFramerate - lastFramerate;
      lastFramerate = currentFramerate;
      previousMillis = currentMillis;
      seconds++;
    }
    if ((currentMillis - previousMillis) % 200 >= 100) {
      shapeColor += dir;
      if (shapeColor % 0xff == 0)
        dir = -dir;
    }
    currentFramerate++;

    tft.setCursor(5, 2, 1);
    tft.print("Secs :");
    tft.setCursor(50, 2);
    tft.print(seconds);

    tft.setCursor(5, 12, 1);
    tft.print("FPS  :");
    tft.setCursor(50, 12);
    tft.print(fps);

    // print some graphics
    // tft.drawCircle(0, 0, 10, shapeColor);
    // tft.drawRect(0, 0, 160, 80, shapeColor);
    tft.fillRectHGradient(3, 22, 150, 55,
                          rgb565(0xff - shapeColor, shapeColor, 0),
                          rgb565(shapeColor, 0xff - shapeColor, 0));
    // tft.drawPixel(0, 0, TFT_RED);
    // tft.fillScreen(TFT_BLACK);
  }

  return 0;
}
