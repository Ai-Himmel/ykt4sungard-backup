unit UAAccountRpt;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, Db, WVDBBinders, WVCmdReq, WorkViews, Grids, DBGrids,
  StdCtrls, ImageCtrls, ExtCtrls, UICtrls, WVCtrls, UIncrementComboBox,
  Mask, RzDBGrid, Buttons, UParamsRptTemp, RM_Common, RM_Class, RM_Dataset,
  RM_Designer, ImgList, RM_e_Xls, RM_e_Jpeg, RM_e_Graphic, RM_e_bmp,
  RM_e_main, RM_e_htm, DBActns, ActnList, RM_Preview, RzPanel, RzButton,
  DBCtrls, RzDBNav, RzRadChk, RzTabs, ZAbstractRODataset, ZAbstractDataset,
  ZDataset, RzEdit, ComCtrls, RzRadGrp;

type
  TfaAccountRpt = class(TfaParamsRptTemp)
    WVLabel4: TWVLabel;
    pnlRptQ: TPanel;
    pnlQry: TPanel;
    zqry1: TZQuery;
    cbbStatus: TWVComboBox;
    Label5: TLabel;
    lbl2: TLabel;
    chkAcc: TCheckBox;
    lblAccType: TLabel;
    rgQType: TRzRadioGroup;
    wv850061: TWorkView;
    wvr850061: TWVRequest;
    wvr850062: TWVRequest;
    wv850062: TWorkView;
    wvr850063: TWVRequest;
    wv850063: TWorkView;
    edtBeginDate: TWVEdit;
    edtEndDate: TWVEdit;
    procedure btnChangeClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure GridDblClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure rgQTypeClick(Sender: TObject);
  private
    { Private declarations }
    endSign:Boolean;
    subjNo,subjName,accName:string;
    accType:Integer;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faAccountRpt: TfaAccountRpt;

implementation

uses KSFrameWorks,KSDataDictionary,UAccRptUnit, UAccountMgrImp,KSClientConsts,SmartCardCommon;

{$R *.DFM}
{
850061总分类账查询
850062日记账查询
850063明细分类帐查询
}

procedure TfaAccountRpt.Init;
begin
  inherited;
  subjNo := '';
  lblAccType.Caption := '';
  edtBeginDate.Text := bAccountDate;
  edtEndDate.Text := bAccountDate;
  WorkView.FieldByName('账簿类型').Data.SetString('1');
  endSign := True;
end;

procedure TfaAccountRpt.btnChangeClick(Sender: TObject);
begin
  if subjNo='' then
  begin
    Context.GetDialogSystem.ShowMessage('请先单击选择一条要查看报表的记录！');
    Exit;
  end;
  inherited;
  rptQRpt.Clear;
  rptQRpt.Preview := rmprvwP;
  rptQRpt.ShowReport;
  lblAccType.Caption := accName+'('+subjNo+'-'+subjname+')';
  {
  if accType=2 then
  begin
    rgQType.Visible := True;
    chkAcc.Visible := False;
  end
  else
  begin
    rgQType.Visible := False;
    chkAcc.Visible := True;
  end;
  }
end;

procedure TfaAccountRpt.GridCellClick(Column: TColumn);
var
  tempData:TDataSet;
begin
  //inherited;
  subjNo := '';
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
    Exit;
  tempData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  try
    subjNo := tempData.fieldbyname('scust_auth').AsString;
    accType := tempData.fieldbyname('lvol1').AsInteger;
    subjName := tempData.fieldbyname('scusttypes').AsString;
    accName := tempData.fieldbyname('sall_name').AsString;
  except

  end;
end;

procedure TfaAccountRpt.GridDblClick(Sender: TObject);
begin
  //inherited;
  btnChange.Click;
end;

procedure TfaAccountRpt.btnOKClick(Sender: TObject);
var
  acc:Integer;
  qtype:string;
  tempData:TDataSet;
  qry:TZQuery;
  strBDate,strEDate:string;
  title:string;
