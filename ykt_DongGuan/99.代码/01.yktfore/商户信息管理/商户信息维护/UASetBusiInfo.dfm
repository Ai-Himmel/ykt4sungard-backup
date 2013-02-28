inherited faqhSetBusiInfo: TfaqhSetBusiInfo
  Width = 725
  Height = 481
  Caption = '商户信息维护'
  inherited pcPages: TRzPageControl
    Width = 725
    Height = 481
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 428
        Width = 721
        TabOrder = 1
        inherited btnAdd: TBitBtn [0]
          Left = 455
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 543
          Enabled = False
          TabOrder = 4
        end
        inherited btnQuery: TBitBtn [2]
          Left = 366
        end
        inherited btnDelete: TBitBtn
          Left = 632
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 721
        TabOrder = 3
      end
      inherited Grid: TRzDBGrid
        Top = 105
        Width = 721
        Height = 323
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户编号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '中心商户号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '省商户编号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户名称'
            Width = 172
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户英文名称'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户简称'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbranch_code0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户类型'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbranch_code1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '行业类型'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbankname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '联系人'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '电话'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '手机'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '电子信箱'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '传真'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '营业地址'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spost_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '邮政编码'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '结算费率'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '开户银行'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spager'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '银行账号'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbankname2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '银行帐户名'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '联行号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '开户日期'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '销户日期'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '商户状态'
            Width = 70
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 721
        Height = 87
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label2: TLabel
          Left = 42
          Top = 10
          Width = 48
          Height = 12
          Caption = '商户编号'
        end
        object Label3: TLabel
          Left = 230
          Top = 10
          Width = 60
          Height = 12
          Caption = '中心商户号'
        end
        object Label4: TLabel
          Left = 30
          Top = 34
          Width = 60
          Height = 12
          Caption = '省商户编号'
        end
        object Label5: TLabel
          Left = 242
          Top = 34
          Width = 48
          Height = 12
          Caption = '商户名称'
        end
        object Label6: TLabel
          Left = 418
          Top = 34
          Width = 72
          Height = 12
          Caption = '商户英文名称'
        end
        object Label7: TLabel
          Left = 42
          Top = 58
          Width = 48
          Height = 12
          Caption = '商户简称'
        end
        object Label8: TLabel
          Left = 242
          Top = 58
          Width = 48
          Height = 12
          Caption = '商户类型'
        end
        object Label9: TLabel
          Left = 442
          Top = 58
          Width = 48
          Height = 12
          Caption = '行业类型'
        end
        object Label25: TLabel
          Left = 442
          Top = 10
          Width = 48
          Height = 12
          Caption = '商户状态'
        end
        object WVEdit3: TWVEdit
          Left = 300
          Top = 6
          Width = 114
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.中心商户号>'
          WorkView = WorkView
          FieldName = '查询.中心商户号'
        end
        object WVEdit4: TWVEdit
          Left = 100
          Top = 30
          Width = 124
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.省商户编号>'
          WorkView = WorkView
          FieldName = '查询.省商户编号'
        end
        object WVEdit5: TWVEdit
          Left = 300
          Top = 30
          Width = 114
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 2
          Text = '<查询.商户名>'
          WorkView = WorkView
          FieldName = '查询.商户名'
        end
        object WVEdit6: TWVEdit
          Left = 500
          Top = 30
          Width = 120
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 3
          Text = '<查询.商户英文名称>'
          WorkView = WorkView
          FieldName = '查询.商户英文名称'
        end
        object WVEdit7: TWVEdit
          Left = 100
          Top = 54
          Width = 124
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 4
          Text = '<查询.商户简称>'
          WorkView = WorkView
          FieldName = '查询.商户简称'
        end
        object edtBusiId: TWVEdit
          Left = 100
          Top = 6
          Width = 124
          Height = 20
          Color = clInfoBk
          MaxLength = 22
          ReadOnly = False
          TabOrder = 5
          Text = '<查询.商户编号>'
          WorkView = WorkView
          FieldName = '查询.商户编号'
        end
        object WVComboBox8: TWVComboBox
          Left = 500
          Top = 6
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 6
          WorkView = WorkView
          FieldName = '查询.商户状态'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*224'
        end
        object WVComboBox1: TWVComboBox
          Left = 300
          Top = 54
          Width = 114
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 7
          WorkView = WorkView
          FieldName = '查询.商户类型'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*216'
        end
        object WVComboBox2: TWVComboBox
          Left = 500
          Top = 54
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 8
          WorkView = WorkView
          FieldName = '查询.行业类型'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*217'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label26: TLabel [0]
        Left = 74
        Top = 12
        Width = 48
        Height = 12
        Caption = '商户编号'
        Visible = False
      end
      inherited UIPanel2: TUIPanel
        Top = 422
        Width = 721
        TabOrder = 1
        inherited btnOK: TBitBtn
          Left = 545
        end
        inherited btnCancel: TBitBtn
          Left = 633
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object WVDigitalEdit26: TWVDigitalEdit
        Left = 132
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
        TabOrder = 0
        TabStop = True
        Text = '0'
        Visible = False
        WorkView = WorkView
        FieldName = '商户编号'
        SynchronizeByValue = True
      end
      object grp1: TGroupBox
        Left = 48
        Top = 32
        Width = 617
        Height = 121
        Caption = '基本信息'
        TabOrder = 2
        object Label28: TLabel
          Left = 22
          Top = 26
          Width = 60
          Height = 12
          Caption = '省商户编号'
        end
        object Label27: TLabel
          Left = 222
          Top = 26
          Width = 60
          Height = 12
          Caption = '中心商户号'
        end
        object Label29: TLabel
          Left = 418
          Top = 26
          Width = 48
          Height = 12
          Caption = '商户名称'
        end
        object Label30: TLabel
          Left = 10
          Top = 59
          Width = 72
          Height = 12
          Caption = '商户英文名称'
        end
        object Label31: TLabel
          Left = 234
          Top = 59
          Width = 48
          Height = 12
          Caption = '商户简称'
        end
        object Label32: TLabel
          Left = 418
          Top = 59
          Width = 48
          Height = 12
          Caption = '商户类型'
        end
        object Label33: TLabel
          Left = 34
          Top = 93
          Width = 48
          Height = 12
          Caption = '行业类型'
        end
        object Label47: TLabel
          Left = 418
          Top = 93
          Width = 6
          Height = 12
          Caption = '%'
        end
        object Label41: TLabel
          Left = 234
          Top = 93
          Width = 48
          Height = 12
          Caption = '结算费率'
        end
        object WVEdit28: TWVEdit
          Left = 84
          Top = 21
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<省商户编号>'
          WorkView = WorkView
          FieldName = '省商户编号'
          SynchronizeWhenExit = True
        end
        object WVEdit27: TWVEdit
          Left = 284
          Top = 21
          Width = 125
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<中心商户号>'
          WorkView = WorkView
          FieldName = '中心商户号'
          SynchronizeWhenExit = True
        end
        object edtBusiName: TWVEdit
          Left = 468
          Top = 21
          Width = 141
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 2
          Text = '<商户名>'
          WorkView = WorkView
          FieldName = '商户名'
          SynchronizeWhenExit = True
        end
        object edtBusiEngName: TWVEdit
          Left = 84
          Top = 55
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 3
          Text = '<商户英文名称>'
          WorkView = WorkView
          FieldName = '商户英文名称'
          SynchronizeWhenExit = True
        end
        object WVEdit31: TWVEdit
          Left = 284
          Top = 55
          Width = 125
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 4
          Text = '<商户简称>'
          WorkView = WorkView
          FieldName = '商户简称'
          SynchronizeWhenExit = True
        end
        object WVEdit47: TWVEdit
          Left = 468
          Top = 113
          Width = 129
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 5
          Text = '<销户日期>'
          Visible = False
          WorkView = WorkView
          FieldName = '销户日期'
          SynchronizeWhenExit = True
        end
        object WVDigitalEdit41: TWVDigitalEdit
          Left = 284
          Top = 89
          Width = 125
          Height = 20
          AllowPoint = True
          AllowNegative = True
          UserSeprator = True
          Precision = 2
          MaxIntLen = 10
          Color = clInfoBk
          ParentColor = False
          TabOrder = 6
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '结算费率'
          SynchronizeByValue = True
        end
        object cbb1: TWVComboBox
          Left = 468
          Top = 54
          Width = 141
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 7
          WorkView = WorkView
          FieldName = '商户类型'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*216'
        end
        object WVComboBox3: TWVComboBox
          Left = 84
          Top = 89
          Width = 135
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 8
          WorkView = WorkView
          FieldName = '行业类型'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*217'
        end
      end
      object GroupBox1: TGroupBox
        Left = 48
        Top = 160
        Width = 617
        Height = 113
        Caption = '联系人信息'
        TabOrder = 3
        object Label34: TLabel
          Left = 46
          Top = 25
          Width = 36
          Height = 12
          Caption = '联系人'
        end
        object Label35: TLabel
          Left = 258
          Top = 25
          Width = 24
          Height = 12
          Caption = '电话'
        end
        object Label36: TLabel
          Left = 442
          Top = 25
          Width = 24
          Height = 12
          Caption = '手机'
        end
        object Label37: TLabel
          Left = 34
          Top = 55
          Width = 48
          Height = 12
          Caption = '电子信箱'
        end
        object Label38: TLabel
          Left = 258
          Top = 55
          Width = 24
          Height = 12
          Caption = '传真'
        end
        object Label39: TLabel
          Left = 34
          Top = 85
          Width = 48
          Height = 12
          Caption = '营业地址'
        end
        object Label40: TLabel
          Left = 418
          Top = 85
          Width = 48
          Height = 12
          Caption = '邮政编码'
        end
        object WVEdit34: TWVEdit
          Left = 84
          Top = 21
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<联系人>'
          WorkView = WorkView
          FieldName = '联系人'
          SynchronizeWhenExit = True
        end
        object WVEdit35: TWVEdit
          Left = 284
          Top = 21
          Width = 125
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<电话>'
          WorkView = WorkView
          FieldName = '电话'
          SynchronizeWhenExit = True
        end
        object WVEdit36: TWVEdit
          Left = 468
          Top = 21
          Width = 141
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 2
          Text = '<手机>'
          WorkView = WorkView
          FieldName = '手机'
          SynchronizeWhenExit = True
        end
        object WVEdit37: TWVEdit
          Left = 84
          Top = 51
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 3
          Text = '<电子信箱>'
          WorkView = WorkView
          FieldName = '电子信箱'
          SynchronizeWhenExit = True
        end
        object WVEdit38: TWVEdit
          Left = 284
          Top = 51
          Width = 125
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 4
          Text = '<传真>'
          WorkView = WorkView
          FieldName = '传真'
          SynchronizeWhenExit = True
        end
        object WVEdit39: TWVEdit
          Left = 84
          Top = 81
          Width = 325
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 5
          Text = '<营业地址>'
          WorkView = WorkView
          FieldName = '营业地址'
          SynchronizeWhenExit = True
        end
        object WVEdit40: TWVEdit
          Left = 468
          Top = 80
          Width = 141
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 6
          Text = '<邮政编码>'
          WorkView = WorkView
          FieldName = '邮政编码'
          SynchronizeWhenExit = True
        end
      end
      object grp2: TGroupBox
        Left = 48
        Top = 280
        Width = 617
        Height = 81
        Caption = '开户银行信息'
        TabOrder = 4
        object Label42: TLabel
          Left = 34
          Top = 21
          Width = 48
          Height = 12
          Caption = '开户银行'
        end
        object Label43: TLabel
          Left = 418
          Top = 21
          Width = 48
          Height = 12
          Caption = '银行账号'
        end
        object Label44: TLabel
          Left = 22
          Top = 53
          Width = 60
          Height = 12
          Caption = '银行帐户名'
        end
        object Label45: TLabel
          Left = 430
          Top = 53
          Width = 36
          Height = 12
          Caption = '联行号'
        end
        object WVEdit43: TWVEdit
          Left = 468
          Top = 17
          Width = 141
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<银行账号>'
          WorkView = WorkView
          FieldName = '银行账号'
          SynchronizeWhenExit = True
        end
        object WVEdit44: TWVEdit
          Left = 84
          Top = 49
          Width = 325
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 2
          Text = '<银行帐户名>'
          WorkView = WorkView
          FieldName = '银行帐户名'
          SynchronizeWhenExit = True
        end
        object WVEdit45: TWVEdit
          Left = 468
          Top = 49
          Width = 141
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<联行号>'
          WorkView = WorkView
          FieldName = '联行号'
          SynchronizeWhenExit = True
        end
        object edt1: TWVEdit
          Left = 84
          Top = 17
          Width = 325
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 3
          Text = '<开户银行>'
          WorkView = WorkView
          FieldName = '开户银行'
          SynchronizeWhenExit = True
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 492
    Top = 39
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
      end
      item
        Name = '查询.商户编号'
        Caption = '查询.商户编号'
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
        Name = '查询.中心商户号'
        Caption = '查询.中心商户号'
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
        Name = '查询.商户状态'
        Caption = '查询.商户状态'
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
        Name = '查询.省商户编号'
        Caption = '查询.省商户编号'
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
        Name = '查询.商户名'
        Caption = '查询.商户名'
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
        Name = '查询.商户英文名称'
        Caption = '查询.商户英文名称'
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
        Name = '查询.商户简称'
        Caption = '查询.商户简称'
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
        Name = '查询.商户类型'
        Caption = '查询.商户类型'
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
        Name = '查询.行业类型'
        Caption = '查询.行业类型'
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
        Name = '商户编号'
        Caption = '商户编号'
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
        Name = '中心商户号'
        Caption = '中心商户号'
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
        Name = '省商户编号'
        Caption = '省商户编号'
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
        DataField = 'sname2'
      end
      item
        Name = '商户名'
        Caption = '商户名'
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
        Name = '商户英文名称'
        Caption = '商户英文名称'
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
        DataField = 'snote2'
      end
      item
        Name = '商户简称'
        Caption = '商户简称'
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
        Name = '商户类型'
        Caption = '商户类型'
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
        Name = '行业类型'
        Caption = '行业类型'
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
        DataField = 'sbranch_code1'
      end
      item
        Name = '联系人'
        Caption = '联系人'
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
        DataField = 'sbankname'
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
        DataField = 'semail2'
      end
      item
        Name = '传真'
        Caption = '传真'
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
        DataField = 'sphone3'
      end
      item
        Name = '营业地址'
        Caption = '营业地址'
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
        Name = '邮政编码'
        Caption = '邮政编码'
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
        DataField = 'spost_code'
      end
      item
        Name = '结算费率'
        Caption = '结算费率'
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
        Name = '开户银行'
        Caption = '开户银行'
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
        Name = '银行账号'
        Caption = '银行账号'
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
        Name = '银行帐户名'
        Caption = '银行帐户名'
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
        DataField = 'sbankname2'
      end
      item
        Name = '联行号'
        Caption = '联行号'
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
        DataField = 'scert_no'
      end
      item
        Name = '开户日期'
        Caption = '开户日期'
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
        Name = '销户日期'
        Caption = '销户日期'
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
        Name = '销户状态'
        Caption = '销户状态'
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
        Name = '商户状态'
        Caption = '商户状态'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.操作标志|查询.商户编号|查询.中心商户号|查询.省商户编号|查' +
          '询.商户名|查询.商户英文名称|查询.商户简称|查询.商户类型|查询.行' +
          '业类型|查询.联系人|查询.电话|查询.手机|查询.电子信箱|查询.传真|' +
          '查询.营业地址|查询.邮政编码|查询.结算费率|查询.开户银行|查询.银' +
          '行账号|查询.银行帐户名|查询.联行号|查询.开户日期|查询.销户日期|' +
          '查询.销户状态|查询.商户状态|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|商户编号|中心商户号|省商户编号|商户名|商户英文名称|商户简称|商' +
          '户类型|行业类型|联系人|电话|手机|电子信箱|传真|营业地址|邮政编码' +
          '|结算费率|开户银行|银行账号|银行帐户名|联行号|开户日期|销户日期|' +
          '销户状态|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 368
    Top = 8
  end
  inherited QueryRequest: TWVRequest
    ID = '商户信息维护查询'
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
        ParamName = '商户编号'
        FieldName = '查询.商户编号'
      end
      item
        ParamName = '中心商户号'
        FieldName = '查询.中心商户号'
      end
      item
        ParamName = '商户状态'
        FieldName = '查询.商户状态'
      end
      item
        ParamName = '省商户编号'
        FieldName = '查询.省商户编号'
      end
      item
        ParamName = '商户名'
        FieldName = '查询.商户名'
      end
      item
        ParamName = '商户英文名称'
        FieldName = '查询.商户英文名称'
      end
      item
        ParamName = '商户简称'
        FieldName = '查询.商户简称'
      end
      item
        ParamName = '商户类型'
        FieldName = '查询.商户类型'
      end
      item
        ParamName = '行业类型'
        FieldName = '查询.行业类型'
      end>
    Left = 528
    Top = 8
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sbranch_code0'
        WVFieldName = '商户类型'
        DataPresentType = 'idobjects'
        DataPresentParam = '216'
      end
      item
        FieldName = 'sbranch_code1'
        WVFieldName = '行业类型'
        DataPresentType = 'idobjects'
        DataPresentParam = '217'
      end
      item
        FieldName = 'scust_auth'
        WVFieldName = '开户银行'
        DataPresentType = 'idobjects'
        DataPresentParam = '218'
      end
      item
        FieldName = 'sstatus1'
        WVFieldName = '商户状态'
        DataPresentType = 'idobjects'
        DataPresentParam = '224'
      end>
    Left = 412
    Top = 39
  end
  inherited AddRequest: TWVRequest
    ID = '商户信息维护'
    Bindings = <
      item
        ParamName = '商户编号'
        FieldName = '商户编号'
      end
      item
        ParamName = '中心商户号'
        FieldName = '中心商户号'
      end
      item
        ParamName = '省商户编号'
        FieldName = '省商户编号'
      end
      item
        ParamName = '商户名'
        FieldName = '商户名'
      end
      item
        ParamName = '商户英文名称'
        FieldName = '商户英文名称'
      end
      item
        ParamName = '商户简称'
        FieldName = '商户简称'
      end
      item
        ParamName = '商户类型'
        FieldName = '商户类型'
      end
      item
        ParamName = '行业类型'
        FieldName = '行业类型'
      end
      item
        ParamName = '联系人'
        FieldName = '联系人'
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
        ParamName = '传真'
        FieldName = '传真'
      end
      item
        ParamName = '营业地址'
        FieldName = '营业地址'
      end
      item
        ParamName = '邮政编码'
        FieldName = '邮政编码'
      end
      item
        ParamName = '结算费率'
        FieldName = '结算费率'
      end
      item
        ParamName = '开户银行'
        FieldName = '开户银行'
      end
      item
        ParamName = '银行账号'
        FieldName = '银行账号'
      end
      item
        ParamName = '银行帐户名'
        FieldName = '银行帐户名'
      end
      item
        ParamName = '联行号'
        FieldName = '联行号'
      end
      item
        ParamName = '开户日期'
        FieldName = '开户日期'
      end
      item
        ParamName = '销户日期'
        FieldName = '销户日期'
      end
      item
        ParamName = '销户状态'
        FieldName = '销户状态'
      end
      item
        ParamName = '商户状态'
        FieldName = '商户状态'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end>
    Left = 408
    Top = 8
  end
  inherited DeleteRequest: TWVRequest
    ID = '商户信息维护'
    Bindings = <
      item
        ParamName = '商户编号'
        FieldName = '商户编号'
      end
      item
        ParamName = '中心商户号'
        FieldName = '中心商户号'
      end
      item
        ParamName = '省商户编号'
        FieldName = '省商户编号'
      end
      item
        ParamName = '商户名'
        FieldName = '商户名'
      end
      item
        ParamName = '商户英文名称'
        FieldName = '商户英文名称'
      end
      item
        ParamName = '商户简称'
        FieldName = '商户简称'
      end
      item
        ParamName = '商户类型'
        FieldName = '商户类型'
      end
      item
        ParamName = '行业类型'
        FieldName = '行业类型'
      end
      item
        ParamName = '联系人'
        FieldName = '联系人'
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
        ParamName = '传真'
        FieldName = '传真'
      end
      item
        ParamName = '营业地址'
        FieldName = '营业地址'
      end
      item
        ParamName = '邮政编码'
        FieldName = '邮政编码'
      end
      item
        ParamName = '结算费率'
        FieldName = '结算费率'
      end
      item
        ParamName = '开户银行'
        FieldName = '开户银行'
      end
      item
        ParamName = '银行账号'
        FieldName = '银行账号'
      end
      item
        ParamName = '银行帐户名'
        FieldName = '银行帐户名'
      end
      item
        ParamName = '联行号'
        FieldName = '联行号'
      end
      item
        ParamName = '开户日期'
        FieldName = '开户日期'
      end
      item
        ParamName = '销户日期'
        FieldName = '销户日期'
      end
      item
        ParamName = '销户状态'
        FieldName = '销户状态'
      end
      item
        ParamName = '商户状态'
        FieldName = '商户状态'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end>
    Left = 448
    Top = 8
  end
  inherited ChangeRequest: TWVRequest
    ID = '商户信息维护'
    Bindings = <
      item
        ParamName = '商户编号'
        FieldName = '商户编号'
      end
      item
        ParamName = '中心商户号'
        FieldName = '中心商户号'
      end
      item
        ParamName = '省商户编号'
        FieldName = '省商户编号'
      end
      item
        ParamName = '商户名'
        FieldName = '商户名'
      end
      item
        ParamName = '商户英文名称'
        FieldName = '商户英文名称'
      end
      item
        ParamName = '商户简称'
        FieldName = '商户简称'
      end
      item
        ParamName = '商户类型'
        FieldName = '商户类型'
      end
      item
        ParamName = '行业类型'
        FieldName = '行业类型'
      end
      item
        ParamName = '联系人'
        FieldName = '联系人'
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
        ParamName = '传真'
        FieldName = '传真'
      end
      item
        ParamName = '营业地址'
        FieldName = '营业地址'
      end
      item
        ParamName = '邮政编码'
        FieldName = '邮政编码'
      end
      item
        ParamName = '结算费率'
        FieldName = '结算费率'
      end
      item
        ParamName = '开户银行'
        FieldName = '开户银行'
      end
      item
        ParamName = '银行账号'
        FieldName = '银行账号'
      end
      item
        ParamName = '银行帐户名'
        FieldName = '银行帐户名'
      end
      item
        ParamName = '联行号'
        FieldName = '联行号'
      end
      item
        ParamName = '开户日期'
        FieldName = '开户日期'
      end
      item
        ParamName = '销户日期'
        FieldName = '销户日期'
      end
      item
        ParamName = '销户状态'
        FieldName = '销户状态'
      end
      item
        ParamName = '商户状态'
        FieldName = '商户状态'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end>
    Left = 488
    Top = 8
  end
  inherited WVDataSource: TWVDataSource
    Left = 532
    Top = 39
  end
  inherited alDatasetActions: TActionList
    Left = 452
    Top = 36
  end
end
