//
//  GameConst.h
//  SampleGame2
//
//  Created by 杉山 浩 on 12/03/21.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BraveFrontier_GameConst_h
#define BraveFrontier_GameConst_h

////////////////////////////////
// テキストALIGN
static const int TEXT_ALIGN_LEFT_TOP        = 1;
static const int TEXT_ALIGN_CENTER_TOP      = 2;
static const int TEXT_ALIGN_RIGHT_TOP       = 3;

static const int TEXT_ALIGN_LEFT_MIDDLE     = 4;
static const int TEXT_ALIGN_CENTER_MIDDLE   = 5;
static const int TEXT_ALIGN_RIGHT_MIDDLE    = 6;

static const int TEXT_ALIGN_LEFT_BOTTOM     = 7;
static const int TEXT_ALIGN_CENTER_BOTTOM   = 8;
static const int TEXT_ALIGN_RIGHT_BOTTOM    = 9;


static const char* const DEFAULT_FONT_NAME  =  "DFHEI5A.ttf";

static const int GAME_CANVAS_WIDTH  = 320;
static const int GAME_CANVAS_HEIGHT = 480;

// 色設定
static const char* const COLOR_KEY_LV    = "LV_LABEL";
static const char* const COLOR_KEY_HP    = "HP_LABEL";
static const char* const COLOR_KEY_ATK   = "ATK_LABEL";
static const char* const COLOR_KEY_DEF   = "DEF_LABEL";
static const char* const COLOR_KEY_HEAL  = "HEAL_LABEL";
static const char* const COLOR_KEY_BBLV  = "BBLV_LABEL";
static const char* const COLOR_KEY_COST  = "COST_LABEL";
static const char* const COLOR_KEY_GOLD  = "GOLD_LABEL";
static const char* const COLOR_KEY_WHITE = "WHITE_LABEL";
static const char* const COLOR_KEY_RED   = "RED_LABEL";
static const char* const COLOR_KEY_INFO  = "INFO_LABEL";

const int DIALOG_BUTTON_PRIORITY = -138;// kCCMenuHandlerPriority - 10;
static const int RECOVER_TIME = 180;

////////////////////////////////
// 課金端末定義
static const int PURCHASE_MODEL_STATUS_START_CONN_BEFORE = 0;
static const int PURCHASE_MODEL_STATUS_START_CONN_AFTER = 1;
static const int PURCHASE_MODEL_STATUS_PRODUCT_CHECK_BEFORE = 2;
static const int PURCHASE_MODEL_STATUS_PRODUCT_CHECK_AFTER = 3;
static const int PURCHASE_MODEL_STATUS_PRODUCT_STORE_KIT_PUSH_AFTER = 4;
static const int PURCHASE_MODEL_STATUS_PRODUCT_STORE_KIT_RECIEVE = 5;

////////////////////////////////
// 有効、無効
static const int INVALID    = 0;
static const int VALID      = 1;
static const int BOTH       = -1;

////////////////////////////////
// 課金処理定義
static const int PURCHASE_STATE_START = 0;
static const int PURCHASE_STATE_CANCEL = 1;
static const int PURCHASE_STATE_COMPLETE = 2;
static const int PURCHASE_STATE_RECEIPT_NG = 3;
static const int PURCHASE_STATE_GIVEUP = 4;
static const int PURCHASE_STATE_ALREADY = 5;
static const int PURCHASE_STATE_DEFERRED = 6;

#endif
