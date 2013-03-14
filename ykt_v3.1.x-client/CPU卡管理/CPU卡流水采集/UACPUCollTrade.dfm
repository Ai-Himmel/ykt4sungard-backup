inherited faqhCPUCollTrade: TfaqhCPUCollTrade
  Width = 798
  Height = 526
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 798
    Height = 67
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 521
      Caption = '读取流水'
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 180
      Top = 1000
      TabOrder = 6
      Visible = False
    end
    object btnUpLoad: TBitBtn
      Left = 612
      Top = 3
      Width = 75
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '上传流水'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnUpLoadClick
    end
    object pb1: TProgressBar
      Left = 0
      Top = 33
      Width = 798
      Height = 9
      Align = alBottom
      Min = 0
      Max = 100
      TabOrder = 4
    end
    object stat1: TStatusBar
      Left = 0
      Top = 42
      Width = 798
      Height = 25
      Color = 15458000
      Panels = <
        item
          Width = 500
        end>
      SimplePanel = False
    end
    object btnClear: TBitBtn
      Left = 699
      Top = 3
      Width = 89
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '清空记录'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnClearClick
    end
    object chkSelectAll: TCheckBox
      Left = 8
      Top = 8
      Width = 49
      Height = 17
      Caption = '全选'
      TabOrder = 3
      OnClick = chkSelectAllClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 798
    inherited Image1: TImage
      Width = 798
    end
    inherited LabRecordCount: TLabel
      Left = 0
      Visible = False
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 798
    Height = 441
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 2
    object lvSerial: TRzListView
      Left = 0
      Top = 0
      Width = 798
      Height = 441
      Align = alClient
      Checkboxes = True
      Columns = <
        item
          Caption = '序号'
        end
        item
          Alignment = taCenter
          Caption = '交易日期'
          Width = 80
        end
        item
          Alignment = taCenter
          Caption = '交易时间'
          Width = 80
        end
        item
          Caption = '交易次数'
          Width = 60
        end
        item
          Alignment = taRightJustify
          Caption = '交易前余额'
          Width = 90
        end
        item
          Alignment = taRightJustify
          Caption = '交易金额'
          Width = 70
        end
        item
          Alignment = taRightJustify
          Caption = '搭伙费'
        end
        item
          Alignment = taRightJustify
          Caption = '补写金额'
          Width = 70
        end
        item
          Caption = '商户号'
        end
        item
          Caption = '终端编号'
          Width = 60
        end
        item
          Caption = '交易序号'
          Width = 117
        end>
      FlatScrollBars = True
      GridLines = True
      MultiSelect = True
      SortType = stData
      TabOrder = 0
      ViewStyle = vsReport
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 488
    Top = 0
    Width = 65
    Height = 17
    Align = alNone
    Visible = False
    inherited Grid: TRzDBGrid
      Left = 152
      Top = 112
      Width = 97
      Height = 18
      Align = alNone
      Columns = <
        item
          Expanded = False
          FieldName = 'Lserial1'
          PickList.Strings = ()
          Title.Caption = '后台流水号'
          Visible = True
        end>
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
      end
      item
        Name = '站点号'
        Caption = '站点号'
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
        Name = '卡号'
        Caption = '卡号'
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
        Name = '交易标志'
        Caption = '交易标志'
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
        Name = '消费次数'
        Caption = '消费次数'
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
        Name = '交易前余额'
        Caption = '交易前余额'
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
        Name = '交易金额'
        Caption = '交易金额'
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
        Name = '搭伙费'
        Caption = '搭伙费'
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
        Name = '补写金额'
        Caption = '补写金额'
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
        Name = '商户号'
        Caption = '商户号'
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
        Name = '终端编号'
        Caption = '终端编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sserial0'
      end
      item
        Name = '交易序号'
        Caption = '交易序号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|设备号|金额|'
      end>
    Left = 156
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = 'CPU卡流水采集'
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
        ParamName = '站点号'
        FieldName = '站点号'
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '交易标志'
        FieldName = '交易标志'
      end
      item
        ParamName = '消费次数'
        FieldName = '消费次数'
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
        ParamName = '交易前余额'
        FieldName = '交易前余额'
      end
      item
        ParamName = '交易金额'
        FieldName = '交易金额'
      end
      item
        ParamName = '搭伙费'
        FieldName = '搭伙费'
      end
      item
        ParamName = '补写金额'
        FieldName = '补写金额'
      end
      item
        ParamName = '商户号'
        FieldName = '商户号'
      end
      item
        ParamName = '终端编号'
        FieldName = '终端编号'
      end
      item
        ParamName = '交易序号'
        FieldName = '交易序号'
      end>
    Left = 192
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 232
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 272
    Top = 224
  end
end
