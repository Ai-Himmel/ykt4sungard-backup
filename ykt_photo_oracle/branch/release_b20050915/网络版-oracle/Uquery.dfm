object QueryForm: TQueryForm
  Left = 275
  Top = 133
  Width = 696
  Height = 488
  Caption = '��ѯ'
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 688
    Height = 97
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object Label1: TLabel
      Left = 32
      Top = 16
      Width = 53
      Height = 13
      Caption = 'ѧ  �ţ�'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 234
      Top = 16
      Width = 53
      Height = 13
      Caption = '��  ����'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 20
      Top = 40
      Width = 65
      Height = 13
      Caption = 'һ����λ��'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 221
      Top = 40
      Width = 65
      Height = 13
      Caption = '������λ��'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 460
      Top = 16
      Width = 53
      Height = 13
      Caption = '��  ����'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label7: TLabel
      Left = 448
      Top = 40
      Width = 65
      Height = 13
      Caption = '�������'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 20
      Top = 69
      Width = 65
      Height = 13
      Caption = '�Ƿ����գ�'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object edtNo: TEdit
      Left = 80
      Top = 10
      Width = 121
      Height = 21
      ImeName = 'ƴ���ӼӼ��ϰ�'
      TabOrder = 0
    end
    object edtName: TEdit
      Left = 288
      Top = 10
      Width = 121
      Height = 21
      ImeName = 'ƴ���ӼӼ��ϰ�'
      TabOrder = 1
    end
    object cbdept: TComboBox
      Left = 80
      Top = 34
      Width = 121
      Height = 21
      ImeName = 'ƴ���ӼӼ��ϰ�'
      ItemHeight = 13
      TabOrder = 2
    end
    object cbCode: TComboBox
      Left = 288
      Top = 34
      Width = 121
      Height = 21
      ImeName = 'ƴ���ӼӼ��ϰ�'
      ItemHeight = 13
      TabOrder = 3
    end
    object cbnj: TComboBox
      Left = 520
      Top = 10
      Width = 121
      Height = 21
      ImeName = 'ƴ���ӼӼ��ϰ�'
      ItemHeight = 13
      TabOrder = 4
    end
    object cbtype: TComboBox
      Left = 520
      Top = 34
      Width = 121
      Height = 21
      ImeName = 'ƴ���ӼӼ��ϰ�'
      ItemHeight = 13
      TabOrder = 5
    end
    object grPic: TRadioGroup
      Left = 80
      Top = 56
      Width = 209
      Height = 33
      Columns = 3
      ItemIndex = 2
      Items.Strings = (
        '��'
        '��'
        'ȫ��')
      TabOrder = 6
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 392
    Width = 688
    Height = 62
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object Label9: TLabel
      Left = 8
      Top = 16
      Width = 84
      Height = 13
      Caption = '�����ļ�����'
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -13
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object btnQuery: TButton
      Left = 384
      Top = 8
      Width = 65
      Height = 25
      Caption = '&Q�� ѯ'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = btnQueryClick
    end
    object btnExport: TButton
      Left = 456
      Top = 8
      Width = 65
      Height = 25
      Caption = '&D�� ��'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = btnExportClick
    end
    object btnPrint: TButton
      Left = 528
      Top = 8
      Width = 65
      Height = 25
      Caption = '&P�� ӡ'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = btnPrintClick
    end
    object btnExit: TButton
      Left = 600
      Top = 8
      Width = 65
      Height = 25
      Caption = '&X�� ��'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = btnExitClick
    end
    object Button1: TButton
      Left = 280
      Top = 8
      Width = 81
      Height = 25
      Caption = '���֤�˶�'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      OnClick = Button1Click
    end
    object edttitle: TEdit
      Left = 88
      Top = 10
      Width = 129
      Height = 21
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -13
      Font.Name = '����'
      Font.Style = [fsBold]
      ImeName = 'ƴ���ӼӼ��ϰ�'
      ParentFont = False
      TabOrder = 5
    end
    object ProgressBar1: TProgressBar
      Left = 0
      Top = 40
      Width = 688
      Height = 22
      Align = alBottom
      Min = 0
      Max = 100
      TabOrder = 6
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 97
    Width = 688
    Height = 295
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    object DBGridEh1: TDBGridEh
      Left = 0
      Top = 0
      Width = 688
      Height = 295
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
      FooterRowCount = 1
      ImeName = 'ƴ���ӼӼ��ϰ�'
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentFont = False
      ReadOnly = True
      SumList.Active = True
      TabOrder = 0
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
          FieldName = 'sex_name'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = '�Ա�'
          Width = 40
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
          FieldName = 'id2'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = '���֤��'
          Width = 120
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
        end
        item
          EditButtons = <>
          FieldName = 'oper'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = '����Ա'
          Width = 150
        end>
    end
  end
  object ADOQuery1: TADOQuery
    Connection = dm.ConnectPhoto
    Parameters = <>
    Left = 192
    Top = 185
  end
  object DataSource1: TDataSource
    DataSet = ADOQuery1
    Left = 240
    Top = 185
  end
  object PrintDBGridEh1: TPrintDBGridEh
    DBGridEh = DBGridEh1
    Options = [pghFitGridToPageWidth, pghColored, pghFitingByColWidths]
    PageFooter.Font.Charset = DEFAULT_CHARSET
    PageFooter.Font.Color = clWindowText
    PageFooter.Font.Height = -11
    PageFooter.Font.Name = 'MS Sans Serif'
    PageFooter.Font.Style = []
    PageHeader.Font.Charset = ANSI_CHARSET
    PageHeader.Font.Color = clWindowText
    PageHeader.Font.Height = -16
    PageHeader.Font.Name = '����'
    PageHeader.Font.Style = [fsBold]
    Units = MM
    Left = 288
    Top = 185
  end
  object SaveDialog1: TSaveDialog
    Filter = 
      '�ı��ļ�|*.txt|��ҳ��ʽ|*.htm|Word��ʽ|*.rtf|Excel��ʽ|*.xls|csv' +
      '|*.csv'
    Left = 328
    Top = 185
  end
  object qryFilltypeData: TADOQuery
    Connection = dm.ConnectPhoto
    Parameters = <>
    Left = 464
    Top = 233
  end
  object qryFillcodeData: TADOQuery
    Connection = dm.ConnectPhoto
    Parameters = <>
    Left = 520
    Top = 233
  end
  object qryFilldeptData: TADOQuery
    Connection = dm.ConnectPhoto
    Parameters = <>
    Left = 528
    Top = 281
  end
  object qryFillnjData: TADOQuery
    Connection = dm.ConnectPhoto
    Parameters = <>
    Left = 576
    Top = 241
  end
end
