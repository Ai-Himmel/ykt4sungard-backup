inherited faqhQueryBusinessEquipByOther: TfaqhQueryBusinessEquipByOther
  Width = 801
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 453
    Width = 801
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 621
      Top = 5
    end
    inherited btnPrint: TBitBtn
      Left = 711
      Top = 5
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 801
    inherited Image1: TImage
      Width = 801
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 801
    Height = 87
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 2
    object Label1: TLabel
      Left = 57
      Top = 13
      Width = 48
      Height = 12
      Caption = '设备标识'
    end
    object Label3: TLabel
      Left = 33
      Top = 39
      Width = 72
      Height = 12
      Caption = '设备启用日期'
    end
    object Label5: TLabel
      Left = 33
      Top = 64
      Width = 72
      Height = 12
      Caption = '使用结束时间'
    end
    object Label6: TLabel
      Left = 414
      Top = 39
      Width = 72
      Height = 12
      Caption = '设备停用日期'
    end
    object Label10: TLabel
      Left = 274
      Top = 66
      Width = 114
      Height = 12
      Caption = '输入6位数字(hhddss)'
    end
    object WVLabel1: TWVLabel
      Left = 272
      Top = 40
      Width = 126
      Height = 12
      Caption = '输入8位数字(yyyymmdd)'
    end
    object WVLabel2: TWVLabel
      Left = 629
      Top = 40
      Width = 126
      Height = 12
      Caption = '输入8位数字(yyyymmdd)'
    end
    object Label7: TLabel
      Left = 438
      Top = 12
      Width = 48
      Height = 12
      Caption = '商户名称'
    end
    object Label2: TLabel
      Left = 438
      Top = 63
      Width = 48
      Height = 12
      Caption = '使用状态'
    end
    object edtBDate: TWVEdit
      Left = 119
      Top = 34
      Width = 146
      Height = 20
      Color = clWhite
      MaxLength = 8
      ReadOnly = False
      TabOrder = 2
      Text = '<使用开始日期>'
      WorkView = WorkView
      FieldName = '使用开始日期'
    end
    object edtETime: TWVEdit
      Left = 119
      Top = 58
      Width = 146
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 4
      Text = '<使用结束时间>'
      WorkView = WorkView
      FieldName = '使用结束时间'
    end
    object edtEDate: TWVEdit
      Left = 500
      Top = 34
      Width = 122
      Height = 20
      Color = clWhite
      MaxLength = 8
      ReadOnly = False
      TabOrder = 3
      Text = '<使用结束日期>'
      WorkView = WorkView
      FieldName = '使用结束日期'
    end
    object WVEdit1: TWVEdit
      Left = 500
      Top = 7
      Width = 122
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<商户名称>'
      WorkView = WorkView
      FieldName = '商户名称'
    end
    object WVComboBox2: TWVComboBox
      Left = 500
      Top = 58
      Width = 122
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '使用状态'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*115'
    end
    object edtId: TWVDigitalEdit
      Left = 119
      Top = 9
      Width = 146
      Height = 20
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 1
      TabStop = True
      Text = '0'
      WorkView = WorkView
      FieldName = '设备标识'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 105
    Width = 801
    Height = 348
    inherited Grid: TRzDBGrid
      Width = 801
      Height = 348
      Columns = <
        item
          Expanded = False
          FieldName = 'Lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '编号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '设备名称'
          Width = 84
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '商户名称'
          Width = 93
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '使用开始时间'
          Width = 96
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '使用结束时间'
          Width = 88
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '设备启用日期'
          Width = 98
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '设备停用日期'
          Width = 89
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '使用状态'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ssectypes'
          PickList.Strings = ()
          Title.Caption = '备注'
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
        Name = '设备标识'
        Caption = '设备标识'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '使用开始日期'
        Caption = '使用开始日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
        Features.Strings = ()
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
        Name = '使用结束日期'
        Caption = '使用结束日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
        Features.Strings = ()
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
        Name = '使用状态'
        Caption = '使用状态'
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
        Name = '使用结束时间'
        Caption = '使用结束时间'
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
        Name = '商户编号'
        Caption = '商户编号'
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
        MonitorValueChangedFields = '|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 148
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '设备商户信息非主键查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '使用开始日期'
        FieldName = '使用开始日期'
      end
      item
        ParamName = '设备标识'
        FieldName = '设备标识'
      end
      item
        ParamName = '使用结束日期'
        FieldName = '使用结束日期'
      end
      item
        ParamName = '使用结束时间'
        FieldName = '使用结束时间'
      end
      item
        ParamName = '使用状态'
        FieldName = '使用状态'
      end
      item
        ParamName = '商户名称'
        FieldName = '商户名称'
      end
      item
        ParamName = '商户编号'
        FieldName = '商户编号'
      end>
    Left = 184
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-31'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '115'
      end>
    Left = 220
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 264
    Top = 256
  end
end
