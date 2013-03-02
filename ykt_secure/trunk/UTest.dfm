object FrmTest: TFrmTest
  Left = 198
  Top = 127
  Width = 599
  Height = 370
  Caption = '测试'
  Color = clBtnFace
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = '宋体'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 12
  object Label5: TLabel
    Left = 96
    Top = 88
    Width = 24
    Height = 12
    Caption = '扇区'
  end
  object Label1: TLabel
    Left = 35
    Top = 24
    Width = 60
    Height = 12
    Caption = '主工作密钥'
  end
  object Label2: TLabel
    Left = 48
    Top = 48
    Width = 48
    Height = 12
    Caption = '卡物理ID'
  end
  object Edit1: TEdit
    Left = 88
    Top = 144
    Width = 121
    Height = 20
    CharCase = ecUpperCase
    ImeName = '拼音加加集合版'
    TabOrder = 0
    Text = 'FFFFFFFFFFFF'
    OnChange = Edit1Change
  end
  object Edit2: TEdit
    Left = 88
    Top = 168
    Width = 121
    Height = 21
    AutoSize = False
    CharCase = ecUpperCase
    ImeName = '拼音加加集合版'
    TabOrder = 1
    Text = 'FFFFFFFFFFFF'
    OnChange = Edit2Change
  end
  object SpinEdit3: TSpinEdit
    Left = 40
    Top = 82
    Width = 49
    Height = 21
    MaxValue = 31
    MinValue = 0
    TabOrder = 2
    Value = 2
  end
  object Edit16: TEdit
    Left = 27
    Top = 205
    Width = 265
    Height = 20
    ImeName = '拼音加加集合版'
    TabOrder = 3
  end
  object Edit15: TEdit
    Left = 27
    Top = 229
    Width = 265
    Height = 20
    ImeName = '拼音加加集合版'
    TabOrder = 4
  end
  object Edit14: TEdit
    Left = 27
    Top = 253
    Width = 265
    Height = 20
    ImeName = '拼音加加集合版'
    TabOrder = 5
  end
  object Edit11: TEdit
    Left = 27
    Top = 277
    Width = 94
    Height = 20
    ImeName = '拼音加加集合版'
    TabOrder = 6
  end
  object Edit12: TEdit
    Left = 123
    Top = 277
    Width = 70
    Height = 20
    ImeName = '拼音加加集合版'
    TabOrder = 7
  end
  object Edit13: TEdit
    Left = 195
    Top = 277
    Width = 97
    Height = 20
    ImeName = '拼音加加集合版'
    TabOrder = 8
  end
  object Button1: TButton
    Left = 24
    Top = 304
    Width = 65
    Height = 25
    Caption = '登录扇区'
    TabOrder = 9
    OnClick = Button1Click
  end
  object RadioButton1: TRadioButton
    Left = 24
    Top = 144
    Width = 60
    Height = 17
    Caption = 'KEY-A'
    Checked = True
    TabOrder = 10
    TabStop = True
  end
  object RadioButton2: TRadioButton
    Left = 24
    Top = 168
    Width = 60
    Height = 17
    Caption = 'KEY-B'
    TabOrder = 11
  end
  object ListBox1: TListBox
    Left = 312
    Top = 8
    Width = 265
    Height = 321
    ImeName = '拼音加加集合版'
    ItemHeight = 12
    TabOrder = 12
  end
  object Button2: TButton
    Left = 88
    Top = 304
    Width = 65
    Height = 25
    Caption = '读取数据'
    TabOrder = 13
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 152
    Top = 304
    Width = 67
    Height = 25
    Caption = '写入数据'
    TabOrder = 14
  end
  object Button4: TButton
    Left = 218
    Top = 304
    Width = 75
    Height = 25
    Caption = '搽除数据'
    TabOrder = 15
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 136
    Top = 80
    Width = 137
    Height = 25
    Caption = '生成格式化的KEY'
    TabOrder = 16
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 216
    Top = 144
    Width = 75
    Height = 25
    Caption = '<----复位'
    TabOrder = 17
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 216
    Top = 168
    Width = 75
    Height = 25
    Caption = '<----复位'
    TabOrder = 18
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 136
    Top = 104
    Width = 137
    Height = 25
    Caption = '生成校园卡密钥'
    TabOrder = 19
    OnClick = Button8Click
  end
  object Edit3: TEdit
    Left = 112
    Top = 20
    Width = 129
    Height = 20
    ImeName = '拼音加加集合版'
    TabOrder = 20
  end
  object Button9: TButton
    Left = 248
    Top = 16
    Width = 41
    Height = 25
    Caption = '读取'
    TabOrder = 21
    OnClick = Button9Click
  end
  object Edit4: TEdit
    Left = 112
    Top = 43
    Width = 129
    Height = 20
    ImeName = '拼音加加集合版'
    TabOrder = 22
  end
end
