object Form1: TForm1
  Left = 388
  Top = 269
  BorderStyle = bsDialog
  Caption = 'Form1'
  ClientHeight = 150
  ClientWidth = 289
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = '宋体'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 12
  object Image1: TImage
    Left = 152
    Top = 24
    Width = 73
    Height = 20
  end
  object Label1: TLabel
    Left = 24
    Top = 0
    Width = 169
    Height = 12
    AutoSize = False
    Caption = '生成的验证码在一分钟后过期'
  end
  object Button1: TButton
    Left = 24
    Top = 56
    Width = 75
    Height = 25
    Caption = '生成验证码'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 136
    Top = 104
    Width = 75
    Height = 25
    Caption = '关 闭'
    TabOrder = 1
    OnClick = Button2Click
  end
  object Edit1: TEdit
    Left = 24
    Top = 24
    Width = 121
    Height = 20
    ImeName = '拼音加加集合版'
    TabOrder = 2
    Text = 'Edit1'
  end
  object Button3: TButton
    Left = 24
    Top = 104
    Width = 75
    Height = 25
    Caption = '测 试'
    TabOrder = 3
    OnClick = Button3Click
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 120
    Top = 56
  end
end
