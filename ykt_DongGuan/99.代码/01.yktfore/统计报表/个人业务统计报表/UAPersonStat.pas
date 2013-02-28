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
  if Application.MessageBox('��ȷ��Ҫ�������㽻��ͳ����Ϣ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;

  if not DirectoryExists(edtFilePath.Text) then
    ForceDirectories(edtFilePath.Text);
  ListViewToXLS(lvData,edtFilePath.Text+'\���㽻��ͳ��.xls');
  Context.GetDialogSystem.ShowMessage('�������㽻��ͳ����Ϣ��ɣ�');
end;

procedure TfrmPersonStat.fillList(wv: TWorkView);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  tmpDataSet := TDataSet(wv.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvData.Items.Add;
    //�ֻ�ͨ������
    tmpItem.Caption := tmpdataset.fieldbyname('sall_name').AsString;
    //�ֻ���
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sname').AsString);
    //����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail').AsString);
    //������
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sname2').AsString);
    //��ֵ����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);
    //��ֵ���
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('damt0').AsString);
    //���Ѵ���
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol1').AsString);
    //���ѽ��
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('damt1').AsString);
    tmpdataset.Next;
  end;
  LabRecordCount.Caption := '��ѯ��'+inttostr(lvData.Items.Count)+'����¼';
end;

procedure TfrmPersonStat.btnQueryClick(Sender: TObject);
begin
  lvData.Items.Clear;
  if (Trim(edtBeginDate.Text)='')or(Length(edtBeginDate.Text)<>6) then
  begin
    Context.GetDialogSystem.ShowMessage('����������·�(��:201008)��');
    edtBeginDate.SetFocus;
    Exit;
  end;
  if (Trim(edtEndDate.Text)='')or(Length(edtEndDate.Text)<>6) then
  begin
    Context.GetDialogSystem.ShowMessage('����������·�(��:201008)��');
    edtEndDate.SetFocus;
    Exit;
  end;
  if Trim(edtEndDate.Text)<>'' then
    if CheckInputDateFormat(edtEndDate.Text+'01')=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����·����벻��ȷ����ʽ��yyyymm(����201006)');
      edtEndDate.SetFocus;
      Exit;
    end;
  if Trim(edtBeginDate.Text)<>'' then
    if CheckInputDateFormat(edtBeginDate.Text+'01')=False then
    begin
      Context.GetDialogSystem.ShowMessage('��ʼ�·����벻��ȷ����ʽ��yyyymm(����201006)');
      edtBeginDate.SetFocus;
      Exit;
    end;
  inherited;
  fillList(WorkView);

end;

initialization
  TUIStdClassFactory.Create('����ҵ��ͳ�Ʊ���',TfrmPersonStat);

end.