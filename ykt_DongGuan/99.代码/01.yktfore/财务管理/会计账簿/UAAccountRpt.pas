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
850061�ܷ����˲�ѯ
850062�ռ��˲�ѯ
850063��ϸ�����ʲ�ѯ
}

procedure TfaAccountRpt.Init;
begin
  inherited;
  subjNo := '';
  lblAccType.Caption := '';
  edtBeginDate.Text := bAccountDate;
  edtEndDate.Text := bAccountDate;
  WorkView.FieldByName('�˲�����').Data.SetString('1');
  endSign := True;
end;

procedure TfaAccountRpt.btnChangeClick(Sender: TObject);
begin
  if subjNo='' then
  begin
    Context.GetDialogSystem.ShowMessage('���ȵ���ѡ��һ��Ҫ�鿴����ļ�¼��');
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
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
    Exit;
  tempData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
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

  title := '';
  if chkAcc.Checked then
    acc := 1
  else
    acc := 0;
  if accType=1 then
  begin
    title := '�ܷ����˲�ѯ';
    wv850061.FieldByName('��Ŀ��').Data.SetString(subjNo);
    wv850061.FieldByName('��ʼ����').Data.SetInteger(StrToInt(edtBeginDate.Text));
    wv850061.FieldByName('��������').Data.SetInteger(StrToInt(edtEndDate.Text));
    wv850061.FieldByName('����δ����').Data.SetInteger(acc);
    wvr850061.SendCommand;
    if wv850061.FieldByName('��ѯ�����').Data.IsEmpty then
    begin
      Context.GetDialogSystem.ShowMessage('����ͳ�Ʊ�û����ؼ�¼��������ָ������');
      Exit;
    end;
    tempData := Tdataset(wv850061.FieldByName('��ѯ�����').Data.AsObject);
  end
  else
  if accType=2 then
  begin
    title := '�ռ��˲�ѯ';
    wv850062.FieldByName('��Ŀ��').Data.SetString(subjNo);
    wv850062.FieldByName('��ʼ����').Data.SetInteger(StrToInt(edtBeginDate.Text));
    wv850062.FieldByName('��������').Data.SetInteger(StrToInt(edtEndDate.Text));
    wv850062.FieldByName('����δ����').Data.SetInteger(acc);
    wvr850062.SendCommand;
    if wv850062.FieldByName('��ѯ�����').Data.IsEmpty then
    begin
      Context.GetDialogSystem.ShowMessage('����ͳ�Ʊ�û����ؼ�¼��������ָ������');
      Exit;
    end;
    tempData := Tdataset(wv850062.FieldByName('��ѯ�����').Data.AsObject);
  end
  else
  if accType=3 then
  begin
    title := '��ϸ�����˲�ѯ';
    wv850063.FieldByName('��Ŀ��').Data.SetString(subjNo);
    wv850063.FieldByName('��ʼ����').Data.SetInteger(StrToInt(edtBeginDate.Text));
    wv850063.FieldByName('��������').Data.SetInteger(StrToInt(edtEndDate.Text));
    wv850063.FieldByName('����δ����').Data.SetInteger(acc);
    wv850063.FieldByName('��ѯ��ʽ').Data.SetString(qtype);
    wvr850063.SendCommand;
    if wv850063.FieldByName('��ѯ�����').Data.IsEmpty then
    begin
      Context.GetDialogSystem.ShowMessage('����ͳ�Ʊ�û����ؼ�¼��������ָ������');
      Exit;
    end;
    tempData := Tdataset(wv850063.FieldByName('��ѯ�����').Data.AsObject);
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
        rptQRpt.LoadFromFile(sPreAppPath+'report\Account\����˲�_����ϸ.rmf')
      else
        rptQRpt.LoadFromFile(sPreAppPath+'report\Account\����˲�_����ϸ.rmf')
    end
    else
      rptQRpt.LoadFromFile(sPreAppPath+'report\Account\����˲�.rmf');
    if zqry1.Active=True then
      zqry1.Active := False;
    zqry1.Active := True;
    
    if rgQType.ItemIndex=1 then
      rptQRpt.Dictionary.Variables.AsString['colDate'] := '����'
    else
      rptQRpt.Dictionary.Variables.AsString['colDate'] := '�·�';
    rptQRpt.Dictionary.Variables.AsString['dateRange'] := strBDate+'��'+strEDate;
    rptQRpt.Dictionary.Variables.AsString['SubjName'] := subjNo+'-'+subjname;
    rptQRpt.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
    rptQRpt.Dictionary.Variables.AsString['title'] := title;
    rptQRpt.Dictionary.Variables.AsString['rptOper'] := rptOper;
    rptQRpt.Dictionary.Variables.AsString['checkOper'] := Context.ParamData(svOperatorNameName).AsString;
    rptQRpt.DoublePass := True;
    rptQRpt.Preview := rmprvwP;
    rptQRpt.ShowReport;
  except
    Context.GetDialogSystem.ShowMessage('��û�а�װ��ӡ�������Ȱ�װ(�����������ӡ��)��');
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
  TUIStdClassFactory.Create('����˲�',TfaAccountRpt);

end.
