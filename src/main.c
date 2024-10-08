#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS   1000

#define LED_RED_NODE    DT_ALIAS(led0)
#define LED_GREEN_NODE  DT_ALIAS(led1)
#define LED_BLUE_NODE   DT_ALIAS(led2)

//Get the specs
static const struct gpio_dt_spec led_red = GPIO_DT_SPEC_GET(LED_RED_NODE, gpios);
static const struct gpio_dt_spec led_green = GPIO_DT_SPEC_GET(LED_GREEN_NODE, gpios);
static const struct gpio_dt_spec led_blue = GPIO_DT_SPEC_GET(LED_BLUE_NODE, gpios);

int main(void)
{
  //return value
	int ret;


  //If any of 3 LEDs is not working, return
  if(!gpio_is_ready_dt(&led_red)
  || !gpio_is_ready_dt(&led_green)
  || !gpio_is_ready_dt(&led_blue)){

    return 0;
  }

  //configuring LED, checking for errors
  ret = gpio_pin_configure_dt(&led_red, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

  ret = gpio_pin_configure_dt(&led_green, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

  ret = gpio_pin_configure_dt(&led_blue, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

  //led switch - 0 red, 1 green, 2 blue
  int led = 0;

  while(1){
    //Turn on
    if (led == 0) ret = gpio_pin_toggle_dt(&led_red);
    if (led == 1) ret = gpio_pin_toggle_dt(&led_green);
    if (led == 2) ret = gpio_pin_toggle_dt(&led_blue);

    if(ret < 0){
      return 0;
    }    

    k_msleep(SLEEP_TIME_MS);

    //Turn off
    if (led == 0) ret = gpio_pin_toggle_dt(&led_red);
    if (led == 1) ret = gpio_pin_toggle_dt(&led_green);
    if (led == 2) ret = gpio_pin_toggle_dt(&led_blue);

    if(ret < 0){
      return 0;
    }  

    //Change LED
    if(led >= 2){
      led = 0;
    }else{
      led++;
    }
  }
	return 0;
}