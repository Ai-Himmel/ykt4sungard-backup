unit UACPUSetwaterCard2;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzPanel, RzRadChk, RzButton,
  RzEdit, RzSpnEdt, UIncrementComboBox, WaterDll, ComCtrls, Buttons,CardDll,
  RzRadGrp;

type
  TfaqhUACPUSetwaterCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    lbl1: TLabel;
    cbbFeeType: TWVComboBox;
    edtNo: TRzSpinEdit;
    Label1: TLabel;
    Label5: TLabel;
    edtRateNum: TRzSpinEdit;
    Label2: TLabel;
    rb1: TRzGroupBox;
    lblUnitName1: TLabel;
    lblUnit1: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    edtUnit1: TRzSpinEdit;
    edtMoney1: TRzSpinEdit;
    rb2: TRzGroupBox;
    lblUnitName2: TLabel;
    lblUnit2: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    edtUnit2: TRzSpinEdit;
    edtMoney2: TRzSpinEdit;
    rb3: TRzGroupBox;
    lblUnitName3: TLabel;
    lblUnit3: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    edtUnit3: TRzSpinEdit;
    edtMoney3: TRzSpinEdit;
    rb4: TRzGroupBox;
    lblUnitName4: TLabel;
    lblUnit4: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    edtUnit4: TRzSpinEdit;
    edtMoney4: TRzSpinEdit;
    rb5: TRzGroupBox;
    lblUnitName5: TLabel;
    lblUnit5: TLabel;
    Label24: TLabel;
    Label25: TLabel;
    edtUnit5: TRzSpinEdit;
    edtMoney5: TRzSpinEdit;
    btnRateSet: TBitBtn;
    btnConCard: TBitBtn;
    btnClear: TBitBtn;
    bvl1: TBevel;
    Label4: TLabel;
    edtNumN5: TRzSpinEdit;
    Label26: TLabel;
    edtNumN4: TRzSpinEdit;
    Label27: TLabel;
    edtNumN3: TRzSpinEdit;
    Label28: TLabel;
    edtNumN2: TRzSpinEdit;
    Label29: TLabel;
    edtNumN1: TRzSpinEdit;
    Label30: TLabel;
    Label31: TLabel;
    Label32: TLabel;
    Label33: TLabel;
    Label34: TLabel;
    Label35: TLabel;
    rgUse: TRzRadioGroup;
    Label3: TLabel;
    rgFeeType: TRzRadioGroup;
    Label6: TLabel;
    rgFeeUnit: TRzRadioGroup;
    Label7: TLabel;
    cbbWorkView: TComboBox;
    lbl2: TLabel;
    edtFeeName: TWVEdit;
    btnSave2Db: TBitBtn;
    wvrSaveFeeType: TWVRequest;
    wvSaveFeeType: TWorkView;
    procedure edtRateNumChange(Sender: TObject);
    procedure cbbFeeTypeChange(Sender: TObject);
    procedure btn1Click(Sender: TObject);
    procedure cbbFeeTypeExit(Sender: TObject);
    procedure btnRateSetClick(Sender: TObject);
    procedure btnConCardClick(Sender: TObject);
    procedure btnClearClick(Sender: TObject);
    procedure rgFeeUnitClick(Sender: TObject);
    procedure btnSave2DbClick(Sender: TObject);
  private

    { Private declarations }
    feeRateCard: TFeeRateCardInfo;
    ifeeType:Integer;

    procedure showRate(rateNum:Integer);

    procedure initRateValue;

    procedure setRateValue(feeType:Integer;feeNum:Integer);

    procedure readRateValue(feeType:Integer);

    function ifUse: Integer;

    function cardType: string;

    procedure chkCardType(cardType:string);

    procedure chkIfUse(ifUse:Integer);

    function ifRepeatTime: Integer;

    procedure setFeeUnit;

    //function stringToByte(): ;

    function saveFeeType(infeeRate: TFeeRateCardInfo):Integer;
    function getFeeTypeNum(infeeRate: TFeeRateCardInfo):Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhUACPUSetwaterCard: TfaqhUACPUSetwaterCard;

implementation

uses KsFrameworks, 
     KSClientConsts,SmartCardCommon;

{$R *.DFM}

function HexStrToByteBuf(sHexStr:string;var Buf:array of Byte):integer;
var
i:integer;
begin
  i:=0;
  while sHexStr<>'' do
  begin
   Buf[i]:=Byte(strtoint('$'+Copy(sHexStr,1,2)));
   delete(sHexStr,1,2);
   inc(i);
  end;
