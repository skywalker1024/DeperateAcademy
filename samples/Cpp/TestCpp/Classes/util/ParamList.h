//
//  ParamList.h
//  BraveFrontier

//  Created by WillArk on 7/20/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_ParamList_h
#define BraveFrontier_ParamList_h

#include "cocos2d.h"


USING_NS_CC;

class ParamList : public CCObject
{
	public:
		// インスタンスの取得
		static ParamList* shared();
		// オブジェクトの追加
		//void addObject( Param* info);
		// オブジェクトの解放
		void removeAllObjects();
		// 件数の取得
		int getCount();
		// オブジェクトの取得
		//Param* getObject( string key );
   
        // 値の設定
        void setValue( string key, int value );
        void setValue( string key, string value );
        void setValue( string key, CCString* value );
    
        // 値の取得
        string getValue( string key );
        // キーの取得
        vector<string> allKeys();

    
	protected:

	private:
		// コンストラクタ
		ParamList();
		// デストラクタ
		~ParamList();
		// infoリスト
		CCMutableDictionary<string,CCString*> *infoList;

};

#endif
