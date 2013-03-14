unit UAsetTimeGroup;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, 
  RzDBNav, RzDBGrid, RzButton, RzRadChk, RzTabs, UIncrementComboBox,
  RzPanel, RzGrids, Buttons;

type
  TfaqhsetTimeGroup = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label6: TLabel;
	WVEdit1: TWVEdit;
    WVDigitalEdit2: TWVDigitalEdit;
    edtName: TWVEdit;
    Label3: TLabel;
    edtNo: TWVDigitalEdit;
    Label7: TLabel;
    rbTimeSet: TRzGroupBox;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    lblTime1: TLabel;
    lblTime2: TLabel;
    lblTime3: TLabel;
    lblTime4: TLabel;
    lblTime5: TLabel;
    lblTime6: TLabel;
    lblTime7: TLabel;
    lblTime8: TLabel;
    edtTime1: TWVEdit;
    edtTime2: TWVEdit;
    edtTime3: TWVEdit;
    edtTime4: TWVEdit;
    edtTime5: TWVEdit;
    edtTime6: TWVEdit;
    edtTime7: TWVEdit;
    edtTime8: TWVEdit;
    btn1: TSpeedButton;
    btn2: TSpeedButton;
    btn3: TSpeedButton;
    btn4: TSpeedButton;
    btn5: TSpeedButton;
    btn6: TSpeedButton;
    btn7: TSpeedButton;
    btn8: TSpeedButton;
    pnlQuery: TPanel;
    Label16: TLabel;
    WVEdit2: TWVEdit;
    pnl1: TPanel;
    btnTimeQuery: TBitBtn;
    btnSelect: TBitBtn;
    WVRequest1: TWVRequest;
    WorkView1: TWorkView;
    DataSource1: TDataSource;
    btnCancle: TBitBtn;
    dbgrd1: TDBGrid;
    btnSet0: TBitBtn;
    WVDBBinder1: TWVDBBinder;
    pnl2: TPanel;
    RzDBGrid1: TRzDBGrid;
    WorkView2: TWorkView;
    WVRequest2: TWVRequest;
    DataSource2: TDataSource;
    WVDBBinder: TWVDBBinder;
    btnClose: TBitBtn;
    Label4: TLabel;
    WVEdit5: TWVEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure WorkViewFieldsMonitors1ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnTimeQueryClick(Sender: TObject);
    procedure btn1Click(Sender: TObject);
    procedure btn2Click(Sender: TObject);
    procedure btn3Click(Sender: TObject);
    procedure btn4Click(Sender: TObject);
    procedure btn5Click(Sender: TObject);
    procedure btn6Click(Sender: TObject);
    procedure btn7Click(Sender: TObject);
    procedure btn8Click(Sender: TObject);
    procedure btnSelectClick(Sender: TObject);
    procedure btnCancleClick(Sender: TObject);
    procedure dbgrd1DblClick(Sender: TObject);
    procedure btnSet0Click(Sender: TObject);
    procedure btnCloseClick(Sender: TObject);
    procedure btnViewDetailClick(Sender: TObject);
    procedure GridDblClick(Sender: TObject);
    procedure RzDBGrid1DrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
    procedure btnCancelClick(Sender: TObject);
  private

    { Private declarations }
    operatorNoName : string;
    iSelectTime:Integer;
    procedure queryTimeDetail(iTag:Integer) ;
    function trancLtoB(inData:Integer):string;
    procedure clearLabel;
    procedure setEdtReadOnly;

    procedure getTimeDetail;

    procedure setQueryCon;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhsetTimeGroup: TfaqhsetTimeGroup;

implementation

uses KsFrameworks, 
     KSClientConsts, gateComm;
     
{$R *.DFM}

procedure TfaqhsetTimeGroup.Init;
begin
  inherited;
  {
  WorkView.FieldByName('查询.时间段名称').DefaultValue := '';
  WorkView.FieldByName('查询.标识').DefaultValue := 0;
  WorkView.FieldByName('交易类型').DefaultValue := '';
  WorkView.FieldByName('时间段名称').DefaultValue := '';
  WorkView.FieldByName('标识').DefaultValue := 0;
  WorkView.FieldByName('时间段一').DefaultValue := 0;
  WorkView.FieldByName('时间段二').DefaultValue := 0;
  WorkView.FieldByName('时间段三').DefaultValue := 0;
  WorkView.FieldByName('时间段四').DefaultValue := 0;
  WorkView.FieldByName('时间段五').DefaultValue := 0;
  WorkView.FieldByName('时间段六').DefaultValue := 0;
  WorkView.FieldByName('时间段七').DefaultValue := 0;
  WorkView.FieldByName('时间段八').DefaultValue := 0;
  WorkView.Reset;
  }
  OperatorNoName := Context.ParamData(svOperatorNoName).AsString;
  btnTimeQuery.Caption := '查　询';
  btnSelect.Caption := '选　择';
  btnOK.Caption :='保存设置';
  btnCancle.Caption := '取　消';
  btnSet0.Caption := '置  零';
  btnClose.Caption := '&C 关闭';
