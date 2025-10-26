#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#pragma once
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
// defines
#define IR_SENSOR_QUEUE_SIZE 10
#define COND_TO_COUNT 0 // logic to increase the count value (0 mean 1->0 transition; 1 mean 0->1 transition)
#define MS_PER_OBJ 3

// struct for IR sensor handler
typedef struct {
    uint8_t gpio_num;
    uint8_t current_level;
    uint32_t event_count;
} ir_sensor_handler;

// struct for IR sensor event
typedef struct {
    uint8_t gpio_num;
    uint8_t level;
} ir_sensor_event_t;

// init
void ir_sensor_init(ir_sensor_handler* handler, gpio_num_t gpio_num, bool use_pullup);
// cleanup
void ir_sensor_deinit(void);
// count events
void ir_sensor_counter(ir_sensor_handler* handler, ir_sensor_event_t *evt);

#endif // IR_SENSOR_H