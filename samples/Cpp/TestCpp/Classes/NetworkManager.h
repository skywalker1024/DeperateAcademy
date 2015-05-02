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
#include "Constants.h"
#include "LoadingLockLayer.h"

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
                        SEL_CallFuncND selector,
                        bool loadingScreen = true,
                        bool showErrorDialog = true);
    
	void NetworkRequestPost(std::string url,
                            std::string data,
                            std::string tag,
                            CCObject* caller,
                            SEL_CallFuncND selector);
    
    void NetworkRequestGet(std::string url,
                            std::string tag,
                            CCObject* caller,
                            SEL_CallFuncND selector);
    
    void NetworkRequestForImg(std::string url,
                              CCHttpRequest::HttpRequestType requestType,
                              std::string tag,
                              CCObject* caller,
                              SEL_CallFuncND selector);
    void NetworkRequestFile(const char *url,
                            std::string data,
                            const char* md5,
                            const char *tag,
                            CCObject* caller,
                            SEL_CallFuncND selector);
    bool onNetworkRequestFileComplete(cocos2d::CCNode *sender, void *data);
    void forwardResponse(CCHttpResponse* pResponse);
    void NetworkRequestForRetry(CCHttpRequest *request, bool showLoadingScreen);
	bool onNetworkRequestComplete(void *data);
    bool onNetworkRequestCompleteAsync(void *data); //No loading screen
    bool checkResponse(void *data);

    typedef enum
    {
        DO_NOTHING = 0,
        DO_POPUP_ERROR_DIALOG = 1, //弹出错误框
        DO_RETRY_NETWORK = 2, //弹出重新请求框
        DO_REDIRECTOR = 3, //跳转做其它处理，(暂时没用到)
    } HANDLE_TYPE;

    HANDLE_TYPE handleServerError(Constants::SERVER_STATUS, std::string &requestUrl, Json::Value &json, bool showErrorDialog);
    HANDLE_TYPE handleHTTPError(Constants::HTTP_STATUS, CCHttpRequest* request);

private:
    NetworkManager();
    virtual ~NetworkManager();
    NetworkManager(const NetworkManager &);
    NetworkManager& operator=(const NetworkManager &);
    void showLoadingScreen();
    static NetworkManager *instance;
    CC_SYNTHESIZE_RETAIN(CCHttpClient*, m_httpClient, HttpClient);
    void showLoading();
    void hideLoading();
    vector<CCHttpResponse*> m_pFailedResponses;
private:
    CC_SYNTHESIZE_RETAIN(LoadingLockLayer*, m_loading_lock_layer, LoadingLockLayer);
    CC_SYNTHESIZE(CCObject*, m_caller, Caller);

};

#endif /* defined(__CrossKaiser__NetworkManager__) */
