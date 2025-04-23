# Building

Build the kernel modules in their respective subdirectories using `make`.

# Loading and Unloading

To load a kernel module: `sudo modprobe path/to/module_name.ko`.

To unload a kernel module `sudo rmmod module_name`.

Currently loaded modules can be listed with `lsmod`.

# Example

```bash
cd kernel_modules/disable_instret_module
make

sudo modprobe ./disable_instret.ko

...

sudo rmmod disable_instret
```
