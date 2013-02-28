unit UHQRecieveThread;
{DEFINE HQDebug}
interface

uses
  Classes, Windows, KCDataPack, Syncobjs;

type
  TStatus = array [0..1] of Char;
  PStatus = ^TStatus;

  THQRecieveThread = class(TThread)
  private
    FiHqWay: Integer;
    FhWnd: THandle;
    FiMsg: Word;
    FstrOperCode: string;
    FwDestNo: Word;
    FwMainFunc: Word;
    FstrIP: string;
    FwPort: Word;
    FwLocalPort: Word;
    FwRegtimeval: Word;
    FRequestType : LongWord;
    Fitimeout: Integer;

    FBuffer : array [0..1024*8-1] of Byte;
    FData : TSTPack;

    FLVSubItemCount : Byte;

    FWaitForOP : TEvent;
    { Private declarations }
    procedure GetData;
    procedure ShowError;
    procedure CheckValue(RltValue : Boolean);
    procedure InitHQLV;
  protected
    procedure Execute; override;
    procedure UpdateHQ;
    function GetArrowDir(PCompressedStr: PByte): string;
    function AddArrow(SrcStr : String; Arrow : Char) : string;
  public
    constructor Create( strIP: string = '';
                        strOperCode: string = '';
                        iHqWay: Integer = 1;
                        hWnd: THandle = 0;
                        iMsg: Word = 0;
                        wDestNo: Word = 0;
                        wMainFunc: Word = 666;
                        wPort: Word = 2000;
                        wLocalPort: Word = 0;
                        wRegtimeval: Word = 15;
                        RequestType : LongWord = 854077;
                        itimeout: Integer = 200);
    destructor Destroy; override;
    procedure UpdateCaption;
    procedure Open;
    procedure Close;

  end;

implementation

uses
  KSHQDLL, Sysutils, UFutureFrame, LogFile, KSClientConsts,
  {$IFDEF SYSMONSERVER}
    UMain;
  {$ELSE}
    UMainPop;
  {$ENDIF}
  
  
  //�����Ӧ��Cpack�ֶ�

  {
      854077	������������

      in	����������	smarket_code
      in	Ʒ�ִ���	sstock_code
      in	������	sdate1
      in	���̼�	damt20
      in	�����	damt21
      in	������	lvol9
      in	������	damt22
      in	������	lvol10
      in	���¼�	damt23
      in	��߼�	damt24
      in	��ͼ�	damt25
      in	�ɽ���	lvol11
      in	�ǵ�	damt26
      in	��ͣ��	damt27
      in	��ͣ��	damt28
      in	��ʷ��߼�	damt29
      in	��ʷ��ͼ�	damt30
      in	���ֲ�	lvol12
      in	�����	damt32
      in	������	damt31
      in	�����	damt33
      in	�ɽ����	damt17

      out	id��	lvol6
      out	״̬	sstatus1
      out	���	lvol2
      out	��������	sdate0
      out	����������	smarket_code
      out	Ʒ�ִ���	sstock_code
      out	������	sdate1
      out	���̼�	damt20
      out	�����	damt21
      out	������	lvol9
      out	������	damt22
      out	������	lvol10
      out	���¼�	damt23
      out	��߼�	damt24
      out	��ͼ�	damt25
      out	�ɽ���	lvol11
      out	�ǵ�	damt26
      out	��ͣ��	damt27
      out	��ͣ��	damt28
      out	��ʷ��߼�	damt29
      out	��ʷ��ͼ�	damt30
      out	���ֲ�	lvol12
      out	�����	damt32
      out	������	damt31
      out	�����	damt33
      out	�ɽ����	damt17

  }

{ THQRecieveThread }

function THQRecieveThread.AddArrow(SrcStr : String; Arrow : Char) : string;
begin
  case Arrow of
   '2' : SrcStr := '��' + SrcStr;
   '1' : SrcStr := '��' + SrcStr;
   //'0' : ;
  end;
  Result := SrcStr;
end;

procedure THQRecieveThread.CheckValue(RltValue: Boolean);
begin
  if not RltValue then ShowError;
end;

procedure THQRecieveThread.Close;
begin
  Terminate;
  WaitFor;
  CheckValue(HQ_Stop);
  CheckValue(HQ_Uninit);
  WriteLog('HQThread have closed!',lcKSClientStart);
end;

constructor THQRecieveThread.Create(strIP: string ; strOperCode: string;
  iHqWay: Integer; hWnd: THandle;iMsg: Word; wDestNo, wMainFunc: Word;
  wPort, wLocalPort, wRegtimeval: Word; RequestType: LongWord;
  itimeout: Integer);
