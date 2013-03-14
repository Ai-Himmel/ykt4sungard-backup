inherited faqhBusPosSerialStat: TfaqhBusPosSerialStat
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 453
    Width = 700
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 521
      Top = 6
    end
    inherited btnPrint: TBitBtn
      Left = 612
      Top = 6
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    TabOrder = 2
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 55
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object Label2: TLabel
      Left = 34
      Top = 9
      Width = 42
      Height = 12
      Caption = '学/工号'
    end
    object Label3: TLabel
      Left = 210
      Top = 9
      Width = 24
      Height = 12
      Caption = '姓名'
    end
    object Label6: TLabel
      Left = 26
      Top = 33
      Width = 48
      Height = 12
      Caption = '所属部门'
    end
    object Label1: TLabel
      Left = 346
      Top = 9
      Width = 48
      Height = 12
      Caption = '开始月份'
    end
    object Label4: TLabel
      Left = 506
      Top = 9
      Width = 48
      Height = 12
      Caption = '结束月份'
    end
    object Label5: TLabel
      Left = 370
      Top = 33
      Width = 24
      Height = 12
      Caption = '类别'
    end
    object WVEdit2: TWVEdit
      Left = 79
      Top = 5
      Width = 101
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<学工号>'
      WorkView = WorkView
      FieldName = '学工号'
    end
    object WVEdit3: TWVEdit
      Left = 237
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<姓名>'
      WorkView = WorkView
      FieldName = '姓名'
    end
    object edtBDate: TWVEdit
      Left = 398
      Top = 5
      Width = 101
      Height = 20
      Color = clWhite
      MaxLength = 6
      ReadOnly = False
      TabOrder = 2
      Text = '<开始日期>'
      WorkView = WorkView
      FieldName = '开始日期'
    end
    object edtEDate: TWVEdit
      Left = 557
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 6
      ReadOnly = False
      TabOrder = 3
      Text = '<结束日期>'
      WorkView = WorkView
      FieldName = '结束日期'
    end
    object cbbQDept: TWVComboBox
      Left = 79
      Top = 29
      Width = 259
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 20
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '部门'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object cbbQType: TComboBox
      Left = 398
      Top = 28
      Width = 101
      Height = 20
      Style = csDropDownList
      ItemHeight = 12
      TabOrder = 4
      Items.Strings = (
        '0-所有'
        '1-教职工(正式)'
        '2-其它'
        '3-所有收费类')
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 73
    Width = 700
    Height = 380
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 380
      Columns = <
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '月份'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '所属部门'
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '收费类别'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '姓名'
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
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '刷卡总次数'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '刷卡总天数'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '刷卡总金额'
          Width = 80
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
        DataField = '@Return'
      end
      item
        Name = '返回信息'
        Caption = '返回信息'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '姓名'
        Caption = '姓名'
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
        Name = '部门'
        Caption = '部门'
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
        Name = '开始日期'
        Caption = '开始日期'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '结束日期'
        Caption = '结束日期'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '类别'
        Caption = '类别'
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
        MonitorValueChangedFields = '|参数标志|参数名称|参数值|生效时间|设置时间|参数单位|'
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '车载机流水统计'
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
        ParamName = '返回数据集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '姓名'
        FieldName = '姓名'
      end
      item
        ParamName = '部门'
        FieldName = '部门'
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
        ParamName = '类别'
        FieldName = '类别'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'scard0'
        DataPresentType = 'idobjects'
        DataPresentParam = '-43'
      end>
    Left = 240
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 280
    Top = 224
  end
end
