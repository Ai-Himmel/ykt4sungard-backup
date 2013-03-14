unit SmartCardCommon;

interface

uses
  SysUtils, Controls, Math,KSFrameWorkUtils,KSClientConsts,classes,Dialogs,
  RzDTP,ComCtrls,Graphics,DBGrids,IniFiles,Forms,FilterCombos,KSChineseSpell,
  WVCtrls;

const
   SuperOperator = 'system'; //��ʼ���Ĳ���Ա

var
  AssetOwesKind:TStringList;
  CurrentOperateRecordNo:TStringList;
  function SpareseBirthdayAndSex(const IDcard:String; out Birthday:TDate;
                                out Sex:String):Boolean;
  function ValidateIDcard(IDcard:String; out ErrMsg:String):Boolean;
  function IsValidDate(const AYear, AMonth, ADay: Word): Boolean;
  function UpgrateIDCard(OldIDCard:String):String;
  {�����ַ��Ƿ�ȫ�����������}
  function CheckNumber(IStr:String):Boolean;
  {����ip��ַ�Ƿ���ȷ}
  function CheckIpAddress(const AIpString:String):String;
  {����MAC��ַ�Ƿ���ȷ}
  function CheckMACAddress(const AMACString:String):String;
  {�õ������Ĭ����ʼ����}
  function GetReportDefaultBeginDate:String;
  {�õ������Ĭ�Ͻ�������}
  function GetReportDefaultEndDate:String;
  {����绰�����Ƿ�Ϸ�}
  function CheckTelNumber(IStr:String):Boolean;
  {��������ID�Ƿ�Ϸ�}
  function CheckEquipPhyID(const IStr:String):String;

  {�Ƿ�ȫ�������֡�Ӣ����ĸ���Լ� "-","_"��ɣ�������Ҫ���ڸ����û������ע���ж�}
  function CheckCodeValid(IStr:String):Boolean;
  {�����ֻ������Ƿ�Ϸ�}
  function CheckMobileNumber(IStr:String):Boolean;
  {�������������ַ����Ƿ�Ϸ�}
  function CheckInputDateFormat(input: string): boolean;
  {��������ʱ���ַ����Ƿ�Ϸ�}
  function CheckInputTimeFormat(input: string): boolean;
  {�õ������Ĭ�Ͽ�ʼʱ��}
  function GetReportDefaultBeginTime:string;
  {�õ������Ĭ�Ͻ���ʱ��}
  function GetReportDefaultEndTime:string;

  {�Զ�����������}
  function DBGridRecordSize(mColumn: TColumn): Boolean;
  function DBGridAutoSize(mDBGrid: TDBGrid; mOffset: Integer = 5): Boolean;

  function inputNum(key:Char): Boolean;
  function Checkedt(key:Char;dot:string): Boolean;

  {�Զ�����־�ļ�д��}
  procedure WriteLog(inText: string);

  //�ļ���־��д�룬�����Զ����ļ���
  procedure wLog(sfile,inText: string);

  function ValidatePID(const APID: string): string;

  //��combobox�е�������䵽filtercombobox��
  procedure fillData2FilterCbb(var FSpells,FDisplayItems:TStringList;sCbb:TWVComboBox);
  procedure cbbFilterItem( FSpells,FDisplayItems:TStringList;sender:TObject);

  function strToZero(inStr:string):string;
  {����ҽ���Сдת���ĺ���}
  Function NtoC(n0 :real) :String;
  //�ַ�������ʱ�����㣬��ʽyyyymmdd
  function shadate(MaxDate,MinDate:string):Integer ;

type {��Կ���е�����༭�����ϵͳ������ѡ���}
  TPrivateDefine=Class;

  TPrivateDefine=Class
  private

  public
    FMonthCalendar :TMonthCalendar;
    FOutDate:TDate;

    constructor Create(FParent:TWinControl);overload;
    destructor Destroy; override;
    procedure CalendarInitial(Fdate:TDate);
    procedure CalendarOnclick(Sender: TObject);
    procedure MonthCalendar1GetMonthInfo(Sender: TObject;
  Month: Cardinal; var MonthBoldInfo: Cardinal);
end;

type
  TWorkerRecordList = record
    WorkerNo:String;
    WorkerName:String;
    WorkerUnit:String;
    WorkerPolicy:Integer;
    WorkerCardId:String;
    WorkerStatus:Integer;
    WorkerSex:String;
    WorkerKind:Integer;
    WorkerNation:Integer;
    WorkerEmpNo:Integer;
    WorkerAdd:String;
    WorkerPhone:String;
  end;

