#include <stdint.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/display.h>
#include <zephyr/logging/log.h>

#include "logo_image.h"


#define DISPLAY_BUFFER_PITCH 128

LOG_MODULE_REGISTER(display);


static const struct device *display = DEVICE_DT_GET(DT_NODELABEL(ssd1306));

void main(void) {
  if (display == NULL) {
    LOG_ERR("[!] Device pointer is NULL.");
    return;
  }

  if (!device_is_ready(display)) {
    LOG_ERR("[!] Display is not ready.");
    return;
  } 

  struct display_capabilities capabilities;
  display_get_capabilities(display, &capabilities);

  const uint16_t x_res = capabilities.x_resolution;
  const uint16_t y_res = capabilities.y_resolution;

  LOG_INF("X_resolution: %d", capabilities.x_resolution);
  LOG_INF("Y_resolution: %d", capabilities.y_resolution);
  LOG_INF("supported pixel formats: %d", capabilities.supported_pixel_formats);
  LOG_INF("screen_info: %d", capabilities.screen_info);
  LOG_INF("current_pixel_format: %d", capabilities.current_pixel_format);
  LOG_INF("current_orientation: %d", capabilities.current_orientation);
  
  const struct display_buffer_descriptor buf_desc = {
    .width = x_res,
    .height = y_res,
    .buf_size = x_res * y_res,
    .pitch = DISPLAY_BUFFER_PITCH
  };

  if (display_write(display, 0, 0, &buf_desc, buf) != 0) {
    LOG_ERR("[!] Unable to write to buffer");
  }

}