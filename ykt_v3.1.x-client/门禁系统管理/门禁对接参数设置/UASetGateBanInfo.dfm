inherited faqhSetGateBanInterface: TfaqhSetGateBanInterface
  Width = 770
  Height = 505
  Caption = '门禁参数对接设置'
  inherited pcPages: TRzPageControl
    Width = 770
    Height = 505
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 446
        Width = 766
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 506
          Top = 5
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 591
          Top = 5
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 421
          Top = 5
        end
        inherited btnDelete: TBitBtn
          Left = 676
          Top = 5
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 34
          Top = 5
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Top = 10
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 766
      end
      inherited Grid: TRzDBGrid
        Top = 49
        Width = 766
        Height = 397
        Columns = <
          item
            Expanded = False
            FieldName = 'scert_no'
            PickList.Strings = ()
            Title.Caption = '楼宇编号'
            Width = 89
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Caption = '大楼名称'
            Width = 148
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '门禁组编号'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            PickList.Strings = ()
            Title.Caption = '门禁组名称'
            Width = 142
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Caption = '备注'
            Width = 151
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 766
        Height = 31
        Align = alTop
        ParentColor = True
        TabOrder = 2
        object Label1: TLabel
          Left = 18
          Top = 10
          Width = 48
          Height = 12
          Caption = '大楼名称'
        end
        object WVEdit4: TWVEdit
          Left = 69
          Top = 6
          Width = 178
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 0
          Text = '<大楼名称>'
          WorkView = WorkView
          FieldName = '大楼名称'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 74
        Top = 85
        Width = 48
        Height = 12
        Caption = '大楼编号'
      end
      object Label3: TLabel [1]
        Left = 50
        Top = 120
        Width = 72
        Height = 12
        Caption = '大楼名称名称'
      end
      object Label6: TLabel [2]
        Left = 38
        Top = 154
        Width = 84
        Height = 12
        Caption = '对应门禁组编号'
        ParentShowHint = False
        ShowHint = True
        WordWrap = True
      end
      object Label8: TLabel [3]
        Left = 98
        Top = 189
        Width = 24
        Height = 12
        Caption = '备注'
        WordWrap = True
      end
      object Label10: TLabel [4]
        Left = 34
        Top = 5
        Width = 128
        Height = 16
        Caption = '门禁对接参数设置'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '黑体'
        Font.Style = []
        ParentFont = False
      end
      inherited UIPanel2: TUIPanel
        Top = 446
        Width = 766
        TabOrder = 1
        inherited btnOK: TBitBtn
          Left = 597
          Top = 5
        end
        inherited btnCancel: TBitBtn
          Left = 682
          Top = 5
        end
        inherited DBNavigator: TRzDBNavigator
          Left = 34
          Top = 5
          Hints.Strings = ()
        end
      end
      object WVEdit3: TWVEdit
        Left = 123
        Top = 116
        Width = 209
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 0
        Text = '<大楼名称_1>'
        WorkView = WorkView
        FieldName = '大楼名称_1'
        SynchronizeWhenExit = True
      end
      object WVEdit1: TWVEdit
        Left = 123
        Top = 150
        Width = 120
        Height = 20
        Color = clWhite
        MaxLength = 22
        ParentShowHint = False
        ReadOnly = False
        ShowHint = True
        TabOrder = 2
        Text = '<门禁组编号>'
        WorkView = WorkView
        FieldName = '门禁组编号'
      end
      object WVEdit2: TWVEdit
        Left = 123
        Top = 81
        Width = 145
        Height = 20
        ParentColor = True
        ReadOnly = True
        TabOrder = 3
        Text = '<大楼编号>'
        WorkView = WorkView
        FieldName = '大楼编号'
      end
      object WVEdit5: TWVEdit
        Left = 123
        Top = 184
        Width = 622
        Height = 20
        Color = clWhite
        ParentShowHint = False
        ReadOnly = False
        ShowHint = True
        TabOrder = 4
        Text = '<备注>'
        WorkView = WorkView
        FieldName = '备注'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 108
    Top = 383
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '大楼名称'
        Caption = '大楼名称'
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
        Name = '返回数据集'
        Caption = '返回数据集'
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
        Name = '操作码'
        Caption = '操作码'
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
        Name = '大楼编号'
        Caption = '大楼编号'
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
        DataField = 'scert_no'
      end
      item
        Name = '大楼名称_1'
        Caption = '大楼名称_1'
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
        DataField = 'scusttypes'
      end
      item
        Name = '门禁组编号'
        Caption = '门禁组编号'
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
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'vsvarstr0'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|查询.客户类别代码|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|客户类别名称|是否交搭伙费|搭伙费费率|正式卡有效期|押金金额|卡成' +
          '本费|手续金额|第一次是否收取卡成本费|是否退卡成本费|账户最大余额' +
          '|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Top = 344
  end
  inherited QueryRequest: TWVRequest
    ID = '门禁对接参数设置'
    Bindings = <
      item
        ParamName = '操作码'
        FieldName = '操作码'
      end
      item
        ParamName = 'oper.大楼名称'
        FieldName = '大楼名称'
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
        ParamName = '查询结果集'
        FieldName = '返回数据集'
        Direction = bdParam2Field
      end>
    Left = 200
    Top = 344
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '返回数据集'
    Left = 76
    Top = 383
  end
  inherited AddRequest: TWVRequest
    ID = '门禁对接参数设置'
    Bindings = <
      item
        ParamName = '操作码'
        FieldName = '操作码'
      end
      item
        ParamName = 'oper.大楼编号'
        FieldName = '大楼编号'
      end
      item
        ParamName = 'oper.大楼名称'
        FieldName = '大楼名称_1'
      end
      item
        ParamName = 'oper.门禁组'
        FieldName = '门禁组编号'
      end
      item
        ParamName = 'oper.备注'
        FieldName = '备注'
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
      end>
    Left = 104
    Top = 344
  end
  inherited DeleteRequest: TWVRequest
    ID = '门禁对接参数设置'
    Bindings = <
      item
        ParamName = 'oper.大楼编号'
        FieldName = '大楼编号'
      end
      item
        ParamName = '操作码'
        FieldName = '操作码'
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
      end>
    Left = 136
    Top = 344
  end
  inherited ChangeRequest: TWVRequest
    ID = '门禁对接参数设置'
    Bindings = <
      item
        ParamName = '操作码'
        FieldName = '操作码'
      end
      item
        ParamName = 'oper.大楼编号'
        FieldName = '大楼编号'
      end
      item
        ParamName = 'oper.大楼名称'
        FieldName = '大楼名称_1'
      end
      item
        ParamName = 'oper.门禁组'
        FieldName = '门禁组编号'
      end
      item
        ParamName = 'oper.备注'
        FieldName = '备注'
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
      end>
    Top = 344
  end
  inherited WVDataSource: TWVDataSource
    Left = 172
    Top = 383
  end
  inherited alDatasetActions: TActionList
    Left = 140
    Top = 380
  end
end