implementation

constructor TPrivateDefine.Create(FParent:TWinControl);
begin
  FMonthCalendar:=TMonthCalendar.Create(nil);
  FMonthCalendar.parent:=FParent;
  FMonthCalendar.OnClick:=CalendarOnclick;
end;

destructor TPrivateDefine.Destroy;
begin
  FMonthCalendar.Destroy;
  inherited;
end;

function GetReportDefaultBeginTime:string;
begin
  Result:='';
  Result:= '140000';
end;

function GetReportDefaultEndTime:string;
begin
  Result:='';
  Result:= '140000';
end;


function CheckInputDateFormat(input: string): boolean;
{
  function SpliteDateStr(input: string) : string;
  begin
    Result := '';
    if length(input) <> 8 then
      Exit;
    Result := Format('%s-%s-%s',
      [Copy(input,1,4),Copy(input,5,2),Copy(input,7,2)]);
  end;
begin
  Result := False;
  input := trim(input);
  if length(input) = 8 then
  begin
    try
      StrToDateTime(SpliteDateStr(input));
      Result := True;
    except
    end;
  end;
  }
var
  sYear,sMonth,sDate:Word;
begin
  Result := False;
  try
    sYear := StrToInt(Copy(Trim(input),1,4));
    sMonth := StrToInt(Copy(Trim(input),5,2));
    sDate := StrToInt(Copy(Trim(input),7,2));
    EncodeDate(syear,smonth,sdate);
    Result := True;
  except

  end;
end;



{-------------------------------------------------------------------------------
  ������:    CheckInputTimeFormat����ʱ���ʽ���
  ����:      ����ΰ
  ����:      2005.08.03
  ����:      input: string
  ����ֵ:    boolean
-------------------------------------------------------------------------------}
function CheckInputTimeFormat(input: string): boolean;
{
  function SpliteTimeStr(input: string) : string;
  begin
    Result := '';
    if length(input) <> 6 then
      Exit;
    Result := Format('%s:%s:%s',
      [Copy(input,1,2),Copy(input,3,2),Copy(input,5,2)]);
  end;
begin
  Result := False;
  if length(input) = 6 then
  begin
    try
      StrToTime(SpliteTimeStr(input));
      Result := True;
    except
    end;
  end;
  }
var
  sHour, sMin, sSec, sMSec:Word;
begin
  Result := false;
  try
    sHour := StrToInt(Copy(Trim(input),1,2));
    sMin:= StrToInt(Copy(Trim(input),3,2));
    sSec := StrToInt(Copy(Trim(input),5,2));
    sMSec := 0;
    EncodeTime(sHour,sMin,sSec,sMSec);
    Result := True;
  except

  end;
end;


