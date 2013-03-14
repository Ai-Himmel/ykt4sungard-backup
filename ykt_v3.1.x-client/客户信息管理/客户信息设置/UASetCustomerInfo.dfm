inherited faqhSetCustomerInfo: TfaqhSetCustomerInfo
  Width = 788
  Height = 500
  Caption = '客户信息设置'
  inherited pcPages: TRzPageControl
    Width = 788
    Height = 500
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 441
        Width = 784
        Height = 36
        TabOrder = 3
        inherited btnDelete: TBitBtn [0]
          Left = 702
          Top = 5
        end
        inherited btnAdd: TBitBtn
          Left = 532
          Top = 5
        end
        inherited btnChange: TBitBtn
          Left = 617
          Top = 5
        end
        inherited btnQuery: TBitBtn [3]
          Left = 447
          Top = 5
        end
        inherited btnViewDetail: TBitBtn
          Left = 10
          Top = 5
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 10
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 784
      end
      inherited Grid: TRzDBGrid
        Top = 97
        Width = 784
        Height = 344
        DragCursor = crHandPoint
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'sbranch_code0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '校区'
            Width = 83
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '客户号'
            Width = 62
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '学/工号'
            Width = 83
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '客户姓名'
            Width = 96
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smarket_code2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '性别'
            Width = 66
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '客户类别'
            Width = 74
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
            Title.Caption = '部门'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '部门全称'
            Width = 80
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
            FieldName = 'scard1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '班级'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '状态'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '注册日期'
            Width = 93
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smarket_code'
            PickList.Strings = ()
            Title.Caption = '证件类型'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '证件证号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snation_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '国籍'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_type2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '民族'
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
            Title.Alignment = taCenter
            Title.Caption = '手机'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
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
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '入学日期'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '预计注销日期'
            Width = 70
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 784
        Height = 79
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label1: TLabel
          Left = 54
          Top = 9
          Width = 36
          Height = 12
          Caption = '客户号'
        end
        object WVLabel4: TWVLabel
          Left = 461
          Top = 9
          Width = 48
          Height = 12
          Caption = '客户姓名'
        end
        object WVLabel5: TWVLabel
          Left = 263
          Top = 33
          Width = 48
          Height = 12
          Caption = '证件号码'
        end
        object WVLabel6: TWVLabel
          Left = 269
          Top = 9
          Width = 42
          Height = 12
          Caption = '学/工号'
        end
        object WVLabel7: TWVLabel
          Left = 263
          Top = 57
          Width = 48
          Height = 12
          Caption = '注册日期'
        end
        object WVLabel8: TWVLabel
          Left = 42
          Top = 57
          Width = 48
          Height = 12
          Caption = '客户类别'
        end
        object WVLabel9: TWVLabel
          Left = 42
          Top = 33
          Width = 48
          Height = 12
          Caption = '收费类别'
        end
        object WVLabel10: TWVLabel
          Left = 473
          Top = 32
          Width = 36
          Height = 12
          Caption = '批次号'
        end
        object WVLabel11: TWVLabel
          Left = 461
          Top = 56
          Width = 48
          Height = 12
          Caption = '所属班级'
        end
        object WVEdit3: TWVEdit
          Left = 95
          Top = 4
          Width = 120
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.客户号>'
          WorkView = WorkView
          FieldName = '查询.客户号'
        end
        object WVEdit7: TWVEdit
          Left = 519
          Top = 4
          Width = 120
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 2
          Text = '<查询.客户名称>'
          WorkView = WorkView
          FieldName = '查询.客户名称'
        end
        object WVEdit9: TWVEdit
          Left = 319
          Top = 28
          Width = 120
          Height = 20
          Color = clWhite
          MaxLength = 18
          ReadOnly = False
          TabOrder = 4
          Text = '<查询.联系人身份证号>'
          WorkView = WorkView
          FieldName = '查询.联系人身份证号'
        end
        object WVEdit10: TWVEdit
          Left = 319
          Top = 4
          Width = 120
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.联系人学工号>'
          WorkView = WorkView
          FieldName = '查询.联系人学工号'
        end
        object WVEdit15: TWVEdit
          Left = 319
          Top = 52
          Width = 120
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 7
          Text = '<查询.注册日期>'
          WorkView = WorkView
          FieldName = '查询.注册日期'
        end
        object WVComboBox1: TWVComboBox
          Left = 95
          Top = 52
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 6
          Text = '<查询.客户类别>'
          WorkView = WorkView
          FieldName = '查询.客户类别'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-34'
        end
        object WVComboBox5: TWVComboBox
          Left = 95
          Top = 28
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 3
          Text = '<查询.收费类别>'
          WorkView = WorkView
          FieldName = '查询.收费类别'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-43'
        end
        object WVEdit16: TWVEdit
          Left = 519
          Top = 28
          Width = 120
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 5
          Text = '<查询.批次号>'
          WorkView = WorkView
          FieldName = '查询.批次号'
        end
        object WVEdit17: TWVEdit
          Left = 519
          Top = 52
          Width = 120
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 8
          Text = '<查询.班级>'
          WorkView = WorkView
          FieldName = '查询.班级'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 62
        Top = 421
        Width = 48
        Height = 12
        Caption = '客户号 *'
        Visible = False
      end
      object Label3: TLabel [1]
        Left = 526
        Top = 44
        Width = 60
        Height = 12
        Caption = '客户类别 *'
      end
      object Label4: TLabel [2]
        Left = 74
        Top = 84
        Width = 36
        Height = 12
        Caption = '校区 *'
      end
      object Label5: TLabel [3]
        Left = 50
        Top = 44
        Width = 60
        Height = 12
        Caption = '客户姓名 *'
      end
      object Label6: TLabel [4]
        Left = 68
        Top = 124
        Width = 42
        Height = 12
        Caption = '学/工号'
      end
      object Label7: TLabel [5]
        Left = 294
        Top = 84
        Width = 48
        Height = 12
        Caption = '所属部门'
      end
      object Label8: TLabel [6]
        Left = 538
        Top = 203
        Width = 48
        Height = 12
        Caption = '电子邮箱'
      end
      object Label9: TLabel [7]
        Left = 318
        Top = 124
        Width = 24
        Height = 12
        Caption = '性别'
      end
      object Label10: TLabel [8]
        Left = 86
        Top = 164
        Width = 24
        Height = 12
        Caption = '民族'
      end
      object Label11: TLabel [9]
        Left = 538
        Top = 163
        Width = 48
        Height = 12
        Caption = '证件号码'
      end
      object Label12: TLabel [10]
        Left = 62
        Top = 204
        Width = 48
        Height = 12
        Caption = '联系电话'
      end
      object Label13: TLabel [11]
        Left = 64
        Top = 285
        Width = 48
        Height = 12
        Caption = '联系地址'
      end
      object Label14: TLabel [12]
        Left = 514
        Top = 242
        Width = 72
        Height = 12
        Caption = '预计注销日期'
      end
      object WVLabel2: TWVLabel [13]
        Left = 86
        Top = 244
        Width = 24
        Height = 12
        Caption = '班级'
      end
      object Label17: TLabel [14]
        Left = 282
        Top = 44
        Width = 60
        Height = 12
        Caption = '收费类别 *'
      end
      object Label18: TLabel [15]
        Left = 562
        Top = 84
        Width = 24
        Height = 12
        Caption = '专业'
      end
      object Label15: TLabel [16]
        Left = 562
        Top = 124
        Width = 24
        Height = 12
        Caption = '国籍'
      end
      object Label19: TLabel [17]
        Left = 294
        Top = 164
        Width = 48
        Height = 12
        Caption = '证件类型'
      end
      object Label20: TLabel [18]
        Left = 562
        Top = 282
        Width = 24
        Height = 12
        Caption = '邮编'
      end
      object Label21: TLabel [19]
        Left = 318
        Top = 204
        Width = 24
        Height = 12
        Caption = '手机'
      end
      object Label22: TLabel [20]
        Left = 294
        Top = 244
        Width = 48
        Height = 12
        Caption = '入校日期'
      end
      inherited UIPanel2: TUIPanel
        Top = 441
        Width = 784
        TabOrder = 23
        inherited btnOK: TBitBtn
          Left = 600
          Top = 5
          Enabled = False
          TabOrder = 0
        end
        inherited btnCancel: TBitBtn
          Left = 693
          Top = 5
          TabOrder = 1
        end
        inherited DBNavigator: TRzDBNavigator
          Left = 34
          Hints.Strings = ()
          TabOrder = 2
        end
      end
      object cbbCustType: TWVComboBox
        Left = 592
        Top = 40
        Width = 161
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 2
        WorkView = WorkView
        FieldName = '客户类别'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-34'
      end
      object WVComboBox4: TWVComboBox
        Left = 121
        Top = 80
        Width = 147
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 7
        WorkView = WorkView
        FieldName = '客户所在区域'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-27'
      end
      object WVEdit5: TWVEdit
        Left = 121
        Top = 40
        Width = 147
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 0
        Text = '<客户名称>'
        WorkView = WorkView
        FieldName = '客户名称'
        SynchronizeWhenExit = True
      end
      object cbbDept: TWVComboBox
        Left = 353
        Top = 79
        Width = 159
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 5
        WorkView = WorkView
        FieldName = '联系人班级或部门号'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-22'
      end
      object WVEdit8: TWVEdit
        Left = 592
        Top = 197
        Width = 161
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 14
        Text = '<电子邮箱>'
        WorkView = WorkView
        FieldName = '电子邮箱'
        SynchronizeWhenExit = True
      end
      object WVComboBox9: TWVComboBox
        Left = 353
        Top = 118
        Width = 159
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 8
        WorkView = WorkView
        FieldName = '联系人性别'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*39'
      end
      object WVComboBox10: TWVComboBox
        Left = 121
        Top = 159
        Width = 147
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 13
        WorkView = WorkView
        FieldName = '联系人民族'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*2001'
      end
      object edtIdCardNo: TWVEdit
        Left = 592
        Top = 156
        Width = 161
        Height = 20
        Color = clWhite
        MaxLength = 20
        ReadOnly = False
        TabOrder = 11
        Text = '<联系人身份证号>'
        WorkView = WorkView
        FieldName = '联系人身份证号'
        SynchronizeWhenExit = True
      end
      object WVEdit12: TWVEdit
        Left = 121
        Top = 199
        Width = 147
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 15
        Text = '<联系电话>'
        WorkView = WorkView
        FieldName = '联系电话'
        SynchronizeWhenExit = True
      end
      object WVEdit13: TWVEdit
        Left = 120
        Top = 280
        Width = 393
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 21
        Text = '<联系地址>'
        WorkView = WorkView
        FieldName = '联系地址'
        SynchronizeWhenExit = True
      end
      object edtDestoryDate: TWVEdit
        Left = 593
        Top = 238
        Width = 159
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 17
        Text = '<预计注销时间>'
        WorkView = WorkView
        FieldName = '预计注销时间'
        SynchronizeWhenExit = True
      end
      object WVEdit2: TWVEdit
        Left = 121
        Top = 240
        Width = 147
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 18
        Text = '<联系人班级或部门名称>'
        WorkView = WorkView
        FieldName = '联系人班级或部门名称'
      end
      object WVEdit4: TWVEdit
        Left = 120
        Top = 416
        Width = 89
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 22
        Text = '<客户号>'
        Visible = False
        WorkView = WorkView
        FieldName = '客户号'
      end
      object WVEdit6: TWVEdit
        Left = 121
        Top = 119
        Width = 147
        Height = 20
        CharCase = ecUpperCase
        Color = clWhite
        ReadOnly = False
        TabOrder = 10
        Text = '<联系人学号或员工号>'
        WorkView = WorkView
        FieldName = '联系人学号或员工号'
        SynchronizeWhenExit = True
      end
      object cbbFeeType: TWVComboBox
        Left = 353
        Top = 40
        Width = 159
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 1
        WorkView = WorkView
        FieldName = '收费类别'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-43'
      end
      object cbbSpec: TWVComboBox
        Left = 592
        Top = 79
        Width = 161
        Height = 18
        Style = csOwnerDrawFixed
        Color = clWhite
        ItemHeight = 12
        TabOrder = 6
        WorkView = WorkView
        FieldName = '专业'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-23'
      end
      object WVComboBox2: TWVComboBox
        Left = 592
        Top = 118
        Width = 161
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 9
        WorkView = WorkView
        FieldName = '国籍'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*89'
      end
      object cbbIdCardType: TWVComboBox
        Left = 353
        Top = 158
        Width = 159
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 12
        WorkView = WorkView
        FieldName = '证件类型'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*87'
      end
      object WVEdit14: TWVEdit
        Left = 593
        Top = 278
        Width = 160
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 20
        Text = '<邮编>'
        WorkView = WorkView
        FieldName = '邮编'
        SynchronizeWhenExit = True
      end
      object WVEdit18: TWVEdit
        Left = 353
        Top = 199
        Width = 159
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 16
        Text = '<手机>'
        WorkView = WorkView
        FieldName = '手机'
        SynchronizeWhenExit = True
      end
      object edtInDate: TWVEdit
        Left = 353
        Top = 240
        Width = 159
        Height = 20
        Color = clWhite
        MaxLength = 8
        ReadOnly = False
        TabOrder = 19
        Text = '<入学日期>'
        WorkView = WorkView
        FieldName = '入学日期'
        SynchronizeWhenExit = True
      end
      object cbb1: TKSFilterComboBox
        Left = 353
        Top = 77
        Width = 159
        Height = 22
        ListFont.Charset = GB2312_CHARSET
        ListFont.Color = clWindowText
        ListFont.Height = -12
        ListFont.Name = '宋体'
        ListFont.Style = []
        OnFilterItems = cbb1FilterItems
        TabOrder = 3
      end
      object cbb2: TKSFilterComboBox
        Left = 592
        Top = 77
        Width = 162
        Height = 22
        ListFont.Charset = GB2312_CHARSET
        ListFont.Color = clWindowText
        ListFont.Height = -12
        ListFont.Name = '宋体'
        ListFont.Style = []
        OnFilterItems = cbb2FilterItems
        TabOrder = 4
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 468
    Top = 31
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
        Name = '联系地址'
        Caption = '联系地址'
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
        DataField = 'scusttypes'
      end
      item
        Name = '客户所在区域'
        Caption = '客户所在区域'
        FieldType = wftUndefined
        DomainName = '选择项目'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbranch_code0'
      end
      item
        Name = '预计注销时间'
        Caption = '预计注销时间'
        FieldType = wftUndefined
        DomainName = '日期校验'
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
        DataField = 'sdate2'
      end
      item
        Name = '联系人班级或部门名称'
        Caption = '联系人班级或部门名称'
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
        DataField = 'scard1'
      end
      item
        Name = '联系人班级或部门号'
        Caption = '联系人班级或部门号'
        FieldType = wftUndefined
        DomainName = '选择项目'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scert_no'
      end
      item
        Name = '备注'
        Caption = '备注'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 100
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'ssectypes'
      end
      item
        Name = '客户号'
        Caption = '客户号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '客户名称'
        Caption = '客户名称'
        FieldType = wftUndefined
        DomainName = '非空'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sall_name'
      end
      item
        Name = '客户类别'
        Caption = '客户类别'
        FieldType = wftUndefined
        DomainName = '选择项目'
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol3'
      end
      item
        Name = '收费类别'
        Caption = '收费类别'
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
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '联系人姓名'
        Caption = '联系人姓名'
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
        DataField = 'sname2'
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
        Checker.MaxLength = 20
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'scust_auth'
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
        GroupIndex = 1
        DataField = 'scust_no2'
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
        GroupIndex = 1
        DataField = 'scust_type2'
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
        GroupIndex = 1
        DataField = 'smarket_code2'
      end
      item
        Name = '联系人学号或员工号'
        Caption = '联系人学号或员工号'
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
        DataField = 'scust_auth2'
      end
      item
        Name = '联系电话'
        Caption = '联系电话'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
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
        DataField = 'sphone'
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
        Name = '国籍'
        Caption = '国籍'
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
        DataField = 'snation_code'
      end
      item
        Name = '手机'
        Caption = '手机'
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
        DataField = 'sphone2'
      end
      item
        Name = '电子邮箱'
        Caption = '电子邮箱'
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
        DataField = 'semail'
      end
      item
        Name = '邮编'
        Caption = '邮编'
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
        DataField = 'spost_code'
      end
      item
        Name = '入学日期'
        Caption = '入学日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sdate1'
      end
      item
        Name = '证件类型'
        Caption = '证件类型'
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
        DataField = 'smarket_code'
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
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.客户类别'
        Caption = '查询.客户类别'
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
      end
      item
        Name = '查询.客户状态'
        Caption = '查询.客户状态'
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
      end
      item
        Name = '查询.客户所在区域'
        Caption = '查询.客户所在区域'
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
      end
      item
        Name = '查询.客户名称'
        Caption = '查询.客户名称'
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
      end
      item
        Name = '查询.联系人学工号'
        Caption = '查询.联系人学工号'
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
      end
      item
        Name = '查询.联系人单位号'
        Caption = '查询.联系人单位号'
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
      end
      item
        Name = '查询.注册日期'
        Caption = '查询.注册日期'
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
      end
      item
        Name = '查询.联系人性别'
        Caption = '查询.联系人性别'
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
      end
      item
        Name = '查询.联系人民族'
        Caption = '查询.联系人民族'
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
      end
      item
        Name = '查询.联系人身份证号'
        Caption = '查询.联系人身份证号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 18
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GetPrevChar = '*'
      end
      item
        Name = '查询.联系地址'
        Caption = '查询.联系地址'
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
      end
      item
        Name = '查询.联系人单位名称'
        Caption = '查询.联系人单位名称'
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
      end
      item
        Name = '查询.收费类别'
        Caption = '查询.收费类别'
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
        Name = '查询.批次号'
        Caption = '查询.批次号'
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
        Name = '查询.班级'
        Caption = '查询.班级'
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
        MonitorValueChangedFields = '|查询.客户号|'
      end
      item
        MonitorValueChangedFields = '|客户名称|客户类别|收费类别|联系人学号或员工号|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 320
    Top = 8
  end
  inherited QueryRequest: TWVRequest
    ID = '客户信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '客户号'
        FieldName = '查询.客户号'
      end
      item
        ParamName = '客户类别'
        FieldName = '查询.客户类别'
      end
      item
        ParamName = '客户所在区域'
        FieldName = '查询.客户所在区域'
      end
      item
        ParamName = '客户状态'
        FieldName = '查询.客户状态'
      end
      item
        ParamName = '联系人单位号'
        FieldName = '查询.联系人单位号'
      end
      item
        ParamName = '联系人民族'
        FieldName = '查询.联系人民族'
      end
      item
        ParamName = '联系人身份证号'
        FieldName = '查询.联系人身份证号'
      end
      item
        ParamName = '联系人性别'
        FieldName = '查询.联系人性别'
      end
      item
        ParamName = '联系人学工号'
        FieldName = '查询.联系人学工号'
      end
      item
        ParamName = '客户名称'
        FieldName = '查询.客户名称'
      end
      item
        ParamName = '收费类别'
        FieldName = '查询.收费类别'
      end
      item
        ParamName = '批次号'
        FieldName = '查询.批次号'
      end
      item
        ParamName = '班级'
        FieldName = '查询.班级'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '注册日期'
        FieldName = '查询.注册日期'
      end>
    Left = 472
    Top = 8
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-34'
      end
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'scert_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'smarket_code2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '39'
      end
      item
        FieldName = 'scust_type2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2001'
      end
      item
        FieldName = 'scard1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '15'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
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
      end>
    Left = 428
    Top = 47
  end
  inherited AddRequest: TWVRequest
    ID = '客户信息设置'
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
        ParamName = '联系地址'
        FieldName = '联系地址'
      end
      item
        ParamName = '客户所在区域'
        FieldName = '客户所在区域'
      end
      item
        ParamName = '预计注销时间'
        FieldName = '预计注销时间'
      end
      item
        ParamName = '联系人班级或部门名称'
        FieldName = '联系人班级或部门名称'
      end
      item
        ParamName = '联系人班级或部门号'
        FieldName = '联系人班级或部门号'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end
      item
        ParamName = '客户名称'
        FieldName = '客户名称'
      end
      item
        ParamName = '客户类别'
        FieldName = '客户类别'
      end
      item
        ParamName = '联系人姓名'
        FieldName = '联系人姓名'
      end
      item
        ParamName = '联系人身份证号'
        FieldName = '联系人身份证号'
      end
      item
        ParamName = '联系人民族'
        FieldName = '联系人民族'
      end
      item
        ParamName = '联系人性别'
        FieldName = '联系人性别'
      end
      item
        ParamName = '联系人学号或员工号'
        FieldName = '联系人学号或员工号'
      end
      item
        ParamName = '联系电话'
        FieldName = '联系电话'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '专业'
        FieldName = '专业'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '电子邮箱'
        FieldName = '电子邮箱'
      end
      item
        ParamName = '国籍'
        FieldName = '国籍'
      end
      item
        ParamName = '手机'
        FieldName = '手机'
      end
      item
        ParamName = '邮编'
        FieldName = '邮编'
      end
      item
        ParamName = '入学日期'
        FieldName = '入学日期'
      end
      item
        ParamName = '证件类型'
        FieldName = '证件类型'
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end>
    Left = 360
    Top = 8
  end
  inherited DeleteRequest: TWVRequest
    ID = '客户信息设置'
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
        ParamName = '联系地址'
        FieldName = '联系地址'
      end
      item
        ParamName = '客户所在区域'
        FieldName = '客户所在区域'
      end
      item
        ParamName = '预计注销时间'
        FieldName = '预计注销时间'
      end
      item
        ParamName = '联系人班级或部门名称'
        FieldName = '联系人班级或部门名称'
      end
      item
        ParamName = '联系人班级或部门号'
        FieldName = '联系人班级或部门号'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
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
        ParamName = '客户类别'
        FieldName = '客户类别'
      end
      item
        ParamName = '联系人姓名'
        FieldName = '联系人姓名'
      end
      item
        ParamName = '联系人身份证号'
        FieldName = '联系人身份证号'
      end
      item
        ParamName = '联系人民族'
        FieldName = '联系人民族'
      end
      item
        ParamName = '联系人性别'
        FieldName = '联系人性别'
      end
      item
        ParamName = '联系人学号或员工号'
        FieldName = '联系人学号或员工号'
      end
      item
        ParamName = '联系电话'
        FieldName = '联系电话'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '专业'
        FieldName = '专业'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '国籍'
        FieldName = '国籍'
      end
      item
        ParamName = '手机'
        FieldName = '手机'
      end
      item
        ParamName = '电子邮箱'
        FieldName = '电子邮箱'
      end
      item
        ParamName = '邮编'
        FieldName = '邮编'
      end
      item
        ParamName = '入学日期'
        FieldName = '入学日期'
      end
      item
        ParamName = '证件类型'
        FieldName = '证件类型'
      end>
    Left = 400
    Top = 8
  end
  inherited ChangeRequest: TWVRequest
    ID = '客户信息设置'
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
        ParamName = '联系地址'
        FieldName = '联系地址'
      end
      item
        ParamName = '客户所在区域'
        FieldName = '客户所在区域'
      end
      item
        ParamName = '预计注销时间'
        FieldName = '预计注销时间'
      end
      item
        ParamName = '联系人班级或部门名称'
        FieldName = '联系人班级或部门名称'
      end
      item
        ParamName = '联系人班级或部门号'
        FieldName = '联系人班级或部门号'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
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
        ParamName = '客户类别'
        FieldName = '客户类别'
      end
      item
        ParamName = '联系人姓名'
        FieldName = '联系人姓名'
      end
      item
        ParamName = '联系人身份证号'
        FieldName = '联系人身份证号'
      end
      item
        ParamName = '联系人民族'
        FieldName = '联系人民族'
      end
      item
        ParamName = '联系人性别'
        FieldName = '联系人性别'
      end
      item
        ParamName = '联系人学号或员工号'
        FieldName = '联系人学号或员工号'
      end
      item
        ParamName = '联系电话'
        FieldName = '联系电话'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '专业'
        FieldName = '专业'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '国籍'
        FieldName = '国籍'
      end
      item
        ParamName = '手机'
        FieldName = '手机'
      end
      item
        ParamName = '电子邮箱'
        FieldName = '电子邮箱'
      end
      item
        ParamName = '邮编'
        FieldName = '邮编'
      end
      item
        ParamName = '入学日期'
        FieldName = '入学日期'
      end
      item
        ParamName = '证件类型'
        FieldName = '证件类型'
      end>
    Left = 440
    Top = 8
  end
  inherited WVDataSource: TWVDataSource
    Left = 532
    Top = 23
  end
  inherited alDatasetActions: TActionList
    Left = 500
    Top = 31
  end
end
