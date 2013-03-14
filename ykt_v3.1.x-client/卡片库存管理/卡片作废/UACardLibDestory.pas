unit UACardLibDestory;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db,UtCardDll, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  RzStatus, RzPanel;

type
  TfaqhCardLibDestory = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    WVCardDestory: TWorkView;
    WVRCardDestory: TWVRequest;
    grp1: TGroupBox;
    Label2: TLabel;
    lblTransTo: TLabel;
    lblBNo: TLabel;
    cbbCardType: TWVComboBox;
    cbbOperTrans: TWVComboBox;
    edtBNo: TEdit;
    chkReadCard: TCheckBox;
    chkInfo: TCheckBox;
    RzStatusBar1: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    btnDestory: TBitBtn;
    Label1: TLabel;
    WVComboBox3: TWVComboBox;
    edtPatchNo: TWVEdit;
    lbl1: TLabel;
    Label7: TLabel;
    Label5: TLabel;
    WVComboBox4: TWVComboBox;
    WVComboBox1: TWVComboBox;
    Label6: TLabel;
    Label4: TLabel;
    WVComboBox2: TWVComboBox;
    edtShowCardNo: TWVEdit;
    btnCelDestory: TBitBtn;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnDestoryClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure btnCelDestoryClick(Sender: TObject);
  private

    { Private declarations }
    procedure destCard(ss:string);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardLibDestory: TfaqhCardLibDestory;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhCardLibDestory.Init;
begin
  inherited;
end;

procedure TfaqhCardLibDestory.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhCardLibDestory.btnDestoryClick(Sender: TObject);
var
  cardType:string;
  oper:string;
begin
  cardType := Copy(cbbCardType.Text,0,Pos('-',cbbCardType.Text)-1);
  oper := Copy(cbbOperTrans.Text,0,Pos('-',cbbOperTrans.Text)-1);
  if ((cardType='')or(cardType='-')or(oper='')or(oper='-')) then
  begin
    ShowMessage('��ѡ��Ҫ���Ͽ�Ƭ�����ͺͲ���Ա��');
    exit;
  end;

  if chkInfo.Checked then
    if Application.MessageBox('��ȷ��Ҫ���ϸ����͵Ŀ���',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
      Exit;
  destCard('');
  btnQueryClick(Sender);
end;

procedure TfaqhCardLibDestory.GridCellClick(Column: TColumn);
var
  tmpData:TDataSet;
begin
  tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  try
    edtBNo.Text := tmpData.FieldByName('scust_no').AsString;
    WVCardDestory.FieldByName('������').Data.SetInteger(tmpData.FieldByName('lvol0').AsInteger);
    WVCardDestory.FieldByName('ת�����Ա').Data.SetString(tmpData.FieldByName('semp_no').AsString);
  except
  end;
end;

procedure TfaqhCardLibDestory.destCard(ss: string);
var
  showCardNo:string;
begin
  if chkReadCard.Checked then
  begin
    showCardNo := readShowCarNo;
    edtBNo.Text := showCardNo;
    //edtENo.Text := showCardNo;
  end;
  WVCardDestory.FieldByName('��ʼ���').Data.SetString(edtBNo.Text);
  WVCardDestory.FieldByName('���ϱ�־').Data.SetString(ss);
  WVRCardDestory.SendCommand;
  RzStatusPane1.Caption := WVCardDestory.fieldbyname('������Ϣ').Data.AsString;
end;

procedure TfaqhCardLibDestory.btnCelDestoryClick(Sender: TObject);
var
  cardType:string;
  oper:string;
begin
  cardType := Copy(cbbCardType.Text,0,Pos('-',cbbCardType.Text)-1);
  oper := Copy(cbbOperTrans.Text,0,Pos('-',cbbOperTrans.Text)-1);
  if ((cardType='')or(cardType='-')or(oper='')or(oper='-')) then
  begin
    ShowMessage('��ѡ��Ҫ���Ͽ�Ƭ�����ͺͲ���Ա��');
    exit;
  end;

  if chkInfo.Checked then
    if Application.MessageBox('��ȷ��Ҫȡ�����ϸ����͵Ŀ���',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
      Exit;
  destCard('1');
  btnQueryClick(Sender);
end;

initialization
  TUIStdClassFactory.Create('��Ƭ����',TfaqhCardLibDestory);

end.