{-------------------------------------------------------------------------------
  ������:    CheckMobileNumber �ƶ��绰������Ч�Լ��
  ����:      ����ΰ
  ����:      2005.08.03
  ����:      IStr:String
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function CheckMobileNumber(IStr:String):Boolean;
var i,len:Integer;
begin
  Result:=True;
  len:=length(IStr);
  for i:=1 to len do
  begin
    if (IStr[i]='1')or(IStr[i]='2')or(IStr[i]='3')or(IStr[i]='4')or
       (IStr[i]='5')or(IStr[i]='6')or(IStr[i]='7')or(IStr[i]='8')or
       (IStr[i]='9')or(IStr[i]='0') then
    begin
      Continue;
    end
    else
    begin
      Result:=False;
      Break;
    end;
  end;
end;


function CheckCodeValid(IStr:String):Boolean;
var i,len:Integer;
begin
  Result:=True;
  len:=length(IStr);
  for i:=1 to len do
  begin
    
    if (IStr[i]='1')or(IStr[i]='2')or(IStr[i]='3')or(IStr[i]='4')or
       (IStr[i]='5')or(IStr[i]='6')or(IStr[i]='7')or(IStr[i]='8')or
       (IStr[i]='9')or(IStr[i]='0')or(IStr[i]='a')or(IStr[i]='A')or
       (IStr[i]='b')or(IStr[i]='B')or(IStr[i]='c')or(IStr[i]='C')or
       (IStr[i]='d')or(IStr[i]='D')or(IStr[i]='e')or(IStr[i]='E')or
       (IStr[i]='f')or(IStr[i]='F')or(IStr[i]='g')or(IStr[i]='G')or
       (IStr[i]='h')or(IStr[i]='H')or(IStr[i]='i')or(IStr[i]='I')or
       (IStr[i]='j')or(IStr[i]='J')or(IStr[i]='k')or(IStr[i]='K')or
       (IStr[i]='l')or(IStr[i]='L')or(IStr[i]='n')or(IStr[i]='N')or(IStr[i]='m')or(IStr[i]='M')or
       (IStr[i]='o')or(IStr[i]='O')or(IStr[i]='p')or(IStr[i]='P')or
       (IStr[i]='q')or(IStr[i]='Q')or(IStr[i]='r')or(IStr[i]='R')or(IStr[i]='s')or(IStr[i]='S')or
       (IStr[i]='t')or(IStr[i]='T')or(IStr[i]='u')or(IStr[i]='U')or
       (IStr[i]='v')or(IStr[i]='V')or(IStr[i]='w')or(IStr[i]='W')or
       (IStr[i]='x')or(IStr[i]='X')or(IStr[i]='y')or(IStr[i]='Y')or
       (IStr[i]='Z')or(IStr[i]='z')or(IStr[i]='-')or(IStr[i]='_') 
       then
    begin
      Continue;
    end
    else
    begin
      Result:=False;
      Break;
    end;
  end;
end;


procedure TPrivateDefine.MonthCalendar1GetMonthInfo(Sender: TObject;
  Month: Cardinal; var MonthBoldInfo: Cardinal);
begin
  Showmessage('');
  self.Destroy;
end;


function strToZero(inStr:string):string;
begin
  if Trim(inStr)='' then
    Result := '0'
  else
    Result := Trim(inStr);
end;

procedure TPrivateDefine.CalendarOnclick(Sender: TObject);
begin
  FOutDate:=FMonthCalendar.Date;
end;


procedure TPrivateDefine.CalendarInitial(Fdate:TDate);
begin
  FMonthCalendar.Date:=Fdate;
  FMonthCalendar.CalColors.BackColor:=clWindow;
  FMonthCalendar.CalColors.TextColor:=clblack;
  FMonthCalendar.CalColors.TitleBackColor:=$00EBDED0;
  //FMonthCalendar.CalColors.
end;




function GetReportDefaultBeginDate:String;
var TmpDate:TDate;
    TmpString:String;
begin
  Result:='';
  Result:= GetSystemDate;
  TmpDate:=DBStrDateToDateTime(Result);
  TmpDate:=TmpDate-1;

  TmpString:=formatDatetime(NormalDateTimeFormat,TmpDate);
  Result:=TmpString;
end;


function GetReportDefaultEndDate:String;
var TmpDate:TDate;
    TmpString:String;
begin
  Result:='';
  Result:= GetSystemDate;
  TmpDate:=DBStrDateToDateTime(Result);
  TmpDate:=TmpDate-1;

  TmpString:=formatDatetime(NormalDateTimeFormat,TmpDate);
  Result:=TmpString;
end;


function CheckIpAddress(const AIpString:String):String;
var len:Integer;
    IStr:String;
    i:Integer;
    ISubStr:String;
begin
  Result:='';
  IStr:= Trim(AIpString);
  len:=length(IStr);
  try
    //������һλ�������֣���ʾ����
    //ShowMessage(Copy(IStr,Length(IStr)-1,1));
    if StrToInt(Copy(IStr,Length(IStr),1))<0 then
    begin
      Result := 'IP��ַ��ʽ����ȷ��';
      Exit;
    end;
    for i:=1 to len do
    begin
      if (IStr[i]='1')or(IStr[i]='2')or(IStr[i]='3')or(IStr[i]='4')or
         (IStr[i]='5')or(IStr[i]='6')or(IStr[i]='7')or(IStr[i]='8')or
         (IStr[i]='9')or(IStr[i]='0')or(IStr[i]='.') then
      begin
        Continue;
      end
      else
      begin
        Result:='IP��ַֻ�ܰ������ֻ�"."��';
        Break;
      end;
    end;
    i:=0;
    IStr:= Trim(AIpString);
    len:=length(IStr);
    While Length(IStr)>0 do
    begin
      if Pos('.',IStr)>0 then
      begin
        ISubStr:=Copy(IStr,1,Pos('.',IStr)-1);
        i:=i+1;
      end
      else ISubStr:=IStr;

      len:=length(IStr);
      if len=0 then Break;
      if  ((StrToInt(Trim(ISubStr))<0) or  (StrToInt(Trim(ISubStr))>255)) then
      begin
        Result:='IP��ַֻ�ܰ���0~255�����֣�';
        Exit;
      end;
      if (Pos('.',IStr)>0)  then
        IStr:=Copy(IStr,Pos('.',IStr)+1,len-Pos('.',IStr))
      else IStr:='';
    end;
    if i<>3 then
    begin
        Result:='IP��ַ��ʽ����ȷ��';
        Exit;
    end;
  except
    Result := 'IP��ַ���벻��ȷ�����������룡';
  end;
end;



{Լ�������ŵ绰����֮��ķ������á�-��}
function CheckTelNumber(IStr:String):Boolean;
var i,len:Integer;
begin
  Result:=True;
  len:=length(IStr);
  for i:=1 to len do
  begin
    if (IStr[i]='1')or(IStr[i]='2')or(IStr[i]='3')or(IStr[i]='4')or
       (IStr[i]='5')or(IStr[i]='6')or(IStr[i]='7')or(IStr[i]='8')or
       (IStr[i]='9')or(IStr[i]='0')or(IStr[i]='-')or(Trim(IStr[i])='') then
    begin
      Continue;
    end
    else
    begin
      Result:=False;
      Break;
    end;
  end;
end;


function CheckMACAddress(const AMACString:String):String;
var i:Integer;
    j:String;
begin
  Result:='';
  //ShowMessage(IntToStr(length(Trim(AMACString))));
  if (length(Trim(AMACString)) =17)  then
  begin
    for i :=1 to 17 do
    begin
      j :=copy(Trim(AMACString),i,1);
      if (i=3)or(i=6)or(i=9)or(i=12)or(i=15) then
      begin
        if (j<>'-') then
        begin
          Result:='�ָ���λ�ô���';
          Exit;
        end;
      end
      else
      begin
        if not(((j>='0')and(j<='9'))or((j>='a')and(j<='f'))or((j>='A')and(j<='F')))
        then
        begin
          Result:='��������0-9����A-F֮����ַ�';
          exit;
        end;
      end;
    end;
  end
  else if AMACString <> '' then
  begin
       Result:='������ַ���ȱ���17λ';
  end;
end;


function CheckEquipPhyID(const IStr:String):String;
var i:Integer;
    j:String;
begin
  Result:='';
  //ShowMessage(IntToStr(length(Trim(AMACString))));
  if (length(Trim(IStr)) =8)  then
  begin
    for i :=1 to 8 do
    begin
      j :=copy(Trim(IStr),i,1);

      if not(((j>='0')and(j<='9'))or((j>='a')and(j<='f'))or((j>='A')and(j<='F')))
      then
      begin
        Result:='��������0-9����A-F֮����ַ�';
        exit;
      end;

    end;
  end
  else if IStr <> '' then
  begin
       Result:='�豸����ID���ȱ���8λ';
  end;
end;


function CheckNumber(IStr:String):Boolean;
var i,len:Integer;
begin
  Result:=True;
  len:=length(IStr);
  for i:=1 to len do
  begin
    if (IStr[i]='1')or(IStr[i]='2')or(IStr[i]='3')or(IStr[i]='4')or
       (IStr[i]='5')or(IStr[i]='6')or(IStr[i]='7')or(IStr[i]='8')or
       (IStr[i]='9')or(IStr[i]='0') then
    begin
      Continue;
    end
    else
    begin
      Result:=False;
      Break;
    end;
  end;
end;


function DaysInAMonth(const AYear, AMonth: Word): Word;
begin
  Result := MonthDays[(AMonth = 2) and IsLeapYear(AYear), AMonth];
end;


function IsValidDate(const AYear, AMonth, ADay: Word): Boolean;
begin
  Result := (AYear >= 1) and (AYear <= 9999) and
            (AMonth >= 1) and (AMonth <= 12) and
            (ADay >= 1) and (ADay <= DaysInAMonth(AYear, AMonth));
end;



function CheckIDcard(const IDcard:String):Char;
var
  Num, nPos:Integer;
begin
  Num:= 0;
  for nPos := 18 downto 2 do
    Num := Num + Trunc(Power(2, nPos - 1)) mod 11 * (Ord(IDcard[19 - nPos])-$30);
  Num := Num mod 11;

  case Num of
    0: Result := '1';
    1: Result := '0';
    2: Result := 'X';
    3: Result := '9';
    4: Result := '8';
    5: Result := '7';
    6: Result := '6';
    7: Result := '5';
    8: Result := '4';
    9: Result := '3';
    10: Result := '2';
  end;
end;



function SpareseBirthdayAndSex(const IDcard:String; out Birthday:TDate;
                               out Sex:String):Boolean;
var
  nYear,nMonth,nDay:Word;
begin
  Result:=False;
  if Length(IDcard) = 18 then begin
     nYear:=StrToInt(Copy(IDcard,7,4));
     nMonth:=StrToInt(Copy(IDcard,11,2));
     nDay:=StrToInt(Copy(IDcard,13,2));

     if IsValidDate(nYear,nMonth,nDay) then
       Birthday:=EncodeDate(nYear,nMonth,nDay)
     else
       Exit;

     if Odd(StrToInt(Copy(IDcard,15,3))) then
       Sex:='��'
     else
       Sex:='Ů';
     Result:=True;
  end else if  Length(IDcard) = 15 then begin
     nYear:=StrToInt(Copy(IDcard,7,2)) + 1900;
     nMonth:=StrToInt(Copy(IDcard,9,2));
     nDay:=StrToInt(Copy(IDcard,11,2));

     if IsValidDate(nYear,nMonth,nDay) then
       Birthday:=EncodeDate(nYear,nMonth,nDay)
     else
       Exit;

     if Odd(StrToInt(Copy(IDcard,13,3))) then
       Sex:='��'
     else
       Sex:='Ů';
     Result:=True;
  end;
end;

function ValidatePID(const APID: string): string;
{�ڲ�����,ȡ���֤��У��λ,���һλ,��18λ��Ч}
  function GetVerifyBit(sIdentityNum: string): Char;
  var
    nNum: Integer;
  begin
    Result := #0;
    nNum := StrToInt(sIdentityNum[1]) * 7 +
    StrToInt(sIdentityNum[2]) * 9 +
    StrToInt(sIdentityNum[3]) * 10 +
    StrToInt(sIdentityNum[4]) * 5 +
    StrToInt(sIdentityNum[5]) * 8 +
    StrToInt(sIdentityNum[6]) * 4 +
    StrToInt(sIdentityNum[7]) * 2 +
    StrToInt(sIdentityNum[8]) * 1 +
    StrToInt(sIdentityNum[9]) * 6 +
    StrToInt(sIdentityNum[10]) * 3 +
    StrToInt(sIdentityNum[11]) * 7 +
    StrToInt(sIdentityNum[12]) * 9 +
    StrToInt(sIdentityNum[13]) * 10 +
    StrToInt(sIdentityNum[14]) * 5 +
    StrToInt(sIdentityNum[15]) * 8 +
    StrToInt(sIdentityNum[16]) * 4 +
    StrToInt(sIdentityNum[17]) * 2;
    nNum := nNum mod 11;
    case nNum of
      0: Result := '1';
      1: Result := '0';
      2: Result := 'X';
      3: Result := '9';
      4: Result := '8';
      5: Result := '7';
      6: Result := '6';
      7: Result := '5';
      8: Result := '4';
      9: Result := '3';
      10: Result := '2';
    end;
    end;
var
  L : Integer;
  sCentury : string;
  sYear2Bit : string;
  sMonth : string;
  sDate : string;
  iCentury : Integer;
  iMonth : Integer;
  iDate : Integer;
  CRCFact : string;//18λ֤�ŵ�ʵ��ֵ
  CRCTh : string; //18λ֤�ŵ�����ֵ
  FebDayAmt: Byte;//2������
begin
  L := Length(APID);
  if (L in [15, 18]) = False then
  begin
    Result := Format('���֤�Ų���15λ��18λ(%0:s, ʵ��λ��:%1:d)', [APID, L]);
    Exit;
  end;
  CRCFact := '';
  if L = 18 then
  begin
    sCentury := Copy(APID, 7, 2);
    iCentury := StrToInt(sCentury);
    if (iCentury in [18..20]) = False then
    begin
      Result := Format('���֤������Ч:18λ֤�ŵ����ǰ��λ������18-20֮��(%0:S)', [sCentury]);
      Exit;
    end;
    sYear2Bit := Copy(APID, 9, 2);
    sMonth := Copy(APID, 11, 2);
    sDate := Copy(APID, 13, 2);
    CRCFact := Copy(APID, 18, 1);
  end
  else
  begin
    sCentury := '19';
    sYear2Bit := Copy(APID, 7, 2);
    sMonth := Copy(APID, 9, 2);
    sDate := Copy(APID, 11, 2);
  end;
  iMonth := StrToInt(sMonth);
  iDate := StrToInt(sDate);
  if (iMonth in [01..12]) = False then
  begin
    Result := Format('���֤������Ч:�·ݱ�����01-12֮��(%0:s)', [sMonth]);
    Exit;
  end;
  if (iMonth in [1, 3, 5, 7, 8, 10, 12]) then
  begin
    if (iDate in [01..31]) = False then
    begin
      Result := Format('���֤������Ч:������Ч,����Ϊ��򳬳��������ֵ(%0:s)', [sDate]);
      Exit;
    end;
  end;
  if (iMonth in [4, 6, 9, 11]) then
  begin
    if (iDate in [01..30]) = False then
    begin
      Result := Format('���֤������Ч:������Ч,����Ϊ��򳬳��������ֵ(%0:s)', [sDate]);
      Exit;
    end;
  end;
  if IsLeapYear(StrToInt(sCentury + sYear2Bit)) = True then
  begin
    FebDayAmt := 29;
  end
  else
  begin
    FebDayAmt := 28;
  end;
  if (iMonth in [2]) then
  begin
    if (iDate in [01..FebDayAmt]) = False then
    begin
      Result := Format('���֤������Ч:������Ч,����Ϊ��򳬳��������ֵ(%0:s)', [sDate]);
      Exit;
    end;
  end;
  if CRCFact <> '' then
  begin
    CRCTh := GetVerifyBit(APID);
    if CRCFact <> CRCTh then
    begin
      Result := Format('���֤������Ч:У��λ(��18λ)��:(%0:s)', [APID]);
      Exit;
    end;
  end;
  Result := '';
end;

function ValidateIDcard(IDcard:String; out ErrMsg:String):Boolean;
var
  nIDcardLen:Integer;
  nYear,nMonth,nDay:Word;
begin
  Result:=False;
  nIDcardLen:=Length(IDcard);
  if not (nIDcardLen in [15,18]) then begin
    ErrMsg:='���֤���λ������,�й��������֤���ӦΪ15λ��18λ! ';
    Result:=True;
    Exit;
  end;
  if  (nIDcardLen=15) then
  begin
    if (not CheckNumber(Copy(IDcard,1,nIDcardLen))) then
    begin
      ErrMsg:='���֤��������ֻ�������֣�! ';
      Result:=True;
      Exit;
    end;
  end;
  if (nIDcardLen=18) and (not CheckNumber(Copy(IDcard,1,nIDcardLen-1))) then
    begin
      ErrMsg:='�����֤ǰʮ��λ��������ֻ�������֣�! ';
      Result:=True;
      Exit;
    end;
  if (nIDcardLen=18) and (not CheckNumber(Copy(IDcard,nIDcardLen,1))) then
  begin
    if  (not((Copy(IDcard,nIDcardLen,1)='x')or(Copy(IDcard,nIDcardLen,1)='X'))) then
    begin
      ErrMsg:='�����֤�����һλ���������ֻ��ߡ�x�����ߡ�X��! ';
      Result:=True;
      Exit;
    end;
  end;

  if nIDcardLen = 18 then begin
    nYear:=StrToInt(Copy(IDcard,7,4));
    nMonth:=StrToInt(Copy(IDcard,11,2));
    nDay:=StrToInt(Copy(IDcard,13,2));

    if not IsValidDate(nYear,nMonth,nDay) then begin
      ErrMsg:='���֤��ŵĳ��������벿�ݰ�����Ч��������Ϣ(��7~14λ)!               ';
      Result:=True;
      Exit;
    end;

    if CheckIDcard(Copy(IDcard,1,17)) <> IDcard[18] then begin
      ErrMsg:='���֤���У�����,�����Ƿ�¼�����!';
      Result:=True;
      Exit;
    end;
  end else begin
     nYear:=StrToInt(Copy(IDcard,7,2)) + 1900;
     nMonth:=StrToInt(Copy(IDcard,9,2));
     nDay:=StrToInt(Copy(IDcard,11,2));

     if not IsValidDate(nYear,nMonth,nDay) then begin
       ErrMsg:='���֤��ŵĳ��������벿�ݰ�����Ч��������Ϣ(��7~12λ)!               ';
       Result:=True;
       Exit;
     end;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    UpgrateIDCard�����֤�������������֤��
-------------------------------------------------------------------------------}
function UpgrateIDCard(OldIDCard:String):String;
var
  nYear,nMonth,nDay:Word;
