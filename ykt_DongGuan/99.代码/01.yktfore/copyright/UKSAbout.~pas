unit UKSAbout;
{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UAbout
   <What>关于对话框
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}


interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, jpeg, ExtCtrls, ImageCtrls, UICtrls, ComCtrls, KSBaseAbout,
  RzListVw, Buttons, AAFont, AACtrls,UtCardDll;

type
  TdlgAbout = class(TdlgKSBaseAbout)
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  dlgAbout: TdlgAbout;

procedure ShowAbout;

implementation

{$R *.DFM}

uses ExtUtils,KSClientConsts;

procedure ShowAbout;
var
  Dialog : TdlgAbout;
begin
  Dialog := TdlgAbout.Create(nil);
  try
    Dialog.ShowModal;
  finally
    Dialog.Free;
  end;
end;

{ TdlgAbout }

end.
