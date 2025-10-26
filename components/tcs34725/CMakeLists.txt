idf_component_register(
    SRCS "tcs34725.c"
    INCLUDE_DIRS "include"
    REQUIRES driver esp_driver_gpio
)