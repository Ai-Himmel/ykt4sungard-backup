unit UACardFreeze;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzButton,RzRadChk, RzStatus, RzPanel, RzEdit, Buttons,
  dxCntner, dxInspct, RzSplit, Menus, UIncrementComboBox, CardDll;

type
  TfaqhCardFreeze = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    WVLabel5: TWVLabel;
    WVComboBox6: TWVComboBox;
    WVLabel6: TWVLabel;
    WVComboBox1: TWVComboBox;
    WVLabel2: TWVLabel;
    WVComboBox3: TWVComboBox;
    Label7: TLabel;
    WVEdit8: TWVEdit;
    WVLabel9: TWVLabel;
    WVLabel1: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel8: TWVLabel;
    WVComboBox5: TWVComboBox;
    WVEdit6: TWVEdit;
    Label6: TLabel;
    WVEdit5: TWVEdit;
    Label5: TLabel;
    btnFreeze: TBitBtn;
    WVCardFreeze: TWorkView;
    WVRCardFreeze: TWVRequest;
    btnUnFreeze: TBitBtn;
    rgCardSign: TRadioGroup;
    btnPatchOper: TBitBtn;
    WVEdit4: TWVEdit;
    WVLabel3: TWVLabel;
    WVComboBox4: TWVComboBox;
    WVLabel4: TWVLabel;
    WVComboBox7: TWVComboBox;
    Label8: TLabel;
    edtCardNo: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnFreezeClick(Sender: TObject);
    procedure btnUnFreezeClick(Sender: TObject);
    procedure btnPatchOperClick(Sender: TObject);
  private
    { Private declarations }

  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardFreeze: TfaqhCardFreeze;

implementation

uses KsFrameworks,KSDataDictionary,KSClientConsts;

{$R *.DFM}

procedure TfaqhCardFreeze.Init;
var
  operId : string;
begin
  operId := Context.ParamData(svOperatorNoName).AsString;
  inherited;
  {
  if operId='system' then
    btnPatchOper.Visible:=True
  else
    btnPatchOper.Visible := False;
  }
end;

procedure TfaqhCardFreeze.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhCardFreeze.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit1.Text) = '' then
  begin
    WorkView.FieldByName('�ͻ���').Data.SetInteger(0);
  end;
  WorkView.FieldByName('Ǯ����').Data.SetInteger(1);
  inherited;
end;