end;
{
function ByteToHex(Src: Byte): String;
begin
  SetLength(Result, 2);
  asm
    MOV         EDI, [Result]
    MOV         EDI, [EDI]
    MOV         AL, Src
    MOV         AH, AL          // Save to AH
    SHR         AL, 4           // Output High 4 Bits
    ADD         AL, '0'
    CMP         AL, '9'
    JBE         @@OutCharLo
    ADD         AL, 'A'-'9'-1
    @@OutCharLo:
    AND         AH, $f
    ADD         AH, '0'
    CMP         AH, '9'
    JBE         @@OutChar
    ADD         AH, 'A'-'9'-1
    @@OutChar:
    STOSW
  end;
end;
}
function BytesToStr(mBytes: array of Byte):   string;
var
  I:Integer;
begin
  Result := '';
  for I := Low(mBytes)to High(mBytes)do
    Result := Result + Chr(mBytes[I])
end;

procedure TfaqhUACPUSetwaterCard.Init;
begin
  inherited;
  cbbWorkView.ItemIndex := 0;
  showRate(StrToInt(edtRateNum.Text));
  initRateValue;
end;

procedure TfaqhUACPUSetwaterCard.showRate(rateNum: Integer);
var
  i,j,k:Integer;
begin
  for i := 1 to rateNum do
    for j := 0 to Panel1.ControlCount-1 do
      if Panel1.Controls[j] is TRzGroupBox then
        if TRzGroupBox(Panel1.Controls[j]).Tag=i then
          TRzGroupBox(Panel1.Controls[j]).Visible:=True;
  for i := rateNum+1 to 5 do
    for j := 0 to Panel1.ControlCount-1 do
      if Panel1.Controls[j] is TRzGroupBox then
        if TRzGroupBox(Panel1.Controls[j]).Tag=i then
        begin
          for k := 0 to TRzGroupBox(Panel1.Controls[j]).ControlCount-1 do
            if TRzGroupBox(Panel1.Controls[j]).Controls[k] is TRzSpinEdit then
              TRzSpinEdit(TRzGroupBox(Panel1.Controls[j]).Controls[k]).Text:='0';
          TRzGroupBox(Panel1.Controls[j]).Visible:=False;
        end;
end;

procedure TfaqhUACPUSetwaterCard.edtRateNumChange(Sender: TObject);
begin
  showRate(StrToInt(edtRateNum.Text));
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhreleaseWaterManageCard.initRateSetValue初始化费率值
  作者:      hanjiwei
  日期:      2007.02.01
  参数:      无
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfaqhUACPUSetwaterCard.initRateValue;
var
  i,k:Integer;
begin
  StrCopy(@feeRateCard.water_card_flag,PChar('0000'));
  feeRateCard.packet_num := chr(0);
  StrCopy(@feeRateCard.main_work_key,'00000000');
  StrCopy(@feeRateCard.packet_work_key,'00000000');
  //StrCopy(@feeRateCard.data_length,'0');
  for i := 1 to 256 do
  begin
    feeRateCard.fee_right_num[i].right_flag:=0;
    feeRateCard.fee_right_num[i].right_num:=0;
    for k := 1 to 5 do
    begin
      feeRateCard.fee_right_num[i].fee_rate[k].deduct_fee:=0;
      feeRateCard.fee_right_num[i].fee_rate[k].deduct_time:=0;
      feeRateCard.fee_right_num[i].fee_rate[k].time_ladder:=0;
    end;
  end;
end;

procedure TfaqhUACPUSetwaterCard.readRateValue(feeType:Integer);
var
  i,pnl,gbx:Integer;
  rateNum:Integer;
  fee,time,ladder:Integer;
