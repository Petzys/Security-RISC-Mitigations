obj-m += clear_icache_on_context_switch.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(CURDIR)

all: 
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	
