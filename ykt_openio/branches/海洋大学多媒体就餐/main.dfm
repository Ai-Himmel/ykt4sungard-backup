object mainfrm: Tmainfrm
  Left = 292
  Top = 157
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #22810#23186#20307#35748#35777
  ClientHeight = 466
  ClientWidth = 862
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  OnClose = FormClose
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object mainp: TPanel
    Left = 0
    Top = 0
    Width = 862
    Height = 466
    Align = alClient
    TabOrder = 0
    object Label1: TLabel
      Left = 1224
      Top = 8
      Width = 32
      Height = 13
      Caption = 'Label1'
      Visible = False
    end
    object photo: TPanel
      Left = 208
      Top = 113
      Width = 193
      Height = 225
      TabOrder = 0
      object Image1: TImage
        Left = 1
        Top = 1
        Width = 191
        Height = 223
        Align = alClient
        Center = True
        Stretch = True
      end
    end
    object messagep: TPanel
      Left = 432
      Top = 113
      Width = 345
      Height = 232
      TabOrder = 1
      object name: TPanel
        Left = 16
        Top = 48
        Width = 281
        Height = 65
        Caption = #22995#21517#65306#29579#23567#20108
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -35
        Font.Name = #21326#25991#23435#20307
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
      end
      object studentno: TPanel
        Left = 16
        Top = 136
        Width = 321
        Height = 65
        Caption = #23398#24037#21495#65306'8939293909'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -35
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 1
      end
    end
    object welcome: TPanel
      Left = 1
      Top = 400
      Width = 860
      Height = 65
      Align = alBottom
      Anchors = [akLeft, akTop, akBottom]
      BevelOuter = bvNone
      Caption = #29579#23567#20108#65292#27426#36814#20320#30340#21040#26469#65281
      Ctl3D = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -35
      Font.Name = #38582#20070
      Font.Style = [fsBold]
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 2
    end
    object Panel1: TPanel
      Left = 8
      Top = 8
      Width = 225
      Height = 49
      BevelOuter = bvNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object Panel2: TPanel
      Left = 248
      Top = 8
      Width = 225
      Height = 49
      BevelOuter = bvNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object Panel3: TPanel
      Left = 488
      Top = 8
      Width = 361
      Height = 49
      BevelOuter = bvNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
      TabOrder = 5
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 136
    Top = 24
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 10000
    OnTimer = Timer2Timer
    Left = 232
    Top = 24
  end
end
