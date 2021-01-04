#include "controls.h"


const struct device *led, *wheel1_sw, *wheel1_brk, *wheel1_fr, *wheel1_tr_l, *wheel1_tr_r, *compresor_1;

int car_speed = 0;
uint8_t direction = 1;
uint8_t car_enabled = 1;
uint8_t rotating = 0;
uint8_t rotating_direction = 0;

void gpio_init_controls() {
    int ret;

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

    wheel1_tr_l = device_get_binding(WHEEL1_TR_L);
    if (wheel1_tr_l == NULL) {
        return;
    }
    ret = gpio_pin_configure(wheel1_tr_l, WHEEL1_TR_L_PIN, GPIO_OUTPUT_INACTIVE | WHEEL1_TR_L_FLAGS);
    if (ret < 0) {
        return;
    }

    wheel1_tr_r = device_get_binding(WHEEL1_TR_R);
    if (wheel1_tr_r == NULL) {
        return;
    }
    ret = gpio_pin_configure(wheel1_tr_r, WHEEL1_TR_R_PIN, GPIO_OUTPUT_INACTIVE | WHEEL1_TR_R_FLAGS);
    if (ret < 0) {
        return;
    }

    compresor_1 = device_get_binding(COMPRESOR1);
    if (compresor_1 == NULL) {
        return;
    }
    ret = gpio_pin_configure(compresor_1, COMPRESOR1_PIN, GPIO_OUTPUT_INACTIVE | COMPRESOR1_FLAGS);
    if (ret < 0) {
        return;
    }
}

void stop_car() {
    car_enabled = 0;
    gpio_pin_set(wheel1_brk, WHEEL1_BRK_PIN, (int) false);
}

void unbreak_car() {
    car_enabled = 1;
    gpio_pin_set(wheel1_brk, WHEEL1_BRK_PIN, (int) true);
}

void set_direction(uint8_t dir) {
    if (dir == 0) {
        gpio_pin_set(wheel1_fr, WHEEL1_FR_PIN, (int) false);
    } else {
        gpio_pin_set(wheel1_fr, WHEEL1_FR_PIN, (int) true);
    }
}

void set_car_speed(uint8_t speed) {
    if (car_enabled == 0) return;
    if (speed > 0) {
        gpio_pin_set(wheel1_sw, WHEEL1_SW_PIN, (int) true);
    } else {
        gpio_pin_set(wheel1_sw, WHEEL1_SW_PIN, (int) false);
    }
//    TIM1->CCR1 = speed;
}

void start_compressor() { // TODO: change pin
    gpio_pin_set(compresor_1, COMPRESOR1_PIN, (int) true);
}

void stop_compressor() {
    gpio_pin_set(compresor_1, COMPRESOR1_PIN, (int) false);
}

void turn_left() {
    gpio_pin_set(wheel1_tr_l, WHEEL1_TR_L_PIN, (int) true);
    gpio_pin_set(wheel1_tr_r, WHEEL1_TR_R_PIN, (int) false);
    k_msleep(30);
    gpio_pin_set(wheel1_tr_l, WHEEL1_TR_L_PIN, (int) true);
    gpio_pin_set(wheel1_tr_r, WHEEL1_TR_R_PIN, (int) true);
}

void turn_right() {
    gpio_pin_set(wheel1_tr_l, WHEEL1_TR_L_PIN, (int) false);
    gpio_pin_set(wheel1_tr_r, WHEEL1_TR_R_PIN, (int) true);
    k_msleep(30);
    gpio_pin_set(wheel1_tr_l, WHEEL1_TR_L_PIN, (int) true);
    gpio_pin_set(wheel1_tr_r, WHEEL1_TR_R_PIN, (int) true);
}
