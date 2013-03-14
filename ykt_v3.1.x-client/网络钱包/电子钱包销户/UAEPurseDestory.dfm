inherited faqhEPurseDestory: TfaqhEPurseDestory
  Width = 700
  Height = 536
  inherited UIPanel1: TUIPanel
    Top = 481
    Width = 700
    Height = 55
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
      Caption = '销户(&D)'
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
      Width = 177
      Height = 34
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
      object edtPwd: TWVEdit
        Left = 67
        Top = 10
        Width = 94
        Height = 20
        Color = clWhite
        MaxLength = 8
        PasswordChar = '*'
        ReadOnly = False
        TabOrder = 0
        Text = '<帐户密码>'
        WorkView = WVEPurseDestory
        FieldName = '帐户密码'
      end
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 34
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
    Height = 87
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label3: TLabel
      Left = 76
      Top = 39
      Width = 24
      Height = 12
      Caption = '校区'
    end
    object Label4: TLabel
      Left = 485
      Top = 15
      Width = 48
      Height = 12
      Caption = '客户姓名'
    end
    object Label5: TLabel
      Left = 283
      Top = 15
      Width = 42
      Height = 12
      Caption = '学/工号'
    end
    object Label6: TLabel
      Left = 277
      Top = 39
      Width = 48
      Height = 12
      Caption = '所属部门'
    end
    object Label10: TLabel
      Left = 52
      Top = 63
      Width = 48
      Height = 12
      Caption = '止付状态'
    end
    object Label11: TLabel
      Left = 277
      Top = 63
      Width = 48
      Height = 12
      Caption = '开户日期'
    end
    object WVLabel2: TWVLabel
      Left = 64
      Top = 15
      Width = 36
      Height = 12
      Caption = '客户号'
    end
    object WVLabel1: TWVLabel
      Left = 485
      Top = 39
      Width = 48
      Height = 12
      Caption = '证件号码'
    end
    object Label1: TLabel
      Left = 509
      Top = 63
      Width = 24
      Height = 12
      Caption = '帐号'
    end
    object WVComboBox3: TWVComboBox
      Left = 107
      Top = 34
      Width = 146
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '所属区域'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-27'
    end
    object WVEdit4: TWVEdit
      Left = 541
      Top = 10
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<客户姓名>'
      WorkView = WorkView
      FieldName = '客户姓名'
    end
    object WVEdit5: TWVEdit
      Left = 331
      Top = 10
      Width = 146
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<学工号>'
      WorkView = WorkView
      FieldName = '学工号'
    end
    object WVComboBox6: TWVComboBox
      Left = 331
      Top = 34
      Width = 146
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 4
      WorkView = WorkView
      FieldName = '所在部门'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object WVEdit2: TWVEdit
      Left = 107
      Top = 10
      Width = 146
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
      Left = 541
      Top = 34
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 5
      Text = '<证件号码>'
      WorkView = WorkView
      FieldName = '证件号码'
    end
    object WVComboBox1: TWVComboBox
      Left = 107
      Top = 58
      Width = 146
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView
      FieldName = '止付状态'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*126'
    end
    object WVEdit3: TWVEdit
      Left = 331
      Top = 58
      Width = 146
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 7
      Text = '<开户日期>'
      WorkView = WorkView
      FieldName = '开户日期'
    end
    object WVEdit6: TWVEdit
      Left = 541
      Top = 58
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 8
      Text = '<帐号>'
      WorkView = WorkView
      FieldName = '帐号'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 105
    Width = 700
    Height = 376
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 376
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
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '帐号'
          Width = 80
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
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户姓名'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Caption = '开户日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_type'
          PickList.Strings = ()
          Title.Caption = '止付状态'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '帐户余额'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '帐户可用余额'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '帐户冻结余额'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '上次交易日期'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lsafe_level2'
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
          FieldName = 'scert_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '专业'
          Width = 80
          Visible = True
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
          FieldName = 'semail2'
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
        Checker.LowerCase = False
        Checker.UpperCase = False
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
      end
      item
        Name = '客户姓名'
        Caption = '客户姓名'
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
        Name = '所属区域'
        Caption = '所属区域'
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
        Name = '所在部门'
        Caption = '所在部门'
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
        Name = '证件号码'
        Caption = '证件号码'
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
        Name = '止付状态'
        Caption = '止付状态'
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
        Name = '开户日期'
        Caption = '开户日期'
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
        Name = '帐号'
        Caption = '帐号'
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
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 84
    Top = 319
  end
  inherited MainRequest: TWVRequest
    ID = '销户查询'
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
        ParamName = '开户日期'
        FieldName = '开户日期'
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '客户姓名'
        FieldName = '客户姓名'
      end
      item
        ParamName = '所在部门'
        FieldName = '所在部门'
      end
      item
        ParamName = '所属区域'
        FieldName = '所属区域'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '帐号'
        FieldName = '帐号'
      end
      item
        ParamName = '证件号码'
        FieldName = '证件号码'
      end
      item
        ParamName = '止付状态'
        FieldName = '止付状态'
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
        FieldName = 'lsafe_level2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-34'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '15'
      end
      item
        FieldName = 'scust_type2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2001'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '39'
      end
      item
        FieldName = 'scert_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'scert_no2'
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
      end
      item
        FieldName = 'scust_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '126'
      end>
    Left = 192
    Top = 320
  end
  inherited DataSource: TDataSource
    Top = 320
  end
  object WVEPurseDestory: TWorkView
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
      end
      item
        Name = '帐号'
        Caption = '帐号'
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
    Top = 263
  end
  object WVREPurseDestory: TWVRequest
    WorkView = WVEPurseDestory
    ID = '电子钱包销户'
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
      end
      item
        ParamName = '帐号'
        FieldName = '帐号'
      end>
    AfterExec = MainRequestAfterExec
    Left = 120
    Top = 264
  end
end
