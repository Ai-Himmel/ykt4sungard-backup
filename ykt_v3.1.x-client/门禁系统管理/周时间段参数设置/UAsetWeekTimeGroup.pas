unit UAsetWeekTimeGroup;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, 
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, Buttons;

type
  TfaqhsetWeekTimeGroup = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    Label20: TLabel;
    WVDigitalEdit1: TWVDigitalEdit;
	  WVEdit2: TWVEdit;
    WVDigitalEdit11: TWVDigitalEdit;
    edtName: TWVEdit;
    WVEdit1: TWVEdit;
    WVEdit3: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit5: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit7: TWVEdit;
    WVEdit8: TWVEdit;
    btn1: TSpeedButton;
    SpeedButton1: TSpeedButton;
    SpeedButton2: TSpeedButton;
    SpeedButton3: TSpeedButton;
    SpeedButton4: TSpeedButton;
    SpeedButton5: TSpeedButton;
    SpeedButton6: TSpeedButton;
    lbl1: TLabel;
    lbl2: TLabel;
    lbl3: TLabel;
    lbl4: TLabel;
    lbl5: TLabel;
    lbl6: TLabel;
    lbl7: TLabel;
    pnlQuery: TPanel;
    Label10: TLabel;
    Label13: TLabel;
    WVEdit9: TWVEdit;
    WVEdit10: TWVEdit;
    pnl1: TPanel;
    btnTimeQuery: TBitBtn;
    btnSelect: TBitBtn;
    btnCancle: TBitBtn;
    dbgrd1: TDBGrid;
    WorkView2: TWorkView;
    WVDBBinder1: TWVDBBinder;
    DataSource1: TDataSource;
    WVRequest2: TWVRequest;
    btnSet0: TBitBtn;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btn1Click(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure SpeedButton2Click(Sender: TObject);
    procedure SpeedButton3Click(Sender: TObject);
    procedure SpeedButton4Click(Sender: TObject);
    procedure SpeedButton5Click(Sender: TObject);
    procedure SpeedButton6Click(Sender: TObject);
    procedure btnTimeQueryClick(Sender: TObject);
    procedure btnCancleClick(Sender: TObject);
    procedure btnSelectClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure dbgrd1DblClick(Sender: TObject);
    procedure WVEdit1Change(Sender: TObject);
    procedure WVEdit3Change(Sender: TObject);
    procedure WVEdit4Change(Sender: TObject);
    procedure WVEdit5Change(Sender: TObject);
    procedure WVEdit6Change(Sender: TObject);
    procedure WVEdit7Change(Sender: TObject);
    procedure WVEdit8Change(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure GridDblClick(Sender: TObject);
    procedure btnSet0Click(Sender: TObject);
  private

    { Private declarations }
    iSelect:Integer;
    //iSelectTime:Integer;
    function transLToB(instr:Integer): string;
    procedure clearLabel;

    function getNameById(inId:Integer): string;

  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetWeekTimeGroup: TfaqhsetWeekTimeGroup;

implementation

uses KsFrameworks,USetParamsTemp, 
     gateComm;
     
{$R *.DFM}

procedure TfaqhsetWeekTimeGroup.Init;
begin
  inherited;
  {
  WorkView.FieldByName('查询.时间段组编号').DefaultValue := 0;
  WorkView.FieldByName('查询.时间段组名称').DefaultValue := '';
  WorkView.FieldByName('查询.周一组编号').DefaultValue := 0;
  WorkView.FieldByName('查询.周二组编号').DefaultValue := 0;
  WorkView.FieldByName('查询.周三组编号').DefaultValue := 0;
  WorkView.FieldByName('查询.周四组编号').DefaultValue := 0;
  WorkView.FieldByName('查询.周五组编号').DefaultValue := 0;
  WorkView.FieldByName('查询.周六组编号').DefaultValue := 0;
  WorkView.FieldByName('查询.周日组编号').DefaultValue := 0;
  WorkView.FieldByName('时间段组编号').DefaultValue := 0;
  WorkView.FieldByName('时间段组名').DefaultValue := '';
  WorkView.FieldByName('周一组编号').DefaultValue := 0;
  WorkView.FieldByName('周二组编号').DefaultValue := 0;
  WorkView.FieldByName('周三组编号').DefaultValue := 0;
  WorkView.FieldByName('周四组编号').DefaultValue := 0;
  WorkView.FieldByName('周五组编号').DefaultValue := 0;
  WorkView.FieldByName('周六组编号').DefaultValue := 0;
  WorkView.FieldByName('周日组编号').DefaultValue := 0;
  WorkView.Reset;
  }
  btnTimeQuery.Caption := '查　询';
  btnSelect.Caption := '选　择';
  btnCancle.Caption := '取　消';
  clearLabel;
end;

procedure TfaqhsetWeekTimeGroup.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetWeekTimeGroup.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetWeekTimeGroup.btn1Click(Sender: TObject);
begin
  iSelect := 1;
  pnlQuery.Visible := True;
  WorkView2.FieldByName('查询.标识').Data.SetInteger(0);
  WorkView2.FieldByName('查询.时间段名称').Data.SetString('');
  btnTimeQuery.Click;
  //ShowMessage('111');
end;

procedure TfaqhsetWeekTimeGroup.SpeedButton1Click(Sender: TObject);
begin
  iSelect := 2;
  pnlQuery.Visible := True;
  WorkView2.FieldByName('查询.标识').Data.SetInteger(0);
  WorkView2.FieldByName('查询.时间段名称').Data.SetString('');
  btnTimeQuery.Click;
end;

procedure TfaqhsetWeekTimeGroup.SpeedButton2Click(Sender: TObject);
begin
  iSelect := 3;
  pnlQuery.Visible := True;
  WorkView2.FieldByName('查询.标识').Data.SetInteger(0);
  WorkView2.FieldByName('查询.时间段名称').Data.SetString('');
  btnTimeQuery.Click;
end;

procedure TfaqhsetWeekTimeGroup.SpeedButton3Click(Sender: TObject);
begin
  iSelect := 4;
  pnlQuery.Visible := True;
  WorkView2.FieldByName('查询.标识').Data.SetInteger(0);
  WorkView2.FieldByName('查询.时间段名称').Data.SetString('');
  btnTimeQuery.Click;
end;

procedure TfaqhsetWeekTimeGroup.SpeedButton4Click(Sender: TObject);
begin
  iSelect := 5;
  pnlQuery.Visible := True;
  WorkView2.FieldByName('查询.标识').Data.SetInteger(0);
  WorkView2.FieldByName('查询.时间段名称').Data.SetString('');
  btnTimeQuery.Click;
end;

procedure TfaqhsetWeekTimeGroup.SpeedButton5Click(Sender: TObject);
begin
  iSelect := 6;
  pnlQuery.Visible := True;
  WorkView2.FieldByName('查询.标识').Data.SetInteger(0);
  WorkView2.FieldByName('查询.时间段名称').Data.SetString('');
  btnTimeQuery.Click;
end;

procedure TfaqhsetWeekTimeGroup.SpeedButton6Click(Sender: TObject);
begin
  iSelect := 7;
  pnlQuery.Visible := True;
  WorkView2.FieldByName('查询.标识').Data.SetInteger(0);
  WorkView2.FieldByName('查询.时间段名称').Data.SetString('');
  btnTimeQuery.Click;
end;

function TfaqhsetWeekTimeGroup.transLToB(instr: Integer): string;
begin
  case instr of
    1: Result := '周一组编号';
    2: Result := '周二组编号';
    3: Result := '周三组编号';
    4: Result := '周四组编号';
    5: Result := '周五组编号';
    6: Result := '周六组编号';
    7: Result := '周日组编号';
  end;
        
end;

procedure TfaqhsetWeekTimeGroup.btnTimeQueryClick(Sender: TObject);
begin
  if WVEdit9.Text='' then
    WorkView2.FieldByName('查询.标识').Data.SetInteger(0);
  //WorkView2.FieldByName('查询.时间段名称').Data.SetString('');
  WorkView2.FieldByName('交易类型').Data.SetString('R');
  WVRequest2.SendCommand;
end;

procedure TfaqhsetWeekTimeGroup.btnCancleClick(Sender: TObject);
begin
  pnlQuery.Visible:=False;
end;

procedure TfaqhsetWeekTimeGroup.btnSelectClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
begin
  tmpDataSet := TDataSet(WorkView2.FieldByName('查询结果集').Data.AsObject);
  if tmpDataSet = nil then
  begin
    ShowMessage('请先查询出结果，然后再选择！');
    Exit;
  end;
  case iSelect of
    1:begin
        WorkView.FieldByName(transLToB(1)).Data.SetInteger(tmpDataSet.fieldbyname('lcert_code').AsInteger);
        lbl1.Caption := tmpDataSet.fieldbyname('semail').AsString;
      end;
    2:begin
        WorkView.FieldByName(transLToB(2)).Data.SetInteger(tmpDataSet.fieldbyname('lcert_code').AsInteger);
        lbl2.Caption := tmpDataSet.fieldbyname('semail').AsString;
      end;
    3:begin
        WorkView.FieldByName(transLToB(3)).Data.SetInteger(tmpDataSet.fieldbyname('lcert_code').AsInteger);
        lbl3.Caption := tmpDataSet.fieldbyname('semail').AsString;
      end;
    4:begin
        WorkView.FieldByName(transLToB(4)).Data.SetInteger(tmpDataSet.fieldbyname('lcert_code').AsInteger);
        lbl4.Caption := tmpDataSet.fieldbyname('semail').AsString;
      end;
    5:begin
        WorkView.FieldByName(transLToB(5)).Data.SetInteger(tmpDataSet.fieldbyname('lcert_code').AsInteger);
        lbl5.Caption := tmpDataSet.fieldbyname('semail').AsString;
      end;
    6:begin
        WorkView.FieldByName(transLToB(6)).Data.SetInteger(tmpDataSet.fieldbyname('lcert_code').AsInteger);
        lbl6.Caption := tmpDataSet.fieldbyname('semail').AsString;
      end;
    7:begin
        WorkView.FieldByName(transLToB(7)).Data.SetInteger(tmpDataSet.fieldbyname('lcert_code').AsInteger);
        lbl7.Caption := tmpDataSet.fieldbyname('semail').AsString;
      end;
  end;

  pnlQuery.Visible := False;
end;

procedure TfaqhsetWeekTimeGroup.clearLabel;
var
  i:Integer;
begin
  for i := 0 to tsEdit.ControlCount-1 do
  begin
    if tsEdit.Controls[i] is TLabel then
      if TLabel(tsEdit.Controls[i]).Tag>0 then
        TLabel(tsEdit.Controls[i]).Caption := '';
  end;
end;

procedure TfaqhsetWeekTimeGroup.btnOKClick(Sender: TObject);
var
  i:Integer;
begin
  if Trim(edtName.Text)='' then
  begin
    ShowMessage('请输入周时间段名称！');
    edtName.SetFocus;
    Exit;
  end;
  for i := 0 to tsEdit.ControlCount-1 do
  begin
    if tsEdit.Controls[i] is TWVEdit then
      if (TWVEdit(tsEdit.Controls[i]).Text='') then
      begin
        ShowMessage('组编号均不能为空,但可以为零，请选择！');
        Exit;
      end;
  end;
  inherited;
  clearLabel;
  btnQuery.Click;
end;

procedure TfaqhsetWeekTimeGroup.btnQueryClick(Sender: TObject);
begin
  queryType('',WorkView);
  inherited;

end;

procedure TfaqhsetWeekTimeGroup.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('时间段组编号').Data.SetInteger(0);
  addType('',WorkView);
end;

procedure TfaqhsetWeekTimeGroup.btnChangeClick(Sender: TObject);
begin
  inherited;
  chargeType('',WorkView);
end;

procedure TfaqhsetWeekTimeGroup.btnDeleteClick(Sender: TObject);
begin
  inherited;
  deleteType('',WorkView);
end;

procedure TfaqhsetWeekTimeGroup.dbgrd1DblClick(Sender: TObject);
begin
  btnSelect.Click;

end;

function TfaqhsetWeekTimeGroup.getNameById(inId: Integer): string;
var
  tmpDataSet:TDataSet;
begin
  if inId=0 then
  begin
    Result := '';
    Exit;
  end;
  WorkView2.FieldByName('查询.标识').Data.SetInteger(inId);
  WorkView2.FieldByName('交易类型').Data.SetString('R');
  WVRequest2.SendCommand;
  tmpDataSet := TDataSet(WorkView2.FieldByName('查询结果集').Data.AsObject);
  Result := tmpDataSet.fieldbyname('semail').AsString;
end;

procedure TfaqhsetWeekTimeGroup.WVEdit1Change(Sender: TObject);
begin
  if WVEdit1.Text='' then
    Exit;
  try
    lbl1.Caption := getNameById(StrToInt(WVEdit1.Text));
  except
  end;
end;

procedure TfaqhsetWeekTimeGroup.WVEdit3Change(Sender: TObject);
begin
  if WVEdit3.Text='' then
    Exit;
  try
    lbl2.Caption := getNameById(StrToInt(WVEdit3.Text));
  except
  end;
end;

procedure TfaqhsetWeekTimeGroup.WVEdit4Change(Sender: TObject);
begin
  if WVEdit4.Text='' then
    Exit;
  try
    lbl3.Caption := getNameById(StrToInt(WVEdit4.Text));
  except
  end;
end;

procedure TfaqhsetWeekTimeGroup.WVEdit5Change(Sender: TObject);
begin
  if WVEdit5.Text='' then
    Exit;
  try
    lbl4.Caption := getNameById(StrToInt(WVEdit5.Text));
  except
  end;
end;

procedure TfaqhsetWeekTimeGroup.WVEdit6Change(Sender: TObject);
begin
  if WVEdit6.Text='' then
    Exit;
  try
    lbl5.Caption := getNameById(StrToInt(WVEdit6.Text));
  except
  end;
end;

procedure TfaqhsetWeekTimeGroup.WVEdit7Change(Sender: TObject);
begin
  if WVEdit7.Text='' then
    Exit;
  try
    lbl6.Caption := getNameById(StrToInt(WVEdit7.Text));
  except
  end;
end;

procedure TfaqhsetWeekTimeGroup.WVEdit8Change(Sender: TObject);
begin
  if WVEdit8.Text='' then
    Exit;
  try
    lbl7.Caption := getNameById(StrToInt(WVEdit8.Text));
  except
  end;
end;

procedure TfaqhsetWeekTimeGroup.btnCancelClick(Sender: TObject);
begin
  inherited;
  pnlQuery.Visible := False;
end;

procedure TfaqhsetWeekTimeGroup.GridDblClick(Sender: TObject);
begin
  //inherited;
end;

procedure TfaqhsetWeekTimeGroup.btnSet0Click(Sender: TObject);
begin
  case iSelect of
    1: begin
         WorkView.FieldByName(transLToB(1)).Data.SetInteger(0);
         lbl1.Caption := '';
       end;
    2: begin
        WorkView.FieldByName(transLToB(2)).Data.SetInteger(0);
        lbl2.Caption := '';
       end;
    3: begin
         WorkView.FieldByName(transLToB(3)).Data.SetInteger(0);
         lbl3.Caption := '';
       end;
    4: begin
         WorkView.FieldByName(transLToB(4)).Data.SetInteger(0);
         lbl4.Caption := '';
       end;
    5: begin
         WorkView.FieldByName(transLToB(5)).Data.SetInteger(0);
         lbl5.Caption := '';
       end;
    6: begin
         WorkView.FieldByName(transLToB(6)).Data.SetInteger(0);
         lbl6.Caption := '';
       end;
    7: begin
         WorkView.FieldByName(transLToB(7)).Data.SetInteger(0);
         lbl7.Caption := '';
       end;
       {
    8: begin
         WorkView.FieldByName(transLToB(8)).Data.SetInteger(0);
         lbl8.Caption := '';
       end;
       }
  end;
  pnlQuery.Visible := False;
end;

initialization
  TUIStdClassFactory.Create('周时间段参数设置',TfaqhsetWeekTimeGroup);

end.