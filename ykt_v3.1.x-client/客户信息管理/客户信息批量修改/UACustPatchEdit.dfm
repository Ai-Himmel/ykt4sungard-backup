inherited faqhCustPatchEdit: TfaqhCustPatchEdit
  Width = 752
  Height = 536
  inherited UIPanel1: TUIPanel
    Top = 379
    Width = 752
    Height = 157
    TabOrder = 4
    object Label11: TLabel [0]
      Left = 80
      Top = 103
      Width = 48
      Height = 12
      Caption = '表单名称'
    end
    inherited btnQuery: TBitBtn
      Left = 577
      Top = 97
      Enabled = False
      TabOrder = 4
    end
    inherited btnPrint: TBitBtn
      Left = 14
      Top = 10000
      TabOrder = 9
      Visible = False
    end
    object edtSheetName: TEdit
      Left = 136
      Top = 99
      Width = 77
      Height = 20
      TabOrder = 6
      Text = 'sheet1'
    end
    object btnSelectFile: TBitBtn
      Left = 219
      Top = 97
      Width = 85
      Height = 25
      Hint = '冻结校园卡'
      Caption = '选择文件'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnSelectFileClick
    end
    object btnImportQuery: TBitBtn
      Left = 307
      Top = 97
      Width = 85
      Height = 25
      Hint = '导入查询'
      Caption = '导入查询'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnImportQueryClick
    end
    object btnClear: TBitBtn
      Left = 396
      Top = 97
      Width = 85
      Height = 25
      Hint = '导入查询'
      Caption = '清空列表'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnClearClick
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 136
      Width = 752
      Height = 21
      AutoStyle = False
      BorderColor = clWindow
      BorderInner = fsNone
      BorderOuter = fsNone
      BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
      BorderWidth = 0
      Color = 16184303
      FlatColor = 15458000
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 8
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 752
        Height = 21
        FrameStyle = fsStatus
        Align = alClient
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object chkSelect: TCheckBox
      Left = 8
      Top = 100
      Width = 45
      Height = 17
      Caption = '全选'
      TabOrder = 7
      OnClick = chkSelectClick
    end
    object grp1: TGroupBox
      Left = 0
      Top = 0
      Width = 752
      Height = 89
      Hint = '把需要修改的内容打钩'
      Align = alTop
      Caption = '修改信息'
      TabOrder = 0
      object chkCustType: TCheckBox
        Left = 40
        Top = 16
        Width = 65
        Height = 17
        Alignment = taLeftJustify
        Caption = '客户类别'
        TabOrder = 3
      end
      object chkFeeType: TCheckBox
        Left = 40
        Top = 40
        Width = 65
        Height = 17
        Alignment = taLeftJustify
        Caption = '收费类别'
        TabOrder = 10
      end
      object chkArea: TCheckBox
        Left = 288
        Top = 16
        Width = 41
        Height = 17
        Alignment = taLeftJustify
        Caption = '校区'
        TabOrder = 4
      end
      object chkDept: TCheckBox
        Left = 264
        Top = 40
        Width = 65
        Height = 17
        Alignment = taLeftJustify
        Caption = '所属部门'
        TabOrder = 11
      end
      object chkDestoryTime: TCheckBox
        Left = 40
        Top = 64
        Width = 65
        Height = 17
        Alignment = taLeftJustify
        Caption = '有效日期'
        TabOrder = 14
      end
      object chkClass: TCheckBox
        Left = 520
        Top = 16
        Width = 41
        Height = 17
        Alignment = taLeftJustify
        Caption = '班级'
        TabOrder = 5
      end
      object cbbCustType: TWVComboBox
        Left = 113
        Top = 14
        Width = 142
        Height = 20
        Style = csDropDownList
        Color = clBtnHighlight
        DropDownCount = 20
        ItemHeight = 12
        TabOrder = 0
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-34'
      end
      object cbbFeeType: TWVComboBox
        Left = 113
        Top = 37
        Width = 142
        Height = 20
        Style = csDropDownList
        Color = clBtnHighlight
        DropDownCount = 20
        ItemHeight = 12
        TabOrder = 6
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-43'
      end
      object cbbArea: TWVComboBox
        Left = 338
        Top = 14
        Width = 142
        Height = 20
        Style = csDropDownList
        Color = clBtnHighlight
        DropDownCount = 20
        ItemHeight = 12
        TabOrder = 1
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-27'
      end
      object cbbDept: TWVComboBox
        Left = 322
        Top = 37
        Width = 142
        Height = 20
        Style = csDropDownList
        Color = clBtnHighlight
        DropDownCount = 20
        ItemHeight = 12
        TabOrder = 7
        Visible = False
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-22'
      end
      object edtClass: TWVEdit
        Left = 568
        Top = 14
        Width = 145
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 2
      end
      object edtDestoryTime: TWVEdit
        Left = 113
        Top = 61
        Width = 142
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 13
      end
      object cbb2: TKSFilterComboBox
        Left = 338
        Top = 37
        Width = 142
        Height = 22
        ListFont.Charset = GB2312_CHARSET
        ListFont.Color = clWindowText
        ListFont.Height = -12
        ListFont.Name = '宋体'
        ListFont.Style = []
        OnFilterItems = cbb2FilterItems
        TabOrder = 8
      end
      object chkSpec: TCheckBox
        Left = 520
        Top = 40
        Width = 41
        Height = 17
        Alignment = taLeftJustify
        Caption = '专业'
        TabOrder = 12
      end
      object cbbSpec: TWVComboBox
        Left = 568
        Top = 37
        Width = 145
        Height = 20
        Style = csDropDownList
        Color = clBtnHighlight
        DropDownCount = 20
        ItemHeight = 12
        TabOrder = 9
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-23'
      end
    end
    object btnPatchEdit: TBitBtn
      Left = 660
      Top = 97
      Width = 85
      Height = 25
      Hint = '批量修改'
      Anchors = [akTop, akRight]
      Caption = '批量修改'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = btnPatchEditClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 752
    inherited Image1: TImage
      Width = 752
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 752
    Height = 127
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object WVLabel2: TWVLabel
      Left = 64
      Top = 15
      Width = 36
      Height = 12
      Caption = '客户号'
    end
    object Label1: TLabel
      Left = 52
      Top = 39
      Width = 48
      Height = 12
      Caption = '客户类别'
    end
    object Label8: TLabel
      Left = 76
      Top = 63
      Width = 24
      Height = 12
      Caption = '性别'
    end
    object Label10: TLabel
      Left = 52
      Top = 87
      Width = 48
      Height = 12
      Caption = '证件号码'
    end
    object Label3: TLabel
      Left = 301
      Top = 87
      Width = 24
      Height = 12
      Caption = '校区'
    end
    object WVLabel1: TWVLabel
      Left = 493
      Top = 63
      Width = 36
      Height = 12
      Caption = '批次号'
    end
    object Label9: TLabel
      Left = 504
      Top = 39
      Width = 24
      Height = 12
      Caption = '民族'
    end
    object Label5: TLabel
      Left = 283
      Top = 63
      Width = 42
      Height = 12
      Caption = '学/工号'
    end
    object Label13: TLabel
      Left = 277
      Top = 39
      Width = 48
      Height = 12
      Caption = '收费类别'
    end
    object Label4: TLabel
      Left = 277
      Top = 15
      Width = 48
      Height = 12
      Caption = '客户姓名'
    end
    object Label6: TLabel
      Left = 480
      Top = 15
      Width = 48
      Height = 12
      Caption = '所属部门'
    end
    object WVLabel3: TWVLabel
      Left = 504
      Top = 87
      Width = 24
      Height = 12
      Caption = '班级'
    end
    object WVEdit2: TWVEdit
      Left = 112
      Top = 10
      Width = 120
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<客户号>'
      WorkView = WorkView
      FieldName = '客户号'
    end
    object WVComboBox1: TWVComboBox
      Left = 112
      Top = 34
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 4
      WorkView = WorkView
      FieldName = '客户类别'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-34'
    end
    object WVComboBox8: TWVComboBox
      Left = 112
      Top = 58
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView
      FieldName = '联系人性别'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*39'
    end
    object WVEdit10: TWVEdit
      Left = 112
      Top = 82
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 10
      Text = '<联系人身份证号>'
      WorkView = WorkView
      FieldName = '联系人身份证号'
    end
    object WVComboBox3: TWVComboBox
      Left = 339
      Top = 82
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 11
      WorkView = WorkView
      FieldName = '客户所在区域'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-27'
    end
    object WVEdit1: TWVEdit
      Left = 541
      Top = 58
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 9
      Text = '<批次号>'
      WorkView = WorkView
      FieldName = '批次号'
    end
    object WVComboBox9: TWVComboBox
      Left = 541
      Top = 34
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView
      FieldName = '联系人民族'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*2001'
    end
    object WVEdit5: TWVEdit
      Left = 339
      Top = 58
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 8
      Text = '<联系人学工号>'
      WorkView = WorkView
      FieldName = '联系人学工号'
    end
    object WVComboBox4: TWVComboBox
      Left = 339
      Top = 34
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '收费类别'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-43'
    end
    object WVEdit4: TWVEdit
      Left = 339
      Top = 10
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<客户名称>'
      WorkView = WorkView
      FieldName = '客户名称'
    end
    object cbbQDept: TWVComboBox
      Left = 541
      Top = 10
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      Visible = False
      WorkView = WorkView
      FieldName = '联系人单位号'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object WVEdit3: TWVEdit
      Left = 541
      Top = 82
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 12
      Text = '<班级>'
      WorkView = WorkView
      FieldName = '班级'
    end
    object chkFilter: TCheckBox
      Left = 112
      Top = 104
      Width = 169
      Height = 17
      Caption = '过滤掉列表中重复的记录'
      TabOrder = 13
    end
    object cbb1: TKSFilterComboBox
      Left = 540
      Top = 9
      Width = 144
      Height = 22
      ListFont.Charset = GB2312_CHARSET
      ListFont.Color = clWindowText
      ListFont.Height = -12
      ListFont.Name = '宋体'
      ListFont.Style = []
      OnFilterItems = cbb1FilterItems
      TabOrder = 3
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 145
    Width = 752
    Height = 234
    TabOrder = 3
    inherited Grid: TRzDBGrid
      Width = 752
      Height = 234
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '校区'
          Width = 91
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户名称'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smarket_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '性别'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户类别'
          Width = 61
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '收费类别'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '所属部门'
          Width = 128
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '专业'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户状态'
          Width = 57
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户号'
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spager'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '注册时间'
          Width = 103
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '所在部门'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Caption = '班级'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '联系人'
          Width = 75
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '身份证号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '民族'
          Width = 71
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '预计注销时间'
          Width = 92
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '学/工号'
          Width = 76
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scusttypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '联系地址'
          Width = 229
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '联系电话'
          Width = 109
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ssectypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '备注'
          Width = 270
          Visible = True
        end>
    end
  end
  object lv1: TListView [4]
    Left = 0
    Top = 145
    Width = 752
    Height = 234
    Align = alClient
    Checkboxes = True
    Columns = <
      item
        Caption = '客户号'
        Width = 70
      end
      item
        Caption = '学/工号'
        Width = 70
      end
      item
        Caption = '校区'
        Width = 91
      end
      item
        Caption = '客户姓名'
        Width = 70
      end
      item
        Caption = '性别'
        Width = 60
      end
      item
        Caption = '客户类别'
        Width = 100
      end
      item
        Caption = '收费类别'
        Width = 60
      end
      item
        Caption = '所属部门'
        Width = 130
      end
      item
        Caption = '专业'
        Width = 70
      end
      item
        Caption = '班级'
        Width = 60
      end
      item
        Caption = '证件类型'
        Width = 70
      end
      item
        Caption = '证件号码'
        Width = 120
      end
      item
        Caption = '民族'
        Width = 71
      end
      item
        Caption = '有效日期'
        Width = 90
      end
      item
        Caption = '联系电话'
        Width = 60
      end
      item
        Caption = '联系地址'
        Width = 120
      end>
    ColumnClick = False
    FlatScrollBars = True
    GridLines = True
    RowSelect = True
    TabOrder = 2
    ViewStyle = vsReport
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        Caption = '查询结果集'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtObject
        OwnObject = True
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
        Name = '客户号'
        Caption = '客户号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
      end
      item
        Name = '客户名称'
        Caption = '客户名称'
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
      end
      item
        Name = '客户状态'
        Caption = '客户状态'
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
      end
      item
        Name = '客户类别'
        Caption = '客户类别'
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
      end
      item
        Name = '收费类别'
        Caption = '收费类别'
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
      end
      item
        Name = '联系人单位号'
        Caption = '联系人单位号'
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
      end
      item
        Name = '联系人性别'
        Caption = '联系人性别'
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
      end
      item
        Name = '联系人学工号'
        Caption = '联系人学工号'
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
      end
      item
        Name = '联系人民族'
        Caption = '联系人民族'
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
      end
      item
        Name = '联系人身份证号'
        Caption = '联系人身份证号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
      end
      item
        Name = '客户所在区域'
        Caption = '客户所在区域'
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
      end
      item
        Name = '批次号'
        Caption = '批次号'
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
      end
      item
        Name = '班级'
        Caption = '班级'
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
      end
      item
        Name = '交易类型'
        Caption = '交易类型'
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
        MonitorValueChangedFields = 
          '|客户类别|客户状态|地区|客户名称|联系人学号或员工号|联系人班级或' +
          '部门|联系人姓名|联系人性别|联系人民族代码|联系人身份证号|联系电' +
          '话|联系地址|注册时间|预计注销时间|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 84
    Top = 319
  end
  inherited MainRequest: TWVRequest
    ID = '客户信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
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
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '客户名称'
        FieldName = '客户名称'
      end
      item
        ParamName = '客户状态'
        FieldName = '客户状态'
      end
      item
        ParamName = '客户类别'
        FieldName = '客户类别'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '联系人单位号'
        FieldName = '联系人单位号'
      end
      item
        ParamName = '联系人性别'
        FieldName = '联系人性别'
      end
      item
        ParamName = '联系人学工号'
        FieldName = '联系人学工号'
      end
      item
        ParamName = '联系人民族'
        FieldName = '联系人民族'
      end
      item
        ParamName = '联系人身份证号'
        FieldName = '联系人身份证号'
      end
      item
        ParamName = '客户所在区域'
        FieldName = '客户所在区域'
      end
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end
      item
        ParamName = '班级'
        FieldName = '班级'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 120
    Top = 320
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-34'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '15'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2001'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '39'
      end
      item
        FieldName = 'scust_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'scust_no2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-23'
      end>
    Left = 192
    Top = 320
  end
  inherited DataSource: TDataSource
    Top = 320
  end
  object dlgOpen: TOpenDialog
    Left = 88
    Top = 352
  end
  object conSource: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\Documents and Se' +
      'ttings\Administrator\桌面\新建 Microsoft Office Access 应用程序.' +
      'mdb;Persist Security Info=False'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 144
    Top = 352
  end
  object qrySource: TADOQuery
    Connection = conSource
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from sheet1')
    Left = 184
    Top = 352
  end
  object ChangeRequest: TWVRequest
    WorkView = WorkView1
    ID = '客户信息设置'
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
        ParamName = '客户类别'
        FieldName = '客户类别'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '客户所在区域'
        FieldName = '客户所在区域'
      end
      item
        ParamName = '预计注销时间'
        FieldName = '预计注销时间'
      end
      item
        ParamName = '联系人班级或部门号'
        FieldName = '联系人班级或部门号'
      end
      item
        ParamName = '联系人班级或部门名称'
        FieldName = '联系人班级或部门名称'
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '联系人性别'
        FieldName = '联系人性别'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end
      item
        ParamName = '批量标志'
        FieldName = '批量标志'
      end
      item
        ParamName = '专业'
        FieldName = '专业'
      end>
    Left = 128
    Top = 256
  end
  object WorkView1: TWorkView
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
        Name = '客户类别'
        Caption = '客户类别'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lvol3'
      end
      item
        Name = '收费类别'
        Caption = '收费类别'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lvol5'
      end
      item
        Name = '客户所在区域'
        Caption = '客户所在区域'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '预计注销时间'
        Caption = '预计注销时间'
        FieldType = wftUndefined
        DomainName = '日期校验'
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
        DataField = 'sphone3'
      end
      item
        Name = '联系人班级或部门号'
        Caption = '联系人班级或部门号'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'scert_no'
      end
      item
        Name = '联系人班级或部门名称'
        Caption = '联系人班级或部门名称'
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
        Name = '客户号'
        Caption = '客户号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lvol1'
      end
      item
        Name = '联系人性别'
        Caption = '联系人性别'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'smarket_code'
      end
      item
        Name = '交易类型'
        Caption = '交易类型'
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
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '专业'
        Caption = '专业'
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
    FieldsMonitors = <>
    InvalidColor = clBtnHighlight
    Left = 88
    Top = 256
  end
end
