inherited faqhBusiReportDay: TfaqhBusiReportDay
  Width = 745
  Height = 489
  inherited upnlBottom: TUIPanel
    Top = 452
    Width = 745
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
      Left = 648
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 745
    inherited Image1: TImage
      Width = 745
    end
    inherited LabRecordCount: TLabel
      Width = 169
      Visible = False
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 745
    Height = 434
    inherited Grid: TRzDBGrid
      Top = 25
      Width = 536
      Height = 409
      Columns = <
        item
          Expanded = False
          FieldName = 'sbank_acc'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�̻��ʺ�'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�̻���'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ժҪ'
          Width = 150
          Visible = True
        end
        item
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
          Width = 80
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'sserial2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֧��'
          Width = 80
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'sserial3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 80
          Visible = True
        end>
    end
    inherited rmprvwP: TRMPreview
      Top = 25
      Width = 536
      Height = 409
      TabOrder = 3
    end
    inherited RzSizePanel1: TRzSizePanel
      Top = 25
      Height = 409
      TabOrder = 1
      inherited tvTree: TRzTreeView
        Height = 409
        OnClick = tvCustClick
      end
    end
    object pnl1: TPanel
      Left = 0
      Top = 0
      Width = 745
      Height = 25
      Align = alTop
      Alignment = taLeftJustify
      BevelOuter = bvNone
      Color = 15458000
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      object lbl2: TLabel
        Left = 264
        Top = 8
        Width = 48
        Height = 12
        Caption = '��ʾ����'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object cbbleave: TComboBox
        Left = 320
        Top = 3
        Width = 105
        Height = 20
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 0
      end
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
        Name = '�̻��˺�'
        Caption = '�̻��˺�'
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
        DataField = 'vsmess'
      end
      item
        Name = '��ʼ����'
        Caption = '��ʼ����'
        FieldType = wftUndefined
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
        Name = '����'
        Caption = '����'
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
        MonitorValueChangedFields = '|����Ա��|����|�̻��˺�|���|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '�̻����ս����'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�̻��ʺ�'
        FieldName = '�̻��˺�'
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ʼ����'
        FieldName = '��ʼ����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 168
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 208
    Top = 256
  end
  inherited rptReport: TRMReport
    ReportData = {}
  end
  inherited rmDS: TRMDBDataSet
    DataSet = ztbl1
  end
  object WorkView2: TWorkView
    WorkFields = <
      item
        Name = '������'
        Caption = '������'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�̻���ʶ'
        Caption = '�̻���ʶ'
        FieldType = wftUndefined
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
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�̻���ʶ|'
      end>
    Left = 92
    Top = 199
  end
  object QueryRequest2: TWVRequest
    WorkView = WorkView2
    ID = '�̻���Ϣ������ѯ2'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = '�̻���ʶ'
      end>
    Left = 128
    Top = 200
  end
  object ztbl1: TZTable
    Connection = dmReportImp.conSLite
    SortedFields = 'SORTID'
    TableName = 't_rptaccledger'
    IndexFieldNames = 'SORTID Asc'
    Left = 408
    Top = 86
  end
end
