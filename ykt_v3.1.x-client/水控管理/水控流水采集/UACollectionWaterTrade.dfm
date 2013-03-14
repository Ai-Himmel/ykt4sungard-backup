inherited faqhCollectionWaterTrade: TfaqhCollectionWaterTrade
  Width = 739
  Height = 526
  inherited UIPanel1: TUIPanel
    Top = 469
    Width = 739
    Height = 57
    inherited btnQuery: TBitBtn
      Left = 462
      Caption = '读取流水'
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 121
      Top = 1
      Visible = False
    end
    object btnUpLoad: TBitBtn
      Left = 553
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
      TabOrder = 2
      OnClick = btnUpLoadClick
    end
    object pb1: TProgressBar
      Left = 0
      Top = 3
      Width = 337
      Height = 22
      Min = 0
      Max = 100
      TabOrder = 3
    end
    object stat1: TStatusBar
      Left = 0
      Top = 32
      Width = 739
      Height = 25
      Color = 15458000
      Panels = <
        item
          Width = 500
        end>
      SimplePanel = False
    end
    object btnClear: TBitBtn
      Left = 640
      Top = 3
      Width = 89
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '清空采集卡'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = btnClearClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 739
    inherited Image1: TImage
      Width = 739
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 739
    Height = 451
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object lvSerial: TRzListView
      Left = 0
      Top = 0
      Width = 739
      Height = 451
      Align = alClient
      Columns = <
        item
          Caption = '序号'
        end
        item
          Alignment = taCenter
          Caption = '水控设备号'
          Width = 200
        end
        item
          Alignment = taRightJustify
          Caption = '金额'
          Width = 469
        end>
      FlatScrollBars = True
      GridLines = True
      SortType = stData
      TabOrder = 0
      ViewStyle = vsReport
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 240
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
        Name = '设备号'
        Caption = '设备号'
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
        Name = '金额'
        Caption = '金额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
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
        Name = '失败码'
        Caption = '失败码'
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
        Name = '操作员代码'
        Caption = '操作员代码'
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
        MonitorValueChangedFields = '|设备号|金额|'
      end>
    Left = 156
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '水控流水采集'
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
        ParamName = '设备号'
        FieldName = '设备号'
      end
      item
        ParamName = '金额'
        FieldName = '金额'
      end
      item
        ParamName = '失败码'
        FieldName = '失败码'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作员代码'
        FieldName = '操作员代码'
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
