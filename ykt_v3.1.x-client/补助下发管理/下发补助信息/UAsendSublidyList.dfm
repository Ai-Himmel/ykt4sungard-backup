inherited faqhsendSublidyList: TfaqhsendSublidyList
  Width = 756
  Height = 455
  inherited UIPanel1: TUIPanel
    Top = 354
    Width = 756
    Height = 101
    TabOrder = 3
    object Label10: TLabel [0]
      Left = 30
      Top = 9
      Width = 60
      Height = 12
      Caption = '导入批次号'
    end
    object Label11: TLabel [1]
      Left = 66
      Top = 57
      Width = 24
      Height = 12
      Caption = '摘要'
    end
    object Label12: TLabel [2]
      Left = 224
      Top = 9
      Width = 48
      Height = 12
      Caption = '付款方式'
    end
    object Label13: TLabel [3]
      Left = 398
      Top = 9
      Width = 48
      Height = 12
      Caption = '票据号码'
    end
    object Label14: TLabel [4]
      Left = 30
      Top = 33
      Width = 60
      Height = 12
      Caption = '补助总人数'
    end
    object Label15: TLabel [5]
      Left = 212
      Top = 33
      Width = 60
      Height = 12
      Caption = '补助总金额'
    end
    object Label16: TLabel [6]
      Left = 576
      Top = 9
      Width = 48
      Height = 12
      Caption = '补助标志'
      Visible = False
    end
    object RzStatusPane1: TRzStatusPane [7]
      Left = 0
      Top = 80
      Width = 756
      Height = 21
      FrameStyle = fsStatus
      Align = alBottom
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
    end
    object Label1: TLabel [8]
      Left = 388
      Top = 33
      Width = 60
      Height = 12
      Caption = '操作员密码'
    end
    inherited btnQuery: TBitBtn
      Left = 575
      Top = 52
      Enabled = False
      TabOrder = 7
    end
    inherited btnPrint: TBitBtn
      Left = 666
      Top = 52
      Hint = '下发补助'
      Caption = '下发补助'
      TabOrder = 8
      Glyph.Data = {00000000}
    end
    object edtPNo: TWVEdit
      Left = 92
      Top = 5
      Width = 100
      Height = 20
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 0
      Text = '<导入批次号>'
      WorkView = WorkView1
      FieldName = '导入批次号'
    end
    object edtInfo: TWVEdit
      Left = 92
      Top = 53
      Width = 461
      Height = 20
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 9
      Text = '<摘要>'
      WorkView = WorkView1
      FieldName = '摘要'
    end
    object cbbFeeType: TWVComboBox
      Left = 277
      Top = 5
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clBtnHighlight
      ItemHeight = 12
      TabOrder = 1
      OnChange = cbbFeeTypeChange
      WorkView = WorkView1
      FieldName = '付款方式'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*63'
    end
    object edtTicketNo: TWVEdit
      Left = 452
      Top = 5
      Width = 100
      Height = 20
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 2
      Text = '<票据号码>'
      WorkView = WorkView1
      FieldName = '票据号码'
    end
    object edtNum: TWVEdit
      Left = 92
      Top = 29
      Width = 100
      Height = 20
      Color = clBtnHighlight
      MaxLength = 22
      ReadOnly = False
      TabOrder = 4
      Text = '<补助总人数>'
      WorkView = WorkView1
      FieldName = '补助总人数'
    end
    object edtMoney: TWVEdit
      Left = 276
      Top = 29
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 5
    end
    object cbbFlag: TWVComboBox
      Left = 629
      Top = 5
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clBtnHighlight
      ItemHeight = 12
      TabOrder = 3
      Visible = False
      WorkView = WorkView1
      FieldName = '补助标志'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*77'
    end
    object edtPwd: TWVEdit
      Left = 452
      Top = 29
      Width = 100
      Height = 20
      Color = clBtnHighlight
      PasswordChar = '*'
      ReadOnly = False
      TabOrder = 6
      WorkView = WorkView1
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 756
    TabOrder = 2
    inherited Image1: TImage
      Width = 756
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 756
    Height = 79
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object Label4: TLabel
      Left = 448
      Top = 10
      Width = 42
      Height = 12
      Caption = '学/工号'
    end
    object Label7: TLabel
      Left = 66
      Top = 34
      Width = 24
      Height = 12
      Caption = '卡号'
    end
    object Label2: TLabel
      Left = 30
      Top = 9
      Width = 60
      Height = 12
      Caption = '导入批次号'
    end
    object Label5: TLabel
      Left = 254
      Top = 10
      Width = 36
      Height = 12
      Caption = '客户号'
    end
    object Label3: TLabel
      Left = 466
      Top = 34
      Width = 24
      Height = 12
      Caption = '状态'
    end
    object Label6: TLabel
      Left = 230
      Top = 34
      Width = 60
      Height = 12
      Caption = '补助批次号'
    end
    object lbl1: TLabel
      Left = 42
      Top = 57
      Width = 48
      Height = 12
      Caption = '所属部门'
    end
    object Label8: TLabel
      Left = 442
      Top = 58
      Width = 48
      Height = 12
      Caption = '审核状态'
    end
    object WVEdit4: TWVEdit
      Left = 500
      Top = 6
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<查询.学工号>'
      WorkView = WorkView
      FieldName = '查询.学工号'
    end
    object edtCardId: TWVEdit
      Left = 100
      Top = 29
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 3
      Text = '<查询.卡号>'
      WorkView = WorkView
      FieldName = '查询.卡号'
    end
    object WVEdit2: TWVEdit
      Left = 100
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<查询.导入批次号>'
      WorkView = WorkView
      FieldName = '查询.导入批次号'
    end
    object edtCustNo: TWVEdit
      Left = 300
      Top = 6
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<查询.客户号>'
      WorkView = WorkView
      FieldName = '查询.客户号'
    end
    object cbbType: TWVComboBox
      Left = 501
      Top = 29
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 4
      WorkView = WorkView
      FieldName = '查询.状态'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*76'
    end
    object edtPatchNo: TWVEdit
      Left = 300
      Top = 30
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 5
      Text = '<查询.补助批次号>'
      WorkView = WorkView
      FieldName = '查询.补助批次号'
    end
    object cbbDept: TWVComboBox
      Left = 100
      Top = 53
      Width = 301
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 20
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView
      FieldName = '部门'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object WVComboBox1: TWVComboBox
      Left = 501
      Top = 53
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView
      FieldName = '审核状态'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*160'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 97
    Width = 756
    Height = 257
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Width = 756
      Height = 257
      Columns = <
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
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '顺序号'
          Width = 40
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = '客户号'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '学/工号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '姓名'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol10'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '补助批次号'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smain_flag'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '补助类型'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '补助金额'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '状态'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lsafe_level2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '审核状态'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '错误信息'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '导入日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '导入时间'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '发生日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '发生时间'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '领取日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '领取时间'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '摘要'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol11'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '卡号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '经办人姓名'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '经办人身份证号'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '票据类型'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '票据号码'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semp_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '导入操作员'
          Width = 60
          Visible = True
        end>
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
        Name = '交易类型'
        Caption = '交易类型'
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
        Name = '查询.导入批次号'
        Caption = '查询.导入批次号'
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
        Name = '查询.状态'
        Caption = '查询.状态'
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
        Name = '查询.学工号'
        Caption = '查询.学工号'
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
      end
      item
        Name = '查询.补助批次号'
        Caption = '查询.补助批次号'
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
        Name = '查询.卡号'
        Caption = '查询.卡号'
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
        Name = '部门'
        Caption = '部门'
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
        Name = '审核状态'
        Caption = '审核状态'
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
        MonitorValueChangedFields = '|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 108
    Top = 191
  end
  inherited MainRequest: TWVRequest
    ID = '补助信息查询'
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
        ParamName = '补助批次号'
        FieldName = '查询.补助批次号'
      end
      item
        ParamName = '导入批次号'
        FieldName = '查询.导入批次号'
      end
      item
        ParamName = '卡号'
        FieldName = '查询.卡号'
      end
      item
        ParamName = '状态'
        FieldName = '查询.状态'
      end
      item
        ParamName = '客户号'
        FieldName = '查询.客户号'
      end
      item
        ParamName = '学工号'
        FieldName = '查询.学工号'
      end
      item
        ParamName = '部门'
        FieldName = '部门'
      end
      item
        ParamName = '审核状态'
        FieldName = '审核状态'
      end>
    Left = 152
    Top = 192
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '63'
      end
      item
        FieldName = 'scust_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '76'
      end
      item
        FieldName = 'smain_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '77'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'lsafe_level2'
        DataPresentType = 'idobjects'
        DataPresentParam = '160'
      end>
    Left = 192
    Top = 192
  end
  inherited DataSource: TDataSource
    Left = 224
    Top = 192
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
        Name = '导入批次号'
        Caption = '导入批次号'
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
        Name = '摘要'
        Caption = '摘要'
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
        Name = '付款方式'
        Caption = '付款方式'
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
        Name = '票据号码'
        Caption = '票据号码'
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
        Name = '补助总人数'
        Caption = '补助总人数'
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
        Name = '补助总金额'
        Caption = '补助总金额'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = -999999
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '经办人身份证号'
        Caption = '经办人身份证号'
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
        Name = '经办人姓名'
        Caption = '经办人姓名'
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
        Name = '补助标志'
        Caption = '补助标志'
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
        Name = '密码'
        Caption = '密码'
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
        MonitorValueChangedFields = '|'
      end>
    InvalidColor = clBtnHighlight
    Left = 108
    Top = 239
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '下发'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
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
      end
      item
        ParamName = '导入批次号'
        FieldName = '导入批次号'
      end
      item
        ParamName = '摘要'
        FieldName = '摘要'
      end
      item
        ParamName = '付款方式'
        FieldName = '付款方式'
      end
      item
        ParamName = '票据号码'
        FieldName = '票据号码'
      end
      item
        ParamName = '补助总人数'
        FieldName = '补助总人数'
      end
      item
        ParamName = '补助总金额'
        FieldName = '补助总金额'
      end
      item
        ParamName = '经办人身份证号'
        FieldName = '经办人身份证号'
      end
      item
        ParamName = '经办人姓名'
        FieldName = '经办人姓名'
      end
      item
        ParamName = '补助标志'
        FieldName = '补助标志'
      end
      item
        ParamName = '密码'
        FieldName = '密码'
      end>
    AfterExec = MainRequestAfterExec
    Left = 152
    Top = 240
  end
end
