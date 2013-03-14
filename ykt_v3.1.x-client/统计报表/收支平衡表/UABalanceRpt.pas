unit UABalanceRpt;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ComCtrls, RzTreeVw, RzGrids,
  RzCmboBx, RzPanel, RzSplit, UIncrementComboBox,
  Buttons, UReportMachineTemp, RM_Common, RM_Class, RM_e_main, RM_e_Xls,
  RM_Designer, RM_Dataset, ImgList, RM_Preview, RzButton,
  ZAbstractRODataset, ZAbstractDataset, ZAbstractTable, ZDataset, RM_e_htm,
  RM_e_Graphic, RM_e_Jpeg, RM_e_bmp;
type
  PMyRec = ^TMyRec;
  TMyRec = record
    id: Integer;
    name: string;
end;
type
  TfaqhBalanceRpt = class(TfaReportMachineTemp)
    Panel1: TPanel;
    lblBusiName: TLabel;
    WVLabel1: TWVLabel;
    edtBeginDate: TWVEdit;
    WVLabel2: TWVLabel;
    edtEndDate: TWVEdit;
    ztbl1: TZTable;
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
    strBDate,strEDate:string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhBalanceRpt: TfaqhBalanceRpt;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSClientConsts,SmartCardCommon,
  UCMqhReportImp, UrptTbl;

{$R *.DFM}

procedure TfaqhBalanceRpt.Init;
begin
  inherited;
  edtBeginDate.Text := bAccountDate;
  edtEndDate.Text := bAccountDate;
end;

procedure TfaqhBalanceRpt.btnQueryClick(Sender: TObject);
var
  tmpData:TDataSet;
  qry:TZQuery;
begin
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
      Context.GetDialogSystem.ShowMessage('��ʼ���ڲ��ܴ��ڽ������ڣ�');
  inherited;
  strBDate := edtBeginDate.Text;
  strEDate := edtEndDate.Text;
  
  tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  if tmpData.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('����ͳ�Ʊ�û����ؼ�¼��������ָ������');
    Exit;
  end;
  if execSQL_SLite(delrptsubjbal)<>0 then
    Exit;
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
      if Trim(tmpData.fieldbyname('sdate3').AsString)='' then
      begin
        tmpData.Next;
        Continue;
      end;
      }
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add(irptBalanceSql(tmpData));
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
    rptReport.LoadFromFile(sPreAppPath+'report\��֧ƽ���.rmf');
    ztbl1.TableName := 'T_RPTSUBJBAL';
    if ztbl1.Active=True then
      ztbl1.Active := False;
    ztbl1.Active := True;
    rptReport.Dictionary.Variables.AsString['dateRange'] := 'ͳ�����ڣ�'+strBDate+'��'+strEDate;
    rptReport.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
    rptReport.Dictionary.Variables.AsString['rptOper'] := rptOper;
    rptReport.Dictionary.Variables.AsString['checkOper'] := Context.ParamData(svOperatorNameName).AsString;
    rptReport.DoublePass := True;
    rptReport.Preview := rmprvwP;
    rptReport.ShowReport;
  except
    Context.GetDialogSystem.ShowMessage('��û�а�װ��ӡ�������Ȱ�װ(�����������ӡ��)��');
  end;
end;

initialization
  TUIStdClassFactory.Create('��֧ƽ���',TfaqhBalanceRpt);

end.