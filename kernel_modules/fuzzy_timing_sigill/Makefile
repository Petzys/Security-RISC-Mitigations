obj-m += fuzzy_timing_sigill.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(CURDIR)

all: 
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	
