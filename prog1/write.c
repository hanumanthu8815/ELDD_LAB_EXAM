#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<asm/ioctl.h>
#include "ioctl.h"

/*struct DefaultData {
    int Baudrate;
    int StopBits;
    int Parity;
}; */

struct stats
{
    int size;
    char buff[100];
    int r_w;
}

int main()
{
    //int fd,res, BAUD_RATE = 9600, STP_BITS = 8, *test;
    //struct DefaultData ToSend={9800,1,0};
    struct stats ToSend={50,"This is from write user",1};
    char Ubuff[]="--this is user buffer--sending data to the kernel--";
    char Kbuff[100];
    fd=open("/dev/IOCTL_Device",O_RDWR,0777);
    if(fd<0)
    {
        printf("\nerror in opening file\n");
        exit(1);
    }
    /*res= ioctl (fd,SET_BAUD_RATE, &BAUD_RATE);
    if(res<0)
    {
        printf("\n IOCTL error");
        return (-1);
    }
    printf("the baud conformation: %d",BAUD_RATE);
    test=&STP_BITS;
    ioctl (fd, SET_NO_STOP_BITS,&STP_BITS);
    ioctl (fd, SET_DIRECTION_WRITE, NULL);
    ioctl (fd, DEFAULT_DATA, &ToSend);*/
    ioctl(fd, WRITE, (char *)Ubuff);

    write(fd,Ubuff,sizeof(Ubuff));
    //read(fd,Kbuff,sizeof(Ubuff));
   // printf("\n data read from kernel is\n>>> %s<<<\n",Kbuff);
    close(fd);
}