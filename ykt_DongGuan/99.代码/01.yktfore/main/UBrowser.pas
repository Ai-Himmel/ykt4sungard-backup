unit UBrowser;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UBrowser
   <What>显示向导
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}

interface

uses SysUtils, Windows, Messages, Classes, Graphics, Controls, Forms,
KSFrameWorks, KSFrames,
  OleCtrls, SHDocVw, UHTMLBrowser, ImgList, ExtCtrls;

type
  TfaBrowser = class(TKSFrame)
    HTMLBrowser: TfaHTMLBrowser;
    ImageList1: TImageList;
    Panel1: TPanel;
  private

  protected
    procedure Init; override;
  public
    constructor Create(AOwner: TComponent); override;
  end;

var
  faBrowser: TfaBrowser;

implementation

uses KSClientConsts, KSFrameWorkUtils;

{$R *.DFM}

{
var
  Factory : TUIStdClassFactory;
}

{ TfaBrowser }

constructor TfaBrowser.Create(AOwner: TComponent);
var
  FileName: string;
begin
  inherited;
  FileName := GetFileName(dkHelp, GuideFile);
  HTMLBrowser.HomePage := FileName;
  //HTMLBrowser.OpenPage(FileName);
end;

procedure TfaBrowser.Init;
begin
  inherited;
  HTMLBrowser.GoHome;
end;

initialization
  {Factory := } TUIStdClassFactory.Create(UIGuide, TfaBrowser);

end.
