#ifdef LOVYAN_GFX
#define LGFX_USE_V1

#include <Arduino.h>
#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>

class LGFX : public lgfx::LGFX_Device{
  lgfx::Bus_RGB     _bus_instance;
  lgfx::Panel_RGB   _panel_instance;
  lgfx::Light_PWM   _light_instance;
  lgfx::Touch_GT911 _touch_instance;

public:LGFX(void){
  auto cfg              = _bus_instance.config();
  cfg.panel             = &_panel_instance;
  cfg.pin_d0            = 8;  // B0
  cfg.pin_d1            = 3;  // B1
  cfg.pin_d2            = 46; // B2
  cfg.pin_d3            = 9;  // B3
  cfg.pin_d4            = 1;  // B4
  cfg.pin_d5            = 5;  // G0
  cfg.pin_d6            = 6;  // G1
  cfg.pin_d7            = 7;  // G2
  cfg.pin_d8            = 15; // G3
  cfg.pin_d9            = 16; // G4
  cfg.pin_d10           = 4;  // G5
  cfg.pin_d11           = 45; // R0
  cfg.pin_d12           = 48; // R1
  cfg.pin_d13           = 47; // R2
  cfg.pin_d14           = 21; // R3
  cfg.pin_d15           = 14; // R4
  cfg.pin_henable       = 40;
  cfg.pin_vsync         = 41;
  cfg.pin_hsync         = 39;
  cfg.pin_pclk          = 42;
  cfg.freq_write        = 16000000;
  cfg.hsync_polarity    = 0;
  cfg.hsync_front_porch = 8;
  cfg.hsync_pulse_width = 4;
  cfg.hsync_back_porch  = 43;
  cfg.vsync_polarity    = 0;
  cfg.vsync_front_porch = 8;
  cfg.vsync_pulse_width = 4;
  cfg.vsync_back_porch  = 12;
  cfg.pclk_idle_high    = 1;
  _bus_instance.config(cfg);
  _panel_instance.setBus(&_bus_instance);

  { auto cfg = _panel_instance.config();
  cfg.memory_width      = MAIN_CONTENT_WIDTH;
  cfg.memory_height     = MAIN_CONTENT_HEIGHT;
  cfg.panel_width       = MAIN_CONTENT_WIDTH;
  cfg.panel_height      = MAIN_CONTENT_HEIGHT;
  cfg.offset_x          = 0;
  cfg.offset_y          = 0;
  _panel_instance.config(cfg);
  }

  { auto cfg = _panel_instance.config_detail();
  cfg.use_psram         = 1;
  _panel_instance.config_detail(cfg);
  }

  { auto cfg = _light_instance.config();
  cfg.pin_bl            = 2;
  cfg.freq              = 44100;
  cfg.pwm_channel       = 7;
  _light_instance.config(cfg);
  }
  _panel_instance.light(&_light_instance);

{
  auto cfg = _touch_instance.config();
  cfg.x_min = 25;
  cfg.x_max = 473;
  cfg.y_min = 14;
  cfg.y_max = 264;
  cfg.pin_int = -1;
  cfg.bus_shared = true;
  cfg.offset_rotation = 0;
  // I2C接続
  cfg.i2c_port = 1;
  cfg.pin_sda = 19;
  cfg.pin_scl = 20;
  cfg.pin_rst = 38;
  cfg.freq = 400000;
  cfg.i2c_addr = 0x5D;  // 0x5D , 0x14
  _touch_instance.config(cfg);
  _panel_instance.setTouch(&_touch_instance);
}
  setPanel(&_panel_instance); // 使用するパネルをセットします。
  }
};
#endif

