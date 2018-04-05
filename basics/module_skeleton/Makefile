obj-m := skeleton.o

CFLAGS_skeleton.o = -DDEBUG

KERNELDIR += /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) clean
