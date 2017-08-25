#ifndef _MGR_SDI_H_
#define _MGR_SDI_H_

#define unchar 			unsigned char
#define ushort 			unsigned short
#define uint 			unsigned int
#define ulong 			unsigned long

#include "xmcs/xmcs_sdi.h"

extern MGR_S32 gpIoctlFd ;
#define XMCS_IOCTL_SDI(cmd, arg)		ioctl(gpIoctlFd, cmd, arg)


#endif /* _MGR_SDI_H_ */

