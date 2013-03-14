unit UAGateListDelete;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox, ComCtrls,
  RzListVw, RzButton, RzRadChk, RzEdit, Buttons, ADODB;

type
  TfaqhGateListDelete = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    WVEdit1: TWVEdit;
    WVEdit4: TWVEdit;
    Label4: TLabel;
    Label7: TLabel;
    cbbCustType: TWVComboBox;
    WVEdit10: TWVEdit;
    Label10: TLabel;
    Label11: TLabel;
    WVComboBox6: TWVComboBox;
    cbbFeeType: TWVComboBox;
    cbbDep: TWVComboBox;
    WVEdit2: TWVEdit;
    Label2: TLabel;
    Label5: TLabel;
    Label8: TLabel;
    Label12: TLabel;
    Label9: TLabel;
    Label6: TLabel;
    Label3: TLabel;
    WVEdit3: TWVEdit;
    WVEdit6: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    lv1: TRzListView;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    btnDelete: TBitBtn;
    chkCustUnAllot: TRzCheckBox;
    pnl1: TPanel;
    mmo1: TRzMemo;
    btn1: TSpeedButton;
    btnInfo: TBitBtn;
    SpeedButton1: TSpeedButton;
    Label14: TLabel;
    edtTable: TWVEdit;
    btnOpen: TBitBtn;
    btnIMPQuery: TBitBtn;
    btnCloseConn: TBitBtn;
    btnDelList: TBitBtn;
    conSource: TADOConnection;
    qrySource: TADOQuery;
    dlgOpen: TOpenDialog;
    Label13: TLabel;
    WVComboBox3: TWVComboBox;
    btnErrInfo: TBitBtn;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure chkCustUnAllotClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btn1Click(Sender: TObject);
    procedure btnInfoClick(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure btnOpenClick(Sender: TObject);
    procedure btnIMPQueryClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure btnDelListClick(Sender: TObject);
    procedure btnErrInfoClick(Sender: TObject);
  private

    { Private declarations }
    fileName:string;
    procedure fillList(wv: TWorkView);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhGateListDelete: TfaqhGateListDelete;

implementation

uses KsFrameworks, 
     KSDataDictionary,gateComm,KSClientConsts;

{$R *.DFM}

procedure TfaqhGateListDelete.Init;
begin
  inherited;
  btnInfo.Caption := '删除信息';
  btnInfo.Enabled := True;
end;

procedure TfaqhGateListDelete.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhGateListDelete.btnQueryClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  //inherited;
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    ShowMessage(WorkView1.FieldByName('返回信息').Data.AsString);
    Exit;
  end;
  {
  tmpDataSet := TDataSet(WorkView1.FieldByName('查询结果集').Data.AsObject);
  tmpDataSet.First;
  lv1.Items.Clear;
  while not tmpDataSet.Eof do
  begin
    tmpItem := lv1.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lvol0').asstring;                                  //设备标识
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail2').AsString);                            //设备名称
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol2').AsString);                          //客户号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_auth').AsString);                          //学工号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail').AsString);                            //姓名
    tmpItem.SubItems.Add(GetIdObjectName(84,tmpdataset.fieldbyname('sstatus1').AsString));          //状态
    tmpItem.SubItems.Add(GetIdObjectName(-34,tmpdataset.fieldbyname('lvol3').AsString));         //客户类别
    tmpItem.SubItems.Add(GetIdObjectName(-43,tmpdataset.fieldbyname('lvol4').AsString));         //收费类别                 
    tmpItem.SubItems.Add(GetIdObjectName(-22,tmpdataset.fieldbyname('sstation0').AsString));       //院系
    tmpItem.SubItems.Add(GetIdObjectName(-23,tmpdataset.fieldbyname('sstation1').AsString));       //专业
    tmpItem.SubItems.Add(GetIdObjectName(133,tmpdataset.fieldbyname('sstat_type').AsString));       //名单类型
    tmpdataset.Next;
  end;
  }
  fillList(WorkView1);

  btnDelete.Enabled := True;
end;

procedure TfaqhGateListDelete.chkCustUnAllotClick(Sender: TObject);
begin
  if listViewSelectAll(lv1,chkCustUnAllot)=False then
    Exit;
