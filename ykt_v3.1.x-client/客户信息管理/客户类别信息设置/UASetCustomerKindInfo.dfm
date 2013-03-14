inherited faqhSetCustomerKindInfo: TfaqhSetCustomerKindInfo
  Width = 770
  Height = 505
  Caption = '客户类别信息设置'
  inherited pcPages: TRzPageControl
    Width = 770
    Height = 505
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 446
        Width = 766
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 506
          Top = 5
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 591
          Top = 5
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 421
          Top = 5
        end
        inherited btnDelete: TBitBtn
          Left = 676
          Top = 5
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 10
          Top = 5
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 10
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 766
      end
      inherited Grid: TRzDBGrid
        Top = 49
        Width = 766
        Height = 397
        ImeName = ''
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '客户类别代码'
            Width = 92
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scard0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '客户类别名称'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Caption = '默认收费类别'
            Width = 100
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 766
        Height = 31
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label1: TLabel
          Left = 18
          Top = 10
          Width = 48
          Height = 12
          Caption = '客户类别'
        end
        object WVComboBox1: TWVComboBox
          Left = 73
          Top = 5
          Width = 208
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '查询.客户类别代码'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-34'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 66
        Top = 45
        Width = 72
        Height = 12
        Caption = '客户类别代码'
      end
      object Label3: TLabel [1]
        Left = 66
        Top = 85
        Width = 72
        Height = 12
        Caption = '客户类别名称'
      end
      object Label9: TLabel [2]
        Left = 66
        Top = 126
        Width = 72
        Height = 12
        Caption = '默认收费类别'
      end
      inherited UIPanel2: TUIPanel
        Top = 446
        Width = 766
        TabOrder = 3
        inherited btnOK: TBitBtn
          Left = 597
          Top = 5
        end
        inherited btnCancel: TBitBtn
          Left = 682
          Top = 5
        end
        inherited DBNavigator: TRzDBNavigator
          Left = 34
          Top = 5
          Hints.Strings = ()
        end
      end
      object WVEdit3: TWVEdit
        Left = 152
        Top = 80
        Width = 209
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<客户类别名称>'
        WorkView = WorkView
        FieldName = '客户类别名称'
        SynchronizeWhenExit = True
      end
      object WVEdit2: TWVEdit
        Left = 152
        Top = 40
        Width = 120
        Height = 20
        Color = clInfoBk
        MaxLength = 4
        ReadOnly = False
        TabOrder = 0
        Text = '<客户类别代码>'
        WorkView = WorkView
        FieldName = '客户类别代码'
      end
      object WVComboBox5: TWVComboBox
        Left = 153
        Top = 121
        Width = 208
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 0
        TabOrder = 2
        Text = '<默认收费类别>'
        WorkView = WorkView
        FieldName = '默认收费类别'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-43'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 108
    Top = 383
  end
  inherited WorkView: TWorkView
    WorkFields = <
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
        GroupIndex = 1
        DataField = '@Return'
      end
      item
        Name = '返回信息'
        Caption = '返回信息'
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
        DataField = 'vsmess'
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
        Name = '查询.客户类别代码'
        Caption = '查询.客户类别代码'
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
        Name = '客户类别代码'
        Caption = '客户类别代码'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 4
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '客户类别名称'
        Caption = '客户类别名称'
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
        GroupIndex = 1
        DataField = 'scard0'
      end
      item
        Name = '默认收费类别'
        Caption = '默认收费类别'
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
        DataField = 'lvol5'
      end
      item
        Name = '交易类型'
        Caption = '交易类型'
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
        MonitorValueChangedFields = '|查询.客户类别代码|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|客户类别名称|是否交搭伙费|搭伙费费率|正式卡有效期|押金金额|卡成' +
          '本费|手续金额|第一次是否收取卡成本费|是否退卡成本费|账户最大余额' +
          '|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Top = 344
  end
  inherited QueryRequest: TWVRequest
    ID = '客户类别查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
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
        ParamName = '客户类别代码'
        FieldName = '查询.客户类别代码'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 200
    Top = 344
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
      end>
    Left = 76
    Top = 383
  end
  inherited AddRequest: TWVRequest
    ID = '客户类别信息设置'
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
        ParamName = '客户类别代码'
        FieldName = '客户类别代码'
      end
      item
        ParamName = '客户类别名称'
        FieldName = '客户类别名称'
      end
      item
        ParamName = '默认收费类别'
        FieldName = '默认收费类别'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 104
    Top = 344
  end
  inherited DeleteRequest: TWVRequest
    ID = '客户类别信息设置'
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
        ParamName = '客户类别代码'
        FieldName = '客户类别代码'
      end
      item
        ParamName = '客户类别名称'
        FieldName = '客户类别名称'
      end
      item
        ParamName = '默认收费类别'
        FieldName = '默认收费类别'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 136
    Top = 344
  end
  inherited ChangeRequest: TWVRequest
    ID = '客户类别信息设置'
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
        ParamName = '客户类别代码'
        FieldName = '客户类别代码'
      end
      item
        ParamName = '客户类别名称'
        FieldName = '客户类别名称'
      end
      item
        ParamName = '默认收费类别'
        FieldName = '默认收费类别'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Top = 344
  end
  inherited WVDataSource: TWVDataSource
    Left = 172
    Top = 383
  end
  inherited alDatasetActions: TActionList
    Left = 140
    Top = 380
  end
end
