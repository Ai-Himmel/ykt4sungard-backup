unit ksPicHandler;
 
{ ***********************************************************************
  Copyright (c) 2005 �Ϻ��������˴��������޹�˾
  ��    ��: ����ͼ���ļ�����Ƭ���������ţ��ü�����ת�ȡ�Ŀǰ�����ͼ���ļ�
            �ĸ�ʽ��JPEG��
  ��    ��: Haifeng Zhu
  ��������: '2005-04-30'
  �޸�����:
  ��    ��: Ver 1.0
  ��    ��:
  ************************************************************************ }

interface

uses
  Classes, Windows, ExtCtrls, JPEG, Graphics;

type
  TksPicHandler = class(TPersistent)
  private
    FImage: TImage;                 // �ⲿת����û������е�ͼ��ؼ�
    FJPEG: TJPEGImage;              // װ����Ƭ�� TJPEGImage ����
    FBitmap: TBitmap;               // ��Ƭ�������ʾ��λͼ
    FPixelsW, FPixelsH: Integer;    // ��Ƭ�ߴ�

    FFrame, FOldFrame: TRect;       // ���, ���ڲü�
    FAngle: Real;                   // ��ת�Ƕ�

    FOldWidth, FOldHeight: Integer; // FImage �ĳ�ʼλ�ü���С

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
  PicPixels: array of Integer;     // ԭʼ��Ƭ������ֵ

{ TPicHandler }

procedure TksPicHandler.Init;
// ��������Ƭǰ�ĳ�ʼ��
begin
  FImage.Left := 0;
  FImage.Top := 0;
  FImage.Width := FOldWidth;
  FImage.Height := FOldHeight;
  FFrame := FOldFrame;
  FAngle := 0;
end;

function TksPicHandler.View2Pic(Value: Integer): Integer;
// �û������е�λ�ö�Ӧ����Ƭλͼ�е�λ��
begin
  Result := (Value * FPixelsW) div (FImage.Width);
end;

constructor TksPicHandler.Create(AImage: TImage);
// AImage �û������е�ͼ��ؼ�
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
// �������, ���ڲü�
begin
  FOldFrame := ARect;
  FFrame := FOldFrame;
end;

procedure TksPicHandler.LoadFromFile(FileName: string);
// ������Ƭ�ļ�
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
  // ����ֵ����һά���Ķ�ά������
  SetLength(PicPixels, FPixelsW * FPixelsH);
  for X := 0 to FPixelsW - 1 do
    for Y := 0 to FPixelsH - 1 do
      PicPixels[X*FPixelsH + Y] := FBitmap.Canvas.Pixels[X, Y];
  // �û�������ʾ��Ƭ
  FImage.Picture.Bitmap.Assign(FBitmap);
end;

procedure TksPicHandler.SaveToFile(FileName: string);
// ���洦������Ƭ
var
  Bitmap: TBitmap;
  AFrame: TRect;
begin
  // ��òü������
  AFrame.Left := View2Pic(FFrame.Left);
  AFrame.Right := View2Pic(FFrame.Right);
  AFrame.Top := View2Pic(FFrame.Top);
  AFrame.Bottom := View2Pic(FFrame.Bottom);
  // �ü� FBitmap, ������� Bitmap
  Bitmap := TBitmap.Create;
  Bitmap.Width := AFrame.Right - AFrame.Left;
  Bitmap.Height := AFrame.Bottom - AFrame.Top;
  Bitmap.Canvas.CopyRect(Bitmap.Canvas.ClipRect, FBitmap.Canvas, AFrame);
  // ����ü������Ƭ
  FJPEG.Assign(Bitmap);
  FJPEG.SaveToFile(FileName);

  Bitmap.Free;
end;

procedure TksPicHandler.Rotate(Angle: Real);
// ��ת��Ƭ
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
// ������Ƭ
var
  VValue: Integer;
begin
  // ��ֱ���������ֵ
  VValue := Value * 4 div 3;
  // �û�����ͼ��ؼ�������
  FImage.Left := FImage.Left - Value;
  FImage.Top := FImage.Top - VValue;
  FImage.Width := FImage.Width + Value * 2;
  FImage.Height := FImage.Height + VValue * 2;
  FImage.Picture.Bitmap.Assign(FBitmap);
  // �޸����ڲü������
  FFrame.Left := FFrame.Left + Value;
  FFrame.Top := FFrame.Top + VValue;
  FFrame.Right := FFrame.Right + Value;
  FFrame.Bottom := FFrame.Bottom + VValue;

end;
 
procedure TksPicHandler.Move(Offset: TPoint);
// �ƶ���Ƭ
begin
  // �û�����ͼ��ؼ����ƶ�
  FImage.Left := FImage.Left + Offset.x;
  FImage.Top := FImage.Top + Offset.y;
  // �޸����ڲü������
  FFrame.Left := FFrame.Left - Offset.x;
  FFrame.Top := FFrame.Top - Offset.y;
  FFrame.Right := FFrame.Right - Offset.x;
  FFrame.Bottom := FFrame.Bottom - Offset.y;
end;

end.
