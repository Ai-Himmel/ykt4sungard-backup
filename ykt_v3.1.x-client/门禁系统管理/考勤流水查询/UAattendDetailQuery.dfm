inherited faqhattendDetailQuery: TfaqhattendDetailQuery
  Width = 809
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 809
    inherited btnQuery: TBitBtn
      Left = 632
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 719
    end
  end
  inherited Grid: TRzDBGrid
    Top = 113
    Width = 809
    Height = 346
    Columns = <
      item
        Expanded = False
        FieldName = 'lserial0'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '流水号'
        Width = 55
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sall_name'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '部门名称'
        Width = 150
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol0'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '客户号'
        Width = 55
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scert_no'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '学工号'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol1'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '卡号'
        Width = 53
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sname'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '姓名'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sdate0'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '发生日期'
        Width = 68
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'stime0'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '发生时间'
        Width = 71
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sphone'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '发生设备'
        Width = 80
        Visible = True
      end>
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 809
    Height = 95
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left = 66
      Top = 9
      Width = 24
      Height = 12
      Caption = '部门'
    end
    object Label2: TLabel
      Left = 303
      Top = 9
      Width = 36
      Height = 12
      Caption = '客户号'
    end
    object Label3: TLabel
      Left = 494
      Top = 9
      Width = 36
      Height = 12
      Caption = '学工号'
    end
    object Label4: TLabel
      Left = 66
      Top = 57
      Width = 24
      Height = 12
      Caption = '卡号'
    end
    object Label5: TLabel
      Left = 66
      Top = 33
      Width = 24
      Height = 12
      Caption = '姓名'
    end
    object Label6: TLabel
      Left = 290
      Top = 33
      Width = 48
      Height = 12
      Caption = '开始日期'
    end
    object Label7: TLabel
      Left = 482
      Top = 33
      Width = 48
      Height = 12
      Caption = '结束日期'
    end
    object Label8: TLabel
      Left = 291
      Top = 57
      Width = 48
      Height = 12
      Caption = '开始时间'
    end
    object Label9: TLabel
      Left = 482
      Top = 57
      Width = 48
      Height = 12
      Caption = '结束时间'
    end
    object Label10: TLabel
      Left = 42
      Top = 81
      Width = 276
      Height = 12
      Caption = '提示信息：日期格式(yyyymmdd)，时间格式(hhmmss)'
    end
    object edtCustNo: TWVEdit
      Left = 349
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<客户号>'
      WorkView = WorkView
      FieldName = '客户号'
    end
    object WVEdit3: TWVEdit
      Left = 540
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 1
      Text = '<学工号>'
      WorkView = WorkView
      FieldName = '学工号'
    end
    object edtCardNo: TWVEdit
      Left = 100
      Top = 53
      Width = 165
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 2
      Text = '<卡号>'
      WorkView = WorkView
      FieldName = '卡号'
    end
    object WVEdit5: TWVEdit
      Left = 100
      Top = 29
      Width = 166
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 3
      Text = '<姓名>'
      WorkView = WorkView
      FieldName = '姓名'
    end
    object edtBeginDate: TWVEdit
      Left = 348
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 4
      Text = '<开始日期>'
      WorkView = WorkView
      FieldName = '开始日期'
    end
    object edtEndDate: TWVEdit
      Left = 540
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 5
      Text = '<结束日期>'
      WorkView = WorkView
      FieldName = '结束日期'
    end
    object WVEdit8: TWVEdit
      Left = 349
      Top = 53
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 6
      Text = '<开始时间>'
      WorkView = WorkView
      FieldName = '开始时间'
    end
    object WVEdit9: TWVEdit
      Left = 540
      Top = 53
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 7
      Text = '<结束时间>'
      WorkView = WorkView
      FieldName = '结束时间'
    end
    object WVComboBox6: TWVComboBox
      Tag = 1
      Left = 100
      Top = 6
      Width = 167
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 8
      WorkView = WorkView
      FieldName = '部门名称'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 809
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
        Name = '部门名称'
        Caption = '部门名称'
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
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
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
        GetPrevChar = '*'
      end
      item
        Name = '结束日期'
        Caption = '结束日期'
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
        GetPrevChar = '*'
      end
      item
        Name = '开始时间'
        Caption = '开始时间'
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
        Name = '结束时间'
        Caption = '结束时间'
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
        MonitorValueChangedFields = '|部门名称|学工号|姓名|开始日期|结束日期|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '考勤流水查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '部门名称'
        FieldName = '部门名称'
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '姓名'
        FieldName = '姓名'
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
        ParamName = '开始时间'
        FieldName = '开始时间'
      end
      item
        ParamName = '结束时间'
        FieldName = '结束时间'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sall_name'
        DataPresentType = 'idobjects'
        DataPresentParam = '-22'
      end>
    Left = 232
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 264
    Top = 224
  end
end
