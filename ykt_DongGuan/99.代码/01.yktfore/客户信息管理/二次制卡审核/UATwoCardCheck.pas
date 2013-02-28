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
  if WorkView1.FieldByName('返回码').Data.AsString<>'0' then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView1.fieldbyname('返回信息').Data.AsString);
    Exit;
  end;
  if WorkView1.FieldByName('查询结果集').Data.IsEmpty then
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
  if Application.MessageBox('你确定要审核通过选中的人进行二次制卡吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
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
        WorkView.FieldByName('卡编号').Data.SetInteger(StrToInt(cardId));
        WorkView.FieldByName('批次号').Data.SetString(patchNo);
        WorkView.FieldByName('顺序号').Data.SetInteger(cardNum);
        if cardNum= lvInfo.Items.Count then
          WorkView.FieldByName('结束标志').Data.SetInteger(1)
        else
          WorkView.FieldByName('结束标志').Data.SetInteger(0);
        try
          MainRequest.SendCommand;
          if WorkView.FieldByName('返回码').Data.AsString<>'0' then
          begin
            errList.Add('卡号：'+cardNo+'审核失败，原因-'+WorkView.FieldByName('返回信息').Data.AsString);
            pbStatues.Position := pbStatues.Position + 1;
            Continue;
          end;
        except
          on e:Exception do
          begin
            errList.Add('卡号：'+cardNo+'审核失败，原因-'+e.Message);
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
    stat1.Panels[0].Text := '审核批次号['+patchNo+'],审核总人数['+inttostr(cardNum)+']';
  finally
    if errlist.count>0 then
    begin
      if dlgSave1.Execute then
        errList.SaveToFile(dlgSave1.FileName+'.txt');
    end;
    errList.Destroy;
  end;
  Context.GetDialogSystem.ShowMessage('审核完成！');
end;

procedure TfaqhTwoCardCheck.fillList(wv: TWorkView);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  tmpDataSet := TDataSet(wv.FieldByName('查询结果集').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvInfo.Items.Add;
    //发卡部门
    tmpItem.Caption := GetIdObjectName(210,tmpdataset.fieldbyname('sroom_no2').AsString);
    //卡号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol1').AsString);
    //应用序列号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scard0').AsString);
    //物理编号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_auth').AsString);
    //发卡类型
    tmpItem.SubItems.Add(GetIdObjectName(-1,tmpdataset.fieldbyname('lvol2').AsString));
    //姓名
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sall_name').AsString);
    //首次制卡序列号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sphone').AsString);
    //卡ID
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);
    tmpdataset.Next;
  end;
  LabRecordCount.Caption := '查询到'+inttostr(lvInfo.Items.Count)+'条记录';
end;

procedure TfaqhTwoCardCheck.btnClearClick(Sender: TObject);
var
  i:Integer;
begin
  //ShowMessage(IntToStr(lvInfo.Items.Count));
  if Application.MessageBox('你确定要清空列表信息吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
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
    Context.GetDialogSystem.ShowMessage('读卡查询失败，应用序列号为零或不存在!');
    Exit;
  end;
  edtAppNo.Text:=cardNo;
  inherited;
end;

initialization
  TUIStdClassFactory.Create('二次制卡审核',TfaqhTwoCardCheck);

end.