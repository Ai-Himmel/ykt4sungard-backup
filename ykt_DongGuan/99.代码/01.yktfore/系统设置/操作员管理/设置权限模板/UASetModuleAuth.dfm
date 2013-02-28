inherited faqhSetModuleAuth: TfaqhSetModuleAuth
  Width = 681
  Height = 477
  Caption = '设置权限模板'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 677
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 416
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 502
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 330
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
        Align = alNone
        TabOrder = 2
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 677
        Height = 391
        Columns = <
          item
            Expanded = False
            FieldName = 'sbank_code'
            PickList.Strings = ()
            Title.Caption = '模板代码'
            Width = 134
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth2'
            PickList.Strings = ()
            Title.Caption = '模板名称'
            Width = 181
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 677
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Labelmodule_code2: TLabel
          Left = 42
          Top = 10
          Width = 48
          Height = 12
          Caption = '权限模板'
        end
        object WVEditmodule_code2: TWVEdit
          Left = 100
          Top = 6
          Width = 100
          Height = 20
          Enabled = False
          ParentColor = True
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.模板代码>'
          Visible = False
          WorkView = WorkView
          FieldName = '查询.模板代码'
        end
        object WVComboBox1: TWVComboBox
          Left = 100
          Top = 6
          Width = 125
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 0
          TabOrder = 1
          Text = '<查询.模板代码>'
          WorkView = WorkView
          FieldName = '查询.模板代码'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-29'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 2
        inherited btnOK: TBitBtn
          Left = 501
        end
        inherited btnCancel: TBitBtn
          Left = 589
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object Panel2: TPanel
        Left = 0
        Top = 105
        Width = 677
        Height = 313
        Align = alClient
        BevelOuter = bvNone
        ParentColor = True
        TabOrder = 1
        inline faAuth1: TfaAuth
          Left = 83
          Width = 594
          Height = 313
          Align = alClient
          TabOrder = 1
          inherited TreeView: TTreeView
            Width = 594
            Height = 313
            OnKeyDown = faAuth1TreeViewKeyDown
          end
          inherited ImageList: TImageList
            Left = 184
            Top = 32
          end
        end
        object Panel4: TPanel
          Left = 0
          Top = 0
          Width = 83
          Height = 313
          Align = alLeft
          BevelOuter = bvNone
          ParentColor = True
          TabOrder = 0
          object Label1: TLabel
            Left = 25
            Top = 3
            Width = 48
            Height = 12
            Caption = '菜单权限'
          end
        end
      end
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 677
        Height = 105
        Align = alTop
        BevelOuter = bvNone
        ParentColor = True
        TabOrder = 0
        object Labelmodule_name4: TLabel
          Left = 26
          Top = 68
          Width = 48
          Height = 12
          Caption = '模板名称'
        end
        object Labelmodule_code3: TLabel
          Left = 26
          Top = 28
          Width = 48
          Height = 12
          Caption = '模板代码'
        end
        object WVEditmodule_name4: TWVEdit
          Left = 84
          Top = 64
          Width = 100
          Height = 20
          Color = clInfoBk
          MaxLength = 20
          ReadOnly = False
          TabOrder = 1
          Text = '<模板名称>'
          WorkView = WorkView
          FieldName = '模板名称'
          SynchronizeWhenExit = True
        end
        object WVEditmodule_code3: TWVEdit
          Left = 84
          Top = 24
          Width = 100
          Height = 20
          Color = clInfoBk
          MaxLength = 6
          ReadOnly = False
          TabOrder = 0
          Text = '<模板代码>'
          WorkView = WorkView
          FieldName = '模板代码'
          SynchronizeWhenExit = True
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 276
    Top = 199
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
        Name = '查询.模板代码'
        Caption = '查询.模板代码'
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
        Name = '模板代码'
        Caption = '模板代码'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 1
        Checker.MaxLength = 6
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sbank_code'
      end
      item
        Name = '模板名称'
        Caption = '模板名称'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 1
        Checker.MaxLength = 20
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'scust_auth2'
      end
      item
        Name = '菜单权限1'
        Caption = '菜单权限1'
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
        DataField = 'vsvarstr0'
      end
      item
        Name = '菜单权限2'
        Caption = '菜单权限2'
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
        DataField = 'vsvarstr1'
      end
      item
        Name = '菜单权限3'
        Caption = '菜单权限3'
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
        DataField = 'vsvarstr2'
      end
      item
        Name = '菜单权限4'
        Caption = '菜单权限4'
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
        DataField = 'vsvarstr3'
      end
      item
        Name = '功能权限'
        Caption = '功能权限'
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
        DataField = 'usset1'
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
        MonitorValueChangedFields = '|模板代码|模板名称|菜单权限|功能权限|'
        GroupIndex = 1
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 192
    Top = 160
  end
  inherited QueryRequest: TWVRequest
    ID = '权限模板查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '模板代码'
        FieldName = '查询.模板代码'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end>
    Left = 352
    Top = 160
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 236
    Top = 199
  end
  inherited AddRequest: TWVRequest
    ID = '设置权限模板'
    Bindings = <
      item
        ParamName = '模板代码'
        FieldName = '模板代码'
      end
      item
        ParamName = '模板名称'
        FieldName = '模板名称'
      end
      item
        ParamName = '功能权限'
        FieldName = '功能权限'
      end
      item
        ParamName = '菜单权限1'
        FieldName = '菜单权限1'
      end
      item
        ParamName = '菜单权限2'
        FieldName = '菜单权限2'
      end
      item
        ParamName = '菜单权限3'
        FieldName = '菜单权限3'
      end
      item
        ParamName = '菜单权限4'
        FieldName = '菜单权限4'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end>
    Left = 232
    Top = 160
  end
  inherited DeleteRequest: TWVRequest
    ID = '设置权限模板'
    Bindings = <
      item
        ParamName = '模板代码'
        FieldName = '模板代码'
      end
      item
        ParamName = '模板名称'
        FieldName = '模板名称'
      end
      item
        ParamName = '功能权限'
        FieldName = '功能权限'
      end
      item
        ParamName = '菜单权限1'
        FieldName = '菜单权限1'
      end
      item
        ParamName = '菜单权限2'
        FieldName = '菜单权限2'
      end
      item
        ParamName = '菜单权限3'
        FieldName = '菜单权限3'
      end
      item
        ParamName = '菜单权限4'
        FieldName = '菜单权限4'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end>
    Left = 272
    Top = 160
  end
  inherited ChangeRequest: TWVRequest
    ID = '设置权限模板'
    Bindings = <
      item
        ParamName = '模板代码'
        FieldName = '模板代码'
      end
      item
        ParamName = '模板名称'
        FieldName = '模板名称'
      end
      item
        ParamName = '功能权限'
        FieldName = '功能权限'
      end
      item
        ParamName = '菜单权限1'
        FieldName = '菜单权限1'
      end
      item
        ParamName = '菜单权限2'
        FieldName = '菜单权限2'
      end
      item
        ParamName = '菜单权限3'
        FieldName = '菜单权限3'
      end
      item
        ParamName = '菜单权限4'
        FieldName = '菜单权限4'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end>
    Left = 312
    Top = 160
  end
  inherited WVDataSource: TWVDataSource
    Left = 356
    Top = 199
  end
  inherited alDatasetActions: TActionList
    Left = 316
    Top = 196
  end
end
