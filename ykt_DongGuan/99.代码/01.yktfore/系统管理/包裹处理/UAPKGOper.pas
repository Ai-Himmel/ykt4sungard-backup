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
      Context.GetDialogSystem.ShowMessage('��������Ч�Ŀ�ʼ���ڣ�');
      Exit;
    end;
  if Trim(edtEDate.Text)<>'' then
    if (CheckInputDateFormat(edtEDate.Text)=False) then
    begin
      Context.GetDialogSystem.ShowMessage('��������Ч�Ľ������ڣ�');
      Exit;
    end;
  if edtBDate.Text>edteDate.Text then
  begin
    Context.GetDialogSystem.ShowMessage('��ʼ���ڲ��ܴ��ڽ������ڣ�');
    Exit;
  end;
  btnUStatus.Enabled := False;
  btnDelPKG.Enabled := False;
  //inherited;
  WorkView.FieldByName('������־').Data.SetString('R');
  MainRequest.SendCommand;
  btnUStatus.Enabled := True;
  btnDelPKG.Enabled := True;
end;

procedure TfaqhPKGOper.btnUStatusClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫ�޸İ���״̬��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WVPKGOper.FieldByName('������־').Data.SetString('U');
  WVPKGOper.FieldByName('�������').Data.SetString(Grid.DataSource.DataSet.fieldbyname('scust_no').AsString);
  WVRPKGOper.SendCommand;
  Context.GetDialogSystem.ShowMessage('�޸İ���״̬�ɹ���');
end;

procedure TfaqhPKGOper.btnDelPKGClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫɾ���ð�����',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WVPKGOper.FieldByName('������־').Data.SetString('D');
  WVPKGOper.FieldByName('�������').Data.SetString(Grid.DataSource.DataSet.fieldbyname('scust_no').AsString);
  WVRPKGOper.SendCommand;
  Context.GetDialogSystem.ShowMessage('ɾ�������ɹ���');
end;

procedure TfaqhPKGOper.btnFileQueryClick(Sender: TObject);
var
  pkgId:string;
begin
  btnFileU.Enabled := False;
  btnFileDel.Enabled := False;
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
    pkgId :=''
  else
    pkgId := Grid.DataSource.DataSet.fieldbyname('scust_no').AsString;
  WVFileQ.FieldByName('������־').Data.SetString('R');
  WVFileQ.FieldByName('�������').Data.SetString(pkgId);
  WVRFileQ.SendCommand;
  btnFileU.Enabled := True;
  btnFileDel.Enabled := True;

end;

procedure TfaqhPKGOper.btnFileUClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫ�޸��ļ�״̬��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WVFileOper.FieldByName('������־').Data.SetString('U');
  WVFileOper.FieldByName('�������').Data.SetInteger(GridFile.DataSource.DataSet.fieldbyname('lvol0').AsInteger);
  WVRFileOper.SendCommand;
  Context.GetDialogSystem.ShowMessage('�޸İ����ļ�״̬�ɹ���');
end;

procedure TfaqhPKGOper.btnFileDelClick(Sender: TObject);
begin
  if Application.MessageBox('��ȷ��Ҫɾ�����ļ���',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WVFileOper.FieldByName('������־').Data.SetString('D');
  WVFileOper.FieldByName('�������').Data.SetInteger(GridFile.DataSource.DataSet.fieldbyname('lvol0').AsInteger);
  WVRFileOper.SendCommand;
  Context.GetDialogSystem.ShowMessage('ɾ�������ļ��ɹ���');
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
  TUIStdClassFactory.Create('��������',TfaqhPKGOper);

end.