end;

procedure TfaqhsetTimeGroup.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;


procedure TfaqhsetTimeGroup.WorkViewFieldsMonitors1ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnOk.Enabled:=Valid;
end;

procedure TfaqhsetTimeGroup.btnDeleteClick(Sender: TObject);
begin
  inherited;
  edtNo.ReadOnly := True;
  deleteType(operatorNoName,WorkView);
end;

procedure TfaqhsetTimeGroup.btnChangeClick(Sender: TObject);
begin
  inherited;
  edtNo.ReadOnly := True;
  setEdtReadOnly;
  chargeType(operatorNoName,WorkView);
  getTimeDetail;
end;

procedure TfaqhsetTimeGroup.btnQueryClick(Sender: TObject);
begin
  queryType(operatorNoName,WorkView);
  inherited;
end;

procedure TfaqhsetTimeGroup.btnAddClick(Sender: TObject);
begin
  inherited;
  setEdtReadOnly;
  edtNo.ReadOnly := True;
  WorkView.FieldByName('标识').Data.SetInteger(0);
  addType(operatorNoName,WorkView);
  getTimeDetail;
end;

procedure TfaqhsetTimeGroup.btnOKClick(Sender: TObject);
begin
  if edtName.Text='' then
  begin
    ShowMessage('请输入时间段组名称！');
    Exit;
  end;
  inherited;
  clearLabel;
  pnlQuery.Visible := False;
  btnQuery.Click;
end;

procedure TfaqhsetTimeGroup.btnTimeQueryClick(Sender: TObject);
begin
  if WVEdit5.Text='' then
    WorkView1.FieldByName('查询.标识').Data.SetInteger(0);
  WorkView1.FieldByName('交易类型').Data.SetString('R');
  WVRequest1.SendCommand;
end;

procedure TfaqhsetTimeGroup.queryTimeDetail(iTag: Integer);
var
  i , j: Integer;
  timeId : Integer;
  timeText : string;
  tmpDataSet : TDataSet;
begin
  timeId := 0;
  for i := 0 to rbTimeSet.ControlCount-1 do
  begin
    if rbTimeSet.Controls[i] is TWVComboBox then
      if TWVComboBox(rbTimeSet.Controls[i]).Tag = iTag then
      begin
        timeText := TWVComboBox(rbTimeSet.Controls[i]).Text;
        timeId := StrToInt(Copy(timeText,1,Pos('-',timeText)-1));
        Break;
      end;
  end;
  WorkView1.FieldByName('查询.标识').Data.SetInteger(timeId);
  WorkView1.FieldByName('交易类型').Data.SetString('R');
  WVRequest1.SendCommand;
  tmpDataSet := TDataSet(WorkView1.FieldByName('查询结果集').Data.AsObject);
  if tmpDataSet.IsEmpty then
    Exit;
  for j := 0 to rbTimeSet.ControlCount-1 do
  begin
    if rbTimeSet.Controls[i] is TLabel then
      if TLabel(rbTimeSet.Controls[i]).Tag = iTag then
        TLabel(rbTimeSet.Controls[i]).Caption := '时间范围：'
          +tmpDataSet.fieldbyname('sdate0').AsString
          + tmpDataSet.fieldbyname('sdate1').AsString;
  end;
end;

procedure TfaqhsetTimeGroup.btn1Click(Sender: TObject);
begin
  iSelectTime := 1;
  pnlQuery.Visible := True;
  setQueryCon;
end;

procedure TfaqhsetTimeGroup.btn2Click(Sender: TObject);
begin
  iSelectTime := 2;
  pnlQuery.Visible := True;
  setQueryCon;
end;

procedure TfaqhsetTimeGroup.btn3Click(Sender: TObject);
begin
  iSelectTime := 3;
  pnlQuery.Visible := True;
  setQueryCon;
end;

procedure TfaqhsetTimeGroup.btn4Click(Sender: TObject);
begin
  iSelectTime := 4;
  pnlQuery.Visible := True;
  setQueryCon;
end;