begin
  nYear:=StrToInt(Copy(OldIDCard,7,2)) + 1900;
  nMonth:=StrToInt(Copy(OldIDCard,9,2));
  nDay:=StrToInt(Copy(OldIDCard,11,2));
  Result:=Copy(OldIDCard,1,6) +
          Format('%0.4d%0.2d%0.2d',[nYear,nMonth,nDay]) +
          Copy(OldIDCard,13,3);
  Result:=Result + CheckIDcard(Result);

end;

{-------------------------------------------------------------------------------
  ������:    WriteLog�Զ�����־�ļ�д��
-------------------------------------------------------------------------------}
procedure WriteLog(inText: string);
var
  sFileName,s:string;
  mytext:TextFile;
begin
  sFileName:= 'C:\KStarLog.txt';
  if not FileExists(sFileName) then
    FileCreate(sfilename);

  AssignFile(mytext,sFileName);
  Append(mytext);
  try
    s:=#13+FormatDateTime('yyyymmddhhmmss',Now)+'--'+inText+#13;
    Writeln(mytext,s);
  finally
    CloseFile(mytext);
  end;
end;

procedure wLog(sfile,inText: string);
var
  s:string;
  mytext:TextFile;
begin
  //sFileName:= 'C:\KStarLog.txt';
  if not FileExists(sfile) then
    FileCreate(sfile);

  AssignFile(mytext,sfile);
  Append(mytext);
  try
    s:=#13+FormatDateTime('yyyymmddhhmmss',Now)+'--'+inText+#13;
    Writeln(mytext,s);
  finally
    CloseFile(mytext);
  end;
