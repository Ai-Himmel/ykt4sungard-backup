inherited faqhSetSpeInfo: TfaqhSetSpeInfo
  Width = 681
  Height = 477
  Caption = '专业信息设置'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 418
        Width = 677
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 416
          Top = 5
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 502
          Top = 5
          Enabled = False
          TabOrder = 1
        end
        inherited btnQuery: TBitBtn [2]
          Left = 330
          Top = 5
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Top = 5
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
          Top = 5
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 104
          Top = 10
          Width = 169
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 49
        Width = 677
        Height = 369
        Columns = <
          item
            Expanded = False
            FieldName = 'scert_no2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '专业代码'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '专业名称'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '最后更新时间'
            Width = 300
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 31
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label1: TLabel
          Left = 34
          Top = 8
          Width = 48
          Height = 12
          Caption = '专业代码'
        end
        object WVLabel1: TWVLabel
          Left = 232
          Top = 8
          Width = 48
          Height = 12
          Caption = '专业名称'
        end
        object WVEdit4: TWVEdit
          Left = 90
          Top = 4
          Width = 120
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.专业代码>'
          WorkView = WorkView
          FieldName = '查询.专业代码'
        end
        object WVEdit5: TWVEdit
          Left = 289
          Top = 4
          Width = 120
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.专业名称>'
          WorkView = WorkView
          FieldName = '查询.专业名称'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 36
        Top = 45
        Width = 60
        Height = 12
        Caption = '专业代码 *'
      end
      object Label3: TLabel [1]
        Left = 36
        Top = 85
        Width = 60
        Height = 12
        Caption = '专业名称 *'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 2
        inherited btnOK: TBitBtn
          Left = 504
          Top = 5
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 587
          Top = 5
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Left = 34
          Top = 5
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object WVEdit3: TWVEdit
        Left = 110
        Top = 80
        Width = 339
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<专业名称>'
        WorkView = WorkView
        FieldName = '专业名称'
        SynchronizeWhenExit = True
      end
      object WVEdit2: TWVEdit
        Left = 110
        Top = 40
        Width = 339
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 0
        Text = '<专业代码>'
        WorkView = WorkView
        FieldName = '专业代码'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 204
    Top = 335
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '返回码'
        Caption = '返回码'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '返回信息'
        Caption = '返回信息'
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
        Name = '查询结果集'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '查询.专业名称'
        Caption = '查询.专业名称'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.专业代码'
        Caption = '查询.专业代码'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '操作类别'
        Caption = '操作类别'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '1'
        GroupIndex = 1
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
        DataField = 'scert_no2'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|查询.专业代码|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|专业代码|专业名称|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 71
    Top = 336
  end
  inherited QueryRequest: TWVRequest
    ID = '专业信息非主键查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '专业代码'
        FieldName = '查询.专业代码'
      end
      item
        ParamName = '专业名称'
        FieldName = '查询.专业名称'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end>
    Left = 168
    Top = 296
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 104
    Top = 335
  end
  inherited AddRequest: TWVRequest
    ID = '专业信息设置'
    Bindings = <
      item
        ParamName = '专业代码'
        FieldName = '专业代码'
      end
      item
        ParamName = '专业名称'
        FieldName = '专业名称'
      end
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end>
    Left = 72
    Top = 296
  end
  inherited DeleteRequest: TWVRequest
    ID = '专业信息设置'
    Bindings = <
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end
      item
        ParamName = '专业代码'
        FieldName = '专业代码'
      end
      item
        ParamName = '专业名称'
        FieldName = '专业名称'
      end>
    Left = 104
    Top = 296
  end
  inherited ChangeRequest: TWVRequest
    ID = '专业信息设置'
    Bindings = <
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end
      item
        ParamName = '专业代码'
        FieldName = '专业代码'
      end
      item
        ParamName = '专业名称'
        FieldName = '专业名称'
      end>
    Left = 136
    Top = 296
  end
  inherited WVDataSource: TWVDataSource
    Left = 168
    Top = 335
  end
  inherited alDatasetActions: TActionList
    Left = 136
    Top = 335
  end
end
