object frmIfRepalce: TfrmIfRepalce
  Left = 320
  Top = 121
  Width = 381
  Height = 361
  BorderIcons = []
  Caption = '确认照片替换'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = '宋体'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 14
  object imgOld: TImage
    Left = 48
    Top = 96
    Width = 120
    Height = 160
    Stretch = True
  end
  object imgNew: TImage
    Left = 208
    Top = 96
    Width = 120
    Height = 160
    Stretch = True
  end
  object Label1: TLabel
    Left = 32
    Top = 24
    Width = 140
    Height = 14
    Caption = '数据库中已有学工号为'
  end
  object lblNum: TLabel
    Left = 176
    Top = 24
    Width = 42
    Height = 14
    Caption = 'lblNum'
  end
  object Label3: TLabel
    Left = 248
    Top = 24
    Width = 84
    Height = 14
    Caption = '的照片数据。'
  end
  object Label4: TLabel
    Left = 32
    Top = 48
    Width = 119
    Height = 14
    Caption = '覆盖以前的数据吗?'
  end
  object Label2: TLabel
    Left = 80
    Top = 72
    Width = 42
    Height = 14
    Caption = '旧照片'
  end
  object Label5: TLabel
    Left = 240
    Top = 72
    Width = 42
    Height = 14
    Caption = '新照片'
  end
  object btnReplace: TButton
    Left = 24
    Top = 280
    Width = 75
    Height = 25
    Caption = '覆盖'
    TabOrder = 0
    OnClick = btnReplaceClick
  end
  object btnAllReplace: TButton
    Left = 104
    Top = 280
    Width = 75
    Height = 25
    Caption = '全部覆盖'
    TabOrder = 1
    OnClick = btnAllReplaceClick
  end
  object btnSkip: TButton
    Left = 184
    Top = 280
    Width = 75
    Height = 25
    Caption = '跳过'
    TabOrder = 2
    OnClick = btnSkipClick
  end
  object btnCancel: TButton
    Left = 272
    Top = 280
    Width = 75
    Height = 25
    Caption = '取消'
    TabOrder = 3
    OnClick = btnCancelClick
  end
end
