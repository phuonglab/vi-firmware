#include "rtc_config_command.h"
#include "platform_profile.h"


#include "config.h"
#include "util/log.h"
#ifdef RTC_SUPPORT
#include "rtc.h"
#endif

bool openxc::commands::validateRTCConfigurationCommand(openxc_VehicleMessage* message) {
    bool valid = false;
    if(message->has_control_command) {
        openxc_ControlCommand* command = &message->control_command;
        if(command->has_rtc_configuration_command) {
            valid = true;
        }
    }
    return valid;
}

bool openxc::commands::handleRTCConfigurationCommand(openxc_ControlCommand* command) {
    
    bool status = false;
    
    if(command->has_rtc_configuration_command) {
        openxc_RTCConfigurationCommand* rtcConfigurationCommand =
          &command->rtc_configuration_command;

        if(rtcConfigurationCommand->has_unix_time){
#ifdef RTC_SUPPORT
            uint32_t new_unix_time =
              rtcConfigurationCommand->unix_time;            
            status = RTC_SetTimeUnix(new_unix_time);
#endif                
        }
    }
    sendCommandResponse(openxc_ControlCommand_Type_RTC_CONFIGURATION, status);
    
    return status;
}