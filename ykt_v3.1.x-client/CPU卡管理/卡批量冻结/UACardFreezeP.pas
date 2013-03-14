unit UACardFreezeP;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzButton,RzRadChk, RzStatus, RzPanel, RzEdit, Buttons,
  dxCntner, dxInspct, RzSplit, Menus, UIncrementComboBox, UtCardDll, ADODB,
  ComCtrls, RzListVw;

type
  TfaqhCardFreezeP = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    WVLabel5: TWVLabel;
    WVComboBox6: TWVComboBox;
    WVLabel6: TWVLabel;
    WVComboBox1: TWVComboBox;
    WVLabel2: TWVLabel;
    WVComboBox3: TWVComboBox;
    Label7: TLabel;
    WVEdit8: TWVEdit;
    WVLabel9: TWVLabel;
    WVLabel1: TWVLabel;
    WVComboBox2: TWVComboBox;
    WVLabel8: TWVLabel;
    WVComboBox5: TWVComboBox;
    WVEdit6: TWVEdit;
    Label6: TLabel;
    WVEdit5: TWVEdit;
    Label5: TLabel;
    WVCardFreeze: TWorkView;
    WVRCardFreeze: TWVRequest;
    btnPatchOper: TBitBtn;
    WVEdit4: TWVEdit;
    WVLabel3: TWVLabel;
    WVComboBox4: TWVComboBox;
    chkSelect: TCheckBox;
    lbl1: TLabel;
    edtSheetName: TEdit;
    btnSelectFile: TImageButton;
    btnImportQuery: TImageButton;
    btnClear: TImageButton;
    dlgOpen: TOpenDialog;
    conSource: TADOConnection;
    qrySource: TADOQuery;
    lvCustUnAllot: TRzListView;
    btnExprot: TBitBtn;
    dlgSave1: TSaveDialog;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnPatchOperClick(Sender: TObject);
    procedure chkSelectClick(Sender: TObject);
    procedure btnSelectFileClick(Sender: TObject);
    procedure btnClearClick(Sender: TObject);
    procedure btnImportQueryClick(Sender: TObject);
    procedure btnExprotClick(Sender: TObject);
  private
    { Private declarations }
    sFileName:string;
    errList:TStrings;
    procedure fillList(wv: TWorkView);
    function checkListViewSelect(inLv:TRzListView): Boolean;
    function findIndexLV(inLv:TRzListView;iId:string): Boolean;
    procedure clearListView(inLv:TRzListView);
    procedure iniWV(wv:TWorkView);

  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardFreezeP: TfaqhCardFreezeP;

implementation

uses KsFrameworks,KSDataDictionary,KSClientConsts,DataTypes,data2Excel;

{$R *.DFM}

procedure TfaqhCardFreezeP.Init;
var
  operId : string;
begin
  operId := Context.ParamData(svOperatorNoName).AsString;
  inherited;
end;

procedure TfaqhCardFreezeP.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled := Valid;
end;

procedure TfaqhCardFreezeP.btnQueryClick(Sender: TObject);
begin
  if trim(WVEdit1.Text) = '' then
  begin
    WorkView.FieldByName('客户号').Data.SetInteger(0);
  end;
  WorkView.FieldByName('钱包号').Data.SetInteger(1);
  inherited;
  fillList(WorkView);
end;

procedure TfaqhCardFreezeP.btnPatchOperClick(Sender: TObject);
var
  cardId:Integer;
  custId:string;
  custName:string;
  i:Integer;
  dateStr:string;
  appPath:string;
