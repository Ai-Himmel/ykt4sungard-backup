inherited faqhqueryOperLog: TfaqhqueryOperLog
  Width = 755
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 755
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 578
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 665
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 755
    TabOrder = 0
    inherited Image1: TImage
      Width = 755
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 755
    Height = 55
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 2
    object Label1: TLabel
      Left = 30
      Top = 9
      Width = 36
      Height = 12
      Caption = '站点号'
    end
    object Label2: TLabel
      Left = 574
      Top = 9
      Width = 60
      Height = 12
      Caption = '站点流水号'
    end
    object Label3: TLabel
      Left = 406
      Top = 9
      Width = 36
      Height = 12
      Caption = '操作员'
    end
    object Label4: TLabel
      Left = 18
      Top = 33
      Width = 48
      Height = 12
      Caption = '开始日期'
    end
    object Label5: TLabel
      Left = 406
      Top = 33
      Width = 36
      Height = 12
      Caption = '交易码'
    end
    object Label6: TLabel
      Left = 218
      Top = 9
      Width = 48
      Height = 12
      Caption = '流水状态'
    end
    object Label7: TLabel
      Left = 217
      Top = 34
      Width = 48
      Height = 12
      Caption = '结束日期'
    end
    object edtBDate: TWVEdit
      Left = 76
      Top = 29
      Width = 121
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 5
      Text = '<开始日期>'
      WorkView = WorkView
      FieldName = '开始日期'
    end
    object WVComboBox6: TWVComboBox
      Left = 76
      Top = 5
      Width = 121
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '站点号'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-33'
    end
    object WVComboBox1: TWVComboBox
      Left = 448
      Top = 5
      Width = 116
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      MaxLength = 8
      TabOrder = 2
      WorkView = WorkView
      FieldName = '操作员'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-30'
    end
    object WVComboBox2: TWVComboBox
      Left = 448
      Top = 29
      Width = 281
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView
      FieldName = '交易码'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-38'
    end
    object WVComboBox3: TWVComboBox
      Left = 275
      Top = 5
      Width = 121
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 1
      WorkView = WorkView
      FieldName = '流水状态'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*20'
    end
    object edtEDate: TWVEdit
      Left = 275
      Top = 28
      Width = 121
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 4
      Text = '<结束日期>'
      WorkView = WorkView
      FieldName = '结束日期'
    end
    object edtMoney: TWVDigitalEdit
      Left = 640
      Top = 5
      Width = 86
      Height = 20
      AllowPoint = True
      AllowNegative = True
      UserSeprator = True
      Precision = 0
      MaxIntLen = 12
      ParentColor = False
      TabOrder = 3
      TabStop = True
      Text = '0'
      WorkView = WorkView
      FieldName = '站点流水号'
      SynchronizeByValue = True
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 73
    Width = 755
    Height = 386
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Width = 755
      Height = 386
      Columns = <
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易时间'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lwithdraw_flag'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '站点号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '站点流水号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semp_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '操作员'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semp_no2'
          PickList.Strings = ()
          Title.Caption = '审核操作员'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易码'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易金额'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '流水状态'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lsafe_level'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '错误码'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '备注'
          Width = 200
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Vsvarstr1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '请求数据包'
          Width = 200
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
        Name = '站点号'
        Caption = '站点号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '站点流水号'
        Caption = '站点流水号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '操作员'
        Caption = '操作员'
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
        Name = '开始日期'
        Caption = '开始日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        MonitorValueChangedFields = '|开始日期|'
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '交易码'
        Caption = '交易码'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '流水状态'
        Caption = '流水状态'
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
        Name = '结束日期'
        Caption = '结束日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        MonitorValueChangedFields = '|结束日期|'
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|站点号|站点流水号|操作员|交易日期|交易码|流水状态|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '操作日志查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '站点号'
        FieldName = '站点号'
      end
      item
        ParamName = '站点流水号'
        FieldName = '站点流水号'
      end
      item
        ParamName = '操作员'
        FieldName = '操作员'
      end
      item
        ParamName = '开始日期'
        FieldName = '开始日期'
      end
      item
        ParamName = '交易码'
        FieldName = '交易码'
      end
      item
        ParamName = '流水状态'
        FieldName = '流水状态'
      end
      item
        ParamName = '结束日期'
        FieldName = '结束日期'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lwithdraw_flag'
        DataPresentType = 'idobjects'
        DataPresentParam = '-33'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '20'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-21'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '-38'
      end
      item
        FieldName = 'semp_no2'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end>
    Left = 160
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 192
    Top = 256
  end
end
