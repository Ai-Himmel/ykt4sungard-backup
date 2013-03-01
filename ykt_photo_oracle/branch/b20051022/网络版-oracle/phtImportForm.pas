unit phtImportForm;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs;

type
  TfrmImportForm = class(TForm)
  private
    { Private declarations }
  public
    { Public declarations }
    procedure Enter; virtual; abstract;
    function Leave: Boolean; virtual; abstract;
  end;

implementation

{$R *.DFM}

end.
