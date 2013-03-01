object BatchImport: TBatchImport
  Left = 203
  Top = 180
  Width = 573
  Height = 466
  Caption = 'BatchImport'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = '宋体'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 12
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 565
    Height = 417
    Align = alClient
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 19
      Width = 84
      Height = 12
      Caption = '选择照片文件夹'
    end
    object Label2: TLabel
      Left = 16
      Top = 208
      Width = 78
      Height = 12
      Caption = '当前导入学号:'
    end
    object Label3: TLabel
      Left = 96
      Top = 208
      Width = 89
      Height = 12
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 272
      Top = 208
      Width = 97
      Height = 12
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 192
      Top = 208
      Width = 78
      Height = 12
      Caption = '当前导入姓名:'
    end
    object Label6: TLabel
      Left = 384
      Top = 208
      Width = 78
      Height = 12
      Caption = '当前导入部门:'
    end
    object Label7: TLabel
      Left = 464
      Top = 208
      Width = 78
      Height = 12
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 16
      Top = 232
      Width = 78
      Height = 12
      Caption = '当前导入路径:'
    end
    object Label9: TLabel
      Left = 96
      Top = 232
      Width = 289
      Height = 12
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label10: TLabel
      Left = 344
      Top = 19
      Width = 24
      Height = 12
      Caption = '日期'
    end
    object Label11: TLabel
      Left = 16
      Top = 256
      Width = 49
      Height = 12
      Alignment = taRightJustify
      AutoSize = False
      Caption = '0'
    end
    object Label12: TLabel
      Left = 72
      Top = 256
      Width = 6
      Height = 12
      Caption = '/'
    end
    object Label13: TLabel
      Left = 80
      Top = 256
      Width = 73
      Height = 12
      AutoSize = False
      Caption = '0'
    end
    object Label14: TLabel
      Left = 16
      Top = 280
      Width = 108
      Height = 12
      Caption = '导入过程的错误信息'
    end
    object DirectoryListBox1: TDirectoryListBox
      Left = 112
      Top = 40
      Width = 225
      Height = 153
      FileList = FileListBox1
      ImeName = '拼音加加集合版'
      ItemHeight = 16
      TabOrder = 0
    end
    object FileListBox1: TFileListBox
      Left = 344
      Top = 40
      Width = 201
      Height = 153
      ImeName = '拼音加加集合版'
      ItemHeight = 12
      TabOrder = 1
    end
    object DriveComboBox1: TDriveComboBox
      Left = 112
      Top = 16
      Width = 225
      Height = 18
      DirList = DirectoryListBox1
      ImeName = '拼音加加集合版'
      TabOrder = 2
    end
    object Button1: TButton
      Left = 392
      Top = 256
      Width = 75
      Height = 25
      Caption = '导入'
      TabOrder = 3
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 472
      Top = 256
      Width = 75
      Height = 25
      Caption = '返回'
      TabOrder = 4
      OnClick = Button2Click
    end
    object dtp_date: TDateTimePicker
      Left = 376
      Top = 16
      Width = 90
      Height = 20
      CalAlignment = dtaLeft
      Date = 38366.6800549421
      Time = 38366.6800549421
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = '拼音加加集合版'
      Kind = dtkDate
      ParseInput = False
      TabOrder = 5
    end
    object dtp_time: TDateTimePicker
      Left = 464
      Top = 16
      Width = 81
      Height = 20
      CalAlignment = dtaLeft
      Date = 38366.6800549421
      Time = 38366.6800549421
      DateFormat = dfShort
      DateMode = dmUpDown
      ImeName = '拼音加加集合版'
      Kind = dtkTime
      ParseInput = False
      TabOrder = 6
    end
    object ListBox1: TListBox
      Left = 16
      Top = 296
      Width = 529
      Height = 97
      ImeName = '拼音加加集合版'
      ItemHeight = 12
      TabOrder = 7
    end
  end
  object ProgressBar1: TProgressBar
    Left = 0
    Top = 417
    Width = 565
    Height = 22
    Align = alBottom
    Min = 0
    Max = 100
    TabOrder = 1
  end
  object DataSource1: TDataSource
    Left = 200
    Top = 136
  end
  object ADOQuery2: TADOQuery
    Connection = dm.ADOConnection1
    LockType = ltUnspecified
    Parameters = <>
    Left = 232
    Top = 137
  end
  object ADOQuery1: TADOQuery
    AutoCalcFields = False
    Connection = dm.ADOConnection1
    CursorType = ctUnspecified
    MarshalOptions = moMarshalModifiedOnly
    EnableBCD = False
    ParamCheck = False
    Parameters = <>
    Left = 168
    Top = 137
  end
end
