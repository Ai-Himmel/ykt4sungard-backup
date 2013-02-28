unit UATwoCardCheck;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  ComCtrls, RzListVw,CardDll;

type
  TfaqhTwoCardCheck = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label4: TLabel;
    cbbDept: TWVComboBox;
    edtBeginDate: TWVEdit;
    Label9: TLabel;
    Label10: TLabel;
    cbbIDType: TWVComboBox;
    Label11: TLabel;
    edtAppNo: TWVEdit;
    QueryRequest: TWVRequest;
    WorkView1: TWorkView;
    btnCheck: TBitBtn;
    chkSelect: TCheckBox;
    lvInfo: TRzListView;
    btnClear: TBitBtn;
    dlgSave1: TSaveDialog;
    stat1: TStatusBar;
    pbStatues: TProgressBar;
    Label6: TLabel;
    WVEdit1: TWVEdit;
    Label1: TLabel;
    edtCardNo: TWVEdit;
    btnReadCardQ: TBitBtn;
    procedure btnQueryClick(Sender: TObject);
    procedure btnCheckClick(Sender: TObject);
    procedure btnClearClick(Sender: TObject);
    procedure chkSelectClick(Sender: TObject);
    procedure btnReadCardQClick(Sender: TObject);
  private

    { Private declarations }
    procedure fillList(wv:TWorkView);
    //function listCheck(cbb:TWVComboBox):Integer;
    //function findIndexLV(inLv:TListView;iId:string): Boolean;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhTwoCardCheck: TfaqhTwoCardCheck;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhTwoCardCheck.Init;
begin
  inherited;
end;

procedure TfaqhTwoCardCheck.btnQueryClick(Sender: TObject);
begin

  lvInfo.Items.Clear;
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text:= '0';
  QueryRequest.SendCommand;
  if WorkView1.FieldByName('������').Data.AsString<>'0' then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView1.fieldbyname('������Ϣ').Data.AsString);
    Exit;
  end;
  if WorkView1.FieldByName('��ѯ�����').Data.IsEmpty then
    btnCheck.Enabled := False
  else
    btnCheck.Enabled := True;
  //inherited;
  fillList(WorkView1);
end;

procedure TfaqhTwoCardCheck.btnCheckClick(Sender: TObject);
var
  i:Integer;
  cardId:string;
  errList:TStringList;
  patchNo:string;
  cardNum:Integer;
  //totMoney:Double;
  cardNo:string;
begin
  if Application.MessageBox('��ȷ��Ҫ���ͨ��ѡ�е��˽��ж����ƿ���',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  errList := nil;
  patchNo := FormatDateTime('yyyymmddhhmmss',Now);
  cardNum := 0;
  //totMoney := 0;
  pbStatues.Max := lvInfo.Items.Count;
  try
    errList := TStringList.Create;
    for i := 0 to lvInfo.Items.Count-1 do
    begin
      inc(cardNum);
      if lvInfo.Items[i].Checked then
      begin
        cardId := lvInfo.Items[i].SubItems[6];
        cardNo := lvInfo.Items[i].SubItems[0];
        WorkView.FieldByName('�����').Data.SetInteger(StrToInt(cardId));
        WorkView.FieldByName('���κ�').Data.SetString(patchNo);
        WorkView.FieldByName('˳���').Data.SetInteger(cardNum);
        if cardNum= lvInfo.Items.Count then
          WorkView.FieldByName('������־').Data.SetInteger(1)
        else
          WorkView.FieldByName('������־').Data.SetInteger(0);
        try
          MainRequest.SendCommand;
          if WorkView.FieldByName('������').Data.AsString<>'0' then
          begin
            errList.Add('���ţ�'+cardNo+'���ʧ�ܣ�ԭ��-'+WorkView.FieldByName('������Ϣ').Data.AsString);
            pbStatues.Position := pbStatues.Position + 1;
            Continue;
          end;
        except
          on e:Exception do
          begin
            errList.Add('���ţ�'+cardNo+'���ʧ�ܣ�ԭ��-'+e.Message);
            pbStatues.Position := pbStatues.Position + 1;
            Continue;
          end;
        end;
        pbStatues.Position := pbStatues.Position + 1;
        //Inc(cardNum);
        //totMoney := totMoney+strtofloat(lvInfo.Items[i].SubItems[4]);
      end;
    end;
    pbStatues.Position := pbStatues.Max;
    stat1.Panels[0].Text := '������κ�['+patchNo+'],���������['+inttostr(cardNum)+']';
  finally
    if errlist.count>0 then
    begin
      if dlgSave1.Execute then
        errList.SaveToFile(dlgSave1.FileName+'.txt');
    end;
    errList.Destroy;
  end;
  Context.GetDialogSystem.ShowMessage('�����ɣ�');
end;

procedure TfaqhTwoCardCheck.fillList(wv: TWorkView);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  tmpDataSet := TDataSet(wv.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvInfo.Items.Add;
    //��������
    tmpItem.Caption := GetIdObjectName(210,tmpdataset.fieldbyname('sroom_no2').AsString);
    //����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol1').AsString);
    //Ӧ�����к�
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scard0').AsString);
    //������
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_auth').AsString);
    //��������
    tmpItem.SubItems.Add(GetIdObjectName(-1,tmpdataset.fieldbyname('lvol2').AsString));
    //����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sall_name').AsString);
    //�״��ƿ����к�
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sphone').AsString);
    //��ID
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);
    tmpdataset.Next;
  end;
  LabRecordCount.Caption := '��ѯ��'+inttostr(lvInfo.Items.Count)+'����¼';
end;

procedure TfaqhTwoCardCheck.btnClearClick(Sender: TObject);
var
  i:Integer;
begin
  //ShowMessage(IntToStr(lvInfo.Items.Count));
  if Application.MessageBox('��ȷ��Ҫ����б���Ϣ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  for i := lvInfo.Items.Count-1 downto 0 do
    lvInfo.Items.Delete(i);
end;

procedure TfaqhTwoCardCheck.chkSelectClick(Sender: TObject);
var
  i:Integer;
begin
  if chkSelect.Checked then
    for i := 0 to lvInfo.Items.Count-1 do
      lvInfo.Items[i].Checked := True
  else
    for i := 0 to lvInfo.Items.Count-1 do
      lvInfo.Items[i].Checked := False;
end;

procedure TfaqhTwoCardCheck.btnReadCardQClick(Sender: TObject);
var
  cardNo:string;
begin
  edtAppNo.Text:='';
  try
    cardNo := readCardOneInfo(CF_APPSERIALNO);
  except
    Exit;
  end;
  if (cardNo='') or (cardNo='0') then
  begin
    Context.GetDialogSystem.ShowMessage('������ѯʧ�ܣ�Ӧ�����к�Ϊ��򲻴���!');
    Exit;
  end;
  edtAppNo.Text:=cardNo;
  inherited;
end;

initialization
  TUIStdClassFactory.Create('�����ƿ����',TfaqhTwoCardCheck);

end.