unit UASetBusiInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhSetBusiInfo = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label25: TLabel;
    Label26: TLabel;
	WVEdit3: TWVEdit;
	WVEdit4: TWVEdit;
	WVEdit5: TWVEdit;
	WVEdit6: TWVEdit;
	WVEdit7: TWVEdit;
    WVDigitalEdit26: TWVDigitalEdit;
    edtBusiId: TWVEdit;
    WVComboBox8: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    grp1: TGroupBox;
    Label28: TLabel;
    WVEdit28: TWVEdit;
    Label27: TLabel;
    WVEdit27: TWVEdit;
    Label29: TLabel;
    edtBusiName: TWVEdit;
    Label30: TLabel;
    edtBusiEngName: TWVEdit;
    Label31: TLabel;
    WVEdit31: TWVEdit;
    Label32: TLabel;
    Label33: TLabel;
    Label47: TLabel;
    WVEdit47: TWVEdit;
    Label41: TLabel;
    WVDigitalEdit41: TWVDigitalEdit;
    GroupBox1: TGroupBox;
    Label34: TLabel;
    WVEdit34: TWVEdit;
    Label35: TLabel;
    WVEdit35: TWVEdit;
    Label36: TLabel;
    WVEdit36: TWVEdit;
    Label37: TLabel;
    WVEdit37: TWVEdit;
    Label38: TLabel;
    WVEdit38: TWVEdit;
    Label39: TLabel;
    WVEdit39: TWVEdit;
    Label40: TLabel;
    WVEdit40: TWVEdit;
    grp2: TGroupBox;
    Label42: TLabel;
    Label43: TLabel;
    WVEdit43: TWVEdit;
    Label44: TLabel;
    WVEdit44: TWVEdit;
    Label45: TLabel;
    WVEdit45: TWVEdit;
    cbb1: TWVComboBox;
    WVComboBox3: TWVComboBox;
    edt1: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetBusiInfo: TfaqhSetBusiInfo;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhSetBusiInfo.Init;
begin
  inherited;
  {
  WorkView.FieldByName('查询.操作标志').DefaultValue := '';
  WorkView.FieldByName('查询.商户编号').DefaultValue := 0;
  WorkView.FieldByName('查询.中心商户号').DefaultValue := '';
  WorkView.FieldByName('查询.省商户编号').DefaultValue := '';
  WorkView.FieldByName('查询.商户名').DefaultValue := '';
  WorkView.FieldByName('查询.商户英文名称').DefaultValue := '';
  WorkView.FieldByName('查询.商户简称').DefaultValue := '';
  WorkView.FieldByName('查询.商户类型').DefaultValue := '';
  WorkView.FieldByName('查询.行业类型').DefaultValue := '';
  WorkView.FieldByName('查询.联系人').DefaultValue := '';
  WorkView.FieldByName('查询.电话').DefaultValue := '';
  WorkView.FieldByName('查询.手机').DefaultValue := '';
  WorkView.FieldByName('查询.电子信箱').DefaultValue := '';
  WorkView.FieldByName('查询.传真').DefaultValue := '';
  WorkView.FieldByName('查询.营业地址').DefaultValue := ;
  WorkView.FieldByName('查询.邮政编码').DefaultValue := '';
  WorkView.FieldByName('查询.结算费率').DefaultValue := 0.00;
  WorkView.FieldByName('查询.开户银行').DefaultValue := '';
  WorkView.FieldByName('查询.银行账号').DefaultValue := '';
  WorkView.FieldByName('查询.银行帐户名').DefaultValue := '';
  WorkView.FieldByName('查询.联行号').DefaultValue := '';
  WorkView.FieldByName('查询.开户日期').DefaultValue := '';
  WorkView.FieldByName('查询.销户日期').DefaultValue := '';
  WorkView.FieldByName('查询.销户状态').DefaultValue := '';
  WorkView.FieldByName('查询.商户状态').DefaultValue := '';
  WorkView.FieldByName('商户编号').DefaultValue := 0;
  WorkView.FieldByName('中心商户号').DefaultValue := '';
  WorkView.FieldByName('省商户编号').DefaultValue := '';
  WorkView.FieldByName('商户名').DefaultValue := '';
  WorkView.FieldByName('商户英文名称').DefaultValue := '';
  WorkView.FieldByName('商户简称').DefaultValue := '';
  WorkView.FieldByName('商户类型').DefaultValue := '';
  WorkView.FieldByName('行业类型').DefaultValue := '';
  WorkView.FieldByName('联系人').DefaultValue := '';
  WorkView.FieldByName('电话').DefaultValue := '';
  WorkView.FieldByName('手机').DefaultValue := '';
  WorkView.FieldByName('电子信箱').DefaultValue := '';
  WorkView.FieldByName('传真').DefaultValue := '';
  WorkView.FieldByName('营业地址').DefaultValue := ;
  WorkView.FieldByName('邮政编码').DefaultValue := '';
  WorkView.FieldByName('结算费率').DefaultValue := 0.00;
  WorkView.FieldByName('开户银行').DefaultValue := '';
  WorkView.FieldByName('银行账号').DefaultValue := '';
  WorkView.FieldByName('银行帐户名').DefaultValue := '';
  WorkView.FieldByName('联行号').DefaultValue := '';
  WorkView.FieldByName('开户日期').DefaultValue := '';
  WorkView.FieldByName('销户日期').DefaultValue := '';
  WorkView.FieldByName('销户状态').DefaultValue := '';
  WorkView.FieldByName('商户状态').DefaultValue := '';
  WorkView.Reset;
  }
end;

procedure TfaqhSetBusiInfo.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhSetBusiInfo.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhSetBusiInfo.btnQueryClick(Sender: TObject);
begin
  if Trim(edtBusiId.Text)='' then
    edtBusiId.Text := '0';
  WorkView.FieldByName('操作标志').Data.SetString('R');
  inherited;
end;

procedure TfaqhSetBusiInfo.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('A');
end;

procedure TfaqhSetBusiInfo.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('E');
end;

procedure TfaqhSetBusiInfo.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('D');
end;

procedure TfaqhSetBusiInfo.btnOKClick(Sender: TObject);
begin
  if Trim(edtBusiName.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('商户名称不能为空！');
    edtBusiName.SetFocus;
    Exit;
  end;
  inherited;
  btnQuery.Click;
end;

initialization
  TUIStdClassFactory.Create('商户信息管理',TfaqhSetBusiInfo);

end.