end;

{-------------------------------------------------------------------------------
  ������:    DBGridAutoSize
-------------------------------------------------------------------------------}
function DBGridRecordSize(mColumn: TColumn): Boolean;
begin
  Result := False;
  if not Assigned(mColumn.Field) then Exit;
  mColumn.Field.Tag := Max(mColumn.Field.Tag,
    TDBGrid(mColumn.Grid).Canvas.TextWidth(mColumn.Field.DisplayText));
  Result := True;
end; { DBGridRecordSize }

{-------------------------------------------------------------------------------
  ������:    DBGridAutoSize
  ����:      ����ΰ
  ����ֵ:    Boolean�������������Զ���Ӧ����Ƿ�ɹ�
-------------------------------------------------------------------------------}
function DBGridAutoSize(mDBGrid: TDBGrid; mOffset: Integer = 5): Boolean;
var
  I: Integer;
begin
  Result := False;
  if not Assigned(mDBGrid) then Exit;
  if not Assigned(mDBGrid.DataSource) then Exit;
  if not Assigned(mDBGrid.DataSource.DataSet) then Exit;
  if not mDBGrid.DataSource.DataSet.Active then Exit;
  for I := 0 to mDBGrid.Columns.Count - 1 do begin
    if not mDBGrid.Columns[I].Visible then Continue;
    if Assigned(mDBGrid.Columns[I].Field) then
      mDBGrid.Columns[I].Width := Max(mDBGrid.Columns[I].Field.Tag,
        mDBGrid.Canvas.TextWidth(mDBGrid.Columns[I].Title.Caption)) + mOffset
    else mDBGrid.Columns[I].Width :=
      mDBGrid.Canvas.TextWidth(mDBGrid.Columns[I].Title.Caption) + mOffset;
    mDBGrid.Refresh;
  end;
  Result := True;
