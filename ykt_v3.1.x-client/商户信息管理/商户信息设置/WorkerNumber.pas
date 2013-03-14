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
  WorkView2.FieldByName('员工号').Data.SetString(WVEdit1.Text);
  WorkView2.FieldByName('员工状态').Data.SetInteger(0);
  WorkView2.FieldByName('员工类别').Data.SetInteger(0);
  WorkView2.FieldByName('姓名').Data.SetString(WVEdit2.Text);
  WorkView2.FieldByName('性别').Data.SetString('');
  WorkView2.FieldByName('政治面貌').Data.SetInteger(0);
  WorkView2.FieldByName('民族').Data.SetInteger(0);
  WorkView2.FieldByName('身份证号').Data.SetString(WVEdit3.Text);
  WorkView2.FieldByName('职称代码').Data.SetInteger(0);
  WorkView2.FieldByName('单位代码').Data.SetString('');
  WorkView2.FieldByName('联系电话').Data.SetString('');
  WorkView2.FieldByName('联系地址').Data.SetString('');

  WVRequest2.SendCommand;
  reDataSet:=WorkView2.FieldByName('查询结果集').Data.AsObject as TDataSet;
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
