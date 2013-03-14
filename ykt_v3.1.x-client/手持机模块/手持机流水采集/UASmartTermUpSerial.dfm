inherited faqhSmartTermUpSerial: TfaqhSmartTermUpSerial
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 426
    Width = 700
    Height = 36
    inherited btnQuery: TBitBtn
      Left = 379
      Top = 6
      Enabled = False
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 466
      Top = 6
      Visible = False
    end
    object ibnUpLoadSerial: TBitBtn
      Left = 603
      Top = 6
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
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel2: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 15
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
  end
  inherited UIPanel2: TUIPanel
    Top = 33
    Width = 700
    Height = 393
    inherited Grid: TRzDBGrid
      Align = alNone
      Visible = False
    end
  end
  object lvSerial: TRzListView [4]
    Left = 0
    Top = 33
    Width = 700
    Height = 393
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
        Caption = '通信版本'
        Width = 70
      end
      item
        Caption = '启动原因'
        Width = 70
      end
      item
        Caption = '交易日期'
        Width = 90
      end
      item
        Caption = '卡号'
      end
      item
        Caption = '卡使用次数'
        Width = 100
      end
      item
        Caption = '入卡值'
        Width = 60
      end
      item
        Caption = '出卡值'
        Width = 60
      end
      item
        Caption = '交易金额'
        Width = 70
      end
      item
        Caption = '交易标记'
        Width = 70
      end
      item
        Caption = 'CRC'
        Width = 20
      end>
    ColumnClick = False
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
    ParentColor = True
    ParentFont = False
    RowSelect = True
    ShowWorkAreas = True
    TabOrder = 4
    ViewStyle = vsReport
  end
  object sbInfo: TStatusBar [5]
    Left = 0
    Top = 462
    Width = 700
    Height = 27
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
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '终端设备ＩＤ'
        Caption = '终端设备ＩＤ'
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
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
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
      end
      item
        Name = '交易日期'
        Caption = '交易日期'
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
        Name = '交易时间'
        Caption = '交易时间'
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
        Name = '累计使用次数'
        Caption = '累计使用次数'
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
        Name = '本次消费金额'
        Caption = '本次消费金额'
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
        Name = '入卡金额'
        Caption = '入卡金额'
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
        Name = '出卡金额'
        Caption = '出卡金额'
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
        Name = '交易标记'
        Caption = '交易标记'
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
        Name = '通信版本号'
        Caption = '通信版本号'
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
        Name = '数据通信启动原因'
        Caption = '数据通信启动原因'
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
        Name = 'CRC'
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
        Name = '返回值'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '-1'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|终端设备ＩＤ|交易流水号|交易卡号|钱包号|交易日期|交易时间|累计' +
          '使用次数|本次消费金额|入卡金额|出卡金额|交易标记|通信版本号|数据' +
          '通信启动原因||'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 20
    Top = 207
  end
  inherited MainRequest: TWVRequest
    ID = '手持机流水采集'
    Bindings = <
      item
        ParamName = '终端设备ＩＤ'
        FieldName = '终端设备ＩＤ'
      end
      item
        ParamName = '交易流水号'
        FieldName = '交易流水号'
      end
      item
        ParamName = '交易卡号'
        FieldName = '交易卡号'
      end
      item
        ParamName = '钱包号'
        FieldName = '钱包号'
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
        ParamName = '累计使用次数'
        FieldName = '累计使用次数'
      end
      item
        ParamName = '本次消费金额'
        FieldName = '本次消费金额'
      end
      item
        ParamName = '入卡金额'
        FieldName = '入卡金额'
      end
      item
        ParamName = '出卡金额'
        FieldName = '出卡金额'
      end
      item
        ParamName = '交易标记'
        FieldName = '交易标记'
      end
      item
        ParamName = '通信版本号'
        FieldName = '通信版本号'
      end
      item
        ParamName = '数据通信启动原因'
        FieldName = '数据通信启动原因'
      end
      item
        ParamName = 'CRC'
        FieldName = 'CRC'
      end
      item
        ParamName = '返回码'
        FieldName = '返回值'
        Direction = bdParam2Field
      end>
    Left = 56
    Top = 208
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 88
    Top = 208
  end
  inherited DataSource: TDataSource
    Left = 120
    Top = 208
  end
end