begin
  inherited Create(True);

  FiHqWay      := iHqWay;
  FhWnd        := hWnd;
  FiMsg        := iMsg;
  FstrOperCode := strOperCode;
  FwDestNo     := wDestNo;
  FwMainFunc   := wMainFunc;
  FstrIP       := strIP;
  FwPort       := wPort;
  FwLocalPort  := wLocalPort;
  FwRegtimeval := wRegtimeval;
  FRequestType := RequestType;
  Fitimeout    := itimeout;

  WriteLog('HQThread have created!',lcKSClientStart);
  WriteLog(Format('FiHqWay=%d;FhWnd=%d;FiMsg=%d;FstrOperCode=%s;' +
                  'FwDestNo=%d;FwMainFunc=%d;FstrIP=%s;FwPort=%d;' +
                  'FwLocalPort=%d;FwRegtimeval=%d;FRequestType=%d;Fitimeout=%d;',
                  [ FiHqWay     ,FhWnd       ,FiMsg       ,FstrOperCode,FwDestNo,
                    FwMainFunc  ,FstrIP      ,FwPort      ,FwLocalPort ,
                    FwRegtimeval,FRequestType,Fitimeout]),
                    lcKSClientStart);

  FLVSubItemCount := fmMain.MainFrame.ListViewTop.Columns.Count - 1;
  FWaitForOP := TEvent.Create(nil,False,True,'');
end;

destructor THQRecieveThread.Destroy;
begin
  FreeAndNil(FWaitForOP);
  inherited;
end;

procedure THQRecieveThread.Execute;
begin
  while not Terminated do
  begin
    GetData;
  end;

end;

function THQRecieveThread.GetArrowDir(PCompressedStr: PByte): string;
const
  MaskValue = 3;
var
  J : Integer;
  Value, Mask : Byte;
begin
  Value := PCompressedStr^ shr 2;
  Mask := MaskValue;
  for J := 1 to 3 do
  begin
    case Mask and Value of
      3 : Result := Result + '2';
      0 : Result := Result + '0';
    else Result := Result + '1';
    end;
    Value := Value shr 2;
  end;
end;

