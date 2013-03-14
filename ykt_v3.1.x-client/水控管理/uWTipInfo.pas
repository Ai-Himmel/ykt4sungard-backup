unit uWTipInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls;

type
  TfrmWTipInfo = class(TForm)
    pnl1: TPanel;
    lblInfo: TLabel;
    img1: TImage;
    pnl2: TPanel;
    btnAllY: TButton;
    btnYes: TButton;
    btnNo: TButton;
    procedure FormShow(Sender: TObject);
    procedure btnAllYClick(Sender: TObject);
    procedure btnYesClick(Sender: TObject);
    procedure btnNoClick(Sender: TObject);
  private
    { Private declarations }
    procedure iniWForm(inStr:string);
  public
    { Public declarations }
    wtipInfo:string;
    iWGSign:Integer;//1是，0否，2全部是
  end;

var
  frmWTipInfo: TfrmWTipInfo;

implementation

{$R *.DFM}

{ TfrmWTipInfo }

procedure TfrmWTipInfo.iniWForm(inStr: string);
var
  strLength:Integer;
begin
  lblInfo.Left := 40;
  lblInfo.Top := 16;
  strLength := Length(inStr)*7;
  if strLength<=400 then
  begin
    frmWTipInfo.Width := 430;
    frmWTipInfo.Height := 110;
    lblInfo.Height := 14;
  end
  else if strLength<=650 then
  begin
    frmWTipInfo.Width := 680;
    lblInfo.Height := 14;
    lblInfo.Width := 630;
  end
  else
  begin
    frmWTipInfo.Width := 680;
    lblInfo.Height := (Trunc(strLength/650)+1)*14;
    lblInfo.Width := 640;
    pnl1.Height := lblInfo.Top+lblinfo.Height+10;
  end;

  frmWTipInfo.Height := pnl1.Height + pnl2.Height + 50;
  lblInfo.Caption := inStr;
  pnl2.Top := pnl1.Height+10;
  pnl2.Left := Round((frmWTipInfo.Width-pnl2.Width)/2);
end;

procedure TfrmWTipInfo.FormShow(Sender: TObject);
begin
  iniWForm(wtipInfo);
end;

procedure TfrmWTipInfo.btnAllYClick(Sender: TObject);
begin
  iWGSign := 2;
  Close;
end;

procedure TfrmWTipInfo.btnYesClick(Sender: TObject);
begin
  iWGSign := 1;
  Close;
end;

procedure TfrmWTipInfo.btnNoClick(Sender: TObject);
begin
  iWGSign := 0;
  Close;
end;

end.
