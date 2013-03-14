inherited faqhBankCardLinkBind: TfaqhBankCardLinkBind
  Width = 770
  Height = 463
  inherited UIPanel1: TUIPanel
    Top = 427
    Width = 770
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 419
      Top = 5
    end
    inherited btnPrint: TBitBtn
      Left = 680
      Top = 100
      Enabled = True
      TabOrder = 5
    end
    object btnBinding: TBitBtn
      Left = 506
      Top = 5
      Width = 79
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '绑 定'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnBindingClick
    end
    object chkSelectAll: TCheckBox
      Left = 16
      Top = 8
      Width = 57
      Height = 17
      Caption = '全选'
      TabOrder = 4
      OnClick = chkSelectAllClick
    end
    object btnCloseBinding: TBitBtn
      Left = 594
      Top = 5
      Width = 79
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '解除绑定'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnCloseBindingClick
    end
    object btnSynoData: TBitBtn
      Left = 682
      Top = 5
      Width = 79
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '同步数据'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnSynoDataClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 770
    inherited Image1: TImage
      Width = 770
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 770
    Height = 55
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label6: TLabel
      Left = 40
      Top = 10
      Width = 42
      Height = 12
      Caption = '学/工号'
    end
    object Label13: TLabel
      Left = 34
      Top = 34
      Width = 48
      Height = 12
      Caption = '银行卡号'
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
    object Label3: TLabel
      Left = 414
      Top = 10
      Width = 36
      Height = 12
      Caption = '批次号'
    end
    object Label7: TLabel
      Left = 590
      Top = 10
      Width = 36
      Height = 12
      Caption = '客户号'
    end
    object WVEdit6: TWVEdit
      Left = 92
      Top = 6
      Width = 119
      Height = 20
      CharCase = ecUpperCase
      Color = clInfoBk
      MaxLength = 50
      ReadOnly = False
      TabOrder = 0
      Text = '<查询.学工号>'
      WorkView = WorkView1
      FieldName = '查询.学工号'
    end
    object WVEdit13: TWVEdit
      Left = 92
      Top = 30
      Width = 119
      Height = 20
      Color = clInfoBk
      MaxLength = 50
      ReadOnly = False
      TabOrder = 4
      Text = '<查询.银行卡号>'
      WorkView = WorkView1
      FieldName = '查询.银行卡号'
    end
    object WVEdit9: TWVEdit
      Left = 276
      Top = 6
      Width = 118
      Height = 20
      Color = clInfoBk
      MaxLength = 50
      ReadOnly = False
      TabOrder = 1
      Text = '<查询.客户姓名>'
      WorkView = WorkView1
      FieldName = '查询.客户姓名'
    end
    object cbbQFeeType: TWVComboBox
      Left = 276
      Top = 32
      Width = 118
      Height = 18
      Style = csOwnerDrawFixed
      Color = clWhite
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView1
      FieldName = '查询.绑定状态'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*10'
    end
    object WVEdit3: TWVEdit
      Left = 460
      Top = 6
      Width = 125
      Height = 20
      Color = clInfoBk
      MaxLength = 50
      ReadOnly = False
      TabOrder = 2
      Text = '<查询.批次号>'
      WorkView = WorkView1
      FieldName = '查询.批次号'
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
      WorkView = WorkView1
      FieldName = '查询.客户号'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 73
    Width = 770
    Height = 354
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 770
      Height = 354
      TabOrder = 1
    end
    object lv1: TRzListView
      Left = 0
      Top = 0
      Width = 770
      Height = 354
      Align = alClient
      AlphaSortAll = True
      Checkboxes = True
      Columns = <
        item
          Caption = '记录号'
          Width = 80
        end
        item
          Caption = '导入批次号'
          Width = 80
        end
        item
          Caption = '操作员'
          Width = 60
        end
        item
          Caption = '客户号'
          Width = 70
        end
        item
          Caption = '学/工号'
          Width = 80
        end
        item
          Caption = '客户姓名'
          Width = 80
        end
        item
          Caption = '银行卡号'
          Width = 120
        end
        item
          Caption = '操作类型'
          Width = 60
        end
        item
          Caption = '处理状态'
          Width = 60
        end
        item
          Caption = '备注'
          Width = 59
        end>
      GridLines = True
      TabOrder = 0
      ViewStyle = vsReport
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
        Name = '操作标志'
        Caption = '操作标志'
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
        Name = '记录号'
        Caption = '记录号'
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
        Name = '类型'
        Caption = '类型'
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
        MonitorValueChangedFields = 
          '|客户类别|客户状态|地区|客户名称|联系人学号或员工号|联系人班级或' +
          '部门|联系人姓名|联系人性别|联系人民族代码|联系人身份证号|联系电' +
          '话|联系地址|注册时间|预计注销时间|'
      end>
    Left = 84
    Top = 319
  end
  inherited MainRequest: TWVRequest
    ID = '银行卡联机绑定'
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
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '记录号'
        FieldName = '记录号'
      end
      item
        ParamName = '类型'
        FieldName = '类型'
      end>
    Left = 120
    Top = 320
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-34'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '15'
      end
      item
        FieldName = 'scust_type2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2001'
      end
      item
        FieldName = 'smarket_code2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '39'
      end
      item
        FieldName = 'scert_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'scust_no2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-23'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '87'
      end
      item
        FieldName = 'snation_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '89'
      end
      item
        FieldName = 'sstat_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '125'
      end>
    Left = 192
    Top = 320
  end
  inherited DataSource: TDataSource
    Top = 320
  end
  object QueryRequest: TWVRequest
    WorkView = WorkView1
    ID = '银行卡绑定查询联机'
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
    Left = 120
    Top = 264
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
        GroupIndex = 1
        DataField = '@Dataset'
      end
      item
        Name = '操作类别.增加'
        Caption = '操作类别.增加'
        FieldType = wftUndefined
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
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.操作标志|查询.导入日期|查询.批次号|查询.导入顺序号|查询.导' +
          '入操作员|查询.学工号|查询.客户类型|查询.收费类别|查询.客户姓名|' +
          '查询.区域代码|查询.部门代码|查询.专业代码|查询.班级|查询.证件类' +
          '型|查询.证件号码|查询.性别|查询.国籍|查询.民族|查询.电子邮箱|查' +
          '询.电话|查询.手机|查询.地址|查询.邮政编码|查询.入校日期|查询.预' +
          '计离校日期|'
      end
      item
        MonitorValueChangedFields = 
          '|导入日期|批次号|导入顺序号|导入操作员|学工号|客户类型|收费类别|' +
          '客户姓名|区域代码|部门代码|专业代码|班级|证件类型|证件号码|性别|' +
          '国籍|民族|电子邮箱|电话|手机|地址|邮政编码|入校日期|'
      end>
    Left = 80
    Top = 264
  end
  object dlgSave1: TSaveDialog
    Filter = '文本文件(*.txt)|*.txt'
    Title = '操作失败记录'
    Left = 232
    Top = 321
  end
end
