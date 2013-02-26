unit CommU;

interface

uses SysUtils, Messages, StdCtrls, Classes, Controls, Forms, Windows, Ora, MemDS, DB, DBAccess, SQLiteTable3, IniFIles;

const
  WM_RELEASEDLL = WM_USER + 101;
  SP = '~~';
  //ORACLE�����ַ���

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
    DeadLineDate: array[1..9] of char; //�û���ʹ�ý�ֹ����
    CardRightType: longint; //�û���ʹ��Ȩ�����ͣ�1--254��
    ucName: array[1..9] of Char; //����
    ucDutyNo: array[1..9] of Char; //ְ�����
    ucCertificateNo: array[1..21] of Char; //֤������
    ucDepartmentNo: array[1..11] of Char; //���ű��
    ucIdentifyNo: array[1..21] of Char; //��ݴ���
    ucSexNo: array[1..2] of Char; //�Ա����
    ucCardNo: array[1..21] of Char; //���ţ����Ż�ѧ�ţ�
  end;

type
  TRunDllFun = function(AFile, AStr: PChar; i, x, y, mode: integer): integer; stdcall;
  TProductZS = record
    ID: string; //��Ʒ����
    Name: string; //��Ʒ����
    Count: Double; //�ͻ�����
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
    ShowCardNo: array[1..11] of char; //�û�����ʾ����
    CardNo: array[1..8] of char; //�û������׿���
    DeadLineDate: array[1..9] of Char; //�û���ʹ�ý�ֹ����
    CardRightType: longint; //Ȩ�����ͣ�1--254���շ����
    ucName: array[1..9] of Char; //����
    ucDutyNo: array[1..9] of Char; //ְ�����
    ucCertificateNo: array[1..21] of Char; //���֤����
    ucDepartmentNo: array[1..11] of Char; //��λ���
    ucIdentifyNo: array[1..5] of Char; //�ͻ����
    ucSexNo: array[1..2] of Char; //�Ա����
    ucCardNo: array[1..21] of Char; //���Ż�ѧ��
    ucPwd: array[1..6] of Char; //����
    ucLibraryNo: array[1..21] of Char; //ͼ��֤��
    Money: longint; //���֣�
    isFormat: Char; //�Ƿ��ʽ����һ����
  end;

  PDBConn = ^TOraSession;
  PUser = ^TUserInfo;
  //��ģ����Ϣ����
  TSubMenu = record
    Caption: string; //��ģ������
    ID: string; //��ģ��ID
    DLL: string; //��ģ��DLL��
    isVisble: boolean; //�Ƿ���ʾ��Ĭ��FALSE��������ʾ
    isWeb: boolean; //�Ƿ�WEB��ʽ
  end;
  //��ģ����Ϣ����
  TMenu = record
    Caption: string; //��ģ����
    ID: string; //��ģ��ID
    isValid: boolean; //��ģ���Ƿ���Ч,Ĭ��FALSE����Ч
    isWeb: boolean; //��ģ���Ƿ�ΪWEB��ʽ
    SubMenu: array of TSubMenu; //��Ӧ����ģ��
  end;
  //�û���Ϣ����
  TUserInfo = class(TObject)
  private
    UserName: string; //�û���
    Password: string; //����
    CNName: string; //��������
  protected

  public
    //�û���Ӧ��ģ���б�
    MenuList: array of TMenu;
    //����-1����������; ����0����½�ɹ���
    //����1���û������ڣ�����2���������
    function funcLogin: integer;
    //��֯�û���Ӧ�Ĺ���
    function funcGetMenuList: boolean;
    //��ȡ�û���
    function GetUserName(): string;
    //��ȡ����
    function GetPassword(): string;
    //��ȡ������
    function GetCNName(): string;
    constructor Create(AName, APwd: string);
  end;
var
   //  OraSession1: TOraSession;
  //  OraQuery1: TOraQuery;
  //���ݿ���ر���
  DBConn: TOraSession;
  PtConn: PDBConn; //DLLģ����ʹ��
  DBQuery, DBQueryTmp, DBQueryBaK: TOraQuery;
  DEVPHYID, dllstr, DBSOURCE, DBUser, DBPASS, DBIP, port, DBCONNSTR: string;
  baud, posport: integer;
  dllnamelist: Tstringlist;
  menunamelist: Tstringlist;
  //CurrUserName:string;
  //�û���Ϣ
  User: TUserInfo;
  PtUser: PUser; //DLLģ����ʹ��
  usename: string;
  debug: string;
  voice: string;
  updatetime: integer;
  //��ӡ���
  PrintName: string; //��ӡ������
  PrintIndex: integer; //��ǰ��ӡ�����
  Orient: integer; //��ӡ����
  X, Y: integer; //X�������ֵ��Y�������ֵ
  ORA_CONNECT_STRING: string;
  oldphicd: string;
  slDBpath: string;
  sldb: TSQLiteDatabase;

  g_begintime: string;
  g_endtime: string;
//********************************************************************
//������
//********************************************************************
//�����SMT_CheckForCard();
//����1��ʾ�㿨��2��ʾ��ʼ�����Ŀ�, 3��ʾ����ʶ��Ŀ�
function SMT_CheckForCard(): longint;
stdcall; far; external 'CardDLL.dll' name 'SMT_CheckForCard';

//��ʼ������ *
function ConnectMF(port: longint; baud: longint): longint;
stdcall; far; external 'CardDLL.dll' name 'ConnectMF';

