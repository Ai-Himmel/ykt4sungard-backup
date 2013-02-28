inherited faqhPKGOper: TfaqhPKGOper
  Width = 1078
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 1078
    TabOrder = 2
    inherited btnQuery: TBitBtn
      Left = 901
      Top = 100
      Enabled = False
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 988
      Top = 100
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 1078
    TabOrder = 0
    inherited Image1: TImage
      Width = 1078
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 561
    Height = 441
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Top = 49
      Width = 561
      Height = 352
      Color = clWhite
      OnCellClick = GridCellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'scust_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '包裹ID'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '发送单位'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '包裹文件名'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '包裹编号'
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '城市代码'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '接收日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '接收时间'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '文件个数'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '处理日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '处理时间'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstock_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '处理状态'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstock_code2'
          PickList.Strings = ()
          Title.Caption = '错误代码'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr1'
          PickList.Strings = ()
          Title.Caption = '备注'
          Width = 120
          Visible = True
        end>
    end
    object Panel1: TPanel
      Left = 0
      Top = 0
      Width = 561
      Height = 49
      Align = alTop
      BevelOuter = bvNone
      ParentColor = True
      TabOrder = 1
      object Label4: TLabel
        Left = 5
        Top = 29
        Width = 72
        Height = 12
        Caption = '接收开始日期'
      end
      object Label6: TLabel
        Left = 370
        Top = 29
        Width = 48
        Height = 12
        Caption = '处理状态'
      end
      object Label7: TLabel
        Left = 185
        Top = 29
        Width = 72
        Height = 12
        Caption = '接收结束日期'
      end
      object edtBDate: TWVEdit
        Left = 79
        Top = 25
        Width = 101
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 2
        Text = '<开始日期>'
        WorkView = WorkView
        FieldName = '开始日期'
      end
      object WVComboBox3: TWVComboBox
        Left = 422
        Top = 25
        Width = 105
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 0
        WorkView = WorkView
        FieldName = '处理状态'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*235'
      end
      object edtEDate: TWVEdit
        Left = 259
        Top = 25
        Width = 102
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<结束日期>'
        WorkView = WorkView
        FieldName = '结束日期'
      end
      object pnl1: TPanel
        Left = 0
        Top = 0
        Width = 561
        Height = 20
        Align = alTop
        Alignment = taLeftJustify
        Caption = ' >>>包裹信息'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
      end
    end
    object pnlPKGbtm: TPanel
      Left = 0
      Top = 401
      Width = 561
      Height = 40
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 2
      object grp1: TGroupBox
        Left = 0
        Top = 0
        Width = 281
        Height = 40
        Align = alLeft
        Caption = '状态修改'
        TabOrder = 0
        object Label1: TLabel
          Left = 6
          Top = 17
          Width = 48
          Height = 12
          Caption = '处理状态'
        end
        object lbl1: TLabel
          Left = 142
          Top = 17
          Width = 24
          Height = 12
          Caption = '备注'
        end
        object WVComboBox1: TWVComboBox
          Left = 58
          Top = 14
          Width = 79
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 0
          WorkView = WVPKGOper
          FieldName = '处理状态'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*235'
        end
        object edt1: TWVEdit
          Left = 167
          Top = 14
          Width = 106
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
          Text = '<备注>'
          WorkView = WVPKGOper
          FieldName = '备注'
        end
      end
      object btnPKGQuery: TBitBtn
        Left = 314
        Top = 8
        Width = 70
        Height = 25
        Hint = '查询/刷新数据'
        Anchors = [akTop, akRight]
        Caption = '包裹查询'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = btnPKGQueryClick
      end
      object btnUStatus: TBitBtn
        Left = 394
        Top = 7
        Width = 70
        Height = 25
        Hint = '包裹状态修改'
        Anchors = [akTop, akRight]
        Caption = '状态修改'
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = btnUStatusClick
      end
      object btnDelPKG: TBitBtn
        Left = 474
        Top = 7
        Width = 70
        Height = 25
        Hint = '包裹删除'
        Anchors = [akTop, akRight]
        Caption = '包裹删除'
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = btnDelPKGClick
      end
    end
  end
  object RzSizePanel1: TRzSizePanel [3]
    Left = 561
    Top = 18
    Width = 517
    Height = 441
    Align = alRight
    HotSpotVisible = True
    SizeBarWidth = 7
    TabOrder = 3
    UseGradients = True
    object Panel2: TPanel
      Left = 8
      Top = 0
      Width = 509
      Height = 49
      Align = alTop
      BevelOuter = bvNone
      ParentColor = True
      TabOrder = 0
      object Label3: TLabel
        Left = 2
        Top = 29
        Width = 48
        Height = 12
        Caption = '处理状态'
      end
      object WVComboBox2: TWVComboBox
        Left = 54
        Top = 25
        Width = 105
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 0
        WorkView = WVFileQ
        FieldName = '处理状态'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*235'
      end
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 509
        Height = 20
        Align = alTop
        Alignment = taLeftJustify
        Caption = ' >>>包裹文件信息'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
      end
    end
    object GridFile: TRzDBGrid
      Left = 8
      Top = 49
      Width = 509
      Height = 352
      Align = alClient
      Color = clWhite
      DataSource = DataSource1
      FixedColor = 15458000
      TabOrder = 1
      TitleFont.Charset = GB2312_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -12
      TitleFont.Name = '宋体'
      TitleFont.Style = []
      OnDrawColumnCell = GridDrawColumnCell
      OnKeyDown = GridKeyDown
      FrameColor = 12164479
      FrameStyle = fsGroove
      FrameVisible = True
      FixedLineColor = 12164479
      LineColor = clBackground
      Columns = <
        item
          Expanded = False
          FieldName = 'scust_no'
          Title.Alignment = taCenter
          Title.Caption = '包裹ID'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          Title.Alignment = taCenter
          Title.Caption = '文件编号'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          Title.Alignment = taCenter
          Title.Caption = '文件名'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          Title.Alignment = taCenter
          Title.Caption = '序号'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          Title.Alignment = taCenter
          Title.Caption = '商户编号'
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          Title.Alignment = taCenter
          Title.Caption = '记录条数'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          Title.Alignment = taCenter
          Title.Caption = '总金额'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          Title.Alignment = taCenter
          Title.Caption = '处理日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime1'
          Title.Alignment = taCenter
          Title.Caption = '处理时间'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstock_code'
          Title.Alignment = taCenter
          Title.Caption = '处理状态'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstock_code2'
          Title.Caption = '错误代码'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr1'
          Title.Caption = '备注'
          Width = 120
          Visible = True
        end>
    end
    object Panel4: TPanel
      Left = 8
      Top = 401
      Width = 509
      Height = 40
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 2
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 267
        Height = 40
        Align = alLeft
        Caption = '状态修改'
        TabOrder = 0
        object Label8: TLabel
          Left = 6
          Top = 17
          Width = 48
          Height = 12
          Caption = '处理状态'
        end
        object Label2: TLabel
          Left = 134
          Top = 17
          Width = 24
          Height = 12
          Caption = '备注'
        end
        object WVComboBox4: TWVComboBox
          Left = 58
          Top = 14
          Width = 74
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 0
          WorkView = WVFileOper
          FieldName = '处理状态'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*235'
        end
        object WVEdit1: TWVEdit
          Left = 161
          Top = 14
          Width = 101
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
          Text = '<备注>'
          WorkView = WVFileOper
          FieldName = '备注'
        end
      end
      object btnFileU: TBitBtn
        Left = 349
        Top = 7
        Width = 71
        Height = 25
        Hint = '文件状态修改'
        Anchors = [akTop, akRight]
        Caption = '状态修改'
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = btnFileUClick
      end
      object btnFileDel: TBitBtn
        Left = 429
        Top = 7
        Width = 71
        Height = 25
        Hint = '包裹删除'
        Anchors = [akTop, akRight]
        Caption = '文件删除'
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = btnFileDelClick
      end
      object btnFileQuery: TBitBtn
        Left = 270
        Top = 8
        Width = 71
        Height = 25
        Hint = '查询/刷新数据'
        Anchors = [akTop, akRight]
        Caption = '文件查询'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = btnFileQueryClick
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
        Name = '结束日期'
        Caption = '结束日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        MonitorValueChangedFields = '|结束日期|'
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '开始日期'
        Caption = '开始日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        MonitorValueChangedFields = '|开始日期|'
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '处理状态'
        Caption = '处理状态'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|站点号|站点流水号|操作员|交易日期|交易码|流水状态|'
      end>
    Left = 92
    Top = 215
  end
  inherited MainRequest: TWVRequest
    ID = '包裹查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '开始日期'
        FieldName = '开始日期'
      end
      item
        ParamName = '结束日期'
        FieldName = '结束日期'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '处理状态'
        FieldName = '处理状态'
      end>
    Left = 128
    Top = 216
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lwithdraw_flag'
        DataPresentType = 'idobjects'
        DataPresentParam = '-33'
      end
      item
        FieldName = 'sstock_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '235'
      end
      item
        FieldName = 'sstock_code2'
        DataPresentType = 'idobjects'
        DataPresentParam = '232'
      end>
    Left = 160
    Top = 216
  end
  inherited DataSource: TDataSource
    Left = 192
    Top = 216
  end
  object WVRPKGOper: TWVRequest
    WorkView = WVPKGOper
    ID = '包裹操作'
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
        ParamName = '包裹编号'
        FieldName = '包裹编号'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '处理状态'
        FieldName = '处理状态'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
    AfterExec = MainRequestAfterExec
    Left = 128
    Top = 296
  end
  object WVPKGOper: TWorkView
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
        Name = '包裹编号'
        Caption = '包裹编号'
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
        Name = '处理状态'
        Caption = '处理状态'
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
        Name = '操作标志'
        Caption = '操作标志'
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
        Name = '备注'
        Caption = '备注'
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
        MonitorValueChangedFields = '|站点号|站点流水号|操作员|交易日期|交易码|流水状态|'
      end>
    Left = 92
    Top = 295
  end
  object WVFileQ: TWorkView
    WorkFields = <
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
        Name = '处理状态'
        Caption = '处理状态'
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
        Name = '操作标志'
        Caption = '操作标志'
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
        Name = '包裹编号'
        Caption = '包裹编号'
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
        MonitorValueChangedFields = '|站点号|站点流水号|操作员|交易日期|交易码|流水状态|'
      end>
    Left = 604
    Top = 207
  end
  object WVRFileQ: TWVRequest
    WorkView = WVFileQ
    ID = '文件查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '处理状态'
        FieldName = '处理状态'
      end
      item
        ParamName = '包裹编号'
        FieldName = '包裹编号'
      end>
    AfterExec = MainRequestAfterExec
    Left = 640
    Top = 208
  end
  object WVDBBinder1: TWVDBBinder
    DataSource = DataSource1
    WorkView = WVFileQ
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lwithdraw_flag'
        DataPresentType = 'idobjects'
        DataPresentParam = '-33'
      end
      item
        FieldName = 'sstock_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '235'
      end
      item
        FieldName = 'sstock_code2'
        DataPresentType = 'idobjects'
        DataPresentParam = '232'
      end>
    HideUnbindingFields = False
    Left = 672
    Top = 208
  end
  object DataSource1: TDataSource
    OnDataChange = DataSourceDataChange
    Left = 704
    Top = 208
  end
  object WVFileOper: TWorkView
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
        Name = '包裹编号'
        Caption = '包裹编号'
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
        Name = '处理状态'
        Caption = '处理状态'
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
        Name = '操作标志'
        Caption = '操作标志'
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
        Name = '备注'
        Caption = '备注'
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
        MonitorValueChangedFields = '|站点号|站点流水号|操作员|交易日期|交易码|流水状态|'
      end>
    Left = 604
    Top = 247
  end
  object WVRFileOper: TWVRequest
    WorkView = WVFileOper
    ID = '文件操作'
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
        ParamName = '包裹编号'
        FieldName = '包裹编号'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '处理状态'
        FieldName = '处理状态'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
    AfterExec = MainRequestAfterExec
    Left = 640
    Top = 248
  end
end
