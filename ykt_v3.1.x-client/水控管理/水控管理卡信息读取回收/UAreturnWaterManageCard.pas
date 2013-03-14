unit UAreturnWaterManageCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzPanel, RzRadChk, RzButton,
  RzEdit, RzSpnEdt, UIncrementComboBox, UtCardDll, Buttons, RzRadGrp;

type
  TfaqhreturnWaterManageCard = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    btnModify: TBitBtn;
    btnReturn: TBitBtn;
    lbl1: TLabel;
    cbbFeeType: TWVComboBox;
    edtNo1: TRzSpinEdit;
    Label1: TLabel;
    Label5: TLabel;
    edtRateNum: TRzSpinEdit;
    Label2: TLabel;
    btnReturnCon: TBitBtn;
    bvl1: TBevel;
    rb1: TRzGroupBox;
    lblUnitName1: TLabel;
    lblUnit1: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label29: TLabel;
    edtUnit1: TRzSpinEdit;
    edtMoney1: TRzSpinEdit;
    edtNumN1: TRzSpinEdit;
    rb2: TRzGroupBox;
    lblUnitName2: TLabel;
    lblUnit2: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label28: TLabel;
    edtUnit2: TRzSpinEdit;
    edtMoney2: TRzSpinEdit;
    edtNumN2: TRzSpinEdit;
    rb3: TRzGroupBox;
    lblUnitName3: TLabel;
    lblUnit3: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label27: TLabel;
    edtUnit3: TRzSpinEdit;
    edtMoney3: TRzSpinEdit;
    edtNumN3: TRzSpinEdit;
    rb4: TRzGroupBox;
    lblUnitName4: TLabel;
    lblUnit4: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label26: TLabel;
    edtUnit4: TRzSpinEdit;
    edtMoney4: TRzSpinEdit;
    edtNumN4: TRzSpinEdit;
    rb5: TRzGroupBox;
    lblUnitName5: TLabel;
    lblUnit5: TLabel;
    Label24: TLabel;
    Label25: TLabel;
    Label30: TLabel;
    edtUnit5: TRzSpinEdit;
    edtMoney5: TRzSpinEdit;
    edtNumN5: TRzSpinEdit;
    Label31: TLabel;
    Label32: TLabel;
    Label33: TLabel;
    Label34: TLabel;
    Label35: TLabel;
    Label4: TLabel;
    Label3: TLabel;
    rgUse: TRzRadioGroup;
    Label36: TLabel;
    rgFeeUnit: TRzRadioGroup;
    rgFeeType: TRzRadioGroup;
    Label7: TLabel;
    cbbWorkView: TComboBox;
    procedure cbbFeeTypeChange(Sender: TObject);
    procedure cbbFeeTypeExit(Sender: TObject);
    procedure edtRateNumChange(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnModifyClick(Sender: TObject);
    procedure btnReturnClick(Sender: TObject);
    procedure btnReturnConClick(Sender: TObject);
    procedure rgFeeUnitClick(Sender: TObject);
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

  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhreturnWaterManageCard: TfaqhreturnWaterManageCard;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
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
function BytesToStr(mBytes: array of Byte):   string;
var
  I:Integer;
begin
  Result := '';
  for I := Low(mBytes)to High(mBytes)do
    Result := Result + Chr(mBytes[I])
end;

function TfaqhreturnWaterManageCard.cardType: string;
begin
  if rgFeeType.ItemIndex=0 then
    Result := 'LYCS'
  else if rgFeeType.ItemIndex=1 then
    Result := 'CKSJ'
  else
    Result := '';
end;

procedure TfaqhreturnWaterManageCard.chkCardType(cardType: string);
begin
  if LowerCase(Trim(cardType))='lycs' then
    rgFeeType.ItemIndex:=0
  else if LowerCase(Trim(cardType))='cksj' then
    rgFeeType.ItemIndex:=1;
end;

procedure TfaqhreturnWaterManageCard.chkIfUse(ifUse: Integer);
begin
  if ifUse=1 then
    rgUse.ItemIndex := 0
  else if ifUse=0 then
    rgUse.ItemIndex := 1;
end;

function TfaqhreturnWaterManageCard.ifUse: Integer;
begin
  if rgUse.ItemIndex = 0 then
    Result:=1
  else
    Result:=0;
end;

procedure TfaqhreturnWaterManageCard.Init;
begin
  inherited;
  WorkView.FieldByName('������־').DefaultValue := 0;
  WorkView.Reset;
  btnModify.Enabled := False;
  showRate(StrToInt(edtRateNum.Text));
end;

procedure TfaqhreturnWaterManageCard.initRateValue;
var
  i,k:Integer;
begin
  StrCopy(@feeRateCard.water_card_flag,PChar('0000'));
  feeRateCard.packet_num := Char('0');
  StrCopy(@feeRateCard.main_work_key,'00000000');
  StrCopy(@feeRateCard.packet_work_key,'00000000');
  StrCopy(@feeRateCard.data_length,'0');
  for i := 1 to 255 do
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

procedure TfaqhreturnWaterManageCard.readRateValue(feeType: Integer);
var
  i,pnl,gbx:Integer;
  rateNum:Integer;
  fee,time,ladder:Integer;
begin
  edtNo1.Text:=IntToStr(Ord(feeRateCard.packet_num));
  chkCardType(BytesToStr(feeRateCard.water_card_flag));
  chkIfUse(feeRateCard.fee_right_num[feeType].right_flag);
  rateNum:=feeRateCard.fee_right_num[feeType].right_num;
  edtRateNum.Text:=IntToStr(rateNum);
  //ShowMessage(IntToStr(feeRateCard.work_model));
  if Int(feeRateCard.work_model)=255 then
    cbbWorkView.ItemIndex := 1
  else
    cbbWorkView.ItemIndex := 0;
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

procedure TfaqhreturnWaterManageCard.setRateValue(feeType,
  feeNum: Integer);
var
  i,pnl,gbx:Integer;
  fee,time,ladder:Integer;
begin
  fee := 0;
  time := 0;
  ladder := 0;
  StrCopy(@feeRateCard.water_card_flag,PChar(cardType));
  //StrCopy(@feeRateCard.packet_num,PChar(edtNo.Text));
  feeRateCard.packet_num := chr((StrToInt(edtNo1.Text)));
  feeRateCard.fee_right_num[feeType].right_flag:=ifUse;
  feeRateCard.fee_right_num[feeType].right_num:=feeNum;
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

procedure TfaqhreturnWaterManageCard.showRate(rateNum: Integer);
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

procedure TfaqhreturnWaterManageCard.cbbFeeTypeChange(Sender: TObject);
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

procedure TfaqhreturnWaterManageCard.cbbFeeTypeExit(Sender: TObject);
var
  selType:string;
begin
  try
  selType := cbbFeeType.Text;
  ifeeType := StrToInt(Copy(selType,0,Pos('-',selType)-1));
  except
  end;
end;

procedure TfaqhreturnWaterManageCard.edtRateNumChange(Sender: TObject);
begin
  showRate(StrToInt(edtRateNum.Text));
end;

procedure TfaqhreturnWaterManageCard.btnQueryClick(Sender: TObject);
var
  selType:string;
  ifeeType:Integer;
  cardManage:TCardManage;
  re:Integer;
  cardType:array[1..5] of Byte;
begin
  initRateValue;
  //Ȼ���ȡ����Ϣ
  selType := cbbFeeType.Text;
  if Trim(selType)='' then
  begin
    ShowMessage('��ѡ����Ҫ�鿴���շ����');
    Exit;
  end;
  ifeeType := StrToInt(Copy(selType,0,Pos('-',selType)-1));
  cardManage:=nil;
  try
    try
    cardManage := TCardManage.Create;
    re := cardManage.ReadWaterCardFlag(@cardType);
    if re<>0 then
    begin
      ShowMessage('��ȡ������ʧ��,����úÿ���');
      Exit;
    end;
    //ShowMessage(Trim(LowerCase(BytesToStr(cardType))));
    if Trim(LowerCase(BytesToStr(cardType)))='lycj' then
    begin
      ShowMessage('�ÿ�Ϊ�ɼ��������ܶ�ȡ����Ϣ��');
      Exit;
    end;
    re := cardManage.ReadFeeRateCard(@feeRateCard);
    if re<>0 then
    begin
      ShowMessage('��ȡ�շ������Ϣʧ�ܣ�����úÿ���');
      Exit;
    end;
    readRateValue(ifeeType);
    btnModify.Enabled := True;
    except
      ShowMessage('��ȡ�������ÿ���Ϣʧ�ܣ���źÿ���');
    end;
  finally
    cardManage.Destroy;
  end;
end;

procedure TfaqhreturnWaterManageCard.btnModifyClick(Sender: TObject);
var
  reMainKey:string;
  selType:string;
  cardManage:TCardManage;
  re:Integer;
  tempStr: PChar;
  tempArr: array[1..8] of Byte;
  smlTempArr:array[1..8] of Byte;
  tempErr: string;
  ifeeType : Integer;
begin
  if cbbFeeType.Text='' then
  begin
    ShowMessage('�������÷��ʣ�Ȼ�����޸Ŀ���Ϣ��');
    Exit;
  end;
  if not SmartCardPortStatus then
  begin
     Context.GetDialogSystem.ShowWarning('���ȴ򿪴��ڣ�');
     Exit;
  end;
  cardManage := nil;
  selType := cbbFeeType.Text;
  ifeeType := StrToInt(Copy(selType,0,Pos('-',selType)-1));
  setRateValue(ifeeType,StrToInt(edtRateNum.Text));
  
  ifeeType := ifRepeatTime;
  if ifeeType<>0 then
  begin
    ShowMessage('�շ����Ϊ--'+inttostr(ifeeType)+'���ظ���ʱ������ã����������ã�');
    Exit;
  end;

  if Application.MessageBox('��ȷ��Ҫ�޸ķ������ÿ���Ϣ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;

  try
    cardManage := TCardManage.Create;
    //ShowMessage(BytesToStr(feeRateCard.main_work_key));
    WorkView.FieldByName('������־').Data.SetInteger(2006);
    MainRequest.SendCommand;
    if WorkView.FieldByName('������').Data.AsInteger<>0 then
    begin
      ShowMessage(WorkView.FieldByName('������Ϣ').Data.AsString);
      Exit;
    end;
    reMainKey := WorkView.fieldbyname('��Կ').Data.AsString;
    {
    tempErr := '';
    ZeroMemory(@tempArr, 8);
    tempStr := @tempArr;
    CardManage.ConvertHexStrToPChar(reMainKey, 16, tempStr, tempErr);
    if tempErr <> '' then
    begin
      ShowMessage('ת��ʧ��--'+tempErr);
      Exit;
    end;}
    //����Կ
    HexStrToByteBuf(reMainKey,tempArr);
    CopyMemory(@feeRateCard.main_work_key,@TempArr,SizeOf(feeRateCard.main_work_key)-1);
    //StrCopy(@feeRateCard.main_work_key,PChar(tempStr));
    WorkView.FieldByName('������־').Data.SetInteger(2009);
    MainRequest.SendCommand;
    if WorkView.FieldByName('������').Data.AsInteger<>0 then
    begin
      ShowMessage(WorkView.FieldByName('������Ϣ').Data.AsString);
      Exit;
    end;
    reMainKey := WorkView.fieldbyname('��Կ').Data.AsString;
    //СǮ����Կ
    HexStrToByteBuf(reMainKey,smlTempArr);
    CopyMemory(@feeRateCard.packet_work_key,@smlTempArr,SizeOf(feeRateCard.packet_work_key)-1);
    {
    CardManage.ConvertHexStrToPChar(reMainKey, 16, tempStr, tempErr);
    if tempErr <> '' then
    begin
      ShowMessage('ת��ʧ��--'+tempErr);
      Exit;
    end;
    StrCopy(@feeRateCard.packet_work_key,PChar(tempStr)); }
    //ShowMessage((feeRateCard.packet_num));
    if cbbWorkView.ItemIndex=0 then
      feeRateCard.work_model := $00
    else
      feeRateCard.work_model := $FF;
    try
      re := cardManage.PublishFeeRateCard(@feeRateCard);
      if re<>0 then
      begin
        ShowMessage('�޸ķ������ÿ�ʧ�ܣ������ԣ�');
        Exit;
      end
      else
      begin
        ShowMessage('�޸ķ������ÿ��ɹ���');
        btnModify.Enabled := False;
      end;
    except
      ShowMessage('���÷������ÿ���Ϣʧ�ܣ���źÿ���');
    end;
  finally
    cardManage.Destroy;
  end;
end;

procedure TfaqhreturnWaterManageCard.btnReturnClick(Sender: TObject);
var
  cardManage:TCardManage;
  re,err_code:Integer;
  cardType:array[1..5] of Byte;
begin
  //�������ÿ�
  if not SmartCardPortStatus then
  begin
     Context.GetDialogSystem.ShowWarning('���ȴ򿪴��ڣ�');
     Exit;
  end;
  if Application.MessageBox('���Ƿ�Ҫ���շ�������(��ɼ�)����',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  cardManage:=nil;
  err_code:=0;
  try
    cardManage := TCardManage.Create;
    re := cardManage.ReadWaterCardFlag(@cardType);
    if re<>0 then
    begin
      ShowMessage('��ȡ������ʧ��,����úÿ���');
      Exit;
    end;
    if Trim(LowerCase(BytesToStr(cardType)))='lycj' then
    begin
      ShowMessage('�ÿ�Ϊ�ɼ���������ʹ�øù��ܻ��գ�');
      Exit;
    end;
    try
      re := cardManage.RefineWaterCard(err_code);
      if re<>0 then
        ShowMessage('���շ������ÿ�ʧ��--'+inttostr(err_code))
      else
        ShowMessage('���շ������ÿ��ɹ�!');
    except
      ShowMessage('���շ������ÿ�ʧ�ܣ���źÿ���');
    end;
  finally
    cardManage.Destroy;
  end;
end;

procedure TfaqhreturnWaterManageCard.btnReturnConClick(Sender: TObject);
var
  cardManage:TCardManage;
  re,err_code:Integer;
  cardType:array[1..5] of Byte;
begin
  //�������ÿ�
  if not SmartCardPortStatus then
  begin
     Context.GetDialogSystem.ShowWarning('���ȴ򿪴��ڣ�');
     Exit;
  end;
  if Application.MessageBox('���Ƿ�Ҫ���շ�������(��ɼ�)����',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  cardManage:=nil;
  err_code:=0;
  try
    cardManage := TCardManage.Create;
    re := cardManage.ReadWaterCardFlag(@cardType);
    if re<>0 then
    begin
      ShowMessage('��ȡ������ʧ��,����úÿ���');
      Exit;
    end;
    if Trim(LowerCase(BytesToStr(cardType)))<>'lycj' then
    begin
      ShowMessage('�ÿ�Ϊ�������ÿ�������ʹ�øù��ܻ��գ�');
      Exit;
    end;
    try
      re := cardManage.RefineWaterCard(err_code);
      if re<>0 then
        ShowMessage('���ղɼ���ʧ��--'+inttostr(err_code))
      else
        ShowMessage('���ղɼ����ɹ�!');
    except
      ShowMessage('���ղɼ���ʧ�ܣ���źÿ���');
    end;
  finally
    cardManage.Destroy;
  end;
end;

function TfaqhreturnWaterManageCard.ifRepeatTime: Integer;
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

      //�Ƚ������е������Ƿ������ֵ������У����ظ�iֵ����������Ƚϣ�û�з���0
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

procedure TfaqhreturnWaterManageCard.setFeeUnit;
var
  sUnitName,sUnit:string;
begin
  if rgFeeUnit.ItemIndex = 0 then
  begin
    sUnitName := '�۷�ʱ�䵥λ��';
    sUnit := '����Ϊ��λ';
  end
  else if rgFeeUnit.ItemIndex = 1 then
  begin
    sUnitName := '�۷�������λ��';
    sUnit := '����Ϊ��λ';
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

procedure TfaqhreturnWaterManageCard.rgFeeUnitClick(Sender: TObject);
begin
  setFeeUnit;
end;

initialization
  TUIStdClassFactory.Create('ˮ�ؿ���Ϣ��ȡ����',TfaqhreturnWaterManageCard);

end.