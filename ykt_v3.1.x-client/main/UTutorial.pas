unit UTutorial;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ImageCtrls, ExtCtrls, UICtrls, UHTMLBrowser;

type
  TdlgTutorial = class(TForm)
    UIPanel1: TUIPanel;
    btnClose: TImageButton;
    Browser: TfaHTMLBrowser;
    procedure btnCloseClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure Execute;
  end;

var
  dlgTutorial: TdlgTutorial;

procedure ExecuteTutorial;

implementation

{$R *.DFM}

uses KSFrameWorks, KSFrameWorkUtils, KSClientConsts, LogFile;

procedure ExecuteTutorial;
var
  Dialog: TdlgTutorial;
begin
  Dialog := TdlgTutorial.Create(Application);
  try
    Dialog.Execute;
  finally
    Dialog.Free;
  end;
end;

{ TdlgTutorial }

procedure TdlgTutorial.Execute;
var
  TutorialHome: string;
begin
  TutorialHome := GetFileName(dkHelp, TutorialFile);
  Browser.HomePage := TutorialHome;
  Browser.OpenPage(TutorialHome);
  if FirstShowTutorial = 0 then
  begin
    FirstShowTutorial := GetTickCount;
    WriteLog('Start Tutorial, Time Elapsed=' + IntToStr(FirstShowTutorial -
      StartTime), lcKSClientStart);
  end;
  Browser.pnToolBar.Visible := False;
  ShowModal;
end;

procedure TdlgTutorial.btnCloseClick(Sender: TObject);
begin
  Close;
end;

end.