begin
  edtNo.Text:=IntToStr(Ord(feeRateCard.packet_num));
  chkCardType(BytesToStr(feeRateCard.water_card_flag));
  chkIfUse(feeRateCard.fee_right_num[feeType].right_flag);
  rateNum:=feeRateCard.fee_right_num[feeType].right_num;
  edtRateNum.Text:=IntToStr(rateNum);
  //edtNumN.Text := IntToStr(feeRateCard.fee_right_num[feeType].fee_rate[rateNum].time_ladder);
  for i := 1 to rateNum do
  begin
    fee := feeRateCard.fee_right_num[feeType].fee_rate[i].deduct_fee;
    time := feeRateCard.fee_right_num[feeType].fee_rate[i].deduct_time;
    ladder := feeRateCard.fee_right_num[feeType].fee_rate[i].time_ladder;
    for pnl := 0 to Panel1.ControlCount-1 do
    begin
      if TRzGroupBox(Panel1.Controls[pnl]).Tag = i then
      begin
        for gbx := 0 to TRzGroupBox(Panel1.Controls[pnl]).ControlCount-1 do
        begin
          if TRzSpinEdit(TRzGroupBox(Panel1.Controls[pnl]).Controls[gbx]).TabOrder=0 then
            TRzSpinEdit(TRzGroupBox(Panel1.Controls[pnl]).Controls[gbx]).Text:=IntToStr(time);
          if TRzSpinEdit(TRzGroupBox(Panel1.Controls[pnl]).Controls[gbx]).TabOrder=1 then
            TRzSpinEdit(TRzGroupBox(Panel1.Controls[pnl]).Controls[gbx]).Text:=IntToStr(fee);
          if TRzSpinEdit(TRzGroupBox(Panel1.Controls[pnl]).Controls[gbx]).TabOrder=2 then
            TRzSpinEdit(TRzGroupBox(Panel1.Controls[pnl]).Controls[gbx]).Text:=IntToStr(ladder);
        end;
      end;
    end;
  end;
end;

procedure TfaqhUACPUSetwaterCard.setRateValue(feeType:Integer;feeNum:Integer);
var
  i,pnl,gbx:Integer;
  fee,time,ladder:Integer;
begin
  fee := 0;
  time := 0;
  ladder := 0;
  StrCopy(@feeRateCard.water_card_flag,PChar(cardType));
  feeRateCard.packet_num := chr(StrToInt(edtNo.Text));
  feeRateCard.fee_right_num[feeType].right_num:=feeNum;
  feeRateCard.fee_right_num[feeType].right_flag:=ifUse;
  for i := 1 to feeNum do
  begin
    for pnl := 0 to Panel1.ControlCount-1 do
    begin
      if TRzGroupBox(Panel1.Controls[pnl]).Tag=i then
      begin
         for gbx := 0 to TRzGroupBox(Panel1.Controls[pnl]).ControlCount-1 do
         begin
           if TRzSpinEdit(TRzGroupBox(Panel1.Controls[pnl]).Controls[gbx]).TabOrder=0 then
             time := StrToInt(TRzSpinEdit(TRzGroupBox(Panel1.Controls[pnl]).Controls[gbx]).Text);
           if TRzSpinEdit(TRzGroupBox(Panel1.Controls[pnl]).Controls[gbx]).TabOrder=1 then
             fee := StrToInt(TRzSpinEdit(TRzGroupBox(Panel1.Controls[pnl]).Controls[gbx]).Text);
           if TRzSpinEdit(TRzGroupBox(Panel1.Controls[pnl]).Controls[gbx]).TabOrder=2 then
             ladder := StrToInt(TRzSpinEdit(TRzGroupBox(Panel1.Controls[pnl]).Controls[gbx]).Text);
         end;
      end;
    end;

    feeRateCard.fee_right_num[feeType].fee_rate[i].deduct_fee:=fee;
    feeRateCard.fee_right_num[feeType].fee_rate[i].deduct_time:=time;
    feeRateCard.fee_right_num[feeType].fee_rate[i].time_ladder:=ladder;
  end;
end;

function TfaqhUACPUSetwaterCard.ifUse: Integer;
begin
  if rgUse.ItemIndex=0 then
    Result:=1
  else if rgUse.ItemIndex=1 then
    Result:=0
  else
    Result:=-1;
end;

function TfaqhUACPUSetwaterCard.cardType: string;
begin
  if rgFeeType.ItemIndex=0 then
    Result := 'LYCS'
  else if rgFeeType.ItemIndex=1 then
    Result := 'CKSJ'
  else if rgFeeType.ItemIndex=2 then
    Result := 'WASH'
  else if rgFeeType.ItemIndex=3 then
    Result := 'TJSK'   
  else
    Result := '';
end;

