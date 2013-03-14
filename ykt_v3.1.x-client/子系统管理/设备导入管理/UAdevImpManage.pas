unit UAdevImpManage;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhdevImpManage = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label17: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label23: TLabel;
    Label24: TLabel;
    Label25: TLabel;
    Label26: TLabel;
    Label27: TLabel;
    Label28: TLabel;
    Label29: TLabel;
    Label30: TLabel;
    Label31: TLabel;
    Label32: TLabel;
    Label33: TLabel;
    Label35: TLabel;
    Label36: TLabel;
    Label37: TLabel;
    WVEdit3: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    edtPatchNo: TWVEdit;
    edtEquName: TWVEdit;
    WVEdit24: TWVEdit;
    edtUEqu: TWVEdit;
    edtSerPortNo: TWVEdit;
    edtIP: TWVEdit;
    cbbQEquPhyType: TWVComboBox;
    cbbQMachineType: TWVComboBox;
    cbbQUseType: TWVComboBox;
    cbbQChildSys: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox4: TWVComboBox;
    Label1: TLabel;
    Label2: TLabel;
    cbbEquPhyType: TWVComboBox;
    cbbMachineType: TWVComboBox;
    cbbUseType: TWVComboBox;
    cbbArea: TWVComboBox;
    cbbChildSys: TWVComboBox;
    WVComboBox8: TWVComboBox;
    cbbComm: TWVComboBox;
    WVImpCheck: TWorkView;
    WVRImpCheck: TWVRequest;
    edtMachineNo: TWVEdit;
    edtSerPortNum: TWVEdit;
    edtCommPortNo: TWVEdit;
    edtNo: TWVEdit;
    pbstat: TProgressBar;
    btnPatchDel: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    Label10: TLabel;
    edtDelPatchNo: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnAddClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
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
  faqhdevImpManage: TfaqhdevImpManage;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary,SmartCardCommon,USetParamsTemp;
     
{$R *.DFM}

procedure TfaqhdevImpManage.Init;
begin
  inherited;
  btnAdd.Enabled := False
end;

procedure TfaqhdevImpManage.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhdevImpManage.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhdevImpManage.btnAddClick(Sender: TObject);
var
  tmpDate:TDataSet;
  patchNo:string;
  No:Integer;
begin
  //inherited;
  if Grid.DataSource.DataSet.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('���Ȳ�ѯ��Ҫ��˵��豸��Ȼ����ˣ�');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ��˸����豸��',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
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
    pbstat.Position := pbstat.Position + 1;
    tmpDate.Next;
  end;
  Context.GetDialogSystem.ShowMessage('�豸��Ϣ������˳ɹ���');
end;

procedure TfaqhdevImpManage.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('������־').Data.SetString('R');
  inherited;
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    btnAdd.Enabled := False ;
    btnPatchDel.Enabled := False;
  end
  else
  begin
    btnAdd.Enabled := True;
    btnPatchDel.Enabled := True;
  end;
  pbstat.Position := 0;
end;

procedure TfaqhdevImpManage.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('U');
  edtNo.Enabled := False;
  edtPatchNo.Enabled := False;
end;

procedure TfaqhdevImpManage.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('������־').Data.SetString('D');
end;

procedure TfaqhdevImpManage.btnOKClick(Sender: TObject);
var
  tmpMsg:string;
begin
  if ((Status = ssAdd) or (Status = ssChange)) then
  begin
    if Trim(edtEquName.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('�������豸���ƣ�');
      edtEquName.SetFocus;
      exit;
    end;
    if Trim(cbbEquPhyType.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('��ѡ���豸���ͣ�');
      cbbEquPhyType.SetFocus;
      exit;
    end;
    if Trim(cbbMachineType.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('��ѡ���豸���ͣ�');
      cbbMachineType.SetFocus;
      exit;
    end;
    if Trim(cbbUseType.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('��ѡ���豸��;��');
      cbbUseType.SetFocus;
      exit;
    end;
    if Trim(cbbArea.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('��ѡ���豸��������');
      cbbArea.SetFocus;
      exit;
    end;
    if Trim(cbbChildSys.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('��ѡ���豸������ϵͳ��');
      cbbChildSys.SetFocus;
      exit;
    end;
    if Trim(edtUEqu.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('�������ϼ��豸��');
      Exit;
    end;
  end;
  if (Trim(edtIP.Text)<>'') then
  begin
    tmpMsg := CheckIpAddress(edtIP.Text);
    if tmpMsg<>'' then
    begin
      Context.GetDialogSystem.ShowMessage(tmpMsg);
      edtIP.SetFocus;
      Exit;
    end;
  end;
  if Trim(edtSerPortNo.Text)='' then
    edtSerPortNo.Text := '0';
  if Trim(edtSerPortNum.Text)='' then
    edtSerPortNum.Text := '0';
  if Trim(edtMachineNo.Text)='' then
    edtMachineNo.Text := '0';
  if Trim(edtCommPortNo.Text)='' then
    edtCommPortNo.Text := '0';
  WorkView.FieldByName('�Ƿ�֧�ֿ�Ŀ�շ�').Data.SetInteger(0);
  inherited;
  btnQuery.Click;
end;

procedure TfaqhdevImpManage.btnPatchDelClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫɾ�������κŵ��豸��',PChar(Application.Title),MB_YESNO)=idno then
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
  btnQueryClick(Sender);
end;

initialization
  TUIStdClassFactory.Create('�豸�������',TfaqhdevImpManage);

end.