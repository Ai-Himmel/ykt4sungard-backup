unit UAVoucherCheck;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox;

type
  TfaqhVoucherCheck = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    edtYear: TWVEdit;
    edtMonth: TWVEdit;
    edtDate: TWVEdit;
    edtVoucherNo: TWVEdit;
    WVEdit7: TWVEdit;
    cbbVoucherType: TWVComboBox;
    cbbStatus: TWVComboBox;
    cbbManual: TWVComboBox;
    btnCheck: TBitBtn;
    btnCancelCheck: TBitBtn;
    btnEnter: TBitBtn;
    wvVOper: TWorkView;
    wvrVOper: TWVRequest;
    procedure btnQueryClick(Sender: TObject);
    procedure btnCheckClick(Sender: TObject);
    procedure btnCancelCheckClick(Sender: TObject);
    procedure btnEnterClick(Sender: TObject);
  private

    { Private declarations }
    function enterAccount(operSign:string;btn:TBitBtn):Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhVoucherCheck: TfaqhVoucherCheck;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhVoucherCheck.Init;
begin
  inherited;
  //edtDate.Text := sysDate;
  edtYear.Text := Copy(accountDate,1,4);
  edtMonth.Text := Copy(accountDate,5,2);
  cbbStatus.ItemIndex := 0;
  cbbManual.ItemIndex := 0;
end;

procedure TfaqhVoucherCheck.btnQueryClick(Sender: TObject);
begin
  if Trim(edtYear.Text)='' then
    edtYear.Text := '0';

  if Trim(edtMonth.Text)='' then
    edtMonth.Text := '0';

  if Trim(edtVoucherNo.Text)='' then
    edtVoucherNo.Text := '0';
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
  if Trim(edtDate.Text)<>'' then
  begin
    if CheckInputDateFormat(edtDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('请输入正确的日期，格式:yyyymmdd');
      edtDate.SetFocus;
      Exit;
    end;
  end;

  WorkView.FieldByName('标志').Data.SetString('R');
  inherited;

end;

function TfaqhVoucherCheck.enterAccount(operSign: string;btn:TBitBtn): Integer;
var
  tempData:TDataSet;
  id:Integer;
  //sYear,sMonth:Integer;
  //voucherType,voucherNo:Integer;
begin
  if  WorkView.FieldByName('查询结果集').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('请先选择要操作的记录！');
    Result := -1;
    Exit;
  end;

  tempData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  if Application.MessageBox(PChar('你确定要执行'+btn.Caption+'操作吗？'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
  begin
    Result := -4;
    Exit;
  end;
  {
  sYear := tempData.fieldbyname('lvol10').AsInteger;
  sMonth := tempData.fieldbyname('lvol11').AsInteger;
  voucherType := tempData.fieldbyname('lsafe_level').AsInteger;
  voucherNo := tempData.fieldbyname('lserial0').AsInteger;
  }
  id := tempData.fieldbyname('lserial1').AsInteger;
  wvVOper.FieldByName('标志').Data.SetString(operSign);
  wvVOper.FieldByName('会计期间(年)').Data.SetInteger(0);
  wvVOper.FieldByName('会计期间(月)').Data.SetInteger(0);
  wvVOper.FieldByName('凭证类型').Data.SetInteger(0);
  wvVOper.FieldByName('凭证号').Data.SetInteger(0);
  wvVOper.FieldByName('凭证ID').Data.SetInteger(id);
  try
    wvrVOper.SendCommand;
    if wvVOper.FieldByName('返回码').Data.AsString<>'0' then
    begin
      Context.GetDialogSystem.ShowMessage(wvVOper.FieldByName('返回信息').Data.AsString);
      Result := -2;
      Exit;
    end;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage(e.Message);
      Result := -3;
      Exit;
    end;
  end;
  Context.GetDialogSystem.ShowMessage(btn.Caption+'成功！');
  Result := 0;
end;

procedure TfaqhVoucherCheck.btnCheckClick(Sender: TObject);
begin
  enterAccount('K',btnCheck);

end;

procedure TfaqhVoucherCheck.btnCancelCheckClick(Sender: TObject);
begin
  enterAccount('C',btnCancelCheck);

end;

procedure TfaqhVoucherCheck.btnEnterClick(Sender: TObject);
begin
  enterAccount('B',btnEnter);

end;

initialization
  TUIStdClassFactory.Create('凭证审核',TfaqhVoucherCheck);

end.