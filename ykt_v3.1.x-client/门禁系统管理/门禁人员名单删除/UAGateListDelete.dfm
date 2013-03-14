inherited faqhGateListDelete: TfaqhGateListDelete
  Width = 880
  Height = 578
  inherited UIPanel1: TUIPanel
    Top = 542
    Width = 880
    Height = 36
    TabOrder = 5
    object Label14: TLabel [0]
      Left = 70
      Top = 14
      Width = 60
      Height = 12
      Caption = '表单名称：'
    end
    inherited btnQuery: TBitBtn
      Left = 709
      Top = 6
      Enabled = False
      TabOrder = 4
    end
    inherited btnPrint: TBitBtn
      Left = 246
      Top = 1000
      TabOrder = 9
      Visible = False
    end
    object btnDelete: TBitBtn
      Left = 791
      Top = 6
      Width = 79
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '删除(&D)'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = btnDeleteClick
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF00FFFF
        FF000000FF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF000000FF0000FFFF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF000000FF000000FF000000FF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF000000FF000000FF0000007B00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF0000007B00FFFFFF00FFFF
        FF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF0000007B000000
        FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF000000
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF0000007B000000
        FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF0000007B00FFFFFF00FFFF
        FF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF000000FF000000FF000000FF0000007B00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF000000FF0000FFFF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF000000FF0000007B00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF007B7B7B000000FF007B7B7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
    end
    object chkCustUnAllot: TRzCheckBox
      Left = 13
      Top = 12
      Width = 57
      Height = 17
      Caption = '全选'
      FrameColor = 8409372
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      HighlightColor = 2203937
      HotTrack = True
      HotTrackColor = 3983359
      HotTrackColorType = htctActual
      ParentFont = False
      State = cbUnchecked
      TabOrder = 8
      OnClick = chkCustUnAllotClick
    end
    object btnInfo: TBitBtn
      Left = 631
      Top = 6
      Width = 75
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '删除信息'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnInfoClick
    end
    object edtTable: TWVEdit
      Left = 132
      Top = 9
      Width = 85
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 7
      Text = 'sheet1'
    end
    object btnOpen: TBitBtn
      Left = 227
      Top = 6
      Width = 75
      Height = 25
      Hint = '打开Excel文档'
      Caption = '打开Excel'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnOpenClick
    end
    object btnIMPQuery: TBitBtn
      Left = 307
      Top = 6
      Width = 75
      Height = 25
      Hint = '查询/刷新数据'
      Caption = '&Q 查询'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnIMPQueryClick
    end
    object btnCloseConn: TBitBtn
      Left = 386
      Top = 6
      Width = 75
      Height = 25
      Hint = '断开连接'
      Caption = '断开连接'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnPrintClick
    end
    object btnDelList: TBitBtn
      Left = 550
      Top = 7
      Width = 75
      Height = 25
      Hint = '断开连接'
      Anchors = [akTop, akRight]
      Caption = '清空列表'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      OnClick = btnDelListClick
    end
    object btnErrInfo: TBitBtn
      Left = 466
      Top = 6
      Width = 75
      Height = 25
      Hint = '断开连接'
      Caption = '失败信息'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 10
      OnClick = btnErrInfoClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 880
    TabOrder = 4
    inherited Image1: TImage
      Width = 880
    end
    inherited LabRecordCount: TLabel
      Visible = False
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 880
    Height = 127
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object Label1: TLabel
      Left = 41
      Top = 9
      Width = 48
      Height = 12
      Caption = '门禁名称'
    end
    object Label4: TLabel
      Left = 66
      Top = 33
      Width = 24
      Height = 12
      Caption = '姓名'
    end
    object Label7: TLabel
      Left = 42
      Top = 57
      Width = 48
      Height = 12
      Caption = '客户类别'
    end
    object Label10: TLabel
      Left = 66
      Top = 81
      Width = 24
      Height = 12
      Caption = '班级'
    end
    object Label11: TLabel
      Left = 266
      Top = 81
      Width = 24
      Height = 12
      Caption = '专业'
    end
    object Label2: TLabel
      Left = 242
      Top = 9
      Width = 48
      Height = 12
      Caption = '门禁编号'
    end
    object Label5: TLabel
      Left = 266
      Top = 33
      Width = 24
      Height = 12
      Caption = '院系'
    end
    object Label8: TLabel
      Left = 242
      Top = 57
      Width = 48
      Height = 12
      Caption = '收费类别'
    end
    object Label12: TLabel
      Left = 490
      Top = 57
      Width = 24
      Height = 12
      Caption = '状态'
    end
    object Label9: TLabel
      Left = 466
      Top = 80
      Width = 48
      Height = 12
      Caption = '名单类型'
    end
    object Label6: TLabel
      Left = 478
      Top = 33
      Width = 36
      Height = 12
      Caption = '客户号'
    end
    object Label3: TLabel
      Left = 470
      Top = 9
      Width = 42
      Height = 12
      Caption = '学/工号'
    end
    object Label13: TLabel
      Left = 42
      Top = 105
      Width = 48
      Height = 12
      Caption = '增删标志'
    end
    object WVEdit1: TWVEdit
      Left = 100
      Top = 5
      Width = 117
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 0
      Text = '<门禁机名称>'
      WorkView = WorkView1
      FieldName = '门禁机名称'
    end
    object WVEdit4: TWVEdit
      Left = 100
      Top = 29
      Width = 117
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 4
      Text = '<姓名>'
      WorkView = WorkView1
      FieldName = '姓名'
    end
    object cbbCustType: TWVComboBox
      Left = 100
      Top = 53
      Width = 117
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView1
      FieldName = '收费类型'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-34'
    end
    object WVEdit10: TWVEdit
      Left = 100
      Top = 77
      Width = 117
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 9
      Text = '<班级>'
      WorkView = WorkView1
      FieldName = '班级'
    end
    object WVComboBox6: TWVComboBox
      Left = 300
      Top = 78
      Width = 141
      Height = 18
      Style = csOwnerDrawFixed
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 11
      WorkView = WorkView1
      FieldName = '专业代码'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '-23'
    end
    object cbbFeeType: TWVComboBox
      Left = 300
      Top = 53
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView1
      FieldName = '收费类型'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-43'
    end
    object cbbDep: TWVComboBox
      Left = 300
      Top = 28
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView1
      FieldName = '院系代码'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object WVEdit2: TWVEdit
      Left = 300
      Top = 5
      Width = 141
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<门禁设备编号>'
      WorkView = WorkView1
      FieldName = '门禁设备编号'
    end
    object WVEdit3: TWVEdit
      Left = 524
      Top = 5
      Width = 139
      Height = 20
      CharCase = ecUpperCase
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<学工号>'
      WorkView = WorkView1
      FieldName = '学工号'
    end
    object WVEdit6: TWVEdit
      Left = 524
      Top = 29
      Width = 139
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 5
      Text = '<客户号>'
      WorkView = WorkView1
      FieldName = '客户号'
    end
    object WVComboBox1: TWVComboBox
      Left = 524
      Top = 77
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 10
      WorkView = WorkView1
      FieldName = '名单类型'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*133'
    end
    object WVComboBox2: TWVComboBox
      Left = 524
      Top = 53
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 8
      WorkView = WorkView1
      FieldName = '状态'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*84'
    end
    object WVComboBox3: TWVComboBox
      Left = 100
      Top = 100
      Width = 117
      Height = 18
      Style = csOwnerDrawFixed
      Color = clWhite
      ItemHeight = 12
      TabOrder = 12
      WorkView = WorkView1
      FieldName = '增删标志'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*44'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 145
    Width = 880
    Height = 397
    inherited Grid: TRzDBGrid
      Align = alNone
      DataSource = nil
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = '门禁设备编号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail2'
          PickList.Strings = ()
          Title.Caption = '门禁机名称'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Caption = '客户号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Caption = '客户类型'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Caption = '收费类型'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Caption = '医院收费方式'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Caption = '学号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail'
          PickList.Strings = ()
          Title.Caption = '姓名'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Caption = '卡状态'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Caption = '批次号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstation0'
          PickList.Strings = ()
          Title.Caption = '院系代码'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstation1'
          PickList.Strings = ()
          Title.Caption = '专业代码'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Caption = '班级'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol7'
          PickList.Strings = ()
          Title.Caption = '状态'
          Visible = True
        end>
    end
  end
  object lv1: TRzListView [4]
    Left = 0
    Top = 145
    Width = 880
    Height = 397
    Align = alClient
    Checkboxes = True
    Columns = <
      item
        Caption = '门禁编号'
        Width = 60
      end
      item
        Caption = '门禁名称'
        Width = 150
      end
      item
        Caption = '客户号'
      end
      item
        Caption = '学/工号'
        Width = 80
      end
      item
        Caption = '姓名'
        Width = 80
      end
      item
        Caption = '状态码'
        Width = 1
      end
      item
        Caption = '状态'
        Width = 60
      end
      item
        Caption = '增删标志码'
        Width = 1
      end
      item
        Caption = '增删标志'
        Width = 60
      end
      item
        Caption = '时间周'
        Width = 60
      end
      item
        Caption = '客户类别'
        Width = 80
      end
      item
        Caption = '收费类别'
        Width = 80
      end
      item
        Caption = '院系'
        Width = 100
      end
      item
        Caption = '专业'
        Width = 57
      end>
    ColumnClick = False
    FlatScrollBars = True
    GridLines = True
    RowSelect = True
    TabOrder = 1
    ViewStyle = vsReport
  end
  object pnl1: TPanel [5]
    Left = 252
    Top = 265
    Width = 437
    Height = 281
    Anchors = [akRight, akBottom]
    BevelOuter = bvNone
    Color = 16184303
    TabOrder = 3
    Visible = False
    object btn1: TSpeedButton
      Left = 376
      Top = 256
      Width = 57
      Height = 22
      Caption = '关 闭'
      Flat = True
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      OnClick = btn1Click
    end
    object SpeedButton1: TSpeedButton
      Left = 300
      Top = 256
      Width = 57
      Height = 22
      Caption = '清空信息'
      Flat = True
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      OnClick = SpeedButton1Click
    end
    object mmo1: TRzMemo
      Left = 0
      Top = 0
      Width = 437
      Height = 249
      Align = alTop
      ScrollBars = ssBoth
      TabOrder = 0
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
        Name = '客户号'
        Caption = '客户号'
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
        Name = '门禁编号'
        Caption = '门禁编号'
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
        Name = '时间周'
        Caption = '时间周'
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
          '|门禁机名称|门禁设备编号|学工号|姓名|院系代码|客户号|客户类型|收' +
          '费类型|医院收费方式|班级|专业代码|状态|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 84
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '门禁人员名单删除'
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
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '门禁编号'
        FieldName = '门禁编号'
      end
      item
        ParamName = '时间周'
        FieldName = '时间周'
        DefaultValue = 0
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
    Left = 192
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
        Name = '门禁机名称'
        Caption = '门禁机名称'
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
        Name = '门禁设备编号'
        Caption = '门禁设备编号'
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
        Name = '学工号'
        Caption = '学工号'
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
        Name = '姓名'
        Caption = '姓名'
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
        Name = '院系代码'
        Caption = '院系代码'
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
        Name = '客户号'
        Caption = '客户号'
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
        Name = '客户类型'
        Caption = '客户类型'
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
        Name = '收费类型'
        Caption = '收费类型'
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
        Name = '名单类型'
        Caption = '名单类型'
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
        Name = '班级'
        Caption = '班级'
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
        Name = '专业代码'
        Caption = '专业代码'
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
        Name = '状态'
        Caption = '状态'
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
        Name = '操作员'
        Caption = '操作员'
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
        Name = '批次号'
        Caption = '批次号'
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
        Name = '增删标志'
        Caption = '增删标志'
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
        MonitorValueChangedFields = 
          '|门禁机名称|门禁设备编号|学工号|姓名|院系代码|客户号|客户类型|收' +
          '费类型|医院收费方式|班级|专业代码|状态|'
      end>
    Left = 84
    Top = 295
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '门禁人员名单查询'
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
        ParamName = '门禁机名称'
        FieldName = '门禁机名称'
      end
      item
        ParamName = '门禁设备编号'
        FieldName = '门禁设备编号'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '姓名'
        FieldName = '姓名'
      end
      item
        ParamName = '院系代码'
        FieldName = '院系代码'
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '客户类型'
        FieldName = '客户类型'
      end
      item
        ParamName = '收费类型'
        FieldName = '收费类型'
      end
      item
        ParamName = '名单类型'
        FieldName = '名单类型'
      end
      item
        ParamName = '班级'
        FieldName = '班级'
      end
      item
        ParamName = '专业代码'
        FieldName = '专业代码'
      end
      item
        ParamName = '状态'
        FieldName = '状态'
      end
      item
        ParamName = '操作员'
        FieldName = '操作员'
      end
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end
      item
        ParamName = '增删标志'
        FieldName = '增删标志'
      end>
    AfterExec = MainRequestAfterExec
    Left = 120
    Top = 296
  end
  object conSource: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\Documents and Se' +
      'ttings\Administrator\桌面\新建 Microsoft Office Access 应用程序.' +
      'mdb;Persist Security Info=False'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 88
    Top = 336
  end
  object qrySource: TADOQuery
    Connection = conSource
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from sheet1')
    Left = 128
    Top = 336
  end
  object dlgOpen: TOpenDialog
    Left = 216
    Top = 336
  end
end
