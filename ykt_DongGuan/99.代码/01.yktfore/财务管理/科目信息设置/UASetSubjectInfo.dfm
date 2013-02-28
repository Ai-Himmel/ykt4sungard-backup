inherited faqhSetSubjectInfo: TfaqhSetSubjectInfo
  Width = 743
  Height = 511
  Caption = '商户组织结构设置'
  inherited pcPages: TRzPageControl
    Width = 743
    Height = 511
    ActivePage = tsQuery
    TabIndex = 0
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
      object Panel1: TPanel [1]
        Left = 0
        Top = 18
        Width = 739
        Height = 57
        Align = alTop
        ParentColor = True
        TabOrder = 2
        object Label1: TLabel
          Left = 14
          Top = 10
          Width = 48
          Height = 12
          Caption = '科目代码'
        end
        object Label25: TLabel
          Left = 214
          Top = 10
          Width = 36
          Height = 12
          Caption = '助记码'
        end
        object Label26: TLabel
          Left = 388
          Top = 10
          Width = 48
          Height = 12
          Caption = '科目级别'
        end
        object Label27: TLabel
          Left = 578
          Top = 9
          Width = 48
          Height = 12
          Caption = '科目类别'
        end
        object Label9: TLabel
          Left = 14
          Top = 34
          Width = 48
          Height = 12
          Caption = '科目性质'
        end
        object Label17: TLabel
          Left = 202
          Top = 33
          Width = 48
          Height = 12
          Caption = '余额方向'
        end
        object WVEdit2: TWVEdit
          Left = 254
          Top = 6
          Width = 120
          Height = 20
          Color = clWhite
          ImeName = '中文 (简体) - 微软拼音'
          ReadOnly = False
          TabOrder = 1
          Text = '<助记码Q>'
          WorkView = WorkView
          FieldName = '助记码Q'
          SynchronizeWhenExit = True
        end
        object WVComboBox8: TWVComboBox
          Left = 440
          Top = 6
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '科目级别Q'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*14'
        end
        object WVComboBox9: TWVComboBox
          Left = 628
          Top = 5
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '科目类别Q'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*29'
        end
        object edtBusiId: TWVEdit
          Left = 68
          Top = 6
          Width = 120
          Height = 20
          Color = clWhite
          ImeName = '中文 (简体) - 微软拼音'
          ReadOnly = False
          TabOrder = 0
          Text = '<科目代码Q>'
          WorkView = WorkView
          FieldName = '科目代码Q'
          SynchronizeWhenExit = True
        end
        object WVComboBox1: TWVComboBox
          Left = 68
          Top = 30
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '科目性质Q'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*31'
        end
        object WVComboBox2: TWVComboBox
          Left = 254
          Top = 29
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ImeName = '中文 (简体) - 微软拼音'
          ItemHeight = 12
          TabOrder = 5
          WorkView = WorkView
          FieldName = '余额方向Q'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*30'
        end
      end
      inherited UIPanel1: TUIPanel
        Top = 458
        Width = 739
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 478
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 564
        end
        inherited btnQuery: TBitBtn [2]
          Left = 392
        end
        inherited btnDelete: TBitBtn
          Left = 650
          Hint = '注销当前选中的条目'
          Caption = '注销(&D)'
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 98
          Width = 159
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 739
      end
      inherited Grid: TRzDBGrid
        Top = 75
        Width = 739
        Height = 383
        ImeName = ''
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        Columns = <
          item
            Expanded = False
            FieldName = 'Lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '序列号'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lserial0'
            PickList.Strings = ()
            Title.Caption = '上级序列号'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '科目代码'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '科目名称'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '科目全称'
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '助记码'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '科目级别'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '科目类别'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '科目性质'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '余额方向'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol5'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '是否末级'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol6'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '现金类科目'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol7'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '银行类科目'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol8'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '一卡通科目'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'Lvol9'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '是否删除'
            Width = 80
            Visible = True
          end>
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 166
        Top = 74
        Width = 48
        Height = 12
        Caption = '科目代码'
      end
      object Label3: TLabel [1]
        Left = 166
        Top = 213
        Width = 48
        Height = 12
        Caption = '科目性质'
      end
      object Label4: TLabel [2]
        Left = 178
        Top = 143
        Width = 36
        Height = 12
        Caption = '助记码'
      end
      object Label5: TLabel [3]
        Left = 166
        Top = 247
        Width = 48
        Height = 12
        Caption = '余额方向'
      end
      object Label6: TLabel [4]
        Left = 166
        Top = 282
        Width = 48
        Height = 12
        Caption = '是否末级'
      end
      object Label7: TLabel [5]
        Left = 166
        Top = 178
        Width = 48
        Height = 12
        Caption = '科目类别'
      end
      object Label8: TLabel [6]
        Left = 178
        Top = 40
        Width = 36
        Height = 12
        Caption = '序列号'
        Visible = False
      end
      object Label11: TLabel [7]
        Left = 166
        Top = 109
        Width = 48
        Height = 12
        Caption = '科目名称'
      end
      object Label12: TLabel [8]
        Left = 142
        Top = 317
        Width = 72
        Height = 12
        Caption = '是否现金科目'
      end
      object Label13: TLabel [9]
        Left = 142
        Top = 351
        Width = 72
        Height = 12
        Caption = '是否银行科目'
      end
      object Label14: TLabel [10]
        Left = 130
        Top = 386
        Width = 84
        Height = 12
        Caption = '是否一卡通科目'
        Visible = False
      end
      inherited UIPanel2: TUIPanel
        Top = 452
        Width = 739
        TabOrder = 11
        inherited btnOK: TBitBtn
          Left = 507
        end
        inherited btnCancel: TBitBtn
          Left = 603
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object WVComboBox3: TWVComboBox
        Left = 220
        Top = 209
        Width = 120
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 5
        WorkView = WorkView
        FieldName = '科目性质'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*31'
      end
      object edtSubjNo: TWVEdit
        Left = 220
        Top = 70
        Width = 120
        Height = 20
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ReadOnly = False
        TabOrder = 1
        Text = '<科目代码>'
        WorkView = WorkView
        FieldName = '科目代码'
        SynchronizeWhenExit = True
      end
      object WVComboBox4: TWVComboBox
        Left = 220
        Top = 243
        Width = 120
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 6
        WorkView = WorkView
        FieldName = '余额方向'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*30'
      end
      object WVEdit3: TWVEdit
        Left = 220
        Top = 139
        Width = 120
        Height = 20
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ReadOnly = False
        TabOrder = 3
        Text = '<助记码>'
        WorkView = WorkView
        FieldName = '助记码'
        SynchronizeWhenExit = True
      end
      object WVComboBox5: TWVComboBox
        Left = 220
        Top = 278
        Width = 120
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 7
        WorkView = WorkView
        FieldName = '是否末级'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object WVComboBox6: TWVComboBox
        Left = 220
        Top = 174
        Width = 120
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 4
        WorkView = WorkView
        FieldName = '科目类别'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*29'
      end
      object edtId: TWVEdit
        Left = 220
        Top = 36
        Width = 120
        Height = 20
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        MaxLength = 22
        ReadOnly = False
        TabOrder = 0
        Text = '<序列号>'
        Visible = False
        WorkView = WorkView
        FieldName = '序列号'
        SynchronizeWhenExit = True
      end
      object edtSubjName: TWVEdit
        Left = 220
        Top = 105
        Width = 120
        Height = 20
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ReadOnly = False
        TabOrder = 2
        Text = '<科目名称>'
        WorkView = WorkView
        FieldName = '科目名称'
        SynchronizeWhenExit = True
      end
      object WVComboBox7: TWVComboBox
        Left = 220
        Top = 313
        Width = 120
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 8
        WorkView = WorkView
        FieldName = '现金科目'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object WVComboBox10: TWVComboBox
        Left = 220
        Top = 347
        Width = 120
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 9
        WorkView = WorkView
        FieldName = '银行科目'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object WVComboBox11: TWVComboBox
        Left = 220
        Top = 382
        Width = 120
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        ItemHeight = 12
        TabOrder = 10
        Visible = False
        WorkView = WorkView
        FieldName = '一卡通科目'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 564
    Top = 327
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
        Name = '标志'
        Caption = '标志'
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
        Name = '科目代码Q'
        Caption = '科目代码Q'
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
        Name = '助记码Q'
        Caption = '助记码Q'
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
        Name = '科目级别Q'
        Caption = '科目级别Q'
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
        Name = '科目类别Q'
        Caption = '科目类别Q'
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
        Name = '科目性质Q'
        Caption = '科目性质Q'
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
        Name = '余额方向Q'
        Caption = '余额方向Q'
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
        Name = '科目代码'
        Caption = '科目代码'
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
        Name = '科目名称'
        Caption = '科目名称'
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
        DataField = 'sall_name'
      end
      item
        Name = '助记码'
        Caption = '助记码'
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
        DataField = 'sname'
      end
      item
        Name = '科目类别'
        Caption = '科目类别'
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
        Name = '科目性质'
        Caption = '科目性质'
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
        Name = '余额方向'
        Caption = '余额方向'
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
        Name = '是否末级'
        Caption = '是否末级'
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
        DataField = 'lvol5'
      end
      item
        Name = '现金科目'
        Caption = '现金科目'
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
        Name = '银行科目'
        Caption = '银行科目'
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
        Name = '一卡通科目'
        Caption = '一卡通科目'
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
        DataField = 'lvol8'
      end
      item
        Name = '是否删除'
        Caption = '是否删除'
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
        DataField = 'lvol9'
      end
      item
        Name = '序列号'
        Caption = '序列号'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|商户标识|父商户标识|商户名称|商户类别|是否为独立核算|是否为叶节' +
          '点|商户状态|负责人姓名|是否收取管理费|校区|联系人班级或部门号|帐' +
          '户密码|'
      end>
    Left = 536
    Top = 296
  end
  inherited QueryRequest: TWVRequest
    ID = '科目信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '科目代码'
        FieldName = '科目代码Q'
      end
      item
        ParamName = '助记码'
        FieldName = '助记码Q'
      end
      item
        ParamName = '科目级别'
        FieldName = '科目级别Q'
      end
      item
        ParamName = '科目类别'
        FieldName = '科目类别Q'
      end
      item
        ParamName = '科目性质'
        FieldName = '科目性质Q'
      end
      item
        ParamName = '余额方向'
        FieldName = '余额方向Q'
      end>
    Left = 568
    Top = 296
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '29'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '31'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '30'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol6'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol7'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol8'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol9'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end>
    Left = 596
    Top = 327
  end
  inherited AddRequest: TWVRequest
    ID = '科目信息设置'
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
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '科目代码'
        FieldName = '科目代码'
      end
      item
        ParamName = '科目名称'
        FieldName = '科目名称'
      end
      item
        ParamName = '助记码'
        FieldName = '助记码'
      end
      item
        ParamName = '科目类别'
        FieldName = '科目类别'
      end
      item
        ParamName = '科目性质'
        FieldName = '科目性质'
      end
      item
        ParamName = '余额方向'
        FieldName = '余额方向'
      end
      item
        ParamName = '是否末级'
        FieldName = '是否末级'
      end
      item
        ParamName = '现金科目'
        FieldName = '现金科目'
      end
      item
        ParamName = '银行科目'
        FieldName = '银行科目'
      end
      item
        ParamName = '一卡通科目'
        FieldName = '一卡通科目'
      end>
    Left = 600
    Top = 296
  end
  inherited DeleteRequest: TWVRequest
    ID = '科目信息设置'
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
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '序列号'
        FieldName = '序列号'
      end
      item
        ParamName = '科目代码'
        FieldName = '科目代码'
      end
      item
        ParamName = '科目名称'
        FieldName = '科目名称'
      end
      item
        ParamName = '助记码'
        FieldName = '助记码'
      end
      item
        ParamName = '科目类别'
        FieldName = '科目类别'
      end
      item
        ParamName = '科目性质'
        FieldName = '科目性质'
      end
      item
        ParamName = '余额方向'
        FieldName = '余额方向'
      end
      item
        ParamName = '是否末级'
        FieldName = '是否末级'
      end
      item
        ParamName = '现金科目'
        FieldName = '现金科目'
      end
      item
        ParamName = '银行科目'
        FieldName = '银行科目'
      end
      item
        ParamName = '一卡通科目'
        FieldName = '一卡通科目'
      end>
    Left = 632
    Top = 296
  end
  inherited ChangeRequest: TWVRequest
    ID = '科目信息设置'
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
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '序列号'
        FieldName = '序列号'
      end
      item
        ParamName = '科目代码'
        FieldName = '科目代码'
      end
      item
        ParamName = '科目名称'
        FieldName = '科目名称'
      end
      item
        ParamName = '助记码'
        FieldName = '助记码'
      end
      item
        ParamName = '科目类别'
        FieldName = '科目类别'
      end
      item
        ParamName = '科目性质'
        FieldName = '科目性质'
      end
      item
        ParamName = '余额方向'
        FieldName = '余额方向'
      end
      item
        ParamName = '是否末级'
        FieldName = '是否末级'
      end
      item
        ParamName = '现金科目'
        FieldName = '现金科目'
      end
      item
        ParamName = '银行科目'
        FieldName = '银行科目'
      end
      item
        ParamName = '一卡通科目'
        FieldName = '一卡通科目'
      end>
    Left = 664
    Top = 296
  end
  inherited WVDataSource: TWVDataSource
    Left = 664
    Top = 328
  end
  inherited alDatasetActions: TActionList
    Left = 628
    Top = 328
  end
end
