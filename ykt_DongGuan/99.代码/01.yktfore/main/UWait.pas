unit UWait;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, UICtrls, ExtCtrls;

type
  TfmWaiting = class(TForm)
    UIPanel1: TUIPanel;
    lbMessage: TLabel;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  fmWaiting: TfmWaiting;

implementation

{$R *.DFM}

end.
