inherited faqhfillBusiSaveMoney: TfaqhfillBusiSaveMoney
  Width = 667
  Height = 569
  inherited UIPanel1: TUIPanel
    Top = 517
    Width = 667
    Height = 52
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 90
      Enabled = False
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 177
      Visible = False
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 31
      Width = 667
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
      TabOrder = 2
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 667
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
    Width = 667
    inherited Image1: TImage
      Width = 667
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 667
    Height = 499
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object grp1: TGroupBox
      Left = 168
      Top = 72
      Width = 393
      Height = 185
      Caption = '商户存款信息'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object lbl1: TRzLabel
        Left = 32
        Top = 31
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '商户名称'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel1: TRzLabel
        Left = 32
        Top = 151
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '存款金额'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel16: TRzLabel
        Left = 32
        Top = 55
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '提成比例'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object lblBl: TRzLabel
        Left = 128
        Top = 54
        Width = 224
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel18: TRzLabel
        Left = 32
        Top = 78
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '帐户余额'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object lblAccMoney: TRzLabel
        Left = 128
        Top = 77
        Width = 224
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object lbl2: TLabel
        Left = 360
        Top = 59
        Width = 7
        Height = 14
        Caption = '%'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label1: TLabel
        Left = 360
        Top = 83
        Width = 14
        Height = 14
        Caption = '元'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label2: TLabel
        Left = 360
        Top = 155
        Width = 14
        Height = 14
        Caption = '元'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object RzLabel4: TRzLabel
        Left = 32
        Top = 103
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '充值类型'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel5: TRzLabel
        Left = 32
        Top = 127
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '票据号码'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object edtSveMoney: TWVDigitalEdit
        Left = 128
        Top = 151
        Width = 224
        Height = 22
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        TabOrder = 3
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '存款金额'
        SynchronizeByValue = True
      end
      object cbbBusiName: TWVComboBox
        Left = 128
        Top = 30
        Width = 225
        Height = 22
        Style = csDropDownList
        Color = clInfoBk
        DropDownCount = 20
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ImeName = '紫光拼音输入法'
        ItemHeight = 14
        ParentFont = False
        TabOrder = 0
        OnChange = cbbBusiNameChange
        WorkView = WorkView
        FieldName = '商户号'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-50'
      end
      object cbbType: TWVComboBox
        Left = 128
        Top = 102
        Width = 225
        Height = 22
        Style = csDropDownList
        Color = clWhite
        DropDownCount = 20
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ImeName = '紫光拼音输入法'
        ItemHeight = 14
        ParentFont = False
        TabOrder = 1
        OnChange = cbbTypeChange
        WorkView = WorkView
        FieldName = '充值类型'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '63'
      end
      object edtTicketNo: TRzEdit
        Left = 127
        Top = 126
        Width = 224
        Height = 22
        DisabledColor = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        TabOrder = 2
      end
    end
    object grpSuccInfo: TGroupBox
      Left = 168
      Top = 264
      Width = 393
      Height = 201
      Caption = '存款成功信息'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      object RzLabel2: TRzLabel
        Left = 32
        Top = 47
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '商户号'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel3: TRzLabel
        Left = 32
        Top = 70
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '商户名称'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel6: TRzLabel
        Left = 32
        Top = 22
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '后台流水号'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel8: TRzLabel
        Left = 32
        Top = 94
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '交易日期'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel10: TRzLabel
        Left = 32
        Top = 142
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '提成金额'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel12: TRzLabel
        Left = 32
        Top = 166
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '帐户余额'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object RzLabel14: TRzLabel
        Left = 32
        Top = 118
        Width = 87
        Height = 22
        Alignment = taRightJustify
        AutoSize = False
        Caption = '存款金额'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        BorderOuter = fsStatus
        Rotation = roFlat
      end
      object Label3: TLabel
        Left = 360
        Top = 149
        Width = 14
        Height = 14
        Caption = '元'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel
        Left = 360
        Top = 173
        Width = 14
        Height = 14
        Caption = '元'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label5: TLabel
        Left = 360
        Top = 125
        Width = 14
        Height = 14
        Caption = '元'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object edtSeriId: TRzEdit
        Left = 129
        Top = 22
        Width = 224
        Height = 22
        Color = 16184303
        DisabledColor = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
      end
      object edtBusiId: TRzEdit
        Left = 129
        Top = 46
        Width = 224
        Height = 22
        Color = 16184303
        DisabledColor = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
      end
      object edtBusiName: TRzEdit
        Left = 129
        Top = 70
        Width = 224
        Height = 22
        Color = 16184303
        DisabledColor = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
      end
      object edtDate: TRzEdit
        Left = 129
        Top = 94
        Width = 224
        Height = 22
        Color = 16184303
        DisabledColor = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 3
      end
      object edtTc: TRzEdit
        Left = 129
        Top = 142
        Width = 224
        Height = 22
        Color = 16184303
        DisabledColor = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 5
      end
      object edtAccMoney: TRzEdit
        Left = 129
        Top = 166
        Width = 224
        Height = 22
        Color = 16184303
        DisabledColor = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 6
      end
      object edtSaveMoney: TRzEdit
        Left = 129
        Top = 118
        Width = 224
        Height = 22
        Color = 16184303
        DisabledColor = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 4
      end
    end
    object btnSaveMoney: TImageButton
      Left = 466
      Top = 467
      Width = 95
      Height = 25
      Caption = '商户存款(&S)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnSaveMoneyClick
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 696
    Top = 432
    Width = 56
    Height = 33
    Align = alNone
    TabOrder = 2
    Visible = False
    inherited Grid: TRzDBGrid
      Align = alNone
      Columns = <
        item
          Expanded = False
          FieldName = 'semp_pwd'
          PickList.Strings = ()
          Title.Caption = '错账操作员密码'
          Visible = True
        end>
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
      end
      item
        Name = '商户号'
        Caption = '商户号'
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
        Name = '存款金额'
        Caption = '存款金额'
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
        GetPrevChar = '*'
      end
      item
        Name = '交易日期'
        Caption = '交易日期'
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
        Name = '操作员号'
        Caption = '操作员号'
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
        Name = '后台流水号'
        Caption = '后台流水号'
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
        Name = '商户名称'
        Caption = '商户名称'
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
        Name = '提成金额'
        Caption = '提成金额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '帐户余额'
        Caption = '帐户余额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '充值类型'
        Caption = '充值类型'
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
        Name = '票据号码'
        Caption = '票据号码'
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
        MonitorValueChangedFields = '|商户号|存款金额|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 308
    Top = 31
  end
  inherited MainRequest: TWVRequest
    ID = '充值商户存款'
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
        ParamName = '商户号'
        FieldName = '商户号'
        Direction = bdBiDirection
      end
      item
        ParamName = '存款金额'
        FieldName = '存款金额'
        Direction = bdBiDirection
      end
      item
        ParamName = '操作员号'
        FieldName = '操作员号'
        Direction = bdParam2Field
      end
      item
        ParamName = '后台流水号'
        FieldName = '后台流水号'
        Direction = bdParam2Field
      end
      item
        ParamName = '交易日期'
        FieldName = '交易日期'
        Direction = bdParam2Field
      end
      item
        ParamName = '商户名称'
        FieldName = '商户名称'
        Direction = bdParam2Field
      end
      item
        ParamName = '提成金额'
        FieldName = '提成金额'
        Direction = bdParam2Field
      end
      item
        ParamName = '帐户余额'
        FieldName = '帐户余额'
        Direction = bdParam2Field
      end
      item
        ParamName = '票据号码'
        FieldName = '票据号码'
      end
      item
        ParamName = '充值类型'
        FieldName = '充值类型'
      end>
    Left = 344
    Top = 32
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 392
    Top = 32
  end
  inherited DataSource: TDataSource
    Left = 432
    Top = 32
  end
  object WorkView1: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        FieldType = wftUndefined
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
        Name = '查询.商户号'
        Caption = '查询.商户号'
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
        Name = '操作标志'
        Caption = '操作标志'
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
          '|查询.商户名称|查询.商户负责人名称|查询.商户证件类型|查询.商户证' +
          '件号码|查询.商户提成比率|查询.操作员号|'
      end
      item
        MonitorValueChangedFields = '|商户号|商户名称|商户负责人名称|商户证件类型|商户证件号码|'
      end>
    Left = 48
    Top = 40
  end
  object QueryRequest: TWVRequest
    WorkView = WorkView1
    ID = '商户信息主键查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '商户标识'
        FieldName = '查询.商户号'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end>
    Left = 88
    Top = 40
  end
end
