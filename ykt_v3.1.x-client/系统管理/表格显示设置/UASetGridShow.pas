unit UASetGridShow;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, RzPanel, RzSplit,  RzEdit, RzCmboBx,
  RzButton, RzRadChk, Buttons;

type
  TfaqhSetGridShow = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Panel2: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    WVEdit1: TWVEdit;
    Label3: TLabel;
    WVEdit2: TWVEdit;
    Pnl1: TRzSizePanel;
    lbl1: TLabel;
    lbl2: TLabel;
    lbl3: TLabel;
    lbl4: TLabel;
    lbl5: TLabel;
    lbl6: TLabel;
    lbl7: TLabel;
    lbl8: TLabel;
    lbl9: TLabel;
    lbl11: TLabel;
    lbl12: TLabel;
    lbl13: TLabel;
    lbl14: TLabel;
    edtFieldName: TRzEdit;
    edtShowName: TRzEdit;
    cbbTitAlign: TRzComboBox;
    FontCbbTitFont: TRzFontComboBox;
    NumEdtTitFontSize: TRzNumericEdit;
    ColorcbbTitFont: TRzColorComboBox;
    cbbGridAlign: TRzComboBox;
    FontCbbGridFont: TRzFontComboBox;
    NumEdtGridFontSize: TRzNumericEdit;
    ColorcbbGridFontColor: TRzColorComboBox;
    NumEdtShowWidth: TRzNumericEdit;
    NumEdtShowID: TRzNumericEdit;
    chkIfShow: TRzCheckBox;
    lbl10: TLabel;
    edtFuncNo: TRzEdit;
    Pnl2: TRzSizePanel;
    gridpreview: TRzDBGrid;
    btnpreview: TBitBtn;
    chkAutoSave: TRzCheckBox;
    wvSave: TWorkView;
    wvRSave: TWVRequest;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure GridCellClick(Column: TColumn);
  private
    //功能号
    funcId : string;
    //字段名称
    fieldName:string;
    //显示名称
    showName :string;
    //是否显示
    ifshow:string;
    //显示顺序号
    showId:Integer;
    //表格宽度
    gridWidth:Integer;
    //表头对齐方式
    titAlign:Integer;
    //表头字体
    titFont:string;
    //表头字体大小
    titFontSize:Integer;
    //表头字体颜色
    titFontColor:string;
    //表格对齐方式
    gridAlign:Integer;
    //表格字体
    gridFont:string;
    //表格字体大小
    gridFontSize:Integer;
    //表格字体颜色
    gridFontColor:string;

    { Private declarations }
    //初始化时把第一条数据的值赋给变量
    procedure setValueToVar();
    //当记录移动时判断是否修改了上条记录的值，如果修改了提示是否保存
    function ifChangeValue(): Boolean;
    //把当前记录的值显示到可编辑页面上去
    procedure setValueToEdit();
    //保存修改过的值
    procedure saveValueToDb();
    //预览表格显示
    procedure previewGridShow();
    //显示表格字段改变内容
    function ifShowGridChange: Boolean;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetGridShow: TfaqhSetGridShow;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhSetGridShow.Init;
begin
  inherited;
  //WorkView.FieldByName('姓名').DefaultValue := '';
  WorkView.Reset;
  btnPrint.Caption:='&S保存';
  btnpreview.Caption:='&P预览';
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhSetGridShow.ifChangeValue
  作者:      hanjiwei
  日期:      2006.07.14
  参数:      无
  返回值:    Boolean,改变值返回true，否则返回false
  说明：     当记录移动时判断是否修改了上条记录的值，如果修改了提示是否保存
