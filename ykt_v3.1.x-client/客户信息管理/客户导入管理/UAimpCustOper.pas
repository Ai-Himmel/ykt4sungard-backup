unit UAimpCustOper;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhimpCustOper = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label3: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    WVEdit3: TWVEdit;
    WVEdit5: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit9: TWVEdit;
    WVEdit13: TWVEdit;
    WVEdit15: TWVEdit;
    cbbQFeeType: TWVComboBox;
    cbbQCustType: TWVComboBox;
    WVComboBox4: TWVComboBox;
    WVComboBox7: TWVComboBox;
    WVComboBox6: TWVComboBox;
    cbbQIdCardType: TWVComboBox;
    Label1: TLabel;
    edtCustName: TWVEdit;
    cbbArea: TWVComboBox;
    Label4: TLabel;
    Label2: TLabel;
    Label17: TLabel;
    cbbFeeType: TWVComboBox;
    WVComboBox3: TWVComboBox;
    Label18: TLabel;
    WVComboBox5: TWVComboBox;
    cbbCustType: TWVComboBox;
    Label16: TLabel;
    WVComboBox9: TWVComboBox;
    Label19: TLabel;
    WVComboBox10: TWVComboBox;
    Label20: TLabel;
    WVEdit2: TWVEdit;
    Label21: TLabel;
    Label22: TLabel;
    WVComboBox11: TWVComboBox;
    Label23: TLabel;
    cbbIdCardType: TWVComboBox;
    Label24: TLabel;
    WVEdit8: TWVEdit;
    Label25: TLabel;
    WVEdit18: TWVEdit;
    WVEdit4: TWVEdit;
    Label26: TLabel;
    Label27: TLabel;
    WVEdit12: TWVEdit;
    WVEdit7: TWVEdit;
    WVLabel2: TWVLabel;
    Label28: TLabel;
    Label29: TLabel;
    WVEdit10: TWVEdit;
    Label30: TLabel;
    Label31: TLabel;
    WVEdit14: TWVEdit;
    edtDestoryDate: TWVEdit;
    WVEdit11: TWVEdit;
    Label32: TLabel;
    edtIdCardNo: TWVEdit;
    WVEdit16: TWVEdit;
    btnCheck: TBitBtn;
    WVRImpCheck: TWVRequest;
    WVImpCheck: TWorkView;
    pbStat: TProgressBar;
    btnPatchDel: TBitBtn;
    Label33: TLabel;
    edtDelPatchNo: TWVEdit;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    lbl1: TLabel;
    WVEdit1: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnCheckClick(Sender: TObject);
    procedure btnPatchDelClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhimpCustOper: TfaqhimpCustOper;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary,USetParamsTemp,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhimpCustOper.Init;
begin
  inherited;
end;

procedure TfaqhimpCustOper.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhimpCustOper.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;



procedure TfaqhimpCustOper.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('操作标志').Data.SetString('R');
  inherited;
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    btnCheck.Enabled := False;
    btnPatchDel.Enabled := False;
  end
  else
  begin
    btnCheck.Enabled := True;
    btnPatchDel.Enabled := True;
  end;
  pbStat.Position := 0;
end;

procedure TfaqhimpCustOper.btnAddClick(Sender: TObject);
begin
  inherited;
  //WorkView.FieldByName('操作标志').Data.SetString('A');
  //WorkView.FieldByName('批次号').Data.SetString('');
  //WorkView.FieldByName('导入顺序号').Data.SetInteger(0);

end;

procedure TfaqhimpCustOper.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('U');
end;

procedure TfaqhimpCustOper.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('D');
end;

procedure TfaqhimpCustOper.btnOKClick(Sender: TObject);
var
  errorMsg:string;
begin
  if ((Status = ssAdd) or (Status = ssChange)) then
  begin
    if Copy(cbbIdCardType.Text,1,Pos('-',cbbIdCardType.Text)-1)='1' then
      if ValidateIDcard(edtIdCardNo.Text,errorMsg)=True then
      begin
        Context.GetDialogSystem.ShowMessage(errorMsg);
        edtIdCardNo.SetFocus;
        Exit;
      end;
    if (cbbFeeType.ItemIndex = -1) or (Trim(cbbFeeType.Text) = '') then
    begin
      Context.GetDialogSystem.ShowMessage('收费类别不能为空！');
      cbbFeeType.SetFocus;
      cbbFeeType.SelectAll;
      Exit;
    end;
    if (cbbCustType.ItemIndex = -1) or (Trim(cbbCustType.Text) = '') then
    begin
      Context.GetDialogSystem.ShowMessage('客户类别不能为空！');
      cbbCustType.SetFocus;
      cbbCustType.SelectAll;
      Exit;
    end;
    if Trim(edtCustName.Text) = '' then
    begin
      Context.GetDialogSystem.ShowMessage('客户名称不能为空！');
      edtCustName.SetFocus;
      edtCustName.SelectAll;
      Exit;
    end;
    if (cbbArea.ItemIndex = -1) or (Trim(cbbArea.Text) = '') then
    begin
      Context.GetDialogSystem.ShowMessage('校区不能为空！');
      WVComboBox4.SetFocus;
      WVComboBox4.SelectAll;
      Exit;
    end;
    if (edtDestoryDate.Text<>'') then
      if CheckInputDateFormat(edtDestoryDate.text)=False then
      begin
        ShowMessage('请输入有效的日期，格式(yyyymmdd)!');
        edtDestoryDate.SetFocus;
        Exit;
      end;
  end;
  inherited;
  btnQuery.Click;
end;

procedure TfaqhimpCustOper.btnCheckClick(Sender: TObject);
var
  tmpDate:TDataSet;
  patchNo:string;
  No:Integer;
begin
  //inherited;
  if Application.MessageBox('你确定要审核该批客户信息吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  tmpDate := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  tmpDate.Last;
  tmpDate.First;
  pbStat.Max := tmpDate.RecordCount;
  while not tmpDate.Eof do
  begin
    patchNo := tmpDate.fieldbyname('scust_limit').AsString;
    no := tmpDate.fieldbyname('lvol4').AsInteger;
    WVImpCheck.FieldByName('导入批次号').Data.SetString(patchNo);
    WVImpCheck.FieldByName('导入顺序号').Data.SetInteger(No);
    WVImpCheck.FieldByName('操作标志').Data.SetString('C');
    WVRImpCheck.SendCommand;
    pbStat.Position := pbStat.Position + 1;
    Sleep(50);
    tmpDate.Next;
  end;
  Context.GetDialogSystem.ShowMessage('客户导入审核完成！');
end;

procedure TfaqhimpCustOper.btnPatchDelClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要删除该批次号的客户吗？',PChar(Application.Title),MB_YESNO)=idno then
    Exit;
  if edtDelPatchNo.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('请输入要批量删除的批次号！');
    Exit;
  end;
  WorkView1.FieldByName('操作标志').Data.SetString('D');
  WorkView1.FieldByName('批量标志').Data.SetInteger(1);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('返回码').Data.AsInteger=0 then
    edtDelPatchNo.Text :='';
  Context.GetDialogSystem.ShowMessage(WorkView1.fieldbyname('返回信息').Data.AsString);
  btnQuery.Click;

end;

initialization
  TUIStdClassFactory.Create('客户导入管理',TfaqhimpCustOper);

end.