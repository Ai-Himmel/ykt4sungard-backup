unit UAimpNewStuCardOper;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhimpNewStuCardOper = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label3: TLabel;
    Label6: TLabel;
    Label9: TLabel;
    WVEdit3: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit9: TWVEdit;
    edtStuempNo: TWVEdit;
    Label21: TLabel;
    Label32: TLabel;
    btnPatchDel: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    Label10: TLabel;
    edtDelPatchNo: TWVEdit;
    Label12: TLabel;
    WVEdit1: TWVEdit;
    lbl1: TLabel;
    cbbstatus: TWVComboBox;
    Label1: TLabel;
    edtDealDate: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnPatchDelClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhimpNewStuCardOper: TfaqhimpNewStuCardOper;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary,USetParamsTemp,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhimpNewStuCardOper.Init;
begin
  inherited;
end;

procedure TfaqhimpNewStuCardOper.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhimpNewStuCardOper.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhimpNewStuCardOper.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('������־').Data.SetString('R');
  inherited;
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    btnPatchDel.Enabled := False;
  end
  else
  begin
    btnPatchDel.Enabled := True;
  end;
end;

procedure TfaqhimpNewStuCardOper.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('A');
end;

procedure TfaqhimpNewStuCardOper.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('U');
  //edtStuempNo.Enabled := False;
end;

procedure TfaqhimpNewStuCardOper.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('D');
end;

procedure TfaqhimpNewStuCardOper.btnOKClick(Sender: TObject);
begin
  if (Trim(edtDealDate.Text)='') then
  begin
    Context.GetDialogSystem.ShowMessage('��������Ч�����ڣ���ʽ(yyyymmdd)!');
    edtDealDate.SetFocus;
    Exit;
  end;
  if (edtDealDate.Text<>'') then
    if CheckInputDateFormat(edtDealDate.text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('��������Ч�����ڣ���ʽ(yyyymmdd)!');
      edtDealDate.SetFocus;
      Exit;
    end;
  if (Status = ssAdd) then
  begin
    if (Trim(WVEdit1.Text)='') and (Trim(edtStuempNo.Text)='') then
    begin
      Context.GetDialogSystem.ShowMessage('�¿����ź�ѧ���Ų���Ϊ�գ�');
      Exit;
    end;
  end;
  inherited;
  btnQuery.Click;
end;

procedure TfaqhimpNewStuCardOper.btnPatchDelClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫɾ�������κŵ�����������',PChar(Application.Title),MB_YESNO)=idno then
    Exit;
  if edtDelPatchNo.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('������Ҫ����ɾ�������κţ�');
    Exit;
  end;
  WorkView1.FieldByName('������־').Data.SetString('D');
  WorkView1.FieldByName('������־').Data.SetInteger(1);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('������').Data.AsInteger=0 then
    edtDelPatchNo.Text :='';
  Context.GetDialogSystem.ShowMessage(WorkView1.fieldbyname('������Ϣ').Data.AsString);

end;

initialization
  TUIStdClassFactory.Create('����������������',TfaqhimpNewStuCardOper);

end.