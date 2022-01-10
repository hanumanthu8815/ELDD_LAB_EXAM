obj-m:=chardriver.o
KD=/lib/modules/$(shell uname -r)/build/
PWD:=$(shell pwd)

default:
	$(MAKE) -C $(KD) M=$(PWD) modules
	gcc -o app app.c
clean:
	$(MAKE) -C $(KD) M=$(PWD) modules clean
	rm app

