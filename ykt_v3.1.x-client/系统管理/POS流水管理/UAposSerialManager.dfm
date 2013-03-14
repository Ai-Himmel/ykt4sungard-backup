inherited faqhposSerialManager: TfaqhposSerialManager
  Width = 775
  Height = 478
  Caption = 'POS流水管理'
  inherited pcPages: TRzPageControl
    Width = 775
    Height = 478
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 425
        Width = 771
        TabOrder = 3
        object Label33: TLabel [0]
          Left = 102
          Top = 9
          Width = 36
          Height = 12
          Caption = '批次号'
        end
        inherited btnAdd: TBitBtn [1]
          Left = 334
          Enabled = False
        end
        inherited btnChange: TBitBtn [2]
          Left = 421
          Enabled = False
        end
        inherited btnQuery: TBitBtn [3]
          Left = 248
        end
        inherited btnDelete: TBitBtn
          Left = 507
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 24
          Top = 24
          Width = 161
          TabOrder = 8
          Visible = False
        end
        object btnCheck: TBitBtn
          Left = 680
          Top = 3
          Width = 79
          Height = 25
          Hint = '审核Pos流水'
          Anchors = [akTop, akRight]
          Caption = '审核(&C)'
          Enabled = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
          TabOrder = 6
          OnClick = btnCheckClick
          Glyph.Data = {
            36030000424D3603000000000000360000002800000010000000100000000100
            18000000000000030000120B0000120B00000000000000000000FFFFFFFFFFFF
            FFFFFFCBD9CF509050408040306830305030203820202820B7C6B7FFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF70A08090E8B080E8A080E0A040
            905050B070509060304030B05040A04030A03020872C1DD3CDCBFFFFFFFFFFFF
            FFFFFF80B080C0E8D090F0B080B080C0D8C040905050A870406040FF9890C058
            50F05840E05030902810FFFFFFFFFFFFFFFFFFCBD5CF80B89070B070F0F0F0FF
            F8FF70A070407840D08870E09080F0B8B0C05850E05840A03820DBECF37AADBD
            598FA66080904068705050505050506060603B774AA66859C06860F0F8F0FFF8
            FFC05850B04830F0F0F06297B250B0D080D8F080B8C0000000B0B0B0B0B8B090
            98905058506F6F6F606060505850606060B04830CFBDB7FFFFFF5090B050D8FF
            90E8FF302830201820E0E0E0D0D0D0B0B0B0909890605860D0D0D0B0B0B09098
            90505850878787FFFFFF5090B050D0FF90E8F0404840403840C0C0C0E0E0E0D0
            D0D0B0B0B0706870E0E0E0D0D0D0B0B0B0909890605860FFFFFF5098B050D0FF
            90E8F0607070505850505050606060504850D0D0D0707070C0C0C0E0E0E0D0D0
            D0B0B0B0706870FFFFFF6098B050D0FF90E8F080B8C0606060807880A098A080
            8880404840404840505050606060504850D0D0D0777777FFFFFF6098B050D0FF
            90E0F0A0E0F060A0B0507880808080707880405060605860807880A098A08088
            80404840A4A4A4FFFFFF60A0C050D0FF90E0F0A0E8F070D8F020B8F000A8F000
            A0E0306890B7BAB77C847C808080778077ABAFABEFF0EFFFFFFF60A0C040D0F0
            90E0F0A0E8F070D8F020B8F000A8F000A0E0307090FFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFF904820FFFFFF70A8C050D8FFA0F0FFB0F0FFA0F0FF90E8FF70D8F040
            C0F0408090FFFFFFF6E3D8904820FFFFFFF9ECE5D06830FFFFFF80B0C0A0E0F0
            C0F8FFC0F8FFC0F8FFC0F8FFC0F8FFA0E0F06090A0FFFFFFA048209048209048
            20D06830F9ECE5FFFFFFD5EAED97C4D970A8C070A0B070A0B07098B070A0B081
            B3BAC0DCE3FFFFFFF6E3D8904820FFFFFFFFFFFFFFFFFFFFFFFF}
        end
        object btnPatchDel: TBitBtn
          Left = 594
          Top = 3
          Width = 79
          Height = 25
          Hint = '删除当前选中的条目'
          Anchors = [akTop, akRight]
          Caption = '批量删除'
          Enabled = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
          OnClick = btnPatchDelClick
        end
        object edtDelPatchNo: TWVEdit
          Left = 143
          Top = 5
          Width = 98
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 7
          Text = '<批次号>'
          WorkView = WorkView1
          FieldName = '批次号'
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 771
      end
      inherited Grid: TRzDBGrid
        Top = 97
        Width = 771
        Height = 328
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
            Title.Caption = '审核状态'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '导入操作员'
            Width = 71
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '批次号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '导入序号'
            Width = 60
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
            FieldName = 'Semp_no2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '审核操作员'
            Width = 70
            Visible = True
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
        Width = 771
        Height = 79
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label1: TLabel
          Left = 42
          Top = 10
          Width = 48
          Height = 12
          Caption = '交易日期'
        end
        object Label3: TLabel
          Left = 218
          Top = 10
          Width = 72
          Height = 12
          Caption = '设备物理编号'
        end
        object Label4: TLabel
          Left = 430
          Top = 10
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
          Left = 254
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
          Left = 253
          Top = 58
          Width = 36
          Height = 12
          Caption = '批次号'
        end
        object Label9: TLabel
          Left = 442
          Top = 34
          Width = 48
          Height = 12
          Caption = '审核状态'
        end
        object edtQDate: TWVEdit
          Left = 100
          Top = 6
          Width = 103
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.交易日期>'
          WorkView = WorkView
          FieldName = '查询.交易日期'
        end
        object WVEdit3: TWVEdit
          Left = 300
          Top = 6
          Width = 103
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
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
          Left = 500
          Top = 29
          Width = 103
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '流水状态'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*135'
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
          Left = 300
          Top = 77
          Width = 103
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 8
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
          TabOrder = 4
          Text = '<查询.商户卡号>'
          WorkView = WorkView
          FieldName = '查询.商户卡号'
        end
        object edtSeriNo: TWVEdit
          Left = 500
          Top = 6
          Width = 103
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 2
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
          TabOrder = 5
          Text = '<查询.卡号>'
          WorkView = WorkView
          FieldName = '查询.卡号'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label15: TLabel [0]
        Left = 42
        Top = 124
        Width = 48
        Height = 12
        Caption = '交易日期'
      end
      object Label16: TLabel [1]
        Left = 276
        Top = 124
        Width = 48
        Height = 12
        Caption = '交易时间'
      end
      object Label17: TLabel [2]
        Left = 30
        Top = 164
        Width = 60
        Height = 12
        Caption = '设备流水号'
      end
      object Label18: TLabel [3]
        Left = 288
        Top = 164
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
        Left = 66
        Top = 84
        Width = 24
        Height = 12
        Caption = '卡号'
      end
      object Label21: TLabel [6]
        Left = 510
        Top = 84
        Width = 36
        Height = 12
        Caption = '钱包号'
      end
      object Label22: TLabel [7]
        Left = 264
        Top = 84
        Width = 60
        Height = 12
        Caption = '卡交易次数'
      end
      object Label23: TLabel [8]
        Left = 252
        Top = 204
        Width = 72
        Height = 12
        Caption = '卡交易前余额'
      end
      object Label24: TLabel [9]
        Left = 474
        Top = 204
        Width = 72
        Height = 12
        Caption = '卡交易后余额'
      end
      object Label25: TLabel [10]
        Left = 54
        Top = 204
        Width = 36
        Height = 12
        Caption = '发生额'
      end
      object Label26: TLabel [11]
        Left = 56
        Top = 244
        Width = 36
        Height = 12
        Caption = '搭伙费'
      end
      object Label27: TLabel [12]
        Left = 498
        Top = 164
        Width = 48
        Height = 12
        Caption = '交易标记'
      end
      object Label10: TLabel [13]
        Left = 474
        Top = 124
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
      inherited UIPanel2: TUIPanel
        Top = 419
        Width = 771
        TabOrder = 14
        inherited btnOK: TBitBtn
          Left = 599
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 687
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object edtDate: TWVEdit
        Left = 94
        Top = 120
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 3
        Text = '<交易日期>'
        WorkView = WorkView
        FieldName = '交易日期'
        SynchronizeWhenExit = True
      end
      object edtTime: TWVEdit
        Left = 334
        Top = 120
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 4
        Text = '<交易时间>'
        WorkView = WorkView
        FieldName = '交易时间'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit23: TWVDigitalEdit
        Left = 334
        Top = 200
        Width = 100
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
        FieldName = '卡交易前余额'
        SynchronizeByValue = True
      end
      object WVDigitalEdit24: TWVDigitalEdit
        Left = 558
        Top = 199
        Width = 103
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
        FieldName = '卡交易后余额'
        SynchronizeByValue = True
      end
      object WVDigitalEdit25: TWVDigitalEdit
        Left = 94
        Top = 200
        Width = 100
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
      object WVEdit4: TWVEdit
        Left = 558
        Top = 120
        Width = 103
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 5
        Text = '<设备物理编号>'
        WorkView = WorkView
        FieldName = '设备物理编号'
        SynchronizeWhenExit = True
      end
      object WVComboBox1: TWVComboBox
        Left = 558
        Top = 158
        Width = 103
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 0
        TabOrder = 6
        Text = '<交易标记>'
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
        ItemHeight = 0
        TabOrder = 13
        Text = '<交易码>'
        Visible = False
        WorkView = WorkView
        FieldName = '交易码'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-8'
      end
      object edtCardNo: TWVEdit
        Left = 94
        Top = 80
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 0
        Text = '<卡号>'
        WorkView = WorkView
        FieldName = '卡号'
        SynchronizeWhenExit = True
      end
      object edtTradeNum: TWVEdit
        Left = 334
        Top = 80
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 1
        Text = '<卡交易次数>'
        WorkView = WorkView
        FieldName = '卡交易次数'
        SynchronizeWhenExit = True
      end
      object edtPackageNo: TWVEdit
        Left = 558
        Top = 80
        Width = 103
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 2
        Text = '<钱包号>'
        WorkView = WorkView
        FieldName = '钱包号'
        SynchronizeWhenExit = True
      end
      object edtDevNo: TWVEdit
        Left = 94
        Top = 160
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 7
        Text = '<设备流水号>'
        WorkView = WorkView
        FieldName = '设备流水号'
        SynchronizeWhenExit = True
      end
      object edtBusiCardNo: TWVEdit
        Left = 334
        Top = 160
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 8
        Text = '<商户卡号>'
        WorkView = WorkView
        FieldName = '商户卡号'
        SynchronizeWhenExit = True
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
        Name = '查询.交易日期'
        Caption = '查询.交易日期'
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
    ID = 'POS流水查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '交易日期'
        FieldName = '查询.交易日期'
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
        FieldName = '流水状态'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
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
        DataPresentParam = '135'
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
    ID = 'POS流水管理'
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
    ID = 'POS流水管理'
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
      end>
    Left = 552
    Top = 16
  end
  inherited ChangeRequest: TWVRequest
    ID = 'POS流水管理'
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
  object WVCheck: TWorkView
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
        DataField = '@Return'
      end
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
        DataField = 'vsmess'
      end
      item
        Name = '批次号'
        Caption = '批次号'
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
        Name = '卡号'
        Caption = '卡号'
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
        Name = '钱包号'
        Caption = '钱包号'
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
        Name = '交易次数'
        Caption = '交易次数'
        FieldType = wftUndefined
        DataType = kdtInteger
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
          '|查询.交易日期|查询.交易时间|查询.设备物理编号|查询.设备流水号|' +
          '查询.商户卡号|查询.交易码|查询.卡号|查询.钱包号|查询.卡交易次数|' +
          '查询.卡交易前余额|查询.卡交易后余额|查询.发生额|查询.管理费|查询' +
          '.交易标记|'
      end
      item
        MonitorValueChangedFields = 
          '|交易日期|交易时间|设备流水号|商户卡号|交易码|卡号|钱包号|卡交易' +
          '次数|卡交易前余额|卡交易后余额|发生额|管理费|交易标记|流水状态|' +
          '导入操作员|导入批次号|导入序号|导入日期|导入时间|审核操作员|记账' +
          '日期|终端编号|'
      end>
    Left = 480
    Top = 112
  end
  object WVRCheck: TWVRequest
    WorkView = WVCheck
    ID = 'Pos流水审核1'
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
        ParamName = '批次号'
        FieldName = '批次号'
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '钱包号'
        FieldName = '钱包号'
      end
      item
        ParamName = '交易次数'
        FieldName = '交易次数'
      end>
    AfterExec = CheckReturnData
    Left = 520
    Top = 112
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
    Left = 488
    Top = 152
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = 'pos流水批量删除'
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
      end>
    AfterExec = CheckReturnData
    Left = 520
    Top = 152
  end
end