-------------------------------------------------------------------------------}
function TfaqhSetGridShow.ifChangeValue: Boolean;
begin
  if (funcId<>Trim(edtFuncNo.Text)) or
     (fieldName<>Trim(edtFieldName.Text)) or
     (showName<>Trim(edtShowName.Text)) or
     (ifShowGridChange) or
     (showId<>NumEdtShowID.Value) or
     (gridWidth<>NumEdtShowWidth.Value) or
     (titAlign<>cbbTitAlign.ItemIndex) or
     (titFont<>FontCbbTitFont.FontName)or
     (titFontSize<>NumEdtTitFontSize.Value)or
     (titFontColor<>ColorToString(ColorcbbTitFont.SelectedColor))or
     (gridAlign<>cbbGridAlign.ItemIndex)or
     (gridFont<>FontCbbGridFont.FontName)or
     (gridFontSize<>NumEdtGridFontSize.Value)or
     (gridFontColor<>ColorToString(ColorcbbGridFontColor.SelectedColor)) then
      Result := True
  else
    Result := False;
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhSetGridShow.previewGridShow
  作者:      hanjiwei
  日期:      2006.07.14
  参数:      无
  返回值:    无
  说明：     预览表格显示
-------------------------------------------------------------------------------}
procedure TfaqhSetGridShow.previewGridShow;
begin

end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhSetGridShow.saveValueToDb
  作者:      hanjiwei
  日期:      2006.07.14
  参数:      无
  返回值:    无
  说明：     保存修改过的值
-------------------------------------------------------------------------------}
procedure TfaqhSetGridShow.saveValueToDb;
var
  //功能号
  dfuncId : string;
  //字段名称
  dfieldName:string;
  //显示名称
  dshowName :string;
  //是否显示
  difshow:string;
  //显示顺序号
  dshowId:Integer;
  //表格宽度
  dgridWidth:Integer;
  //表头对齐方式
  dtitAlign:Integer;
  //表头字体
  dtitFont:string;
  //表头字体大小
  dtitFontSize:Integer;
  //表头字体颜色
  dtitFontColor:string;
  //表格对齐方式
  dgridAlign:Integer;
  //表格字体
  dgridFont:string;
  //表格字体大小
  dgridFontSize:Integer;
  //表格字体颜色
  dgridFontColor:string;
begin
  dfuncId := Trim(edtFuncNo.Text);
  dfieldName := Trim(edtFieldName.Text);
  dshowName := Trim(edtShowName.Text);
  if chkIfShow.Checked then
    difshow:='1'
  else
    difshow:='0';
  dshowId := NumEdtShowID.IntValue;
  dgridWidth := NumEdtShowWidth.IntValue;
  dtitAlign := cbbTitAlign.ItemIndex;
  dtitFont := FontCbbTitFont.FontName;
  dtitFontSize := NumEdtTitFontSize.IntValue;
  dtitFontColor := ColorToString(ColorcbbTitFont.SelectedColor);
  dgridAlign := cbbGridAlign.ItemIndex;
  dgridFont := FontCbbGridFont.FontName;
  dgridFontSize := NumEdtGridFontSize.IntValue;
  dgridFontColor := ColorToString(ColorcbbGridFontColor.SelectedColor);

  wvSave.FieldByName('功能号').Data.SetString(dfuncId);
  wvSave.FieldByName('字段名').Data.SetString(dfieldName);
  wvSave.FieldByName('显示名称').Data.SetString(dshowName);
  wvSave.FieldByName('是否显示').Data.SetString(difshow);
  wvSave.FieldByName('显示顺序号').Data.SetInteger(dshowId);
  wvSave.FieldByName('表格宽度').Data.SetInteger(dgridWidth);
  wvSave.FieldByName('表头对齐方式').Data.SetInteger(dtitAlign);
  wvSave.FieldByName('表头字体').Data.SetString(dtitFont);
  wvSave.FieldByName('表头字体大小').Data.SetInteger(dtitFontSize);
  wvSave.FieldByName('表头字体颜色').Data.SetString(dtitFontColor);
  wvSave.FieldByName('表格对齐方式').Data.SetInteger(dgridAlign);
  wvSave.FieldByName('表格字体').Data.SetString(dgridFont);
  wvSave.FieldByName('表格字体大小').Data.SetInteger(dgridFontSize);
  wvSave.FieldByName('表格字体颜色').Data.SetString(dgridFontColor);
  wvRSave.SendCommand;
  if wvSave.FieldByName('返回码').Data.AsInteger<>0 then
    ShowMessage(wvSave.fieldbyname('返回信息').Data.AsString);
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhSetGridShow.setValueToEdit
  作者:      hanjiwei
  日期:      2006.07.14
  参数:      无
  返回值:    无
  说明：     把当前记录的值显示到可编辑页面上去
