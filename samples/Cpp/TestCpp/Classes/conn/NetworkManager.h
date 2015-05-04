//
//  NetworkManager.h
//  CrossKaiser
//
//  Created by 龚畅优 on 13-1-18.
//
//

#ifndef __CrossKaiser__NetworkManager__
#define __CrossKaiser__NetworkManager__

#include <iostream>
#include "cocos-ext.h"
#include "cocos2d.h"
#include "json.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

class NetworkManager : public CCObject
{
public:
    //obtain or construct singleton instance
    static NetworkManager *sharedInstance();
    void NetworkRequest(std::string url,
                        CCHttpRequest::HttpRequestType requestType,
                        std::string data,  // TODO 使用get时，暂时无效，后面在完善
                        std::string tag,
                        CCObject* caller,
                        SEL_HttpResponse selector,
                        bool loadingScreen = true,
                        bool showErrorDialog = true);
    
	void NetworkRequestPost(std::string url,
                            std::string data,
                            std::string tag,
                            CCObject* caller,
                            SEL_HttpResponse selector);
    
    void NetworkRequestGet(std::string url,
                            std::string tag,
                            CCObject* caller,
                            SEL_HttpResponse selector);
private:
    static NetworkManager *instance;
    NetworkManager();
    virtual ~NetworkManager();
    CC_SYNTHESIZE_RETAIN(CCHttpClient*, m_httpClient, HttpClient);
    CC_SYNTHESIZE(CCObject*, m_caller, Caller);
};

#endif /* defined(__CrossKaiser__NetworkManager__) */
