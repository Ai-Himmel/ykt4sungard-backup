object ReportCount1: TReportCount1
  Left = 276
  Top = 195
  Width = 700
  Height = 480
  Caption = '拍照统计'
  Color = clInfoBk
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
    Width = 692
    Height = 49
    Align = alTop
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 24
      Width = 70
      Height = 13
      AutoSize = False
      Caption = '统计内容：'
    end
    object RadioGroup1: TRadioGroup
      Left = 88
      Top = 8
      Width = 401
      Height = 33
      Columns = 4
      ItemIndex = 0
      Items.Strings = (
        '教职工'
        '博士研究生'
        '研究生'
        '本专科生')
      TabOrder = 0
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 412
    Width = 692
    Height = 41
    Align = alBottom
    TabOrder = 1
    object Button1: TButton
      Left = 456
      Top = 8
      Width = 75
      Height = 25
      Caption = '&S统 计'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 568
      Top = 8
      Width = 75
      Height = 25
      Caption = '&X退 出'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = Button2Click
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 49
    Width = 692
    Height = 363
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    object StringGrid1: TStringGrid
      Left = 0
      Top = 0
      Width = 692
      Height = 363
      Align = alClient
      BorderStyle = bsNone
      DefaultRowHeight = 20
      FixedColor = clInfoBk
      FixedCols = 0
      RowCount = 2
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      ColWidths = (
        189
        111
        104
        130
        122)
    end
  end
  object ADOQuery5: TADOQuery
    Connection = dm.ConnectPhoto
    LockType = ltUnspecified
    Parameters = <>
    Left = 113
    Top = 114
  end
  object ADOQuery6: TADOQuery
    Connection = dm.ConnectPhoto
    LockType = ltUnspecified
    Parameters = <>
    Left = 193
    Top = 114
  end
  object ADOQuery7: TADOQuery
    Connection = dm.ConnectPhoto
    LockType = ltUnspecified
    Parameters = <>
    Left = 265
    Top = 114
  end
end
