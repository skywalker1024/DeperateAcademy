//
//  NetworkManager.cpp
//  CrossKaiser
//
//  Created by 龚畅优 on 13-1-18.
//
//

#include "NetworkManager.h"
#include "Player.h"
#include "Utilities.h"
#include "NetworkRetryDialog.h"
#include "Constants.h"
#include "NetworkErrorDialog.h"
#include "LoadingLockLayer.h"
#include "Language.h"
#include "Maintenance.h"
#define SET_EXTRA_HEADER do { \
    Player *_player = Player::sharedObject(); \
    const CCString &uuid = _player->getUUID(); \
    const CCString &playerID = _player->getID(); \
    if (uuid.compare("") != 0) \
        headers.push_back("X-KK-UUID:"+uuid.m_sString); \
    if (playerID.compare("") != 0) \
        headers.push_back("X-KK-USERID:"+playerID.m_sString); \
    headers.push_back("X-KK-IDENTITY-TYPE:0"); \
    headers.push_back("X-KK-IDENTITY-ID:" + Utilities::getMacAddress()); \
    headers.push_back("X-KK-DEVICEOS:" + Utilities::getDeviceOS());   \
    headers.push_back("X-KK-DEVICEMODEL:" + Utilities::getDeviceInfo()); \
    headers.push_back("X-KK-OSVERSION:" + Utilities::getOSVersion());   \
    headers.push_back("X-KK-APPVERSION:" + Utilities::getBundleVersion());   \
    headers.push_back("X-KK-DLCVERSION:" + getDlcVersion());   \
    if(CCUserDefault::sharedUserDefault()->getIntegerForKey(GAME_ZONE_SEQUENCE_KEY)) \
        headers.push_back("X-KK-GZID:" + Utilities::convertInt( CCUserDefault::sharedUserDefault()->getIntegerForKey(GAME_ZONE_SEQUENCE_KEY)) );   \
    else \
        headers.push_back("X-KK-GZID:''"); \
    headers.push_back("X-KK-IDENTIFIER-FOR-VENDOR:" + Utilities::getIdentifierForVendor());   \
} while (0)


NetworkManager *NetworkManager::instance = NULL;

NetworkManager::NetworkManager()
:m_httpClient(NULL)
,m_loading_lock_layer(NULL)
,m_caller(NULL)
{
    CCHttpClient* httpClient = CCHttpClient::getInstance();
    setHttpClient(httpClient);
//    httpClient->setTimeoutForConnect(15);
    // TODO: 不太确定这个值会不会影响大文件的下载
//    httpClient->setTimeoutForRead(15);
}
NetworkManager::~NetworkManager()
{
    delete instance;
    instance = NULL;
    CC_SAFE_RELEASE_NULL(m_loading_lock_layer);
    CC_SAFE_RELEASE_NULL(m_httpClient);
}

NetworkManager *NetworkManager::sharedInstance()
{
    if (!instance) {
        instance = new NetworkManager;
    }
    return instance;
}

void NetworkManager::NetworkRequest(std::string url,
                                    CCHttpRequest::HttpRequestType requestType,
                                    std::string data,
                                    std::string tag,
                                    CCObject* caller,
                                    SEL_CallFuncND selector,
                                    bool loadingScreen,
                                    bool showErrorDialog)
{
    this->setCaller(caller);
    
    if(loadingScreen)
    {
        this->showLoading();
    }
    CCHttpRequest *request = new CCHttpRequest();

    if (requestType == CCHttpRequest::kHttpPost && url.find("/api/") != std::string::npos)
    {
    	CCLOG("----post----\n%d",data.length());
		if (data.length() <= 1000) {
			CCLOG("before xxtea encrypt, data : %s", data.c_str());
		} else {
			CCLOG("before xxtea encrypt, data : %d", data.length());
		}
        data = Utilities::XXTEA_Encrypt_Decrypt(Constants::REQUEST_DATA, false).append(Utilities::XXTEA_Encrypt_Decrypt(data, true));
        if (data.length() <= 1000) {
			CCLOG("after xxtea encrypt, data : %s", data.c_str());
		} else {
			CCLOG("after xxtea encrypt, data : %d", data.length());
		}
    }
    
    std::string signature_url = Utilities::addSignature(url, requestType, data);
    request->setUrl(signature_url.c_str());
    request->setRequestType(requestType);
    request->setRequestData(data.c_str(), data.length());
    request->setResponseCallback(caller, selector);
    request->setTag(tag.c_str());
    request->setLoadingVisible(loadingScreen);
    request->setShowErrorDialog(showErrorDialog);
    
    //preparing the headers for submission with the request
    std::vector<std::string> headers;
    SET_EXTRA_HEADER;
    headers.push_back("Content-Type: application/json; charset=utf-8");
    request->setHeaders(headers);
    
    getHttpClient()->send(request);
    request->release();
}

