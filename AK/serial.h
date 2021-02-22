#ifndef HYPEROS_AK_SERIAL_H_
#define HYPEROS_AK_SERIAL_H_

int serial_init(void);

int serial_received(void);
char serial_read(void);

int serial_transmit_empty(void);
void serial_write(char c);
void serial_write_string(const char* str);

#endif