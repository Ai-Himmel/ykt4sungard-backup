unit UUIPlate;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,KSFrameWorks;

type
  TfmUIPlate = class(TForm)
  private
    { Private declarations }
    FInstanceRecord: TUIInstanceRecord;
  public
    { Public declarations }
    property  InstanceRecord : TUIInstanceRecord
                read FInstanceRecord write FInstanceRecord;
  end;

var
  fmUIPlate: TfmUIPlate;

implementation
uses KSFrameWorkUtils;
{$R *.DFM}

{ TfmUIPlate }

end.
