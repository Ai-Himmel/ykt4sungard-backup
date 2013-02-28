unit UAExpTradeStat;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons,filetrans, ComCtrls,FileCtrl,
  RzListVw, UIncrementComboBox;

type
  TfaqhExpTradeStat = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    edtFilePath: TEdit;
    lvData: TRzListView;
    pbStatues: TProgressBar;
    Label1: TLabel;
    cbbNetInfo: TWVComboBox;
    lbl1: TLabel;
    cbb1: TWVComboBox;
    WVLabel1: TWVLabel;
    edtBeginDate: TWVEdit;
    WVLabel2: TWVLabel;
    edtEndDate: TWVEdit;
    procedure btnPrintClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
    //endGetPhotoSign:Boolean;
    //procedure getPhoto;
    procedure fillList(wv:TWorkView);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhExpTradeStat: TfaqhExpTradeStat;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,data2Excel,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhExpTradeStat.Init;
begin
  inherited;
  edtBeginDate.Text := sysDate;
  edtEndDate.Text := sysDate;
end;

procedure TfaqhExpTradeStat.btnPrintClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要导出网点交易统计信息吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;

  if not DirectoryExists(edtFilePath.Text) then
    ForceDirectories(edtFilePath.Text);
  ListViewToXLS(lvData,edtFilePath.Text+'\网点交易统计.xls');
  Context.GetDialogSystem.ShowMessage('导出网点交易统计信息完成！');
end;

procedure TfaqhExpTradeStat.fillList(wv: TWorkView);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  tmpDataSet := TDataSet(wv.FieldByName('查询结果集').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvData.Items.Add;
    //统计日期
    tmpItem.Caption := tmpdataset.fieldbyname('sdate0').AsString;
    //所属区域
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_auth2').AsString);
    //渠道编码
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sname').AsString);
    //网点号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sname2').AsString);
    //网点名称
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('vsvarstr2').AsString);
    //交易类型
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail').AsString);
    //交易次数
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);
    //交易金额
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('damt0').AsString);
    tmpdataset.Next;
  end;
  LabRecordCount.Caption := '查询到'+inttostr(lvData.Items.Count)+'条记录';
end;

procedure TfaqhExpTradeStat.btnQueryClick(Sender: TObject);
begin
  lvData.Items.Clear;
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
  inherited;
  fillList(WorkView);

end;

initialization
  TUIStdClassFactory.Create('网点交易统计导出',TfaqhExpTradeStat);

end.