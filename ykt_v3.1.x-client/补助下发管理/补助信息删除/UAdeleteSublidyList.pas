unit UAdeleteSublidyList;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, RzStatus, UIncrementComboBox,
  Buttons;

type
  TfaqhdeleteSublidyList = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    WVEdit1: TWVEdit;
    edtPatchNo: TWVEdit;
    WVEdit3: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit7: TWVEdit;
    Label10: TLabel;
    edtPNo: TWVEdit;
    btnPDelete: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    RzStatusPane1: TRzStatusPane;
    cbbType: TWVComboBox;
    Label11: TLabel;
    edtCustNo: TWVEdit;
    Label9: TLabel;
    edtCardNo: TWVEdit;
    procedure btnQueryClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure btnPDeleteClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhdeleteSublidyList: TfaqhdeleteSublidyList;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhdeleteSublidyList.Init;
begin
  inherited;
  {
  WorkView.FieldByName('ѧ����').DefaultValue := '';
  WorkView.FieldByName('�ͻ���').DefaultValue := 0;
  WorkView.FieldByName('�������κ�').DefaultValue := 0;
  WorkView.FieldByName('����').DefaultValue := 0;
  WorkView.FieldByName('�������κ�').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('��ȡ����').DefaultValue := '';
  WorkView.FieldByName('���������֤��').DefaultValue := '';
  WorkView.FieldByName('����������').DefaultValue := '';
  WorkView.FieldByName('״̬').DefaultValue := '';
  WorkView.Reset;
  }
end;

procedure TfaqhdeleteSublidyList.btnQueryClick(Sender: TObject);
begin
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  if Trim(edtPatchNo.Text)='' then
    edtPatchNo.Text := '0';
  if Trim(edtCardno.Text)='' then
    WorkView.FieldByName('����').Data.SetInteger(0);
  WorkView.FieldByName('��������').Data.SetString('R');
  inherited;

end;

procedure TfaqhdeleteSublidyList.btnPrintClick(Sender: TObject);
var
  custNo : string;
  tempDataSet : TDataSet;
  scustlimit:string;
begin
  //inherited;
  tempDataSet := WorkView.FieldByName('��ѯ�����').Data.AsObject as TDataSet;
  custNo := tempDataSet.fieldbyname('scust_auth').AsString;
  scustlimit := tempDataSet.fieldbyname('scust_limit').AsString;
  WorkView1.FieldByName('ѧ����').Data.SetString(custNo);
  WorkView1.FieldByName('�������κ�').Data.SetString(scustlimit);
  WorkView1.FieldByName('ɾ����־').Data.SetInteger(0);
  WorkView1.FieldByName('��������').Data.SetString('D');
  WVRequest1.SendCommand;
  ShowMessage(WorkView1.fieldbyname('������Ϣ').Data.AsString);
  RzStatusPane1.Caption:=WorkView1.fieldbyname('������Ϣ').Data.AsString;
  btnQuery.Click;

end;

procedure TfaqhdeleteSublidyList.btnPDeleteClick(Sender: TObject);
begin
  if Trim(edtPNo.Text)='' then
  begin
    ShowMessage('��������Ҫ����ɾ�������κ�');
    edtPNo.SetFocus;
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ����ɾ������������Ϣ��',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  WorkView1.FieldByName('ѧ����').Data.SetString('');
  WorkView1.FieldByName('��������').Data.SetString('D');
  WorkView1.FieldByName('�������κ�').Data.SetString(edtPNo.Text);
  WorkView1.FieldByName('ɾ����־').Data.SetInteger(1);
  WVRequest1.SendCommand;
  ShowMessage(WorkView1.fieldbyname('������Ϣ').Data.AsString);
  RzStatusPane1.Caption:=WorkView1.fieldbyname('������Ϣ').Data.AsString;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('������Ϣɾ��',TfaqhdeleteSublidyList);

end.