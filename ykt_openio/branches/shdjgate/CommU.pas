unit CommU;

interface

uses SysUtils, Messages, StdCtrls, Classes, Controls, Forms, Windows, Ora, MemDS, DB, Dialogs,
    DBAccess, SQLiteTable3,
{$IFDEF VER210}
    AES2010,
{$ELSE}
    AES,
{$ENDIF}
    IniFiles;

const
    WM_RELEASEDLL = WM_USER + 101;
    SP = '~~';
    // ORACLE连接字符串

    CONFIGFILE = 'config.ini';
    LOGINFILE = 'picture\Login.bmp';
    USERCODEFILE = 'usercode.ini';

type
    LOOPPURSEINFO = packed record
        RemainMoney: DWORD; // 电子钱包余额
        DealTimes: WORD; // 用户卡交易流水号
        DealYear: BYTE; // 交易日期
        DealMonth: BYTE;
        DealDay: BYTE;
        DealHour: BYTE;
        DealMin: BYTE;
        DealTimes_CurTime: BYTE; // 累计交易次数(当前时间段内)
        DealTimes_CurDay: BYTE; // 累计交易次数(当日内)
    end;

type
    TCardInfo = packed record
        DeadLineDate: array [1 .. 9] of char; // 用户卡使用截止日期
        CardRightType: longint; // 用户卡使用权限类型（1--254）
        ucName: array [1 .. 9] of char; // 姓名
        ucDutyNo: array [1 .. 9] of char; // 职务代码
        ucCertificateNo: array [1 .. 21] of char; // 证件号码
        ucDepartmentNo: array [1 .. 11] of char; // 部门编号
        ucIdentifyNo: array [1 .. 21] of char; // 身份代码
        ucSexNo: array [1 .. 2] of char; // 性别代码
        ucCardNo: array [1 .. 21] of char; // 卡号（工号或学号）
    end;

type
    TRunDllFun = function(AFile, AStr: PChar; i, x, y, mode: integer): integer; stdcall;

    TProductZS = record
        ID: string; // 产品代码
        Name: string; // 产品名称
        Count: Double; // 送货数量
    end;

    TPeople = record
        sOperatorCode: string;
        sOperatorName: string;
        sBusinessCode: string;
        sBusinessName: string;
        sManagerCode: string;
        sManagerName: string;
        sCheckerCode: string;
        sCheckerName: string;
        sSenderCode: string;
        sSenderName: string;
        sTesterCode: string;
        sTesterName: string;
    end;

    TPublishCardMes = packed record
        ShowCardNo: array [1 .. 11] of char; // 用户卡显示卡号
        CardNo: array [1 .. 8] of char; // 用户卡交易卡号
        DeadLineDate: array [1 .. 9] of char; // 用户卡使用截止日期
        CardRightType: longint; // 权限类型（1--254）收费类别
        ucName: array [1 .. 9] of char; // 姓名
        ucDutyNo: array [1 .. 9] of char; // 职务代码
        ucCertificateNo: array [1 .. 21] of char; // 身份证号码
        ucDepartmentNo: array [1 .. 11] of char; // 单位编号
        ucIdentifyNo: array [1 .. 5] of char; // 客户类别
        ucSexNo: array [1 .. 2] of char; // 性别代码
        ucCardNo: array [1 .. 21] of char; // 工号或学号
        ucPwd: array [1 .. 6] of char; // 密码
        ucLibraryNo: array [1 .. 21] of char; // 图书证号
        Money: longint; // 金额（分）
        isFormat: char; // 是否格式化第一扇区
    end;

    PDBConn = ^TOraSession;
    PUser = ^TUserInfo;

    // 子模块信息定义
    TSubMenu = record
        Caption: string; // 子模块名称
        ID: string; // 子模块ID
        DLL: string; // 子模块DLL名
        isVisble: boolean; // 是否显示，默认FALSE，即不显示
        isWeb: boolean; // 是否WEB方式
    end;

    // 父模块信息定义
    TMenu = record
        Caption: string; // 父模块名
        ID: string; // 父模块ID
        isValid: boolean; // 子模块是否有效,默认FALSE即无效
        isWeb: boolean; // 父模块是否为WEB方式
        SubMenu: array of TSubMenu; // 对应的子模块
    end;

    // 用户信息定义
    TUserInfo = class(TObject)
    private
        UserName: string; // 用户名
        Password: string; // 密码
        CNName: string; // 中文姓名
    protected

    public
        // 用户对应的模块列表
        MenuList: array of TMenu;

        function funcGetMenuList: boolean;
        // 获取用户名
        function GetUserName(): string;
        // 获取密码
        function GetPassword(): string;
        // 获取中文名
        function GetCNName(): string;
        constructor Create(AName, APwd: string);
    end;

