object Form1: TForm1
  Left = 235
  Top = 169
  BorderStyle = bsDialog
  Caption = '照片转换'
  ClientHeight = 451
  ClientWidth = 741
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object lbl1: TLabel
    Left = 8
    Top = 368
    Width = 57
    Height = 13
    AutoSize = False
    Caption = '开始日期'
  end
  object lbl2: TLabel
    Left = 184
    Top = 368
    Width = 57
    Height = 13
    AutoSize = False
    Caption = '结束日期'
  end
  object lblcount: TLabel
    Left = 8
    Top = 392
    Width = 337
    Height = 13
    AutoSize = False
    Caption = '开始日期'
  end
  object pb1: TProgressBar
    Left = 0
    Top = 424
    Width = 741
    Height = 27
    Align = alBottom
    Min = 0
    Max = 100
    TabOrder = 8
  end
  object mmoError: TMemo
    Left = 0
    Top = 0
    Width = 741
    Height = 121
    Align = alTop
    Lines.Strings = (
      '')
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object btn1: TButton
    Left = 456
    Top = 360
    Width = 89
    Height = 25
    Caption = '转换小照片'
    TabOrder = 3
    OnClick = btn1Click
  end
  object dbgrd1: TDBGrid
    Left = 0
    Top = 121
    Width = 741
    Height = 232
    Align = alTop
    DataSource = ds1
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object btn2: TButton
    Left = 368
    Top = 360
    Width = 75
    Height = 25
    Caption = '查询'
    TabOrder = 2
    OnClick = btn2Click
  end
  object dtpBDate: TDateTimePicker
    Left = 72
    Top = 363
    Width = 97
    Height = 21
    CalAlignment = dtaLeft
    Date = 39899.7077043519
    Time = 39899.7077043519
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 6
  end
  object dtpEDate: TDateTimePicker
    Left = 248
    Top = 363
    Width = 97
    Height = 21
    CalAlignment = dtaLeft
    Date = 39899.7077043519
    Time = 39899.7077043519
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 7
  end
  object btn3: TButton
    Left = 560
    Top = 360
    Width = 75
    Height = 25
    Caption = '保存失败信息'
    TabOrder = 4
    OnClick = btn3Click
  end
  object btn4: TButton
    Left = 656
    Top = 360
    Width = 75
    Height = 25
    Caption = '退出'
    TabOrder = 5
    OnClick = btn4Click
  end
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=MSDASQL.1;Persist Security Info=False;Data Source=yktph' +
      'oto'
    LoginPrompt = False
    Mode = cmReadWrite
    Provider = 'MSDASQL.1'
    Left = 80
    Top = 40
  end
  object qry1: TADOQuery
    AutoCalcFields = False
    Connection = ADOConnection1
    CursorType = ctUnspecified
    MarshalOptions = moMarshalModifiedOnly
    EnableBCD = False
    ParamCheck = False
    Parameters = <>
    Left = 128
    Top = 41
  end
  object qry2: TADOQuery
    AutoCalcFields = False
    Connection = ADOConnection1
    CursorType = ctUnspecified
    MarshalOptions = moMarshalModifiedOnly
    EnableBCD = False
    ParamCheck = False
    Parameters = <>
    Left = 168
    Top = 41
  end
  object ds1: TDataSource
    DataSet = qry1
    Left = 200
    Top = 40
  end
  object dlgSave1: TSaveDialog
    Left = 240
    Top = 40
  end
end
