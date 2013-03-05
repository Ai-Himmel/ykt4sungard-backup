///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  ファイル名          CVosTable.cpp                                        //
//                                                                           //
//  概要                データベース接続のインスタンスを唯一に管理する       //
//                                                                           //
//  作成者              制御（村田機械(株)）                                 //
//                                                                           //
//  作成日              2010.01.06                                           //
//                                                                           //
//  開発環境                                                                 //
//      (OS)            2.6.14.7-WR1.5ag_cgl(Linux)                          //
//      (COMPILER)      g++ (GCC) 3.4.6  Free Software Foundation, Inc.      //
//      (MACHINE)       RHPU7100eMe-600C                                     //
//                                                                           //
//  Copyright (C) 2008 Murata Machinery,Ltd. All right reserved.             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------------//
//-------------------------- Modification History ---------------------------//
//---------------------------------------------------------------------------//
//
// |------------------------------- Ver. 1.000 -------------------------------|
// 2010.01.06 制御 OPC K.Onda
//    1.新規作成
//


//---------------------------------------------------------------------------//
//------------------------------ Include Files ------------------------------//
//---------------------------------------------------------------------------//
#include "CVosTable.h"
#include "CVosErrorLog.h"

/* shanghai */
#ifdef WIN32
	#include "CLocalMem.h"
#else
	#include "CSysVShm.h"
#endif

#include "tableinfo.h"
#include <csignal>
#include <iostream>
#include <sstream>
#include <cstdlib>


