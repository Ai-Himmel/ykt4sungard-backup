object frmConfig: TfrmConfig
  Left = 365
  Top = 210
  Width = 334
  Height = 252
  Caption = '配置信息'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = '宋体'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 14
  object btnSrc: TSpeedButton
    Left = 281
    Top = 30
    Width = 23
    Height = 22
    Caption = '...'
    OnClick = btnSrcClick
  end
  object btnDst: TSpeedButton
    Left = 281
    Top = 83
    Width = 23
    Height = 22
    Caption = '...'
    OnClick = btnDstClick
  end
  object lbl1: TLabel
    Left = 16
    Top = 8
    Width = 98
    Height = 14
    Caption = '下载图象的目录'
  end
  object lbl2: TLabel
    Left = 16
    Top = 64
    Width = 98
    Height = 14
    Caption = '本地保存的目录'
  end
  object lbl3: TLabel
    Left = 16
    Top = 120
    Width = 70
    Height = 14
    Caption = '文件名前缀'
  end
  object lbl4: TLabel
    Left = 184
    Top = 120
    Width = 56
    Height = 14
    Caption = '数字位数'
  end
  object edtSrcDir: TEdit
    Left = 16
    Top = 31
    Width = 264
    Height = 22
    TabOrder = 0
  end
  object edtDstDir: TEdit
    Left = 16
    Top = 85
    Width = 264
    Height = 22
    TabOrder = 1
  end
  object edtPreName: TEdit
    Left = 16
    Top = 141
    Width = 121
    Height = 22
    TabOrder = 2
  end
  object edtNumLen: TEdit
    Left = 183
    Top = 141
    Width = 121
    Height = 22
    TabOrder = 3
  end
  object btnOk: TButton
    Left = 107
    Top = 190
    Width = 75
    Height = 25
    Caption = '确定'
    TabOrder = 4
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 230
    Top = 189
    Width = 75
    Height = 25
    Caption = '取消'
    TabOrder = 5
    OnClick = btnCancelClick
  end
  object grp1: TGroupBox
    Left = 15
    Top = 171
    Width = 290
    Height = 8
    TabOrder = 6
  end
end
