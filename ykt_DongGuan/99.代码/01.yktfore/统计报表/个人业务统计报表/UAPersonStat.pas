unit UAPersonStat;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons,filetrans, ComCtrls,FileCtrl,
  RzListVw, UIncrementComboBox;

type
  TfrmPersonStat = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    edtFilePath: TEdit;
    lvData: TRzListView;
    pbStatues: TProgressBar;
    Label1: TLabel;
    cbbNetInfo: TWVComboBox;
    lbl1: TLabel;
    WVLabel1: TWVLabel;
    edtBeginDate: TWVEdit;
    WVLabel2: TWVLabel;
    edtEndDate: TWVEdit;
    edt1: TWVEdit;
    WVEdit1: TWVEdit;
    Label3: TLabel;
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
  frmPersonStat: TfrmPersonStat;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,data2Excel,SmartCardCommon;
     
{$R *.DFM}

procedure TfrmPersonStat.Init;
begin
  inherited;
  edtBeginDate.Text := Copy(sysDate,1,6);
  edtEndDate.Text := Copy(sysDate,1,6);
end;

procedure TfrmPersonStat.btnPrintClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要导出网点交易统计信息吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;

  if not DirectoryExists(edtFilePath.Text) then
    ForceDirectories(edtFilePath.Text);
  ListViewToXLS(lvData,edtFilePath.Text+'\网点交易统计.xls');
  Context.GetDialogSystem.ShowMessage('导出网点交易统计信息完成！');
end;

procedure TfrmPersonStat.fillList(wv: TWorkView);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  tmpDataSet := TDataSet(wv.FieldByName('查询结果集').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvData.Items.Add;
    //手机通宝卡号
    tmpItem.Caption := tmpdataset.fieldbyname('sall_name').AsString;
    //手机号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sname').AsString);
    //卡号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail').AsString);
    //卡类型
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sname2').AsString);
    //充值次数
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);
    //充值金额
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('damt0').AsString);
    //消费次数
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol1').AsString);
    //消费金额
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('damt1').AsString);
    tmpdataset.Next;
  end;
  LabRecordCount.Caption := '查询到'+inttostr(lvData.Items.Count)+'条记录';
end;

procedure TfrmPersonStat.btnQueryClick(Sender: TObject);
begin
  lvData.Items.Clear;
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
  inherited;
  fillList(WorkView);

end;

initialization
  TUIStdClassFactory.Create('个人业务统计报表',TfrmPersonStat);

end.