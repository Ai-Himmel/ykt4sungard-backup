unit UCheckOutUser;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
  USimpleQueryTemp, UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids,
    StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, UIncrementComboBox, RzDBGrid, KCDataAccess,
  SmartCardCommon, WVCommands, UqhSetParamsTemp, DBActns, ActnList,
  DBCtrls, RzDBNav, RzButton, RzRadChk, RzTabs, USetParamsTemp, Buttons;

type
  TFrmCheckOutUser = class(TfaSetParamsTemp)
    Labeloper_code2: TLabel;
    edtOperCode: TWVEdit;
    Labelif_station9: TLabel;
    cbbStation: TWVComboBox;
    cbbStat: TWVComboBox;
    Labelif_access10: TLabel;
    Labeloper_name3: TLabel;
    edtOpername: TWVEdit;
    procedure btnChangeClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
  private
    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  FrmCheckOutUser: TFrmCheckOutUser;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
  KSClientConsts, KSDataDictionary, DataUsageUtils, UCommData;

{$R *.DFM}

procedure TFrmCheckOutUser.Init;
begin
  inherited;
end;

procedure TFrmCheckOutUser.btnChangeClick(Sender: TObject);
begin
  if DataSource.DataSet.FieldByName('scust_no').AsString = SuperOperator then
  begin
    Context.GetDialogSystem.ShowMessage('不允许将超级操作员强制签出！');
    Exit;
  end;
  inherited;
  edtOperCode.Enabled := False;
  edtOpername.Enabled := False;
  cbbStation.Enabled := False;
  cbbStat.Enabled := False;                                                                      
end;

procedure TFrmCheckOutUser.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('操作类别').Data.SetString('R');
  inherited;
  //
end;

procedure TFrmCheckOutUser.btnOKClick(Sender: TObject);
begin
  inherited;
  btnQueryClick(Sender);    
end;

initialization
  TUIStdClassFactory.Create('签出操作员', TFrmCheckOutUser);

end.
