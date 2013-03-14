unit UHTMLBrowser;
{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UHTMLBrowser
   <What>ÄÚÇ¶HTMLä¯ÀÀÆ÷
   <Written By> Huang YanLai (»ÆÑàÀ´)
   <History>
**********************************************}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ActnList, OleCtrls, SHDocVw, ImgList, StdCtrls, ComCtrls, ToolWin,
  ExtCtrls, UICtrls, jpeg;

type
  TfaHTMLBrowser = class(TFrame)
    NavigatorImages: TImageList;
    NavigatorHotImages: TImageList;
    ActionList1: TActionList;
    BackAction: TAction;
    ForwardAction: TAction;
    StopAction: TAction;
    RefreshAction: TAction;
    HomeAction: TAction;
    pnToolbar: TUIPanel;
    ToolBar: TToolBar;
    ToolButton1: TToolButton;
    BackBtn: TToolButton;
    ForwardBtn: TToolButton;
    StopBtn: TToolButton;
    RefreshBtn: TToolButton;
    NewBrowserWindowBtn: TToolButton;
    ToolButton2: TToolButton;
    WebBrowser: TWebBrowser;
    pnl1: TPanel;
    img1: TImage;
    procedure BackActionExecute(Sender: TObject);
    procedure ForwardActionExecute(Sender: TObject);
    procedure StopActionExecute(Sender: TObject);
    procedure RefreshActionExecute(Sender: TObject);
    procedure HomeActionExecute(Sender: TObject);
    procedure NewBrowserWindowBtnClick(Sender: TObject);
    procedure RefreshBtnClick(Sender: TObject);
  private
    FHomePage: string;
    FURL: string;
    FFirstLoading : boolean;
    { Private declarations }
  public
    { Public declarations }
    procedure OpenPage(const AURL: string);
    procedure GoHome;
    property HomePage: string read FHomePage write FHomePage;
    property URL: string read FURL;
  end;
implementation

{$R *.DFM}

uses LogFile, KSClientConsts, ExtUtils;

procedure TfaHTMLBrowser.BackActionExecute(Sender: TObject);
begin
  try
    //WebBrowser.GoBack;
  except

  end;
end;

procedure TfaHTMLBrowser.ForwardActionExecute(Sender: TObject);
begin
  try
    //WebBrowser.GoForward;
  except

  end;
end;

procedure TfaHTMLBrowser.StopActionExecute(Sender: TObject);
begin
  //WebBrowser.Stop;
end;

procedure TfaHTMLBrowser.RefreshActionExecute(Sender: TObject);
begin
  //WebBrowser.Refresh;
end;

procedure TfaHTMLBrowser.OpenPage(const AURL: string);
var
  URLParam : OleVariant;
  Flags : OleVariant;
begin
  {
  FFirstLoading := True;
  WriteLog('OpenPage=' + AURL, lcKSClient);
  FURL := AURL;
  if NewBrowserWindowBtn.Down then
  begin
    ShellOpenFile(URL);
  end
  else
  begin
    WebBrowser.HandleNeeded;
    URLParam := URL;
    Flags := 0;
    WebBrowser.Navigate2(URLParam);
    while WebBrowser.ReadyState <> READYSTATE_COMPLETE  do
      Application.ProcessMessages;
  end;
  }
end;

procedure TfaHTMLBrowser.HomeActionExecute(Sender: TObject);
begin
  GoHome;
end;

procedure TfaHTMLBrowser.GoHome;
begin
  if HomePage <> '' then
    OpenPage(HomePage);
end;

procedure TfaHTMLBrowser.NewBrowserWindowBtnClick(Sender: TObject);
begin
  //NewBrowserWindowBtn.Down := not NewBrowserWindowBtn.Down;
  if NewBrowserWindowBtn.Down then
    ShellOpenFile(URL);
end;

procedure TfaHTMLBrowser.RefreshBtnClick(Sender: TObject);
begin
  //WebBrowser.Refresh;
end;

end.
