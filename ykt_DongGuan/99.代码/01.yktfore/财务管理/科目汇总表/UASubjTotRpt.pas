unit UASubjTotRpt;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, Db, WVDBBinders, WVCmdReq, WorkViews, Grids, DBGrids,
  StdCtrls, ImageCtrls, ExtCtrls, UICtrls, WVCtrls, UIncrementComboBox,
  Mask, RzDBGrid, Buttons, UReportMachineTemp, RM_e_Xls, RM_e_Jpeg,
  RM_e_Graphic, RM_e_bmp, RM_Common, RM_Class, RM_e_main, RM_e_htm,
  RM_Designer, RM_Dataset, ImgList, RM_Preview, RzPanel, RzButton, RzRadGrp,
  ZAbstractRODataset, ZAbstractDataset, ZDataset;

type
  TfaQueryAreaTable = class(TfaReportMachineTemp)
    WVLabel4: TWVLabel;
    pnlRptQ: TPanel;
    lbl2: TLabel;
    chkAcc: TCheckBox;
    rgQType: TRzRadioGroup;
    edtBeginDate: TWVEdit;
    edtEndDate: TWVEdit;
    chkShowSub: TCheckBox;
    zqry1: TZQuery;
    Label5: TLabel;
    cbbLeval: TWVComboBox;
    procedure btnQueryClick(Sender: TObject);
    procedure rgQTypeClick(Sender: TObject);
  private
    { Private declarations }
    endSign:Boolean;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faQueryAreaTable: TfaQueryAreaTable;

implementation
uses KSFrameWorks,KSDataDictionary,KSClientConsts,SmartCardCommon,UAccountMgrImp,UAccRptUnit;

{$R *.DFM}
{ TfaQueryAreaTable }

procedure TfaQueryAreaTable.Init;
begin
  inherited;
  edtBeginDate.Text := bAccountDate;
  edtEndDate.Text := bAccountDate;
  endSign := True;
  //cbbLeval.ItemIndex := 0;
  WorkView.FieldByName('��Ŀ����').Data.SetInteger(1);
end;

procedure TfaQueryAreaTable.btnQueryClick(Sender: TObject);
var
  acc,showAcc:Integer;
  qtype:string;
  tempData:TDataSet;
  qry:TZQuery;
  strBDate,strEDate:string;
  damt1,damt2,damt3,damt4,damt5,damt6:string;
begin
  //inherited;
  //tempData := nil;
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
  strBDate:=edtBeginDate.Text;
  strEDate:=edtEndDate.Text;
  qtype := IntToStr(rgQType.ItemIndex);
  if chkAcc.Checked then
    acc := 1
  else
    acc := 0;
  if chkShowSub.Checked then
    showAcc := 1
  else
    showAcc := 0;
  //WorkView.FieldByName('��Ŀ��').Data.SetString(subjNo);
  WorkView.FieldByName('����δ����').Data.SetInteger(acc);
  WorkView.FieldByName('��ʾδ����').Data.SetInteger(showAcc);
  //WorkView.FieldByName('��Ŀ����').Data.SetInteger(0);
  WorkView.FieldByName('��ѯ��ʽ').Data.SetString(qtype);
  inherited;
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('����ͳ�Ʊ�û����ؼ�¼��������ָ������');
    Exit;
  end;
  tempData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);

  if endSign = False then
    Exit;
  endSign := False;
  
  execSQL(delsubjtot);
  qry := nil;
  try
    qry := TZQuery.Create(nil);
    qry.Connection := cmAccountMgrImp.conFB;
    {
    qry.Close;
    qry.SQL.Clear;
    qry.SQL.Add(beginTrans);
    qry.ExecSQL;
    }
    tempData.First;
    while not tempData.Eof do
    begin
      {
      if tempData.fieldbyname('scust_auth').AsString='' then
      begin
        tempData.Next;
        Continue;
      end;
      }     
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add(insertSubjTot(tempData));
      qry.ExecSQL;
      tempData.Next;
    end;
    qry.Close;
    qry.SQL.Clear;
    qry.SQL.Add(calcSubTot);
    qry.Open;
    if not qry.IsEmpty then
    begin
      damt1 := qry.fieldbyname('damt1').AsString;
      damt2 := qry.fieldbyname('damt2').AsString;
      damt3 := qry.fieldbyname('damt3').AsString;
      damt4 := qry.fieldbyname('damt4').AsString;
      damt5 := qry.fieldbyname('damt5').AsString;
      damt6 := qry.fieldbyname('damt6').AsString;
    end;
    try
      rptReport.LoadFromFile(sPreAppPath+'report\Account\��Ŀ���ܱ�.rmf');
      if zqry1.Active=True then
        zqry1.Active := False;
      zqry1.Active := True;
      {
      if cbbSubName.Text='-' then
        rptReport.Dictionary.Variables.AsString['subjectNo'] := ''
      else
        rptReport.Dictionary.Variables.AsString['subjectNo'] := cbbSubName.Text;
      }
      rptReport.Dictionary.Variables.AsString['damt1'] := damt1;
      rptReport.Dictionary.Variables.AsString['damt2'] := damt2;
      rptReport.Dictionary.Variables.AsString['damt3'] := damt3;
      rptReport.Dictionary.Variables.AsString['damt4'] := damt4;
      rptReport.Dictionary.Variables.AsString['damt5'] := damt5;
      rptReport.Dictionary.Variables.AsString['damt6'] := damt6;
      rptReport.Dictionary.Variables.AsString['dateRange'] := strBDate+'��'+strEDate;
      rptReport.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
      rptReport.Dictionary.Variables.AsString['operName'] := Context.ParamData(svOperatorNameName).AsString;
      rptReport.Dictionary.Variables.AsString['rptOper'] := rptOper;
      rptReport.Dictionary.Variables.AsString['checkOper'] := Context.ParamData(svOperatorNameName).AsString;
      rptReport.DoublePass := True;
      rptReport.Preview := rmprvwP;
      rptReport.ShowReport;
    except
      Context.GetDialogSystem.ShowMessage('��û�а�װ��ӡ�������Ȱ�װ(�����������ӡ��)��');
    end;
  finally
    qry.Close;
    qry.Destroy;
  end;
  endSign := True;
end;

procedure TfaQueryAreaTable.rgQTypeClick(Sender: TObject);
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
  TUIStdClassFactory.Create('��Ŀ���ܱ�',TfaQueryAreaTable);

end.
