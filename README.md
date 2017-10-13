Solar Flare PPS Control
-----------------------

A quick utility that can enable or disable the One Pulse-Per-Second (1PPS) Input on a Solar Flare adapter using OpenOnload ioctls.

It's useful for simulating 1PPS media failures and measuring drift while free running. It can also be used to turn on the 1PPS input without
having to run Solar Flare's sfptpd daemon.

It is hard coded with the ioctl numbers and structures from OpenOnload version 201606-u1.2, under the assumption that those won't
change much between releases. I can't guarantee it will work with any in-kernel driver that's not Onload though.

Usage
=====

```bash
sudo ./sfppsctrl enable eth1
sudo ./sfppsctrl disable eth1
```

License
=======

It's close to a cut and paste of the examples out of `efx_ioctl.h`, so must follow the OpenOnload license, GPLv2.