procedure TfaqhsetTimeGroup.btn5Click(Sender: TObject);
begin
  iSelectTime := 5;
  pnlQuery.Visible := True;
  setQueryCon;
end;

procedure TfaqhsetTimeGroup.btn6Click(Sender: TObject);
begin
  iSelectTime := 6;
  pnlQuery.Visible := True;
  setQueryCon;
end;

procedure TfaqhsetTimeGroup.btn7Click(Sender: TObject);
begin
  iSelectTime := 7;
  pnlQuery.Visible := True;
  setQueryCon;
end;

procedure TfaqhsetTimeGroup.btn8Click(Sender: TObject);
begin
  iSelectTime := 8;
  pnlQuery.Visible := True;
  setQueryCon;
end;

procedure TfaqhsetTimeGroup.btnSelectClick(Sender: TObject);
var
  tmpDataSet:TDataSet;
  beginTime,endTime,conTime:string;
begin
  tmpDataSet := TDataSet(WorkView1.FieldByName('查询结果集').Data.AsObject);
  if tmpDataSet = nil then
  begin
    ShowMessage('请先查询出结果，然后再选择！');
    Exit;
  end;
  beginTime:=tmpDataSet.fieldbyname('sdate0').AsString;
  endTime:=tmpDataSet.fieldbyname('sdate1').AsString;
  conTime:='开始时间:'+beginTime+'  结束时间:'+endTime;
  case iSelectTime of
    1: begin
         WorkView.FieldByName(trancLtoB(1)).Data.SetInteger(tmpDataSet.fieldbyname('lvol0').AsInteger);
         lblTime1.Caption := conTime;
       end;
    2: begin
        WorkView.FieldByName(trancLtoB(2)).Data.SetInteger(tmpDataSet.fieldbyname('lvol0').AsInteger);
        lblTime2.Caption := conTime;
       end;
    3: begin
         WorkView.FieldByName(trancLtoB(3)).Data.SetInteger(tmpDataSet.fieldbyname('lvol0').AsInteger);
         lblTime3.Caption := conTime;
       end;
    4: begin
         WorkView.FieldByName(trancLtoB(4)).Data.SetInteger(tmpDataSet.fieldbyname('lvol0').AsInteger);
         lblTime4.Caption := conTime;
       end;
    5: begin
         WorkView.FieldByName(trancLtoB(5)).Data.SetInteger(tmpDataSet.fieldbyname('lvol0').AsInteger);
         lblTime5.Caption := conTime;
       end;
    6: begin
         WorkView.FieldByName(trancLtoB(6)).Data.SetInteger(tmpDataSet.fieldbyname('lvol0').AsInteger);
         lblTime6.Caption := conTime;
       end;
    7: begin
         WorkView.FieldByName(trancLtoB(7)).Data.SetInteger(tmpDataSet.fieldbyname('lvol0').AsInteger);
         lblTime7.Caption := conTime;
       end;
    8: begin
         WorkView.FieldByName(trancLtoB(8)).Data.SetInteger(tmpDataSet.fieldbyname('lvol0').AsInteger);
         lblTime8.Caption := conTime;
       end;
  end;
  pnlQuery.Visible := False;
end;

procedure TfaqhsetTimeGroup.btnCancleClick(Sender: TObject);
begin
  pnlQuery.Visible := False;

end;

function TfaqhsetTimeGroup.trancLtoB(inData: Integer): string;
begin
  case inData of
    1: Result := '时间段一';
    2: Result := '时间段二';
    3: Result := '时间段三';
    4: Result := '时间段四';
    5: Result := '时间段五';
    6: Result := '时间段六';
    7: Result := '时间段七';
    8: Result := '时间段八';
  end;
end;

procedure TfaqhsetTimeGroup.clearLabel;
var
  i:Integer;
begin
  for i :=0  to rbTimeSet.ControlCount-1 do
  begin
    if rbTimeSet.Controls[i] is TLabel then
      if TLabel(rbTimeSet.Controls[i]).Tag>0 then
         TLabel(rbTimeSet.Controls[i]).Caption := '';
  end;
end;

procedure TfaqhsetTimeGroup.setEdtReadOnly;
var
  i:Integer;
begin
  for i :=0  to rbTimeSet.ControlCount-1 do
  begin
    if rbTimeSet.Controls[i] is TWVEdit then
      TWVEdit(rbTimeSet.Controls[i]).ReadOnly := True;
  end;
end;

procedure TfaqhsetTimeGroup.dbgrd1DblClick(Sender: TObject);
begin
  btnSelect.Click;
end;

