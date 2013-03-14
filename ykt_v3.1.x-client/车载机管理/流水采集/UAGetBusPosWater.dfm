inherited faqhGetBusPosWater: TfaqhGetBusPosWater
  Width = 828
  Height = 504
  inherited UIPanel1: TUIPanel
    Top = 504
    Width = 828
    Height = 0
    TabOrder = 4
    object Label4: TLabel [0]
      Left = 13
      Top = 11
      Width = 9
      Height = 16
      Font.Charset = GB2312_CHARSET
      Font.Color = clRed
      Font.Height = -16
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
    end
    inherited btnQuery: TBitBtn
      Left = 641
      Top = 5
      Hint = ''
    end
    inherited btnPrint: TBitBtn
      Left = 726
      Top = 5
      Hint = ''
      Enabled = True
    end
    object ImageButton1: TImageButton
      Left = 752
      Top = 11
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '确定'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = ImageButton1Click
      CommandName = '查询'
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 828
    Height = 16
    TabOrder = 0
    inherited Image1: TImage
      Width = 828
      Height = 16
    end
    inherited LabRecordCount: TLabel
      Left = 12
      Width = 481
      Font.Color = clBlue
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 16
    Width = 828
    Height = 0
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 2
    object Label2: TLabel
      Left = 531
      Top = 58
      Width = 72
      Height = 12
      Caption = '是否交搭伙费'
      Visible = False
    end
    object WVLabel1: TWVLabel
      Left = 40
      Top = 58
      Width = 108
      Height = 12
      Caption = '第一次收取卡成本费'
      Visible = False
    end
    object WVLabel2: TWVLabel
      Left = 295
      Top = 58
      Width = 84
      Height = 12
      Caption = '是否退卡成本费'
      Visible = False
    end
    object WVComboBox1: TWVComboBox
      Left = 615
      Top = 53
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      Visible = False
      WorkView = WorkView
      FieldName = '是否交搭伙费'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*2'
    end
    object WVComboBox2: TWVComboBox
      Left = 159
      Top = 53
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 0
      Visible = False
      WorkView = WorkView
      FieldName = '第一次是否收取卡成本费'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*2'
    end
    object WVComboBox3: TWVComboBox
      Left = 391
      Top = 53
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 1
      Visible = False
      WorkView = WorkView
      FieldName = '是否退卡成本费'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*2'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 16
    Width = 828
    Height = 488
    TabOrder = 3
    inherited Grid: TRzDBGrid
      Width = 828
      Height = 488
    end
  end
  object Panel2: TPanel [4]
    Left = 0
    Top = 16
    Width = 828
    Height = 488
    Align = alClient
    Color = 16184303
    TabOrder = 1
    object Panel4: TPanel
      Left = 1
      Top = 434
      Width = 826
      Height = 53
      Align = alBottom
      Color = 16184303
      TabOrder = 1
      object Label3: TLabel
        Left = 8
        Top = 14
        Width = 84
        Height = 14
        Caption = '选择流水文件'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object edtFile: TEdit
        Left = 96
        Top = 10
        Width = 369
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        TabOrder = 4
      end
      object btnOpenfile: TImageButton
        Left = 571
        Top = 8
        Width = 75
        Height = 25
        Anchors = [akTop, akRight]
        Caption = '打开文件'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = btnOpenfileClick
      end
      object btnAnaSerial: TImageButton
        Left = 655
        Top = 8
        Width = 75
        Height = 25
        Anchors = [akTop, akRight]
        Caption = '分析流水'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = btnAnaSerialClick
      end
      object btngetSerial: TImageButton
        Left = 488
        Top = 8
        Width = 75
        Height = 25
        Anchors = [akTop, akRight]
        Caption = '提取流水'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = btngetSerialClick
      end
      object btnTrans: TImageButton
        Left = 738
        Top = 8
        Width = 75
        Height = 25
        Anchors = [akTop, akRight]
        Caption = '上传流水'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = btnTransClick
      end
    end
    object ListView1: TListView
      Left = 1
      Top = 1
      Width = 826
      Height = 433
      Align = alClient
      Columns = <
        item
          Caption = '物理ID号'
          Width = 80
        end
        item
          Caption = '流水号'
          Width = 56
        end
        item
          Caption = '交易卡号'
          Width = 100
        end
        item
          Alignment = taRightJustify
          Caption = '入卡金额'
          Width = 60
        end
        item
          Alignment = taRightJustify
          Caption = '交易金额'
          Width = 60
        end
        item
          Alignment = taRightJustify
          Caption = '出卡金额'
          Width = 61
        end
        item
          Caption = '卡中交易次数'
          Width = 100
        end
        item
          Caption = '交易日期'
          Width = 80
        end
        item
          Caption = '交易时间'
          Width = 80
        end
        item
          Caption = '交易标志'
          Width = 100
        end
        item
          Caption = '交易类型'
          Width = 60
        end
        item
          Caption = '钱包号'
          Width = 51
        end
        item
          Caption = 'CRC'
          Width = 60
        end>
      GridLines = True
      RowSelect = True
      TabOrder = 0
      ViewStyle = vsReport
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
        Name = '客户类别名称'
        Caption = '客户类别名称'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '是否交搭伙费'
        Caption = '是否交搭伙费'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '搭伙费费率'
        Caption = '搭伙费费率'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '正式卡有效期'
        Caption = '正式卡有效期'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '押金金额'
        Caption = '押金金额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '卡成本费'
        Caption = '卡成本费'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '手续金额'
        Caption = '手续金额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '第一次是否收取卡成本费'
        Caption = '第一次是否收取卡成本费'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '是否退卡成本费'
        Caption = '是否退卡成本费'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '账户最大余额'
        Caption = '账户最大余额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|'
      end>
    Left = 108
    Top = 487
  end
  inherited MainRequest: TWVRequest
    ID = '客户类别非主键查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '客户类别名称'
        FieldName = '客户类别名称'
      end
      item
        ParamName = '是否交搭伙费'
        FieldName = '是否交搭伙费'
      end
      item
        ParamName = '搭伙费费率'
        FieldName = '搭伙费费率'
      end
      item
        ParamName = '正式卡有效期'
        FieldName = '正式卡有效期'
      end
      item
        ParamName = '押金金额'
        FieldName = '押金金额'
      end
      item
        ParamName = '卡成本费'
        FieldName = '卡成本费'
      end
      item
        ParamName = '手续金额'
        FieldName = '手续金额'
      end
      item
        ParamName = '第一次是否收取卡成本费'
        FieldName = '第一次是否收取卡成本费'
      end
      item
        ParamName = '是否退卡成本费'
        FieldName = '是否退卡成本费'
      end
      item
        ParamName = '账户最大余额'
        FieldName = '账户最大余额'
      end>
    Left = 152
    Top = 496
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'smain_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
      end>
    Left = 200
    Top = 496
  end
  inherited DataSource: TDataSource
    Left = 336
    Top = 496
  end
  object SaveDialog1: TSaveDialog
    Filter = '文本文件|*.txt'
    Title = '无效流水保存'
    Left = 272
    Top = 496
  end
  object OpenDialog1: TOpenDialog
    Filter = '车载机流水文件(*.bps)|*.bps'
    Left = 272
    Top = 368
  end
  object upwaterdata: TWorkView
    WorkFields = <
      item
        Name = '流水号'
        Caption = '流水号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '物理卡号'
        Caption = '物理卡号'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '交易卡号'
        Caption = '交易卡号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '工作站标示'
        Caption = '工作站标示'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '入卡金额'
        Caption = '入卡金额'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '出卡金额'
        Caption = '出卡金额'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '消费金额'
        Caption = '消费金额'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '钱包'
        Caption = '钱包'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '消费次数'
        Caption = '消费次数'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '交易标志'
        Caption = '交易标志'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
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
        DefaultValue = '0'
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
      end
      item
        Name = 'CRC校验码'
        Caption = 'CRC校验码'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '发生日期'
        Caption = '发生日期'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '发生时间'
        Caption = '发生时间'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '物理编号2'
        Caption = '物理编号2'
        FieldType = wftUndefined
        DataType = kdtString
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
        MonitorValueChangedFields = '|'
      end>
    Left = 236
    Top = 327
  end
  object WVRequest1: TWVRequest
    WorkView = upwaterdata
    ID = '上传流水'
    Bindings = <
      item
        ParamName = '流水号'
        FieldName = '流水号'
        DefaultValue = '0'
      end
      item
        ParamName = '交易卡号'
        FieldName = '交易卡号'
        DefaultValue = '0'
      end
      item
        ParamName = '物理ID'
        FieldName = '物理卡号'
        DefaultValue = '0'
      end
      item
        ParamName = '工作站标示'
        FieldName = '工作站标示'
        DefaultValue = '0'
      end
      item
        ParamName = '入卡金额'
        FieldName = '入卡金额'
        DefaultValue = '0'
      end
      item
        ParamName = '出卡金额'
        FieldName = '出卡金额'
        DefaultValue = '0'
      end
      item
        ParamName = '消费金额'
        FieldName = '消费金额'
        DefaultValue = '0'
      end
      item
        ParamName = '钱包'
        FieldName = '钱包'
        DefaultValue = '0'
      end
      item
        ParamName = '消费次数'
        FieldName = '消费次数'
        DefaultValue = '0'
      end
      item
        ParamName = '交易标志'
        FieldName = '交易标志'
        DefaultValue = '0'
      end
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
        DefaultValue = '0'
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
        DefaultValue = '0'
      end
      item
        ParamName = 'CRC校验码'
        FieldName = 'CRC校验码'
      end
      item
        ParamName = '发生日期'
        FieldName = '发生日期'
      end
      item
        ParamName = '发生时间'
        FieldName = '发生时间'
      end
      item
        ParamName = '物理编号2'
        FieldName = '物理编号2'
      end>
    AfterExec = MainRequestAfterExec
    Left = 272
    Top = 328
  end
end