procedure TfaqhCardFreeze.btnFreezeClick(Sender: TObject);
var
  CardID: integer;
  custName:string;
  showCardNo:string;
  tmpName:string;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('û�����ݣ��޷����д˲�����');
    Exit;
  end;

  CardID := (WorkView.FieldByName('��ѯ�����').Data.AsObject as
    TDataSet).FieldByName('lvol0').AsInteger;
  custName := (WorkView.FieldByName('��ѯ�����').Data.AsObject as
    TDataSet).FieldByName('sall_name').AsString;
  showCardNo := (WorkView.FieldByName('��ѯ�����').Data.AsObject as
    TDataSet).FieldByName('sorder0').AsString;

  if Trim(custName)='' then
    tmpName := showCardNo
  else
    tmpName := custName;
  if Application.MessageBox(PChar('��ȷ��Ҫ����['+tmpName+']�Ŀ���'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  WVCardFreeze.FieldByName('����').Data.SetInteger(CardID);
  WVCardFreeze.FieldByName('������־').Data.SetString('1');

  try
    //ShowWaiting(SWaitingOperation);
    WVRCardFreeze.SendCommand;
  finally
    //CloseWaiting;
    if (WVCardFreeze.FieldByName('������').Data.AsInteger = 0) then
    begin
      Context.GetDialogSystem.ShowSuccess('����У԰�������ɹ���');
    end
    else
    begin
      getReturn('����У԰��ʧ��  ',WVCardFreeze);
    end;
  end;
  try
    MainRequest.SendCommand;
  except
  end;
end;

procedure TfaqhCardFreeze.btnUnFreezeClick(Sender: TObject);
var
  dbCardNo: integer;
  CardNo:string;
  cm: TCM;
  tipInfo:string;
  st:integer;
  phyId:string;
  cardSign:Integer;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('û�����ݣ��޷����д˲�����');
    Exit;
  end;
  dbCardNo := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol0').AsInteger;
  tipInfo := '����Ϊ��'+inttostr(dbCardNo)+'���Ŀ�';
  if rgCardSign.ItemIndex=0 then
  begin
    if  preReadCard=False then
      Exit;
    cm := nil;
    try
      cm := TCM.Create;
      st := cm.card(phyId);
      if st<>0 then
      begin
        context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
        exit;
      end;
      cm.clearallfieldreadmode;
      cm.setfieldreadmode(CARD_NO);
      cm.setfieldreadmode(BLACK_CARD_SIGN);
      st := cm.readCard(phyId);
      if st<>0 then
      begin
        Context.GetDialogSystem.ShowMessage('����ʧ��-'+geterrmsg);
        Exit;
      end;
      cardNo := cm.getCardNo;
      try
        cardSign := StrToInt(cm.getBlackCardSign);
      except
        Context.GetDialogSystem.ShowMessage('��ȡ����־ʧ��-'+geterrmsg);
        Exit;
      end;
      //CardNo := readCardOneInfo(CARD_NO);
      if CardNo= '' then
      begin
        Context.GetDialogSystem.ShowWarning('��ȡ���׿���ʧ�ܣ�');
        Exit;
      end;
      if cardSign=FEE_LOCK_CARD then
      begin
        Context.GetDialogSystem.ShowMessage('�ÿ�״̬Ϊ�󸶷��������뵽�󸶷ѿۿ���������');
        Exit;
      end;

      if StrToInt(CardNo) <> dbCardNo then
      begin
        Context.GetDialogSystem.ShowWarning('���������Ŀ��Ͷ�д���Ϸ��õĲ���ͬһ�ſ���');
        Exit;
      end;

      WVCardFreeze.FieldByName('����').Data.SetInteger(dbCardNo);
      WVCardFreeze.FieldByName('������־').Data.SetString('2');

      //ShowWaiting(SWaitingOperation);
      WVRCardFreeze.SendCommand;
      if WVCardFreeze.FieldByName('������').Data.AsInteger = 0 then
      begin
        //try
          //д������
          //��������еĶ�ȡȨ��
          cm.clearallfieldreadmode;
          cm.setfieldwritemode(BLACK_CARD_SIGN);
          cm.setfieldwritemode(BLACK_VER);
          cm.setBlackCardSign(IntToStr(NORMAL_CARD));
          cm.setBlackVer(WVCardFreeze.FieldByName('���汾��').Data.AsString);
          if cm.writeData(phyId)=0 then
          begin
            cm.beep;
            Context.GetDialogSystem.ShowSuccess(tipInfo+'�ⶳ�ɹ���');
          end
          else
          begin
            Context.GetDialogSystem.ShowWarning('�ⶳ��ʧ�ܣ�');
            Exit;
          end;
      end
      else
      begin
        Context.GetDialogSystem.ShowWarning(tipInfo+'�ⶳʧ�ܣ�');
      end;
    finally
      cm.Destroy;
    end;
  end
  else
  begin
    WVCardFreeze.FieldByName('����').Data.SetInteger(dbCardNo);
    WVCardFreeze.FieldByName('������־').Data.SetString('2');

    WVRCardFreeze.SendCommand;
    if WVCardFreeze.FieldByName('������').Data.AsInteger = 0 then
      Context.GetDialogSystem.ShowSuccess(tipInfo+'�ⶳ�ɹ���')
    else
      Context.GetDialogSystem.ShowWarning(tipInfo+'�ⶳʧ�ܣ�');
  end;
  btnQuery.Click;
end;

procedure TfaqhCardFreeze.btnPatchOperClick(Sender: TObject);
var
  cardNo:string;
  //cardId:Integer;
begin
  {
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('û�����ݣ��޷����д˲�����');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ���������������',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  Grid.DataSource.DataSet.First;
  while not Grid.DataSource.DataSet.Eof do
  begin
    CardID := (WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet).FieldByName('lvol0').AsInteger;
    WVCardFreeze.FieldByName('����').Data.SetInteger(CardID);
    WVCardFreeze.FieldByName('������־').Data.SetString('1');
    WVRCardFreeze.SendCommand;
    if WVCardFreeze.FieldByName('������').Data.AsInteger <> 0 then
    begin
      Context.GetDialogSystem.ShowWarning('����Ϊ'+inttostr(cardId)+'�Ŀ�����ʧ�ܣ�');
      Exit;
    end;
    Sleep(200);
    Grid.DataSource.DataSet.Next;
  end;
  ShowMessage('����������ɹ���');
  btnQuery.Click;
  }
  edtCardNo.Text:='';
  try
    cardNo := readCardOneInfo(CARD_NO);
  except
    Exit;
  end;
  if (cardNo='') or (cardNo='0') then
  begin
    Context.GetDialogSystem.ShowMessage('������ѯʧ�ܣ�����Ϊ��򲻴���!');
    Exit;
  end;
  edtCardNo.Text:=cardNo;
  btnQuery.Click();
end;

initialization
  TUIStdClassFactory.Create('����ⶳ����', TfaqhCardFreeze);

end.