procedure TfaqhUACPUSetwaterCard.chkCardType(cardType:string);
begin
  if LowerCase(Trim(cardType))='lycs' then
    rgFeeType.ItemIndex := 0
  else if LowerCase(Trim(cardType))='cksj' then
    rgFeeType.ItemIndex := 1
  else if LowerCase(Trim(cardType))='wash' then
    rgFeeType.ItemIndex := 2
  else if LowerCase(Trim(cardType))='tjsk' then
    rgFeeType.ItemIndex := 3;
end;

procedure TfaqhUACPUSetwaterCard.chkIfUse(ifUse: Integer);
begin
  if ifUse=1 then
    rgUse.ItemIndex := 0
  else if ifUse=0 then
    rgUse.ItemIndex := 1;
end;

procedure TfaqhUACPUSetwaterCard.cbbFeeTypeChange(Sender: TObject);
var
  rateType:Integer;
  selType:string;
begin
  selType := Trim(cbbFeeType.Text);
  rateType := StrToInt(Copy(selType,0,Pos('-',selType)-1));
  setRateValue(ifeeType,StrToInt(edtRateNum.Text));
  readRateValue(rateType);
  ifeeType := rateType;
end;

procedure TfaqhUACPUSetwaterCard.btn1Click(Sender: TObject);
var
  rateType:Integer;
  selType:string;
begin
  selType := cbbFeeType.Text;
  rateType := StrToInt(Copy(selType,0,Pos('-',selType)-1));

  setRateValue(rateType,StrToInt(edtRateNum.Text));
end;

procedure TfaqhUACPUSetwaterCard.cbbFeeTypeExit(Sender: TObject);
var
  selType:string;
begin
  selType := cbbFeeType.Text;
  if selType='' then
    Exit;
  ifeeType := StrToInt(Copy(selType,0,Pos('-',selType)-1));
end;

procedure TfaqhUACPUSetwaterCard.btnRateSetClick(Sender: TObject);
var
  selType:string;
  re:Integer;
  //err_code:Integer;
  reMainKey:string;
  tempArr: array[1..8] of Byte;
  smlTempArr:array[1..8] of Byte;
  //tempErr: string;
  //cardType:array[1..5] of Byte;
  ifeeType:Integer;
  rePhyid : array[0..16] of Char;

