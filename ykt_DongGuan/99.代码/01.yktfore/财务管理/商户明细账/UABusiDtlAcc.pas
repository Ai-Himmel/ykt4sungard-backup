unit UABusiDtlAcc;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzPanel, RzSplit, ComCtrls, RzTreeVw, Buttons,
  UReportMachineTemp, RM_Common, RM_Class, RM_e_main, RM_e_Xls,
  RM_Designer, RM_Dataset, ImgList, RM_Preview, RzButton,
  ZAbstractRODataset, ZAbstractDataset, ZAbstractTable, ZDataset,
  RM_e_Jpeg, RM_e_Graphic, RM_e_bmp, RM_e_htm, UTreeRptTemp,contnrs,
  UIncrementComboBox, RzListVw, RzRadGrp;
{
type
  PMyRec = ^TMyRec;
  TMyRec = record
    id: Integer;
    name: string;
end;
type
  TTreeNodeInfoData = class
  private
    FMetaNode: TKSMetaNode;

  protected

  public
    constructor Create(AMetaNode: TKSMetaNode);
    function    GetCaption : string;
    function    GetID : string;
    property    MetaNode: TKSMetaNode read FMetaNode;
  end;
}
type
  TfaqhBusiDtlAcc = class(TfaTreeRptTemp)
    Panel1: TPanel;
    edtBeginDate: TWVEdit;
    Label1: TLabel;
    edtEndDate: TWVEdit;
    pnl1: TPanel;
    ztbl1: TZTable;
    WorkView4: TWorkView;
    QueryRequest: TWVRequest;
    Panel2: TPanel;
    Label9: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    WVEdit3: TWVEdit;
    WVEdit1: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit6: TWVEdit;
    btnBusiQ: TBitBtn;
    lvBusi: TRzListView;
    rgQType: TRzRadioGroup;
    procedure btnQueryClick(Sender: TObject);
    procedure btnBusiQClick(Sender: TObject);
    procedure lvBusiClick(Sender: TObject);
    procedure rgQTypeClick(Sender: TObject);
  private

    { Private declarations }
    endSign:Boolean;
    strBDate,strEDate:string;
    custId:string;
    custName:string;
    {
    FList: TObjectList;
    //刷新商户树
    procedure RefreshCurrentTree();
    procedure getLeval;
    procedure   BuildTree();
    procedure   InternalBuildTree(AInfo: TUIInfo; Parent: TTreeNode);
    }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhBusiDtlAcc: TfaqhBusiDtlAcc;

implementation

uses KsFrameworks,KSClientConsts,SmartCardCommon, UAccRptUnit,KSDataDictionary,UAccountMgrImp;
     
{$R *.DFM}

procedure TfaqhBusiDtlAcc.Init;
begin
  inherited;
  edtBeginDate.Text := bAccountDate;
  edtEndDate.Text := bAccountDate;
  endSign := True;
end;
procedure TfaqhBusiDtlAcc.btnQueryClick(Sender: TObject);
var
  //subId,subName:string;
  tmpData:TDataSet;
  qry:TZQuery;
