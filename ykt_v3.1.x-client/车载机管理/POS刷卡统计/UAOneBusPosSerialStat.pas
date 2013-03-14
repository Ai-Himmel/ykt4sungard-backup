unit UAOneBusPosSerialStat;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, UIncrementComboBox;

type
  TfaqhOneBusPosSerialStat = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    Label1: TLabel;
    edtBDate: TWVEdit;
    Label4: TLabel;
    edtEDate: TWVEdit;
    Label5: TLabel;
    edtBTime: TWVEdit;
    Label7: TLabel;
    edtETime: TWVEdit;
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhOneBusPosSerialStat: TfaqhOneBusPosSerialStat;

implementation

uses KsFrameworks,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhOneBusPosSerialStat.Init;
var
  sDate:string;
begin
  inherited;
  sDate := FormatDateTime('yyyymmdd',Date);
  edtBDate.Text := sDate;
  edtEDate.Text := sDate;
end;

procedure TfaqhOneBusPosSerialStat.btnQueryClick(Sender: TObject);
begin
  if Trim(edtEDate.Text)<>'' then
    if CheckInputDateFormat(edtEDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('结束日期输入错误，格式:yyyymmdd');
      edtEDate.SetFocus;
      Exit;
    end;
  if Trim(edtBDate.Text)<>'' then
    if CheckInputDateFormat(edtBDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('开始日期输入错误，格式:yyyymmdd');
      edtBDate.SetFocus;
      Exit;
    end;
  if (Trim(edtEDate.Text)<>'') and (Trim(edtBDate.Text)<>'') then
    if Trim(edtBDate.Text)>Trim(edtEDate.Text) then
    begin
      Context.GetDialogSystem.ShowMessage('开始日期不能大于结束日期!');
      Exit;
    end;

  if Trim(edtBTime.Text)<>'' then
    if CheckInputTimeFormat(edtBTime.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('开始时间输入错误，格式hhmmss');
      edtBTime.SetFocus;
      Exit;
    end;
  if Trim(edtETime.Text)<>'' then
    if CheckInputTimeFormat(edtETime.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('开始时间输入错误，格式hhmmss');
      edtETime.SetFocus;
      Exit;
    end;
  if (Trim(edtETime.Text)<>'') and (Trim(edtBTime.Text)<>'') then
    if Trim(edtBTime.Text)>Trim(edtETime.Text) then
    begin
      Context.GetDialogSystem.ShowMessage('开始时间不能大于结束时间!');
      Exit;
    end;
  inherited;

end;

initialization
  TUIStdClassFactory.Create('单POS刷卡统计',TfaqhOneBusPosSerialStat);

end.