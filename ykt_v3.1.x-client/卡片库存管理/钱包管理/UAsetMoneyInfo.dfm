inherited faqhsetMoneyInfo: TfaqhsetMoneyInfo
  Width = 681
  Height = 477
  Caption = '钱包管理'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 414
        Width = 677
        Height = 40
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 267
          Top = 7
          Enabled = False
          TabOrder = 0
          Visible = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 589
          Top = 7
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 506
          Top = 7
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = 348
          Top = 7
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
          Top = 8
          TabOrder = 4
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 13
          Width = 161
          Visible = False
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 41
        Width = 677
        Height = 373
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '钱包号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '钱包名称'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '最大充值金额'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '是否使用'
            Visible = False
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 23
        Align = alTop
        ParentColor = True
        TabOrder = 1
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label8: TLabel [0]
        Left = 40
        Top = 89
        Width = 48
        Height = 12
        Caption = '钱包名称'
      end
      object Label9: TLabel [1]
        Left = 52
        Top = 60
        Width = 36
        Height = 12
        Caption = '钱包号'
      end
      object Label1: TLabel [2]
        Left = 16
        Top = 119
        Width = 72
        Height = 12
        Caption = '最大充值金额'
      end
      object Label2: TLabel [3]
        Left = 288
        Top = 120
        Width = 96
        Height = 12
        Caption = '说明：只能是整数'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 3
        inherited btnOK: TBitBtn
          Left = 505
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 593
          TabOrder = 2
          TabStop = True
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object WVEdit8: TWVEdit
        Left = 102
        Top = 85
        Width = 181
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<钱包名称>'
        WorkView = WorkView
        FieldName = '钱包名称'
        SynchronizeWhenExit = True
      end
      object edtMoneyId: TWVDigitalEdit
        Left = 102
        Top = 56
        Width = 181
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '钱包号'
        SynchronizeByValue = True
      end
      object WVDigitalEdit1: TWVDigitalEdit
        Left = 102
        Top = 114
        Width = 181
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        ParentColor = False
        TabOrder = 2
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '最大充值额'
        SynchronizeByValue = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 452
    Top = 223
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
        Name = '交易类型'
        Caption = '交易类型'
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
        DataField = 'Sstatus0'
      end
      item
        Name = '钱包名称'
        Caption = '钱包名称'
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
        DataField = 'sname'
      end
      item
        Name = '钱包号'
        Caption = '钱包号'
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
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '最大充值额'
        Caption = '最大充值额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 1
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '是否使用'
        Caption = '是否使用'
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
        DataField = 'sstatus1'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.交易类型|查询.钱包名称|查询.钱包号|查询.最大充值额|查询.卡' +
          '类别范围|查询.是否使用|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|交易类型|钱包名称|钱包号|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 368
    Top = 176
  end
  inherited QueryRequest: TWVRequest
    ID = '钱包查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 528
    Top = 176
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '2'
      end>
    Left = 412
    Top = 223
  end
  inherited AddRequest: TWVRequest
    ID = '钱包管理'
    Bindings = <
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '钱包名称'
        FieldName = '钱包名称'
      end
      item
        ParamName = '钱包号'
        FieldName = '钱包号'
      end
      item
        ParamName = '最大充值额'
        FieldName = '最大充值额'
      end>
    Left = 408
    Top = 176
  end
  inherited DeleteRequest: TWVRequest
    ID = '钱包管理'
    Bindings = <
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '钱包名称'
        FieldName = '钱包名称'
      end
      item
        ParamName = '钱包号'
        FieldName = '钱包号'
      end
      item
        ParamName = '最大充值额'
        FieldName = '最大充值额'
      end>
    Left = 448
    Top = 176
  end
  inherited ChangeRequest: TWVRequest
    ID = '钱包管理'
    Bindings = <
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '钱包名称'
        FieldName = '钱包名称'
      end
      item
        ParamName = '钱包号'
        FieldName = '钱包号'
      end
      item
        ParamName = '最大充值额'
        FieldName = '最大充值额'
      end
      item
        ParamName = '是否使用'
        FieldName = '是否使用'
      end>
    Left = 488
    Top = 176
  end
  inherited WVDataSource: TWVDataSource
    Left = 532
    Top = 223
  end
  inherited alDatasetActions: TActionList
    Left = 492
    Top = 220
  end
end
