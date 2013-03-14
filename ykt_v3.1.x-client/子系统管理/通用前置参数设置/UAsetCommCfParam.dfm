inherited faqhsetCommCfParam: TfaqhsetCommCfParam
  Width = 763
  Height = 517
  Caption = '通用前置参数设置'
  inherited pcPages: TRzPageControl
    Width = 763
    Height = 517
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 464
        Width = 759
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 586
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 673
          Enabled = False
          TabOrder = 4
        end
        inherited btnQuery: TBitBtn [2]
          Left = 500
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = 254
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Width = 177
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 759
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 759
        Height = 431
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lcert_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '前置编号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Caption = '前置机名'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '心跳时间间隔'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Caption = '心跳接阀值'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Caption = '心跳应答功能号'
            Width = 85
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Caption = '指令调度队列号'
            Width = 85
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol9'
            PickList.Strings = ()
            Title.Caption = '指令应答功能号'
            Width = 85
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol4'
            PickList.Strings = ()
            Title.Caption = '指令执行超时时间'
            Width = 85
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol8'
            PickList.Strings = ()
            Title.Caption = '指令获取时间间隔'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol6'
            PickList.Strings = ()
            Title.Caption = '设备档案请求功能号'
            Width = 85
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Caption = '设备联机模式'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Caption = '流水采集频率'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol7'
            PickList.Strings = ()
            Title.Caption = '指令队列上限'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol10'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '通讯平台节点号'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '通讯平台IP地址'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol12'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '通讯平台端口'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lsafe_level'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '主功能号'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lsafe_level2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '轮询间隔时间(毫秒)'
            Width = 90
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 759
        Height = 15
        Align = alTop
        ParentColor = True
        TabOrder = 1
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label16: TLabel [0]
        Left = 42
        Top = 308
        Width = 48
        Height = 12
        Caption = '前置编号'
        Visible = False
      end
      object Label17: TLabel [1]
        Left = 42
        Top = 348
        Width = 48
        Height = 12
        Caption = '前置机名'
        Visible = False
      end
      object Label18: TLabel [2]
        Left = 22
        Top = 84
        Width = 72
        Height = 12
        Caption = '心跳时间间隔'
      end
      object Label19: TLabel [3]
        Left = 34
        Top = 124
        Width = 60
        Height = 12
        Caption = '心跳接阀值'
      end
      object Label20: TLabel [4]
        Left = 10
        Top = 164
        Width = 84
        Height = 12
        Caption = '心跳应答功能号'
      end
      object Label21: TLabel [5]
        Left = 264
        Top = 44
        Width = 84
        Height = 12
        Caption = '指令调度队列号'
      end
      object Label22: TLabel [6]
        Left = 264
        Top = 84
        Width = 84
        Height = 12
        Caption = '指令应答功能号'
      end
      object Label23: TLabel [7]
        Left = 252
        Top = 124
        Width = 96
        Height = 12
        Caption = '指令执行超时时间'
      end
      object Label24: TLabel [8]
        Left = 252
        Top = 164
        Width = 96
        Height = 12
        Caption = '指令获取时间间隔'
      end
      object Label25: TLabel [9]
        Left = 244
        Top = 348
        Width = 72
        Height = 12
        Caption = '设备种类标志'
        Visible = False
      end
      object Label26: TLabel [10]
        Left = 466
        Top = 44
        Width = 108
        Height = 12
        Caption = '设备档案请求功能号'
      end
      object Label27: TLabel [11]
        Left = 254
        Top = 380
        Width = 72
        Height = 12
        Caption = '设备联机模式'
        Visible = False
      end
      object Label28: TLabel [12]
        Left = 502
        Top = 84
        Width = 72
        Height = 12
        Caption = '流水采集频率'
      end
      object Label29: TLabel [13]
        Left = 502
        Top = 124
        Width = 72
        Height = 12
        Caption = '指令队列上限'
      end
      object Label2: TLabel [14]
        Left = 46
        Top = 44
        Width = 48
        Height = 12
        Caption = '前置编号'
      end
      object Label1: TLabel [15]
        Left = 10
        Top = 204
        Width = 84
        Height = 12
        Caption = '通讯平台节点号'
      end
      object Label3: TLabel [16]
        Left = 264
        Top = 204
        Width = 84
        Height = 12
        Caption = '通讯平台IP地址'
      end
      object Label4: TLabel [17]
        Left = 502
        Top = 164
        Width = 72
        Height = 12
        Caption = '通讯平台端口'
      end
      object Label5: TLabel [18]
        Left = 46
        Top = 244
        Width = 48
        Height = 12
        Caption = '主功能号'
      end
      object Label6: TLabel [19]
        Left = 240
        Top = 244
        Width = 108
        Height = 12
        Caption = '轮询间隔时间(毫秒)'
      end
      inherited UIPanel2: TUIPanel
        Top = 458
        Width = 759
        TabOrder = 20
        inherited btnOK: TBitBtn
          Left = 587
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 675
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object WVEdit16: TWVEdit
        Tag = 9
        Left = 100
        Top = 304
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 16
        Text = '<前置编号>'
        Visible = False
        WorkView = WorkView
        FieldName = '前置编号'
        SynchronizeWhenExit = True
      end
      object WVEdit17: TWVEdit
        Left = 100
        Top = 344
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 17
        Text = '<前置机名>'
        Visible = False
        WorkView = WorkView
        FieldName = '前置机名'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit18: TWVEdit
        Tag = 9
        Left = 100
        Top = 80
        Width = 137
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 3
        Text = '<心跳时间间隔>'
        WorkView = WorkView
        FieldName = '心跳时间间隔'
      end
      object WVDigitalEdit19: TWVEdit
        Tag = 9
        Left = 100
        Top = 120
        Width = 137
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 6
        Text = '<心跳接阀值>'
        WorkView = WorkView
        FieldName = '心跳接阀值'
      end
      object WVDigitalEdit20: TWVEdit
        Tag = 9
        Left = 100
        Top = 160
        Width = 137
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 9
        Text = '<心跳应答功能号>'
        WorkView = WorkView
        FieldName = '心跳应答功能号'
      end
      object WVDigitalEdit21: TWVEdit
        Tag = 9
        Left = 352
        Top = 40
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 1
        Text = '<指令调度队列号>'
        WorkView = WorkView
        FieldName = '指令调度队列号'
      end
      object WVDigitalEdit22: TWVEdit
        Tag = 9
        Left = 352
        Top = 80
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 4
        Text = '<指令应答功能号>'
        WorkView = WorkView
        FieldName = '指令应答功能号'
      end
      object WVDigitalEdit23: TWVEdit
        Tag = 9
        Left = 352
        Top = 120
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 7
        Text = '<指令执行超时时间>'
        WorkView = WorkView
        FieldName = '指令执行超时时间'
      end
      object WVDigitalEdit24: TWVEdit
        Tag = 9
        Left = 352
        Top = 160
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 10
        Text = '<指令获取时间间隔>'
        WorkView = WorkView
        FieldName = '指令获取时间间隔'
      end
      object WVEdit25: TWVEdit
        Left = 326
        Top = 344
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 18
        Text = '<设备种类标志>'
        Visible = False
        WorkView = WorkView
        FieldName = '设备种类标志'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit26: TWVEdit
        Tag = 9
        Left = 580
        Top = 40
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 2
        Text = '<设备档案请求功能号>'
        WorkView = WorkView
        FieldName = '设备档案请求功能号'
      end
      object WVEdit27: TWVEdit
        Left = 332
        Top = 376
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 19
        Text = '<设备联机模式>'
        Visible = False
        WorkView = WorkView
        FieldName = '设备联机模式'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit28: TWVEdit
        Tag = 9
        Left = 580
        Top = 80
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 5
        Text = '<流水采集频率>'
        WorkView = WorkView
        FieldName = '流水采集频率'
      end
      object WVDigitalEdit29: TWVEdit
        Tag = 9
        Left = 580
        Top = 120
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 8
        Text = '<指令队列上限>'
        WorkView = WorkView
        FieldName = '指令队列上限'
      end
      object WVComboBox1: TWVComboBox
        Left = 100
        Top = 40
        Width = 137
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 0
        WorkView = WorkView
        FieldName = '前置编号'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-32'
      end
      object WVEdit1: TWVEdit
        Tag = 9
        Left = 100
        Top = 200
        Width = 137
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 12
        Text = '<节点号>'
        WorkView = WorkView
        FieldName = '节点号'
      end
      object edtIp: TWVEdit
        Left = 352
        Top = 200
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 13
        Text = '<平台IP>'
        WorkView = WorkView
        FieldName = '平台IP'
      end
      object WVEdit3: TWVEdit
        Tag = 9
        Left = 580
        Top = 160
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 11
        Text = '<端口>'
        WorkView = WorkView
        FieldName = '端口'
      end
      object WVEdit4: TWVEdit
        Tag = 9
        Left = 100
        Top = 240
        Width = 137
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 14
        Text = '<功能号>'
        WorkView = WorkView
        FieldName = '功能号'
      end
      object WVEdit5: TWVEdit
        Tag = 9
        Left = 352
        Top = 240
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 15
        Text = '<轮询间隔时间>'
        WorkView = WorkView
        FieldName = '轮询间隔时间'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 404
    Top = 303
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
        Name = '标志'
        Caption = '标志'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '前置编号'
        Caption = '前置编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lcert_code'
      end
      item
        Name = '前置机名'
        Caption = '前置机名'
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
        GroupIndex = 1
        DataField = 'semail'
      end
      item
        Name = '心跳时间间隔'
        Caption = '心跳时间间隔'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '心跳接阀值'
        Caption = '心跳接阀值'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '心跳应答功能号'
        Caption = '心跳应答功能号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol2'
      end
      item
        Name = '指令调度队列号'
        Caption = '指令调度队列号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol3'
      end
      item
        Name = '指令应答功能号'
        Caption = '指令应答功能号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol9'
      end
      item
        Name = '指令执行超时时间'
        Caption = '指令执行超时时间'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol4'
      end
      item
        Name = '指令获取时间间隔'
        Caption = '指令获取时间间隔'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol8'
      end
      item
        Name = '设备种类标志'
        Caption = '设备种类标志'
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
        GroupIndex = 1
        DataField = 'sdate0'
      end
      item
        Name = '设备档案请求功能号'
        Caption = '设备档案请求功能号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol6'
      end
      item
        Name = '设备联机模式'
        Caption = '设备联机模式'
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
        GroupIndex = 1
        DataField = 'sstatus1'
      end
      item
        Name = '流水采集频率'
        Caption = '流水采集频率'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '指令队列上限'
        Caption = '指令队列上限'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol7'
      end
      item
        Name = '工作密钥'
        Caption = '工作密钥'
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
        GroupIndex = 1
        DataField = 'sname2'
      end
      item
        Name = '节点号'
        Caption = '节点号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol10'
      end
      item
        Name = '平台IP'
        Caption = '平台IP'
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
        DataField = 'scust_auth'
      end
      item
        Name = '端口'
        Caption = '端口'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol12'
      end
      item
        Name = '功能号'
        Caption = '功能号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lsafe_level'
      end
      item
        Name = '轮询间隔时间'
        Caption = '轮询间隔时间'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lsafe_level2'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.前置粅查询.心跳时间间隔|查询.心跳接阀值|查询.心跳应答功能' +
          '号|查询.指令调度队列号|查询.指令应答功能号|查询.指令执行超时时间' +
          '|查询.指令获取时间间隔|查询.设备种类标志|查询.设备档案请求功能号' +
          '|查询.设备联机模式|查询.流水采集频率|查询.指令队列上限|查询.工作' +
          '密钥|查询.标志|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|前置粅前置机名|心跳时间间隔|心跳接阀值|心跳应答功能号|指令调度' +
          '队列号|指令应答功能号|指令执行超时时间|指令获取时间间隔|设备种类' +
          '标志|设备档案请求功能号|设备联机模式|流水采集频率|指令队列上限|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 328
    Top = 304
  end
  inherited QueryRequest: TWVRequest
    ID = '通用前置参数查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '标志'
        FieldName = '标志'
      end>
    Left = 448
    Top = 272
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 364
    Top = 303
  end
  inherited AddRequest: TWVRequest
    ID = '通用前置参数设置'
    Bindings = <
      item
        ParamName = '前置编号'
        FieldName = '前置编号'
      end
      item
        ParamName = '前置机名'
        FieldName = '前置机名'
      end
      item
        ParamName = '心跳时间间隔'
        FieldName = '心跳时间间隔'
      end
      item
        ParamName = '心跳接阀值'
        FieldName = '心跳接阀值'
      end
      item
        ParamName = '心跳应答功能号'
        FieldName = '心跳应答功能号'
      end
      item
        ParamName = '指令调度队列号'
        FieldName = '指令调度队列号'
      end
      item
        ParamName = '指令应答功能号'
        FieldName = '指令应答功能号'
      end
      item
        ParamName = '指令执行超时时间'
        FieldName = '指令执行超时时间'
      end
      item
        ParamName = '指令获取时间间隔'
        FieldName = '指令获取时间间隔'
      end
      item
        ParamName = '设备种类标志'
        FieldName = '设备种类标志'
      end
      item
        ParamName = '设备档案请求功能号'
        FieldName = '设备档案请求功能号'
      end
      item
        ParamName = '设备联机模式'
        FieldName = '设备联机模式'
      end
      item
        ParamName = '流水采集频率'
        FieldName = '流水采集频率'
      end
      item
        ParamName = '指令队列上限'
        FieldName = '指令队列上限'
      end
      item
        ParamName = '工作密钥'
        FieldName = '工作密钥'
      end
      item
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '节点号'
        FieldName = '节点号'
      end
      item
        ParamName = '平台IP'
        FieldName = '平台IP'
      end
      item
        ParamName = '端口'
        FieldName = '端口'
      end
      item
        ParamName = '功能号'
        FieldName = '功能号'
      end
      item
        ParamName = '轮询间隔时间'
        FieldName = '轮询间隔时间'
      end>
    Left = 328
    Top = 272
  end
  inherited DeleteRequest: TWVRequest
    ID = '通用前置参数设置'
    Bindings = <
      item
        ParamName = '前置编号'
        FieldName = '前置编号'
      end
      item
        ParamName = '前置机名'
        FieldName = '前置机名'
      end
      item
        ParamName = '心跳时间间隔'
        FieldName = '心跳时间间隔'
      end
      item
        ParamName = '心跳接阀值'
        FieldName = '心跳接阀值'
      end
      item
        ParamName = '心跳应答功能号'
        FieldName = '心跳应答功能号'
      end
      item
        ParamName = '指令调度队列号'
        FieldName = '指令调度队列号'
      end
      item
        ParamName = '指令应答功能号'
        FieldName = '指令应答功能号'
      end
      item
        ParamName = '指令执行超时时间'
        FieldName = '指令执行超时时间'
      end
      item
        ParamName = '指令获取时间间隔'
        FieldName = '指令获取时间间隔'
      end
      item
        ParamName = '设备种类标志'
        FieldName = '设备种类标志'
      end
      item
        ParamName = '设备档案请求功能号'
        FieldName = '设备档案请求功能号'
      end
      item
        ParamName = '设备联机模式'
        FieldName = '设备联机模式'
      end
      item
        ParamName = '流水采集频率'
        FieldName = '流水采集频率'
      end
      item
        ParamName = '指令队列上限'
        FieldName = '指令队列上限'
      end
      item
        ParamName = '工作密钥'
        FieldName = '工作密钥'
      end
      item
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '节点号'
        FieldName = '节点号'
      end
      item
        ParamName = '平台IP'
        FieldName = '平台IP'
      end
      item
        ParamName = '端口'
        FieldName = '端口'
      end
      item
        ParamName = '功能号'
        FieldName = '功能号'
      end
      item
        ParamName = '轮询间隔时间'
        FieldName = '轮询间隔时间志'
      end>
    Left = 368
    Top = 272
  end
  inherited ChangeRequest: TWVRequest
    ID = '通用前置参数设置'
    Bindings = <
      item
        ParamName = '前置编号'
        FieldName = '前置编号'
      end
      item
        ParamName = '前置机名'
        FieldName = '前置机名'
      end
      item
        ParamName = '心跳时间间隔'
        FieldName = '心跳时间间隔'
      end
      item
        ParamName = '心跳接阀值'
        FieldName = '心跳接阀值'
      end
      item
        ParamName = '心跳应答功能号'
        FieldName = '心跳应答功能号'
      end
      item
        ParamName = '指令调度队列号'
        FieldName = '指令调度队列号'
      end
      item
        ParamName = '指令应答功能号'
        FieldName = '指令应答功能号'
      end
      item
        ParamName = '指令执行超时时间'
        FieldName = '指令执行超时时间'
      end
      item
        ParamName = '指令获取时间间隔'
        FieldName = '指令获取时间间隔'
      end
      item
        ParamName = '设备种类标志'
        FieldName = '设备种类标志'
      end
      item
        ParamName = '设备档案请求功能号'
        FieldName = '设备档案请求功能号'
      end
      item
        ParamName = '设备联机模式'
        FieldName = '设备联机模式'
      end
      item
        ParamName = '流水采集频率'
        FieldName = '流水采集频率'
      end
      item
        ParamName = '指令队列上限'
        FieldName = '指令队列上限'
      end
      item
        ParamName = '工作密钥'
        FieldName = '工作密钥'
      end
      item
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '节点号'
        FieldName = '节点号'
      end
      item
        ParamName = '平台IP'
        FieldName = '平台IP'
      end
      item
        ParamName = '端口'
        FieldName = '端口'
      end
      item
        ParamName = '功能号'
        FieldName = '功能号'
      end
      item
        ParamName = '轮询间隔时间'
        FieldName = '轮询间隔时间'
      end>
    Left = 408
    Top = 272
  end
  inherited WVDataSource: TWVDataSource
    Left = 444
    Top = 303
  end
  inherited alDatasetActions: TActionList
    Left = 444
    Top = 340
  end
end
