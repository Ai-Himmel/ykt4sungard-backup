unit CommU;

interface

uses SysUtils, Messages, StdCtrls, Classes, Controls, Forms, Windows, ADODB, DB,
{$IFDEF VER210}
    AES2010,
{$ELSE}
    AES,
{$ENDIF}
    IniFiles;

const

    // ORACLE连接字符串

    CONFIGFILE = '..\conf\config.ini';

type
    PDBConn = ^TADOConnection;

var
    // OraSession1: TOraSession;
    // OraQuery1: TOraQuery;
    // 数据库相关变量
    DBConn: TADOConnection;
    PtConn: TADOConnection; // DLL模块中使用
    DBQuery, DBQueryTmp, DBQueryBaK: TADOQuery;
    DEVPHYID, dllstr, DBSOURCE, DBUser, DBPASS, DBIP, port, DBCONNSTR: string;
    baud, posport: integer;
    _internal : integer;
    usename: string;
    debug: string;
    voice: string;
    updatetime: integer;
    // 打印相关
    PrintName: string; // 打印机名称
    PrintIndex: integer; // 当前打印机序号
    Orient: integer; // 打印方向
    X, Y: integer; // X方向调整值，Y方向调整值
    ORA_CONNECT_STRING: string;
    oldphicd: string;
    slDBpath: string;

    g_begintime: string;
    g_endtime: string;

function encryConfigFile(filename: string): boolean;
// 加密 dll
function calc_oper_pwd(oper_code: pchar; pwd: pchar; text: pchar): longint; stdcall; far;
external 'desdll.dll' name 'calc_oper_pwd';
// function SMT_ControlBuzzer: longint; stdcall; external 'KS_ThirdInterface.dll' name 'SMT_ControlBuzzer';
// 读学工号  *
function SMT_ReadCardNo(cardno: pchar): longint; stdcall; external 'KS_ThirdInterface.dll' name 'SMT_ReadCardNo';
function ReadCardNO(cardno: PInteger): longint; stdcall; external 'KS_ThirdInterface.dll' name 'ReadCardNO';
// function SMT_ReadCardID(cardno: integer): longint; stdcall; external 'KS_ThirdInterface.dll' name 'SMT_ReadCardID';
// 读取金额
function SMT_ReadBalance(var Balance: integer): longint; stdcall;
external 'KS_ThirdInterface.dll' name 'SMT_ReadBalance';
// 读取金额
function SMT_ControlBuzzer: longint; stdcall; external 'KS_ThirdInterface.dll' name 'SMT_ControlBuzzer';
function LPReadCardNO: longint; stdcall; external 'KS_ThirdInterface.dll' name 'LPReadCardNO';
// 交易
function SMT_PacketDelMomey(nMoney: integer; var nFlowNo: integer): longint; stdcall;
external 'KS_ThirdInterface.dll' name 'SMT_PacketDelMomey';
// 打开串口
function SMT_ConnectMF280(port: integer; baud: integer): longint; stdcall;
external 'KS_ThirdInterface.dll' name 'SMT_ConnectMF280';
// 关闭串口
function SMT_CloseMF280: longint; stdcall; external 'KS_ThirdInterface.dll' name 'SMT_CloseMF280';
// 加密函数
function encOperPwd(operCode, operPwd: string): string;
function FuncShowMessage(hdl: HWND; StrMsg: string; IntMsgType: integer): integer;
// 获取应用程序路径
function GetAppPath: string;
// 连接数据库
function funcConnectDB(): boolean; overload;
function funcConnectDB(Pt: PDBConn): boolean; overload;
// 查询SQL
function funcSelectSql(ASql: string; AQuery: TADOQuery; PtEnable: boolean = true): boolean;

// 执行SQL
function funcExcuteSql(ASql: string; AQuery: TADOQuery; PtEnable: boolean = true): boolean;

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

implementation

procedure writelog(strmessage: string);
var
    myfile: TextFile;
    // size, FileHandle: Integer;
    filename: string;
    patch: string;
    writestr: string;
