unit UAPKGOper;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  EditExts, RzPanel, RzSplit;

type
  TfaqhPKGOper = class(TfaqhSimpleQueryTemp)
    RzSizePanel1: TRzSizePanel;
    Panel1: TPanel;
    Label4: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    edtBDate: TWVEdit;
    WVComboBox3: TWVComboBox;
    edtEDate: TWVEdit;
    pnlPKGbtm: TPanel;
    pnl1: TPanel;
    grp1: TGroupBox;
    Label1: TLabel;
    WVComboBox1: TWVComboBox;
    btnPKGQuery: TBitBtn;
    btnUStatus: TBitBtn;
    btnDelPKG: TBitBtn;
    WVRPKGOper: TWVRequest;
    WVPKGOper: TWorkView;
    Panel2: TPanel;
    Label3: TLabel;
    WVComboBox2: TWVComboBox;
    Panel3: TPanel;
    GridFile: TRzDBGrid;
    Panel4: TPanel;
    GroupBox1: TGroupBox;
    Label8: TLabel;
    WVComboBox4: TWVComboBox;
    btnFileU: TBitBtn;
    btnFileDel: TBitBtn;
    btnFileQuery: TBitBtn;
    WVFileQ: TWorkView;
    WVRFileQ: TWVRequest;
    WVDBBinder1: TWVDBBinder;
    DataSource1: TDataSource;
    WVFileOper: TWorkView;
    WVRFileOper: TWVRequest;
    lbl1: TLabel;
    edt1: TWVEdit;
    Label2: TLabel;
    WVEdit1: TWVEdit;
    procedure btnPKGQueryClick(Sender: TObject);
    procedure btnUStatusClick(Sender: TObject);
    procedure btnDelPKGClick(Sender: TObject);
    procedure btnFileQueryClick(Sender: TObject);
    procedure btnFileUClick(Sender: TObject);
    procedure btnFileDelClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure GridDrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhPKGOper: TfaqhPKGOper;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhPKGOper.Init;
begin
  inherited;
  edtBDate.Text := sysDate;
  edtEDate.Text := sysDate;
end;

procedure TfaqhPKGOper.btnPKGQueryClick(Sender: TObject);
begin
  if Trim(edtBDate.Text)<>'' then
    if (CheckInputDateFormat(edtBDate.Text)=False) then
    begin
      Context.GetDialogSystem.ShowMessage('请输入有效的开始日期！');
      Exit;
    end;
  if Trim(edtEDate.Text)<>'' then
    if (CheckInputDateFormat(edtEDate.Text)=False) then
    begin
      Context.GetDialogSystem.ShowMessage('请输入有效的结束日期！');
      Exit;
    end;
  if edtBDate.Text>edteDate.Text then
  begin
    Context.GetDialogSystem.ShowMessage('开始日期不能大于结束日期！');
    Exit;
  end;
  btnUStatus.Enabled := False;
  btnDelPKG.Enabled := False;
  //inherited;
  WorkView.FieldByName('操作标志').Data.SetString('R');
  MainRequest.SendCommand;
  btnUStatus.Enabled := True;
  btnDelPKG.Enabled := True;
end;

procedure TfaqhPKGOper.btnUStatusClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要修改包裹状态吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WVPKGOper.FieldByName('操作标志').Data.SetString('U');
  WVPKGOper.FieldByName('包裹编号').Data.SetString(Grid.DataSource.DataSet.fieldbyname('scust_no').AsString);
  WVRPKGOper.SendCommand;
  Context.GetDialogSystem.ShowMessage('修改包裹状态成功！');
end;

procedure TfaqhPKGOper.btnDelPKGClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要删除该包裹吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WVPKGOper.FieldByName('操作标志').Data.SetString('D');
  WVPKGOper.FieldByName('包裹编号').Data.SetString(Grid.DataSource.DataSet.fieldbyname('scust_no').AsString);
  WVRPKGOper.SendCommand;
  Context.GetDialogSystem.ShowMessage('删除包裹成功！');
end;

procedure TfaqhPKGOper.btnFileQueryClick(Sender: TObject);
var
  pkgId:string;
begin
  btnFileU.Enabled := False;
  btnFileDel.Enabled := False;
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
    pkgId :=''
  else
    pkgId := Grid.DataSource.DataSet.fieldbyname('scust_no').AsString;
  WVFileQ.FieldByName('操作标志').Data.SetString('R');
  WVFileQ.FieldByName('包裹编号').Data.SetString(pkgId);
  WVRFileQ.SendCommand;
  btnFileU.Enabled := True;
  btnFileDel.Enabled := True;

end;

procedure TfaqhPKGOper.btnFileUClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要修改文件状态吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WVFileOper.FieldByName('操作标志').Data.SetString('U');
  WVFileOper.FieldByName('包裹编号').Data.SetInteger(GridFile.DataSource.DataSet.fieldbyname('lvol0').AsInteger);
  WVRFileOper.SendCommand;
  Context.GetDialogSystem.ShowMessage('修改包裹文件状态成功！');
end;

procedure TfaqhPKGOper.btnFileDelClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要删除该文件吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WVFileOper.FieldByName('操作标志').Data.SetString('D');
  WVFileOper.FieldByName('包裹编号').Data.SetInteger(GridFile.DataSource.DataSet.fieldbyname('lvol0').AsInteger);
  WVRFileOper.SendCommand;
  Context.GetDialogSystem.ShowMessage('删除包裹文件成功！');
end;

procedure TfaqhPKGOper.GridCellClick(Column: TColumn);
begin
  btnFileQuery.Click;

end;

procedure TfaqhPKGOper.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

initialization
  TUIStdClassFactory.Create('包裹处理',TfaqhPKGOper);

end.