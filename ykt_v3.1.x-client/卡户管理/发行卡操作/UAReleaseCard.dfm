inherited faqhReleaseCard: TfaqhReleaseCard
  Width = 750
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 405
    Width = 750
    Height = 84
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 575
      Top = 34
      Width = 81
      TabOrder = 2
    end
    inherited btnPrint: TBitBtn
      Left = -25
      Top = 10
      Height = 22
      Visible = False
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 63
      Width = 750
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
      TabOrder = 4
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 750
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
    object btnReleaseCard: TBitBtn
      Left = 664
      Top = 34
      Width = 81
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '卡发行'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnReleaseCardClick
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00000000000000
        0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000000063FFFF0063FF
        FF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00000000000000000029FFFF0063FFFF0094FFFF00000000000000
        000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
        00000000000029FFFF0063FFFF0063FFFF0063FFFF0094FFFF0094FFFF0094FF
        FF0094FFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00000000000000
        000063FFFF0063FFFF0063FFFF0063FFFF0063FFFF0094FFFF0094FFFF0094FF
        FF0094FFFF00CEFFFF0000000000FFFFFF00FFFFFF00FFFFFF000000000063FF
        FF0063FFFF0063FFFF0063FFFF0063FFFF0094FFFF0094FFFF0094FFFF0094FF
        FF00CEFFFF00CEFFFF00CEFFFF0000000000FFFFFF00FFFFFF000000000063FF
        FF0063FFFF0063FFFF0063FFFF0063FFFF0094FFFF0094FFFF0094FFFF0094FF
        FF00CEFFFF00C6D6EF00BDBDBD009494940000000000FFFFFF00FFFFFF000000
        000063FFFF0063FFFF0063FFFF0094FFFF0094FFFF0094FFFF0094FFFF00CEFF
        FF00C6D6EF0084848400949494009494940063949400FFFFFF00FFFFFF00FFFF
        FF000000000063FFFF0063FFFF0094FFFF0094FFFF0094FFFF00CEFFFF00C6D6
        EF0073737300313131005A5A5A009494940084848400BDBDBD00FFFFFF00FFFF
        FF00FFFFFF000000000063FFFF0094FFFF0094FFFF0094FFFF00CEFFFF007373
        73006363290063630000632900006329290052525200ADADAD00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF000000000063FFFF0094FFFF0094FFFF0094CEFF006363
        2900CECE630094630000946300006363000052525200FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF000000000063FFFF0094FFFF00CEFFFF00C6D6EF007373
        730063632900CE9429009463000063290000BDBDBD00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF000000000063FFFF00CEFFFF0000000000BDBD
        BD00313131009463000029290000ADADAD00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF000000000063FFFF0000000000FFFFFF00BDBD
        BD000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF000000
        0000CECE2900FFFF9400FFFF63000000000000000000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00000000000000000000000000FFFFFF00FFFFFF00FFFFFF00}
    end
    object grpReleaseCard: TGroupBox
      Left = 0
      Top = 0
      Width = 441
      Height = 63
      Hint = '发卡相关参数设置'
      Align = alLeft
      Caption = '发卡相关参数'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      object WVLabel11: TWVLabel
        Left = 8
        Top = 18
        Width = 48
        Height = 12
        Caption = '收费方式'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label10: TLabel
        Left = 176
        Top = 18
        Width = 48
        Height = 12
        Caption = '票据号码'
      end
      object Label4: TLabel
        Left = 200
        Top = 42
        Width = 24
        Height = 12
        Caption = '金额'
      end
      object Label8: TLabel
        Left = 350
        Top = 42
        Width = 12
        Height = 12
        Caption = '元'
      end
      object lblMoney: TLabel
        Left = 7
        Top = 43
        Width = 48
        Height = 12
        Caption = '卡有效期'
      end
      object cbbType: TWVComboBox
        Left = 60
        Top = 14
        Width = 112
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 0
        OnChange = cbbTypeChange
        FieldName = '充值类型'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '63'
      end
      object edtTicketNo: TWVEdit
        Left = 228
        Top = 14
        Width = 120
        Height = 20
        Color = clWhite
        MaxLength = 20
        ReadOnly = False
        TabOrder = 1
      end
      object edtEndDate: TWVEdit
        Left = 60
        Top = 38
        Width = 112
        Height = 20
        Color = clWhite
        MaxLength = 8
        ReadOnly = False
        TabOrder = 3
      end
      object edtmoney: TWVDigitalEdit
        Left = 228
        Top = 37
        Width = 120
        Height = 19
        AllowPoint = True
        Precision = 2
        MaxIntLen = 12
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        TabOrder = 2
        TabStop = True
        Text = '0'
        WorkView = WVReleaseCard
        FieldName = '收费金额'
        SynchronizeByValue = True
      end
      object chkSaveMoney: TCheckBox
        Left = 364
        Top = 39
        Width = 69
        Height = 17
        Caption = '保存金额'
        TabOrder = 4
      end
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 750
    inherited Image1: TImage
      Width = 750
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 750
    Height = 127
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 44
      Top = 9
      Width = 36
      Height = 12
      Caption = '客户号'
    end
    object Label2: TLabel
      Left = 255
      Top = 9
      Width = 42
      Height = 12
      Caption = '学/工号'
    end
    object Label3: TLabel
      Left = 249
      Top = 33
      Width = 48
      Height = 12
      Caption = '证件号码'
    end
    object Label5: TLabel
      Left = 249
      Top = 80
      Width = 48
      Height = 12
      Caption = '注册日期'
    end
    object Label6: TLabel
      Left = 262
      Top = 103
      Width = 36
      Height = 12
      Caption = '批次号'
    end
    object WVLabel5: TWVLabel
      Left = 470
      Top = 33
      Width = 48
      Height = 12
      Caption = '客户类别'
    end
    object WVLabel1: TWVLabel
      Left = 249
      Top = 56
      Width = 48
      Height = 12
      Caption = '所属区域'
    end
    object WVLabel6: TWVLabel
      Left = 32
      Top = 33
      Width = 48
      Height = 12
      Caption = '证件类型'
    end
    object WVLabel2: TWVLabel
      Left = 32
      Top = 56
      Width = 48
      Height = 12
      Caption = '收费类别'
    end
    object Label7: TLabel
      Left = 470
      Top = 9
      Width = 48
      Height = 12
      Caption = '客户姓名'
    end
    object WVLabel8: TWVLabel
      Left = 470
      Top = 57
      Width = 48
      Height = 12
      Caption = '所属部门'
    end
    object WVLabel9: TWVLabel
      Left = 56
      Top = 80
      Width = 24
      Height = 12
      Caption = '专业'
    end
    object Label9: TLabel
      Left = 56
      Top = 103
      Width = 24
      Height = 12
      Caption = '班级'
    end
    object WVLabel7: TWVLabel
      Left = 471
      Top = 82
      Width = 48
      Height = 12
      Caption = '发卡类别'
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object WVEdit1: TWVEdit
      Left = 86
      Top = 5
      Width = 125
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<客户号>'
      WorkView = WorkView
      FieldName = '客户号'
    end
    object WVEdit2: TWVEdit
      Left = 304
      Top = 5
      Width = 125
      Height = 20
      CharCase = ecUpperCase
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<学工号>'
      WorkView = WorkView
      FieldName = '学工号'
    end
    object WVEdit3: TWVEdit
      Left = 304
      Top = 29
      Width = 125
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 4
      Text = '<证件号码>'
      WorkView = WorkView
      FieldName = '证件号码'
    end
    object WVEdit5: TWVEdit
      Left = 304
      Top = 76
      Width = 125
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 10
      Text = '<注销日期>'
      WorkView = WorkView
      FieldName = '注销日期'
    end
    object WVEdit6: TWVEdit
      Left = 304
      Top = 99
      Width = 125
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 13
      Text = '<导入批次号>'
      WorkView = WorkView
      FieldName = '导入批次号'
    end
    object WVComboBox6: TWVComboBox
      Left = 526
      Top = 29
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '客户类别'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-34'
    end
    object WVComboBox2: TWVComboBox
      Left = 304
      Top = 52
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView
      FieldName = '所属区域'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-27'
    end
    object WVComboBox1: TWVComboBox
      Left = 86
      Top = 28
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '证件类型'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*87'
    end
    object WVComboBox3: TWVComboBox
      Left = 86
      Top = 51
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView
      FieldName = '收费类别'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-43'
    end
    object WVEdit8: TWVEdit
      Left = 526
      Top = 5
      Width = 125
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<客户姓名>'
      WorkView = WorkView
      FieldName = '客户姓名'
    end
    object WVComboBox5: TWVComboBox
      Left = 526
      Top = 53
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 8
      WorkView = WorkView
      FieldName = '部门'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object WVComboBox7: TWVComboBox
      Left = 86
      Top = 75
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 9
      WorkView = WorkView
      FieldName = '专业'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-23'
    end
    object WVEdit4: TWVEdit
      Left = 86
      Top = 99
      Width = 125
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 12
      Text = '<班级>'
      WorkView = WorkView
      FieldName = '班级'
    end
    object cbbCardType: TWVComboBox
      Left = 526
      Top = 78
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 11
      OnChange = cbbCardTypeChange
      WorkView = WorkView
      FieldName = '发卡类别'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '-5'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 145
    Width = 750
    Height = 260
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 750
      Height = 260
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
      OnCellClick = GridCellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'sbranch_code0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '所属区域'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户号'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spager'
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
          Title.Caption = '客户姓名'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lsafe_level2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户类别'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '收费类别'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '部门'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '部门全称'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '专业'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '入校日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '毕业日期'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '注册日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '批次号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '最后保存时间'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smarket_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '证件类型'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '证件号码'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smarket_code2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '性别'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snation_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '国籍'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_type2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '民族'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '电子信箱'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '电话'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '手机'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scusttypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '地址'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spost_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '邮编'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '扩展属性'
          Width = 70
          Visible = True
        end>
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        Caption = '查询结果集'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtObject
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
        Name = '学工号'
        Caption = '学工号'
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
        Name = '客户姓名'
        Caption = '客户姓名'
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
      end
      item
        Name = '所属区域'
        Caption = '所属区域'
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
        Name = '专业'
        Caption = '专业'
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
      end
      item
        Name = '注销日期'
        Caption = '注销日期'
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
      end
      item
        Name = '发卡类别'
        Caption = '发卡类别'
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
        MonitorValueChangedFields = '|客户号|学工号|卡号|姓名|身份证号|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 132
    Top = 183
  end
  inherited MainRequest: TWVRequest
    ID = '发卡客户信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '部门'
        FieldName = '部门'
      end
      item
        ParamName = '导入批次号'
        FieldName = '导入批次号'
      end
      item
        ParamName = '客户类别'
        FieldName = '客户类别'
      end
      item
        ParamName = '客户姓名'
        FieldName = '客户姓名'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '所属区域'
        FieldName = '所属区域'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '证件号码'
        FieldName = '证件号码'
      end
      item
        ParamName = '证件类型'
        FieldName = '证件类型'
      end
      item
        ParamName = '注销日期'
        FieldName = '注销日期'
      end
      item
        ParamName = '专业'
        FieldName = '专业'
      end
      item
        ParamName = '班级'
        FieldName = '班级'
      end
      item
        ParamName = '发卡类别'
        FieldName = '发卡类别'
      end>
    Left = 168
    Top = 184
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'lsafe_level2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-34'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
      end
      item
        FieldName = 'scert_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'scert_no2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-23'
      end
      item
        FieldName = 'snation_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '89'
      end
      item
        FieldName = 'scust_type2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2001'
      end
      item
        FieldName = 'smarket_code2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '39'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '87'
      end>
    Left = 200
    Top = 184
  end
  inherited DataSource: TDataSource
    Left = 240
    Top = 184
  end
  object WVFeeQuery: TWorkView
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
        DataField = 'vsmess'
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
        GroupIndex = 1
        DataField = '@Return'
      end
      item
        Name = '功能号'
        Caption = '功能号'
        FieldType = wftUndefined
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
        Name = '卡类型'
        Caption = '卡类型'
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
        Name = '收费类别'
        Caption = '收费类别'
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
        Name = '收费信息'
        Caption = '收费信息'
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
        Name = '总费用'
        Caption = '总费用'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '是否不记名卡'
        Caption = '是否不记名卡'
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
        Name = '卡有效期'
        Caption = '卡有效期'
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|客户号|学工号|卡号|姓名|身份证号|'
      end>
    Left = 132
    Top = 223
  end
  object WVRFeeQuery: TWVRequest
    WorkView = WVFeeQuery
    ID = '发卡收费查询'
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
        ParamName = '收费信息'
        FieldName = '收费信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '总费用'
        FieldName = '总费用'
        Direction = bdParam2Field
      end
      item
        ParamName = '功能号'
        FieldName = '功能号'
      end
      item
        ParamName = '卡类型'
        FieldName = '卡类型'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '是否不记名卡'
        FieldName = '是否不记名卡'
      end
      item
        ParamName = '卡有效期'
        FieldName = '卡有效期'
        Direction = bdParam2Field
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end>
    AfterExec = MainRequestAfterExec
    Left = 168
    Top = 224
  end
  object WVRReleaseCard: TWVRequest
    WorkView = WVReleaseCard
    ID = '发行卡trunk'
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
        ParamName = '操作员'
        FieldName = '操作员'
        Direction = bdBiDirection
      end
      item
        ParamName = '卡类型'
        FieldName = '卡类型'
      end
      item
        ParamName = '显示卡号'
        FieldName = '显示卡号'
        Direction = bdBiDirection
      end
      item
        ParamName = '物理卡号'
        FieldName = '物理卡号'
      end
      item
        ParamName = '票据号码'
        FieldName = '票据号码'
      end
      item
        ParamName = '到期日期'
        FieldName = '到期日期'
        Direction = bdBiDirection
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '收费方式'
        FieldName = '收费方式'
      end
      item
        ParamName = '收费金额'
        FieldName = '收费金额'
      end
      item
        ParamName = '客户类别'
        FieldName = '客户类别'
        Direction = bdParam2Field
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
        Direction = bdParam2Field
      end
      item
        ParamName = '客户姓名'
        FieldName = '客户姓名'
        Direction = bdParam2Field
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
        Direction = bdParam2Field
      end
      item
        ParamName = '部门代码'
        FieldName = '部门代码'
        Direction = bdParam2Field
      end
      item
        ParamName = '证件号码'
        FieldName = '证件号码'
        Direction = bdParam2Field
      end
      item
        ParamName = '性别'
        FieldName = '性别'
        Direction = bdParam2Field
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
        Direction = bdParam2Field
      end
      item
        ParamName = '卡密码'
        FieldName = '卡密码'
        Direction = bdParam2Field
      end
      item
        ParamName = '出卡值'
        FieldName = '出卡值'
        Direction = bdParam2Field
      end
      item
        ParamName = '流水号'
        FieldName = '流水号'
        Direction = bdParam2Field
      end
      item
        ParamName = '业务日期'
        FieldName = '业务日期'
        Direction = bdParam2Field
      end
      item
        ParamName = '是否不记名卡'
        FieldName = '是否不记名卡'
      end
      item
        ParamName = '终端编号'
        FieldName = '终端编号'
        Direction = bdParam2Field
      end
      item
        ParamName = '日限额'
        FieldName = '日限额'
        Direction = bdParam2Field
      end
      item
        ParamName = '单次限额'
        FieldName = '单次限额'
        Direction = bdParam2Field
      end>
    AfterExec = MainRequestAfterExec
    Left = 168
    Top = 264
  end
  object WVReleaseCard: TWorkView
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
        Name = '操作员'
        Caption = '操作员'
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
        Name = '卡类型'
        Caption = '卡类型'
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
        Name = '显示卡号'
        Caption = '显示卡号'
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
        Name = '物理卡号'
        Caption = '物理卡号'
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
        Name = '票据号码'
        Caption = '票据号码'
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
        Name = '到期日期'
        Caption = '到期日期'
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '收费方式'
        Caption = '收费方式'
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
        Name = '收费金额'
        Caption = '收费金额'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = True
        Checker.UpperCase = False
      end
      item
        Name = '客户类别'
        Caption = '客户类别'
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
        Name = '收费类别'
        Caption = '收费类别'
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
        Name = '客户姓名'
        Caption = '客户姓名'
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
        Name = '学工号'
        Caption = '学工号'
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
        Name = '部门代码'
        Caption = '部门代码'
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
        Name = '证件号码'
        Caption = '证件号码'
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
        Name = '性别'
        Caption = '性别'
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
        Name = '卡密码'
        Caption = '卡密码'
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
        Name = '出卡值'
        Caption = '出卡值'
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
        Name = '流水号'
        Caption = '流水号'
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
        Name = '业务日期'
        Caption = '业务日期'
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
        Name = '是否不记名卡'
        Caption = '是否不记名卡'
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
        Name = '终端编号'
        Caption = '终端编号'
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
        Name = '单次限额'
        Caption = '单次限额'
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
        Name = '日限额'
        Caption = '日限额'
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
        MonitorValueChangedFields = '|客户号|学工号|卡号|姓名|身份证号|'
      end>
    Left = 132
    Top = 263
  end
  object WVRelCardOk: TWorkView
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
        Name = '终端编号'
        Caption = '终端编号'
        FieldType = wftUndefined
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
        Name = '流水号'
        Caption = '流水号'
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
        Name = '业务日期'
        Caption = '业务日期'
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
        Name = '开户操作员'
        Caption = '开户操作员'
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
    Left = 136
    Top = 296
  end
  object WVRRelCardOk: TWVRequest
    WorkView = WVRelCardOk
    ID = '发卡确认'
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
        ParamName = '终端编号'
        FieldName = '终端编号'
      end
      item
        ParamName = '流水号'
        FieldName = '流水号'
      end
      item
        ParamName = '业务日期'
        FieldName = '业务日期'
      end
      item
        ParamName = '开户操作员'
        FieldName = '开户操作员'
      end>
    Left = 168
    Top = 296
  end
end
