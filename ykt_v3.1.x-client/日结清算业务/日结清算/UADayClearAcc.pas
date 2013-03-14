unit UADayClearAcc;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  Buttons;

type
  TfaDayClearAcc = class(TfaInputTemp)
    procedure btnOKClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  faDayClearAcc: TfaDayClearAcc;

implementation
uses ksframeworks,KSClientConsts;

{$R *.DFM}
procedure TfaDayClearAcc.btnOKClick(Sender: TObject);
begin
  WorkView.FieldByName('操作员代码').Data.SetString(Context.ParamData(svOperatorNoName).AsString);
  WorkView.SynchronizeCtrlsToFields;
  inherited;
end;

initialization
  TUIStdClassFactory.Create('手动日结',TfaDayClearAcc);

end.
