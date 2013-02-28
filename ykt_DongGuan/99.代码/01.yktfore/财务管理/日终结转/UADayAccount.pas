unit UADayAccount;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  UReportMachineTemp, RM_e_Xls, RM_e_Jpeg, RM_e_Graphic, RM_e_bmp,
  RM_Common, RM_Class, RM_e_main, RM_e_htm, RM_Designer, RM_Dataset,
  ImgList, RM_Preview, RzPanel, RzButton, ZAbstractRODataset,
  ZAbstractDataset, ZDataset;

type
  TfaqhDayAccount = class(TfaReportMachineTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    edtYear: TWVEdit;
    edtMonth: TWVEdit;
    edtDate: TWVEdit;
    wvVOper: TWorkView;
    wvrVOper: TWVRequest;
    btnCalc: TBitBtn;
    zqry1: TZQuery;
    procedure btnQueryClick(Sender: TObject);
    procedure btnCalcClick(Sender: TObject);
  private

    { Private declarations }
    endSign:Boolean;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhDayAccount: TfaqhDayAccount;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon,
  UAccountMgrImp,UAccRptUnit;
     
{$R *.DFM}

procedure TfaqhDayAccount.Init;
begin
  inherited;
  edtYear.Text := Copy(accountDate,1,4);
  edtMonth.Text := Copy(accountDate,5,2);
  endSign := True;
end;

procedure TfaqhDayAccount.btnQueryClick(Sender: TObject);
var
  tempData:TDataSet;
  qry:TZQuery;
  damt1,damt2,damt3,damt4,damt5,damt6:string;
begin
  if Trim(edtYear.Text)='' then
    edtYear.Text := '0';

  if Trim(edtMonth.Text)='' then
    edtMonth.Text := '0';

  if (Trim(edtYear.Text)<>'') and (Trim(edtYear.Text)<>'0') then
  begin
    try
      if (StrToInt(edtYear.Text)<=1900) or (StrToInt(edtYear.Text)>=2100) then
      begin
        Context.GetDialogSystem.ShowMessage('请输入有效的年份！');
        edtYear.SetFocus;
        Exit;
      end;
    except
      Context.GetDialogSystem.ShowMessage('请输入有效的年份！');
      edtYear.SetFocus;
      Exit;
    end;
  end;
  if (Trim(edtMonth.Text)<>'') and (Trim(edtMonth.Text)<>'0') then
  begin
    try
      if (StrToInt(edtMonth.Text)<=0) or (StrToInt(edtMonth.Text)>12) then
      begin
        Context.GetDialogSystem.ShowMessage('请输入有效的月份！');
        edtMonth.SetFocus;
        Exit;
      end;
    except
      Context.GetDialogSystem.ShowMessage('请输入有效的月份！');
      edtMonth.SetFocus;
      Exit;
    end;
  end;
  WorkView.FieldByName('类型').Data.SetInteger(1);
  inherited;
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('数据统计表没有相关记录，请重新指定条件');
    Exit;
  end;
  tempData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);

  if endSign = false then
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
      rptReport.LoadFromFile(sPreAppPath+'report\Account\汇总统计表.rmf');
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
      rptReport.Dictionary.Variables.AsString['dataRange'] := accountDate;
      rptReport.Dictionary.Variables.AsString['operName'] := Context.ParamData(svOperatorNameName).AsString;
      rptReport.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
      rptReport.DoublePass := True;
      rptReport.Preview := rmprvwP;
      rptReport.ShowReport;
    except
      Context.GetDialogSystem.ShowMessage('你没有安装打印机，请先安装(可以是虚拟打印机)！');
    end;
  finally
    qry.Close;
    qry.Destroy;
  end;
  endSign := True;
end;

procedure TfaqhDayAccount.btnCalcClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要日终结转吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  wvrVOper.SendCommand;
  if wvVOper.FieldByName('返回码').Data.AsString='0' then
    Context.GetDialogSystem.ShowMessage('日终结转成功！');
end;

initialization
  TUIStdClassFactory.Create('日终结转',TfaqhDayAccount);

end.