inherited faqhDevBusiAllot: TfaqhDevBusiAllot
  Width = 847
  Height = 489
  inherited UIPnlQueryCount: TUIPanel [0]
    Width = 847
    TabOrder = 2
    inherited Image1: TImage
      Width = 847
    end
    inherited LabRecordCount: TLabel
      Font.Color = clBlack
    end
  end
  inherited UIPanel1: TUIPanel [1]
    Top = 424
    Width = 847
    Height = 65
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 494
      Top = 35
      Caption = '设备查询'
      Enabled = False
      TabOrder = 1
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 285
      Top = 200
      TabOrder = 5
    end
    object btnAdd: TBitBtn
      Left = 582
      Top = 35
      Width = 79
      Height = 25
      Hint = '分配'
      Anchors = [akTop, akRight]
      Caption = '分  配'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnAddClick
    end
    object btnDel: TBitBtn
      Left = 758
      Top = 35
      Width = 79
      Height = 25
      Hint = '删除'
      Anchors = [akTop, akRight]
      Caption = '删  除'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btnDelClick
    end
    object btnChange: TBitBtn
      Left = 670
      Top = 35
      Width = 79
      Height = 25
      Hint = '修改'
      Anchors = [akTop, akRight]
      Caption = '修  改'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnChangeClick
    end
    object grp1: TGroupBox
      Left = 0
      Top = 0
      Width = 385
      Height = 65
      Align = alLeft
      TabOrder = 0
      object lblBusiName: TLabel
        Left = 12
        Top = 18
        Width = 189
        Height = 14
        AutoSize = False
        Caption = '商户名称'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label12: TLabel
        Left = 12
        Top = 42
        Width = 72
        Height = 12
        Caption = '设备启用日期'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label11: TLabel
        Left = 204
        Top = 43
        Width = 72
        Height = 12
        Caption = '设备停用日期'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label7: TLabel
        Left = 204
        Top = 20
        Width = 72
        Height = 12
        Caption = '使用结束时间'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object edtStartDate: TWVEdit
        Left = 92
        Top = 38
        Width = 85
        Height = 20
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 8
        ParentFont = False
        ReadOnly = False
        TabOrder = 1
        Text = '<启用日期>'
        WorkView = WorkView1
        FieldName = '启用日期'
        SynchronizeWhenExit = True
      end
      object edtEndTime: TWVEdit
        Left = 284
        Top = 13
        Width = 85
        Height = 20
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 6
        ParentFont = False
        ReadOnly = False
        TabOrder = 0
        Text = '<使用结束时间>'
        WorkView = WorkView1
        FieldName = '使用结束时间'
        SynchronizeWhenExit = True
      end
      object edtStopDate: TWVEdit
        Left = 284
        Top = 38
        Width = 85
        Height = 20
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 8
        ParentFont = False
        ReadOnly = False
        TabOrder = 2
        Text = '<停用日期>'
        WorkView = WorkView1
        FieldName = '停用日期'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 267
    Width = 580
    Height = 406
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Left = 96
      Top = 240
      Width = 270
      Height = 142
      Align = alNone
      DataSource = nil
      TabOrder = 3
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
    object Panel1: TPanel
      Left = 0
      Top = 0
      Width = 580
      Height = 108
      Align = alTop
      BevelOuter = bvNone
      Color = 16119543
      TabOrder = 0
      object Label1: TLabel
        Left = 18
        Top = 9
        Width = 48
        Height = 12
        Caption = '设备名称'
      end
      object Label3: TLabel
        Left = 376
        Top = 9
        Width = 60
        Height = 12
        Caption = '设备物理ID'
      end
      object Label4: TLabel
        Left = 42
        Top = 35
        Width = 24
        Height = 12
        Caption = '机号'
      end
      object Label5: TLabel
        Left = 194
        Top = 11
        Width = 48
        Height = 12
        Caption = '设备机型'
      end
      object Label6: TLabel
        Left = 352
        Top = 35
        Width = 84
        Height = 12
        Caption = '上级设备物理ID'
      end
      object Label8: TLabel
        Left = 194
        Top = 35
        Width = 48
        Height = 12
        Caption = '设备类型'
      end
      object Label9: TLabel
        Left = 6
        Top = 62
        Width = 60
        Height = 12
        Caption = '所属子系统'
      end
      object Label10: TLabel
        Left = 194
        Top = 61
        Width = 48
        Height = 12
        Caption = '所在区域'
      end
      object Label2: TLabel
        Left = 376
        Top = 61
        Width = 60
        Height = 12
        Caption = '导入批次号'
      end
      object Label13: TLabel
        Left = 18
        Top = 87
        Width = 48
        Height = 12
        Caption = '设备标识'
      end
      object WVEdit1: TWVEdit
        Left = 68
        Top = 5
        Width = 112
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 0
        Text = '<设备名称>'
        WorkView = WorkView
        FieldName = '设备名称'
      end
      object WVEdit3: TWVEdit
        Left = 444
        Top = 5
        Width = 100
        Height = 20
        CharCase = ecUpperCase
        Color = clWhite
        ReadOnly = False
        TabOrder = 2
        Text = '<设备物理ID>'
        WorkView = WorkView
        FieldName = '设备物理ID'
      end
      object WVEdit6: TWVEdit
        Left = 444
        Top = 31
        Width = 100
        Height = 20
        CharCase = ecUpperCase
        Color = clWhite
        ReadOnly = False
        TabOrder = 4
        Text = '<上级设备物理ID>'
        WorkView = WorkView
        FieldName = '上级设备物理ID'
      end
      object WVComboBox2: TWVComboBox
        Left = 244
        Top = 57
        Width = 105
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 6
        WorkView = WorkView
        FieldName = '设备所在区域'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-28'
      end
      object WVComboBox3: TWVComboBox
        Left = 68
        Top = 58
        Width = 112
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 8
        WorkView = WorkView
        FieldName = '所属子系统'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-32'
      end
      object WVComboBox5: TWVComboBox
        Left = 244
        Top = 31
        Width = 105
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView
        FieldName = '设备物理型号'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-35'
      end
      object WVComboBox6: TWVComboBox
        Left = 244
        Top = 5
        Width = 105
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 1
        WorkView = WorkView
        FieldName = '机型代码'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*47'
      end
      object edtMachineNo: TWVEdit
        Left = 68
        Top = 32
        Width = 112
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 5
        Text = '<机号>'
        WorkView = WorkView
        FieldName = '机号'
      end
      object WVEdit2: TWVEdit
        Left = 444
        Top = 57
        Width = 100
        Height = 20
        CharCase = ecUpperCase
        Color = clWhite
        ReadOnly = False
        TabOrder = 7
        Text = '<导入批次号>'
        WorkView = WorkView
        FieldName = '导入批次号'
      end
      object WVEdit4: TWVEdit
        Left = 68
        Top = 84
        Width = 112
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 9
        Text = '<设备标识>'
        WorkView = WorkView
        FieldName = '设备标识'
      end
    end
    object lvDev: TRzListView
      Left = 0
      Top = 108
      Width = 580
      Height = 101
      Align = alClient
      Checkboxes = True
      Columns = <
        item
          Caption = '所在区域'
          Width = 100
        end
        item
          Caption = '设备标识'
          Width = 70
        end
        item
          Caption = '设备名称'
          Width = 120
        end
        item
          Caption = '设备物理ID'
          Width = 80
        end
        item
          Caption = '机型代码'
          Width = 100
        end
        item
          Caption = '所属子系统'
          Width = 100
        end
        item
          Caption = '设备用途'
          Width = 23
        end>
      FlatScrollBars = True
      GridLines = True
      RowSelect = True
      TabOrder = 1
      ViewStyle = vsReport
    end
    object rzszpnl1: TRzSizePanel
      Left = 0
      Top = 209
      Width = 580
      Height = 197
      Align = alBottom
      HotSpotVisible = True
      SizeBarWidth = 7
      TabOrder = 2
      UseGradients = True
      object lvAllotDev: TRzListView
        Left = 0
        Top = 33
        Width = 580
        Height = 164
        Align = alClient
        Checkboxes = True
        Columns = <
          item
            Width = 25
          end
          item
            Caption = '编号'
            Width = 70
          end
          item
            Caption = '设备名称'
            Width = 120
          end
          item
            Caption = '商户名称'
            Width = 100
          end
          item
            Caption = '使用开始时间'
            Width = 100
          end
          item
            Caption = '使用结束时间'
            Width = 100
          end
          item
            Caption = '设备启用日期'
            Width = 100
          end
          item
            Caption = '设备停用日期'
            Width = 100
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
        Width = 580
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
  end
  object RzSizePanel1: TRzSizePanel [3]
    Left = 0
    Top = 18
    Width = 267
    Height = 406
    HotSpotVisible = True
    SizeBarWidth = 7
    TabOrder = 0
    UseGradients = True
    object tvBusiness: TRzTreeView
      Left = 0
      Top = 0
      Width = 259
      Height = 406
      SelectionPen.Color = clBtnShadow
      Align = alClient
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      Indent = 19
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      OnClick = tvBusinessClick
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
        Name = '设备名称'
        Caption = '设备名称'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scert_no'
      end
      item
        Name = '三九设备注册号'
        Caption = '三九设备注册号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_pwd'
      end
      item
        Name = '设备物理ID'
        Caption = '设备物理ID'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'sbank_pwd2'
      end
      item
        Name = '机号'
        Caption = '机号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '机型代码'
        Caption = '机型代码'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_code'
      end
      item
        Name = '上级设备物理ID'
        Caption = '上级设备物理ID'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'sdate1'
      end
      item
        Name = '设备状态'
        Caption = '设备状态'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol4'
      end
      item
        Name = '设备物理型号'
        Caption = '设备物理型号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lbank_acc_type'
      end
      item
        Name = '所属子系统'
        Caption = '所属子系统'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial0'
      end
      item
        Name = '设备所在区域'
        Caption = '设备所在区域'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial1'
      end
      item
        Name = '导入批次号'
        Caption = '导入批次号'
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
        Name = '设备标识'
        Caption = '设备标识'
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
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 84
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '设备非关键字查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '设备名称'
        FieldName = '设备名称'
      end
      item
        ParamName = '三九设备注册号'
        FieldName = '三九设备注册号'
      end
      item
        ParamName = '设备物理ID'
        FieldName = '设备物理ID'
      end
      item
        ParamName = '机号'
        FieldName = '机号'
      end
      item
        ParamName = '机型代码'
        FieldName = '机型代码'
      end
      item
        ParamName = '上级设备物理ID'
        FieldName = '上级设备物理ID'
      end
      item
        ParamName = '设备状态'
        FieldName = '设备状态'
      end
      item
        ParamName = '设备物理型号'
        FieldName = '设备物理型号'
      end
      item
        ParamName = '所属子系统'
        FieldName = '所属子系统'
      end
      item
        ParamName = '设备所在区域'
        FieldName = '设备所在区域'
      end
      item
        ParamName = '导入批次号'
        FieldName = '导入批次号'
      end
      item
        ParamName = '设备标识'
        FieldName = '设备标识'
      end>
    Left = 120
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 160
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 208
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
        GroupIndex = 1
      end
      item
        Name = '编号'
        Caption = '编号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '设备标识'
        Caption = '设备标识'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '商户标识'
        Caption = '商户标识'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol3'
      end
      item
        Name = '使用结束时间'
        Caption = '使用结束时间'
        FieldType = wftUndefined
        DomainName = '时间格式'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 6
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'stime2'
      end
      item
        Name = '启用日期'
        Caption = '启用日期'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sdate1'
      end
      item
        Name = '停用日期'
        Caption = '停用日期'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sdate2'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|查询.设备商户标识|'
      end
      item
        MonitorValueChangedFields = 
          '|编号|前端机标识|商户标识|使用开始日期|使用开始时间|使用结束时间' +
          '|使用结束日期|'
      end>
    Left = 80
    Top = 296
  end
  object AddRequest: TWVRequest
    WorkView = WorkView1
    ID = '设备商户信息设置'
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
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '编号'
        FieldName = '编号'
      end
      item
        ParamName = '商户标识'
        FieldName = '商户标识'
      end
      item
        ParamName = '设备标识'
        FieldName = '设备标识'
      end
      item
        ParamName = '使用结束时间'
        FieldName = '使用结束时间'
      end
      item
        ParamName = '启用日期'
        FieldName = '启用日期'
      end
      item
        ParamName = '停用日期'
        FieldName = '停用日期'
      end>
    Left = 112
    Top = 296
  end
  object QueryRequest2: TWVRequest
    WorkView = WorkView2
    ID = '商户信息主键查询2'
    Bindings = <
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '商户标识'
        FieldName = '商户标识'
      end>
    Left = 112
    Top = 336
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
        Name = '商户标识'
        Caption = '商户标识'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|商户标识|'
      end>
    Left = 76
    Top = 335
  end
  object WorkView3: TWorkView
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
        Name = '设备标识'
        Caption = '设备标识'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '使用开始日期'
        Caption = '使用开始日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '使用结束日期'
        Caption = '使用结束日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '商户名称'
        Caption = '商户名称'
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
        Name = '使用状态'
        Caption = '使用状态'
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
        Name = '使用结束时间'
        Caption = '使用结束时间'
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
        Name = '商户编号'
        Caption = '商户编号'
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
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|'
      end>
    Left = 84
    Top = 207
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView3
    ID = '设备商户信息非主键查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '使用开始日期'
        FieldName = '使用开始日期'
      end
      item
        ParamName = '设备标识'
        FieldName = '设备标识'
      end
      item
        ParamName = '使用结束日期'
        FieldName = '使用结束日期'
      end
      item
        ParamName = '使用结束时间'
        FieldName = '使用结束时间'
      end
      item
        ParamName = '使用状态'
        FieldName = '使用状态'
      end
      item
        ParamName = '商户名称'
        FieldName = '商户名称'
      end
      item
        ParamName = '商户编号'
        FieldName = '商户编号'
      end>
    AfterExec = MainRequestAfterExec
    Left = 120
    Top = 208
  end
end