namespace libvosdb {

namespace {

/// @brief VOS3共有メモリキー
const key_t VOS_IPC_KEY = 0x22151903;

}       // anonymous namespace


// インスタンス実体
CVosTable* CVosTable::m_Instance = 0;


//---------------------------------------------------------------------------//
//------------------------ Class Member Definitions -------------------------//
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//      形式    CVosTable()                                                  //
//      機能    メインスレッド唯一のデータベース接続                         //
//      引数    無し                                                         //
//      戻り値  無し                                                         //
//---------------------------------------------------------------------------//
//      説明                                                                 //
//---------------------------------------------------------------------------//
//      作成    2009.05.27 制御（村田機械(株)）                              //
//---------------------------------------------------------------------------//
//      変更                                                                 //
//---------------------------------------------------------------------------//
CVosTable::CVosTable(const std::string& connstr) throw(std::exception)
        : m_Trans(0), m_RequestProcess(0),
          m_DbHandle(0), m_AdmTrans(0), m_TransFailed(false),
          m_AdmChange(0), m_ChangeFailed(false), m_GetLock(false),
          m_Lock(0), m_Shm(0), m_Layout(0), m_Cache(0),
          m_Change(0), m_SavedChange(0), m_CurrentChange(0)
{
        try {
                m_DbHandle = new pqxx::connection(connstr);
                m_Lock = new CVosLock(VOS_IPC_KEY);

/* shanghai */
#ifdef WIN32
                m_Shm = new CLocalMem();
#else
                m_Shm = new CSysVShm(VOS_IPC_KEY);
#endif

                m_Layout = new CVosMemoryLayout(
                        VOS_LOCAL_TABLE_INFO, VOS_LOCAL_TABLE_INFO_SIZE);
                m_Cache = new CVosCache(m_Shm, m_Layout);
                m_Change = new CChangeSetList();
                m_SavedChange = new CChangeSetList();

                m_Lock->lock();
                try {
                        pqxx::work T(*m_DbHandle);
                        m_Cache->initialize(T);
                        T.commit();
                        m_Lock->unlock();
                }
                catch (...) {
                        m_Lock->unlock();
                        throw;
                }
        }
        catch (...) {
                delete m_SavedChange;
                delete m_Change;
                delete m_Cache;
                delete m_Layout;
                delete m_Shm;
                delete m_Lock;
                delete m_DbHandle;
                throw;
        }
}

//---------------------------------------------------------------------------//
//      形式    ~CVosTable()                                                 //
//      機能    メインスレッド唯一のデータベース接続                         //
//      引数    無し                                                         //
//      戻り値  無し                                                         //
//---------------------------------------------------------------------------//
//      説明                                                                 //
//---------------------------------------------------------------------------//
//      作成    2008.11.27 制御（村田機械(株)）                              //
//---------------------------------------------------------------------------//
//      変更                                                                 //
//---------------------------------------------------------------------------//
CVosTable::~CVosTable() throw()
{
        if (0 != m_Trans) {
                if (0 < m_AdmTrans) {
                        try {
                                m_Trans->abort();
                        }
                        catch (...) {
                                // ignore all exception
                                std::cerr << LIBVOSDBERROR_HEADER;
                                std::cerr << ": failed to abort transaction";
                                std::cerr << std::endl;
                        }
                }
                delete m_Trans;
        }
        delete m_SavedChange;
        delete m_Change;
        delete m_Cache;
        delete m_Layout;
        delete m_Shm;
        if (0 != m_Lock) {
                if (0 < m_AdmTrans) {
                        try {
                                m_Lock->unlock();
                        }
                        catch (...) {
                                // ignore all exception
                                std::cerr << LIBVOSDBERROR_HEADER;
                                std::cerr << ": failed to unlock";
                                std::cerr << std::endl;
                        }
                }
                delete m_Lock;
        }
        delete m_DbHandle;
}

//---------------------------------------------------------------------------//
//      形式    CVosTable* getInstance()                                     //
//      機能    メインスレッド唯一の当クラスインスタンスを取得               //
//      引数    無し                                                         //
//      戻り値  当クラスインスタンス                                         //
//---------------------------------------------------------------------------//
//      説明                                                                 //
//---------------------------------------------------------------------------//
//      作成    2009.11.21 制御（村田機械(株)）                              //
//---------------------------------------------------------------------------//
//      変更                                                                 //
//---------------------------------------------------------------------------//
CVosTable* CVosTable::getInstance() throw()
{
#ifndef WIN32
        std::signal(SIGPIPE, SIG_IGN);
#endif

        if (0 != m_Instance) {
                return m_Instance;
        }

        try {
                // データベース接続文字列を生成する
                std::stringstream dbCon;

                const char* envPgDatabase = std::getenv("PGDATABASE");
                if (0 == envPgDatabase) {
                        dbCon << "dbname=vos";
                }
#ifdef WIN32
                dbCon.str("");
#if defined(VOS_MACHINE_AW_TYPE)
                dbCon << "host=localhost dbname=aw_vos port=5432 user=root password=muratec";
#elif defined(VOS_MACHINE_MS_TYPE)
/* shanghai */
                //dbCon << "host=localhost dbname=ms_vos port=5432 user=root password=muratec" );
				dbCon << "host=localhost dbname=ms_vos port=5432 user=root password=muratec";
#else
#error "Donnot Support Vos Machine Type"
#endif
#endif

                // メインスレッド唯一の当クラスインスタンス
                m_Instance = new CVosTable(dbCon.str());

                // 送信元プロセス番号を設定
                // export VOS_PROCESS_ID = 0x????
                const char* env = std::getenv("VOS_PROCESS_ID");
                if (0 != env) {
                        m_Instance->m_RequestProcess = std::strtol(env, 0, 0);
                }
        }
        catch (const std::exception &e) {
                std::cerr << LIBVOSDBERROR_HEADER;
                std::cerr << ": Exception: " << e.what() << std::endl;
                return 0;
        }
        catch (...) {
                std::cerr << LIBVOSDBERROR_HEADER;
                std::cerr << ": Uknown exception" << std::endl;
                return 0;
        }
        return m_Instance;
}

//---------------------------------------------------------------------------//
//      形式    void destroyInstance()                                       //
//      機能    メインスレッド唯一の当クラスインスタンスを解放               //
//      引数    無し                                                         //
//      戻り値  無し                                                         //
//---------------------------------------------------------------------------//
//      説明                                                                 //
//---------------------------------------------------------------------------//
//      作成    2008.11.27 制御（村田機械(株)）                              //
//---------------------------------------------------------------------------//
//      変更                                                                 //
//---------------------------------------------------------------------------//
void CVosTable::destroyInstance() throw()
{
        // メインスレッド唯一の当クラスインスタンス
        delete m_Instance;
        m_Instance = 0;
}

//---------------------------------------------------------------------------//
//      形式    string begin(bool lock)                                      //
//      機能    データベーストランザクションを開始する                       //
//      引数    lock trueならトランザクション中は共有メモリロックする        //
//      戻り値  empty()：成功                                                //
//             !empty()：失敗                                                //
//---------------------------------------------------------------------------//
//      説明                                                                 //
//---------------------------------------------------------------------------//
//      作成    2010.01.06 制御（村田機械(株)）                              //
//---------------------------------------------------------------------------//
//      変更                                                                 //
//---------------------------------------------------------------------------//
std::string CVosTable::begin(bool lock) throw()
{
        std::stringstream sts;

        try {
                if (0 == m_Trans) {
                        if (lock) {
                                m_Lock->lock();
                                m_GetLock = true;
                        }
                        else {
                                m_GetLock = false;
                        }
                        try {
                                m_Trans = new pqxx::work(*m_DbHandle);
                        }
                        catch (...) {
                                m_Lock->unlock();
                                m_GetLock = false;
                                throw;
                        }
                }
                ++m_AdmTrans;
                m_TransFailed = false;
        }
        catch (const std::exception& e) {
                sts << LIBVOSDBERROR_HEADER;
                sts << ": Exception: " << e.what();
                std::cerr << sts.str() << std::endl;
        }
        catch (...) {
                sts << LIBVOSDBERROR_HEADER;
                sts << ": Unknown exception";
                std::cerr << sts.str() << std::endl;
        }
        return sts.str();
}

//---------------------------------------------------------------------------//
//      形式    string begin()                                               //
//      機能    データベーストランザクションを開始する                       //
//      引数    無し                                                         //
//      戻り値  empty()：成功                                                //
//             !empty()：失敗                                                //
//---------------------------------------------------------------------------//
//      説明                                                                 //
//---------------------------------------------------------------------------//
//      作成    2010.01.06 制御（村田機械(株)）                              //
//---------------------------------------------------------------------------//
//      変更                                                                 //
//---------------------------------------------------------------------------//
std::string CVosTable::begin() throw()
{
        return begin(true);
}

//---------------------------------------------------------------------------//
//      形式    string commit()                                              //
//      機能    データベーストランザクションを確定する                       //
//      引数    無し                                                         //
//      戻り値  empty()：成功                                                //
//             !empty()：失敗                                                //
//---------------------------------------------------------------------------//
//      説明                                                                 //
//---------------------------------------------------------------------------//
//      作成    2009.09.17 制御（村田機械(株)）                              //
//---------------------------------------------------------------------------//
//      変更                                                                 //
//---------------------------------------------------------------------------//
std::string CVosTable::commit() throw()
{
        std::stringstream sts;

        if (m_TransFailed) {
                sts << LIBVOSDBERROR_HEADER;
                sts << ": try to commit a transaction already failed";
                std::cerr << sts.str() << std::endl;
                return sts.str();
        }

        try {
                if (0 < m_AdmTrans) {
                        if (1 == m_AdmTrans) {
                                m_Trans->commit();
                                delete m_Trans;
                                m_Trans = 0;
                                commitToShm();
                                m_Shm->sync();
                                m_SavedChange->clear();
                                if (m_GetLock) {
                                        m_Lock->unlock();
                                }
                        }
                        --m_AdmTrans;
                }
        }
        catch (const std::exception& e) {
                sts << LIBVOSDBERROR_HEADER;
                sts << ": Exception: " << e.what();
                std::cerr << sts.str() << std::endl;
        }
        catch (...) {
                sts << LIBVOSDBERROR_HEADER;
                sts << ": Unknown exception";
                std::cerr << sts.str() << std::endl;
        }
        return sts.str();
}

//---------------------------------------------------------------------------//
//      形式    string rollback()                                            //
//      機能    データベーストランザクションを取消しする                     //
//      引数    無し                                                         //
//      戻り値  empty()：成功                                                //
//             !empty()：失敗                                                //
//---------------------------------------------------------------------------//
//      説明                                                                 //
//---------------------------------------------------------------------------//
//      作成    2010.01.06 制御（村田機械(株)）                              //
//---------------------------------------------------------------------------//
//      変更                                                                 //
//---------------------------------------------------------------------------//
std::string CVosTable::rollback() throw()
{
        std::stringstream sts;

        m_TransFailed = true;
        try {
                if (0 < m_AdmTrans) {
                        --m_AdmTrans;
                        if (0 == m_AdmTrans) {
                                // reset saves
                                m_Change->spliceToOld(*m_SavedChange);
                                try {
                                        if (0 != m_Trans) {
                                                m_Trans->abort();
                                        }
                                }
                                catch (...) {
                                        // ignore
                                        std::cerr << LIBVOSDBERROR_HEADER;
                                        std::cerr << ": failed to rollback";
                                        std::cerr << std::endl;
                                }
                                delete m_Trans;
                                m_Trans = 0;
                        }
                        if (m_GetLock) {
                                m_Lock->unlock();
                        }
                }
        }
        catch (const std::exception& e) {
                sts << LIBVOSDBERROR_HEADER;
                sts << ": Exception: " << e.what();
                std::cerr << sts.str() << std::endl;
        }
        catch (...) {
                sts << LIBVOSDBERROR_HEADER;
                sts << ": Unknown exception";
                std::cerr << sts.str() << std::endl;
        }
        return sts.str();
}


//---------------------------------------------------------------------------//
//      形式    connection* getDbHandle()                                    //
//      機能    データベース接続子取得                                       //
//      引数    無し                                                         //
//      戻り値  0より大きい：成功                                            //
//                      0以下：失敗                                          //
//---------------------------------------------------------------------------//
//      説明                                                                 //
//---------------------------------------------------------------------------//
//      作成    2008.12.12 制御（村田機械(株)）                              //
//---------------------------------------------------------------------------//
//      変更                                                                 //
//---------------------------------------------------------------------------//
pqxx::connection* CVosTable::getDbHandle() throw()
{
        return m_DbHandle;
}

bool CVosTable::isChanging() const throw()
{
        return 0 != m_CurrentChange;
}

void CVosTable::startChange(bool edit) throw()
{
        if (0 < m_AdmChange) {
                ++m_AdmChange;
        }
        else {
                if (0 != m_CurrentChange) {
                        std::cerr << LIBVOSDBERROR_HEADER;
                        std::cerr << ": WARNING: invalid calc status";
                        std::cerr << std::endl;
                        delete m_CurrentChange;
                }
                m_CurrentChange = new CChangeSet();
                m_CurrentChange->setEdit(edit);
                m_AdmChange = 1;
                m_ChangeFailed = false;
        }
}

void CVosTable::startChange() throw()
{
        startChange(true);
}

void CVosTable::endChange(bool ok) throw()
{
        if (!m_ChangeFailed) {
                m_ChangeFailed = !ok;
        }
        if (1 < m_AdmChange) {
                --m_AdmChange;
        }
        else {
                if (0 != m_CurrentChange) {
                        if (!m_ChangeFailed) {
                                m_Change->push(*m_CurrentChange);
                        }
                        delete m_CurrentChange;
                        m_CurrentChange = 0;
                }
                else {
                        std::cerr << LIBVOSDBERROR_HEADER;
                        std::cerr << ": WARNING: invalid calc status";
                        std::cerr << std::endl;
                }
                m_AdmChange = 0;
        }
}

std::string CVosTable::lock() throw()
{
        std::stringstream sts;
        try {
                m_Lock->lock();
        }
        catch (const std::exception& e) {
                sts << e.what();
        }
        return sts.str();
}

std::string CVosTable::tryLock(bool& ok) throw()
{
        std::stringstream sts;
        try {
                ok = m_Lock->try_lock();
        }
        catch (const std::exception& e) {
                sts << e.what();
        }
        return sts.str();
}

std::string CVosTable::unlock() throw()
{
        std::stringstream sts;
        try {
                m_Lock->unlock();
        }
        catch (const std::exception& e) {
                sts << e.what();
        }
        return sts.str();
}

const CVosCache& CVosTable::getCache() const throw()
{
        return *m_Cache;
}

const CChangeSetList& CVosTable::getChangeSetList() const throw()
{
        return *m_Change;
}

void CVosTable::commitToShm() throw(std::exception)
{
        std::set<CCacheItemReference> chgs;
        m_SavedChange->getChangeSet(chgs);
        for (std::set<CCacheItemReference>::const_iterator p = chgs.begin();
             p != chgs.end();
             ++p) {
                SettingValue* oldval = m_Cache->findSettingValue(
                        p->m_Table, p->m_Index, p->m_Item);
                const SettingValue* newval = m_SavedChange->getChange(*p);
                if ((0 != oldval) && (0 != newval)) {
                        *oldval = *newval;
                }
                else {
                        std::cerr << LIBVOSDBERROR_HEADER;
                        std::cerr << ": invalid pointer ";
                        std::cerr << " OLD=" << oldval;
                        std::cerr << " NEW=" << newval;
                        std::cerr << std::endl;
                }
        }
}

} // namespace libvosdb

// Local Variables:
// mode: c++
// End:

//---------------------- End of CVosTable.cpp -------------------------------//
