inherited faqhDevBusiAllot: TfaqhDevBusiAllot
  Width = 1038
  Height = 489
  inherited UIPnlQueryCount: TUIPanel [0]
    Width = 1038
    TabOrder = 2
    inherited Image1: TImage
      Width = 1038
    end
    inherited LabRecordCount: TLabel
      Font.Color = clBlack
      Visible = False
    end
  end
  inherited UIPanel1: TUIPanel [1]
    Top = 456
    Width = 1038
    Height = 33
    TabOrder = 3
    object lblBusi: TLabel [0]
      Left = 16
      Top = 8
      Width = 497
      Height = 12
      AutoSize = False
      Caption = 'lblBusi'
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    inherited btnQuery: TBitBtn
      Left = 853
      Caption = '绑 定'
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 476
      Top = 200
      TabOrder = 2
    end
    object btnDel: TBitBtn
      Left = 949
      Top = 3
      Width = 79
      Height = 25
      Hint = '删除'
      Anchors = [akTop, akRight]
      Caption = '解除绑定'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnDelClick
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 524
    Width = 514
    Height = 438
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Left = 96
      Top = 240
      Width = 270
      Height = 142
      Align = alNone
      DataSource = nil
      TabOrder = 2
      Columns = <
        item
          Expanded = False
          FieldName = 'lserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '所在区域'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '设备标识'
          Width = 68
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '设备名称'
          Width = 87
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '设备物理ID'
          Width = 71
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '机号'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '机型代码'
          Width = 72
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '服务器端口总数'
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt6'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '上级设备'
          Width = 68
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scurrency_type'
          PickList.Strings = ()
          Title.Caption = '卡片结构'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '服务器端口号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '设备状态'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_code2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '通讯端口号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '设备类型'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstation0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'IP地址'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '所属子系统'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ssectypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '备注'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'damt5'
          PickList.Strings = ()
          Title.Caption = '设备用途'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt4'
          PickList.Strings = ()
          Title.Caption = '是否支持科目收费'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Caption = '通讯类别'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '导入批次号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '黑名单版本'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Caption = '备注'
          Width = 120
          Visible = True
        end>
    end
    object lvDev: TRzListView
      Left = 0
      Top = 85
      Width = 514
      Height = 156
      Align = alClient
      Columns = <
        item
          Caption = '地区编码'
          Width = 100
        end
        item
          Caption = '设备编号'
          Width = 70
        end
        item
          Caption = '设备名称'
          Width = 120
        end
        item
          Caption = '设备终端号'
          Width = 80
        end
        item
          Caption = '设备序列号'
          Width = 100
        end
        item
          Caption = '设备型号'
          Width = 80
        end
        item
          Caption = '设备类型'
          Width = 80
        end
        item
          Caption = '设备用途'
          Width = 80
        end
        item
          Caption = '设备状态'
          Width = 80
        end
        item
          Caption = '启用日期'
          Width = 80
        end>
      FlatScrollBars = True
      GridLines = True
      RowSelect = True
      TabOrder = 0
      ViewStyle = vsReport
      OnClick = lvDevClick
    end
    object rzszpnl1: TRzSizePanel
      Left = 0
      Top = 241
      Width = 514
      Height = 197
      Align = alBottom
      HotSpotVisible = True
      SizeBarWidth = 7
      TabOrder = 1
      UseGradients = True
      object lvAllotDev: TRzListView
        Left = 0
        Top = 33
        Width = 514
        Height = 164
        Align = alClient
        Checkboxes = True
        Columns = <
          item
            Caption = '设备编号'
            Width = 70
          end
          item
            Caption = '设备名称'
            Width = 100
          end
          item
            Caption = '设备终端序列号'
            Width = 100
          end
          item
            Caption = '商户编号'
            Width = 70
          end
          item
            Caption = '商户名称'
            Width = 90
          end
          item
            Caption = '产品编号'
            Width = 80
          end
          item
            Caption = '设备终端号'
            Width = 80
          end
          item
            Caption = '设备型号'
            Width = 80
          end
          item
            Caption = '设备类型'
            Width = 80
          end
          item
            Caption = '中心商户号'
            Width = 80
          end
          item
            Caption = '省商户号'
            Width = 80
          end
          item
            Caption = '商户类型'
            Width = 80
          end>
        FlatScrollBars = True
        GridLines = True
        RowSelect = True
        TabOrder = 1
        ViewStyle = vsReport
      end
      object pnlAllot: TPanel
        Left = 0
        Top = 8
        Width = 514
        Height = 25
        Align = alTop
        BevelOuter = bvNone
        Caption = '商户已分配设备'
        Font.Charset = GB2312_CHARSET
        Font.Color = clNavy
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object lblShowAllot: TRzURLLabel
          Left = 8
          Top = 7
          Width = 84
          Height = 13
          AutoSize = False
          Caption = '显示已分配设备'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clHighlight
          Font.Height = -11
          Font.Name = 'Verdana'
          Font.Style = [fsUnderline]
          ParentFont = False
          OnClick = lblShowAllotClick
          Rotation = roFlat
        end
      end
    end
    object Panel1: TPanel
      Left = 0
      Top = 0
      Width = 514
      Height = 85
      Align = alTop
      ParentColor = True
      TabOrder = 3
      object Label2: TLabel
        Left = 18
        Top = 10
        Width = 48
        Height = 12
        Caption = '设备编号'
      end
      object Label4: TLabel
        Left = 346
        Top = 10
        Width = 60
        Height = 12
        Caption = '设备终端号'
      end
      object Label5: TLabel
        Left = 6
        Top = 34
        Width = 60
        Height = 12
        Caption = '终端序列号'
      end
      object Label6: TLabel
        Left = 178
        Top = 34
        Width = 48
        Height = 12
        Caption = '设备型号'
      end
      object Label7: TLabel
        Left = 358
        Top = 34
        Width = 48
        Height = 12
        Caption = '设备类型'
      end
      object Label8: TLabel
        Left = 178
        Top = 10
        Width = 48
        Height = 12
        Caption = '设备名称'
      end
      object Label10: TLabel
        Left = 18
        Top = 58
        Width = 48
        Height = 12
        Caption = '设备状态'
      end
      object lblDev: TLabel
        Left = 181
        Top = 60
        Width = 236
        Height = 12
        AutoSize = False
        Caption = 'lblBusi'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object WVEdit4: TWVEdit
        Left = 409
        Top = 6
        Width = 106
        Height = 20
        ReadOnly = False
        TabOrder = 2
        Text = '<查询.设备终端号>'
        WorkView = WorkView1
        FieldName = '查询.设备终端号'
      end
      object WVEdit5: TWVEdit
        Left = 68
        Top = 30
        Width = 104
        Height = 20
        ReadOnly = False
        TabOrder = 3
        Text = '<查询.终端序列号>'
        WorkView = WorkView1
        FieldName = '查询.终端序列号'
      end
      object WVEdit8: TWVEdit
        Left = 228
        Top = 6
        Width = 116
        Height = 20
        ReadOnly = False
        TabOrder = 1
        Text = '<查询.设备名称>'
        WorkView = WorkView1
        FieldName = '查询.设备名称'
      end
      object WVComboBox3: TWVComboBox
        Left = 228
        Top = 30
        Width = 116
        Height = 20
        Style = csDropDownList
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 4
        WorkView = WorkView1
        FieldName = '查询.设备型号'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*223'
      end
      object WVComboBox1: TWVComboBox
        Left = 68
        Top = 54
        Width = 104
        Height = 20
        Style = csDropDownList
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 6
        WorkView = WorkView1
        FieldName = '查询.设备状态'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*220'
      end
      object WVComboBox2: TWVComboBox
        Left = 409
        Top = 30
        Width = 106
        Height = 20
        Style = csDropDownList
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 5
        WorkView = WorkView1
        FieldName = '查询.设备类型'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*221'
      end
      object edtPosIdQ: TWVEdit
        Left = 68
        Top = 6
        Width = 104
        Height = 20
        ReadOnly = False
        TabOrder = 0
        Text = '<查询.设备编号>'
        WorkView = WorkView1
        FieldName = '查询.设备编号'
      end
      object btnDevQ: TBitBtn
        Left = 436
        Top = 54
        Width = 79
        Height = 25
        Hint = '分配'
        Caption = '设备查询'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 7
        OnClick = btnDevQClick
      end
    end
  end
  object RzSizePanel1: TRzSizePanel [3]
    Left = 0
    Top = 18
    Width = 524
    Height = 438
    HotSpotVisible = True
    SizeBarWidth = 7
    TabOrder = 0
    UseGradients = True
    object Panel2: TPanel
      Left = 0
      Top = 0
      Width = 516
      Height = 87
      Align = alTop
      ParentColor = True
      TabOrder = 0
      object Label3: TLabel
        Left = 22
        Top = 10
        Width = 84
        Height = 12
        Caption = '设备终端序列号'
      end
      object Label1: TLabel
        Left = 10
        Top = 34
        Width = 96
        Height = 12
        Caption = '省设备终端序列号'
      end
      object Label9: TLabel
        Left = 282
        Top = 10
        Width = 48
        Height = 12
        Caption = '设备类型'
      end
      object Label11: TLabel
        Left = 306
        Top = 34
        Width = 24
        Height = 12
        Caption = '状态'
      end
      object btnBusiQ: TBitBtn
        Left = 401
        Top = 54
        Width = 79
        Height = 25
        Hint = '分配'
        Caption = '商户查询'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = btnBusiQClick
      end
      object WVEdit1: TWVEdit
        Left = 116
        Top = 30
        Width = 133
        Height = 20
        Color = clBtnHighlight
        ReadOnly = False
        TabOrder = 1
        Text = '<查询.省设备终端序列号>'
        WorkView = WorkView3
        FieldName = '查询.省设备终端序列号'
      end
      object WVEdit3: TWVEdit
        Left = 116
        Top = 6
        Width = 133
        Height = 20
        Color = clBtnHighlight
        ReadOnly = False
        TabOrder = 2
        Text = '<查询.设备终端序列号>'
        WorkView = WorkView3
        FieldName = '查询.设备终端序列号'
      end
      object WVComboBox4: TWVComboBox
        Left = 340
        Top = 27
        Width = 141
        Height = 20
        Style = csDropDownList
        Color = clBtnHighlight
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView3
        FieldName = '查询.状态'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*239'
      end
      object WVComboBox5: TWVComboBox
        Left = 340
        Top = 3
        Width = 141
        Height = 20
        Style = csDropDownList
        Color = clBtnHighlight
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 4
        WorkView = WorkView3
        FieldName = '查询.设备类型'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*221'
      end
    end
    object lvBusi: TRzListView
      Left = 0
      Top = 87
      Width = 516
      Height = 351
      Align = alClient
      Columns = <
        item
          Caption = '商户编号'
          Width = 70
        end
        item
          Caption = '商户名称'
          Width = 120
        end
        item
          Caption = '设备终端序列号'
          Width = 100
        end
        item
          Caption = '设备类型'
          Width = 100
        end
        item
          Caption = '状态'
          Width = 100
        end
        item
          Caption = '绑定设备编号'
          Width = 5
        end>
      FlatScrollBars = True
      GridLines = True
      RowSelect = True
      TabOrder = 1
      ViewStyle = vsReport
      OnClick = lvBusiClick
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
        Name = '设备编号'
        Caption = '设备编号'
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
        Name = '操作类型'
        Caption = '操作类型'
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
        Name = '序列号'
        Caption = '序列号'
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
          '|设备名称|三九设备注册号|设备物纜机号|机型代码|上级设备物纜设备' +
          '状态|设备物理型号|所属子系统|设备所在区域|负责人员工号|'
      end>
    Left = 76
    Top = 295
  end
  inherited MainRequest: TWVRequest
    ID = '设备商户绑定'
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
        ParamName = '商户编号'
        FieldName = '商户号'
        DefaultValue = 0
      end
      item
        ParamName = '设备编号'
        FieldName = '设备编号'
      end
      item
        ParamName = '操作类型'
        FieldName = '操作类型'
      end
      item
        ParamName = '序列号'
        FieldName = '序列号'
      end>
    Left = 112
    Top = 296
  end
  inherited WVDBBinder: TWVDBBinder
    WorkView = nil
    FieldName = '查询结果集'
    Left = 144
    Top = 336
  end
  inherited DataSource: TDataSource
    Left = 192
    Top = 336
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = 'POS信息维护查询'
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
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '设备编号'
        FieldName = '查询.设备编号'
      end
      item
        ParamName = '所属商户号'
        FieldName = '查询.所属商户号'
      end
      item
        ParamName = '设备终端号'
        FieldName = '查询.设备终端号'
      end
      item
        ParamName = '终端序列号'
        FieldName = '查询.终端序列号'
      end
      item
        ParamName = '设备型号'
        FieldName = '查询.设备型号'
      end
      item
        ParamName = '设备类型'
        FieldName = '查询.设备类型'
      end
      item
        ParamName = '设备名称'
        FieldName = '查询.设备名称'
      end
      item
        ParamName = '用途'
        FieldName = '查询.用途'
      end
      item
        ParamName = '设备状态'
        FieldName = '查询.设备状态'
      end>
    Left = 112
    Top = 376
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
        Name = '查询.设备编号'
        Caption = '查询.设备编号'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.所属商户号'
        Caption = '查询.所属商户号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.设备终端号'
        Caption = '查询.设备终端号'
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
        Name = '查询.终端序列号'
        Caption = '查询.终端序列号'
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
        Name = '查询.设备型号'
        Caption = '查询.设备型号'
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
      end
      item
        Name = '查询.设备类型'
        Caption = '查询.设备类型'
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
        Name = '查询.设备名称'
        Caption = '查询.设备名称'
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
        Name = '查询.用途'
        Caption = '查询.用途'
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
      end
      item
        Name = '查询.设备状态'
        Caption = '查询.设备状态'
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
        Name = '操作标志'
        Caption = '操作标志'
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
        DataField = 'sstat_type'
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    InvalidColor = clWindow
    Left = 80
    Top = 376
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
        Name = '商户号'
        Caption = '商户号'
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
        Name = '设备编号'
        Caption = '设备编号'
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
        MonitorValueChangedFields = 
          '|设备名称|三九设备注册号|设备物纜机号|机型代码|上级设备物纜设备' +
          '状态|设备物理型号|所属子系统|设备所在区域|负责人员工号|'
      end>
    Left = 76
    Top = 407
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '设备商户查询'
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
        ParamName = '商户编号'
        FieldName = '商户号'
      end
      item
        ParamName = '设备编号'
        FieldName = '设备编号'
      end>
    AfterExec = MainRequestAfterExec
    Left = 112
    Top = 408
  end
  object QueryRequest: TWVRequest
    WorkView = WorkView3
    ID = '商户设备管理查询'
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
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '商户号'
        FieldName = '查询.商户号'
        DefaultValue = 0
      end
      item
        ParamName = '设备终端序列号'
        FieldName = '查询.设备终端序列号'
      end
      item
        ParamName = '省设备终端序列号'
        FieldName = '查询.省设备终端序列号'
      end
      item
        ParamName = '设备类型'
        FieldName = '查询.设备类型'
      end
      item
        ParamName = '状态'
        FieldName = '查询.状态'
      end
      item
        ParamName = '注册日期'
        FieldName = '查询.注册日期'
      end
      item
        ParamName = '启用日期'
        FieldName = '查询.启用日期'
      end
      item
        ParamName = '停用日期'
        FieldName = '查询.停用日期'
      end>
    Left = 112
    Top = 336
  end
  object WorkView3: TWorkView
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
        Name = '操作标志'
        Caption = '操作标志'
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
        Name = '查询.商户号'
        Caption = '查询.商户号'
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
      end
      item
        Name = '查询.设备终端序列号'
        Caption = '查询.设备终端序列号'
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
        Name = '查询.省设备终端序列号'
        Caption = '查询.省设备终端序列号'
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
        Name = '查询.设备类型'
        Caption = '查询.设备类型'
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
        Name = '查询.状态'
        Caption = '查询.状态'
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
        Name = '查询.注册日期'
        Caption = '查询.注册日期'
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
        Name = '查询.启用日期'
        Caption = '查询.启用日期'
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
        Name = '查询.停用日期'
        Caption = '查询.停用日期'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.操作标志|查询.商户号|查询.设备终端序列号|查询.省设备终端序' +
          '列号|查询.设备类型|查询.状态|查询.注册日期|查询.启用日期|查询.停' +
          '用日期|'
      end
      item
        MonitorValueChangedFields = 
          '|商户号|商户名称|设备终端序列号|蕓设备类型|状态|注册日期|启用日' +
          '期|停用日期|绑定设备编号|备注|'
      end>
    InvalidColor = clBtnHighlight
    Left = 72
    Top = 336
  end
end