//����������
function SMT_ControlBuzzer: longint;
stdcall; far; external 'CardDLL.dll' name 'ControlBuzzer';

//����Ȩ��
function DLLReadCardMainKey(OutMainKey: PByte; swith: SmallInt; flag: PSmallInt): LongInt;
stdcall; far; external 'CardDLL.dll' name 'ReadCardMainKey';

//���ÿ�ƬΪ����������ҡ��ⶳ��
function SMT_SetNormalFlag: longint;
stdcall; far; external 'CardDLL.dll' name 'SMT_SetNormalFlag';

//���ÿ�ƬΪ����������ң��ⶳ������汾��2005-06-08����
function SMT_SetNormalFlagByVer(ver: PChar): longint;
stdcall; far; external 'CardDLL.dll' name 'SMT_SetNormalFlagByBlkVerion';

//���տ�
function SMT_ClearCard: longint;
stdcall; far; external 'CardDLL.dll' name 'SMT_ClearCard';

//��д����Ȩ *
function ReaderAuthor(MoneyBuf: pchar): longint;
stdcall; far; external 'CardDLL.dll' name 'SMT_AutoDll';

function Load_Dll: longint;
stdcall; far; external 'CardDLL.dll' name 'Load_Dll';

// ���ùرմ��� *
function CloseMF: SmallInt;
stdcall; far; External 'CardDll.dll' name 'CloseMF';

//���п�   *
function PublishCard(const PCM: TPublishCardMes): longint;
stdcall; external 'CardDLL.dll' name 'PublishCard';

//������Ϣ   *
function ReadCardInfo(const PCM: TPublishCardMes): longint;
stdcall; external 'CardDLL.dll' name 'ReadCardInfo';

//�������к� *
function RequestCard(ucSerialNo: pchar; ucType: pchar): longint;
stdcall; external 'CardDLL.dll' name 'RequestCard';

//�û�����Ǯ
function PacketAddMomey(nPacketNo: smallint; nMoney: longint): longint;
stdcall; external 'CardDLL.dll' name 'SMT_PacketAddMomey';

//�û���ȡ�� *
function PacketDelMomey(nPacketNo: smallint; nMoney: longint): longint;
stdcall; external 'CardDLL.dll' name 'SMT_PacketDelMomey';

//���û���������Ϣ
function ReadPacketInfo(const LPI: LOOPPURSEINFO): longint;
stdcall; external 'CardDLL.dll' name 'ReadPacketInfo';

//�û������������ȡ  *
function ReadPersonalPassword(PersonalPsd: pchar): longint;
stdcall; external 'CardDLL.dll' name 'ReadCardPwd';

//�û�������������� *
function ChangePersonalPassword(PersonalPsd: pchar): longint;
stdcall; external 'CardDLL.dll' name 'WriteCardPwd';

//�����׿���  *
function ReadExchCardNo(ExchCardNo: PInteger): longint;
stdcall; external 'CardDLL.dll' name 'ReadCardNO';

//������Ϣ *
function GetLastErrMsg(errcode: pointer; msg: pchar): longint;
stdcall; external 'CardDLL.dll' name 'GetLastErrMsg';

//���¿���Ϣ   *
function UpdateCardInfo(const CardInfo: TPublishCardMes): longint;
stdcall; external 'CardDLL.dll' name 'UpdateCardInfo';
//������Ȩĸ�� *
function CreateMonKeyCard(nKey1: longint; nKey2: longint): longint;
stdcall; far; external 'CardDLL.dll' name 'SMT_CreateMonKeyCard';

//������Ȩĸ��  *
function ClearMonKeyCard: smallInt;
stdcall; far; External 'CardDLL.dll' name 'SMT_ClearMonKeyCard';

//����������Կ�ӿ�  *
function PublishComsumeChildCard(year, month, day, hour: pchar): longint;
stdcall; external 'CardDLL.dll' name 'PublishComsumeChildCard';

//����������Կ�ӿ�  *
function ClearComsumeChildCard: SmallInt;
stdcall; far; External 'CardDLL.dll' name 'SMT_ClearComsumeChildCard';

//���г�ֵ��Կ�ӿ�  *
function PublishAddMoneyChildCard(year, month, day, hour: pchar): longint;
stdcall; external 'CardDLL.dll' name 'PublishAddMoneyChildCard';

//���ճ�ֵ��Կ�ӿ�  *
function ClearAddMoneyChildCard: SmallInt;
stdcall; far; External 'CardDLL.dll' name 'SMT_ClearAddMoneyChildCard';

function get_check_char(InCheckSumString: PChar): longint;
stdcall; far; external 'desdll.dll' name 'get_check_char';

function SMT_Login_With_UserKey(Sector: longint; key: PChar; keyFlag: longint): longint;
stdcall; far; external 'SmartCom411DXQ.dll' name 'SMT_Login_With_UserKey';

function SleepCard: longint;
stdcall; far; external 'SmartCom411DXQ.dll' name 'SMT_SleepCard';

//���½��׿���
function SMT_ChangeDealCardNo(dealCardNo: LongInt): longint;
stdcall; far; external 'CardDLL.dll' name 'SMT_ChangeDealCardNo';

//���¿����
function SMT_PacketSetMoney(nPacketNo, dealCardNo: LongInt): longint;
stdcall; far; external 'CardDLL.dll' name 'SMT_PacketSetMoney';

