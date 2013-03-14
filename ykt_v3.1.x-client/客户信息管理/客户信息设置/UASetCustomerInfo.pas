unit UASetCustomerInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, 
  UIncrementComboBox, RzDBNav, RzButton, RzRadChk, RzDBGrid, RzTabs,
  Buttons, FilterCombos;

type
  TfaqhSetCustomerInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
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
    cbbCustType: TWVComboBox;
    WVComboBox4: TWVComboBox;
    WVEdit5: TWVEdit;
    cbbDept: TWVComboBox;
    WVEdit8: TWVEdit;
    WVComboBox9: TWVComboBox;
    WVComboBox10: TWVComboBox;
    edtIdCardNo: TWVEdit;
    WVEdit12: TWVEdit;
    WVEdit13: TWVEdit;
    edtDestoryDate: TWVEdit;
    WVLabel2: TWVLabel;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    WVEdit4: TWVEdit;
    WVLabel4: TWVLabel;
    WVEdit7: TWVEdit;
    WVLabel5: TWVLabel;
    WVEdit9: TWVEdit;
    WVLabel6: TWVLabel;
    WVEdit10: TWVEdit;
    WVLabel7: TWVLabel;
    WVEdit15: TWVEdit;
    WVLabel8: TWVLabel;
    WVComboBox1: TWVComboBox;
    WVEdit6: TWVEdit;
    Label17: TLabel;
    cbbFeeType: TWVComboBox;
    WVLabel9: TWVLabel;
    WVComboBox5: TWVComboBox;
    Label18: TLabel;
    cbbSpec: TWVComboBox;
    WVLabel10: TWVLabel;
    WVEdit16: TWVEdit;
    WVLabel11: TWVLabel;
    WVEdit17: TWVEdit;
    Label15: TLabel;
    WVComboBox2: TWVComboBox;
    Label19: TLabel;
    cbbIdCardType: TWVComboBox;
    WVEdit14: TWVEdit;
    Label20: TLabel;
    Label21: TLabel;
    WVEdit18: TWVEdit;
    Label22: TLabel;
    edtInDate: TWVEdit;
    cbb1: TKSFilterComboBox;
    cbb2: TKSFilterComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnChangeClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure DBNavigatorClick(Sender: TObject; Button: TNavigateBtn);
    procedure btnDeleteClick(Sender: TObject);
    procedure cbb1FilterItems(Sender: TObject);
    procedure cbb2FilterItems(Sender: TObject);
    {procedure WVComboBox3Change(Sender: TObject);}
  private

    { Private declarations }
    Fdept,Fspec:TStringList;
    FDspDept,FDspSpec:TStringList;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetCustomerInfo: TfaqhSetCustomerInfo;
  flag: integer;

implementation

uses KsFrameworks, 
  SmartCardCommon, USetParamsTemp,TypInfo, DBAIntf;

{$R *.DFM}

procedure TfaqhSetCustomerInfo.Init;
begin
  inherited;
  fillData2FilterCbb(Fdept,FDspDept,cbbDept);
  fillData2FilterCbb(Fspec,FDspSpec,cbbSpec);

  WVEdit3.Text := '0';
end;                                           

procedure TfaqhSetCustomerInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;


procedure TfaqhSetCustomerInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled := Valid;
end;

procedure TfaqhSetCustomerInfo.btnChangeClick(Sender: TObject);
begin
  inherited;
  WVEdit4.Enabled := False;
  WorkView.FieldByName('交易类型').Data.SetString('U');
  cbb1.Text := cbbDept.Text;
  cbb2.Text := cbbSpec.Text;
  cbb1.Enabled := True;
  cbb2.Enabled := True;
end;

procedure TfaqhSetCustomerInfo.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit3.Text) = '' then
  begin
    WorkView.FieldByName('查询.客户号').Data.SetInteger(0);
  end;
  WorkView.FieldByName('交易类型').Data.SetString('R');
  inherited;
end;

