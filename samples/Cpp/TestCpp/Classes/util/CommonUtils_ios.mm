//
//  CommonUtils.cpp
//  SampleGame2
//
//  Created by 株式会社 ウィルアーク on 3/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CommonUtils.h"
#include "AlertView.h"
#include "PaymentUtil.h"
#include "TalkingDataAppCpa.h"
#include "UserInfo.h"
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

void CommonUtils::showAlert(){
    [[AlertView alloc] init];
}

bool CommonUtils::checkoutPaymentID(string aPaymentID)//订单优化
{
    return [PaymentUtil checkoutPaymentID:[NSString stringWithFormat:@"%s", aPaymentID.c_str()]];
}

void CommonUtils::startCheckID()
{
    PaymentUtil* util = [[PaymentUtil alloc ] init ];
    [ util paymentRequest:[ NSString stringWithUTF8String:"check" ] ];
}

void CommonUtils::talkingDataCpaOnPay(const char * orderId,int amount,const char * currencyType,const char * payType)
{
    NSString * userIdStr = [NSString stringWithFormat:@"%d",  UserInfo::shared()->getUserId()];
    NSString * orderIdStr = [NSString stringWithFormat:@"%s", orderId];
    NSString * currencyTypeStr = [NSString stringWithFormat:@"%s", currencyType];
    NSString * payTypeStr = [NSString stringWithFormat:@"%s", payType];
    [TalkingDataAppCpa onPay:userIdStr withOrderId:orderIdStr withAmount:amount withCurrencyType:currencyTypeStr withPayType:payTypeStr];
}

void CommonUtils::paymentRequest(string purchaseId){
    PaymentUtil* util = [ [ PaymentUtil alloc ] init ];
    [ util paymentRequest:[ NSString stringWithUTF8String:purchaseId.c_str() ] ];
}