inherited faqhBusiReport: TfaqhBusiReport
  Width = 745
  Height = 489
  inherited upnlBottom: TUIPanel
    Top = 452
    Width = 745
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
    Top = 48
    Width = 745
    Height = 404
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Top = 25
      Width = 536
      Height = 379
      DataSource = DataSource
      Columns = <
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Visible = True
        end>
    end
    inherited rmprvwP: TRMPreview
      Top = 25
      Width = 536
      Height = 379
      TabOrder = 3
    end
    inherited RzSizePanel1: TRzSizePanel
      Top = 25
      Height = 379
      TabOrder = 1
      inherited tvTree: TRzTreeView
        Height = 379
        OnClick = tvtreeClick
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
    end
  end
  object Panel1: TPanel [3]
    Left = 0
    Top = 18
    Width = 745
    Height = 30
    Align = alTop
    Color = 16184303
    TabOrder = 1
    object lbl1: TLabel
      Left = 24
      Top = 8
      Width = 48
      Height = 12
      Caption = '��ʼ����'
    end
    object Label1: TLabel
      Left = 200
      Top = 8
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object lbl2: TLabel
      Left = 376
      Top = 8
      Width = 48
      Height = 12
      Caption = '��ʾ����'
      Visible = False
    end
    object edtBeginDate: TWVEdit
      Left = 81
      Top = 4
      Width = 96
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<��ʼ����>'
      WorkView = WorkView
      FieldName = '��ʼ����'
    end
    object edtEndDate: TWVEdit
      Left = 257
      Top = 4
      Width = 96
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object cbbleave: TComboBox
      Left = 432
      Top = 4
      Width = 105
      Height = 20
      ItemHeight = 12
      TabOrder = 2
      Visible = False
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
        Name = '��ʾ����'
        Caption = '��ʾ����'
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
    ID = '�̻������'
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
        ParamName = '��ʾ����'
        FieldName = '��ʾ����'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    DataSource = DataSource
    WorkView = WorkView1
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
    DataSet = zqry1
  end
  inherited SaveDialog: TSaveDialog
    Top = 82
  end
  object zqry1: TZQuery
    Connection = dmReportImp.conSLite
    SQL.Strings = (
      'select * from t_rptaccledger')
    Params = <>
    Left = 408
    Top = 92
  end
  object WorkView1: TWorkView
    WorkFields = <
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
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '������־'
        Caption = '������־'
        FieldType = wftUndefined
        DataType = kdtString
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
        MonitorValueChangedFields = 
          '|�̻���ʶ|���̻���ʶ|�̻�����|�̻����|�Ƿ�Ϊ��������|�Ƿ�ΪҶ��' +
          '��|�̻�״̬|����������|�Ƿ���ȡ�����|У��|��ϵ�˰༶���ź�|��' +
          '������|'
      end>
    Left = 96
    Top = 176
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�̻���Ϣ����Q'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = '�̻���ʶ'
        DefaultValue = 0
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 128
    Top = 176
  end
end
