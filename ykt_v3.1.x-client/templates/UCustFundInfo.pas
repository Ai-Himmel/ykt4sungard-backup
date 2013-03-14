unit UCustFundInfo;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UCustFundInfo
   <What>客户资金信息模版
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}


interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UCustBaseInfo, WVCtrls, StdCtrls;

type
  TCustFundInfo = class(TCustBaseInfo)
    Label8: TLabel;
    WVLabel14: TWVLabel;
    WVLabel12: TWVLabel;
    Label6: TLabel;
    Label7: TLabel;
    WVLabel13: TWVLabel;
    Label9: TLabel;
    WVLabel15: TWVLabel;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  CustFundInfo: TCustFundInfo;

implementation

{$R *.DFM}

end.
