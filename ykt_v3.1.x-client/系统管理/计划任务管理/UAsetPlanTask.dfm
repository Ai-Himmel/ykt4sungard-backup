inherited faqhsetPlanTask: TfaqhsetPlanTask
  Width = 681
  Height = 477
  Caption = '计划任务管理'
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
          Top = 7
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 499
          Top = 7
          Enabled = False
          TabOrder = 1
        end
        inherited btnQuery: TBitBtn [2]
          Left = 322
          Top = 7
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Top = 7
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
          Top = 7
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 88
          Top = 12
          Width = 169
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 41
        Width = 677
        Height = 373
        Columns = <
          item
            Expanded = False
            FieldName = 'Lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '任务编号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '任务说明'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '程序名'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Vsvarstr1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '程序路径'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Vsvarstr2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '命令行参数'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '每天一次'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '每周一次'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '每月一次'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '开始时间'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '结束时间'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '是否启用'
            Width = 50
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 23
        Align = alTop
        ParentColor = True
        TabOrder = 0
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label12: TLabel [0]
        Left = 44
        Top = 60
        Width = 48
        Height = 12
        Caption = '任务编号'
      end
      object Label13: TLabel [1]
        Left = 292
        Top = 60
        Width = 48
        Height = 12
        Caption = '任务说明'
      end
      object Label14: TLabel [2]
        Left = 56
        Top = 100
        Width = 36
        Height = 12
        Caption = '程序名'
      end
      object Label15: TLabel [3]
        Left = 292
        Top = 100
        Width = 48
        Height = 12
        Caption = '程序路径'
      end
      object Label16: TLabel [4]
        Left = 32
        Top = 140
        Width = 60
        Height = 12
        Caption = '命令行参数'
      end
      object Label17: TLabel [5]
        Left = 292
        Top = 140
        Width = 48
        Height = 12
        Caption = '每天一次'
      end
      object Label18: TLabel [6]
        Left = 42
        Top = 180
        Width = 48
        Height = 12
        Caption = '每周一次'
      end
      object Label19: TLabel [7]
        Left = 292
        Top = 180
        Width = 48
        Height = 12
        Caption = '每月一次'
      end
      object Label20: TLabel [8]
        Left = 44
        Top = 220
        Width = 48
        Height = 12
        Caption = '开始时间'
      end
      object Label21: TLabel [9]
        Left = 292
        Top = 220
        Width = 48
        Height = 12
        Caption = '结束时间'
      end
      object Label23: TLabel [10]
        Left = 42
        Top = 5
        Width = 96
        Height = 16
        Caption = '计划任务管理'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '黑体'
        Font.Style = []
        ParentFont = False
      end
      object Label1: TLabel [11]
        Left = 196
        Top = 220
        Width = 72
        Height = 12
        Caption = '格式：hhmmss'
      end
      object Label2: TLabel [12]
        Left = 460
        Top = 220
        Width = 72
        Height = 12
        Caption = '格式：hhmmss'
      end
      object Label3: TLabel [13]
        Left = 156
        Top = 60
        Width = 48
        Height = 12
        Caption = '是否启用'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 7
        inherited btnOK: TBitBtn
          Left = 505
        end
        inherited btnCancel: TBitBtn
          Left = 593
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtTaskId: TWVDigitalEdit
        Left = 100
        Top = 56
        Width = 45
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
        FieldName = '任务编号'
        SynchronizeByValue = True
      end
      object WVEdit13: TWVEdit
        Left = 350
        Top = 56
        Width = 197
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<任务说明>'
        WorkView = WorkView
        FieldName = '任务说明'
        SynchronizeWhenExit = True
      end
      object WVEdit14: TWVEdit
        Left = 100
        Top = 96
        Width = 173
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 2
        Text = '<程序名>'
        WorkView = WorkView
        FieldName = '程序名'
        SynchronizeWhenExit = True
      end
      object WVEdit15: TWVEdit
        Left = 350
        Top = 96
        Width = 197
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 3
        Text = '<程序路径>'
        WorkView = WorkView
        FieldName = '程序路径'
        SynchronizeWhenExit = True
      end
      object WVEdit16: TWVEdit
        Left = 100
        Top = 136
        Width = 171
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 4
        Text = '<命令行参数>'
        WorkView = WorkView
        FieldName = '命令行参数'
        SynchronizeWhenExit = True
      end
      object WVEdit20: TWVEdit
        Left = 100
        Top = 216
        Width = 93
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 5
        Text = '<运行开始时间>'
        WorkView = WorkView
        FieldName = '运行开始时间'
        SynchronizeWhenExit = True
      end
      object WVEdit21: TWVEdit
        Left = 350
        Top = 216
        Width = 100
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 6
        Text = '<运行结束时间>'
        WorkView = WorkView
        FieldName = '运行结束时间'
        SynchronizeWhenExit = True
      end
      object WVComboBox1: TWVComboBox
        Left = 350
        Top = 136
        Width = 196
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        MaxLength = 8
        TabOrder = 8
        WorkView = WorkView
        FieldName = '每天一次'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*100'
      end
      object WVComboBox2: TWVComboBox
        Left = 100
        Top = 176
        Width = 172
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        MaxLength = 8
        TabOrder = 9
        WorkView = WorkView
        FieldName = '每星期一次'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*101'
      end
      object WVComboBox3: TWVComboBox
        Left = 350
        Top = 176
        Width = 196
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        MaxLength = 8
        TabOrder = 10
        WorkView = WorkView
        FieldName = '每月一次'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*102'
      end
      object WVComboBox4: TWVComboBox
        Left = 214
        Top = 56
        Width = 59
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        MaxLength = 8
        TabOrder = 11
        WorkView = WorkView
        FieldName = '是否启用'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*64'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 508
    Top = 199
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
        Name = '任务编号'
        Caption = '任务编号'
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
        Name = '任务说明'
        Caption = '任务说明'
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
        GroupIndex = 1
        DataField = 'vsvarstr0'
      end
      item
        Name = '程序名'
        Caption = '程序名'
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
        GroupIndex = 1
        DataField = 'snote'
      end
      item
        Name = '程序路径'
        Caption = '程序路径'
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
        GroupIndex = 1
        DataField = 'Vsvarstr1'
      end
      item
        Name = '命令行参数'
        Caption = '命令行参数'
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
        GroupIndex = 1
        DataField = 'Vsvarstr2'
      end
      item
        Name = '每天一次'
        Caption = '每天一次'
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
        DataField = 'Lvol1'
      end
      item
        Name = '每星期一次'
        Caption = '每星期一次'
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
        Name = '每月一次'
        Caption = '每月一次'
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
        DataField = 'Lvol3'
      end
      item
        Name = '运行开始时间'
        Caption = '运行开始时间'
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
        GroupIndex = 1
        DataField = 'stime0'
      end
      item
        Name = '运行结束时间'
        Caption = '运行结束时间'
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
        GroupIndex = 1
        DataField = 'stime1'
      end
      item
        Name = '是否启用'
        Caption = '是否启用'
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
        GroupIndex = 1
        DataField = 'sstatus1'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.任务说明|查询.程序名|查询.程序路径|查询.命令行参数|查询.每' +
          '天一次|查询.每星期一次|查询.每月一次|查询.运行开始时间|查询.运行' +
          '结束时间|查询.是否启用|查询.交易类型|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|任务编号|任务说明|程序名|程序路径|命令行参数|每天一次|每星期一' +
          '次|每月一次|运行开始时间|运行结束时间|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 424
    Top = 160
  end
  inherited QueryRequest: TWVRequest
    ID = '计划任务查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 560
    Top = 160
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol1'
        DataPresentType = 'idobjects'
        DataPresentParam = '100'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'idobjects'
        DataPresentParam = '101'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '102'
      end
      item
        FieldName = 'sstatus1'
        WVFieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '64'
      end>
    Left = 468
    Top = 199
  end
  inherited AddRequest: TWVRequest
    ID = '计划任务管理'
    Bindings = <
      item
        ParamName = '任务编号'
        FieldName = '任务编号'
      end
      item
        ParamName = '任务说明'
        FieldName = '任务说明'
      end
      item
        ParamName = '程序名'
        FieldName = '程序名'
      end
      item
        ParamName = '程序路径'
        FieldName = '程序路径'
      end
      item
        ParamName = '命令行参数'
        FieldName = '命令行参数'
      end
      item
        ParamName = '每天一次'
        FieldName = '每天一次'
      end
      item
        ParamName = '每星期一次'
        FieldName = '每星期一次'
      end
      item
        ParamName = '每月一次'
        FieldName = '每月一次'
      end
      item
        ParamName = '运行开始时间'
        FieldName = '运行开始时间'
      end
      item
        ParamName = '运行结束时间'
        FieldName = '运行结束时间'
      end
      item
        ParamName = '是否启用'
        FieldName = '是否启用'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 464
    Top = 160
  end
  inherited DeleteRequest: TWVRequest
    ID = '计划任务管理'
    Bindings = <
      item
        ParamName = '任务编号'
        FieldName = '任务编号'
      end
      item
        ParamName = '任务说明'
        FieldName = '任务说明'
      end
      item
        ParamName = '程序名'
        FieldName = '程序名'
      end
      item
        ParamName = '程序路径'
        FieldName = '程序路径'
      end
      item
        ParamName = '命令行参数'
        FieldName = '命令行参数'
      end
      item
        ParamName = '每天一次'
        FieldName = '每天一次'
      end
      item
        ParamName = '每星期一次'
        FieldName = '每星期一次'
      end
      item
        ParamName = '每月一次'
        FieldName = '每月一次'
      end
      item
        ParamName = '运行开始时间'
        FieldName = '运行开始时间'
      end
      item
        ParamName = '运行结束时间'
        FieldName = '运行结束时间'
      end
      item
        ParamName = '是否启用'
        FieldName = '是否启用'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 496
    Top = 160
  end
  inherited ChangeRequest: TWVRequest
    ID = '计划任务管理'
    Bindings = <
      item
        ParamName = '任务编号'
        FieldName = '任务编号'
      end
      item
        ParamName = '任务说明'
        FieldName = '任务说明'
      end
      item
        ParamName = '程序名'
        FieldName = '程序名'
      end
      item
        ParamName = '程序路径'
        FieldName = '程序路径'
      end
      item
        ParamName = '命令行参数'
        FieldName = '命令行参数'
      end
      item
        ParamName = '每天一次'
        FieldName = '每天一次'
      end
      item
        ParamName = '每星期一次'
        FieldName = '每星期一次'
      end
      item
        ParamName = '每月一次'
        FieldName = '每月一次'
      end
      item
        ParamName = '运行开始时间'
        FieldName = '运行开始时间'
      end
      item
        ParamName = '运行结束时间'
        FieldName = '运行结束时间'
      end
      item
        ParamName = '是否启用'
        FieldName = '是否启用'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 528
    Top = 160
  end
  inherited WVDataSource: TWVDataSource
    Left = 580
    Top = 199
  end
  inherited alDatasetActions: TActionList
    Left = 540
    Top = 196
  end
end
