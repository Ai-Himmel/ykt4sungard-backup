unit UPictureMag;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, ExtDlgs, ADODB, jpeg;



type
  TPictureMag = class(TForm)
    lblPosition: TLabel;
    OpenPictureDialog: TOpenPictureDialog;
    SavePictureDialog1: TSavePictureDialog;
    sbDestinate: TScrollBox;
    pbDestinate: TPaintBox;
    imgDestinate: TImage;
    sbSource: TScrollBox;
    pbSource: TPaintBox;
    imgSource: TImage;
    btnLoad: TButton;
    btnOK: TButton;
    btnPaste: TButton;
    Label1: TLabel;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Label3: TLabel;
    procedure btnLoadClick(Sender: TObject);
    procedure btnPasteClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure imgSourceClick(Sender: TObject);
    procedure imgSourceMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure imgSourceMouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure imgSourceMouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure FormClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
  private
    FZoneSelected: Boolean;
    FScanOperated: Boolean;
    FPhotoWidth: Integer;
    FPhotoHeight: Integer;

    {提取学号和姓名信息}
    procedure GetPersonInfoToLabel(FPerNo: string; var FLabelCaption: string; var FLabelName: string);
    {设置特殊字体}
    procedure SetSpecialFont(FString: string);

    { Private declarations }
  public
    { Public declarations }
  end;

var
  PictureMag: TPictureMag;

implementation

uses Udb, UtConfigs;

{$R *.DFM}

var
  OP1, OP2: TPoint;
  P1, P2: TPoint;

  DownFlag: Boolean = False;

  foldx,foldy: Integer;




procedure DrawRectangle(Canvas: TCanvas);
begin
  with Canvas do
  begin
    Brush.Style := bsClear;
    Pen.Color := clGray;
    Pen.Style := psDot;
    Pen.Mode := pmNot;
//  Canvas.Brush.Style := bsClear;
    Rectangle(OP1.X, OP1.Y, OP2.X, OP2.Y);
  end;
end;



procedure TPictureMag.SetSpecialFont(FString: string);
var
  FLogFont: tagLogFontA; // file://逻辑字体--结构体类型
  hTempFont, hPrevFont: HFONT; // file://字体句柄
  hTempDC: HDC; // file://设备描述表或图形设备句柄
  Fontname: string;
begin
  FLogFont.lfHeight := 10; // file://字高
  FLogFont.lfWidth := 6; // file://字宽
  FLogFont.lfWeight := 700; // file://字体笔划粗细程度
  FLogFont.lfUnderline := 0; // file://没有下划线
  FLogFont.lfStrikeOut := 0; // file://没有删除线
  FLogFont.lfItalic := 0; //file://斜体效果否
  FLogFont.lfCharSet := GB2312_CHARSET; //file://字符集
  FLogfont.lfEscapement := 2700; // file://倾斜度
  FLogFont.lfOrientation := 2700; // file://方向与倾斜度取值同
  FLogFont.lfFaceName := '宋体'; // file://字体名称
  //file://创建逻辑字体
  //hTempFont := CreateFontIndirect(FLogFont);
  //file://取得窗口的设备句柄
  //hTempDC := GetDC(panel1.Handle);

{  hTempDC:=Screen.ActiveForm.Canvas.handle;
  SetBkMode(hTempDC, transparent);
  Fontname:= Screen.ActiveForm.Canvas.Font.Name;
  P1.x:=imgSource.Left+FCurrentLabelLeft;
  P1.y:=imgSource.Top+FCurrentLabelTop;
  P1 := PictureMag.ScreenToClient(imgSource.ClientToScreen(P1));
  windows.ClientToScreen(PictureMag.Handle,p1);

  ShowMessage(Inttostr(p1.x));
  ShowMessage(Inttostr(p1.y));
  hTempFont:= CreateFont(0,0, 2700,2700, fw_normal,0, 0,0,1,4,$10,2,4,PChar(Fontname));

  //file://取出窗口设备的当前字体，并替换为新字体
  hPrevFont := SelectObject(hTempDC, hTempFont);
  //file://设置设备窗口的文字色彩
  SetTextColor(hTempDc, clRed);
  //file://输出文字
  TextOut(hTempDc, 30 , 200, PChar(FString), Length(FString));
  //file://恢复原有的字体
  SelectObject(hTempDc, hPrevFont);
  //file://删除逻辑字体
  DeleteObject(hTempFont);
  //file://释放设备接口
  //ReleaseDC(Handle, hTempDC);
}
  hTempDC := pbSource.Canvas.handle;
  SetBkMode(hTempDC, transparent);
  Fontname := pbSource.Canvas.Font.Name;
  P1.x := Label3.Left + 14;
  P1.y := FCurrentLabelTop;

  hTempFont := CreateFont(0, 0, 2700, 2700, fw_Bold, 0, 0, 0, 1, 4, $10, 2, 4, PChar(Fontname));
  hPrevFont := SelectObject(hTempDC, hTempFont);
  TextOut(hTempDC, p1.x, p1.y, PChar(FString), length(FString));
  SelectObject(hTempDC, hPrevFont);
  DeleteObject(hTempFont);
