obj-m += seconds.o
KDIR = /usr/src/linux-headers-4.4.0-87/include/
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean