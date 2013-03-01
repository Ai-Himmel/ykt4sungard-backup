object frmDBConnect: TfrmDBConnect
  Left = 341
  Top = 238
  BorderStyle = bsNone
  Caption = '数据源连接'
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
    Left = 14
    Top = 14
    Width = 198
    Height = 12
    Caption = '步骤一：数据源连接 --- 共四个步骤'
  end
  object Label3: TLabel
    Left = 14
    Top = 47
    Width = 48
    Height = 12
    Caption = '数据源：'
  end
  object Label4: TLabel
    Left = 14
    Top = 79
    Width = 24
    Height = 12
    Caption = '表：'
  end
  object Shape1: TShape
    Left = 14
    Top = 30
    Width = 198
    Height = 1
    Brush.Style = bsClear
    Pen.Color = clTeal
    Pen.Style = psInsideFrame
  end
  object Shape2: TShape
    Left = 14
    Top = 33
    Width = 198
    Height = 1
    Brush.Style = bsClear
    Pen.Color = clTeal
    Pen.Style = psInsideFrame
  end
  object lblTotal: TLabel
    Left = 400
    Top = 88
    Width = 66
    Height = 12
    Caption = '共有 条记录'
  end
  object edtDataSource: TEdit
    Left = 62
    Top = 47
    Width = 313
    Height = 20
    Enabled = False
    TabOrder = 0
  end
  object cbTable: TComboBox
    Left = 62
    Top = 79
    Width = 177
    Height = 22
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = '宋体'
    Font.Style = []
    ItemHeight = 14
    ParentFont = False
    TabOrder = 1
    OnChange = cbTableChange
  end
  object grdSource: TDBGrid
    Left = 14
    Top = 112
    Width = 473
    Height = 201
    DataSource = DataSource
    TabOrder = 2
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -12
    TitleFont.Name = '宋体'
    TitleFont.Style = []
  end
  object DataSource: TDataSource
    Left = 400
    Top = 40
  end
end
