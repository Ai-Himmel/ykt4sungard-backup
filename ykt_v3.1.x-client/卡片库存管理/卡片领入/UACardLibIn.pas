unit UACardLibIn;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ExtCtrls, UICtrls, WVCtrls, WVDBBinders, Db,UtCardDll, 
  RzDBGrid, Buttons, UIncrementComboBox, ComCtrls, RzStatus, RzPanel, Mask;

type
  TfaqhCardLibIn = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label5: TLabel;
    WVComboBox3: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVCardIn: TWorkView;
    WVRCardIn: TWVRequest;
    grp1: TGroupBox;
    cbbCardType: TWVComboBox;
    Label2: TLabel;
    lblTransTo: TLabel;
    cbbOperTrans: TWVComboBox;
    lblBNo: TLabel;
    edtBNo: TEdit;
    Label3: TLabel;
    edtENo: TEdit;
    btnIn: TBitBtn;
    chkReadCard: TCheckBox;
    chkInfo: TCheckBox;
    RzStatusBar1: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    Label4: TLabel;
    lbl1: TLabel;
    Label6: TLabel;
    WVComboBox2: TWVComboBox;
    edtShowCardNo: TWVEdit;
    edtPatchNo: TWVEdit;
    Label7: TLabel;
    WVComboBox4: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnInClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardLibIn: TfaqhCardLibIn;

implementation

uses KsFrameworks, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhCardLibIn.Init;
begin
  inherited;
end;

procedure TfaqhCardLibIn.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhCardLibIn.btnInClick(Sender: TObject);
var
  cardType:string;
  oper:string;
  showCardNo:string;
begin
  cardType := Copy(cbbCardType.Text,0,Pos('-',cbbCardType.Text)-1);
  oper := Copy(cbbOperTrans.Text,0,Pos('-',cbbOperTrans.Text)-1);
  if ((cardType='')or(cardType='-')or(oper='')or(oper='-')) then
  begin
    ShowMessage('��ѡ��Ҫ���뿨Ƭ�����ͺ�Ҫ����Ĳ���Ա��');
    exit;
  end;

  if chkInfo.Checked then
    if Application.MessageBox('��ȷ��Ҫ��������͵Ŀ���',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
      Exit;

  if chkReadCard.Checked then
  begin
    showCardNo := readShowCarNo;
    edtBNo.Text := showCardNo;
    edtENo.Text := showCardNo;
  end;
  WVCardIn.FieldByName('��ʼ���').Data.SetString(edtBNo.Text);
  WVCardIn.FieldByName('�������').Data.SetString(edtENo.Text);
  WVRCardIn.SendCommand;
  RzStatusPane1.Caption := WVCardIn.fieldbyname('������Ϣ').Data.AsString;
  btnQueryClick(Sender);
end;

initialization
  TUIStdClassFactory.Create('��Ƭ����',TfaqhCardLibIn);

end.