inherited faqhsetGateOpenAlong: TfaqhsetGateOpenAlong
  Width = 816
  Height = 542
  Caption = '常开时间段设置'
  inherited pcPages: TRzPageControl
    Width = 816
    Height = 542
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 483
        Width = 812
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 638
          Top = 6
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 470
          Top = 6
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 553
          Top = 6
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = 723
          Top = 6
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 254
          Top = 6
          Visible = False
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 8
          Top = 11
          Width = 177
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 812
        Align = alNone
        TabOrder = 1
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 812
        Height = 450
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '门禁机编号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '时间周编号'
            Width = 80
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
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '时间周名称'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '状态'
            Width = 60
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 812
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label2: TLabel
          Left = 18
          Top = 10
          Width = 48
          Height = 12
          Caption = '操作员号'
          Visible = False
        end
        object WVComboBox1: TWVComboBox
          Left = 69
          Top = 5
          Width = 156
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 0
          TabOrder = 0
          Text = '<>'
          Visible = False
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-30'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      inherited UIPanel2: TUIPanel
        Top = 483
        Width = 812
        TabOrder = 2
        inherited btnOK: TBitBtn
          Left = 640
        end
        inherited btnCancel: TBitBtn
          Left = 728
        end
        inherited DBNavigator: TRzDBNavigator
          Left = 791
          Hints.Strings = ()
          Visible = False
        end
        object chkSelectAll: TRzCheckBox
          Left = 184
          Top = 11
          Width = 57
          Height = 17
          Caption = '全选'
          FrameColor = 8409372
          HighlightColor = 2203937
          HotTrack = True
          HotTrackColor = 3983359
          HotTrackColorType = htctActual
          State = cbUnchecked
          TabOrder = 3
          OnClick = chkSelectAllClick
        end
        object chkReSelect: TRzCheckBox
          Left = 264
          Top = 11
          Width = 57
          Height = 17
          Caption = '反选'
          FrameColor = 8409372
          HighlightColor = 2203937
          HotTrack = True
          HotTrackColor = 3983359
          HotTrackColorType = htctActual
          State = cbUnchecked
          TabOrder = 4
          Visible = False
          OnClick = chkReSelectClick
        end
      end
      object pnl1: TPanel
        Left = 179
        Top = 0
        Width = 633
        Height = 483
        Align = alClient
        BevelOuter = bvNone
        Caption = 'pnl1'
        TabOrder = 1
        object Panel2: TPanel
          Left = 0
          Top = 0
          Width = 633
          Height = 121
          Align = alTop
          BevelOuter = bvNone
          Color = 16119543
          TabOrder = 0
          object Label10: TLabel
            Left = 2
            Top = 5
            Width = 112
            Height = 16
            Caption = '常开时间段设置'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = '黑体'
            Font.Style = []
            ParentFont = False
          end
          object Label1: TLabel
            Left = 2
            Top = 41
            Width = 48
            Height = 12
            Caption = '设备名称'
          end
          object Label6: TLabel
            Left = 2
            Top = 68
            Width = 48
            Height = 12
            Caption = '设备机型'
          end
          object Label11: TLabel
            Left = 464
            Top = 41
            Width = 60
            Height = 12
            Caption = '设备物理ID'
          end
          object Label12: TLabel
            Left = 441
            Top = 67
            Width = 84
            Height = 12
            Caption = '上级设备物理ID'
          end
          object Label3: TLabel
            Left = 266
            Top = 11
            Width = 48
            Height = 12
            Caption = '设备状态'
            Visible = False
          end
          object Label4: TLabel
            Left = 14
            Top = 95
            Width = 36
            Height = 12
            Caption = '子系统'
          end
          object Label5: TLabel
            Left = 210
            Top = 69
            Width = 72
            Height = 12
            Caption = '设备所在区域'
          end
          object Label7: TLabel
            Left = 210
            Top = 43
            Width = 72
            Height = 12
            Caption = '设备物理型号'
          end
          object WVEdit1: TWVEdit
            Left = 52
            Top = 37
            Width = 157
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 1
            Text = '<设备名称>'
            WorkView = WorkView2
            FieldName = '设备名称'
          end
          object cbbScode: TWVComboBox
            Left = 52
            Top = 64
            Width = 157
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 5
            WorkView = WorkView2
            FieldName = '机型代码'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*47'
          end
          object WVEdit3: TWVEdit
            Left = 526
            Top = 37
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
            Left = 526
            Top = 63
            Width = 100
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 4
            Text = '<上级设备物理ID>'
            WorkView = WorkView2
            FieldName = '上级设备物理ID'
          end
          object WVComboBox5: TWVComboBox
            Left = 284
            Top = 39
            Width = 153
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 3
            WorkView = WorkView2
            FieldName = '设备物理型号'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-35'
          end
          object WVComboBox2: TWVComboBox
            Left = 316
            Top = 7
            Width = 156
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 0
            Visible = False
            WorkView = WorkView2
            FieldName = '设备状态'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*5'
          end
          object WVComboBox3: TWVComboBox
            Left = 52
            Top = 91
            Width = 157
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 8
            WorkView = WorkView2
            FieldName = '所属子系统'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-32'
          end
          object WVComboBox4: TWVComboBox
            Left = 284
            Top = 65
            Width = 153
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 6
            WorkView = WorkView2
            FieldName = '设备所在区域'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-28'
          end
          object btnEquQuery: TBitBtn
            Left = 551
            Top = 88
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
            TabOrder = 7
            OnClick = btnEquQueryClick
          end
        end
        object lvGate: TRzListView
          Left = 0
          Top = 121
          Width = 633
          Height = 362
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
              Caption = '设备物理编号'
              Width = 90
            end
            item
              Caption = '所属子系统'
              Width = 90
            end
            item
              Caption = '所在区域'
              Width = 202
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
      object rzszpnl1: TRzSizePanel
        Left = 0
        Top = 0
        Width = 179
        Height = 483
        Color = 16119543
        HotSpotVisible = True
        SizeBarWidth = 7
        TabOrder = 0
        UseGradients = True
        object lst1: TRzCheckList
          Left = 0
          Top = 0
          Width = 171
          Height = 483
          Align = alClient
          ItemHeight = 17
          TabOrder = 0
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 132
    Top = 375
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
        Name = '查询.时间周编号'
        Caption = '查询.时间周编号'
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
        Name = '查询.门禁机编号'
        Caption = '查询.门禁机编号'
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
      end
      item
        Name = '时间周编号'
        Caption = '时间周编号'
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
        GroupIndex = 1
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.门禁机编号|查询.操作员号|查询.门禁机名称|查询.操作员名|查' +
          '询.交易类型|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|门禁机编号|门禁机名|操作员号|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Top = 344
  end
  inherited QueryRequest: TWVRequest
    ID = '常开时间段查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '时间周编号'
        FieldName = '查询.时间周编号'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '门禁机编号'
        FieldName = '查询.门禁机编号'
      end>
    Left = 200
    Top = 344
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '84'
      end>
    Left = 100
    Top = 375
  end
  inherited AddRequest: TWVRequest
    ID = '常开时间段设置'
    Bindings = <
      item
        ParamName = '门禁机编号'
        FieldName = '门禁机编号'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '时间周编号'
        FieldName = '时间周编号'
      end>
    Left = 104
    Top = 344
  end
  inherited DeleteRequest: TWVRequest
    ID = '常开时间段设置'
    Bindings = <
      item
        ParamName = '门禁机编号'
        FieldName = '门禁机编号'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '时间周编号'
        FieldName = '时间周编号'
      end>
    Left = 136
    Top = 344
  end
  inherited ChangeRequest: TWVRequest
    ID = '常开时间段设置'
    Bindings = <
      item
        ParamName = '门禁机编号'
        FieldName = '门禁机编号'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '时间周编号'
        FieldName = '时间周编号'
      end>
    Top = 344
  end
  inherited WVDataSource: TWVDataSource
    Left = 204
    Top = 375
  end
  inherited alDatasetActions: TActionList
    Left = 164
    Top = 380
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
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end>
    Left = 128
    Top = 224
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
    Left = 92
    Top = 223
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
        Name = '查询.时间段组编号'
        Caption = '查询.时间段组编号'
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
        Name = '查询.时间段组名称'
        Caption = '查询.时间段组名称'
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
        Name = '查询.周一组编号'
        Caption = '查询.周一组编号'
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
        Name = '查询.周二组编号'
        Caption = '查询.周二组编号'
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
        Name = '查询.周三组编号'
        Caption = '查询.周三组编号'
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
        Name = '查询.周四组编号'
        Caption = '查询.周四组编号'
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
        Name = '查询.周五组编号'
        Caption = '查询.周五组编号'
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
        Name = '查询.周六组编号'
        Caption = '查询.周六组编号'
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
        Name = '查询.周日组编号'
        Caption = '查询.周日组编号'
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
        Name = '时间段组编号'
        Caption = '时间段组编号'
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
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '时间段组名'
        Caption = '时间段组名'
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
        DataField = 'semail'
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
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '周一组编号'
        Caption = '周一组编号'
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
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '周二组编号'
        Caption = '周二组编号'
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
        GroupIndex = 1
        DataField = 'lvol2'
      end
      item
        Name = '周三组编号'
        Caption = '周三组编号'
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
        GroupIndex = 1
        DataField = 'lvol3'
      end
      item
        Name = '周四组编号'
        Caption = '周四组编号'
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
        GroupIndex = 1
        DataField = 'lvol4'
      end
      item
        Name = '周五组编号'
        Caption = '周五组编号'
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
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '周六组编号'
        Caption = '周六组编号'
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
        GroupIndex = 1
        DataField = 'lvol6'
      end
      item
        Name = '周日组编号'
        Caption = '周日组编号'
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
        GroupIndex = 1
        DataField = 'lvol7'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.时间段组编号|查询.时间段组名称|查询.周一组编号|查询.周二组' +
          '编号|查询.周三组编号|查询.周四组编号|查询.周五组编号|查询.周六组' +
          '编号|查询.周日组编号|查询.标志|'
      end
      item
        MonitorValueChangedFields = 
          '|时间段组编号|时间段组名|标志|周一组编号|周二组编号|周三组编号|' +
          '周四组编号|周五组编号|周六组编号|周日组编号|'
      end>
    Left = 88
    Top = 256
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '周时间段查询'
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
        ParamName = '时间段组编号'
        FieldName = '查询.时间段组编号'
      end
      item
        ParamName = '时间段组名称'
        FieldName = '查询.时间段组名称'
      end
      item
        ParamName = '周一组编号'
        FieldName = '查询.周一组编号'
      end
      item
        ParamName = '周二组编号'
        FieldName = '查询.周二组编号'
      end
      item
        ParamName = '周三组编号'
        FieldName = '查询.周三组编号'
      end
      item
        ParamName = '周四组编号'
        FieldName = '查询.周四组编号'
      end
      item
        ParamName = '周五组编号'
        FieldName = '查询.周五组编号'
      end
      item
        ParamName = '周六组编号'
        FieldName = '查询.周六组编号'
      end
      item
        ParamName = '周日组编号'
        FieldName = '查询.周日组编号'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    AfterExec = CheckReturnData
    Left = 128
    Top = 256
  end
end
