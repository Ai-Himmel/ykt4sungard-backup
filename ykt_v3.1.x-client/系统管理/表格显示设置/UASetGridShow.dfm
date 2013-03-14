inherited faqhSetGridShow: TfaqhSetGridShow
  Width = 700
  Height = 581
  inherited UIPanel1: TUIPanel
    Top = 551
    Width = 700
    inherited btnQuery: TBitBtn
      Left = 523
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 610
      Hint = '保存修改'
      Caption = '&S保存'
    end
    object btnpreview: TBitBtn
      Left = 363
      Top = 3
      Width = 75
      Height = 25
      Hint = '预览表格设置结果'
      Anchors = [akTop, akRight]
      Caption = '&P预览'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = btnQueryClick
    end
    object chkAutoSave: TRzCheckBox
      Left = 24
      Top = 8
      Width = 115
      Height = 17
      Caption = '自动保存数据'
      FrameColor = 8409372
      HighlightColor = 2203937
      HotTrack = True
      HotTrackColor = 3983359
      HotTrackColorType = htctActual
      State = cbUnchecked
      TabOrder = 3
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Top = 25
    Width = 700
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel2: TPanel [2]
    Left = 0
    Top = 0
    Width = 700
    Height = 25
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 4
    object Label2: TLabel
      Left = 10
      Top = 5
      Width = 96
      Height = 16
      Caption = '表格显示设置'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = '黑体'
      Font.Style = []
      ParentFont = False
    end
  end
  object Panel1: TPanel [3]
    Left = 0
    Top = 43
    Width = 700
    Height = 35
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left = 18
      Top = 9
      Width = 48
      Height = 12
      Caption = '模板名称'
    end
    object Label3: TLabel
      Left = 186
      Top = 9
      Width = 36
      Height = 12
      Caption = '功能号'
    end
    object WVEdit1: TWVEdit
      Left = 76
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 0
      Text = '<姓名>'
      WorkView = WorkView
      FieldName = '姓名'
    end
    object WVEdit2: TWVEdit
      Left = 228
      Top = 5
      Width = 125
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 1
      Text = '<姓名>'
      WorkView = WorkView
      FieldName = '姓名'
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 233
    Top = 78
    Width = 467
    Height = 467
    inherited Grid: TRzDBGrid
      Width = 467
      Height = 467
      Hint = '单击可编辑选中的数据'
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentShowHint = False
      ShowHint = True
      OnCellClick = GridCellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Caption = '姓名'
          Visible = True
        end>
    end
  end
  object Pnl1: TRzSizePanel [5]
    Left = 0
    Top = 78
    Width = 233
    Height = 467
    BorderOuter = fsGroove
    Color = 16184303
    HotSpotVisible = True
    SizeBarWidth = 5
    TabOrder = 5
    UseGradients = True
    object lbl1: TLabel
      Left = 12
      Top = 56
      Width = 84
      Height = 12
      AutoSize = False
      Caption = 'CnPack字段名：'
    end
    object lbl2: TLabel
      Left = 12
      Top = 88
      Width = 84
      Height = 12
      AutoSize = False
      Caption = '表格显示名称：'
    end
    object lbl3: TLabel
      Left = 36
      Top = 120
      Width = 60
      Height = 12
      AutoSize = False
      Caption = '是否显示：'
    end
    object lbl4: TLabel
      Left = 24
      Top = 152
      Width = 72
      Height = 12
      AutoSize = False
      Caption = '显示顺序号：'
    end
    object lbl5: TLabel
      Left = 36
      Top = 184
      Width = 60
      Height = 12
      AutoSize = False
      Caption = '表格宽度：'
    end
    object lbl6: TLabel
      Left = 12
      Top = 216
      Width = 84
      Height = 12
      AutoSize = False
      Caption = '表头对齐方式：'
    end
    object lbl7: TLabel
      Left = 36
      Top = 248
      Width = 60
      Height = 12
      AutoSize = False
      Caption = '表头字体：'
    end
    object lbl8: TLabel
      Left = 12
      Top = 280
      Width = 84
      Height = 12
      AutoSize = False
      Caption = '表头字体大小：'
    end
    object lbl9: TLabel
      Left = 12
      Top = 312
      Width = 84
      Height = 12
      AutoSize = False
      Caption = '表头字体颜色：'
    end
    object lbl11: TLabel
      Left = 12
      Top = 344
      Width = 84
      Height = 12
      AutoSize = False
      Caption = '表格对齐方式：'
    end
    object lbl12: TLabel
      Left = 36
      Top = 376
      Width = 60
      Height = 12
      AutoSize = False
      Caption = '表格字体：'
    end
    object lbl13: TLabel
      Left = 12
      Top = 408
      Width = 84
      Height = 12
      AutoSize = False
      Caption = '表格字体大小：'
    end
    object lbl14: TLabel
      Left = 12
      Top = 440
      Width = 84
      Height = 12
      AutoSize = False
      Caption = '表格字体颜色：'
    end
    object lbl10: TLabel
      Left = 48
      Top = 24
      Width = 48
      Height = 12
      Caption = '功能号：'
    end
    object edtFieldName: TRzEdit
      Left = 96
      Top = 51
      Width = 123
      Height = 20
      ReadOnly = True
      TabOrder = 1
    end
    object edtShowName: TRzEdit
      Left = 96
      Top = 83
      Width = 123
      Height = 20
      MaxLength = 20
      TabOrder = 2
    end
    object cbbTitAlign: TRzComboBox
      Left = 96
      Top = 210
      Width = 123
      Height = 20
      Style = csDropDownList
      ItemHeight = 12
      TabOrder = 6
      Text = '居左对齐'
      Items.Strings = (
        '居左对齐'
        '居右对齐'
        '居中对齐')
      ItemIndex = 0
    end
    object FontCbbTitFont: TRzFontComboBox
      Left = 96
      Top = 241
      Width = 123
      Height = 22
      FontName = '宋体'
      FontSize = 9
      ShowStyle = ssFontPreview
      ItemHeight = 16
      TabOrder = 7
    end
    object NumEdtTitFontSize: TRzNumericEdit
      Left = 96
      Top = 274
      Width = 123
      Height = 20
      TabOrder = 8
      Max = 20
      Min = 6
      Value = 9
      DisplayFormat = ',0;(,0)'
    end
    object ColorcbbTitFont: TRzColorComboBox
      Left = 96
      Top = 304
      Width = 123
      Height = 22
      ItemHeight = 16
      TabOrder = 9
    end
    object cbbGridAlign: TRzComboBox
      Left = 96
      Top = 338
      Width = 123
      Height = 20
      Style = csDropDownList
      ItemHeight = 12
      TabOrder = 10
      Text = '居左对齐'
      Items.Strings = (
        '居左对齐'
        '居右对齐'
        '居中对齐')
      ItemIndex = 0
    end
    object FontCbbGridFont: TRzFontComboBox
      Left = 96
      Top = 369
      Width = 123
      Height = 22
      FontName = '宋体'
      ShowStyle = ssFontPreview
      ItemHeight = 16
      TabOrder = 11
    end
    object NumEdtGridFontSize: TRzNumericEdit
      Left = 96
      Top = 402
      Width = 123
      Height = 20
      TabOrder = 12
      Max = 20
      Min = 6
      Value = 9
      DisplayFormat = ',0;(,0)'
    end
    object ColorcbbGridFontColor: TRzColorComboBox
      Left = 96
      Top = 432
      Width = 123
      Height = 22
      ItemHeight = 16
      TabOrder = 13
    end
    object NumEdtShowWidth: TRzNumericEdit
      Left = 96
      Top = 178
      Width = 123
      Height = 20
      TabOrder = 5
      Max = 500
      Min = -1
      Value = 50
      DisplayFormat = ',0;(,0)'
    end
    object NumEdtShowID: TRzNumericEdit
      Left = 96
      Top = 146
      Width = 123
      Height = 20
      MaxLength = 3
      TabOrder = 4
      Max = 999
      DisplayFormat = ',0;(,0)'
    end
    object chkIfShow: TRzCheckBox
      Left = 96
      Top = 117
      Width = 49
      Height = 17
      FrameColor = 8409372
      HighlightColor = 2203937
      HotTrack = True
      HotTrackColor = 3983359
      HotTrackColorType = htctActual
      State = cbUnchecked
      TabOrder = 3
    end
    object edtFuncNo: TRzEdit
      Left = 96
      Top = 19
      Width = 123
      Height = 20
      ReadOnly = True
      TabOrder = 0
    end
  end
  object Pnl2: TRzSizePanel [6]
    Left = 0
    Top = 545
    Width = 700
    Height = 6
    Align = alBottom
    Color = 16184303
    HotSpotVisible = True
    SizeBarWidth = 5
    TabOrder = 8
    UseGradients = True
    HotSpotClosed = True
    HotSpotPosition = 55
    object gridpreview: TRzDBGrid
      Left = 0
      Top = 6
      Width = 700
      Height = 0
      Align = alClient
      DataSource = DataSource
      FixedColor = 15458000
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      TabOrder = 0
      TitleFont.Charset = GB2312_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -12
      TitleFont.Name = '宋体'
      TitleFont.Style = []
      OnDrawColumnCell = GridDrawColumnCell
      OnKeyDown = GridKeyDown
      FrameColor = 12164479
      FrameStyle = fsGroove
      FrameVisible = True
      FixedLineColor = 12164479
      LineColor = clBackground
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|姓名|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 300
    Top = 135
  end
  inherited MainRequest: TWVRequest
    ID = '表格显示设置'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end>
    Left = 336
    Top = 136
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 376
    Top = 136
  end
  inherited DataSource: TDataSource
    Left = 408
    Top = 136
  end
  object wvSave: TWorkView
    WorkFields = <
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|姓名|'
      end>
    Left = 300
    Top = 191
  end
  object wvRSave: TWVRequest
    WorkView = wvSave
    ID = '表格显示设置保存'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end>
    AfterExec = MainRequestAfterExec
    Left = 336
    Top = 192
  end
end
