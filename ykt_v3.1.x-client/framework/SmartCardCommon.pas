unit SmartCardCommon;

interface

uses
  SysUtils, Controls, Math,KSFrameWorkUtils,KSClientConsts,classes,Dialogs,
  RzDTP,ComCtrls,Graphics,DBGrids,IniFiles,Forms,FilterCombos,KSChineseSpell,
  WVCtrls;

const
   SuperOperator = 'system'; //初始化的操作员

var
  AssetOwesKind:TStringList;
  CurrentOperateRecordNo:TStringList;
  function SpareseBirthdayAndSex(const IDcard:String; out Birthday:TDate;
                                out Sex:String):Boolean;
  function ValidateIDcard(IDcard:String; out ErrMsg:String):Boolean;
  function IsValidDate(const AYear, AMonth, ADay: Word): Boolean;
  function UpgrateIDCard(OldIDCard:String):String;
  {检验字符是否全部由数字组成}
  function CheckNumber(IStr:String):Boolean;
  {检验ip地址是否正确}
  function CheckIpAddress(const AIpString:String):String;
  {检验MAC地址是否正确}
  function CheckMACAddress(const AMACString:String):String;
  {得到报表的默认起始日期}
  function GetReportDefaultBeginDate:String;
  {得到报表的默认结束日期}
  function GetReportDefaultEndDate:String;
  {检验电话号码是否合法}
  function CheckTelNumber(IStr:String):Boolean;
  {检验物理ID是否合法}
  function CheckEquipPhyID(const IStr:String):String;

  {是否全部由数字、英文字母、以及 "-","_"组成－－－主要用于各类用户代码的注册判断}
  function CheckCodeValid(IStr:String):Boolean;
  {检验手机号码是否合法}
  function CheckMobileNumber(IStr:String):Boolean;
  {检测输入的日期字符串是否合法}
  function CheckInputDateFormat(input: string): boolean;
  {检测输入的时间字符串是否合法}
  function CheckInputTimeFormat(input: string): boolean;
  {得到报表的默认开始时间}
  function GetReportDefaultBeginTime:string;
  {得到报表的默认结束时间}
  function GetReportDefaultEndTime:string;

  {自动调整网格宽度}
  function DBGridRecordSize(mColumn: TColumn): Boolean;
  function DBGridAutoSize(mDBGrid: TDBGrid; mOffset: Integer = 5): Boolean;

  function inputNum(key:Char): Boolean;
  function Checkedt(key:Char;dot:string): Boolean;

  {自定义日志文件写入}
  procedure WriteLog(inText: string);

  //文件日志的写入，可以自定义文件名
  procedure wLog(sfile,inText: string);

  function ValidatePID(const APID: string): string;

  //把combobox中的内容填充到filtercombobox中
  procedure fillData2FilterCbb(var FSpells,FDisplayItems:TStringList;sCbb:TWVComboBox);
  procedure cbbFilterItem( FSpells,FDisplayItems:TStringList;sender:TObject);

  function strToZero(inStr:string):string;
  {人民币金额大小写转换的函数}
  Function NtoC(n0 :real) :String;
  //字符串日期时间差计算，格式yyyymmdd
  function shadate(MaxDate,MinDate:string):Integer ;

type {针对框架中的特殊编辑框调用系统的日期选择框}
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
  过程名:    CheckInputTimeFormat输入时间格式检测
  作者:      韩纪伟
  日期:      2005.08.03
  参数:      input: string
  返回值:    boolean
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
  过程名:    CheckMobileNumber 移动电话号码有效性检测
  作者:      韩纪伟
  日期:      2005.08.03
  参数:      IStr:String
  返回值:    Boolean
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
    //如果最后一位不是数字，提示错误
    //ShowMessage(Copy(IStr,Length(IStr)-1,1));
    if StrToInt(Copy(IStr,Length(IStr),1))<0 then
    begin
      Result := 'IP地址格式不正确！';
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
        Result:='IP地址只能包含数字或"."！';
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
        Result:='IP地址只能包含0~255的数字！';
        Exit;
      end;
      if (Pos('.',IStr)>0)  then
        IStr:=Copy(IStr,Pos('.',IStr)+1,len-Pos('.',IStr))
      else IStr:='';
    end;
    if i<>3 then
    begin
        Result:='IP地址格式不正确！';
        Exit;
    end;
  except
    Result := 'IP地址输入不正确，请重新输入！';
  end;
end;



{约定：区号电话号码之间的风格符采用“-”}
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
          Result:='分隔符位置错误！';
          Exit;
        end;
      end
      else
      begin
        if not(((j>='0')and(j<='9'))or((j>='a')and(j<='f'))or((j>='A')and(j<='F')))
        then
        begin
          Result:='必须输入0-9或者A-F之间的字符';
          exit;
        end;
      end;
    end;
  end
  else if AMACString <> '' then
  begin
       Result:='网卡地址长度必须17位';
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
        Result:='必须输入0-9或者A-F之间的字符';
        exit;
      end;

    end;
  end
  else if IStr <> '' then
  begin
       Result:='设备物理ID长度必须8位';
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
       Sex:='男'
     else
       Sex:='女';
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
       Sex:='男'
     else
       Sex:='女';
     Result:=True;
  end;
end;

function ValidatePID(const APID: string): string;
{内部函数,取身份证号校验位,最后一位,对18位有效}
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
  CRCFact : string;//18位证号的实际值
  CRCTh : string; //18位证号的理论值
  FebDayAmt: Byte;//2月天数
