inherited faqhSubjectBalanceReport: TfaqhSubjectBalanceReport
  Width = 702
  Height = 517
  inherited upnlBottom: TUIPanel
    Top = 480
    Width = 702
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
      Left = 608
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 702
    inherited Image1: TImage
      Width = 702
    end
    inherited LabRecordCount: TLabel
      Visible = False
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 702
    Height = 31
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object lbl1: TLabel
      Left = 32
      Top = 10
      Width = 24
      Height = 12
      Caption = '��Ŀ'
    end
    object lblBusiName: TLabel
      Left = 104
      Top = 7
      Width = 6
      Height = 12
      Font.Charset = GB2312_CHARSET
      Font.Color = clMaroon
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object WVLabel1: TWVLabel
      Left = 290
      Top = 10
      Width = 48
      Height = 12
      Caption = '��ʼ����'
    end
    object WVLabel2: TWVLabel
      Left = 432
      Top = 10
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object edtBeginDate: TWVEdit
      Left = 344
      Top = 6
      Width = 81
      Height = 20
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ReadOnly = False
      TabOrder = 1
      Text = '<��ʼ����>'
      WorkView = WorkView
      FieldName = '��ʼ����'
    end
    object edtEndDate: TWVEdit
      Left = 488
      Top = 6
      Width = 89
      Height = 20
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ReadOnly = False
      TabOrder = 2
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object cbbBusiName: TWVComboBox
      Left = 64
      Top = 5
      Width = 217
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      DropDownCount = 20
      ImeName = '�Ϲ�ƴ�����뷨'
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '��Ŀ��'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-25'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 49
    Width = 702
    Height = 431
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 702
      Height = 431
      Columns = <
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��Ŀ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��Ŀ����'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ڳ��跽���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ڳ��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�跽������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ĩ�跽���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt6'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ĩ�������'
          Width = 80
          Visible = True
        end>
    end
    inherited rmprvwP: TRMPreview
      Width = 702
      Height = 431
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
        Name = '������Ϣ'
        Caption = '������Ϣ'
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
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��Ŀ��'
        Caption = '��Ŀ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
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
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
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
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ʼ����|��������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 156
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '��Ŀ����'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '��Ŀ��'
        FieldName = '��Ŀ��'
      end
      item
        ParamName = '��ʼ����'
        FieldName = '��ʼ����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 192
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'damt1'
        DataPresentType = '����'
      end
      item
        FieldName = 'damt2'
        DataPresentType = '����'
      end
      item
        FieldName = 'damt3'
        DataPresentType = '����'
      end
      item
        FieldName = 'damt4'
        DataPresentType = '����'
      end
      item
        FieldName = 'damt5'
        DataPresentType = '����'
      end
      item
        FieldName = 'damt6'
        DataPresentType = '����'
      end>
    Left = 224
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 344
    Top = 224
  end
  inherited rptReport: TRMReport
    ReportData = {}
  end
  inherited rmDS: TRMDBDataSet
    DataSet = ztbl1
  end
  object ztbl1: TZTable
    Connection = dmReportImp.conSLite
    SortedFields = 'ACCDATE Desc,SUBJNO Asc'
    SortType = stIgnored
    TableName = 'T_RPTSUBJBAL'
    IndexFieldNames = 'ACCDATE Desc,SUBJNO Asc'
    Left = 411
    Top = 92
  end
end
