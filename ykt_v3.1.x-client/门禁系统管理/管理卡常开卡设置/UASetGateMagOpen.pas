unit UASetGateMagOpen;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  UIncrementComboBox, ComCtrls, RzDBGrid, Buttons, EditExts, RzPanel,
  RzSplit;

type
  TEquipParaTreeNode = class
  public
    CEquipID: Integer;       {设备标识} //是 设备商户表 与 设备表关联的唯一字段，
    CNodeID: String;        {设备物理ID}
    CNodeCaption: String;   {设备名称}
    CNodeKind: String;     {机型ID}
    CParentNodeID: String;  {父设备物理ID}
    CParentNodeCaption: String;  {父设备名称}
    CNodeKindCaption:String; {机型名称}
    CEquipRegNo : String ;  {三九设备注册号}
 //   CEquipNo: Integer ; {机号}
 //   CEquipState : Integer; {设备状态ID}
 //   CEquipShowId:Integer;{设备所属类型归类}
 //   CNodeImage : Integer;
end;

type
  TfaqhSetGateMgrOpen = class(TfaqhSimpleQueryTemp)
    spnl1: TRzSizePanel;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    pnlDevInfo: TPanel;
    pnl1: TPanel;
    Label6: TLabel;
    Label7: TLabel;
    WVLabel5: TWVLabel;
    WVLabel9: TWVLabel;
    WVLabel8: TWVLabel;
    WVEdit4: TWVEdit;
    WVEdit8: TWVEdit;
    WVComboBox6: TWVComboBox;
    WVEdit5: TWVEdit;
    WVComboBox5: TWVComboBox;
    btnCardQuery: TBitBtn;
    pnlCardInfo: TPanel;
    pnlCardQuery: TPanel;
    Label4: TLabel;
    Label1: TLabel;
    Label2: TLabel;
    Label5: TLabel;
    Label3: TLabel;
    WVComboBox18: TWVComboBox;
    WVEdit1: TWVEdit;
    WVComboBox17: TWVComboBox;
    WVEdit2: TWVEdit;
    WVEdit3: TWVEdit;
    btnDevQuery: TBitBtn;
    lvEqu: TListView;
    lvCard: TListView;
    WVLabel1: TWVLabel;
    cbbUse: TWVComboBox;
    WVLabel2: TWVLabel;
    cbbOperType: TWVComboBox;
    WorkView2: TWorkView;
    WVRequest2: TWVRequest;
    dlgSave1: TSaveDialog;
    chkCustAll: TCheckBox;
    chkDevall: TCheckBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnDevQueryClick(Sender: TObject);
    procedure btnCardQueryClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure chkCustAllClick(Sender: TObject);
    procedure chkDevallClick(Sender: TObject);
  private
    { Private declarations }

    function selectAllotD(lv:TListView):Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetGateMgrOpen: TfaqhSetGateMgrOpen;
  flag:integer;

implementation

uses KsFrameworks,KSDataDictionary,SmartCardCommon;

{$R *.DFM}
procedure TfaqhSetGateMgrOpen.Init;
begin
  inherited;
end;

procedure TfaqhSetGateMgrOpen.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhSetGateMgrOpen.btnDevQueryClick(Sender: TObject);
var
  tmpItem: TListItem;
  tmpdataset:TDataSet;
begin
  MainRequest.SendCommand;
  lvEqu.Items.Clear;
  inherited;
  tmpdataset := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    if tmpdataset.fieldbyname('lvol0').AsInteger=1 then
    begin
      tmpdataset.Next;
      Continue;
    end;
    tmpItem := lvEqu.Items.Add;
    //tmpItem.Caption := tmpdataset.fieldbyname('lvol0').AsString;//
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);//设备编号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sphone3').AsString);//设备物理编号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scert_no').AsString); //设备名称
    tmpItem.SubItems.Add(GetIdObjectName(-31,tmpdataset.fieldbyname('damt6').AsString));//上级设备
    tmpItem.SubItems.Add(GetIdObjectName(47,tmpdataset.fieldbyname('sbank_code').AsString));//设备机型
    tmpItem.SubItems.Add(GetIdObjectName(-32,tmpdataset.fieldbyname('lserial0').AsString));//所属子系统
    tmpdataset.Next;
  end;
end;

procedure TfaqhSetGateMgrOpen.btnCardQueryClick(Sender: TObject);
var
  tmpItem: TListItem;
  tmpdataset:TDataSet;
