inherited faqhTicketCashReport: TfaqhTicketCashReport
  Width = 654
  Height = 489
  inherited upnlBottom: TUIPanel
    Top = 452
    Width = 654
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
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 654
    inherited Image1: TImage
      Width = 654
    end
    inherited LabRecordCount: TLabel
      Visible = False
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 654
    Height = 28
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 22
      Top = 9
      Width = 36
      Height = 12
      Caption = '�����'
    end
    object Label2: TLabel
      Left = 218
      Top = 9
      Width = 48
      Height = 12
      Caption = '����Ա��'
    end
    object Label3: TLabel
      Left = 426
      Top = 10
      Width = 24
      Height = 12
      Caption = '�ʹ�'
    end
    object cbbOperTrans: TWVComboBox
      Left = 276
      Top = 5
      Width = 136
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ItemHeight = 12
      ParentFont = False
      TabOrder = 1
      WorkView = WorkView
      FieldName = '����Ա��'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-30'
    end
    object cbbNetInfo: TWVComboBox
      Left = 67
      Top = 5
      Width = 136
      Height = 18
      Style = csOwnerDrawFixed
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '�����'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-2'
    end
    object WVComboBox1: TWVComboBox
      Left = 460
      Top = 5
      Width = 85
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
      TabOrder = 2
      WorkView = WorkView
      FieldName = '�ʹ�'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-21'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 46
    Width = 654
    Height = 406
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 654
      Height = 406
      Columns = <
        item
          Expanded = False
          FieldName = 'Sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Visible = False
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
          Width = 100
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
          Width = 60
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'sserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 60
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'sserial2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֧��'
          Width = 60
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'sserial3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����'
          Width = 60
          Visible = True
        end>
    end
    inherited rmprvwP: TRMPreview
      Width = 654
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
        Name = '�����'
        Caption = '�����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '����Ա��'
        Caption = '����Ա��'
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
        GetPrevChar = '*'
      end
      item
        Name = '�ʹ�'
        Caption = '�ʹ�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
    ID = 'Ʊ���ֽ𱨱�'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '����Ա��'
        FieldName = '����Ա��'
      end
      item
        ParamName = '�ʹ�'
        FieldName = '�ʹ�'
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
    SQL.Strings = (
      
        'select t1.accdate,t1.branchno,t1.branchname,t1.opercode,t1.opern' +
        'ame,'
      't1.subjno,t2.subjname,t1.summary,t1.transcnt,t1.inamt,t1.outamt,'
      '(t1.inamt-t1.outamt)balance,t1.begintime,t1.endtime'
      
        'from t_rptopercash t1 left join t_subject t2 on t1.subjno=t2.sub' +
        'jno'
      'order by t1.accdate desc,t1.branchno asc,t1.subjno asc')
    Params = <>
    Left = 403
    Top = 89
  end
end
