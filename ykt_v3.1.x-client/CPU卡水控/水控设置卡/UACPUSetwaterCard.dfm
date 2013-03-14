inherited faqhSetWaterCard: TfaqhSetWaterCard
  Width = 700
  Height = 588
  inherited UIPanel1: TUIPanel
    Top = 552
    Width = 700
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 96
      Top = 5
      Width = 90
      Caption = '读卡信息(&R)'
      TabOrder = 1
      Visible = False
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 10
      TabOrder = 0
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    TabOrder = 2
    inherited Image1: TImage
      Width = 700
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 700
    Height = 534
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Align = alNone
      Columns = <
        item
          Expanded = False
          FieldName = 'Lvol0'
          PickList.Strings = ()
          Title.Caption = '后台流水号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol1'
          PickList.Strings = ()
          Title.Caption = '购水后台流水号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt0'
          PickList.Strings = ()
          Title.Caption = '大钱包出卡值'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt2'
          PickList.Strings = ()
          Title.Caption = '小钱包出卡值'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol9'
          PickList.Strings = ()
          Title.Caption = '大钱包次数'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Caption = '小钱包次数'
          Visible = True
        end>
    end
  end
  object Panel1: TPanel [3]
    Left = 0
    Top = 18
    Width = 700
    Height = 534
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 184
      Top = 72
      Width = 433
      Height = 265
      Caption = '水控参数卡信息'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object RzStatusPane4: TRzStatusPane
        Left = 13
        Top = 161
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '单次转账单位'
      end
      object rzstspn1: TRzStatusPane
        Left = 13
        Top = 195
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '单价'
      end
      object lbl3: TLabel
        Left = 291
        Top = 201
        Width = 133
        Height = 14
        AutoSize = False
        Caption = '分/吨'
      end
      object rzstspn4: TRzStatusPane
        Left = 13
        Top = 22
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '水控类型'
      end
      object RzStatusPane6: TRzStatusPane
        Left = 13
        Top = 230
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '参数卡标志'
      end
      object lbl4: TLabel
        Left = 291
        Top = 166
        Width = 133
        Height = 14
        AutoSize = False
        Caption = '分(新天为吨)'
      end
      object RzStatusPane1: TRzStatusPane
        Left = 13
        Top = 57
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '钱包预警金额'
      end
      object RzStatusPane2: TRzStatusPane
        Left = 13
        Top = 91
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '钱包金额上线'
      end
      object Label1: TLabel
        Left = 291
        Top = 62
        Width = 133
        Height = 14
        AutoSize = False
        Caption = '分(新天为吨)'
      end
      object Label2: TLabel
        Left = 291
        Top = 97
        Width = 133
        Height = 14
        AutoSize = False
        Caption = '分'
      end
      object RzStatusPane3: TRzStatusPane
        Left = 13
        Top = 126
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '计费单位'
      end
      object Label3: TLabel
        Left = 291
        Top = 131
        Width = 133
        Height = 14
        AutoSize = False
        Caption = '秒/升'
      end
      object edtTransMoney: TWVEdit
        Left = 132
        Top = 161
        Width = 157
        Height = 22
        Color = clBtnHighlight
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = False
        TabOrder = 4
        Text = '0'
      end
      object edtUnitMoney: TWVEdit
        Left = 132
        Top = 196
        Width = 157
        Height = 22
        Color = clBtnHighlight
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = False
        TabOrder = 5
        Text = '0'
      end
      object rgWaterType: TRzRadioGroup
        Left = 129
        Top = 23
        Width = 166
        Height = 21
        Color = 16184303
        Columns = 2
        GroupStyle = gsTopLine
        ItemIndex = 1
        Items.Strings = (
          '新天水控'
          '汇多水控')
        TextShadowDepth = 1
        TabOrder = 0
        ThemeAware = False
      end
      object rgCardFlag: TRzRadioGroup
        Left = 129
        Top = 231
        Width = 200
        Height = 21
        Color = 16184303
        Columns = 3
        GroupStyle = gsTopLine
        ItemIndex = 0
        Items.Strings = (
          '参数卡'
          '清零卡'
          '常开卡')
        TextShadowDepth = 1
        TabOrder = 6
        ThemeAware = False
      end
      object edtMin: TWVEdit
        Left = 132
        Top = 58
        Width = 157
        Height = 22
        Color = clBtnHighlight
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = False
        TabOrder = 1
        Text = '0'
      end
      object edtMax: TWVEdit
        Left = 132
        Top = 93
        Width = 157
        Height = 22
        Color = clBtnHighlight
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = False
        TabOrder = 2
        Text = '0'
      end
      object edtUnit: TWVEdit
        Left = 132
        Top = 127
        Width = 157
        Height = 22
        Color = clBtnHighlight
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = False
        TabOrder = 3
        Text = '0'
      end
    end
    object btnReadCard: TButton
      Left = 526
      Top = 349
      Width = 90
      Height = 25
      Caption = '回收设置卡'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnReadCardClick
    end
    object btnReleaseCard: TButton
      Left = 422
      Top = 349
      Width = 90
      Height = 25
      Caption = '发行设置卡'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnReleaseCardClick
    end
    object btnReadWaterFee: TButton
      Left = 318
      Top = 349
      Width = 90
      Height = 25
      Caption = '读取设置卡'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnReadWaterFeeClick
    end
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
        Name = '密钥'
        Caption = '密钥'
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
        Name = '参数标志'
        Caption = '参数标志'
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
        MonitorValueChangedFields = 
          '|交易卡号|充值金额|操作员代码|大钱包金额|大钱包次数|小钱包次数|' +
          '小钱包金额|'
      end>
    Left = 36
    Top = 231
  end
  inherited MainRequest: TWVRequest
    ID = '全局参数主键查询_water'
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
        FieldName = '参数标志'
      end
      item
        ParamName = '密钥'
        FieldName = '密钥'
        Direction = bdParam2Field
      end>
    Left = 80
    Top = 232
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 80
    Top = 264
  end
  inherited DataSource: TDataSource
    Left = 80
    Top = 296
  end
end