begin
  WVRequest1.SendCommand;
  lvCard.Items.Clear;
  inherited;
  tmpdataset := TDataSet(WorkView1.FieldByName('查询结果集').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvCard.Items.Add;
    //tmpItem.Caption := tmpdataset.fieldbyname('lvol0').AsString;//
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol1').AsString);//客户号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);//卡号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('spager').AsString); //学工号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sall_name').AsString);//客户名称
    tmpItem.SubItems.Add(GetIdObjectName(-34,tmpdataset.fieldbyname('lsafe_level2').AsString));//客户类别
    tmpItem.SubItems.Add(GetIdObjectName(-56,tmpdataset.fieldbyname('lsafe_level').AsString));//卡类别
    tmpItem.SubItems.Add(GetIdObjectName(17,tmpdataset.fieldbyname('sserial0').AsString));//卡状态
    tmpdataset.Next;
  end;
end;

procedure TfaqhSetGateMgrOpen.btnQueryClick(Sender: TObject);
var
  i,j:Integer;
  cardUse,operType:Integer;
  cardNo,devNo:Integer;
  errList:TStrings;
begin
  if cbbUse.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('请选择卡用途！');
    Exit;
  end;
  if cbbOperType.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('请选择操作类别！');
    Exit;
  end;
  if selectAllotD(lvCard)<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择要分配的卡！');
    Exit;
  end;
  if selectAllotD(lvEqu)<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择要分配的门禁设备！');
    Exit;
  end;
  if Application.MessageBox('你确定要设置选择的卡到门禁设备吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  cardUse := StrToInt(Copy(cbbUse.Text,1,Pos('-',cbbUse.Text)-1));
  operType := StrToInt(Copy(cbbOperType.Text,1,Pos('-',cbbOperType.Text)-1));
  errList := nil;
  try
    errList := TStringList.Create;
    for i:= 0 to lvCard.Items.Count-1 do
    begin
      if lvCard.Items[i].Checked then
      begin
        cardNo := StrToInt(lvCard.Items[i].SubItems[1]);
        //ShowMessage(IntToStr(cardNo));
        for j := 0 to lvEqu.Items.Count-1 do
        begin
          if lvEqu.Items[j].Checked then
          begin
            devNo := StrToInt(lvEqu.Items[j].SubItems[0]);
            //ShowMessage(IntToStr(devNo));
            WorkView2.FieldByName('卡用途').Data.SetInteger(cardUse);
            WorkView2.FieldByName('操作类别').Data.SetInteger(operType);

            WorkView2.FieldByName('卡号').Data.SetInteger(cardNo);
            WorkView2.FieldByName('设备号').Data.SetInteger(devNo);
            WorkView2.FieldByName('操作标志').Data.SetString('U');
            try
              WVRequest2.SendCommand;
            except
              on e:Exception do
              begin
                errList.Add('卡号：['+inttostr(cardNo)+'],设备号:['+inttostr(devNo)+']设置失败，原因:'+e.Message);
              end;
            end;
          end;
        end;
      end;
    end;
    if errList.Count>0 then
      if dlgSave1.Execute then
        errList.SaveToFile(dlgSave1.FileName+'.txt');
    Context.GetDialogSystem.ShowMessage('设置常开管理卡完成！');
  finally
    errList.Destroy;
  end;
end;

function TfaqhSetGateMgrOpen.selectAllotD(lv: TListView): Integer;
var
  i:Integer;
begin
  for i:= 0 to lv.Items.Count-1 do
  begin
    if lv.Items[i].Checked then
    begin
      Result := 0;
      Exit;
    end;
  end;
  Result := -1;
end;

procedure TfaqhSetGateMgrOpen.chkCustAllClick(Sender: TObject);
var
  i:Integer;
begin
  if chkCustAll.Checked = True then
  begin
    for i := 0 to lvCard.Items.Count - 1 do
    begin
      lvCard.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to lvCard.Items.Count - 1 do
    begin
      lvCard.Items[i].Checked := False;
    end;
  end;
end;

procedure TfaqhSetGateMgrOpen.chkDevallClick(Sender: TObject);
var
  i:Integer;
begin
  if chkDevall.Checked = True then
  begin
    for i := 0 to lvEqu.Items.Count - 1 do
    begin
      lvEqu.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to lvEqu.Items.Count - 1 do
    begin
      lvEqu.Items[i].Checked := False;
    end;
  end;
end;

initialization
  TUIStdClassFactory.Create('管理卡常开卡设置',TfaqhSetGateMgrOpen);

end.