begin
  //inherited;
  tempData := nil;
  if rgQType.ItemIndex=1 then
  begin
    if Trim(edtBeginDate.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('请输入开始日期！');
      edtBeginDate.SetFocus;
      Exit;
    end;
    if Trim(edtEndDate.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('请输入结束日期！');
      edtEndDate.SetFocus;
      Exit;
    end;
    if Trim(edtEndDate.Text)<>'' then
      if CheckInputDateFormat(edtEndDate.Text)=False then
      begin
        Context.GetDialogSystem.ShowMessage('结束日期输入不正确，格式：yyyymmdd');
        edtEndDate.SetFocus;
        Exit;
      end;
    if Trim(edtBeginDate.Text)<>'' then
      if CheckInputDateFormat(edtBeginDate.Text)=False then
      begin
        Context.GetDialogSystem.ShowMessage('开始日期输入不正确，格式：yyyymmdd');
        edtBeginDate.SetFocus;
        Exit;
      end;
    if (Trim(edtEndDate.Text)<>'') and (Trim(edtBeginDate.Text)<>'') then
      if Trim(edtBeginDate.Text)>Trim(edtEndDate.Text) then
      begin
        Context.GetDialogSystem.ShowMessage('开始日期不能大于结束日期，请重新输入！');
        edtBeginDate.SetFocus;
        Exit;
      end;
  end
  else
  begin
    if (Trim(edtBeginDate.Text)='')or(Length(edtBeginDate.Text)<>6) then
    begin
      Context.GetDialogSystem.ShowMessage('请输入年和月份(例:201008)！');
      edtBeginDate.SetFocus;
      Exit;
    end;
    if (Trim(edtEndDate.Text)='')or(Length(edtEndDate.Text)<>6) then
    begin
      Context.GetDialogSystem.ShowMessage('请输入年和月份(例:201008)！');
      edtEndDate.SetFocus;
      Exit;
    end;
    if Trim(edtEndDate.Text)<>'' then
      if CheckInputDateFormat(edtEndDate.Text+'01')=False then
      begin
        Context.GetDialogSystem.ShowMessage('结束月份输入不正确，格式：yyyymm(例：201006)');
        edtEndDate.SetFocus;
        Exit;
      end;
    if Trim(edtBeginDate.Text)<>'' then
      if CheckInputDateFormat(edtBeginDate.Text+'01')=False then
      begin
        Context.GetDialogSystem.ShowMessage('开始月份输入不正确，格式：yyyymm(例：201006)');
        edtBeginDate.SetFocus;
        Exit;
      end;
    if (Trim(edtEndDate.Text)<>'') and (Trim(edtBeginDate.Text)<>'') then
      if Trim(edtBeginDate.Text)>Trim(edtEndDate.Text) then
      begin
        Context.GetDialogSystem.ShowMessage('开始月份不能大于结束日期，请重新输入！');
        edtBeginDate.SetFocus;
        Exit;
      end;
  end;
  strBDate:=edtBeginDate.Text;
  strEDate:=edtEndDate.Text;
  qtype := IntToStr(rgQType.ItemIndex);

  title := '';
  if chkAcc.Checked then
    acc := 1
  else
    acc := 0;
  if accType=1 then
  begin
    title := '总分类账查询';
    wv850061.FieldByName('科目号').Data.SetString(subjNo);
    wv850061.FieldByName('开始日期').Data.SetInteger(StrToInt(edtBeginDate.Text));
    wv850061.FieldByName('结束日期').Data.SetInteger(StrToInt(edtEndDate.Text));
    wv850061.FieldByName('包含未入账').Data.SetInteger(acc);
    wvr850061.SendCommand;
    if wv850061.FieldByName('查询结果集').Data.IsEmpty then
    begin
      Context.GetDialogSystem.ShowMessage('数据统计表没有相关记录，请重新指定条件');
      Exit;
    end;
    tempData := Tdataset(wv850061.FieldByName('查询结果集').Data.AsObject);
  end
  else
  if accType=2 then
  begin
    title := '日记账查询';
    wv850062.FieldByName('科目号').Data.SetString(subjNo);
    wv850062.FieldByName('开始日期').Data.SetInteger(StrToInt(edtBeginDate.Text));
    wv850062.FieldByName('结束日期').Data.SetInteger(StrToInt(edtEndDate.Text));
    wv850062.FieldByName('包含未入账').Data.SetInteger(acc);
    wvr850062.SendCommand;
    if wv850062.FieldByName('查询结果集').Data.IsEmpty then
    begin
      Context.GetDialogSystem.ShowMessage('数据统计表没有相关记录，请重新指定条件');
      Exit;
    end;
    tempData := Tdataset(wv850062.FieldByName('查询结果集').Data.AsObject);
  end
  else
  if accType=3 then
  begin
    title := '明细分类账查询';
    wv850063.FieldByName('科目号').Data.SetString(subjNo);
    wv850063.FieldByName('开始日期').Data.SetInteger(StrToInt(edtBeginDate.Text));
    wv850063.FieldByName('结束日期').Data.SetInteger(StrToInt(edtEndDate.Text));
    wv850063.FieldByName('包含未入账').Data.SetInteger(acc);
    wv850063.FieldByName('查询方式').Data.SetString(qtype);
    wvr850063.SendCommand;
    if wv850063.FieldByName('查询结果集').Data.IsEmpty then
    begin
      Context.GetDialogSystem.ShowMessage('数据统计表没有相关记录，请重新指定条件');
      Exit;
    end;
    tempData := Tdataset(wv850063.FieldByName('查询结果集').Data.AsObject);
  end;
  if endSign = False then
    Exit;
  endSign := False;
  
  execSQL(delaccquery);
  qry := nil;
  try
    qry := TZQuery.Create(nil);
    qry.Connection := cmAccountMgrImp.conFB;
    qry.Close;
    qry.SQL.Clear;
    qry.SQL.Add(beginTrans);
    qry.ExecSQL;
    
    tempData.First;
    while not tempData.Eof do
    begin
      {
      if tempData.fieldbyname('lserial1').asinteger=0 then
      begin
        tempData.Next;
        Continue;
      end;
      }
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add(insertStr(tempData));
      qry.ExecSQL;
      tempData.Next;
    end;
    qry.Close;
    qry.SQL.Clear;
    qry.SQL.Add(commitTrans);
    qry.ExecSQL;
  finally
    qry.Close;
    qry.Destroy;
  end;
  try
    if accType=3 then
    begin
      if rgQType.ItemIndex=1 then
        rptQRpt.LoadFromFile(sPreAppPath+'report\Account\会计账簿_日明细.rmf')
      else
        rptQRpt.LoadFromFile(sPreAppPath+'report\Account\会计账簿_月明细.rmf')
    end
    else
      rptQRpt.LoadFromFile(sPreAppPath+'report\Account\会计账簿.rmf');
    if zqry1.Active=True then
      zqry1.Active := False;
    zqry1.Active := True;
    
    if rgQType.ItemIndex=1 then
      rptQRpt.Dictionary.Variables.AsString['colDate'] := '日期'
    else
      rptQRpt.Dictionary.Variables.AsString['colDate'] := '月份';
    rptQRpt.Dictionary.Variables.AsString['dateRange'] := strBDate+'至'+strEDate;
    rptQRpt.Dictionary.Variables.AsString['SubjName'] := subjNo+'-'+subjname;
    rptQRpt.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
    rptQRpt.Dictionary.Variables.AsString['title'] := title;
    rptQRpt.Dictionary.Variables.AsString['rptOper'] := rptOper;
    rptQRpt.Dictionary.Variables.AsString['checkOper'] := Context.ParamData(svOperatorNameName).AsString;
    rptQRpt.DoublePass := True;
    rptQRpt.Preview := rmprvwP;
    rptQRpt.ShowReport;
  except
    Context.GetDialogSystem.ShowMessage('你没有安装打印机，请先安装(可以是虚拟打印机)！');
  end;
  endSign := true;

end;

procedure TfaAccountRpt.rgQTypeClick(Sender: TObject);
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
  TUIStdClassFactory.Create('会计账簿',TfaAccountRpt);

end.
