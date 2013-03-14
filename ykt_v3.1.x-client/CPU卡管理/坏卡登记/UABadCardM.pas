unit UABadCardM;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzButton,RzRadChk, RzStatus, RzPanel, RzEdit, Buttons,
  dxCntner, dxInspct, RzSplit, Menus, UIncrementComboBox, CardDll;

type
  TfaqhCardBad = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    WVLabel5: TWVLabel;
    WVComboBox6: TWVComboBox;
    WVLabel6: TWVLabel;
    WVComboBox1: TWVComboBox;
    WVLabel2: TWVLabel;
    WVComboBox3: TWVComboBox;
    Label7: TLabel;
    WVEdit8: TWVEdit;
    WVLabel9: TWVLabel;
    WVLabel1: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel8: TWVLabel;
    WVComboBox5: TWVComboBox;
    WVEdit6: TWVEdit;
    Label6: TLabel;
    Label5: TLabel;
    btnLose: TBitBtn;
    WVEdit4: TWVEdit;
    cbb1: TWVComboBox;
    Label4: TLabel;
    WVEdit5: TWVEdit;
    Label12: TLabel;
    cbbBadRea: TWVComboBox;
    WVRequest1: TWVRequest;
    WorkView1: TWorkView;
    Label8: TLabel;
    WVComboBox4: TWVComboBox;
    btnDelete: TBitBtn;
    btnEdit: TBitBtn;
    WVLabel4: TWVLabel;
    WVComboBox7: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnLoseClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnEditClick(Sender: TObject);
  private
    { Private declarations }
    procedure recordOper(operSign:string;operContext:string);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardBad: TfaqhCardBad;

implementation

uses KsFrameworks,KSDataDictionary,KSClientConsts;

{$R *.DFM}

procedure TfaqhCardBad.Init;
begin
  inherited;
end;

procedure TfaqhCardBad.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhCardBad.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit1.Text) = '' then
  begin
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  end;
  WorkView.FieldByName('钱包号').Data.SetInteger(1);
  inherited;
end;


procedure TfaqhCardBad.btnLoseClick(Sender: TObject);
var
  ssType:string;
begin
  ssType := Copy(cbbBadRea.Text,1,Pos('-',cbbBadRea.Text)-1);
  if (ssType='')or(ssType='-') then
  begin
    Context.GetDialogSystem.ShowMessage('请选择坏卡原因!');
    Exit;
  end;
  recordOper('A','登记');
end;

procedure TfaqhCardBad.btnDeleteClick(Sender: TObject);
begin
  recordOper('D','取消登记');
end;

procedure TfaqhCardBad.recordOper(operSign:string;operContext:string);
var
  cardid:Integer;
  tipInfo:string;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('没有数据，无法进行此操作！');
    Exit;
  end;
  if Application.MessageBox(PChar('你确定要'+opercontext+'选中的坏卡吗？'),PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  try
    CardID := (WorkView.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('lvol0').AsInteger;
  except
    Context.GetDialogSystem.ShowMessage('请选择要登记的记录！');
    Exit;
  end;
  WorkView1.FieldByName('卡号').Data.SetInteger(CardID);
  WorkView1.FieldByName('操作标志').Data.SetString(operSign);

  try
    WVRequest1.SendCommand;
  finally
    tipInfo := WorkView1.fieldbyname('返回信息').Data.AsString;
    if (WorkView1.FieldByName('返回码').Data.AsInteger = 0) then
    begin
      Context.GetDialogSystem.ShowSuccess(operContext+'坏卡成功  '+tipinfo);
      RzStatusPane1.Caption := operContext+'坏卡成功  '+tipinfo;
    end
    else
    begin
      getReturn(operContext+'坏卡失败  ',WorkView1);
      RzStatusPane1.Caption := operContext+'坏卡失败  '+tipinfo;
    end;
  end;
  try
    btnQuery.Click;
  except
  end;

end;

procedure TfaqhCardBad.btnEditClick(Sender: TObject);
var
  ssType:string;
begin
  ssType := Copy(cbbBadRea.Text,1,Pos('-',cbbBadRea.Text)-1);
  if (ssType='')or(ssType='-') then
  begin
    Context.GetDialogSystem.ShowMessage('请选择坏卡原因!');
    Exit;
  end;
  recordOper('U','修改登记');

end;

initialization
  TUIStdClassFactory.Create('坏卡登记', TfaqhCardBad);

end.