//д�����״���
function SMT_SetTxCnt(nPacketNo, tx_cnt: LongInt): longint;
stdcall; far; external 'CardDLL.dll' name 'SMT_SetTxCnt';
//�����������汾
function SMT_ReadBlackNameListVersion(flag: Pointer; version: string): longint;
stdcall; far; external 'CardDLL.dll' name 'SMT_ReadBlackNameListVersion';
//���Ǯ����Ϣ
function SMT_PacketReset(PackNo: Integer): longint;
stdcall; far; external 'CardDLL.dll' name 'SMT_PacketReset';
//��ȡ����Ϣ
function SMT_ReadBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):
  longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_ReadBlock';

//��ʼ��������
function InitNewCard(err_code: PInteger; showcardno: PChar; test: Pointer): longint;
stdcall; far; external 'CardDLL.dll' name 'InitNewCard';

function HaltCard: LongInt;
stdcall; far; external 'CardDLL.dll' name 'HaltCard';

//������Ȩ��--------------------------------------------------------------------
function InitNewAuthCard(mainKey: PChar; flag: Byte; callBack: Pointer): LongInt;
stdcall; external 'CardDLL.dll' name 'InitNewAuthCard';
function SMT_ModifyDeadLineDateAndFlag(mainKey: PChar; flag: Byte): LongInt;
stdcall; external 'CardDLL.dll' name 'SMT_ModifyDeadLineDateAndFlag';
function SMT_ReadAuthorWorkKeyAndFlag(mainKey: PChar; flag: PByte): LongInt;
stdcall; external 'CardDLL.dll' name 'SMT_ReadAuthorWorkKeyAndFlag';
function PublishAuthCard(const PCM: TPublishCardMes): LongInt;
stdcall; external 'CardDLL.dll' name 'PublishAuthCard';
function ResetNewAuthCard(err_code: Integer; callBack: Pointer): LongInt;
stdcall; external 'CardDLL.dll' name 'ResetNewAuthCard';
function SMT_SetAuthNormalFlagByBlkVerion(ver: PChar): LongInt;
stdcall; far; external 'CardDLL.dll' name 'SMT_SetAuthNormalFlagByBlkVerion';
function ReadAuthCardInfo(const PCM: TPublishCardMes): LongInt;
stdcall; external 'CardDLL.dll' name 'ReadAuthCardInfo';
 //***********************************************************************

//���� dll
function calc_oper_pwd(oper_code: pchar; pwd: pchar; text: pchar): longint; stdcall; far; external 'desdll.dll' name 'calc_oper_pwd';
//function SMT_ControlBuzzer: longint; stdcall; external 'KS_ThirdInterface.dll' name 'SMT_ControlBuzzer';
//��ѧ����  *
function SMT_ReadCardNo(cardno: pchar): longint; stdcall; external 'KS_ThirdInterface.dll' name 'SMT_ReadCardNo';
//��ȡ���
function SMT_ReadBalance(var Balance: integer): longint; stdcall; external 'KS_ThirdInterface.dll' name 'SMT_ReadBalance';
 //����
function SMT_PacketDelMomey(nMoney: integer; var nFlowNo: integer): longint; stdcall; external 'KS_ThirdInterface.dll' name 'SMT_PacketDelMomey';
//�򿪴���
function SMT_ConnectMF280(port: integer; baud: integer): longint; stdcall; external 'KS_ThirdInterface.dll' name 'SMT_ConnectMF280';
//�رմ���
function SMT_CloseMF280: longint; stdcall; external 'KS_ThirdInterface.dll' name 'SMT_CloseMF280';
  //���ܺ���
function encOperPwd(operCode, operPwd: string): string;
function FuncShowMessage(hdl: HWND; StrMsg: string; IntMsgType: integer): integer;
//��ȡӦ�ó���·��
function GetAppPath: string;
//�������ݿ�
function funcConnectDB(): boolean; overload;
function funcConnectDB(Pt: PDBConn): boolean; overload;
//��ѯSQL
function funcSelectSql(ASql: string; AQuery: TOraQuery; PtEnable: boolean = true): boolean;
//����param����ѯSQL
function funcSelectSqlWithParams(AQuery: TOraQuery; PtEnable: boolean = true): boolean;

//ִ��SQL
function funcExcuteSql(ASql: string; AQuery: TOraQuery; PtEnable: boolean = true): boolean;

//����param��ִ��SQL
function funcExcuteSqlForChinese(AQuery: TOraQuery; PtEnable: boolean = true): boolean;
function writelog(strmessage: string): boolean;
//��ȡINI�ļ�
procedure procGetIniInfo;
//д��INI�ļ�
procedure procWriteIniInfo();
//��ȡϵͳĿ¼
function funcGetSystemDir: string;
//��ȡ���ַ���
function FuncGetSubStr(Str, AStart, AEnd: string): string;
//���ַ����õ���ֵ
function Fun_CurrGetValue(SrcStr: string): Double;
//����ֵ�õ�ǧ��λ�ַ���
function Fun_StrFormatEditValue(Curr: Double): string;
//�������õ���ֵ
function Fun_CurrGetEditValue(SrcObj: TEdit): Double;
//�����ǧ��λ�õ���׼�ַ���
function Fun_StrGetFloatStr(SrcStr: string): string;
//����ת������
function funcConvertDate(ADate: string): TDate;
function funcFillZero(AID: string; len: integer = 10): string;
//��1�����ַ���ǰ���0
function funcGetNewID(AID: string; Len: Integer = 10): string;
//ȥ���ַ����пո�
function funcEraseStringSpace(AStr: string): string;

