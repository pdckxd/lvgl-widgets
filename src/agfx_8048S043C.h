// #ifdef ARDUINO_GFX

#include <Arduino_GFX_Library.h>
#include <TAMC_GT911.h>
#include <Wire.h>
#define TFT_BL 45

Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
    39 /* DE */, 38 /* VSYNC */, 5 /* HSYNC */, 9 /* PCLK */, 10 /* R0 */,
    11 /* R1 */, 12 /* R2 */, 13 /* R3 */, 14 /* R4 */, 21 /* G0 */, 0 /* G1 */,
    46 /* G2 */, 3 /* G3 */, 8 /* G4 */, 18 /* G5 */, 17 /* B0 */, 16 /* B1 */,
    15 /* B2 */, 7 /* B3 */, 6 /* B4 */, 0 /* hsync_polarity */,
    20 /* hsync_front_porch */, 1 /* hsync_pulse_width */,
    87 /* hsync_back_porch */, 0 /* vsync_polarity */,
    5 /* vsync_front_porch */, 1 /* vsync_pulse_width */,
    31 /* vsync_back_porch */, 0 /* pclk_active_neg */,
    24000000 /* prefer_speed */, 0 /* de_idle_high */, 0 /* pclk_idle_high */
);

Arduino_RGB_Display *gfx =
    new Arduino_RGB_Display(800 /* width */, 480 /* height */, rgbpanel);

#define TOUCH_GT911_SCL 47
#define TOUCH_GT911_SDA 48
#define TOUCH_GT911_INT -1
#define TOUCH_GT911_RST -1
#define TOUCH_GT911_ROTATION ROTATION_NORMAL
#define TOUCH_MAP_X1 480
#define TOUCH_MAP_X2 0
#define TOUCH_MAP_Y1 272
#define TOUCH_MAP_Y2 0

int touch_last_x = 0, touch_last_y = 0;

TAMC_GT911 ts = TAMC_GT911(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT,
                           TOUCH_GT911_RST, max(TOUCH_MAP_X1, TOUCH_MAP_X2),
                           max(TOUCH_MAP_Y1, TOUCH_MAP_Y2));

void touch_init() {
  Wire.begin(TOUCH_GT911_SDA, TOUCH_GT911_SCL);
  ts.begin();
  ts.setRotation(TOUCH_GT911_ROTATION);
}

bool touch_has_signal() { return true; }

bool touch_touched() {
  ts.read();
  if (ts.isTouched) {
#if defined(TOUCH_SWAP_XY)
    touch_last_x =
        map(ts.points[0].y, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, gfx->width() - 1);
    touch_last_y =
        map(ts.points[0].x, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, gfx->height() - 1);
#else
    touch_last_x =
        map(ts.points[0].x, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, gfx->width() - 1);
    touch_last_y =
        map(ts.points[0].y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, gfx->height() - 1);
#endif
    return true;
  } else {
    return false;
  }
}

bool touch_released() { return true; }

// #endif
