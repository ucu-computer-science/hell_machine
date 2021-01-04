/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
//#include <sys/util.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   20


#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0    DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN        DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS    DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0	""
#define PIN	0
#define FLAGS	0
#endif


#define WHEEL1_SW_NODE DT_ALIAS(wheel1_sw)

#if DT_NODE_HAS_STATUS(WHEEL1_SW_NODE, okay)
#define WHEEL1_SW           DT_GPIO_LABEL(WHEEL1_SW_NODE, gpios)
#define WHEEL1_SW_PIN       DT_GPIO_PIN(WHEEL1_SW_NODE, gpios)
#define WHEEL1_SW_FLAGS     DT_GPIO_FLAGS(WHEEL1_SW_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: WHEEL1_NODE devicetree alias is not defined"
#define WHEEL1_SW	""
#define WHEEL1_SW_PIN	0
#define WHEEL1_SW_FLAGS	0
#endif


#define WHEEL1_BRK_NODE DT_ALIAS(wheel1_brk)

#if DT_NODE_HAS_STATUS(WHEEL1_BRK_NODE, okay)
#define WHEEL1_BRK    DT_GPIO_LABEL(WHEEL1_BRK_NODE, gpios)
#define WHEEL1_BRK_PIN        DT_GPIO_PIN(WHEEL1_BRK_NODE, gpios)
#define WHEEL1_BRK_FLAGS    DT_GPIO_FLAGS(WHEEL1_BRK_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: WHEEL1_NODE devicetree alias is not defined"
#define WHEEL1_BRK	""
#define WHEEL1_BRK_PIN	0
#define WHEEL1_BRK_FLAGS	0
#endif

#define WHEEL1_FR_NODE DT_ALIAS(wheel1_fr)

#if DT_NODE_HAS_STATUS(WHEEL1_FR_NODE, okay)
#define WHEEL1_FR    DT_GPIO_LABEL(WHEEL1_FR_NODE, gpios)
#define WHEEL1_FR_PIN        DT_GPIO_PIN(WHEEL1_FR_NODE, gpios)
#define WHEEL1_FR_FLAGS    DT_GPIO_FLAGS(WHEEL1_FR_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: WHEEL1_NODE devicetree alias is not defined"
#define WHEEL1_FR	    ""
#define WHEEL1_FR_PIN	0
#define WHEEL1_FR_FLAGS	0
#endif

#define SW0_NODE    DT_ALIAS(sw0)

#if DT_NODE_HAS_STATUS(SW0_NODE, okay)
#define SW0_GPIO_LABEL    DT_GPIO_LABEL(SW0_NODE, gpios)
#define SW0_GPIO_PIN    DT_GPIO_PIN(SW0_NODE, gpios)
#define SW0_GPIO_FLAGS    (GPIO_INPUT | DT_GPIO_FLAGS(SW0_NODE, gpios))
#else
#error "Unsupported board: sw0 devicetree alias is not defined"
#define SW0_GPIO_LABEL	""
#define SW0_GPIO_PIN	0
#define SW0_GPIO_FLAGS	0
#endif

//void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
//    printk("Button pressed at %" PRIu32 "\n");
//}

static struct gpio_callback button_cb_data;

void main(void) {
    const struct device *led, *wheel1_sw, *wheel1_brk, *wheel1_fr;
    const struct device *button;
    bool led_is_on;
    int ret;

    button = device_get_binding(SW0_GPIO_LABEL);
    if (button == NULL) {
        return;
    }
    ret = gpio_pin_configure(button, SW0_GPIO_PIN, SW0_GPIO_FLAGS);
    if (ret != 0) {
        return;
    }
//    ret = gpio_pin_interrupt_configure(button, SW0_GPIO_PIN, GPIO_INT_EDGE_TO_ACTIVE);
//    if (ret != 0) {
//        return;
//    }
//    gpio_init_callback(&button_cb_data, button_pressed, BIT(SW0_GPIO_PIN));
//    gpio_add_callback(button, &button_cb_data);


    led = device_get_binding(LED0);
    if (led == NULL) {
        return;
    }
    ret = gpio_pin_configure(led, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
    if (ret < 0) {
        return;
    }

    wheel1_sw = device_get_binding(WHEEL1_SW);
    if (wheel1_sw == NULL) {
        return;
    }
    ret = gpio_pin_configure(wheel1_sw, WHEEL1_SW_PIN, GPIO_OUTPUT_ACTIVE | WHEEL1_SW_FLAGS);
    if (ret < 0) {
        return;
    }

    wheel1_brk = device_get_binding(WHEEL1_BRK);
    if (wheel1_brk == NULL) {
        return;
    }
    ret = gpio_pin_configure(wheel1_brk, WHEEL1_BRK_PIN, GPIO_OUTPUT_INACTIVE | WHEEL1_BRK_FLAGS);
    if (ret < 0) {
        return;
    }

    wheel1_fr = device_get_binding(WHEEL1_FR);
    if (wheel1_fr == NULL) {
        return;
    }
    ret = gpio_pin_configure(wheel1_fr, WHEEL1_FR_PIN, GPIO_OUTPUT_INACTIVE | WHEEL1_FR_FLAGS);
    if (ret < 0) {
        return;
    }

    led_is_on = false;
    gpio_pin_set(wheel1_sw, WHEEL1_SW_PIN, (int) led_is_on);
    while (1) {
        if (gpio_pin_get(button, SW0_GPIO_PIN) != led_is_on) {
            k_msleep(50);
            if (gpio_pin_get(button, SW0_GPIO_PIN) != led_is_on) {
                led_is_on = !led_is_on;
                gpio_pin_set(led, PIN, (int) led_is_on);
                gpio_pin_set(wheel1_sw, WHEEL1_SW_PIN, (int) led_is_on);
            }
        }
        k_msleep(SLEEP_TIME_MS);
    }
}
