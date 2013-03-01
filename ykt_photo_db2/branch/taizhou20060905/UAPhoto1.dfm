object PhotoSystem: TPhotoSystem
  Left = 244
  Top = 17
  Width = 573
  Height = 739
  Align = alLeft
  Caption = 'PhotoSystem'
  Color = clInfoBk
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnClick = FormClick
  OnCreate = FormCreate
  OnMouseDown = FormMouseDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 565
    Height = 57
    Align = alTop
    Color = clInfoBk
    TabOrder = 0
    object Label1: TLabel
      Left = 32
      Top = 16
      Width = 169
      Height = 27
      AutoSize = False
      Caption = '拍照辅助系统'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -27
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label18: TLabel
      Left = 424
      Top = 16
      Width = 121
      Height = 13
      AutoSize = False
      Caption = '0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label19: TLabel
      Left = 296
      Top = 16
      Width = 113
      Height = 13
      AutoSize = False
      Caption = '已拍过照片的总数是:'
    end
    object Label22: TLabel
      Left = 296
      Top = 40
      Width = 113
      Height = 13
      AutoSize = False
      Caption = '当天拍的照片总数是:'
    end
    object L_Tnum: TLabel
      Left = 424
      Top = 40
      Width = 113
      Height = 13
      AutoSize = False
      Caption = '0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 57
    Width = 565
    Height = 49
    Align = alTop
    Color = clInfoBk
    TabOrder = 1
    object Label2: TLabel
      Left = 176
      Top = 16
      Width = 56
      Height = 13
      Caption = '学/工号 ：'
    end
    object lbl2: TLabel
      Left = 8
      Top = 16
      Width = 36
      Height = 13
      Caption = '校区：'
    end
    object Edit1: TEdit
      Left = 240
      Top = 11
      Width = 113
      Height = 21
      ImeName = '中文 (简体) - 微软拼音'
      TabOrder = 0
      OnKeyUp = Edit1KeyUp
    end
    object Button1: TButton
      Left = 368
      Top = 8
      Width = 75
      Height = 25
      Caption = '查询'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = Button1Click
    end
    object cbbArea: TComboBox
      Left = 48
      Top = 11
      Width = 121
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 2
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 106
    Width = 201
    Height = 587
    Align = alLeft
    Color = clInfoBk
    TabOrder = 2
    object Label3: TLabel
      Left = 8
      Top = 40
      Width = 53
      Height = 12
      Caption = '姓  名：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 8
      Top = 80
      Width = 59
      Height = 12
      Caption = '学/工号：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label5: TLabel
      Left = 8
      Top = 112
      Width = 72
      Height = 12
      Caption = '院系/单位：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label6: TLabel
      Left = 8
      Top = 176
      Width = 53
      Height = 12
      Caption = '类  别：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label10: TLabel
      Left = 8
      Top = 8
      Width = 112
      Height = 16
      AutoSize = False
      Caption = '个人基本信息：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label11: TLabel
      Left = 0
      Top = 504
      Width = 72
      Height = 13
      Caption = '原照片拍于：'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label12: TLabel
      Left = 64
      Top = 34
      Width = 135
      Height = 19
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label13: TLabel
      Left = 64
      Top = 80
      Width = 129
      Height = 12
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label14: TLabel
      Left = 80
      Top = 112
      Width = 113
      Height = 12
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label15: TLabel
      Left = 64
      Top = 176
      Width = 129
      Height = 12
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label16: TLabel
      Left = 8
      Top = 144
      Width = 53
      Height = 12
      Caption = '专  业：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label17: TLabel
      Left = 64
      Top = 144
      Width = 129
      Height = 12
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label20: TLabel
      Left = 80
      Top = 504
      Width = 54
      Height = 13
      AutoSize = False
    end
    object Label21: TLabel
      Left = 144
      Top = 504
      Width = 49
      Height = 13
      AutoSize = False
    end
    object lbl1: TLabel
      Left = 8
      Top = 208
      Width = 65
      Height = 12
      AutoSize = False
      Caption = '在校状态：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblstat: TLabel
      Left = 72
      Top = 208
      Width = 105
      Height = 12
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Panel6: TPanel
      Left = 8
      Top = 248
      Width = 181
      Height = 241
      Caption = '原始照片'
      Color = clBackground
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object Image2: TImage
        Left = 1
        Top = 1
        Width = 179
        Height = 239
        Align = alClient
        Stretch = True
      end
    end
    object DBEdit1: TDBEdit
      Left = 40
      Top = 352
      Width = 137
      Height = 28
      DataSource = DataSource1
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ImeName = '中文 (简体) - 微软拼音'
      ParentFont = False
      TabOrder = 1
      Visible = False
    end
    object DBEdit2: TDBEdit
      Left = 32
      Top = 360
      Width = 129
      Height = 28
      DataSource = DataSource1
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ImeName = '中文 (简体) - 微软拼音'
      ParentFont = False
      TabOrder = 2
      Visible = False
    end
    object Edit5: TEdit
      Left = 40
      Top = 352
      Width = 129
      Height = 28
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ImeName = '中文 (简体) - 微软拼音'
      ParentFont = False
      TabOrder = 3
      Text = 'Edit5'
      Visible = False
    end
    object DBEdit4: TDBEdit
      Left = 40
      Top = 356
      Width = 129
      Height = 28
      DataSource = DataSource1
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ImeName = '中文 (简体) - 微软拼音'
      ParentFont = False
      TabOrder = 4
      Visible = False
    end
    object Edit6: TEdit
      Left = 32
      Top = 344
      Width = 129
      Height = 28
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ImeName = '中文 (简体) - 微软拼音'
      ParentFont = False
      TabOrder = 5
      Text = 'Edit6'
      Visible = False
    end
  end
  object Panel4: TPanel
    Left = 201
    Top = 106
    Width = 364
    Height = 587
    Align = alClient
    Color = clInfoBk
    TabOrder = 3
    object Label8: TLabel
      Left = 8
      Top = 492
      Width = 65
      Height = 13
      AutoSize = False
      Caption = '原文件名'
      Visible = False
    end
    object Label9: TLabel
      Left = 161
      Top = 492
      Width = 72
      Height = 13
      AutoSize = False
      Caption = '改名文件名：'
      Visible = False
    end
    object Label7: TLabel
      Left = 8
      Top = 12
      Width = 72
      Height = 13
      Caption = '相机顺序号：'
    end
    object Button2: TButton
      Left = 216
      Top = 40
      Width = 75
      Height = 25
      Caption = '取照片'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = Button2Click
    end
    object Edit2: TEdit
      Left = 72
      Top = 488
      Width = 86
      Height = 21
      ImeName = '中文 (简体) - 微软拼音'
      TabOrder = 1
      Visible = False
    end
    object Edit3: TEdit
      Left = 232
      Top = 488
      Width = 105
      Height = 21
      ImeName = '中文 (简体) - 微软拼音'
      TabOrder = 2
      Visible = False
    end
    object Button3: TButton
      Left = 72
      Top = 528
      Width = 75
      Height = 25
      Caption = '确认'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 248
      Top = 528
      Width = 75
      Height = 25
      Caption = '取消'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      OnClick = Button4Click
    end
    object Edit4: TEdit
      Left = 88
      Top = 8
      Width = 121
      Height = 21
      ImeName = '中文 (简体) - 微软拼音'
      TabOrder = 5
    end
    object Button5: TButton
      Left = 80
      Top = 40
      Width = 97
      Height = 25
      Caption = '修改相机顺序号'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 6
      OnClick = Button5Click
    end
    object Panel5: TPanel
      Left = 24
      Top = 80
      Width = 301
      Height = 401
      Caption = '新拍照片'
      Color = clSilver
      FullRepaint = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clYellow
      Font.Height = -40
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsItalic]
      ParentFont = False
      TabOrder = 7
      object Image1: TImage
        Left = 1
        Top = 1
        Width = 299
        Height = 399
        Align = alClient
        AutoSize = True
        IncrementalDisplay = True
        Stretch = True
      end
    end
    object Button6: TButton
      Left = 80
      Top = 40
      Width = 49
      Height = 25
      Caption = '确认'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 8
      OnClick = Button6Click
    end
    object Button7: TButton
      Left = 152
      Top = 40
      Width = 49
      Height = 25
      Caption = '取消'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 9
      OnClick = Button7Click
    end
  end
  object ADOQuery1: TADOQuery
    AutoCalcFields = False
    Connection = dm.ADOConnection1
    CursorType = ctUnspecified
    MarshalOptions = moMarshalModifiedOnly
    OnEditError = ADOQuery1EditError
    OnPostError = ADOQuery1PostError
    EnableBCD = False
    ParamCheck = False
    Parameters = <>
    Left = 56
    Top = 9
  end
  object DataSource1: TDataSource
    DataSet = ADOQuery1
    Left = 184
    Top = 9
  end
  object ADOQuery2: TADOQuery
    Connection = dm.ADOConnection1
    LockType = ltUnspecified
    Parameters = <>
    Left = 88
    Top = 9
  end
  object MainMenu1: TMainMenu
    Left = 24
    Top = 9
    object file1: TMenuItem
      Caption = '参数设置'
      object N2: TMenuItem
        Caption = '相机首选项'
        OnClick = N2Click
      end
    end
    object count1: TMenuItem
      Caption = '统计报表'
      object N1: TMenuItem
        Caption = '报表'
        OnClick = N1Click
      end
    end
    object N3: TMenuItem
      Caption = '数据操作'
      object N4: TMenuItem
        Caption = '批量导出'
        OnClick = N4Click
      end
      object N5: TMenuItem
        Caption = '批量导入'
        OnClick = N5Click
      end
    end
  end
  object ADOQuery3: TADOQuery
    Connection = dm.ADOConnection1
    LockType = ltUnspecified
    Parameters = <>
    Left = 120
    Top = 9
  end
  object ADOQuery4: TADOQuery
    Connection = dm.ADOConnection1
    LockType = ltUnspecified
    Parameters = <>
    Left = 153
    Top = 9
  end
  object ADOTable1: TADOTable
    Connection = dm.ADOConnection1
    CursorType = ctUnspecified
    TableName = 'tab_pers_photo'
    Left = 224
    Top = 8
  end
end