{
var
  J : Integer;
  Mask: Byte;
  S,R : string;
  tempArray : array [0..BITSPERBYTE - 1] of Char;
begin
  Result := '';
  Mask := 1;
  S := '';
  for J := 0 to BITSPERBYTE - 1 do
  begin
    if (PCompressedStr^ and Mask)<>0 then
      S := S+'1' else
      S := S+'0';
    Mask := Mask shl 1;
  end;
  for J := 1 to BITSPERBYTE do
  begin
    tempArray[BITSPERBYTE - J] := S[J];
  end;
  WriteLog(Format('Release S: %s',[S]),lcDebug);
  S := tempArray;
  for J := 1 to BITSPERBYTE div 2 - 1 do
  begin
    R := S[2*J - 1] + S[2*J];
    if R = '11' then Result := Result + '2'
    else if R = '00' then Result := Result + '0'
    else if R = '01' then Result := Result + '1';
  end;

{
    WriteLog(Format('Release tempArray: %s',[tempArray]),lcDebug);
    WriteLog(Format('Result string: %s',[Result]),lcDebug);
}

  {
end;}

procedure THQRecieveThread.GetData;
var
  PBuffer : PByte;
  RltCode : Integer;
begin
  try
    FillChar(FBuffer,SizeOf(FBuffer),0);
    FillChar(FData,SizeOf(TSTPack),0);
    PBuffer := @FBuffer;

//    WriteLog(Format('Before HQ_GetRec:%d',[GetTickCount]),lcException);
    RltCode := HQ_GetRec(PBuffer^,SizeOf(FBuffer),Fitimeout);
//    WriteLog(Format('HQ_GetRec Returned(%d):%d',[RltCode,GetTickCount]),lcKSClientStart);
  //  CheckValue(RltCode < 0);
    if RltCode > 0 then
    begin
      //WriteLog(Format('%20s At %d',['Data Arrived!',GetTickCount]),lcKSClientStart);
      if FWaitForOP.WaitFor(INFINITE) = wrSignaled then
  //    WriteLog(Format('%20s At %d',['Event Singaled!',GetTickCount]),lcKSClientStart);
      UpdateCaption;
    end;
  except
    On E : Exception do
    begin
      WriteLog(Format('THQRecieveThread Raise Error:%s',[E.Message]),lcException);
    end;
  end;
end;

procedure THQRecieveThread.InitHQLV;
begin
  Synchronize(fmMain.MainFrame.InitHQView);
end;

procedure THQRecieveThread.Open;
begin
  try
    CheckValue(
    HQ_Init(FiHqWay          ,
            FhWnd            ,
            FiMsg            ,
            PChar(FstrOperCode)     ,
            FwDestNo         ,
            FwMainFunc       ,
            PChar(FstrIP)           ,
            FwPort           ,
            FwLocalPort      ,
            FwRegtimeval      ));
  except
    ShowError;
  end;
  CheckValue(HQ_Start);
  WriteLog('HQThread have started!',lcKSClientStart);
  Resume;
end;

procedure THQRecieveThread.ShowError;
var
  ErrorMessage : array [0..200] of char;
begin
  HQ_GetErrorMsg(ErrorMessage,SizeOf(ErrorMessage));
  WriteLog(Format('HQThread Error(%d):%s', [HQ_GetErrorNo,Trim(ErrorMessage)]),lcKSClientStart);
end;

procedure THQRecieveThread.UpdateCaption;
var
  PHead : PSTDataHead;
  Body : PByte;
  tempCount, Size, tempSize : Integer;
begin
  PHead := PSTDataHead(@FBuffer);

  {
  with PHead^ do
  begin
    WriteLog(Format('HQ_Thread Have Got a Message(RequestType : %d)!',
      [RequestType]),lcException);
    WriteLog(Format('RequestType :%d;',[RequestType]),lcException); //LongWord;			// ���ױ��룬4�ֽ�
    WriteLog(Format('FirstFlag   :%d;',[FirstFlag  ]),lcException); //Byte ;				// �Ƿ��һ�������װ�����
    WriteLog(Format('NextFlag    :%d;',[NextFlag   ]),lcException); //Byte ;				// �Ƿ����������
    WriteLog(Format('RecCount    :%d;',[RecCount   ]),lcException); //LongWord;			// �����ļ�¼��
    WriteLog(Format('RetCode     :%d;',[RetCode    ]),lcException); //LongWord;		  // ���ش���
    //WriteLog(Format('Addr        :%d;',[Addr       ]),lcRevSendPkgDetails); //TSTADDR;			// �����ŵĵ�ַ��6���ӽڣ�
    WriteLog(Format('queuename   :%s;',[Cookie.queuename]),lcException); //TSTCookie;
    WriteLog(Format('userdata    :%d;',[userdata   ]),lcException); //LongWord;
  end;
  }
  
  Assert(PHead^.RecCount > 0);
  Size := 0;
  Body := @FBuffer;
  Inc(Body,SizeOf(PHead^));
  for tempCount := 0 to PHead^.RecCount - 1 do
  begin
    FillChar(FData,SizeOf(TSTPack),0);
    Inc(Body,Size);
    Size := KCUnPackData(PHead^.ParamBits,FData,Body);
    Synchronize(UpdateHQ);
  end;
end;

procedure THQRecieveThread.UpdateHQ;
var
  Arrow : string;
  TempSL : TStringList;
  I : Integer;
begin

  TempSL := TStringList.Create;
  try
    if Trim(FData.sstock_code + FData.sdate1) = '' then Exit;
    for I := 1 to FLVSubItemCount do
    begin
      TempSL.Add('');
    end;
    with FData do
    begin
      Arrow := GetArrowDir(@sstatus1);

      TempSL[HQLVOrder.kaipanjia.Order - 1] := FloatToStr(damt20);
      TempSL[HQLVOrder.mairujia.Order - 1] := AddArrow(FloatToStr(damt21),Arrow[3]);
      TempSL[HQLVOrder.mairuliang.Order - 1] := IntToStr(lvol9);
      TempSL[HQLVOrder.maichujia.Order - 1] := AddArrow(FloatToStr(damt22),Arrow[2]);
      TempSL[HQLVOrder.maichuliang.Order - 1] := IntToStr(lvol10);
      TempSL[HQLVOrder.zuixinjia.Order - 1] := AddArrow(FloatToStr(damt23),Arrow[1]);;
      TempSL[HQLVOrder.zuigaojia.Order - 1] := FloatToStr(damt24);
      TempSL[HQLVOrder.zuidijia.Order - 1] := FloatToStr(damt25);
      TempSL[HQLVOrder.chengjiaoliang.Order - 1] := IntToStr(lvol11);
      TempSL[HQLVOrder.zhangdie.Order - 1] := FloatToStr(damt26);
      TempSL[HQLVOrder.zhangtingban.Order - 1] := FloatToStr(damt27);
      TempSL[HQLVOrder.dietingban.Order - 1] := FloatToStr(damt28);
      TempSL[HQLVOrder.jingchicang.Order - 1] := IntToStr(lvol12);
      TempSL[HQLVOrder.zuoshoupan.Order - 1] := FloatToStr(damt31);
      TempSL[HQLVOrder.zuojiesuan.Order - 1] := FloatToStr(damt32);
      TempSL[HQLVOrder.jinjiesuan.Order - 1] := FloatToStr(damt33);
      try
        fmMain.MainFrame.UpdateHQ(sstock_code + sdate1,TempSL.CommaText);
      except
        On E : Exception do
        begin
          WriteLog(Format('UpdateHQ Raise Error:%s',[E.Message]),lcException);
        end;
      end;
    end;
  finally
    {$IFDEF HQDebug}
    WriteLog('',lcKSClientStart);
    WriteLog('$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$',lcKSClientStart);
    WriteLog(FData.sstock_code,lcKSClientStart);
    WriteLog(FData.sdate1,lcKSClientStart);

    for I := 0 to TempSL.Count - 1 do
    begin
      WriteLog(TempSL[I],lcKSClientStart);
    end;
    WriteLog('@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@',lcKSClientStart);
    WriteLog('',lcKSClientStart);
    {$ENDIF}
    FWaitForOP.SetEvent;
//    WriteLog(Format('%20s At %d',['Singal Event!',GetTickCount]),lcKSClientStart);
    TempSL.Free;
  end;
end;

end.
