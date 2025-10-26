// main.c (ESP-IDF)

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "ir_sensor.h"
#include "tcs34725.h"
#include "driver/i2c.h"

// begin defines
#define IRSENSOR_GPIO 32
#define USE_PULLUP 1
// end defines
// begin structs

// end structs 

// begin global variables, constants
ir_sensor_handler ir_handler;
ir_sensor_event_t ir_event;
tcs34725_handler tcs_handler;

static const char *TAG = "main";
// end global variables

// begin function prototypes
void ir_sensor_task(void *arg);
void tcs34725_task(void *arg);
// end function prototypes
void app_main(void)
{
    // Initialize 
    ir_sensor_init(&ir_handler, IRSENSOR_GPIO, USE_PULLUP);
    tcs34725_init(&tcs_handler);
    
    // Create tasks
    xTaskCreate(ir_sensor_task, "IR_Sensor_Task", 2048, NULL, 5, NULL);
    xTaskCreate(tcs34725_task, "TCS34725_Task", 2048, NULL, 5, NULL);
    // Bind tasks to cores if needed (optional)
    xTaskCreatePinnedToCore(ir_sensor_task, "IR_Sensor_Task", 2048, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(tcs34725_task, "TCS34725_Task", 2048, NULL, 5, NULL, 1);
}
// end main function
// begin function definitions
void ir_sensor_task(void *arg) {
    while (1) {
        ir_sensor_counter(&ir_handler, &ir_event);
    }
}
void tcs34725_task(void *arg) {
    while (1) {
        tcs34725_reader(&tcs_handler);
    }
}