var
    // OraSession1: TOraSession;
    // OraQuery1: TOraQuery;
    // 数据库相关变量
    DBConn: TOraSession;
    PtConn: PDBConn; // DLL模块中使用
    DBQuery, DBQueryTmp, DBQueryBaK: TOraQuery;
    DEVPHYID, dllstr, DBSOURCE, DBUser, DBPASS, DBIP, port, DBCONNSTR: string;
    baud, posport: integer;
    dllnamelist: Tstringlist;
    menunamelist: Tstringlist;
    // CurrUserName:string;
    // 用户信息
    User: TUserInfo;
    PtUser: PUser; // DLL模块中使用
    usename: string;
    debug: string;
    voice: string;
    updatetime: integer;
    // 打印相关
    PrintName: string; // 打印机名称
    PrintIndex: integer; // 当前打印机序号
    Orient: integer; // 打印方向
    x, y: integer; // X方向调整值，Y方向调整值
    ORA_CONNECT_STRING: string;
    oldphicd: string;
    // slDBpath: string;
    // sldb: TSQLiteDatabase;

    g_begintime: string;
    g_endtime: string;

function encryConfigFile(filename: string): boolean;

function FuncShowMessage(hdl: HWND; StrMsg: string; IntMsgType: integer): integer;
// 获取应用程序路径
function GetAppPath: string;
// 连接数据库
function funcConnectDB(): boolean; overload;
function funcConnectDB(Pt: PDBConn): boolean; overload;
// 查询SQL
function funcSelectSql(ASql: string; AQuery: TOraQuery; PtEnable: boolean = true): boolean;
// 利用param来查询SQL
function funcSelectSqlWithParams(AQuery: TOraQuery; PtEnable: boolean = true): boolean;

// 执行SQL
function funcExcuteSql(ASql: string; AQuery: TOraQuery; PtEnable: boolean = true): boolean;

// 利用param来执行SQL
function funcExcuteSqlForChinese(AQuery: TOraQuery; PtEnable: boolean = true): boolean;
procedure writelog(strmessage: string);
// 读取INI文件
procedure procGetIniInfo;
// 写入INI文件
procedure procWriteIniInfo();
// 获取系统目录
function funcGetSystemDir: string;
// 获取子字符串
function FuncGetSubStr(Str, AStart, AEnd: string): string;
// 由字符串得到数值
function Fun_CurrGetValue(SrcStr: string): Double;
// 由数值得到千分位字符串
function Fun_StrFormatEditValue(Curr: Double): string;
// 由输入框得到数值
function Fun_CurrGetEditValue(SrcObj: TEdit): Double;
// 输入框千分位得到标准字符串
function Fun_StrGetFloatStr(SrcStr: string): string;
// 返回转化日期
function funcConvertDate(ADate: string): TDate;
function funcFillZero(AID: string; len: integer = 10): string;
// 加1后，在字符串前填充0
function funcGetNewID(AID: string; len: integer = 10): string;
// 去除字符串中空格
function funcEraseStringSpace(AStr: string): string;

function GetNextStr(var SrcStr: string; ASPLIT: string = ','): string;
// 释放分配的数据集内存
procedure procDestroyDBSET;
// 下载客户信息
// procedure procDownloadcustomer;
// 下载时间段
// procedure procDownloadLUNCHRDATE;
// procedure procUploaddata;
// procedure procDownloaddata;
procedure saveUserCode(userCode: string);
function readUserCode(): string;

function adddlllist(dllstr: string): boolean;
function GetDelphiVer: String;

implementation

