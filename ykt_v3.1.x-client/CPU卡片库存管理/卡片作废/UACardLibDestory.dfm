inherited faqhCardLibDestory: TfaqhCardLibDestory
  Width = 779
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 405
    Width = 779
    Height = 84
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 602
      Top = 35
      Width = 81
      Enabled = False
      TabOrder = 1
    end
    inherited btnPrint: TBitBtn
      Left = 689
      Top = 35
      Width = 81
      TabOrder = 2
    end
    object grp1: TGroupBox
      Left = 0
      Top = 0
      Width = 569
      Height = 65
      Align = alLeft
      Caption = '卡作废信息'
      TabOrder = 0
      object Label2: TLabel
        Left = 16
        Top = 18
        Width = 58
        Height = 13
        AutoSize = False
        Caption = '卡 类 型'
      end
      object lblTransTo: TLabel
        Left = 210
        Top = 42
        Width = 38
        Height = 13
        AutoSize = False
        Caption = '操作员'
      end
      object lblBNo: TLabel
        Left = 16
        Top = 41
        Width = 58
        Height = 13
        AutoSize = False
        Caption = '卡片编号'
      end
      object cbbCardType: TWVComboBox
        Left = 72
        Top = 13
        Width = 105
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 0
        WorkView = WVCardDestory
        FieldName = '卡类型'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-56'
      end
      object cbbOperTrans: TWVComboBox
        Left = 253
        Top = 37
        Width = 105
        Height = 20
        Style = csDropDownList
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 6
        WorkView = WVCardDestory
        FieldName = '转入操作员'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-30'
      end
      object edtBNo: TEdit
        Left = 72
        Top = 37
        Width = 105
        Height = 20
        MaxLength = 10
        TabOrder = 5
      end
      object chkReadCard: TCheckBox
        Left = 210
        Top = 14
        Width = 73
        Height = 17
        Caption = '读卡作废'
        TabOrder = 1
      end
      object chkInfo: TCheckBox
        Left = 296
        Top = 14
        Width = 73
        Height = 17
        Caption = '提示信息'
        Checked = True
        State = cbChecked
        TabOrder = 2
      end
      object btnDestory: TBitBtn
        Left = 366
        Top = 34
        Width = 83
        Height = 25
        Anchors = [akTop, akRight]
        Caption = '卡片作废(&D)'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = btnDestoryClick
      end
      object btnCelDestory: TBitBtn
        Left = 462
        Top = 34
        Width = 83
        Height = 25
        Anchors = [akTop, akRight]
        Caption = '取消作废'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnClick = btnCelDestoryClick
      end
    end
    object RzStatusBar1: TRzStatusBar
      Left = 0
      Top = 65
      Width = 779
      Height = 19
      BorderInner = fsNone
      BorderOuter = fsNone
      BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
      BorderWidth = 0
      TabOrder = 3
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 725
        Height = 19
        Align = alLeft
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 779
    inherited Image1: TImage
      Width = 779
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 779
    Height = 55
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 54
      Top = 9
      Width = 36
      Height = 12
      Caption = '卡类型'
    end
    object lbl1: TLabel
      Left = 30
      Top = 33
      Width = 60
      Height = 12
      Caption = '领入批次号'
    end
    object Label7: TLabel
      Left = 238
      Top = 33
      Width = 60
      Height = 12
      Caption = '转交操作员'
    end
    object Label5: TLabel
      Left = 262
      Top = 9
      Width = 36
      Height = 12
      Caption = '操作员'
    end
    object Label6: TLabel
      Left = 470
      Top = 33
      Width = 24
      Height = 12
      Caption = '状态'
    end
    object Label4: TLabel
      Left = 446
      Top = 9
      Width = 48
      Height = 12
      Caption = '显示卡号'
    end
    object WVComboBox3: TWVComboBox
      Left = 96
      Top = 4
      Width = 131
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '卡类型'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-56'
    end
    object edtPatchNo: TWVEdit
      Left = 96
      Top = 28
      Width = 131
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 3
      Text = '<领入批次号>'
      WorkView = WorkView
      FieldName = '领入批次号'
    end
    object WVComboBox4: TWVComboBox
      Left = 304
      Top = 28
      Width = 121
      Height = 20
      Style = csDropDownList
      Color = clWhite
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ItemHeight = 12
      ParentFont = False
      TabOrder = 4
      WorkView = WorkView
      FieldName = '转交操作员'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-30'
    end
    object WVComboBox1: TWVComboBox
      Left = 304
      Top = 4
      Width = 121
      Height = 20
      Style = csDropDownList
      Color = clWhite
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ItemHeight = 12
      ParentFont = False
      TabOrder = 1
      WorkView = WorkView
      FieldName = '转入操作员'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-30'
    end
    object WVComboBox2: TWVComboBox
      Left = 504
      Top = 28
      Width = 123
      Height = 20
      Style = csDropDownList
      Color = clWhite
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ItemHeight = 12
      ParentFont = False
      TabOrder = 5
      WorkView = WorkView
      FieldName = '状态'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*127'
    end
    object edtShowCardNo: TWVEdit
      Left = 504
      Top = 4
      Width = 123
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<显示卡号>'
      WorkView = WorkView
      FieldName = '显示卡号'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 73
    Width = 779
    Height = 332
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 779
      Height = 332
      OnCellClick = GridCellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '卡类型'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '显示卡号'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semp_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '操作员'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '领入日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '领入批次号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '使用日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '回收日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '状态'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semp_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '转交操作员'
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
        Name = '卡类型'
        Caption = '卡类型'
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
        Name = '转入操作员'
        Caption = '转入操作员'
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
        Name = '显示卡号'
        Caption = '显示卡号'
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
        Name = '领入批次号'
        Caption = '领入批次号'
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
        Name = '状态'
        Caption = '状态'
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
        Name = '转交操作员'
        Caption = '转交操作员'
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
        MonitorValueChangedFields = '|卡类型|起始编号|截止编号|操作员号|转入操作员|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 412
    Top = 143
  end
  inherited MainRequest: TWVRequest
    ID = '卡片信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '卡类型'
        FieldName = '卡类型'
      end
      item
        ParamName = '转入操作员'
        FieldName = '转入操作员'
      end
      item
        ParamName = '显示卡号'
        FieldName = '显示卡号'
      end
      item
        ParamName = '领入批次号'
        FieldName = '领入批次号'
      end
      item
        ParamName = '状态'
        FieldName = '状态'
      end
      item
        ParamName = '转交操作员'
        FieldName = '转交操作员'
      end>
    Left = 448
    Top = 144
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'semp'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'lvol0'
        DataPresentType = 'idobjects'
        DataPresentParam = '-56'
      end
      item
        FieldName = 'semp_no2'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '127'
      end>
    Left = 480
    Top = 144
  end
  inherited DataSource: TDataSource
    Left = 520
    Top = 144
  end
  object WVCardDestory: TWorkView
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
        Name = '卡类型'
        Caption = '卡类型'
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
      end
      item
        Name = '起始编号'
        Caption = '起始编号'
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
        Name = '转入操作员'
        Caption = '转入操作员'
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
        Name = '作废标志'
        Caption = '作废标志'
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
        MonitorValueChangedFields = '|卡类型|起始编号|截止编号|操作员号|转入操作员|'
      end>
    Left = 412
    Top = 183
  end
  object WVRCardDestory: TWVRequest
    WorkView = WVCardDestory
    ID = '卡片作废'
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
        ParamName = '卡类型'
        FieldName = '卡类型'
      end
      item
        ParamName = '起始编号'
        FieldName = '起始编号'
      end
      item
        ParamName = '转入操作员'
        FieldName = '转入操作员'
      end
      item
        ParamName = '作废标志'
        FieldName = '作废标志'
      end>
    AfterExec = MainRequestAfterExec
    Left = 448
    Top = 184
  end
end
