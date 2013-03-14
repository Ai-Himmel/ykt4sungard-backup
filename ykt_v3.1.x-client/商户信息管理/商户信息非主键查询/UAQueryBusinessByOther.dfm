inherited faqhQueryBusinessByOther: TfaqhQueryBusinessByOther
  Width = 680
  Height = 463
  inherited UIPanel1: TUIPanel
    Top = 433
    Width = 680
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 503
    end
    inherited btnPrint: TBitBtn
      Left = 590
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 680
    inherited Image1: TImage
      Width = 680
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 680
    Height = 87
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label2: TLabel
      Left = 70
      Top = 9
      Width = 36
      Height = 12
      Caption = '商户号'
    end
    object Label3: TLabel
      Left = 265
      Top = 9
      Width = 60
      Height = 12
      Caption = '上级商户号'
    end
    object Label4: TLabel
      Left = 490
      Top = 9
      Width = 48
      Height = 12
      Caption = '商户名称'
    end
    object Label5: TLabel
      Left = 58
      Top = 38
      Width = 48
      Height = 12
      Caption = '商户类型'
    end
    object Label6: TLabel
      Left = 490
      Top = 37
      Width = 48
      Height = 12
      Caption = '末级商户'
      Visible = False
    end
    object Label9: TLabel
      Left = 70
      Top = 66
      Width = 36
      Height = 12
      Caption = '联系人'
    end
    object Label11: TLabel
      Left = 469
      Top = 217
      Width = 60
      Height = 12
      Caption = '负责人民族'
      Visible = False
    end
    object Label12: TLabel
      Left = 241
      Top = 62
      Width = 84
      Height = 12
      Caption = '联系人证件号码'
    end
    object Label14: TLabel
      Left = 468
      Top = 249
      Width = 48
      Height = 12
      Caption = '联系地址'
      Visible = False
    end
    object Label20: TLabel
      Left = 88
      Top = 225
      Width = 24
      Height = 12
      Caption = '备注'
      Visible = False
    end
    object Label1: TLabel
      Left = 4
      Top = 248
      Width = 108
      Height = 12
      Caption = '商户管理费计算方式'
      Visible = False
    end
    object Label17: TLabel
      Left = 236
      Top = 248
      Width = 96
      Height = 12
      Caption = '商户税费计算方式'
      Visible = False
    end
    object Label18: TLabel
      Left = 277
      Top = 36
      Width = 48
      Height = 12
      Caption = '独立核算'
    end
    object WVEdit2: TWVEdit
      Left = 116
      Top = 5
      Width = 121
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<商户标识>'
      OnChange = WVEdit2Change
      WorkView = WorkView
      FieldName = '商户标识'
    end
    object WVEdit3: TWVEdit
      Left = 332
      Top = 5
      Width = 121
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<父商户标识>'
      OnChange = WVEdit3Change
      WorkView = WorkView
      FieldName = '父商户标识'
    end
    object WVEdit4: TWVEdit
      Left = 552
      Top = 5
      Width = 105
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<商户名称>'
      WorkView = WorkView
      FieldName = '商户名称'
    end
    object WVEdit9: TWVEdit
      Left = 116
      Top = 61
      Width = 121
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 7
      Text = '<负责人姓名>'
      WorkView = WorkView
      FieldName = '负责人姓名'
    end
    object WVEdit12: TWVEdit
      Left = 332
      Top = 57
      Width = 121
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 6
      Text = '<负责人身份证号>'
      WorkView = WorkView
      FieldName = '负责人身份证号'
    end
    object WVEdit14: TWVEdit
      Left = 540
      Top = 245
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 12
      Text = '<联系地址>'
      Visible = False
      WorkView = WorkView
      FieldName = '联系地址'
    end
    object WVEdit20: TWVEdit
      Left = 136
      Top = 221
      Width = 297
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 9
      Text = '<备注>'
      Visible = False
      WorkView = WorkView
      FieldName = '备注'
    end
    object WVComboBox1: TWVComboBox
      Left = 116
      Top = 33
      Width = 121
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '商户类别'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*14'
    end
    object WVComboBox2: TWVComboBox
      Left = 552
      Top = 31
      Width = 105
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 4
      Visible = False
      WorkView = WorkView
      FieldName = '是否为叶节点'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*2'
    end
    object WVComboBox5: TWVComboBox
      Left = 548
      Top = 213
      Width = 101
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 8
      Visible = False
      WorkView = WorkView
      FieldName = '负责人民族'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*34'
    end
    object WVEdit1: TWVEdit
      Left = 136
      Top = 244
      Width = 89
      Height = 20
      ReadOnly = False
      TabOrder = 10
      Text = 'WVEdit1'
      Visible = False
    end
    object WVEdit6: TWVEdit
      Left = 348
      Top = 244
      Width = 97
      Height = 20
      ReadOnly = False
      TabOrder = 11
      Text = 'WVEdit6'
      Visible = False
    end
    object WVComboBox6: TWVComboBox
      Left = 332
      Top = 31
      Width = 121
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '是否为独立核算'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*2'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 105
    Width = 680
    Height = 328
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 680
      Height = 328
      Columns = <
        item
          Expanded = False
          FieldName = 'sbranch_code0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '区域'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '商户号'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '商户帐号'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '商户名称'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol7'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '商户类型'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smain_flag2'
          PickList.Strings = ()
          Title.Caption = '末级商户'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'smain_flag'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '独立核算'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '收搭伙费'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smarket_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '佣金类型'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'drate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '佣金费率(%)'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'drate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '提成比率(%)'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Caption = '帐户余额'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '银行代码'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '银行帐号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbankname2'
          PickList.Strings = ()
          Title.Caption = '银行帐户名'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '上级商户'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '上级商户名'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Caption = '联系人'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smarket_code2'
          PickList.Strings = ()
          Title.Caption = '证件类型'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail2'
          PickList.Strings = ()
          Title.Caption = '证件号码'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone2'
          PickList.Strings = ()
          Title.Caption = '手机'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail'
          PickList.Strings = ()
          Title.Caption = '电子邮箱'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scusttypes'
          PickList.Strings = ()
          Title.Caption = '地址'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spost_code'
          PickList.Strings = ()
          Title.Caption = '邮编'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no'
          PickList.Strings = ()
          Title.Caption = '部门'
          Width = 60
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '商户标识'
        Caption = '商户标识'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '父商户标识'
        Caption = '父商户标识'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol1'
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
        GroupIndex = 1
        DataField = 'scard1'
      end
      item
        Name = '商户类别'
        Caption = '商户类别'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sstat_type'
      end
      item
        Name = '是否为独立核算'
        Caption = '是否为独立核算'
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
        Name = '是否为叶节点'
        Caption = '是否为叶节点'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'smarket_code2'
      end
      item
        Name = '负责人姓名'
        Caption = '负责人姓名'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sname'
      end
      item
        Name = '负责人身份证号'
        Caption = '负责人身份证号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sname2'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|商户标识|客户号|父商户标识|商户名称|商户类别|是否为叶节点|商户' +
          '状态|负责人员工号|负责人姓名|负责人性别|负责人民族代码|负责人身' +
          '份证号|联系电话|联系地址|是否收取管理费|收取消费管理费比例|商户' +
          '管理费计算方式|商户税费计算方式|注册时间|备注|'
      end>
    Left = 180
    Top = 359
  end
  inherited MainRequest: TWVRequest
    ID = '商户信息非主键查询'
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
        ParamName = '商户标识'
        FieldName = '商户标识'
      end
      item
        ParamName = '父商户标识'
        FieldName = '父商户标识'
      end
      item
        ParamName = '商户名称'
        FieldName = '商户名称'
      end
      item
        ParamName = '商户类别'
        FieldName = '商户类别'
      end
      item
        ParamName = '是否为独立核算'
        FieldName = '是否为独立核算'
      end
      item
        ParamName = '是否为叶节点'
        FieldName = '是否为叶节点'
      end
      item
        ParamName = '负责人姓名'
        FieldName = '负责人姓名'
      end
      item
        ParamName = '负责人身份证号'
        FieldName = '负责人身份证号'
      end>
    Left = 216
    Top = 360
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'lvol7'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '14'
      end
      item
        FieldName = 'smain_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '91'
      end
      item
        FieldName = 'scert_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'smarket_code2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '87'
      end
      item
        FieldName = 'scust_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'sbank_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '110'
      end>
    Left = 248
    Top = 360
  end
  inherited DataSource: TDataSource
    Left = 280
    Top = 360
  end
end
