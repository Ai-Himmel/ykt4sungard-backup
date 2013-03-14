unit UAWaterParaQuery;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, UIncrementComboBox;

type
  TfaqhWaterParaQ = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    WVLabel1: TWVLabel;
    WVEdit1: TWVEdit;
    WVLabel2: TWVLabel;
    cbbFeeType: TWVComboBox;
    btnDelete: TBitBtn;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhWaterParaQ: TfaqhWaterParaQ;

implementation

uses KsFrameworks;
     
{$R *.DFM}

procedure TfaqhWaterParaQ.Init;
begin
  inherited;
end;

procedure TfaqhWaterParaQ.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhWaterParaQ.btnQueryClick(Sender: TObject);
begin
  if (cbbFeeType.Text='') or (cbbFeeType.Text='-') then
  begin
    Context.GetDialogSystem.ShowMessage('请选择要查询的费率名称！');
    Exit;
  end;

  WorkView.FieldByName('标志').Data.SetString('R');
  inherited;

end;

procedure TfaqhWaterParaQ.btnDeleteClick(Sender: TObject);
var
  feeNo:Integer;
begin
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('先查询出要删除的费率类别，然后删除！');
    Exit;
  end;
  if Application.MessageBox('你确定要删除选择的费率吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  feeNo := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject).fieldbyname('lcert_code').AsInteger;
  WorkView1.FieldByName('标志').Data.SetString('D');
  WorkView1.FieldByName('费率').Data.SetInteger(feeNo);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('返回码').Data.AsString='0' then
    Context.GetDialogSystem.ShowMessage('删除费率成功！');
end;

initialization
  TUIStdClassFactory.Create('水控设置删除',TfaqhWaterParaQ);

end.