begin
  if cbbFeeType.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('请先设置费率，然后再发行卡！');
    Exit;
  end;
  //设置密钥
  //setCardKey();
  if not SmartCardPortStatus then
  begin
     Context.GetDialogSystem.ShowWarning('请先打开串口！');
     Exit;
  end;

  //cardManage := nil;
  //err_code := 0;
  selType := cbbFeeType.Text;
  ifeeType := StrToInt(Copy(selType,0,Pos('-',selType)-1));
  setRateValue(ifeeType,StrToInt(edtRateNum.Text));
  ifeeType := ifRepeatTime;
  if ifeeType<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('收费类别为:'+inttostr(ifeeType)+'有重复的时间段设置，请重新设置！');
    Exit;
  end;

  if Application.MessageBox('你确定要发行费率设置卡吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;

  try
    //cardManage := TCardManage.Create;
    {
    re := cardManage.ReadWaterCardFlag(@cardType);
    if re<>0 then
    begin
      ShowMessage('读取卡类型失败,请放置好卡--'+inttostr(re));
      Exit;
    end;
    
    if Trim(BytesToStr(cardType))<>'' then
    begin
      ShowMessage('该卡已经发行过，不能再发！');
      Exit;
    end;
    }
    WorkView.FieldByName('参数标志').Data.SetInteger(2006);
    MainRequest.SendCommand;
    if WorkView.FieldByName('返回码').Data.AsInteger<>0 then
    begin
      ShowMessage(WorkView.FieldByName('返回信息').Data.AsString);
      Exit;
    end;
    reMainKey := Trim(WorkView.fieldbyname('密钥').Data.AsString);
    HexStrToByteBuf(reMainKey,tempArr);

    //主密钥
    CopyMemory(@feeRateCard.main_work_key,@TempArr,SizeOf(feeRateCard.main_work_key)-1);
    WorkView.FieldByName('参数标志').Data.SetInteger(2009);
    MainRequest.SendCommand;
    if WorkView.FieldByName('返回码').Data.AsInteger<>0 then
    begin
      ShowMessage(WorkView.FieldByName('返回信息').Data.AsString);
      Exit;
    end;
    reMainKey := Trim(WorkView.fieldbyname('密钥').Data.AsString);
    HexStrToByteBuf(reMainKey,smlTempArr);
    CopyMemory(@feeRateCard.packet_work_key,@smlTempArr,SizeOf(feeRateCard.packet_work_key)-1);
    //小钱包密钥
    {
    tempErr := '';
    ZeroMemory(@tempArr, 8);
    tempStr := @tempArr;
    CardManage.ConvertHexStrToPChar(reMainKey, 16, tempStr, tempErr); 
    if tempErr <> '' then
    begin
      ShowMessage('转化失败--'+tempErr);
      Exit;
    end; }

    //
    {
    ss := '';
    for i := 1 to 8 do
      ss := ss+ByteToHex(feeRateCard.main_work_key[i]);
    edt1.Text := ss;

    ss:='';
    for i := 1 to 8 do
      ss := ss+ByteToHex(feeRateCard.packet_work_key[i]);
    edt2.Text := ss;
    ShowMessage('dfdfdfd');
    Exit;
    }
    //
    if cbbWorkView.ItemIndex=0 then
      feeRateCard.work_model := $00
    else if cbbWorkView.ItemIndex=1 then
      feeRateCard.work_model := $FF;
    {
    try
      re := cardManage.InitNewFeeRateCard(err_code);
      if re<>0 then
      begin
        ShowMessage('初始化费率卡失败--'+inttostr(err_code));
        pb1.Position:=0;
        Exit;
      end;
      pb1.Position:=60;
    except
      on e:exception do
      begin
      ShowMessage('初始化费率设置卡失败，请重新发卡--'+e.Message);
      pb1.Position := 0;
      Exit;
      end;
    end;
    }
    re := ks_card(PChar(@rePhyid));
    if re<>0 then
    begin

    end;
    
    //ZeroMemory(@feeRateCard,SizeOf(feeRateCard));
    //ShowMessage(PChar(@feeRateCard.water_card_flag));
    try
      re := ks_water_publish_legacycard(4,@feeRateCard);
      if re<>0 then
      begin
        Context.GetDialogSystem.ShowMessage('发行费率设置卡失败，请重新发行--错误号：'+inttostr(re));
        Exit;
      end
      else
      begin
        KNG_beep;
        Context.GetDialogSystem.ShowMessage('发行费率设置卡成功！');
      end;
    except
      on e:exception do
      begin
        Context.GetDialogSystem.ShowMessage('发行费率设置卡失败，请重新发卡--'+e.Message);
      end;
    end;

  finally
    
  end;
end;

procedure TfaqhUACPUSetwaterCard.btnConCardClick(Sender: TObject);
var
  st:Integer;
  rePhyid : array[0..16] of Char;
begin

  st := ks_card(PChar(@rePhyid));
  if st<>0 then
  begin
  end;
  
  try
  st := ks_water_recycleparamcard(4);
  if st<>0 then
    Context.GetDialogSystem.ShowMessage('回收费率设置卡失败-'+inttostr(st))
  else
  begin
    KNG_beep;
    Context.GetDialogSystem.ShowMessage('回收费率设置卡成功！');
  end;
  except
    on e:Exception do
      Context.GetDialogSystem.ShowMessage(e.Message);
  end;
  {
  if not SmartCardPortStatus then
  begin
     Context.GetDialogSystem.ShowWarning('请先打开串口！');
     Exit;
  end;
  if Application.MessageBox('你确定要发行采集卡吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;

  cardManage := nil;
  err_code := 0;
  try
    cardManage := TCardManage.Create;       
    re := cardManage.ReadWaterCardFlag(@cardType);
    if re<>0 then
    begin
      ShowMessage('读取卡类型失败--'+inttostr(re));
      Exit;
    end;
    if Trim(BytesToStr(cardType))<>'' then
    begin
      ShowMessage('该卡已经发行过，不能再发！');
      Exit;
    end;
    try
      re := cardManage.InitNewCollectionCard(err_code);
      if re<>0 then
      begin
        ShowMessage('发行采集卡失败--'+inttostr(err_code));
        Exit;
      end
      else
        ShowMessage('发行采集卡成功！');
    except
      ShowMessage('发行采集失败，请重新发卡！');
    end;
  finally
    cardManage.Destroy;
  end;
  }
end;

procedure TfaqhUACPUSetwaterCard.btnClearClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要清空已经存在的费率设置信息吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  initRateValue;
  Context.GetDialogSystem.ShowMessage('清空费率设置信息成功！');
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhreleaseWaterManageCard.ifRepeatTime判断是否有重复的时间段设置
  作者:      hanjiwei
  日期:      2007.02.08
  参数:      无
  返回值:    Boolean
-------------------------------------------------------------------------------}
function TfaqhUACPUSetwaterCard.ifRepeatTime: Integer;
var
  i,k:Integer;
  timeValue:array[1..5] of Integer;
  n,l:Integer;
begin
  Result := 0;
  for i := 1 to 256 do
  begin
    for k :=1  to 5 do
    begin
      timeValue[k] := feeRateCard.fee_right_num[i].fee_rate[k].time_ladder;
      //比较数组中的数据是否有相等值，如果有，返回该i值，否则继续比较，没有返回0
      for n := Low(timeValue) to High(timeValue) - 1 do
      begin
        for l := n + 1 to High(timeValue) do
        begin
          if (timeValue[n] = timeValue[l]) and (timeValue[n]<>0) then
          begin
            Label35.Caption:='n:'+IntToStr(n)+'---l:'+IntToStr(l)+'---i:'+IntToStr(i)+'---timevalue:'+inttostr(timeValue[n]);
            Result := i;
            Exit;
          end;
        end;
      end;
    end;
  end;
end;

procedure TfaqhUACPUSetwaterCard.setFeeUnit;
var
  sUnitName,sUnit:string;
begin
  if rgFeeUnit.ItemIndex = 0 then
  begin
    sUnitName := '扣费时间单位：';
    sUnit := '以秒为单位';
  end
  else if rgFeeUnit.ItemIndex = 1 then
  begin
    sUnitName := '扣费流量单位：';
    sUnit := '以升为单位';
  end;
  lblUnitName1.Caption := sUnitName;
  lblUnitName2.Caption := sUnitName;
  lblUnitName3.Caption := sUnitName;
  lblUnitName4.Caption := sUnitName;
  lblUnitName5.Caption := sUnitName;
  lblUnit1.Caption := sUnit;
  lblUnit2.Caption := sUnit;
  lblUnit3.Caption := sUnit;
  lblUnit4.Caption := sUnit;
  lblUnit5.Caption := sUnit;
end;

procedure TfaqhUACPUSetwaterCard.rgFeeUnitClick(Sender: TObject);
begin
  setFeeUnit;
end;

function TfaqhUACPUSetwaterCard.saveFeeType(infeeRate: TFeeRateCardInfo): Integer;
var
  i:Integer;
  feeNum:Integer;
  //firstSign:Boolean;
  feeNo:Integer;
begin
  if Trim(edtFeeName.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('请输入要保存到数据库的费率名称！');
    edtFeeName.SetFocus;
    Result := -1;
    Exit;
  end;
  //判断设置的收费类别的个数是否大于20，大于则提示只能设置20个
  feeNum := getFeeTypeNum(feeRateCard);
  if feeNum>20 then
  begin
    Context.GetDialogSystem.ShowMessage('每次设置的收费类别个数不能大于20个！');
    Result := -3;
    Exit;
  end;
  if feeNum=0 then
  begin
    Context.GetDialogSystem.ShowMessage('请先设置相关的收费！');
    Result := -4;
    Exit;
  end;
  //ShowMessage('fff');
  //firstSign := false;
  feeNo := 0;
  wvSaveFeeType.FieldByName('标志').Data.SetString('A');
  wvSaveFeeType.FieldByName('费率编号').Data.SetInteger(feeNo);
  wvSaveFeeType.FieldByName('费率名称').Data.SetString(edtFeeName.Text);
  wvSaveFeeType.FieldByName('钱包号').Data.SetInteger(Ord(feeRateCard.packet_num));
  wvSaveFeeType.FieldByName('计费单位').Data.SetInteger(rgFeeType.ItemIndex);
  wvSaveFeeType.FieldByName('费率类型').Data.SetString(cardType);
  wvSaveFeeType.FieldByName('数量').Data.SetInteger(feeNum);
  {
  wvSaveFeeType.FieldByName('费率个数').Data.SetInteger(infeeRate.fee_right_num[i].right_num);
  wvSaveFeeType.FieldByName('收费类别').Data.SetInteger(i);
  wvSaveFeeType.FieldByName('费率时间1').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[1].time_ladder);
  wvSaveFeeType.FieldByName('费率金额1').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[1].deduct_fee);
  wvSaveFeeType.FieldByName('费率分钟1').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[1].deduct_time);
  wvSaveFeeType.FieldByName('费率时间2').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[2].time_ladder);
  wvSaveFeeType.FieldByName('费率金额2').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[2].deduct_fee);
  wvSaveFeeType.FieldByName('费率分钟2').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[2].deduct_time);
  wvSaveFeeType.FieldByName('费率时间3').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[3].time_ladder);
  wvSaveFeeType.FieldByName('费率金额3').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[3].deduct_fee);
  wvSaveFeeType.FieldByName('费率分钟3').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[3].deduct_time);
  }
  try
    wvrSaveFeeType.SendCommand;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Result := -6;
      Exit;
    end;
  end;
  if wvSaveFeeType.FieldByName('返回码').Data.AsString='0' then
  begin
    feeNo := wvSaveFeeType.fieldbyname('费率编号').Data.AsInteger;
    //firstSign := True;
  end
  else
  begin
    result:=-5;
    Exit;
  end;
  for i:= 1 to 256 do
  begin
    if infeeRate.fee_right_num[i].right_num>0 then
    begin
      wvSaveFeeType.FieldByName('标志').Data.SetString('I');
      wvSaveFeeType.FieldByName('费率编号').Data.SetInteger(feeNo);
      wvSaveFeeType.FieldByName('费率名称').Data.SetString(edtFeeName.Text);
      wvSaveFeeType.FieldByName('钱包号').Data.SetInteger(Ord(feeRateCard.packet_num));
      wvSaveFeeType.FieldByName('计费单位').Data.SetInteger(rgFeeType.ItemIndex);
      wvSaveFeeType.FieldByName('费率类型').Data.SetString(cardType);
      wvSaveFeeType.FieldByName('费率个数').Data.SetInteger(infeeRate.fee_right_num[i].right_num);
      wvSaveFeeType.FieldByName('收费类别').Data.SetInteger(i);
      wvSaveFeeType.FieldByName('数量').Data.SetInteger(feeNum);
      wvSaveFeeType.FieldByName('费率时间1').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[1].time_ladder);
      wvSaveFeeType.FieldByName('费率金额1').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[1].deduct_fee);
      wvSaveFeeType.FieldByName('费率分钟1').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[1].deduct_time);
      wvSaveFeeType.FieldByName('费率时间2').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[2].time_ladder);
      wvSaveFeeType.FieldByName('费率金额2').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[2].deduct_fee);
      wvSaveFeeType.FieldByName('费率分钟2').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[2].deduct_time);
      wvSaveFeeType.FieldByName('费率时间3').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[3].time_ladder);
      wvSaveFeeType.FieldByName('费率金额3').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[3].deduct_fee);
      wvSaveFeeType.FieldByName('费率分钟3').Data.SetInteger(infeeRate.fee_right_num[i].fee_rate[3].deduct_time);
      try
        wvrSaveFeeType.SendCommand;
      except
        on e:Exception do
        begin
          Context.GetDialogSystem.ShowMessage(e.Message);
          Result := -6;
          Exit;
        end;
      end;
    end;
  end;
  Result := 0;
