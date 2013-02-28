unit UStyles;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UStyles
   <What>提供界面风格的样式
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UIStyles, ImagesMan;

type
  TdmStyles = class(TDataModule)
    NormalStyle: TUIStyle;
    DefaultButtons: TCommandImages;
    LightStyle: TUIStyle;
    LightButtons: TCommandImages;
    DefaultSmallButtons: TCommandImages;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  dmStyles: TdmStyles;

implementation

{$R *.DFM}

end.
