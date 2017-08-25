/*********************************************************************
* LEGAL DISCLAIMER
*
* (Header of MediaTek Software/Firmware Release or Documentation)
*
* BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY 
* ACKNOWLEDGES AND AGREES THAT THE SOFTWARE/FIRMWARE AND ITS 
* DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED FROM MEDIATEK AND/OR 
* ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS ONLY. 
* MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR 
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF 
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR 
* NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY 
* WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH 
* MAY BE USED BY, INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK 
* SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY
* WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO NOT BE 
* RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S 
* SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
* BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND 
* CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED 
* HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE 
* MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR 
* SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE
* AT ISSUE.
*
* THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN 
* ACCORDANCE WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING
* ITS CONFLICT OF LAWS PRINCIPLES.
**********************************************************************
*/

/*
 *	File:	spi_test.c
 *	 
 *	Author: Peter Jiang
 *	 		
 *	Last Revision Date: 2015.6.11
 *	 
 *	Description:
 *	test spi read/write via accessing /dev/spi (spi.ko)
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/ioctl.h>

#define SPI_CTRL_IOCTL_MAGIC		0x91

typedef struct _spi_cmd_struct {
	unsigned char ctrl;
	unsigned char cmd;
	unsigned char len;
	unsigned char data[29];

}spi_cmd_struct;

enum {
	SPI_CTRL_IOCTL_INIT		= _IOW(SPI_CTRL_IOCTL_MAGIC,  1, int),
	SPI_CTRL_IOCTL_READ		= _IOW(SPI_CTRL_IOCTL_MAGIC,  2, spi_cmd_struct),
	SPI_CTRL_IOCTL_WRITE	= _IOW(SPI_CTRL_IOCTL_MAGIC,  3, spi_cmd_struct),
};

int slic_init ()
{
	int ret = -1;
	int fd = -1;
	int i = 0;
	fd = (int)open("/dev/spi", O_RDWR);

	if (fd <= 0) {
		printf ("open /dev/spi failed\n");
		return -1;
	}
	ret = ioctl(fd, SPI_CTRL_IOCTL_INIT, 0);

	if (fd)
		close(fd);

	return ret;

}

int access_spi (spi_cmd_struct *cmd)
{
	int ret = -1;
	int fd = -1;
	int i = 0;
	fd = (int)open("/dev/spi", O_RDWR);

	if (fd <= 0) {
		printf ("open /dev/spi failed\n");
		return -1;
	}

	if ((cmd->ctrl&0xFF) == 0x7E) {/*write*/
		ret = ioctl(fd, SPI_CTRL_IOCTL_WRITE, (int)cmd);
	}
	else if ((cmd->ctrl&0xFF) == 0xBE) {/*read*/
		ret = ioctl(fd, SPI_CTRL_IOCTL_READ, (int)cmd);
		for (i = 0; i < cmd->len; i++)
			printf ("[test] data[%d]=0x%2x\n", i, cmd->data[i]);
	
	}

	if (fd)
		close(fd);

	return ret;
}

int pressure_test ()
{
	spi_cmd_struct cmd = {0};
	int count = 0;
	
	printf ("pressure_test\n");
	while (count++ < 10000) {
		memset (&cmd, 0, sizeof(spi_cmd_struct));
		
		cmd.ctrl = 0x7E;
		cmd.cmd  = 0x07;
		cmd.len  = 2;
		cmd.data[0] = 0x00;
		cmd.data[1] = 0x1A;

		access_spi (&cmd);  

		memset (&cmd, 0, sizeof(spi_cmd_struct));
		
		cmd.ctrl = 0xBE;
		cmd.cmd  = 0x07;
		cmd.len  = 2;
		cmd.data[0] = 0x00;
		cmd.data[1] = 0x00;

		access_spi (&cmd);

		if (cmd.data[0]==0 && cmd.data[1]==0x1A)
			printf ("success %d\n", count);
		else
			printf ("failed with 0x%x 0x%x\n", cmd.data[0], cmd.data[1]);
	}

	return 0;
}

int pressure_test2 ()
{
	spi_cmd_struct cmd = {0};
	int i = 0, j = 0;
	unsigned char write_bytes[6] = {0x20, 0x06, 0x08, 0x0a, 0x14, 0x07};
  unsigned char read_bytes[6]  = {0x18, 0x14, 0x24, 0x0c, 0x0e, 0x07};
	
	printf ("pressure_test2\n");
	while(j++ < 10000*1000) {
		for (i = 0; i < 6; i++) {
			memset (&cmd, 0, sizeof(spi_cmd_struct));
			
			cmd.ctrl = 0x7E;
			cmd.cmd  = write_bytes[i];
			cmd.len  = 2;
			cmd.data[0] = 0x00;
			cmd.data[1] = 0x0f;
	
			access_spi (&cmd);  
	
			memset (&cmd, 0, sizeof(spi_cmd_struct));
			
			cmd.ctrl = 0xBE;
			cmd.cmd  = read_bytes[i];
			cmd.len  = 2;
			cmd.data[0] = 0x00;
			cmd.data[1] = 0x00;
	
			access_spi (&cmd);
		}
		if (cmd.data[0]==0 && cmd.data[1]==0x0f)
			printf ("success %d\n", j);
		else
			printf ("failed with 0x%x 0x%x\n", cmd.data[0], cmd.data[1]);
	}

	return 0;
}

int main (int argc, char *argv[])
{
	int ret = 0;
	int fd = -1;
	int i = 0;
	

	spi_cmd_struct cmd = {0};

	if (!strcmp (argv[1], "init"))
	{
		slic_init ();
		return 0;
	}
	if (argc < 5) {
		printf ("invalid params");
		return -1;
	}
	
	printf ("[test]%s %s %s %s %s\n", argv[0], argv[1], argv[2], argv[3], argv[4]);

	cmd.ctrl = strtol(argv[1], NULL, 16) & 0xFF;
	cmd.cmd = strtol(argv[2], NULL, 16) & 0xFF;
	cmd.len = strtol(argv[3], NULL, 10) & 0xFF;

	printf ("[test]ctrl:0x%x, cmd: 0x%x, len: %d\n", cmd.ctrl, cmd.cmd, cmd.len);
	if (cmd.len > 28){
		printf ("length invalid, should < 29\n");
		return -1;
	}
		
	for (i = 0; (i< cmd.len) && (4+i < argc); i++)
	{
		cmd.data[i] = strtol(argv[4+i], NULL, 16) & 0xFF;
		printf (" 0x%x ", cmd.data[i]);
	}
	printf ("\n");
	
	ret = access_spi (&cmd);

#if 0
	ret = pressure_test ();
#endif		

#if 0
	ret = pressure_test2 ();
#endif	
	return ret;
}
