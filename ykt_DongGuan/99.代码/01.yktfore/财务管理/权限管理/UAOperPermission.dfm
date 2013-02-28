inherited faqhOperPermission: TfaqhOperPermission
  Width = 681
  Height = 477
  Caption = '财务操作权限'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 418
        Width = 677
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 503
          Top = 5
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 502
          Top = 1000
          Enabled = False
          TabOrder = 5
        end
        inherited btnQuery: TBitBtn [2]
          Left = 418
          Top = 5
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Top = 5
          Enabled = False
          TabOrder = 3
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
          Top = 5
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 104
          Top = 10
          Width = 169
          TabOrder = 4
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 49
        Width = 677
        Height = 369
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '操作员号'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '操作员名称'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '权限类别'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_addr'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '权限名称'
            Width = 120
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 31
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label1: TLabel
          Left = 26
          Top = 8
          Width = 36
          Height = 12
          Caption = '操作员'
        end
        object WVLabel1: TWVLabel
          Left = 232
          Top = 8
          Width = 48
          Height = 12
          Caption = '权限类别'
        end
        object cbbVoucherType: TWVComboBox
          Left = 68
          Top = 3
          Width = 133
          Height = 20
          Style = csDropDownList
          Color = clWhite
          DropDownCount = 12
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '查询.操作员号'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-30'
        end
        object WVComboBox1: TWVComboBox
          Left = 292
          Top = 3
          Width = 141
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 1
          WorkView = WorkView
          FieldName = '查询.权限类别'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-62'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 90
        Top = 96
        Width = 36
        Height = 12
        Caption = '操作员'
      end
      object WVLabel2: TWVLabel [1]
        Left = 78
        Top = 144
        Width = 48
        Height = 12
        Caption = '权限类别'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 2
        inherited btnOK: TBitBtn
          Left = 504
          Top = 5
        end
        inherited btnCancel: TBitBtn
          Left = 587
          Top = 5
        end
        inherited DBNavigator: TRzDBNavigator
          Left = 34
          Top = 5
          Hints.Strings = ()
        end
      end
      object cbbOperNo: TWVComboBox
        Left = 132
        Top = 91
        Width = 189
        Height = 20
        Style = csDropDownList
        Color = clWhite
        DropDownCount = 12
        ItemHeight = 12
        TabOrder = 0
        WorkView = WorkView
        FieldName = '操作员号'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-30'
      end
      object cbbLimit: TWVComboBox
        Left = 132
        Top = 139
        Width = 189
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 1
        WorkView = WorkView
        FieldName = '权限类别'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-62'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 204
    Top = 335
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
        Name = '查询.操作员号'
        Caption = '查询.操作员号'
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
        Name = '查询.权限类别'
        Caption = '查询.权限类别'
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
        Name = '查询.操作员名称'
        Caption = '查询.操作员名称'
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
        Name = '操作员号'
        Caption = '操作员号'
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
        DataField = 'semp_no'
      end
      item
        Name = '权限类别'
        Caption = '权限类别'
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
        DataField = 'lvol1'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|查询.专业代码|'
      end
      item
        MonitorValueChangedFields = '|专业代码|专业名称|'
      end>
    Left = 71
    Top = 336
  end
  inherited QueryRequest: TWVRequest
    ID = '财务权限管理查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作员号'
        FieldName = '查询.操作员号'
      end
      item
        ParamName = '操作员名称'
        FieldName = '查询.操作员名称'
      end
      item
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '权限类别'
        FieldName = '查询.权限类别'
      end>
    Left = 168
    Top = 296
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 104
    Top = 335
  end
  inherited AddRequest: TWVRequest
    ID = '财务权限管理'
    Bindings = <
      item
        ParamName = '权限类别'
        FieldName = '权限类别'
      end
      item
        ParamName = '操作员号'
        FieldName = '操作员号'
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
        ParamName = '标志'
        FieldName = '标志'
      end>
    Left = 72
    Top = 296
  end
  inherited DeleteRequest: TWVRequest
    ID = '财务权限管理'
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
        ParamName = '操作员号'
        FieldName = '操作员号'
      end
      item
        ParamName = '权限类别'
        FieldName = '权限类别'
      end>
    Left = 104
    Top = 296
  end
  inherited ChangeRequest: TWVRequest
    ID = '财务权限管理'
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
        ParamName = '操作员号'
        FieldName = '操作员号'
      end
      item
        ParamName = '权限类别'
        FieldName = '权限类别'
      end>
    Left = 136
    Top = 296
  end
  inherited WVDataSource: TWVDataSource
    Left = 168
    Top = 335
  end
  inherited alDatasetActions: TActionList
    Left = 136
    Top = 335
  end
end
