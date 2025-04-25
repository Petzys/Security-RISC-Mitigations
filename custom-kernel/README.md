# Uninstalling old kernels

If `/boot/` is too full (check with `df`),
we need to uninstall old kernels.

List installed packages with `dpkg --get-selections`, filter for kernels with `grep`, e.g., version 6.6.20:
```bash
niklas@starfive:~$ dpkg --get-selections | grep 6.6.20
linux-headers-6.6.20-cosec-test+                install
linux-headers-6.6.20-starfive                   install
linux-image-6.6.20-cosec-test+                  install
linux-image-6.6.20-starfive                     install
```

Keep the original kernel (`linux-image-6.6.20-starfive`).

Uninstall others with `dpkg -P`, e.g.,
```bash
sudo dpkg -P linux-headers-6.6.20-cosec-test+ linux-image-6.6.20-cosec-test+
```
