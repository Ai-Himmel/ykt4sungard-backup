unit UASettlePara;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  USetParamsTemp;

type
  TfaqhSettlePara = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label8: TLabel;
    Label9: TLabel;
	WVEdit1: TWVEdit;
	WVEdit2: TWVEdit;
	WVEdit3: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    WVEdit6: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    Label_snote: TLabel;
    WVEdit_snote: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnOKClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure WVComboBox1Exit(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSettlePara: TfaqhSettlePara;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhSettlePara.Init;
begin
  inherited;
  WorkView.FieldByName('查询.查询标志（1：结算；2：交易）').DefaultValue := 1;
  WorkView.FieldByName('查询.席_位').DefaultValue := '';
  WorkView.FieldByName('查询.参数代码').DefaultValue := '';
  WorkView.FieldByName('席_位_代_码').DefaultValue := '';  //wlj20031222 为了界面上能修改，名字不能包含席位，否则模板会修改
  WorkView.FieldByName('参数代码').DefaultValue := '';
  WorkView.FieldByName('参数代码值').DefaultValue := '';
  WorkView.FieldByName('操作类别').DefaultValue := '';
  WorkView.Reset;
end;

procedure TfaqhSettlePara.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhSettlePara.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;



procedure TfaqhSettlePara.btnOKClick(Sender: TObject);
var
  tempValue : string;
  iPos : integer;
begin
  tempValue :=  workview.fieldbyname('席_位_代_码').data.asstring;
  iPos := Pos('-',tempValue);
  if iPos <> 0 then             //如果有 － 则进行处理
    workview.fieldbyname('席_位_代_码').data.SetString(Copy(tempValue,1, iPos - 1));

  if(Status = ssDelete) then
  begin
    inherited;
  end
  else  if(WVEdit4.Text = '') then
  begin
    context.GetDialogSystem.ShowMessage('请输入席位代码');
    WVComboBox1.SetFocus;
  end
  else inherited;
  WVEdit_snote.Visible := true;  //显示描述
  Label_snote.Visible := true;
end;

procedure TfaqhSettlePara.btnChangeClick(Sender: TObject);
begin
  inherited;
  WVEdit_snote.Visible := false;  //隐藏描述
  Label_snote.Visible := false;

  WVEdit5.Enabled := false;
  WVComboBox1.Enabled := false;
  WVEdit6.SetFocus;
  WVEdit6.SelectAll;
end;

procedure TfaqhSettlePara.btnAddClick(Sender: TObject);
begin
  inherited;
  WVEdit_snote.Visible := false;  //隐藏描述
  Label_snote.Visible := false;

  WVEdit5.Enabled := true;
  WVComboBox1.Enabled := true;
  WVComboBox1.selectAll;
end;

procedure TfaqhSettlePara.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WVEdit_snote.Visible := false;  //隐藏描述
  Label_snote.Visible := false;

end;

procedure TfaqhSettlePara.btnCancelClick(Sender: TObject);
begin
  inherited;
  WVEdit_snote.Visible := true;  //显示描述
  Label_snote.Visible := true;
end;

procedure TfaqhSettlePara.WVComboBox1Exit(Sender: TObject);
var
  tempValue : string;
  sSeat_no : string;
  iPos : integer;
begin
//  inherited;


  // wlj 20040115 增加对席位有效性的检查
  if workview.fieldbyname('席_位_代_码').data.asstring = '' then exit;
  if workview.fieldbyname('席_位_代_码').data.asstring = '0' then exit;
  if workview.fieldbyname('席_位_代_码').data.asstring = '*' then exit;

  tempValue :=  workview.fieldbyname('席_位_代_码').data.asstring;
  iPos := Pos('-',tempValue);
  if iPos <> 0 then             //如果有 － 则进行处理
    sSeat_no := Copy(tempValue,1, iPos - 1)
  else
    sSeat_no := tempValue;

  //wlj 20040219 如果按esc，席位变disable 或 invisible 那么设置setfocus就会失败。

  if GetIdObjectName(-23,sSeat_no) = '' then
  begin
    try
      WVComboBox1.SelectAll;
      WVComboBox1.SetFocus;
      context.GetDialogSystem.ShowMessage('输入的席位不存在');
    except
    end;
  end;


end;

initialization
  TUIStdClassFactory.Create('设置结算参数',TfaqhSettlePara);

end.