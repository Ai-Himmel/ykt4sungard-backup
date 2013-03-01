unit phtComplete;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, phtImportForm;

type
  TfrmComplete = class(TfrmImportForm)
    Label1: TLabel;
    Shape1: TShape;
    Shape2: TShape;
    Memo1: TMemo;
  private
    { Private declarations }
  public
    { public declarations }  
    procedure Enter; override;
    function Leave: Boolean; override;
  end;

implementation

{$R *.DFM}

{ TfrmComplete }

procedure TfrmComplete.Enter;
begin
  Self.Show;
end;

function TfrmComplete.Leave: Boolean;
begin
  Result := True;
end;

end.
