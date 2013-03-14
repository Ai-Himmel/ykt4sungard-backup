unit UPreview;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, ToolWin, ExtCtrls, ImgList,  FR_View, frexpimg,
  frHTMExp, frRtfExp, FR_Class, frOLEExl;

type
  TfrmPreview = class(TForm)
    pnlControl: TPanel;
    tlb1: TToolBar;
    btnHolePage: TToolButton;
    btnFit: TToolButton;
    btnPageWidth: TToolButton;
    btnFirstPage: TToolButton;
    btn1: TToolButton;
    btnPriPage: TToolButton;
    btnNextPage: TToolButton;
    btnLastPage: TToolButton;
    btn2: TToolButton;
    btnOpen: TToolButton;
    btnSave: TToolButton;
    btnPrint: TToolButton;
    btnSetup: TToolButton;
    btn3: TToolButton;
    btnClose: TToolButton;
    il1: TImageList;
    frlxclxprt1: TfrOLEExcelExport;
    frtfdvxprt1: TfrRtfAdvExport;
    frhtmltblxprt1: TfrHTMLTableExport;
    frjpgxprt1: TfrJPEGExport;
    frPreview: TfrPreview;
    procedure btnCloseClick(Sender: TObject);
    procedure btnFirstPageClick(Sender: TObject);
    procedure btnPriPageClick(Sender: TObject);
    procedure btnNextPageClick(Sender: TObject);
    procedure btnLastPageClick(Sender: TObject);
    procedure btnSetupClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure btnSaveClick(Sender: TObject);
    procedure btnOpenClick(Sender: TObject);
    procedure btnHolePageClick(Sender: TObject);
    procedure btnFitClick(Sender: TObject);
    procedure btnPageWidthClick(Sender: TObject);
    procedure FormActivate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmPreview: TfrmPreview;

implementation

{$R *.DFM}

procedure TfrmPreview.btnCloseClick(Sender: TObject);
begin
  close;
end;

procedure TfrmPreview.btnFirstPageClick(Sender: TObject);
begin
  frPreview.First;
end;

procedure TfrmPreview.btnPriPageClick(Sender: TObject);
begin
  frPreview.Prev;
end;

procedure TfrmPreview.btnNextPageClick(Sender: TObject);
begin
  frPreview.Next;
end;

procedure TfrmPreview.btnLastPageClick(Sender: TObject);
begin
  frPreview.Last;
end;

procedure TfrmPreview.btnSetupClick(Sender: TObject);
begin
  frPreview.PageSetupDlg;
end;

procedure TfrmPreview.btnPrintClick(Sender: TObject);
begin
  frPreview.Print;
end;

procedure TfrmPreview.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  //frmPreview := nil;
end;

procedure TfrmPreview.btnSaveClick(Sender: TObject);
begin
  frPreview.SaveToFile;
end;

procedure TfrmPreview.btnOpenClick(Sender: TObject);
begin
  frPreview.LoadFromFile;
end;

procedure TfrmPreview.btnHolePageClick(Sender: TObject);
begin
  frPreview.Zoom := 100;
end;

procedure TfrmPreview.btnFitClick(Sender: TObject);
begin
  frPreview.OnePage;
end;

procedure TfrmPreview.btnPageWidthClick(Sender: TObject);
begin
  frPreview.PageWidth;
end;

procedure TfrmPreview.FormActivate(Sender: TObject);
begin
  btnHolePage.Down := True;
  btnHolePageClick(nil);
end;

end.
