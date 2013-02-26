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
    // ORACLE�����ַ���

    CONFIGFILE = 'config.ini';
    LOGINFILE = 'picture\Login.bmp';
    USERCODEFILE = 'usercode.ini';

type
    LOOPPURSEINFO = packed record
        RemainMoney: DWORD; // ����Ǯ�����
        DealTimes: WORD; // �û���������ˮ��
        DealYear: BYTE; // ��������
        DealMonth: BYTE;
        DealDay: BYTE;
        DealHour: BYTE;
        DealMin: BYTE;
        DealTimes_CurTime: BYTE; // �ۼƽ��״���(��ǰʱ�����)
        DealTimes_CurDay: BYTE; // �ۼƽ��״���(������)
    end;

type
    TCardInfo = packed record
        DeadLineDate: array [1 .. 9] of char; // �û���ʹ�ý�ֹ����
        CardRightType: longint; // �û���ʹ��Ȩ�����ͣ�1--254��
        ucName: array [1 .. 9] of char; // ����
        ucDutyNo: array [1 .. 9] of char; // ְ�����
        ucCertificateNo: array [1 .. 21] of char; // ֤������
        ucDepartmentNo: array [1 .. 11] of char; // ���ű��
        ucIdentifyNo: array [1 .. 21] of char; // ��ݴ���
        ucSexNo: array [1 .. 2] of char; // �Ա����
        ucCardNo: array [1 .. 21] of char; // ���ţ����Ż�ѧ�ţ�
    end;

type
    TRunDllFun = function(AFile, AStr: PChar; i, x, y, mode: integer): integer; stdcall;

    TProductZS = record
        ID: string; // ��Ʒ����
        Name: string; // ��Ʒ����
        Count: Double; // �ͻ�����
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
        ShowCardNo: array [1 .. 11] of char; // �û�����ʾ����
        CardNo: array [1 .. 8] of char; // �û������׿���
        DeadLineDate: array [1 .. 9] of char; // �û���ʹ�ý�ֹ����
        CardRightType: longint; // Ȩ�����ͣ�1--254���շ����
        ucName: array [1 .. 9] of char; // ����
        ucDutyNo: array [1 .. 9] of char; // ְ�����
        ucCertificateNo: array [1 .. 21] of char; // ���֤����
        ucDepartmentNo: array [1 .. 11] of char; // ��λ���
        ucIdentifyNo: array [1 .. 5] of char; // �ͻ����
        ucSexNo: array [1 .. 2] of char; // �Ա����
        ucCardNo: array [1 .. 21] of char; // ���Ż�ѧ��
        ucPwd: array [1 .. 6] of char; // ����
        ucLibraryNo: array [1 .. 21] of char; // ͼ��֤��
        Money: longint; // ���֣�
        isFormat: char; // �Ƿ��ʽ����һ����
    end;

    PDBConn = ^TOraSession;
    PUser = ^TUserInfo;

    // ��ģ����Ϣ����
    TSubMenu = record
        Caption: string; // ��ģ������
        ID: string; // ��ģ��ID
        DLL: string; // ��ģ��DLL��
        isVisble: boolean; // �Ƿ���ʾ��Ĭ��FALSE��������ʾ
        isWeb: boolean; // �Ƿ�WEB��ʽ
    end;

    // ��ģ����Ϣ����
    TMenu = record
        Caption: string; // ��ģ����
        ID: string; // ��ģ��ID
        isValid: boolean; // ��ģ���Ƿ���Ч,Ĭ��FALSE����Ч
        isWeb: boolean; // ��ģ���Ƿ�ΪWEB��ʽ
        SubMenu: array of TSubMenu; // ��Ӧ����ģ��
    end;

    // �û���Ϣ����
    TUserInfo = class(TObject)
    private
        UserName: string; // �û���
        Password: string; // ����
        CNName: string; // ��������
    protected

    public
        // �û���Ӧ��ģ���б�
        MenuList: array of TMenu;

        function funcGetMenuList: boolean;
        // ��ȡ�û���
        function GetUserName(): string;
        // ��ȡ����
        function GetPassword(): string;
        // ��ȡ������
        function GetCNName(): string;
        constructor Create(AName, APwd: string);
    end;

