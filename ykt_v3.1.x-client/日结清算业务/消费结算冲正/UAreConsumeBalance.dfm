inherited faqhreConsumeBalance: TfaqhreConsumeBalance
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 453
    Width = 700
    Height = 36
    object Label1: TLabel [0]
      Left = 18
      Top = 12
      Width = 48
      Height = 12
      Caption = '操作员号'
    end
    object Label2: TLabel [1]
      Left = 194
      Top = 12
      Width = 24
      Height = 12
      Caption = '密码'
    end
    inherited btnQuery: TBitBtn
      Left = 525
      Top = 6
    end
    inherited btnPrint: TBitBtn
      Left = 614
      Top = 6
      Caption = '结算冲正'
      Glyph.Data = {00000000}
    end
    object edtOperCode: TWVEdit
      Left = 76
      Top = 8
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<操作员号>'
      WorkView = WorkView
      FieldName = '操作员号'
    end
    object WVEdit2: TWVEdit
      Left = 228
      Top = 8
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 3
      Text = '<密码>'
      WorkView = WorkView
      FieldName = '密码'
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
    Height = 29
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label13: TLabel
      Left = 18
      Top = 10
      Width = 60
      Height = 12
      Caption = '操作员代码'
    end
    object WVComboBox1: TWVComboBox
      Left = 85
      Top = 5
      Width = 196
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 0
      FieldName = '操作员代码'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-30'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 47
    Width = 700
    Height = 406
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 406
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = '流水号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Caption = '交易名称'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder1'
          PickList.Strings = ()
          Title.Caption = '发生日期'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Caption = '发生时间'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial2'
          PickList.Strings = ()
          Title.Caption = '操作员'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Caption = '交易金额'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstation0'
          PickList.Strings = ()
          Title.Caption = '出账账号'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstation1'
          PickList.Strings = ()
          Title.Caption = '入账账号'
          Width = 120
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
        GetPrevChar = '*'
      end
      item
        Name = '密码'
        Caption = '密码'
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
        Name = '交易流水号'
        Caption = '交易流水号'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|操作员号|密码|交易流水号|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '消费结算冲正'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作员号'
        FieldName = '操作员号'
      end
      item
        ParamName = '密码'
        FieldName = '密码'
      end
      item
        ParamName = '交易流水号'
        FieldName = '交易流水号'
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    WorkView = WorkView1
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-38'
      end
      item
        FieldName = 'sserial2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-30'
      end>
    Left = 160
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 192
    Top = 256
  end
  object WorkView1: TWorkView
    WorkFields = <
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
      end
      item
        Name = '采集开始日期'
        Caption = '采集开始日期'
        FieldType = wftUndefined
        DomainName = '日期校验*'
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
        Checker.Required = False
        GetPrevChar = '*'
      end
      item
        Name = '采集开始时间'
        Caption = '采集开始时间'
        FieldType = wftUndefined
        DomainName = '时间校验'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        Checker.Required = False
        GetPrevChar = '*'
      end
      item
        Name = '采集结束日期'
        Caption = '采集结束日期'
        FieldType = wftUndefined
        DomainName = '日期校验*'
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
        Checker.Required = False
        GetPrevChar = '*'
      end
      item
        Name = '采集结束时间'
        Caption = '采集结束时间'
        FieldType = wftUndefined
        DomainName = '时间校验'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        Checker.Required = False
        GetPrevChar = '*'
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
        GetPrevChar = '*'
      end
      item
        Name = '上传端流水号'
        Caption = '上传端流水号'
        FieldType = wftUndefined
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
        Name = '交易代码'
        Caption = '交易代码'
        FieldType = wftUndefined
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
        Name = '流水状态'
        Caption = '流水状态'
        FieldType = wftUndefined
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
        Name = '上传工作站标识'
        Caption = '上传工作站标识'
        FieldType = wftUndefined
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
        Name = '交易发生设备标识'
        Caption = '交易发生设备标识'
        FieldType = wftUndefined
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
        GetPrevChar = '*'
      end
      item
        Name = '客户标识'
        Caption = '客户标识'
        FieldType = wftUndefined
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
        Name = '操作员代码'
        Caption = '操作员代码'
        FieldType = wftUndefined
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
        GetPrevChar = '*'
      end
      item
        Name = '设备物理ID'
        Caption = '设备物理ID'
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
        MonitorValidChangedFields = '|采集开始日期|采集开始时间|采集结束日期|采集结束时间|'
      end>
    Left = 92
    Top = 207
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '交易流水详细信息查询解款冲正'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '采集开始日期'
        FieldName = '采集开始日期'
      end
      item
        ParamName = '采集开始时间'
        FieldName = '采集开始时间'
      end
      item
        ParamName = '采集结束日期'
        FieldName = '采集结束日期'
      end
      item
        ParamName = '采集结束时间'
        FieldName = '采集结束时间'
      end
      item
        ParamName = '流水号'
        FieldName = '流水号'
      end
      item
        ParamName = '上传端流水号'
        FieldName = '上传端流水号'
      end
      item
        ParamName = '交易代码'
        FieldName = '交易代码'
      end
      item
        ParamName = '流水状态'
        FieldName = '流水状态'
      end
      item
        ParamName = '上传工作站标识'
        FieldName = '上传工作站标识'
      end
      item
        ParamName = '交易发生设备标识'
        FieldName = '交易发生设备标识'
      end
      item
        ParamName = '交易卡号'
        FieldName = '交易卡号'
      end
      item
        ParamName = '客户标识'
        FieldName = '客户标识'
      end
      item
        ParamName = '操作员代码'
        FieldName = '操作员代码'
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
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '设备物理ID'
        FieldName = '设备物理ID'
      end>
    AfterExec = MainRequestAfterExec
    Left = 128
    Top = 208
  end
end
