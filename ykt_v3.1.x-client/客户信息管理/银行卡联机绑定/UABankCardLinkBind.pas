unit UABankCardLinkBind;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, RzDBGrid, Buttons, FilterCombos,KSChineseSpell,
  ComCtrls, RzListVw;

type
  TfaqhBankCardLinkBind = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    btnBinding: TBitBtn;
    Label6: TLabel;
    WVEdit6: TWVEdit;
    WVEdit13: TWVEdit;
    Label13: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    WVEdit9: TWVEdit;
    cbbQFeeType: TWVComboBox;
    Label3: TLabel;
    WVEdit3: TWVEdit;
    Label7: TLabel;
    edtCustNo: TWVEdit;
    lv1: TRzListView;
    QueryRequest: TWVRequest;
    WorkView1: TWorkView;
    chkSelectAll: TCheckBox;
    btnCloseBinding: TBitBtn;
    btnSynoData: TBitBtn;
    dlgSave1: TSaveDialog;
    procedure btnQueryClick(Sender: TObject);
    procedure chkSelectAllClick(Sender: TObject);
    procedure btnBindingClick(Sender: TObject);
    procedure btnCloseBindingClick(Sender: TObject);
    procedure btnSynoDataClick(Sender: TObject);
  private

    { Private declarations }
    procedure fillList(wv: TWorkView);
    function checkListViewSelect(inLv: TRzListView): Boolean;
    procedure operData(oper:string;tipInfo:string);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhBankCardLinkBind: TfaqhBankCardLinkBind;

implementation

uses KsFrameworks,
  SmartCardCommon,filetrans,KSClientConsts,LogFile,KSDataDictionary;

{$R *.DFM}

procedure TfaqhBankCardLinkBind.Init;
begin
  inherited;
end;

procedure TfaqhBankCardLinkBind.fillList(wv: TWorkView);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  tmpDataSet := TDataSet(wv.FieldByName('��ѯ�����').Data.AsObject);
  WriteLog('��ˮ��'+inttostr(tmpDataSet.RecordCount));
  if ((tmpDataSet.IsEmpty)or(tmpDataSet.RecordCount=0))then
  begin
    Context.GetDialogSystem.ShowMessage('û�м�¼�������²�ѯ��');
    Exit;
  end;
  tmpdataset.First;
  lv1.Items.Clear;
  while not tmpdataset.eof do
  begin
    tmpItem := lv1.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('Sname2').AsString;
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_limit').AsString);
    tmpItem.SubItems.Add(GetIdObjectName(-30,tmpdataset.fieldbyname('Semp_no').AsString));
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol1').AsString);
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('spager').AsString);
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('Sall_name').AsString);
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('Scard0').AsString);
    tmpItem.SubItems.Add(GetIdObjectName(33,tmpdataset.fieldbyname('lbank_acc_type').AsString));
    //tmpItem.SubItems.Add(GetIdObjectName(44,tmpdataset.fieldbyname('Lvol2').AsString));
    tmpItem.SubItems.Add(GetIdObjectName(10,tmpdataset.fieldbyname('lsafe_level2').AsString));
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('ssectypes').AsString);
    tmpdataset.Next;
  end;
end;

procedure TfaqhBankCardLinkBind.btnQueryClick(Sender: TObject);
begin
  if edtCustNo.Text = '' then
    edtCustNo.Text := '0';
  WorkView1.FieldByName('������־').Data.SetString('R');
  QueryRequest.SendCommand;
  if (WorkView1.FieldByName('������').Data.AsString<>'0') then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView1.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  fillList(WorkView1);
end;

procedure TfaqhBankCardLinkBind.chkSelectAllClick(Sender: TObject);
var
  i: integer;
begin
  if lv1.Items.Count = 0 then
  begin
    Exit;
  end;
  if chkSelectAll.Checked = True then
  begin
    for i := 0 to lv1.Items.Count - 1 do
    begin
      lv1.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to lv1.Items.Count - 1 do
    begin
      lv1.Items[i].Checked := False;
    end;
  end;
end;

function TfaqhBankCardLinkBind.checkListViewSelect(inLv: TRzListView): Boolean;
var
  i:Integer;
begin
  Result := False;
  for i :=0  to inLv.Items.Count-1 do
    if inLv.Items[i].Checked = True then
    begin
      Result := True;
      Exit;
    end;
end;

procedure TfaqhBankCardLinkBind.btnBindingClick(Sender: TObject);
begin
  if checkListViewSelect(lv1)=False then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ��Ҫ�󶨵���Ա������');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ��ѡ������п���',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  operData('A','���������');

end;

procedure TfaqhBankCardLinkBind.operData(oper: string;tipInfo:string);
var
  errList:TStrings;
  recNo:string;
  stuempno,custname:string;
  i:Integer;
begin
  errList := nil;
  try
    errList := TStringList.Create;
    for i := 0 to lv1.Items.Count-1 do
    begin
      if lv1.Items[i].Checked then
      begin
        recNo := lv1.Items[i].Caption;
        stuempno := lv1.Items[i].SubItems[3];
        custname := lv1.Items[i].SubItems[4];
        WorkView.FieldByName('��¼��').Data.SetString(recNo);
        WorkView.FieldByName('������־').Data.SetString('B');
        WorkView.FieldByName('����').Data.SetString(oper);
        try
          MainRequest.SendCommand;
        except
          on e:Exception do
          begin
            errList.Add('ѧ/����Ϊ['+stuempno+']����Ϊ['+custname+']�����п�'+tipInfo+'ʧ��,ʧ��ԭ��--'+e.Message);
            Continue;
          end;
        end;
        if WorkView.FieldByName('������').Data.AsString <> '0' then
        begin
          errList.Add('ѧ/����Ϊ['+stuempno+']����Ϊ['+custname+']�����п�'+tipInfo+'ʧ��,ʧ��ԭ��--'+WorkView.FieldByName('������Ϣ').Data.AsString);
          Continue;
        end;
        Sleep(100);
      end;
    end;
    //dateStr := FormatDateTime('yyyymmddhhmmss',Now);
    if errList.Count>0 then
    begin
      if Application.MessageBox('�ò�����ʧ�ܼ�¼����Ҫ�����ʧ�ܼ�¼��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idyes then
      begin
        if dlgSave1.Execute then
          errList.SaveToFile(dlgSave1.FileName+'_'+tipInfo+'.txt');
        Context.GetDialogSystem.ShowMessage(tipInfo+'�������');
      end;
    end
    else
    begin
      Context.GetDialogSystem.ShowMessage(tipInfo+'�������!');
    end;
    //btnQuery.Click;
  finally
    errList.Destroy;
  end;

end;

procedure TfaqhBankCardLinkBind.btnCloseBindingClick(Sender: TObject);
begin
  if checkListViewSelect(lv1)=False then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ��Ҫ����󶨵���Ա������');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ�����ѡ������п���',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  operData('D','�����');
end;

procedure TfaqhBankCardLinkBind.btnSynoDataClick(Sender: TObject);
begin
  if checkListViewSelect(lv1)=False then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ��Ҫͬ������Ա������');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫͬ��ѡ������п���',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  operData('S','ͬ��');
end;

initialization
  TUIStdClassFactory.Create('���п�������', TfaqhBankCardLinkBind);

end.
