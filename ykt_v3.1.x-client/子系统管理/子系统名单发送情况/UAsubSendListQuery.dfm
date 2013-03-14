inherited faqhsubSendListQuery: TfaqhsubSendListQuery
  Width = 776
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 776
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 599
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 686
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 776
    inherited Image1: TImage
      Width = 776
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 776
    Height = 30
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 14
      Top = 10
      Width = 36
      Height = 12
      Caption = '子系统'
    end
    object Label2: TLabel
      Left = 178
      Top = 10
      Width = 48
      Height = 12
      Caption = '交易卡号'
    end
    object Label3: TLabel
      Left = 318
      Top = 10
      Width = 36
      Height = 12
      Caption = '学工号'
    end
    object Label4: TLabel
      Left = 458
      Top = 10
      Width = 48
      Height = 12
      Caption = '名单类型'
    end
    object Label5: TLabel
      Left = 634
      Top = 10
      Width = 24
      Height = 12
      Caption = '状态'
    end
    object WVEdit2: TWVEdit
      Left = 228
      Top = 5
      Width = 77
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<交易卡号>'
      WorkView = WorkView
      FieldName = '交易卡号'
    end
    object WVEdit3: TWVEdit
      Left = 356
      Top = 5
      Width = 93
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<学工号>'
      WorkView = WorkView
      FieldName = '学工号'
    end
    object WVComboBox1: TWVComboBox
      Left = 56
      Top = 5
      Width = 113
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '子系统'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-47'
    end
    object WVComboBox2: TWVComboBox
      Left = 512
      Top = 5
      Width = 113
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '名单类型'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*73'
    end
    object WVComboBox3: TWVComboBox
      Left = 664
      Top = 5
      Width = 81
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 4
      WorkView = WorkView
      FieldName = '状态'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*68'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 48
    Width = 776
    Height = 411
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 776
      Height = 411
      Columns = <
        item
          Expanded = False
          FieldName = 'Lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '子系统标识'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '子系统名称'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易卡号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '物理卡号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '学工号'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '名单类型'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '版本'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '状态'
          Width = 80
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
        Name = '子系统'
        Caption = '子系统'
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
        Name = '交易卡号'
        Caption = '交易卡号'
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
        GetPrevChar = '*'
      end
      item
        Name = '名单类型'
        Caption = '名单类型'
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
        Name = '状态'
        Caption = '状态'
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
        MonitorValueChangedFields = '|子系统|交易卡号|学工号|模块名称|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '子系统名单发送情况'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '子系统'
        FieldName = '子系统'
      end
      item
        ParamName = '交易卡号'
        FieldName = '交易卡号'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '名单类型'
        FieldName = '名单类型'
      end
      item
        ParamName = '状态'
        FieldName = '状态'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol2'
        DataPresentType = 'idobjects'
        DataPresentParam = '73'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '68'
      end>
    Left = 168
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 208
    Top = 256
  end
end
