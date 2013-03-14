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
        Title.Caption = '专业代码'
        Width = 90
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ssectypes'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '专业名称'
        Width = 137
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scusttypes'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '备注'
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
      Caption = '专业名称'
    end
    object Label2: TLabel
      Left = 427
      Top = 10
      Width = 24
      Height = 12
      Caption = '备注'
    end
    object WVLabel1: TWVLabel
      Left = 34
      Top = 10
      Width = 48
      Height = 12
      Caption = '专业代码'
    end
    object WVEdit1: TWVEdit
      Left = 285
      Top = 5
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<专业名称>'
      WorkView = WorkView
      FieldName = '专业名称'
    end
    object WVEdit2: TWVEdit
      Left = 460
      Top = 5
      Width = 206
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<备注>'
      WorkView = WorkView
      FieldName = '备注'
    end
    object WVEdit3: TWVEdit
      Left = 92
      Top = 5
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<专业代码>'
      WorkView = WorkView
      FieldName = '专业代码'
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        Caption = '查询结果集'
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
        Name = '专业代码'
        Caption = '专业代码'
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
        Name = '专业名称'
        Caption = '专业名称'
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
        Name = '备注'
        Caption = '备注'
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
        MonitorValueChangedFields = '|专业名称|备注|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '专业信息非主键查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '专业代码'
        FieldName = '专业代码'
      end
      item
        ParamName = '专业名称'
        FieldName = '专业名称'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 232
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 264
    Top = 224
  end
end
