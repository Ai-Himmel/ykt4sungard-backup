object Form1: TForm1
  Left = 225
  Top = 202
  Width = 696
  Height = 480
  Caption = 'Form1'
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
    Width = 688
    Height = 97
    Align = alTop
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 0
    object Label1: TLabel
      Left = 32
      Top = 24
      Width = 42
      Height = 13
      Caption = '学工号'
    end
    object Label2: TLabel
      Left = 192
      Top = 24
      Width = 28
      Height = 13
      Caption = '院系'
    end
    object Label3: TLabel
      Left = 400
      Top = 24
      Width = 28
      Height = 13
      Caption = '专业'
    end
    object Combo_academy: TComboBox
      Left = 232
      Top = 19
      Width = 145
      Height = 21
      ItemHeight = 13
      TabOrder = 0
    end
    object Combo_Spec: TComboBox
      Left = 440
      Top = 19
      Width = 145
      Height = 21
      ItemHeight = 13
      TabOrder = 1
    end
    object Edit1: TEdit
      Left = 80
      Top = 19
      Width = 89
      Height = 21
      TabOrder = 2
    end
    object BitBtn1: TBitBtn
      Left = 416
      Top = 56
      Width = 75
      Height = 25
      Caption = 'BitBtn1'
      TabOrder = 3
      OnClick = BitBtn1Click
    end
    object BitBtn2: TBitBtn
      Left = 504
      Top = 56
      Width = 75
      Height = 25
      Caption = 'BitBtn2'
      TabOrder = 4
    end
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 97
    Width = 688
    Height = 349
    Align = alClient
    DataSource = DataSource1
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object ADOQuery1: TADOQuery
    Connection = PhotoSystem.ADOConnection1
    Parameters = <>
    Left = 320
    Top = 88
  end
  object DataSource1: TDataSource
    DataSet = ADOQuery1
    Left = 280
    Top = 88
  end
end
