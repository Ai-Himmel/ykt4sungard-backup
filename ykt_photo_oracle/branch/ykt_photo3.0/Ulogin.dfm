object loginForm: TloginForm
  Left = 302
  Top = 238
  Width = 351
  Height = 230
  BorderIcons = []
  Caption = #25293#29031#31995#32479#30331#24405
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 335
    Height = 192
    Align = alClient
    BevelInner = bvRaised
    BevelOuter = bvLowered
    Color = 16053492
    TabOrder = 0
    object Label1: TLabel
      Left = 72
      Top = 40
      Width = 60
      Height = 15
      AutoSize = False
      Caption = #25805#20316#21592#65306
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 72
      Top = 72
      Width = 61
      Height = 15
      AutoSize = False
      Caption = #23494'  '#30721#65306
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 72
      Top = 104
      Width = 60
      Height = 15
      AutoSize = False
      Caption = #39564#35777#30721#65306
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
    end
    object Image1: TImage
      Left = 222
      Top = 99
      Width = 58
      Height = 22
    end
    object edtpwd: TEdit
      Left = 136
      Top = 67
      Width = 145
      Height = 23
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ImeName = #25340#38899#21152#21152#38598#21512#29256
      ParentFont = False
      PasswordChar = '*'
      TabOrder = 1
    end
    object btnLogin: TButton
      Left = 136
      Top = 136
      Width = 65
      Height = 25
      Caption = #30331' '#24405
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = btnLoginClick
    end
    object btnExit: TButton
      Left = 216
      Top = 136
      Width = 65
      Height = 25
      Caption = #21462' '#28040
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      OnClick = btnExitClick
    end
    object edtRCode: TEdit
      Left = 136
      Top = 99
      Width = 85
      Height = 23
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ImeName = #25340#38899#21152#21152#38598#21512#29256
      ParentFont = False
      TabOrder = 2
    end
    object edtOper: TEdit
      Left = 136
      Top = 35
      Width = 145
      Height = 23
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ImeName = #25340#38899#21152#21152#38598#21512#29256
      ParentFont = False
      TabOrder = 0
    end
  end
  object qryQuery: TADOQuery
    Connection = frmdm.conn
    LockType = ltReadOnly
    Parameters = <>
    Left = 72
    Top = 8
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 184
    Top = 8
  end
end
