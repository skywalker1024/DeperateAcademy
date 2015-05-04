//
//  NetworkManager.cpp
//  CrossKaiser
//
//  Created by 龚畅优 on 13-1-18.
//
//

#include "NetworkManager.h"

NetworkManager *NetworkManager::instance = NULL;

NetworkManager::NetworkManager()
{
    m_httpClient = NULL;
    m_caller = NULL;
//    httpClient->setTimeoutForConnect(15);
    // TODO: 不太确定这个值会不会影响大文件的下载
//    httpClient->setTimeoutForRead(15);
}
NetworkManager::~NetworkManager()
{
    delete instance;
    instance = NULL;
}

NetworkManager *NetworkManager::sharedInstance()
{
    if (!instance) {
        instance = new NetworkManager();
        CCHttpClient* httpClient = CCHttpClient::getInstance();
        instance->setHttpClient(httpClient);
    }
    return instance;
}

void NetworkManager::NetworkRequest(std::string url,
                                    CCHttpRequest::HttpRequestType requestType,
                                    std::string data,
                                    std::string tag,
                                    CCObject* caller,
                                    SEL_HttpResponse selector,
                                    bool loadingScreen,
                                    bool showErrorDialog)
{
    this->setCaller(caller);
    
    CCLog("url=%s postData=%s postLen=%lu HttpRequestType=%d",url.c_str(), data.c_str(), data.length(), requestType);
    CCHttpRequest *request = new CCHttpRequest();

    request->setUrl(url.c_str());
    request->setRequestType(requestType);
    request->setRequestData(data.c_str(), data.length());
    request->setResponseCallback(caller, selector);
    request->setTag(tag.c_str());
    
    //preparing the headers for submission with the request
//    std::vector<std::string> headers;
//    headers.push_back("Content-Type: application/json; charset=utf-8");
//    request->setHeaders(headers);
    
    getHttpClient()->send(request);
    request->release();
}

void NetworkManager::NetworkRequestPost(std::string url,
                                        std::string data,
                                        std::string tag,
                                        CCObject* caller,
                                        SEL_HttpResponse selector)
{
    this->NetworkRequest(url, CCHttpRequest::kHttpPost, data, tag, caller, selector);
}


void NetworkManager::NetworkRequestGet(std::string url, std::string tag, cocos2d::CCObject *caller, SEL_HttpResponse selector)
{
    this->NetworkRequest(url, CCHttpRequest::kHttpGet, "", tag, caller, selector);
}