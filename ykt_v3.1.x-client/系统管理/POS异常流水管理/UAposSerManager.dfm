inherited faqhposSerManager: TfaqhposSerManager
  Width = 681
  Height = 478
  Caption = 'POS异常流水管理'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 478
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 425
        Width = 677
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 272
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 502
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 418
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 104
          Width = 161
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 121
        Width = 677
        Height = 304
        ImeName = ''
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
            FieldName = 'stime0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '交易时间'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备物理编号'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lserial0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备流水号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lwithdraw_flag'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '设备编号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '交易码'
            Visible = False
          end
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
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '钱包号'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol6'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '卡交易次数'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Damt3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '卡交易前余额'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Damt4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '卡交易后余额'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '发生额'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '搭伙费'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol11'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '交易标记'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '流水状态'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '导入操作员'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '导入批次号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '导入序号'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '采集日期'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '采集时间'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Semp_no2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '审核操作员'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'Sdate3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '记账日期'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lwithdraw_flag'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '终端编号'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lserial1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '终端流水号'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Caption = '错误信息'
            Width = 100
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 103
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label1: TLabel
          Left = 18
          Top = 10
          Width = 72
          Height = 12
          Caption = '交易开始日期'
        end
        object Label3: TLabel
          Left = 418
          Top = 10
          Width = 72
          Height = 12
          Caption = '设备物理编号'
        end
        object Label4: TLabel
          Left = 430
          Top = 34
          Width = 60
          Height = 12
          Caption = '设备流水号'
        end
        object Label5: TLabel
          Left = 54
          Top = 34
          Width = 36
          Height = 12
          Caption = '商户号'
        end
        object Label6: TLabel
          Left = 462
          Top = 82
          Width = 36
          Height = 12
          Caption = '交易码'
          Visible = False
        end
        object Label7: TLabel
          Left = 266
          Top = 34
          Width = 24
          Height = 12
          Caption = '卡号'
        end
        object Label14: TLabel
          Left = 42
          Top = 58
          Width = 48
          Height = 12
          Caption = '交易标记'
        end
        object Label2: TLabel
          Left = 231
          Top = 58
          Width = 60
          Height = 12
          Caption = '导入批次号'
        end
        object Label9: TLabel
          Left = 242
          Top = 82
          Width = 48
          Height = 12
          Caption = '流水状态'
        end
        object Label8: TLabel
          Left = 218
          Top = 10
          Width = 72
          Height = 12
          Caption = '交易结束日期'
        end
        object Label12: TLabel
          Left = 42
          Top = 82
          Width = 48
          Height = 12
          Caption = '设备编号'
        end
        object edtQDate: TWVEdit
          Left = 100
          Top = 6
          Width = 103
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.交易开始日期>'
          WorkView = WorkView
          FieldName = '查询.交易开始日期'
        end
        object WVEdit3: TWVEdit
          Left = 500
          Top = 6
          Width = 103
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 2
          Text = '<查询.设备物理编号>'
          WorkView = WorkView
          FieldName = '查询.设备物理编号'
        end
        object WVEdit2: TWVEdit
          Left = 300
          Top = 54
          Width = 103
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 7
          Text = '<查询.导入批次号>'
          WorkView = WorkView
          FieldName = '查询.导入批次号'
        end
        object WVComboBox6: TWVComboBox
          Left = 300
          Top = 77
          Width = 103
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 8
          WorkView = WorkView
          FieldName = '查询.流水状态'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*3'
        end
        object WVComboBox2: TWVComboBox
          Left = 100
          Top = 53
          Width = 103
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 6
          WorkView = WorkView
          FieldName = '查询.交易标记'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*130'
        end
        object WVComboBox3: TWVComboBox
          Left = 508
          Top = 77
          Width = 103
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 9
          Visible = False
          WorkView = WorkView
          FieldName = '查询.交易码'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-8'
        end
        object edtBusiNo: TWVEdit
          Left = 100
          Top = 30
          Width = 103
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 3
          Text = '<查询.商户卡号>'
          WorkView = WorkView
          FieldName = '查询.商户卡号'
        end
        object edtSeriNo: TWVEdit
          Left = 500
          Top = 30
          Width = 103
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 5
          Text = '<查询.设备流水号>'
          WorkView = WorkView
          FieldName = '查询.设备流水号'
        end
        object edtQCardNo: TWVEdit
          Left = 300
          Top = 30
          Width = 103
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 4
          Text = '<查询.卡号>'
          WorkView = WorkView
          FieldName = '查询.卡号'
        end
        object edtQEdate: TWVEdit
          Left = 300
          Top = 6
          Width = 103
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.交易结束日期>'
          WorkView = WorkView
          FieldName = '查询.交易结束日期'
        end
        object edtDevid: TWVEdit
          Left = 100
          Top = 78
          Width = 103
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 10
          Text = '<查询.设备编号>'
          WorkView = WorkView
          FieldName = '查询.设备编号'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label15: TLabel [0]
        Left = 40
        Top = 76
        Width = 48
        Height = 12
        Caption = '交易日期'
      end
      object Label16: TLabel [1]
        Left = 40
        Top = 118
        Width = 48
        Height = 12
        Caption = '交易时间'
      end
      object Label17: TLabel [2]
        Left = 486
        Top = 76
        Width = 60
        Height = 12
        Caption = '设备流水号'
      end
      object Label18: TLabel [3]
        Left = 286
        Top = 160
        Width = 36
        Height = 12
        Caption = '商户号'
      end
      object Label19: TLabel [4]
        Left = 46
        Top = 308
        Width = 36
        Height = 12
        Caption = '交易码'
        Visible = False
      end
      object Label20: TLabel [5]
        Left = 298
        Top = 118
        Width = 24
        Height = 12
        Caption = '卡号'
      end
      object Label21: TLabel [6]
        Left = 510
        Top = 118
        Width = 36
        Height = 12
        Caption = '钱包号'
      end
      object Label22: TLabel [7]
        Left = 28
        Top = 160
        Width = 60
        Height = 12
        Caption = '卡交易次数'
      end
      object Label23: TLabel [8]
        Left = 250
        Top = 202
        Width = 72
        Height = 12
        Caption = '卡交易前余额'
      end
      object Label24: TLabel [9]
        Left = 474
        Top = 202
        Width = 72
        Height = 12
        Caption = '卡交易后余额'
      end
      object Label25: TLabel [10]
        Left = 52
        Top = 202
        Width = 36
        Height = 12
        Caption = '发生额'
      end
      object Label26: TLabel [11]
        Left = 52
        Top = 244
        Width = 36
        Height = 12
        Caption = '搭伙费'
      end
      object Label27: TLabel [12]
        Left = 498
        Top = 160
        Width = 48
        Height = 12
        Caption = '交易标记'
      end
      object Label10: TLabel [13]
        Left = 250
        Top = 76
        Width = 72
        Height = 12
        Caption = '设备物理编号'
      end
      object lbl1: TLabel [14]
        Left = 66
        Top = 36
        Width = 280
        Height = 14
        Caption = '提示：发生额 = 卡交易前金额-卡交易后金额'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label11: TLabel [15]
        Left = 274
        Top = 245
        Width = 48
        Height = 12
        Caption = '流水状态'
      end
      inherited UIPanel2: TUIPanel
        Top = 419
        Width = 677
        TabOrder = 15
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
      object edtDate: TWVEdit
        Left = 94
        Top = 72
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 0
        Text = '<交易日期>'
        WorkView = WorkView
        FieldName = '交易日期'
        SynchronizeWhenExit = True
      end
      object edtTime: TWVEdit
        Left = 94
        Top = 114
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 3
        Text = '<交易时间>'
        WorkView = WorkView
        FieldName = '交易时间'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit23: TWVDigitalEdit
        Left = 334
        Top = 198
        Width = 103
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        ParentColor = False
        TabOrder = 10
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '卡交易前余额'
        SynchronizeByValue = True
      end
      object WVDigitalEdit24: TWVDigitalEdit
        Left = 558
        Top = 198
        Width = 103
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        ParentColor = False
        TabOrder = 11
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '卡交易后余额'
        SynchronizeByValue = True
      end
      object WVDigitalEdit25: TWVDigitalEdit
        Left = 94
        Top = 198
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        ParentColor = False
        TabOrder = 9
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '发生额'
        SynchronizeByValue = True
      end
      object WVDigitalEdit26: TWVDigitalEdit
        Left = 94
        Top = 240
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        ParentColor = False
        TabOrder = 12
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '管理费'
        SynchronizeByValue = True
      end
      object edtPhyId: TWVEdit
        Left = 334
        Top = 72
        Width = 103
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<设备物理编号>'
        WorkView = WorkView
        FieldName = '设备物理编号'
        SynchronizeWhenExit = True
      end
      object WVComboBox1: TWVComboBox
        Left = 558
        Top = 156
        Width = 103
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 8
        WorkView = WorkView
        FieldName = '交易标记'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*130'
      end
      object WVComboBox4: TWVComboBox
        Left = 94
        Top = 303
        Width = 103
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 14
        Visible = False
        WorkView = WorkView
        FieldName = '交易码'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-8'
      end
      object edtCardNo: TWVEdit
        Left = 334
        Top = 114
        Width = 103
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 4
        Text = '<卡号>'
        WorkView = WorkView
        FieldName = '卡号'
        SynchronizeWhenExit = True
      end
      object edtTradeNum: TWVEdit
        Left = 94
        Top = 156
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 6
        Text = '<卡交易次数>'
        WorkView = WorkView
        FieldName = '卡交易次数'
        SynchronizeWhenExit = True
      end
      object edtPackageNo: TWVEdit
        Left = 558
        Top = 114
        Width = 103
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 5
        Text = '<钱包号>'
        WorkView = WorkView
        FieldName = '钱包号'
        SynchronizeWhenExit = True
      end
      object edtDevNo: TWVEdit
        Left = 558
        Top = 72
        Width = 103
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 2
        Text = '<设备流水号>'
        WorkView = WorkView
        FieldName = '设备流水号'
        SynchronizeWhenExit = True
      end
      object edtBusiCardNo: TWVEdit
        Left = 334
        Top = 156
        Width = 103
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 7
        Text = '<商户卡号>'
        WorkView = WorkView
        FieldName = '商户卡号'
        SynchronizeWhenExit = True
      end
      object WVComboBox5: TWVComboBox
        Left = 334
        Top = 240
        Width = 103
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 13
        WorkView = WorkView
        FieldName = '流水状态'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*3'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 556
    Top = 47
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
        Name = '查询.交易开始日期'
        Caption = '查询.交易开始日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
        Features.Strings = ()
        DataType = kdtString
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
        GetPrevChar = '*'
      end
      item
        Name = '查询.交易结束日期'
        Caption = '查询.交易结束日期'
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
      end
      item
        Name = '查询.设备物理编号'
        Caption = '查询.设备物理编号'
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
        Name = '查询.设备流水号'
        Caption = '查询.设备流水号'
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
        GetPrevChar = '*'
      end
      item
        Name = '查询.商户卡号'
        Caption = '查询.商户卡号'
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.交易标记'
        Caption = '查询.交易标记'
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
        Name = '查询.交易时间'
        Caption = '查询.交易时间'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
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
        GetPrevChar = '*'
      end
      item
        Name = '查询.流水状态'
        Caption = '查询.流水状态'
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
        Name = '查询.导入批次号'
        Caption = '查询.导入批次号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'scust_limit'
      end
      item
        Name = '查询.设备编号'
        Caption = '查询.设备编号'
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
        Name = '导入批次号'
        Caption = '导入批次号'
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
        DataField = 'scust_limit'
      end
      item
        Name = '导入序号'
        Caption = '导入序号'
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
        DataField = 'Lvol1'
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
        GroupIndex = 1
        DataField = 'sstatus1'
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
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '卡交易次数'
        Caption = '卡交易次数'
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
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol6'
      end
      item
        Name = '交易日期'
        Caption = '交易日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
        Features.Strings = ()
        DataType = kdtString
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
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sdate0'
      end
      item
        Name = '交易时间'
        Caption = '交易时间'
        FieldType = wftUndefined
        DomainName = '时间校验'
        Features.Strings = ()
        DataType = kdtString
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
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'stime0'
      end
      item
        Name = '设备物理编号'
        Caption = '设备物理编号'
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
        DataField = 'sname'
      end
      item
        Name = '设备流水号'
        Caption = '设备流水号'
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
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lserial0'
      end
      item
        Name = '商户卡号'
        Caption = '商户卡号'
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
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'Lvol2'
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
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lbank_acc_type'
      end
      item
        Name = '钱包号'
        Caption = '钱包号'
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
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol3'
      end
      item
        Name = '卡交易前余额'
        Caption = '卡交易前余额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'Damt3'
      end
      item
        Name = '卡交易后余额'
        Caption = '卡交易后余额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'Damt4'
      end
      item
        Name = '发生额'
        Caption = '发生额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'damt0'
      end
      item
        Name = '管理费'
        Caption = '管理费'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'damt1'
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
        DataField = 'Sstatus1'
      end
      item
        Name = '交易标记'
        Caption = '交易标记'
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
        GroupIndex = 1
        DataField = 'lvol11'
      end
      item
        Name = '主交易日期'
        Caption = '主交易日期'
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
        Name = '主设备物理编号'
        Caption = '主设备物理编号'
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
        Name = '主设备流水号'
        Caption = '主设备流水号'
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
        MonitorValueChangedFields = 
          '|查询.交易日期|查询.交易时间|查询.设备物理编号|查询.设备流水号|' +
          '查询.商户卡号|查询.交易码|查询.卡号|查询.钱包号|查询.卡交易次数|' +
          '查询.卡交易前余额|查询.卡交易后余额|查询.发生额|查询.管理费|查询' +
          '.交易标记|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|交易日期|交易时间|设备流水号|商户卡号|交易码|卡号|钱包号|卡交易' +
          '次数|卡交易前余额|卡交易后余额|发生额|管理费|交易标记|流水状态|' +
          '导入操作员|导入批次号|导入序号|导入日期|导入时间|审核操作员|记账' +
          '日期|终端编号|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 480
    Top = 16
  end
  inherited QueryRequest: TWVRequest
    ID = 'POS异常流水查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '交易开始日期'
        FieldName = '查询.交易开始日期'
      end
      item
        ParamName = '交易结束日期'
        FieldName = '查询.交易结束日期'
      end
      item
        ParamName = '设备物理编号'
        FieldName = '查询.设备物理编号'
      end
      item
        ParamName = '设备流水号'
        FieldName = '查询.设备流水号'
      end
      item
        ParamName = '商户卡号'
        FieldName = '查询.商户卡号'
      end
      item
        ParamName = '交易码'
        FieldName = '查询.交易码'
      end
      item
        ParamName = '卡号'
        FieldName = '查询.卡号'
      end
      item
        ParamName = '交易标记'
        FieldName = '查询.交易标记'
      end
      item
        ParamName = '导入批次号'
        FieldName = '查询.导入批次号'
      end
      item
        ParamName = '导入序号'
        FieldName = '导入序号'
      end
      item
        ParamName = '流水状态'
        FieldName = '查询.流水状态'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '设备编号'
        FieldName = '查询.设备编号'
      end>
    Left = 616
    Top = 16
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol11'
        DataPresentType = 'idobjects'
        DataPresentParam = '130'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '-8'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '3'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'semp_no2'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end>
    Left = 524
    Top = 47
  end
  inherited AddRequest: TWVRequest
    ID = 'POS异常流水管理'
    Bindings = <
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '卡交易次数'
        FieldName = '卡交易次数'
      end
      item
        ParamName = '交易日期'
        FieldName = '交易日期'
      end
      item
        ParamName = '交易时间'
        FieldName = '交易时间'
      end
      item
        ParamName = '设备物理编号'
        FieldName = '设备物理编号'
      end
      item
        ParamName = '设备流水号'
        FieldName = '设备流水号'
      end
      item
        ParamName = '商户卡号'
        FieldName = '商户卡号'
      end
      item
        ParamName = '交易码'
        FieldName = '交易码'
      end
      item
        ParamName = '钱包号'
        FieldName = '钱包号'
      end
      item
        ParamName = '卡交易前余额'
        FieldName = '卡交易前余额'
      end
      item
        ParamName = '卡交易后余额'
        FieldName = '卡交易后余额'
      end
      item
        ParamName = '发生额'
        FieldName = '发生额'
      end
      item
        ParamName = '管理费'
        FieldName = '管理费'
      end
      item
        ParamName = '交易标记'
        FieldName = '交易标记'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end>
    Left = 520
    Top = 16
  end
  inherited DeleteRequest: TWVRequest
    ID = 'POS异常流水管理'
    Bindings = <
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '卡交易次数'
        FieldName = '卡交易次数'
      end
      item
        ParamName = '导入批次号'
        FieldName = '导入批次号'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '设备流水号'
        FieldName = '设备流水号'
      end
      item
        ParamName = '商户卡号'
        FieldName = '商户卡号'
      end
      item
        ParamName = '交易码'
        FieldName = '交易码'
      end
      item
        ParamName = '钱包号'
        FieldName = '钱包号'
      end
      item
        ParamName = '卡交易前余额'
        FieldName = '卡交易前余额'
      end
      item
        ParamName = '卡交易后余额'
        FieldName = '卡交易后余额'
      end
      item
        ParamName = '发生额'
        FieldName = '发生额'
      end
      item
        ParamName = '管理费'
        FieldName = '管理费'
      end
      item
        ParamName = '交易标记'
        FieldName = '交易标记'
      end
      item
        ParamName = '主交易日期'
        FieldName = '主交易日期'
      end
      item
        ParamName = '主设备流水号'
        FieldName = '主设备流水号'
      end
      item
        ParamName = '主设备物理编号'
        FieldName = '主设备物理编号'
      end>
    Left = 552
    Top = 16
  end
  inherited ChangeRequest: TWVRequest
    ID = 'POS异常流水管理'
    Bindings = <
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '卡交易次数'
        FieldName = '卡交易次数'
      end
      item
        ParamName = '交易日期'
        FieldName = '交易日期'
      end
      item
        ParamName = '交易时间'
        FieldName = '交易时间'
      end
      item
        ParamName = '设备物理编号'
        FieldName = '设备物理编号'
      end
      item
        ParamName = '设备流水号'
        FieldName = '设备流水号'
      end
      item
        ParamName = '商户卡号'
        FieldName = '商户卡号'
      end
      item
        ParamName = '交易码'
        FieldName = '交易码'
      end
      item
        ParamName = '钱包号'
        FieldName = '钱包号'
      end
      item
        ParamName = '卡交易前余额'
        FieldName = '卡交易前余额'
      end
      item
        ParamName = '卡交易后余额'
        FieldName = '卡交易后余额'
      end
      item
        ParamName = '发生额'
        FieldName = '发生额'
      end
      item
        ParamName = '管理费'
        FieldName = '管理费'
      end
      item
        ParamName = '交易标记'
        FieldName = '交易标记'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '主交易日期'
        FieldName = '主交易日期'
      end
      item
        ParamName = '主设备流水号'
        FieldName = '主设备流水号'
      end
      item
        ParamName = '主设备物理编号'
        FieldName = '主设备物理编号'
      end
      item
        ParamName = '流水状态'
        FieldName = '流水状态'
      end>
    Left = 584
    Top = 16
  end
  inherited WVDataSource: TWVDataSource
    Left = 628
    Top = 47
  end
  inherited alDatasetActions: TActionList
    Left = 588
    Top = 44
  end
end