end;

procedure TPictureMag.GetPersonInfoToLabel(FPerNo: string; var FLabelCaption: string; var FLabelName: string);
var MyADOQuery: TADOQuery;
  Flen: integer;
  i: integer;
  TmpId: string;
  TmpName: string;
  NoCaption: string;
  NameCaption: string;
begin
  MyADOQuery := TADOQuery.Create(nil);
  try
    MyADOQuery.Connection := dm.ConnectPhoto;
    MyADOQuery.Close;
    MyADOQuery.SQL.Clear;
    MyADOQuery.SQL.Add('select * from ' + PhotoTableName + ' where ' + StuempNo +
      ' = ' + QuotedStr(FPerNo));
    MyADOQuery.Open;
    if MyADOQuery.RecordCount = 0 then
    begin
      ShowMessage('没有这个人的信息，无法加入信息字幕！');
      Exit;
    end;

    TmpId := Trim(MyADOQuery.FieldByName(StuempNo).AsString);
    TmpName := Trim(MyADOQuery.FieldByName(StuempName).AsString);
    Flen := length(TmpId);
    NoCaption := '';
    for i := 1 to Flen do
    begin
      if i > 1 then NoCaption := NoCaption + #13 + TmpId[i]
      else NoCaption := TmpId[i];
    end;
    //NoCaption:=NoCaption+#13+'/';

    Flen := length(TmpName);
    NameCaption := '';
    for i := 1 to Flen do
    begin
      if i > 1 then
      begin
        if Odd(i) then
        begin
          NameCaption := NameCaption + #13 + Copy(TmpName, i, 2);
        end;
      end
      else
      begin
        NameCaption := Copy(TmpName, i, 2);
      end;
    end;
    FLabelCaption := NoCaption;
    FLabelName := NameCaption;
  finally
    MyADOQuery.Close;
    MyADOQuery.Free;
  end;
end;

procedure TPictureMag.btnLoadClick(Sender: TObject);
begin
  try
    if not OpenPictureDialog.Execute then Exit;
    imgSource.Picture.LoadFromFile(OpenPictureDialog.FileName);
    FScanOperated := True;
    FZoneSelected := False;
    sbSource.Cursor := crCross;
    OP1.x := 0;
    Op1.y := 0;
    Op2.x := 0;
    OP2.y := 0;
  except
    ShowMessage('扫描照片错误！请检查扫描仪连接是否正常。');
  end;
end;

procedure TPictureMag.btnPasteClick(Sender: TObject);
begin
  if not FZoneSelected then
  begin
    ShowMessage('请选定图片区域。');
    Exit;
  end;
  try
    imgDestinate.Canvas.CopyRect(imgDestinate.ClientRect, imgSource.Canvas,
      Rect(P1.x, P1.y, P2.x, P2.y));
    imgDestinate.Update;
  except
    ShowMessage('无效的图片操作。');
  end;
end;

procedure TPictureMag.btnOKClick(Sender: TObject);
begin
  if FZoneSelected then
    ModalResult := mrOK;
end;

procedure TPictureMag.imgSourceClick(Sender: TObject);
begin
  FZoneSelected := (not FZoneSelected) and (FScanOperated);
end;

procedure TPictureMag.imgSourceMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  imgDestinate.Canvas.Refresh;
  OP1 := Point(X, Y);
  OP2 := Point(X, Y);
  DownFlag := True;
  DrawRectangle(pbSource.Canvas);
end;

