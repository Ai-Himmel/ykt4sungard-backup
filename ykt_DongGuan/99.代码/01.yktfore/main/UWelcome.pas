unit UWelcome;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  Mask, WVCtrls, WVDBBinders, Db, 
  RzStatus, EditExts, RzEdit, Buttons, jpeg;

type
  TfaWelcome = class(TfaInputTemp)
    DataSource1: TDataSource;
    WVDBBinder1: TWVDBBinder;
    pnl1: TPanel;
    img1: TImage;
  private
    { Private declarations }
  protected
     procedure Init; override;
  public
    { Public declarations }
  end;

var
  faWelcome: TfaWelcome;
  OldMoney: string;

implementation
uses KsFrameworks, 
  KSClientConsts;

{$R *.DFM}

procedure TfaWelcome.Init;
begin
  inherited;
end;


initialization
  TUIStdClassFactory.Create('»¶Ó­Ò³Ãæ',TfaWelcome);

end.
