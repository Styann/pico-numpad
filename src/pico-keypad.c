//#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

//usb
#include "usb/dev_lowlevel.h"

//keys
#include "keys/keys.h"

#define LED_PIN 16

bool keyboard_timer_callback(struct repeating_timer *timer);

int main(void) {   
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, true);

    stdio_init_all();
    usb_device_init();
    keys_init();

    while(!is_configured()){
        tight_loop_contents();
    }

    // Get ready to rx from host
    //usb_start_transfer(usb_get_endpoint_configuration(EP0_OUT_ADDR), NULL, 64);

    struct repeating_timer keyboard_timer;

    add_repeating_timer_ms(
        10, //10ms
        keyboard_timer_callback,
        NULL,
        &keyboard_timer
    );

    while(true){
        tight_loop_contents();
    }
    
    return 0;
}

bool keyboard_timer_callback(struct repeating_timer *timer){
    isr_scan_keyboard();
    // if ready -> irq_scan_keyboard();

    return true;
}