#ifndef UART_CLASS_H
#define UART_CLASS_H

#include "driver/uart.h"

struct uart_pin_config_t
{
    uart_port_t uart_port;
    size_t tx_pin;
    size_t rx_pin;
};

class Uart
{
   public:
    Uart(uart_pin_config_t &uart_pin_config, uart_config_t &uart_config);

    int write(const char *data, size_t size);
    int read(char *data, size_t size);

   private:
    void init(uart_pin_config_t &uart_pin_config, uart_config_t &uart_config);
    uart_port_t uart_num;
    const size_t read_timeout{100};
    const size_t rx_buffer_size{256};
    const size_t tx_buffer_size{0};
    const size_t queue_size{0};
    const size_t interrupt_flags{0};
};

#endif /* UART_CLASS_H */
