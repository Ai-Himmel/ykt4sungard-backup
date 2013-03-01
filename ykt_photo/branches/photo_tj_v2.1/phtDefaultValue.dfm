object frmDefaultValue: TfrmDefaultValue
  Left = 338
  Top = 211
  BorderStyle = bsNone
  Caption = '默认值设置'
  ClientHeight = 327
  ClientWidth = 504
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = '宋体'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefault
  PixelsPerInch = 96
  TextHeight = 12
  object Label1: TLabel
    Left = 16
    Top = 14
    Width = 198
    Height = 12
    Caption = '步骤三：默认值设置 --- 共四个步骤'
  end
  object Shape1: TShape
    Left = 16
    Top = 30
    Width = 198
    Height = 1
    Brush.Style = bsClear
    Pen.Color = clTeal
    Pen.Style = psInsideFrame
  end
  object Shape2: TShape
    Left = 16
    Top = 33
    Width = 198
    Height = 1
    Brush.Style = bsClear
    Pen.Color = clTeal
    Pen.Style = psInsideFrame
  end
  object tsGrid1: TtsGrid
    Left = 72
    Top = 80
    Width = 361
    Height = 209
    CheckBoxStyle = stCheck
    Cols = 3
    DefaultRowHeight = 18
    HeadingFont.Charset = ANSI_CHARSET
    HeadingFont.Color = clWindowText
    HeadingFont.Height = -12
    HeadingFont.Name = '宋体'
    HeadingFont.Style = []
    HeadingHeight = 19
    ParentShowHint = False
    Rows = 1
    ShowHint = True
    StoreData = True
    TabOrder = 0
    Version = '2.01'
    ColProperties = <
      item
        DataCol = 1
        Col.Color = clInactiveBorder
        Col.Heading = '字段名称'
        Col.HeadingHorzAlignment = htaCenter
        Col.HeadingVertAlignment = vtaCenter
        Col.ReadOnly = True
        Col.Width = 129
      end
      item
        DataCol = 2
        Col.Color = clInactiveBorder
        Col.Heading = '数据类型'
        Col.HeadingHorzAlignment = htaCenter
        Col.HeadingVertAlignment = vtaCenter
        Col.ReadOnly = True
        Col.Width = 75
      end
      item
        DataCol = 3
        Col.Heading = '默认值'
        Col.HeadingHorzAlignment = htaCenter
        Col.HeadingVertAlignment = vtaCenter
        Col.Width = 113
      end>
    Data = {01000000030000000100000000010000000001000000000000000000000000}
  end
  object Memo1: TMemo
    Left = 72
    Top = 48
    Width = 361
    Height = 25
    BorderStyle = bsNone
    Color = clBtnFace
    Lines.Strings = (
      '导入数据中没有提供以下字段的信息，可以为这些字段设置默认值。')
    TabOrder = 1
  end
end
