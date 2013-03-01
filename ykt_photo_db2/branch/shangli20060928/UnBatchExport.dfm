object BatchExpot: TBatchExpot
  Left = 151
  Top = 186
  Width = 732
  Height = 480
  Caption = '照片导出'
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
    Width = 724
    Height = 273
    Align = alTop
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 0
    object Label1: TLabel
      Left = 32
      Top = 8
      Width = 49
      Height = 13
      AutoSize = False
      Caption = '学工号：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 368
      Top = 8
      Width = 49
      Height = 13
      AutoSize = False
      Caption = '类  别：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 24
      Top = 176
      Width = 161
      Height = 13
      AutoSize = False
      Caption = '当前要处理的记录数目：'
    end
    object Label6: TLabel
      Left = 184
      Top = 176
      Width = 73
      Height = 13
      AutoSize = False
      Caption = '0'
    end
    object Label7: TLabel
      Left = 32
      Top = 88
      Width = 8
      Height = 39
      Caption = 'S'#13'Q'#13'L'
    end
    object Label8: TLabel
      Left = 24
      Top = 192
      Width = 12
      Height = 52
      Caption = '错'#13'误'#13'提'#13'示'
    end
    object Label9: TLabel
      Left = 24
      Top = 160
      Width = 593
      Height = 13
      AutoSize = False
      Caption = 
        'SQL输入格式（符合where语句后面语法即可，但字段前需要加表名）： t' +
        'ab_pers_dept.dept_id  '
    end
    object lblName: TLabel
      Left = 200
      Top = 8
      Width = 49
      Height = 13
      AutoSize = False
      Caption = '姓  名：'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Edit1: TEdit
      Left = 80
      Top = 3
      Width = 97
      Height = 21
      ImeName = '拼音加加集合版'
      TabOrder = 0
    end
    object BitBtn1: TBitBtn
      Left = 468
      Top = 32
      Width = 65
      Height = 25
      Caption = '查 询'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = BitBtn1Click
    end
    object BitBtn2: TBitBtn
      Left = 541
      Top = 32
      Width = 65
      Height = 25
      Caption = '导 出'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = BitBtn2Click
    end
    object cbtype: TComboBox
      Left = 416
      Top = 3
      Width = 97
      Height = 21
      ImeName = '拼音加加集合版'
      ItemHeight = 13
      TabOrder = 3
      Items.Strings = (
        '教职工'
        '研究生'
        '本专科生')
    end
    object Memo1: TMemo
      Left = 56
      Top = 64
      Width = 649
      Height = 89
      ImeName = '拼音加加集合版'
      Lines.Strings = (
        ' stuemp_no not in('#39#39')')
      TabOrder = 4
    end
    object ListBox1: TListBox
      Left = 40
      Top = 192
      Width = 665
      Height = 73
      ImeName = '拼音加加集合版'
      ItemHeight = 13
      TabOrder = 5
    end
    object Button1: TButton
      Left = 608
      Top = 32
      Width = 65
      Height = 25
      Caption = '退 出'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 6
      OnClick = Button1Click
    end
    object dtpStartDate: TDateTimePicker
      Left = 96
      Top = 35
      Width = 81
      Height = 21
      CalAlignment = dtaLeft
      Date = 38455.7226207986
      Time = 38455.7226207986
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = '拼音加加集合版'
      Kind = dtkDate
      ParseInput = False
      TabOrder = 7
    end
    object dtpEndDate: TDateTimePicker
      Left = 184
      Top = 34
      Width = 81
      Height = 21
      CalAlignment = dtaLeft
      Date = 38455.7231351273
      Time = 38455.7231351273
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = '拼音加加集合版'
      Kind = dtkDate
      ParseInput = False
      TabOrder = 8
    end
    object cbDate: TCheckBox
      Left = 8
      Top = 40
      Width = 73
      Height = 17
      Alignment = taLeftJustify
      Caption = '日期选择'
      TabOrder = 9
    end
    object edtName: TEdit
      Left = 248
      Top = 3
      Width = 97
      Height = 21
      ImeName = '拼音加加集合版'
      TabOrder = 10
    end
    object chk1: TCheckBox
      Left = 296
      Top = 40
      Width = 97
      Height = 17
      Caption = '去除已导出'
      TabOrder = 11
    end
  end
  object ProgressBar1: TProgressBar
    Left = 0
    Top = 433
    Width = 724
    Height = 20
    Align = alBottom
    Min = 0
    Max = 100
    TabOrder = 1
  end
  object DBGridEh1: TDBGridEh
    Left = 0
    Top = 273
    Width = 724
    Height = 160
    Align = alClient
    DataSource = DataSource1
    Flat = True
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = '宋体'
    Font.Style = []
    FooterColor = clWindow
    FooterFont.Charset = ANSI_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -12
    FooterFont.Name = '宋体'
    FooterFont.Style = [fsBold]
    ImeName = '拼音加加集合版'
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentFont = False
    ReadOnly = True
    TabOrder = 2
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clBlue
    TitleFont.Height = -15
    TitleFont.Name = '宋体'
    TitleFont.Style = []
    Columns = <
      item
        EditButtons = <>
        FieldName = 'stuemp_no'
        Footer.Value = '合计：'
        Footer.ValueType = fvtStaticText
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '学工号'
        Width = 60
      end
      item
        EditButtons = <>
        FieldName = 'stuemp_name'
        Footer.FieldName = 'stuemp_no'
        Footer.ValueType = fvtCount
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '姓名'
        Width = 80
      end
      item
        EditButtons = <>
        FieldName = 'in_date'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '年级'
        Width = 40
      end
      item
        EditButtons = <>
        FieldName = 'cut_type'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '类别'
        Width = 100
      end
      item
        EditButtons = <>
        FieldName = 'dept_name'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '一级部门'
        Width = 120
      end
      item
        EditButtons = <>
        FieldName = 's_code'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '二级部门'
        Width = 120
      end>
  end
  object DataSource1: TDataSource
    DataSet = ADOQuery1
    Left = 224
    Top = 96
  end
  object ADOQuery1: TADOQuery
    Connection = dm.ADOConnection1
    LockType = ltUnspecified
    Parameters = <>
    Left = 288
    Top = 97
  end
  object ADOQuery2: TADOQuery
    Connection = dm.ADOConnection1
    LockType = ltUnspecified
    Parameters = <>
    Left = 336
    Top = 97
  end
  object SaveDialog1: TSaveDialog
    Filter = 
      '文本文件|*.txt|网页格式|*.htm|Word格式|*.rtf|Excel格式|*.xls|csv' +
      '|*.csv'
    Left = 384
    Top = 97
  end
  object qry1: TADOQuery
    Connection = dm.ADOConnection1
    LockType = ltUnspecified
    Parameters = <>
    Left = 432
    Top = 97
  end
end
