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
      Left = 372
      Top = 19
      Width = 373
      Height = 415
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
      Left = 372
      Top = 19
      Width = 373
      Height = 415
      TabOrder = 3
    end
    inherited RzSizePanel1: TRzSizePanel
      Top = 19
      Width = 372
      Height = 415
      TabOrder = 1
      inherited tvTree: TRzTreeView
        Left = 56
        Top = 200
        Width = 97
        Height = 81
        Align = alNone
        OnClick = tvCustClick
      end
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 365
        Height = 84
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label9: TLabel
          Left = 9
          Top = 10
          Width = 60
          Height = 12
          Caption = '�����̻���'
        end
        object Label11: TLabel
          Left = 182
          Top = 10
          Width = 60
          Height = 12
          Caption = 'ʡ�̻����'
        end
        object Label12: TLabel
          Left = 21
          Top = 34
          Width = 48
          Height = 12
          Caption = '�̻�����'
        end
        object Label13: TLabel
          Left = 194
          Top = 34
          Width = 48
          Height = 12
          Caption = 'Ӣ������'
        end
        object WVEdit3: TWVEdit
          Left = 72
          Top = 6
          Width = 105
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.�����̻���>'
          WorkView = WorkView4
          FieldName = '��ѯ.�����̻���'
        end
        object WVEdit1: TWVEdit
          Left = 246
          Top = 6
          Width = 107
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.ʡ�̻����>'
          WorkView = WorkView4
          FieldName = '��ѯ.ʡ�̻����'
        end
        object WVEdit2: TWVEdit
          Left = 72
          Top = 30
          Width = 105
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 2
          Text = '<��ѯ.�̻���>'
          WorkView = WorkView4
          FieldName = '��ѯ.�̻���'
        end
        object WVEdit6: TWVEdit
          Left = 246
          Top = 30
          Width = 107
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 3
          Text = '<��ѯ.�̻�Ӣ������>'
          WorkView = WorkView4
          FieldName = '��ѯ.�̻�Ӣ������'
        end
        object btnBusiQ: TBitBtn
          Left = 274
          Top = 54
          Width = 79
          Height = 25
          Hint = '����'
          Caption = '�̻���ѯ'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
          OnClick = btnBusiQClick
        end
      end
      object lvBusi: TRzListView
        Left = 0
        Top = 84
        Width = 365
        Height = 331
        Align = alClient
        Columns = <
          item
            Caption = '�̻����'
            Width = 70
          end
          item
            Caption = '�̻�����'
            Width = 120
          end
          item
            Caption = '�����̻���'
            Width = 100
          end
          item
            Caption = 'ʡ�̻����'
            Width = 100
          end
          item
            Caption = '�̻�����'
            Width = 100
          end
          item
            Caption = '��ҵ����'
            Width = 5
          end>
        FlatScrollBars = True
        GridLines = True
        RowSelect = True
        TabOrder = 2
        ViewStyle = vsReport
        OnClick = lvBusiClick
      end
    end
    object pnl1: TPanel
      Left = 0
      Top = 0
      Width = 745
      Height = 19
      Align = alTop
      Alignment = taLeftJustify
      BevelOuter = bvNone
      Color = 15458000
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      object lbl2: TLabel
        Left = 480
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
        Visible = False
      end
      object cbbleave: TComboBox
        Left = 536
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
        Visible = False
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
  object ztbl1: TZTable
    Connection = dmReportImp.conSLite
    SortedFields = 'SORTID'
    TableName = 't_rptaccledger'
    IndexFieldNames = 'SORTID Asc'
    Left = 408
    Top = 86
  end
  object WorkView4: TWorkView
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
        DataField = '@Return'
      end
      item
        Name = '������Ϣ'
        Caption = '������Ϣ'
        FieldType = wftUndefined
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
        Name = '��ѯ�����'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '�������.����'
        Caption = '�������.����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '1'
      end
      item
        Name = '�������.ɾ��'
        Caption = '�������.ɾ��'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '2'
      end
      item
        Name = '�������.�޸�'
        Caption = '�������.�޸�'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '3'
      end
      item
        Name = '������־'
        Caption = '������־'
        FieldType = wftUndefined
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
        Name = '��ѯ.�̻����'
        Caption = '��ѯ.�̻����'
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
        Name = '��ѯ.�����̻���'
        Caption = '��ѯ.�����̻���'
        FieldType = wftUndefined
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
        Name = '��ѯ.�̻�״̬'
        Caption = '��ѯ.�̻�״̬'
        FieldType = wftUndefined
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
        Name = '��ѯ.ʡ�̻����'
        Caption = '��ѯ.ʡ�̻����'
        FieldType = wftUndefined
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
        Name = '��ѯ.�̻���'
        Caption = '��ѯ.�̻���'
        FieldType = wftUndefined
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
        Name = '��ѯ.�̻�Ӣ������'
        Caption = '��ѯ.�̻�Ӣ������'
        FieldType = wftUndefined
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
        Name = '��ѯ.�̻����'
        Caption = '��ѯ.�̻����'
        FieldType = wftUndefined
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
        Name = '��ѯ.�̻�����'
        Caption = '��ѯ.�̻�����'
        FieldType = wftUndefined
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
        Name = '��ѯ.��ҵ����'
        Caption = '��ѯ.��ҵ����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.������־|��ѯ.�̻����|��ѯ.�����̻���|��ѯ.ʡ�̻����|��' +
          'ѯ.�̻���|��ѯ.�̻�Ӣ������|��ѯ.�̻����|��ѯ.�̻�����|��ѯ.��' +
          'ҵ����|��ѯ.��ϵ��|��ѯ.�绰|��ѯ.�ֻ�|��ѯ.��������|��ѯ.����|' +
          '��ѯ.Ӫҵ��ַ|��ѯ.��������|��ѯ.�������|��ѯ.��������|��ѯ.��' +
          '���˺�|��ѯ.�����ʻ���|��ѯ.���к�|��ѯ.��������|��ѯ.��������|' +
          '��ѯ.����״̬|��ѯ.�̻�״̬|'
      end
      item
        MonitorValueChangedFields = 
          '|�̻����|�����̻���|ʡ�̻����|�̻���|�̻�Ӣ������|�̻����|��' +
          '������|��ҵ����|��ϵ��|�绰|�ֻ�|��������|����|Ӫҵ��ַ|��������' +
          '|�������|��������|�����˺�|�����ʻ���|���к�|��������|��������|' +
          '����״̬|'
      end>
    Left = 96
    Top = 296
  end
  object QueryRequest: TWVRequest
    WorkView = WorkView4
    ID = '�̻���Ϣά��Q'
    Bindings = <
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
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�̻����'
        FieldName = '��ѯ.�̻����'
      end
      item
        ParamName = '�����̻���'
        FieldName = '��ѯ.�����̻���'
      end
      item
        ParamName = '�̻�״̬'
        FieldName = '��ѯ.�̻�״̬'
      end
      item
        ParamName = 'ʡ�̻����'
        FieldName = '��ѯ.ʡ�̻����'
      end
      item
        ParamName = '�̻���'
        FieldName = '��ѯ.�̻���'
      end
      item
        ParamName = '�̻�Ӣ������'
        FieldName = '��ѯ.�̻�Ӣ������'
      end
      item
        ParamName = '�̻����'
        FieldName = '��ѯ.�̻����'
      end
      item
        ParamName = '�̻�����'
        FieldName = '��ѯ.�̻�����'
      end
      item
        ParamName = '��ҵ����'
        FieldName = '��ѯ.��ҵ����'
      end>
    Left = 128
    Top = 296
  end
end