begin
  L := Length(APID);
  if (L in [15, 18]) = False then
  begin
    Result := Format('身份证号不是15位或18位(%0:s, 实际位数:%1:d)', [APID, L]);
    Exit;
  end;
  CRCFact := '';
  if L = 18 then
  begin
    sCentury := Copy(APID, 7, 2);
    iCentury := StrToInt(sCentury);
    if (iCentury in [18..20]) = False then
    begin
      Result := Format('身份证号码无效:18位证号的年份前两位必须在18-20之间(%0:S)', [sCentury]);
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
    Result := Format('身份证号码无效:月份必须在01-12之间(%0:s)', [sMonth]);
    Exit;
  end;
  if (iMonth in [1, 3, 5, 7, 8, 10, 12]) then
  begin
    if (iDate in [01..31]) = False then
    begin
      Result := Format('身份证号码无效:日期无效,不能为零或超出当月最大值(%0:s)', [sDate]);
      Exit;
    end;
  end;
  if (iMonth in [4, 6, 9, 11]) then
  begin
    if (iDate in [01..30]) = False then
    begin
      Result := Format('身份证号码无效:日期无效,不能为零或超出当月最大值(%0:s)', [sDate]);
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
      Result := Format('身份证号码无效:日期无效,不能为零或超出当月最大值(%0:s)', [sDate]);
      Exit;
    end;
  end;
  if CRCFact <> '' then
  begin
    CRCTh := GetVerifyBit(APID);
    if CRCFact <> CRCTh then
    begin
      Result := Format('身份证号码无效:校验位(第18位)错:(%0:s)', [APID]);
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
    ErrMsg:='身份证编号位数不够,中国居民身份证编号应为15位或18位! ';
    Result:=True;
    Exit;
  end;
  if  (nIDcardLen=15) then
  begin
    if (not CheckNumber(Copy(IDcard,1,nIDcardLen))) then
    begin
      ErrMsg:='身份证输入有误（只能是数字）! ';
      Result:=True;
      Exit;
    end;
  end;
  if (nIDcardLen=18) and (not CheckNumber(Copy(IDcard,1,nIDcardLen-1))) then
    begin
      ErrMsg:='新身份证前十七位输入有误（只能是数字）! ';
      Result:=True;
      Exit;
    end;
  if (nIDcardLen=18) and (not CheckNumber(Copy(IDcard,nIDcardLen,1))) then
  begin
    if  (not((Copy(IDcard,nIDcardLen,1)='x')or(Copy(IDcard,nIDcardLen,1)='X'))) then
    begin
      ErrMsg:='新身份证的最后一位必须是数字或者“x”或者“X”! ';
      Result:=True;
      Exit;
    end;
  end;

  if nIDcardLen = 18 then begin
    nYear:=StrToInt(Copy(IDcard,7,4));
    nMonth:=StrToInt(Copy(IDcard,11,2));
    nDay:=StrToInt(Copy(IDcard,13,2));

    if not IsValidDate(nYear,nMonth,nDay) then begin
      ErrMsg:='身份证编号的出生日期码部份包含无效的日期信息(第7~14位)!               ';
      Result:=True;
      Exit;
    end;

    if CheckIDcard(Copy(IDcard,1,17)) <> IDcard[18] then begin
      ErrMsg:='身份证编号校验错误,请检查是否录入错误!';
      Result:=True;
      Exit;
    end;
  end else begin
     nYear:=StrToInt(Copy(IDcard,7,2)) + 1900;
     nMonth:=StrToInt(Copy(IDcard,9,2));
     nDay:=StrToInt(Copy(IDcard,11,2));

     if not IsValidDate(nYear,nMonth,nDay) then begin
       ErrMsg:='身份证编号的出生日期码部份包含无效的日期信息(第7~12位)!               ';
       Result:=True;
       Exit;
     end;
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    UpgrateIDCard旧身份证号升级到新身份证号
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
  过程名:    WriteLog自定义日志文件写入
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
  过程名:    DBGridAutoSize
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
  过程名:    DBGridAutoSize
  作者:      韩纪伟
  返回值:    Boolean返回数据网格自动适应宽度是否成功
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
  过程名:    NtoC本函数用于将小于十万亿元的小写金额转换为大写
  日期:      2010.07.21
  参数:      n0 :real
  返回值:    String
-------------------------------------------------------------------------------}
Function NtoC( n0 :real) :String;
  Function IIF( b :boolean; s1,s2 :string) :string;
  begin
    if b then IIF:= s1
    else IIF:=s2;
  end; //本函数的功能一目了然: 当b为真时返回s1,否则返回s2
  Const c= '零壹贰叁肆伍陆柒捌玖◇分角圆拾佰仟万拾佰仟亿拾佰仟万';
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
       + IIf( (n>0), Copy( c,(i+11)*2-1, 2), IIf( (i=2) Or Z, '', '整'))
       + s2;
    Z:= (n=0);
  end;
  For i:= 1 To Length( s1) do If Copy(s1, i, 4) = '亿万' Then Delete(s1,i+2,2);
  NtoC:= IIf(n0=0, '零', s1+s2);
End;

//字符串日期时间差计算，格式yyyymmdd
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
  AssetOwesKind.Add('一、资产类');
  AssetOwesKind.Add('二、负债类');
  AssetOwesKind.Add('三、损益');

  CurrentOperateRecordNo:=TStringList.Create;
end;

finalization
begin
  AssetOwesKind.Free;
  CurrentOperateRecordNo.Free;
end;
end.
