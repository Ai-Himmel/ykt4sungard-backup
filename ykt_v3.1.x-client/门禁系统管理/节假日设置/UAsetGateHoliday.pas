unit UAsetGateHoliday;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, UIncrementComboBox,
  RzPanel, RzGrids, Buttons, ComCtrls, RzListVw;

type
  TfaqhsetGateHoliday = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label4: TLabel;
    Label6: TLabel;
    WVDigitalEdit1: TWVDigitalEdit;
	  WVEdit2: TWVEdit;
    edtNo: TWVDigitalEdit;
    Label3: TLabel;
    edtName: TWVEdit;
    Label7: TLabel;
    btnDelDate: TBitBtn;
    btnSet: TBitBtn;
    Label9: TLabel;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    lblTime: TLabel;
    edtTime: TWVEdit;
    WVDBBinder1: TWVDBBinder;
    DataSource1: TDataSource;
    WVRequest2: TWVRequest;
    WorkView2: TWorkView;
    btn1: TSpeedButton;
    dtpTime: TDateTimePicker;
    WVRequest3: TWVRequest;
    WorkView3: TWorkView;
    lblNo: TLabel;
    lvTime: TRzListView;
    dtpETime: TDateTimePicker;
    Label8: TLabel;
    pnlQuery: TPanel;
    Label16: TLabel;
    Label18: TLabel;
    WVEdit1: TWVEdit;
    WVEdit4: TWVEdit;
    pnl1: TPanel;
    btnTimeQuery: TBitBtn;
    btnSelect: TBitBtn;
    btnCancle: TBitBtn;
    dbgrd1: TDBGrid;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnAddClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure gridDetailClick(Sender: TObject);
    procedure btnSetClick(Sender: TObject);
    procedure btnDelDateClick(Sender: TObject);
    procedure btnTimeQueryClick(Sender: TObject);
    procedure btnSelectClick(Sender: TObject);
    procedure edtTimeChange(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btn1Click(Sender: TObject);
    procedure btnCancleClick(Sender: TObject);
    procedure dbgrd1DblClick(Sender: TObject);
    procedure lvTimeClick(Sender: TObject);
    procedure dtpTimeChange(Sender: TObject);
    procedure lvTimeCustomDrawItem(Sender: TCustomListView;
      Item: TListItem; State: TCustomDrawState; var DefaultDraw: Boolean);
  private

    { Private declarations }
    OperatorNoName:string;
    procedure saveDataToGrid(inDate:TDate;inTimeId:string);
    procedure selectTimeDetail;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetGateHoliday: TfaqhsetGateHoliday;

implementation

uses KsFrameworks, 
     KSClientConsts, gateComm;
     
{$R *.DFM}

procedure TfaqhsetGateHoliday.Init;
begin
  inherited;
  WorkView.FieldByName('查询.节假日编号').DefaultValue := 0;
  WorkView.FieldByName('查询.节假日名').DefaultValue := '';
  WorkView.FieldByName('交易类型').DefaultValue := '';
  WorkView.FieldByName('节假日编号').DefaultValue := 0;
  WorkView.FieldByName('节假日名').DefaultValue := '';
  WorkView.Reset;
  
  WorkView1.FieldByName('节假日编号').DefaultValue := 0;
  WorkView1.FieldByName('时间段组编号').DefaultValue := 0;
  WorkView1.Reset;

  operatorNoName := Context.ParamData(svOperatorNoName).AsString;
  btnSet.Caption:='设置日期';
  btnDelDate.Caption:='删除日期';
  btnOK.Caption:='保存设置';
  btnTimeQuery.Caption := '查　询';
  btnSelect.Caption := '选　择';
  btnCancle.Caption := '取　消';
  lblTime.Caption:='';
  dtpTime.Date := Date;
  dtpETime.Date := dtpTime.Date;
end;

procedure TfaqhsetGateHoliday.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetGateHoliday.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetGateHoliday.btnAddClick(Sender: TObject);
begin
  inherited;
  lvTime.Items.Clear;
  edtNo.ReadOnly := True;
  edtTime.ReadOnly:=True;
  WorkView.FieldByName('节假日编号').Data.SetInteger(0);
  addType(operatorNoName,WorkView);
  lblNo.Caption := Trim(edtNo.Text);
end;

procedure TfaqhsetGateHoliday.btnQueryClick(Sender: TObject);
begin
  queryType(operatorNoName,WorkView);
  inherited;
end;

procedure TfaqhsetGateHoliday.btnChangeClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  tmpItem: TListItem;
begin
  inherited;
  edtNo.ReadOnly := True;
  edtTime.ReadOnly:=True;
  lvTime.Items.Clear;
  chargeType(operatorNoName,WorkView);
  lblNo.Caption := Trim(edtNo.Text);
  WorkView3.FieldByName('节假日编号').Data.SetInteger(Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger);
  WVRequest3.SendCommand;
  tmpDataSet := TDataSet(WorkView3.FieldByName('查询结果集').Data.AsObject);
  if tmpDataSet=nil then
    Exit;
  tmpDataSet.First;
  while not tmpDataSet.Eof do
  begin
    tmpItem := lvTime.Items.Add;
    tmpItem.Caption:=tmpDataSet.fieldbyname('sdate0').AsString;
    tmpItem.SubItems.Add(tmpDataSet.fieldbyname('lvol1').AsString);
    tmpDataSet.Next;
  end;
end;

procedure TfaqhsetGateHoliday.btnDeleteClick(Sender: TObject);
begin
  if Application.MessageBox('你确定要删除该节假日吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  WorkView.FieldByName('节假日编号').Data.SetInteger(Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger);
  WorkView.FieldByName('交易类型').Data.SetString('D');
  DeleteRequest.SendCommand;
  btnQuery.Click;
  //inherited;
  //edtNo.ReadOnly := True;
  //deleteType(operatorNoName,WorkView);
end;

procedure TfaqhsetGateHoliday.saveDataToGrid(inDate:TDate;inTimeId:string);
var
  i:Integer;
  sDate : string;
  tmpItem: TListItem;
begin
  //先查找是否有记录，有则修改，没有则添加
  for i := 0 to lvTime.Items.Count-1 do
  begin
    sDate := lvTime.Items[i].Caption;
    if sDate = FormatDateTime('yyyymmdd',inDate) then
    begin
      lvTime.Items[i].SubItems[0] := inTimeId;
      Exit;
    end;
  end;
  tmpItem := lvTime.Items.Add;
  tmpItem.Caption := FormatDateTime('yyyymmdd',inDate);
  tmpItem.SubItems.Add(inTimeId);
end;

procedure TfaqhsetGateHoliday.selectTimeDetail;
var
  i : Integer;
  sDate:string;
begin
  i:=lvTime.Items.IndexOf(lvTime.Selected);
  if i<0 then
    Exit;
  sDate := lvTime.Items[i].Caption;
  dtpTime.Date := StrToDate(Copy(sDate,1,4)+'-'+copy(sDate,5,2)+'-'+copy(sDate,7,2));
  dtpETime.Date := dtpTime.Date;
  edtTime.Text := lvTime.Items[i].SubItems[0];
end;

procedure TfaqhsetGateHoliday.gridDetailClick(Sender: TObject);
begin
  selectTimeDetail;
end;

procedure TfaqhsetGateHoliday.btnSetClick(Sender: TObject);
var
  sDate,eDate:TDate;
begin
  if (Trim(edtTime.Text)='')or(Trim(edtTime.Text)='0') then
  begin
    ShowMessage('请选择时间段组！');
    Exit;
  end;
  sDate := dtpTime.Date;
  eDate := dtpETime.Date;
  if sDate>eDate then
  begin
    ShowMessage('开始日期不能大约结束日期，请从新设置！');
    Exit;
  end;
  while sDate<=eDate do
  begin
    saveDataToGrid(sDate,edtTime.Text);
    sDate := sDate + 1;
  end;
end;

procedure TfaqhsetGateHoliday.btnDelDateClick(Sender: TObject);
var
  i:Integer;
begin
  i:=lvTime.Items.IndexOf(lvTime.Selected);
  if i<0 then
  begin
    ShowMessage('请选择要删除的节假日日期！');
    Exit;
  end;
  if Application.MessageBox('你确定要删除当前选择的行吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  lvTime.Items.Delete(lvTime.Selected.Index);
end;

procedure TfaqhsetGateHoliday.btnTimeQueryClick(Sender: TObject);
begin
  //WorkView2.FieldByName('查询.标识').Data.SetInteger(0);
  WorkView2.FieldByName('交易类型').Data.SetString('R');
  WVRequest2.SendCommand;
end;

procedure TfaqhsetGateHoliday.btnSelectClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
begin
  tmpDataSet := TDataSet(WorkView2.FieldByName('查询结果集').Data.AsObject);
  if tmpDataSet = nil then
  begin
    ShowMessage('请先查询出结果，然后再选择！');
    Exit;
  end;
  //WorkView1.FieldByName('时间段组编号').Data.SetInteger(tmpDataSet.fieldbyname('lcert_code').AsInteger);
  lblTime.Caption := '时间段组名称：'+tmpDataSet.fieldbyname('semail').AsString;
  edtTime.Text:=tmpDataSet.fieldbyname('lcert_code').AsString;
  pnlQuery.Visible := False;
end;

procedure TfaqhsetGateHoliday.edtTimeChange(Sender: TObject);
var
  tmpDataSet:TDataSet;
begin
  WorkView2.FieldByName('查询.标识').Data.SetInteger(StrToInt(edtTime.Text));
  WorkView2.FieldByName('交易类型').Data.SetString('R');
  WVRequest2.SendCommand;
  tmpDataSet := TDataSet(WorkView2.FieldByName('查询结果集').Data.AsObject);
  if tmpDataSet = nil then
  begin
    ShowMessage('请先查询出结果，然后再选择！');
    Exit;
  end;
  lblTime.Caption := '时间段组名称：'+tmpDataSet.fieldbyname('semail').AsString;
end;

procedure TfaqhsetGateHoliday.btnOKClick(Sender: TObject);
var
  i:Integer;
begin
  if Trim(edtName.Text)='' then
  begin
    ShowMessage('请输入节假日名称！');
    Exit;
  end;
  if (lvTime.Items.Count)<=0 then
    if Application.MessageBox('没有设置节假日日期，你确定要保存吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
      Exit;
  inherited;
  if Trim(lblNo.Caption)='0' then
  begin
    WorkView1.FieldByName('节假日编号').Data.SetInteger(WorkView.fieldbyname('节假日编号').Data.AsInteger);
  end
  else
  begin
    WorkView1.FieldByName('节假日编号').Data.SetInteger(StrToInt(lblNo.Caption));
  end;
  if lvTime.Items.Count=1 then
  begin
    WorkView1.FieldByName('标志').Data.SetString('3');
    WorkView1.FieldByName('节假日日期').Data.SetString(lvTime.items[i].Caption);
    WorkView1.FieldByName('时间段组编号').Data.SetInteger(StrToInt(lvTime.items[i].SubItems[0]));
    WVRequest1.SendCommand;
  end
  else
  begin
    for i := 0 to lvTime.Items.Count-1 do
    begin
      if i=0 then
        WorkView1.FieldByName('标志').Data.SetString('1')
      else if i=lvTime.Items.Count-1 then
        WorkView1.FieldByName('标志').Data.SetString('2')
      else
        WorkView1.FieldByName('标志').Data.SetString('0');
      WorkView1.FieldByName('节假日日期').Data.SetString(lvTime.items[i].Caption);
      WorkView1.FieldByName('时间段组编号').Data.SetInteger(StrToInt(lvTime.items[i].SubItems[0]));
      WVRequest1.SendCommand;
    end;
  end;
  lvTime.items.clear;
  lblTime.Caption:='';
  lblNo.Caption :='0';
  btnQuery.Click;
end;

procedure TfaqhsetGateHoliday.btn1Click(Sender: TObject);
begin
  pnlQuery.Visible:=True;
  WorkView2.FieldByName('查询.标识').Data.SetInteger(0);
  btnTimeQuery.Click;
end;

procedure TfaqhsetGateHoliday.btnCancleClick(Sender: TObject);
begin
  pnlQuery.Visible:=False;

end;

procedure TfaqhsetGateHoliday.dbgrd1DblClick(Sender: TObject);
begin
  btnSelect.Click;
end;

procedure TfaqhsetGateHoliday.lvTimeClick(Sender: TObject);
begin
  selectTimeDetail;
end;

procedure TfaqhsetGateHoliday.dtpTimeChange(Sender: TObject);
begin
  dtpETime.Date := dtpTime.Date;
end;

procedure TfaqhsetGateHoliday.lvTimeCustomDrawItem(Sender: TCustomListView;
  Item: TListItem; State: TCustomDrawState; var DefaultDraw: Boolean);
begin
  inherited;
  DefaultDraw:=false;
  if Item.Index mod 2 <>0 then
    Sender.Canvas.Brush.Color := clInfoBk
  else
    Sender.Canvas.Brush.Color := $00EBDED0;
  Sender.Canvas.Font.Color := clBlack;
  DefaultDraw:=true;
end;

initialization
  TUIStdClassFactory.Create('节假日设置',TfaqhsetGateHoliday);

end.