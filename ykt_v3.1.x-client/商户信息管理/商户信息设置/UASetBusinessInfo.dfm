inherited faqhSetBusinessInfo: TfaqhSetBusinessInfo
  Width = 808
  Height = 511
  Caption = '商户信息设置'
  inherited pcPages: TRzPageControl
    Width = 808
    Height = 511
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      object Label30: TLabel [0]
        Left = 344
        Top = 64
        Width = 128
        Height = 16
        Caption = '在左边选择父商户'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Splitter1: TSplitter [1]
        Left = 273
        Top = 33
        Width = 4
        Height = 425
        Cursor = crHSplit
      end
      object Panel1: TPanel [2]
        Left = 0
        Top = 0
        Width = 804
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label1: TLabel
          Left = 22
          Top = 10
          Width = 36
          Height = 12
          Caption = '商户号'
        end
        object Label25: TLabel
          Left = 202
          Top = 10
          Width = 48
          Height = 12
          Caption = '商户名称'
        end
        object Label26: TLabel
          Left = 396
          Top = 10
          Width = 48
          Height = 12
          Caption = '商户类别'
        end
        object Label27: TLabel
          Left = 586
          Top = 9
          Width = 48
          Height = 12
          Caption = '独立核算'
        end
        object WVEdit2: TWVEdit
          Left = 260
          Top = 6
          Width = 120
          Height = 20
          Color = clWhite
          ImeName = '中文 (简体) - 微软拼音'
          ReadOnly = False
          TabOrder = 2
          Text = '<查询.商户名称>'
          WorkView = WorkView
          FieldName = '查询.商户名称'
          SynchronizeWhenExit = True
        end
        object WVComboBox8: TWVComboBox
          Left = 456
          Top = 6
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '查询.商户类别'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*14'
        end
        object WVComboBox9: TWVComboBox
          Left = 644
          Top = 5
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '查询.是否为独立核算'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*2'
        end
        object edtBusiId: TWVEdit
          Left = 68
          Top = 6
          Width = 120
          Height = 20
          Color = clWhite
          ImeName = '中文 (简体) - 微软拼音'
          MaxLength = 22
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.商户标识>'
          WorkView = WorkView
          FieldName = '查询.商户标识'
          SynchronizeWhenExit = True
        end
      end
      inherited UIPanel1: TUIPanel
        Top = 458
        Width = 804
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 543
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 629
        end
        inherited btnQuery: TBitBtn [2]
          Left = 457
        end
        inherited btnDelete: TBitBtn
          Left = 715
          Hint = '注销当前选中的条目'
          Caption = '注销(&D)'
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 90
          Width = 159
        end
        inherited RBtnAddBrother: TRzRadioButton
          Left = 336
        end
        inherited RbtnAddChild: TRzRadioButton
          Left = 256
        end
      end
      inherited TreeView: TRzTreeView
        Top = 33
        Width = 273
        Height = 425
        Align = alLeft
        DragMode = dmManual
        TabOrder = 1
      end
      inherited Grid: TRzDBGrid
        Left = 277
        Top = 33
        Width = 527
        Height = 425
        Align = alClient
        ImeName = ''
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        TabOrder = 2
        OnCellClick = GridCellClick
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
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 312
        Top = 41
        Width = 42
        Height = 12
        Caption = '商户号*'
      end
      object Label10: TLabel [1]
        Left = 330
        Top = 236
        Width = 24
        Height = 12
        Caption = '电话'
      end
      object Label11: TLabel [2]
        Left = 51
        Top = 202
        Width = 36
        Height = 12
        Caption = '联系人'
      end
      object Label12: TLabel [3]
        Left = 306
        Top = 203
        Width = 48
        Height = 12
        Caption = '证件类型'
      end
      object Label13: TLabel [4]
        Left = 585
        Top = 235
        Width = 24
        Height = 12
        Caption = '手机'
      end
      object Label15: TLabel [5]
        Left = 39
        Top = 267
        Width = 48
        Height = 12
        Caption = '电子信箱'
      end
      object Label16: TLabel [6]
        Left = 306
        Top = 268
        Width = 48
        Height = 12
        Caption = '联系地址'
      end
      object WVLabel1: TWVLabel [7]
        Left = 585
        Top = 268
        Width = 24
        Height = 12
        Caption = '邮编'
      end
      object Bevel1: TBevel [8]
        Left = 32
        Top = 189
        Width = 753
        Height = 2
        Shape = bsFrame
        Style = bsRaised
      end
      object Label32: TLabel [9]
        Left = 39
        Top = 235
        Width = 48
        Height = 12
        Caption = '所属部门'
      end
      object Label4: TLabel [10]
        Left = 45
        Top = 41
        Width = 42
        Height = 12
        Caption = '父商户*'
      end
      object Label6: TLabel [11]
        Left = 300
        Top = 73
        Width = 54
        Height = 12
        Caption = '商户类型*'
      end
      object Label7: TLabel [12]
        Left = 33
        Top = 106
        Width = 54
        Height = 12
        Caption = '独立核算*'
      end
      object Label31: TLabel [13]
        Left = 57
        Top = 73
        Width = 30
        Height = 12
        Caption = '区域*'
      end
      object Label5: TLabel [14]
        Left = 553
        Top = 41
        Width = 54
        Height = 12
        Caption = '商户名称*'
      end
      object Label14: TLabel [15]
        Left = 561
        Top = 203
        Width = 48
        Height = 12
        Caption = '证件号码'
      end
      object Label22: TLabel [16]
        Left = 306
        Top = 171
        Width = 48
        Height = 12
        Caption = '银行帐号'
      end
      object Label37: TLabel [17]
        Left = 33
        Top = 138
        Width = 54
        Height = 12
        Caption = '佣金类型*'
      end
      object Label35: TLabel [18]
        Left = 306
        Top = 138
        Width = 48
        Height = 12
        Caption = '佣金比例'
      end
      object Label36: TLabel [19]
        Left = 516
        Top = 135
        Width = 6
        Height = 12
        Caption = '%'
      end
      object Label18: TLabel [20]
        Left = 282
        Top = 106
        Width = 72
        Height = 12
        Caption = '存款提成比率'
      end
      object Label24: TLabel [21]
        Left = 39
        Top = 170
        Width = 48
        Height = 12
        Caption = '银行代码'
      end
      object Label38: TLabel [22]
        Left = 549
        Top = 170
        Width = 60
        Height = 12
        Caption = '银行帐户名'
      end
      object Bevel2: TBevel [23]
        Left = 32
        Top = 155
        Width = 753
        Height = 2
        Shape = bsFrame
        Style = bsRaised
      end
      object Label3: TLabel [24]
        Left = 516
        Top = 105
        Width = 6
        Height = 12
        Caption = '%'
      end
      object Label8: TLabel [25]
        Left = 561
        Top = 74
        Width = 48
        Height = 12
        Caption = '收搭伙费'
      end
      inherited UIPanel2: TUIPanel
        Top = 452
        Width = 804
        TabOrder = 22
        inherited btnOK: TBitBtn
          Left = 620
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          OnClick = DBNavigatorClick
        end
      end
      object WVEdit10: TWVEdit
        Left = 360
        Top = 231
        Width = 150
        Height = 20
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        MaxLength = 14
        ReadOnly = False
        TabOrder = 17
        Text = '<电话>'
        WorkView = WorkView
        FieldName = '电话'
        SynchronizeWhenExit = True
      end
      object WVEdit11: TWVEdit
        Left = 96
        Top = 198
        Width = 173
        Height = 20
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ReadOnly = False
        TabOrder = 13
        Text = '<联系人>'
        WorkView = WorkView
        FieldName = '联系人'
        SynchronizeWhenExit = True
      end
      object WVEdit15: TWVEdit
        Left = 96
        Top = 264
        Width = 173
        Height = 20
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ReadOnly = False
        TabOrder = 19
        Text = '<电子邮箱>'
        WorkView = WorkView
        FieldName = '电子邮箱'
        SynchronizeWhenExit = True
      end
      object WVEdit16: TWVEdit
        Left = 360
        Top = 264
        Width = 150
        Height = 20
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ReadOnly = False
        TabOrder = 20
        Text = '<地址>'
        WorkView = WorkView
        FieldName = '地址'
        SynchronizeWhenExit = True
      end
      object cbbBusiType: TWVComboBox
        Left = 360
        Top = 69
        Width = 150
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 0
        TabOrder = 3
        Text = '<商户类型>'
        OnChange = cbbBusiTypeChange
        WorkView = WorkView
        FieldName = '商户类型'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*14'
      end
      object WVComboBox5: TWVComboBox
        Left = 360
        Top = 199
        Width = 150
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 0
        TabOrder = 15
        Text = '<证件类型>'
        WorkView = WorkView
        FieldName = '证件类型'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*87'
      end
      object WVEdit1: TWVEdit
        Left = 617
        Top = 264
        Width = 150
        Height = 20
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        MaxLength = 6
        ReadOnly = False
        TabOrder = 21
        Text = '<邮编>'
        WorkView = WorkView
        FieldName = '邮编'
      end
      object edtId: TWVEdit
        Left = 360
        Top = 37
        Width = 150
        Height = 20
        Color = clInfoBk
        ImeName = '中文 (简体) - 微软拼音'
        MaxLength = 22
        ReadOnly = False
        TabOrder = 1
        Text = '<商户标识>'
        WorkView = WorkView
        FieldName = '商户标识'
        SynchronizeWhenExit = True
      end
      object WVComboBox13: TWVComboBox
        Left = 96
        Top = 231
        Width = 173
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '紫光拼音输入法'
        ItemHeight = 0
        TabOrder = 16
        Text = '<部门>'
        WorkView = WorkView
        FieldName = '部门'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-22'
      end
      object edtPId: TWVEdit
        Left = 96
        Top = 37
        Width = 173
        Height = 20
        Color = clInfoBk
        ImeName = '中文 (简体) - 微软拼音'
        MaxLength = 22
        ReadOnly = False
        TabOrder = 0
        Text = '<父商户标识>'
        WorkView = WorkView
        FieldName = '父商户标识'
      end
      object WVEdit5: TWVEdit
        Left = 616
        Top = 38
        Width = 151
        Height = 20
        Color = clInfoBk
        ImeName = '中文 (简体) - 微软拼音'
        ReadOnly = False
        TabOrder = 2
        Text = '<商户名称>'
        WorkView = WorkView
        FieldName = '商户名称'
        SynchronizeWhenExit = True
      end
      object cbbCheckSelf: TWVComboBox
        Left = 96
        Top = 103
        Width = 173
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 7
        Text = '<独立核算>'
        OnChange = cbbCheckSelfChange
        WorkView = WorkView
        FieldName = '独立核算'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object WVComboBox12: TWVComboBox
        Left = 96
        Top = 70
        Width = 173
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ImeName = '紫光拼音输入法'
        ItemHeight = 0
        TabOrder = 4
        Text = '<区域>'
        WorkView = WorkView
        FieldName = '区域'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-27'
      end
      object WVEdit14: TWVEdit
        Left = 617
        Top = 198
        Width = 150
        Height = 20
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ReadOnly = False
        TabOrder = 14
        Text = '<证件号码>'
        WorkView = WorkView
        FieldName = '证件号码'
        SynchronizeWhenExit = True
      end
      object edtBankAccNo: TWVEdit
        Left = 360
        Top = 166
        Width = 150
        Height = 20
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ReadOnly = False
        TabOrder = 11
        Text = '<银行帐号>'
        WorkView = WorkView
        FieldName = '银行帐号'
        SynchronizeWhenExit = True
      end
      object cbbEmpRateType: TWVComboBox
        Left = 96
        Top = 134
        Width = 173
        Height = 18
        Style = csOwnerDrawFixed
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 9
        Text = '<佣金类型>'
        WorkView = WorkView
        FieldName = '佣金类型'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*91'
      end
      object edtEmpRate: TWVEdit
        Left = 360
        Top = 133
        Width = 150
        Height = 20
        Color = clWhite
        DragKind = dkDock
        ImeName = '中文 (简体) - 微软拼音'
        MaxLength = 22
        ReadOnly = False
        TabOrder = 8
        Text = '<佣金费率>'
        WorkView = WorkView
        FieldName = '佣金费率'
      end
      object edtFee: TWVEdit
        Left = 360
        Top = 101
        Width = 150
        Height = 20
        Color = clWhite
        DragKind = dkDock
        ImeName = '中文 (简体) - 微软拼音'
        MaxLength = 22
        ReadOnly = False
        TabOrder = 6
        Text = '<存款提成比率>'
        WorkView = WorkView
        FieldName = '存款提成比率'
      end
      object edtBankAccName: TWVEdit
        Left = 617
        Top = 165
        Width = 150
        Height = 20
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ReadOnly = False
        TabOrder = 10
        Text = '<银行帐户名>'
        WorkView = WorkView
        FieldName = '银行帐户名'
        SynchronizeWhenExit = True
      end
      object WVEdit4: TWVEdit
        Left = 617
        Top = 231
        Width = 150
        Height = 20
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        MaxLength = 15
        ReadOnly = False
        TabOrder = 18
        Text = '<手机>'
        WorkView = WorkView
        FieldName = '手机'
        SynchronizeWhenExit = True
      end
      object cbbBankCode: TWVComboBox
        Left = 96
        Top = 167
        Width = 173
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '紫光拼音输入法'
        ItemHeight = 0
        TabOrder = 12
        Text = '<银行代码>'
        WorkView = WorkView
        FieldName = '银行代码'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*110'
      end
      object cbbDhf: TWVComboBox
        Left = 616
        Top = 71
        Width = 153
        Height = 18
        Style = csOwnerDrawFixed
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 5
        Text = '<是否收搭伙费>'
        OnChange = cbbCheckSelfChange
        WorkView = WorkView
        FieldName = '是否收搭伙费'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 68
    Top = 375
  end
  inherited QueryRequest: TWVRequest
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
        FieldName = '查询.商户标识'
        DefaultValue = 0
      end
      item
        ParamName = '父商户标识'
        FieldName = '查询.父商户标识'
      end
      item
        ParamName = '商户名称'
        FieldName = '查询.商户名称'
      end
      item
        ParamName = '商户类别'
        FieldName = '查询.商户类别'
      end
      item
        ParamName = '是否为独立核算'
        FieldName = '查询.是否为独立核算'
      end
      item
        ParamName = '是否为叶节点'
        FieldName = '查询.是否为叶节点'
      end>
    Left = 72
    Top = 344
  end
  inherited QueryBinder: TWVDBBinder
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
        FieldName = 'smain_flag2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
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
        FieldName = 'sbank_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '110'
      end
      item
        FieldName = 'scust_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-39'
      end>
    Left = 100
    Top = 375
  end
  inherited AddRequest: TWVRequest
    ID = '商户信息设置'
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
        ParamName = '区域'
        FieldName = '区域'
      end
      item
        ParamName = '部门'
        FieldName = '部门'
      end
      item
        ParamName = '商户类型'
        FieldName = '商户类型'
      end
      item
        ParamName = '独立核算'
        FieldName = '独立核算'
      end
      item
        ParamName = '联系人'
        FieldName = '联系人'
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
        ParamName = '电话'
        FieldName = '电话'
      end
      item
        ParamName = '手机'
        FieldName = '手机'
      end
      item
        ParamName = '电子邮箱'
        FieldName = '电子邮箱'
      end
      item
        ParamName = '地址'
        FieldName = '地址'
      end
      item
        ParamName = '邮编'
        FieldName = '邮编'
      end
      item
        ParamName = '佣金类型'
        FieldName = '佣金类型'
      end
      item
        ParamName = '佣金费率'
        FieldName = '佣金费率'
      end
      item
        ParamName = '存款提成比率'
        FieldName = '存款提成比率'
      end
      item
        ParamName = '银行代码'
        FieldName = '银行代码'
      end
      item
        ParamName = '银行帐号'
        FieldName = '银行帐号'
      end
      item
        ParamName = '银行帐户名'
        FieldName = '银行帐户名'
      end
      item
        ParamName = '末级商户'
        FieldName = '末级商户'
      end
      item
        ParamName = '是否收搭伙费'
        FieldName = '是否收搭伙费'
      end>
    Top = 344
  end
  inherited DeleteRequest: TWVRequest
    ID = '商户信息设置'
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
        ParamName = '区域'
        FieldName = '区域'
      end
      item
        ParamName = '部门'
        FieldName = '部门'
      end
      item
        ParamName = '商户类型'
        FieldName = '商户类型'
      end
      item
        ParamName = '独立核算'
        FieldName = '独立核算'
      end
      item
        ParamName = '联系人'
        FieldName = '联系人'
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
        ParamName = '电话'
        FieldName = '电话'
      end
      item
        ParamName = '手机'
        FieldName = '手机'
      end
      item
        ParamName = '电子邮箱'
        FieldName = '电子邮箱'
      end
      item
        ParamName = '地址'
        FieldName = '地址'
      end
      item
        ParamName = '邮编'
        FieldName = '邮编'
      end
      item
        ParamName = '佣金类型'
        FieldName = '佣金类型'
      end
      item
        ParamName = '佣金费率'
        FieldName = '佣金费率'
      end
      item
        ParamName = '存款提成比率'
        FieldName = '存款提成比率'
      end
      item
        ParamName = '银行代码'
        FieldName = '银行代码'
      end
      item
        ParamName = '银行帐号'
        FieldName = '银行帐号'
      end
      item
        ParamName = '银行帐户名'
        FieldName = '银行帐户名'
      end
      item
        ParamName = '末级商户'
        FieldName = '末级商户'
      end
      item
        ParamName = '是否收搭伙费'
        FieldName = '是否收搭伙费'
      end>
    Top = 344
  end
  inherited ChangeRequest: TWVRequest
    ID = '商户信息设置'
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
        ParamName = '区域'
        FieldName = '区域'
      end
      item
        ParamName = '部门'
        FieldName = '部门'
      end
      item
        ParamName = '商户类型'
        FieldName = '商户类型'
      end
      item
        ParamName = '独立核算'
        FieldName = '独立核算'
      end
      item
        ParamName = '联系人'
        FieldName = '联系人'
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
        ParamName = '电话'
        FieldName = '电话'
      end
      item
        ParamName = '手机'
        FieldName = '手机'
      end
      item
        ParamName = '电子邮箱'
        FieldName = '电子邮箱'
      end
      item
        ParamName = '地址'
        FieldName = '地址'
      end
      item
        ParamName = '邮编'
        FieldName = '邮编'
      end
      item
        ParamName = '佣金类型'
        FieldName = '佣金类型'
      end
      item
        ParamName = '佣金费率'
        FieldName = '佣金费率'
      end
      item
        ParamName = '存款提成比率'
        FieldName = '存款提成比率'
      end
      item
        ParamName = '银行代码'
        FieldName = '银行代码'
      end
      item
        ParamName = '银行帐号'
        FieldName = '银行帐号'
      end
      item
        ParamName = '银行帐户名'
        FieldName = '银行帐户名'
      end
      item
        ParamName = '末级商户'
        FieldName = '末级商户'
      end
      item
        ParamName = '是否收搭伙费'
        FieldName = '是否收搭伙费'
      end>
    Left = 168
    Top = 344
  end
  inherited WVDataSource: TWVDataSource
    Left = 168
    Top = 376
  end
  inherited alDatasetActions: TActionList
    Left = 132
    Top = 376
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
        DataField = '@Return'
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
        DataField = 'vsmess'
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
        Name = '查询.商户标识'
        Caption = '查询.商户标识'
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
        DataField = 'lvol5'
      end
      item
        Name = '查询.商户名称'
        Caption = '查询.商户名称'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'scard1'
      end
      item
        Name = '查询.商户类别'
        Caption = '查询.商户类别'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sstat_type'
      end
      item
        Name = '查询.是否为独立核算'
        Caption = '查询.是否为独立核算'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'smain_flag'
      end
      item
        Name = '查询.是否为叶节点'
        Caption = '查询.是否为叶节点'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'smarket_code2'
      end
      item
        Name = '查询.父商户标识'
        Caption = '查询.父商户标识'
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
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol3'
      end
      item
        Name = '父商户标识'
        Caption = '父商户标识'
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
        Name = '商户名称'
        Caption = '商户名称'
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
        DataField = 'sall_name'
      end
      item
        Name = '区域'
        Caption = '区域'
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
        DataField = 'sbranch_code0'
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
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'scert_no'
      end
      item
        Name = '商户类型'
        Caption = '商户类型'
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
        DataField = 'lvol7'
      end
      item
        Name = '独立核算'
        Caption = '独立核算'
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
        DataField = 'smain_flag'
      end
      item
        Name = '联系人'
        Caption = '联系人'
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
        Name = '证件类型'
        Caption = '证件类型'
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
        DataField = 'smarket_code2'
      end
      item
        Name = '证件号码'
        Caption = '证件号码'
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
        DataField = 'semail2'
      end
      item
        Name = '电话'
        Caption = '电话'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 14
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
        Checker.MinLength = 0
        Checker.MaxLength = 15
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sphone2'
      end
      item
        Name = '电子邮箱'
        Caption = '电子邮箱'
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
        Name = '地址'
        Caption = '地址'
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
        DataField = 'scusttypes'
      end
      item
        Name = '邮编'
        Caption = '邮编'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'spost_code'
      end
      item
        Name = '佣金类型'
        Caption = '佣金类型'
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
        DataField = 'smarket_code'
      end
      item
        Name = '佣金费率'
        Caption = '佣金费率'
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
        DataField = 'drate0'
      end
      item
        Name = '存款提成比率'
        Caption = '存款提成比率'
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
        DataField = 'drate1'
      end
      item
        Name = '银行代码'
        Caption = '银行代码'
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
        DataField = 'sbank_code'
      end
      item
        Name = '银行帐号'
        Caption = '银行帐号'
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
        DataField = 'sbank_acc2'
      end
      item
        Name = '银行帐户名'
        Caption = '银行帐户名'
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
        DataField = 'sbankname2'
      end
      item
        Name = '末级商户'
        Caption = '末级商户'
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
        DataField = 'smain_flag2'
      end
      item
        Name = '是否收搭伙费'
        Caption = '是否收搭伙费'
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
        DataField = 'scust_type'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|商户标识|父商户标识|商户名称|商户类别|是否为独立核算|是否为叶节' +
          '点|商户状态|负责人姓名|是否收取管理费|校区|联系人班级或部门号|帐' +
          '户密码|'
      end>
    Left = 40
    Top = 344
  end
  object WorkView1: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        FieldType = wftUndefined
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
        GroupIndex = 1
        DataField = 'lvol5'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|商户标识|父商户标识|商户名称|商户类别|是否为独立核算|是否为叶节' +
          '点|商户状态|负责人姓名|是否收取管理费|校区|联系人班级或部门号|帐' +
          '户密码|'
      end>
    Left = 72
    Top = 408
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '商户信息主键查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '商户标识'
        FieldName = '商户标识'
        DefaultValue = 0
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end>
    AfterExec = CheckReturnData
    Left = 104
    Top = 408
  end
end