function GetNextStr(var SrcStr: string; ASPLIT: string = ','): string;
//�ͷŷ�������ݼ��ڴ�
procedure procDestroyDBSET;
 //���ؿͻ���Ϣ
procedure procDownloadcustomer;
  //����ʱ���
procedure procDownloadLUNCHRDATE;
procedure procUploaddata;
procedure procDownloaddata;
procedure saveUserCode(userCode: string);
function readUserCode(): string;

implementation


function writelog(strmessage: string): boolean;
var
  myfile: TextFile;
  size, FileHandle: Integer;
  filename: string;
  patch: string;
  writestr: string;
begin
  result := true;
  patch := ExtractFilePath(ParamStr(0));
  filename := patch + 'log.txt';
  AssignFile(myfile, filename);
  try
    if FileExists(filename) then
    begin
      Append(myfile);
    end
    else
      ReWrite(myfile);
    writestr := FormatdateTime('yyyymmdd hhmmss', now()) + ':' + strmessage;
    Writeln(myfile, writestr);
  finally
    CloseFile(myfile);
  end;
  result := false;
end;


function readUserCode(): string;
var
  iniFile: TiniFile;
  sFile: string;
begin
  sFile := GetAppPath + USERCODEFILE;
  iniFile := TIniFile.Create(sFile);
  result := '';
  try
    result := iniFile.ReadString('usercode', 'usename', '');

  finally
    iniFile.Free;
  end;

end;

procedure saveUserCode(userCode: string);
var
  INI: TIniFile;
  sFile: string;
begin
  sFile := GetAppPath + USERCODEFILE;
  INI := TIniFile.Create(sFile);
  try
    ini.Writestring('usercode', 'usename', userCode);
  finally
    Ini.Free;
  end;
end;


procedure procDestroyDBSET;
begin
  DBQuery.Close;
  DBQueryTmp.Close;
  DBQueryBak.Close;
  dllnamelist.Free;
  menunamelist.Free;
end;



procedure procDownloadLUNCHRDATE;
var
  i: integer;
  sSql: string;
  sltb: TSQLIteTable;
begin
  try
    sSql := 'select t.ORDID,t.BG_DATE,t.BG_TIME,t.ED_DATE,t.ED_TIME,t.RECODE ' +
      'from T_TIF_LUNCHRDATE t ';
    procGetIniInfo;
    if funcConnectDB() then
    begin
      DBQuery.Connection := DBConn;
      funcSelectSql(sSql, DBQuery);
    end;
    if DBQuery.RecordCount < 1 then
    begin
      writelog('���ݿ���û��ʱ�����Ϣ��');
  //  FuncShowMessage(Application.Handle, '���ݿ���û��ʱ�����Ϣ��', 2);
    end
    else
    begin
      sSQL := 'delete from T_TIF_LUNCHRDATE;';
      sldb.ExecSQL(sSQL);
      for i := 1 to DBQuery.RecordCount do
      begin
        sldb.BeginTransaction;
        sSQL := 'INSERT INTO T_TIF_LUNCHRDATE(ORDID,BG_DATE,BG_TIME,ED_DATE,ED_TIME,RECODE) VALUES (';
        sSQL := sSQL + '"' + DBQuery.FieldByName('ORDID').AsString + '",';
        sSQL := sSQL + '"' + DBQuery.FieldByName('BG_DATE').AsString + '",';
        sSQL := sSQL + '"' + DBQuery.FieldByName('BG_TIME').AsString + '",';
        sSQL := sSQL + '"' + DBQuery.FieldByName('ED_DATE').AsString + '",';
        sSQL := sSQL + '"' + DBQuery.FieldByName('ED_TIME').AsString + '",';
        sSQL := sSQL + '"' + DBQuery.FieldByName('RECODE').AsString + '"';
        sSQL := sSQL + ');';
      //do the insert
        sldb.ExecSQL(sSQL);
        sldb.Commit;
      end;
    end;
  except
    writelog('����ʱ�����Ϣ��');
  end;
  DBQuery.Close;
end;

procedure procDownloadcustomer;
var
  i: integer;
  ssql: string;
  sltb: TSQLIteTable;
  state: string;
  card: string;
  phi: string;

  serverOrigCardID: string;
  serverNewCardID: string;
  localPHYID: string;
  serverCardNo: string;
  recCount: integer;
