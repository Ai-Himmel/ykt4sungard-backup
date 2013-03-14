inherited faqhsetGateGroupForGate: TfaqhsetGateGroupForGate
  Width = 783
  Height = 558
  Caption = '门禁组门禁机设置'
  inherited pcPages: TRzPageControl
    Width = 783
    Height = 558
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 499
        Width = 779
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 605
          Top = 6
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 285
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 520
          Top = 6
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = 690
          Top = 6
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 206
          Visible = False
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 8
          Top = 11
          Width = 169
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 779
        Align = alNone
        TabOrder = 1
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 779
        Height = 466
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '门禁组编号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Caption = '门禁机编号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '门禁组名'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '门禁机名'
            Width = 200
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 779
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label1: TLabel
          Left = 30
          Top = 10
          Width = 60
          Height = 12
          Caption = '门禁组编号'
        end
        object cbbType: TWVComboBox
          Left = 93
          Top = 6
          Width = 228
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '查询.门禁组编号'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-46'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      inherited UIPanel2: TUIPanel
        Top = 499
        Width = 779
        TabOrder = 3
        inherited btnOK: TBitBtn
          Left = 607
          TabOrder = 2
        end
        inherited btnCancel: TBitBtn
          Left = 695
          TabOrder = 3
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
          Visible = False
        end
        object chkSelectAll: TRzCheckBox
          Left = 216
          Top = 8
          Width = 57
          Height = 17
          Caption = '全选'
          FrameColor = 8409372
          HighlightColor = 2203937
          HotTrack = True
          HotTrackColor = 3983359
          HotTrackColorType = htctActual
          State = cbUnchecked
          TabOrder = 1
          OnClick = chkSelectAllClick
        end
      end
      object pnl1: TPanel
        Left = 0
        Top = 0
        Width = 779
        Height = 25
        Align = alTop
        BevelOuter = bvNone
        Color = 16119543
        TabOrder = 0
        object Label8: TLabel
          Left = 18
          Top = 5
          Width = 112
          Height = 16
          Caption = '门禁机分组设置'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = '黑体'
          Font.Style = []
          ParentFont = False
        end
      end
      object rzszpnl1: TRzSizePanel
        Left = 0
        Top = 25
        Width = 209
        Height = 474
        Color = 16119543
        HotSpotVisible = True
        SizeBarWidth = 7
        TabOrder = 1
        UseGradients = True
        object lst1: TRzCheckList
          Left = 0
          Top = 0
          Width = 201
          Height = 474
          Align = alClient
          ItemHeight = 17
          TabOrder = 0
        end
      end
      object pnl2: TPanel
        Left = 209
        Top = 25
        Width = 570
        Height = 474
        Align = alClient
        BevelOuter = bvNone
        Color = 16119543
        TabOrder = 2
        object pnl3: TPanel
          Left = 0
          Top = 0
          Width = 570
          Height = 89
          Align = alTop
          BevelOuter = bvNone
          Color = 16119543
          TabOrder = 0
          object Label2: TLabel
            Left = 2
            Top = 9
            Width = 48
            Height = 12
            Caption = '设备名称'
          end
          object Label3: TLabel
            Left = 226
            Top = 67
            Width = 48
            Height = 12
            Caption = '设备状态'
            Visible = False
          end
          object Label9: TLabel
            Left = 14
            Top = 35
            Width = 36
            Height = 12
            Caption = '子系统'
          end
          object Label5: TLabel
            Left = 170
            Top = 9
            Width = 72
            Height = 12
            Caption = '设备物理型号'
          end
          object Label6: TLabel
            Left = 2
            Top = 61
            Width = 48
            Height = 12
            Caption = '设备机型'
          end
          object Label10: TLabel
            Left = 170
            Top = 35
            Width = 72
            Height = 12
            Caption = '设备所在区域'
          end
          object Label11: TLabel
            Left = 400
            Top = 9
            Width = 60
            Height = 12
            Caption = '设备物理ID'
          end
          object Label12: TLabel
            Left = 377
            Top = 35
            Width = 84
            Height = 12
            Caption = '上级设备物理ID'
          end
          object WVEdit1: TWVEdit
            Left = 52
            Top = 5
            Width = 112
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 0
            Text = '<设备名称>'
            WorkView = WorkView2
            FieldName = '设备名称'
          end
          object WVComboBox1: TWVComboBox
            Left = 276
            Top = 63
            Width = 112
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 8
            Visible = False
            WorkView = WorkView2
            FieldName = '设备状态'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*5'
          end
          object cbbScode: TWVComboBox
            Left = 52
            Top = 57
            Width = 113
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 7
            WorkView = WorkView2
            FieldName = '机型代码'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*47'
          end
          object WVComboBox5: TWVComboBox
            Left = 244
            Top = 5
            Width = 132
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 1
            WorkView = WorkView2
            FieldName = '设备物理型号'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-35'
          end
          object WVComboBox3: TWVComboBox
            Left = 52
            Top = 31
            Width = 112
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 3
            WorkView = WorkView2
            FieldName = '所属子系统'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-32'
          end
          object WVComboBox2: TWVComboBox
            Left = 244
            Top = 31
            Width = 132
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 4
            WorkView = WorkView2
            FieldName = '设备所在区域'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-28'
          end
          object WVEdit3: TWVEdit
            Left = 462
            Top = 5
            Width = 100
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 2
            Text = '<设备物理ID>'
            WorkView = WorkView2
            FieldName = '设备物理ID'
          end
          object WVEdit6: TWVEdit
            Left = 462
            Top = 31
            Width = 100
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 5
            Text = '<上级设备物理ID>'
            WorkView = WorkView2
            FieldName = '上级设备物理ID'
          end
          object btnEquQuery: TBitBtn
            Left = 487
            Top = 56
            Width = 75
            Height = 25
            Hint = '确认操作'
            Caption = '设备查询'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            TabOrder = 6
            OnClick = btnEquQueryClick
          end
        end
        object lvGate: TRzListView
          Left = 0
          Top = 89
          Width = 570
          Height = 385
          Align = alClient
          Checkboxes = True
          Columns = <
            item
              Caption = '门禁机编号'
              Width = 80
            end
            item
              Caption = '门禁机名称'
              Width = 150
            end
            item
              Caption = '设备编号'
              Width = 60
            end
            item
              Caption = '所属子系统'
              Width = 90
            end
            item
              Caption = '所在区域'
              Width = 169
            end>
          ColumnClick = False
          GridLines = True
          MultiSelect = True
          ReadOnly = True
          RowSelect = True
          SortType = stBoth
          TabOrder = 1
          ViewStyle = vsReport
          OnCustomDrawItem = lvGateCustomDrawItem
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 100
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Features.Strings = ()
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
        Features.Strings = ()
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
        Features.Strings = ()
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
        Name = '查询.门禁组编号'
        Caption = '查询.门禁组编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.门禁机编号'
        Caption = '查询.门禁机编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '交易类型'
        Caption = '交易类型'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '门禁组编号'
        Caption = '门禁组编号'
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
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '门禁机编号'
        Caption = '门禁机编号'
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
        GroupIndex = 1
        DataField = 'lvol1'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|查询.门禁组编号|查询.门禁机编号|查询.交易类型|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|门禁组编号|门禁组名|门禁机编号|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 32
    Top = 256
  end
  inherited QueryRequest: TWVRequest
    ID = '门禁组门禁机查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '门禁组编号'
        FieldName = '查询.门禁组编号'
      end
      item
        ParamName = '门禁机编号'
        FieldName = '查询.门禁机编号'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 160
    Top = 256
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 132
  end
  inherited AddRequest: TWVRequest
    ID = '门禁组门禁机设置'
    Bindings = <
      item
        ParamName = '门禁组编号'
        FieldName = '门禁组编号'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '门禁机编号'
        FieldName = '门禁机编号'
      end>
    Left = 64
    Top = 256
  end
  inherited DeleteRequest: TWVRequest
    ID = '门禁组门禁机设置'
    Bindings = <
      item
        ParamName = '门禁组编号'
        FieldName = '门禁组编号'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '门禁机编号'
        FieldName = '门禁机编号'
      end>
    Left = 96
    Top = 256
  end
  inherited ChangeRequest: TWVRequest
    ID = '门禁组门禁机设置'
    Bindings = <
      item
        ParamName = '门禁组编号'
        FieldName = '门禁组编号'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '门禁机编号'
        FieldName = '门禁机编号'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDataSource: TWVDataSource
    Left = 164
  end
  inherited alDatasetActions: TActionList
    Left = 68
    Top = 292
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '门禁组查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '门禁组编号'
        FieldName = '查询.门禁组编号'
      end
      item
        ParamName = '门禁组名称'
        FieldName = '查询.门禁组名称'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    AfterExec = CheckReturnData
    Left = 80
    Top = 192
  end
  object WorkView1: TWorkView
    WorkFields = <
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
        Name = '查询.门禁组编号'
        Caption = '查询.门禁组编号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.门禁组名称'
        Caption = '查询.门禁组名称'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '交易类型'
        Caption = '交易类型'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|查询.门禁组编号|查询.门禁组名称|查询.交易类型|'
      end
      item
        MonitorValueChangedFields = '|门禁组编号|'
      end>
    Left = 32
    Top = 192
  end
  object MainRequest2: TWVRequest
    WorkView = WorkView2
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
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end>
    Left = 72
    Top = 360
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
        Name = '设备名称'
        Caption = '设备名称'
        FieldType = wftUndefined
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
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '机型代码'
        Caption = '机型代码'
        FieldType = wftUndefined
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
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial1'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|设备名称|三九设备注册号|设备物纜机号|机型代码|上级设备物纜设备' +
          '状态|设备物理型号|所属子系统|设备所在区域|负责人员工号|'
      end>
    Left = 36
    Top = 359
  end
end
