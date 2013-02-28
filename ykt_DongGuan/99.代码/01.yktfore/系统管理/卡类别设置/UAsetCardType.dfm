inherited faqhsetCardType: TfaqhsetCardType
  Width = 744
  Height = 477
  Caption = '卡类别设置'
  inherited pcPages: TRzPageControl
    Width = 744
    Height = 477
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 414
        Width = 740
        Height = 40
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 474
          Top = 7
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 562
          Top = 7
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 385
          Top = 7
        end
        inherited btnDelete: TBitBtn
          Left = 651
          Top = 7
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
          Top = 7
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 12
          Width = 169
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 740
      end
      inherited Grid: TRzDBGrid
        Top = 41
        Width = 740
        Height = 373
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '卡类别'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '卡类别名称'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '卡成本费'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '预存金额'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '单笔充值限额'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '卡限额'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '卡物理类别'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smarket_code2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '是否匿名卡'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '能否重用'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '能否补办'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '固定卡有效期'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '是否支持多钱包'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'smarket_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '使用状态'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '有效天数'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Caption = '匿名卡收费类别'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'vsvarstr1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '可用的收费类别'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '用途'
            Visible = False
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 740
        Height = 23
        Align = alTop
        ParentColor = True
        TabOrder = 1
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label14: TLabel [0]
        Left = 102
        Top = 52
        Width = 36
        Height = 12
        Caption = '卡类别'
      end
      object Label15: TLabel [1]
        Left = 90
        Top = 110
        Width = 48
        Height = 12
        Caption = '卡成本费'
      end
      object Label16: TLabel [2]
        Left = 74
        Top = 81
        Width = 66
        Height = 12
        Caption = '卡类别名称*'
      end
      object Label17: TLabel [3]
        Left = 90
        Top = 309
        Width = 48
        Height = 12
        Caption = '预存金额'
      end
      object Label18: TLabel [4]
        Left = 90
        Top = 164
        Width = 48
        Height = 12
        Caption = '能否重用'
      end
      object Label19: TLabel [5]
        Left = 90
        Top = 250
        Width = 48
        Height = 12
        Caption = '能否补办'
      end
      object Label20: TLabel [6]
        Left = 66
        Top = 221
        Width = 72
        Height = 12
        Caption = '固定卡有效期'
      end
      object Label21: TLabel [7]
        Left = 406
        Top = 278
        Width = 84
        Height = 12
        Caption = '是否支持多钱包'
        Visible = False
      end
      object Label23: TLabel [8]
        Left = 90
        Top = 192
        Width = 48
        Height = 12
        Caption = '有效天数'
      end
      object Label1: TLabel [9]
        Left = 78
        Top = 279
        Width = 60
        Height = 12
        Caption = '是否匿名卡'
      end
      object Label2: TLabel [10]
        Left = 405
        Top = 334
        Width = 84
        Height = 12
        Caption = '匿名卡收费类别'
        Visible = False
      end
      object WVLabel3: TWVLabel [11]
        Left = 80
        Top = 137
        Width = 60
        Height = 12
        Caption = '卡物理类别'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel [12]
        Left = 66
        Top = 338
        Width = 72
        Height = 12
        Caption = '单笔充值限额'
      end
      object Label4: TLabel [13]
        Left = 102
        Top = 367
        Width = 36
        Height = 12
        Caption = '卡限额'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 740
        TabOrder = 13
        inherited btnOK: TBitBtn
          Left = 568
        end
        inherited btnCancel: TBitBtn
          Left = 656
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtCardType: TWVDigitalEdit
        Left = 150
        Top = 48
        Width = 187
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '卡类别'
        SynchronizeByValue = True
      end
      object WVDigitalEdit15: TWVDigitalEdit
        Left = 150
        Top = 106
        Width = 187
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 3
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '卡成本费'
        SynchronizeByValue = True
      end
      object edtName: TWVEdit
        Left = 150
        Top = 77
        Width = 187
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<卡类别名称>'
        WorkView = WorkView
        FieldName = '卡类别名称'
        SynchronizeWhenExit = True
      end
      object WVEdit17: TWVEdit
        Left = 150
        Top = 305
        Width = 187
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 11
        Text = '<预存金额>'
        WorkView = WorkView
        FieldName = '预存金额'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit23: TWVDigitalEdit
        Left = 150
        Top = 188
        Width = 187
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 5
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '有效天数'
        SynchronizeByValue = True
      end
      object WVComboBox1: TWVComboBox
        Left = 150
        Top = 160
        Width = 187
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 4
        WorkView = WorkView
        FieldName = '能否重用'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object WVComboBox3: TWVComboBox
        Left = 150
        Top = 216
        Width = 187
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 6
        WorkView = WorkView
        FieldName = '能否挂失'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object WVComboBox4: TWVComboBox
        Left = 150
        Top = 245
        Width = 187
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 7
        WorkView = WorkView
        FieldName = '能否补办'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object WVComboBox5: TWVComboBox
        Left = 502
        Top = 274
        Width = 187
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 8
        Visible = False
        WorkView = WorkView
        FieldName = '是否支持多钱包'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object cbbNMK: TWVComboBox
        Left = 150
        Top = 275
        Width = 187
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 9
        OnChange = cbbNMKChange
        WorkView = WorkView
        FieldName = '是否匿名卡'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object cbbFeeType: TWVComboBox
        Left = 502
        Top = 330
        Width = 187
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 10
        Visible = False
        WorkView = WorkView
        FieldName = '默认收费类别'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-43'
      end
      object cbbCardType: TWVComboBox
        Left = 150
        Top = 414
        Width = 187
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 12
        Visible = False
        WorkView = WorkView
        FieldName = '默认收费类别'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-43'
      end
      object cbbPhyType: TWVComboBox
        Left = 150
        Top = 133
        Width = 187
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 2
        WorkView = WorkView
        FieldName = '卡物理类别'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-4'
      end
      object WVEdit1: TWVEdit
        Left = 150
        Top = 334
        Width = 187
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 14
        Text = '<单笔限额>'
        WorkView = WorkView
        FieldName = '单笔限额'
        SynchronizeWhenExit = True
      end
      object WVEdit2: TWVEdit
        Left = 150
        Top = 363
        Width = 187
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 15
        Text = '<卡限额>'
        WorkView = WorkView
        FieldName = '卡限额'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 556
    Top = 207
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
        Name = '交易类型'
        Caption = '交易类型'
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
        DataField = 'Sstatus0'
      end
      item
        Name = '卡类别'
        Caption = '卡类别'
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
        Name = '卡成本费'
        Caption = '卡成本费'
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
      end
      item
        Name = '卡类别名称'
        Caption = '卡类别名称'
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
        DataField = 'sname'
      end
      item
        Name = '用途'
        Caption = '用途'
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
        DataField = 'vsvarstr0'
      end
      item
        Name = '能否重用'
        Caption = '能否重用'
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
        DataField = 'sstatus1'
      end
      item
        Name = '能否补办'
        Caption = '能否补办'
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
        DataField = 'sstatus2'
      end
      item
        Name = '能否挂失'
        Caption = '能否挂失'
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
        DataField = 'sstatus3'
      end
      item
        Name = '是否支持多钱包'
        Caption = '是否支持多钱包'
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
        DataField = 'sstatus4'
      end
      item
        Name = '使用状态'
        Caption = '使用状态'
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
        DataField = 'smarket_code'
      end
      item
        Name = '有效天数'
        Caption = '有效天数'
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
        DataField = 'lvol2'
      end
      item
        Name = '可用的收费类别'
        Caption = '可用的收费类别'
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
        GroupIndex = 1
        DataField = 'vsvarstr1'
      end
      item
        Name = '是否匿名卡'
        Caption = '是否匿名卡'
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
        GroupIndex = 1
        DataField = 'smarket_code2'
      end
      item
        Name = '默认收费类别'
        Caption = '默认收费类别'
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
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '卡物理类别'
        Caption = '卡物理类别'
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
        DataField = 'lvol3'
      end
      item
        Name = '预存金额'
        Caption = '预存金额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
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
        DataField = 'damt0'
      end
      item
        Name = '单笔限额'
        Caption = '单笔限额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
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
        DataField = 'damt1'
      end
      item
        Name = '卡限额'
        Caption = '卡限额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
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
        DataField = 'damt2'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.交易类型|查询.卡类别|查询.卡类别名称|查询.卡成本费|查询.使' +
          '用状态|查询.能否重用|查询.用途|查询.能否补办|查询.能否挂失|查询.' +
          '是否支持多钱包|查询.有效天数|查询.可用的收费类别|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|交易类型|卡类别|卡成本费|卡类别名称|用途|能否重用|能否补办|能否' +
          '挂失|是否支持多钱包|使用状态|有效天数|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 472
    Top = 160
  end
  inherited QueryRequest: TWVRequest
    ID = '卡类别查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '卡类别'
        FieldName = '卡类别'
        DefaultValue = 0
      end>
    Left = 632
    Top = 160
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '2'
      end
      item
        FieldName = 'sstatus2'
        DataPresentType = 'idobjects'
        DataPresentParam = '2'
      end
      item
        FieldName = 'sstatus3'
        DataPresentType = 'idobjects'
        DataPresentParam = '2'
      end
      item
        FieldName = 'sstatus4'
        DataPresentType = 'idobjects'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '-43'
      end
      item
        FieldName = 'smarket_code2'
        DataPresentType = 'idobjects'
        DataPresentParam = '2'
      end>
    Left = 516
    Top = 207
  end
  inherited AddRequest: TWVRequest
    ID = '卡类别设置'
    Bindings = <
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '卡类别'
        FieldName = '卡类别'
      end
      item
        ParamName = '卡成本费'
        FieldName = '卡成本费'
      end
      item
        ParamName = '卡类别名称'
        FieldName = '卡类别名称'
      end
      item
        ParamName = '用途'
        FieldName = '用途'
      end
      item
        ParamName = '能否重用'
        FieldName = '能否重用'
      end
      item
        ParamName = '能否补办'
        FieldName = '能否补办'
      end
      item
        ParamName = '能否挂失'
        FieldName = '能否挂失'
      end
      item
        ParamName = '是否支持多钱包'
        FieldName = '是否支持多钱包'
      end
      item
        ParamName = '使用状态'
        FieldName = '使用状态'
      end
      item
        ParamName = '有效天数'
        FieldName = '有效天数'
      end
      item
        ParamName = '可用的收费类别'
        FieldName = '可用的收费类别'
      end
      item
        ParamName = '默认收费类别'
        FieldName = '默认收费类别'
      end
      item
        ParamName = '是否匿名卡'
        FieldName = '是否匿名卡'
      end
      item
        ParamName = '卡物理类别'
        FieldName = '卡物理类别'
      end
      item
        ParamName = '预存金额'
        FieldName = '预存金额'
      end
      item
        ParamName = '卡限额'
        FieldName = '卡限额'
      end
      item
        ParamName = '单笔限额'
        FieldName = '单笔限额'
      end>
    Left = 512
    Top = 160
  end
  inherited DeleteRequest: TWVRequest
    ID = '卡类别设置'
    Bindings = <
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '卡类别'
        FieldName = '卡类别'
      end
      item
        ParamName = '卡成本费'
        FieldName = '卡成本费'
      end
      item
        ParamName = '卡类别名称'
        FieldName = '卡类别名称'
      end
      item
        ParamName = '用途'
        FieldName = '用途'
      end
      item
        ParamName = '能否重用'
        FieldName = '能否重用'
      end
      item
        ParamName = '能否补办'
        FieldName = '能否补办'
      end
      item
        ParamName = '能否挂失'
        FieldName = '能否挂失'
      end
      item
        ParamName = '是否支持多钱包'
        FieldName = '是否支持多钱包'
      end
      item
        ParamName = '使用状态'
        FieldName = '使用状态'
      end
      item
        ParamName = '有效天数'
        FieldName = '有效天数'
      end
      item
        ParamName = '可用的收费类别'
        FieldName = '可用的收费类别'
      end
      item
        ParamName = '是否匿名卡'
        FieldName = '是否匿名卡'
      end
      item
        ParamName = '默认收费类别'
        FieldName = '默认收费类别'
      end
      item
        ParamName = '卡物理类别'
        FieldName = '卡物理类别'
      end
      item
        ParamName = '预存金额'
        FieldName = '预存金额'
      end
      item
        ParamName = '单笔限额'
        FieldName = '单笔限额'
      end
      item
        ParamName = '卡限额'
        FieldName = '卡限额'
      end>
    Left = 552
    Top = 160
  end
  inherited ChangeRequest: TWVRequest
    ID = '卡类别设置'
    Bindings = <
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '卡类别'
        FieldName = '卡类别'
      end
      item
        ParamName = '卡成本费'
        FieldName = '卡成本费'
      end
      item
        ParamName = '卡类别名称'
        FieldName = '卡类别名称'
      end
      item
        ParamName = '用途'
        FieldName = '用途'
      end
      item
        ParamName = '能否重用'
        FieldName = '能否重用'
      end
      item
        ParamName = '能否补办'
        FieldName = '能否补办'
      end
      item
        ParamName = '能否挂失'
        FieldName = '能否挂失'
      end
      item
        ParamName = '是否支持多钱包'
        FieldName = '是否支持多钱包'
      end
      item
        ParamName = '使用状态'
        FieldName = '使用状态'
      end
      item
        ParamName = '有效天数'
        FieldName = '有效天数'
      end
      item
        ParamName = '可用的收费类别'
        FieldName = '可用的收费类别'
      end
      item
        ParamName = '是否匿名卡'
        FieldName = '是否匿名卡'
      end
      item
        ParamName = '默认收费类别'
        FieldName = '默认收费类别'
      end
      item
        ParamName = '卡物理类别'
        FieldName = '卡物理类别'
      end
      item
        ParamName = '预存金额'
        FieldName = '预存金额'
      end
      item
        ParamName = '卡限额'
        FieldName = '卡限额'
      end
      item
        ParamName = '单笔限额'
        FieldName = '单笔限额'
      end>
    Left = 592
    Top = 160
  end
  inherited WVDataSource: TWVDataSource
    Left = 636
    Top = 207
  end
  inherited alDatasetActions: TActionList
    Left = 596
    Top = 204
  end
end
