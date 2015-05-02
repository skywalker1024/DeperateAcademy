//
//  SQLiteManager.cpp
//  CrossKaiser
//
//  Created by tangyue on 13-2-18.
//
//

#include "SQLiteManager.h"
SQLiteManager *SQLiteManager::_instance = NULL;

SQLiteManager::SQLiteManager():
m_p_db(NULL),
m_err_msg(NULL)
{
    dbPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("sqlite/sanguo.db");
    CCLog("dbPath=%s", dbPath.c_str());
}

SQLiteManager::~SQLiteManager()
{
    m_p_db = NULL;
    m_err_msg = NULL;
}

SQLiteManager* SQLiteManager::sharedInstance()
{
    if (_instance == NULL)
    {
        _instance = new SQLiteManager();
    }
    return _instance;
}

sqlite3* SQLiteManager::getDB(){
    if(!open_db())
        return NULL;
    return m_p_db;
}

bool SQLiteManager::execute_sql(const char *zSql,sqlite3_callback xCallback,void *pArg)
{
    if(!open_db())
        return false;
    
    m_result = sqlite3_exec(m_p_db, zSql, xCallback, pArg, &m_err_msg);
    if( m_result != SQLITE_OK ){
        CCLOG( "执行失败，错误码:%d ，错误原因:%s\n" , m_result, m_err_msg );
        close_db();
        return false;
    }
    close_db();
    return true;
}

bool SQLiteManager::open_db(){
    //打开一个数据库，如果该数据库不存在，则创建一个数据库文件
//    m_result = sqlite3_open_v2(dbPath.c_str(), &m_p_db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
    //CCLOG("open db: %s", dbPath.c_str());
    m_result = sqlite3_open(dbPath.c_str(), &m_p_db);
    
    if( m_result != SQLITE_OK ){
        CCLOG( "打开数据库失败，错误码:%d ，错误原因:%s\n" , m_result, m_err_msg );
        return false;
    }
    else
    {
#ifdef SQLITE_HAS_CODEC
        sqlite3_key(m_p_db, Utilities::XXTEA_Encrypt_Decrypt(DB_SECRET_KEY, false).c_str(), strlen(Utilities::XXTEA_Encrypt_Decrypt(DB_SECRET_KEY, false).c_str()));
#endif
        return true;
    }

}

