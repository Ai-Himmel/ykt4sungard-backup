object Form1: TForm1
  Left = 206
  Top = 221
  Width = 365
  Height = 225
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lbl1: TLabel
    Left = 88
    Top = 32
    Width = 36
    Height = 13
    Caption = #23398#24037#21495
  end
  object edt1: TEdit
    Left = 135
    Top = 30
    Width = 121
    Height = 21
    TabOrder = 0
  end
  object btn1: TButton
    Left = 152
    Top = 80
    Width = 75
    Height = 25
    Caption = #26597#35810
    TabOrder = 1
    OnClick = btn1Click
  end
  object btn2: TButton
    Left = 144
    Top = 128
    Width = 75
    Height = 25
    Caption = #20805#20540'1'#20803
    TabOrder = 2
    OnClick = btn2Click
  end
  object bsns1: TBusiness
    AutoConnect = False
    ConnectKind = ckRunningOrNew
    Left = 280
    Top = 40
  end
end
