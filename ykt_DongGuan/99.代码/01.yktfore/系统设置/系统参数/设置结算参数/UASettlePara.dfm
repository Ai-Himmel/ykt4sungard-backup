inherited faqhSettlePara: TfaqhSettlePara
  Width = 681
  Height = 477
  Caption = '设置结算参数'
  inherited pcPages: TPageControl
    Width = 681
    Height = 477
    ActivePage = tsEdit
    inherited tsQuery: TTabSheet
      inherited UIPanel1: TUIPanel
        Top = 420
        Width = 673
        TabOrder = 1
        inherited btnAdd: TBitBtn [0]
          Left = 415
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 503
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 322
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
        end
      end
      inherited Grid: TDBGrid
        Top = 60
        Width = 673
        Height = 360
        TabOrder = 2
        OnDrawColumnCell = GridDrawColumnCell
        Columns = <
          item
            Expanded = False
            FieldName = 'sserial2'
            PickList.Strings = ()
            Title.Caption = '席位代码'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial1'
            PickList.Strings = ()
            Title.Caption = '参数代码'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial0'
            PickList.Strings = ()
            Title.Caption = '参数代码值'
            Width = 83
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote'
            PickList.Strings = ()
            Title.Caption = '描述'
            Width = 263
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 673
        Height = 60
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label8: TLabel
          Left = 40
          Top = 5
          Width = 96
          Height = 16
          Caption = '结算参数查询'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = '黑体'
          Font.Style = []
          ParentFont = False
        end
        object Label2: TLabel
          Left = 42
          Top = 34
          Width = 48
          Height = 12
          Caption = '席位代码'
        end
        object Label3: TLabel
          Left = 242
          Top = 34
          Width = 48
          Height = 12
          Caption = '参数代码'
        end
        object WVEdit1: TWVEdit
          Left = 100
          Top = 30
          Width = 100
          Height = 20
          Enabled = False
          ImeName = ''
          ParentColor = True
          ReadOnly = False
          TabOrder = 2
          Text = '<查询.查询标志（1：结算；2：交易）>'
          Visible = False
          WorkView = WorkView
          FieldName = '查询.查询标志（1：结算；2：交易）'
        end
        object WVEdit2: TWVEdit
          Left = 100
          Top = 30
          Width = 100
          Height = 20
          Enabled = False
          ImeName = ''
          ParentColor = True
          ReadOnly = False
          TabOrder = 3
          Text = '<查询.席_位>'
          Visible = False
          WorkView = WorkView
          FieldName = '查询.席_位'
        end
        object WVEdit3: TWVEdit
          Left = 300
          Top = 30
          Width = 100
          Height = 20
          Color = clInfoBk
          ImeName = ''
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.参数代码>'
          WorkView = WorkView
          FieldName = '查询.参数代码'
        end
        object WVComboBox2: TWVComboBox
          Left = 100
          Top = 30
          Width = 100
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = ''
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '查询.席_位'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-23'
        end
      end
    end
    inherited tsEdit: TTabSheet
      object Label4: TLabel [0]
        Left = 42
        Top = 44
        Width = 48
        Height = 12
        Caption = '席位代码'
      end
      object Label5: TLabel [1]
        Left = 42
        Top = 84
        Width = 48
        Height = 12
        Caption = '参数代码'
      end
      object Label6: TLabel [2]
        Left = 42
        Top = 124
        Width = 48
        Height = 12
        Caption = '代 码 值'
      end
      object Label9: TLabel [3]
        Left = 40
        Top = 5
        Width = 96
        Height = 16
        Caption = '设置结算参数'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '黑体'
        Font.Style = []
        ParentFont = False
      end
      object Label_snote: TLabel [4]
        Left = 42
        Top = 164
        Width = 48
        Height = 12
        Caption = '描    述'
      end
      inherited UIPanel2: TUIPanel
        Top = 414
        Width = 673
        TabOrder = 4
        inherited btnOK: TBitBtn
          Left = 501
        end
        inherited btnCancel: TBitBtn
          Left = 589
        end
        inherited DBNavigator: TDBNavigator
          Hints.Strings = ()
        end
      end
      object WVEdit4: TWVEdit
        Left = 108
        Top = 40
        Width = 100
        Height = 20
        Enabled = False
        ImeName = ''
        ParentColor = True
        ReadOnly = False
        TabOrder = 3
        Text = '<席_位_代_码>'
        Visible = False
        WorkView = WorkView
        FieldName = '席_位_代_码'
        SynchronizeWhenExit = True
      end
      object WVEdit5: TWVEdit
        Left = 108
        Top = 80
        Width = 100
        Height = 20
        Color = clInfoBk
        ImeName = ''
        MaxLength = 10
        ReadOnly = False
        TabOrder = 1
        Text = '<参数代码>'
        WorkView = WorkView
        FieldName = '参数代码'
        SynchronizeWhenExit = True
      end
      object WVEdit6: TWVEdit
        Left = 108
        Top = 120
        Width = 100
        Height = 20
        Color = clInfoBk
        ImeName = ''
        MaxLength = 10
        ReadOnly = False
        TabOrder = 2
        Text = '<参数代码值>'
        WorkView = WorkView
        FieldName = '参数代码值'
        SynchronizeWhenExit = True
      end
      object WVComboBox1: TWVComboBox
        Left = 108
        Top = 40
        Width = 101
        Height = 20
        Color = clInfoBk
        ImeName = ''
        ItemHeight = 12
        TabOrder = 0
        Text = '<席_位_代_码>'
        OnExit = WVComboBox1Exit
        WorkView = WorkView
        FieldName = '席_位_代_码'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-23'
      end
      object WVEdit_snote: TWVEdit
        Left = 108
        Top = 160
        Width = 277
        Height = 20
        Color = clWhite
        ImeName = ''
        ReadOnly = False
        TabOrder = 5
        Text = '<描述>'
        WorkView = WorkView
        FieldName = '描述'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 260
    Top = 383
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
        DefaultValue = '3'
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
        DefaultValue = '2'
      end
      item
        Name = '查询.查询标志（1：结算；2：交易）'
        Caption = '查询.查询标志（1：结算；2：交易）'
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
        Name = '查询.席_位'
        Caption = '查询.席_位'
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
        Name = '查询.参数代码'
        Caption = '查询.参数代码'
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
        Name = '席_位_代_码'
        Caption = '席_位_代_码'
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
        Name = '参数代码'
        Caption = '参数代码'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 1
        Checker.MaxLength = 10
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sserial1'
      end
      item
        Name = '参数代码值'
        Caption = '参数代码值'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 1
        Checker.MaxLength = 10
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sserial0'
      end
      item
        Name = '操作类别'
        Caption = '操作类别'
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
        DataField = 'sstatus0'
      end
      item
        Name = '描述'
        Caption = '描述'
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
        DataField = 'snote'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|查询.查询标志（1：结算；2：交易）|查询.席位代码|查询.参数代码|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|席位代码|参数代码|参数代码值|操作员|'
        GroupIndex = 1
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Top = 344
  end
  inherited QueryRequest: TWVRequest
    ID = '结算参数查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '查询标志（1：结算；2：交易）'
        FieldName = '查询.查询标志（1：结算；2：交易）'
        DefaultValue = '1'
      end
      item
        ParamName = '席位代码'
        FieldName = '查询.席_位'
      end
      item
        ParamName = '参数代码'
        FieldName = '查询.参数代码'
      end>
    Left = 472
    Top = 344
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 164
    Top = 383
  end
  inherited AddRequest: TWVRequest
    ID = '设置结算参数'
    Bindings = <
      item
        ParamName = '席位代码'
        FieldName = '席_位_代_码'
      end
      item
        ParamName = '参数代码'
        FieldName = '参数代码'
      end
      item
        ParamName = '参数代码值'
        FieldName = '参数代码值'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别.增加'
        DefaultValue = '1'
      end>
    Top = 360
  end
  inherited DeleteRequest: TWVRequest
    ID = '设置结算参数'
    Bindings = <
      item
        ParamName = '席位代码'
        FieldName = '席_位_代_码'
      end
      item
        ParamName = '参数代码'
        FieldName = '参数代码'
      end
      item
        ParamName = '参数代码值'
        FieldName = '参数代码值'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别.删除'
        DefaultValue = '3'
      end>
    Left = 216
    Top = 344
  end
  inherited ChangeRequest: TWVRequest
    ID = '设置结算参数'
    Bindings = <
      item
        ParamName = '席位代码'
        FieldName = '席_位_代_码'
      end
      item
        ParamName = '参数代码'
        FieldName = '参数代码'
      end
      item
        ParamName = '参数代码值'
        FieldName = '参数代码值'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别.修改'
        DefaultValue = '2'
      end>
    Left = 384
    Top = 336
  end
  inherited WVDataSource: TWVDataSource
    Left = 540
    Top = 375
  end
  inherited alDatasetActions: TActionList
    Left = 332
    Top = 396
  end
end