void NetworkManager::NetworkRequestPost(std::string url,
                                        std::string data,
                                        std::string tag,
                                        CCObject* caller,
                                        SEL_CallFuncND selector)
{
    this->NetworkRequest(url, CCHttpRequest::kHttpPost, data, tag, caller, selector);
}


void NetworkManager::NetworkRequestGet(std::string url, std::string tag, cocos2d::CCObject *caller, SEL_CallFuncND selector)
{
    this->NetworkRequest(url, CCHttpRequest::kHttpGet, "", tag, caller, selector);
}

void NetworkManager::NetworkRequestForRetry(CCHttpRequest *request, bool showLoadingScreen){//retry用
    std::string url = request->getUrl();
    std::string post_data = "";
    if (request->getRequestType() == CCHttpRequest::kHttpPost and request->getRequestDataSize()>0)
        post_data = string(request->getRequestData(), request->getRequestDataSize());
    std::string signature_url = Utilities::reAddSignature(url, request->getRequestType(), post_data);
    request->setUrl(signature_url.c_str());
    this->setCaller(request->getTarget());
    if (showLoadingScreen) {
        request->setLoadingVisible(true);
        this->showLoading();
    }
    request->setShowErrorDialog(true);
    getHttpClient()->send(request);
}
bool NetworkManager::onNetworkRequestComplete(void *data)
{
   
    CCHttpResponse *response = (CCHttpResponse*)data;
    if(!response)
    {
        this->hideLoading();
        return false;
    }
    
    if(0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLOG("%s completed", response->getHttpRequest()->getTag());
    }

    int statusCode = response->getResponseCode();
    CCLOG("response code: %d", statusCode);
    
    if(!response->isSucceed())
    {
        CCLOG("response failed");
        std::vector<char> v = *(response->getResponseData());
        std::string str(v.begin(), v.end());
        CCLOG(" %s ", str.c_str());
    }
    if (response->getHttpRequest()->getLoadingVisible()) {
        this->hideLoading();
    }

    return checkResponse(data);
}

void NetworkManager::NetworkRequestForImg(std::string url,
                                          CCHttpRequest::HttpRequestType requestType,
                                          std::string tag,
                                          CCObject* caller,
                                          SEL_CallFuncND selector)
{
    CCHttpRequest *request = new CCHttpRequest();
    std::string signature_url = Utilities::addSignature(url, requestType);
    request->setUrl(signature_url.c_str());
    request->setRequestType(requestType);
    request->setResponseCallback(caller, selector);
    request->setTag(tag.c_str());
    
    //preparing the headers for submission with the request
    std::vector<std::string> headers;
    if(string(url).find(".jpg") != std::string::npos)
    {
        CCLOG("jpg header");
        headers.push_back("Content-Type: image/jpg");
    }
    else if(string(url).find(".png") != std::string::npos)
    {
        CCLOG("png header");
        headers.push_back("Content-Type: image/png");
    }
    
    request->setHeaders(headers);
    
    getHttpClient()->send(request);
    request->release();
}

void NetworkManager::NetworkRequestFile(const char *url,
                                        std::string data,
                                        const char* md5,
                                        const char *tag,
                                        CCObject* caller,
                                        SEL_CallFuncND selector)
{
    //isDisableHUD = true;
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl(url);
    request->setRequestType(CCHttpRequest::kHttpFile);
    request->setRequestData(data.c_str(), data.length());
	request->setUserData((void*)md5);
    request->setShowErrorDialog(false);//在onNetworkRequestFileComplete中自行处理
#ifdef NO_ERROR_POPUP
	request->setResponseCallback(caller, selector);
#else
    request->setResponseCallback(this, callfuncND_selector(NetworkManager::onNetworkRequestFileComplete));
	request->setForwardCallback(caller, selector);
#endif
    request->setTag(tag);
    request->setRequestTime(Utilities::getCurrentTimeMs());

    CCHttpClient::getInstance()->send(request);
    CCLOG("request file start");
	request->release();
}

