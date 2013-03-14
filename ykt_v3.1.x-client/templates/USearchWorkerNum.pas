unit USearchWorkerNum;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Grids, DBGrids, Db, BDAImpEx, KCDataAccess, StdCtrls, WVDBBinders,
  WVCmdReq, WorkViews, UIncrementComboBox, WVCtrls, Mask;

type
  TQueryWorkerNum = class(TForm)
    WorkerDBGrid: TDBGrid;
    Button1: TButton;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    procedure Button1Click(Sender: TObject);
    procedure WorkerDBGridCellClick(Column: TColumn);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
  public
    QrWorkerData:TDataSet;
    QrWorkerWorkView:TWorkView;
    QrWorkerRequest:TWVRequest;

    WorkerID:String;
    { Public declarations }
  end;

var
  QueryWorkerNum: TQueryWorkerNum;

implementation

{$R *.DFM}

procedure TQueryWorkerNum.Button1Click(Sender: TObject);
var
  reDataSet:TDataSet;
begin
{  faqhSetSubSystemInfo:=TfaqhSetSubSystemInfo.Create(nil);
  faqhSetSubSystemInfo.WorkView2.FieldByName('员工号').Data.SetString(WVEdit1.Text);
  faqhSetSubSystemInfo.WorkView2.FieldByName('员工状态').Data.SetInteger(0);
  faqhSetSubSystemInfo.WorkView2.FieldByName('员工类别').Data.SetInteger(0);
  faqhSetSubSystemInfo.WorkView2.FieldByName('姓名').Data.SetString(WVEdit2.Text);
  faqhSetSubSystemInfo.WorkView2.FieldByName('性别').Data.SetString('');
  faqhSetSubSystemInfo.WorkView2.FieldByName('政治面貌').Data.SetInteger(0);
  faqhSetSubSystemInfo.WorkView2.FieldByName('民族').Data.SetInteger(0);
  faqhSetSubSystemInfo.WorkView2.FieldByName('身份证号').Data.SetString(WVEdit3.Text);
  faqhSetSubSystemInfo.WorkView2.FieldByName('职称代码').Data.SetInteger(0);
  faqhSetSubSystemInfo.WorkView2.FieldByName('单位代码').Data.SetString('');
  faqhSetSubSystemInfo.WorkView2.FieldByName('联系电话').Data.SetString('');
  faqhSetSubSystemInfo.WorkView2.FieldByName('联系地址').Data.SetString('');
  try
    faqhSetSubSystemInfo.WVRequest2.SendCommand;
    reDataSet:=faqhSetSubSystemInfo.WorkView2.FieldByName('查询结果集').Data.AsObject as TDataSet;
    WorkerDBGrid.DataSource.DataSet:=reDataSet;
    WorkerID:=reDataSet.FieldByName('sname2').AsString;
  finally
    faqhSetSubSystemInfo.Free;
  end; }
end;

procedure TQueryWorkerNum.WorkerDBGridCellClick(Column: TColumn);
begin
  try
    WorkerID:=WorkerDBGrid.DataSource.DataSet.FieldByName('sname2').asstring;
  finally
  end;
end;

procedure TQueryWorkerNum.FormClose(Sender: TObject;
  var Action: TCloseAction);
begin
  try
    WorkerID:=WorkerDBGrid.DataSource.DataSet.FieldByName('sname2').asstring;
  finally
  end;
end;

end.
