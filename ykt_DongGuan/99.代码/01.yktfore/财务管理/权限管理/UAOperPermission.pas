unit UAOperPermission;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSetParamsTemp, WVCtrls, StdCtrls, Mask, DBActns, ActnList,
  WorkViews, WVDBBinders, WVCmdReq, Db, DBCtrls, Grids, DBGrids,
  ImageCtrls, ExtCtrls, UICtrls, WVCmdProc, KCWVProcBinds, 
  RzDBNav, RzButton, RzRadChk, RzDBGrid, RzTabs, Buttons,
  UIncrementComboBox;

type
  TfaqhOperPermission = class(TfaqhSetParamsTemp)
    Panel1: TPanel;
    Label1: TLabel;
    WVLabel1: TWVLabel;
    cbbVoucherType: TWVComboBox;
    WVComboBox1: TWVComboBox;
    Label2: TLabel;
    cbbOperNo: TWVComboBox;
    WVLabel2: TWVLabel;
    cbbLimit: TWVComboBox;
    procedure btnAddClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhOperPermission: TfaqhOperPermission;

implementation

uses KsFrameworks, KSDataDictionary;
     
{$R *.DFM}

procedure TfaqhOperPermission.Init;
begin
  inherited;
end;

procedure TfaqhOperPermission.btnAddClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('标志').Data.SetString('A');
end;

procedure TfaqhOperPermission.btnDeleteClick(Sender: TObject);
begin
  inherited;
  WorkView.FieldByName('标志').Data.SetString('D');
end;

procedure TfaqhOperPermission.btnOKClick(Sender: TObject);
begin
  if (trim(cbbOperNo.text)='') or (trim(cbbOperNo.text)='-') then
  begin
    Context.GetDialogSystem.ShowWarning('请选择操作员！');
    cbbOperNo.SetFocus;
    Exit;
  end;
  if (trim(cbbLimit.text)='') or (trim(cbbLimit.text)='-') then
  begin
    Context.GetDialogSystem.ShowWarning('请选择权限类别！');
    cbbLimit.SetFocus;
    Exit;
  end;
  inherited;
  btnQuery.Click;
end;

procedure TfaqhOperPermission.btnQueryClick(Sender: TObject);
begin
  WorkView.FieldByName('标志').Data.SetString('R');
  inherited;

end;

initialization
  TUIStdClassFactory.Create('权限管理',TfaqhOperPermission);

end.