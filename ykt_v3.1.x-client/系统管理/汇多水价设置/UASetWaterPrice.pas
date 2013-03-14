unit UASetWaterPrice;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, EditExts, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, ComCtrls,WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  RzDBNav, RzDBGrid, RzButton, RzRadChk, Buttons, RzTabs,
  UIncrementComboBox;

type
  TfaqhSetWaterPrice = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    cbbFee: TWVComboBox;
    cbbFeeType: TWVComboBox;
    edtP3: TWVEdit;
    edtP2: TWVEdit;
    edtP1: TWVEdit;
    Label1: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    procedure btnQueryClick(Sender: TObject);
    procedure btnAddClick(Sender: TObject);
    procedure btnChangeClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetWaterPrice: TfaqhSetWaterPrice;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhSetWaterPrice.Init;
begin
  inherited;
  {
  WorkView.FieldByName('查询.操作标志').DefaultValue := '';
  WorkView.FieldByName('查询.收费类别').DefaultValue := 0;
  WorkView.FieldByName('查询.水价1').DefaultValue := 0;
  WorkView.FieldByName('查询.水价2').DefaultValue := 0;
  WorkView.FieldByName('查询.水价3').DefaultValue := 0;
  WorkView.FieldByName('收费类别').DefaultValue := 0;
  WorkView.FieldByName('水价1').DefaultValue := 0;
  WorkView.FieldByName('水价2').DefaultValue := 0;
  WorkView.FieldByName('水价3').DefaultValue := 0;
  WorkView.Reset;
  }
end;

procedure TfaqhSetWaterPrice.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('操作标志').Data.SetString('R');
  inherited;

end;

procedure TfaqhSetWaterPrice.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('A');
end;

procedure TfaqhSetWaterPrice.btnChangeClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('U');
end;

procedure TfaqhSetWaterPrice.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('操作标志').Data.SetString('D');
end;

procedure TfaqhSetWaterPrice.btnOKClick(Sender: TObject);
var
  feeType:string;
begin
  feeType := Copy(cbbFeeType.Text,1,Pos('-',cbbFeeType.Text)-1);
  if (feeType='') or (feeType='-') then
  begin
    Context.GetDialogSystem.ShowMessage('请选择要设置的收费类别！');
    Exit;
  end;
  if Trim(edtP3.Text)='' then
    edtP3.Text := '0';
  if Trim(edtP2.Text)='' then
    edtP2.Text := '0';
  if Trim(edtP1.Text)='' then
    edtP1.Text := '0';
  inherited;
  btnQueryClick(Sender);
end;

initialization
  TUIStdClassFactory.Create('脱机水价设置',TfaqhSetWaterPrice);

end.