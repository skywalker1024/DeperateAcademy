//
//  MissionMstList.h
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#ifndef BraveFrontier_MissionMstList_h
#define BraveFrontier_MissionMstList_h

#include "cocos2d.h"
#include "MissionMst.h"

USING_NS_CC;

class MissionMstList : public CCObject
{
	public:
		// インスタンスの取得
		static MissionMstList* shared();
		// オブジェクトの追加
		void addObject( MissionMst* mst);
		// オブジェクトの解放
		void removeAllObjects();
		// 件数の取得
		int getCount();
		// オブジェクトの取得
		MissionMst* getObject( int index );
        MissionMst* getObjectWithMissionID( string mission_id );
        // ミッションリストの取得
        CCMutableArray<MissionMst*>* getMissionListWithDungeonID( string dungeon_id );
        // ミッションリストの取得
        CCMutableArray<MissionMst*>* getMissionListWithDungeonIDAll( string dungeon_id );

	protected:

	private:
		// コンストラクタ
		MissionMstList();
		// デストラクタ
		~MissionMstList();
		// mstリスト
		CCMutableArray<MissionMst*> *mstList;

};

#endif
