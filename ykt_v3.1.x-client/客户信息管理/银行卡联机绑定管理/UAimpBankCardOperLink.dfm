inherited faqhimpBankCardOperLink: TfaqhimpBankCardOperLink
  Width = 873
  Height = 477
  Caption = '客户导入管理'
  inherited pcPages: TRzPageControl
    Width = 873
    Height = 477
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 869
        TabOrder = 3
        object Label10: TLabel [0]
          Left = 94
          Top = 9
          Width = 36
          Height = 12
          Caption = '批次号'
        end
        inherited btnAdd: TBitBtn [1]
          Left = 528
          Enabled = False
        end
        inherited btnChange: TBitBtn [2]
          Left = 614
          Enabled = False
        end
        inherited btnQuery: TBitBtn [3]
          Left = 442
        end
        inherited btnDelete: TBitBtn
          Left = 701
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 0
          Width = 161
          TabOrder = 7
          Visible = False
        end
        object btnPatchDel: TBitBtn
          Left = 787
          Top = 3
          Width = 79
          Height = 25
          Hint = '删除当前选中的条目'
          Anchors = [akTop, akRight]
          Caption = '批量删除'
          Enabled = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
          OnClick = btnPatchDelClick
        end
        object edtDelPatchNo: TWVEdit
          Left = 135
          Top = 5
          Width = 98
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 6
          Text = '<批次号>'
          WorkView = WorkView1
          FieldName = '批次号'
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 869
      end
      inherited Grid: TRzDBGrid
        Top = 73
        Width = 869
        Height = 351
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'Sname2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '记录号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '导入批次号'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '操作员'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '客户号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spager'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '学/工号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '客户姓名'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Scard0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '银行卡号'
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '操作类型'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '增删标志'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lsafe_level2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '处理状态'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '备注'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '绑定日期'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'Sbank_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '银行代码'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sbranch_code0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '所属区域'
            Visible = False
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 869
        Height = 55
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label3: TLabel
          Left = 414
          Top = 10
          Width = 36
          Height = 12
          Caption = '批次号'
        end
        object Label6: TLabel
          Left = 40
          Top = 10
          Width = 42
          Height = 12
          Caption = '学/工号'
        end
        object Label8: TLabel
          Left = 218
          Top = 34
          Width = 48
          Height = 12
          Caption = '处理状态'
        end
        object Label9: TLabel
          Left = 218
          Top = 10
          Width = 48
          Height = 12
          Caption = '客户姓名'
        end
        object Label11: TLabel
          Left = 578
          Top = 34
          Width = 48
          Height = 12
          Caption = '银行代码'
          Visible = False
        end
        object Label13: TLabel
          Left = 34
          Top = 34
          Width = 48
          Height = 12
          Caption = '银行卡号'
        end
        object Label7: TLabel
          Left = 590
          Top = 10
          Width = 36
          Height = 12
          Caption = '客户号'
        end
        object WVEdit3: TWVEdit
          Left = 460
          Top = 6
          Width = 125
          Height = 20
          Color = clBtnHighlight
          MaxLength = 50
          ReadOnly = False
          TabOrder = 2
          Text = '<查询.批次号>'
          WorkView = WorkView
          FieldName = '查询.批次号'
        end
        object WVEdit6: TWVEdit
          Left = 92
          Top = 6
          Width = 119
          Height = 20
          CharCase = ecUpperCase
          Color = clBtnHighlight
          MaxLength = 50
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.学工号>'
          WorkView = WorkView
          FieldName = '查询.学工号'
        end
        object WVEdit9: TWVEdit
          Left = 276
          Top = 6
          Width = 118
          Height = 20
          Color = clBtnHighlight
          MaxLength = 50
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.客户姓名>'
          WorkView = WorkView
          FieldName = '查询.客户姓名'
        end
        object WVEdit13: TWVEdit
          Left = 92
          Top = 30
          Width = 119
          Height = 20
          Color = clBtnHighlight
          MaxLength = 50
          ReadOnly = False
          TabOrder = 4
          Text = '<查询.银行卡号>'
          WorkView = WorkView
          FieldName = '查询.银行卡号'
        end
        object cbbQFeeType: TWVComboBox
          Left = 276
          Top = 32
          Width = 118
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          ItemHeight = 12
          TabOrder = 6
          WorkView = WorkView
          FieldName = '查询.绑定状态'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*10'
        end
        object WVComboBox7: TWVComboBox
          Left = 636
          Top = 31
          Width = 118
          Height = 18
          Style = csOwnerDrawFixed
          Color = clBtnHighlight
          ItemHeight = 12
          TabOrder = 5
          Visible = False
          WorkView = WorkView
          FieldName = '查询.银行代码'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*110'
        end
        object edtCustNo: TWVEdit
          Left = 636
          Top = 6
          Width = 123
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 3
          Text = '<查询.客户号>'
          WorkView = WorkView
          FieldName = '查询.客户号'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label1: TLabel [0]
        Left = 84
        Top = 68
        Width = 36
        Height = 12
        Caption = '记录号'
      end
      object Label21: TLabel [1]
        Left = 78
        Top = 100
        Width = 42
        Height = 12
        Caption = '学/工号'
      end
      object Label32: TLabel [2]
        Left = 62
        Top = 421
        Width = 48
        Height = 12
        Caption = '客户号 *'
        Visible = False
      end
      object Label2: TLabel [3]
        Left = 72
        Top = 132
        Width = 48
        Height = 12
        Caption = '银行卡号'
      end
      object Label12: TLabel [4]
        Left = 84
        Top = 164
        Width = 36
        Height = 12
        Caption = '批次号'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 869
        TabOrder = 4
        inherited btnOK: TBitBtn
          Left = 697
        end
        inherited btnCancel: TBitBtn
          Left = 785
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtCustId: TWVEdit
        Left = 129
        Top = 64
        Width = 159
        Height = 20
        ParentColor = True
        ReadOnly = True
        TabOrder = 0
        Text = '<记录号>'
        WorkView = WorkView
        FieldName = '记录号'
        SynchronizeWhenExit = True
      end
      object edtStuempNo: TWVEdit
        Left = 129
        Top = 95
        Width = 159
        Height = 20
        CharCase = ecUpperCase
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<学工号>'
        WorkView = WorkView
        FieldName = '学工号'
        SynchronizeWhenExit = True
      end
      object edtOldBankCardNo: TWVEdit
        Left = 129
        Top = 127
        Width = 159
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 2
        Text = '<银行卡号>'
        WorkView = WorkView
        FieldName = '银行卡号'
        SynchronizeWhenExit = True
      end
      object WVEdit1: TWVEdit
        Left = 129
        Top = 159
        Width = 159
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 3
        Text = '<批次号>'
        WorkView = WorkView
        FieldName = '批次号'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 364
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
        GroupIndex = 1
        DataField = '@Dataset'
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
        Name = '操作标志'
        Caption = '操作标志'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.批次号'
        Caption = '查询.批次号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.客户号'
        Caption = '查询.客户号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
      end
      item
        Name = '查询.学工号'
        Caption = '查询.学工号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.客户姓名'
        Caption = '查询.客户姓名'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.银行卡号'
        Caption = '查询.银行卡号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
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
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.绑定状态'
        Caption = '查询.绑定状态'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '记录号'
        Caption = '记录号'
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
        GroupIndex = 1
        DataField = 'sname2'
      end
      item
        Name = '学工号'
        Caption = '学工号'
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
        DataField = 'spager'
      end
      item
        Name = '银行卡号'
        Caption = '银行卡号'
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
        DataField = 'Scard0'
      end
      item
        Name = '批次号'
        Caption = '批次号'
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
        DataField = 'scust_limit'
      end>
    InvalidColor = clBtnHighlight
    Left = 336
    Top = 248
  end
  inherited QueryRequest: TWVRequest
    ID = '银行卡绑定查询联机'
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
        ParamName = '绑定状态'
        FieldName = '查询.绑定状态'
      end
      item
        ParamName = '批次号'
        FieldName = '查询.批次号'
      end
      item
        ParamName = '客户姓名'
        FieldName = '查询.客户姓名'
      end
      item
        ParamName = '学工号'
        FieldName = '查询.学工号'
      end
      item
        ParamName = '银行代码'
        FieldName = '查询.银行代码'
      end
      item
        ParamName = '银行卡号'
        FieldName = '查询.银行卡号'
      end
      item
        ParamName = '客户号'
        FieldName = '查询.客户号'
      end>
    Left = 464
    Top = 248
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'sbank_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '110'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '33'
      end
      item
        FieldName = 'Lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '44'
      end
      item
        FieldName = 'lsafe_level2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '10'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-30'
      end>
    Left = 396
  end
  inherited AddRequest: TWVRequest
    ID = '导入银行卡管理联机'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '记录号'
        FieldName = '记录号'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '银行卡号'
        FieldName = '银行卡号'
      end
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end>
    Left = 368
    Top = 248
  end
  inherited DeleteRequest: TWVRequest
    ID = '导入银行卡管理联机'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '记录号'
        FieldName = '记录号'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '银行卡号'
        FieldName = '银行卡号'
      end
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end>
    Left = 400
    Top = 248
  end
  inherited ChangeRequest: TWVRequest
    ID = '导入银行卡管理联机'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '记录号'
        FieldName = '记录号'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '银行卡号'
        FieldName = '银行卡号'
      end
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end>
    Left = 432
    Top = 248
  end
  inherited WVDataSource: TWVDataSource
    Left = 468
  end
  inherited alDatasetActions: TActionList
    Left = 428
    Top = 284
  end
  object WorkView1: TWorkView
    WorkFields = <
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
        GroupIndex = 1
      end
      item
        Name = '批次号'
        Caption = '批次号'
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
        DataField = 'scust_limit'
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
        Name = '批量标志'
        Caption = '批量标志'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.操作标志|查询.导入批次号|查询.导入顺序号|查询.记录号|查询.' +
          '设备编号|查询.设备物理编号|查询.设备名称|查询.商户编号|查询.商户' +
          '名称|查询.开始时间|查询.结束时间|查询.启用日期|查询.停用日期|查' +
          '询.备注|'
      end
      item
        MonitorValueChangedFields = 
          '|导入批次号|导入顺序号|记录号|设备编号|设备物理编号|设备名称|商' +
          '户编号|商户名称|开始时间|结束时间|启用日期|停用日期|'
      end>
    Left = 336
    Top = 328
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '银行卡批量删除联机'
    Bindings = <
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '批量标志'
        FieldName = '批量标志'
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
    AfterExec = CheckReturnData
    Left = 368
    Top = 328
  end
end
