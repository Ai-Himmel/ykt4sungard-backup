unit UCustTXInfo;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UCustTXInfo
   <What>�ͻ�������Ϣģ��
   <Written By> Huang YanLai (������)
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
