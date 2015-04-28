//
//  ParticleAnimeList.cpp
//  BraveFrontier

//  Created by WillArk on 10/5/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "ParticleAnimeList.h"

ParticleAnimeList* ParticleAnimeListInstance = NULL;

/*
 * シングルトンインスタンスを取得。
 */
ParticleAnimeList* ParticleAnimeList::shared()
{
	if( ParticleAnimeListInstance == NULL )
	{
		ParticleAnimeListInstance= new ParticleAnimeList();
	}

	return ParticleAnimeListInstance;
}

/*
 * コンストラクタ。
 */
ParticleAnimeList::ParticleAnimeList()
{
	animeList = new CCMutableArray<ParticleAnime*>;
    m_removeFlg = true;
}

/*
 * デストラクタ。
 */
ParticleAnimeList::~ParticleAnimeList()
{

}

/*
 * オブジェクトの追加。
 */
void ParticleAnimeList::addAnime( ParticleAnime* anime )
{
	animeList->addObject( anime );
}

/*
 * オブジェクトの解放。
 */
void ParticleAnimeList::removeAllAnime()
{
    CCLog( "ParticleAnimeList::removeAllAnime()" );
    
    if (!m_removeFlg) {
        return;
    }
    
    for( int i = 0; i < animeList->count(); i++ )
    {
        ParticleAnime* anime = animeList->getObjectAtIndex( i );
        anime->setVisible(false);
        anime->stopSystem();
        anime->setTotalParticles( 0 );
        
        CCLog( " particle cnt=%d", anime->retainCount() );
        
    }
    
    
	animeList->removeAllObjects();
}

/*
 * オブジェクトの解放。
 */
void ParticleAnimeList::removeAnime( ParticleAnime* anime )
{
    anime->stopSystem();
    
    animeList->removeObject( anime );
}


/*
 * 件数の取得。
 */
int ParticleAnimeList::getCount()
{
	return animeList->count();
}

/*
 * オブジェクトを取得。
 */
ParticleAnime* ParticleAnimeList::getObject( int index )
{
	return animeList->getObjectAtIndex( index );
}



/*
 * 定期処理。
 */
void ParticleAnimeList::process()
{
    CCMutableArray<ParticleAnime*> *delete_list = new CCMutableArray<ParticleAnime*>;;
    delete_list->autorelease();
    
    for( int i = 0; i < animeList->count(); i++ )
    {
        ParticleAnime* anime = animeList->getObjectAtIndex( i );
        
        if( anime->getPauseFlg() ) continue;
        
        anime->process();
        
        // 有効無効のチェック
        if( !anime->getIsEnable() )
        {
            anime->setTotalParticles( 0 );
            delete_list->addObject( anime );
            //CCLog( "--- particle enable=false" );
        }
    }

    
    animeList->removeObjectsInArray( delete_list );
    
    /*
    if( delete_list->count() > 0 )
    {
        CCLog( "@@@@@@@@@@ParticleAnimeList::proces count=%d", animeList->count() );
    }
    */
    
}

void ParticleAnimeList::pause()
{
    CCLog( "#############ParticleAnimeList::pause()" );
    
    for( int i = 0; i < animeList->count(); i++ )
    {
        ParticleAnime* anime = animeList->getObjectAtIndex( i );  
        anime->unscheduleUpdate();
        
        anime->setPauseFlg( true );
    }
    
}

void ParticleAnimeList::resume()
{
  
    for( int i = 0; i < animeList->count(); i++ )
    {
        ParticleAnime* anime = animeList->getObjectAtIndex( i );
        
        if( !anime->getPauseFlg() ) continue;
        
        anime->scheduleUpdate();
        
         anime->setPauseFlg( false );
    }
    
}



/*
 * 存在チェック。
 */
bool ParticleAnimeList::exist( string anime_id, float x, float y, int wait )
{
    for( int i = 0; i < animeList->count(); i++ )
    {
        ParticleAnime *anime = animeList->getObjectAtIndex( i );
        
        if( anime->getIsStart() ) continue;
        if( anime->getAnimeID() != anime_id ) continue;
        if( anime->getAnimeX() != x ) continue;
        if( anime->getAnimeY() != y ) continue;
        if( anime->getWaitFrame() != wait ) continue;
        
        return true;
    }
    
    return false;
}
