unit ksPicHandler;
 
{ ***********************************************************************
  Copyright (c) 2005 上海复旦金仕达计算机有限公司
  描    述: 处理图像文件（照片），如缩放，裁剪，旋转等。目前处理的图像文件
            的格式是JPEG。
  作    者: Haifeng Zhu
  创建日期: '2005-04-30'
  修改日期:
  版    本: Ver 1.0
  改    进:
  ************************************************************************ }

interface

uses
  Classes, Windows, ExtCtrls, JPEG, Graphics;

type
  TksPicHandler = class(TPersistent)
  private
    FImage: TImage;                 // 外部转入的用户界面中的图像控件
    FJPEG: TJPEGImage;              // 装载照片的 TJPEGImage 对象
    FBitmap: TBitmap;               // 照片处理后显示的位图
    FPixelsW, FPixelsH: Integer;    // 照片尺寸

    FFrame, FOldFrame: TRect;       // 相框, 用于裁剪
    FAngle: Real;                   // 旋转角度

    FOldWidth, FOldHeight: Integer; // FImage 的初始位置及大小

    procedure Init;
    function View2Pic(Value: Integer): Integer;
  public
    constructor Create(AImage: TImage);
    destructor Destroy(); override;
    procedure SetFrame(ARect: TRect);

    procedure LoadFromFile(FileName: string);
    procedure SaveToFile(FileName: string);

    procedure Rotate(Angle: Real);
    procedure Zoom(Value: Integer);
    procedure Move(Offset: TPoint);
  end;

implementation

var
  PicPixels: array of Integer;     // 原始照片的像素值

{ TPicHandler }

procedure TksPicHandler.Init;
// 处理新照片前的初始化
begin
  FImage.Left := 0;
  FImage.Top := 0;
  FImage.Width := FOldWidth;
  FImage.Height := FOldHeight;
  FFrame := FOldFrame;
  FAngle := 0;
end;

function TksPicHandler.View2Pic(Value: Integer): Integer;
// 用户界面中的位置对应于照片位图中的位置
begin
  Result := (Value * FPixelsW) div (FImage.Width);
end;

constructor TksPicHandler.Create(AImage: TImage);
// AImage 用户界面中的图像控件
begin
  FJPEG := TJPEGImage.Create;
  FBitmap := TBitmap.Create;
  FImage := AImage;

  FOldWidth := FImage.Width;
  FOldHeight := FImage.Height;
  FAngle := 0;
end;

destructor TksPicHandler.Destroy;
begin
  FJPEG.Free;
  FBitmap.Free;
  inherited;
end;

procedure TksPicHandler.SetFrame(ARect: TRect);
// 设置相框, 用于裁剪
begin
  FOldFrame := ARect;
  FFrame := FOldFrame;
end;

procedure TksPicHandler.LoadFromFile(FileName: string);
// 读入照片文件
var
  X, Y: Integer;
begin
  Init;

  FJPEG.LoadFromFile(FileName);
  FPixelsW := FJPEG.Width;
  FPixelsH := FJPEG.Height;

  FBitmap.Width := FPixelsW;
  FBitmap.Height := FPixelsH;

  FBitmap.Canvas.Draw(0, 0, FJPEG);
  // 像素值存于一维化的二维数组中
  SetLength(PicPixels, FPixelsW * FPixelsH);
  for X := 0 to FPixelsW - 1 do
    for Y := 0 to FPixelsH - 1 do
      PicPixels[X*FPixelsH + Y] := FBitmap.Canvas.Pixels[X, Y];
  // 用户界面显示照片
  FImage.Picture.Bitmap.Assign(FBitmap);
end;

procedure TksPicHandler.SaveToFile(FileName: string);
// 保存处理后的照片
var
  Bitmap: TBitmap;
  AFrame: TRect;
begin
  // 获得裁剪的像框
  AFrame.Left := View2Pic(FFrame.Left);
  AFrame.Right := View2Pic(FFrame.Right);
  AFrame.Top := View2Pic(FFrame.Top);
  AFrame.Bottom := View2Pic(FFrame.Bottom);
  // 裁剪 FBitmap, 结果放入 Bitmap
  Bitmap := TBitmap.Create;
  Bitmap.Width := AFrame.Right - AFrame.Left;
  Bitmap.Height := AFrame.Bottom - AFrame.Top;
  Bitmap.Canvas.CopyRect(Bitmap.Canvas.ClipRect, FBitmap.Canvas, AFrame);
  // 保存裁剪后的照片
  FJPEG.Assign(Bitmap);
  FJPEG.SaveToFile(FileName);

  Bitmap.Free;
end;

procedure TksPicHandler.Rotate(Angle: Real);
// 旋转照片
var
  X0, Y0: Integer;
  COS_ANG, SIN_ANG: Real;
  X, Y, X1, Y1: Integer;
begin
  FAngle := FAngle + Angle;

  X0 := View2Pic((FFrame.Left + FFrame.Right) div 2);
  Y0 := View2Pic((FFrame.Top + FFrame.Bottom) div 2);

  COS_ANG := Cos(FAngle);
  SIN_ANG := Sin(FAngle);

  for X := 0 to FPixelsW - 1 do
    for Y := 0 to FPixelsH - 1 do
    begin   
      X1 := Round((X - X0) * COS_ANG - (Y - Y0) * SIN_ANG) + X0;
      Y1 := Round((X - X0) * SIN_ANG + (Y - Y0) * COS_ANG) + Y0;

      FBitmap.Canvas.Pixels[X1, Y1] := PicPixels[X*FPixelsH + Y];
    end;

  FImage.Picture.Bitmap.Assign(FBitmap);
end;

procedure TksPicHandler.Zoom(Value: Integer);
// 缩放照片
var
  VValue: Integer;
begin
  // 垂直方向的缩放值
  VValue := Value * 4 div 3;
  // 用户界面图像控件的缩放
  FImage.Left := FImage.Left - Value;
  FImage.Top := FImage.Top - VValue;
  FImage.Width := FImage.Width + Value * 2;
  FImage.Height := FImage.Height + VValue * 2;
  FImage.Picture.Bitmap.Assign(FBitmap);
  // 修改用于裁剪的像框
  FFrame.Left := FFrame.Left + Value;
  FFrame.Top := FFrame.Top + VValue;
  FFrame.Right := FFrame.Right + Value;
  FFrame.Bottom := FFrame.Bottom + VValue;

end;
 
procedure TksPicHandler.Move(Offset: TPoint);
// 移动照片
begin
  // 用户界面图像控件的移动
  FImage.Left := FImage.Left + Offset.x;
  FImage.Top := FImage.Top + Offset.y;
  // 修改用于裁剪的像框
  FFrame.Left := FFrame.Left - Offset.x;
  FFrame.Top := FFrame.Top - Offset.y;
  FFrame.Right := FFrame.Right - Offset.x;
  FFrame.Bottom := FFrame.Bottom - Offset.y;
end;

end.
