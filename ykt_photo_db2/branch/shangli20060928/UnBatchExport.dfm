object BatchExpot: TBatchExpot
  Left = 151
  Top = 186
  Width = 732
  Height = 480
  Caption = '��Ƭ����'
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
      Caption = 'ѧ���ţ�'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 368
      Top = 8
      Width = 49
      Height = 13
      AutoSize = False
      Caption = '��  ��'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 24
      Top = 176
      Width = 161
      Height = 13
      AutoSize = False
      Caption = '��ǰҪ����ļ�¼��Ŀ��'
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
      Caption = '��'#13'��'#13'��'#13'ʾ'
    end
    object Label9: TLabel
      Left = 24
      Top = 160
      Width = 593
      Height = 13
      AutoSize = False
      Caption = 
        'SQL�����ʽ������where�������﷨���ɣ����ֶ�ǰ��Ҫ�ӱ������� t' +
        'ab_pers_dept.dept_id  '
    end
    object lblName: TLabel
      Left = 200
      Top = 8
      Width = 49
      Height = 13
      AutoSize = False
      Caption = '��  ����'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Edit1: TEdit
      Left = 80
      Top = 3
      Width = 97
      Height = 21
      ImeName = 'ƴ���ӼӼ��ϰ�'
      TabOrder = 0
    end
    object BitBtn1: TBitBtn
      Left = 468
      Top = 32
      Width = 65
      Height = 25
      Caption = '�� ѯ'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
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
      Caption = '�� ��'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
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
      ImeName = 'ƴ���ӼӼ��ϰ�'
      ItemHeight = 13
      TabOrder = 3
      Items.Strings = (
        '��ְ��'
        '�о���'
        '��ר����')
    end
    object Memo1: TMemo
      Left = 56
      Top = 64
      Width = 649
      Height = 89
      ImeName = 'ƴ���ӼӼ��ϰ�'
      Lines.Strings = (
        ' stuemp_no not in('#39#39')')
      TabOrder = 4
    end
    object ListBox1: TListBox
      Left = 40
      Top = 192
      Width = 665
      Height = 73
      ImeName = 'ƴ���ӼӼ��ϰ�'
      ItemHeight = 13
      TabOrder = 5
    end
    object Button1: TButton
      Left = 608
      Top = 32
      Width = 65
      Height = 25
      Caption = '�� ��'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
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
      ImeName = 'ƴ���ӼӼ��ϰ�'
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
      ImeName = 'ƴ���ӼӼ��ϰ�'
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
      Caption = '����ѡ��'
      TabOrder = 9
    end
    object edtName: TEdit
      Left = 248
      Top = 3
      Width = 97
      Height = 21
      ImeName = 'ƴ���ӼӼ��ϰ�'
      TabOrder = 10
    end
    object chk1: TCheckBox
      Left = 296
      Top = 40
      Width = 97
      Height = 17
      Caption = 'ȥ���ѵ���'
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
    Font.Name = '����'
    Font.Style = []
    FooterColor = clWindow
    FooterFont.Charset = ANSI_CHARSET
    FooterFont.Color = clWindowText
    FooterFont.Height = -12
    FooterFont.Name = '����'
    FooterFont.Style = [fsBold]
    ImeName = 'ƴ���ӼӼ��ϰ�'
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentFont = False
    ReadOnly = True
    TabOrder = 2
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clBlue
    TitleFont.Height = -15
    TitleFont.Name = '����'
    TitleFont.Style = []
    Columns = <
      item
        EditButtons = <>
        FieldName = 'stuemp_no'
        Footer.Value = '�ϼƣ�'
        Footer.ValueType = fvtStaticText
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = 'ѧ����'
        Width = 60
      end
      item
        EditButtons = <>
        FieldName = 'stuemp_name'
        Footer.FieldName = 'stuemp_no'
        Footer.ValueType = fvtCount
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '����'
        Width = 80
      end
      item
        EditButtons = <>
        FieldName = 'in_date'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '�꼶'
        Width = 40
      end
      item
        EditButtons = <>
        FieldName = 'cut_type'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '���'
        Width = 100
      end
      item
        EditButtons = <>
        FieldName = 'dept_name'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = 'һ������'
        Width = 120
      end
      item
        EditButtons = <>
        FieldName = 's_code'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = '��������'
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
      '�ı��ļ�|*.txt|��ҳ��ʽ|*.htm|Word��ʽ|*.rtf|Excel��ʽ|*.xls|csv' +
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