-------------------------------------------------------------------------------}
procedure TfaqhSetGridShow.setValueToEdit;
begin
  with Grid.DataSource.DataSet do
  begin
    edtFuncNo.Text := fieldbyname('').AsString;
    edtFieldName.Text := fieldbyname('').AsString;
    edtShowName.Text  := fieldbyname('').AsString;
    chkIfShow.Checked := fieldbyname('').AsBoolean;
    NumEdtShowID.Value := fieldbyname('').AsInteger;
    NumEdtShowWidth.Value := fieldbyname('').AsInteger;
    cbbTitAlign.ItemIndex := fieldbyname('').AsInteger;
    FontCbbTitFont.FontName := fieldbyname('').AsString;
    NumEdtTitFontSize.Value := fieldbyname('').AsInteger;
    ColorcbbTitFont.Color := StringToColor(fieldbyname('').AsString);
    cbbGridAlign.ItemIndex := fieldbyname('').AsInteger;
    FontCbbGridFont.FontName := fieldbyname('').AsString;
    NumEdtGridFontSize.Value := fieldbyname('').AsInteger;
    ColorcbbGridFontColor.Color := StringToColor(fieldbyname('').AsString);
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhSetGridShow.setValueToVar
  作者:      hanjiwei
  日期:      2006.07.14
  参数:      无
  返回值:    无
  说明：     初始化时把第一条数据的值赋给变量
-------------------------------------------------------------------------------}
procedure TfaqhSetGridShow.setValueToVar;
begin
  with Grid.DataSource.DataSet do
  begin
    funcId := fieldbyname('').AsString;
    fieldName := fieldbyname('').AsString;
    showName  := fieldbyname('').AsString;
    ifshow := fieldbyname('').AsString;
    showId := fieldbyname('').AsInteger;
    gridWidth := fieldbyname('').AsInteger;
    titAlign := fieldbyname('').AsInteger;
    titFont := fieldbyname('').AsString;
    titFontSize := fieldbyname('').AsInteger;
    titFontColor := fieldbyname('').AsString;
    gridAlign := fieldbyname('').AsInteger;
    gridFont := fieldbyname('').AsString;
    gridFontSize := fieldbyname('').AsInteger;
    gridFontColor := fieldbyname('').AsString;
  end;

end;

procedure TfaqhSetGridShow.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhSetGridShow.GridCellClick(Column: TColumn);
begin
  inherited;
  if chkautosave.Checked and ifChangeValue then
    saveValueToDb;

  if (not chkAutoSave.Checked) and ifChangeValue then
    if Application.MessageBox('上条数据已经改变，你确定要保存吗？','提示信息',MB_YESNO+mb_iconquestion)=idyes then
      saveValueToDb;

  setValueToEdit;
  setValueToVar;
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhSetGridShow.ifShowGridChange
  作者:      hanjiwei
  日期:      2006.07.14
  参数:      无
  返回值:    Boolean
  说明:      表格显示是否改变值，改变返回true，不改变返回false
-------------------------------------------------------------------------------}
function TfaqhSetGridShow.ifShowGridChange: Boolean;
var
  ss:string;
begin
  if chkIfShow.Checked then
    ss:='1'
  else
    ss:='0';
  if ss<>ifshow then
    Result := True
  else
    Result := False;
end;

initialization
  TUIStdClassFactory.Create('表格显示设置',TfaqhSetGridShow);

end.