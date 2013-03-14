unit UAPASMCardOper;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, UIncrementComboBox, RzButton,
  RzRadChk, RzStatus, RzPanel, Buttons, CardDll;

type
  TfaqhPASMCardOper = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    edtCardNo: TWVEdit;
    WVEdit3: TWVEdit;
    WVComboBox3: TWVComboBox;
    btnpasmEdit: TBitBtn;
    btnReturn: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    WVRequest2: TWVRequest;
    WorkView2: TWorkView;
    WVComboBox1: TWVComboBox;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    grp1: TGroupBox;
    lbl1: TLabel;
    cbbStatus: TWVComboBox;
    lbl2: TLabel;
    edtLimitDate: TEdit;
    lbl3: TLabel;
    cbbUser: TWVComboBox;
    btnReadCard: TBitBtn;
    procedure btnQueryClick(Sender: TObject);
    procedure btnReturnClick(Sender: TObject);
    procedure btnpasmEditClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhPASMCardOper: TfaqhPASMCardOper;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,SmartCardCommon;

{$R *.DFM}

procedure TfaqhPASMCardOper.Init;
begin
  inherited;
  btnpasmEdit.Enabled := False;
  btnReturn.Enabled := False;
  //cbbpasmSeat.ItemIndex := pasmseat;
  if not SmartCardPortStatus then
    Exit;
end;

procedure TfaqhPASMCardOper.btnQueryClick(Sender: TObject);
begin
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  WorkView.FieldByName('������־').Data.SetString('R');
  //MainRequest.SendCommand;
  inherited;

  if  WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    btnpasmEdit.Enabled := False;
    btnReturn.Enabled := False;
  end
  else
  begin
    btnpasmEdit.Enabled := True;
    btnReturn.Enabled := True;
  end;

end;

procedure TfaqhPASMCardOper.btnReturnClick(Sender: TObject);
var
  cardNo:Integer;
  termNo:string;
  st:Integer;
begin
  if preReadCard=False then
    Exit;
  if Application.MessageBox(PChar('���Ƿ�Ҫ���ո�PSAM����'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  //ks_setcpupara4sam(cbbpasmSeat.ItemIndex+1);
  //ks_samcpureset;
  cardNo := Grid.DataSource.DataSet.fieldbyname('Lvol0').AsInteger;
  termNo := Grid.DataSource.DataSet.fieldbyname('Sserial0').AsString;
  WorkView1.FieldByName('���׿���').Data.SetInteger(cardNo);
  WorkView1.FieldByName('�ն˱��').Data.SetString(termNo);
  WorkView1.FieldByName('������־').Data.SetString('D');
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('������').Data.AsInteger=0 then
  begin
    //��ʼ���տ�
    st := ks_recyclepsamcard;
    if st<>0 then
    begin
      getDllErr;
      Exit;
    end
    else
    begin
      KNG_beep;
      Context.GetDialogSystem.ShowMessage('PSAM�����ճɹ���');
    end;
  end;
  RzStatusPane1.Caption := WorkView1.fieldbyname('������Ϣ').Data.AsString;
end;

procedure TfaqhPASMCardOper.btnpasmEditClick(Sender: TObject);
var
  cardNo:Integer;
  termNo:string;
  cardType:Integer;
  cardIndex:Integer;
  userId:string;
  //st:Integer;
begin
  ShowMessage('û��ʵ�ֵĹ���,Ҫ�򿪴��ڣ����ÿ���');
  Exit;
  if Trim(edtLimitDate.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('��������Ч���ڣ�');
    edtLimitDate.SetFocus;
    Exit;
  end;
  if CheckInputDateFormat(edtLimitDate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('��Ч�������벻��ȷ����ʽ��yyyymmdd');
    edtLimitDate.SetFocus;
    Exit;
  end;
  cardNo := Grid.DataSource.DataSet.fieldbyname('Lvol0').AsInteger;
  termNo := Grid.DataSource.DataSet.fieldbyname('Sserial0').AsString;
  cardType := Grid.DataSource.DataSet.fieldbyname('Lvol5').AsInteger;
  cardIndex := Grid.DataSource.DataSet.fieldbyname('lsafe_level').AsInteger;
  userId := Grid.DataSource.DataSet.fieldbyname('sholder_ac_no2').asstring;
  WorkView2.FieldByName('���׿���').Data.SetInteger(cardNo);
  WorkView2.FieldByName('�ն˱��').Data.SetString(termNo);
  WorkView2.FieldByName('������').Data.SetInteger(cardType);
  WorkView2.FieldByName('ʹ�÷���ʶ').Data.SetString(userId);
  WorkView2.FieldByName('��Կ������').Data.SetInteger(cardIndex);
  WorkView2.FieldByName('��Ч����').Data.SetString(edtLimitDate.Text);
  WorkView2.FieldByName('������־').Data.SetString('U');
  WVRequest2.SendCommand;
  if WorkView2.FieldByName('������').Data.AsInteger=0 then
  begin
    {TODO:�޸�pasm����Ϣ}

  end;
  RzStatusPane1.Caption := WorkView1.fieldbyname('������Ϣ').Data.AsString;
end;

procedure TfaqhPASMCardOper.btnReadCardClick(Sender: TObject);
var
  pasmCard:TPUBPSAMCARD;
  st:Integer;
  reError:string;
begin
  if not preReadCard then
    Exit;
  //ks_setcpupara4sam(cbbpasmSeat.ItemIndex+1);
  //ks_samcpureset;
  try
    //preReadPASM(pasmCard);
    ZeroMemory(@pasmCard,SizeOf(pasmCard));
    st:= ks_readpsamcard(@pasmCard);
    if st=0 then
    begin
      KNG_beep;
      edtCardNo.Text := pasmCard.CardNo;
      btnQuery.Click;
    end
    else
    begin
      ks_geterrmsg(@reError);
      RzStatusPane1.Caption := reError;
    end;
  except
    on e:Exception do
      Context.GetDialogSystem.ShowMessage('��ȡPSAMʧ��,��ȷ���ÿ�Ϊ�Ѿ����й���PSAM��');
  end;
end;

initialization
  TUIStdClassFactory.Create('PSAM������',TfaqhPASMCardOper);

end.