var
    // OraSession1: TOraSession;
    // OraQuery1: TOraQuery;
    // ���ݿ���ر���
    DBConn: TOraSession;
    PtConn: PDBConn; // DLLģ����ʹ��
    DBQuery, DBQueryTmp, DBQueryBaK: TOraQuery;
    DEVPHYID, dllstr, DBSOURCE, DBUser, DBPASS, DBIP, port, DBCONNSTR: string;
    baud, posport: integer;
    dllnamelist: Tstringlist;
    menunamelist: Tstringlist;
    // CurrUserName:string;
    // �û���Ϣ
    User: TUserInfo;
    PtUser: PUser; // DLLģ����ʹ��
    usename: string;
    debug: string;
    voice: string;
    updatetime: integer;
    // ��ӡ���
    PrintName: string; // ��ӡ������
    PrintIndex: integer; // ��ǰ��ӡ�����
    Orient: integer; // ��ӡ����
    x, y: integer; // X�������ֵ��Y�������ֵ
    ORA_CONNECT_STRING: string;
    oldphicd: string;
    // slDBpath: string;
    // sldb: TSQLiteDatabase;

    g_begintime: string;
    g_endtime: string;

function encryConfigFile(filename: string): boolean;

function FuncShowMessage(hdl: HWND; StrMsg: string; IntMsgType: integer): integer;
// ��ȡӦ�ó���·��
function GetAppPath: string;
// �������ݿ�
function funcConnectDB(): boolean; overload;
function funcConnectDB(Pt: PDBConn): boolean; overload;
// ��ѯSQL
function funcSelectSql(ASql: string; AQuery: TOraQuery; PtEnable: boolean = true): boolean;
// ����param����ѯSQL
function funcSelectSqlWithParams(AQuery: TOraQuery; PtEnable: boolean = true): boolean;

// ִ��SQL
function funcExcuteSql(ASql: string; AQuery: TOraQuery; PtEnable: boolean = true): boolean;

// ����param��ִ��SQL
function funcExcuteSqlForChinese(AQuery: TOraQuery; PtEnable: boolean = true): boolean;
procedure writelog(strmessage: string);
// ��ȡINI�ļ�
procedure procGetIniInfo;
// д��INI�ļ�
procedure procWriteIniInfo();
// ��ȡϵͳĿ¼
function funcGetSystemDir: string;
// ��ȡ���ַ���
function FuncGetSubStr(Str, AStart, AEnd: string): string;
// ���ַ����õ���ֵ
function Fun_CurrGetValue(SrcStr: string): Double;
// ����ֵ�õ�ǧ��λ�ַ���
function Fun_StrFormatEditValue(Curr: Double): string;
// �������õ���ֵ
function Fun_CurrGetEditValue(SrcObj: TEdit): Double;
// �����ǧ��λ�õ���׼�ַ���
function Fun_StrGetFloatStr(SrcStr: string): string;
// ����ת������
function funcConvertDate(ADate: string): TDate;
function funcFillZero(AID: string; len: integer = 10): string;
// ��1�����ַ���ǰ���0
function funcGetNewID(AID: string; len: integer = 10): string;
// ȥ���ַ����пո�
function funcEraseStringSpace(AStr: string): string;

function GetNextStr(var SrcStr: string; ASPLIT: string = ','): string;
// �ͷŷ�������ݼ��ڴ�
procedure procDestroyDBSET;
// ���ؿͻ���Ϣ
// procedure procDownloadcustomer;
// ����ʱ���
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

function Fun_CurrGetValue(SrcStr: string): Double; // �������õ���ֵ
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
            raise exception.Create('ֵ�������Ч!' + Str + #13 + e.Message);
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
            MessageBox(hdl, PChar(StrMsg), '��ʾ', MB_OK + MB_ICONINFORMATION);
        1:
            MessageBox(hdl, PChar(StrMsg), '����', MB_OK + MB_ICONWARNING);
        2:
            MessageBox(hdl, PChar(StrMsg), '����', MB_OK + MB_ICONERROR);
        3:
            Result := MessageBox(hdl, PChar(StrMsg), '��ʾ', MB_YESNO + MB_ICONQUESTION);
        4:
            Result := MessageBox(hdl, PChar(StrMsg), '��ʾ', MB_YESNOCANCEL + MB_ICONQUESTION);
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
            writelog('���Ӵ���:' + e.Message);
        // FuncShowMessage(Application.Handle, '���Ӵ���:' + e.Message, 2);
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
            writelog('���Ӵ���:' + e.Message);
            // FuncShowMessage(Application.Handle, '���Ӵ���:' + e.Message, 2);
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
    MenuList[i].Caption := 'ҽ���շ�';
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
