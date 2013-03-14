unit UATotSubject;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, Buttons, UIncrementComboBox, UReportMachineTemp, RM_Common,
  RM_Class, RM_e_main, RM_e_Xls, RM_Designer, RM_Dataset, ImgList,
  RM_Preview, RzPanel, RzButton, ZAbstractRODataset, ZAbstractDataset,
  ZAbstractTable, ZDataset, RM_e_Jpeg, RM_e_Graphic, RM_e_bmp, RM_e_htm,
  ComCtrls, RzSplit;

type
  TfaqhTotSubject = class(TfaReportMachineTemp)
    Panel1: TPanel;
    cbbSubName: TWVComboBox;
    zqry1: TZQuery;
    Label1: TLabel;
    edtBeginDate: TWVEdit;
    Label2: TLabel;
    edtEndDate: TWVEdit;
    rzszpnl1: TRzSizePanel;
    lvSub: TListView;
    chkSelectall: TCheckBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure chkSelectallClick(Sender: TObject);
  private

    { Private declarations }
    strBDate,strEDate:string;
    procedure addSubList;
    function getSelectSub(lv:TListView):string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhTotSubject: TfaqhTotSubject;

implementation

uses KsFrameworks, KSFrameWorkUtils, 
     KSClientConsts,SmartCardCommon, UCMqhReportImp, UrptTbl;
     
{$R *.DFM}

procedure TfaqhTotSubject.Init;
begin
  inherited;
  edtBeginDate.Text := bAccountDate;
  edtEndDate.Text := bAccountDate;
  addSubList;
end;

procedure TfaqhTotSubject.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;
procedure TfaqhTotSubject.btnQueryClick(Sender: TObject);
var
  tmpData:TDataSet;
  qry:TZQuery;
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

  WorkView.FieldByName('会计科目').Data.SetString(getSelectSub(lvSub));
  inherited;
  strBDate := edtBeginDate.Text;
  strEDate := edtEndDate.Text;
  tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  if tmpData.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('数据统计表没有相关记录，请重新指定条件');
    Exit;
  end;
  if execSQL_SLite(delrptsubjledger)<>0 then
    Exit;
  //execSQL(delrptsubjledger);
  qry := nil;
  try
    qry := TZQuery.Create(nil);
    qry.Connection := dmReportImp.conSLite;
    tmpData.First;
    if execSQL_SLite(beginTrans)<>0 then
      Exit;
    while not tmpData.Eof do
    begin
      {
      if Trim(tmpData.fieldbyname('scust_auth').AsString)='' then
      begin
        tmpData.Next;
        Continue;
      end;
      }
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add(iRptsubjledgerSql(tmpData));
      qry.ExecSQL;
      tmpData.Next;
    end;
    if execSQL_SLite(commitTrans)<>0 then
      Exit;
  finally
    qry.Close;
    qry.Destroy;
  end;
  try
    rptReport.LoadFromFile(sPreAppPath+'report\科目总账表.rmf');
    //ztbl1.TableName := 't_rptsysstat';
    if zqry1.Active=True then
      zqry1.Active := False;
    zqry1.Active := True;
    if cbbSubName.Text='-' then
      rptReport.Dictionary.Variables.AsString['subjectNo'] := ''
    else
      rptReport.Dictionary.Variables.AsString['subjectNo'] := cbbSubName.Text;
    rptReport.Dictionary.Variables.AsString['dateRange'] := '统计日期：'+strBDate+'至'+strEDate;
    rptReport.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
    rptReport.Dictionary.Variables.AsString['rptOper'] := rptOper;
    rptReport.Dictionary.Variables.AsString['checkOper'] := Context.ParamData(svOperatorNameName).AsString;
    rptReport.DoublePass := True;
    rptReport.Preview := rmprvwP;
    rptReport.ShowReport;
  except
    Context.GetDialogSystem.ShowMessage('你没有安装打印机，请先安装(可以是虚拟打印机)！');
  end;
end;

procedure TfaqhTotSubject.addSubList;
var
  tmpItem: TListItem;
  i:Integer;
begin
  lvSub.Items.Clear;
  for i := 1 to cbbSubName.Items.Count-1 do
  begin
    tmpItem := lvSub.Items.Add;
    tmpItem.Caption := Copy(cbbSubName.Items[i],1,Pos('-',cbbSubName.Items[i])-1);
    tmpItem.SubItems.Add(Copy(cbbSubName.Items[i],Pos('-',cbbSubName.Items[i])+1,Length(cbbSubName.Items[i])));
  end;
end;

procedure TfaqhTotSubject.chkSelectallClick(Sender: TObject);
var
  i: integer;
begin
  if lvSub.Items.Count = 0 then
  begin
    Exit;
  end;
  if chkSelectall.Checked = True then
  begin
    for i := 0 to lvSub.Items.Count - 1 do
    begin
      lvSub.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to lvSub.Items.Count - 1 do
    begin
      lvSub.Items[i].Checked := False;
    end;
  end;
end;

function TfaqhTotSubject.getSelectSub(lv: TListView): string;
var
  i:Integer;
  subStr:string;
begin
  for i := 0 to lv.Items.Count-1 do
  begin
    if lv.Items[i].Checked then
    begin
      if subStr ='' then
        subStr := lv.Items[i].Caption
      else
        subStr := subStr + ',' + lv.Items[i].Caption;
    end;
  end;
  Result := subStr;
end;

initialization
  TUIStdClassFactory.Create('科目总账表',TfaqhTotSubject);

end.