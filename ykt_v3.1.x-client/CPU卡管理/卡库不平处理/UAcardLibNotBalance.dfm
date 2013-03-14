inherited faqhcardLibNotBalance: TfaqhcardLibNotBalance
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    TabOrder = 3
    object Label9: TLabel [0]
      Left = 14
      Top = 8
      Width = 48
      Height = 12
      Caption = '处理方式'
    end
    inherited btnQuery: TBitBtn
      Left = 435
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 610
      TabOrder = 2
    end
    object cbbBalanceType: TWVComboBox
      Left = 67
      Top = 4
      Width = 110
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView1
      FieldName = '平帐方式'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '137'
    end
    object btnBalance: TBitBtn
      Left = 522
      Top = 3
      Width = 79
      Height = 25
      Hint = '打印'
      Anchors = [akTop, akRight]
      Caption = '处 理'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnBalanceClick
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
    Height = 79
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 66
      Top = 9
      Width = 24
      Height = 12
      Caption = '卡号'
    end
    object Label2: TLabel
      Left = 254
      Top = 9
      Width = 36
      Height = 12
      Caption = '客户号'
    end
    object Label3: TLabel
      Left = 418
      Top = 9
      Width = 72
      Height = 12
      Caption = '卡库不平类型'
    end
    object Label4: TLabel
      Left = 18
      Top = 33
      Width = 72
      Height = 12
      Caption = '不平金额阀值'
    end
    object Label5: TLabel
      Left = 242
      Top = 33
      Width = 48
      Height = 12
      Caption = '统计日期'
    end
    object Label6: TLabel
      Left = 442
      Top = 33
      Width = 48
      Height = 12
      Caption = '处理日期'
    end
    object Label7: TLabel
      Left = 30
      Top = 57
      Width = 60
      Height = 12
      Caption = '处理操作员'
    end
    object Label8: TLabel
      Left = 242
      Top = 57
      Width = 48
      Height = 12
      Caption = '处理状态'
    end
    object Label10: TLabel
      Left = 442
      Top = 55
      Width = 48
      Height = 12
      Caption = '所属区域'
    end
    object edtCardNo: TWVEdit
      Left = 100
      Top = 5
      Width = 124
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<卡号>'
      WorkView = WorkView
      FieldName = '卡号'
    end
    object edtCustNo: TWVEdit
      Left = 299
      Top = 5
      Width = 113
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 2
      Text = '<客户号>'
      WorkView = WorkView
      FieldName = '客户号'
    end
    object edtValue: TWVEdit
      Left = 100
      Top = 29
      Width = 124
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 3
      Text = '<不平金额阀值>'
      WorkView = WorkView
      FieldName = '不平金额阀值'
    end
    object edtStatDate: TWVEdit
      Left = 299
      Top = 29
      Width = 113
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 4
      Text = '<统计日期>'
      WorkView = WorkView
      FieldName = '统计日期'
    end
    object edtBalanceDate: TWVEdit
      Left = 497
      Top = 29
      Width = 116
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 5
      Text = '<平账日期>'
      WorkView = WorkView
      FieldName = '平账日期'
    end
    object WVComboBox1: TWVComboBox
      Left = 497
      Top = 4
      Width = 116
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '卡库不平类型'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*136'
    end
    object WVComboBox2: TWVComboBox
      Left = 299
      Top = 52
      Width = 113
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView
      FieldName = '平账状态'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*138'
    end
    object WVComboBox3: TWVComboBox
      Left = 101
      Top = 53
      Width = 124
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      MaxLength = 8
      TabOrder = 8
      WorkView = WorkView
      FieldName = '平账操作员'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-30'
    end
    object WVComboBox4: TWVComboBox
      Left = 497
      Top = 51
      Width = 116
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView
      FieldName = '所属区域'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-27'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 97
    Width = 700
    Height = 362
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 362
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '卡号'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '姓名'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '不平金额'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '账户余额'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '卡余额'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '卡交易次数'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '统计日期'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '统计时间'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '平账开始日期'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '平账截止日期'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '期间消费缺失金额'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt6'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '期间充值缺失金额'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol7'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '期间缺失记录条数'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt7'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '期间缺失总金额'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '处理日期'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Semp_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '处理操作员'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Sstatus3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '处理状态'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '备注'
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
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '卡号'
        Caption = '卡号'
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
        GetPrevChar = '*'
      end
      item
        Name = '卡库不平类型'
        Caption = '卡库不平类型'
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
        Name = '不平金额阀值'
        Caption = '不平金额阀值'
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
        Name = '统计日期'
        Caption = '统计日期'
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
        Name = '平账日期'
        Caption = '平账日期'
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
        Name = '平账操作员'
        Caption = '平账操作员'
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
        Name = '平账状态'
        Caption = '平账状态'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|卡号|客户号|卡库不平类型|不平金额阀值|统计日期|平账日期|平账操' +
          '作员|平账状态|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '卡库不平处理查询'
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
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '卡库不平类型'
        FieldName = '卡库不平类型'
      end
      item
        ParamName = '不平金额阀值'
        FieldName = '不平金额阀值'
      end
      item
        ParamName = '统计日期'
        FieldName = '统计日期'
      end
      item
        ParamName = '平账日期'
        FieldName = '平账日期'
      end
      item
        ParamName = '平账操作员'
        FieldName = '平账操作员'
      end
      item
        ParamName = '平账状态'
        FieldName = '平账状态'
      end
      item
        ParamName = '所属区域'
        FieldName = '所属区域'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'Sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '136'
      end
      item
        FieldName = 'sstatus3'
        DataPresentType = 'idobjects'
        DataPresentParam = '138'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end>
    Left = 232
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 272
    Top = 224
  end
  object WorkView1: TWorkView
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
      end
      item
        Name = '卡号'
        Caption = '卡号'
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
        Name = '统计日期'
        Caption = '统计日期'
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
        Name = '平帐方式'
        Caption = '平帐方式'
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
          '|卡号|客户号|卡库不平类型|不平金额阀值|统计日期|平账日期|平账操' +
          '作员|平账状态|'
      end>
    Left = 164
    Top = 271
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '卡库不平处理'
    Bindings = <
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '统计日期'
        FieldName = '统计日期'
      end
      item
        ParamName = '平账方式'
        FieldName = '平帐方式'
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
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 272
  end
end
