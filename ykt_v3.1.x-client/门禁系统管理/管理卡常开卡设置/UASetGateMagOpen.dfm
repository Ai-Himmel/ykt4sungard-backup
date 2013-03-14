inherited faqhSetGateMgrOpen: TfaqhSetGateMgrOpen
  Width = 871
  Height = 547
  inherited UIPnlQueryCount: TUIPanel [0]
    Width = 871
    inherited Image1: TImage
      Width = 871
    end
    inherited LabRecordCount: TLabel
      Font.Color = clBlack
      Visible = False
    end
  end
  inherited UIPanel1: TUIPanel [1]
    Top = 513
    Width = 871
    Height = 34
    object WVLabel1: TWVLabel [0]
      Left = 8
      Top = 12
      Width = 36
      Height = 12
      Caption = '卡用途'
    end
    object WVLabel2: TWVLabel [1]
      Left = 152
      Top = 12
      Width = 48
      Height = 12
      Caption = '操作类别'
    end
    inherited btnQuery: TBitBtn
      Left = 782
      Height = 26
      Caption = '设 置'
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 781
      Top = 300
      TabOrder = 3
      Visible = False
    end
    object cbbUse: TWVComboBox
      Left = 48
      Top = 7
      Width = 89
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '85'
    end
    object cbbOperType: TWVComboBox
      Left = 208
      Top = 6
      Width = 89
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 1
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '44'
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 871
    Height = 495
    inherited Grid: TRzDBGrid
      Left = 40
      Top = 240
      Width = 153
      Height = 137
      Align = alNone
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
    object spnl1: TRzSizePanel
      Left = 0
      Top = 0
      Width = 411
      Height = 495
      Color = 15458000
      HotSpotVisible = True
      SizeBarWidth = 7
      TabOrder = 0
      UseGradients = True
      object pnlDevInfo: TPanel
        Left = 0
        Top = 0
        Width = 403
        Height = 495
        Align = alClient
        BevelOuter = bvNone
        Color = 15458000
        TabOrder = 0
        object pnl1: TPanel
          Left = 0
          Top = 0
          Width = 403
          Height = 97
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object Label6: TLabel
            Left = 15
            Top = 9
            Width = 42
            Height = 12
            Caption = '学/工号'
          end
          object Label7: TLabel
            Left = 9
            Top = 57
            Width = 48
            Height = 12
            Caption = '客户姓名'
          end
          object WVLabel5: TWVLabel
            Left = 192
            Top = 9
            Width = 48
            Height = 12
            Caption = '客户类别'
          end
          object WVLabel9: TWVLabel
            Left = 9
            Top = 32
            Width = 48
            Height = 12
            Caption = '显示卡号'
          end
          object WVLabel8: TWVLabel
            Left = 192
            Top = 33
            Width = 48
            Height = 12
            Caption = '所属部门'
          end
          object WVEdit4: TWVEdit
            Left = 59
            Top = 5
            Width = 118
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 0
            Text = '<学工号>'
            WorkView = WorkView1
            FieldName = '学工号'
          end
          object WVEdit8: TWVEdit
            Left = 59
            Top = 53
            Width = 118
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 4
            Text = '<客户姓名>'
            WorkView = WorkView1
            FieldName = '客户姓名'
          end
          object WVComboBox6: TWVComboBox
            Left = 243
            Top = 5
            Width = 143
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 1
            WorkView = WorkView1
            FieldName = '客户类别'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-34'
          end
          object WVEdit5: TWVEdit
            Left = 59
            Top = 29
            Width = 118
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 2
            Text = '<显示卡号>'
            WorkView = WorkView1
            FieldName = '显示卡号'
          end
          object WVComboBox5: TWVComboBox
            Left = 243
            Top = 29
            Width = 143
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 3
            WorkView = WorkView1
            FieldName = '部门'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-22'
          end
          object btnCardQuery: TBitBtn
            Left = 306
            Top = 55
            Width = 79
            Height = 25
            Hint = '查询/刷新数据'
            Anchors = [akTop, akRight]
            Caption = '卡查询'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            TabOrder = 5
            OnClick = btnCardQueryClick
          end
          object chkCustAll: TCheckBox
            Left = 8
            Top = 77
            Width = 97
            Height = 17
            Caption = '全选'
            TabOrder = 6
            OnClick = chkCustAllClick
          end
        end
        object lvCard: TListView
          Left = 0
          Top = 97
          Width = 403
          Height = 398
          Align = alClient
          Checkboxes = True
          Columns = <
            item
              Caption = '选择'
              Width = 40
            end
            item
              Caption = '客户号'
              Width = 60
            end
            item
              Caption = '卡号'
              Width = 60
            end
            item
              Caption = '学/工号'
              Width = 80
            end
            item
              Caption = '客户名称'
              Width = 100
            end
            item
              Caption = '客户类别'
              Width = 80
            end
            item
              Caption = '卡类型'
              Width = 60
            end
            item
              Caption = '卡状态'
            end>
          ColumnClick = False
          FlatScrollBars = True
          GridLines = True
          TabOrder = 1
          ViewStyle = vsReport
        end
      end
    end
    object pnlCardInfo: TPanel
      Left = 411
      Top = 0
      Width = 460
      Height = 495
      Align = alClient
      BevelOuter = bvNone
      Color = 15458000
      TabOrder = 1
      object pnlCardQuery: TPanel
        Left = 0
        Top = 0
        Width = 460
        Height = 97
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object Label4: TLabel
          Left = 30
          Top = 10
          Width = 48
          Height = 12
          Caption = '设备机型'
        end
        object Label1: TLabel
          Left = 6
          Top = 34
          Width = 72
          Height = 12
          Caption = '上级物理编号'
        end
        object Label2: TLabel
          Left = 229
          Top = 34
          Width = 72
          Height = 12
          Caption = '设备物理编号'
        end
        object Label5: TLabel
          Left = 241
          Top = 10
          Width = 60
          Height = 12
          Caption = '所属子系统'
        end
        object Label3: TLabel
          Left = 30
          Top = 58
          Width = 48
          Height = 12
          Caption = '设备名称'
        end
        object WVComboBox18: TWVComboBox
          Left = 84
          Top = 6
          Width = 133
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '设备机型'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*47'
        end
        object WVEdit1: TWVEdit
          Left = 84
          Top = 30
          Width = 133
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 2
          Text = '<上级设备>'
          WorkView = WorkView
          FieldName = '上级设备'
        end
        object WVComboBox17: TWVComboBox
          Left = 312
          Top = 6
          Width = 133
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 1
          WorkView = WorkView
          FieldName = '子系统'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-32'
        end
        object WVEdit2: TWVEdit
          Left = 312
          Top = 30
          Width = 133
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 3
          Text = '<设备物理编号>'
          WorkView = WorkView
          FieldName = '设备物理编号'
        end
        object WVEdit3: TWVEdit
          Left = 84
          Top = 54
          Width = 133
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 4
          Text = '<设备名称>'
          WorkView = WorkView
          FieldName = '设备名称'
        end
        object btnDevQuery: TBitBtn
          Left = 365
          Top = 55
          Width = 79
          Height = 25
          Hint = '查询/刷新数据'
          Anchors = [akTop, akRight]
          Caption = '设备查询'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
          OnClick = btnDevQueryClick
        end
        object chkDevall: TCheckBox
          Left = 32
          Top = 77
          Width = 97
          Height = 17
          Caption = '全选'
          TabOrder = 6
          OnClick = chkDevallClick
        end
      end
      object lvEqu: TListView
        Left = 0
        Top = 97
        Width = 460
        Height = 398
        Align = alClient
        Checkboxes = True
        Columns = <
          item
            Caption = '选择'
            Width = 40
          end
          item
            Caption = '设备编号'
            Width = 60
          end
          item
            Caption = '设备物理编号'
            Width = 120
          end
          item
            Caption = '设备名称'
            Width = 200
          end
          item
            Caption = '上级设备'
            Width = 120
          end
          item
            Caption = '设备机型'
            Width = 80
          end
          item
            Caption = '所属子系统'
            Width = 80
          end>
        ColumnClick = False
        FlatScrollBars = True
        GridLines = True
        TabOrder = 1
        ViewStyle = vsReport
      end
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
        Name = '上级设备'
        Caption = '上级设备'
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
      end
      item
        Name = '设备物理编号'
        Caption = '设备物理编号'
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
      end
      item
        Name = '设备机型'
        Caption = '设备机型'
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
        Name = '子系统'
        Caption = '子系统'
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
          '|设备名称|三九设备注册号|设备物纜机号|机型代码|上级设备物纜设备' +
          '状态|设备物理型号|所属子系统|设备所在区域|负责人员工号|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 76
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '设备查询'
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
        ParamName = '上级设备'
        FieldName = '上级设备'
      end
      item
        ParamName = '设备物理编号'
        FieldName = '设备物理编号'
      end
      item
        ParamName = '设备名称'
        FieldName = '设备名称'
      end
      item
        ParamName = '设备机型'
        FieldName = '设备机型'
      end
      item
        ParamName = '子系统'
        FieldName = '子系统'
      end>
    Left = 120
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 184
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 232
    Top = 256
  end
  object WorkView1: TWorkView
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
        Name = '客户号'
        Caption = '客户号'
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
        GetPrevChar = '*'
      end
      item
        Name = '学工号'
        Caption = '学工号'
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
        Name = '客户姓名'
        Caption = '客户姓名'
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
        Name = '部门'
        Caption = '部门'
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
        Name = '证件类型'
        Caption = '证件类型'
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
        Name = '证件号码'
        Caption = '证件号码'
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
        Name = '客户类别'
        Caption = '客户类别'
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
        Name = '收费类别'
        Caption = '收费类别'
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
        Name = '所属区域'
        Caption = '所属区域'
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
        Name = '显示卡号'
        Caption = '显示卡号'
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
        Name = '导入批次号'
        Caption = '导入批次号'
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
        Name = '注销日期'
        Caption = '注销日期'
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
        Name = '卡号'
        Caption = '卡号'
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
        Name = '钱包号'
        Caption = '钱包号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lvol3'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|客户号|学工号|卡号|姓名|身份证号|'
      end>
    Left = 76
    Top = 303
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '已开卡客户信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
        DefaultValue = 0
      end
      item
        ParamName = '部门'
        FieldName = '部门'
      end
      item
        ParamName = '导入批次号'
        FieldName = '导入批次号'
      end
      item
        ParamName = '客户类别'
        FieldName = '客户类别'
        DefaultValue = 0
      end
      item
        ParamName = '客户姓名'
        FieldName = '客户姓名'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
        DefaultValue = 0
      end
      item
        ParamName = '所属区域'
        FieldName = '所属区域'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '证件号码'
        FieldName = '证件号码'
      end
      item
        ParamName = '证件类型'
        FieldName = '证件类型'
      end
      item
        ParamName = '注销日期'
        FieldName = '注销日期'
      end
      item
        ParamName = '显示卡号'
        FieldName = '显示卡号'
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
        DefaultValue = 0
      end
      item
        ParamName = '钱包号'
        FieldName = '钱包号'
        DefaultValue = 0
      end>
    AfterExec = MainRequestAfterExec
    Left = 112
    Top = 304
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
        Name = '卡号'
        Caption = '卡号'
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
        Name = '设备号'
        Caption = '设备号'
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
        Name = '卡用途'
        Caption = '卡用途'
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
        Name = '操作类别'
        Caption = '操作类别'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|设备名称|三九设备注册号|设备物纜机号|机型代码|上级设备物纜设备' +
          '状态|设备物理型号|所属子系统|设备所在区域|负责人员工号|'
      end>
    Left = 68
    Top = 359
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '管理卡常开卡设置'
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
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '设备号'
        FieldName = '设备号'
      end
      item
        ParamName = '卡用途'
        FieldName = '卡用途'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end>
    AfterExec = MainRequestAfterExec
    Left = 112
    Top = 360
  end
  object dlgSave1: TSaveDialog
    Filter = '文本文件(*.txt)|*.txt'
    Title = '设置常开管理卡失败信息'
    Left = 192
    Top = 362
  end
end
