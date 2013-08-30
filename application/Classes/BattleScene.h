//
//  BattleScene.h
//  CrossKaiser
//
//  Created by 龚畅优 on 13-8-27.
//
//

#ifndef __CrossKaiser__BattleScene__
#define __CrossKaiser__BattleScene__

#include "cocos2d.h"
USING_NS_CC;

class BattleScene : public CCLayer{
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(BattleScene);
    BattleScene();
    virtual ~BattleScene();
    
};
#endif /* defined(__CrossKaiser__BattleScene__) */
