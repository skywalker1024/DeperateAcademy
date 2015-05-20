//
//  PurchaseMst.cpp
//  BraveFrontier

//  Created by WillArk on 5/24/12.
//  Copyright (c) 2012 WillArk. All rights reserved.
//

#include "PurchaseMst.h"

/*
 * コンストラクタ。
 */
PurchaseMst::PurchaseMst()
{
    m_id = 0;
    m_name = "";
    m_productId = "";
    m_amount = 0;
    m_diamond = 0;
    m_description = "";
}

/*
 * デストラクタ。
 */
PurchaseMst::~PurchaseMst()
{

}

void PurchaseMst::initWithArray(CCDictionary * list){
    
    m_id = dynamic_cast<CCString*>(list->objectForKey("id"))->intValue();
    m_name = dynamic_cast<CCString*>(list->objectForKey("name"))->m_sString;
    m_productId = dynamic_cast<CCString*>(list->objectForKey("product_id"))->m_sString;
    m_amount = dynamic_cast<CCString*>(list->objectForKey("amount"))->intValue();
    m_diamond = dynamic_cast<CCString*>(list->objectForKey("diamond"))->intValue();
    m_description = dynamic_cast<CCString*>(list->objectForKey("description"))->m_sString;
}