end; { DBGridAutoSize }

procedure fillData2FilterCbb(var FSpells,FDisplayItems:TStringList;sCbb:TWVComboBox);
var
  I : Integer;
  S : string;
begin
  FSpells := TStringList.Create;
  FDisplayItems := TStringList.Create;
  for I:=0 to sCbb.Items.Count-1 do
  begin
    S := Uppercase(GetChineseFirstSpell(sCbb.Items[I]));
    FSpells.AddObject(S,Pointer(I));
    FDisplayItems.AddObject(Format('%s',[sCbb.Items[I]]),Pointer(I));
  end;
end;

procedure cbbFilterItem( FSpells,FDisplayItems:TStringList;sender:TObject);
var
  FilterComboBox : TKSFilterComboBox;
  I : Integer;
  S : string;
begin
  if FSpells=nil then
    Exit;
    
  FilterComboBox := TKSFilterComboBox(Sender);
  if FilterComboBox.Text='' then
  begin
    FilterComboBox.Items := FDisplayItems;
    FilterComboBox.ItemIndex := 0;
  end else
  begin
    S := Uppercase(FilterComboBox.Text);
    FilterComboBox.Items.BeginUpdate;
    FilterComboBox.Items.Clear;
    for I:=0 to FSpells.Count-1 do
    begin
      if Pos(S,FSpells[I])>0 then
        FilterComboBox.Items.AddObject(FDisplayItems[I],Pointer(I));
    end;
    FilterComboBox.Items.EndUpdate;
    FilterComboBox.ItemIndex := 0;
  end;
