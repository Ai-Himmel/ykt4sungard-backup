unit UAMakeCardCheck;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  ComCtrls, RzListVw;

type
  TfaqhMakeCardCheck = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label4: TLabel;
    cbbDept: TWVComboBox;
    edtBeginDate: TWVEdit;
    Label9: TLabel;
    Label10: TLabel;
    cbbIDType: TWVComboBox;
    Label11: TLabel;
    edtEndDate: TWVEdit;
    QueryRequest: TWVRequest;
    WorkView1: TWorkView;
    btnCheck: TBitBtn;
    chkSelect: TCheckBox;
    lvInfo: TRzListView;
    btnClear: TBitBtn;
    dlgSave1: TSaveDialog;
    stat1: TStatusBar;
    pbStatues: TProgressBar;
    Label1: TLabel;
    cbbApp: TWVComboBox;
    Label2: TLabel;
    cbbFact: TWVComboBox;
    Label3: TLabel;
    cbbCity: TWVComboBox;
    Label5: TLabel;
    WVComboBox1: TWVComboBox;
    procedure btnQueryClick(Sender: TObject);
    procedure btnCheckClick(Sender: TObject);
    procedure btnClearClick(Sender: TObject);
    procedure chkSelectClick(Sender: TObject);
  private

    { Private declarations }
    procedure fillList(wv:TWorkView);
    function listCheck(cbb:TWVComboBox):Integer;
    //function findIndexLV(inLv:TListView;iId:string): Boolean;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhMakeCardCheck: TfaqhMakeCardCheck;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhMakeCardCheck.Init;
begin
  inherited;
end;

procedure TfaqhMakeCardCheck.btnQueryClick(Sender: TObject);
begin
  if Trim(edtEndDate.Text)<>'' then
    if CheckInputDateFormat(edtEndDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('结束日期输入不正确，格式：yyyymmdd');
      edtEndDate.SetFocus;
      Exit;
    end;
  if Trim(edtBeginDate.Text)<>'' then
    if CheckInputDateFormat(edtBeginDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('开始日期输入不正确，格式：yyyymmdd');
      edtBeginDate.SetFocus;
      Exit;
    end;
  if (Trim(edtEndDate.Text)<>'') and (Trim(edtBeginDate.Text)<>'') then
    if Trim(edtBeginDate.Text)>Trim(edtEndDate.Text) then
    begin
      Context.GetDialogSystem.ShowMessage('开始日期不能大于结束日期，请重新输入！');
      edtBeginDate.SetFocus;
      Exit;
    end;

  lvInfo.Items.Clear;
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

procedure TfaqhMakeCardCheck.btnCheckClick(Sender: TObject);
var
  i:Integer;
  custId:string;
  errList:TStringList;
  patchNo:string;
  cardNum:Integer;
  totMoney:Double;
begin
  if listCheck(cbbFact)<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择厂家编码！');
    Exit;
  end;
  if listCheck(cbbApp)<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择应用类型！');
    Exit;
  end;
  if listCheck(cbbCity)<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择城市编码！');
    Exit;
  end;
  if Application.MessageBox('你确定要审核通过选中的人进行制卡吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  errList := nil;
  patchNo := FormatDateTime('yyyymmddhhmmss',Now);
  cardNum := 0;
  totMoney := 0;
  pbStatues.Max := lvInfo.Items.Count;
  try
    errList := TStringList.Create;
    for i := 0 to lvInfo.Items.Count-1 do
    begin
      if lvInfo.Items[i].Checked then
      begin
        custId := lvInfo.Items[i].SubItems[0];
        WorkView.FieldByName('操作标志').Data.SetString('C');
        WorkView.FieldByName('客户号').Data.SetInteger(StrToInt(custId));
        WorkView.FieldByName('批次号').Data.SetString(patchNo);
        WorkView.FieldByName('卡序列号').Data.SetInteger(StrToInt(lvInfo.Items[i].SubItems[8]));
        try
          MainRequest.SendCommand;
          if WorkView.FieldByName('返回码').Data.AsString<>'0' then
          begin
            errList.Add('客户号：'+custId+'审核失败，原因-'+WorkView.FieldByName('返回信息').Data.AsString);
            pbStatues.Position := pbStatues.Position + 1;
            Continue;
          end;
        except
          on e:Exception do
          begin
            errList.Add('客户号：'+custId+'审核失败，原因-'+e.Message);
            pbStatues.Position := pbStatues.Position + 1;
            Continue;
          end;
        end;
        pbStatues.Position := pbStatues.Position + 1;
        Inc(cardNum);
        totMoney := totMoney+strtofloat(lvInfo.Items[i].SubItems[4]);
      end;
    end;
    pbStatues.Position := pbStatues.Max;
    stat1.Panels[0].Text := '审核批次号['+patchNo+'],审核总人数['+inttostr(cardNum)+'],总金额['+floattostr(totMoney)+']';
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

procedure TfaqhMakeCardCheck.fillList(wv: TWorkView);
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
    //客户号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);
    //卡号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scard0').AsString);
    //应用序列号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sphone3').AsString);
    //发卡类型
    tmpItem.SubItems.Add(GetIdObjectName(-1,tmpdataset.fieldbyname('lvol2').AsString));
    //充值金额
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('damt0').AsString);
    //姓名
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('snote').AsString);
    //证件类型
    tmpItem.SubItems.Add(GetIdObjectName(201,tmpdataset.fieldbyname('sroom_no').AsString));
    //证件号码
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('spager').AsString);
    //卡ID
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol1').AsString);
    tmpdataset.Next;
  end;
  LabRecordCount.Caption := '查询到'+inttostr(lvInfo.Items.Count)+'条记录';
end;

procedure TfaqhMakeCardCheck.btnClearClick(Sender: TObject);
var
  i:Integer;
begin
  //ShowMessage(IntToStr(lvInfo.Items.Count));
  if Application.MessageBox('你确定要清空列表信息吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  for i := lvInfo.Items.Count-1 downto 0 do
    lvInfo.Items.Delete(i);
end;

procedure TfaqhMakeCardCheck.chkSelectClick(Sender: TObject);
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

function TfaqhMakeCardCheck.listCheck(cbb: TWVComboBox): Integer;
var
  str:string;
begin
  str := Copy(cbb.Text,1,Pos('-',cbb.Text)-1);
  if str='' then
    Result := -1
  else
    Result := 0;
end;

initialization
  TUIStdClassFactory.Create('制卡审核',TfaqhMakeCardCheck);

end.