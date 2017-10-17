Solar Flare PPS Control
-----------------------

A quick utility that can enable or disable the One Pulse-Per-Second (1PPS) Input on a Solar Flare adapter using OpenOnload ioctls.

It's useful for simulating 1PPS media failures and measuring drift while free running. It can also be used to turn on the 1PPS input without
having to run Solar Flare's sfptpd daemon.

It is hard coded with the ioctl numbers and structures from OpenOnload version 201606-u1.2, under the assumption that those won't
change much between releases.

It will work not work with any in-kernel Solar Flare driver, it will only work with the out-of-tree Onload driver.

Usage
=====

```bash
sudo ./sfppsctrl enable eth1
sudo ./sfppsctrl disable eth1
```

As A Service
============

The RPM installs a simple init script to start/stop 1PPS on a set of interfaces on boot.

RPM
===

There is a very basic Red Hat style Spec file included:

```bash
make dist
cp sfppsctrl-${version}.tar.gz ~/rpmbuild/SOURCES
rpmbuild -ba sfppsctrl.spec
```

License
=======

It's close to a cut and paste of the examples out of `efx_ioctl.h`, so must follow the OpenOnload license, GPLv2.
