//
//  CommonUtils.cpp
//  SampleGame2
//
//  Created by 株式会社 ウィルアーク on 3/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CommonUtils.h"
std::string CommonUtils::getDeviceID()
{
    
    std::string ret = "";
    std::string deviceOS = [[[UIDevice currentDevice] systemVersion] UTF8String];
    
    if (![[UIDevice currentDevice]respondsToSelector:@selector(identifierForVendor)] || strcmp(deviceOS.c_str(), "6.0") == 0) {
        // iOS6之前的版本可以使用openUDID...
        NSString *uuid = [[UIDevice currentDevice] uniqueDeviceIdentifier];
        ret = std::string([uuid UTF8String]);
    }
    else
    {
        // iOS6版本以后将无法获取MAC address，所以使用identifierForVendor。
        ret = [[[[UIDevice currentDevice] identifierForVendor] UUIDString] UTF8String];
    }
    return ret;
}
