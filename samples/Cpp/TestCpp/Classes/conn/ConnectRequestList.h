//
//  ConnectRequestList.h
//  BraveFrontier

//  Created by WillArk on 11/21/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_ConnectRequestList_h
#define BraveFrontier_ConnectRequestList_h

#include "cocos2d.h"
#include "BaseRequest.h"

USING_NS_CC;

class ConnectRequestList : public CCObject
{
	public:
		// インスタンスの取得
		static ConnectRequestList* shared();
		// オブジェクトの追加
		void addObject( BaseRequest* info );

		// オブジェクトの解放
		void removeAllObjects();
		// 件数の取得
		int getCount();
		// オブジェクトの取得
		BaseRequest* getObject( int index );
    void removeObject( BaseRequest* request );
	protected:

	private:
		// コンストラクタ
		ConnectRequestList();
		// デストラクタ
		~ConnectRequestList();
		// infoリスト
		CCMutableArray<BaseRequest*>*requestList;

};

#endif

