inherited faqhwaterCardPatch: TfaqhwaterCardPatch
  Width = 789
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 432
    Width = 789
    Height = 57
    object RzStatusPane1: TRzStatusPane [0]
      Left = 0
      Top = 35
      Width = 789
      Height = 22
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
    inherited btnQuery: TBitBtn
      Left = 581
      Top = 5
    end
    inherited btnPrint: TBitBtn
      Left = 19
      Visible = False
    end
    object btnPacth: TBitBtn
      Left = 673
      Top = 5
      Width = 106
      Height = 25
      Hint = '为写卡操作失败后提供的补写卡信息的方法'
      Anchors = [akTop, akRight]
      Caption = '补写水控信息'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnPacthClick
    end
    object btnReadCardQuery: TBitBtn
      Left = 482
      Top = 5
      Width = 85
      Height = 25
      Hint = '为写卡操作失败后提供的补写卡信息的方法'
      Anchors = [akTop, akRight]
      Caption = '读卡查询'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnReadCardQueryClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 789
    inherited Image1: TImage
      Width = 789
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 789
    Height = 29
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label2: TLabel
      Left = 14
      Top = 10
      Width = 42
      Height = 12
      Caption = '学/工号'
    end
    object Label1: TLabel
      Left = 158
      Top = 10
      Width = 24
      Height = 12
      Caption = '卡号'
    end
    object Label3: TLabel
      Left = 289
      Top = 10
      Width = 24
      Height = 12
      Caption = '姓名'
    end
    object Label4: TLabel
      Left = 413
      Top = 10
      Width = 48
      Height = 12
      Caption = '身份证号'
    end
    object Label5: TLabel
      Left = 593
      Top = 10
      Width = 48
      Height = 12
      Caption = '显示卡号'
    end
    object WVEdit2: TWVEdit
      Left = 60
      Top = 4
      Width = 93
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 0
      Text = '<学工号>'
      WorkView = WorkView
      FieldName = '学工号'
    end
    object edtCardNo: TWVEdit
      Left = 188
      Top = 4
      Width = 93
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<卡号>'
      WorkView = WorkView
      FieldName = '卡号'
    end
    object WVEdit3: TWVEdit
      Left = 315
      Top = 4
      Width = 94
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<姓名>'
      WorkView = WorkView
      FieldName = '姓名'
    end
    object WVEdit4: TWVEdit
      Left = 468
      Top = 5
      Width = 120
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 3
      Text = '<身份证号>'
      WorkView = WorkView
      FieldName = '身份证号'
    end
    object WVEdit1: TWVEdit
      Left = 644
      Top = 4
      Width = 120
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 4
      Text = '<显示卡号>'
      WorkView = WorkView
      FieldName = '显示卡号'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 47
    Width = 789
    Height = 385
    inherited Grid: TRzDBGrid
      Width = 789
      Height = 385
      Columns = <
        item
          Expanded = False
          FieldName = 'Lvol2'
          PickList.Strings = ()
          Title.Caption = '交易码'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Caption = '客户号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Scust_auth'
          PickList.Strings = ()
          Title.Caption = '学工号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Sname'
          PickList.Strings = ()
          Title.Caption = '客户姓名'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no'
          PickList.Strings = ()
          Title.Caption = '显示卡号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = '交易卡号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Caption = '钱包号'
          Width = 40
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol1'
          PickList.Strings = ()
          Title.Caption = '客户类型'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol5'
          PickList.Strings = ()
          Title.Caption = '收费类别'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Caption = '可用余额'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Caption = '有效期'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no2'
          PickList.Strings = ()
          Title.Caption = '单位'
          Width = 100
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
        Name = '学工号'
        Caption = '学工号'
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
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '姓名'
        Caption = '姓名'
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
        Name = '身份证号'
        Caption = '身份证号'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|物理卡号|交易卡号|交易代码|入卡值|操作员代码|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 84
    Top = 151
  end
  inherited MainRequest: TWVRequest
    ID = '补写水控信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '身份证号'
        FieldName = '身份证号'
      end
      item
        ParamName = '显示卡号'
        FieldName = '显示卡号'
      end
      item
        ParamName = '姓名'
        FieldName = '姓名'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end>
    Left = 128
    Top = 152
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'scust_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '39'
      end
      item
        FieldName = 'lvol1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-34'
      end
      item
        FieldName = 'scust_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-38'
      end>
    Left = 168
    Top = 152
  end
  inherited DataSource: TDataSource
    Left = 208
    Top = 152
  end
  object WorkView2: TWorkView
    WorkFields = <
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
        GroupIndex = 1
        DataField = 'damt2'
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
        Name = '显示卡号'
        Caption = '显示卡号'
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
        Name = '卡密码'
        Caption = '卡密码'
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
        Name = '客户类型'
        Caption = '客户类型'
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
        Name = '收费类型'
        Caption = '收费类型'
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
        Name = '截至日期'
        Caption = '截至日期'
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
        Name = '身份证号'
        Caption = '身份证号'
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
        Name = '部门代码'
        Caption = '部门代码'
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
        Name = '性别'
        Caption = '性别'
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
      end
      item
        Name = '图书证号'
        Caption = '图书证号'
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
        Name = '客户名称'
        Caption = '客户名称'
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
        GroupIndex = 1
        DataField = 'damt1'
      end
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
        GroupIndex = 1
        DataField = 'sbank_acc'
      end
      item
        Name = '操作员号'
        Caption = '操作员号'
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
        GroupIndex = 1
        DataField = 'lvol6'
      end
      item
        Name = '交易次数'
        Caption = '交易次数'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol8'
      end
      item
        Name = '设备号'
        Caption = '设备号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol7'
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
      end
      item
        Name = '钱包号'
        Caption = '钱包号'
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
    Left = 80
    Top = 200
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '补写水控信息'
    Bindings = <
      item
        ParamName = '卡标识'
        FieldName = '卡标识'
      end
      item
        ParamName = '入卡值'
        FieldName = '入卡值'
      end
      item
        ParamName = '物理卡号'
        FieldName = '物理卡号'
      end
      item
        ParamName = '操作员号'
        FieldName = '操作员号'
      end
      item
        ParamName = '工作站号'
        FieldName = '工作站号'
      end
      item
        ParamName = '交易次数'
        FieldName = '交易次数'
      end
      item
        ParamName = '设备号'
        FieldName = '设备号'
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
        ParamName = '出卡值'
        FieldName = '出卡值'
        Direction = bdParam2Field
      end
      item
        ParamName = '搭伙费'
        FieldName = '搭伙费'
        Direction = bdParam2Field
      end
      item
        ParamName = '交易卡号'
        FieldName = '交易卡号'
        Direction = bdParam2Field
      end
      item
        ParamName = '显示卡号'
        FieldName = '显示卡号'
        Direction = bdParam2Field
      end
      item
        ParamName = '卡密码'
        FieldName = '卡密码'
        Direction = bdParam2Field
      end
      item
        ParamName = '客户类型'
        FieldName = '客户类型'
        Direction = bdParam2Field
      end
      item
        ParamName = '收费类型'
        FieldName = '收费类型'
        Direction = bdParam2Field
      end
      item
        ParamName = '截至日期'
        FieldName = '截至日期'
        Direction = bdParam2Field
      end
      item
        ParamName = '图书证号'
        FieldName = '图书证号'
        Direction = bdParam2Field
      end
      item
        ParamName = '后台交易流水号'
        FieldName = '后台交易流水号'
        Direction = bdParam2Field
      end
      item
        ParamName = '部门代码'
        FieldName = '部门代码'
        Direction = bdParam2Field
      end
      item
        ParamName = '身份证号'
        FieldName = '身份证号'
        Direction = bdParam2Field
      end
      item
        ParamName = '性别'
        FieldName = '性别'
        Direction = bdParam2Field
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
        Direction = bdParam2Field
      end
      item
        ParamName = '客户名称'
        FieldName = '客户名称'
        Direction = bdParam2Field
      end
      item
        ParamName = '钱包号'
        FieldName = '钱包号'
      end>
    Left = 128
    Top = 200
  end
  object WVRReCreCardOK: TWVRequest
    WorkView = WVReCreCardOK
    ID = '补写水控信息确认'
    Bindings = <
      item
        ParamName = '卡标识'
        FieldName = '卡标识'
      end
      item
        ParamName = '交易码'
        FieldName = '交易码'
      end
      item
        ParamName = '交易流水号'
        FieldName = '交易流水号'
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
        ParamName = '钱包号'
        FieldName = '钱包号'
      end>
    Left = 128
    Top = 248
  end
  object WVReCreCardOK: TWorkView
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
        DataField = 'lserial0'
      end
      item
        Name = '交易流水号'
        Caption = '交易流水号'
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
        Name = '钱包号'
        Caption = '钱包号'
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
    Left = 80
    Top = 248
  end
  object WorkView3: TWorkView
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    Left = 80
    Top = 296
  end
  object WVRequest3: TWVRequest
    WorkView = WorkView3
    ID = '修改水控状态'
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
    Left = 128
    Top = 296
  end
end