void SQLiteManager::close_db(){
    sqlite3_close(m_p_db);
}
CCDictionary* SQLiteManager::selectDictionary(std::string strSql, std::string columnName){
    if(!open_db())
        return NULL;
    char **pszResult = 0;
    int nRow = 0;
    int nColumn = 0;
    int rc = sqlite3_get_table(m_p_db, strSql.c_str(), &pszResult, &nRow, &nColumn, &m_err_msg);
    CCDictionary *result = CCDictionary::create();
    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error " << m_err_msg << std::endl;
        m_err_msg = NULL;
    }else{
        CCArray *columnKeyAry = CCArray::create();
        for (int i = 0; i <= nRow; i++)
        {
            if (i==0) {
                //获取列名
                for (int j = 0; j < nColumn; j++)
                {
                    CCString *columnKey =  CCString::create(*(pszResult + j));
                    columnKeyAry->addObject(columnKey);
                }
            }else{
                //存储每行记录
                CCDictionary *row = CCDictionary::create();
                std::string dicKey;
                for (int j = 0; j < nColumn; j++)
                {
                    std::string columnKey = ((CCString *) columnKeyAry->objectAtIndex(j))->getCString();
                    
                    CCString * columnValue;
                    if (*(pszResult + nColumn * i + j) == NULL) {
                        columnValue = CCString::create("");
                    }else{
                        columnValue =  CCString::create(*(pszResult + nColumn * i + j));
                    }
                    //CCLOG(columnValue->getCString());
                    row->setObject(columnValue, columnKey);
                    if (columnKey == columnName) {
                        dicKey = columnValue->getCString();
                    }
                }
                if (dicKey != "") {
                    result->setObject(row, dicKey);
                }
            }
        }
    }
    sqlite3_free_table(pszResult);
    close_db();
    return result;
}
CCDictionary* SQLiteManager::selectDictionaryMultiRows(std::string strSql, std::string columnName){
    if(!open_db())
        return NULL;
    char **pszResult = 0;
    int nRow = 0;
    int nColumn = 0;
    int rc = sqlite3_get_table(m_p_db, strSql.c_str(), &pszResult, &nRow, &nColumn, &m_err_msg);
    CCDictionary *result = CCDictionary::create();
    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error " << m_err_msg << std::endl;
        m_err_msg = NULL;
    }else{
        CCArray *columnKeyAry = CCArray::create();
        for (int i = 0; i <= nRow; i++)
        {
            if (i==0) {
                //获取列名
                for (int j = 0; j < nColumn; j++)
                {
                    CCString *columnKey =  CCString::create(*(pszResult + j));
                    columnKeyAry->addObject(columnKey);
                }
            }else{
                //存储每行记录
                CCDictionary *row = CCDictionary::create();
                CCArray *rowAry;
                std::string dicKey;
                for (int j = 0; j < nColumn; j++)
                {
                    std::string columnKey = ((CCString *) columnKeyAry->objectAtIndex(j))->getCString();
                    
                    CCString * columnValue;
                    if (*(pszResult + nColumn * i + j) == NULL) {
                        columnValue = CCString::create("");
                    }else{
                        columnValue =  CCString::create(*(pszResult + nColumn * i + j));
                    }
                    //CCLOG(columnValue->getCString());
                    row->setObject(columnValue, columnKey);
                    if (columnKey == columnName) {
                        dicKey = columnValue->getCString();
                    }
                }
                rowAry = (CCArray*)result->objectForKey(dicKey);
                if (rowAry) {
                    rowAry->addObject(row);
                }else{
                    rowAry = CCArray::create();
                    rowAry->addObject(row);
                }
                if (dicKey != "") {
                    result->setObject(rowAry, dicKey);
                }
            }
        }
    }
    sqlite3_free_table(pszResult);
    close_db();
    return result;
}
CCArray* SQLiteManager::selectRows(const char *strSql){
    if(!open_db())
        return NULL;
    char **pszResult = 0;
    int nRow = 0;
    int nColumn = 0;
    int rc = sqlite3_get_table(m_p_db, strSql, &pszResult, &nRow, &nColumn, &m_err_msg);
    CCArray *result = CCArray::create();
    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error " << m_err_msg << std::endl;
        m_err_msg = NULL;
    }else{
        CCArray *columnKeyAry = CCArray::create();
        for (int i = 0; i <= nRow; i++)
        {
            if (i==0) {
                //获取列名
                for (int j = 0; j < nColumn; j++)
                {
                    CCString *columnKey =  CCString::create(*(pszResult + j));
                    columnKeyAry->addObject(columnKey);
                }
            }else{
                //存储每行记录
                CCDictionary *row = CCDictionary::create();
                for (int j = 0; j < nColumn; j++)
                {
                    const char *columnKey = ((CCString *) columnKeyAry->objectAtIndex(j))->getCString();
                    
                    CCString * columnValue;
                    if (*(pszResult + nColumn * i + j) == NULL) {
                        columnValue = CCString::create("");
                    }else{
                        columnValue =  CCString::create(*(pszResult + nColumn * i + j));
                    }
                    //CCLOG(columnValue->getCString());
                    row->setObject(columnValue, columnKey);
                }
                result->addObject(row);
            }
        }
    }
    sqlite3_free_table(pszResult);
    close_db();
    return result;
}
CCDictionary* SQLiteManager::selectSingleRow(const char *strSql){
    if(!open_db()) {
        CCLOG("selectSingleRow: cannot open db");
        return NULL;
    }
    char **pszResult = 0;
    int nRow = 0;
    int nColumn = 0;
    int rc = sqlite3_get_table(m_p_db, strSql, &pszResult, &nRow, &nColumn, &m_err_msg);
    CCDictionary *row = CCDictionary::create();
    if (rc != SQLITE_OK)
    {
        CCLOG("SQL error: %s", m_err_msg);
        m_err_msg = NULL;
    }else{
        CCArray *columnKeyAry = CCArray::create();
        for (int i = 0; i <= nRow; i++)
        {
            if (i==0) {
                //获取列名
                for (int j = 0; j < nColumn; j++)
                {
                    CCString *columnKey =  CCString::create(*(pszResult + j));
                    columnKeyAry->addObject(columnKey);
                }
            }else{
                //存储每行记录
                
                for (int j = 0; j < nColumn; j++)
                {
                    const char *columnKey = ((CCString *) columnKeyAry->objectAtIndex(j))->getCString();
                    
                    CCString * columnValue;
                    if (*(pszResult + nColumn * i + j) == NULL) {
                        columnValue = CCString::create("");
                    }else{
                        columnValue =  CCString::create(*(pszResult + nColumn * i + j));
                    }
                    row->setObject(columnValue, columnKey);
                    
                }
            }
        }
    }
    sqlite3_free_table(pszResult);
    sqlite3_close(m_p_db);
    return row;
}
