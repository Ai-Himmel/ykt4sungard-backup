inherited faqhUACPUSetwaterCard: TfaqhUACPUSetwaterCard
  Width = 787
  Height = 580
  inherited UIPanel1: TUIPanel
    Top = 544
    Width = 787
    Height = 36
    inherited btnQuery: TBitBtn
      Left = 130
      Top = 1000
      TabOrder = 5
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 105
      Top = 1000
      Enabled = True
      TabOrder = 4
      Visible = False
    end
    object btnRateSet: TBitBtn
      Left = 545
      Top = 6
      Width = 129
      Height = 25
      Hint = '发行费率设置卡'
      Anchors = [akTop, akRight]
      Caption = '发行费率设置卡'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnRateSetClick
    end
    object btnConCard: TBitBtn
      Left = 687
      Top = 6
      Width = 89
      Height = 25
      Hint = '回收设置卡'
      Anchors = [akTop, akRight]
      Caption = '回收设置卡'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnConCardClick
    end
    object btnClear: TBitBtn
      Left = 346
      Top = 6
      Width = 75
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '清空设置'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnClearClick
    end
    object btnSave2Db: TBitBtn
      Left = 432
      Top = 6
      Width = 101
      Height = 25
      Hint = '保存费率设置到数据库'
      Anchors = [akTop, akRight]
      Caption = '保存到数据库'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnSave2DbClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 787
    inherited Image1: TImage
      Width = 787
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 787
    Height = 526
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object lbl1: TLabel
      Left = 86
      Top = 80
      Width = 70
      Height = 14
      Caption = '收费类别：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label1: TLabel
      Left = 72
      Top = 137
      Width = 84
      Height = 14
      Caption = '水控钱包号：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 86
      Top = 163
      Width = 70
      Height = 14
      Caption = '费率个数：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 86
      Top = 255
      Width = 70
      Height = 14
      Caption = '费率类型：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object bvl1: TBevel
      Left = 352
      Top = 39
      Width = 6
      Height = 498
    end
    object Label35: TLabel
      Left = 44
      Top = 528
      Width = 70
      Height = 14
      Caption = '收费类别：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      Visible = False
    end
    object Label3: TLabel
      Left = 86
      Top = 109
      Width = 70
      Height = 14
      Caption = '是否可用：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 86
      Top = 215
      Width = 70
      Height = 14
      Caption = '计费单位：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label7: TLabel
      Left = 86
      Top = 190
      Width = 70
      Height = 14
      Caption = '工作模式：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object lbl2: TLabel
      Left = 86
      Top = 52
      Width = 70
      Height = 14
      Caption = '费率名称：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object cbbFeeType: TWVComboBox
      Left = 156
      Top = 75
      Width = 157
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 10
      ItemHeight = 12
      TabOrder = 2
      OnChange = cbbFeeTypeChange
      OnExit = cbbFeeTypeExit
      WorkView = WorkView
      FieldName = '查询.收费类别'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '-43'
    end
    object edtNo: TRzSpinEdit
      Left = 156
      Top = 134
      Width = 157
      Height = 20
      AllowKeyEdit = True
      Max = 10
      TabOrder = 4
    end
    object edtRateNum: TRzSpinEdit
      Left = 156
      Top = 160
      Width = 157
      Height = 20
      BlankValue = 1
      AllowKeyEdit = True
      Max = 3
      Min = 1
      Value = 1
      TabOrder = 6
      OnChange = edtRateNumChange
    end
    object rb1: TRzGroupBox
      Tag = 1
      Left = 384
      Top = 40
      Width = 329
      Height = 89
      Caption = '费率一'
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      GroupStyle = gsTopLine
      ParentFont = False
      TabOrder = 0
      ThemeAware = False
      Visible = False
      object lblUnitName1: TLabel
        Left = 14
        Top = 19
        Width = 98
        Height = 14
        Alignment = taRightJustify
        Caption = '扣费时间单位：'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object lblUnit1: TLabel
        Left = 214
        Top = 19
        Width = 70
        Height = 14
        Caption = '以秒为单位'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label8: TLabel
        Left = 14
        Top = 43
        Width = 98
        Height = 14
        Caption = '扣费金额单位：'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label9: TLabel
        Left = 214
        Top = 43
        Width = 70
        Height = 14
        Caption = '以分为单位'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label29: TLabel
        Left = 7
        Top = 67
        Width = 105
        Height = 14
        Caption = '从第N分钟开始：'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label30: TLabel
        Left = 214
        Top = 67
        Width = 84
        Height = 14
        Caption = '以分钟为单位'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object edtUnit1: TRzSpinEdit
        Tag = 1
        Left = 116
        Top = 16
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 0
      end
      object edtMoney1: TRzSpinEdit
        Tag = 1
        Left = 116
        Top = 40
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 1
      end
      object edtNumN1: TRzSpinEdit
        Tag = 1
        Left = 116
        Top = 63
        Width = 93
        Height = 22
        BlankValue = 1
        AllowKeyEdit = True
        Max = 255
        Value = 1
        TabOrder = 2
        OnChange = edtRateNumChange
      end
    end
    object rb2: TRzGroupBox
      Tag = 2
      Left = 384
      Top = 136
      Width = 329
      Height = 89
      Caption = '费率二'
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      GroupStyle = gsTopLine
      ParentFont = False
      TabOrder = 5
      ThemeAware = False
      Visible = False
      object lblUnitName2: TLabel
        Left = 14
        Top = 19
        Width = 98
        Height = 14
        Alignment = taRightJustify
        Caption = '扣费时间单位：'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object lblUnit2: TLabel
        Left = 214
        Top = 19
        Width = 70
        Height = 14
        Caption = '以秒为单位'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label12: TLabel
        Left = 14
        Top = 43
        Width = 98
        Height = 14
        Caption = '扣费金额单位：'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label13: TLabel
        Left = 214
        Top = 43
        Width = 70
        Height = 14
        Caption = '以分为单位'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label28: TLabel
        Left = 7
        Top = 67
        Width = 105
        Height = 14
        Caption = '从第N分钟开始：'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label31: TLabel
        Left = 214
        Top = 67
        Width = 84
        Height = 14
        Caption = '以分钟为单位'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object edtUnit2: TRzSpinEdit
        Tag = 2
        Left = 116
        Top = 16
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 0
      end
      object edtMoney2: TRzSpinEdit
        Tag = 2
        Left = 116
        Top = 40
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 1
      end
      object edtNumN2: TRzSpinEdit
        Tag = 2
        Left = 116
        Top = 63
        Width = 93
        Height = 22
        BlankValue = 1
        AllowKeyEdit = True
        Max = 255
        Value = 1
        TabOrder = 2
        OnChange = edtRateNumChange
      end
    end
    object rb3: TRzGroupBox
      Tag = 3
      Left = 384
      Top = 232
      Width = 329
      Height = 89
      Caption = '费率三'
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      GroupStyle = gsTopLine
      ParentFont = False
      TabOrder = 9
      ThemeAware = False
      Visible = False
      object lblUnitName3: TLabel
        Left = 14
        Top = 19
        Width = 98
        Height = 14
        Alignment = taRightJustify
        Caption = '扣费时间单位：'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object lblUnit3: TLabel
        Left = 214
        Top = 19
        Width = 70
        Height = 14
        Caption = '以秒为单位'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label16: TLabel
        Left = 14
        Top = 43
        Width = 98
        Height = 14
        Caption = '扣费金额单位：'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label17: TLabel
        Left = 214
        Top = 43
        Width = 70
        Height = 14
        Caption = '以分为单位'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label27: TLabel
        Left = 7
        Top = 67
        Width = 105
        Height = 14
        Caption = '从第N分钟开始：'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label32: TLabel
        Left = 214
        Top = 67
        Width = 84
        Height = 14
        Caption = '以分钟为单位'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object edtUnit3: TRzSpinEdit
        Tag = 3
        Left = 116
        Top = 16
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 0
      end
      object edtMoney3: TRzSpinEdit
        Tag = 3
        Left = 116
        Top = 40
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 1
      end
      object edtNumN3: TRzSpinEdit
        Tag = 3
        Left = 116
        Top = 63
        Width = 93
        Height = 22
        BlankValue = 1
        AllowKeyEdit = True
        Max = 255
        Value = 1
        TabOrder = 2
        OnChange = edtRateNumChange
      end
    end
    object rb4: TRzGroupBox
      Tag = 4
      Left = 384
      Top = 328
      Width = 329
      Height = 89
      Caption = '费率四'
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      GroupStyle = gsTopLine
      ParentFont = False
      TabOrder = 11
      ThemeAware = False
      Visible = False
      object lblUnitName4: TLabel
        Left = 14
        Top = 19
        Width = 98
        Height = 14
        Alignment = taRightJustify
        Caption = '扣费时间单位：'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object lblUnit4: TLabel
        Left = 214
        Top = 19
        Width = 70
        Height = 14
        Caption = '以秒为单位'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label20: TLabel
        Left = 14
        Top = 43
        Width = 98
        Height = 14
        Caption = '扣费金额单位：'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label21: TLabel
        Left = 214
        Top = 43
        Width = 70
        Height = 14
        Caption = '以分为单位'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label26: TLabel
        Left = 7
        Top = 67
        Width = 105
        Height = 14
        Caption = '从第N分钟开始：'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label33: TLabel
        Left = 214
        Top = 67
        Width = 84
        Height = 14
        Caption = '以分钟为单位'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object edtUnit4: TRzSpinEdit
        Tag = 4
        Left = 116
        Top = 16
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 0
      end
      object edtMoney4: TRzSpinEdit
        Tag = 4
        Left = 116
        Top = 40
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 1
      end
      object edtNumN4: TRzSpinEdit
        Tag = 4
        Left = 116
        Top = 63
        Width = 93
        Height = 22
        BlankValue = 1
        AllowKeyEdit = True
        Max = 255
        Value = 1
        TabOrder = 2
        OnChange = edtRateNumChange
      end
    end
    object rb5: TRzGroupBox
      Tag = 5
      Left = 384
      Top = 422
      Width = 329
      Height = 91
      Caption = '费率五'
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      GroupStyle = gsTopLine
      ParentFont = False
      TabOrder = 12
      ThemeAware = False
      Visible = False
      object lblUnitName5: TLabel
        Left = 14
        Top = 19
        Width = 98
        Height = 14
        Alignment = taRightJustify
        Caption = '扣费时间单位：'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object lblUnit5: TLabel
        Left = 214
        Top = 19
        Width = 70
        Height = 14
        Caption = '以秒为单位'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label24: TLabel
        Left = 14
        Top = 43
        Width = 98
        Height = 14
        Caption = '扣费金额单位：'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label25: TLabel
        Left = 214
        Top = 43
        Width = 70
        Height = 14
        Caption = '以分为单位'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel
        Left = 7
        Top = 67
        Width = 105
        Height = 14
        Caption = '从第N分钟开始：'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label34: TLabel
        Left = 214
        Top = 67
        Width = 84
        Height = 14
        Caption = '以分钟为单位'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object edtUnit5: TRzSpinEdit
        Tag = 5
        Left = 116
        Top = 16
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 0
      end
      object edtMoney5: TRzSpinEdit
        Tag = 5
        Left = 116
        Top = 40
        Width = 93
        Height = 22
        AllowKeyEdit = True
        Max = 255
        TabOrder = 1
      end
      object edtNumN5: TRzSpinEdit
        Tag = 5
        Left = 116
        Top = 63
        Width = 93
        Height = 22
        BlankValue = 1
        AllowKeyEdit = True
        Max = 255
        Value = 1
        TabOrder = 2
        OnChange = edtRateNumChange
      end
    end
    object rgUse: TRzRadioGroup
      Left = 157
      Top = 94
      Width = 156
      Height = 38
      Caption = ' '
      Color = 16184303
      Columns = 2
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ItemFrameColor = 8409372
      ItemHotTrack = True
      ItemHighlightColor = 2203937
      ItemHotTrackColor = 3983359
      ItemHotTrackColorType = htctActual
      ItemIndex = 0
      Items.Strings = (
        '可用'
        '不可用')
      ParentFont = False
      TabOrder = 3
    end
    object rgFeeType: TRzRadioGroup
      Left = 156
      Top = 249
      Width = 157
      Height = 110
      Caption = ' '
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ItemFrameColor = 8409372
      ItemHotTrack = True
      ItemHighlightColor = 2203937
      ItemHotTrackColor = 3983359
      ItemHotTrackColorType = htctActual
      ItemIndex = 0
      Items.Strings = (
        '费率设置卡'
        '常开设置卡'
        '预扣费卡'
        '脱机水控卡')
      ParentFont = False
      TabOrder = 10
    end
    object rgFeeUnit: TRzRadioGroup
      Left = 156
      Top = 208
      Width = 157
      Height = 39
      Caption = ' '
      Color = 16184303
      Columns = 2
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ItemFrameColor = 8409372
      ItemHotTrack = True
      ItemHighlightColor = 2203937
      ItemHotTrackColor = 3983359
      ItemHotTrackColorType = htctActual
      ItemIndex = 0
      Items.Strings = (
        '时间'
        '流量')
      ParentFont = False
      TabOrder = 8
      OnClick = rgFeeUnitClick
    end
    object cbbWorkView: TComboBox
      Left = 157
      Top = 187
      Width = 156
      Height = 20
      Style = csDropDownList
      ItemHeight = 12
      TabOrder = 7
      Items.Strings = (
        '公寓模式'
        '大浴室模式')
    end
    object edtFeeName: TWVEdit
      Left = 156
      Top = 47
      Width = 157
      Height = 22
      Color = clBtnHighlight
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      MaxLength = 22
      ParentFont = False
      ReadOnly = False
      TabOrder = 1
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 752
    Top = 576
    Width = 35
    Height = 29
    Align = alNone
    TabOrder = 3
    Visible = False
    inherited Grid: TRzDBGrid
      Align = alNone
      Columns = <
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Caption = '操作日期'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'SORDER1'
          PickList.Strings = ()
          Title.Caption = '操作时间'
          Visible = True
        end>
    end
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
        Name = '密钥'
        Caption = '密钥'
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
        Name = '参数标志'
        Caption = '参数标志'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|开始日期|结束日期|'
      end>
    Left = 548
    Top = 15
  end
  inherited MainRequest: TWVRequest
    ID = '全局参数主键查询_water'
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
        ParamName = '密钥'
        FieldName = '密钥'
        Direction = bdParam2Field
      end
      item
        ParamName = '参数标志'
        FieldName = '参数标志'
      end>
    Left = 584
    Top = 16
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 624
    Top = 16
  end
  inherited DataSource: TDataSource
    Left = 656
    Top = 16
  end
  object wvrSaveFeeType: TWVRequest
    WorkView = wvSaveFeeType
    ID = '保存费率设置卡'
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
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '费率编号'
        FieldName = '费率编号'
        Direction = bdBiDirection
      end
      item
        ParamName = '费率名称'
        FieldName = '费率名称'
      end
      item
        ParamName = '钱包号'
        FieldName = '钱包号'
      end
      item
        ParamName = '计费单位'
        FieldName = '计费单位'
      end
      item
        ParamName = '费率类型'
        FieldName = '费率类型'
      end
      item
        ParamName = '费率个数'
        FieldName = '费率个数'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '数量'
        FieldName = '数量'
      end
      item
        ParamName = '费率时间1'
        FieldName = '费率时间1'
      end
      item
        ParamName = '费率金额1'
        FieldName = '费率金额1'
      end
      item
        ParamName = '费率分钟1'
        FieldName = '费率分钟1'
      end
      item
        ParamName = '费率时间2'
        FieldName = '费率时间2'
      end
      item
        ParamName = '费率金额2'
        FieldName = '费率金额2'
      end
      item
        ParamName = '费率分钟2'
        FieldName = '费率分钟2'
      end
      item
        ParamName = '费率时间3'
        FieldName = '费率时间3'
      end
      item
        ParamName = '费率金额3'
        FieldName = '费率金额3'
      end
      item
        ParamName = '费率分钟3'
        FieldName = '费率分钟3'
      end>
    AfterExec = MainRequestAfterExec
    Left = 584
    Top = 56
  end
  object wvSaveFeeType: TWorkView
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
        Name = '标志'
        Caption = '标志'
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
        Name = '费率编号'
        Caption = '费率编号'
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
        Name = '费率名称'
        Caption = '费率名称'
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
        Name = '计费单位'
        Caption = '计费单位'
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
        Name = '费率类型'
        Caption = '费率类型'
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
        Name = '费率个数'
        Caption = '费率个数'
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
        Name = '数量'
        Caption = '数量'
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
        Name = '费率时间1'
        Caption = '费率时间1'
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
        Name = '费率金额1'
        Caption = '费率金额1'
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
        Name = '费率分钟1'
        Caption = '费率分钟1'
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
        Name = '费率时间2'
        Caption = '费率时间2'
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
        Name = '费率金额2'
        Caption = '费率金额2'
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
        Name = '费率分钟2'
        Caption = '费率分钟2'
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
        Name = '费率时间3'
        Caption = '费率时间3'
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
        Name = '费率金额3'
        Caption = '费率金额3'
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
        Name = '费率分钟3'
        Caption = '费率分钟3'
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
        MonitorValueChangedFields = '|开始日期|结束日期|'
      end>
    Left = 548
    Top = 55
  end
end
