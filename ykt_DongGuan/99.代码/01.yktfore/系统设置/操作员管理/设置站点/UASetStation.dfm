inherited faqhSetStation: TfaqhSetStation
  Width = 752
  Height = 523
  Caption = '设置站点'
  inherited pcPages: TRzPageControl
    Width = 752
    Height = 523
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 464
        Width = 748
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 493
          Top = 5
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 575
          Top = 5
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 410
          Top = 5
        end
        inherited btnDelete: TBitBtn
          Left = 658
          Top = 5
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 10
          Top = 5
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 92
          Top = 10
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 748
        Align = alNone
        TabOrder = 1
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 748
        Height = 431
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Caption = '站点号'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Caption = '站点名称'
            Width = 119
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone'
            PickList.Strings = ()
            Title.Caption = 'ip地址'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scard1'
            PickList.Strings = ()
            Title.Caption = '机器码'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote'
            PickList.Strings = ()
            Title.Caption = '备注'
            Width = 200
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 748
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Labelsite_no1: TLabel
          Left = 34
          Top = 13
          Width = 36
          Height = 12
          Caption = '站点号'
        end
        object WVComboBox6: TWVComboBox
          Left = 77
          Top = 8
          Width = 156
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '查询.站点号'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-33'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Labelsite_no2: TLabel [0]
        Left = 47
        Top = 29
        Width = 36
        Height = 12
        Caption = '站点号'
      end
      object Labelmachine_name5: TLabel [1]
        Left = 29
        Top = 69
        Width = 54
        Height = 12
        Caption = '站点名称*'
      end
      object Labelip_addr3: TLabel [2]
        Left = 41
        Top = 109
        Width = 42
        Height = 12
        Caption = 'IP地址*'
      end
      object Label2: TLabel [3]
        Left = 286
        Top = 109
        Width = 252
        Height = 12
        Caption = '格式“***.***.***.***“，例如：192.34.0.98'
      end
      object Label1: TLabel [4]
        Left = 286
        Top = 237
        Width = 234
        Height = 12
        Caption = '网卡地址必须为12位0-9或者A-F之间的字符 '
        Visible = False
      end
      object Labelmac_addr4: TLabel [5]
        Left = 32
        Top = 237
        Width = 48
        Height = 12
        Caption = '网卡地址'
        Visible = False
      end
      object Labelnotes6: TLabel [6]
        Left = 59
        Top = 149
        Width = 24
        Height = 12
        Caption = '备注'
      end
      inherited UIPanel2: TUIPanel
        Top = 464
        Width = 748
        TabOrder = 5
        inherited btnOK: TBitBtn
          Left = 576
          Top = 5
          Enabled = False
        end
        inherited btnCancel: TBitBtn
          Left = 658
          Top = 5
        end
        inherited DBNavigator: TRzDBNavigator
          Left = 34
          Top = 5
          Hints.Strings = ()
        end
      end
      object edtSiteNo: TWVEdit
        Left = 89
        Top = 24
        Width = 188
        Height = 20
        Color = clWhite
        MaxLength = 10
        ReadOnly = False
        TabOrder = 0
        Text = '<站点号>'
        WorkView = WorkView
        FieldName = '站点号'
        SynchronizeWhenExit = True
      end
      object WVEditmachine_name5: TWVEdit
        Left = 89
        Top = 64
        Width = 188
        Height = 20
        Color = clInfoBk
        MaxLength = 32
        ReadOnly = False
        TabOrder = 1
        Text = '<机器名称>'
        WorkView = WorkView
        FieldName = '机器名称'
        SynchronizeWhenExit = True
      end
      object WVEditip_addr3: TWVEdit
        Left = 89
        Top = 104
        Width = 188
        Height = 20
        Color = clInfoBk
        MaxLength = 15
        ReadOnly = False
        TabOrder = 2
        Text = '<ip地址>'
        WorkView = WorkView
        FieldName = 'ip地址'
        SynchronizeWhenExit = True
      end
      object WVEditmac_addr4: TWVEdit
        Left = 89
        Top = 232
        Width = 188
        Height = 20
        CharCase = ecUpperCase
        Color = clWhite
        MaxLength = 20
        ReadOnly = False
        TabOrder = 4
        Visible = False
        SynchronizeWhenExit = True
      end
      object WVEditnotes6: TWVEdit
        Left = 89
        Top = 143
        Width = 456
        Height = 20
        Color = clWhite
        MaxLength = 100
        ReadOnly = False
        TabOrder = 3
        Text = '<备注>'
        WorkView = WorkView
        FieldName = '备注'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 94
    Top = 375
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
      end
      item
        Name = '查询.站点号'
        Caption = '查询.站点号'
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
        DefaultValue = '0'
        GetPrevChar = '*'
      end
      item
        Name = '站点号'
        Caption = '站点号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 1
        Checker.MaxLength = 10
        Checker.DefaultValid = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = 'ip地址'
        Caption = 'ip地址'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 15
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sphone'
      end
      item
        Name = '网卡物理地址'
        Caption = '网卡物理地址'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 20
        Checker.LowerCase = False
        Checker.UpperCase = True
        GetPrevChar = '*'
      end
      item
        Name = '机器名称'
        Caption = '机器名称'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 1
        Checker.MaxLength = 32
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'scust_limit'
      end
      item
        Name = '备注'
        Caption = '备注'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 100
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'snote'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|查询.站点号|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|IP地址|网卡物理地址|机器名称|'
        GroupIndex = 1
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 96
    Top = 336
  end
  inherited QueryRequest: TWVRequest
    ID = '站点信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '站点号'
        FieldName = '查询.站点号'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end>
    Left = 192
    Top = 296
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 132
    Top = 335
  end
  inherited AddRequest: TWVRequest
    ID = '设置站点'
    Bindings = <
      item
        ParamName = '站点号'
        FieldName = '站点号'
      end
      item
        ParamName = 'ip地址'
        FieldName = 'ip地址'
      end
      item
        ParamName = '网卡物理地址'
        FieldName = '网卡物理地址'
      end
      item
        ParamName = '机器名称'
        FieldName = '机器名称'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end>
    Left = 96
    Top = 296
  end
  inherited DeleteRequest: TWVRequest
    ID = '设置站点'
    Bindings = <
      item
        ParamName = '站点号'
        FieldName = '站点号'
      end
      item
        ParamName = 'ip地址'
        FieldName = 'ip地址'
      end
      item
        ParamName = '网卡物理地址'
        FieldName = '网卡物理地址'
      end
      item
        ParamName = '机器名称'
        FieldName = '机器名称'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
        DefaultValue = '3'
      end>
    Left = 128
    Top = 296
  end
  inherited ChangeRequest: TWVRequest
    ID = '设置站点'
    Bindings = <
      item
        ParamName = '站点号'
        FieldName = '站点号'
      end
      item
        ParamName = 'ip地址'
        FieldName = 'ip地址'
      end
      item
        ParamName = '网卡物理地址'
        FieldName = '网卡物理地址'
      end
      item
        ParamName = '机器名称'
        FieldName = '机器名称'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end>
    Left = 160
    Top = 296
  end
  inherited WVDataSource: TWVDataSource
    Left = 164
    Top = 335
  end
  inherited alDatasetActions: TActionList
    Left = 196
    Top = 334
  end
end