function GetDelphiVer: String;
begin
{$IFDEF VER110}
    Result := '110';
{$ENDIF}
{$IFDEF VER120}
    Result := '120';
{$ENDIF}
{$IFDEF VER130}
    Result := '130';
{$ENDIF}
{$IFDEF VER140}
    Result := '140';
{$ENDIF}
{$IFDEF VER150}
    Result := '150';
{$ENDIF}
{$IFDEF VER160}
    Result := '160';
{$ENDIF}
{$IFDEF VER170}
    Result := '170';
{$ENDIF}
{$IFDEF VER180}
    Result := '180';
{$ENDIF}
{$IFDEF VER185}
    Result := '185';
{$ENDIF}
{$IFDEF VER190}
    Result := '190';
{$ENDIF}
{$IFDEF VER200}
    Result := '200';
{$ENDIF}
{$IFDEF VER205}
    Result := '205';
{$ENDIF}
{$IFDEF VER210}
    Result := '210';
{$ENDIF}
{$IFDEF VER215}
    Result := '215';
{$ENDIF}
{$IFDEF VER220}
    Result := '220';
{$ENDIF}
end;

procedure writelog(strmessage: string);
var
    myfile: TextFile;
    // size, FileHandle: Integer;
    filename: string;
    patch: string;
    writestr: string;
begin
    patch := ExtractFilePath(ParamStr(0));
    filename := patch + 'log.txt';
    AssignFile(myfile, filename);
    try
        if FileExists(filename) then begin
            Append(myfile);
        end
        else
            ReWrite(myfile);
        writestr := FormatdateTime('yyyymmdd hhmmss', now()) + ':' + strmessage;
        Writeln(myfile, writestr);
    finally
        CloseFile(myfile);
    end;
end;

function readUserCode(): string;
var
    iniFile: TiniFile;
    sFile: string;
begin
    sFile := GetAppPath + USERCODEFILE;
    iniFile := TiniFile.Create(sFile);
    Result := '';
    try
        Result := iniFile.ReadString('usercode', 'usename', '');

    finally
        iniFile.Free;
    end;

end;

procedure saveUserCode(userCode: string);
var
    INI: TiniFile;
    sFile: string;
begin
    sFile := GetAppPath + USERCODEFILE;
    INI := TiniFile.Create(sFile);
    try
        INI.Writestring('usercode', 'usename', userCode);
    finally
        INI.Free;
    end;
end;

procedure procDestroyDBSET;
begin
    if DBQuery <> nil then
        DBQuery.Close;
    if DBQueryTmp <> nil then
        DBQueryTmp.Close;
    if DBQueryBaK <> nil then
        DBQueryBaK.Close;
end;

function GetNextStr(var SrcStr: string; ASPLIT: string = ','): string;
var
    i: integer;
begin
    Result := '';
    if SrcStr = '' then
        exit;
    i := pos(ASPLIT, SrcStr);
    if i <> 0 then begin
        Result := copy(SrcStr, 1, i - 1);
        SrcStr := copy(SrcStr, i + Length(ASPLIT), Length(SrcStr));
    end
    else begin
        Result := SrcStr;
        SrcStr := '';
    end;
end;

function adddlllist(dllstr: string): boolean;
var
    getstr: string;
    outwhile: boolean;
begin
    dllnamelist := Tstringlist.Create;
    menunamelist := Tstringlist.Create;
    outwhile := true;
    while outwhile do begin
        getstr := GetNextStr(dllstr);
        if getstr = '' then begin
            outwhile := false;
        end
        else begin
            dllnamelist.Add(getstr);
            getstr := GetNextStr(dllstr);
            menunamelist.Add(getstr);
        end
    end;
    Result := outwhile;
end;

function funcEraseStringSpace(AStr: string): string;
var
    i: integer;
begin
    AStr := UpperCase(Trim(AStr));
    i := pos('OR', AStr);
    if i <> 0 then
        AStr := copy(AStr, 1, i - 1) + copy(AStr, i + 2, maxint);
    Result := AStr;
end;

function funcFillZero(AID: string; len: integer = 10): string;
var
    i, p: integer;
begin
    if AID = '' then
        AID := '1';
    p := Length(AID);
    if (p >= len) then
        AID := copy(AID, 1, len);
    for i := 1 to (len - p) do
        AID := '0' + AID;
    Result := AID;
end;

function funcGetNewID(AID: string; len: integer): string;
var
    // i, p: integer;
    temp: longint;
begin
    if AID = '' then
        AID := '1';
    temp := StrToInt(AID);
    inc(temp);
    AID := IntToStr(temp);
    Result := funcFillZero(AID, len);
end;

function funcConvertDate(ADate: string): TDate;
var
    tmp: char;
