inherited faqhSetGlobeParaInfo: TfaqhSetGlobeParaInfo
  Width = 708
  Height = 477
  Caption = '全局参数设置'
  inherited pcPages: TRzPageControl
    Width = 708
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 418
        Width = 704
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 346
          Enabled = False
          TabOrder = 0
          Visible = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 610
          Top = 6
          Enabled = False
          TabOrder = 4
        end
        inherited btnQuery: TBitBtn [2]
          Left = 525
          Top = 6
          TabOrder = 3
        end
        inherited btnDelete: TBitBtn
          Left = 391
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
          Top = 6
          TabOrder = 2
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 11
          Visible = False
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
        Align = alNone
        TabOrder = 1
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 704
        Height = 385
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '参数标识'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Caption = '参数名称'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scard0'
            PickList.Strings = ()
            Title.Caption = '参数值'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_no'
            PickList.Strings = ()
            Title.Caption = '参数单位'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Caption = '备注'
            Width = 300
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 704
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label1: TLabel
          Left = 42
          Top = 13
          Width = 48
          Height = 12
          Caption = '参数标识'
        end
        object WVEdit1: TWVEdit
          Left = 104
          Top = 8
          Width = 105
          Height = 20
          Color = clInfoBk
          MaxLength = 22
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.参数标志>'
          WorkView = WorkView
          FieldName = '查询.参数标志'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 42
        Top = 44
        Width = 48
        Height = 12
        Caption = '参数标识'
      end
      object Label3: TLabel [1]
        Left = 42
        Top = 84
        Width = 48
        Height = 12
        Caption = '参数名称'
      end
      object Label4: TLabel [2]
        Left = 54
        Top = 164
        Width = 36
        Height = 12
        Caption = '参数值'
      end
      object Label7: TLabel [3]
        Left = 42
        Top = 124
        Width = 48
        Height = 12
        Caption = '参数单位'
      end
      object WVLabel2: TWVLabel [4]
        Left = 66
        Top = 203
        Width = 24
        Height = 12
        Caption = '备注'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 704
        TabOrder = 5
        inherited btnOK: TBitBtn
          Left = 532
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 620
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object edtName: TWVEdit
        Left = 99
        Top = 80
        Width = 152
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<参数名称>'
        WorkView = WorkView
        FieldName = '参数名称'
        SynchronizeWhenExit = True
      end
      object WVEdit4: TWVEdit
        Left = 99
        Top = 160
        Width = 152
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 3
        Text = '<参数值>'
        WorkView = WorkView
        FieldName = '参数值'
        SynchronizeWhenExit = True
      end
      object edtUnit: TWVEdit
        Left = 99
        Top = 120
        Width = 152
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 2
        Text = '<参数单位>'
        WorkView = WorkView
        FieldName = '参数单位'
        SynchronizeWhenExit = True
      end
      object WVEdit5: TWVEdit
        Left = 99
        Top = 200
        Width = 369
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 4
        Text = '<备注>'
        WorkView = WorkView
        FieldName = '备注'
      end
      object edtId: TWVEdit
        Left = 99
        Top = 40
        Width = 152
        Height = 20
        MaxLength = 22
        ParentColor = True
        ReadOnly = True
        TabOrder = 0
        Text = '<参数标识>'
        WorkView = WorkView
        FieldName = '参数标识'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 260
    Top = 383
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        Caption = '查询结果集'
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
        Name = '操作类别.增加'
        Caption = '操作类别.增加'
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
      end
      item
        Name = '操作类别.删除'
        Caption = '操作类别.删除'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '操作类别.修改'
        Caption = '操作类别.修改'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '查询.参数标志'
        Caption = '查询.参数标志'
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
        DataField = 'lvol5'
      end
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
        Name = '参数标识'
        Caption = '参数标识'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '参数名称'
        Caption = '参数名称'
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
        DataField = 'scust_auth'
      end
      item
        Name = '参数值'
        Caption = '参数值'
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
        DataField = 'scard0'
      end
      item
        Name = '生效时间'
        Caption = '生效时间'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 14
        Checker.MaxLength = 14
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'spager'
      end
      item
        Name = '参数单位'
        Caption = '参数单位'
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
        MonitorValueChangedFields = '|查询.参数标志|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|参数标志|参数名称|参数值|生效时间|设置时间|参数单位|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Top = 344
  end
  inherited QueryRequest: TWVRequest
    ID = '全局参数关键字查询'
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
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '参数标志'
        FieldName = '查询.参数标志'
      end>
    Left = 168
    Top = 304
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 104
    Top = 344
  end
  inherited AddRequest: TWVRequest
    ID = '全局参数设置.增加'
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
        ParamName = '参数标识'
        FieldName = '参数标识'
      end
      item
        ParamName = '参数名称'
        FieldName = '参数名称'
      end
      item
        ParamName = '参数值'
        FieldName = '参数值'
      end
      item
        ParamName = '生效时间'
        FieldName = '生效时间'
      end
      item
        ParamName = '参数单位'
        FieldName = '参数单位'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
    Left = 72
    Top = 304
  end
  inherited DeleteRequest: TWVRequest
    ID = '全局参数设置.删除'
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
        ParamName = '参数标识'
        FieldName = '参数标识'
      end
      item
        ParamName = '参数名称'
        FieldName = '参数名称'
      end
      item
        ParamName = '参数值'
        FieldName = '参数值'
      end
      item
        ParamName = '生效时间'
        FieldName = '生效时间'
      end
      item
        ParamName = '参数单位'
        FieldName = '参数单位'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
    Left = 104
    Top = 304
  end
  inherited ChangeRequest: TWVRequest
    ID = '全局参数设置.修改'
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
        ParamName = '参数标识'
        FieldName = '参数标识'
      end
      item
        ParamName = '参数名称'
        FieldName = '参数名称'
      end
      item
        ParamName = '参数值'
        FieldName = '参数值'
      end
      item
        ParamName = '生效时间'
        FieldName = '生效时间'
      end
      item
        ParamName = '参数单位'
        FieldName = '参数单位'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
    Left = 136
    Top = 304
  end
  inherited WVDataSource: TWVDataSource
    Left = 168
    Top = 343
  end
  inherited alDatasetActions: TActionList
    Left = 135
    Top = 344
  end
end