procedure TfaqhSetCustomerInfo.btnAddClick(Sender: TObject);
begin
  WVEdit6.Text:='';
  inherited;
  WorkView.FieldByName('交易类型').Data.SetString('A');
  WorkView.FieldByName('客户号').Data.SetInteger(0);
  cbb1.Text := cbbDept.Text;
  cbb2.Text := cbbSpec.Text;
  cbb1.Enabled := True;
  cbb2.Enabled := True;
end;

procedure TfaqhSetCustomerInfo.btnOKClick(Sender: TObject);
var
  errorMsg:string;
  deptNo,specNo:string;
begin
  if ((Status = ssAdd) or (Status = ssChange)) then
  begin
    if Copy(cbbIdCardType.Text,1,Pos('-',cbbIdCardType.Text)-1)='1' then
    begin
      errorMsg := ValidatePID(trim(edtIdCardNo.Text));
      if errorMsg<>'' then
      begin
        if Application.MessageBox(PChar(errorMsg+',你是否要继续保存？'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
          Exit;
        //Context.GetDialogSystem.ShowMessage(errorMsg);
      end;

    end;
    {
      if ValidateIDcard(edtIdCardNo.Text,errorMsg)=True then
      begin
        Context.GetDialogSystem.ShowMessage(errorMsg);
        edtIdCardNo.SetFocus;
        Exit;
      end;
      }
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
    if Trim(WVEdit5.Text) = '' then
    begin
      Context.GetDialogSystem.ShowMessage('客户名称不能为空！');
      WVEdit5.SetFocus;
      WVEdit5.SelectAll;
      Exit;
    end;
    if (WVComboBox4.ItemIndex = -1) or (Trim(WVComboBox4.Text) = '') then
    begin
      Context.GetDialogSystem.ShowMessage('校区不能为空！');
      WVComboBox4.SetFocus;
      WVComboBox4.SelectAll;
      Exit;
    end;
    if (edtDestoryDate.Text<>'') then
      if CheckInputDateFormat(edtDestoryDate.text)=False then
      begin
        Context.GetDialogSystem.ShowMessage('请输入有效的日期，格式(yyyymmdd)!');
        edtDestoryDate.SetFocus;
        Exit;
      end;
    if (edtInDate.Text<>'') then
      if CheckInputDateFormat(edtInDate.text)=False then
      begin
        Context.GetDialogSystem.ShowMessage('请输入有效的日期，格式(yyyymmdd)!');
        edtInDate.SetFocus;
        Exit;
      end;
  end;
  try
    deptNo := Trim(Copy(cbb1.Text,1,Pos('-',cbb1.Text)-1));
    specNo := Trim(Copy(cbb2.Text,1,Pos('-',cbb2.Text)-1));
  except

  end;
  
  WorkView.FieldByName('联系人班级或部门号').Data.SetString(deptNo);
  WorkView.FieldByName('专业').Data.SetString(specNo);

  inherited;
  btnQuery.Click;
end;

procedure TfaqhSetCustomerInfo.DBNavigatorClick(Sender: TObject;
  Button: TNavigateBtn);
begin
  inherited;
  if datasource.DataSet.RecNo = datasource.DataSet.RecordCount then
  begin
    datasource.DataSet.Last;
  end;
  if datasource.DataSet.RecNo = 0 then
  begin
    datasource.DataSet.First;
  end;

end;

procedure TfaqhSetCustomerInfo.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('交易类型').Data.SetString('D');
  cbb1.Text := cbbDept.Text;
  cbb2.Text := cbbSpec.Text;
  cbb1.Enabled := False;
  cbb2.Enabled := False;

end;

procedure TfaqhSetCustomerInfo.cbb1FilterItems(Sender: TObject);
begin
  cbbFilterItem( Fdept,FDspDept,sender);

end;

procedure TfaqhSetCustomerInfo.cbb2FilterItems(Sender: TObject);
begin
  cbbFilterItem( Fspec,FDspSpec,sender);

end;

initialization
  TUIStdClassFactory.Create('客户信息设置', TfaqhSetCustomerInfo);

end.


