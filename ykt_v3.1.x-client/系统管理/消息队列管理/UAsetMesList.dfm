inherited faqhsetMesList: TfaqhsetMesList
  Width = 681
  Height = 477
  Caption = '消息队列管理'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 414
        Width = 677
        Height = 40
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 179
          Top = 7
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 499
          Top = 7
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 410
          Top = 7
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Top = 7
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
          Top = 7
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 12
          Width = 169
          Visible = False
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 97
        Width = 677
        Height = 317
        TabOrder = 2
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
            FieldName = 'Lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '消息编号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '交易码'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '消息状态'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '消息级别'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '子系统编号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol9'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '最大发送次数'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol5'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备编号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '消息生成时间'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '消息开始处理时间'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '消息处理完成时间'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol6'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '错误码'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '错误消息'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol7'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '父交易码'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol8'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '交易卡号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '删除标志'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'Lvol10'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '接收次数'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol11'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '序号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol12'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '消息类型'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr1'
            PickList.Strings = ()
            Title.Caption = '请求数据'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr2'
            PickList.Strings = ()
            Title.Caption = '应答数据'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lserial0'
            PickList.Strings = ()
            Title.Caption = '已发送次数'
            Width = 80
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 79
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label2: TLabel
          Left = 218
          Top = 10
          Width = 48
          Height = 12
          Caption = '消息编号'
        end
        object Label3: TLabel
          Left = 54
          Top = 34
          Width = 36
          Height = 12
          Caption = '交易码'
        end
        object Label4: TLabel
          Left = 42
          Top = 10
          Width = 48
          Height = 12
          Caption = '消息状态'
        end
        object Label6: TLabel
          Left = 398
          Top = 34
          Width = 60
          Height = 12
          Caption = '子系统编号'
        end
        object Label7: TLabel
          Left = 42
          Top = 58
          Width = 48
          Height = 12
          Caption = '设备编号'
        end
        object Label8: TLabel
          Left = 410
          Top = 10
          Width = 48
          Height = 12
          Caption = '交易日期'
        end
        object Label1: TLabel
          Left = 218
          Top = 33
          Width = 48
          Height = 12
          Caption = '消息级别'
        end
        object WVDigitalEdit2: TWVDigitalEdit
          Left = 276
          Top = 6
          Width = 100
          Height = 20
          AllowNegative = True
          Precision = 0
          MaxIntLen = 10
          Color = clInfoBk
          ParentColor = False
          TabOrder = 1
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '查询.消息编号'
          SynchronizeByValue = True
        end
        object WVEdit8: TWVEdit
          Left = 468
          Top = 6
          Width = 129
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 2
          Text = '<查询.交易日期>'
          WorkView = WorkView
          FieldName = '查询.交易日期'
        end
        object WVComboBox4: TWVComboBox
          Left = 100
          Top = 55
          Width = 277
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 6
          WorkView = WorkView
          FieldName = '查询.设备编号'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-31'
        end
        object WVComboBox1: TWVComboBox
          Left = 468
          Top = 29
          Width = 129
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '查询.子系统编号'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-47'
        end
        object WVComboBox2: TWVComboBox
          Left = 100
          Top = 6
          Width = 101
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '查询.消息状态'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*103'
        end
        object WVComboBox6: TWVComboBox
          Left = 276
          Top = 29
          Width = 101
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '查询.消息级别'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*104'
        end
        object WVDigitalEdit1: TWVDigitalEdit
          Left = 100
          Top = 30
          Width = 100
          Height = 20
          AllowNegative = True
          Precision = 0
          MaxIntLen = 10
          Color = clInfoBk
          ParentColor = False
          TabOrder = 5
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '查询.交易码'
          SynchronizeByValue = True
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label10: TLabel [0]
        Left = 74
        Top = 84
        Width = 48
        Height = 12
        Caption = '消息编号'
      end
      object Label12: TLabel [1]
        Left = 74
        Top = 164
        Width = 48
        Height = 12
        Caption = '消息状态'
      end
      object Label23: TLabel [2]
        Left = 50
        Top = 124
        Width = 72
        Height = 12
        Caption = '最大发送次数'
      end
      object Label28: TLabel [3]
        Left = 42
        Top = 5
        Width = 96
        Height = 16
        Caption = '消息队列管理'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '黑体'
        Font.Style = []
        ParentFont = False
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 3
        inherited btnOK: TBitBtn
          Left = 505
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 593
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object edtId: TWVDigitalEdit
        Left = 132
        Top = 80
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '消息编号'
        SynchronizeByValue = True
      end
      object edtNum: TWVDigitalEdit
        Left = 132
        Top = 120
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 1
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '最大发送次数'
        SynchronizeByValue = True
      end
      object cbbStat: TWVComboBox
        Left = 132
        Top = 159
        Width = 101
        Height = 20
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 2
        Text = '<消息状态>'
        WorkView = WorkView
        FieldName = '消息状态'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*103'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 492
    Top = 223
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Features.Strings = ()
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
        Features.Strings = ()
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
        Features.Strings = ()
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
        Name = '查询.消息编号'
        Caption = '查询.消息编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.交易码'
        Caption = '查询.交易码'
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
        Name = '查询.消息状态'
        Caption = '查询.消息状态'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.消息级别'
        Caption = '查询.消息级别'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.子系统编号'
        Caption = '查询.子系统编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.设备编号'
        Caption = '查询.设备编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.交易日期'
        Caption = '查询.交易日期'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '交易类型'
        Caption = '交易类型'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '消息编号'
        Caption = '消息编号'
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
        GroupIndex = 1
        DataField = 'Lvol0'
      end
      item
        Name = '消息状态'
        Caption = '消息状态'
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
        GroupIndex = 1
        DataField = 'Lvol2'
      end
      item
        Name = '最大发送次数'
        Caption = '最大发送次数'
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
        GroupIndex = 1
        DataField = 'Lvol9'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.交易类型|查询.消息编号|查询.交易码|查询.消息状态|查询.消息' +
          '级别|查询.子系统编号|查询.设备编号|查询.交易日期|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|交易日期|消息编号|交易码|消息状态|消息级别|子系统编号|设备编号|' +
          '消息生成时间|消息开始处理时间|消息处理完成时间|错误码|错误消息|' +
          '父交易码|交易卡号|最大发送次数|删除标志|接收次数|序号|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 424
    Top = 184
  end
  inherited QueryRequest: TWVRequest
    ID = '消息队列查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '消息编号'
        FieldName = '查询.消息编号'
      end
      item
        ParamName = '交易码'
        FieldName = '查询.交易码'
      end
      item
        ParamName = '消息状态'
        FieldName = '查询.消息状态'
      end
      item
        ParamName = '消息级别'
        FieldName = '查询.消息级别'
      end
      item
        ParamName = '子系统编号'
        FieldName = '查询.子系统编号'
      end
      item
        ParamName = '设备编号'
        FieldName = '查询.设备编号'
      end
      item
        ParamName = '交易日期'
        FieldName = '查询.交易日期'
      end>
    Left = 552
    Top = 184
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol1'
        DataPresentType = 'idobjects'
        DataPresentParam = '-38'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'idobjects'
        DataPresentParam = '103'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '104'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'idobjects'
        DataPresentParam = '-47'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '-31'
      end
      item
        FieldName = 'lvol12'
        DataPresentType = 'idobjects'
        DataPresentParam = '105'
      end>
    Left = 460
    Top = 223
  end
  inherited AddRequest: TWVRequest
    ID = '消息队列管理'
    Bindings = <
      item
        ParamName = '交易日期'
        FieldName = '交易日期'
      end
      item
        ParamName = '消息编号'
        FieldName = '消息编号'
      end
      item
        ParamName = '交易码'
        FieldName = '交易码'
      end
      item
        ParamName = '消息状态'
        FieldName = '消息状态'
      end
      item
        ParamName = '消息级别'
        FieldName = '消息级别'
      end
      item
        ParamName = '子系统编号'
        FieldName = '子系统编号'
      end
      item
        ParamName = '设备编号'
        FieldName = '设备编号'
      end
      item
        ParamName = '消息生成时间'
        FieldName = '消息生成时间'
      end
      item
        ParamName = '消息开始处理时间'
        FieldName = '消息开始处理时间'
      end
      item
        ParamName = '消息处理完成时间'
        FieldName = '消息处理完成时间'
      end
      item
        ParamName = '错误码'
        FieldName = '错误码'
      end
      item
        ParamName = '错误消息'
        FieldName = '错误消息'
      end
      item
        ParamName = '父交易码'
        FieldName = '父交易码'
      end
      item
        ParamName = '交易卡号'
        FieldName = '交易卡号'
      end
      item
        ParamName = '最大发送次数'
        FieldName = '最大发送次数'
      end
      item
        ParamName = '删除标志'
        FieldName = '删除标志'
      end
      item
        ParamName = '接收次数'
        FieldName = '接收次数'
      end
      item
        ParamName = '序号'
        FieldName = '序号'
      end
      item
        ParamName = '消息类型'
        FieldName = '消息类型'
      end>
    Left = 456
    Top = 184
  end
  inherited DeleteRequest: TWVRequest
    ID = '消息队列管理'
    Bindings = <
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '消息编号'
        FieldName = '消息编号'
      end
      item
        ParamName = '最大发送次数'
        FieldName = '最大发送次数'
      end
      item
        ParamName = '消息状态'
        FieldName = '消息状态'
      end>
    Left = 488
    Top = 184
  end
  inherited ChangeRequest: TWVRequest
    ID = '消息队列管理'
    Bindings = <
      item
        ParamName = '消息编号'
        FieldName = '消息编号'
      end
      item
        ParamName = '消息状态'
        FieldName = '消息状态'
      end
      item
        ParamName = '最大发送次数'
        FieldName = '最大发送次数'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 520
    Top = 184
  end
  inherited WVDataSource: TWVDataSource
    Left = 556
    Top = 223
  end
  inherited alDatasetActions: TActionList
    Left = 524
    Top = 228
  end
end
