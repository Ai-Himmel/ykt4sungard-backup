unit UKSGTCopyRight;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UIStyles, ImagesMan, KSFrameWorks;

type
  TdmKSGTCopyRight = class(TDataModule)
    DefaultImages: TUIImages;
    LightImages: TUIImages;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

  TKSGTCopyRight = class(TInterfacedObject,ICopyRightSystem)
  private

  protected
    procedure ShowAbout;
    function  GetVersion : string;
  public

  end;

var
  dmKSGTCopyRight: TdmKSGTCopyRight;

resourcestring
  SVersion = '1.0.0.1';

implementation

uses UKSGTAbout;

{$R *.DFM}

procedure InstallCopyRight;
begin
  dmKSGTCopyRight := TdmKSGTCopyRight.Create(nil);
  if Context<>nil then
    Context.SetCopyRight(TKSGTCopyRight.Create);
end;

procedure UnInstallCopyRight;
begin
  if Context<>nil then
    Context.SetCopyRight(nil);
  FreeAndNil(dmKSGTCopyRight);
end;

{ TKSGTCopyRight }

function TKSGTCopyRight.GetVersion: string;
begin
  Result := SVersion;
end;

procedure TKSGTCopyRight.ShowAbout;
begin
  UKSGTAbout.ShowAbout;
end;

{ TdmKSGTCopyRight }

initialization
  InstallCopyRight;

finalization
  UnInstallCopyRight;

end.