begin
    Result := Date();
    if Length(ADate) <> 8 then
        exit;
    ADate := copy(ADate, 1, 4) + '-' + copy(ADate, 5, 2) + '-' + copy(ADate, 7, 2);
    tmp := DateSeparator;
    try
        DateSeparator := '-';
        try
            Result := StrToDate(ADate);
        except
            exit;
        end;
    finally
        DateSeparator := tmp;
    end;
end;

function Fun_StrGetFloatStr(SrcStr: string): string;
begin
    Result := SysUtils.FormatFloat('0.00', Fun_CurrGetValue(SrcStr));
end;

function Fun_CurrGetEditValue(SrcObj: TEdit): Double;
begin
    try
        Result := Fun_CurrGetValue(SrcObj.Text);
    except
        on e: exception do begin
            SrcObj.SetFocus();
            SrcObj.SelectAll();
            raise exception.Create(e.message);
        end;
    end;
end;

function Fun_StrFormatEditValue(Curr: Double): string;
var
    Str: string;
begin
    Str := SysUtils.FloatToStrF(Curr, ffFixed, 18, 4);
    Result := SysUtils.FormatFloat('#,##0.00', Fun_CurrGetValue(Str));
end;

function Fun_CurrGetValue(SrcStr: string): Double; // 由输入框得到数值
var
    Str: string;
    i: integer;
    c, d: char;
