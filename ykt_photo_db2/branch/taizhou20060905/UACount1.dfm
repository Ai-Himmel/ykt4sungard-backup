object ReportCount1: TReportCount1
  Left = 208
  Top = 184
  Width = 545
  Height = 480
  Caption = 'ReportCount1'
  Color = clInfoBk
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object StringGrid1: TStringGrid
    Left = 0
    Top = 0
    Width = 537
    Height = 393
    Align = alTop
    ColCount = 4
    FixedCols = 0
    TabOrder = 0
    ColWidths = (
      210
      116
      104
      127)
    RowHeights = (
      24
      24
      24
      24
      24)
  end
  object Button1: TButton
    Left = 304
    Top = 416
    Width = 75
    Height = 25
    Caption = '统 计'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = '宋体'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 440
    Top = 416
    Width = 75
    Height = 25
    Caption = '退 出'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = '宋体'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = Button2Click
  end
  object ADOQuery5: TADOQuery
    Connection = dm.ADOConnection1
    LockType = ltUnspecified
    Parameters = <>
    Left = 169
    Top = 10
  end
  object ADOQuery6: TADOQuery
    Connection = dm.ADOConnection1
    LockType = ltUnspecified
    Parameters = <>
    Left = 201
    Top = 10
  end
  object ADOQuery7: TADOQuery
    Connection = dm.ADOConnection1
    LockType = ltUnspecified
    Parameters = <>
    Left = 233
    Top = 10
  end
end
