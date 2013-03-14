unit UAdevBusiImpManage;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs;

type
  TfaqhdevBusiImpManage = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label20: TLabel;
    Label22: TLabel;
    Label24: TLabel;
    Label25: TLabel;
    Label26: TLabel;
	WVEdit2: TWVEdit;
	WVEdit6: TWVEdit;
	WVEdit7: TWVEdit;
	WVEdit9: TWVEdit;
    edtPatchNo: TWVEdit;
    edtDevName: TWVEdit;
    edtBusiName: TWVEdit;
    edtEndTime: TWVEdit;
    edtStartDate: TWVEdit;
    edtStopDate: TWVEdit;
    Label1: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    WVImpCheck: TWorkView;
    WVRImpCheck: TWVRequest;
    edtDevNo: TWVEdit;
    edtBusiNo: TWVEdit;
    edtNO: TWVEdit;
    btnPatchDel: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    Label33: TLabel;
    edtDelPatchNo: TWVEdit;
    pbstat: TProgressBar;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnPatchDelClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhdevBusiImpManage: TfaqhdevBusiImpManage;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhdevBusiImpManage.Init;
begin
  inherited;
end;

procedure TfaqhdevBusiImpManage.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhdevBusiImpManage.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhdevBusiImpManage.btnAddClick(Sender: TObject);
var
  tmpDate:TDataSet;
  patchNo:string;
  No:Integer;
begin
  //inherited;
  if Application.MessageBox('��ȷ��Ҫ��˸����豸�̻��󶨹�ϵ��',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  try
    tmpDate := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
    tmpDate.Last;
    pbstat.Max := tmpDate.RecordCount;
    tmpDate.First;
    while not tmpDate.Eof do
    begin
      patchNo := tmpDate.fieldbyname('scust_limit').AsString;
      no := tmpDate.fieldbyname('lvol4').AsInteger;
      WVImpCheck.FieldByName('�������κ�').Data.SetString(patchNo);
      WVImpCheck.FieldByName('����˳���').Data.SetInteger(No);
      WVImpCheck.FieldByName('������־').Data.SetString('C');
      WVRImpCheck.SendCommand;
      Sleep(50);
      pbstat.Position := pbstat.Position+1;
      tmpDate.Next;
    end;
    pbstat.Position := pbstat.Max;
    Context.GetDialogSystem.ShowMessage('�豸�̻���ϵ�������ɣ�');
  except
    on ex:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(ex.Message);
    end;
  end;
end;

procedure TfaqhdevBusiImpManage.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('U');
  edtPatchNo.Enabled := False;
  edtNo.Enabled := False;
  edtBusiName.Enabled := False;
  edtDevName.Enabled := False;
end;

procedure TfaqhdevBusiImpManage.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('D');
end;

procedure TfaqhdevBusiImpManage.btnQueryClick(Sender: TObject);
begin
  if Trim(edtDevNo.Text)='' then
    edtDevNo.Text := '0';
  if Trim(edtBusiNo.Text)='' then
    edtBusiNo.Text := '0';
  WorkView.FieldByName('������־').Data.SetString('R');
  inherited;
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    btnPatchDel.Enabled := False;
    btnAdd.Enabled := False;
  end
  else
  begin
    btnAdd.Enabled := True;
    btnPatchDel.Enabled :=True;
  end;
end;

procedure TfaqhdevBusiImpManage.btnOKClick(Sender: TObject);
begin
  if (Trim(edtStartDate.Text)<>'') and (CheckInputDateFormat(edtStartDate.Text)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('�������������ʽ����ȷ��');
    edtStartDate.SetFocus;
    Exit;
  end;
  if (Trim(edtStopDate.Text)<>'') and (CheckInputDateFormat(edtStopDate.Text)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('ͣ�����������ʽ����ȷ��');
    edtStopDate.SetFocus;
    Exit;
  end;
  if (Trim(edtEndTime.Text)<>'') and (CheckInputTimeFormat(edtEndTime.Text)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('����ʱ�������ʽ����ȷ��');
    edtEndTime.SetFocus;
    Exit;
  end;
  inherited;
  btnQuery.Click;
end;

procedure TfaqhdevBusiImpManage.btnPatchDelClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫɾ�������κŵ��豸�̻���',PChar(Application.Title),MB_YESNO)=idno then
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
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('�豸�̻��������',TfaqhdevBusiImpManage);

end.