end;

function TfaqhUACPUSetwaterCard.getFeeTypeNum(infeeRate: TFeeRateCardInfo): Integer;
var
  i:Integer;
  feeNum:Integer;
begin
  feeNum := 0;
  for i := 1 to 256 do
  begin
    if infeeRate.fee_right_num[i].right_num>0 then
      Inc(feeNum);
  end;
  Result := feeNum;
end;

procedure TfaqhUACPUSetwaterCard.btnSave2DbClick(Sender: TObject);
var
  selType:string;
  ifeeType:Integer;
begin
  selType := cbbFeeType.Text;
  ifeeType := StrToInt(Copy(selType,0,Pos('-',selType)-1));
  setRateValue(ifeeType,StrToInt(edtRateNum.Text));
  ifeeType := ifRepeatTime;
  if ifeeType<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('收费类别为:'+inttostr(ifeeType)+'有重复的时间段设置，请重新设置！');
    Exit;
  end;

  if Application.MessageBox('你确定要保存费率设置到数据库吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  if saveFeeType(feeRateCard)<>0 then
    Exit;
  Context.GetDialogSystem.ShowMessage('保存费率设置成功！');
end;

initialization
  TUIStdClassFactory.Create('水控设置卡管理',TfaqhUACPUSetwaterCard);

end.