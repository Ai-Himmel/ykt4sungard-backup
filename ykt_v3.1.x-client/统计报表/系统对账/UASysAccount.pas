unit UASysAccount;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, UIncrementComboBox;

type
  TfaqhSysAccount = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label6: TLabel;
    edtBdate: TWVEdit;
    lblTip: TWVLabel;
    lbl1: TLabel;
    edtAccDate: TEdit;
    lbl2: TLabel;
    btnAcc: TButton;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    Label1: TLabel;
    edtEdate: TWVEdit;
    Label2: TLabel;
    Label3: TLabel;
    cbbQType: TComboBox;
    cbbSysType: TWVComboBox;
    cbbQAcctype: TWVComboBox;
    procedure btnAccClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSysAccount: TfaqhSysAccount;

implementation

uses KsFrameworks,SmartCardCommon,KSClientConsts;
     
{$R *.DFM}

procedure TfaqhSysAccount.Init;
begin
  inherited;
  cbbQAccType.ItemIndex := 0;
  cbbQType.ItemIndex := 0;
  //strDate := FormatDateTime('yyyymmdd',Date);
  edtAccDate.Text := bAccountDate;
  edtBdate.Text := bAccountDate;
  edtEdate.Text := bAccountDate;
  lblTip.Caption := '';
end;

procedure TfaqhSysAccount.btnAccClick(Sender: TObject);
begin
  //
  if CheckInputDateFormat(edtAccDate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('������Ϸ������ڣ���ʽ:yyyymmdd');
    edtAccDate.SetFocus;
    Exit;
  end;
  if cbbSysType.ItemIndex<=0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��������');
    cbbSysType.SetFocus;
    Exit;
  end;
  WorkView.FieldByName('��������').Data.SetString(Trim(edtAccDate.Text));
  //WorkView.FieldByName('��������').Data.SetInteger(cbbAccType.ItemIndex+1);
  MainRequest.SendCommand;
  if WorkView.FieldByName('������').Data.AsInteger=0 then
    Context.GetDialogSystem.ShowMessage('ϵͳ�����ļ���ȡ�ɹ������˽�����Ժ��ѯ��');
end;

procedure TfaqhSysAccount.btnQueryClick(Sender: TObject);
var
  tmpData:TDataSet;
begin
  lblTip.Caption := '';
  if CheckInputDateFormat(edtBdate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('������Ϸ������ڣ���ʽ:yyyymmdd');
    edtBdate.SetFocus;
    Exit;
  end;
  if CheckInputDateFormat(edtEdate.Text)=False then
  begin
    Context.GetDialogSystem.ShowMessage('������Ϸ������ڣ���ʽ:yyyymmdd');
    edtEdate.SetFocus;
    Exit;
  end;
  if cbbQAcctype.ItemIndex<=0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��������');
    cbbQAcctype.SetFocus;
    Exit;
  end;
  //WorkView1.FieldByName('��������').Data.SetInteger(cbbQAccType.ItemIndex+1);
  WorkView1.FieldByName('��ѯ���').Data.SetInteger(cbbQType.ItemIndex);
  WVRequest1.SendCommand;
  try
    if WorkView1.FieldByName('������').Data.AsInteger=0 then
    begin
      tmpData := TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject);
      tmpData.First;
        lblTip.Caption := '���гɹ�������'+tmpData.FieldByName('lvol2').AsString +
        '��һ��ͨ�ɹ�������'+tmpData.FieldByName('lvol3').AsString;
    end;
  except

  end;
end;

initialization
  TUIStdClassFactory.Create('ϵͳ����',TfaqhSysAccount);

end.