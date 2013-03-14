inherited faqhsetBusiCC: TfaqhsetBusiCC
  Width = 681
  Height = 477
  Caption = '商户餐次信息设置'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 677
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 503
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 255
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 418
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 88
          Width = 161
          Visible = False
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 49
        Width = 677
        Height = 375
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户编号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户名称'
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '早餐结束时间'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '午餐结束时间'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '晚餐结束时间'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '夜宵结束时间'
            Width = 80
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
        TabOrder = 1
        object Label1: TLabel
          Left = 18
          Top = 10
          Width = 48
          Height = 12
          Caption = '商户编号'
        end
        object WVDigitalEdit1: TWVDigitalEdit
          Left = 76
          Top = 6
          Width = 100
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
          FieldName = '查询.商户编号'
          SynchronizeByValue = True
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object lbl1: TLabel [0]
        Left = 232
        Top = 16
        Width = 72
        Height = 12
        AutoSize = False
        Caption = '当前选择商户'
      end
      object lblBusi: TLabel [1]
        Left = 312
        Top = 16
        Width = 353
        Height = 12
        AutoSize = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clRed
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 2
        inherited btnOK: TBitBtn
          Left = 505
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 593
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object pnl1: TPanel
        Left = 0
        Top = 0
        Width = 209
        Height = 418
        Align = alLeft
        BevelOuter = bvNone
        TabOrder = 0
        object pnl2: TPanel
          Left = 0
          Top = 0
          Width = 209
          Height = 41
          Align = alTop
          BevelOuter = bvNone
          Color = 14999516
          TabOrder = 0
        end
        object tvCust: TRzTreeView
          Left = 0
          Top = 41
          Width = 225
          Height = 377
          SelectionPen.Color = clBtnShadow
          Align = alLeft
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          Indent = 19
          ParentFont = False
          TabOrder = 1
          OnClick = tvCustClick
        end
      end
      object grp1: TGroupBox
        Left = 232
        Top = 40
        Width = 289
        Height = 153
        Caption = '餐次信息'
        TabOrder = 1
        object Label7: TLabel
          Left = 28
          Top = 28
          Width = 72
          Height = 12
          Caption = '早餐结束时间'
        end
        object Label8: TLabel
          Left = 28
          Top = 68
          Width = 72
          Height = 12
          Caption = '午餐结束时间'
        end
        object Label9: TLabel
          Left = 28
          Top = 108
          Width = 72
          Height = 12
          Caption = '晚餐结束时间'
        end
        object edtTime1: TWVEdit
          Left = 109
          Top = 24
          Width = 100
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<早餐结束时间>'
          WorkView = WorkView
          FieldName = '早餐结束时间'
          SynchronizeWhenExit = True
        end
        object edtTime2: TWVEdit
          Left = 109
          Top = 64
          Width = 100
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<午餐结束时间>'
          WorkView = WorkView
          FieldName = '午餐结束时间'
          SynchronizeWhenExit = True
        end
        object edtTime3: TWVEdit
          Left = 109
          Top = 104
          Width = 100
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 2
          Text = '<晚餐结束时间>'
          WorkView = WorkView
          FieldName = '晚餐结束时间'
          SynchronizeWhenExit = True
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 108
    Top = 159
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
        Name = '查询.商户编号'
        Caption = '查询.商户编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '商户编号'
        Caption = '商户编号'
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
        Name = '早餐结束时间'
        Caption = '早餐结束时间'
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
        Name = '午餐结束时间'
        Caption = '午餐结束时间'
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
        DataField = 'stime2'
      end
      item
        Name = '晚餐结束时间'
        Caption = '晚餐结束时间'
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
        DataField = 'stime3'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.商户编号|查询.早餐结束时间|查询.午餐结束时间|查询.晚餐结束' +
          '时间|查询.夜宵结束时间|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|商户编号|早餐结束时间|午餐结束时间|晚餐结束时间|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 40
    Top = 128
  end
  inherited QueryRequest: TWVRequest
    ID = '商户餐次信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '商户编号'
        FieldName = '查询.商户编号'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end>
    Left = 168
    Top = 128
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 76
    Top = 159
  end
  inherited AddRequest: TWVRequest
    ID = '商户餐次信息设置'
    Bindings = <
      item
        ParamName = '商户编号'
        FieldName = '商户编号'
      end
      item
        ParamName = '早餐结束时间'
        FieldName = '早餐结束时间'
      end
      item
        ParamName = '午餐结束时间'
        FieldName = '午餐结束时间'
      end
      item
        ParamName = '晚餐结束时间'
        FieldName = '晚餐结束时间'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end>
    Left = 72
    Top = 128
  end
  inherited DeleteRequest: TWVRequest
    ID = '商户餐次信息设置'
    Bindings = <
      item
        ParamName = '商户编号'
        FieldName = '商户编号'
      end
      item
        ParamName = '早餐结束时间'
        FieldName = '早餐结束时间'
      end
      item
        ParamName = '午餐结束时间'
        FieldName = '午餐结束时间'
      end
      item
        ParamName = '晚餐结束时间'
        FieldName = '晚餐结束时间'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end>
    Left = 104
    Top = 128
  end
  inherited ChangeRequest: TWVRequest
    ID = '商户餐次信息设置'
    Bindings = <
      item
        ParamName = '商户编号'
        FieldName = '商户编号'
      end
      item
        ParamName = '早餐结束时间'
        FieldName = '早餐结束时间'
      end
      item
        ParamName = '午餐结束时间'
        FieldName = '午餐结束时间'
      end
      item
        ParamName = '晚餐结束时间'
        FieldName = '晚餐结束时间'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end>
    Left = 136
    Top = 128
  end
  inherited WVDataSource: TWVDataSource
    Left = 172
    Top = 159
  end
  inherited alDatasetActions: TActionList
    Left = 140
    Top = 156
  end
  object QueryRequest2: TWVRequest
    WorkView = WorkView2
    ID = '商户信息主键查询2'
    Bindings = <
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '商户标识'
        FieldName = '商户标识'
      end>
    Left = 80
    Top = 88
  end
  object WorkView2: TWorkView
    WorkFields = <
      item
        Name = '返回码'
        Caption = '返回码'
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
        Name = '商户标识'
        Caption = '商户标识'
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
        Name = '查询结果集'
        Caption = '查询结果集'
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
        MonitorValueChangedFields = '|商户标识|'
      end>
    Left = 36
    Top = 87
  end
end
