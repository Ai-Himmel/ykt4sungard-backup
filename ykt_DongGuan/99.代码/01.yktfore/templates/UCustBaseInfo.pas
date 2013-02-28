unit UCustBaseInfo;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UCustBaseInfo
   <What>客户基本信息模版
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}


interface

uses SysUtils, Windows, Messages, Classes, Graphics, Controls,Forms, 
  StdCtrls, WVCtrls;

type
  TCustBaseInfo = class(TFrame)
    GroupBox1: TGroupBox;
    Label32: TLabel;
    Label1: TLabel;
    Label22: TLabel;
    Label23: TLabel;
    WVLabel1: TWVLabel;
    WVLabel2: TWVLabel;
    WVLabel3: TWVLabel;
    WVLabel4: TWVLabel;
    WVLabel5: TWVLabel;
    WVLabel6: TWVLabel;
    WVLabel7: TWVLabel;
    Label24: TLabel;
    Label25: TLabel;
    Label26: TLabel;
    Label2: TLabel;
    WVLabel8: TWVLabel;
    Label3: TLabel;
    WVLabel9: TWVLabel;
    Label4: TLabel;
    WVLabel10: TWVLabel;
    Label5: TLabel;
    WVLabel11: TWVLabel;
    lbReserved1: TLabel;
    lbReserved2: TLabel;
    wlbReserved1: TWVLabel;
    wlbReserved2: TWVLabel;
  private

  protected

  public

  end;

var
  CustBaseInfo: TCustBaseInfo;

implementation

{$R *.DFM}

end.
