unit UCustAccountInfo;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UCustAccountInfo
   <What>客户股东账号基本信息模版
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}


interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UCustBaseInfo, WVCtrls, StdCtrls;

type
  TCustAccountInfo = class(TCustBaseInfo)
    Label6: TLabel;
    Label7: TLabel;
    WVLabel12: TWVLabel;
    WVLabel13: TWVLabel;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  CustAccountInfo: TCustAccountInfo;

implementation

{$R *.DFM}

end.
