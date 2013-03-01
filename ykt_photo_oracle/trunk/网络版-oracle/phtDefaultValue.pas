unit phtDefaultValue;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, phtImportForm, ExtCtrls, Grids, Grids_ts, TSGrid, phtImport;

type
  TfrmDefaultValue = class(TfrmImportForm)
    Label1: TLabel;
    Shape1: TShape;
    Shape2: TShape;
    tsGrid1: TtsGrid;
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

{ TfrmDefaultValue }

procedure TfrmDefaultValue.Enter;
begin
  G_phtImport.InitTsGrid(tsGrid1);
  Self.Show;
end;

function TfrmDefaultValue.Leave: Boolean;
begin
  G_phtImport.GetDefValue(tsGrid1);
  Result := True;
end;

end.
