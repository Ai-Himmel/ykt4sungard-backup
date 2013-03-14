unit UStartFlash;
{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UStartFlash
   <What>初始启动界面
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, jpeg, StdCtrls;

type
  TfmStartFlash = class(TForm)
    Panel1: TPanel;
    Image1: TImage;
    lblInfo: TLabel;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  fmStartFlash: TfmStartFlash;

procedure ShowStartFlash;

procedure CloseStartFlash;

procedure UpdateFlash;

procedure WriteStartProgress(const S: string);

implementation

{$R *.DFM}

procedure ShowStartFlash;
begin
  fmStartFlash := TfmStartFlash.Create(nil);
  fmStartFlash.Show;
  fmStartFlash.Update;
end;

procedure CloseStartFlash;
begin
  FreeAndNil(fmStartFlash);
end;

procedure UpdateFlash;
begin
  if fmStartFlash <> nil then
    fmStartFlash.Update;
end;

procedure WriteStartProgress(const S: string);
begin
  if fmStartFlash <> nil then
  begin
    fmStartFlash.lblInfo.Caption := S;
    UpdateFlash;
  end;
end;

end.
