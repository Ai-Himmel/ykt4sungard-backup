unit UAsendSublidyList;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox, RzStatus, Buttons,CardDll;

type
  TfaqhsendSublidyList = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label10: TLabel;
    edtPNo: TWVEdit;
    Label11: TLabel;
    edtInfo: TWVEdit;
    Label12: TLabel;
    cbbFeeType: TWVComboBox;
    Label13: TLabel;
    edtTicketNo: TWVEdit;
    Label14: TLabel;
    edtNum: TWVEdit;
    Label15: TLabel;
    edtMoney: TWVEdit;
    Label16: TLabel;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    cbbFlag: TWVComboBox;
    RzStatusPane1: TRzStatusPane;
    Label4: TLabel;
    WVEdit4: TWVEdit;
    edtCardId: TWVEdit;
    Label7: TLabel;
    Label2: TLabel;
    WVEdit2: TWVEdit;
    edtCustNo: TWVEdit;
    Label5: TLabel;
    Label3: TLabel;
    Label6: TLabel;
    cbbType: TWVComboBox;
    edtPatchNo: TWVEdit;
    Label1: TLabel;
    edtPwd: TWVEdit;
    lbl1: TLabel;
    cbbDept: TWVComboBox;
    Label8: TLabel;
    WVComboBox1: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnPrintClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure cbbFeeTypeChange(Sender: TObject);
  private

    { Private declarations }
    function checkData:Boolean;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsendSublidyList: TfaqhsendSublidyList;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
{$R *.DFM}

procedure TfaqhsendSublidyList.Init;
begin
  inherited;
end;

procedure TfaqhsendSublidyList.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhsendSublidyList.btnPrintClick(Sender: TObject);
var
  operCode:string;
  operPwd:string;
begin
  //inherited;
  operCode := Context.ParamData(svOperatorNoName).AsString;
  if checkData=False then
    Exit;
  //WorkView1.FieldByName('����Ա').Data.SetString(operCode);
  try
    operPwd := encOperPwd(operCode,Trim(edtPwd.Text));
    WorkView1.FieldByName('�����ܽ��').Data.SetFloat(StrToFloat(edtMoney.text));
    WorkView1.FieldByName('����').Data.SetString(operPwd);
  except
    Context.GetDialogSystem.ShowMessage('��������Ч�Ĳ����ܽ�');
    Exit;
  end;
  if Application.MessageBox('���·�����ǰ����ȷ����������Ϣ����ȷ�ԣ���ȷ��Ҫ�·���',PChar(application.Title),MB_YESNO+mb_iconquestion)=idyes then
  begin
    WVRequest1.SendCommand;
    Context.GetDialogSystem.ShowMessage(WorkView1.fieldbyname('������Ϣ').Data.AsString);
    RzStatusPane1.Caption:=WorkView1.fieldbyname('������Ϣ').Data.AsString;
  end;
  edtPwd.Text := '';
  btnQueryClick(Sender);
end;

function TfaqhsendSublidyList.checkData:Boolean;
begin
  Result:=True;
  if Trim(edtPNo.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('�������κŲ���Ϊ�գ�');
    edtPNo.SetFocus;
    Result := False;
    Exit;
  end;
  if Trim(edtInfo.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('ժҪ��Ϣ����Ϊ�գ�');
    edtInfo.SetFocus;
    Result := False;
    Exit;
  end;
  if Trim(edtNum.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('��������������Ϊ�գ�');
    edtNum.SetFocus;
    Result := False;
    Exit;
  end;
  if Trim(edtMoney.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('�����ܽ���Ϊ�գ�');
    edtMoney.SetFocus;
    Result := False;
    Exit;
  end;
  {
  if Trim(edtCardNo.Text)='' then
  begin
    ShowMessage('���������֤�Ų���Ϊ�գ�');
    edtCardNo.SetFocus;
    Result := False;
    Exit;
  end;
  if Trim(edtName.Text)='' then
  begin
    ShowMessage('��������������Ϊ�գ�');
    edtName.SetFocus;
    Result := False;
    Exit;
  end;
  }
  if cbbFeeType.ItemIndex<=0 then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ�񸶿ʽ��');
    cbbFeeType.SetFocus;
    Result := False;
    Exit;
  end;
  {if cbbFlag.ItemIndex<=0 then
  begin
    ShowMessage('��ѡ������־��');
    cbbFlag.SetFocus;
    Result := False;
    Exit;
  end;}
  if (cbbFeeType.ItemIndex<>1) and (trim(edtTicketNo.Text)='')  then
    begin
      Context.GetDialogSystem.ShowMessage('������Ʊ�ݺ��룡');
      edtTicketNo.SetFocus;
      Result := False;
      Exit;
    end;
end;

procedure TfaqhsendSublidyList.btnQueryClick(Sender: TObject);
begin
  if Trim(edtPatchNo.Text)='' then
    edtPatchNo.Text := '0';
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  if Trim(edtCardId.Text)='' then
    edtCardId.Text := '0';
  WorkView.FieldByName('��������').Data.SetString('R');
  inherited;

end;

procedure TfaqhsendSublidyList.cbbFeeTypeChange(Sender: TObject);
begin
  inherited;
  if (cbbFeeType.ItemIndex=0) or (cbbFeeType.ItemIndex=1) then
  begin
    edtTicketNo.Text:='';
    edtTicketNo.Enabled:=False;
  end
  else
  begin
    edtTicketNo.Enabled:=True;
  end;
end;

initialization
  TUIStdClassFactory.Create('������Ϣ�·�',TfaqhsendSublidyList);

end.