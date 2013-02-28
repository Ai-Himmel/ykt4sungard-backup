inherited faqhSetOperator: TfaqhSetOperator
  Width = 680
  Height = 477
  Caption = '设置操作员'
  inherited pcPages: TRzPageControl
    Width = 680
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 676
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 415
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 501
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
        end
        inherited btnDelete: TBitBtn
          Left = 587
          Caption = '注销(&D)'
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Width = 169
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 676
        Align = alNone
        TabOrder = 1
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 676
        Height = 391
        ReadOnly = True
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'sstatus2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '操作员类型'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_no'
            PickList.Strings = ()
            Title.Caption = '操作员代码'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Caption = '姓名'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type2'
            PickList.Strings = ()
            Title.Caption = '所属网点号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '充值限额'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sphone'
            PickList.Strings = ()
            Title.Caption = '电话'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone2'
            PickList.Strings = ()
            Title.Caption = '手机'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Caption = '电子邮件'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Caption = '地址'
            Width = 80
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
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Caption = '是否限制站点'
            Width = 94
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus2'
            PickList.Strings = ()
            Title.Caption = '是否限制访问'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sstatus3'
            PickList.Strings = ()
            Title.Caption = '状态'
            Width = 53
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lwithdraw_flag'
            PickList.Strings = ()
            Title.Caption = '登录站点'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Sstatus4'
            PickList.Strings = ()
            Title.Caption = '操作员登录状态'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '查询权限'
            Width = 80
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 676
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Labeloper_code1: TLabel
          Left = 190
          Top = 10
          Width = 60
          Height = 12
          Caption = '操作员代码'
          Visible = False
        end
        object Label5: TLabel
          Left = 14
          Top = 10
          Width = 24
          Height = 12
          Caption = '状态'
        end
        object WVComboBox1: TWVComboBox
          Left = 261
          Top = 5
          Width = 116
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          MaxLength = 8
          TabOrder = 0
          Text = '<查询.操作员代码>'
          Visible = False
          WorkView = WorkView
          FieldName = '查询.操作员代码'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-30'
        end
        object WVComboBox3: TWVComboBox
          Left = 45
          Top = 5
          Width = 116
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          MaxLength = 8
          TabOrder = 1
          Text = '<查询.状态>'
          WorkView = WorkView
          FieldName = '查询.状态'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*62'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 676
        TabOrder = 2
        inherited btnOK: TBitBtn
          Left = 500
        end
        inherited btnCancel: TBitBtn
          Left = 588
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 436
        Height = 418
        Align = alLeft
        BevelOuter = bvNone
        ParentColor = True
        TabOrder = 0
        object Labelemail8: TLabel
          Left = 226
          Top = 188
          Width = 48
          Height = 12
          Caption = '电子邮件'
        end
        object Labeladdr6: TLabel
          Left = 249
          Top = 229
          Width = 24
          Height = 12
          Caption = '邮编'
        end
        object Labelphone4: TLabel
          Left = 41
          Top = 189
          Width = 24
          Height = 12
          Caption = '电话'
        end
        object lblpwd: TLabel
          Left = 41
          Top = 148
          Width = 24
          Height = 12
          Caption = '密码'
        end
        object Labeloper_name3: TLabel
          Left = 41
          Top = 69
          Width = 24
          Height = 12
          Caption = '姓名'
        end
        object Labeloper_code2: TLabel
          Left = 5
          Top = 29
          Width = 60
          Height = 12
          Caption = '操作员代码'
        end
        object Labelif_station9: TLabel
          Left = 226
          Top = 70
          Width = 48
          Height = 12
          Caption = '限制站点'
        end
        object Labelif_access10: TLabel
          Left = 18
          Top = 307
          Width = 48
          Height = 12
          Caption = '查询权限'
        end
        object lblrepwd: TLabel
          Left = 226
          Top = 148
          Width = 48
          Height = 12
          Caption = '密码校验'
        end
        object Labelmobile5: TLabel
          Left = 41
          Top = 229
          Width = 24
          Height = 12
          Caption = '手机'
        end
        object Label1: TLabel
          Left = 238
          Top = 109
          Width = 36
          Height = 12
          Caption = '网点号'
        end
        object Label2: TLabel
          Left = 41
          Top = 109
          Width = 24
          Height = 12
          Caption = '类型'
        end
        object Label3: TLabel
          Left = 26
          Top = 365
          Width = 48
          Height = 12
          Caption = '充值限额'
          Visible = False
        end
        object Label4: TLabel
          Left = 41
          Top = 269
          Width = 24
          Height = 12
          Caption = '地址'
        end
        object Labelmenu_set14: TLabel
          Left = 226
          Top = 27
          Width = 48
          Height = 12
          Caption = '操作模板'
        end
        object WVEditemail8: TWVEdit
          Left = 283
          Top = 185
          Width = 136
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 9
          Text = '<电子邮件>'
          WorkView = WorkView
          FieldName = '电子邮件'
          SynchronizeWhenExit = True
        end
        object WVEditaddr6: TWVEdit
          Left = 283
          Top = 225
          Width = 136
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 11
          Text = '<邮编>'
          WorkView = WorkView
          FieldName = '邮编'
          SynchronizeWhenExit = True
        end
        object WVEditphone4: TWVEdit
          Left = 72
          Top = 185
          Width = 126
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 8
          Text = '<电话>'
          WorkView = WorkView
          FieldName = '电话'
          SynchronizeWhenExit = True
        end
        object edtPwd: TWVEdit
          Left = 72
          Top = 144
          Width = 126
          Height = 20
          Color = clBtnHighlight
          MaxLength = 6
          PasswordChar = '*'
          ReadOnly = False
          TabOrder = 7
          SynchronizeWhenExit = True
        end
        object WVEditoper_name3: TWVEdit
          Left = 72
          Top = 65
          Width = 126
          Height = 20
          Hint = '字母或数字，长度10位：长度32位'
          Color = clInfoBk
          MaxLength = 32
          ReadOnly = False
          TabOrder = 3
          Text = '<操作员姓名>'
          WorkView = WorkView
          FieldName = '操作员姓名'
          SynchronizeWhenExit = True
        end
        object WVEditoper_code2: TWVEdit
          Left = 72
          Top = 25
          Width = 126
          Height = 20
          Hint = '字母或数字，长度10位'
          Color = clInfoBk
          MaxLength = 11
          ReadOnly = False
          TabOrder = 1
          Text = '<操作员代码>'
          WorkView = WorkView
          FieldName = '操作员代码'
          SynchronizeWhenExit = True
        end
        object WVComboBoxif_station9: TWVComboBox
          Left = 283
          Top = 64
          Width = 136
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '是否限制访问站点'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '2'
        end
        object WVComboBoxif_access10: TWVComboBox
          Left = 72
          Top = 303
          Width = 126
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          ItemHeight = 12
          TabOrder = 13
          WorkView = WorkView
          FieldName = '查询类型'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*245'
        end
        object edtPwdCheck: TWVEdit
          Left = 283
          Top = 143
          Width = 136
          Height = 20
          Color = 14999516
          MaxLength = 6
          PasswordChar = '*'
          ReadOnly = False
          TabOrder = 6
          OnKeyDown = edtPwdCheckKeyDown
        end
        object WVEditmobile5: TWVEdit
          Left = 72
          Top = 225
          Width = 126
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 10
          Text = '<手机>'
          WorkView = WorkView
          FieldName = '手机'
          SynchronizeWhenExit = True
        end
        object cbbNetInfo: TWVComboBox
          Left = 283
          Top = 103
          Width = 136
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 5
          WorkView = WorkView
          FieldName = '网点号'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-2'
        end
        object cbbType: TWVComboBox
          Left = 72
          Top = 103
          Width = 126
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '操作员类型'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*108'
        end
        object edtMoneyLimit: TWVDigitalEdit
          Left = 84
          Top = 360
          Width = 133
          Height = 20
          AllowPoint = True
          AllowNegative = True
          UserSeprator = True
          Precision = 0
          MaxIntLen = 10
          Color = clInfoBk
          ParentColor = False
          TabOrder = 14
          TabStop = True
          Text = '0'
          Visible = False
          WorkView = WorkView
          FieldName = '充值限额'
          SynchronizeByValue = True
        end
        object WVEdit1: TWVEdit
          Left = 71
          Top = 265
          Width = 347
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 12
          Text = '<地址>'
          WorkView = WorkView
          FieldName = '地址'
          SynchronizeWhenExit = True
        end
        object WVComboBoxmenu_set14: TWVComboBox
          Left = 283
          Top = 23
          Width = 136
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '权限模板'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-29'
        end
      end
      object Panel3: TPanel
        Left = 436
        Top = 0
        Width = 240
        Height = 418
        Align = alClient
        BevelOuter = bvNone
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        inline faAuth1: TfaAuth
          Width = 240
          Height = 418
          Align = alClient
          inherited TreeView: TTreeView
            Width = 240
            Height = 418
          end
          inherited ImageList: TImageList
            Left = 200
            Top = 56
          end
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 148
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
        DefaultValue = '3'
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
        DefaultValue = '2'
      end
      item
        Name = '查询.操作员代码'
        Caption = '查询.操作员代码'
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
        Checker.Required = False
        GetPrevChar = '*'
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
        DataField = 'sstatus3'
      end
      item
        Name = '操作员代码'
        Caption = '操作员代码'
        FieldType = wftUndefined
        Features.Strings = ()
        Hint = '字母或数字，长度10位'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 1
        Checker.MaxLength = 11
        Checker.AcceptOther = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'scust_no'
      end
      item
        Name = '操作员姓名'
        Caption = '操作员姓名'
        FieldType = wftUndefined
        Features.Strings = ()
        Hint = '字母或数字，长度10位：长度32位'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 1
        Checker.MaxLength = 32
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sname'
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
        Name = '邮编'
        Caption = '邮编'
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
        DataField = 'spost_code'
      end
      item
        Name = '电子邮件'
        Caption = '电子邮件'
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
        DataField = 'semail'
      end
      item
        Name = '是否限制访问站点'
        Caption = '是否限制访问站点'
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
        Name = '操作员状态'
        Caption = '操作员状态'
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
        Name = '操作员密码'
        Caption = '操作员密码'
        FieldType = wftUndefined
        DomainName = '操作员密码*'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'stx_pwd'
      end
      item
        Name = '功能权限'
        Caption = '功能权限'
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
        DataField = 'usset1'
      end
      item
        Name = '菜单权限1'
        Caption = '菜单权限1'
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
        Name = '菜单权限2'
        Caption = '菜单权限2'
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
        DataField = 'vsvarstr1'
      end
      item
        Name = '菜单权限3'
        Caption = '菜单权限3'
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
        Name = '菜单权限4'
        Caption = '菜单权限4'
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
        DataField = 'vsvarstr3'
      end
      item
        Name = '操作类别'
        Caption = '操作类别'
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
        DataField = 'sstatus0'
      end
      item
        Name = '权限模板结果集'
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
        Name = '权限模板'
        Caption = '权限模板'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        OnValueChanged = WorkViewWorkFields20ValueChanged
      end
      item
        Name = '网点号'
        Caption = '网点号'
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
        DataField = 'lbank_acc_type2'
      end
      item
        Name = '操作员类型'
        Caption = '操作员类型'
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
        GroupIndex = 1
        DataField = 'sstatus2'
      end
      item
        Name = '充值限额'
        Caption = '充值限额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'damt0'
      end
      item
        Name = '查询类型'
        Caption = '查询类型'
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
        DataField = 'lvol1'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|查询.操作员代码|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|操作员代码|操作员姓名|电话|手机|地址|邮编|电子邮件|是否限制访问' +
          '站点|操作员状态|功能权限|'
        GroupIndex = 1
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 24
    Top = 16
  end
  inherited QueryRequest: TWVRequest
    ID = '操作员查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作员代码'
        FieldName = '查询.操作员代码'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end
      item
        ParamName = '状态'
        FieldName = '查询.状态'
      end>
    Left = 152
    Top = 16
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sstatus1'
        WVFieldName = '是否限制访问站点'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'sstatus3'
        WVFieldName = '操作员状态'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '62'
      end
      item
        FieldName = 'lcert_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-2'
      end
      item
        FieldName = 'sstatus2'
        WVFieldName = '操作员类型'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '108'
      end
      item
        FieldName = 'lbank_acc_type2'
        WVFieldName = '所属网点'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-2'
      end
      item
        FieldName = 'sstatus4'
        WVFieldName = '操作员登录状态'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '111'
      end
      item
        FieldName = 'lwithdraw_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-33'
      end
      item
        FieldName = 'lvol1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '245'
      end>
    Left = 116
    Top = 351
  end
  inherited AddRequest: TWVRequest
    ID = '设置操作员'
    Bindings = <
      item
        ParamName = '操作员代码'
        FieldName = '操作员代码'
      end
      item
        ParamName = '操作员姓名'
        FieldName = '操作员姓名'
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
        ParamName = '地址'
        FieldName = '地址'
      end
      item
        ParamName = '邮编'
        FieldName = '邮编'
      end
      item
        ParamName = '电子邮件'
        FieldName = '电子邮件'
      end
      item
        ParamName = '是否限制访问站点'
        FieldName = '是否限制访问站点'
      end
      item
        ParamName = '操作员状态'
        FieldName = '操作员状态'
      end
      item
        ParamName = '操作员密码'
        FieldName = '操作员密码'
      end
      item
        ParamName = '功能权限'
        FieldName = '功能权限'
      end
      item
        ParamName = '菜单权限1'
        FieldName = '菜单权限1'
      end
      item
        ParamName = '菜单权限2'
        FieldName = '菜单权限2'
      end
      item
        ParamName = '菜单权限3'
        FieldName = '菜单权限3'
      end
      item
        ParamName = '菜单权限4'
        FieldName = '菜单权限4'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
        DefaultValue = '1'
      end
      item
        ParamName = '网点号'
        FieldName = '网点号'
      end
      item
        ParamName = '操作员类型'
        FieldName = '操作员类型'
      end
      item
        ParamName = '充值限额'
        FieldName = '充值限额'
      end
      item
        ParamName = '查询类型'
        FieldName = '查询类型'
      end>
    Left = 56
    Top = 16
  end
  inherited DeleteRequest: TWVRequest
    ID = '设置操作员'
    Bindings = <
      item
        ParamName = '操作员代码'
        FieldName = '操作员代码'
      end
      item
        ParamName = '操作员姓名'
        FieldName = '操作员姓名'
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
        ParamName = '地址'
        FieldName = '地址'
      end
      item
        ParamName = '邮编'
        FieldName = '邮编'
      end
      item
        ParamName = '电子邮件'
        FieldName = '电子邮件'
      end
      item
        ParamName = '是否限制访问站点'
        FieldName = '是否限制访问站点'
      end
      item
        ParamName = '操作员状态'
        FieldName = '操作员状态'
      end
      item
        ParamName = '操作员密码'
        FieldName = '操作员密码'
      end
      item
        ParamName = '功能权限'
        FieldName = '功能权限'
      end
      item
        ParamName = '菜单权限1'
        FieldName = '菜单权限1'
      end
      item
        ParamName = '菜单权限2'
        FieldName = '菜单权限2'
      end
      item
        ParamName = '菜单权限3'
        FieldName = '菜单权限3'
      end
      item
        ParamName = '菜单权限4'
        FieldName = '菜单权限4'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
        DefaultValue = '3'
      end
      item
        ParamName = '网点号'
        FieldName = '网点号'
      end
      item
        ParamName = '操作员类型'
        FieldName = '操作员类型'
      end
      item
        ParamName = '充值限额'
        FieldName = '充值限额'
      end
      item
        ParamName = '查询类型'
        FieldName = '查询类型'
        DefaultValue = 0
      end>
    Left = 88
    Top = 16
  end
  inherited ChangeRequest: TWVRequest
    ID = '设置操作员'
    Bindings = <
      item
        ParamName = '操作员代码'
        FieldName = '操作员代码'
      end
      item
        ParamName = '操作员姓名'
        FieldName = '操作员姓名'
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
        ParamName = '地址'
        FieldName = '地址'
      end
      item
        ParamName = '邮编'
        FieldName = '邮编'
      end
      item
        ParamName = '电子邮件'
        FieldName = '电子邮件'
      end
      item
        ParamName = '是否限制访问站点'
        FieldName = '是否限制访问站点'
      end
      item
        ParamName = '操作员状态'
        FieldName = '操作员状态'
      end
      item
        ParamName = '操作员密码'
        FieldName = '操作员密码'
      end
      item
        ParamName = '功能权限'
        FieldName = '功能权限'
      end
      item
        ParamName = '菜单权限1'
        FieldName = '菜单权限1'
      end
      item
        ParamName = '菜单权限2'
        FieldName = '菜单权限2'
      end
      item
        ParamName = '菜单权限3'
        FieldName = '菜单权限3'
      end
      item
        ParamName = '菜单权限4'
        FieldName = '菜单权限4'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
        DefaultValue = '2'
      end
      item
        ParamName = '网点号'
        FieldName = '网点号'
      end
      item
        ParamName = '充值限额'
        FieldName = '充值限额'
      end
      item
        ParamName = '操作员类型'
        FieldName = '操作员类型'
      end
      item
        ParamName = '查询类型'
        FieldName = '查询类型'
      end>
    Left = 120
    Top = 16
  end
  inherited WVDataSource: TWVDataSource
    Left = 420
    Top = 23
  end
  inherited alDatasetActions: TActionList
    Left = 180
    Top = 348
  end
  object QryModuleAuth: TWVRequest
    WorkView = WorkView
    ID = '权限模板查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '权限模板结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '模板代码'
        FieldName = '权限模板'
      end>
    AfterExec = CheckReturnData
    Left = 464
    Top = 24
  end
  object DataSource1: TDataSource
    Left = 532
    Top = 23
  end
  object WVDBBinder1: TWVDBBinder
    DataSource = DataSource1
    WorkView = WorkView
    FieldName = '权限模板结果集'
    Bindings = <>
    HideUnbindingFields = False
    Left = 500
    Top = 23
  end
end
