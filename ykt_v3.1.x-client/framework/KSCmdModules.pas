unit KSCmdModules;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSCmdModules
   <What>用于命令定义对象、命令处理对象的数据模块。可以自动注册。
   <Written By> Huang YanLai (黄燕来)
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
