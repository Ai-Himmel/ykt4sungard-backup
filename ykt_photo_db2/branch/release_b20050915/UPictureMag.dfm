object PictureMag: TPictureMag
  Left = 184
  Top = 154
  Width = 638
  Height = 401
  Caption = 'PictureMag'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Arial Narrow'
  Font.Style = [fsBold]
  OldCreateOrder = False
  OnClick = FormClick
  OnCreate = FormCreate
  OnMouseDown = imgSourceMouseDown
  OnMouseMove = imgSourceMouseMove
  OnMouseUp = imgSourceMouseUp
  PixelsPerInch = 96
  TextHeight = 16
  object lblPosition: TLabel
    Left = 353
    Top = 47
    Width = 6
    Height = 16
    Caption = '  '
  end
  object Label1: TLabel
    Left = 320
    Top = 48
    Width = 34
    Height = 16
    Caption = 'ÇøÓò'
  end
  object sbDestinate: TScrollBox
    Left = 400
    Top = 27
    Width = 192
    Height = 280
    TabOrder = 0
    object pbDestinate: TPaintBox
      Left = 0
      Top = 0
      Width = 188
      Height = 276
      Align = alClient
    end
    object imgDestinate: TImage
      Left = 0
      Top = 0
      Width = 188
      Height = 276
      Align = alClient
      Transparent = True
    end
  end
  object sbSource: TScrollBox
    Left = 32
    Top = 24
    Width = 196
    Height = 284
    TabOrder = 1
    object pbSource: TPaintBox
      Left = 0
      Top = 0
      Width = 192
      Height = 280
      Align = alClient
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object imgSource: TImage
      Left = 0
      Top = 0
      Width = 192
      Height = 280
      Align = alClient
      AutoSize = True
      OnClick = imgSourceClick
      OnMouseDown = imgSourceMouseDown
      OnMouseMove = imgSourceMouseMove
      OnMouseUp = imgSourceMouseUp
    end
    object Label3: TLabel
      Left = 12
      Top = 124
      Width = 14
      Height = 154
      AutoSize = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clMenu
      Font.Height = -13
      Font.Name = 'ËÎÌå'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
      WordWrap = True
    end
  end
  object btnLoad: TButton
    Left = 312
    Top = 160
    Width = 75
    Height = 25
    Caption = 'btnLoad'
    TabOrder = 2
    OnClick = btnLoadClick
  end
  object btnOK: TButton
    Left = 312
    Top = 224
    Width = 75
    Height = 25
    Caption = 'btnOK'
    TabOrder = 3
    OnClick = btnOKClick
  end
  object btnPaste: TButton
    Left = 312
    Top = 192
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 4
    OnClick = btnPasteClick
  end
  object Button1: TButton
    Left = 312
    Top = 88
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 5
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 312
    Top = 128
    Width = 75
    Height = 25
    Caption = 'Button2'
    TabOrder = 6
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 312
    Top = 288
    Width = 75
    Height = 25
    Caption = 'Button3'
    TabOrder = 7
    OnClick = Button3Click
  end
  object OpenPictureDialog: TOpenPictureDialog
    DefaultExt = 'jpg'
    Filter = 'jpg Files (*.jpg)|*.jpg|bmp Files (*.bmp)|*.bmp'
    Left = 240
    Top = 72
  end
  object SavePictureDialog1: TSavePictureDialog
    Left = 272
    Top = 72
  end
end
