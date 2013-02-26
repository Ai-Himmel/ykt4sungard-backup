object mainfrm: Tmainfrm
  Left = 197
  Top = 146
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #22810#23186#20307#35748#35777
  ClientHeight = 560
  ClientWidth = 804
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
    Width = 804
    Height = 560
    Align = alClient
    TabOrder = 0
    object Panel1: TPanel
      Left = 1
      Top = 1
      Width = 802
      Height = 49
      Align = alTop
      BevelOuter = bvNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 361
        Height = 49
        BevelOuter = bvNone
        Caption = #26102#38388#65306
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -24
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
    end
    object Panel2: TPanel
      Left = 1
      Top = 50
      Width = 802
      Height = 468
      Align = alClient
      Caption = 'Panel2'
      TabOrder = 1
      object photo: TPanel
        Left = 1
        Top = 1
        Width = 362
        Height = 466
        Align = alClient
        Caption = #26412#20154#26080#29031#29255
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -48
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object Image1: TImage
          Left = 1
          Top = 1
          Width = 360
          Height = 464
          Align = alClient
          Center = True
          Stretch = True
        end
      end
      object messagep: TPanel
        Left = 363
        Top = 1
        Width = 438
        Height = 466
        Align = alRight
        TabOrder = 1
        object philab: TLabel
          Left = 64
          Top = 78
          Width = 64
          Height = 21
          Caption = #21345'    '#21495
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = #21326#25991#23435#20307
          Font.Style = [fsBold]
          ParentFont = False
        end
        object name: TPanel
          Left = 64
          Top = 248
          Width = 321
          Height = 65
          Alignment = taLeftJustify
          Caption = '    '#22995#21517#65306#29579#23567#20108
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = #21326#25991#23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
        end
        object department: TPanel
          Left = 64
          Top = 152
          Width = 321
          Height = 65
          Alignment = taLeftJustify
          Caption = '    '#37096#38376#65306#26080
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = #21326#25991#23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
        end
        object phiinput: TEdit
          Left = 152
          Top = 72
          Width = 233
          Height = 29
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = #21326#25991#23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
        end
        object studentno: TPanel
          Left = 62
          Top = 347
          Width = 321
          Height = 65
          Alignment = taLeftJustify
          Caption = '    '#23398#24037#21495#65306'8939293909'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = #21326#25991#23435#20307
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
        end
      end
    end
    object welcome: TPanel
      Left = 1
      Top = 518
      Width = 802
      Height = 41
      Align = alBottom
      Caption = #20320#22909#65292#27426#36814#20320#30340#21040#26469
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -35
      Font.Name = #21326#25991#23435#20307
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 128
    Top = 144
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 10000
    OnTimer = Timer2Timer
    Left = 216
    Top = 152
  end
end
