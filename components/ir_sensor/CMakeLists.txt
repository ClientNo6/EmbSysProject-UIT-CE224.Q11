idf_component_register(
    SRCS "ir_sensor.c"
    INCLUDE_DIRS "include"        # ir_sensor.h
    REQUIRES driver freertos      # depends on these components
)