inherited faqhsetMealOrder: TfaqhsetMealOrder
  Width = 681
  Height = 477
  Caption = '餐次信息设置'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 418
        Width = 677
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 267
          Top = 6
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 595
          Top = 6
          Enabled = False
          TabOrder = 4
        end
        inherited btnQuery: TBitBtn [2]
          Left = 506
          Top = 6
          TabOrder = 3
        end
        inherited btnDelete: TBitBtn
          Left = 348
          Top = 6
          Enabled = False
          TabOrder = 2
          Visible = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
          Top = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 12
          Width = 177
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 41
        Width = 677
        Height = 377
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '序号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Caption = '餐次名称'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime1'
            PickList.Strings = ()
            Title.Caption = '开始时间'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime2'
            PickList.Strings = ()
            Title.Caption = '结束时间'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Caption = '备注'
            Width = 100
            Visible = True
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
      object Label4: TLabel [0]
        Left = 194
        Top = 76
        Width = 24
        Height = 12
        Caption = '序号'
        Visible = False
      end
      object Label5: TLabel [1]
        Left = 170
        Top = 116
        Width = 48
        Height = 12
        Caption = '餐次名称'
      end
      object Label6: TLabel [2]
        Left = 172
        Top = 156
        Width = 48
        Height = 12
        Caption = '开始时间'
      end
      object Label8: TLabel [3]
        Left = 42
        Top = 5
        Width = 96
        Height = 16
        Caption = '餐次信息设置'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '黑体'
        Font.Style = []
        ParentFont = False
      end
      object Label9: TLabel [4]
        Left = 172
        Top = 196
        Width = 48
        Height = 12
        Caption = '结束时间'
      end
      object Label10: TLabel [5]
        Left = 332
        Top = 156
        Width = 96
        Height = 12
        Caption = '时间格式(hhmmss)'
      end
      object Label11: TLabel [6]
        Left = 332
        Top = 196
        Width = 96
        Height = 12
        Caption = '时间格式(hhmmss)'
      end
      object Label12: TLabel [7]
        Left = 196
        Top = 228
        Width = 24
        Height = 12
        Caption = '备注'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 5
        inherited btnOK: TBitBtn
          Left = 501
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 589
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object WVDigitalEdit4: TWVDigitalEdit
        Left = 228
        Top = 72
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        Visible = False
        WorkView = WorkView
        FieldName = '序号'
        SynchronizeByValue = True
      end
      object edtName: TWVEdit
        Left = 228
        Top = 112
        Width = 277
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<餐次名称>'
        WorkView = WorkView
        FieldName = '餐次名称'
        SynchronizeWhenExit = True
      end
      object edtBegin: TWVEdit
        Left = 230
        Top = 152
        Width = 100
        Height = 20
        Color = clInfoBk
        MaxLength = 6
        ReadOnly = False
        TabOrder = 2
        Text = '<开始时间>'
        WorkView = WorkView
        FieldName = '开始时间'
        SynchronizeWhenExit = True
      end
      object edtEnd: TWVEdit
        Left = 230
        Top = 192
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 6
        ReadOnly = False
        TabOrder = 3
        Text = '<结束时间>'
        WorkView = WorkView
        FieldName = '结束时间'
        SynchronizeWhenExit = True
      end
      object edtMemo: TWVEdit
        Left = 230
        Top = 224
        Width = 275
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 4
        Text = '<备注>'
        WorkView = WorkView
        FieldName = '备注'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 156
    Top = 295
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
        Name = '序号'
        Caption = '序号'
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
        Name = '餐次名称'
        Caption = '餐次名称'
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
        DataField = 'sall_name'
      end
      item
        Name = '开始时间'
        Caption = '开始时间'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'stime1'
      end
      item
        Name = '结束时间'
        Caption = '结束时间'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'stime2'
      end
      item
        Name = '操作标志'
        Caption = '操作标志'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sstatus0'
      end
      item
        Name = '操作员号'
        Caption = '操作员号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '查询.餐次名称'
        Caption = '查询.餐次名称'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '查询.开始时间'
        Caption = '查询.开始时间'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '查询.结束时间'
        Caption = '查询.结束时间'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
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
        MonitorValueChangedFields = '|查询.餐次名称|查询.开始时间|查询.结束时间|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|序号|餐次名称|开始时间|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 344
    Top = 48
  end
  inherited QueryRequest: TWVRequest
    ID = '餐次信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '餐次名称'
        FieldName = '查询.餐次名称'
      end
      item
        ParamName = '开始时间'
        FieldName = '查询.开始时间'
      end
      item
        ParamName = '结束时间'
        FieldName = '查询.结束时间'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end>
    Left = 504
    Top = 48
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 108
    Top = 295
  end
  inherited AddRequest: TWVRequest
    ID = '餐次信息设置'
    Bindings = <
      item
        ParamName = '序号'
        FieldName = '序号'
      end
      item
        ParamName = '餐次名称'
        FieldName = '餐次名称'
      end
      item
        ParamName = '开始时间'
        FieldName = '开始时间'
      end
      item
        ParamName = '结束时间'
        FieldName = '结束时间'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
    Left = 384
    Top = 48
  end
  inherited DeleteRequest: TWVRequest
    ID = '餐次信息设置'
    Bindings = <
      item
        ParamName = '序号'
        FieldName = '序号'
      end
      item
        ParamName = '餐次名称'
        FieldName = '餐次名称'
      end
      item
        ParamName = '开始时间'
        FieldName = '开始时间'
      end
      item
        ParamName = '结束时间'
        FieldName = '结束时间'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
    Left = 424
    Top = 48
  end
  inherited ChangeRequest: TWVRequest
    ID = '餐次信息设置'
    Bindings = <
      item
        ParamName = '序号'
        FieldName = '序号'
      end
      item
        ParamName = '餐次名称'
        FieldName = '餐次名称'
      end
      item
        ParamName = '开始时间'
        FieldName = '开始时间'
      end
      item
        ParamName = '结束时间'
        FieldName = '结束时间'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
    Left = 464
    Top = 48
  end
  inherited WVDataSource: TWVDataSource
    Left = 260
    Top = 311
  end
  inherited alDatasetActions: TActionList
    Left = 220
    Top = 308
  end
end
