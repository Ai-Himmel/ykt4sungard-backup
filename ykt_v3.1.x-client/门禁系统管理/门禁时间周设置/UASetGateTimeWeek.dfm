inherited faqhSetGateTimeWeek: TfaqhSetGateTimeWeek
  Width = 751
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 751
    TabOrder = 5
    inherited btnQuery: TBitBtn
      Left = 662
      Caption = '设 置'
    end
    inherited btnPrint: TBitBtn
      Left = 661
      Top = 400
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 751
    inherited Image1: TImage
      Width = 751
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 436
    Width = 751
    Height = 23
    Align = alBottom
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 4
    object chkGateUnAllot: TRzCheckBox
      Left = 5
      Top = 6
      Width = 57
      Height = 17
      Caption = '全选'
      FrameColor = 8409372
      HighlightColor = 2203937
      HotTrack = True
      HotTrackColor = 3983359
      HotTrackColorType = htctActual
      State = cbUnchecked
      TabOrder = 0
      OnClick = chkGateUnAllotClick
    end
    object chkDevSelectAll: TRzCheckBox
      Left = 325
      Top = 6
      Width = 57
      Height = 17
      Caption = '全选'
      FrameColor = 8409372
      HighlightColor = 2203937
      HotTrack = True
      HotTrackColor = 3983359
      HotTrackColorType = htctActual
      State = cbUnchecked
      TabOrder = 1
      OnClick = chkDevSelectAllClick
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 324
    Width = 427
    Height = 418
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Align = alNone
    end
  end
  object RzSizePanel1: TRzSizePanel [4]
    Left = 0
    Top = 18
    Width = 324
    Height = 418
    Color = 16184303
    GradientColorAdjustment = 40
    HotSpotSizePercent = 100
    HotSpotVisible = True
    SizeBarWidth = 5
    TabOrder = 1
    UseGradients = True
    object rzpnl2: TRzPanel
      Left = 0
      Top = 0
      Width = 318
      Height = 105
      Align = alTop
      BorderOuter = fsNone
      Color = 16184303
      TabOrder = 0
      object Label19: TLabel
        Left = 6
        Top = 58
        Width = 72
        Height = 12
        Caption = '周时间段名称'
      end
      object WVEdit8: TWVEdit
        Left = 85
        Top = 54
        Width = 124
        Height = 20
        Color = clInfoBk
        MaxLength = 9
        ReadOnly = False
        TabOrder = 1
        Text = '<查询.时间段组名称>'
        WorkView = WorkView5
        FieldName = '查询.时间段组名称'
      end
      object btnWeekQuery: TBitBtn
        Left = 236
        Top = 51
        Width = 75
        Height = 25
        Hint = '确认操作'
        Caption = '周查询'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = btnWeekQueryClick
      end
    end
    object lvWeek: TRzListView
      Left = 0
      Top = 105
      Width = 318
      Height = 313
      Align = alClient
      Checkboxes = True
      Columns = <
        item
          Caption = '周时间段编号'
          Width = 100
        end
        item
          Caption = '周时间段名称'
          Width = 197
        end>
      ColumnClick = False
      FlatScrollBars = True
      GridLines = True
      RowSelect = True
      TabOrder = 1
      ViewStyle = vsReport
    end
  end
  object RzPanel1: TRzPanel [5]
    Left = 324
    Top = 18
    Width = 427
    Height = 418
    Align = alClient
    BorderOuter = fsNone
    Color = 16184303
    TabOrder = 3
    object rzpnl1: TRzPanel
      Left = 0
      Top = 0
      Width = 427
      Height = 105
      Align = alTop
      BorderOuter = fsNone
      BorderShadow = 16184303
      Color = 16184303
      TabOrder = 0
      object Label7: TLabel
        Left = 10
        Top = 9
        Width = 48
        Height = 12
        Caption = '设备名称'
      end
      object Label12: TLabel
        Left = 22
        Top = 34
        Width = 36
        Height = 12
        Caption = '子系统'
      end
      object Label11: TLabel
        Left = 10
        Top = 56
        Width = 48
        Height = 12
        Caption = '设备状态'
        Visible = False
      end
      object Label18: TLabel
        Left = 214
        Top = 9
        Width = 60
        Height = 12
        Caption = '设备物理ID'
      end
      object Label15: TLabel
        Left = 202
        Top = 32
        Width = 72
        Height = 12
        Caption = '设备物理型号'
      end
      object Label16: TLabel
        Left = 10
        Top = 56
        Width = 48
        Height = 12
        Caption = '设备机型'
      end
      object Label14: TLabel
        Left = 202
        Top = 55
        Width = 72
        Height = 12
        Caption = '设备所在区域'
      end
      object WVEdit3: TWVEdit
        Left = 64
        Top = 5
        Width = 132
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 0
        Text = '<设备名称>'
        WorkView = WorkView1
        FieldName = '设备名称'
      end
      object WVComboBox7: TWVComboBox
        Left = 64
        Top = 28
        Width = 132
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 2
        WorkView = WorkView1
        FieldName = '所属子系统'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-32'
      end
      object WVComboBox5: TWVComboBox
        Left = 64
        Top = 52
        Width = 132
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 6
        Visible = False
        FieldName = '设备状态'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*5'
      end
      object WVEdit6: TWVEdit
        Left = 282
        Top = 5
        Width = 132
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<设备物理ID>'
        WorkView = WorkView1
        FieldName = '设备物理ID'
      end
      object WVComboBox8: TWVComboBox
        Left = 282
        Top = 28
        Width = 132
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView1
        FieldName = '设备物理型号'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-35'
      end
      object WVComboBox9: TWVComboBox
        Left = 282
        Top = 51
        Width = 132
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 4
        WorkView = WorkView1
        FieldName = '设备所在区域'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-28'
      end
      object cbbScode: TWVComboBox
        Left = 64
        Top = 52
        Width = 132
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 5
        WorkView = WorkView1
        FieldName = '机型代码'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*47'
      end
      object btnDevquery: TBitBtn
        Left = 338
        Top = 74
        Width = 75
        Height = 25
        Hint = '确认操作'
        Caption = '设备查询'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 7
        OnClick = btnDevqueryClick
      end
    end
    object lvGate: TRzListView
      Left = 0
      Top = 105
      Width = 427
      Height = 313
      Align = alClient
      AlphaSortAll = True
      Checkboxes = True
      Columns = <
        item
          Caption = '门禁编号'
          Width = 80
        end
        item
          Caption = '门禁名称'
          Width = 200
        end
        item
          Caption = '控制器编号'
          Width = 175
        end
        item
          Caption = '控制器名称'
          Width = 60
        end
        item
          Caption = '机型编号'
        end
        item
          Caption = '机型名称'
          Width = 70
        end>
      ColumnClick = False
      FlatScrollBars = True
      GridLines = True
      RowSelect = True
      TabOrder = 1
      ViewStyle = vsReport
    end
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
      end
      item
        Name = '设备编号'
        Caption = '设备编号'
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
        Name = '控制器编号'
        Caption = '控制器编号'
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
        Name = '时间周编号'
        Caption = '时间周编号'
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
        Name = '机型代码'
        Caption = '机型代码'
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
          '|客户号|交易卡号|物理卡号|起始日期|起始时间|结束日期|结束时间|设' +
          '备标识|设备物理编号|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '门禁时间周设置'
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
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '设备编号'
        FieldName = '设备编号'
      end
      item
        ParamName = '控制器编号'
        FieldName = '控制器编号'
      end
      item
        ParamName = '时间周编号'
        FieldName = '时间周编号'
      end
      item
        ParamName = '机型代码'
        FieldName = '机型代码'
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
  object WVRequest5: TWVRequest
    WorkView = WorkView5
    ID = '周时间段查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '时间段组编号'
        FieldName = '查询.时间段组编号'
      end
      item
        ParamName = '时间段组名称'
        FieldName = '查询.时间段组名称'
      end
      item
        ParamName = '周一组编号'
        FieldName = '查询.周一组编号'
      end
      item
        ParamName = '周二组编号'
        FieldName = '查询.周二组编号'
      end
      item
        ParamName = '周三组编号'
        FieldName = '查询.周三组编号'
      end
      item
        ParamName = '周四组编号'
        FieldName = '查询.周四组编号'
      end
      item
        ParamName = '周五组编号'
        FieldName = '查询.周五组编号'
      end
      item
        ParamName = '周六组编号'
        FieldName = '查询.周六组编号'
      end
      item
        ParamName = '周日组编号'
        FieldName = '查询.周日组编号'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
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
      end>
    Left = 200
    Top = 288
  end
  object WorkView5: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
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
        Name = '操作类别.增加'
        Caption = '操作类别.增加'
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
        Name = '操作类别.删除'
        Caption = '操作类别.删除'
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
        Name = '操作类别.修改'
        Caption = '操作类别.修改'
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
        Name = '查询.时间段组编号'
        Caption = '查询.时间段组编号'
        FieldType = wftUndefined
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
        Name = '查询.时间段组名称'
        Caption = '查询.时间段组名称'
        FieldType = wftUndefined
        DataType = kdtString
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
        Name = '查询.周一组编号'
        Caption = '查询.周一组编号'
        FieldType = wftUndefined
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
        Name = '查询.周二组编号'
        Caption = '查询.周二组编号'
        FieldType = wftUndefined
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
        Name = '查询.周三组编号'
        Caption = '查询.周三组编号'
        FieldType = wftUndefined
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
        Name = '查询.周四组编号'
        Caption = '查询.周四组编号'
        FieldType = wftUndefined
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
        Name = '查询.周五组编号'
        Caption = '查询.周五组编号'
        FieldType = wftUndefined
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
        Name = '查询.周六组编号'
        Caption = '查询.周六组编号'
        FieldType = wftUndefined
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
        Name = '查询.周日组编号'
        Caption = '查询.周日组编号'
        FieldType = wftUndefined
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
        Name = '时间段组编号'
        Caption = '时间段组编号'
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
        DataField = 'lvol0'
      end
      item
        Name = '时间段组名'
        Caption = '时间段组名'
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
        GroupIndex = 1
        DataField = 'semail'
      end
      item
        Name = '交易类型'
        Caption = '交易类型'
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
        Name = '周一组编号'
        Caption = '周一组编号'
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
        DataField = 'lvol1'
      end
      item
        Name = '周二组编号'
        Caption = '周二组编号'
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
        DataField = 'lvol2'
      end
      item
        Name = '周三组编号'
        Caption = '周三组编号'
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
        DataField = 'lvol3'
      end
      item
        Name = '周四组编号'
        Caption = '周四组编号'
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
        DataField = 'lvol4'
      end
      item
        Name = '周五组编号'
        Caption = '周五组编号'
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
        Name = '周六组编号'
        Caption = '周六组编号'
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
        DataField = 'lvol6'
      end
      item
        Name = '周日组编号'
        Caption = '周日组编号'
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
        DataField = 'lvol7'
      end
      item
        Name = '返回信息'
        Caption = '返回信息'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.时间段组编号|查询.时间段组名称|查询.周一组编号|查询.周二组' +
          '编号|查询.周三组编号|查询.周四组编号|查询.周五组编号|查询.周六组' +
          '编号|查询.周日组编号|查询.标志|'
      end
      item
        MonitorValueChangedFields = 
          '|时间段组编号|时间段组名|标志|周一组编号|周二组编号|周三组编号|' +
          '周四组编号|周五组编号|周六组编号|周日组编号|'
      end>
    Left = 168
    Top = 288
  end
  object WorkView1: TWorkView
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
        DataField = '@Return'
      end
      item
        Name = '返回信息'
        Caption = '返回信息'
        FieldType = wftUndefined
        DataType = kdtInteger
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
        Caption = '查询结果集'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '设备名称'
        Caption = '设备名称'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scert_no'
      end
      item
        Name = '三九设备注册号'
        Caption = '三九设备注册号'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_pwd'
      end
      item
        Name = '设备物理ID'
        Caption = '设备物理ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'sbank_pwd2'
      end
      item
        Name = '机号'
        Caption = '机号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '机型代码'
        Caption = '机型代码'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_code'
      end
      item
        Name = '上级设备物理ID'
        Caption = '上级设备物理ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'sdate1'
      end
      item
        Name = '设备状态'
        Caption = '设备状态'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol4'
      end
      item
        Name = '设备物理型号'
        Caption = '设备物理型号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lbank_acc_type'
      end
      item
        Name = '所属子系统'
        Caption = '所属子系统'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial0'
      end
      item
        Name = '设备所在区域'
        Caption = '设备所在区域'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial1'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|设备名称|三九设备注册号|设备物纜机号|机型代码|上级设备物纜设备' +
          '状态|设备物理型号|所属子系统|设备所在区域|负责人员工号|'
      end>
    Left = 164
    Top = 255
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '设备非关键字查询'
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
        ParamName = '设备名称'
        FieldName = '设备名称'
      end
      item
        ParamName = '三九设备注册号'
        FieldName = '三九设备注册号'
      end
      item
        ParamName = '设备物理ID'
        FieldName = '设备物理ID'
      end
      item
        ParamName = '机号'
        FieldName = '机号'
      end
      item
        ParamName = '机型代码'
        FieldName = '机型代码'
      end
      item
        ParamName = '上级设备物理ID'
        FieldName = '上级设备物理ID'
      end
      item
        ParamName = '设备状态'
        FieldName = '设备状态'
      end
      item
        ParamName = '设备物理型号'
        FieldName = '设备物理型号'
      end
      item
        ParamName = '所属子系统'
        FieldName = '所属子系统'
      end
      item
        ParamName = '设备所在区域'
        FieldName = '设备所在区域'
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 256
  end
end
