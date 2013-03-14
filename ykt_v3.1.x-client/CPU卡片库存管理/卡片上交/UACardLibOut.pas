unit UACardLibOut;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,CardDll,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  ComCtrls, RzStatus, RzPanel;

type
  TfaqhCardLibOut = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    WVCardOut: TWorkView;
    WVRCardOut: TWVRequest;
    grp1: TGroupBox;
    Label2: TLabel;
    lblBNo: TLabel;
    Label3: TLabel;
    cbbCardType: TWVComboBox;
    edtBNo: TEdit;
    edtENo: TEdit;
    chkReadCard: TCheckBox;
    chkInfo: TCheckBox;
    btnOut: TBitBtn;
    RzStatusBar1: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    Label1: TLabel;
    lbl1: TLabel;
    edtPatchNo: TWVEdit;
    WVComboBox3: TWVComboBox;
    Label7: TLabel;
    WVComboBox4: TWVComboBox;
    Label6: TLabel;
    Label4: TLabel;
    edtShowCardNo: TWVEdit;
    WVComboBox2: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnOutClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardLibOut: TfaqhCardLibOut;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;

{$R *.DFM}

procedure TfaqhCardLibOut.Init;
begin
  inherited;
end;

procedure TfaqhCardLibOut.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



procedure TfaqhCardLibOut.btnOutClick(Sender: TObject);
var
  cardType:string;
  showCardNo:string;
begin
  cardType := Copy(cbbCardType.Text,0,Pos('-',cbbCardType.Text)-1);
  //oper := Copy(cbbOperTrans.Text,0,Pos('-',cbbOperTrans.Text)-1);
  if ((cardType='')or(cardType='-')) then
  begin
    ShowMessage('��ѡ��Ҫ�Ͻ���Ƭ�����ͣ�');
    exit;
  end;

  if chkInfo.Checked then
    if Application.MessageBox('��ȷ��Ҫ�Ͻ������͵Ŀ���',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
      Exit;

  if chkReadCard.Checked then
  begin
    showCardNo := readCardOneInfo(SHOW_CARDNO);
    if showCardNo='' then
    begin
      Context.GetDialogSystem.ShowMessage('��ȡ��ʾ����ʧ�ܣ�');
      Exit;
    end;
    edtBNo.Text := showCardNo;
    edtENo.Text := showCardNo;
  end;
  WVCardOut.FieldByName('��ʼ���').Data.SetString(edtBNo.Text);
  WVCardOut.FieldByName('�������').Data.SetString(edtENo.Text);
  WVCardOut.FieldByName('ת�����Ա').Data.SetString(edtENo.Text);
  WVRCardOut.SendCommand;
  RzStatusPane1.Caption := WVCardOut.fieldbyname('������Ϣ').Data.AsString;
  btnQueryClick(Sender);
end;

procedure TfaqhCardLibOut.GridCellClick(Column: TColumn);
var
  tmpData:TDataSet;
begin
  tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  try
    edtBNo.Text := tmpData.FieldByName('scust_no').AsString;
    edteNo.Text := tmpData.FieldByName('scust_no').AsString;
    WVCardOut.FieldByName('������').Data.SetInteger(tmpData.FieldByName('lvol0').AsInteger);
  except
  end;
end;

procedure TfaqhCardLibOut.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('ת�����Ա').Data.SetString(context.GetParamValue(svOperatorNoName));
  inherited;

end;

initialization
  TUIStdClassFactory.Create('��Ƭ�Ͻ�',TfaqhCardLibOut);

end.