bool NetworkManager::onNetworkRequestFileComplete(cocos2d::CCNode *sender, void *data)
{
	CCHttpResponse* pResponse = (CCHttpResponse*)data;
	CCHttpRequest* pRequest = pResponse->getHttpRequest();

    CCLOG("onNetworkRequestFileComplete");
	if (pRequest->getLoadingVisible())
	{
		while (Utilities::getCurrentTimeMs() - pRequest->getRequestTime() < 2000)
		{}
        this->hideLoading();
        //CCNotificationCenter::sharedNotificationCenter()->postNotification(GUMI_LIVE_UI_INPUT_TEXT_VISIBLE, CCBool::create(true));
	}

    // return if we do not to do callback
    if( !pRequest->getForwardTarget() && !pRequest->getForwardSelector() )
        return true;

	if (!pResponse->isSucceed())
    {
        m_pFailedResponses.push_back(pResponse);
        pResponse->retain();
        CCNode * dialog = CCDirector::sharedDirector()->getRunningScene()->getChildByTag(DIALOG_TAG);
		if (!m_pFailedResponses.empty() && !dialog) //if there are no network failures and if there is a current popup shown, then do not display a popup
        {
            if (pResponse->getResponseCode() == 401)
            {
                //PopupConfirmationLayer::create(Json::nullValue, this, CL_GUMI_LIVE_TOKEN_EXPIRY, OnTokenExpiredOkPressed);

                std::vector<CCHttpResponse*>::iterator it;
                for (it = m_pFailedResponses.begin(); it <= m_pFailedResponses.end(); it++)
                {
                    m_pFailedResponses.erase(it);
                    (*it)->release();
                }
            }
            else
            {
                std::vector<char>*buffer = pResponse->getResponseData();
                Json::Value val;
                Utilities::ReadIntoJson(buffer, val, false);

                const char * tag = pRequest->getTag();
                if( strlen(tag) >= 2 && strncmp(tag, "OK", 2) == 0 )
                {
                    CCLOG("file download succeed!");
                    //PopupConfirmationLayer::create(val, this, CL_NETWORK_ERROR_OK_ONLY, OnErrorRetryPressed, OnErrorCancelPressed);
                }
                else
                {
                    CCLOG("file download fail");
                    Utilities::showNetworkRetryDialog(pRequest, true, pRequest->getLoadingVisible(), TXT_LOGIN_DLERROR);
                    return false;
                }
            }
        }
	}
	else
	{
        CCLOG("file download succeed forward!");
		forwardResponse(pResponse);
        return true;
	}
}

void NetworkManager::forwardResponse(CCHttpResponse* pResponse)
{
	CCHttpRequest* pRequest = pResponse->getHttpRequest();

	if (pRequest->getForwardTarget() && pRequest->getForwardSelector())
		(pRequest->getForwardTarget()->*pRequest->getForwardSelector())((CCNode *)this, pResponse);
}

bool NetworkManager::checkResponse(void *data)
{

    CCHttpResponse *response = (CCHttpResponse*)data;
    CCHttpRequest *request = response->getHttpRequest();
    std::string requestUrl = request->getUrl();
    CCLOG("----url----\n%s", requestUrl.c_str());
    if(request->getRequestType() == CCHttpRequest::kHttpPost){
        std::string post_data = string(request->getRequestData(), request->getRequestDataSize());
        CCLOG("----post----\n%d",post_data.length());
        if (post_data.length() <= 1000) {
            CCLOG("----post----\n%s", post_data.c_str());
        }
    }
    if(!response->isSucceed())
    {
        Constants::HTTP_STATUS httpStatus = Constants::HTTP_STATUS(response->getResponseCode());
        handleHTTPError(httpStatus, request);
        return false;
    }

    if (request->getRequestType() == CCHttpRequest::kHttpFile)
    {
        return true;
    }

    Json::Value json;
    if (!Utilities::ResponsetoJson(response, json, false)) {
        if (request->getShowErrorDialog()) {
            Utilities::showNetworkRetryDialog(request, false, request->getLoadingVisible(), "");
        }
        return false;
    }
    
    Constants::SERVER_STATUS status_code = Constants::SERVER_STATUS(json["status_code"].asInt());
    HANDLE_TYPE handleType = handleServerError(status_code, requestUrl, json, request->getShowErrorDialog());

    if (handleType == NetworkManager::DO_POPUP_ERROR_DIALOG){
        return false;
    }

    if(json["maintenance"].asBool()){
        std::string maintenance = json["maintenance"].asString();
        Utilities::showMaintenanceBar(maintenance.c_str());
    }
    //else {
    //    Utilities::removeMaintenanceBar();
    //}

    return true;
}

