inherited faqhQuerySpeInfoByOther: TfaqhQuerySpeInfoByOther
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 453
    Width = 700
    Height = 36
    inherited btnQuery: TBitBtn
      Left = 525
      Top = 5
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 610
      Top = 5
    end
  end
  inherited Grid: TRzDBGrid
    Top = 49
    Width = 700
    Height = 404
    Columns = <
      item
        Expanded = False
        FieldName = 'scust_no'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = 'רҵ����'
        Width = 90
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ssectypes'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = 'רҵ����'
        Width = 137
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scusttypes'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '��ע'
        Width = 264
        Visible = True
      end>
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 31
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left = 228
      Top = 10
      Width = 48
      Height = 12
      Caption = 'רҵ����'
    end
    object Label2: TLabel
      Left = 427
      Top = 10
      Width = 24
      Height = 12
      Caption = '��ע'
    end
    object WVLabel1: TWVLabel
      Left = 34
      Top = 10
      Width = 48
      Height = 12
      Caption = 'רҵ����'
    end
    object WVEdit1: TWVEdit
      Left = 285
      Top = 5
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<רҵ����>'
      WorkView = WorkView
      FieldName = 'רҵ����'
    end
    object WVEdit2: TWVEdit
      Left = 460
      Top = 5
      Width = 206
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<��ע>'
      WorkView = WorkView
      FieldName = '��ע'
    end
    object WVEdit3: TWVEdit
      Left = 92
      Top = 5
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<רҵ����>'
      WorkView = WorkView
      FieldName = 'רҵ����'
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtObject
        OwnObject = True
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = '@Dataset'
      end
      item
        Name = 'רҵ����'
        Caption = 'רҵ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_no'
      end
      item
        Name = 'רҵ����'
        Caption = 'רҵ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'ssectypes'
      end
      item
        Name = '��ע'
        Caption = '��ע'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scusttypes'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|רҵ����|��ע|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = 'רҵ��Ϣ��������ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'רҵ����'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'רҵ����'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 232
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 264
    Top = 224
  end
end
