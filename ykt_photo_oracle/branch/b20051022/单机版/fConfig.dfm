object frmConfig: TfrmConfig
  Left = 365
  Top = 210
  Width = 329
  Height = 265
  BorderIcons = [biSystemMenu]
  Caption = '配置信息'
  Color = clInfoBk
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
    Top = 97
    Width = 23
    Height = 22
    Caption = '...'
    OnClick = btnSrcClick
  end
  object btnDst: TSpeedButton
    Left = 281
    Top = 150
    Width = 23
    Height = 22
    Caption = '...'
    OnClick = btnDstClick
  end
  object lbl1: TLabel
    Left = 16
    Top = 75
    Width = 98
    Height = 14
    Caption = '下载图象的目录'
  end
  object lbl2: TLabel
    Left = 16
    Top = 131
    Width = 98
    Height = 14
    Caption = '本地保存的目录'
  end
  object lbl3: TLabel
    Left = 16
    Top = 8
    Width = 70
    Height = 14
    Caption = '文件名前缀'
  end
  object lbl4: TLabel
    Left = 184
    Top = 8
    Width = 56
    Height = 14
    Caption = '数字位数'
  end
  object edtSrcDir: TEdit
    Left = 16
    Top = 98
    Width = 264
    Height = 22
    TabOrder = 0
  end
  object edtDstDir: TEdit
    Left = 16
    Top = 152
    Width = 264
    Height = 22
    TabOrder = 1
  end
  object edtPreName: TEdit
    Left = 16
    Top = 29
    Width = 121
    Height = 22
    TabOrder = 2
  end
  object edtNumLen: TEdit
    Left = 183
    Top = 29
    Width = 121
    Height = 22
    TabOrder = 3
  end
  object btnOk: TButton
    Left = 107
    Top = 193
    Width = 75
    Height = 25
    Caption = '确定'
    TabOrder = 4
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 230
    Top = 192
    Width = 75
    Height = 25
    Caption = '取消'
    TabOrder = 5
    OnClick = btnCancelClick
  end
  object grp1: TGroupBox
    Left = 15
    Top = 174
    Width = 290
    Height = 8
    TabOrder = 6
  end
  object GroupBox1: TGroupBox
    Left = 15
    Top = 57
    Width = 290
    Height = 8
    TabOrder = 7
  end
end
