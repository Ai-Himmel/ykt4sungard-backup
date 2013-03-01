unit ptMain;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, StdCtrls, uConst, fConfig, ksPicHandler,
  Buttons;

type
  TfMain = class(TForm)
    pnl1: TPanel;
    btnFetch: TButton;
    btnSave: TButton;
    edtPersonNo: TEdit;
    lbl1: TLabel;
    pnlHandlePic: TPanel;
    btnConfig: TButton;
    btnExit: TButton;
    pnlPic: TPanel;
    imgPic: TImage;
    btnQuery: TButton;
    btnCancel: TButton;
    GroupBox1: TGroupBox;
    sbZI: TSpeedButton;
    sbZO: TSpeedButton;
    sbRL: TSpeedButton;
    sbRR: TSpeedButton;
    sbUp: TSpeedButton;
    sbLeft: TSpeedButton;
    sbRight: TSpeedButton;
    sbDown: TSpeedButton;
    PicFrame: TShape;
    shpTop: TShape;
    shpLeft: TShape;
    shpRight: TShape;
    shpCenter: TShape;
    Shape1: TShape;
    Shape2: TShape;
    procedure FormCreate(Sender: TObject);
    procedure btnFetchClick(Sender: TObject);
    procedure btnSaveClick(Sender: TObject);
    procedure btnConfigClick(Sender: TObject);
    procedure btnExitClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure sbRLClick(Sender: TObject);
    procedure sbRRClick(Sender: TObject);
    procedure sbUpClick(Sender: TObject);
    procedure sbDownClick(Sender: TObject);
    procedure sbLeftClick(Sender: TObject);
    procedure sbRightClick(Sender: TObject);
    procedure sbZIClick(Sender: TObject);
    procedure sbZOClick(Sender: TObject);
  private
    { Private declarations }
    FSaved: Boolean;
    FPicNum: string;
    FDown: Boolean;
    FPicHandler: TksPicHandler; 
    SrcPicName: string;

    procedure SetSaved(Value: Boolean);
    function ProducePicNum(len: Integer): string;
  public
    { Public declarations }
  end;

var
  fMain: TfMain;

implementation

{$R *.DFM}

procedure TfMain.SetSaved(Value: Boolean);
begin
  FSaved := Value;
  btnSave.Enabled := not FSaved;
  pnlHandlePic.Enabled := not FSaved;
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

procedure TfMain.FormCreate(Sender: TObject);
var
  ARect: TRect;
begin
  Self.Left := 0;
  Self.Top := 0;
  SetSaved(True);
  FPicNum := ProducePicNum(NumLen);
  FDown := False;
  FPicHandler := TksPicHandler.Create(imgPic); 
  ARect := Rect(PicFrame.Left, PicFrame.Top,
    PicFrame.Left + PicFrame.Width, PicFrame.Top + PicFrame.Height);
  FPicHandler.SetFrame(ARect);
end;

procedure TfMain.btnFetchClick(Sender: TObject);
begin
  SrcPicName := SrcDir + '\' + PreName + FPicNum + '.JPG';
  if FileExists(SrcPicName) then
  begin
    //imgPic.Stretch := False;
    FPicHandler.LoadFromFile(SrcPicName);
    //imgPic.Stretch := True;
    SetSaved(False);
  end
  else
  begin
    MessageDlg('照片不存在或者配置信息错误!', mtInformation, [mbOk], 0);
  end
end;

procedure TfMain.btnSaveClick(Sender: TObject);
var
  PersonNum: string;
  DstPicName: string;
begin
  PersonNum := Trim(edtPersonNo.Text);
  if PersonNum = '' then
  begin
    MessageDlg('学工号不能为空!', mtWarning, [mbOk], 0);
    Exit;
  end;
  DstPicName := DstDir + '\' + PersonNum + '.JPG';
  try
    FPicHandler.SaveToFile(DstPicName);
    DeleteFile(PChar(SrcPicName));
    imgPic.Picture.Assign(nil);
    SetSaved(True);
    MessageDlg('保存成功!', mtInformation, [mbOk], 0);
  except
    MessageDlg('保存失败 !请检查配置信息是否正确!', mtInformation, [mbOk], 0);
  end;
end;

procedure TfMain.btnConfigClick(Sender: TObject);
begin
  Config;
  FPicNum := ProducePicNum(NumLen);
end;

procedure TfMain.btnExitClick(Sender: TObject);
begin
  Close;
end;

procedure TfMain.btnQueryClick(Sender: TObject);
var
  PersonNo: string;
  LoadPicName: string;
begin
  PersonNo := Trim(edtPersonNo.Text);
  LoadPicName := DstDir + '\' + PersonNo + '.JPG';
  if FileExists(LoadPicName) then
  begin
    imgPic.Stretch := False;
    FPicHandler.LoadFromFile(LoadPicName);

    imgPic.Left := PicFrame.Left;
    imgPic.Top := PicFrame.Top;
    imgPic.Width := PicFrame.Width;
    imgPic.Height := PicFrame.Height;
    imgPic.Stretch := True;
    
    SetSaved(True);
  end
  else
  begin
    MessageDlg('照片不存在或者配置信息错误!', mtInformation, [mbOk], 0);
  end
end;

procedure TfMain.btnCancelClick(Sender: TObject);
begin
  imgPic.Picture.Assign(nil);  
  SetSaved(True);
end;

procedure TfMain.sbRLClick(Sender: TObject);
begin
  FPicHandler.Rotate(-0.011);
end;

procedure TfMain.sbRRClick(Sender: TObject);
begin
  FPicHandler.Rotate(0.011);
end;

procedure TfMain.sbUpClick(Sender: TObject);
begin
  FPicHandler.Move(Point(0, -2));
end;

procedure TfMain.sbDownClick(Sender: TObject);
begin
  FPicHandler.Move(Point(0, 2));
end;

procedure TfMain.sbLeftClick(Sender: TObject);
begin
  FPicHandler.Move(Point(-2, 0));
end;

procedure TfMain.sbRightClick(Sender: TObject);
begin
  FPicHandler.Move(Point(2, 0));
end;

procedure TfMain.sbZIClick(Sender: TObject);
begin
  FPicHandler.Zoom(+3);
end;

procedure TfMain.sbZOClick(Sender: TObject);
begin
  FPicHandler.Zoom(-3);
end;

end.
