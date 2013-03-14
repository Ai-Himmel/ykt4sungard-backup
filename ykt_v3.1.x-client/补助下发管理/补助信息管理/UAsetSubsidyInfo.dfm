inherited faqhsetSubsidyInfo: TfaqhsetSubsidyInfo
  Width = 762
  Height = 484
  Caption = '补助信息管理'
  inherited pcPages: TRzPageControl
    Width = 762
    Height = 484
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 431
        Width = 758
        TabOrder = 3
        object Label33: TLabel [0]
          Left = 102
          Top = 9
          Width = 36
          Height = 12
          Caption = '批次号'
        end
        object Label8: TLabel [1]
          Left = 250
          Top = 10
          Width = 24
          Height = 12
          Caption = '状态'
        end
        inherited btnAdd: TBitBtn [2]
          Left = 128
          Top = 1000
          Enabled = False
          TabOrder = 8
          Visible = False
        end
        inherited btnChange: TBitBtn [3]
          Left = 504
          Enabled = False
          TabOrder = 2
        end
        inherited btnQuery: TBitBtn [4]
          Left = 419
        end
        inherited btnDelete: TBitBtn
          Left = 589
          Enabled = False
          TabOrder = 3
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 8
          Width = 57
          TabOrder = 7
          Visible = False
        end
        object btnPatchDel: TBitBtn
          Left = 673
          Top = 3
          Width = 79
          Height = 25
          Anchors = [akTop, akRight]
          Caption = '批量删除'
          Enabled = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
          OnClick = btnPatchDelClick
        end
        object edtDelPatchNo: TWVEdit
          Left = 143
          Top = 5
          Width = 98
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 5
          Text = '<批次号>'
          WorkView = WorkView1
          FieldName = '批次号'
        end
        object WVComboBox1: TWVComboBox
          Left = 285
          Top = 5
          Width = 100
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 6
          WorkView = WorkView1
          FieldName = '状态'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*76'
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 758
      end
      inherited Grid: TRzDBGrid
        Top = 122
        Width = 758
        Height = 309
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '导入批次号'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '顺序号'
            Width = 40
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '客户号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '学/工号'
            Width = 80
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
            FieldName = 'lvol10'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '补助批次号'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '发生额'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '记录状态'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lsafe_level2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '审核状态'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '错误信息'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '导入日期'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '导入时间'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '下发日期'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '下发时间'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '领取日期'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '领取时间'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '摘要'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol11'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '卡号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '经办人姓名'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '经办人身份证号'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '支付方式'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '凭证号码'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '导入操作员'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smain_flag'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '补助类型'
            Visible = False
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 758
        Height = 104
        Align = alTop
        BevelOuter = bvNone
        ParentColor = True
        TabOrder = 1
        object Label2: TLabel
          Left = 30
          Top = 10
          Width = 60
          Height = 12
          Caption = '导入批次号'
        end
        object Label3: TLabel
          Left = 466
          Top = 34
          Width = 24
          Height = 12
          Caption = '状态'
        end
        object Label4: TLabel
          Left = 448
          Top = 10
          Width = 42
          Height = 12
          Caption = '学/工号'
        end
        object Label5: TLabel
          Left = 254
          Top = 10
          Width = 36
          Height = 12
          Caption = '客户号'
        end
        object Label6: TLabel
          Left = 230
          Top = 34
          Width = 60
          Height = 12
          Caption = '补助批次号'
        end
        object Label7: TLabel
          Left = 66
          Top = 34
          Width = 24
          Height = 12
          Caption = '卡号'
        end
        object Label13: TLabel
          Left = 18
          Top = 58
          Width = 72
          Height = 12
          Caption = '下发开始日期'
        end
        object Label14: TLabel
          Left = 218
          Top = 58
          Width = 72
          Height = 12
          Caption = '下发结束日期'
        end
        object lbl1: TLabel
          Left = 42
          Top = 80
          Width = 48
          Height = 12
          Caption = '所属部门'
        end
        object Label16: TLabel
          Left = 442
          Top = 58
          Width = 48
          Height = 12
          Caption = '审核状态'
        end
        object WVEdit2: TWVEdit
          Left = 100
          Top = 5
          Width = 100
          Height = 20
          Color = clBtnHighlight
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.导入批次号>'
          WorkView = WorkView
          FieldName = '查询.导入批次号'
        end
        object WVEdit4: TWVEdit
          Left = 500
          Top = 6
          Width = 100
          Height = 20
          Color = clBtnHighlight
          ReadOnly = False
          TabOrder = 2
          Text = '<查询.学工号>'
          WorkView = WorkView
          FieldName = '查询.学工号'
        end
        object cbbType: TWVComboBox
          Left = 501
          Top = 29
          Width = 100
          Height = 20
          Style = csDropDownList
          Color = clBtnHighlight
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '查询.状态'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*76'
        end
        object edtQCustNo: TWVEdit
          Left = 300
          Top = 6
          Width = 100
          Height = 20
          Color = clBtnHighlight
          MaxLength = 9
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.客户号>'
          WorkView = WorkView
          FieldName = '查询.客户号'
        end
        object edtQPatchNo: TWVEdit
          Left = 300
          Top = 30
          Width = 100
          Height = 20
          Color = clBtnHighlight
          MaxLength = 9
          ReadOnly = False
          TabOrder = 5
          Text = '<查询.补助批次号>'
          WorkView = WorkView
          FieldName = '查询.补助批次号'
        end
        object edtQCardNo: TWVEdit
          Left = 100
          Top = 29
          Width = 100
          Height = 20
          Color = clBtnHighlight
          MaxLength = 9
          ReadOnly = False
          TabOrder = 3
          Text = '<查询.卡号>'
          WorkView = WorkView
          FieldName = '查询.卡号'
        end
        object edtBDate: TWVEdit
          Left = 100
          Top = 53
          Width = 100
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 6
          Text = '<查询.开始日期>'
          WorkView = WorkView
          FieldName = '查询.开始日期'
        end
        object edtEDate: TWVEdit
          Left = 300
          Top = 53
          Width = 100
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 7
          Text = '<查询.结束日期>'
          WorkView = WorkView
          FieldName = '查询.结束日期'
        end
        object cbbDept: TWVComboBox
          Left = 100
          Top = 77
          Width = 301
          Height = 20
          Style = csDropDownList
          Color = clWhite
          DropDownCount = 20
          ItemHeight = 12
          TabOrder = 9
          WorkView = WorkView
          FieldName = '部门'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-22'
        end
        object WVComboBox2: TWVComboBox
          Left = 501
          Top = 53
          Width = 100
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 8
          WorkView = WorkView
          FieldName = '审核状态'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*160'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label9: TLabel [0]
        Left = 54
        Top = 44
        Width = 36
        Height = 12
        Caption = '批次号'
      end
      object Label10: TLabel [1]
        Left = 54
        Top = 84
        Width = 36
        Height = 12
        Caption = '顺序号'
      end
      object Label11: TLabel [2]
        Left = 54
        Top = 308
        Width = 36
        Height = 12
        Caption = '学工号'
        Visible = False
      end
      object Label12: TLabel [3]
        Left = 54
        Top = 124
        Width = 36
        Height = 12
        Caption = '客户号'
      end
      object Label15: TLabel [4]
        Left = 66
        Top = 164
        Width = 24
        Height = 12
        Caption = '卡号'
      end
      object Label21: TLabel [5]
        Left = 54
        Top = 204
        Width = 36
        Height = 12
        Caption = '发生额'
      end
      object Label1: TLabel [6]
        Left = 46
        Top = 284
        Width = 48
        Height = 12
        Caption = '记录状态'
        Visible = False
      end
      inherited UIPanel2: TUIPanel
        Top = 425
        Width = 758
        TabOrder = 7
        inherited btnOK: TBitBtn
          Left = 586
        end
        inherited btnCancel: TBitBtn
          Left = 674
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtPatchNo: TWVEdit
        Left = 102
        Top = 40
        Width = 100
        Height = 20
        Color = clBtnHighlight
        ReadOnly = False
        TabOrder = 0
        Text = '<批次号>'
        WorkView = WorkView
        FieldName = '批次号'
        SynchronizeWhenExit = True
      end
      object edtNo: TWVDigitalEdit
        Left = 102
        Top = 80
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        Precision = 0
        MaxIntLen = 10
        Color = clBtnHighlight
        ParentColor = False
        TabOrder = 1
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '顺序号'
        SynchronizeByValue = True
      end
      object WVEdit11: TWVEdit
        Left = 102
        Top = 304
        Width = 100
        Height = 20
        Color = clBtnHighlight
        ReadOnly = False
        TabOrder = 6
        Text = '<学工号>'
        Visible = False
        WorkView = WorkView
        FieldName = '学工号'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit12: TWVDigitalEdit
        Left = 102
        Top = 120
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        Precision = 0
        MaxIntLen = 10
        Color = clBtnHighlight
        ParentColor = False
        TabOrder = 2
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '客户号'
        SynchronizeByValue = True
      end
      object WVDigitalEdit15: TWVDigitalEdit
        Left = 102
        Top = 160
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        Precision = 0
        MaxIntLen = 10
        Color = clBtnHighlight
        ParentColor = False
        TabOrder = 3
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '卡号'
        SynchronizeByValue = True
      end
      object WVDigitalEdit21: TWVDigitalEdit
        Left = 102
        Top = 200
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        Color = clBtnHighlight
        ParentColor = False
        TabOrder = 4
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '发生额'
        SynchronizeByValue = True
      end
      object WVEdit6: TWVEdit
        Left = 102
        Top = 280
        Width = 100
        Height = 20
        Color = clBtnHighlight
        ReadOnly = False
        TabOrder = 5
        Text = '<记录状态>'
        Visible = False
        WorkView = WorkView
        FieldName = '记录状态'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 492
    Top = 255
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
      end
      item
        Name = '返回信息'
        Caption = '返回信息'
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
        Name = '查询.开始日期'
        Caption = '查询.开始日期'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Max = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '查询.结束日期'
        Caption = '查询.结束日期'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Max = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '查询.导入批次号'
        Caption = '查询.导入批次号'
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
      end
      item
        Name = '查询.状态'
        Caption = '查询.状态'
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
      end
      item
        Name = '查询.学工号'
        Caption = '查询.学工号'
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
      end
      item
        Name = '查询.客户号'
        Caption = '查询.客户号'
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
        Name = '查询.补助批次号'
        Caption = '查询.补助批次号'
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
        Name = '查询.卡号'
        Caption = '查询.卡号'
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
        Name = '审核状态'
        Caption = '审核状态'
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
        Name = '批次号'
        Caption = '批次号'
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
        DataField = 'scust_limit'
      end
      item
        Name = '顺序号'
        Caption = '顺序号'
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
        DataField = 'lvol1'
      end
      item
        Name = '记录状态'
        Caption = '记录状态'
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
      end
      item
        Name = '学工号'
        Caption = '学工号'
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
        DataField = 'scust_auth'
      end
      item
        Name = '客户号'
        Caption = '客户号'
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
        DataField = 'lvol0'
      end
      item
        Name = '卡号'
        Caption = '卡号'
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
        DataField = 'lvol11'
      end
      item
        Name = '发生额'
        Caption = '发生额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'damt0'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.交易类型|查询.导入批次号|查询.状态|查询.学工号|查询.客户号' +
          '|查询.补助批次号|查询.卡号|查询.经办人|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|批次号|顺序号|学工号|客户号|补助批次号|补助类型|卡号|摘要|经办' +
          '人姓名|经办人身份证号|支付方式|凭证号码|发生额|导入日期|导入时间' +
          '|下发日期|下发时间|领取日期|领取时间|记录状态|错误信息|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    InvalidColor = clBtnHighlight
    Left = 408
    Top = 224
  end
  inherited QueryRequest: TWVRequest
    ID = '补助信息查询'
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
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '导入批次号'
        FieldName = '查询.导入批次号'
      end
      item
        ParamName = '状态'
        FieldName = '查询.状态'
      end
      item
        ParamName = '学工号'
        FieldName = '查询.学工号'
      end
      item
        ParamName = '客户号'
        FieldName = '查询.客户号'
      end
      item
        ParamName = '补助批次号'
        FieldName = '查询.补助批次号'
      end
      item
        ParamName = '卡号'
        FieldName = '查询.卡号'
      end
      item
        ParamName = '开始日期'
        FieldName = '查询.开始日期'
      end
      item
        ParamName = '结束日期'
        FieldName = '查询.结束日期'
      end
      item
        ParamName = '部门'
        FieldName = '部门'
      end
      item
        ParamName = '审核状态'
        FieldName = '审核状态'
      end>
    Left = 568
    Top = 224
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '76'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'idobjects'
        DataPresentParam = '63'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'lsafe_level2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '160'
      end>
    Left = 452
    Top = 255
  end
  inherited AddRequest: TWVRequest
    ID = '补助信息管理'
    Bindings = <
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end
      item
        ParamName = '顺序号'
        FieldName = '顺序号'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '补助批次号'
        FieldName = '补助批次号'
      end
      item
        ParamName = '补助类型'
        FieldName = '补助类型'
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '摘要'
        FieldName = '摘要'
      end
      item
        ParamName = '经办人姓名'
        FieldName = '经办人姓名'
      end
      item
        ParamName = '经办人身份证号'
        FieldName = '经办人身份证号'
      end
      item
        ParamName = '支付方式'
        FieldName = '支付方式'
      end
      item
        ParamName = '凭证号码'
        FieldName = '凭证号码'
      end
      item
        ParamName = '发生额'
        FieldName = '发生额'
      end
      item
        ParamName = '导入日期'
        FieldName = '导入日期'
      end
      item
        ParamName = '导入时间'
        FieldName = '导入时间'
      end
      item
        ParamName = '下发日期'
        FieldName = '下发日期'
      end
      item
        ParamName = '下发时间'
        FieldName = '下发时间'
      end
      item
        ParamName = '领取日期'
        FieldName = '领取日期'
      end
      item
        ParamName = '领取时间'
        FieldName = '领取时间'
      end
      item
        ParamName = '记录状态'
        FieldName = '记录状态'
      end
      item
        ParamName = '错误信息'
        FieldName = '错误信息'
      end
      item
        ParamName = '导入操作员'
        FieldName = '导入操作员.增加'
      end>
    Left = 448
    Top = 224
  end
  inherited DeleteRequest: TWVRequest
    ID = '补助信息管理'
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
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end
      item
        ParamName = '顺序号'
        FieldName = '顺序号'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '发生额'
        FieldName = '发生额'
      end
      item
        ParamName = '记录状态'
        FieldName = '记录状态'
      end>
    Left = 488
    Top = 224
  end
  inherited ChangeRequest: TWVRequest
    ID = '补助信息管理'
    Bindings = <
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end
      item
        ParamName = '顺序号'
        FieldName = '顺序号'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '发生额'
        FieldName = '发生额'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '记录状态'
        FieldName = '记录状态'
      end>
    Left = 528
    Top = 224
  end
  inherited WVDataSource: TWVDataSource
    Left = 580
    Top = 255
  end
  inherited alDatasetActions: TActionList
    Left = 532
    Top = 260
  end
  object WorkView1: TWorkView
    WorkFields = <
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
        GroupIndex = 1
      end
      item
        Name = '批次号'
        Caption = '批次号'
        FieldType = wftUndefined
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
        DataField = 'scust_limit'
      end
      item
        Name = '操作标志'
        Caption = '操作标志'
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
        Name = '批量标志'
        Caption = '批量标志'
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
        Name = '状态'
        Caption = '状态'
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
          '|查询.操作标志|查询.导入批次号|查询.导入顺序号|查询.记录号|查询.' +
          '设备编号|查询.设备物理编号|查询.设备名称|查询.商户编号|查询.商户' +
          '名称|查询.开始时间|查询.结束时间|查询.启用日期|查询.停用日期|查' +
          '询.备注|'
      end
      item
        MonitorValueChangedFields = 
          '|导入批次号|导入顺序号|记录号|设备编号|设备物理编号|设备名称|商' +
          '户编号|商户名称|开始时间|结束时间|启用日期|停用日期|'
      end>
    Left = 408
    Top = 304
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '补助批量删除'
    Bindings = <
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '批量标志'
        FieldName = '批量标志'
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
      end
      item
        ParamName = '状态'
        FieldName = '状态'
      end>
    AfterExec = CheckReturnData
    Left = 440
    Top = 304
  end
end
