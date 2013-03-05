#ifndef CVOSTABLE_H
#define CVOSTABLE_H

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  ファイル名          CVosTable.h                                          //
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
#include "CVosLock.h"
#include "IVosArena.h"
#include "CVosCache.h"
#include "CChangeSetList.h"
#include <string>
#include <pqxx/pqxx>


namespace libvosdb {

//--------------------------------------------------------------------------//
//--------------------------- Constant Definition --------------------------//
//--------------------------------------------------------------------------//


//--------------------------------------------------------------------------//
//-------------------------- Data Type Definition --------------------------//
//--------------------------------------------------------------------------//


//--------------------------------------------------------------------------//
//--------------------------- Class Declaration ----------------------------//
//--------------------------------------------------------------------------//

/// @brief データベース接続／共有メモリ管理
///
/// @ingroup interface
/// @since 1.000
class CVosTable {
public:

        /// @name インスタンス管理
        /// @{ 

        /// @brief シングルトンのインスタンスを返す
        ///
        /// @return インスタンスへのポインタ
        /// 
        /// メインスレッド唯一の当クラスインスタンスを取得
        static CVosTable* getInstance() throw();

        /// @brief シングルトンのインスタンスを破棄する
        /// 
        /// メインスレッド唯一の当クラスインスタンスを解放
        static void destroyInstance() throw();

        /// @}


        /// @name トランザクション管理
        /// @{

        /// @brief トランザクション開始
        ///
        /// @param[in] lock トランザクション中にセマフォロックする場合は
        ///                 true を指定する。
        ///                 最も外側の begin(bool) でのみ有効
        /// @return 成功した場合は空文字列、
        ///         失敗した場合はエラー内容を表す文字列
        /// @since 3.000
        /// 
        /// データベーストランザクションを開始する
        std::string begin(bool lock) throw();

        /// @brief トランザクション開始
        ///
        /// @return 成功した場合は空文字列、
        ///         失敗した場合はエラー内容を表す文字列
        ///
        /// データベーストランザクションを開始する
        std::string begin() throw();

        /// @brief コミット
        /// 
        /// @return 成功した場合は空文字列、
        ///         失敗した場合はエラー内容を表す文字列
        /// @pre 入れ子のトランザクションで rollback() していないこと
        ///
        /// データベーストランザクションを確定する
        std::string commit() throw();

        /// @brief ロールバック
        /// 
        /// @return 成功した場合は空文字列、
        ///         失敗した場合はエラー内容を表す文字列
        ///
        /// データベーストランザクションを取り消しする
        std::string rollback() throw();

        /// @brief データベース接続を取得する
        ///
        /// @return データベース接続
        pqxx::connection* getDbHandle() throw();

        /// @}


        /// @name 設定変更管理
        /// @{

        /// @brief 設定値の変更状態を返す
        ///
        /// @return 変更であれば true を返す
        /// @since 3.000
        bool isChanging() const throw();

        /// @brief 設定変更を開始する
        ///
        /// @param[in] edit 変更が編集によるものであれば true を指定する
        /// @since 3.000
        void startChange(bool edit) throw();

        /// @brief 設定変更を開始する
        ///
        /// @since 3.000
        void startChange() throw();

        /// @brief 設定変更を終了する
        ///
        /// @param[in] ok 変更が成功している場合に true を指定する
        /// @since 3.000
        void endChange(bool ok) throw();

        /// @}


        /// @name セマフォによるロックの管理
        /// @{

        /// @brief ロックを獲得する
        /// 
        /// @return 成功した場合は空文字列、
        ///         失敗した場合はエラー内容を表す文字列
        /// @see CVosLock::lock()
        /// @since 3.000
        std::string lock() throw();

        /// @brief ロック獲得を試みる
        ///
        /// @param[out] ok ロックを獲得できた場合に true を返す
        /// 
        /// @return 成功した場合は空文字列、
        ///         失敗した場合はエラー内容を表す文字列
        /// @see CVosLock::try_lock()
        /// @since 3.000
        std::string tryLock(bool& ok) throw();

