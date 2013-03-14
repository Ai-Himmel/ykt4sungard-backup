inherited faqhEPurseReg: TfaqhEPurseReg
  Width = 700
  Height = 536
  inherited UIPanel1: TUIPanel
    Top = 480
    Width = 700
    Height = 56
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 437
      Top = 5
      Enabled = False
      TabOrder = 1
    end
    inherited btnPrint: TBitBtn
      Left = 610
      Top = 5
      TabOrder = 3
    end
    object btnReg: TBitBtn
      Left = 523
      Top = 5
      Width = 79
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '开户(&R)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnRegClick
      Glyph.Data = {
        36030000424D3603000000000000360000002800000010000000100000000100
        18000000000000030000120B0000120B00000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        006E41006E41006E41006E41006E41006E41006E41006E41FFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF006E41FEE5D6FEE3D2FEDDC7FEDAC1FE
        D9BFFED6C2006E41FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        006E41FEF3EAFEF2E6FEE9D6FEE6CFFEE5CBFEDCCE006E41FFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF006E41FEF8F2FEF3EAFEECDAFEE9D6FE
        E6CFFEDDD1006E41FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        006E41FEF9F4FEF8F2FEEFE0FEECDAFEE9D6FEDCD1006E41006E41006E41006E
        41006E41FFFFFFFFFFFFFFFFFFFFFFFF006E41FEFDFCFEF9F4FEF2E6FEEFE0FE
        E6D7FED2CB006E41F1E5CFF1E5CFF1E5CF006E41FFFFFFFFFFFFFFFFFFFFFFFF
        006E41FFFFFFFEFDFCFEF3EA006E41006E41006E41006E41F2E7D4F2E6D3F2E6
        D3006E41FFFFFFFFFFFFFFFFFFFFFFFF006E41FFFFFFFFFFFFFEF8F2006E41FC
        B654006E41E8D5CAF0ECE2F0ECE2F0ECE2006E41FFFFFFFFFFFFFFFFFFFFFFFF
        006E41FFFFFFFFFFFFFEF9F4006E41006E41E7CEC0FBF9F5787E9E7A9ADDFAF7
        F3006E41FFFFFFFFFFFFFFFFFFFFFFFF006E41006E41006E41006E41006E41EC
        D3C2FFFFFFFFFFFF7B96D08EB5ECFCFAF9006E41FFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFF006E41FFFFFFF9F9F9F7F7F7F6F6F6F4F4F4F3F3F3ECEBE9E9E8E5E9E8
        E5006E41FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF006E41006E41006E41006E4100
        6E41006E41006E41006E41006E41006E41006E41FFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
    end
    object grp1: TGroupBox
      Left = 0
      Top = 0
      Width = 353
      Height = 35
      Align = alLeft
      TabOrder = 0
      object lbl1: TLabel
        Left = 12
        Top = 14
        Width = 48
        Height = 12
        AutoSize = False
        Caption = '帐户密码'
      end
      object Label12: TLabel
        Left = 172
        Top = 14
        Width = 72
        Height = 12
        AutoSize = False
        Caption = '重新输入密码'
      end
      object edtPwd: TWVEdit
        Left = 67
        Top = 10
        Width = 94
        Height = 20
        Color = clWhite
        MaxLength = 6
        PasswordChar = '*'
        ReadOnly = False
        TabOrder = 0
        Text = '<帐户密码>'
        WorkView = WVEPurseReg
        FieldName = '帐户密码'
      end
      object edtRePwd: TWVEdit
        Left = 250
        Top = 10
        Width = 94
        Height = 20
        MaxLength = 6
        PasswordChar = '*'
        ReadOnly = False
        TabOrder = 1
      end
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 35
      Width = 700
      Height = 21
      AutoStyle = False
      BorderColor = clWindow
      BorderInner = fsNone
      BorderOuter = fsNone
      BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
      BorderWidth = 0
      Color = 16184303
      FlatColor = 15458000
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 700
        Height = 21
        FrameStyle = fsStatus
        Align = alClient
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 111
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 49
      Top = 39
      Width = 48
      Height = 12
      Caption = '客户类别'
    end
    object Label2: TLabel
      Left = 280
      Top = 111
      Width = 48
      Height = 12
      Caption = '客户状态'
      Visible = False
    end
    object Label3: TLabel
      Left = 301
      Top = 87
      Width = 24
      Height = 12
      Caption = '校区'
    end
    object Label4: TLabel
      Left = 277
      Top = 15
      Width = 48
      Height = 12
      Caption = '客户姓名'
    end
    object Label5: TLabel
      Left = 283
      Top = 63
      Width = 42
      Height = 12
      Caption = '学/工号'
    end
    object Label6: TLabel
      Left = 480
      Top = 15
      Width = 48
      Height = 12
      Caption = '所属部门'
    end
    object Label8: TLabel
      Left = 73
      Top = 63
      Width = 24
      Height = 12
      Caption = '性别'
    end
    object Label9: TLabel
      Left = 504
      Top = 39
      Width = 24
      Height = 12
      Caption = '民族'
    end
    object Label10: TLabel
      Left = 49
      Top = 87
      Width = 48
      Height = 12
      Caption = '证件号码'
    end
    object Label11: TLabel
      Left = 49
      Top = 111
      Width = 48
      Height = 12
      Caption = '联系电话'
      Visible = False
    end
    object WVLabel2: TWVLabel
      Left = 61
      Top = 15
      Width = 36
      Height = 12
      Caption = '客户号'
    end
    object WVLabel1: TWVLabel
      Left = 493
      Top = 63
      Width = 36
      Height = 12
      Caption = '批次号'
    end
    object Label13: TLabel
      Left = 277
      Top = 39
      Width = 48
      Height = 12
      Caption = '收费类别'
    end
    object WVLabel3: TWVLabel
      Left = 481
      Top = 87
      Width = 48
      Height = 12
      Caption = '电子钱包'
    end
    object WVComboBox1: TWVComboBox
      Left = 112
      Top = 34
      Width = 120
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
      Left = 341
      Top = 106
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 13
      Visible = False
      WorkView = WorkView
      FieldName = '客户状态'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*15'
    end
    object WVComboBox3: TWVComboBox
      Left = 339
      Top = 82
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 10
      WorkView = WorkView
      FieldName = '客户所在区域'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-27'
    end
    object WVEdit4: TWVEdit
      Left = 339
      Top = 10
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<客户名称>'
      WorkView = WorkView
      FieldName = '客户名称'
    end
    object WVEdit5: TWVEdit
      Left = 339
      Top = 58
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 7
      Text = '<联系人学工号>'
      WorkView = WorkView
      FieldName = '联系人学工号'
    end
    object WVComboBox6: TWVComboBox
      Left = 539
      Top = 10
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      WorkView = WorkView
      FieldName = '联系人单位号'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object WVComboBox8: TWVComboBox
      Left = 112
      Top = 58
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView
      FieldName = '联系人性别'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*39'
    end
    object WVComboBox9: TWVComboBox
      Left = 539
      Top = 34
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '联系人民族'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*2001'
    end
    object WVEdit10: TWVEdit
      Left = 112
      Top = 82
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 9
      Text = '<联系人身份证号>'
      WorkView = WorkView
      FieldName = '联系人身份证号'
    end
    object WVEdit11: TWVEdit
      Left = 112
      Top = 106
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 12
      Text = '<联系电话>'
      Visible = False
      WorkView = WorkView
      FieldName = '联系电话'
    end
    object WVEdit2: TWVEdit
      Left = 112
      Top = 10
      Width = 120
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
      Left = 539
      Top = 58
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 8
      Text = '<批次号>'
      WorkView = WorkView
      FieldName = '批次号'
    end
    object WVComboBox4: TWVComboBox
      Left = 339
      Top = 34
      Width = 120
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
    object cbbEPurse: TWVComboBox
      Left = 539
      Top = 82
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 11
      WorkView = WorkView
      FieldName = '电子钱包'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*125'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 129
    Width = 700
    Height = 351
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 351
      Columns = <
        item
          Expanded = False
          FieldName = 'sbranch_code0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '校区'
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
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '学/工号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
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
          Title.Alignment = taCenter
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
          FieldName = 'sdate1'
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
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '预计注销时间'
          Visible = False
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
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Caption = '入学日期'
          Visible = False
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
      end
      item
        Name = '电子钱包'
        Caption = '电子钱包'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sstat_type'
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
        ParamName = '客户类别'
        FieldName = '客户类别'
      end
      item
        ParamName = '客户状态'
        FieldName = '客户状态'
      end
      item
        ParamName = '客户所在区域'
        FieldName = '客户所在区域'
      end
      item
        ParamName = '客户名称'
        FieldName = '客户名称'
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
        ParamName = '批次号'
        FieldName = '批次号'
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
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
        ParamName = '电子钱包'
        FieldName = '电子钱包'
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
  object WVEPurseReg: TWorkView
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
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '帐户密码'
        Caption = '帐户密码'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
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
    Top = 263
  end
  object WVREPurseReg: TWVRequest
    WorkView = WVEPurseReg
    ID = '电子钱包开户'
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
        ParamName = '帐户密码'
        FieldName = '帐户密码'
      end>
    AfterExec = MainRequestAfterExec
    Left = 120
    Top = 264
  end
end
