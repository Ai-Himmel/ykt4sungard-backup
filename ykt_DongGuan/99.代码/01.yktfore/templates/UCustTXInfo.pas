unit UCustTXInfo;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UCustTXInfo
   <What>客户交易信息模版
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}


interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UCustAccountInfo, WVCtrls, StdCtrls;

type
  TCustTXInfo = class(TCustAccountInfo)
    Label8: TLabel;
    WVLabel14: TWVLabel;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  CustTXInfo: TCustTXInfo;

implementation

{$R *.DFM}

end.
