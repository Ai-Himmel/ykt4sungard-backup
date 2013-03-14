inherited faqhacceptSmartTermList: TfaqhacceptSmartTermList
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 432
    Width = 700
    Height = 57
    inherited btnQuery: TBitBtn
      Left = 283
      Enabled = False
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 362
      Visible = False
    end
    object ibnUpLoadSerial: TBitBtn
      Left = 595
      Top = 7
      Width = 91
      Height = 25
      Hint = '采集消费流水'
      Anchors = [akTop, akRight]
      Caption = '&U 采集流水'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = ibnUpLoadSerialClick
    end
    object sbInfo: TStatusBar
      Left = 0
      Top = 38
      Width = 700
      Height = 19
      Font.Charset = GB2312_CHARSET
      Font.Color = clTeal
      Font.Height = -15
      Font.Name = '宋体'
      Font.Style = []
      Panels = <
        item
          Width = 400
        end
        item
          Width = 50
        end>
      SimplePanel = False
      UseSystemFont = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 6
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
  end
  inherited UIPanel2: TUIPanel
    Top = 24
    Width = 700
    Height = 408
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 408
      Columns = <
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Caption = '组名称'
          Visible = True
        end>
    end
  end
  object lvSerial: TRzListView [4]
    Left = 0
    Top = 24
    Width = 700
    Height = 408
    Align = alClient
    Color = 16184303
    Columns = <
      item
        Caption = '序号'
        Width = 40
      end
      item
        Caption = '设备物理ID'
        Width = 90
      end
      item
        Caption = '流水号'
        Width = 60
      end
      item
        Caption = '版本号'
        Width = 70
      end
      item
        Caption = '交易时间'
        Width = 120
      end
      item
        Caption = '卡号'
      end
      item
        Caption = '交易标记'
        Width = 70
      end
      item
        Caption = '启动原因'
        Width = 70
      end
      item
        Caption = 'CRC'
        Width = 130
      end>
    ColumnClick = False
    FillLastColumn = False
    FlatScrollBars = True
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = '宋体'
    Font.Style = []
    FrameColor = 16184303
    FrameHotColor = 16184303
    FrameHotStyle = fsFlat
    FrameVisible = True
    GridLines = True
    ParentFont = False
    ParentShowHint = False
    RowSelect = True
    ShowHint = True
    TabOrder = 4
    ViewStyle = vsReport
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
      end
      item
        Name = '终端设备ID'
        Caption = '终端设备ID'
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
      end
      item
        Name = '交易流水号'
        Caption = '交易流水号'
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
        Name = '交易卡号'
        Caption = '交易卡号'
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
        Name = '交易日期'
        Caption = '交易日期'
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
        Name = '交易时间'
        Caption = '交易时间'
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
        Name = '交易标记'
        Caption = '交易标记'
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
        Name = '通信版本号'
        Caption = '通信版本号'
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
        Name = 'CRC'
        Caption = 'CRC'
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
        Name = '数据通信启动原因'
        Caption = '数据通信启动原因'
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
        Name = '返回值'
        Caption = '返回值'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|组名称|设备编号|操作员号|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '采集手持机认证流水'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = 'CRC'
        FieldName = 'CRC'
      end
      item
        ParamName = '交易标记'
        FieldName = '交易标记'
      end
      item
        ParamName = '交易卡号'
        FieldName = '交易卡号'
      end
      item
        ParamName = '交易流水号'
        FieldName = '交易流水号'
      end
      item
        ParamName = '交易日期'
        FieldName = '交易日期'
      end
      item
        ParamName = '交易时间'
        FieldName = '交易时间'
      end
      item
        ParamName = '数据通信启动原因'
        FieldName = '数据通信启动原因'
      end
      item
        ParamName = '通信版本号'
        FieldName = '通信版本号'
      end
      item
        ParamName = '终端设备ID'
        FieldName = '终端设备ID'
      end
      item
        ParamName = '返回码'
        FieldName = '返回值'
        Direction = bdParam2Field
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 240
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 272
    Top = 224
  end
end
