obj-m += disable_csr.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(CURDIR)

all: 
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	
install_autostart:
	sudo mkdir -p /lib/modules/$(shell uname -r)/extra
	sudo cp disable_csr.ko /lib/modules/$(shell uname -r)/extra/
	sudo depmod -a
	echo "disable_csr" | sudo tee /etc/modules-load.d/disable_csr.conf
	sudo modprobe disable_csr
	@echo "disable_csr installed and set to autostart."

remove_autostart:
	sudo rm -f /lib/modules/$(shell uname -r)/extra/disable_csr.ko
	sudo rm -f /etc/modules-load.d/disable_csr.conf
	sudo depmod -a
	sudo rmmod disable_csr || true
	@echo "disable_csr removed from system and autostart."