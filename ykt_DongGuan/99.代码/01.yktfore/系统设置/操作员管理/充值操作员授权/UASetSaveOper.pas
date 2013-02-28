unit UASetSaveOper;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  WVCtrls, ComCtrls, Mask, WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  EditExts, DB, WVDBBinders, Grids,CardDll,
  USetParamsTemp, UIncrementComboBox, Buttons, RzStatus, RzListVw;


type
  TfaqhSetSaveOper = class(TfaqhInputTemp)
    Panel2: TPanel;
    pnl1: TPanel;
    lv1: TRzListView;
    rgLimit: TRadioGroup;
    WorkView1: TWorkView;
    QueryRequest: TWVRequest;
    lbl1: TLabel;
    lbl2: TLabel;
    edtPwd: TEdit;
    procedure btnCancelClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    private
    { Private declarations }
    function  ifSelectGate():Integer ;
    protected
    { protected declarations }
    procedure Init; override;
  public
    { Public declarations }
  end;

var
  faqhSetSaveOper: TfaqhSetSaveOper;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
{$R *.DFM}

procedure TfaqhSetSaveOper.Init;
begin
  inherited;
end;

procedure TfaqhSetSaveOper.btnCancelClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  WorkView1.FieldByName('�������').data.setstring('R');
  QueryRequest.SendCommand;
  if TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject).IsEmpty then
    Exit;
  tmpDataSet := TDataSet(WorkView1.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  lv1.Items.Clear;
  while not tmpdataset.eof do
  begin
    tmpItem := lv1.Items.Add;
    tmpItem.Caption := GetIdObjectName(108,tmpdataset.fieldbyname('sstatus2').asstring); //����Ա����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_no').AsString);                 //����Ա���
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sname').AsString);                     //����Ա����
    try
      tmpItem.SubItems.Add(GetIdObjectName(2,tmpdataset.fieldbyname('lvol1').AsString));//�Ƿ��г�ֵȨ��
    except

    end;
    tmpdataset.Next;
  end;

end;

function TfaqhSetSaveOper.ifSelectGate: Integer;
var
  i:Integer;
  operi:Integer;
begin
  operi := 0;
  for i:= 0 to lv1.Items.Count-1 do
  begin
    if (lv1.Items[i].Checked) then
    begin
      Inc(operi);
      //Exit;
    end;
  end;
  Result := operi;
end;

procedure TfaqhSetSaveOper.btnOKClick(Sender: TObject);
var
  operStr:string;
  operLimit:Integer;
  i:Integer;

  operCode:string;
  operPwd:string;
begin
  if (ifSelectGate=0) then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ��Ҫ���õĳ�ֵ����Ա!');
    Exit;
  end;
  if trim(edtPwd.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('��������Ȩ����Ա���룡');
    Exit;
  end;
  if (ifSelectGate>20) then
  begin
    Context.GetDialogSystem.ShowMessage('ÿ��ѡ�����Ա�ĸ������ܴ���20,������ѡ��!');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ��ѡ��Ĳ���Ա���óɵ�ǰѡ��ĳ�ֵ״̬��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  if rgLimit.ItemIndex=0 then
    operLimit := 1
  else
    operLimit := 0;
  operCode := context.GetParamValue(svOperatorNoName);
  operPwd := encOperPwd(Trim(operCode),Trim(edtPwd.Text));

  WorkView.FieldByName('����ԱȨ��').Data.SetInteger(operLimit);
  WorkView.FieldByName('����').Data.SetString(operPwd);
  for i := 0 to lv1.Items.Count-1 do
  begin
    if lv1.Items[i].Checked then
    begin
      operStr := operStr+ #39+lv1.Items[i].SubItems[0]+#39+',';
    end;
  end;
  if (Copy(operStr,Length(operStr),1))=',' then
    operStr := Copy(operStr,1, Length(operStr) -1);
  WorkView.FieldByName('����Ա').Data.SetString(operStr);
  MainRequest.SendCommand;
  edtPwd.Text := '';
  if WorkView.FieldByName('������').Data.AsString<>'0' then
    Context.GetDialogSystem.ShowMessage(WorkView.FieldByName('������Ϣ').Data.AsString)
  else
    Context.GetDialogSystem.ShowMessage('���ó�ֵ����Ա״̬�ɹ���');
end;

initialization
  TUIStdClassFactory.Create('��ֵ����Ա��Ȩ',TfaqhSetSaveOper);
end.