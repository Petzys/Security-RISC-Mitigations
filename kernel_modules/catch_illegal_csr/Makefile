obj-m += catch_illegal_csr.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(CURDIR)

all: 
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	