begin
    Result := 0;
    for i := 1 to Length(SrcStr) do
        if SrcStr[i] in ['0' .. '9', '.', '-'] then
            Str := Str + SrcStr[i];
    if Str = '' then
        exit;
    try
        c := #0;
        i := pos('.', Str);
        if (i > 14) or ((i = 0) and (Length(Str) > 14)) then
            raise exception.Create('');
        if (i > 0) and (Length(Str) >= i + 3) then begin
            c := Str[i + 3];
            Str := copy(Str, 1, i + 2);
        end;
        d := SysUtils.DecimalSeparator;
        SysUtils.DecimalSeparator := '.';
        Result := SysUtils.StrToFloat(Str);
        if c in ['5' .. '9'] then
            Result := Result + 0.01;
        SysUtils.DecimalSeparator := d;
    except
        on e: exception do begin
            raise exception.Create('值过大或无效!' + Str + #13 + e.Message);
        end;
    end;
end;

function FuncGetSubStr(Str, AStart, AEnd: string): string;
var
    iStart, iEnd: integer;
begin
    iStart := pos(AStart, Str);
    iEnd := pos(AEnd, Str);
    Result := copy(Str, iStart + 1, iEnd - iStart - 1);
end;

function funcGetSystemDir: string;
var
    dir: array [0 .. 255] of char;
begin
    GetWindowsDirectory(dir, 255);
    Result := dir;
end;

procedure procWriteIniInfo();
var
    INI: TiniFile;
    sFile: string;
begin
    sFile := GetAppPath + CONFIGFILE;
    INI := TiniFile.Create(sFile);
    try
        INI.Writestring('use', 'usename', usename);
    finally
        INI.Free;
    end;
end;

procedure procGetIniInfo;
var
    INI: TiniFile;
    sFile: string;
begin
    sFile := GetAppPath + CONFIGFILE;
    INI := TiniFile.Create(sFile);
    try
        debug := LowerCase(INI.ReadString('use', 'debug', 'false'));
        DBIP := INI.ReadString('DB', 'DBIP', '');
        port := INI.ReadString('DB', 'PORT', '');
        if debug = 'true' then begin
            DBSOURCE := INI.ReadString('DB', 'DBSOURCE', '');
            DBUser := INI.ReadString('DB', 'USER', '');
            DBPASS := INI.ReadString('DB', 'PASS', '');
        end
        else begin
{$IFDEF VER210}
            DBSOURCE := Dlah(INI.ReadString('DB', 'DBSOURCE', ''), 'ksykt123');
            DBUser := Dlah(INI.ReadString('DB', 'USER', ''), 'ksykt123');
            DBPASS := Dlah(INI.ReadString('DB', 'PASS', ''), 'ksykt123');
{$ELSE}
            DBSOURCE := DecryptString(INI.ReadString('DB', 'DBSOURCE', ''), 'ksykt123');
            DBUser := DecryptString(INI.ReadString('DB', 'USER', ''), 'ksykt123');
            DBPASS := DecryptString(INI.ReadString('DB', 'PASS', ''), 'ksykt123');
{$ENDIF}
        end;

        // ShowMessage(DBSOURCE);

        posport := INI.Readinteger('pos', 'posport', 1);
        baud := INI.Readinteger('pos', 'baud', 19200);
        DEVPHYID := INI.ReadString('device', 'TERMID', '');
        usename := INI.ReadString('use', 'usename', '');
        voice := INI.ReadString('use', 'voice', 'f_');
        usename := INI.ReadString('use', 'usename', '');
        updatetime := INI.Readinteger('use', 'updatetime', 0);
        ORA_CONNECT_STRING := '' + DBUser + '' + '/' + '' + DBPASS + '' + '@' + '' + DBIP + '' + ':' + '' + port + '' +
          ':' + '' + DBSOURCE + '';
    finally
        INI.Free;
    end;
end;

function encryConfigFile(filename: string): boolean;
var
    INI1, INI2: TiniFile;
    sFile: string;
    sDB, sUser, sPass: string;
begin
    Result := false;
    sFile := GetAppPath + filename;
    INI1 := TiniFile.Create(sFile);
    INI2 := TiniFile.Create(GetAppPath + 'config.ini');
    try
{$IFDEF VER210}
        sDB := Elah(INI1.ReadString('DB', 'DBSOURCE', ''), 'ksykt123');
        sUser := Elah(INI1.ReadString('DB', 'USER', ''), 'ksykt123');
        sPass := Elah(INI1.ReadString('DB', 'PASS', ''), 'ksykt123');
{$ELSE}
        sDB := EncryptString(INI1.ReadString('DB', 'DBSOURCE', ''), 'ksykt123');
        sUser := EncryptString(INI1.ReadString('DB', 'USER', ''), 'ksykt123');
        sPass := EncryptString(INI1.ReadString('DB', 'PASS', ''), 'ksykt123');
{$ENDIF}
        INI2.Writestring('DB', 'DBSOURCE', sDB);
        INI2.Writestring('DB', 'USER', sUser);
        INI2.Writestring('DB', 'PASS', sPass);
        INI2.Writestring('use', 'debug', 'false');

        Result := true;
    finally
        INI1.Free;
        INI2.Free;
    end;

end;
{$WARNINGS OFF}

function FuncShowMessage(hdl: HWND; StrMsg: string; IntMsgType: integer): integer;
begin
    Result := 0;
    case IntMsgType of
        0:
            MessageBox(hdl, PChar(StrMsg), '提示', MB_OK + MB_ICONINFORMATION);
        1:
            MessageBox(hdl, PChar(StrMsg), '警告', MB_OK + MB_ICONWARNING);
        2:
            MessageBox(hdl, PChar(StrMsg), '错误', MB_OK + MB_ICONERROR);
        3:
            Result := MessageBox(hdl, PChar(StrMsg), '提示', MB_YESNO + MB_ICONQUESTION);
        4:
            Result := MessageBox(hdl, PChar(StrMsg), '提示', MB_YESNOCANCEL + MB_ICONQUESTION);
    end;
end;
{$WARNINGS ON}

function GetAppPath: string;
begin
    Result := ExtractFilePath(Application.ExeName);
end;

function funcConnectDB(Pt: PDBConn): boolean;
begin
    Result := false;

    if DBConn = nil then begin
        DBConn := TOraSession.Create(nil);
    end;
    DBConn.Options.Net := true;
    if DBQuery = nil then
        DBQuery := TOraQuery.Create(nil);
    if DBQueryTmp = nil then
        DBQueryTmp := TOraQuery.Create(nil);
    if DBQueryBaK = nil then
        DBQueryBaK := TOraQuery.Create(nil);
    if Pt^.Connected then begin
        Result := true;
        DBQuery.Connection := Pt^;
        DBQueryTmp.Connection := Pt^;
        DBQueryBaK.Connection := Pt^;
        Result := true;
        exit;
    end;
    try
        Pt^.SQL.Text := ORA_CONNECT_STRING;
        Pt^.LoginPrompt := false;
        DBQuery.Connection := Pt^;
        DBQueryTmp.Connection := Pt^;
        DBQueryBaK.Connection := Pt^;
        Pt^.Connected := true;
    except
        on e: exception do
            writelog('连接错误:' + e.Message);
        // FuncShowMessage(Application.Handle, '连接错误:' + e.Message, 2);
    end;
    Result := true;
end;

function funcConnectDB(): boolean;
begin
    Result := false;
    if DBConn = nil then begin
        DBConn := TOraSession.Create(nil);
    end;
    DBConn.Options.Net := true;
    if DBQuery = nil then
        DBQuery := TOraQuery.Create(nil);
    if DBQueryTmp = nil then
        DBQueryTmp := TOraQuery.Create(nil);
    if DBQueryBaK = nil then
        DBQueryBaK := TOraQuery.Create(nil);
    if DBConn.Connected then begin
        Result := true;
        DBQuery.Connection := DBConn;
        DBQueryTmp.Connection := DBConn;
        DBQueryBaK.Connection := DBConn;
        Result := true;
        exit;
    end;
    try

        DBConn.ConnectString := ORA_CONNECT_STRING;
        DBConn.LoginPrompt := false;
        DBQuery.Connection := DBConn;
        DBQueryTmp.Connection := DBConn;
        DBQueryBaK.Connection := DBConn;
        // DBConn.Options.Net:=false;
        DBConn.Open();
    except
        on e: exception do begin
            writelog('连接错误:' + e.Message);
            // FuncShowMessage(Application.Handle, '连接错误:' + e.Message, 2);
            exit;
        end;
    end;
    Result := true;
end;

function funcSelectSqlWithParams(AQuery: TOraQuery; PtEnable: boolean = true): boolean;
begin
    if PtEnable then begin
        Result := PtConn^.Connected;
        if not PtConn^.Connected then begin
            if not funcConnectDB(PtConn) then
                exit;
        end;
    end
    else begin
        Result := DBConn.Connected;
        if not DBConn.Connected then begin
            if not funcConnectDB() then
                exit;
        end;
    end;
    AQuery.Open;
    AQuery.First;
    Result := true;
end;

function funcSelectSql(ASql: string; AQuery: TOraQuery; PtEnable: boolean = true): boolean;
begin
    Result := false;
    try
        if not DBConn.Connected then begin
            if not funcConnectDB() then
                exit;
        end;
        AQuery.Close;
        AQuery.SQL.Clear;
        AQuery.SQL.Text := ASql;
        AQuery.Open;
        AQuery.First;
        Result := true;
    except
        Result := false;
    end;
end;

function funcExcuteSql(ASql: string; AQuery: TOraQuery; PtEnable: boolean = true): boolean;
begin
    Result := false;
    if PtEnable then begin

        Result := DBConn.Connected;
        if not DBConn.Connected then begin
            if not funcConnectDB() then
                exit;
        end;
    end;
    AQuery.Close;
    AQuery.SQL.Clear;
    AQuery.SQL.Text := ASql;
    AQuery.ExecSQL;
    Result := true;
end;

function funcExcuteSqlForChinese(AQuery: TOraQuery; PtEnable: boolean = true): boolean;
begin
    Result := false;
    if PtEnable then begin
        Result := PtConn^.Connected;
        if not PtConn^.Connected then begin
            if not funcConnectDB(PtConn) then
                exit;
        end;
    end
    else begin
        Result := DBConn.Connected;
        if not DBConn.Connected then begin
            if not funcConnectDB() then
                exit;
        end;
    end;

    AQuery.ExecSQL;
    Result := true;
end;

{ TUserInfo }

constructor TUserInfo.Create(AName, APwd: string);
begin
    self.UserName := AName;
    self.Password := APwd;
end;

function TUserInfo.funcGetMenuList: boolean;
var
    i, j: integer;
    // sSql, ParentID, ChildID: string;
begin
    i := 0;
    SetLength(MenuList, i + 1);
    MenuList[i].Caption := '医疗收费';
    MenuList[i].ID := '1';
    MenuList[i].isValid := true;
    for j := 1 to dllnamelist.Count do begin
        SetLength(MenuList[i].SubMenu, j + 1);
        MenuList[i].SubMenu[j].Caption := menunamelist[j - 1];
        MenuList[i].SubMenu[j].ID := IntToStr(j);
        MenuList[i].SubMenu[j].DLL := dllnamelist[j - 1];
        MenuList[i].SubMenu[j].isVisble := true;
    end;
    Result := true;
end;

function TUserInfo.GetCNName: string;
begin
    Result := self.CNName;
end;

function TUserInfo.GetPassword: string;
begin
    Result := self.Password;
end;

function TUserInfo.GetUserName: string;
begin
    Result := self.UserName;
end;

end.