begin
    patch := ExtractFilePath(ParamStr(0));
    filename := patch + '..\log\log_' + FormatdateTime('yyyymmdd', now()) + '.txt';
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
    result := '';
    if SrcStr = '' then
        exit;
    i := pos(ASPLIT, SrcStr);
    if i <> 0 then begin
        result := copy(SrcStr, 1, i - 1);
        SrcStr := copy(SrcStr, i + Length(ASPLIT), Length(SrcStr));
    end
    else begin
        result := SrcStr;
        SrcStr := '';
    end;
end;

function funcEraseStringSpace(AStr: string): string;
var
    i: integer;
begin
    AStr := UpperCase(Trim(AStr));
    i := pos('OR', AStr);
    if i <> 0 then
        AStr := copy(AStr, 1, i - 1) + copy(AStr, i + 2, maxint);
    result := AStr;
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
    result := AID;
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
    result := funcFillZero(AID, len);
end;

function funcConvertDate(ADate: string): TDate;
var
    tmp: char;
begin
    result := Date();
    if Length(ADate) <> 8 then
        exit;
    ADate := copy(ADate, 1, 4) + '-' + copy(ADate, 5, 2) + '-' + copy(ADate, 7, 2);
    tmp := DateSeparator;
    try
        DateSeparator := '-';
        try
            result := StrToDate(ADate);
        except
            exit;
        end;
    finally
        DateSeparator := tmp;
    end;
end;

function Fun_StrGetFloatStr(SrcStr: string): string;
begin
    result := SysUtils.FormatFloat('0.00', Fun_CurrGetValue(SrcStr));
end;

function Fun_CurrGetEditValue(SrcObj: TEdit): Double;
begin
    try
        result := Fun_CurrGetValue(SrcObj.text);
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
    result := SysUtils.FormatFloat('#,##0.00', Fun_CurrGetValue(Str));
end;

function Fun_CurrGetValue(SrcStr: string): Double; // 由输入框得到数值
var
    Str: string;
    i: integer;
    c, d: char;
begin
    result := 0;
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
        result := SysUtils.StrToFloat(Str);
        if c in ['5' .. '9'] then
            result := result + 0.01;
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
    result := copy(Str, iStart + 1, iEnd - iStart - 1);
end;

function funcGetSystemDir: string;
var
    dir: array [0 .. 255] of char;
begin
    GetWindowsDirectory(dir, 255);
    result := dir;
end;

procedure procWriteIniInfo();
var
    INI: TIniFile;
    sFile: string;
begin
    sFile := GetAppPath + CONFIGFILE;
    INI := TIniFile.Create(sFile);
    try
        INI.Writestring('use', 'usename', usename);
    finally
        INI.Free;
    end;
end;

procedure procGetIniInfo;
var
    INI: TIniFile;
    sFile: string;
begin
    sFile := GetAppPath + CONFIGFILE;
    INI := TIniFile.Create(sFile);
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
        dllstr := INI.ReadString('dll', 'dllname', '');
        posport := INI.Readinteger('pos', 'posport', 1);
        baud := INI.Readinteger('pos', 'baud', 19200);
        _internal := INI.Readinteger('pos', 'internal', 5000);
        DEVPHYID := INI.ReadString('device', 'TERMID', '');
        usename := INI.ReadString('use', 'usename', '');
        voice := INI.ReadString('use', 'voice', 'f_');
        usename := INI.ReadString('use', 'usename', '');
        updatetime := INI.Readinteger('use', 'updatetime', 0);
        // ORA_CONNECT_STRING := '' + DBUSER + '' + '/' + '' + DBPASS + '' + '@' + '' + DBIP + '' + ':' + '' + port + '' + ':' + '' + DBSOURCE + '';
        ORA_CONNECT_STRING := 'Provider=IBMDADB2.DB2COPY1;Password=' + DBPASS +
          ';Persist Security Info=True;User ID=' + DBUser + ';Data Source=' + DBSOURCE + ';Location=' + DBIP +
          ';Extended Properties=""';
    finally
        INI.Free;
    end;
end;

function encryConfigFile(filename: string): boolean;
var
    INI1, INI2: TIniFile;
    sFile: string;
    sDB, sUser, sPass: string;
begin
    result := false;
    sFile := GetAppPath + filename;
    INI1 := TIniFile.Create(sFile);
    INI2 := TIniFile.Create(GetAppPath + '../conf/config.ini');
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

        result := true;
    finally
        INI1.Free;
        INI2.Free;
    end;