procedure TfaqhsetTimeGroup.btnSet0Click(Sender: TObject);
begin
  case iSelectTime of
    1: begin
         WorkView.FieldByName(trancLtoB(1)).Data.SetInteger(0);
         lblTime1.Caption := '';
       end;
    2: begin
        WorkView.FieldByName(trancLtoB(2)).Data.SetInteger(0);
        lblTime2.Caption := '';
       end;
    3: begin
         WorkView.FieldByName(trancLtoB(3)).Data.SetInteger(0);
         lblTime3.Caption := '';
       end;
    4: begin
         WorkView.FieldByName(trancLtoB(4)).Data.SetInteger(0);
         lblTime4.Caption := '';
       end;
    5: begin
         WorkView.FieldByName(trancLtoB(5)).Data.SetInteger(0);
         lblTime5.Caption := '';
       end;
    6: begin
         WorkView.FieldByName(trancLtoB(6)).Data.SetInteger(0);
         lblTime6.Caption := '';
       end;
    7: begin
         WorkView.FieldByName(trancLtoB(7)).Data.SetInteger(0);
         lblTime7.Caption := '';
       end;
    8: begin
         WorkView.FieldByName(trancLtoB(8)).Data.SetInteger(0);
         lblTime8.Caption := '';
       end;
  end;
  pnlQuery.Visible := False;
end;

procedure TfaqhsetTimeGroup.btnCloseClick(Sender: TObject);
begin
  pnl2.Visible := false;

end;

procedure TfaqhsetTimeGroup.btnViewDetailClick(Sender: TObject);
var
  vol1:Integer;
begin
  //inherited;
  if DataSource.DataSet.IsEmpty then
    Exit;
  vol1 := DataSource.DataSet.fieldbyname('lcert_code').AsInteger;
  WorkView2.FieldByName('时间段组编号').Data.SetInteger(vol1);
  WorkView2.FieldByName('星期').Data.SetInteger(0);
  WVRequest2.SendCommand;
  pnl2.Visible := True;
end;

procedure TfaqhsetTimeGroup.GridDblClick(Sender: TObject);
begin
  //inherited;

end;

procedure TfaqhsetTimeGroup.RzDBGrid1DrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

procedure TfaqhsetTimeGroup.getTimeDetail;
var
  i,iTag,k:Integer;
  iText:Integer;
  tmpDataSet:TDataSet;
  beginTime,endTime,conTime:string;
begin
  for k :=0  to rbTimeSet.ControlCount-1 do
    if rbTimeSet.Controls[k] is TLabel then
        TLabel(rbTimeSet.Controls[k]).Caption := '';
        
  for i := 0 to rbTimeSet.ControlCount-1 do
  begin
    if rbTimeSet.Controls[i] is TWVEdit then
    begin
      iText := StrToInt(TWVEdit(rbTimeSet.Controls[i]).Text);
      iTag := TWVEdit(rbTimeSet.Controls[i]).Tag;
      if iText>0 then
      begin
        WorkView1.FieldByName('查询.标识').Data.SetInteger(iText);
        WorkView1.FieldByName('交易类型').Data.SetString('R');
        WVRequest1.SendCommand;
        tmpDataSet := TDataSet(WorkView1.FieldByName('查询结果集').Data.AsObject);
        if tmpDataSet.IsEmpty then
          Continue;
        beginTime:=tmpDataSet.fieldbyname('sdate0').AsString;
        endTime:=tmpDataSet.fieldbyname('sdate1').AsString;
        conTime:='开始时间:'+beginTime+'  结束时间:'+endTime;
        //lblTime1.Caption := conTime;
        for k := 0 to rbTimeSet.ControlCount-1 do
        begin
          if rbTimeSet.Controls[k] is TLabel then
            if TLabel(rbTimeSet.Controls[k]).Tag = iTag then
              TLabel(rbTimeSet.Controls[k]).Caption := conTime;
        end;
      end;
    end;
  end;
end;

procedure TfaqhsetTimeGroup.setQueryCon;
begin
  WorkView1.FieldByName('查询.标识').Data.SetInteger(0);
  WorkView1.FieldByName('查询.时间段名称').Data.SetString('');
  WorkView1.FieldByName('查询.开始时间').Data.SetString('');
  WorkView1.FieldByName('查询.结束时间').Data.SetString('');
  btnTimeQuery.Click;
end;

procedure TfaqhsetTimeGroup.btnCancelClick(Sender: TObject);
begin
  inherited;
  pnlQuery.Visible := False;
end;

initialization
  TUIStdClassFactory.Create('时间段组设置',TfaqhsetTimeGroup);

end.