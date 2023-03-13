#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/kernel.h>

static const struct pwm_dt_spec fading_led =
  PWM_DT_SPEC_GET(DT_NODELABEL(fading_led));

void main(void) {
  if (!device_is_ready(fading_led.dev)) {
    printk("[!] ERROR: PWM device %s is not ready\n",
	   fading_led.dev->name);
    return;
  }

  int ret;
  while (1) {
    ret = pwm_set_pulse_dt(&fading_led, 0);
    k_sleep(K_SECONDS(1));
    ret = pwm_set_pulse_dt(&fading_led, 10000);
    k_sleep(K_SECONDS(1));
  }
}