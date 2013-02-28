inherited faqhSetPhoneNo: TfaqhSetPhoneNo
  Width = 763
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 456
    Width = 763
    Height = 33
    object Label1: TLabel [0]
      Left = 162
      Top = 9
      Width = 72
      Height = 12
      Caption = '手机通宝卡号'
    end
    object Label6: TLabel [1]
      Left = 342
      Top = 9
      Width = 36
      Height = 12
      Caption = '手机号'
    end
    object Label7: TLabel [2]
      Left = 18
      Top = 9
      Width = 24
      Height = 12
      Caption = '卡号'
    end
    inherited btnQuery: TBitBtn
      Left = 498
    end
    inherited btnPrint: TBitBtn
      Left = 673
    end
    object edtTNo: TWVEdit
      Left = 236
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<手机通宝卡号>'
      WorkView = WVSet
      FieldName = '手机通宝卡号'
    end
    object edtPhone: TWVEdit
      Left = 380
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 3
      Text = '<手机号>'
      WorkView = WVSet
      FieldName = '手机号'
    end
    object edtCardNo: TWVEdit
      Left = 44
      Top = 5
      Width = 100
      Height = 20
      MaxLength = 22
      ParentColor = True
      ReadOnly = True
      TabOrder = 4
      Text = '<卡号>'
      WorkView = WVSet
      FieldName = '卡号'
    end
    object btnEdit: TBitBtn
      Left = 586
      Top = 3
      Width = 79
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '修改(&E)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = btnEditClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 763
    inherited Image1: TImage
      Width = 763
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 763
    Height = 31
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label2: TLabel
      Left = 26
      Top = 9
      Width = 24
      Height = 12
      Caption = '卡号'
    end
    object Label3: TLabel
      Left = 170
      Top = 9
      Width = 72
      Height = 12
      Caption = '手机通宝卡号'
    end
    object Label4: TLabel
      Left = 350
      Top = 9
      Width = 36
      Height = 12
      Caption = '手机号'
    end
    object Label5: TLabel
      Left = 498
      Top = 9
      Width = 48
      Height = 12
      Caption = '更新时间'
    end
    object edtCardNoQ: TWVEdit
      Left = 60
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<卡号>'
      WorkView = WorkView
      FieldName = '卡号'
    end
    object WVEdit3: TWVEdit
      Left = 244
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 1
      Text = '<手机通宝卡号>'
      WorkView = WorkView
      FieldName = '手机通宝卡号'
    end
    object WVEdit4: TWVEdit
      Left = 388
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<手机号>'
      WorkView = WorkView
      FieldName = '手机号'
    end
    object WVEdit5: TWVEdit
      Left = 556
      Top = 5
      Width = 133
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 3
      Text = '<更新时间>'
      WorkView = WorkView
      FieldName = '更新时间'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 49
    Width = 763
    Height = 407
    inherited Grid: TRzDBGrid
      Width = 763
      Height = 407
      OnCellClick = GridCellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '卡号'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '手机通宝卡号'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '手机号'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '更新时间'
          Width = 150
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
        Name = '操作标志'
        Caption = '操作标志'
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
        Name = '手机通宝卡号'
        Caption = '手机通宝卡号'
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
        Name = '手机号'
        Caption = '手机号'
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
        Name = '更新时间'
        Caption = '更新时间'
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
        MonitorValueChangedFields = '|操作标志|卡号|手机通宝卡号|手机号|更新时间|'
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '手机卡信息维护Q'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
        DefaultValue = 0
      end
      item
        ParamName = '手机通宝卡号'
        FieldName = '手机通宝卡号'
      end
      item
        ParamName = '手机号'
        FieldName = '手机号'
      end
      item
        ParamName = '更新时间'
        FieldName = '更新时间'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 232
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 264
    Top = 224
  end
  object WVSet: TWorkView
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
        Name = '操作标志'
        Caption = '操作标志'
        FieldType = wftUndefined
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
        Name = '手机通宝卡号'
        Caption = '手机通宝卡号'
        FieldType = wftUndefined
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
        Name = '手机号'
        Caption = '手机号'
        FieldType = wftUndefined
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
        Name = '更新时间'
        Caption = '更新时间'
        FieldType = wftUndefined
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
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|操作标志|卡号|手机通宝卡号|手机号|更新时间|'
      end>
    Left = 164
    Top = 263
  end
  object WVRequest1: TWVRequest
    WorkView = WVSet
    ID = '手机卡信息维护'
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
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '手机通宝卡号'
        FieldName = '手机通宝卡号'
      end
      item
        ParamName = '手机号'
        FieldName = '手机号'
      end
      item
        ParamName = '更新时间'
        FieldName = '更新时间'
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 264
  end
end