begin
  try
    sSql := 'select t.cut_id,t.cut_type,t.cut_state,t.cut_name,t.stuemp_no,t.sex,' +
      't.man_id, t.card_id, t.state,t.phy_id from t_cif_cosumer_lunch t';
    procGetIniInfo;
    if funcConnectDB() then
    begin
      DBQuery.Connection := DBConn;
      DBQuery.FetchRows := 10000;
      funcSelectSql(sSql, DBQuery);
    end;
    if DBQuery.RecordCount < 1 then
    begin
      writelog('���ݿ���û���ҵ���ѧ������Ϣ��');
    end
    else
    begin
      for i := 1 to DBQuery.RecordCount do
      begin
        sSql := 'select card_id,physical_no from t_pif_card where cosumer_id=''' + DBQuery.FieldByName('cut_id').AsString + ''' and state_id=''1000'' ';
        if funcConnectDB() then
        begin
          DBQuerytmp.Connection := DBConn;
          funcSelectSql(sSql, DBQuerytmp);
          card := DBQuerytmp.FieldByName('card_id').AsString;
          phi := DBQuerytmp.FieldByName('physical_no').AsString;
          recCount := DBQuerytmp.RecordCount;
          DBQuerytmp.Close;
        end;
        if recCount > 0 then
        begin
          if DBQuery.FieldByName('state').AsString = '3' then
          begin
            state := '3';
          end
          else
          begin
            state := '1';
          end;
        end
        else
        begin
          state := '3';
        end;
        if (state = '1') then begin
          ssql := 'update  t_cif_cosumer_lunch set card_id=''' + card + ''',phy_id=''' + phi + ''' where cut_id=' + DBQuery.FieldByName('CUT_ID').AsString;
          if funcConnectDB() then
          begin
            DBQueryTmp.Connection := DBConn;
            try
              DBQueryTmp.SQL.Text := sSql;
              if debug = 'true' then
                writelog(sSql);
              funcExcuteSql(sSql, DBQueryTmp);
            except
            end;
          end;
          ssql := 'SELECT * FROM t_pif_cosumer where cut_id=' + DBQuery.FieldByName('CUT_ID').AsString;
          sltb := slDb.GetTable(ssql);
          try
            if (sltb.Count > 0) then begin
              sldb.BeginTransaction;
              ssQL := 'update t_pif_cosumer set phy_id=''' + phi + ''',card_id=''' + card + ''' where cut_id=''' + DBQuery.FieldByName('CUT_ID').AsString + '''';
              sldb.ExecSQL(ssQL);
              sldb.Commit;
            end
            else begin
              sldb.BeginTransaction;
              sSQL := 'INSERT INTO t_pif_cosumer(cut_id,cut_type,cut_state,cut_name,stuemp_no,sex,man_id,card_id,phy_id) VALUES (';
              sSQL := sSQL + '"' + DBQuery.FieldByName('CUT_ID').AsString + '",';
              sSQL := sSQL + '"' + DBQuery.FieldByName('cut_type').AsString + '",';
              sSQL := sSQL + '"' + DBQuery.FieldByName('cut_state').AsString + '",';
              sSQL := sSQL + '"' + DBQuery.FieldByName('cut_name').AsString + '",';
              sSQL := sSQL + '"' + DBQuery.FieldByName('stuemp_no').AsString + '",';
              sSQL := sSQL + '"' + DBQuery.FieldByName('sex').AsString + '",';
              sSQL := sSQL + '"' + DBQuery.FieldByName('man_id').AsString + '",';
              sSQL := sSQL + '"' + card + '",';
              sSQL := sSQL + '"' + phi + '"';
              sSQL := sSQL + ');';
              sldb.ExecSQL(sSQL);
              sldb.Commit;
            end;
          finally
            sltb.Free;
          end;
        end
        else begin
          sldb.BeginTransaction;
          ssQL := 'delete from t_pif_cosumer where cut_id=''' + DBQuery.FieldByName('CUT_ID').AsString + '''';
          sldb.ExecSQL(ssQL);
          sldb.Commit;
        end;
        DBQuery.Next;
      end;
      DBQuery.Close;

    end;
  except
    writelog('���ؿͻ���Ϣʧ�ܣ�');
  end;

end;


procedure procUploaddata;
var
  i: integer;
  sSql: string;
  sltb: TSQLIteTable;
  TX_DATE: string;
  TX_TIME: string;
  CARD_NO: string;
  DEVICE_ID: string;
  SERIAL_NO: string;
  reCount: integer;
begin
  try
    sltb := slDb.GetTable('SELECT * FROM T_TIF_LUNCHRCVDTL where  STATUS=''1''');
    reCount := sltb.Count;
    if reCount > 0 then
    begin
      for i := 1 to reCount do
      begin
      //display first row
        TX_DATE := sltb.FieldAsString(sltb.FieldIndex['TX_DATE']);
        TX_TIME := sltb.FieldAsString(sltb.FieldIndex['TX_TIME']);
        CARD_NO := sltb.FieldAsString(sltb.FieldIndex['CARD_NO']);
        DEVICE_ID := sltb.FieldAsString(sltb.FieldIndex['DEVICE_ID']);
        SERIAL_NO := sltb.FieldAsString(sltb.FieldIndex['SERIAL_NO']);
        sltb.Next;
        sSql := 'insert into T_TIF_LUNCHRCVDTL(TX_DATE,TX_TIME,CARD_NO,DEVICE_ID,SERIAL_NO,' +
          'PURSE_NO,IN_BALA,OUT_BALA,AMOUNT,TOTAL_CNT,TX_CODE,TX_MARK,COMU_VER,RUN_REASON,CRC,' +
          'INPOWER_NO,SYS_ID,OPER_NO,STATUS,COL_TIMESTAMP,FEE_CODE,ERR_CODE,MANAGE_FEE,OPERATE_DATE,OPERATE_TIME)' +
          ' values(''' + TX_DATE + ''',''' + TX_TIME + ''', ''' + CARD_NO + ''',''' + DEVICE_ID + ''',''' + SERIAL_NO + ''',' +
          '0,0,0,0,0,0,0,0,0,'''','''',0,'''',''2'','''',0,0,0,'''','''')';
        if funcConnectDB() then
        begin
          DBQueryTmp.Connection := DBConn;
          try
            DBQueryTmp.SQL.Text := sSql;
            if debug = 'true' then
              writelog(sSql);
            funcExcuteSql(sSql, DBQueryTmp);
            sSQL := 'update T_TIF_LUNCHRCVDTL set STATUS=''2'' where CARD_NO=''' + CARD_NO + '''';
            sldb.ExecSQL(sSQL);
            if debug = 'true' then
              writelog(sSql + '�ύ�ɹ���');
          except
            //if debug = 'true' then
            writelog(sSql + '�ύʧ�ܣ�');
          end;
        end;
      end;
    end;
    sSQL := 'delete from T_TIF_LUNCHRCVDTL  where TX_DATE<''' + FormatdateTime('yyyymmdd', now()) + ''' and STATUS=''2''';
    sldb.ExecSQL(sSQL);
    if debug = 'true' then
      writelog(sSql + '�ύ�ɹ���');
  finally
    sltb.Free;
  end;
