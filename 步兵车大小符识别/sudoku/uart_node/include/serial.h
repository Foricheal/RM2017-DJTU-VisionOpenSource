#ifndef SERIAL_H
#define SERIAL_H

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ioctl.h>

#define TRUE 1
#define FALSE 0

#define BAUDRATE        115200
#define UART_DEVICE     "/dev/ttyTHS2"


void GetMode(int &fd,int &mode);
void TransformData(int &fd,int number,int position);
void InitSerial(int &fd);
void set_speed(int fd, int speed);
int set_Parity(int fd,int databits,int stopbits,int parity);

#endif // SERIAL_H
