unit UABusPosSerialStat;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, UIncrementComboBox;

type
  TfaqhBusPosSerialStat = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label6: TLabel;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    Label1: TLabel;
    edtBDate: TWVEdit;
    Label4: TLabel;
    edtEDate: TWVEdit;
    cbbQDept: TWVComboBox;
    Label5: TLabel;
    cbbQType: TComboBox;
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhBusPosSerialStat: TfaqhBusPosSerialStat;

implementation

uses KsFrameworks,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhBusPosSerialStat.Init;
var
  sDate:string;
begin
  inherited;
  sDate := FormatDateTime('yyyymm',Date);
  edtBDate.Text := sDate;
  edtEDate.Text := sDate;
end;

procedure TfaqhBusPosSerialStat.btnQueryClick(Sender: TObject);
var
  qType:Integer;
begin
  if Trim(edtEDate.Text)<>'' then
    if CheckInputDateFormat(edtEDate.Text+'01')=False then
    begin
      Context.GetDialogSystem.ShowMessage('结束月份输入错误，格式:yyyymmdd');
      edtEDate.SetFocus;
      Exit;
    end;
  if Trim(edtBDate.Text)<>'' then
    if CheckInputDateFormat(edtBDate.Text+'01')=False then
    begin
      Context.GetDialogSystem.ShowMessage('开始月份输入错误，格式:yyyymmdd');
      edtBDate.SetFocus;
      Exit;
    end;
  if (Trim(edtEDate.Text)<>'') and (Trim(edtBDate.Text)<>'') then
    if Trim(edtBDate.Text+'01')>Trim(edtEDate.Text+'01') then
    begin
      Context.GetDialogSystem.ShowMessage('开始月份不能大于结束月份!');
      Exit;
    end;
  try
    qtype := strtoint(Copy(cbbqtype.text,1,Pos('-',cbbqtype.text)-1));
  except
    qtype := 0;
  end;
  WorkView.FieldByName('类别').Data.SetInteger(qType);
  inherited;

end;

initialization
  TUIStdClassFactory.Create('车载机流水统计',TfaqhBusPosSerialStat);

end.