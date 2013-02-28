unit KSCmdModules;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSCmdModules
   <What>�������������������������ģ�顣�����Զ�ע�ᡣ
   <Written By> Huang YanLai (������)
   <History>
**********************************************}


interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  WVCmdProc, KCWVProcBinds;

type
  TCommandModule = class(TDataModule)
    procedure DataModuleCreate(Sender: TObject);
  private
    { Private declarations }
  protected
    procedure Init; virtual; 
  public
    { Public declarations }
  end;

var
  CommandModule: TCommandModule;

implementation

uses KSFrameWorks, KSFrameWorkUtils;

{$R *.DFM}

procedure TCommandModule.DataModuleCreate(Sender: TObject);
begin
  RegisterModule(Self);
  Init;
end;

procedure TCommandModule.Init;
begin

end;

end.