procedure TPictureMag.imgSourceMouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin
  if not DownFlag or (Shift <> [ssLeft]) then Exit;
  DrawRectangle(pbSource.Canvas);
  OP2 := Point(X, Y);
  DrawRectangle(pbSource.Canvas);
  Exit;
  if FZoneSelected then Exit;
  if not FScanOperated then Exit;

  P1 := Point(X, Y);
  P2 := Point(X + FPhotoWidth, Y + FPhotoHeight);
  if X + FPhotoWidth > sbSource.Width then
  begin
    P1.x := X - FPhotoWidth;
    P2.x := X;
  end;
  if Y + FPhotoHeight > sbSource.Height then
  begin
    P1.y := Y - FPhotoHeight;
    P2.y := Y;
  end;
{
  P1 := Point(X, Y);
  if X + FPhotoWidth > sbSource.Width then P2.x := X - FPhotoWidth else
  begin
    if (Op1.x > P1.x) and (X > FPhotoWidth) then P2.x := X - FPhotoWidth
    else P2.x := X + FPhotoWidth;
  end;

  if Y + FPhotoHeight > sbSource.Height then P2.y := Y - FPhotoHeight else
  begin
    if (Op1.y > P1.y) and (Y > FPhotoHeight) then P2.y := Y - FPhotoHeight
    else P2.y := Y + FPhotoHeight;
  end;
}
  with pbSource.Canvas do
  begin
    Brush.Style := bsClear;
    Pen.Color := clGray;
    Pen.Style := psDot;
    Pen.Mode := pmNot;
    if not ((Op1.x = 0) and (Op1.y = 0) and (Op2.x = 0) and (Op2.y = 0)) then
      Rectangle(OP1.x, OP1.y, OP2.x, OP2.y);
    Rectangle(P1.x, P1.y, P2.x, P2.y);
    OP1 := P1; OP2 := P2;
  end;

  lblPosition.Caption := '(' + IntToStr(P1.x) + ',' + IntToStr(P1.y) + '),(' +
    IntToStr(P2.x) + ',' + IntToStr(P2.y) + ')';
  lblPosition.Update;
end;

procedure TPictureMag.imgSourceMouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
{  sbSource.HorzScrollBar.Position;
  sbSource.VertScrollBar.Position;
}
  if DownFlag then
  begin
    DrawRectangle(pbSource.Canvas);
    //imgDestinate.Canvas.CopyRect(imgDestinate.ClientRect, imgSource.Canvas, Rect(OP1.X, OP1.Y, OP2.X, OP2.Y));
    //imgDestinate.Canvas.Draw(OP1.X, OP1.Y );

  end;
  DownFlag := False;
  imgDestinate.Canvas.Refresh;
end;

procedure TPictureMag.FormClick(Sender: TObject);
begin
  FZoneSelected := (not FZoneSelected) and (FScanOperated);
end;

procedure TPictureMag.FormCreate(Sender: TObject);
const S = '粘贴处';
begin
  sbSource.Cursor := crDefault;
  FZoneSelected := False;
  FScanOperated := False;
  OP1.x := 0;
  Op1.y := 0;
  Op2.x := 0;
  OP2.y := 0;
  FPhotoWidth := 108;
  FPhotoHeight := 125;

  imgSource.Left := 0;
  imgSource.Top := 0;
  imgDestinate.Update;
end;

procedure TPictureMag.Button1Click(Sender: TObject);
var s, t: string;
  Flen: integer;
  TypeStr: string;
begin
  GetPersonInfoToLabel('03320097', s, t);
  TypeStr := '10280';
  Flen := length(TypeStr);
  {for i:=1 to Flen do
  begin
    if i>1 then TmpStr:= TmpStr+#13+ TypeStr[i]
    else TmpStr:= TypeStr[i];
  end;
  }
  SetSpecialFont(TypeStr + s);
  Label3.Caption := t;
end;

procedure TPictureMag.Button2Click(Sender: TObject);
var
  Fullscreen: Tbitmap;
  FullscreenCanvas: TCanvas;
  DC: HDC;
