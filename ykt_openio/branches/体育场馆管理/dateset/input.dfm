object inpfrm: Tinpfrm
  Left = 229
  Top = 109
  Width = 722
  Height = 409
  Caption = #26085#25253#34920#26597#35810'    '
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 714
    Height = 375
    Align = alClient
    TabOrder = 0
    object Label2: TLabel
      Left = 64
      Top = 80
      Width = 60
      Height = 13
      Caption = #21307#29983#20195#30721#65306
    end
    object stuno: TLabel
      Left = 400
      Top = 80
      Width = 48
      Height = 13
      Caption = #23398#24037#21495#65306
    end
    object Label5: TLabel
      Left = 66
      Top = 244
      Width = 60
      Height = 13
      Caption = #24320#22987#26085#26399#65306
    end
    object Label7: TLabel
      Left = 269
      Top = 245
      Width = 60
      Height = 13
      Caption = #32467#26463#26085#26399#65306
    end
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 712
      Height = 40
      Align = alTop
      TabOrder = 0
      object Label1: TLabel
        Left = 329
        Top = 12
        Width = 66
        Height = 16
        Caption = #26085#25253#34920#26597#35810
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object doctor: TEdit
      Left = 139
      Top = 74
      Width = 78
      Height = 21
      TabOrder = 1
      Text = 'doctor'
    end
    object studentno: TEdit
      Left = 459
      Top = 74
      Width = 94
      Height = 21
      TabOrder = 2
      Text = 'doctor'
    end
    object oldbegdate: TDateTimePicker
      Left = 135
      Top = 240
      Width = 121
      Height = 21
      Date = 40100.000000000000000000
      Time = 40100.000000000000000000
      DateFormat = dfLong
      TabOrder = 3
    end
    object oldenddate: TDateTimePicker
      Left = 335
      Top = 240
      Width = 121
      Height = 21
      Date = 40100.000000000000000000
      Time = 40100.000000000000000000
      DateFormat = dfLong
      TabOrder = 4
    end
    object Button2: TButton
      Left = 508
      Top = 236
      Width = 105
      Height = 25
      Caption = #21382#21490#26597#35810
      TabOrder = 5
      OnClick = Button2Click
    end
  end
end
