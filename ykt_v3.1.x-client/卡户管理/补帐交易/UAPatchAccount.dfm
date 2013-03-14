inherited faqhPatchAccount: TfaqhPatchAccount
  Width = 794
  Height = 486
  inherited UIPanel1: TUIPanel
    Top = 429
    Width = 794
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 617
      Top = 6
      TabOrder = 1
    end
    inherited btnPrint: TBitBtn
      Left = 704
      Top = 6
      Hint = '确定'
      TabOrder = 2
    end
    object grp1: TGroupBox
      Left = 0
      Top = 0
      Width = 537
      Height = 36
      Align = alLeft
      TabOrder = 0
      object Label6: TLabel
        Left = 18
        Top = 16
        Width = 48
        Height = 12
        Caption = '发生金额'
      end
      object Label7: TLabel
        Left = 184
        Top = 16
        Width = 36
        Height = 12
        Caption = '复核员'
      end
      object Label8: TLabel
        Left = 343
        Top = 16
        Width = 60
        Height = 12
        Caption = '复核员密码'
      end
      object edtMoney: TWVEdit
        Left = 76
        Top = 11
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 0
        Text = '<发生金额>'
        WorkView = WVPatchAccount
        FieldName = '发生金额'
      end
      object edtChk: TWVEdit
        Left = 228
        Top = 11
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<复核员>'
        WorkView = WVPatchAccount
        FieldName = '复核员'
      end
      object edtChkPwd: TWVEdit
        Left = 413
        Top = 11
        Width = 100
        Height = 20
        Color = clWhite
        PasswordChar = '*'
        ReadOnly = False
        TabOrder = 2
      end
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 794
    inherited Image1: TImage
      Width = 794
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 794
    Height = 30
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 18
      Top = 9
      Width = 48
      Height = 12
      Caption = '交易卡号'
    end
    object Label2: TLabel
      Left = 186
      Top = 9
      Width = 48
      Height = 12
      Caption = '银行帐号'
    end
    object Label3: TLabel
      Left = 410
      Top = 9
      Width = 48
      Height = 12
      Caption = '开始日期'
    end
    object Label4: TLabel
      Left = 578
      Top = 9
      Width = 48
      Height = 12
      Caption = '结束日期'
    end
    object edtCardNo: TWVEdit
      Left = 76
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<交易卡号>'
      WorkView = WorkView
      FieldName = '交易卡号'
    end
    object edtBankCardNo: TWVEdit
      Left = 244
      Top = 5
      Width = 157
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<银行账号>'
      WorkView = WorkView
      FieldName = '银行账号'
    end
    object edtBeginDate: TWVEdit
      Left = 468
      Top = 5
      Width = 101
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<开始日期>'
      WorkView = WorkView
      FieldName = '开始日期'
    end
    object edtEndDate: TWVEdit
      Left = 636
      Top = 5
      Width = 101
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 3
      Text = '<结束日期>'
      WorkView = WorkView
      FieldName = '结束日期'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 48
    Width = 794
    Height = 381
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 794
      Height = 381
      Columns = <
        item
          Expanded = False
          FieldName = 'sbank_pwd'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易日期'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_pwd2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易时间'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '本机流水号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '银行流水号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '本地金额'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '银行金额'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易卡号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '银行卡号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '不平金额'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '状态'
          Width = 60
          Visible = True
        end>
    end
  end
  object StatusBar: TRzStatusBar [4]
    Left = 0
    Top = 465
    Width = 794
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
      Width = 794
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
        Name = '交易卡号'
        Caption = '交易卡号'
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
        Name = '开始日期'
        Caption = '开始日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '结束日期'
        Caption = '结束日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        MonitorValueChangedFields = '|开始日期|'
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '银行账号'
        Caption = '银行账号'
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
        Name = '状态'
        Caption = '状态'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|学号或员工号|交易卡号|姓名|显示卡号|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 60
    Top = 183
  end
  inherited MainRequest: TWVRequest
    ID = '补帐交易查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '交易卡号'
        FieldName = '交易卡号'
      end
      item
        ParamName = '开始日期'
        FieldName = '开始日期'
      end
      item
        ParamName = '结束日期'
        FieldName = '结束日期'
      end
      item
        ParamName = '银行账号'
        FieldName = '银行账号'
      end
      item
        ParamName = '状态'
        FieldName = '状态'
      end>
    Left = 104
    Top = 184
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '3'
      end>
    Left = 144
    Top = 184
  end
  inherited DataSource: TDataSource
    Left = 184
    Top = 184
  end
  object WVRBackState: TWVRequest
    WorkView = WVBackState
    ID = '修改卡状态'
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
        ParamName = '卡标识'
        FieldName = '卡标识'
      end
      item
        ParamName = '后台交易流水号'
        FieldName = '后台交易流水号'
      end
      item
        ParamName = '交易码'
        FieldName = '交易码'
      end>
    Left = 104
    Top = 328
  end
  object WVBackState: TWorkView
    WorkFields = <
      item
        Name = '卡标识'
        Caption = '卡标识'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '后台交易流水号'
        Caption = '后台交易流水号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial1'
      end
      item
        Name = '交易码'
        Caption = '交易码'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol2'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    Left = 56
    Top = 328
  end
  object WVRPatchAccount: TWVRequest
    WorkView = WVPatchAccount
    ID = '补帐交易'
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
        ParamName = '交易卡号'
        FieldName = '交易卡号'
      end
      item
        ParamName = '物理卡号'
        FieldName = '物理卡号'
      end
      item
        ParamName = '入卡值'
        FieldName = '入卡值'
      end
      item
        ParamName = '工作站号'
        FieldName = '工作站号'
      end
      item
        ParamName = '当前卡交易次数'
        FieldName = '当前卡交易次数'
      end
      item
        ParamName = '操作员'
        FieldName = '操作员'
      end
      item
        ParamName = '发生金额'
        FieldName = '发生金额'
      end
      item
        ParamName = '复核员'
        FieldName = '复核员'
      end
      item
        ParamName = '复核员密码'
        FieldName = '复核员密码'
      end
      item
        ParamName = '搭伙费'
        FieldName = '搭伙费'
        Direction = bdParam2Field
      end
      item
        ParamName = '出卡值'
        FieldName = '出卡值'
        Direction = bdParam2Field
      end
      item
        ParamName = '流水号'
        FieldName = '流水号'
        Direction = bdParam2Field
      end
      item
        ParamName = '充值金额'
        FieldName = '充值金额'
        Direction = bdParam2Field
      end
      item
        ParamName = '流水发生日期'
        FieldName = '流水发生日期'
      end
      item
        ParamName = '原流水号'
        FieldName = '原流水号'
      end>
    Left = 104
    Top = 232
  end
  object WVPatchAccount: TWorkView
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
        Name = '交易卡号'
        Caption = '交易卡号'
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
        Name = '物理卡号'
        Caption = '物理卡号'
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
        Name = '入卡值'
        Caption = '入卡值'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '工作站号'
        Caption = '工作站号'
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
        Name = '当前卡交易次数'
        Caption = '当前卡交易次数'
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
        Name = '操作员'
        Caption = '操作员'
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
        Name = '发生金额'
        Caption = '发生金额'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '复核员'
        Caption = '复核员'
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
        Name = '复核员密码'
        Caption = '复核员密码'
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
        Name = '搭伙费'
        Caption = '搭伙费'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '出卡值'
        Caption = '出卡值'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '流水号'
        Caption = '流水号'
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
        Name = '充值金额'
        Caption = '充值金额'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '流水发生日期'
        Caption = '流水发生日期'
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
        Name = '原流水号'
        Caption = '原流水号'
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
    FieldsMonitors = <>
    Left = 56
    Top = 232
  end
end