begin
  if rgQType.ItemIndex=1 then
  begin
    if Trim(edtBeginDate.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('请输入开始日期！');
      edtBeginDate.SetFocus;
      Exit;
    end;
    if Trim(edtEndDate.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('请输入结束日期！');
      edtEndDate.SetFocus;
      Exit;
    end;
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
  end
  else
  begin
    if (Trim(edtBeginDate.Text)='')or(Length(edtBeginDate.Text)<>6) then
    begin
      Context.GetDialogSystem.ShowMessage('请输入年和月份(例:201008)！');
      edtBeginDate.SetFocus;
      Exit;
    end;
    if (Trim(edtEndDate.Text)='')or(Length(edtEndDate.Text)<>6) then
    begin
      Context.GetDialogSystem.ShowMessage('请输入年和月份(例:201008)！');
      edtEndDate.SetFocus;
      Exit;
    end;
    if Trim(edtEndDate.Text)<>'' then
      if CheckInputDateFormat(edtEndDate.Text+'01')=False then
      begin
        Context.GetDialogSystem.ShowMessage('结束月份输入不正确，格式：yyyymm(例：201006)');
        edtEndDate.SetFocus;
        Exit;
      end;
    if Trim(edtBeginDate.Text)<>'' then
      if CheckInputDateFormat(edtBeginDate.Text+'01')=False then
      begin
        Context.GetDialogSystem.ShowMessage('开始月份输入不正确，格式：yyyymm(例：201006)');
        edtBeginDate.SetFocus;
        Exit;
      end;
    if (Trim(edtEndDate.Text)<>'') and (Trim(edtBeginDate.Text)<>'') then
      if Trim(edtBeginDate.Text)>Trim(edtEndDate.Text) then
      begin
        Context.GetDialogSystem.ShowMessage('开始月份不能大于结束日期，请重新输入！');
        edtBeginDate.SetFocus;
        Exit;
      end;
  end;
  if custId='' then
  begin
    Context.GetDialogSystem.ShowMessage('请选择要查询的商户！');
    Exit;
  end;
  strBDate:=edtBeginDate.Text;
  strEDate:=edtEndDate.Text;
  WorkView.FieldByName('商户账号').Data.SetString(custId);
  WorkView.FieldByName('类型').Data.SetString(IntToStr(rgQType.ItemIndex));
  MainRequest.SendCommand;
  strBDate := edtBeginDate.Text;
  strEDate := edtEndDate.Text;

  tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  if tmpData.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('数据统计表没有相关记录，请重新指定条件');
    Exit;
  end;
  if endSign = False then
    Exit;
  endSign := False;
  execSQL(delrpttemp);
  //execSQL(delrptdailyacc);
  qry := nil;
  try
    qry := TZQuery.Create(nil);
    qry.Connection := cmAccountMgrImp.conFB;
    tmpData.First;
    while not tmpData.Eof do
    begin
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add(insertBusiDtlRpt(tmpData));
      qry.ExecSQL;
      tmpData.Next;
    end;
  finally
    qry.Close;
    qry.Destroy;
  end;
  try
    rptReport.LoadFromFile(sPreAppPath+'report\Account\商户明细账.rmf');
    //ztbl1.TableName := 't_rptsysstat';
    if ztbl1.Active=True then
      ztbl1.Active := False;
    ztbl1.Active := True;
    rptReport.Dictionary.Variables.AsString['dateRange'] := '统计日期：'+strBDate+'至'+strEDate;
    rptReport.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
    rptReport.Dictionary.Variables.AsString['rptOper'] := rptOper;
    rptReport.Dictionary.Variables.AsString['busiName'] := custName;
    rptReport.Dictionary.Variables.AsString['checkOper'] := Context.ParamData(svOperatorNameName).AsString;
    rptReport.DoublePass := True;
    rptReport.Preview := rmprvwP;
    rptReport.ShowReport;
  except
    Context.GetDialogSystem.ShowMessage('你没有安装打印机，请先安装(可以是虚拟打印机)！');
  end;
  endSign := True;
end;
procedure TfaqhBusiDtlAcc.btnBusiQClick(Sender: TObject);
var
  tmpItem: TListItem;
  tmpdata:TDataSet;
begin
  WorkView4.FieldByName('操作标志').Data.SetString('R');
  QueryRequest.SendCommand;
  if WorkView4.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView4.FieldByName('返回信息').Data.AsString);
    Exit;
  end;
  lvBusi.Items.Clear;

  tmpdata := TDataSet(WorkView4.FieldByName('查询结果集').Data.AsObject);
  tmpdata.First;
  while not tmpdata.eof do
  begin
    tmpItem := lvBusi.Items.Add;
    //商户编号
    tmpItem.Caption := tmpdata.fieldbyname('lvol0').AsString;
    //商户名称
    tmpItem.SubItems.Add(tmpdata.fieldbyname('snote').AsString);
    //中心商户号
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sname').AsString);
    //省商户编号
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sname2').AsString);
    //商户类型
    tmpItem.SubItems.Add(GetIdObjectName(216,tmpdata.fieldbyname('sbranch_code0').AsString));
    //行业类型
    tmpItem.SubItems.Add(GetIdObjectName(217,tmpdata.fieldbyname('sbranch_code1').AsString));
    tmpdata.Next;
  end;
end;

procedure TfaqhBusiDtlAcc.lvBusiClick(Sender: TObject);
var
  i:Integer;
begin
  try
    i:=lvBusi.Selected.Index;
    custId := lvBusi.Items.Item[i].Caption;
    custName := lvBusi.Items.Item[i].SubItems[0];
    pnl1.Caption := ' 当前选择商户-'+custName;
  except

  end;
end;

procedure TfaqhBusiDtlAcc.rgQTypeClick(Sender: TObject);
begin
  if rgQType.ItemIndex=0 then
  begin
    edtBeginDate.Text := Copy(accountDate,1,6);
    edtEndDate.Text := Copy(accountDate,1,6);
  end
  else
  begin
    edtBeginDate.Text := accountDate;
    edtEndDate.Text := accountDate;
  end;
end;

initialization
  TUIStdClassFactory.Create('商户明细账',TfaqhBusiDtlAcc);

end.