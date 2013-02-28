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
    //ˢ���̻���
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
      Context.GetDialogSystem.ShowMessage('�����뿪ʼ���ڣ�');
      edtBeginDate.SetFocus;
      Exit;
    end;
    if Trim(edtEndDate.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('������������ڣ�');
      edtEndDate.SetFocus;
      Exit;
    end;
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
  end
  else
  begin
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
    if (Trim(edtEndDate.Text)<>'') and (Trim(edtBeginDate.Text)<>'') then
      if Trim(edtBeginDate.Text)>Trim(edtEndDate.Text) then
      begin
        Context.GetDialogSystem.ShowMessage('��ʼ�·ݲ��ܴ��ڽ������ڣ����������룡');
        edtBeginDate.SetFocus;
        Exit;
      end;
  end;
  if custId='' then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��Ҫ��ѯ���̻���');
    Exit;
  end;
  strBDate:=edtBeginDate.Text;
  strEDate:=edtEndDate.Text;
  WorkView.FieldByName('�̻��˺�').Data.SetString(custId);
  WorkView.FieldByName('����').Data.SetString(IntToStr(rgQType.ItemIndex));
  MainRequest.SendCommand;
  strBDate := edtBeginDate.Text;
  strEDate := edtEndDate.Text;

  tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  if tmpData.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('����ͳ�Ʊ�û����ؼ�¼��������ָ������');
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
    rptReport.LoadFromFile(sPreAppPath+'report\Account\�̻���ϸ��.rmf');
    //ztbl1.TableName := 't_rptsysstat';
    if ztbl1.Active=True then
      ztbl1.Active := False;
    ztbl1.Active := True;
    rptReport.Dictionary.Variables.AsString['dateRange'] := 'ͳ�����ڣ�'+strBDate+'��'+strEDate;
    rptReport.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
    rptReport.Dictionary.Variables.AsString['rptOper'] := rptOper;
    rptReport.Dictionary.Variables.AsString['busiName'] := custName;
    rptReport.Dictionary.Variables.AsString['checkOper'] := Context.ParamData(svOperatorNameName).AsString;
    rptReport.DoublePass := True;
    rptReport.Preview := rmprvwP;
    rptReport.ShowReport;
  except
    Context.GetDialogSystem.ShowMessage('��û�а�װ��ӡ�������Ȱ�װ(�����������ӡ��)��');
  end;
  endSign := True;
end;
procedure TfaqhBusiDtlAcc.btnBusiQClick(Sender: TObject);
var
  tmpItem: TListItem;
  tmpdata:TDataSet;
begin
  WorkView4.FieldByName('������־').Data.SetString('R');
  QueryRequest.SendCommand;
  if WorkView4.FieldByName('������').Data.AsInteger<>0 then
  begin
    Context.GetDialogSystem.ShowMessage(WorkView4.FieldByName('������Ϣ').Data.AsString);
    Exit;
  end;
  lvBusi.Items.Clear;

  tmpdata := TDataSet(WorkView4.FieldByName('��ѯ�����').Data.AsObject);
  tmpdata.First;
  while not tmpdata.eof do
  begin
    tmpItem := lvBusi.Items.Add;
    //�̻����
    tmpItem.Caption := tmpdata.fieldbyname('lvol0').AsString;
    //�̻�����
    tmpItem.SubItems.Add(tmpdata.fieldbyname('snote').AsString);
    //�����̻���
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sname').AsString);
    //ʡ�̻����
    tmpItem.SubItems.Add(tmpdata.fieldbyname('sname2').AsString);
    //�̻�����
    tmpItem.SubItems.Add(GetIdObjectName(216,tmpdata.fieldbyname('sbranch_code0').AsString));
    //��ҵ����
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
    pnl1.Caption := ' ��ǰѡ���̻�-'+custName;
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
  TUIStdClassFactory.Create('�̻���ϸ��',TfaqhBusiDtlAcc);

end.