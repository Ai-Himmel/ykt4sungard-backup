inherited faqhSetBusinessEquipInfo: TfaqhSetBusinessEquipInfo
  Width = 882
  Height = 581
  Caption = '设备商户信息设置'
  inherited pcPages: TRzPageControl
    Width = 882
    Height = 581
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      OnEnter = tsQueryEnter
      inherited UIPanel1: TUIPanel
        Top = 520
        Width = 878
        Height = 38
        TabOrder = 5
        inherited btnAdd: TBitBtn [0]
          Left = 616
          Enabled = False
          TabOrder = 3
          Visible = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 704
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 523
          Visible = False
        end
        inherited btnDelete: TBitBtn
          Left = 789
          Enabled = False
          TabOrder = 2
          Visible = False
        end
        inherited btnViewDetail: TBitBtn
          Visible = False
        end
        inherited ckAutoSetNewParams: TCheckBox
          Visible = False
        end
        object btnAddEB1: TButton
          Left = 488
          Top = 8
          Width = 73
          Height = 28
          Caption = '增加设备'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 6
          OnClick = btnAddEB1Click
        end
        object btnBefChaEB2: TButton
          Left = 576
          Top = 8
          Width = 73
          Height = 28
          Caption = '修改设备'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 7
          OnClick = btnBefChaEB2Click
        end
        object btnBefDelEB2: TButton
          Left = 664
          Top = 8
          Width = 73
          Height = 28
          Caption = '删除设备'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 8
          OnClick = btnBefDelEB2Click
        end
        object btnReTree1: TButton
          Left = 88
          Top = 8
          Width = 73
          Height = 28
          Caption = '刷新显示'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 9
          OnClick = btnReTree1Click
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 878
      end
      inherited Grid: TRzDBGrid
        Left = 568
        Top = 192
        Width = 378
        Height = 328
        Align = alNone
        Visible = False
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Caption = '编号'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '设备标识'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Caption = '商户标识'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_no'
            PickList.Strings = ()
            Title.Caption = '使用开始日期'
            Width = 93
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sholder_ac_no'
            PickList.Strings = ()
            Title.Caption = '使用开始时间'
            Width = 88
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_no2'
            PickList.Strings = ()
            Title.Caption = '使用结束日期'
            Width = 92
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sholder_ac_no2'
            PickList.Strings = ()
            Title.Caption = '使用结束时间'
            Width = 88
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Caption = '备注'
            Width = 193
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 304
        Top = 224
        Width = 273
        Height = 169
        ParentColor = True
        TabOrder = 0
        Visible = False
        object Label9: TLabel
          Left = 42
          Top = 5
          Width = 128
          Height = 16
          Caption = '设备商户信息查询'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = '黑体'
          Font.Style = []
          ParentFont = False
        end
        object Label1: TLabel
          Left = 58
          Top = 41
          Width = 24
          Height = 12
          Caption = '编号'
        end
        object Label13: TLabel
          Left = 258
          Top = 41
          Width = 72
          Height = 12
          Caption = '使用开始日期'
        end
        object Label14: TLabel
          Left = 538
          Top = 41
          Width = 72
          Height = 12
          Caption = '使用结束日期'
        end
        object WVEdit4: TWVEdit
          Left = 104
          Top = 37
          Width = 97
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.编号>'
          WorkView = WorkView
          FieldName = '查询.编号'
        end
        object WVEdit5: TWVEdit
          Left = 356
          Top = 37
          Width = 100
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.使用开始日期>'
          WorkView = WorkView
          FieldName = '查询.使用开始日期'
        end
        object WVEdit8: TWVEdit
          Left = 644
          Top = 37
          Width = 100
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 2
          Text = '<查询.使用结束日期>'
          WorkView = WorkView
          FieldName = '查询.使用结束日期'
        end
      end
      object UIPanel5: TUIPanel
        Left = 0
        Top = 73
        Width = 878
        Height = 447
        Align = alClient
        Color = 15458000
        TabOrder = 3
        object Splitter1: TSplitter
          Left = 401
          Top = 1
          Width = 4
          Height = 445
          Cursor = crHSplit
          Beveled = True
        end
        object treevEquAndBusi2: TTreeView
          Left = 1
          Top = 1
          Width = 400
          Height = 445
          Align = alLeft
          Images = ImageList1
          Indent = 19
          PopupMenu = PopupMenu1
          TabOrder = 0
          OnMouseDown = treevEquAndBusi2MouseDown
          OnMouseUp = treevEquAndBusi2MouseUp
        end
        object EquipTreVw1: TTreeView
          Left = 405
          Top = 1
          Width = 472
          Height = 445
          Align = alClient
          Images = ImageList1
          Indent = 19
          TabOrder = 1
          OnMouseDown = EquipTreVw1MouseDown
        end
      end
      object UIPanel7: TUIPanel
        Left = 0
        Top = 18
        Width = 878
        Height = 55
        Align = alTop
        Color = 15458000
        TabOrder = 4
        object Label15: TLabel
          Left = 344
          Top = 9
          Width = 160
          Height = 16
          Caption = '为选中的商户分配设备'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object Label18: TLabel
          Left = 384
          Top = 29
          Width = 108
          Height = 12
          Caption = '<-----------------'
          Font.Charset = GB2312_CHARSET
          Font.Color = clRed
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
          Visible = False
        end
        object Label17: TLabel
          Left = 496
          Top = 29
          Width = 42
          Height = 12
          Caption = 'Label17'
        end
        object Label16: TLabel
          Left = 312
          Top = 29
          Width = 42
          Height = 12
          Caption = 'Label16'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 66
        Top = 44
        Width = 24
        Height = 12
        Caption = '编号'
      end
      object Label3: TLabel [1]
        Left = 78
        Top = 80
        Width = 48
        Height = 12
        Caption = '设备标识'
        Visible = False
      end
      object Label4: TLabel [2]
        Left = 82
        Top = 120
        Width = 48
        Height = 12
        Caption = '商户标识'
        Visible = False
      end
      object Label5: TLabel [3]
        Left = 268
        Top = 44
        Width = 72
        Height = 12
        Caption = '使用开始日期'
      end
      object Label6: TLabel [4]
        Left = 268
        Top = 80
        Width = 72
        Height = 12
        Caption = '使用开始时间'
      end
      object Label7: TLabel [5]
        Left = 268
        Top = 120
        Width = 72
        Height = 12
        Caption = '使用结束时间'
      end
      object Label8: TLabel [6]
        Left = 468
        Top = 44
        Width = 72
        Height = 12
        Caption = '使用结束日期'
      end
      object Label10: TLabel [7]
        Left = 42
        Top = 5
        Width = 128
        Height = 16
        Caption = '设备商户关系设置'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '黑体'
        Font.Style = []
        ParentFont = False
      end
      object WVLabel1: TWVLabel [8]
        Left = 74
        Top = 200
        Width = 24
        Height = 12
        Caption = '备注'
      end
      object Label11: TLabel [9]
        Left = 464
        Top = 80
        Width = 126
        Height = 12
        Caption = '<-输入6位数字(hhddss)'
      end
      object Label12: TLabel [10]
        Left = 464
        Top = 120
        Width = 126
        Height = 12
        Caption = '<-输入6位数字(hhddss)'
      end
      object Label19: TLabel [11]
        Left = 54
        Top = 80
        Width = 48
        Height = 12
        Caption = '设备名称'
      end
      object Label20: TLabel [12]
        Left = 54
        Top = 120
        Width = 48
        Height = 12
        Caption = '商户名称'
      end
      object lbl1: TLabel [13]
        Left = 54
        Top = 160
        Width = 48
        Height = 12
        Caption = '收费科目'
      end
      object lbl2: TLabel [14]
        Left = 206
        Top = 160
        Width = 264
        Height = 12
        Caption = '收费科目值为0－99之间的整数值，0为无收费科目'
      end
      inherited UIPanel2: TUIPanel
        Top = 522
        Width = 878
        TabOrder = 3
        inherited btnOK: TBitBtn
          Left = 698
        end
        inherited btnCancel: TBitBtn
          Left = 794
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          Visible = False
        end
        object btnAdDlChOK3: TButton
          Left = 416
          Top = 8
          Width = 81
          Height = 25
          Caption = '&O 确认'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
          OnClick = btnAdDlChOK3Click
        end
        object btnAdDlChCcl3: TButton
          Left = 520
          Top = 8
          Width = 81
          Height = 25
          Caption = '取消'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
          OnClick = btnAdDlChCcl3Click
        end
      end
      object WVDigitalEdit2: TWVDigitalEdit
        Left = 151
        Top = 76
        Width = 98
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        ParentColor = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        Visible = False
        WorkView = WorkView
        FieldName = '设备标识'
        SynchronizeByValue = True
      end
      object WVEdit6: TWVEdit
        Left = 350
        Top = 76
        Width = 100
        Height = 20
        Color = clInfoBk
        MaxLength = 6
        ReadOnly = False
        TabOrder = 1
        Text = '<使用开始时间>'
        WorkView = WorkView
        FieldName = '使用开始时间'
        SynchronizeWhenExit = True
      end
      object WVEdit7: TWVEdit
        Left = 350
        Top = 116
        Width = 100
        Height = 20
        Color = clInfoBk
        MaxLength = 6
        ReadOnly = False
        TabOrder = 2
        Text = '<使用结束时间>'
        WorkView = WorkView
        FieldName = '使用结束时间'
        SynchronizeWhenExit = True
      end
      object WVEdit1: TWVEdit
        Left = 104
        Top = 200
        Width = 353
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 4
        Text = '<备注>'
        WorkView = WorkView
        FieldName = '备注'
      end
      object WVDigitalEdit1: TWVDigitalEdit
        Left = 104
        Top = 40
        Width = 97
        Height = 25
        ParentColor = False
        TabOrder = 5
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '编号'
      end
      object WVDigitalEdit3: TWVDigitalEdit
        Left = 152
        Top = 114
        Width = 97
        Height = 25
        ParentColor = False
        TabOrder = 6
        TabStop = True
        Text = '0'
        Visible = False
        WorkView = WorkView
        FieldName = '商户标识'
      end
      object WVEdit2: TWVEdit
        Left = 348
        Top = 37
        Width = 100
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 7
        Text = '<使用开始日期>'
        WorkView = WorkView
        FieldName = '使用开始日期'
      end
      object WVEdit3: TWVEdit
        Left = 548
        Top = 37
        Width = 100
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 8
        Text = '<使用结束日期>'
        WorkView = WorkView
        FieldName = '使用结束日期'
      end
      object UIPanel4: TUIPanel
        Left = 360
        Top = 168
        Width = 185
        Height = 241
        Color = 15458000
        TabOrder = 9
        Visible = False
      end
      object UIPanel3: TUIPanel
        Left = 600
        Top = 160
        Width = 177
        Height = 241
        Color = 15458000
        TabOrder = 10
        Visible = False
      end
      object Edit1: TEdit
        Left = 104
        Top = 76
        Width = 97
        Height = 20
        Enabled = False
        TabOrder = 11
      end
      object Edit2: TEdit
        Left = 104
        Top = 116
        Width = 97
        Height = 20
        Enabled = False
        TabOrder = 12
      end
      object WVDigitalEdit4: TWVDigitalEdit
        Left = 104
        Top = 154
        Width = 97
        Height = 23
        ParentColor = False
        TabOrder = 13
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '收费科目'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 468
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
        Name = '查询.编号'
        Caption = '查询.编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lvol1'
      end
      item
        Name = '编号'
        Caption = '编号'
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
        Name = '设备标识'
        Caption = '设备标识'
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
        Name = '查询.设备标识'
        Caption = '查询.设备标识'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lvol0'
      end
      item
        Name = '商户标识'
        Caption = '商户标识'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'damt0'
      end
      item
        Name = '查询.商户标识'
        Caption = '查询.商户标识'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'damt0'
      end
      item
        Name = '使用开始日期'
        Caption = '使用开始日期'
        FieldType = wftUndefined
        DomainName = '日期格式'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_no'
      end
      item
        Name = '使用开始时间'
        Caption = '使用开始时间'
        FieldType = wftUndefined
        DomainName = '时间格式'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 6
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sholder_ac_no'
      end
      item
        Name = '使用结束日期'
        Caption = '使用结束日期'
        FieldType = wftUndefined
        DomainName = '日期格式'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_no2'
      end
      item
        Name = '使用结束时间'
        Caption = '使用结束时间'
        FieldType = wftUndefined
        DomainName = '时间格式'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 6
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sholder_ac_no2'
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
        DataField = 'scusttypes'
      end
      item
        Name = '查询.备注'
        Caption = '查询.备注'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'scusttypes'
      end
      item
        Name = '查询.使用开始日期'
        Caption = '查询.使用开始日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'scust_no2'
      end
      item
        Name = '查询.使用开始时间'
        Caption = '查询.使用开始时间'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 6
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sholder_ac_no'
      end
      item
        Name = '查询.使用结束日期'
        Caption = '查询.使用结束日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'scust_no2'
      end
      item
        Name = '查询.使用结束时间'
        Caption = '查询.使用结束时间'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 6
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sholder_ac_no2'
      end
      item
        Name = '收费科目'
        Caption = '收费科目'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 2
        Checker.Max = 99
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol2'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|查询.设备商户标识|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|编号|前端机标识|商户标识|使用开始日期|使用开始时间|使用结束时间' +
          '|使用结束日期|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 416
    Top = 376
  end
  inherited QueryRequest: TWVRequest
    ID = '设备商户信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '编号'
        FieldName = '编号'
      end>
    Left = 552
    Top = 336
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol0'
        WVFieldName = '设备标识'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '1317'
      end
      item
        FieldName = 'damt0'
        WVFieldName = '商户标识'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '1317'
      end>
    Left = 468
    Top = 375
  end
  inherited AddRequest: TWVRequest
    ID = '设备商户信息设置.增加'
    Bindings = <
      item
        ParamName = '使用开始日期'
        FieldName = '使用开始日期'
      end
      item
        ParamName = '使用开始时间'
        FieldName = '使用开始时间'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
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
        ParamName = '编号'
        FieldName = '编号'
      end
      item
        ParamName = '商户标识'
        FieldName = '商户标识'
      end
      item
        ParamName = '收费科目'
        FieldName = '收费科目'
      end>
    Left = 416
    Top = 336
  end
  inherited DeleteRequest: TWVRequest
    ID = '设备商户信息设置.删除'
    Bindings = <
      item
        ParamName = '使用开始日期'
        FieldName = '使用开始日期'
      end
      item
        ParamName = '使用开始时间'
        FieldName = '使用开始时间'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
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
        ParamName = '编号'
        FieldName = '编号'
      end
      item
        ParamName = '商户标识'
        FieldName = '商户标识'
      end
      item
        ParamName = '收费科目'
        FieldName = '收费科目'
      end>
    Left = 464
    Top = 336
  end
  inherited ChangeRequest: TWVRequest
    ID = '设备商户信息设置.修改'
    Bindings = <
      item
        ParamName = '使用开始日期'
        FieldName = '使用开始日期'
      end
      item
        ParamName = '使用开始时间'
        FieldName = '使用开始时间'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
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
        ParamName = '编号'
        FieldName = '编号'
      end
      item
        ParamName = '商户标识'
        FieldName = '商户标识'
      end
      item
        ParamName = '收费科目'
        FieldName = '收费科目'
      end>
    Left = 512
    Top = 336
  end
  inherited WVDataSource: TWVDataSource
    Left = 556
    Top = 375
  end
  inherited alDatasetActions: TActionList
    Left = 508
    Top = 372
  end
  object QueryRequest3: TWVRequest
    WorkView = WorkView3
    ID = '设备关键字查询3'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '设备标识'
        FieldName = '设备标识'
      end>
    Left = 712
    Top = 368
  end
  object WorkView3: TWorkView
    WorkFields = <
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
        DataField = '@Dataset'
      end
      item
        Name = '设备标识'
        Caption = '设备标识'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol0'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|设备标志|读卡密钥|'
      end>
    Left = 676
    Top = 367
  end
  object PopupMenu1: TPopupMenu
    Left = 276
    Top = 151
    object ChaDateTime1: TMenuItem
      Caption = '修改设备的日期时间'
      OnClick = ChaDateTime1Click
    end
    object DelEquAndBus1: TMenuItem
      Caption = '删除设备'
      OnClick = DelEquAndBus1Click
    end
  end
  object QueryRequest1: TWVRequest
    WorkView = WorkView1
    ID = '商户信息非主键查询2'
    Bindings = <
      item
        ParamName = '客户号'
        FieldName = '客户号'
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
        ParamName = '商户状态'
        FieldName = '商户状态'
      end
      item
        ParamName = '是否收取管理费'
        FieldName = '是否收取管理费'
      end
      item
        ParamName = '负责人员工号'
        FieldName = '负责人员工号'
      end
      item
        ParamName = '负责人姓名'
        FieldName = '负责人姓名'
      end
      item
        ParamName = '负责人性别'
        FieldName = '负责人性别'
      end
      item
        ParamName = '负责人民族'
        FieldName = '负责人民族'
      end
      item
        ParamName = '负责人身份证号'
        FieldName = '负责人身份证号'
      end
      item
        ParamName = '收取消费管理费比例'
        FieldName = '收取消费管理费比例'
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
        ParamName = '注册时间'
        FieldName = '注册时间'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end>
    Left = 160
    Top = 360
  end
  object WorkView1: TWorkView
    WorkFields = <
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
        Name = '商户标识'
        Caption = '商户标识'
        FieldType = wftUndefined
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
        Name = '客户号'
        Caption = '客户号'
        FieldType = wftUndefined
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
        Name = '父商户标识'
        Caption = '父商户标识'
        FieldType = wftUndefined
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
        Name = '是否为独立核算'
        Caption = '是否为独立核算'
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
        Name = '是否为叶节点'
        Caption = '是否为叶节点'
        FieldType = wftUndefined
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
        Name = '商户状态'
        Caption = '商户状态'
        FieldType = wftUndefined
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
        Name = '负责人员工号'
        Caption = '负责人员工号'
        FieldType = wftUndefined
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
        Name = '负责人姓名'
        Caption = '负责人姓名'
        FieldType = wftUndefined
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
        Name = '负责人性别'
        Caption = '负责人性别'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sstatus0'
      end
      item
        Name = '负责人民族'
        Caption = '负责人民族'
        FieldType = wftUndefined
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
        Name = '负责人身份证号'
        Caption = '负责人身份证号'
        FieldType = wftUndefined
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
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_auth2'
      end
      item
        Name = '联系地址'
        Caption = '联系地址'
        FieldType = wftUndefined
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
        Name = '是否收取管理费'
        Caption = '是否收取管理费'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'smarket_code'
      end
      item
        Name = '收取消费管理费比例'
        Caption = '收取消费管理费比例'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'damt0'
      end
      item
        Name = '注册时间'
        Caption = '注册时间'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sphone3'
      end
      item
        Name = '备注'
        Caption = '备注'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'ssectypes'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|商户标识|客户号|父商户标识|商户名称|商户类别|是否为叶节点|商户' +
          '状态|负责人员工号|负责人姓名|负责人性别|负责人民族代码|负责人身' +
          '份证号|联系电话|联系地址|是否收取管理费|收取消费管理费比例|商户' +
          '管理费计算方式|商户税费计算方式|注册时间|备注|'
      end>
    Left = 124
    Top = 359
  end
  object ImageList1: TImageList
    Left = 253
    Top = 47
    Bitmap = {
      494C010103000400040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000FF000000FF0000000000000000000000FF000000FF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000FFFF00000000000084840000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007BADEF00639CE700528CDE00528CDE004A84CE00427BBD00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF000000FF000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C60000848400008484000084840000000000C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C6000000000000000000000000000000
      0000A5C6EF008CB5EF006BADF7005AA5FF00529CEF004A8CD600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FF000000FF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C6C6C6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000ADC6E70084B5EF007BB5F70063ADFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF000000FF000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B5CEE7008CB5EF008CB5EF00000000005AA5FF00528CDE00000000000000
      000000000000000000000000000000000000C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C6000000FF000000FF00C6C6C600848484000000FF000000FF00C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000BDCEE7008CB5EF008CB5EF007BB5F7006BADF7004A84CE00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C6C6C6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400C6C6C600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000C6C6C6008484840000000000000000000000000000000000000000000000
      0000BDCEEF008CB5EF008CB5EF008CB5EF0073ADF70063A5EF004A8CD600427B
      BD00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400C6C6C600848484008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400C6C6C6008484840084848400000000000000000000000000000000000000
      0000B5CEEF008CB5EF008CB5EF008CB5EF007BB5EF006BADF7005294EF00528C
      DE00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C6008484840084848400000000000000000000000000000000000000
      0000BDCEEF0094BDEF008CB5EF008CB5EF008CB5EF000000000052A5FF00528C
      DE000000000000000000000000000000000084848400C6C6C600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000C6C6C6008484840000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000084
      000000FF00008484840084848400000000000000000000000000000000000000
      0000BDD6EF009CBDEF008CB5EF008CB5EF008CB5EF00000000005AA5FF00528C
      DE000000000000000000000000000000000084848400C6C6C600848484008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400C6C6C6008484840084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008484840084848400000000000000000000000000000000000000
      0000BDD6EF00A5C6EF0094BDEF008CBDEF008CB5EF008CB5EF007BADE700528C
      DE000000000000000000000000000000000084848400C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C6008484840084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C60084848400000000000000000000000000000000000000
      0000B5C6DE00BDCEE700BDD6EF00BDD6EF00BDCEEF00ADC6EF009CBDEF0094BD
      EF000000000000000000000000000000000084848400C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000084
      000000FF00008484840084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000848484008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400848484008484840084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008484840000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008484840084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C60084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000848484008484
      8400848484008484840084848400848484008484840084848400848484008484
      8400848484008484840084848400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFFFFFF0000FC3FF03FF99F0000
      0100E01FFC3F00000000E01FFE7F0000FE7FE01F00000000FE7FE01F00000000
      8003E00FFE7F00003FF1E007FE7F00000000E007800300000000E0073FF10000
      0000E007000000007FF8E007000000008000E00700000000C001F00F7FF80000
      FFFFFFFF80000000FFFFFFFFC001000000000000000000000000000000000000
      000000000000}
  end
  object WorkView5: TWorkView
    WorkFields = <
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
        Name = '编号'
        Caption = '编号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol1'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|设备商户标识|'
      end>
    Left = 124
    Top = 215
  end
  object QueryRequest5: TWVRequest
    WorkView = WorkView5
    ID = '设备商户信息主键查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '编号'
        FieldName = '编号'
      end>
    Left = 160
    Top = 216
  end
  object QueryRequest6: TWVRequest
    WorkView = WorkView
    ID = '设备商户信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '编号'
        FieldName = '编号'
      end>
    Left = 608
    Top = 334
  end
  object QueryRequest4: TWVRequest
    WorkView = WorkView4
    ID = '设备非关键字查询2'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '设备名称'
        FieldName = '设备名称'
      end
      item
        ParamName = '三九设备注册号'
        FieldName = '三九设备注册号'
      end
      item
        ParamName = '设备物理ID'
        FieldName = '设备物理ID'
      end
      item
        ParamName = '机号'
        FieldName = '机号'
      end
      item
        ParamName = '机型代码'
        FieldName = '机型代码'
      end
      item
        ParamName = '上级设备物理ID'
        FieldName = '上级设备物理ID'
      end
      item
        ParamName = '设备状态'
        FieldName = '设备状态'
      end
      item
        ParamName = '设备物理型号'
        FieldName = '设备物理型号'
      end
      item
        ParamName = '所属子系统'
        FieldName = '所属子系统'
      end
      item
        ParamName = '设备所在区域'
        FieldName = '设备所在区域'
      end
      item
        ParamName = '负责人员工号'
        FieldName = '负责人员工号'
      end>
    Left = 712
    Top = 328
  end
  object WorkView4: TWorkView
    WorkFields = <
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
        Name = '设备名称'
        Caption = '设备名称'
        FieldType = wftUndefined
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
        Name = '三九设备注册号'
        Caption = '三九设备注册号'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_pwd'
      end
      item
        Name = '设备物理ID'
        Caption = '设备物理ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_pwd2'
      end
      item
        Name = '机号'
        Caption = '机号'
        FieldType = wftUndefined
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
        Name = '机型代码'
        Caption = '机型代码'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_code'
      end
      item
        Name = '上级设备物理ID'
        Caption = '上级设备物理ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sdate1'
      end
      item
        Name = '设备状态'
        Caption = '设备状态'
        FieldType = wftUndefined
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
        Name = '设备物理型号'
        Caption = '设备物理型号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lbank_acc_type'
      end
      item
        Name = '所属子系统'
        Caption = '所属子系统'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial0'
      end
      item
        Name = '设备所在区域'
        Caption = '设备所在区域'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial1'
      end
      item
        Name = '负责人员工号'
        Caption = '负责人员工号'
        FieldType = wftUndefined
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
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|设备名称|三九设备注册号|设备物纜机号|机型代码|上级设备物纜设备' +
          '状态|设备物理型号|所属子系统|设备所在区域|负责人员工号|'
      end>
    Left = 676
    Top = 327
  end
  object WorkView2: TWorkView
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
        Name = '商户标识'
        Caption = '商户标识'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|商户标识|'
      end>
    Left = 124
    Top = 319
  end
  object QueryRequest2: TWVRequest
    WorkView = WorkView2
    ID = '商户信息主键查询2'
    Bindings = <
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '商户标识'
        FieldName = '商户标识'
      end>
    Left = 160
    Top = 320
  end
end
