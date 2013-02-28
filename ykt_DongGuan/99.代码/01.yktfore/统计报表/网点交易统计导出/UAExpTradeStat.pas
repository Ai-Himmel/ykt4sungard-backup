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
  if Application.MessageBox('��ȷ��Ҫ�������㽻��ͳ����Ϣ��',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;

  if not DirectoryExists(edtFilePath.Text) then
    ForceDirectories(edtFilePath.Text);
  ListViewToXLS(lvData,edtFilePath.Text+'\���㽻��ͳ��.xls');
  Context.GetDialogSystem.ShowMessage('�������㽻��ͳ����Ϣ��ɣ�');
end;

procedure TfaqhExpTradeStat.fillList(wv: TWorkView);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  tmpDataSet := TDataSet(wv.FieldByName('��ѯ�����').Data.AsObject);
  tmpdataset.First;
  while not tmpdataset.eof do
  begin
    tmpItem := lvData.Items.Add;
    //ͳ������
    tmpItem.Caption := tmpdataset.fieldbyname('sdate0').AsString;
    //��������
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_auth2').AsString);
    //��������
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sname').AsString);
    //�����
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('sname2').AsString);
    //��������
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('vsvarstr2').AsString);
    //��������
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail').AsString);
    //���״���
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol0').AsString);
    //���׽��
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('damt0').AsString);
    tmpdataset.Next;
  end;
  LabRecordCount.Caption := '��ѯ��'+inttostr(lvData.Items.Count)+'����¼';
end;

procedure TfaqhExpTradeStat.btnQueryClick(Sender: TObject);
begin
  lvData.Items.Clear;
  if Trim(edtEndDate.Text)<>'' then
    if CheckInputDateFormat(edtEndDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����������벻��ȷ����ʽ��yyyymmdd');
      edtEndDate.SetFocus;
      Exit;
    end;
  if Trim(edtBeginDate.Text)<>'' then
    if CheckInputDateFormat(edtBeginDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('��ʼ�������벻��ȷ����ʽ��yyyymmdd');
      edtBeginDate.SetFocus;
      Exit;
    end;
  if (Trim(edtEndDate.Text)<>'') and (Trim(edtBeginDate.Text)<>'') then
    if Trim(edtBeginDate.Text)>Trim(edtEndDate.Text) then
    begin
      Context.GetDialogSystem.ShowMessage('��ʼ���ڲ��ܴ��ڽ������ڣ����������룡');
      edtBeginDate.SetFocus;
      Exit;
    end;
  inherited;
  fillList(WorkView);

end;

initialization
  TUIStdClassFactory.Create('���㽻��ͳ�Ƶ���',TfaqhExpTradeStat);

end.