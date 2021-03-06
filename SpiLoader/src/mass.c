/****************************************************************************
*                                                                           *
* Copyright (c) 2009 Nuvoton Tech. Corp. All rights reserved.               *
*                                                                           *
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wblib.h"
#include "usbd.h"
#include "mass_storage_class.h"
#include "w55fa93_sic.h"
#include "nvtfat.h"
#include "nvtloader.h"


BOOL connected(void)
{
    return(udcIsAttached());
}


void mass(NDISK_T *disk, INT32 i32TotalSector)
{
#if 0
	WB_CLKFREQ_T clock;		
	
	udcFlashInit((char *)disk);  	
    sysGetClockFreq(&clock);
    	udcInit(clock.pll_clk_freq);	
	udcMassBulk((T_CallbackFunc*) connected);	
	udcDeinit();
	return;
#else	

 #if 0
	/* initial nuvoton file system */
	fsInitFileSystem();
	fsAssignDriveNumber('C', DISK_TYPE_SMART_MEDIA, 0, 1);     // NAND 0, 2 partitions
	fsAssignDriveNumber('D', DISK_TYPE_SMART_MEDIA, 0, 2);     // NAND 0, 2 partitions

	/* initialize FMI (Flash memory interface controller) */
    	sicIoctl(SIC_SET_CLOCK, 192000, 0, 0);  /* clock from PLL */
    	sicOpen();
  #endif
  	
	mscdInit();		
	mscdFlashInit((NDISK_T *)disk, i32TotalSector);	
	udcInit();
	mscdMassEvent(connected);
	udcDeinit();
	udcClose();	
#endif	
}