begin
  if checkListViewSelect(lvCustUnAllot)=False then
  begin
    Context.GetDialogSystem.ShowMessage('请先选择要冻结的人员名单！');
    Exit;
  end;
  if Application.MessageBox('你确定要批量冻结该批卡吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  appPath := ExtractFilePath(Application.ExeName);
  try
    errList := TStringList.Create;
    for i := 0 to lvCustUnAllot.Items.Count-1 do
    begin
      if lvCustUnAllot.Items[i].Checked then
      begin
        CardID := StrToInt(lvCustUnAllot.Items[i].SubItems[3]);
        custId := lvCustUnAllot.Items[i].SubItems[3];
        custName := lvCustUnAllot.Items[i].SubItems[3];
        WVCardFreeze.FieldByName('卡号').Data.SetInteger(CardID);
        WVCardFreeze.FieldByName('操作标志').Data.SetString('1');
        WVRCardFreeze.SendCommand;
        if WVCardFreeze.FieldByName('返回码').Data.AsInteger <> 0 then
        begin
          //Context.GetDialogSystem.ShowWarning('卡号为'+inttostr(cardId)+'的卡冻结失败！');
          errList.Add('客户号为['+custid+']姓名为['+custname+']的客户冻结卡失败,失败原因--'+WVCardFreeze.FieldByName('返回信息').Data.AsString);
        end;
        Sleep(100);
      end;
    end;
    dateStr := FormatDateTime('yyyymmddhhmmss',Now);
    if errList.Count>0 then
    begin
      errList.SaveToFile(appPath+'\logs\批量冻结卡失败记录'+datestr+'.txt');
      Context.GetDialogSystem.ShowMessage('该批卡冻结完成,冻结失败记录存在--..\bin\logs\批量冻结卡失败记录'+datestr+'.txt文件中');
    end
    else
    begin
      Context.GetDialogSystem.ShowMessage('该批卡冻结成功!');
    end;
    //btnQuery.Click;
  finally
    errList.Destroy;
  end;
end;

procedure TfaqhCardFreezeP.fillList(wv: TWorkView);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  tmpDataSet := TDataSet(wv.FieldByName('查询结果集').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    {
    if findIndexLV(lvCustUnAllot,tmpdataset.fieldbyname('lvol1').AsString)=True then
    begin
      tmpdataset.Next;
      Continue;
    end;
    }
    tmpItem := lvCustUnAllot.Items.Add;
    tmpItem.Caption := GetIdObjectName(-27,tmpdataset.fieldbyname('sbranch_code0').AsString);     //所属区域
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol1').AsString);                               //客户号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('spager').AsString);                              //学工号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sall_name').AsString);                           //姓名
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);                               //卡号
    tmpItem.SubItems.Add(GetIdObjectName(-34,tmpdataset.fieldbyname('lsafe_level2').AsString));   //客户类别
    tmpItem.SubItems.Add(GetIdObjectName(-43,tmpdataset.fieldbyname('lvol5').AsString));          //客户状态
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('vsvarstr0').AsString);                           //部门
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('damt5').AsString);                               //卡余额
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('damt0').AsString);                               //帐户余额
    tmpdataset.Next;
  end;
end;

function TfaqhCardFreezeP.checkListViewSelect(inLv: TRzListView): Boolean;
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

procedure TfaqhCardFreezeP.clearListView(inLv: TRzListView);
var
  i:Integer;
begin
  for i := inLv.Items.Count-1 downto 0 do
    inLv.Items.Delete(i);
end;

function TfaqhCardFreezeP.findIndexLV(inLv: TRzListView;iId: string): Boolean;
var
  i:Integer;
begin
  Result := False;
  for i := 0 to inLv.Items.Count-1 do
  begin
    if inLv.Items[i].Caption = iId then
    begin
      Result := True;
      Exit;
    end;
  end;
end;

procedure TfaqhCardFreezeP.chkSelectClick(Sender: TObject);
var
  i: integer;
begin
  if lvCustUnAllot.Items.Count = 0 then
  begin
    Exit;
  end;
  if chkSelect.Checked = True then
  begin
    for i := 0 to lvCustUnAllot.Items.Count - 1 do
    begin
      lvCustUnAllot.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to lvCustUnAllot.Items.Count - 1 do
    begin
      lvCustUnAllot.Items[i].Checked := False;
    end;
  end;
