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
    //���ܺ�
    funcId : string;
    //�ֶ�����
    fieldName:string;
    //��ʾ����
    showName :string;
    //�Ƿ���ʾ
    ifshow:string;
    //��ʾ˳���
    showId:Integer;
    //�����
    gridWidth:Integer;
    //��ͷ���뷽ʽ
    titAlign:Integer;
    //��ͷ����
    titFont:string;
    //��ͷ�����С
    titFontSize:Integer;
    //��ͷ������ɫ
    titFontColor:string;
    //�����뷽ʽ
    gridAlign:Integer;
    //�������
    gridFont:string;
    //��������С
    gridFontSize:Integer;
    //���������ɫ
    gridFontColor:string;

    { Private declarations }
    //��ʼ��ʱ�ѵ�һ�����ݵ�ֵ��������
    procedure setValueToVar();
    //����¼�ƶ�ʱ�ж��Ƿ��޸���������¼��ֵ������޸�����ʾ�Ƿ񱣴�
    function ifChangeValue(): Boolean;
    //�ѵ�ǰ��¼��ֵ��ʾ���ɱ༭ҳ����ȥ
    procedure setValueToEdit();
    //�����޸Ĺ���ֵ
    procedure saveValueToDb();
    //Ԥ�������ʾ
    procedure previewGridShow();
    //��ʾ����ֶθı�����
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
  //WorkView.FieldByName('����').DefaultValue := '';
  WorkView.Reset;
  btnPrint.Caption:='&S����';
  btnpreview.Caption:='&PԤ��';
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhSetGridShow.ifChangeValue
  ����:      hanjiwei
  ����:      2006.07.14
  ����:      ��
  ����ֵ:    Boolean,�ı�ֵ����true�����򷵻�false
  ˵����     ����¼�ƶ�ʱ�ж��Ƿ��޸���������¼��ֵ������޸�����ʾ�Ƿ񱣴�
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
  ������:    TfaqhSetGridShow.previewGridShow
  ����:      hanjiwei
  ����:      2006.07.14
  ����:      ��
  ����ֵ:    ��
  ˵����     Ԥ�������ʾ
-------------------------------------------------------------------------------}
procedure TfaqhSetGridShow.previewGridShow;
begin

end;

{-------------------------------------------------------------------------------
  ������:    TfaqhSetGridShow.saveValueToDb
  ����:      hanjiwei
  ����:      2006.07.14
  ����:      ��
  ����ֵ:    ��
  ˵����     �����޸Ĺ���ֵ
-------------------------------------------------------------------------------}
procedure TfaqhSetGridShow.saveValueToDb;
var
  //���ܺ�
  dfuncId : string;
  //�ֶ�����
  dfieldName:string;
  //��ʾ����
  dshowName :string;
  //�Ƿ���ʾ
  difshow:string;
  //��ʾ˳���
  dshowId:Integer;
  //�����
  dgridWidth:Integer;
  //��ͷ���뷽ʽ
  dtitAlign:Integer;
  //��ͷ����
  dtitFont:string;
  //��ͷ�����С
  dtitFontSize:Integer;
  //��ͷ������ɫ
  dtitFontColor:string;
  //�����뷽ʽ
  dgridAlign:Integer;
  //�������
  dgridFont:string;
  //��������С
  dgridFontSize:Integer;
  //���������ɫ
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

  wvSave.FieldByName('���ܺ�').Data.SetString(dfuncId);
  wvSave.FieldByName('�ֶ���').Data.SetString(dfieldName);
  wvSave.FieldByName('��ʾ����').Data.SetString(dshowName);
  wvSave.FieldByName('�Ƿ���ʾ').Data.SetString(difshow);
  wvSave.FieldByName('��ʾ˳���').Data.SetInteger(dshowId);
  wvSave.FieldByName('�����').Data.SetInteger(dgridWidth);
  wvSave.FieldByName('��ͷ���뷽ʽ').Data.SetInteger(dtitAlign);
  wvSave.FieldByName('��ͷ����').Data.SetString(dtitFont);
  wvSave.FieldByName('��ͷ�����С').Data.SetInteger(dtitFontSize);
  wvSave.FieldByName('��ͷ������ɫ').Data.SetString(dtitFontColor);
  wvSave.FieldByName('�����뷽ʽ').Data.SetInteger(dgridAlign);
  wvSave.FieldByName('�������').Data.SetString(dgridFont);
  wvSave.FieldByName('��������С').Data.SetInteger(dgridFontSize);
  wvSave.FieldByName('���������ɫ').Data.SetString(dgridFontColor);
  wvRSave.SendCommand;
  if wvSave.FieldByName('������').Data.AsInteger<>0 then
    ShowMessage(wvSave.fieldbyname('������Ϣ').Data.AsString);
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhSetGridShow.setValueToEdit
  ����:      hanjiwei
  ����:      2006.07.14
  ����:      ��
  ����ֵ:    ��
  ˵����     �ѵ�ǰ��¼��ֵ��ʾ���ɱ༭ҳ����ȥ
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
  ������:    TfaqhSetGridShow.setValueToVar
  ����:      hanjiwei
  ����:      2006.07.14
  ����:      ��
  ����ֵ:    ��
  ˵����     ��ʼ��ʱ�ѵ�һ�����ݵ�ֵ��������
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
    if Application.MessageBox('���������Ѿ��ı䣬��ȷ��Ҫ������','��ʾ��Ϣ',MB_YESNO+mb_iconquestion)=idyes then
      saveValueToDb;

  setValueToEdit;
  setValueToVar;
end;

{-------------------------------------------------------------------------------
  ������:    TfaqhSetGridShow.ifShowGridChange
  ����:      hanjiwei
  ����:      2006.07.14
  ����:      ��
  ����ֵ:    Boolean
  ˵��:      �����ʾ�Ƿ�ı�ֵ���ı䷵��true�����ı䷵��false
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
  TUIStdClassFactory.Create('�����ʾ����',TfaqhSetGridShow);

end.