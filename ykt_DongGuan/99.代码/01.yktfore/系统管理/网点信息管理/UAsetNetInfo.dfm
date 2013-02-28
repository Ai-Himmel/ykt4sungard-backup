inherited faqhsetNetInfo: TfaqhsetNetInfo
  Width = 706
  Height = 477
  Caption = '网点信息管理'
  inherited pcPages: TRzPageControl
    Width = 706
    Height = 477
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 702
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 436
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 524
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 347
        end
        inherited btnDelete: TBitBtn
          Left = 613
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 104
          Width = 177
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 702
      end
      inherited Grid: TRzDBGrid
        Top = 57
        Width = 702
        Height = 367
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'sbranch_code0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '所在区域'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '镇区'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '网点号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '网点名称'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '网点类型'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '渠道编码'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '银行代码'
            Width = -1
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sbank_acc'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '银行账号'
            Width = -1
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sbankname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '银行帐户名'
            Width = -1
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '联系人'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '电话'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '手机'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '传真'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '地址'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spost_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '邮政编码'
            Width = 60
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 702
        Height = 39
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label1: TLabel
          Left = 18
          Top = 10
          Width = 48
          Height = 12
          Caption = '所在区域'
        end
        object Label5: TLabel
          Left = 242
          Top = 10
          Width = 48
          Height = 12
          Caption = '网点名称'
        end
        object Label6: TLabel
          Left = 442
          Top = 10
          Width = 48
          Height = 12
          Caption = '网点类型'
        end
        object WVEdit5: TWVEdit
          Left = 292
          Top = 6
          Width = 133
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.网点名称>'
          WorkView = WorkView
          FieldName = '查询.网点名称'
        end
        object WVComboBox1: TWVComboBox
          Left = 496
          Top = 6
          Width = 121
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '查询.网点类型'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*107'
        end
        object WVComboBox2: TWVComboBox
          Left = 72
          Top = 6
          Width = 145
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '查询.所在区域'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-28'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label16: TLabel [0]
        Left = 42
        Top = 82
        Width = 48
        Height = 12
        Caption = '所在区域'
      end
      object Label17: TLabel [1]
        Left = 54
        Top = 44
        Width = 36
        Height = 12
        Caption = '网点号'
      end
      object Label20: TLabel [2]
        Left = 252
        Top = 44
        Width = 54
        Height = 12
        Caption = '网点名称*'
      end
      object Label21: TLabel [3]
        Left = 479
        Top = 44
        Width = 54
        Height = 12
        Caption = '网点类型*'
      end
      object Label22: TLabel [4]
        Left = 58
        Top = 348
        Width = 48
        Height = 12
        Caption = '银行代码'
        Visible = False
      end
      object Label23: TLabel [5]
        Left = 274
        Top = 348
        Width = 48
        Height = 12
        Caption = '银行账号'
        Visible = False
      end
      object Label24: TLabel [6]
        Left = 489
        Top = 348
        Width = 60
        Height = 12
        Caption = '银行帐户名'
        Visible = False
      end
      object Label25: TLabel [7]
        Left = 54
        Top = 124
        Width = 36
        Height = 12
        Caption = '联系人'
      end
      object Label26: TLabel [8]
        Left = 282
        Top = 124
        Width = 24
        Height = 12
        Caption = '电话'
      end
      object Label27: TLabel [9]
        Left = 509
        Top = 124
        Width = 24
        Height = 12
        Caption = '手机'
      end
      object Label28: TLabel [10]
        Left = 66
        Top = 164
        Width = 24
        Height = 12
        Caption = '传真'
      end
      object Label29: TLabel [11]
        Left = 66
        Top = 204
        Width = 24
        Height = 12
        Caption = '地址'
      end
      object Label2: TLabel [12]
        Left = 258
        Top = 164
        Width = 48
        Height = 12
        Caption = '邮政编码'
      end
      object Label3: TLabel [13]
        Left = 282
        Top = 82
        Width = 24
        Height = 12
        Caption = '镇区'
      end
      object Label4: TLabel [14]
        Left = 485
        Top = 82
        Width = 48
        Height = 12
        Caption = '渠道编码'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 702
        TabOrder = 16
        inherited btnOK: TBitBtn
          Left = 530
        end
        inherited btnCancel: TBitBtn
          Left = 618
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtNetId: TWVDigitalEdit
        Left = 100
        Top = 40
        Width = 137
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
        FieldName = '站点号'
        SynchronizeByValue = True
      end
      object edtName: TWVEdit
        Left = 317
        Top = 40
        Width = 151
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<网点名称>'
        WorkView = WorkView
        FieldName = '网点名称'
        SynchronizeWhenExit = True
      end
      object WVEdit23: TWVEdit
        Left = 333
        Top = 342
        Width = 151
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 7
        Text = '<银行账号>'
        Visible = False
        WorkView = WorkView
        FieldName = '银行账号'
        SynchronizeWhenExit = True
      end
      object WVEdit24: TWVEdit
        Left = 555
        Top = 342
        Width = 130
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 8
        Text = '<银行帐户名>'
        Visible = False
        WorkView = WorkView
        FieldName = '银行帐户名'
        SynchronizeWhenExit = True
      end
      object WVEdit25: TWVEdit
        Left = 100
        Top = 119
        Width = 137
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 9
        Text = '<联系人>'
        WorkView = WorkView
        FieldName = '联系人'
        SynchronizeWhenExit = True
      end
      object WVEdit26: TWVEdit
        Left = 317
        Top = 119
        Width = 151
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 10
        Text = '<电话>'
        WorkView = WorkView
        FieldName = '电话'
        SynchronizeWhenExit = True
      end
      object WVEdit27: TWVEdit
        Left = 539
        Top = 119
        Width = 130
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 11
        Text = '<手机>'
        WorkView = WorkView
        FieldName = '手机'
        SynchronizeWhenExit = True
      end
      object WVEdit28: TWVEdit
        Left = 100
        Top = 160
        Width = 137
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 12
        Text = '<传真>'
        WorkView = WorkView
        FieldName = '传真'
        SynchronizeWhenExit = True
      end
      object WVEdit29: TWVEdit
        Left = 100
        Top = 200
        Width = 368
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 14
        Text = '<地址>'
        WorkView = WorkView
        FieldName = '地址'
        SynchronizeWhenExit = True
      end
      object WVComboBox4: TWVComboBox
        Left = 100
        Top = 78
        Width = 137
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView
        FieldName = '所在区域'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-28'
      end
      object cbbNetType: TWVComboBox
        Left = 539
        Top = 38
        Width = 130
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 2
        WorkView = WorkView
        FieldName = '网点类型'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*107'
      end
      object WVComboBox3: TWVComboBox
        Left = 116
        Top = 342
        Width = 137
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 6
        Visible = False
        WorkView = WorkView
        FieldName = '银行代码'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*218'
      end
      object cbbNetId: TWVComboBox
        Left = 83
        Top = 318
        Width = 130
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 15
        Visible = False
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-2'
      end
      object WVEdit1: TWVEdit
        Left = 317
        Top = 160
        Width = 151
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 13
        Text = '<邮政编码>'
        WorkView = WorkView
        FieldName = '邮政编码'
        SynchronizeWhenExit = True
      end
      object WVComboBox5: TWVComboBox
        Left = 317
        Top = 78
        Width = 151
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 4
        WorkView = WorkView
        FieldName = '镇区'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*231'
      end
      object WVEdit2: TWVEdit
        Left = 539
        Top = 78
        Width = 130
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 5
        Text = '<渠道编码>'
        WorkView = WorkView
        FieldName = '渠道编码'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 356
    Top = 351
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
        Name = '查询.所在区域'
        Caption = '查询.所在区域'
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
        Name = '查询.站点号'
        Caption = '查询.站点号'
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
        Name = '查询.操作员'
        Caption = '查询.操作员'
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
        Name = '查询.网点名称'
        Caption = '查询.网点名称'
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
        Name = '查询.网点类型'
        Caption = '查询.网点类型'
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
        Name = '查询.银行代码'
        Caption = '查询.银行代码'
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
        Name = '查询.银行帐户名'
        Caption = '查询.银行帐户名'
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
        Name = '查询.联系人'
        Caption = '查询.联系人'
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
        Name = '查询.电话'
        Caption = '查询.电话'
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
        Name = '查询.手机'
        Caption = '查询.手机'
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
        Name = '查询.传真'
        Caption = '查询.传真'
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
        Name = '查询.地址'
        Caption = '查询.地址'
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
        Name = '查询.邮政编码'
        Caption = '查询.邮政编码'
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
        Name = '所在区域'
        Caption = '所在区域'
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
        DataField = 'sbranch_code0'
      end
      item
        Name = '站点号'
        Caption = '站点号'
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
        DataField = 'lbank_acc_type2'
      end
      item
        Name = '操作员'
        Caption = '操作员'
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
        DataField = 'semp_no'
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
        DataField = 'sstatus0'
      end
      item
        Name = '网点名称'
        Caption = '网点名称'
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
        DataField = 'vsvarstr2'
      end
      item
        Name = '网点类型'
        Caption = '网点类型'
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
        Name = '银行代码'
        Caption = '银行代码'
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
        DataField = 'sbank_code'
      end
      item
        Name = '银行账号'
        Caption = '银行账号'
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
        DataField = 'sbank_acc'
      end
      item
        Name = '银行帐户名'
        Caption = '银行帐户名'
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
        Name = '联系人'
        Caption = '联系人'
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
        Name = '电话'
        Caption = '电话'
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
        DataField = 'sphone'
      end
      item
        Name = '手机'
        Caption = '手机'
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
        DataField = 'sphone2'
      end
      item
        Name = '传真'
        Caption = '传真'
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
        DataField = 'sphone3'
      end
      item
        Name = '地址'
        Caption = '地址'
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
        Name = '邮政编码'
        Caption = '邮政编码'
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
        DataField = 'spost_code'
      end
      item
        Name = '渠道编码'
        Caption = '渠道编码'
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
        DataField = 'snote'
      end
      item
        Name = '镇区'
        Caption = '镇区'
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
        DataField = 'snote2'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.所在区域|查询.站点号|查询.操作员|查询.交易类型|查询.网点名' +
          '称|查询.网点类型|查询.银行代码|查询.银行账号|查询.银行帐户名|查' +
          '询.联系人|查询.电话|查询.手机|查询.传真|查询.地址|查询.邮政编码|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|所在区域|站点号|操作员|交易类型|网点名称|网点类型|银行代码|银行' +
          '账号|银行帐户名|联系人|电话|手机|传真|地址|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 280
    Top = 312
  end
  inherited QueryRequest: TWVRequest
    ID = '网点信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '所在区域'
        FieldName = '查询.所在区域'
      end
      item
        ParamName = '站点号'
        FieldName = '查询.站点号'
      end
      item
        ParamName = '操作员'
        FieldName = '查询.操作员'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '网点名称'
        FieldName = '查询.网点名称'
      end
      item
        ParamName = '网点类型'
        FieldName = '查询.网点类型'
      end
      item
        ParamName = '银行代码'
        FieldName = '查询.银行代码'
      end
      item
        ParamName = '银行账号'
        FieldName = '查询.银行账号'
      end
      item
        ParamName = '银行帐户名'
        FieldName = '查询.银行帐户名'
      end
      item
        ParamName = '联系人'
        FieldName = '查询.联系人'
      end
      item
        ParamName = '电话'
        FieldName = '查询.电话'
      end
      item
        ParamName = '手机'
        FieldName = '查询.手机'
      end
      item
        ParamName = '传真'
        FieldName = '查询.传真'
      end
      item
        ParamName = '地址'
        FieldName = '查询.地址'
      end
      item
        ParamName = '邮政编码'
        FieldName = '查询.邮政编码'
      end>
    Left = 440
    Top = 312
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '107'
      end
      item
        FieldName = 'sbank_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '218'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'idobjects'
        DataPresentParam = '-28'
      end
      item
        FieldName = 'snote2'
        DataPresentType = 'idobjects'
        DataPresentParam = '231'
      end>
    Left = 316
    Top = 351
  end
  inherited AddRequest: TWVRequest
    ID = '网点信息管理'
    Bindings = <
      item
        ParamName = '所在区域'
        FieldName = '所在区域'
      end
      item
        ParamName = '站点号'
        FieldName = '站点号'
      end
      item
        ParamName = '操作员'
        FieldName = '操作员'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '网点名称'
        FieldName = '网点名称'
      end
      item
        ParamName = '网点类型'
        FieldName = '网点类型'
      end
      item
        ParamName = '银行代码'
        FieldName = '银行代码'
      end
      item
        ParamName = '银行账号'
        FieldName = '银行账号'
      end
      item
        ParamName = '银行帐户名'
        FieldName = '银行帐户名'
      end
      item
        ParamName = '联系人'
        FieldName = '联系人'
      end
      item
        ParamName = '电话'
        FieldName = '电话'
      end
      item
        ParamName = '手机'
        FieldName = '手机'
      end
      item
        ParamName = '传真'
        FieldName = '传真'
      end
      item
        ParamName = '地址'
        FieldName = '地址'
      end
      item
        ParamName = '邮政编码'
        FieldName = '邮政编码'
      end
      item
        ParamName = '渠道编码'
        FieldName = '渠道编码'
      end
      item
        ParamName = '镇区'
        FieldName = '镇区'
      end>
    Left = 320
    Top = 312
  end
  inherited DeleteRequest: TWVRequest
    ID = '网点信息管理'
    Bindings = <
      item
        ParamName = '所在区域'
        FieldName = '所在区域'
      end
      item
        ParamName = '站点号'
        FieldName = '站点号'
      end
      item
        ParamName = '操作员'
        FieldName = '操作员'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '网点名称'
        FieldName = '网点名称'
      end
      item
        ParamName = '网点类型'
        FieldName = '网点类型'
      end
      item
        ParamName = '银行代码'
        FieldName = '银行代码'
      end
      item
        ParamName = '银行账号'
        FieldName = '银行账号'
      end
      item
        ParamName = '银行帐户名'
        FieldName = '银行帐户名'
      end
      item
        ParamName = '联系人'
        FieldName = '联系人'
      end
      item
        ParamName = '电话'
        FieldName = '电话'
      end
      item
        ParamName = '手机'
        FieldName = '手机'
      end
      item
        ParamName = '传真'
        FieldName = '传真'
      end
      item
        ParamName = '地址'
        FieldName = '地址'
      end
      item
        ParamName = '邮政编码'
        FieldName = '邮政编码'
      end
      item
        ParamName = '渠道编码'
        FieldName = '渠道编码'
      end
      item
        ParamName = '镇区'
        FieldName = '镇区'
      end>
    Left = 360
    Top = 312
  end
  inherited ChangeRequest: TWVRequest
    ID = '网点信息管理'
    Bindings = <
      item
        ParamName = '所在区域'
        FieldName = '所在区域'
      end
      item
        ParamName = '站点号'
        FieldName = '站点号'
      end
      item
        ParamName = '操作员'
        FieldName = '操作员'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '网点名称'
        FieldName = '网点名称'
      end
      item
        ParamName = '网点类型'
        FieldName = '网点类型'
      end
      item
        ParamName = '银行代码'
        FieldName = '银行代码'
      end
      item
        ParamName = '银行账号'
        FieldName = '银行账号'
      end
      item
        ParamName = '银行帐户名'
        FieldName = '银行帐户名'
      end
      item
        ParamName = '联系人'
        FieldName = '联系人'
      end
      item
        ParamName = '电话'
        FieldName = '电话'
      end
      item
        ParamName = '手机'
        FieldName = '手机'
      end
      item
        ParamName = '传真'
        FieldName = '传真'
      end
      item
        ParamName = '地址'
        FieldName = '地址'
      end
      item
        ParamName = '邮政编码'
        FieldName = '邮政编码'
      end
      item
        ParamName = '渠道编码'
        FieldName = '渠道编码'
      end
      item
        ParamName = '镇区'
        FieldName = '镇区'
      end>
    Left = 400
    Top = 312
  end
  inherited WVDataSource: TWVDataSource
    Left = 436
    Top = 351
  end
  inherited alDatasetActions: TActionList
    Left = 396
    Top = 348
  end
end