end;

procedure TfaqhGateListDelete.btnDeleteClick(Sender: TObject);
var
  i:Integer;
begin
  if (checkListViewSelect(lv1)=False) then
  begin
    Context.GetDialogSystem.ShowMessage('请选择删除的人员名单！');
    Exit;
  end;
  if Application.MessageBox('你确定要删除选择的门禁人员信息吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  for i := 0 to lv1.Items.Count-1 do
  begin
    if lv1.Items[i].Checked then
    begin
      WorkView.FieldByName('门禁编号').Data.SetInteger(StrToInt(lv1.Items[i].caption));
      WorkView.FieldByName('客户号').Data.SetInteger(StrToInt(lv1.Items[i].SubItems[1]));
      try
        //WorkView.FieldByName('状态').Data.SetInteger(StrToInt(lv1.Items[i].SubItems[4]));
        //WorkView.FieldByName('增删标志').Data.SetInteger(StrToInt(lv1.Items[i].SubItems[6]));
        WorkView.FieldByName('时间周').Data.SetInteger(StrToInt(lv1.Items[i].SubItems[8]));
      except
        //WorkView.FieldByName('状态').Data.SetInteger(0);
        //WorkView.FieldByName('增删标志').Data.SetInteger(0);
        WorkView.FieldByName('时间周').Data.SetInteger(0);
      end;
      try
        MainRequest.SendCommand;
      except
        on e:Exception do
        begin
          mmo1.Lines.Add('学工号['+lv1.Items[i].SubItems[2]+']姓名为['+lv1.Items[i].SubItems[3]+']的名单删除失败,失败原因--'+e.Message);
          Continue;
        end;
      end;
      mmo1.Lines.Add(WorkView.fieldbyname('返回信息').Data.AsString);
    end;
  end;
  btnInfo.Enabled := True;
  Context.GetDialogSystem.ShowMessage('门禁人员名单删除成功！');
end;

procedure TfaqhGateListDelete.btn1Click(Sender: TObject);
begin
  pnl1.Visible := False;

end;

procedure TfaqhGateListDelete.btnInfoClick(Sender: TObject);
begin
  pnl1.Visible := True;

end;

procedure TfaqhGateListDelete.SpeedButton1Click(Sender: TObject);
begin
  if Application.MessageBox('你确定要清空删除时产生的信息吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  mmo1.Lines.Clear;

end;

procedure TfaqhGateListDelete.fillList(wv: TWorkView);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  tmpDataSet := TDataSet(wv.FieldByName('查询结果集').Data.AsObject);
  tmpdataset.First;
  lv1.Items.Clear;
  while not tmpDataSet.Eof do
  begin
    tmpItem := lv1.Items.Add;
    tmpItem.Caption := tmpdataset.fieldbyname('lvol0').asstring;                                  //设备标识
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail2').AsString);                            //设备名称
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol2').AsString);                          //客户号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('scust_auth').AsString);                          //学工号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('semail').AsString);                            //姓名
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol7').AsString);           //状态
    tmpItem.SubItems.Add(GetIdObjectName(84,tmpdataset.fieldbyname('lvol7').AsString));          //状态               //客户号
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol8').AsString);           //增删标志
    tmpItem.SubItems.Add(GetIdObjectName(44,tmpdataset.fieldbyname('lvol8').AsString));           //增删标志
    tmpItem.SubItems.Add(tmpdataset.fieldbyname('lvol9').AsString);           //时间周
    tmpItem.SubItems.Add(GetIdObjectName(-34,tmpdataset.fieldbyname('lvol3').AsString));         //客户类别                 //学工号
    tmpItem.SubItems.Add(GetIdObjectName(-43,tmpdataset.fieldbyname('lvol4').AsString));         //收费类别                  //学工号
    tmpItem.SubItems.Add(GetIdObjectName(-22,tmpdataset.fieldbyname('sstation0').AsString));       //院系
    tmpItem.SubItems.Add(GetIdObjectName(-23,tmpdataset.fieldbyname('sstation1').AsString));       //专业
    tmpdataset.Next;
  end;
end;

procedure TfaqhGateListDelete.btnOpenClick(Sender: TObject);
begin
  dlgOpen.Title := '请选择相应的Excel文件';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    fileName := dlgOpen.FileName;
end;

procedure TfaqhGateListDelete.btnIMPQueryClick(Sender: TObject);
var
  sqlstr:string;
  i:Integer;
  stuempNo,custName:string;
begin
  //inherited;
  try
    if conSource.Connected=True then
      conSource.Connected:=False;
    conSource.ConnectionString:='Provider=Microsoft.Jet.OLEDB.4.0;Data Source='+
    Trim(fileName)+';Extended Properties=Excel 8.0;Persist Security Info=False';
    conSource.Connected :=True;
    qrySource.Connection := conSource;

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where 学工号<>'+#39+''+#39;
    qrySource.Close;
    qrySource.SQL.Clear;
    qrySource.SQL.Add(sqlstr);
    try
      qrySource.Open;
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage('查询错误--'+e.Message);
        Exit;
      end;
    end;
  except
    on ex:exception do
    begin
      Context.GetDialogSystem.ShowMessage('打开数据表失败--'+ex.message);
      Exit;
    end;
  end;
  if qrySource.RecordCount<=0 then
  begin
    Context.GetDialogSystem.ShowMessage('打开的Excel没有记录，请查看打开的路径和表单名是否正确!');
    Exit;
  end;
  
  try
    qrySource.First;
    while not qrySource.Eof do
    begin
      stuempNo := Trim(qrySource.FieldByName('学工号').AsString);
      custName := Trim(qrySource.FieldByName('姓名').AsString);
      //if Trim(sCustId)='####' then
      //  Exit;
      WorkView1.FieldByName('门禁机名称').Data.SetString('');// := '';
      WorkView1.FieldByName('门禁设备编号').Data.SetInteger(0);// := 0;
      WorkView1.FieldByName('学工号').Data.SetString(stuempNo);// := '';
      WorkView1.FieldByName('姓名').Data.SetString('');// := '';
      WorkView1.FieldByName('院系代码').Data.SetString('');// := '';
      WorkView1.FieldByName('客户号').Data.SetInteger(0);// 0;
      WorkView1.FieldByName('客户类型').Data.SetInteger(0);// := 0;
      WorkView1.FieldByName('收费类型').Data.SetInteger(0);// := 0;
      //WorkView1.FieldByName('医院收费方式').Data.SetInteger(0);// := 0;
      WorkView1.FieldByName('班级').Data.SetString('');// := '';
      WorkView1.FieldByName('专业代码').Data.SetString('');// := '';
      WorkView1.FieldByName('状态').Data.SetInteger(0);// := 0;
      WorkView1.FieldByName('操作员').DefaultValue := Context.ParamData(svOperatorNoName).AsString;
      try
        WVRequest1.SendCommand;
        if WorkView1.FieldByName('返回码').Data.AsInteger<>0 then
        begin
          mmo1.Lines.Add('学工号['+stuempNo+']姓名为['+custName+']的名单导入查询失败,失败原因--'+WorkView1.FieldByName('返回信息').Data.AsString);
          qrySource.Next;
          Continue;
        end;
      except
        on e:Exception do
        begin
          mmo1.Lines.Add('学工号['+stuempNo+']姓名为['+custName+']的名单导入查询失败,失败原因--'+e.Message);
          qrySource.Next;
          Continue;
        end;
      end;
      fillList(WorkView1);
      qrySource.Next;
    end;
    btnDelete.Enabled := True;
  finally
    qrySource.Recordset.Close;
    qrySource.Close;
    conSource.Connected:=false;
  end;
end;

procedure TfaqhGateListDelete.btnPrintClick(Sender: TObject);
begin
  if conSource.Connected=True then
  begin
    qrySource.Recordset.Close;
    qrySource.Close;
    conSource.Connected:=false;
  end;
end;

procedure TfaqhGateListDelete.btnDelListClick(Sender: TObject);
var
  i:Integer;
begin
  for i := lv1.Items.Count-1 downto 0 do
    lv1.Items.Delete(i);
end;

procedure TfaqhGateListDelete.btnErrInfoClick(Sender: TObject);
begin
  pnl1.Visible := True;

end;

initialization
  TUIStdClassFactory.Create('门禁人员名单删除',TfaqhGateListDelete);

end.