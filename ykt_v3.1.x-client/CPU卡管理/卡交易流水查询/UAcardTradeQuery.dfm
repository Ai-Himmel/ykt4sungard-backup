inherited faqhcardTradeQuery: TfaqhcardTradeQuery
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 523
      TabOrder = 1
    end
    inherited btnPrint: TBitBtn
      Left = 610
      TabOrder = 2
    end
    object btnReadCard: TBitBtn
      Left = 435
      Top = 3
      Width = 79
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '读卡查询'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnReadCardClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    TabOrder = 2
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 151
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object Label1: TLabel
      Left = 18
      Top = 33
      Width = 72
      Height = 12
      Caption = '记账开始日期'
    end
    object Label2: TLabel
      Left = 218
      Top = 33
      Width = 72
      Height = 12
      Caption = '记账结束日期'
    end
    object Label3: TLabel
      Left = 424
      Top = 83
      Width = 48
      Height = 12
      Caption = '终端编号'
    end
    object Label4: TLabel
      Left = 30
      Top = 81
      Width = 60
      Height = 12
      Caption = '终端流水号'
    end
    object Label5: TLabel
      Left = 436
      Top = 35
      Width = 36
      Height = 12
      Caption = '交易码'
    end
    object Label6: TLabel
      Left = 242
      Top = 81
      Width = 48
      Height = 12
      Caption = '凭证号码'
    end
    object Label7: TLabel
      Left = 54
      Top = 105
      Width = 36
      Height = 12
      Caption = '客户号'
    end
    object Label8: TLabel
      Left = 248
      Top = 105
      Width = 42
      Height = 12
      Caption = '学/工号'
    end
    object Label9: TLabel
      Left = 424
      Top = 59
      Width = 48
      Height = 12
      Caption = '显示卡号'
    end
    object Label10: TLabel
      Left = 66
      Top = 129
      Width = 24
      Height = 12
      Caption = '卡号'
    end
    object Label11: TLabel
      Left = 436
      Top = 11
      Width = 36
      Height = 12
      Caption = '操作员'
    end
    object Label12: TLabel
      Left = 242
      Top = 129
      Width = 48
      Height = 12
      Caption = '流水状态'
    end
    object Label13: TLabel
      Left = 18
      Top = 9
      Width = 72
      Height = 12
      Caption = '交易开始日期'
    end
    object Label14: TLabel
      Left = 218
      Top = 9
      Width = 72
      Height = 12
      Caption = '交易结束日期'
    end
    object Label15: TLabel
      Left = 424
      Top = 106
      Width = 48
      Height = 12
      Caption = '联机状态'
    end
    object Label16: TLabel
      Left = 42
      Top = 57
      Width = 48
      Height = 12
      Caption = '开始时间'
    end
    object Label17: TLabel
      Left = 242
      Top = 57
      Width = 48
      Height = 12
      Caption = '结束时间'
    end
    object lbl1: TLabel
      Left = 200
      Top = 300
      Width = 48
      Height = 12
      Caption = '交易标志'
      Visible = False
    end
    object Label18: TLabel
      Left = 426
      Top = 128
      Width = 48
      Height = 12
      Caption = '外部类型'
    end
    object edtBDate: TWVEdit
      Left = 100
      Top = 29
      Width = 110
      Height = 20
      Color = clInfoBk
      MaxLength = 8
      ReadOnly = False
      TabOrder = 3
      Text = '<开始日期>'
      WorkView = WorkView
      FieldName = '开始日期'
    end
    object edtEDate: TWVEdit
      Left = 298
      Top = 29
      Width = 110
      Height = 20
      Color = clInfoBk
      MaxLength = 8
      ReadOnly = False
      TabOrder = 4
      Text = '<截止日期>'
      WorkView = WorkView
      FieldName = '截止日期'
    end
    object edtSeriNo: TWVEdit
      Left = 100
      Top = 77
      Width = 110
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 9
      Text = '<终端流水号>'
      WorkView = WorkView
      FieldName = '终端流水号'
    end
    object WVEdit6: TWVEdit
      Left = 298
      Top = 77
      Width = 110
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 10
      Text = '<凭证号码>'
      WorkView = WorkView
      FieldName = '凭证号码'
    end
    object edtCustNo: TWVEdit
      Left = 100
      Top = 101
      Width = 110
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 13
      Text = '<客户号>'
      WorkView = WorkView
      FieldName = '客户号'
    end
    object WVEdit8: TWVEdit
      Left = 298
      Top = 100
      Width = 110
      Height = 20
      CharCase = ecUpperCase
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 12
      Text = '<学/工号>'
      WorkView = WorkView
      FieldName = '学/工号'
    end
    object WVEdit9: TWVEdit
      Left = 480
      Top = 55
      Width = 159
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 8
      Text = '<显示卡号>'
      WorkView = WorkView
      FieldName = '显示卡号'
    end
    object edtCardNo: TWVEdit
      Left = 100
      Top = 125
      Width = 110
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 16
      Text = '<卡号>'
      WorkView = WorkView
      FieldName = '卡号'
    end
    object WVComboBox3: TWVComboBox
      Left = 480
      Top = 79
      Width = 159
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 11
      WorkView = WorkView
      FieldName = '终端编号'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-9'
    end
    object WVComboBox1: TWVComboBox
      Left = 480
      Top = 30
      Width = 159
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '交易码'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-15'
    end
    object WVComboBox2: TWVComboBox
      Left = 480
      Top = 5
      Width = 159
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      WorkView = WorkView
      FieldName = '操作员'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-30'
    end
    object WVComboBox4: TWVComboBox
      Left = 298
      Top = 123
      Width = 110
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 15
      WorkView = WorkView
      FieldName = '流水状态'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*3'
    end
    object edtTBDate: TWVEdit
      Left = 100
      Top = 5
      Width = 110
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<交易开始日期>'
      WorkView = WorkView
      FieldName = '交易开始日期'
    end
    object edtTEDate: TWVEdit
      Left = 298
      Top = 5
      Width = 110
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<交易结束日期>'
      WorkView = WorkView
      FieldName = '交易结束日期'
    end
    object cbbNetConn: TWVComboBox
      Left = 480
      Top = 102
      Width = 159
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 14
      WorkView = WorkView
      FieldName = '联机状态'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*139'
    end
    object edtBTime: TWVEdit
      Left = 100
      Top = 53
      Width = 110
      Height = 20
      Color = clWhite
      MaxLength = 6
      ReadOnly = False
      TabOrder = 6
      Text = '<开始时间>'
      WorkView = WorkView
      FieldName = '开始时间'
    end
    object edtEtime: TWVEdit
      Left = 298
      Top = 53
      Width = 110
      Height = 20
      Color = clWhite
      MaxLength = 6
      ReadOnly = False
      TabOrder = 7
      Text = '<结束时间>'
      WorkView = WorkView
      FieldName = '结束时间'
    end
    object cbb1: TWVComboBox
      Left = 256
      Top = 300
      Width = 159
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 18
      Visible = False
      WorkView = WorkView
      FieldName = '交易标志'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*155'
    end
    object WVComboBox5: TWVComboBox
      Left = 480
      Top = 125
      Width = 159
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 17
      WorkView = WorkView
      FieldName = '外部类型'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-60'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 169
    Width = 700
    Height = 290
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 290
      Columns = <
        item
          Expanded = False
          FieldName = 'lwithdraw_flag'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '终端编号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '终端流水号'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易时间'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '冲正标志'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易码'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semp'
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
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户姓名'
          Width = 70
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
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '部门全称'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '显示卡号'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '卡号'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '钱包号'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Caption = '交易标志'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol6'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易次数'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '发生额'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '其他费用'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易前余额'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易后余额'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstat_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '支付方式'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '凭证号码'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lcert_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '子系统号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '设备物理编号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '设备流水号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lsafe_level2'
          PickList.Strings = ()
          Title.Caption = '联机状态'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '记账日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '记账时间'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '银行代码'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '银行卡号'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lsafe_level'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '外部类型'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Caption = '附加数据内容'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Caption = '交易参考号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '流水状态'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote2'
          PickList.Strings = ()
          Title.Caption = '备注'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '采集日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '采集时间'
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
        Name = '开始日期'
        Caption = '开始日期'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '截止日期'
        Caption = '截止日期'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '终端编号'
        Caption = '终端编号'
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
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '终端流水号'
        Caption = '终端流水号'
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
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '交易码'
        Caption = '交易码'
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
        Name = '凭证号码'
        Caption = '凭证号码'
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
      end
      item
        Name = '客户号'
        Caption = '客户号'
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
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '学/工号'
        Caption = '学/工号'
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
      end
      item
        Name = '显示卡号'
        Caption = '显示卡号'
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
      end
      item
        Name = '卡号'
        Caption = '卡号'
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
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '钱包号'
        Caption = '钱包号'
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
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '流水状态'
        Caption = '流水状态'
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
      end
      item
        Name = '交易开始日期'
        Caption = '交易开始日期'
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
        Name = '交易结束日期'
        Caption = '交易结束日期'
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
        Name = '操作员'
        Caption = '操作员'
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
        Name = '联机状态'
        Caption = '联机状态'
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
        Name = '开始时间'
        Caption = '开始时间'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '结束时间'
        Caption = '结束时间'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '交易标志'
        Caption = '交易标志'
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
        Name = '外部类型'
        Caption = '外部类型'
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
      end>
    FieldsMonitors = <
      item
      end>
    Left = 164
    Top = 303
  end
  inherited MainRequest: TWVRequest
    ID = '卡交易流水查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '开始日期'
        FieldName = '开始日期'
      end
      item
        ParamName = '截止日期'
        FieldName = '截止日期'
      end
      item
        ParamName = '终端编号'
        FieldName = '终端编号'
      end
      item
        ParamName = '终端流水号'
        FieldName = '终端流水号'
      end
      item
        ParamName = '交易码'
        FieldName = '交易码'
      end
      item
        ParamName = '凭证号码'
        FieldName = '凭证号码'
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '学/工号'
        FieldName = '学/工号'
      end
      item
        ParamName = '显示卡号'
        FieldName = '显示卡号'
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '钱包号'
        FieldName = '钱包号'
      end
      item
        ParamName = '流水状态'
        FieldName = '流水状态'
      end
      item
        ParamName = '交易开始日期'
        FieldName = '交易开始日期'
      end
      item
        ParamName = '交易结束日期'
        FieldName = '交易结束日期'
      end
      item
        ParamName = '操作员'
        FieldName = '操作员'
      end
      item
        ParamName = '联机状态'
        FieldName = '联机状态'
      end
      item
        ParamName = '开始时间'
        FieldName = '开始时间'
      end
      item
        ParamName = '结束时间'
        FieldName = '结束时间'
      end
      item
        ParamName = '交易标志'
        FieldName = '交易标志'
      end
      item
        ParamName = '外部类型'
        FieldName = '外部类型'
        DefaultValue = 0
      end>
    Left = 200
    Top = 304
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sstat_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '63'
      end
      item
        FieldName = 'lcert_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '-32'
      end
      item
        FieldName = 'sstatus3'
        DataPresentType = 'idobjects'
        DataPresentParam = '116'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '3'
      end
      item
        FieldName = 'lsafe_level'
        DataPresentType = 'idobjects'
        DataPresentParam = '-60'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '-10'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '-38'
      end
      item
        FieldName = 'lwithdraw_flag'
        DataPresentType = 'idobjects'
        DataPresentParam = '-9'
      end
      item
        FieldName = 'semp'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'sstat_type2'
        DataPresentType = 'idobjects'
        DataPresentParam = '128'
      end
      item
        FieldName = 'lsafe_level2'
        DataPresentType = 'idobjects'
        DataPresentParam = '139'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '155'
      end>
    Left = 232
    Top = 304
  end
  inherited DataSource: TDataSource
    Left = 264
    Top = 304
  end
end
