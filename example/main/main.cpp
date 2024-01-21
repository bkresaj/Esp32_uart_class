/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <inttypes.h>
#include <stdio.h>

#include <cstring>
#include <array>
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "uart.h"

extern "C"
{
    void app_main(void);
}

void sending_task(void *pvParameter)
{
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
        .source_clk = UART_SCLK_DEFAULT
    };

    uart_pin_config_t uart_pin_config = {
        .uart_port = UART_NUM_1, .tx_pin = 19, .rx_pin = 18};

    Uart uart1(uart_pin_config, uart_config);

    const size_t buffer_size{20};
    std::array<char, buffer_size> buffer_write{"Hello from uart1\n"};

    ESP_LOGI("UART1", "Hello!\n");

    while (1)
    {
        uart1.write(buffer_write.data(), buffer_size);

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void receiving_task(void *pvParameter)
{
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
        .source_clk = UART_SCLK_DEFAULT
    };

    uart_pin_config_t uart_pin_config = {
        .uart_port = UART_NUM_2, .tx_pin = 17, .rx_pin = 16};

    Uart uart2(uart_pin_config, uart_config);

    const size_t buffer_size{20};
    std::array<char, buffer_size> buffer_read{};

    ESP_LOGI("UART2", "Hello!\n");

    while (1)
    {
        uart2.read(buffer_read.data(), buffer_size);

        ESP_LOGI("UART2", "RECEIVED: %s\n", buffer_read.data());
        buffer_read.fill(0);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main(void)
{
    xTaskCreate(&sending_task, "sending_task", 2048, nullptr, 5, nullptr);
    xTaskCreate(&receiving_task, "receiving_task", 2048, nullptr, 5, nullptr);

    while (1)
    {
        ESP_LOGI("MAIN_TASK", "Hello!\n");

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}