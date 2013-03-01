object frmComplete: TfrmComplete
  Left = 420
  Top = 180
  BorderStyle = bsNone
  Caption = '完成'
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
    Width = 222
    Height = 12
    Caption = '步骤四：完成，导入数据 --- 共四个步骤'
  end
  object Shape1: TShape
    Left = 16
    Top = 30
    Width = 223
    Height = 1
    Brush.Style = bsClear
    Pen.Color = clTeal
    Pen.Style = psInsideFrame
  end
  object Shape2: TShape
    Left = 16
    Top = 33
    Width = 223
    Height = 1
    Brush.Style = bsClear
    Pen.Color = clTeal
    Pen.Style = psInsideFrame
  end
  object Memo1: TMemo
    Left = 56
    Top = 64
    Width = 385
    Height = 65
    BorderStyle = bsNone
    Color = clBtnFace
    Lines.Strings = (
      '已经为导入数据做好准备。'
      '点击完成按钮将进行导入数据的操作。')
    TabOrder = 0
  end
end
