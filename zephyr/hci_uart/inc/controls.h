#ifndef HCI_UART_CONTROLS_H
#define HCI_UART_CONTROLS_H

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0    DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN        DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS    DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0    ""
#define PIN    0
#define FLAGS    0
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

#define WHEEL1_TR_L_NODE DT_ALIAS(wheel1_turn_l)

#if DT_NODE_HAS_STATUS(WHEEL1_TR_L_NODE, okay)
#define WHEEL1_TR_L    DT_GPIO_LABEL(WHEEL1_TR_L_NODE, gpios)
#define WHEEL1_TR_L_PIN        DT_GPIO_PIN(WHEEL1_TR_L_NODE, gpios)
#define WHEEL1_TR_L_FLAGS    DT_GPIO_FLAGS(WHEEL1_TR_L_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: WHEEL1_NODE devicetree alias is not defined"
#define WHEEL1_TR_L	    ""
#define WHEEL1_TR_L_PIN	0
#define WHEEL1_TR_L_FLAGS	0
#endif


#define WHEEL1_TR_R_NODE DT_ALIAS(wheel1_turn_r)

#if DT_NODE_HAS_STATUS(WHEEL1_TR_R_NODE, okay)
#define WHEEL1_TR_R    DT_GPIO_LABEL(WHEEL1_TR_R_NODE, gpios)
#define WHEEL1_TR_R_PIN        DT_GPIO_PIN(WHEEL1_TR_R_NODE, gpios)
#define WHEEL1_TR_R_FLAGS    DT_GPIO_FLAGS(WHEEL1_TR_R_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: WHEEL1_NODE devicetree alias is not defined"
#define WHEEL1_TR_R	    ""
#define WHEEL1_TR_R_PIN	0
#define WHEEL1_TR_R_FLAGS	0
#endif

#define COMPRESOR1_NODE DT_ALIAS(compressor)

#if DT_NODE_HAS_STATUS(COMPRESOR1_NODE, okay)
#define COMPRESOR1    DT_GPIO_LABEL(COMPRESOR1_NODE, gpios)
#define COMPRESOR1_PIN        DT_GPIO_PIN(COMPRESOR1_NODE, gpios)
#define COMPRESOR1_FLAGS    DT_GPIO_FLAGS(COMPRESOR1_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: WHEEL1_NODE devicetree alias is not defined"
#define COMPRESOR1	    ""
#define COMPRESOR1_PIN	0
#define COMPRESOR1_FLAGS	0
#endif

extern const struct device *led, *wheel1_sw, *wheel1_brk, *wheel1_fr,
        *wheel1_tr_l, *wheel1_tr_r, *compresor_1;

extern int car_speed;
extern uint8_t direction;
extern uint8_t car_enabled;
extern uint8_t rotating;
extern uint8_t rotating_direction;

void gpio_init_controls();

void stop_car();

void unbreak_car();

void set_direction(uint8_t dir);

void set_car_speed(uint8_t speed);

void start_compressor();

void stop_compressor();

void turn_left();

void turn_right();


#endif //HCI_UART_CONTROLS_H
