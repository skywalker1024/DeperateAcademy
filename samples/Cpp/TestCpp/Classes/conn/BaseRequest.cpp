//
//  BaseRequest.cpp
//  BraveFrontier

//  Created by WillArk on 11/13/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "BaseRequest.h"
#include "CommonUtils.h"
/*
 * コンストラクタ。
 */
BaseRequest::BaseRequest()
{
    m_url = "";
    m_data = "";
}

/*
 * デストラクタ。
 */
BaseRequest::~BaseRequest()
{

}

string BaseRequest::getFullUrl(){
    return string("http://niebaosanguo.sinaapp.com/").append(m_url);
}

string BaseRequest::getFullData(){
    if (m_data != "") {
        return m_data.append("&channel_user_id=").append(CommonUtils::getChannelUserId());
    }else{
        return string("channel_user_id=").append(CommonUtils::getChannelUserId());
    }
}
