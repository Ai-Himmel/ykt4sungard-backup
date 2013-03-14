inherited faqhBusPosManage: TfaqhBusPosManage
  Width = 807
  Height = 650
  inherited UIPanel1: TUIPanel
    Top = 647
    Width = 807
    Height = 3
    TabOrder = 4
    inherited btnQuery: TBitBtn
      Left = 624
      Top = 5
      Hint = ''
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 717
      Top = 5
      Hint = ''
      Enabled = True
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 807
    Height = 16
    TabOrder = 0
    inherited Image1: TImage
      Width = 807
      Height = 16
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 16
    Width = 807
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
    Width = 807
    Height = 631
    TabOrder = 3
    inherited Grid: TRzDBGrid
      Width = 807
      Height = 631
    end
  end
  object Panel2: TPanel [4]
    Left = 0
    Top = 16
    Width = 807
    Height = 631
    Align = alClient
    BevelOuter = bvNone
    Color = 16184303
    TabOrder = 1
    object GroupBox2: TGroupBox
      Left = 64
      Top = 29
      Width = 666
      Height = 99
      Caption = '消费参数设置'
      TabOrder = 1
      object Label5: TLabel
        Left = 53
        Top = 20
        Width = 72
        Height = 12
        Caption = '消费参数版本'
      end
      object Label6: TLabel
        Left = 398
        Top = 20
        Width = 48
        Height = 12
        Caption = '基本费率'
      end
      object Label7: TLabel
        Left = 614
        Top = 20
        Width = 12
        Height = 12
        Caption = '元'
      end
      object Label8: TLabel
        Left = 29
        Top = 48
        Width = 96
        Height = 12
        Caption = '采集流水时间间隔'
      end
      object Label9: TLabel
        Left = 277
        Top = 48
        Width = 12
        Height = 12
        Caption = '天'
      end
      object Label10: TLabel
        Left = 350
        Top = 48
        Width = 96
        Height = 12
        Caption = '连续刷卡时间间隔'
      end
      object Label11: TLabel
        Left = 614
        Top = 48
        Width = 12
        Height = 12
        Caption = '秒'
      end
      object edtConParaVer: TWVEdit
        Left = 128
        Top = 16
        Width = 140
        Height = 20
        ReadOnly = True
        TabOrder = 0
        Text = 'WVEdit1'
      end
      object edtBaseFee: TWVEdit
        Left = 449
        Top = 16
        Width = 161
        Height = 20
        ReadOnly = False
        TabOrder = 1
        Text = 'WVEdit1'
      end
      object edtTimeSplit: TWVEdit
        Left = 128
        Top = 44
        Width = 140
        Height = 20
        ReadOnly = False
        TabOrder = 2
        Text = 'WVEdit1'
      end
      object edtCardTimeSpace: TWVEdit
        Left = 449
        Top = 44
        Width = 161
        Height = 20
        ReadOnly = False
        TabOrder = 3
        Text = 'WVEdit1'
      end
      object btnCreateFile: TImageButton
        Left = 528
        Top = 70
        Width = 100
        Height = 23
        Anchors = [akTop, akRight]
        Caption = '传消费参数'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnClick = btnCreateFileClick
      end
      object CheckBox1: TCheckBox
        Left = 408
        Top = 73
        Width = 112
        Height = 17
        Caption = '上传手持机文件'
        Checked = True
        State = cbChecked
        TabOrder = 5
        Visible = False
      end
    end
    object grpWelcome: TGroupBox
      Left = 64
      Top = 1000
      Width = 666
      Height = 53
      Caption = '欢迎信息设置'
      TabOrder = 5
      Visible = False
      object Label13: TLabel
        Left = 40
        Top = 26
        Width = 48
        Height = 12
        Caption = '欢迎信息'
      end
      object edtWelcome: TWVEdit
        Left = 93
        Top = 22
        Width = 284
        Height = 20
        ReadOnly = False
        TabOrder = 1
        Text = 'WVEdit1'
      end
      object ImageButton2: TImageButton
        Left = 552
        Top = 21
        Width = 76
        Height = 23
        Anchors = [akTop, akRight]
        Caption = '生成文件'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = ImageButton2Click
      end
      object CheckBox2: TCheckBox
        Left = 408
        Top = 24
        Width = 112
        Height = 17
        Caption = '上传手持机文件'
        TabOrder = 2
      end
    end
    object grpBlackList: TGroupBox
      Left = 64
      Top = 564
      Width = 666
      Height = 43
      Caption = '黑名单设置'
      TabOrder = 4
      object btnBala: TImageButton
        Left = 528
        Top = 14
        Width = 100
        Height = 23
        Anchors = [akTop, akRight]
        Caption = '传黑名单'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = btnBalaClick
      end
      object CheckBox3: TCheckBox
        Left = 408
        Top = 19
        Width = 112
        Height = 17
        Caption = '上传手持机文件'
        Checked = True
        State = cbChecked
        TabOrder = 1
        Visible = False
      end
    end
    object GroupBox5: TGroupBox
      Left = 64
      Top = 133
      Width = 666
      Height = 228
      Caption = '卡权限设置'
      TabOrder = 2
      object Label15: TLabel
        Left = 64
        Top = 19
        Width = 60
        Height = 12
        Caption = '卡权限版本'
      end
      object Label4: TLabel
        Left = 232
        Top = 203
        Width = 48
        Height = 12
        Caption = '费率比例'
      end
      object edtCardLimit: TWVEdit
        Left = 128
        Top = 15
        Width = 141
        Height = 20
        ReadOnly = True
        TabOrder = 1
        Text = 'WVEdit1'
      end
      object btnSetLimit: TImageButton
        Left = 528
        Top = 14
        Width = 100
        Height = 23
        Anchors = [akTop, akRight]
        Caption = '传卡权限'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = btnSetLimitClick
      end
      object CheckBox4: TCheckBox
        Left = 408
        Top = 17
        Width = 112
        Height = 17
        Caption = '上传手持机文件'
        Checked = True
        State = cbChecked
        TabOrder = 2
        Visible = False
      end
      object ListView1: TListView
        Left = 6
        Top = 40
        Width = 652
        Height = 153
        BiDiMode = bdLeftToRight
        Checkboxes = True
        Columns = <
          item
            Caption = '收费类别'
            Width = 100
          end
          item
            Caption = '收费名称'
            Width = 100
          end
          item
            Caption = '费率比例'
            Width = 100
          end>
        ColumnClick = False
        MultiSelect = True
        ReadOnly = True
        RowSelect = True
        ParentBiDiMode = False
        TabOrder = 3
        ViewStyle = vsReport
        OnClick = ListView1Click
      end
      object edtFeeBal: TEdit
        Left = 285
        Top = 199
        Width = 121
        Height = 20
        TabOrder = 5
        OnKeyPress = edtFeeBalKeyPress
      end
      object CheckBox5: TCheckBox
        Left = 31
        Top = 201
        Width = 97
        Height = 17
        Caption = '全选/全不选'
        TabOrder = 6
        OnClick = CheckBox5Click
      end
      object btnLimitEdit: TImageButton
        Left = 528
        Top = 198
        Width = 100
        Height = 23
        Anchors = [akTop, akRight]
        Caption = '修 改'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnClick = btnLimitEditClick
      end
    end
    object btnTime: TImageButton
      Left = 592
      Top = 6
      Width = 100
      Height = 23
      Caption = '同步时钟'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnTimeClick
    end
    object GroupBox1: TGroupBox
      Left = 64
      Top = 364
      Width = 666
      Height = 174
      Caption = '语音设置'
      TabOrder = 3
      object lbl2: TLabel
        Left = 213
        Top = 146
        Width = 76
        Height = 12
        AutoSize = False
        Caption = '语音分组类别'
      end
      object lblFeeType: TLabel
        Left = 7
        Top = 146
        Width = 180
        Height = 12
        AutoSize = False
        Caption = '语音分组类别'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object btnSoundSet: TImageButton
        Left = 528
        Top = 142
        Width = 100
        Height = 23
        Anchors = [akTop, akRight]
        Caption = '传语音设置'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = btnSoundSetClick
      end
      object CheckBox6: TCheckBox
        Left = 408
        Top = 19
        Width = 112
        Height = 17
        Caption = '上传手持机文件'
        Checked = True
        State = cbChecked
        TabOrder = 1
        Visible = False
      end
      object lvSound: TListView
        Left = 6
        Top = 16
        Width = 652
        Height = 121
        BiDiMode = bdLeftToRight
        Columns = <
          item
            Caption = '收费类别'
            Width = 100
          end
          item
            Caption = '收费名称'
            Width = 100
          end
          item
            Caption = '语音分组类别'
            Width = 100
          end
          item
            Caption = '语音分组名称'
            Width = 100
          end>
        ColumnClick = False
        MultiSelect = True
        ReadOnly = True
        RowSelect = True
        ParentBiDiMode = False
        TabOrder = 0
        ViewStyle = vsReport
        OnClick = lvSoundClick
      end
      object cbbSound: TRzComboBox
        Left = 288
        Top = 143
        Width = 121
        Height = 20
        Style = csDropDownList
        ItemHeight = 12
        TabOrder = 3
        Text = '0-默认类别'
        OnChange = cbbSoundChange
        Items.Strings = (
          '0-默认类别'
          '1-教师卡'
          '2-学生卡'
          '3-职工卡'
          '4-临时卡')
        ItemIndex = 0
      end
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
    Left = 356
    Top = 207
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
    Left = 392
    Top = 208
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
    Left = 424
    Top = 208
  end
  inherited DataSource: TDataSource
    Left = 456
    Top = 208
  end
  object SaveDialog1: TSaveDialog
    Left = 488
    Top = 212
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
        Name = '返回数据集'
        Caption = '返回数据集'
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
    FieldsMonitors = <>
    Left = 352
    Top = 240
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '读取黑名单'
    Bindings = <
      item
        ParamName = '返回数据集'
        FieldName = '返回数据集'
        Direction = bdParam2Field
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
    Left = 416
    Top = 240
  end
  object DataSource1: TDataSource
    Left = 448
    Top = 240
  end
  object WVDBBinder1: TWVDBBinder
    DataSource = DataSource1
    WorkView = WorkView1
    FieldName = '返回数据集'
    Bindings = <>
    HideUnbindingFields = False
    Left = 384
    Top = 240
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
        Name = '返回数据集'
        Caption = '返回数据集'
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
        Name = '字典编号'
        Caption = '字典编号'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 'R'
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    Left = 352
    Top = 296
  end
  object WVDBBinder2: TWVDBBinder
    DataSource = DataSource2
    WorkView = WorkView2
    FieldName = '返回数据集'
    Bindings = <>
    HideUnbindingFields = False
    Left = 384
    Top = 296
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '读取卡类型'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '返回数据集'
        Direction = bdParam2Field
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
      end
      item
        ParamName = '参数标志'
        FieldName = '字典编号'
        DefaultValue = 'R'
      end>
    Left = 416
    Top = 296
  end
  object DataSource2: TDataSource
    Left = 448
    Top = 296
  end
end
