unit UAVouCheckCancle;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  ComCtrls, RzListVw;

type
  TfaqhCheckCancle = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label9: TLabel;
    edtYear: TWVEdit;
    edtMonth: TWVEdit;
    edtDate: TWVEdit;
    edtVoucherNo: TWVEdit;
    cbbVoucherType: TWVComboBox;
    cbbManual: TWVComboBox;
    btnCheck: TBitBtn;
    btnCancelCheck: TBitBtn;
    btnEnter: TBitBtn;
    wvVOper: TWorkView;
    wvrVOper: TWVRequest;
    lvVoucher: TRzListView;
    chkSelect: TWVCheckBox;
    procedure btnQueryClick(Sender: TObject);
    procedure btnCheckClick(Sender: TObject);
    procedure btnCancelCheckClick(Sender: TObject);
    procedure btnEnterClick(Sender: TObject);
    procedure chkSelectClick(Sender: TObject);
  private

    { Private declarations }
    function enterAccount(operSign:string;btn:TBitBtn):Integer;
    function selectSign:Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCheckCancle: TfaqhCheckCancle;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhCheckCancle.Init;
begin
  inherited;
  edtDate.Text := accountDate;
  edtYear.Text := Copy(accountDate,1,4);
  edtMonth.Text := Copy(accountDate,5,2);
  cbbManual.ItemIndex := 0;
end;

procedure TfaqhCheckCancle.btnQueryClick(Sender: TObject);
var
  tempData:TDataSet;
  tmpItem: TListItem;
begin
  lvVoucher.Items.Clear;
  chkSelect.Checked := False;
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

  WorkView.FieldByName('标志').Data.SetString('Q');
  WorkView.FieldByName('查询类型').Data.SetInteger(2);
  inherited;
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
    exit;
  tempData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  tempData.First;
  while not tempData.Eof do
  begin
    try
      tmpItem := lvVoucher.Items.Add;
      //凭证日期
      tmpItem.Caption := tempData.fieldbyname('sorder0').AsString;
      //ID
      tmpItem.SubItems.Add(tempData.fieldbyname('lserial1').AsString);
      //凭证号
      tmpItem.SubItems.Add(tempData.fieldbyname('sphone').AsString);
      //摘要
      tmpItem.SubItems.Add(tempData.fieldbyname('snote').AsString);
      //借方金额
      tmpItem.SubItems.Add(tempData.fieldbyname('damt1').AsString);
      //贷方金额
      tmpItem.SubItems.Add(tempData.fieldbyname('damt2').AsString);
      //审核状态
      tmpItem.SubItems.Add(GetIdObjectName(160,tempData.fieldbyname('lsafe_level2').AsString));
      //入账状态
      tmpItem.SubItems.Add(GetIdObjectName(161,tempData.fieldbyname('lvol5').AsString));
      //手工账标志
      tmpItem.SubItems.Add(GetIdObjectName(162,tempData.fieldbyname('lbank_acc_type2').AsString));
      //制单
      tmpItem.SubItems.Add(GetIdObjectName(-30,tempData.fieldbyname('semp_no').AsString));
      //出纳
      tmpItem.SubItems.Add(GetIdObjectName(-30,tempData.fieldbyname('sclose_emp').AsString));
      //审核
      tmpItem.SubItems.Add(GetIdObjectName(-30,tempData.fieldbyname('scheck_emp').AsString));
      //记账
      tmpItem.SubItems.Add(GetIdObjectName(-30,tempData.fieldbyname('schange_emp').AsString));
    except
    end;
    tempData.Next;
  end;
end;

function TfaqhCheckCancle.enterAccount(operSign: string;btn:TBitBtn): Integer;
var
  i:Integer;
  Id:Integer;
begin
  if selectSign<0 then
  begin
    Context.GetDialogSystem.ShowMessage('请选择要操作的记录！');
    Exit;
  end;
  if Application.MessageBox(PChar('你确定要执行'+btn.Caption+'操作吗？'),PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
  begin
    Result := -4;
    Exit;
  end;
  for i:=0 to lvVoucher.Items.Count-1 do
  begin
    if lvVoucher.Items[i].Checked then
    begin
      id:=StrToInt(lvVoucher.Items[i].SubItems[0]);      
      wvVOper.FieldByName('标志').Data.SetString(operSign);
      wvVOper.FieldByName('会计期间(年)').Data.SetInteger(0);
      wvVOper.FieldByName('会计期间(月)').Data.SetInteger(0);
      wvVOper.FieldByName('凭证类型').Data.SetInteger(0);
      wvVOper.FieldByName('凭证号').Data.SetInteger(0);
      wvVOper.FieldByName('凭证ID').Data.SetInteger(Id);
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
    end;
  end;
  Result := 0;
end;

procedure TfaqhCheckCancle.btnCheckClick(Sender: TObject);
begin
  if selectSign<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('先选择要批量处理的记录!');
    Exit;
  end;
  if enterAccount('K',btnCheck)<>0 then
    Exit;
  Context.GetDialogSystem.ShowMessage('批量审核凭证成功！');
end;

procedure TfaqhCheckCancle.btnCancelCheckClick(Sender: TObject);
begin
  if enterAccount('C',btnCancelCheck)<>0 then
    Exit;
  Context.GetDialogSystem.ShowMessage('批量取消审核成功！');

end;

procedure TfaqhCheckCancle.btnEnterClick(Sender: TObject);
begin
  if enterAccount('B',btnEnter)<>0 then
    Exit;
  Context.GetDialogSystem.ShowMessage('批量凭证入账成功！');

end;

procedure TfaqhCheckCancle.chkSelectClick(Sender: TObject);
var
  i: integer;
begin
  if lvVoucher.Items.Count = 0 then
  begin
    Exit;
  end;
  if chkSelect.Checked = True then
  begin
    for i := 0 to lvVoucher.Items.Count - 1 do
    begin
      lvVoucher.Items[i].Checked := True;
    end;
  end
  else
  begin
    for i := 0 to lvVoucher.Items.Count - 1 do
    begin
      lvVoucher.Items[i].Checked := False;
    end;
  end;
end;

function TfaqhCheckCancle.selectSign: Integer;
var
  i:Integer;
begin
  Result := -1;
  for i := 0 to lvVoucher.Items.Count-1 do
  begin
    if lvVoucher.Items[i].Checked then
    begin
      Result := 0;
      Exit;
    end;
  end;
end;

initialization
  TUIStdClassFactory.Create('凭证审核取消',TfaqhCheckCancle);

end.