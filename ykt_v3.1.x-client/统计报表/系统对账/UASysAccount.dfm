inherited faqhSysAccount: TfaqhSysAccount
  Width = 762
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 453
    Width = 762
    Height = 36
    TabOrder = 3
    object lbl1: TLabel [0]
      Left = 16
      Top = 16
      Width = 48
      Height = 12
      Caption = '对账日期'
    end
    object lbl2: TLabel [1]
      Left = 160
      Top = 16
      Width = 48
      Height = 12
      Caption = '对账类型'
    end
    inherited btnQuery: TBitBtn
      Left = 583
      Top = 6
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00B5848400B5848400B5848400B5848400B5848400B5848400B5848400B584
        8400B5848400B5848400B5848400B5848400B5848400FFFFFF00FFFFFF00FFFF
        FF00636B7B00FFEFD600F7E7C600F7DEBD00F7DEB500F7D6AD00F7D6A500F7CE
        9C00F7CE9400F7CE9C00F7CE9C00F7D69C00B5848400FFFFFF00FFFFFF005A9C
        C600318CD6007B849C00F7E7CE00F7DEC600F7DEBD00F7D6B500F7D6AD00F7D6
        A500EFCE9C00EFCE9400EFCE9400F7D69C00B5848400FFFFFF00FFFFFF00FFFF
        FF004AB5FF00298CE70084849C00F7E7CE00F7DEC600F7DEBD00F7D6B500F7D6
        AD00F7D6A500EFCE9C00EFCE9400F7D69C00B5848400FFFFFF00FFFFFF00FFFF
        FF00B58473004AB5FF00218CDE007B849C00F7E7CE00F7DEC600F7DEBD00F7D6
        B500F7D6AD00F7D6A500EFCE9C00F7D69C00B5848400FFFFFF00FFFFFF00FFFF
        FF00BD8C8400FFFFF7004ABDFF005A94BD00A5847B00BD948C00AD7B7B00BD94
        8C00D6B59C00F7D6AD00F7D6A500F7D69C00B5848400FFFFFF00FFFFFF00FFFF
        FF00BD8C8400FFFFFF00FFF7EF00BDA59C00C6A59C00E7CEBD00F7DEC600E7C6
        AD00C69C9400D6B59C00F7D6AD00F7D6A500B5848400FFFFFF00FFFFFF00FFFF
        FF00CE9C8400FFFFFF00FFFFF700C69C9400E7CEC600FFEFDE00FFE7D600FFFF
        F700E7C6AD00BD948C00F7DEB500F7DEAD00B5848400FFFFFF00FFFFFF00FFFF
        FF00CE9C8400FFFFFF00FFFFFF00AD7B7B00FFEFE700FFEFE700FFEFDE00FFFF
        F700F7DEC600AD7B7B00F7DEBD00FFDEB500B5848400FFFFFF00FFFFFF00FFFF
        FF00DEAD8400FFFFFF00FFFFFF00C69C9C00E7D6D600FFF7EF00FFEFE700FFFF
        DE00E7CEBD00BD948C00F7E7C600F7DEB500B5848400FFFFFF00FFFFFF00FFFF
        FF00DEAD8400FFFFFF00FFFFFF00DECECE00CEADAD00E7D6D600FFEFE700E7CE
        C600C6A59C00C6A59400E7DEC600C6BDAD00B5848400FFFFFF00FFFFFF00FFFF
        FF00E7B58C00FFFFFF00FFFFFF00FFFFFF00DECECE00C69C9C00AD7B7B00C69C
        9400D6BDB500BD847B00BD847B00BD847B00B5848400FFFFFF00FFFFFF00FFFF
        FF00E7B58C00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00E7CECE00BD847B00EFB57300EFA54A00C6846B00FFFFFF00FFFFFF00FFFF
        FF00EFBD9400FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00E7D6D600BD847B00FFC67300CE947300FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00EFBD9400FFF7F700FFF7F700FFF7F700FFF7F700FFF7F700FFF7F700FFF7
        F700E7D6CE00BD847B00CE9C8400FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00EFBD9400DEAD8400DEAD8400DEAD8400DEAD8400DEAD8400DEAD8400DEAD
        8400DEAD8400BD847B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
    end
    inherited btnPrint: TBitBtn
      Left = 674
      Top = 6
    end
    object edtAccDate: TEdit
      Left = 70
      Top = 11
      Width = 75
      Height = 20
      MaxLength = 8
      TabOrder = 4
    end
    object btnAcc: TButton
      Left = 344
      Top = 7
      Width = 75
      Height = 25
      Caption = '系统对账'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnAccClick
    end
    object cbbSysType: TWVComboBox
      Left = 212
      Top = 10
      Width = 122
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '对账类型'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-61'
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 762
    inherited Image1: TImage
      Width = 762
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 762
    Height = 48
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label6: TLabel
      Left = 18
      Top = 9
      Width = 48
      Height = 12
      Caption = '开始日期'
    end
    object lblTip: TWVLabel
      Left = 18
      Top = 32
      Width = 737
      Height = 12
      AutoSize = False
      Caption = '生效时间'
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label1: TLabel
      Left = 186
      Top = 11
      Width = 48
      Height = 12
      Caption = '结束日期'
    end
    object Label2: TLabel
      Left = 352
      Top = 9
      Width = 48
      Height = 12
      Caption = '对账类型'
    end
    object Label3: TLabel
      Left = 536
      Top = 10
      Width = 48
      Height = 12
      Caption = '查询类型'
    end
    object edtBdate: TWVEdit
      Left = 68
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 8
      ReadOnly = False
      TabOrder = 2
      Text = '<开始日期>'
      WorkView = WorkView1
      FieldName = '开始日期'
    end
    object edtEdate: TWVEdit
      Left = 236
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 8
      ReadOnly = False
      TabOrder = 3
      Text = '<结束日期>'
      WorkView = WorkView1
      FieldName = '结束日期'
    end
    object cbbQType: TComboBox
      Left = 588
      Top = 4
      Width = 114
      Height = 20
      Style = csDropDownList
      ItemHeight = 12
      TabOrder = 1
      Items.Strings = (
        '全部'
        '银行多于一卡通'
        '一卡通多于银行')
    end
    object cbbQAcctype: TWVComboBox
      Left = 404
      Top = 4
      Width = 118
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView1
      FieldName = '对账类型'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-61'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 66
    Width = 762
    Height = 387
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 762
      Height = 387
      Columns = <
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易日期'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sholder_ac_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易参考号'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '卡号'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Caption = '客户号'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '学工号'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '姓名'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '银行卡号'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '金额'
          Width = 70
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
        Name = '对账日期'
        Caption = '对账日期'
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
        Name = '对账类型'
        Caption = '对账类型'
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
    Left = 84
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '系统对账'
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
        ParamName = '对账日期'
        FieldName = '对账日期'
      end
      item
        ParamName = '对账类型'
        FieldName = '对账类型'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    WorkView = WorkView1
    FieldName = '查询结果集'
    Left = 176
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 216
    Top = 256
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
        DataField = '@Dataset'
      end
      item
        Name = '开始日期'
        Caption = '开始日期'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '结束日期'
        Caption = '结束日期'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '对账类型'
        Caption = '对账类型'
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
        Name = '查询类别'
        Caption = '查询类别'
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
        Name = '一卡通次数'
        Caption = '一卡通次数'
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
        Name = '银行次数'
        Caption = '银行次数'
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
    FieldsMonitors = <>
    Left = 84
    Top = 199
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '系统对账查询'
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
        ParamName = '银行次数'
        FieldName = '银行次数'
        Direction = bdParam2Field
      end
      item
        ParamName = '一卡通次数'
        FieldName = '一卡通次数'
        Direction = bdParam2Field
      end
      item
        ParamName = '结束日期'
        FieldName = '结束日期'
      end
      item
        ParamName = '开始日期'
        FieldName = '开始日期'
      end
      item
        ParamName = '查询类别'
        FieldName = '查询类别'
      end
      item
        ParamName = '对账类型'
        FieldName = '对账类型'
      end>
    AfterExec = MainRequestAfterExec
    Left = 128
    Top = 200
  end
end
