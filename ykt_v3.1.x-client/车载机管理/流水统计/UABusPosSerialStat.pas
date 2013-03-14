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
      Context.GetDialogSystem.ShowMessage('�����·�������󣬸�ʽ:yyyymmdd');
      edtEDate.SetFocus;
      Exit;
    end;
  if Trim(edtBDate.Text)<>'' then
    if CheckInputDateFormat(edtBDate.Text+'01')=False then
    begin
      Context.GetDialogSystem.ShowMessage('��ʼ�·�������󣬸�ʽ:yyyymmdd');
      edtBDate.SetFocus;
      Exit;
    end;
  if (Trim(edtEDate.Text)<>'') and (Trim(edtBDate.Text)<>'') then
    if Trim(edtBDate.Text+'01')>Trim(edtEDate.Text+'01') then
    begin
      Context.GetDialogSystem.ShowMessage('��ʼ�·ݲ��ܴ��ڽ����·�!');
      Exit;
    end;
  try
    qtype := strtoint(Copy(cbbqtype.text,1,Pos('-',cbbqtype.text)-1));
  except
    qtype := 0;
  end;
  WorkView.FieldByName('���').Data.SetInteger(qType);
  inherited;

end;

initialization
  TUIStdClassFactory.Create('���ػ���ˮͳ��',TfaqhBusPosSerialStat);

end.