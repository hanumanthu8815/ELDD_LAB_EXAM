 obj-m := ioctl.o
 KDIR = /lib/modules/$(shell uname -r)/build/
 PWD = $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc -o ioctl_app ioctl_app.c
	gcc -o read read.c
	gcc -o write write.c

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm ioctl_app read write

install:
	$(MKAE) -C $(KDIR) M=$(PWD) modules_install