end;

procedure TfaqhCardFreezeP.btnSelectFileClick(Sender: TObject);
begin
  dlgOpen.Title := '请选择相应的Excel文件';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  try
    if dlgOpen.Execute then
    begin
      sFileName := dlgOpen.FileName;
      RzStatusPane1.Caption := sFileName;
      //btnImportQuery.Enabled := True;
    end;
  except
    Context.GetDialogSystem.ShowMessage('打开Excel文件失败，请检查文件是否存在或处于打开状态！');
  end;
end;

procedure TfaqhCardFreezeP.btnClearClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要清空列表信息吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  clearListView(lvCustUnAllot);
end;

procedure TfaqhCardFreezeP.btnImportQueryClick(Sender: TObject);
var
  sqlstr:string;
  sCustId:string;
begin
  try
    if conSource.Connected=True then
      conSource.Connected:=False;
    conSource.ConnectionString:='Provider=Microsoft.Jet.OLEDB.4.0;Data Source='+
    Trim(sFileName)+';Extended Properties=Excel 8.0;Persist Security Info=False';
    conSource.Connected :=True;
    qrySource.Connection := conSource;

    sqlstr:='select * from ['+Trim(edtSheetName.Text)+'$] where 客户号>'+'0';
    qrySource.Close;
    qrySource.SQL.Clear;
    qrySource.SQL.Add(sqlstr);
    qrySource.Open;
  except
    Context.GetDialogSystem.ShowMessage('打开数据表失败，请检查打开的Excel文件是否正确！');
    Exit;
  end;
  if qrySource.RecordCount<=0 then
  begin
    Context.GetDialogSystem.ShowMessage('没有记录，请检查打开的Excel是否正确！');
    Exit;
  end;
  iniWV(WorkView);
  try
    qrySource.First;
    while not qrySource.Eof do
    begin
      sCustId := qrySource.FieldByName('客户号').AsString;
      //if Trim(sCustId)='####' then
      //  Exit;
      WorkView.FieldByName('钱包号').Data.SetInteger(1);
      WorkView.FieldByName('客户号').Data.SetInteger(StrToInt(sCustId));
      //WorkView.FieldByName('卡号').Data.SetInteger(0);
      try
      MainRequest.SendCommand;

      if WorkView.FieldByName('返回码').Data.AsInteger<>0 then
      begin
        qrySource.Next;
        Continue;
      end;
      except
        on e:Exception do
        begin
          errList.Add('学工号为['+sCustId+']的客户冻结查询失败,失败原因--'+e.Message);
          qrySource.Next;
          Continue;
        end;
      end;
      fillList(WorkView);
      qrySource.Next;
    end;
  finally
    qrySource.Recordset.Close;
    qrySource.Close;
    conSource.Connected:=false;
  end;
end;

procedure TfaqhCardFreezeP.iniWV(wv: TWorkView);
var
  iwv:Integer;
  icomp:Integer;
begin
  //wv := TWorkView(Self.Components[icomp]);
  for iwv := 0 to wv.FieldCount-1 do
  begin
    if (wv.Fields[iwv].DataType = kdtInteger) or (wv.Fields[iwv].DataType = kdtFloat) then
      wv.FieldByName(wv.Fields[iwv].Name).DefaultValue := 0
    else if wv.Fields[iwv].DataType = kdtstring then
      wv.FieldByName(wv.Fields[iwv].Name).DefaultValue := '';
  end;
  wv.Reset;
end;

procedure TfaqhCardFreezeP.btnExprotClick(Sender: TObject);
begin
  if dlgSave1.Execute then
    ListViewToXLS(lvCustUnAllot,dlgSave1.FileName+'.xls');

end;

initialization
  TUIStdClassFactory.Create('卡批量冻结', TfaqhCardFreezeP);

end.


