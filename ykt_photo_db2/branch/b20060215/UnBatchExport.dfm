object BatchExpot: TBatchExpot
  Left = 243
  Top = 148
  Width = 622
  Height = 456
  Caption = 'BatchExpot'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 614
    Height = 313
    Align = alTop
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 0
    object Label1: TLabel
      Left = 32
      Top = 24
      Width = 49
      Height = 13
      AutoSize = False
      Caption = '学/工号'
    end
    object Label2: TLabel
      Left = 192
      Top = 24
      Width = 33
      Height = 13
      AutoSize = False
      Caption = '单位'
    end
    object Label3: TLabel
      Left = 400
      Top = 24
      Width = 33
      Height = 13
      AutoSize = False
      Caption = '专业'
    end
    object Label4: TLabel
      Left = 40
      Top = 56
      Width = 24
      Height = 13
      Caption = '类别'
    end
    object Label5: TLabel
      Left = 32
      Top = 176
      Width = 145
      Height = 13
      AutoSize = False
      Caption = '当前要处理的记录数目：'
    end
    object Label6: TLabel
      Left = 184
      Top = 176
      Width = 129
      Height = 13
      AutoSize = False
      Caption = 'L'
    end
    object Combo_academy: TComboBox
      Left = 232
      Top = 19
      Width = 145
      Height = 21
      ImeName = '拼音加加集合版'
      ItemHeight = 13
      TabOrder = 0
      OnChange = Combo_academyChange
    end
    object Combo_Spec: TComboBox
      Left = 440
      Top = 19
      Width = 145
      Height = 21
      ImeName = '拼音加加集合版'
      ItemHeight = 13
      TabOrder = 1
      OnChange = Combo_SpecChange
    end
    object Edit1: TEdit
      Left = 80
      Top = 19
      Width = 89
      Height = 21
      ImeName = '拼音加加集合版'
      TabOrder = 2
    end
    object BitBtn1: TBitBtn
      Left = 420
      Top = 48
      Width = 75
      Height = 25
      Caption = '查询'
      TabOrder = 3
      OnClick = BitBtn1Click
    end
    object BitBtn2: TBitBtn
      Left = 509
      Top = 48
      Width = 75
      Height = 25
      Caption = '导出'
      TabOrder = 4
      OnClick = BitBtn2Click
    end
    object ComboBox2: TComboBox
      Left = 416
      Top = 139
      Width = 145
      Height = 21
      ImeName = '拼音加加集合版'
      ItemHeight = 13
      TabOrder = 5
      Visible = False
    end
    object ComboBox3: TComboBox
      Left = 432
      Top = 139
      Width = 145
      Height = 21
      ImeName = '拼音加加集合版'
      ItemHeight = 13
      TabOrder = 6
      Visible = False
    end
    object ComboBox1: TComboBox
      Left = 80
      Top = 51
      Width = 89
      Height = 21
      ImeName = '拼音加加集合版'
      ItemHeight = 13
      TabOrder = 7
    end
    object Memo1: TMemo
      Left = 32
      Top = 80
      Width = 561
      Height = 89
      ImeName = '拼音加加集合版'
      Lines.Strings = (
        'SELECT '
        'YKT_CUR.T_CIF_PHOTO.CUT_TYPE, '
        'YKT_CUR.T_CIF_PHOTO.STUEMP_NO, '
        'YKT_CUR.T_CIF_PHOTO.STUEMP_NAME, '
        'YKT_CUR.T_CIF_DEPT.DEPT_NAME,'
        'YKT_CUR.T_CIF_PHOTO.S_CODE,'
        'YKT_CUR.T_CIF_PHOTO.PHOTO_NO, '
        'YKT_CUR.T_CIF_PHOTO.FILENAME '
        'FROM YKT_CUR.T_CIF_PHOTO , YKT_CUR.T_CIF_DEPT  '
        'WHERE YKT_CUR.T_CIF_DEPT.DEPT_CODE=YKT_CUR.T_CIF_PHOTO.DEPT_NAME')
      ScrollBars = ssVertical
      TabOrder = 8
    end
    object ListBox1: TListBox
      Left = 32
      Top = 200
      Width = 561
      Height = 97
      ImeName = '拼音加加集合版'
      ItemHeight = 13
      TabOrder = 9
    end
    object cb_ZDY: TCheckBox
      Left = 192
      Top = 53
      Width = 121
      Height = 17
      Caption = '自定义条件导出'
      TabOrder = 10
    end
  end
  object ProgressBar1: TProgressBar
    Left = 0
    Top = 404
    Width = 614
    Height = 25
    Align = alBottom
    Min = 0
    Max = 100
    TabOrder = 1
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 313
    Width = 614
    Height = 91
    Align = alClient
    DataSource = DataSource1
    ImeName = '拼音加加集合版'
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object DataSource1: TDataSource
    DataSet = ADOQuery1
    Left = 384
    Top = 136
  end
  object ADOQuery1: TADOQuery
    Connection = dm.ADOConnection1
    LockType = ltUnspecified
    Parameters = <>
    Left = 432
    Top = 137
  end
  object ADOQuery2: TADOQuery
    Connection = dm.ADOConnection1
    LockType = ltUnspecified
    Parameters = <>
    Left = 472
    Top = 137
  end
end