NetworkManager::HANDLE_TYPE
NetworkManager::handleServerError(Constants::SERVER_STATUS status_code, std::string &requestUrl, Json::Value &json, bool showErrorDialog)
{
    HANDLE_TYPE handle_type = DO_POPUP_ERROR_DIALOG;

    if(status_code == Constants::STATUS_CODE_OK or status_code >= Constants::SYSTEM_SERVER_STATUS_CODE){
        handle_type = DO_NOTHING;
    } else if (status_code < Constants::SYSTEM_SERVER_STATUS_CODE){
        handle_type = DO_POPUP_ERROR_DIALOG;
    }

    if(Utilities::is_not_require_player_url(requestUrl)){
        if(status_code != Constants::STATUS_CODE_AUTHENTICATION_ERROR and status_code != Constants::STATUS_CODE_MAINTENANCE){
            handle_type = DO_NOTHING;
        }
    }

    if(Utilities::is_not_require_ban_player_url(requestUrl)){
        handle_type = DO_NOTHING;
    }

    //clear session and go home to request uuid again
    //if(status_code == Constants::STATUS_CODE_INVALID_UUID){
    //}

    if ( handle_type == DO_POPUP_ERROR_DIALOG ) {
        if (showErrorDialog) {
            std::string errmsg = json["errmsg"].asString();
            Json::Value data = json["data"];
            if (status_code == Constants::STATUS_CODE_MAINTENANCE) {
                Maintenance *err_box = Maintenance::createWithJson(data);
                CCDirector::sharedDirector()->getRunningScene()->addChild(err_box,0,DIALOG_TAG);
            }else{
                NetworkErrorDialog * err_box = NetworkErrorDialog::createWithServerStatus(status_code, requestUrl, errmsg, data);
                CCDirector::sharedDirector()->getRunningScene()->addChild(err_box,0,DIALOG_TAG);
            }
            
        }
    }

    return handle_type;
}

NetworkManager::HANDLE_TYPE
NetworkManager::handleHTTPError(Constants::HTTP_STATUS httpStatus, CCHttpRequest* request)
{
    HANDLE_TYPE handle_type = DO_POPUP_ERROR_DIALOG;

    switch (httpStatus) {
        case Constants::HTTP204:
            handle_type = DO_NOTHING;
            break;
        case Constants::HTTP302: break;
        case Constants::HTTP403:
            handle_type = DO_POPUP_ERROR_DIALOG;
            break;
        case Constants::HTTP404: break;
        case Constants::HTTP500:
            handle_type = DO_POPUP_ERROR_DIALOG;
            break;
        default:
            handle_type = DO_RETRY_NETWORK;
            break;
    }
    bool showLoadingScreen = request->getLoadingVisible();
    if (handle_type == DO_POPUP_ERROR_DIALOG) {
        if (request->getShowErrorDialog()) {
            NetworkErrorDialog * err_box = NetworkErrorDialog::createWithHTTPStatus(httpStatus);
            CCDirector::sharedDirector()->getRunningScene()->addChild(err_box, 0, Constants::DIALOG_TAG);
        } else {
            CCLOG(">>>>>> ERROR: %d >>>>>>", httpStatus);
        }
    } else if (handle_type == DO_RETRY_NETWORK){
        if (request->getShowErrorDialog()) {
            Utilities::showNetworkRetryDialog(request,false, showLoadingScreen, "");
        }
    }
    return handle_type;
}

void NetworkManager::showLoading()
{
    LoadingLockLayer* loading_layer = this->getLoadingLockLayer();
    if (loading_layer && loading_layer->isLock()) {
        return;
    }
    loading_layer = LoadingLockLayer::create();
    this->setLoadingLockLayer(loading_layer);
    loading_layer->doLock();
    CCNode* node = dynamic_cast<CCNode*>(this->getCaller());
    if (node) {
        node->addChild(loading_layer);
    } else {
        CCDirector::sharedDirector()->getRunningScene()->addChild(loading_layer);
        loading_layer->show();
    }
}

void NetworkManager::hideLoading()
{
    if (! this->getLoadingLockLayer()) {
        return;
    }
    this->getLoadingLockLayer()->unLock();
    this->setLoadingLockLayer(NULL);
    this->setCaller(NULL);
}
