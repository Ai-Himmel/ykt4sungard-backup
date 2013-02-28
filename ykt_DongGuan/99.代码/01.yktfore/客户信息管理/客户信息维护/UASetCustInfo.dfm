inherited faqhSetCustInfo: TfaqhSetCustInfo
  Width = 840
  Height = 542
  Caption = '客户信息维护'
  inherited pcPages: TRzPageControl
    Width = 840
    Height = 542
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 489
        Width = 836
        TabOrder = 1
        inherited btnAdd: TBitBtn [0]
          Left = 570
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 658
          Enabled = False
          TabOrder = 4
        end
        inherited btnQuery: TBitBtn [2]
          Left = 481
        end
        inherited btnDelete: TBitBtn
          Left = 747
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 22
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 112
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 836
        TabOrder = 3
      end
      inherited Grid: TRzDBGrid
        Top = 105
        Width = 836
        Height = 384
        TabOrder = 2
        Columns = <
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
            FieldName = 'scard0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '卡号'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sroom_no2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '发卡部门'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '有效期限(月)'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '申请日期'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '申请状态'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '发卡类别'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '预交款'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '姓名'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sroom_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '证件类型'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spager'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '证件号码'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '出生日期'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '身高(cm)'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_type'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '性别'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '电话'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '手机'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '电子信箱'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '单位名称'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sorder0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '婚姻状态'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sorder1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '文化程度'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sorder2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '政治面貌'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '经济来源'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snation_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '国籍'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '民族'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_addr'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '籍贯'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '户口所在地类型'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '户口所在地'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '居住是由'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '居住地址'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '居住日期'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '首次到达本市日期'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '更新时间'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smarket_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '是否删除'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstock_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '删除日期'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '集团服务号'
            Width = 90
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 836
        Height = 87
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label4: TLabel
          Left = 42
          Top = 18
          Width = 48
          Height = 12
          Caption = '发卡部门'
        end
        object Label7: TLabel
          Left = 42
          Top = 66
          Width = 48
          Height = 12
          Caption = '申请状态'
        end
        object Label9: TLabel
          Left = 234
          Top = 18
          Width = 24
          Height = 12
          Caption = '姓名'
        end
        object Label10: TLabel
          Left = 402
          Top = 18
          Width = 48
          Height = 12
          Caption = '证件类型'
        end
        object Label11: TLabel
          Left = 602
          Top = 18
          Width = 48
          Height = 12
          Caption = '证件号码'
        end
        object Label12: TLabel
          Left = 42
          Top = 42
          Width = 48
          Height = 12
          Caption = '出生日期'
        end
        object Label14: TLabel
          Left = 234
          Top = 42
          Width = 24
          Height = 12
          Caption = '性别'
        end
        object Label15: TLabel
          Left = 426
          Top = 42
          Width = 24
          Height = 12
          Caption = '电话'
        end
        object Label16: TLabel
          Left = 626
          Top = 42
          Width = 24
          Height = 12
          Caption = '手机'
        end
        object Label17: TLabel
          Left = 210
          Top = 66
          Width = 48
          Height = 12
          Caption = '电子信箱'
        end
        object WVEdit9: TWVEdit
          Left = 268
          Top = 14
          Width = 120
          Height = 20
          Color = clInfoBk
          MaxLength = 20
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.姓名>'
          WorkView = WorkView
          FieldName = '查询.姓名'
        end
        object WVEdit11: TWVEdit
          Left = 660
          Top = 14
          Width = 132
          Height = 20
          Color = clInfoBk
          MaxLength = 20
          ReadOnly = False
          TabOrder = 3
          Text = '<查询.证件号码>'
          WorkView = WorkView
          FieldName = '查询.证件号码'
        end
        object edtBirthdayQ: TWVEdit
          Left = 100
          Top = 38
          Width = 105
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 4
          Text = '<查询.出生日期>'
          WorkView = WorkView
          FieldName = '查询.出生日期'
        end
        object WVEdit15: TWVEdit
          Left = 460
          Top = 38
          Width = 120
          Height = 20
          Color = clInfoBk
          MaxLength = 20
          ReadOnly = False
          TabOrder = 6
          Text = '<查询.电话>'
          WorkView = WorkView
          FieldName = '查询.电话'
        end
        object WVEdit16: TWVEdit
          Left = 660
          Top = 38
          Width = 132
          Height = 20
          Color = clInfoBk
          MaxLength = 20
          ReadOnly = False
          TabOrder = 7
          Text = '<查询.手机>'
          WorkView = WorkView
          FieldName = '查询.手机'
        end
        object WVEdit17: TWVEdit
          Left = 268
          Top = 62
          Width = 120
          Height = 20
          Color = clInfoBk
          MaxLength = 40
          ReadOnly = False
          TabOrder = 9
          Text = '<查询.电子信箱>'
          WorkView = WorkView
          FieldName = '查询.电子信箱'
        end
        object cbbIDTypeQ: TWVComboBox
          Left = 460
          Top = 14
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '查询.证件类型'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*201'
        end
        object cbbDept: TWVComboBox
          Left = 100
          Top = 14
          Width = 105
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          DropDownCount = 20
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '查询.发卡部门'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*210'
        end
        object cbb1: TWVComboBox
          Left = 100
          Top = 62
          Width = 105
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 8
          WorkView = WorkView
          FieldName = '查询.申请状态'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*200'
        end
        object WVComboBox1: TWVComboBox
          Left = 268
          Top = 38
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 5
          WorkView = WorkView
          FieldName = '查询.性别'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*202'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label37: TLabel [0]
        Left = 30
        Top = 12
        Width = 36
        Height = 12
        Caption = '客户号'
        Visible = False
      end
      inherited UIPanel2: TUIPanel
        Top = 483
        Width = 836
        TabOrder = 4
        inherited btnOK: TBitBtn
          Left = 660
        end
        inherited btnCancel: TBitBtn
          Left = 748
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object WVDigitalEdit37: TWVDigitalEdit
        Left = 76
        Top = 8
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 3
        TabStop = True
        Text = '0'
        Visible = False
        WorkView = WorkView
        FieldName = '客户号'
        SynchronizeByValue = True
      end
      object grpBaseInfo: TGroupBox
        Left = 16
        Top = 40
        Width = 649
        Height = 249
        Caption = '基本信息'
        TabOrder = 0
        object Label44: TLabel
          Left = 66
          Top = 29
          Width = 24
          Height = 12
          Caption = '姓名'
        end
        object Label49: TLabel
          Left = 276
          Top = 29
          Width = 24
          Height = 12
          Caption = '性别'
        end
        object Label56: TLabel
          Left = 452
          Top = 29
          Width = 48
          Height = 12
          Caption = '政治面貌'
        end
        object Label47: TLabel
          Left = 42
          Top = 93
          Width = 48
          Height = 12
          Caption = '出生日期'
        end
        object Label45: TLabel
          Left = 42
          Top = 61
          Width = 48
          Height = 12
          Caption = '证件类型'
        end
        object Label46: TLabel
          Left = 252
          Top = 61
          Width = 48
          Height = 12
          Caption = '证件号码'
        end
        object Label48: TLabel
          Left = 252
          Top = 93
          Width = 48
          Height = 12
          Caption = '身高(CM)'
        end
        object Label55: TLabel
          Left = 452
          Top = 93
          Width = 48
          Height = 12
          Caption = '文化程度'
        end
        object Label60: TLabel
          Left = 476
          Top = 125
          Width = 24
          Height = 12
          Caption = '民族'
        end
        object Label54: TLabel
          Left = 42
          Top = 125
          Width = 48
          Height = 12
          Caption = '婚姻状态'
        end
        object Label59: TLabel
          Left = 276
          Top = 125
          Width = 24
          Height = 12
          Caption = '国籍'
        end
        object Label62: TLabel
          Left = 42
          Top = 150
          Width = 48
          Height = 24
          Alignment = taRightJustify
          BiDiMode = bdLeftToRight
          Caption = '户口所在地类型'
          ParentBiDiMode = False
          WordWrap = True
        end
        object Label63: TLabel
          Left = 240
          Top = 156
          Width = 60
          Height = 12
          Caption = '户口所在地'
        end
        object Label61: TLabel
          Left = 66
          Top = 189
          Width = 24
          Height = 12
          Caption = '籍贯'
        end
        object Label67: TLabel
          Left = 252
          Top = 181
          Width = 48
          Height = 24
          Caption = '首次到达本市日期'
          WordWrap = True
        end
        object Label50: TLabel
          Left = 476
          Top = 189
          Width = 24
          Height = 12
          Caption = '电话'
        end
        object Label51: TLabel
          Left = 276
          Top = 221
          Width = 24
          Height = 12
          Caption = '手机'
        end
        object Label53: TLabel
          Left = 42
          Top = 221
          Width = 48
          Height = 12
          Caption = '单位名称'
        end
        object Label52: TLabel
          Left = 452
          Top = 221
          Width = 48
          Height = 12
          Caption = '电子信箱'
        end
        object WVEdit44: TWVEdit
          Left = 98
          Top = 24
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<姓名>'
          WorkView = WorkView
          FieldName = '姓名'
          SynchronizeWhenExit = True
        end
        object edtBirthday: TWVEdit
          Left = 98
          Top = 87
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 5
          Text = '<出生日期>'
          WorkView = WorkView
          FieldName = '出生日期'
          SynchronizeWhenExit = True
        end
        object edtIdNo: TWVEdit
          Left = 305
          Top = 56
          Width = 323
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 4
          Text = '<证件号码>'
          WorkView = WorkView
          FieldName = '证件号码'
          SynchronizeWhenExit = True
        end
        object edtHeight: TWVEdit
          Left = 305
          Top = 87
          Width = 123
          Height = 20
          Color = clInfoBk
          MaxLength = 22
          ReadOnly = False
          TabOrder = 6
          Text = '<身高>'
          WorkView = WorkView
          FieldName = '身高'
          SynchronizeWhenExit = True
        end
        object WVEdit63: TWVEdit
          Left = 305
          Top = 152
          Width = 323
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 12
          Text = '<户口所在地>'
          WorkView = WorkView
          FieldName = '户口所在地'
          SynchronizeWhenExit = True
        end
        object WVEdit61: TWVEdit
          Left = 98
          Top = 182
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 13
          Text = '<籍贯>'
          WorkView = WorkView
          FieldName = '籍贯'
          SynchronizeWhenExit = True
        end
        object edtArriveDate: TWVEdit
          Left = 305
          Top = 183
          Width = 123
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 14
          Text = '<首次到达本市日期>'
          WorkView = WorkView
          FieldName = '首次到达本市日期'
          SynchronizeWhenExit = True
        end
        object WVEdit50: TWVEdit
          Left = 508
          Top = 183
          Width = 120
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 15
          Text = '<电话>'
          WorkView = WorkView
          FieldName = '电话'
          SynchronizeWhenExit = True
        end
        object WVEdit51: TWVEdit
          Left = 305
          Top = 215
          Width = 123
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 17
          Text = '<手机>'
          WorkView = WorkView
          FieldName = '手机'
          SynchronizeWhenExit = True
        end
        object WVEdit53: TWVEdit
          Left = 98
          Top = 215
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 16
          Text = '<单位名称>'
          WorkView = WorkView
          FieldName = '单位名称'
          SynchronizeWhenExit = True
        end
        object WVEdit52: TWVEdit
          Left = 508
          Top = 215
          Width = 120
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 18
          Text = '<电子信箱>'
          WorkView = WorkView
          FieldName = '电子信箱'
          SynchronizeWhenExit = True
        end
        object cbbSex: TWVComboBox
          Tag = 1
          Left = 305
          Top = 24
          Width = 123
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 1
          WorkView = WorkView
          FieldName = '性别'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*202'
        end
        object WVComboBox3: TWVComboBox
          Left = 508
          Top = 24
          Width = 122
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '政治面貌'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*205'
        end
        object cbbIdType: TWVComboBox
          Left = 98
          Top = 56
          Width = 135
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '证件类型'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*201'
        end
        object WVComboBox5: TWVComboBox
          Left = 98
          Top = 119
          Width = 135
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 8
          WorkView = WorkView
          FieldName = '婚姻状态'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*203'
        end
        object WVComboBox6: TWVComboBox
          Left = 305
          Top = 119
          Width = 123
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 9
          WorkView = WorkView
          FieldName = '国籍'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*208'
        end
        object WVComboBox7: TWVComboBox
          Left = 508
          Top = 119
          Width = 122
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 10
          WorkView = WorkView
          FieldName = '民族'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*209'
        end
        object WVComboBox8: TWVComboBox
          Left = 508
          Top = 87
          Width = 122
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 7
          WorkView = WorkView
          FieldName = '文化程度'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*204'
        end
        object WVComboBox11: TWVComboBox
          Left = 98
          Top = 151
          Width = 135
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 11
          WorkView = WorkView
          FieldName = '户口所在地类型'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*211'
        end
      end
      object grpAddr: TGroupBox
        Left = 16
        Top = 304
        Width = 649
        Height = 81
        Caption = '居住信息'
        TabOrder = 1
        object Label57: TLabel
          Left = 42
          Top = 29
          Width = 48
          Height = 12
          Caption = '经济来源'
        end
        object Label66: TLabel
          Left = 252
          Top = 29
          Width = 48
          Height = 12
          Caption = '居住日期'
        end
        object Label64: TLabel
          Left = 452
          Top = 29
          Width = 48
          Height = 12
          Caption = '居住是由'
        end
        object Label65: TLabel
          Left = 42
          Top = 57
          Width = 48
          Height = 12
          Caption = '居住地址'
        end
        object edtLiveDate: TWVEdit
          Left = 305
          Top = 24
          Width = 123
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<居住日期>'
          WorkView = WorkView
          FieldName = '居住日期'
          SynchronizeWhenExit = True
        end
        object WVEdit65: TWVEdit
          Left = 98
          Top = 53
          Width = 530
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 3
          Text = '<居住地址>'
          WorkView = WorkView
          FieldName = '居住地址'
          SynchronizeWhenExit = True
        end
        object WVComboBox9: TWVComboBox
          Left = 98
          Top = 24
          Width = 135
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '经济来源'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*206'
        end
        object WVComboBox10: TWVComboBox
          Left = 508
          Top = 24
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '居住是由'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*212'
        end
      end
      object grpCardInfo: TGroupBox
        Left = 16
        Top = 392
        Width = 649
        Height = 81
        Caption = '发卡信息'
        TabOrder = 2
        object Label41: TLabel
          Left = 42
          Top = 55
          Width = 48
          Height = 12
          Caption = '申请日期'
        end
        object Label39: TLabel
          Left = 42
          Top = 27
          Width = 48
          Height = 12
          Caption = '发卡部门'
        end
        object Label40: TLabel
          Left = 251
          Top = 19
          Width = 48
          Height = 24
          Caption = '申请有效期限(月)'
          WordWrap = True
        end
        object Label38: TLabel
          Left = 468
          Top = 69
          Width = 24
          Height = 12
          Caption = '卡号'
          Visible = False
        end
        object Label1: TLabel
          Left = 452
          Top = 27
          Width = 48
          Height = 12
          Caption = '发卡类别'
        end
        object Label2: TLabel
          Left = 240
          Top = 53
          Width = 60
          Height = 12
          Caption = '集团服务号'
        end
        object edtAppDate: TWVEdit
          Left = 98
          Top = 50
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 2
          Text = '<申请日期>'
          WorkView = WorkView
          FieldName = '申请日期'
          SynchronizeWhenExit = True
        end
        object WVDigitalEdit40: TWVDigitalEdit
          Left = 305
          Top = 21
          Width = 123
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
          FieldName = '申请有效期限(月)'
          SynchronizeByValue = True
        end
        object WVEdit38: TWVEdit
          Left = 497
          Top = 64
          Width = 123
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 3
          Text = '<卡号>'
          Visible = False
          WorkView = WorkView
          FieldName = '卡号'
          SynchronizeWhenExit = True
        end
        object WVComboBox2: TWVComboBox
          Left = 98
          Top = 22
          Width = 135
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          DropDownCount = 20
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '发卡部门'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*210'
        end
        object cbbCardType: TWVComboBox
          Left = 508
          Top = 22
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          DropDownCount = 20
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '发卡类别'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-5'
        end
        object WVEdit1: TWVEdit
          Left = 305
          Top = 48
          Width = 123
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 5
          Text = '<集团服务号>'
          WorkView = WorkView
          FieldName = '集团服务号'
          SynchronizeWhenExit = True
        end
      end
      object grpPhoto: TGroupBox
        Left = 680
        Top = 40
        Width = 137
        Height = 185
        Caption = '照片信息'
        TabOrder = 5
        Visible = False
        object imgPhoto: TImage
          Left = 8
          Top = 16
          Width = 120
          Height = 160
          Picture.Data = {
            0A544A504547496D6167659B050000FFD8FFE000104A46494600010101006000
            600000FFDB0043000D09090A0A0A0E0B0B0E140D0B0D1417110E0E11171B1515
            1515151B1B1517171717151B1A1E2021201E1A27272A2A272735353535353636
            3636363636363636FFDB0043010E0D0D1111111711111717131413171D191A1A
            191D261D1D1E1D1D262C2420202020242C282B2626262B282F2F2C2C2F2F3636
            36363636363636363636363636FFC00011080070005403011100021101031101
            FFC4001B00000203010101000000000000000000000005010406070302FFC400
            4010000103020303080608040700000000000100020304110512210631411322
            32516171819114162352A1C1333435547292B1F02443D1D2536273A2B2E1F1FF
            C40014010100000000000000000000000000000000FFC4001411010000000000
            0000000000000000000000FFDA000C03010002110311003F00D1A01008250082
            104A0840201008250083E6495B18B9F068DE7C38A057518DB5AEB40DCEDB0B93
            A6A8293F16AC7DB9F6B6BA0DE83C1B553B0B8B6423374ADC507B4389D4C31F26
            D22DD76D77DCF1081A5362F14EFC8E696389E6F107C8206080B202C825041360
            7CD066F10AD3552E976B1BA0693C7C10544020104209DC81AE1B8A4BCA470CB6
            730F35AEE20F040ED00825055C46734F4AF7817E1DD7D1066105AC3F0CABC4A5
            E4E9D97B749E746B7BCFECA0D452EC552B403552BA57FBACE6B7E37282E1D92C
            1C8B726EEFCEEF9E8817576C536D9A8663987F2E5F93C0FD420CB54534D4B298
            67618E46EF69D104D1FD662ED7B47C7FED06B100825056C41A1D47303BB21F31
            AA0CC451BE69191305DF23835A3B4E83CD074CC3A822C3E9594F10E88E73B8B8
            F12822BF13A4C3D99EA64C97E88DEE3DC02058CDB1C29CECA79460F78B34F269
            27E081D41510D4442585E248DDB9C0DD02BDA4C2995D46F91A3F8880678DC379
            B6F6F920C361FF005B87F1041AB4020941F12B43A37B4EE2083E21020D9E607E
            2F4A0EECF7FCA0B87E883A3A0E7BB533BE5C5A60E3CD8F2B59D832827E281420
            D86C3998C5557BF237664FC5ADEDF041A83AEFE28397537D6A3CA74E506A7AAE
            835A8041281263F2CCD7C4C0E223209D389DC502AA7A8969A56CD0BB24ADDCED
            0DB81EBEB417FD65C63EF27C9BFD1050A8A896A6574D33B3C8FE93BE1C1031C1
            3009F157673ECE95A6CE9389FF002B506F292920A385B053B43236F0EDE249EB
            414B1FC523C3A89E737B6906589BC6E74BF820E77F2DC83631B488DA0EF005D0
            7DA0940BF1AA6E5E94B9BD388E6F0E2833282507DC113A696385BD291CD60EF7
            1B20EA14D4F1D340C862196360B01F340A3683684619EC2101F54F17B9DCC1D6
            6DC7B10622A6AA7AA90CD3BCC921DE4FEEC83D30EA7F48AB8D9BDA0E67770DE8
            3596402094020478960F0C71C9511B88035E4F86A6C812A0B98280714A407FC5
            67C08283A620E77B4AE2EC66A6FAD8B47FB1A815A0D561D41152442C3DA380CE
            E3BEFC420B8804128041E73442689F11DCF041418F9E17C1298A4167B74FFC41
            E94351E8B570D45B3724F0ECB7DF6F341A7F5E62FBA3BF38FED419BC4EB05756
            CB521B90484736F7B6806FF04061D48FAAA86B40BB1A4179E000D4A0D620104A
            094108040AB682367A207D867CE05FC0A0474749256D4329A2B72921B36FA0D3
            5EAEC40E3D4CC57AE2FCC7FB502AC42826C3AA3D1E7B1900079BA8D77207F826
            4F408F2EF17CFD77B9417EC80B2094020A73E2D43068E903CFBADE77E9A205F2
            ED20FE4C3E2F3FD102FADC56A2B581920686839B9B7E17EBEF41EDB37F6CD2FE
            277FC5C83A3A0C0ED87DAEEFF4D9F340B292BA7A371313B43BDA777920BECDA3
            A91F491B5C3B2E105C87682924D240633DBA8F82060CABA690666CAC23BD0652
            AB10A9AAFA579CBEE0E8F971415D008041F70CF2D3C82585C592B7A2E1E482EF
            AC18BFDE9E82A54D54F55272B3BCC921D331EC41E48040203F7C500804020100
            804020100804020FFFD9}
          Stretch = True
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 340
    Top = 311
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
        Name = '操作标志'
        Caption = '操作标志'
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
        DataField = 'sstat_type'
      end
      item
        Name = '查询.发卡部门'
        Caption = '查询.发卡部门'
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
        Name = '查询.申请状态'
        Caption = '查询.申请状态'
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
        Name = '查询.姓名'
        Caption = '查询.姓名'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 20
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.证件类型'
        Caption = '查询.证件类型'
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
        Name = '查询.证件号码'
        Caption = '查询.证件号码'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 20
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.出生日期'
        Caption = '查询.出生日期'
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
        Name = '查询.性别'
        Caption = '查询.性别'
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
        Name = '查询.电话'
        Caption = '查询.电话'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 20
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.手机'
        Caption = '查询.手机'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 20
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.电子信箱'
        Caption = '查询.电子信箱'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 40
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
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
        DataField = 'scard0'
      end
      item
        Name = '发卡部门'
        Caption = '发卡部门'
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
        DataField = 'sroom_no2'
      end
      item
        Name = '申请有效期限(月)'
        Caption = '申请有效期限(月)'
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
        Name = '申请日期'
        Caption = '申请日期'
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
        DataField = 'sdate0'
      end
      item
        Name = '申请状态'
        Caption = '申请状态'
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
        DataField = 'sstatus0'
      end
      item
        Name = '预交款'
        Caption = '预交款'
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
      end
      item
        Name = '姓名'
        Caption = '姓名'
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
        Name = '证件类型'
        Caption = '证件类型'
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
        DataField = 'sroom_no'
      end
      item
        Name = '证件号码'
        Caption = '证件号码'
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
        DataField = 'spager'
      end
      item
        Name = '出生日期'
        Caption = '出生日期'
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
        DataField = 'sdate1'
      end
      item
        Name = '身高'
        Caption = '身高'
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
        DataField = 'lvol2'
      end
      item
        Name = '性别'
        Caption = '性别'
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
        DataField = 'scust_type'
      end
      item
        Name = '电话'
        Caption = '电话'
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
        DataField = 'sphone'
      end
      item
        Name = '手机'
        Caption = '手机'
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
        DataField = 'sphone2'
      end
      item
        Name = '电子信箱'
        Caption = '电子信箱'
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
        DataField = 'semail'
      end
      item
        Name = '单位名称'
        Caption = '单位名称'
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
        Name = '婚姻状态'
        Caption = '婚姻状态'
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
        DataField = 'sorder0'
      end
      item
        Name = '文化程度'
        Caption = '文化程度'
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
        DataField = 'sorder1'
      end
      item
        Name = '政治面貌'
        Caption = '政治面貌'
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
        DataField = 'sorder2'
      end
      item
        Name = '经济来源'
        Caption = '经济来源'
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
        DataField = 'sserial0'
      end
      item
        Name = '国籍'
        Caption = '国籍'
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
        DataField = 'snation_code'
      end
      item
        Name = '民族'
        Caption = '民族'
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
        DataField = 'sserial1'
      end
      item
        Name = '籍贯'
        Caption = '籍贯'
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
        DataField = 'scert_addr'
      end
      item
        Name = '户口所在地类型'
        Caption = '户口所在地类型'
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
        DataField = 'sserial2'
      end
      item
        Name = '户口所在地'
        Caption = '户口所在地'
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
        DataField = 'vsvarstr1'
      end
      item
        Name = '居住是由'
        Caption = '居住是由'
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
        DataField = 'sserial3'
      end
      item
        Name = '居住地址'
        Caption = '居住地址'
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
        DataField = 'vsvarstr2'
      end
      item
        Name = '居住日期'
        Caption = '居住日期'
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
        DataField = 'sdate2'
      end
      item
        Name = '首次到达本市日期'
        Caption = '首次到达本市日期'
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
        DataField = 'sdate3'
      end
      item
        Name = '更新时间'
        Caption = '更新时间'
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
        DataField = 'sname'
      end
      item
        Name = '是否删除'
        Caption = '是否删除'
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
        DataField = 'smarket_code'
      end
      item
        Name = '发卡类别'
        Caption = '发卡类别'
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
        DataField = 'semp_no'
      end
      item
        Name = '集团服务号'
        Caption = '集团服务号'
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
        DataField = 'semail2'
      end>
    Left = 64
    Top = 312
  end
  inherited QueryRequest: TWVRequest
    ID = '客户信息维护查询'
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
        ParamName = '发卡部门'
        FieldName = '查询.发卡部门'
      end
      item
        ParamName = '申请状态'
        FieldName = '查询.申请状态'
      end
      item
        ParamName = '姓名'
        FieldName = '查询.姓名'
      end
      item
        ParamName = '证件类型'
        FieldName = '查询.证件类型'
      end
      item
        ParamName = '证件号码'
        FieldName = '查询.证件号码'
      end
      item
        ParamName = '出生日期'
        FieldName = '查询.出生日期'
      end
      item
        ParamName = '性别'
        FieldName = '查询.性别'
      end
      item
        ParamName = '电话'
        FieldName = '查询.电话'
      end
      item
        ParamName = '手机'
        FieldName = '查询.手机'
      end
      item
        ParamName = '电子信箱'
        FieldName = '查询.电子信箱'
      end>
    Left = 224
    Top = 312
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sroom_no'
        WVFieldName = '证件类型'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '201'
      end
      item
        FieldName = 'sstatus0'
        WVFieldName = '申请状态'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '200'
      end
      item
        FieldName = 'scust_type'
        WVFieldName = '性别'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '202'
      end
      item
        FieldName = 'sorder0'
        WVFieldName = '婚姻状态'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '203'
      end
      item
        FieldName = 'sorder1'
        WVFieldName = '文化程度'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '204'
      end
      item
        FieldName = 'sorder2'
        WVFieldName = '政治面貌'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '205'
      end
      item
        FieldName = 'sserial0'
        WVFieldName = '经济来源'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '206'
      end
      item
        FieldName = 'snation_code'
        WVFieldName = '国籍'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '208'
      end
      item
        FieldName = 'sserial1'
        WVFieldName = '民族'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '209'
      end
      item
        FieldName = 'sserial2'
        WVFieldName = '户口所在地类型'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '211'
      end
      item
        FieldName = 'sserial3'
        WVFieldName = '居住是由'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '212'
      end
      item
        FieldName = 'smarket_code'
        WVFieldName = '是否删除'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '213'
      end
      item
        FieldName = 'sroom_no2'
        WVFieldName = '发卡部门'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '210'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-5'
      end>
    Left = 300
    Top = 311
  end
  inherited AddRequest: TWVRequest
    ID = '客户信息维护'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
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
        ParamName = '发卡部门'
        FieldName = '发卡部门'
      end
      item
        ParamName = '申请有效期限(月)'
        FieldName = '申请有效期限(月)'
      end
      item
        ParamName = '申请日期'
        FieldName = '申请日期'
      end
      item
        ParamName = '申请状态'
        FieldName = '申请状态'
      end
      item
        ParamName = '预交款'
        FieldName = '预交款'
      end
      item
        ParamName = '姓名'
        FieldName = '姓名'
      end
      item
        ParamName = '证件类型'
        FieldName = '证件类型'
      end
      item
        ParamName = '证件号码'
        FieldName = '证件号码'
      end
      item
        ParamName = '出生日期'
        FieldName = '出生日期'
      end
      item
        ParamName = '身高'
        FieldName = '身高'
      end
      item
        ParamName = '性别'
        FieldName = '性别'
      end
      item
        ParamName = '电话'
        FieldName = '电话'
      end
      item
        ParamName = '手机'
        FieldName = '手机'
      end
      item
        ParamName = '电子信箱'
        FieldName = '电子信箱'
      end
      item
        ParamName = '单位名称'
        FieldName = '单位名称'
      end
      item
        ParamName = '婚姻状态'
        FieldName = '婚姻状态'
      end
      item
        ParamName = '文化程度'
        FieldName = '文化程度'
      end
      item
        ParamName = '政治面貌'
        FieldName = '政治面貌'
      end
      item
        ParamName = '经济来源'
        FieldName = '经济来源'
      end
      item
        ParamName = '国籍'
        FieldName = '国籍'
      end
      item
        ParamName = '民族'
        FieldName = '民族'
      end
      item
        ParamName = '籍贯'
        FieldName = '籍贯'
      end
      item
        ParamName = '户口所在地类型'
        FieldName = '户口所在地类型'
      end
      item
        ParamName = '户口所在地'
        FieldName = '户口所在地'
      end
      item
        ParamName = '居住是由'
        FieldName = '居住是由'
      end
      item
        ParamName = '居住地址'
        FieldName = '居住地址'
      end
      item
        ParamName = '居住日期'
        FieldName = '居住日期'
      end
      item
        ParamName = '首次到达本市日期'
        FieldName = '首次到达本市日期'
      end
      item
        ParamName = '更新时间'
        FieldName = '更新时间'
      end
      item
        ParamName = '是否删除'
        FieldName = '是否删除'
      end
      item
        ParamName = '发卡类别'
        FieldName = '发卡类别'
      end
      item
        ParamName = '集团服务号'
        FieldName = '集团服务号'
      end>
    Left = 104
    Top = 312
  end
  inherited DeleteRequest: TWVRequest
    ID = '客户信息维护'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
        DefaultValue = 0
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '发卡部门'
        FieldName = '发卡部门'
      end
      item
        ParamName = '申请有效期限(月)'
        FieldName = '申请有效期限(月)'
        DefaultValue = 0
      end
      item
        ParamName = '申请日期'
        FieldName = '申请日期'
      end
      item
        ParamName = '申请状态'
        FieldName = '申请状态'
      end
      item
        ParamName = '预交款'
        FieldName = '预交款'
        DefaultValue = 0
      end
      item
        ParamName = '姓名'
        FieldName = '姓名'
      end
      item
        ParamName = '证件类型'
        FieldName = '证件类型'
      end
      item
        ParamName = '证件号码'
        FieldName = '证件号码'
      end
      item
        ParamName = '出生日期'
        FieldName = '出生日期'
      end
      item
        ParamName = '身高'
        FieldName = '身高'
        DefaultValue = 0
      end
      item
        ParamName = '性别'
        FieldName = '性别'
      end
      item
        ParamName = '电话'
        FieldName = '电话'
      end
      item
        ParamName = '手机'
        FieldName = '手机'
      end
      item
        ParamName = '电子信箱'
        FieldName = '电子信箱'
      end
      item
        ParamName = '单位名称'
        FieldName = '单位名称'
      end
      item
        ParamName = '婚姻状态'
        FieldName = '婚姻状态'
      end
      item
        ParamName = '文化程度'
        FieldName = '文化程度'
      end
      item
        ParamName = '政治面貌'
        FieldName = '政治面貌'
      end
      item
        ParamName = '经济来源'
        FieldName = '经济来源'
      end
      item
        ParamName = '国籍'
        FieldName = '国籍'
      end
      item
        ParamName = '民族'
        FieldName = '民族'
      end
      item
        ParamName = '籍贯'
        FieldName = '籍贯'
      end
      item
        ParamName = '户口所在地类型'
        FieldName = '户口所在地类型'
      end
      item
        ParamName = '户口所在地'
        FieldName = '户口所在地'
      end
      item
        ParamName = '居住是由'
        FieldName = '居住是由'
      end
      item
        ParamName = '居住地址'
        FieldName = '居住地址'
      end
      item
        ParamName = '居住日期'
        FieldName = '居住日期'
      end
      item
        ParamName = '首次到达本市日期'
        FieldName = '首次到达本市日期'
      end
      item
        ParamName = '更新时间'
        FieldName = '更新时间'
      end
      item
        ParamName = '是否删除'
        FieldName = '是否删除'
      end
      item
        ParamName = '发卡类别'
        FieldName = '发卡类别'
      end
      item
        ParamName = '集团服务号'
        FieldName = '集团服务号'
      end>
    Left = 144
    Top = 312
  end
  inherited ChangeRequest: TWVRequest
    ID = '客户信息维护'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
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
        ParamName = '发卡部门'
        FieldName = '发卡部门'
      end
      item
        ParamName = '申请有效期限(月)'
        FieldName = '申请有效期限(月)'
      end
      item
        ParamName = '申请日期'
        FieldName = '申请日期'
      end
      item
        ParamName = '申请状态'
        FieldName = '申请状态'
      end
      item
        ParamName = '预交款'
        FieldName = '预交款'
      end
      item
        ParamName = '姓名'
        FieldName = '姓名'
      end
      item
        ParamName = '证件类型'
        FieldName = '证件类型'
      end
      item
        ParamName = '证件号码'
        FieldName = '证件号码'
      end
      item
        ParamName = '出生日期'
        FieldName = '出生日期'
      end
      item
        ParamName = '身高'
        FieldName = '身高'
      end
      item
        ParamName = '性别'
        FieldName = '性别'
      end
      item
        ParamName = '电话'
        FieldName = '电话'
      end
      item
        ParamName = '手机'
        FieldName = '手机'
      end
      item
        ParamName = '电子信箱'
        FieldName = '电子信箱'
      end
      item
        ParamName = '单位名称'
        FieldName = '单位名称'
      end
      item
        ParamName = '婚姻状态'
        FieldName = '婚姻状态'
      end
      item
        ParamName = '文化程度'
        FieldName = '文化程度'
      end
      item
        ParamName = '政治面貌'
        FieldName = '政治面貌'
      end
      item
        ParamName = '经济来源'
        FieldName = '经济来源'
      end
      item
        ParamName = '国籍'
        FieldName = '国籍'
      end
      item
        ParamName = '民族'
        FieldName = '民族'
      end
      item
        ParamName = '籍贯'
        FieldName = '籍贯'
      end
      item
        ParamName = '户口所在地类型'
        FieldName = '户口所在地类型'
      end
      item
        ParamName = '户口所在地'
        FieldName = '户口所在地'
      end
      item
        ParamName = '居住是由'
        FieldName = '居住是由'
      end
      item
        ParamName = '居住地址'
        FieldName = '居住地址'
      end
      item
        ParamName = '居住日期'
        FieldName = '居住日期'
      end
      item
        ParamName = '首次到达本市日期'
        FieldName = '首次到达本市日期'
      end
      item
        ParamName = '更新时间'
        FieldName = '更新时间'
      end
      item
        ParamName = '是否删除'
        FieldName = '是否删除'
      end
      item
        ParamName = '发卡类别'
        FieldName = '发卡类别'
      end
      item
        ParamName = '集团服务号'
        FieldName = '集团服务号'
      end>
    Left = 184
    Top = 312
  end
  inherited WVDataSource: TWVDataSource
    Left = 260
    Top = 311
  end
  inherited alDatasetActions: TActionList
    Left = 380
    Top = 316
  end
end