end;

function inputNum(key:Char): Boolean;
begin
  if (Key in ['0'..'9',#8,#13]) then
    Result:=True
  else
    result:=False;
end;

function Checkedt(key:Char;dot:string): Boolean;
begin
  if (Key in ['0'..'9','.',#8,#13]) then
    Result:=True
  else
    result:=False;
end;

{-------------------------------------------------------------------------------
  ������:    NtoC���������ڽ�С��ʮ����Ԫ��Сд���ת��Ϊ��д
  ����:      2010.07.21
  ����:      n0 :real
  ����ֵ:    String
-------------------------------------------------------------------------------}
Function NtoC( n0 :real) :String;
  Function IIF( b :boolean; s1,s2 :string) :string;
  begin
    if b then IIF:= s1
    else IIF:=s2;
  end; //�������Ĺ���һĿ��Ȼ: ��bΪ��ʱ����s1,���򷵻�s2
  Const c= '��Ҽ��������½��ƾ���ֽ�Բʰ��Ǫ��ʰ��Ǫ��ʰ��Ǫ��';
  var L,i,n, code :integer;   Z :boolean;   s,s1,s2 :string;
begin
  s:= FormatFloat('0.00', n0);
  L:= Length( s);
  Z:= n0<1;
  For i:= 1 To L-3 do
  begin
    Val( Copy( s, L-i-2, 1), n, code);
    s1:=IIf( (n=0) And (Z Or (i=9) Or (i=5) Or (i=1)), '', Copy( c, n*2+1, 2))
      + IIf( (n=0) And ((i<>9) And (i<>5) And (i<>1) Or Z And (i=1)), '', Copy( c, (i+13)*2-1, 2))
      + s1;
    Z:= (n=0);
  end;
  Z:= False;
  For i:= 1 To 2 do
  begin
    Val( Copy( s, L-i+1, 1), n, code);
    s2:= IIf( (n=0) And ((i=1) Or (i=2) And (Z Or (n0<1))), '', Copy( c, n*2+1, 2))
       + IIf( (n>0), Copy( c,(i+11)*2-1, 2), IIf( (i=2) Or Z, '', '��'))
       + s2;
    Z:= (n=0);
  end;
  For i:= 1 To Length( s1) do If Copy(s1, i, 4) = '����' Then Delete(s1,i+2,2);
  NtoC:= IIf(n0=0, '��', s1+s2);
End;

//�ַ�������ʱ�����㣬��ʽyyyymmdd
function shadate(MaxDate,MinDate:string):Integer ;
var
  max,min:string;
begin
  Result:=0;
  {
  max:= copy(MaxDate,1,4)+'-'+copy(Maxdate,5,2)+'-'+ copy(Maxdate,7,2) ;
  Min:= copy(MinDate,1,4)+'-'+copy(Mindate,5,2)+'-'+ copy(Mindate,7,2) ;
  Result:=DaysBetween(strtodate(Max),strtodate(Min));
  }
end;

initialization
begin
  AssetOwesKind:=TStringList.Create;
  AssetOwesKind.Add('һ���ʲ���');
  AssetOwesKind.Add('������ծ��');
  AssetOwesKind.Add('��������');

  CurrentOperateRecordNo:=TStringList.Create;
end;

finalization
begin
  AssetOwesKind.Free;
  CurrentOperateRecordNo.Free;
end;
end.
