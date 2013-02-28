unit UKSCopyRight;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UIStyles, ImagesMan, KSFrameWorks;

type
  TdmKSCopyRight = class(TDataModule)
    DefaultImages: TUIImages;
    LightImages: TUIImages;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

  TKSCopyRight = class(TInterfacedObject,ICopyRightSystem)
  private

  protected
    procedure ShowAbout;
    function  GetVersion : string;
  public

  end;

var
  dmKSCopyRight: TdmKSCopyRight;
resourcestring
  SVersion = '1.0.0.1';

implementation

uses UKSAbout;

{$R *.DFM}
procedure InstallCopyRight;
begin
  dmKSCopyRight := TdmKSCopyRight.Create(nil);
  if Context<>nil then
    Context.SetCopyRight(TKSCopyRight.Create);
end;

procedure UnInstallCopyRight;
begin
  if Context<>nil then
    Context.SetCopyRight(nil);
  FreeAndNil(dmKSCopyRight);
end;

{ TKSCopyRight }

function TKSCopyRight.GetVersion: string;
begin
  Result := SVersion;
end;

procedure TKSCopyRight.ShowAbout;
begin
  UKSAbout.ShowAbout;
end;

{ TdmKSGTCopyRight }

initialization
  InstallCopyRight;

finalization
  UnInstallCopyRight;

end.