end;
{$WARNINGS OFF}

function FuncShowMessage(hdl: HWND; StrMsg: string; IntMsgType: integer): integer;
begin
    result := 0;
    case IntMsgType of
        0:
            MessageBox(hdl, pchar(StrMsg), '提示', MB_OK + MB_ICONINFORMATION);
        1:
            MessageBox(hdl, pchar(StrMsg), '警告', MB_OK + MB_ICONWARNING);
        2:
            MessageBox(hdl, pchar(StrMsg), '错误', MB_OK + MB_ICONERROR);
        3:
            result := MessageBox(hdl, pchar(StrMsg), '提示', MB_YESNO + MB_ICONQUESTION);
        4:
            result := MessageBox(hdl, pchar(StrMsg), '提示', MB_YESNOCANCEL + MB_ICONQUESTION);
    end;
end;
{$WARNINGS ON}

function GetAppPath: string;
begin
    result := ExtractFilePath(Application.ExeName);
end;

function funcConnectDB(Pt: PDBConn): boolean;
begin
    result := false;

    if DBConn = nil then begin
        DBConn := TADOConnection.Create(nil);
    end;
    if DBQuery = nil then
        DBQuery := TADOQuery.Create(nil);
    if DBQueryTmp = nil then
        DBQueryTmp := TADOQuery.Create(nil);
    if DBQueryBaK = nil then
        DBQueryBaK := TADOQuery.Create(nil);
    // DBCONNSTR := format(ORA_CONNECT_STRING, [DBPASS, DBUSER, DBSOURCE]);
    if Pt^.Connected then begin
        DBQuery.Connection := Pt^;
        DBQueryTmp.Connection := Pt^;
        DBQueryBaK.Connection := Pt^;
        result := true;
        exit;
    end;
    try
        Pt^.ConnectionString := ORA_CONNECT_STRING;
        Pt^.LoginPrompt := false;
        DBQuery.Connection := Pt^;
        DBQueryTmp.Connection := Pt^;
        DBQueryBaK.Connection := Pt^;
        Pt^.Connected := true;
    except
        on e: exception do
            writelog('连接错误:' + e.Message);
    end;
    result := true;
end;

function funcConnectDB(): boolean;
begin
    result := false;
    if DBConn = nil then begin
        DBConn := TADOConnection.Create(nil);
    end;
    if DBQuery = nil then
        DBQuery := TADOQuery.Create(nil);
    if DBQueryTmp = nil then
        DBQueryTmp := TADOQuery.Create(nil);
    if DBQueryBaK = nil then
        DBQueryBaK := TADOQuery.Create(nil);
    if DBConn.Connected then begin
        DBQuery.Connection := DBConn;
        DBQueryTmp.Connection := DBConn;
        DBQueryBaK.Connection := DBConn;
        result := true;
        exit;
    end;
    try

        DBConn.ConnectionString := ORA_CONNECT_STRING;
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
    result := true;
end;

function funcSelectSql(ASql: string; AQuery: TADOQuery; PtEnable: boolean = true): boolean;
begin
    result := false;
    try
        if not DBConn.Connected then begin
            if not funcConnectDB() then
                exit;
        end;
        AQuery.Close;
        AQuery.SQL.Clear;
        AQuery.SQL.text := ASql;
        AQuery.Open;
        AQuery.First;
        result := true;
    except
    end;
end;

function encOperPwd(operCode, operPwd: string): string;
var
    outOperPwd: array [0 .. 16] of char;
    st: integer;
begin
    st := calc_oper_pwd(pchar(operCode), pchar(Trim(operPwd)), @outOperPwd);
    if st <> 0 then begin
        FuncShowMessage(Application.Handle, '加密失败！', 2);
        result := '';
        exit;
    end;
    result := outOperPwd;
end;

function funcExcuteSql(ASql: string; AQuery: TADOQuery; PtEnable: boolean = true): boolean;
begin
    result := false;
    if PtEnable then begin
        result := DBConn.Connected;
        if not DBConn.Connected then begin
            if not funcConnectDB() then begin
                exit;
            end;
        end;
    end;
    AQuery.Close;
    AQuery.SQL.Clear;
    AQuery.SQL.text := ASql;
    AQuery.ExecSQL;
    result := true;
end;

end.
