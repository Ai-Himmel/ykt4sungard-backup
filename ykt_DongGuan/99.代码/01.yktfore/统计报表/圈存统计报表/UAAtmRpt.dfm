inherited faqhAtmRpt: TfaqhAtmRpt
  Width = 908
  Height = 489
  inherited upnlBottom: TUIPanel
    Top = 452
    Width = 908
    TabOrder = 3
    inherited tlb1: TRzToolbar
      ToolbarControls = (
        btn100
        btnPageWidth
        rzspcr1
        btnFirst
        btnprevious
        btnNext
        btnLast
        rzspcr2
        btnExpXls
        btnPagePrint
        btnSetup
        rzspcr3
        btnDesign)
    end
    inherited btnQuery: TBitBtn
      Left = 816
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 908
    inherited Image1: TImage
      Width = 908
    end
    inherited LabRecordCount: TLabel
      Visible = False
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 908
    Height = 28
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 14
      Top = 9
      Width = 24
      Height = 12
      Caption = '��־'
    end
    object Label2: TLabel
      Left = 154
      Top = 9
      Width = 36
      Height = 12
      Caption = '������'
    end
    object WVLabel1: TWVLabel
      Left = 498
      Top = 8
      Width = 48
      Height = 12
      Caption = '��ʼ����'
    end
    object WVLabel2: TWVLabel
      Left = 640
      Top = 8
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label3: TLabel
      Left = 314
      Top = 9
      Width = 48
      Height = 12
      Caption = '�ն˱��'
    end
    object cbbOperTrans: TWVComboBox
      Left = 196
      Top = 5
      Width = 109
      Height = 20
      Style = csDropDownList
      Color = clWhite
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ItemHeight = 12
      ParentFont = False
      TabOrder = 3
      WorkView = WorkView
      FieldName = '������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-1'
    end
    object cbbNetInfo: TWVComboBox
      Left = 43
      Top = 5
      Width = 107
      Height = 18
      Style = csOwnerDrawFixed
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      WorkView = WorkView
      FieldName = '��־'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*240'
    end
    object edtBeginDate: TWVEdit
      Left = 552
      Top = 4
      Width = 81
      Height = 20
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ReadOnly = False
      TabOrder = 0
      Text = '<��ʼ����>'
      WorkView = WorkView
      FieldName = '��ʼ����'
    end
    object edtEndDate: TWVEdit
      Left = 696
      Top = 4
      Width = 89
      Height = 20
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ReadOnly = False
      TabOrder = 1
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object WVEdit1: TWVEdit
      Left = 367
      Top = 5
      Width = 122
      Height = 20
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ReadOnly = False
      TabOrder = 4
      Text = '<�ն˱��>'
      WorkView = WorkView
      FieldName = '�ն˱��'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 46
    Width = 908
    Height = 406
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 908
      Height = 406
      Columns = <
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstock_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Semp_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����Ա'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��Ŀ'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ժҪ'
          Width = 100
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'sserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���״���'
          Width = 70
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'sserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 70
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'sserial2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֧��'
          Width = 70
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'sserial3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����'
          Width = 70
          Visible = True
        end>
    end
    inherited rmprvwP: TRMPreview
      Width = 908
      Height = 406
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ʼ����'
        Caption = '��ʼ����'
        FieldType = wftUndefined
        DomainName = '����У��'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��������'
        Caption = '��������'
        FieldType = wftUndefined
        DomainName = '����У��'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��־'
        Caption = '��־'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '������'
        Caption = '������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�ն˱��'
        Caption = '�ն˱��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�����|����Ա��|������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 244
    Top = 135
  end
  inherited MainRequest: TWVRequest
    ID = 'Ȧ��ͳ�Ʊ���'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��ʼ����'
        FieldName = '��ʼ����'
      end
      item
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '�ն˱��'
        FieldName = '�ն˱��'
      end>
    Left = 280
    Top = 136
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'sstock_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '-2'
      end
      item
        FieldName = 'scust_auth'
        DataPresentType = 'idobjects'
        DataPresentParam = '-25'
      end
      item
        FieldName = 'sserial0'
        DataPresentType = '����'
      end
      item
        FieldName = 'sserial1'
        DataPresentType = '����'
      end
      item
        FieldName = 'sserial2'
        DataPresentType = '����'
      end
      item
        FieldName = 'sserial3'
        DataPresentType = '����'
      end>
    Left = 312
    Top = 136
  end
  inherited DataSource: TDataSource
    Left = 344
    Top = 136
  end
  inherited rptReport: TRMReport
    ReportData = {}
  end
  inherited rmDS: TRMDBDataSet
    DataSet = zqry1
  end
  object zqry1: TZQuery
    Connection = dmReportImp.conSLite
    SortType = stIgnored
    SQL.Strings = (
      'select * from t_rptopercash')
    Params = <>
    Left = 411
    Top = 89
  end
end
