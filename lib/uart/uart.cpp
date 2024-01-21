#include "uart.h"

#include <cstring>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

Uart::Uart(uart_pin_config_t &uart_pin_config, uart_config_t &uart_config)
{
    init(uart_pin_config, uart_config);
}

void Uart::init(uart_pin_config_t &uart_pin_config, uart_config_t &uart_config)
{
    uart_num = uart_pin_config.uart_port;

    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(uart_num, uart_pin_config.tx_pin,
                                 uart_pin_config.rx_pin, UART_PIN_NO_CHANGE,
                                 UART_PIN_NO_CHANGE));
    ESP_ERROR_CHECK(uart_driver_install(uart_num, rx_buffer_size,
                                        tx_buffer_size, queue_size, nullptr,
                                        interrupt_flags));

    ESP_LOGI("Uart", "Uart port %d successfully initialized", uart_num);
}

int Uart::write(const char *data, size_t size)
{
    return uart_write_bytes(uart_num, data, size);
}

int Uart::read(char *data, size_t size)
{
    return uart_read_bytes(uart_num, (uint8_t *)data, size,
                           pdMS_TO_TICKS(read_timeout));
}