inherited faqhSetSubSystemInfo: TfaqhSetSubSystemInfo
  Width = 688
  Height = 485
  Caption = '子系统设置'
  inherited pcPages: TRzPageControl
    Width = 688
    Height = 485
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 432
        Width = 684
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 418
        end
        inherited btnChange: TBitBtn [1]
          Left = 506
        end
        inherited btnQuery: TBitBtn [2]
        end
        inherited btnDelete: TBitBtn
          Left = 595
          Caption = '&D 注销'
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Checked = False
          State = cbUnchecked
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 684
      end
      inherited Grid: TRzDBGrid
        Top = 75
        Width = 684
        Height = 357
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '子系统标识'
            Width = 78
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '名称'
            Width = 82
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '子系统状态'
            Width = 72
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '子系统类别'
            Width = 84
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '所在区域'
            Width = 107
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '网络地址'
            Width = 87
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '网卡物理地址'
            Width = 101
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '工作站'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol6'
            PickList.Strings = ()
            Title.Caption = '端口号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol7'
            PickList.Strings = ()
            Title.Caption = '加密方式'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Caption = '功能列表'
            Visible = False
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
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 684
        Height = 57
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label1: TLabel
          Left = 63
          Top = 12
          Width = 24
          Height = 12
          Caption = '名称'
        end
        object WVLabel11: TWVLabel
          Left = 40
          Top = 36
          Width = 48
          Height = 12
          Caption = '所在区域'
        end
        object WVLabel12: TWVLabel
          Left = 248
          Top = 11
          Width = 60
          Height = 12
          Caption = '子系统类别'
        end
        object WVLabel13: TWVLabel
          Left = 261
          Top = 36
          Width = 48
          Height = 12
          Caption = '网络地址'
        end
        object WVLabel14: TWVLabel
          Left = 468
          Top = 36
          Width = 72
          Height = 12
          Caption = '网卡物理地址'
        end
        object WVLabel15: TWVLabel
          Left = 480
          Top = 11
          Width = 60
          Height = 12
          Caption = '子系统状态'
        end
        object WVComboBox1: TWVComboBox
          Left = 100
          Top = 32
          Width = 130
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '查询.子系统所在区域'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-28'
        end
        object WVEdit9: TWVEdit
          Left = 100
          Top = 8
          Width = 130
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.子系统名称>'
          WorkView = WorkView
          FieldName = '查询.子系统名称'
        end
        object WVComboBox5: TWVComboBox
          Left = 320
          Top = 8
          Width = 130
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 1
          WorkView = WorkView
          FieldName = '查询.子系统类别'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*8'
        end
        object WVEdit11: TWVEdit
          Left = 320
          Top = 32
          Width = 130
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 4
          Text = '<查询.网络地址>'
          WorkView = WorkView
          FieldName = '查询.网络地址'
        end
        object WVEdit12: TWVEdit
          Left = 548
          Top = 32
          Width = 130
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 5
          Text = '<查询.网卡物理地址>'
          WorkView = WorkView
          FieldName = '查询.网卡物理地址'
        end
        object WVComboBox6: TWVComboBox
          Left = 548
          Top = 8
          Width = 130
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '查询.子系统状态'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*7'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label3: TLabel [0]
        Left = 92
        Top = 108
        Width = 30
        Height = 12
        Caption = '名称*'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel [1]
        Left = 68
        Top = 172
        Width = 54
        Height = 12
        Caption = '所在区域*'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label5: TLabel [2]
        Left = 650
        Top = 52
        Width = 48
        Height = 12
        Caption = '工作站号'
        Visible = False
      end
      object Label6: TLabel [3]
        Left = 68
        Top = 204
        Width = 54
        Height = 12
        Caption = '网络地址*'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label7: TLabel [4]
        Left = 618
        Top = 180
        Width = 72
        Height = 12
        Caption = '子系统版本号'
        Visible = False
      end
      object Label8: TLabel [5]
        Left = 628
        Top = 18
        Width = 72
        Height = 12
        Caption = '负责人员工号'
        Visible = False
      end
      object Label9: TLabel [6]
        Left = 636
        Top = 84
        Width = 48
        Height = 12
        Caption = '联系电话'
        Visible = False
      end
      object Label10: TLabel [7]
        Left = 644
        Top = 140
        Width = 48
        Height = 12
        Caption = '联系地址'
        Visible = False
      end
      object WVLabel1: TWVLabel [8]
        Left = 98
        Top = 301
        Width = 24
        Height = 12
        Caption = '备注'
      end
      object WVLabel2: TWVLabel [9]
        Left = 60
        Top = 76
        Width = 60
        Height = 12
        Caption = '子系统状态'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Visible = False
      end
      object WVLabel3: TWVLabel [10]
        Left = 604
        Top = 108
        Width = 96
        Height = 12
        Caption = '前次时钟同步时间'
        Visible = False
      end
      object WVLabel4: TWVLabel [11]
        Left = 56
        Top = 141
        Width = 66
        Height = 12
        Caption = '子系统类别*'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object WVLabel5: TWVLabel [12]
        Left = 44
        Top = 235
        Width = 78
        Height = 12
        Caption = '网卡物理地址*'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object WVLabel6: TWVLabel [13]
        Left = 60
        Top = 44
        Width = 60
        Height = 12
        Caption = '子系统标识'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Visible = False
      end
      object WVLabel7: TWVLabel [14]
        Left = 344
        Top = 235
        Width = 287
        Height = 14
        Caption = '格式：17位,0-9或者A-F,每两位之间用"-"符号'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '楷体_GB2312'
        Font.Style = []
        ParentFont = False
      end
      object WVLabel8: TWVLabel [15]
        Left = 632
        Top = 32
        Width = 60
        Height = 12
        Caption = '(双击选择)'
        Visible = False
      end
      object WVLabel9: TWVLabel [16]
        Left = 570
        Top = 269
        Width = 48
        Height = 12
        Caption = '加密方式'
        Visible = False
      end
      object Label2: TLabel [17]
        Left = 86
        Top = 268
        Width = 36
        Height = 12
        Caption = '端口号'
      end
      object Label13: TLabel [18]
        Left = 570
        Top = 300
        Width = 48
        Height = 12
        Caption = '功能列表'
        Visible = False
      end
      object WVLabel10: TWVLabel [19]
        Left = 840
        Top = 299
        Width = 154
        Height = 14
        Caption = '各功能号之间用(，)分开'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '楷体_GB2312'
        Font.Style = []
        ParentFont = False
        Visible = False
      end
      inherited UIPanel2: TUIPanel
        Top = 426
        Width = 684
        TabOrder = 18
        inherited btnOK: TBitBtn
          Left = 508
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 596
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object WVDigitalEdit2: TWVDigitalEdit
        Left = 140
        Top = 40
        Width = 198
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        ParentColor = False
        TabOrder = 1
        TabStop = True
        Text = '0'
        Visible = False
        WorkView = WorkView
        FieldName = '子系统标识'
        SynchronizeByValue = True
      end
      object WVEdit3: TWVEdit
        Left = 140
        Top = 104
        Width = 198
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 5
        Text = '<子系统名称>'
        WorkView = WorkView
        FieldName = '子系统名称'
        SynchronizeWhenExit = True
      end
      object WVComboBox4: TWVComboBox
        Left = 140
        Top = 168
        Width = 198
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 9
        WorkView = WorkView
        FieldName = '子系统所在区域'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-28'
      end
      object WVEdit6: TWVEdit
        Left = 140
        Top = 200
        Width = 198
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 11
        Text = '<网络地址>'
        WorkView = WorkView
        FieldName = '网络地址'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit7: TWVDigitalEdit
        Left = 708
        Top = 176
        Width = 198
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        ParentColor = False
        TabOrder = 10
        TabStop = True
        Text = '0'
        Visible = False
        WorkView = WorkView
        FieldName = '子系统版本号'
        SynchronizeByValue = True
      end
      object WVEdit10: TWVEdit
        Left = 708
        Top = 136
        Width = 529
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 8
        Text = '<联系地址>'
        Visible = False
        WorkView = WorkView
        FieldName = '联系地址'
        SynchronizeWhenExit = True
      end
      object WVEdit1: TWVEdit
        Left = 140
        Top = 296
        Width = 403
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 15
        Text = '<备注>'
        WorkView = WorkView
        FieldName = '备注'
      end
      object WVComboBox2: TWVComboBox
        Left = 140
        Top = 72
        Width = 198
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 3
        Visible = False
        WorkView = WorkView
        FieldName = '子系统状态'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '7'
      end
      object WVEdit2: TWVEdit
        Left = 707
        Top = 104
        Width = 142
        Height = 20
        ParentColor = True
        ReadOnly = True
        TabOrder = 6
        Text = '<前次时钟同步时间>'
        Visible = False
        WorkView = WorkView
        FieldName = '前次时钟同步时间'
      end
      object WVComboBox3: TWVComboBox
        Left = 140
        Top = 136
        Width = 198
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 7
        WorkView = WorkView
        FieldName = '子系统类别'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*8'
      end
      object WVEdit4: TWVEdit
        Left = 140
        Top = 232
        Width = 198
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 12
        Text = '<网卡物理地址>'
        WorkView = WorkView
        FieldName = '网卡物理地址'
      end
      object WVEdit5: TWVEdit
        Left = 708
        Top = 48
        Width = 109
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 2
        Text = '<工作站>'
        Visible = False
        WorkView = WorkView
        FieldName = '工作站'
      end
      object WVDigitalEdit8: TWVEdit
        Left = 708
        Top = 16
        Width = 110
        Height = 20
        ParentColor = True
        ParentShowHint = False
        ReadOnly = True
        ShowHint = True
        TabOrder = 0
        Text = '<负责人员工号>'
        Visible = False
        OnDblClick = WVDigitalEdit8DblClick
        WorkView = WorkView
        FieldName = '负责人员工号'
      end
      object WVDigitalEdit9: TWVEdit
        Left = 704
        Top = 80
        Width = 153
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 4
        Text = '<联系电话>'
        Visible = False
        WorkView = WorkView
        FieldName = '联系电话'
      end
      object cbbency: TWVComboBox
        Left = 636
        Top = 264
        Width = 198
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 14
        Visible = False
        WorkView = WorkView
        FieldName = '加密方式'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*72'
      end
      object WVEdit7: TWVEdit
        Left = 140
        Top = 264
        Width = 198
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 13
        Text = '<端口号>'
        WorkView = WorkView
        FieldName = '端口号'
        SynchronizeWhenExit = True
      end
      object WVEdit8: TWVEdit
        Left = 636
        Top = 296
        Width = 198
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 16
        Text = '<功能列表>'
        Visible = False
        WorkView = WorkView
        FieldName = '功能列表'
        SynchronizeWhenExit = True
      end
      object cbbSubSystem: TWVComboBox
        Left = 100
        Top = 384
        Width = 130
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 17
        Visible = False
        WorkView = WorkView
        FieldName = '查询.子系统所在区域'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-32'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 380
    Top = 239
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
        Name = '子系统标识'
        Caption = '子系统标识'
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
        DataField = 'lvol0'
      end
      item
        Name = '子系统名称'
        Caption = '子系统名称'
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
        Name = '子系统类别'
        Caption = '子系统类别'
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
        Name = '子系统状态'
        Caption = '子系统状态'
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
        DataField = 'lvol2'
      end
      item
        Name = '子系统所在区域'
        Caption = '子系统所在区域'
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
        DataField = 'lvol3'
      end
      item
        Name = '工作站'
        Caption = '工作站'
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
        DataField = 'lvol4'
      end
      item
        Name = '网络地址'
        Caption = '网络地址'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_auth2'
      end
      item
        Name = '网卡物理地址'
        Caption = '网卡物理地址'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = True
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sname'
      end
      item
        Name = '前次时钟同步时间'
        Caption = '前次时钟同步时间'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'spager'
      end
      item
        Name = '子系统版本号'
        Caption = '子系统版本号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Max = 65535
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '联系地址'
        Caption = '联系地址'
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
        DataField = 'scusttypes'
      end
      item
        Name = '负责人员工号'
        Caption = '负责人员工号'
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
      end
      item
        Name = '联系电话'
        Caption = '联系电话'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sphone'
      end
      item
        Name = '备注'
        Caption = '备注'
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
        DataField = 'ssectypes'
      end
      item
        Name = '端口号'
        Caption = '端口号'
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
        DataField = 'lvol6'
      end
      item
        Name = '加密方式'
        Caption = '加密方式'
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
        DataField = 'lvol7'
      end
      item
        Name = '功能列表'
        Caption = '功能列表'
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
        DataField = 'vsvarstr0'
      end
      item
        Name = '查询.子系统名称'
        Caption = '查询.子系统名称'
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
        Name = '查询.子系统类别'
        Caption = '查询.子系统类别'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '查询.子系统状态'
        Caption = '查询.子系统状态'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '查询.子系统所在区域'
        Caption = '查询.子系统所在区域'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '查询.网络地址'
        Caption = '查询.网络地址'
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
        Name = '查询.网卡物理地址'
        Caption = '查询.网卡物理地址'
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
        MonitorValueChangedFields = '|查询.子系统标志|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|子系统标志|子系统名称|子系统区域|工作站号|网卡地址|子系统版本号' +
          '|负责人员工号|联系电话|联系地址|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 344
    Top = 200
  end
  inherited QueryRequest: TWVRequest
    ID = '子系统非主键查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '网卡物理地址'
        FieldName = '查询.网卡物理地址'
      end
      item
        ParamName = '网络地址'
        FieldName = '查询.网络地址'
      end
      item
        ParamName = '子系统类别'
        FieldName = '查询.子系统类别'
      end
      item
        ParamName = '子系统名称'
        FieldName = '查询.子系统名称'
      end
      item
        ParamName = '子系统所在区域'
        FieldName = '查询.子系统所在区域'
      end
      item
        ParamName = '子系统状态'
        FieldName = '查询.子系统状态'
      end>
    Left = 504
    Top = 200
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '8'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '7'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-28'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-31'
      end
      item
        FieldName = 'lvol7'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '72'
      end>
    Left = 340
    Top = 239
  end
  inherited AddRequest: TWVRequest
    ID = '子系统设置.增加'
    Bindings = <
      item
        ParamName = '子系统名称'
        FieldName = '子系统名称'
      end
      item
        ParamName = '子系统类别'
        FieldName = '子系统类别'
      end
      item
        ParamName = '子系统所在区域'
        FieldName = '子系统所在区域'
      end
      item
        ParamName = '工作站'
        FieldName = '工作站'
      end
      item
        ParamName = '网络地址'
        FieldName = '网络地址'
      end
      item
        ParamName = '网卡物理地址'
        FieldName = '网卡物理地址'
      end
      item
        ParamName = '子系统版本号'
        FieldName = '子系统版本号'
      end
      item
        ParamName = '负责人员工号'
        FieldName = '负责人员工号'
      end
      item
        ParamName = '联系电话'
        FieldName = '联系电话'
      end
      item
        ParamName = '联系地址'
        FieldName = '联系地址'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end
      item
        ParamName = '端口号'
        FieldName = '端口号'
      end
      item
        ParamName = '加密方式'
        FieldName = '加密方式'
      end
      item
        ParamName = '功能列表'
        FieldName = '功能列表'
      end>
    Left = 384
    Top = 200
  end
  inherited DeleteRequest: TWVRequest
    ID = '子系统设置.删除'
    Bindings = <
      item
        ParamName = '子系统标识'
        FieldName = '子系统标识'
      end
      item
        ParamName = '子系统名称'
        FieldName = '子系统名称'
      end
      item
        ParamName = '子系统类别'
        FieldName = '子系统类别'
      end
      item
        ParamName = '子系统状态'
        FieldName = '子系统状态'
      end
      item
        ParamName = '子系统所在区域'
        FieldName = '子系统所在区域'
      end
      item
        ParamName = '工作站'
        FieldName = '工作站'
      end
      item
        ParamName = '网络地址'
        FieldName = '网络地址'
      end
      item
        ParamName = '网卡物理地址'
        FieldName = '网卡物理地址'
      end
      item
        ParamName = '前次时钟同步时间'
        FieldName = '前次时钟同步时间'
      end
      item
        ParamName = '子系统版本号'
        FieldName = '子系统版本号'
      end
      item
        ParamName = '负责人员工号'
        FieldName = '负责人员工号'
      end
      item
        ParamName = '联系电话'
        FieldName = '联系电话'
      end
      item
        ParamName = '联系地址'
        FieldName = '联系地址'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end
      item
        ParamName = '端口号'
        FieldName = '端口号'
      end
      item
        ParamName = '加密方式'
        FieldName = '加密方式'
      end
      item
        ParamName = '功能列表'
        FieldName = '功能列表'
      end>
    Left = 424
    Top = 200
  end
  inherited ChangeRequest: TWVRequest
    ID = '子系统设置.修改'
    Bindings = <
      item
        ParamName = '子系统标识'
        FieldName = '子系统标识'
      end
      item
        ParamName = '子系统名称'
        FieldName = '子系统名称'
      end
      item
        ParamName = '子系统类别'
        FieldName = '子系统类别'
      end
      item
        ParamName = '子系统状态'
        FieldName = '子系统状态'
      end
      item
        ParamName = '子系统所在区域'
        FieldName = '子系统所在区域'
      end
      item
        ParamName = '工作站'
        FieldName = '工作站'
      end
      item
        ParamName = '网络地址'
        FieldName = '网络地址'
      end
      item
        ParamName = '网卡物理地址'
        FieldName = '网卡物理地址'
      end
      item
        ParamName = '前次时钟同步时间'
        FieldName = '前次时钟同步时间'
      end
      item
        ParamName = '子系统版本号'
        FieldName = '子系统版本号'
      end
      item
        ParamName = '负责人员工号'
        FieldName = '负责人员工号'
      end
      item
        ParamName = '联系电话'
        FieldName = '联系电话'
      end
      item
        ParamName = '联系地址'
        FieldName = '联系地址'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end
      item
        ParamName = '端口号'
        FieldName = '端口号'
      end
      item
        ParamName = '加密方式'
        FieldName = '加密方式'
      end
      item
        ParamName = '功能列表'
        FieldName = '功能列表'
      end>
    Left = 464
    Top = 200
  end
  inherited WVDataSource: TWVDataSource
    Left = 460
    Top = 239
  end
  inherited alDatasetActions: TActionList
    Left = 420
    Top = 236
  end
end
