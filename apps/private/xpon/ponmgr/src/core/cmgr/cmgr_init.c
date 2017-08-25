#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/fcntl.h>

#include "core/cmgr/cmgr_init.h"
#include "core/dbmgr/dbmgr.h"

MGR_S32		gpIoctlFd = 0 ;
/*****************************************************************************
*****************************************************************************/
MGR_Ret cmgr_init(void)
{
	MGR_Ret ret = EXEC_OK ;

	gpIoctlFd = open(IOCTL_NODE, O_RDWR) ;
	if(gpIoctlFd < 0) {
		return EXEC_ERR ;	
	}
	
	return ret ;	
}


/*****************************************************************************
*****************************************************************************/
MGR_Ret cmgr_destroy(void)
{
	MGR_Ret ret = EXEC_OK ;

	close(gpIoctlFd) ;
	gpIoctlFd = 0 ;
	
	return ret ;	
}

