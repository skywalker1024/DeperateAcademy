//
//  SQLiteManager.h
//  CrossKaiser
//
//  Created by tangyue on 13-2-18.
//
//

#ifndef __CrossKaiser__SQLiteManager__
#define __CrossKaiser__SQLiteManager__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "sqlite3.h"

using namespace cocos2d;
using namespace cocos2d::extension;


class SQLiteManager {
private:
    SQLiteManager();
    ~SQLiteManager();
    
    static SQLiteManager *_instance;
    
    sqlite3 *m_p_db;//数据库指针
    char *m_err_msg;//错误信息
    std::string m_sql;//SQL指令
    int m_result;//sqlite3_exec返回值
    std::string dbPath;
    void init();
    
public:
    static SQLiteManager* sharedInstance();
    bool open_db();
    void close_db();
    bool execute_sql(
                     const char *zSql,           /* The SQL to be executed */
                     sqlite3_callback xCallback, /* Invoke this callback routine */
                     void *pArg                  /* First argument to xCallback() */
                     );
    sqlite3* getDB();
    CCArray* selectRows(const char *strSql);
    CCDictionary* selectSingleRow(const char *strSql);
    CCDictionary* selectDictionary(std::string strSql, std::string columnName);
    CCDictionary* selectDictionaryMultiRows(std::string strSql, std::string columnName);
};

#endif /* defined(__CrossKaiser__SQLiteManager__) */
