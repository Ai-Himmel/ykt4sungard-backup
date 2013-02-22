object SetPix: TSetPix
  Left = 348
  Top = 273
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = '设置'
  ClientHeight = 164
  ClientWidth = 412
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 32
    Width = 60
    Height = 13
    Caption = '照片大小：'
  end
  object Label2: TLabel
    Left = 200
    Top = 32
    Width = 24
    Height = 13
    Caption = '宽度'
  end
  object Label3: TLabel
    Left = 24
    Top = 8
    Width = 65
    Height = 13
    AutoSize = False
    Caption = '单位：MM'
  end
  object Label4: TLabel
    Left = 24
    Top = 64
    Width = 60
    Height = 13
    Caption = '照片位置：'
  end
  object Label5: TLabel
    Left = 189
    Top = 64
    Width = 36
    Height = 13
    Caption = '左边距'
  end
  object Label6: TLabel
    Left = 88
    Top = 64
    Width = 36
    Height = 13
    Caption = '上边距'
  end
  object Label7: TLabel
    Left = 99
    Top = 32
    Width = 24
    Height = 17
    AutoSize = False
    Caption = '高度'
  end
  object Edit1: TEdit
    Left = 128
    Top = 28
    Width = 49
    Height = 21
    ImeName = '中文 (简体) - 微软拼音'
    TabOrder = 0
    OnExit = Edit1Exit
  end
  object Edit2: TEdit
    Left = 232
    Top = 28
    Width = 49
    Height = 21
    ImeName = '中文 (简体) - 微软拼音'
    TabOrder = 1
    OnExit = Edit2Exit
  end
  object Button1: TButton
    Left = 80
    Top = 128
    Width = 75
    Height = 25
    Caption = '确定'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 168
    Top = 128
    Width = 75
    Height = 25
    Caption = '应用'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 304
    Top = 128
    Width = 75
    Height = 25
    Caption = '取消'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = '宋体'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    OnClick = Button3Click
  end
  object Edit3: TEdit
    Left = 128
    Top = 59
    Width = 49
    Height = 21
    ImeName = '中文 (简体) - 微软拼音'
    TabOrder = 5
  end
  object Edit4: TEdit
    Left = 232
    Top = 59
    Width = 49
    Height = 21
    ImeName = '中文 (简体) - 微软拼音'
    TabOrder = 6
  end
  object CheckBox1: TCheckBox
    Left = 312
    Top = 32
    Width = 57
    Height = 17
    Caption = '按比例'
    Checked = True
    State = cbChecked
    TabOrder = 7
  end
  object CheckBox2: TCheckBox
    Left = 16
    Top = 91
    Width = 361
    Height = 22
    Caption = '不打印"姓名、院系、专业、单位、学工号"等提示字段'
    TabOrder = 8
  end
end
