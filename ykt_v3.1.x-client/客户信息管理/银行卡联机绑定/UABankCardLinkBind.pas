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
  tmpDataSet := TDataSet(wv.FieldByName('查询结果集').Data.AsObject);
  WriteLog('流水：'+inttostr(tmpDataSet.RecordCount));
  if ((tmpDataSet.IsEmpty)or(tmpDataSet.RecordCount=0))then
  begin
    Context.GetDialogSystem.ShowMessage('没有记录，请重新查询！');
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
  WorkView1.FieldByName('操作标志').Data.SetString('R');
  QueryRequest.SendCommand;
  if (WorkView1.FieldByName('返回码').Data.AsString<>'0') then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView1.FieldByName('返回信息').Data.AsString);
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
    Context.GetDialogSystem.ShowMessage('请先选择要绑定的人员名单！');
    Exit;
  end;
  if Application.MessageBox('你确定要绑定选择的银行卡吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  operData('A','添加联机绑定');

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
        WorkView.FieldByName('记录号').Data.SetString(recNo);
        WorkView.FieldByName('操作标志').Data.SetString('B');
        WorkView.FieldByName('类型').Data.SetString(oper);
        try
          MainRequest.SendCommand;
        except
          on e:Exception do
          begin
            errList.Add('学/工号为['+stuempno+']姓名为['+custname+']的银行卡'+tipInfo+'失败,失败原因--'+e.Message);
            Continue;
          end;
        end;
        if WorkView.FieldByName('返回码').Data.AsString <> '0' then
        begin
          errList.Add('学/工号为['+stuempno+']姓名为['+custname+']的银行卡'+tipInfo+'失败,失败原因--'+WorkView.FieldByName('返回信息').Data.AsString);
          Continue;
        end;
        Sleep(100);
      end;
    end;
    //dateStr := FormatDateTime('yyyymmddhhmmss',Now);
    if errList.Count>0 then
    begin
      if Application.MessageBox('该操作有失败记录，你要保存该失败记录吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idyes then
      begin
        if dlgSave1.Execute then
          errList.SaveToFile(dlgSave1.FileName+'_'+tipInfo+'.txt');
        Context.GetDialogSystem.ShowMessage(tipInfo+'操作完成');
      end;
    end
    else
    begin
      Context.GetDialogSystem.ShowMessage(tipInfo+'操作完成!');
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
    Context.GetDialogSystem.ShowMessage('请先选择要解除绑定的人员名单！');
    Exit;
  end;
  if Application.MessageBox('你确定要解除绑定选择的银行卡吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  operData('D','解除绑定');
end;

procedure TfaqhBankCardLinkBind.btnSynoDataClick(Sender: TObject);
begin
  if checkListViewSelect(lv1)=False then
  begin
    Context.GetDialogSystem.ShowMessage('请先选择要同步的人员名单！');
    Exit;
  end;
  if Application.MessageBox('你确定要同步选择的银行卡吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  operData('S','同步');
end;

initialization
  TUIStdClassFactory.Create('银行卡联机绑定', TfaqhBankCardLinkBind);

end.