end;

procedure procDownloaddata;
var
  i: integer;
  sSql: string;
  sltb: TSQLIteTable;
  cardid: string;
  TX_DATE: string;
  TX_TIME: string;
  CARD_NO: string;
  DEVICE_ID: string;
  SERIAL_NO: string;
  recCount: integer;
begin

  try
    sSql := 'select * from T_TIF_LUNCHRCVDTL where TX_DATE=''' + FormatdateTime('yyyymmdd', now()) + ''' ';
    procGetIniInfo;
    if funcConnectDB() then
    begin
      DBQuery.Connection := DBConn;
      DBQuery.FetchRows := 10000;
      funcSelectSql(sSql, DBQuery);
      for i := 1 to DBQuery.RecordCount do
      begin
        TX_DATE := DBQuery.FieldByName('TX_DATE').AsString;
        TX_TIME := DBQuery.FieldByName('TX_TIME').AsString;
        CARD_NO := DBQuery.FieldByName('CARD_NO').AsString;
        DEVICE_ID := DBQuery.FieldByName('DEVICE_ID').AsString;
        SERIAL_NO := DBQuery.FieldByName('SERIAL_NO').AsString;
        try
          sltb := slDb.GetTable('SELECT *  FROM T_TIF_LUNCHRCVDTL where   CARD_NO=''' + CARD_NO + '''');
          recCount := sltb.Count;
        finally
          sltb.Free;
        end;
        try
          if recCount > 0 then
          begin
          end
          else
          begin
            sldb.BeginTransaction;
            sSql := 'insert into T_TIF_LUNCHRCVDTL(TX_DATE,TX_TIME,CARD_NO,DEVICE_ID,SERIAL_NO,' +
              'PURSE_NO,IN_BALA,OUT_BALA,AMOUNT,TOTAL_CNT,TX_CODE,TX_MARK,COMU_VER,RUN_REASON,CRC,' +
              'INPOWER_NO,SYS_ID,OPER_NO,STATUS,COL_TIMESTAMP,FEE_CODE,ERR_CODE,MANAGE_FEE,OPERATE_DATE,OPERATE_TIME)' +
              ' values(''' + TX_DATE + ''',''' + TX_TIME + ''', ''' + CARD_NO + ''',''' + DEVICE_ID + ''',''' + SERIAL_NO + ''',' +
              '0,0,0,0,0,0,0,0,0,'''','''',0,'''',''2'','''',0,0,0,'''','''')';
            sldb.ExecSQL(sSQL);
            sldb.Commit;
            if debug = 'true' then
              writelog(sSql + '���سɹ���');
          end
        except
          if debug = 'true' then
            writelog(sSql + '����ʧ�ܣ�');
        end;

        DBQuery.Next;
      end;
      DBQuery.Close;
    end;
  except
    writelog('����TIF_LUNCHRCVDTL����');
  end;


end;


function GetNextStr(var SrcStr: string; ASPLIT: string = ','): string;
var
  i: integer;
begin
  result := '';
  if SrcStr = '' then exit;
  i := pos(ASPLIT, SrcStr);
  if i <> 0 then
  begin
    result := copy(SrcStr, 1, i - 1);
    SrcStr := copy(SrcStr, i + Length(ASPLIT), Length(SrcStr));
  end
  else
  begin
    result := SrcStr;
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
  while outwhile do
  begin
    getstr := GetNextStr(dllstr);
    if getstr = '' then
    begin
      outwhile := false;
    end
    else
    begin
      dllnamelist.Add(getstr);
      getstr := GetNextStr(dllstr);
      menunamelist.Add(getstr);
    end


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
  p := length(AID);
  if (p >= Len) then
    AID := copy(AID, 1, Len);
  for i := 1 to (Len - p) do
    AID := '0' + AID;
  result := AID;
end;

function funcGetNewID(AID: string; Len: Integer): string;
var
  i, p: integer;
  temp: LONGINT;
begin
  if AID = '' then
    AID := '1';
  temp := StrToInt(AID);
  inc(temp);
  AID := IntToStr(temp);
  result := funcFillZero(AID, Len);
end;

function funcConvertDate(ADate: string): TDate;
var
  tmp: char;
begin
  result := Date();
  if length(ADate) <> 8 then exit;
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
    result := Fun_CurrGetValue(SrcObj.Text);
  except
    on e: exception do begin
      SrcObj.SetFocus();
      SrcObj.SelectAll();
      raise Exception.Create(e.message);
    end;
  end;
end;

function Fun_StrFormatEditValue(Curr: Double): string;
var
  str: string;
begin
  str := SysUtils.FloatToStrF(Curr, ffFixed, 18, 4);
  result := SysUtils.FormatFloat('#,##0.00', Fun_CurrGetValue(str));
end;

function Fun_CurrGetValue(SrcStr: string): Double; //�������õ���ֵ
var str: string;
  i: integer;
  c, d: char;
begin
  result := 0;
  for i := 1 to Length(SrcStr) do
    if SrcStr[i] in ['0'..'9', '.', '-'] then str := str + SrcStr[i];
  if str = '' then exit;
  try
    c := #0;
    i := pos('.', Str);
    if (i > 14) or ((i = 0) and (Length(str) > 14)) then raise Exception.Create('');
    if (i > 0) and (Length(Str) >= i + 3) then begin
      c := Str[i + 3];
      Str := copy(Str, 1, i + 2);
    end;
    d := sysutils.DecimalSeparator;
    sysutils.DecimalSeparator := '.';
    result := SysUtils.StrToFloat(str);
    if c in ['5'..'9'] then result := result + 0.01;
    sysutils.DecimalSeparator := d;
  except
    on e: Exception do begin
      raise Exception.Create('ֵ�������Ч!' + str + #13 + e.Message);
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
  dir: array[0..255] of char;
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
  {
    Ini.WriteString('DB', 'DBIP', DBIP);
    Ini.WriteString('DB', 'PORT', port);
    Ini.WriteString('DB', 'SOURCE', DBSOURCE);
    Ini.WriteString('DB', 'USER', DBUSER);
    Ini.WriteString('DB', 'PASS', DBPASS);
    Ini.WriteString('dll', 'dllname', DBPASS);
    Ini.Writeinteger('pos', 'port', posport);
    Ini.Writeinteger('pos', 'baud', baud);
    ini.Writestring('device', 'DEVPHYID', DEVPHYID);
   }
    ini.Writestring('use', 'usename', usename);
  finally
    Ini.Free;
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
    DBIP := INI.ReadString('DB', 'DBIP', '');
    port := INI.ReadString('DB', 'PORT', '');
    DBSOURCE := INI.ReadString('DB', 'DBSOURCE', '');
    DBUSER := INI.ReadString('DB', 'USER', '');
    DBPASS := INI.ReadString('DB', 'PASS', '');
    posport := INI.Readinteger('pos', 'posport', 1);
    baud := INI.Readinteger('pos', 'baud', 19200);
    DEVPHYID := INI.Readstring('device', 'TERMID', '');
    usename := INI.ReadString('use', 'usename', '');
    debug := INI.readstring('use', 'debug', 'false');
    voice := INI.ReadString('use', 'voice', 'f_');
    usename := INI.ReadString('use', 'usename', '');
    updatetime := INI.Readinteger('use', 'updatetime', 0);
    ORA_CONNECT_STRING := '' + DBUSER + '' + '/' + '' + DBPASS + '' + '@' + '' + DBIP + '' + ':' + '' + port + '' + ':' + '' + DBSOURCE + '';
  finally
    INI.Free;
  end;
end;

{$WARNINGS OFF}

function FuncShowMessage(hdl: HWND; StrMsg: string; IntMsgType: integer): integer;
begin
  result := 0;
  case IntMsgType of
    0: MessageBox(HDL, Pchar(StrMsg), '��ʾ', MB_OK + MB_ICONINFORMATION);
    1: MessageBox(HDL, Pchar(StrMsg), '����', MB_OK + MB_ICONWARNING);
    2: MessageBox(HDL, Pchar(StrMsg), '����', MB_OK + MB_ICONERROR);
    3: result := MessageBox(HDL, Pchar(StrMsg), '��ʾ', MB_YESNO + MB_ICONQUESTION);
    4: result := MessageBox(HDL, Pchar(StrMsg), '��ʾ', MB_YESNOCANCEL + MB_ICONQUESTION);
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
    DBConn := TOraSession.Create(nil);
  end;
  DBConn.Options.Net := true;
  if DBQuery = nil then
    DBQuery := TOraQuery.Create(nil);
  if DBQueryTmp = nil then
    DBQueryTmp := TOraQuery.Create(nil);
  if DBQueryBak = nil then
    DBQueryBak := TOraQuery.Create(nil);
 // DBCONNSTR := format(ORA_CONNECT_STRING, [DBPASS, DBUSER, DBSOURCE]);
  if Pt^.Connected then
  begin
    result := true;
    DBQuery.Connection := Pt^;
    DBQueryTmp.Connection := Pt^;
    DBQueryBak.Connection := Pt^;
    result := true;
    exit;
  end;
  try
    Pt^.SQL.Text := ORA_CONNECT_STRING;
    Pt^.LoginPrompt := false;
    DBQuery.Connection := Pt^;
    DBQueryTmp.Connection := Pt^;
    DBQueryBak.Connection := Pt^;
    Pt^.Connected := true;
  except
    on e: exception do
      writelog('���Ӵ���:' + e.Message);
  //    FuncShowMessage(Application.Handle, '���Ӵ���:' + e.Message, 2);
  end;
  result := true;
end;

function funcConnectDB(): boolean;
begin
  result := false;
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
 // DBCONNSTR := format(ORA_CONNECT_STRING, [DBPASS, DBUSER, DBSOURCE]);
  //FuncShowMessage(Application.Handle,DBCONNSTR,0);
  if DBConn.Connected then
  begin
    result := true;
    DBQuery.Connection := DBConn;
    DBQueryTmp.Connection := DBConn;
    DBQueryBaK.Connection := DBConn;
    result := true;
    exit;
  end;
  try

    DBConn.ConnectString := ORA_CONNECT_STRING;
    DBConn.LoginPrompt := false;
    DBQuery.Connection := DBConn;
    DBQueryTmp.Connection := DBConn;
    DBQueryBaK.Connection := DBConn;
    //DBConn.Options.Net:=false;
    DBConn.Open();
  except
    on e: exception do
    begin
      writelog('���Ӵ���:' + e.Message);
    //  FuncShowMessage(Application.Handle, '���Ӵ���:' + e.Message, 2);
      exit;
    end;
  end;
  result := true;
end;

function funcSelectSqlWithParams(AQuery: TOraQuery; PtEnable: boolean = true): boolean;
begin
  if PtEnable then
  begin
    result := PtConn^.Connected;
    if not PtConn^.Connected then
    begin
      if not funcConnectDB(PtConn) then exit;
    end;
  end
  else
  begin
    result := DBConn.Connected;
    if not DBConn.Connected then
    begin
      if not funcConnectDB() then exit;
    end;
  end;
  AQuery.Open;
  AQuery.First;
  result := true;
end;


function funcSelectSql(ASql: string; AQuery: TOraQuery; PtEnable: boolean = true): boolean;
begin

  try
    if not DBConn.Connected then
    begin
      if not funcConnectDB() then exit;
    end;
    AQuery.Close;
    AQuery.SQL.Clear;
    AQuery.SQL.Text := ASql;
    AQuery.Open;
    AQuery.First;
    result := true;
  except
  end;
end;

function encOperPwd(operCode, operPwd: string): string;
var
  outOperPwd: array[0..16] of Char;
  st: Integer;
begin
  st := calc_oper_pwd(PChar(operCode), PChar(Trim(operPwd)), @outOperPwd);
  if st <> 0 then
  begin
    FuncShowMessage(Application.Handle, '����ʧ�ܣ�', 2);
    Result := '';
    Exit;
  end;
  Result := outOperPwd;
end;

function funcExcuteSql(ASql: string; AQuery: TOraQuery; PtEnable: boolean = true): boolean;
begin
  result := false;
  if PtEnable then
  begin

    result := DBConn.Connected;
    if not DBConn.Connected then
    begin
      if not funcConnectDB() then exit;
    end;
  end;
  AQuery.Close;
  AQuery.SQL.Clear;
  AQuery.SQL.Text := ASql;
  AQuery.ExecSQL;
  result := true;
end;

function funcExcuteSqlForChinese(AQuery: TOraQuery; PtEnable: boolean = true): boolean;
begin
  result := false;
  if PtEnable then
  begin
    result := PtConn^.Connected;
    if not PtConn^.Connected then
    begin
      if not funcConnectDB(PtConn) then exit;
    end;
  end
  else
  begin
    result := DBConn.Connected;
    if not DBConn.Connected then
    begin
      if not funcConnectDB() then exit;
    end;
  end;

  AQuery.ExecSQL;
  result := true;
end;
{ TUserInfo }



constructor TUserInfo.Create(AName, APwd: string);
begin
  self.UserName := AName;
  self.Password := APwd;
end;

function TUserInfo.funcGetMenuList: boolean;
var
  i, j, k: integer;
  sSql, ParentID, ChildID: string;
begin
  SetLength(MenuList, i + 1);
  MenuList[i].Caption := 'ҽ���շ�';
  MenuList[i].ID := '1';
  MenuList[i].isValid := true;
  for j := 1 to dllnamelist.Count do
  begin
    SetLength(MenuList[i].SubMenu, j + 1);
    MenuList[i].SubMenu[j].Caption := menunamelist[j - 1];
    MenuList[i].SubMenu[j].ID := inttostr(j);
    MenuList[i].SubMenu[j].DLL := dllnamelist[j - 1];
    MenuList[i].SubMenu[j].isVisble := true;
  end;
  result := true;
end;

function TUserInfo.funcLogin: integer;
var
  sSql: string;
  input: string;
  status: string;
  opertype: string;
begin
  result := -1;
  sSql := 'select * from  t_operator where opercode= :f1';
  DBQuery.close;
  DBQuery.SQL.Clear;
  DBQuery.SQL.Text := sSql;
  DBQuery.Params[0].AsWideString := self.UserName;

  if funcSelectSqlWithParams(DBQuery, false) then
  begin
    if DBQuery.RecordCount <> 1 then
    begin
      result := 1;
      exit;
    end
    else
    try
      input := encOperPwd(self.UserName, Self.Password);
    except
    end;
    if UpperCase(DBQuery.FieldByName('operpwd').AsString) <> input then
    begin
      result := 2;
      exit;
    end
    else
    begin
      opertype := DBQuery.FieldByName('opertype').AsString;
      if opertype <> '3' then
      begin
        result := 5;
        exit;
      end;
      status := DBQuery.FieldByName('STATUS').AsString;
      if status <> '1' then
      begin
        if status = '0' then
          result := 3;
        if status = '2' then
          result := 4;
      end
      else
        result := 0;
    end;
  end;
end;

function TUserInfo.GetCNName: string;
begin
  result := self.CNName;
end;

function TUserInfo.GetPassword: string;
begin
  result := self.Password;
end;

function TUserInfo.GetUserName: string;
begin
  result := self.UserName;
end;


end.

