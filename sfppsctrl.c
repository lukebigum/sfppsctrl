// Quick and dirty way to Enable or disable the PPS Input on a Solar Flare.
//
// Usage: ./sfppsctrl (enable|disable) <interface name>
//
// This code has been adapted from the OpenOnload source code,
// specifically the linux_net/efx_ioctl.h file and examples therein.

/****************************************************************************
 * Ioctl interface to Solarflare network adapter driver
 *
 * Copyright 2005-2006: Fen Systems Ltd.
 * Copyright 2006-2016: Solarflare Communications Inc,
 *                      9501 Jeronimo Road, Suite 250,
 *                      Irvine, CA 92618, USA
 *
 * Initially developed by Michael Brown <mbrown@fensystems.co.uk>
 * Maintained by Solarflare Communications <linux-net-drivers@solarflare.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <net/if.h>
#include <linux/if_ether.h>
#include <linux/sockios.h>
#include <linux/ethtool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdint.h>
#include <linux/ptp_clock.h>
#include <errno.h>

#define SIOCEFX (SIOCDEVPRIVATE + 3)
#define EFX_TS_ENABLE_HW_PPS 0xef1d
struct efx_ts_hw_pps {
        __u32 enable;
};
union efx_ioctl_data {
        struct efx_ts_hw_pps pps_enable;
};
struct efx_sock_ioctl {
        __u16 cmd;
        __u16 reserved;
        union efx_ioctl_data u;
} __attribute__ ((packed));

void usage()
{
  printf("Usage: sfppsctrl (enable|disable) <interface name>\n");
  exit(1);
}

int main (int argc, char *argv[])
{
   int fd,ret;
   uint32_t zero = 0x00;
   uint32_t one = 0x01;
   struct ifreq ifr;
   struct efx_sock_ioctl efx;

   if (argc < 3) {
     usage();
   }

   memset(&efx, 0, sizeof(struct efx_sock_ioctl));
   efx.cmd = EFX_TS_ENABLE_HW_PPS;

   if (strncmp(argv[1], "enable", 2) == 0) {
     efx.u.pps_enable.enable = one;
   } else if (strncmp(argv[1], "disable", 2) == 0) {
     efx.u.pps_enable.enable = zero;
   } else {
     usage();
   }
   strncpy(ifr.ifr_name, argv[2], IFNAMSIZ);
   ifr.ifr_data = (caddr_t) & efx;

   fd = socket(AF_INET, SOCK_DGRAM, 0);
   if (fd == -1) {
     perror("open");
     usage();
   }

   ret = ioctl(fd, SIOCEFX, &ifr);
   if (ret == -1) {
     if (errno == 114) {
       printf("PPS already enabled.\n");
       exit(0);
     }
     perror("ioctl");
     exit(1);
   }
}
