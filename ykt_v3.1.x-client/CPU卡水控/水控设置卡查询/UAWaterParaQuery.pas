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
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ��ѯ�ķ������ƣ�');
    Exit;
  end;

  WorkView.FieldByName('��־').Data.SetString('R');
  inherited;

end;

procedure TfaqhWaterParaQ.btnDeleteClick(Sender: TObject);
var
  feeNo:Integer;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('�Ȳ�ѯ��Ҫɾ���ķ������Ȼ��ɾ����');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫɾ��ѡ��ķ�����',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  feeNo := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject).fieldbyname('lcert_code').AsInteger;
  WorkView1.FieldByName('��־').Data.SetString('D');
  WorkView1.FieldByName('����').Data.SetInteger(feeNo);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('������').Data.AsString='0' then
    Context.GetDialogSystem.ShowMessage('ɾ�����ʳɹ���');
end;

initialization
  TUIStdClassFactory.Create('ˮ������ɾ��',TfaqhWaterParaQ);

end.