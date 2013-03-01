unit ptMain;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, StdCtrls, uConst, fConfig, jpeg;

type
  TfMain = class(TForm)
    pnl1: TPanel;
    btnFetch: TButton;
    btnSave: TButton;
    edtPersonNo: TEdit;
    lbl1: TLabel;
    pnlPic: TPanel;
    imgPic: TImage;
    btnConfig: TButton;
    btnExit: TButton;
    procedure FormCreate(Sender: TObject);
    procedure btnFetchClick(Sender: TObject);
    procedure btnSaveClick(Sender: TObject);
    procedure btnConfigClick(Sender: TObject);
    procedure btnExitClick(Sender: TObject);
  private
    { Private declarations }
    bSave: Boolean;
    PicNum: string;
    function ProducePicNum(len: Integer): string;
  public
    { Public declarations }
  end;

var
  fMain: TfMain;

implementation

{$R *.DFM}

procedure TfMain.FormCreate(Sender: TObject);
begin
  bSave := True;
  PicNum := ProducePicNum(NumLen);
  //imgPic.Picture.Bitmap.Width := 10;
end;
 
function TfMain.ProducePicNum(len: Integer): string;
var
  str: string;
begin
  str := '1';
  while (Length(str) < len) do
    str := '0' + str;
  Result := str;
end;

procedure TfMain.btnFetchClick(Sender: TObject);
var
  SrcPicName: string;
begin
  SrcPicName := SrcDir + '\' + PreName + PicNum + '.JPG';
  if FileExists(SrcPicName) then
  begin
    imgPic.Picture.LoadFromFile(SrcPicName);
    // imgPic.Stretch := False;
    // imgPic.Stretch := True;
    DeleteFile(PChar(SrcPicName));
    bSave := False;
  end
  else
  begin
    ShowMessage('照片不存在或者配置信息错误！');
  end
end;

procedure TfMain.btnSaveClick(Sender: TObject);
var
  PersonNum: string;
  DstPicName: string;
begin
  if bSave then
  begin
    ShowMessage('请先取照片！');
  end
  else
  begin
    PersonNum := Trim(edtPersonNo.Text);
    DstPicName := DstDir + '\' + PersonNum + '.JPG';
    imgPic.Picture.SaveToFile(DstPicName);
    imgPic.Picture.Assign(nil);
    bSave := True;
  end;
end;

procedure TfMain.btnConfigClick(Sender: TObject);
begin
  Config;
  PicNum := ProducePicNum(NumLen);
end;

procedure TfMain.btnExitClick(Sender: TObject);
begin
  Close;
end;

end.
