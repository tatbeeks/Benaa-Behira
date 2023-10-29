/**
 ************************************************************************                  
 * @file                    : OTA.c
 * @author                  : Ahmed Hesham
 * @brief                   : OTA Module source file
 ************************************************************************
 */

 #include "OTA.h"

 void OTA_Init (void)
 {
   OTADRIVE.setInfo("b0b639ff-f4ae-4f38-ad93-311cfcc229e0", "v@1.0.1");
 }

void OTA_Runnable(void) {
  if (OTADRIVE.timeTick(3600)) {
    OTADRIVE.updateFirmware();
  }
}