        /// @brief ロックを解放する
        /// 
        /// @return 成功した場合は空文字列、
        ///         失敗した場合はエラー内容を表す文字列
        /// @see CVosLock::unlock()
        /// @since 3.000
        std::string unlock() throw();

        /// @}

        /// @brief 共有メモリキャッシュを取得する
        ///
        /// @return 共有メモりキャッシュ
        const CVosCache& getCache() const throw();

        /// @brief 変更セットリストを取得する
        ///
        /// @return 変更セットリスト
        const CChangeSetList& getChangeSetList() const throw();


        /// @brief トランザクション
        pqxx::work* m_Trans;

        /// @brief 要求元プロセス番号
        SI_32 m_RequestProcess;

private:
        /// @brief コンストラクタ
        ///
        /// @param[in] connstr DB接続パラメータ文字列
        /// @throw std::exception 初期化に失敗した
        explicit CVosTable(const std::string& connstr) throw(std::exception);

        /// @brief デストラクタ
        ///
        /// @warning 未定義につき使用禁止
        virtual ~CVosTable() throw();

        /// @brief デフォルトコンストラクタ
        CVosTable() throw();

        /// @brief コピーコンストラクタ
        ///
        /// @param[in] o コピー元
        /// @warning 未定義につき使用禁止
        CVosTable(const CVosTable& o) throw();

        /// @brief 代入演算子
        ///
        /// @param[in] o コピー元
        /// @return 自身へのポインタ
        /// @warning 未定義につき使用禁止
        CVosTable& operator=(const CVosTable& o) throw();


        /// @brief 設定値の変更を共有メモリキャッシュに確定する
        ///
        /// @throw std::exception 共有メモリキャッシュへの反映に失敗した
        void commitToShm() throw(std::exception);

        /// @brief シングルトンインスタンス
        /// 
        /// メインスレッド唯一の当クラスインスタンス
        static CVosTable* m_Instance;

        /// @brief データベース接続
        pqxx::connection* m_DbHandle;

        /// @name トランザクションの入れ子管理
        /// @{
        UI_32 m_AdmTrans;       ///< @brief トランザクションの入れ子段数
        bool m_TransFailed;     ///< @brief 既に rollback() した場合は true
        /// @}

        /// @name 設定値変更の入れ子管理
        /// @{
        UI_32 m_AdmChange;      ///< @brief 設定値変更の入れ子段数
        bool m_ChangeFailed;    ///< @brief 既に変更失敗した場合は true
        /// @}

        /// @brief ロック状態
        ///
        /// トランザクション開始にてロック獲得を行った場合に true
        bool m_GetLock;


        /// @brief セマフォによるロック機構
        CVosLock* m_Lock;

        /// @brief 共有メモリインタフェース
        IVosArena* m_Shm;

        /// @brief 共有メモリレイアウト
        CVosMemoryLayout* m_Layout;

        /// @brief 共有メモリキャッシュ
        CVosCache* m_Cache;

        /// @brief 未保存の変更セットリスト
        CChangeSetList* m_Change;

        /// @brief 保存済の変更セットリスト
        ///
        /// 保存のためのSQLを発行したが、トランザクションが
        /// コミットされていない変更を持つ。\n
        /// ロールバックした場合は、一旦 m_Change に戻される
        CChangeSetList* m_SavedChange;

        /// @brief 現在の変更セット
        ///
        /// 設定変更開始で作成され、設定変更終了（成功）で m_Change
        /// に追加される
        CChangeSet* m_CurrentChange;


        friend class CVosSettingTable;
        friend class CVosMonitorTable;
        friend class CMonitorControl;
};


} // namespace libvosdb

#endif // CVOSTABLE_H

// Local Variables:
// mode: c++
// End:

//---------------------- End of CVosTable.h ---------------------------------//
