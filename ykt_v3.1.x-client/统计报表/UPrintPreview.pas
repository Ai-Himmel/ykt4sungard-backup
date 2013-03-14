unit UPrintPreview;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ComCtrls, ToolWin, GSMenu, XLPreview, ExtCtrls, XLGrids, 
  XLActns, ActnList;

type
  TfrmPrintPreview = class(TForm)
    PreviewPanel: TPanel;
    GSMenuBar1: TGSMenuBar;
    BPNext: TToolButton;
    BPPrev: TToolButton;
    BPZoom: TToolButton;
    btnAPClose: TToolButton;
    BPPageSetup: TToolButton;
    BPClose: TToolButton;
    StatusBar: TStatusBar;
    Preview: TXLPreview;
    procedure PreviewPageChanged(Sender: TObject);
    procedure BPPrintClick(Sender: TObject);
    procedure XLZoomExecute(Sender: TObject);
    procedure APCloseExecute(Sender: TObject);
    procedure APZoomExecute(Sender: TObject);
    procedure BPPageSetupClick(Sender: TObject);
    procedure btnAPCloseClick(Sender: TObject);
    procedure BPCloseClick(Sender: TObject);
    procedure BPNextClick(Sender: TObject);
    procedure BPPrevClick(Sender: TObject);
    procedure GridCurChanged(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }

  public
    { Public declarations }
    Grid: TXLGrid;
    Sheet: TXLSheet;
  end;

var
  frmPrintPreview: TfrmPrintPreview;
resourcestring
  xlcPageXfromY       = 'Preview: Page %d of %d';

implementation

uses UAsubjectTrade;

{$R *.DFM}

procedure TfrmPrintPreview.PreviewPageChanged(Sender: TObject);
begin
  if Preview.Sheet <> Nil then begin
    StatusBar.Panels[0].Text := Format(xlcPageXfromY, [Preview.PageNo + 1, Preview.PageCount]);
    StatusBar.Panels[1].Text := '';
    StatusBar.Panels[2].Text := '';
  end else if Sheet <> Nil then
    with Grid.Selection do begin
      with StatusBar.Panels[2] do
        if Single or Empty then Text := ''
        else Text := SysUtils.Format('[%s:%s]', [Pos2XLI(Bounds.TopLeft), Pos2XLI(Bounds.BottomRight)]);
      GridCurChanged(nil);
    end;
end;

procedure TfrmPrintPreview.BPPrintClick(Sender: TObject);
begin
  Preview.Sheet.Print;
end;

procedure TfrmPrintPreview.XLZoomExecute(Sender: TObject);
begin
  Preview.Click;
end;

procedure TfrmPrintPreview.APCloseExecute(Sender: TObject);
begin
  Close;
end;

procedure TfrmPrintPreview.APZoomExecute(Sender: TObject);
begin
  preview.click;
end;

procedure TfrmPrintPreview.BPPageSetupClick(Sender: TObject);
begin
  with TPrinterSetupDialog.Create(nil) do
  try
    if Execute then XLManager.SetPrinter;
  finally
    Free;
  end;
end;

procedure TfrmPrintPreview.btnAPCloseClick(Sender: TObject);
begin
  XLManager.SetPrinter;
  with TPrintDialog.Create(nil) do
  try
    if Grid.Selection.Empty then Options := Options - [poSelection];
    if not Grid.Selection.Single and (poSelection in Options) then PrintRange := prSelection;
    with Grid do begin
      Copies := 1;
      MaxPage := Sheet.PrintPageCount;
      FromPage := 1;
      ToPage := MaxPage;
      if Execute then
        case PrintRange of
          prAllPages: Sheet.Print;
          prSelection: Selection.Print;
          else Sheet.PrintPages(FromPage, ToPage);
        end;
    end;
  finally
    Free;
  end;
end;

procedure TfrmPrintPreview.BPCloseClick(Sender: TObject);
begin
  Close;
end;

procedure TfrmPrintPreview.BPNextClick(Sender: TObject);
begin
  BPNext.Enabled := Preview.PageNo < Preview.PageCount - 1;
  bpprev.Enabled := Preview.PageNo > 0;
  Preview.PageNo := Preview.PageNo + 1;
end;

procedure TfrmPrintPreview.BPPrevClick(Sender: TObject);
begin
  BPNext.Enabled := Preview.PageNo < Preview.PageCount - 1;
  bpprev.Enabled := Preview.PageNo > 0;
  Preview.PageNo := Preview.PageNo - 1;
end;

procedure TfrmPrintPreview.GridCurChanged(Sender: TObject);
begin
  with Grid do begin
    StatusBar.Panels[0].Text := Selection.GetNamePath + ': ' + Sheet.CellClasses[CurCol, CurRow].ClassName;
    StatusBar.Panels[1].Text := Pos2XLI(CurPos);
  end;
end;

procedure TfrmPrintPreview.FormShow(Sender: TObject);
begin
  BPNext.Enabled := Preview.PageNo < Preview.PageCount - 1;
  bpprev.Enabled := Preview.PageNo > 0;
end;

end.

