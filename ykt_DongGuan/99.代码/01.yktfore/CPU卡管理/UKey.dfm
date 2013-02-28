object frmKey: TfrmKey
  Left = 413
  Top = 278
  BorderStyle = bsDialog
  Caption = '输入密钥卡口令'
  ClientHeight = 112
  ClientWidth = 259
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object lbl1: TLabel
    Left = 24
    Top = 24
    Width = 89
    Height = 16
    AutoSize = False
    Caption = '密钥卡口令'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
  end
  object edtPwd: TEdit
    Left = 109
    Top = 19
    Width = 108
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MaxLength = 6
    ParentFont = False
    PasswordChar = '*'
    TabOrder = 0
  end
  object btnOk: TButton
    Left = 24
    Top = 62
    Width = 73
    Height = 25
    Caption = '确 定(&O)'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = btnOkClick
  end
  object btnCancle: TButton
    Left = 144
    Top = 62
    Width = 73
    Height = 25
    Caption = '取 消(&C)'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = btnCancleClick
  end
end
