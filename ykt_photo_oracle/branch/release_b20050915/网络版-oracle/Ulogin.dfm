object loginForm: TloginForm
  Left = 302
  Top = 238
  Width = 351
  Height = 230
  BorderIcons = []
  Caption = '拍照辅助系统登录窗口'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 343
    Height = 196
    Align = alClient
    BevelInner = bvLowered
    BevelWidth = 2
    TabOrder = 0
    object Label1: TLabel
      Left = 72
      Top = 40
      Width = 52
      Height = 13
      AutoSize = False
      Caption = '操作员：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 72
      Top = 72
      Width = 52
      Height = 13
      AutoSize = False
      Caption = '密  码：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 72
      Top = 104
      Width = 52
      Height = 13
      AutoSize = False
      Caption = '验证码：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Image1: TImage
      Left = 224
      Top = 96
      Width = 57
      Height = 21
    end
    object cbboper: TComboBox
      Left = 136
      Top = 32
      Width = 145
      Height = 21
      ImeName = '拼音加加集合版'
      ItemHeight = 13
      TabOrder = 0
    end
    object edtpwd: TEdit
      Left = 136
      Top = 64
      Width = 145
      Height = 21
      ImeName = '拼音加加集合版'
      PasswordChar = '*'
      TabOrder = 1
      OnKeyUp = edtpwdKeyUp
    end
    object Button1: TButton
      Left = 80
      Top = 144
      Width = 75
      Height = 25
      Caption = '登  录'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 200
      Top = 144
      Width = 75
      Height = 25
      Caption = '取  消'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      OnClick = Button2Click
    end
    object edtRCode: TEdit
      Left = 136
      Top = 96
      Width = 85
      Height = 21
      ImeName = '拼音加加集合版'
      TabOrder = 2
      OnKeyUp = edtpwdKeyUp
    end
  end
  object ADOQuery1: TADOQuery
    Connection = dm.ConnectPhoto
    LockType = ltReadOnly
    Parameters = <>
    Left = 72
    Top = 8
  end
  object ADOQuery2: TADOQuery
    Connection = dm.ConnectPhoto
    LockType = ltReadOnly
    Parameters = <>
    Left = 128
    Top = 8
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 184
    Top = 8
  end
end
