unit UWorkerNum;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Grids, DBGrids, Db, BDAImpEx, KCDataAccess, StdCtrls, WVDBBinders,
  WVCmdReq, WorkViews, UIncrementComboBox, WVCtrls, Mask,KSFrameWorkUtils,
  ImageCtrls, RzDBGrid,SmartCardCommon, Buttons;

type
  TQueryWorkerNum = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    DataSource2: TDataSource;
    WVDBBinder2: TWVDBBinder;
    WVRequest2: TWVRequest;
    WorkView2: TWorkView;
    btnQuery: TBitBtn;
    WorkerDBGrid: TRzDBGrid;
    procedure FormShow(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure WorkerDBGridDblClick(Sender: TObject);
  private
    { Private declarations }
  public
    //QrWorkerData:TDataSet;
    WorkerInfo:TWorkerRecordList;
    { Public declarations }
  end;

var
  QueryWorkerNum: TQueryWorkerNum;

implementation

{$R *.DFM}

procedure TQueryWorkerNum.FormShow(Sender: TObject);
var
  reDataSet:TDataSet;
begin
  RegisterModule(Self);
  WorkView2.FieldByName('员工号').Data.SetString('');
  WorkView2.FieldByName('员工状态').Data.SetInteger(0);
  WorkView2.FieldByName('员工类别').Data.SetInteger(0);
  WorkView2.FieldByName('姓名').Data.SetString('');
  WorkView2.FieldByName('性别').Data.SetString('');
  WorkView2.FieldByName('政治面貌').Data.SetInteger(0);
  WorkView2.FieldByName('民族').Data.SetInteger(0);
  WorkView2.FieldByName('身份证号').Data.SetString('');
  WorkView2.FieldByName('职称代码').Data.SetInteger(0);
  WorkView2.FieldByName('单位代码').Data.SetString('');
  WorkView2.FieldByName('联系电话').Data.SetString('');
  WorkView2.FieldByName('联系地址').Data.SetString('');
  try
    WVRequest2.SendCommand;

   { reDataSet:=WorkView2.FieldByName('查询结果集').Data.AsObject as TDataSet;
    WorkerInfo.WorkerNo:=reDataSet.FieldByName('sname2').AsString;
    WorkerInfo.WorkerName:=reDataSet.FieldByName('sname').AsString;
    WorkerInfo.WorkerCardId:=reDataSet.FieldByName('scust_auth').AsString;
    WorkerInfo.WorkerUnit:= reDataSet.FieldByName('scust_no').AsString;
    WorkerInfo.WorkerPolicy:=reDataSet.FieldByName('lvol3').AsInteger;
    WorkerInfo.WorkerStatus:=reDataSet.FieldByName('lvol0').AsInteger;
    WorkerInfo.WorkerSex:=reDataSet.FieldByName('smarket_code').AsString;
    WorkerInfo.WorkerKind:=reDataSet.FieldByName('lvol4').AsInteger;
    WorkerInfo.WorkerNation:=reDataSet.FieldByName('lvol2').AsInteger;
    WorkerInfo.WorkerEmpNo:=reDataSet.FieldByName('lvol1').AsInteger;
    WorkerInfo.WorkerAdd:=reDataSet.FieldByName('scusttypes').AsString;
    WorkerInfo.WorkerPhone:=reDataSet.FieldByName('scust_auth2').AsString;

    WorkerDBGrid.Enabled:=True;      }
  except
    WorkerInfo.WorkerNo:='';
    WorkerInfo.WorkerName:='';
    WorkerInfo.WorkerCardId:='';
    WorkerInfo.WorkerUnit:='';
    WorkerInfo.WorkerPolicy:=0;
    WorkerInfo.WorkerStatus:=0;
    WorkerInfo.WorkerSex:='';
    WorkerInfo.WorkerKind:=0;
    WorkerInfo.WorkerNation:=0;
    WorkerInfo.WorkerEmpNo:=0;
    WorkerInfo.WorkerAdd:='';
    WorkerInfo.WorkerPhone:='';
    WorkerInfo.WorkerAdd:='';
    WorkerDBGrid.Enabled:=False;
  end;
end;

procedure TQueryWorkerNum.btnQueryClick(Sender: TObject);
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
  try
    WVRequest2.SendCommand;
    {reDataSet:=WorkView2.FieldByName('查询结果集').Data.AsObject as TDataSet;
    WorkerInfo.WorkerNo:=reDataSet.FieldByName('sname2').AsString;
    WorkerInfo.WorkerName:=reDataSet.FieldByName('sname').AsString;
    WorkerInfo.WorkerCardId:=reDataSet.FieldByName('scust_auth').AsString;
    WorkerInfo.WorkerUnit:= reDataSet.FieldByName('scust_no').AsString;
    WorkerInfo.WorkerPolicy:=reDataSet.FieldByName('lvol3').AsInteger;
    WorkerInfo.WorkerStatus:=reDataSet.FieldByName('lvol0').AsInteger;
    WorkerInfo.WorkerSex:=reDataSet.FieldByName('smarket_code').AsString;
    WorkerInfo.WorkerKind:=reDataSet.FieldByName('lvol4').AsInteger;
    WorkerInfo.WorkerNation:=reDataSet.FieldByName('lvol2').AsInteger;
    WorkerInfo.WorkerEmpNo:=reDataSet.FieldByName('lvol1').AsInteger;
    WorkerInfo.WorkerAdd:=reDataSet.FieldByName('scusttypes').AsString;
    WorkerInfo.WorkerPhone:=reDataSet.FieldByName('scust_auth2').AsString; 
    WorkerDBGrid.Enabled:=True;   }
  except
    WorkerInfo.WorkerNo:='';
    WorkerInfo.WorkerName:='';
    WorkerInfo.WorkerCardId:='';
    WorkerInfo.WorkerUnit:='';
    WorkerInfo.WorkerPolicy:=0;
    WorkerInfo.WorkerStatus:=0;
    WorkerInfo.WorkerSex:='';
    WorkerInfo.WorkerKind:=0;
    WorkerInfo.WorkerNation:=0;
    WorkerInfo.WorkerEmpNo:=0;
    WorkerInfo.WorkerAdd:='';
    WorkerInfo.WorkerPhone:='';
    WorkerInfo.WorkerAdd:='';
    WorkerDBGrid.Enabled:=False;
  end;
end;

procedure TQueryWorkerNum.FormClose(Sender: TObject;
  var Action: TCloseAction);
var
  reDataSet:TDataSet;
begin
  reDataSet:=WorkView2.FieldByName('查询结果集').Data.AsObject as TDataSet;
  if reDataSet.RecordCount>0 then
  begin
    WorkerInfo.WorkerNo:=reDataSet.FieldByName('sname2').AsString;
    WorkerInfo.WorkerName:=reDataSet.FieldByName('sname').AsString;
    WorkerInfo.WorkerCardId:=reDataSet.FieldByName('scust_auth').AsString;
    WorkerInfo.WorkerUnit:= reDataSet.FieldByName('scust_no').AsString;
    WorkerInfo.WorkerPolicy:=reDataSet.FieldByName('lvol3').AsInteger;
    WorkerInfo.WorkerStatus:=reDataSet.FieldByName('lvol0').AsInteger;
    WorkerInfo.WorkerSex:=reDataSet.FieldByName('smarket_code').AsString;
    WorkerInfo.WorkerKind:=reDataSet.FieldByName('lvol4').AsInteger;
    WorkerInfo.WorkerNation:=reDataSet.FieldByName('lvol2').AsInteger;
    WorkerInfo.WorkerEmpNo:=reDataSet.FieldByName('lvol1').AsInteger;
    WorkerInfo.WorkerAdd:=reDataSet.FieldByName('scusttypes').AsString;
    WorkerInfo.WorkerPhone:=reDataSet.FieldByName('scust_auth2').AsString;
  end;
end;

procedure TQueryWorkerNum.WorkerDBGridDblClick(Sender: TObject);
var
  reDataSet:TDataSet;
begin
  reDataSet:=WorkView2.FieldByName('查询结果集').Data.AsObject as TDataSet;
  if reDataSet.RecordCount>0 then
  begin
    WorkerInfo.WorkerNo:=reDataSet.FieldByName('sname2').AsString;
    WorkerInfo.WorkerName:=reDataSet.FieldByName('sname').AsString;
    WorkerInfo.WorkerCardId:=reDataSet.FieldByName('scust_auth').AsString;
    WorkerInfo.WorkerUnit:= reDataSet.FieldByName('scust_no').AsString;
    WorkerInfo.WorkerPolicy:=reDataSet.FieldByName('lvol3').AsInteger;
    WorkerInfo.WorkerStatus:=reDataSet.FieldByName('lvol0').AsInteger;
    WorkerInfo.WorkerSex:=reDataSet.FieldByName('smarket_code').AsString;
    WorkerInfo.WorkerKind:=reDataSet.FieldByName('lvol4').AsInteger;
    WorkerInfo.WorkerNation:=reDataSet.FieldByName('lvol2').AsInteger;
    WorkerInfo.WorkerEmpNo:=reDataSet.FieldByName('lvol1').AsInteger;
    WorkerInfo.WorkerAdd:=reDataSet.FieldByName('scusttypes').AsString;
    WorkerInfo.WorkerPhone:=reDataSet.FieldByName('scust_auth2').AsString;
    Close;
  end;
end;

end.
