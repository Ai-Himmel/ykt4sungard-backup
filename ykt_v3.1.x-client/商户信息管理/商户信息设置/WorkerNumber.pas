unit WorkerNumber;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Grids, DBGrids, Db, BDAImpEx, KCDataAccess, StdCtrls, WVDBBinders,
  WVCmdReq, WorkViews, UIncrementComboBox, WVCtrls, Mask, ExtCtrls, UICtrls;

type
  TQueryWorkerNumber = class(TForm)
    WorkerDBGrid: TDBGrid;
    WorkView2: TWorkView;
    WVRequest2: TWVRequest;
    UIPanel1: TUIPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    Button1: TButton;
    Button2: TButton;
    procedure Button1Click(Sender: TObject);
    procedure WorkerDBGridCellClick(Column: TColumn);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
  public
    WorkerID2:String;
    { Public declarations }
  end;

var
  QueryWorkerNumber: TQueryWorkerNumber;

implementation

{$R *.DFM}

procedure TQueryWorkerNumber.Button1Click(Sender: TObject);
var
  reDataSet:TDataSet;
begin
  WorkView2.FieldByName('Ա����').Data.SetString(WVEdit1.Text);
  WorkView2.FieldByName('Ա��״̬').Data.SetInteger(0);
  WorkView2.FieldByName('Ա�����').Data.SetInteger(0);
  WorkView2.FieldByName('����').Data.SetString(WVEdit2.Text);
  WorkView2.FieldByName('�Ա�').Data.SetString('');
  WorkView2.FieldByName('������ò').Data.SetInteger(0);
  WorkView2.FieldByName('����').Data.SetInteger(0);
  WorkView2.FieldByName('���֤��').Data.SetString(WVEdit3.Text);
  WorkView2.FieldByName('ְ�ƴ���').Data.SetInteger(0);
  WorkView2.FieldByName('��λ����').Data.SetString('');
  WorkView2.FieldByName('��ϵ�绰').Data.SetString('');
  WorkView2.FieldByName('��ϵ��ַ').Data.SetString('');

  WVRequest2.SendCommand;
  reDataSet:=WorkView2.FieldByName('��ѯ�����').Data.AsObject as TDataSet;
  WorkerDBGrid.DataSource.DataSet:=reDataSet;
  WorkerID2:=reDataSet.FieldByName('sname2').AsString;
end;

procedure TQueryWorkerNumber.WorkerDBGridCellClick(Column: TColumn);
begin
  try
    WorkerID2:=WorkerDBGrid.DataSource.DataSet.FieldByName('sname2').asstring;
  finally
  end;
end;

procedure TQueryWorkerNumber.FormClose(Sender: TObject;
  var Action: TCloseAction);
begin
  try
    WorkerID2:=WorkerDBGrid.DataSource.DataSet.FieldByName('sname2').asstring;
  finally
  end;
end;

end.
