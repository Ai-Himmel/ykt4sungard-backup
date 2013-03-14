inherited faSetAreaTable: TfaSetAreaTable
  Width = 658
  Height = 462
  inherited pcPages: TRzPageControl
    Width = 658
    Height = 462
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      object Splitter1: TSplitter [0]
        Left = 201
        Top = 33
        Width = 3
        Height = 370
        Cursor = crHSplit
      end
      inherited UIPanel1: TUIPanel
        Top = 403
        Width = 654
        Height = 36
        TabOrder = 3
        inherited btnQuery: TBitBtn
          Left = 320
          Top = 5
        end
        inherited btnAdd: TBitBtn
          Left = 401
          Top = 5
          Enabled = False
        end
        inherited btnChange: TBitBtn
          Left = 483
          Top = 5
        end
        inherited btnDelete: TBitBtn
          Left = 564
          Top = 5
        end
        inherited btnViewDetail: TBitBtn
          Left = 10
          Top = 5
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 10
        end
        inherited RBtnAddBrother: TRzRadioButton
          Top = 10
        end
        inherited RbtnAddChild: TRzRadioButton
          Left = 264
          Top = 10
        end
      end
      inherited TreeView: TRzTreeView
        Top = 33
        Width = 201
        Height = 370
        Align = alLeft
        DisabledColor = clWhite
        Enabled = False
        FrameColor = clBtnFace
        FrameHotColor = clWindowText
        TabOrder = 1
        OnDblClick = btnViewDetailClick
      end
      inherited Grid: TRzDBGrid
        Left = 204
        Top = 33
        Width = 450
        Height = 370
        Align = alClient
        ReadOnly = True
        TabOrder = 2
        OnCellClick = GridCellClick
        DisabledColor = clWhite
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '区域号'
            Width = 72
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scard0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '区域名称'
            Width = 85
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '父区域'
            Width = 84
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '区域级别'
            Width = 82
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '详细地址'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '备注'
            Width = 137
            Visible = True
          end>
      end
      object UIPanel3: TUIPanel
        Left = 0
        Top = 0
        Width = 654
        Height = 33
        Align = alTop
        Color = 16119543
        TabOrder = 0
        Visible = False
        object WVLabel2: TWVLabel
          Left = 34
          Top = 13
          Width = 24
          Height = 12
          Caption = '区域'
        end
        object WVLabel10: TWVLabel
          Left = 232
          Top = 13
          Width = 48
          Height = 12
          Caption = '区域名称'
        end
        object WVLabel11: TWVLabel
          Left = 452
          Top = 13
          Width = 48
          Height = 12
          Caption = '区域级别'
        end
        object WVComboBox1: TWVComboBox
          Left = 68
          Top = 8
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '查询.区域号'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-28'
        end
        object WVEdit6: TWVEdit
          Left = 289
          Top = 8
          Width = 120
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.区域名称>'
          WorkView = WorkView
          FieldName = '查询.区域名称'
        end
        object WVComboBox3: TWVComboBox
          Left = 507
          Top = 8
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '查询.区域级别'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*37'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object WVLabel4: TWVLabel [0]
        Left = 46
        Top = 45
        Width = 36
        Height = 12
        Caption = '区域号'
        Visible = False
      end
      object WVLabel5: TWVLabel [1]
        Left = 34
        Top = 125
        Width = 48
        Height = 12
        Caption = '父区域号'
      end
      object WVLabel6: TWVLabel [2]
        Left = 34
        Top = 165
        Width = 48
        Height = 12
        Caption = '区域名称'
      end
      object WVLabel7: TWVLabel [3]
        Left = 34
        Top = 85
        Width = 48
        Height = 12
        Caption = '区域级别'
      end
      object WVLabel8: TWVLabel [4]
        Left = 34
        Top = 205
        Width = 48
        Height = 12
        Caption = '详细地址'
      end
      object WVLabel9: TWVLabel [5]
        Left = 58
        Top = 245
        Width = 24
        Height = 12
        Caption = '备注'
      end
      inherited UIPanel2: TUIPanel
        Top = 403
        Width = 654
        TabOrder = 6
        inherited btnOK: TBitBtn
          Left = 483
          Top = 5
          Height = 26
        end
        inherited btnCancel: TBitBtn
          Left = 564
          Top = 5
          Height = 26
        end
        inherited DBNavigator: TRzDBNavigator
          Left = 18
          Top = 5
          Hints.Strings = ()
        end
      end
      object WVEdit1: TWVEdit
        Left = 96
        Top = 40
        Width = 150
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 0
        Text = '<区域号>'
        Visible = False
        WorkView = WorkView
        FieldName = '区域号'
      end
      object WVEdit3: TWVEdit
        Left = 96
        Top = 160
        Width = 150
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 3
        Text = '<区域名称>'
        WorkView = WorkView
        FieldName = '区域名称'
      end
      object WVComboBox2: TWVComboBox
        Left = 96
        Top = 80
        Width = 150
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 0
        TabOrder = 1
        Text = '<区域级别>'
        WorkView = WorkView
        FieldName = '区域级别'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '37'
      end
      object WVEdit4: TWVEdit
        Left = 96
        Top = 200
        Width = 249
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 4
        Text = '<详细地址>'
        WorkView = WorkView
        FieldName = '详细地址'
      end
      object WVEdit5: TWVEdit
        Left = 96
        Top = 240
        Width = 249
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 5
        Text = '<备注>'
        WorkView = WorkView
        FieldName = '备注'
      end
      object cbbAreaNo: TWVComboBox
        Left = 96
        Top = 120
        Width = 150
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 0
        TabOrder = 2
        Text = '<父区域号>'
        WorkView = WorkView
        FieldName = '父区域号'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '-28'
      end
    end
  end
  inherited QueryRequest: TWVRequest
    ID = '区域信息非主键查询'
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
        ParamName = '区域号'
        FieldName = '查询.区域号'
      end
      item
        ParamName = '父区域号'
        FieldName = '查询.父区域号'
      end
      item
        ParamName = '区域名称'
        FieldName = '查询.区域名称'
      end
      item
        ParamName = '区域级别'
        FieldName = '查询.区域级别'
      end
      item
        ParamName = '详细地址'
        FieldName = '查询.详细地址'
      end>
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-28'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '37'
      end>
  end
  inherited AddRequest: TWVRequest
    ID = '区域信息设置.增加'
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
        ParamName = '父区域号'
        FieldName = '父区域号'
      end
      item
        ParamName = '区域名称'
        FieldName = '区域名称'
      end
      item
        ParamName = '区域级别'
        FieldName = '区域级别'
      end
      item
        ParamName = '详细地址'
        FieldName = '详细地址'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
  end
  inherited DeleteRequest: TWVRequest
    ID = '区域信息设置.删除'
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
        ParamName = '区域号'
        FieldName = '区域号'
      end
      item
        ParamName = '父区域号'
        FieldName = '父区域号'
      end
      item
        ParamName = '区域名称'
        FieldName = '区域名称'
      end
      item
        ParamName = '区域级别'
        FieldName = '区域级别'
      end
      item
        ParamName = '详细地址'
        FieldName = '详细地址'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
  end
  inherited ChangeRequest: TWVRequest
    ID = '区域信息设置.修改'
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
        ParamName = '区域号'
        FieldName = '区域号'
      end
      item
        ParamName = '父区域号'
        FieldName = '父区域号'
      end
      item
        ParamName = '区域名称'
        FieldName = '区域名称'
      end
      item
        ParamName = '区域级别'
        FieldName = '区域级别'
      end
      item
        ParamName = '详细地址'
        FieldName = '详细地址'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
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
        GroupIndex = 1
        DataField = '@Dataset'
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
        DefaultValue = '2'
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
        DefaultValue = '3'
      end
      item
        Name = '查询.区域号'
        Caption = '查询.区域号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'lvol0'
      end
      item
        Name = '查询.父区域号'
        Caption = '查询.父区域号'
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
        Name = '查询.区域名称'
        Caption = '查询.区域名称'
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
        Name = '查询.区域级别'
        Caption = '查询.区域级别'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '0'
      end
      item
        Name = '查询.详细地址'
        Caption = '查询.详细地址'
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
        Name = '区域号'
        Caption = '区域号'
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
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '父区域号'
        Caption = '父区域号'
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
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '区域名称'
        Caption = '区域名称'
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
        DataField = 'scard0'
      end
      item
        Name = '区域级别'
        Caption = '区域级别'
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
        GroupIndex = 1
        DataField = 'lvol2'
      end
      item
        Name = '详细地址'
        Caption = '详细地址'
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
        DataField = 'scusttypes'
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
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'ssectypes'
      end>
  end
end
