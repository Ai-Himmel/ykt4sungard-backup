inherited faqhQueryCustomerByOther: TfaqhQueryCustomerByOther
  Width = 770
  Height = 463
  inherited UIPanel1: TUIPanel
    Top = 427
    Width = 770
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 507
      Top = 5
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 680
      Top = 5
      TabOrder = 2
    end
    object btnPhoto: TBitBtn
      Left = 594
      Top = 5
      Width = 79
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '取照片(&S)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnPhotoClick
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
    Height = 135
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 17
      Top = 39
      Width = 48
      Height = 12
      Caption = '客户类别'
    end
    object Label2: TLabel
      Left = 454
      Top = 39
      Width = 48
      Height = 12
      Caption = '客户状态'
    end
    object Label3: TLabel
      Left = 236
      Top = 87
      Width = 48
      Height = 12
      Caption = '所属区域'
    end
    object Label4: TLabel
      Left = 454
      Top = 15
      Width = 48
      Height = 12
      Caption = '客户姓名'
    end
    object Label5: TLabel
      Left = 242
      Top = 15
      Width = 42
      Height = 12
      Caption = '学/工号'
    end
    object Label6: TLabel
      Left = 236
      Top = 63
      Width = 48
      Height = 12
      Caption = '所属部门'
    end
    object Label8: TLabel
      Left = 41
      Top = 63
      Width = 24
      Height = 12
      Caption = '性别'
    end
    object Label9: TLabel
      Left = 478
      Top = 63
      Width = 24
      Height = 12
      Caption = '民族'
    end
    object Label10: TLabel
      Left = 17
      Top = 87
      Width = 48
      Height = 12
      Caption = '证件号码'
    end
    object Label11: TLabel
      Left = 236
      Top = 111
      Width = 48
      Height = 12
      Caption = '注册日期'
    end
    object WVLabel2: TWVLabel
      Left = 29
      Top = 15
      Width = 36
      Height = 12
      Caption = '客户号'
    end
    object WVLabel1: TWVLabel
      Left = 29
      Top = 111
      Width = 36
      Height = 12
      Caption = '批次号'
    end
    object Label13: TLabel
      Left = 236
      Top = 39
      Width = 48
      Height = 12
      Caption = '收费类别'
    end
    object WVLabel3: TWVLabel
      Left = 478
      Top = 111
      Width = 24
      Height = 12
      Caption = '班级'
    end
    object Label7: TLabel
      Left = 478
      Top = 87
      Width = 24
      Height = 12
      Caption = '专业'
    end
    object imgPhoto: TImage
      Left = 657
      Top = 12
      Width = 84
      Height = 112
      Stretch = True
    end
    object WVComboBox1: TWVComboBox
      Left = 77
      Top = 34
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '客户类别'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-34'
    end
    object WVComboBox2: TWVComboBox
      Left = 508
      Top = 34
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '客户状态'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*15'
    end
    object WVComboBox3: TWVComboBox
      Left = 291
      Top = 82
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 12
      WorkView = WorkView
      FieldName = '客户所在区域'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-27'
    end
    object WVEdit4: TWVEdit
      Left = 508
      Top = 10
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<客户名称>'
      WorkView = WorkView
      FieldName = '客户名称'
    end
    object WVEdit5: TWVEdit
      Left = 291
      Top = 10
      Width = 142
      Height = 20
      CharCase = ecUpperCase
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<联系人学工号>'
      WorkView = WorkView
      FieldName = '联系人学工号'
    end
    object cbbDeptName: TWVComboBox
      Left = 291
      Top = 58
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 8
      Visible = False
      WorkView = WorkView
      FieldName = '联系人单位号'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object WVComboBox8: TWVComboBox
      Left = 77
      Top = 58
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView
      FieldName = '联系人性别'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*39'
    end
    object WVComboBox9: TWVComboBox
      Left = 508
      Top = 58
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 9
      WorkView = WorkView
      FieldName = '联系人民族'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*2001'
    end
    object WVEdit10: TWVEdit
      Left = 77
      Top = 82
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 11
      Text = '<联系人身份证号>'
      WorkView = WorkView
      FieldName = '联系人身份证号'
    end
    object WVEdit11: TWVEdit
      Left = 291
      Top = 106
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 15
      Text = '<注册日期>'
      WorkView = WorkView
      FieldName = '注册日期'
    end
    object WVEdit2: TWVEdit
      Left = 77
      Top = 10
      Width = 142
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<客户号>'
      WorkView = WorkView
      FieldName = '客户号'
    end
    object WVEdit1: TWVEdit
      Left = 77
      Top = 106
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 14
      Text = '<批次号>'
      WorkView = WorkView
      FieldName = '批次号'
    end
    object WVComboBox4: TWVComboBox
      Left = 291
      Top = 34
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 4
      WorkView = WorkView
      FieldName = '收费类别'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-43'
    end
    object WVEdit3: TWVEdit
      Left = 508
      Top = 106
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 16
      Text = '<班级>'
      WorkView = WorkView
      FieldName = '班级'
    end
    object cbbSpec: TWVComboBox
      Left = 510
      Top = 82
      Width = 139
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 13
      Visible = False
      WorkView = WorkView
      FieldName = '专业'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-23'
    end
    object cbb1: TKSFilterComboBox
      Left = 291
      Top = 57
      Width = 142
      Height = 22
      ListFont.Charset = GB2312_CHARSET
      ListFont.Color = clWindowText
      ListFont.Height = -12
      ListFont.Name = '宋体'
      ListFont.Style = []
      OnFilterItems = cbb1FilterItems
      TabOrder = 6
    end
    object cbb2: TKSFilterComboBox
      Left = 508
      Top = 81
      Width = 142
      Height = 22
      ListFont.Charset = GB2312_CHARSET
      ListFont.Color = clWindowText
      ListFont.Height = -12
      ListFont.Name = '宋体'
      ListFont.Style = []
      OnFilterItems = cbb2FilterItems
      TabOrder = 10
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 153
    Width = 770
    Height = 274
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 770
      Height = 274
      Columns = <
        item
          Expanded = False
          FieldName = 'sbranch_code0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '所属区域'
          Width = 91
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户号'
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '批次号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '学/工号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户姓名'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstat_type'
          PickList.Strings = ()
          Title.Caption = '电子钱包'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smarket_code2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '性别'
          Width = 40
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户类别'
          Width = 61
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '收费类别'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '所属部门'
          Width = 128
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '部门全称'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '专业'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户状态'
          Width = 57
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '注册日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard1'
          PickList.Strings = ()
          Title.Caption = '班级'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '联系人'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'snation_code'
          PickList.Strings = ()
          Title.Caption = '国籍'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_type2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '民族'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smarket_code'
          PickList.Strings = ()
          Title.Caption = '证件类型'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '证件号码'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '联系电话'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone2'
          PickList.Strings = ()
          Title.Caption = '手机'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail'
          PickList.Strings = ()
          Title.Caption = '电子邮箱'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scusttypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '联系地址'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spost_code'
          PickList.Strings = ()
          Title.Caption = '邮编'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Caption = '入学日期'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Caption = '预计离校日期'
          Width = 70
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
        OwnObject = True
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
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '客户名称'
        Caption = '客户名称'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '客户状态'
        Caption = '客户状态'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '客户类别'
        Caption = '客户类别'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '收费类别'
        Caption = '收费类别'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '联系人单位号'
        Caption = '联系人单位号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '联系人性别'
        Caption = '联系人性别'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '联系人学工号'
        Caption = '联系人学工号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '联系人民族'
        Caption = '联系人民族'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '联系人身份证号'
        Caption = '联系人身份证号'
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
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '客户所在区域'
        Caption = '客户所在区域'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
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
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '注册日期'
        Caption = '注册日期'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '班级'
        Caption = '班级'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
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
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
      end
      item
        Name = '专业'
        Caption = '专业'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|客户类别|客户状态|地区|客户名称|联系人学号或员工号|联系人班级或' +
          '部门|联系人姓名|联系人性别|联系人民族代码|联系人身份证号|联系电' +
          '话|联系地址|注册时间|预计注销时间|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 84
    Top = 319
  end
  inherited MainRequest: TWVRequest
    ID = '客户信息查询'
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
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '客户名称'
        FieldName = '客户名称'
      end
      item
        ParamName = '客户状态'
        FieldName = '客户状态'
      end
      item
        ParamName = '客户类别'
        FieldName = '客户类别'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '客户所在区域'
        FieldName = '客户所在区域'
      end
      item
        ParamName = '联系人学工号'
        FieldName = '联系人学工号'
      end
      item
        ParamName = '联系人单位号'
        FieldName = '联系人单位号'
      end
      item
        ParamName = '联系人性别'
        FieldName = '联系人性别'
      end
      item
        ParamName = '联系人民族'
        FieldName = '联系人民族'
      end
      item
        ParamName = '联系人身份证号'
        FieldName = '联系人身份证号'
      end
      item
        ParamName = '注册日期'
        FieldName = '注册日期'
      end
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end
      item
        ParamName = '班级'
        FieldName = '班级'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '专业'
        FieldName = '专业'
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
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '照片查询'
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
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '文件名'
        FieldName = '文件名'
        Direction = bdParam2Field
      end>
    AfterExec = MainRequestAfterExec
    Left = 120
    Top = 360
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
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '文件名'
        Caption = '文件名'
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
          '|客户类别|客户状态|地区|客户名称|联系人学号或员工号|联系人班级或' +
          '部门|联系人姓名|联系人性别|联系人民族代码|联系人身份证号|联系电' +
          '话|联系地址|注册时间|预计注销时间|'
      end>
    Left = 84
    Top = 359
  end
end
