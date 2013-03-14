inherited faqhBusiSubjectLink: TfaqhBusiSubjectLink
  Width = 805
  Height = 541
  Caption = '商户科目映射'
  inherited pcPages: TRzPageControl
    Width = 805
    Height = 541
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 488
        Width = 801
        inherited btnAdd: TBitBtn [0]
          Left = 539
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 627
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 446
        end
        inherited btnDelete: TBitBtn
          Left = 712
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 88
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 801
      end
      inherited Grid: TRzDBGrid
        Width = 801
        Height = 470
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户名称'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '对应科目号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '对应科目名称'
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbankname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '开户银行'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_acc'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '银行账号'
            Width = 120
            Visible = True
          end>
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label6: TLabel [0]
        Left = 86
        Top = 68
        Width = 36
        Height = 12
        Caption = '商户号'
      end
      object Label7: TLabel [1]
        Left = 74
        Top = 110
        Width = 48
        Height = 12
        Caption = '商户名称'
      end
      object Label8: TLabel [2]
        Left = 74
        Top = 151
        Width = 48
        Height = 12
        Caption = '对应科目'
      end
      object Label10: TLabel [3]
        Left = 74
        Top = 194
        Width = 48
        Height = 12
        Caption = '开户银行'
      end
      object Label1: TLabel [4]
        Left = 74
        Top = 236
        Width = 48
        Height = 12
        Caption = '银行账号'
      end
      object btnSelect: TSpeedButton [5]
        Left = 282
        Top = 62
        Width = 23
        Height = 22
        Caption = '>>>'
        Flat = True
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        OnClick = btnSelectClick
      end
      inherited UIPanel2: TUIPanel
        Top = 482
        Width = 801
        TabOrder = 6
        inherited btnOK: TBitBtn
          Left = 625
        end
        inherited btnCancel: TBitBtn
          Left = 713
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtBusiId: TWVDigitalEdit
        Left = 132
        Top = 64
        Width = 149
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        BiDiMode = bdRightToLeft
        Color = clInfoBk
        ParentBiDiMode = False
        ParentColor = False
        TabOrder = 1
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '商户号'
        SynchronizeByValue = True
      end
      object edtBusiName: TWVEdit
        Left = 132
        Top = 105
        Width = 173
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 2
        Text = '<商户名称>'
        WorkView = WorkView
        FieldName = '商户名称'
        SynchronizeWhenExit = True
      end
      object WVEdit10: TWVEdit
        Left = 132
        Top = 189
        Width = 173
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 4
        Text = '<开户银行>'
        WorkView = WorkView
        FieldName = '开户银行'
        SynchronizeWhenExit = True
      end
      object WVEdit1: TWVEdit
        Left = 132
        Top = 230
        Width = 173
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 5
        Text = '<银行账号>'
        WorkView = WorkView
        FieldName = '银行账号'
        SynchronizeWhenExit = True
      end
      object pnl1: TPanel
        Left = 305
        Top = 62
        Width = 489
        Height = 369
        Color = 16119543
        TabOrder = 0
        object pnl2: TPanel
          Left = 1
          Top = 1
          Width = 487
          Height = 9
          Align = alTop
          Color = 16119543
          TabOrder = 0
        end
        object pnl3: TPanel
          Left = 1
          Top = 327
          Width = 487
          Height = 41
          Align = alBottom
          Color = 16119543
          TabOrder = 2
          object btnQry: TBitBtn
            Left = 228
            Top = 8
            Width = 75
            Height = 25
            Hint = '确认操作'
            Anchors = [akTop, akRight]
            Caption = '&Q 查询'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            OnClick = btnQryClick
          end
          object btnSel: TBitBtn
            Left = 316
            Top = 8
            Width = 75
            Height = 25
            Hint = '确认操作'
            Anchors = [akTop, akRight]
            Caption = '&S 选择'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            TabOrder = 2
            OnClick = btnSelClick
          end
          object btnCommon: TBitBtn
            Left = 20
            Top = 8
            Width = 75
            Height = 25
            Hint = '确认操作'
            Anchors = [akTop, akRight]
            Caption = '通用商户'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = btnCommonClick
          end
          object btnCnl: TBitBtn
            Left = 404
            Top = 8
            Width = 75
            Height = 25
            Hint = '确认操作'
            Anchors = [akTop, akRight]
            Caption = '取 消'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '宋体'
            Font.Style = []
            ParentFont = False
            TabOrder = 3
            OnClick = btnCnlClick
          end
        end
        object RzDBGrid1: TRzDBGrid
          Left = 1
          Top = 10
          Width = 487
          Height = 317
          Align = alClient
          DataSource = DataSource1
          FixedColor = 15458000
          ImeName = '拼音加加集合版'
          TabOrder = 1
          TitleFont.Charset = GB2312_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -12
          TitleFont.Name = '宋体'
          TitleFont.Style = []
          OnKeyDown = GridKeyDown
          FrameColor = 12164479
          FrameStyle = fsGroove
          FrameVisible = True
          FixedLineColor = 12164479
          LineColor = clBackground
          Columns = <
            item
              Expanded = False
              FieldName = 'sbranch_code0'
              Title.Alignment = taCenter
              Title.Caption = '校区'
              Width = 100
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'lvol3'
              Title.Alignment = taCenter
              Title.Caption = '商户号'
              Width = 50
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sall_name'
              Title.Alignment = taCenter
              Title.Caption = '商户名称'
              Width = 110
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'lvol7'
              Title.Alignment = taCenter
              Title.Caption = '商户类别'
              Width = 50
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'smain_flag2'
              Title.Alignment = taCenter
              Title.Caption = '末级商户'
              Visible = False
            end
            item
              Expanded = False
              FieldName = 'smain_flag'
              Title.Alignment = taCenter
              Title.Caption = '独立核算'
              Width = 60
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'scust_type'
              Title.Alignment = taCenter
              Title.Caption = '收搭伙费'
              Width = 60
              Visible = True
            end>
        end
      end
      object cbbSubJNo: TWVComboBox
        Left = 132
        Top = 145
        Width = 173
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ImeName = '紫光拼音输入法'
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView
        FieldName = '对应科目号'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-71'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 412
    Top = 319
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
        Name = '标志'
        Caption = '标志'
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
        Name = '查询.商户号'
        Caption = '查询.商户号'
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
        Name = '查询.对应科目名称'
        Caption = '查询.对应科目名称'
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
        Name = '查询.开户银行'
        Caption = '查询.开户银行'
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
        Name = '查询.银行账号'
        Caption = '查询.银行账号'
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
        Name = '商户号'
        Caption = '商户号'
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
        DataField = 'lvol3'
      end
      item
        Name = '商户名称'
        Caption = '商户名称'
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
        DataField = 'sall_name'
      end
      item
        Name = '对应科目号'
        Caption = '对应科目号'
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
        DataField = 'scust_auth'
      end
      item
        Name = '对应科目名称'
        Caption = '对应科目名称'
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
        DataField = 'scusttypes'
      end
      item
        Name = '开户银行'
        Caption = '开户银行'
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
        DataField = 'sbankname'
      end
      item
        Name = '银行账号'
        Caption = '银行账号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
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
        GroupIndex = 1
        DataField = 'sbank_acc'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.标志|查询.商户号|查询.对应科目名称|查询.开户银行|查询.银行' +
          '账号|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|商户号|商户名称|对应科目号|对应科目名称|开户银行|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 344
    Top = 280
  end
  inherited QueryRequest: TWVRequest
    ID = '商户科目映射查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '商户号'
        FieldName = '查询.商户号'
      end
      item
        ParamName = '对应科目名称'
        FieldName = '查询.对应科目名称'
      end
      item
        ParamName = '开户银行'
        FieldName = '查询.开户银行'
      end
      item
        ParamName = '银行账号'
        FieldName = '查询.银行账号'
      end>
    Left = 472
    Top = 280
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 380
    Top = 319
  end
  inherited AddRequest: TWVRequest
    ID = '商户科目映射'
    Bindings = <
      item
        ParamName = '商户号'
        FieldName = '商户号'
      end
      item
        ParamName = '商户名称'
        FieldName = '商户名称'
      end
      item
        ParamName = '对应科目号'
        FieldName = '对应科目号'
      end
      item
        ParamName = '对应科目名称'
        FieldName = '对应科目名称'
      end
      item
        ParamName = '开户银行'
        FieldName = '开户银行'
      end
      item
        ParamName = '银行账号'
        FieldName = '银行账号'
      end
      item
        ParamName = '标志'
        FieldName = '标志'
      end>
    Left = 376
    Top = 280
  end
  inherited DeleteRequest: TWVRequest
    ID = '商户科目映射'
    Bindings = <
      item
        ParamName = '商户号'
        FieldName = '商户号'
      end
      item
        ParamName = '商户名称'
        FieldName = '商户名称'
      end
      item
        ParamName = '对应科目号'
        FieldName = '对应科目号'
      end
      item
        ParamName = '对应科目名称'
        FieldName = '对应科目名称'
      end
      item
        ParamName = '开户银行'
        FieldName = '开户银行'
      end
      item
        ParamName = '银行账号'
        FieldName = '银行账号'
      end
      item
        ParamName = '标志'
        FieldName = '标志'
      end>
    Left = 408
    Top = 280
  end
  inherited ChangeRequest: TWVRequest
    ID = '商户科目映射'
    Bindings = <
      item
        ParamName = '商户号'
        FieldName = '商户号'
      end
      item
        ParamName = '商户名称'
        FieldName = '商户名称'
      end
      item
        ParamName = '对应科目号'
        FieldName = '对应科目号'
      end
      item
        ParamName = '对应科目名称'
        FieldName = '对应科目名称'
      end
      item
        ParamName = '开户银行'
        FieldName = '开户银行'
      end
      item
        ParamName = '银行账号'
        FieldName = '银行账号'
      end
      item
        ParamName = '标志'
        FieldName = '标志'
      end>
    Left = 440
    Top = 280
  end
  inherited WVDataSource: TWVDataSource
    Left = 476
    Top = 319
  end
  inherited alDatasetActions: TActionList
    Left = 444
    Top = 316
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
        DataField = 'lvol5'
      end
      item
        Name = '父商户标识'
        Caption = '父商户标识'
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
        GroupIndex = 1
        DataField = 'scard1'
      end
      item
        Name = '商户类别'
        Caption = '商户类别'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol7'
      end
      item
        Name = '是否为独立核算'
        Caption = '是否为独立核算'
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
        Name = '是否为叶节点'
        Caption = '是否为叶节点'
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
        Name = '收搭伙费'
        Caption = '收搭伙费'
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
          '|商户标识|客户号|父商户标识|商户名称|商户类别|是否为叶节点|商户' +
          '状态|负责人员工号|负责人姓名|负责人性别|负责人民族代码|负责人身' +
          '份证号|联系电话|联系地址|是否收取管理费|收取消费管理费比例|商户' +
          '管理费计算方式|商户税费计算方式|注册时间|备注|'
      end>
    Left = 380
    Top = 359
  end
  object MainRequest: TWVRequest
    WorkView = WorkView1
    ID = '商户信息非主键查询'
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
        ParamName = '商户标识'
        FieldName = '商户标识'
      end
      item
        ParamName = '父商户标识'
        FieldName = '父商户标识'
      end
      item
        ParamName = '商户名称'
        FieldName = '商户名称'
      end
      item
        ParamName = '商户类别'
        FieldName = '商户类别'
      end
      item
        ParamName = '是否为独立核算'
        FieldName = '是否为独立核算'
      end
      item
        ParamName = '是否为叶节点'
        FieldName = '是否为叶节点'
      end
      item
        ParamName = '收搭伙费'
        FieldName = '收搭伙费'
      end>
    Left = 416
    Top = 360
  end
  object WVDBBinder: TWVDBBinder
    DataSource = DataSource1
    WorkView = WorkView1
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'lvol7'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '14'
      end
      item
        FieldName = 'smain_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'scust_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end>
    HideUnbindingFields = False
    Left = 456
    Top = 360
  end
  object DataSource1: TDataSource
    OnDataChange = DataSourceDataChange
    Left = 488
    Top = 360
  end
end