begin
  Fullscreen := TBitmap.Create;
  Fullscreen.Width := Screen.width;
  Fullscreen.Height := Screen.Height;
  DC := GetDC(0);
  FullscreenCanvas := TCanvas.Create;
  FullscreenCanvas.Handle := DC;
  Fullscreen.Canvas.CopyRect(Rect(0, 0, Screen.Width, Screen.Height), FullscreenCanvas,
    Rect(0, 0, Screen.Width, Screen.Height));
  FullscreenCanvas.Free;
  ReleaseDC(0, DC);
  imgDestinate.picture.Bitmap := fullscreen;
  imgDestinate.Width := Fullscreen.Width;
  imgDestinate.Height := Fullscreen.Height;
  Fullscreen.free;
  //self.WindowState := wsMaximized;
  //self.show;
  messagebeep(1);
  foldx := 0;
  foldy := 0;
  imgDestinate.Canvas.Pen.mode := pmMerge; //笔的模式为取反
  imgDestinate.Canvas.pen.color := clnone; //笔为黑色
  imgDestinate.Canvas.pen.Style := psInsideFrame;
  imgDestinate.Canvas.brush.Style := bsClear; //空白刷子
end;

procedure TPictureMag.Button3Click(Sender: TObject);
var
  Width, Height: Integer;
  NewBitmap: TBitmap;
  jpeg: Tjpegimage;
  Fullscreen: Tbitmap;
  FullscreenCanvas: TCanvas;
  DC: HDC;
begin
  Fullscreen := TBitmap.Create;
  Fullscreen.Width := Screen.width;
  Fullscreen.Height := Screen.Height;
  DC := GetDC(0);
  FullscreenCanvas := TCanvas.Create;
  FullscreenCanvas.Handle := DC;
  Fullscreen.Canvas.CopyRect(Rect(0, 0, Screen.Width, Screen.Height), FullscreenCanvas,
    Rect(0, 0, Screen.Width, Screen.Height));
  FullscreenCanvas.Free;
  ReleaseDC(0, DC);
  imgDestinate.picture.Bitmap := fullscreen;
  Fullscreen.free;
  foldx := 0;
  foldy := 0;
  imgDestinate.Canvas.Pen.mode := pmMerge; //笔的模式为取反
  imgDestinate.Canvas.pen.color := clnone; //笔为黑色
  imgDestinate.Canvas.pen.Style := psInsideFrame;
  imgDestinate.Canvas.brush.Style := bsClear; //空白刷子

  with imgDestinate.canvas do
  begin
    MoveTo(foldx, 0);
    LineTo(foldx, screen.height);
    MoveTo(0, foldy);
    LineTo(screen.width, foldy);
  end;
  P1.x := imgSource.Left;
  P1.y := imgSource.Top;
  P2.x := imgSource.Left + imgSource.Width;
  P2.y := imgSource.Top + imgSource.Height;

  P1 := PictureMag.ScreenToClient(imgSource.ClientToScreen(P1));
  P2 := PictureMag.ScreenToClient(imgSource.ClientToScreen(P2));

  windows.ClientToScreen(PictureMag.Handle, p1);
  windows.ClientToScreen(PictureMag.Handle, p2);

  with imgDestinate.canvas do
  begin
    MoveTo(P1.x, 0); //画上新的十字
    LineTo(p1.x, Screen.Height);
    MoveTo(0, p2.y);
    LineTo(Screen.Width, p2.y);
    foldx := P1.x;
    foldy := p2.y;
  end;

  imgDestinate.Canvas.Pen.mode := pmMerge; //笔的模式为取反
  imgDestinate.Canvas.pen.color := clnone; //笔为黑色
  imgDestinate.Canvas.pen.Style := psInsideFrame;
  imgDestinate.Canvas.brush.Style := bsClear; //空白刷子

  imgDestinate.Canvas.Rectangle(p1.x, p1.y, p2.x, p2.y);
  Width := abs(p2.x - p1.x);
  Height := abs(p2.y - p1.y);
  imgDestinate.Width := Width;
  imgDestinate.Height := Height;

  NewBitmap := Tbitmap.create;
  NewBitmap.Width := Width;
  NewBitmap.Height := Height;
  NewBitmap.Canvas.CopyRect
    (Rect(0, 0, width, Height), imgDestinate.Canvas,
    Rect(p1.x, p1.y, p2.x, p2.y)); //拷贝
  imgDestinate.Picture.Bitmap := NewBitmap; //放到CatchScreenForm的ShowImage上
  NewBitmap.Free;

  try
    jpeg := Tjpegimage.Create;
    // 动态创建Tjpegimage对象
    jpeg.Assign(imgDestinate.Picture.Bitmap);
    jpeg.SaveToFile(ChangeFileExt('C:\Documents and Settings\Sophie\My Documents\My Skype Pictures\03320097_1',
      '.jpg'));
    // 保存jpeg
  finally
    jpeg.Free;
    // 释放jpeg
  end;
end;

end.
