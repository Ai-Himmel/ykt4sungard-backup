inherited faqhSetWaterPrice: TfaqhSetWaterPrice
  Width = 681
  Height = 477
  Caption = '汇多水价设置'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 677
        TabOrder = 1
        inherited btnAdd: TBitBtn [0]
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 499
          Enabled = False
          TabOrder = 4
        end
        inherited btnQuery: TBitBtn [2]
          Left = 322
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Width = 161
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
        TabOrder = 3
      end
      inherited Grid: TRzDBGrid
        Top = 49
        Width = 677
        Height = 375
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '收费类别'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '水价1(单位:分)'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '水价2(单位:分)'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '水价3(单位:分)'
            Width = 100
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
        TabOrder = 0
        object Label2: TLabel
          Left = 18
          Top = 10
          Width = 48
          Height = 12
          Caption = '收费类别'
        end
        object cbbFee: TWVComboBox
          Left = 72
          Top = 5
          Width = 131
          Height = 20
          Style = csDropDownList
          Color = clBtnHighlight
          ItemHeight = 0
          TabOrder = 0
          Text = '<查询.收费类别>'
          WorkView = WorkView
          FieldName = '查询.收费类别'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-44'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label6: TLabel [0]
        Left = 42
        Top = 100
        Width = 48
        Height = 12
        Caption = '收费类别'
      end
      object Label7: TLabel [1]
        Left = 60
        Top = 137
        Width = 30
        Height = 12
        Caption = '水价1'
      end
      object Label8: TLabel [2]
        Left = 60
        Top = 175
        Width = 30
        Height = 12
        Caption = '水价2'
      end
      object Label1: TLabel [3]
        Left = 60
        Top = 212
        Width = 30
        Height = 12
        Caption = '水价3'
      end
      object Label3: TLabel [4]
        Left = 252
        Top = 138
        Width = 48
        Height = 12
        AutoSize = False
        Caption = '单位：分'
      end
      object Label4: TLabel [5]
        Left = 252
        Top = 176
        Width = 48
        Height = 12
        AutoSize = False
        Caption = '单位：分'
      end
      object Label5: TLabel [6]
        Left = 252
        Top = 212
        Width = 48
        Height = 12
        AutoSize = False
        Caption = '单位：分'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
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
      object cbbFeeType: TWVComboBox
        Left = 97
        Top = 96
        Width = 151
        Height = 20
        Style = csDropDownList
        Color = clBtnHighlight
        ItemHeight = 12
        TabOrder = 1
        WorkView = WorkView
        FieldName = '收费类别'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-44'
      end
      object edtP3: TWVEdit
        Left = 97
        Top = 208
        Width = 151
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 2
        Text = '<水价3>'
        WorkView = WorkView
        FieldName = '水价3'
        SynchronizeWhenExit = True
      end
      object edtP2: TWVEdit
        Left = 97
        Top = 171
        Width = 151
        Height = 20
        Color = clBtnHighlight
        MaxLength = 22
        ReadOnly = False
        TabOrder = 3
        Text = '<水价2>'
        WorkView = WorkView
        FieldName = '水价2'
        SynchronizeWhenExit = True
      end
      object edtP1: TWVEdit
        Left = 97
        Top = 133
        Width = 151
        Height = 20
        Color = clBtnHighlight
        MaxLength = 22
        ReadOnly = False
        TabOrder = 4
        Text = '<水价1>'
        WorkView = WorkView
        FieldName = '水价1'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 428
    Top = 279
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
        Name = '操作标志'
        Caption = '操作标志'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '查询.收费类别'
        Caption = '查询.收费类别'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '收费类别'
        Caption = '收费类别'
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
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '水价1'
        Caption = '水价1'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '水价2'
        Caption = '水价2'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '水价3'
        Caption = '水价3'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol2'
      end>
    InvalidColor = clBtnHighlight
    Left = 360
    Top = 240
  end
  inherited QueryRequest: TWVRequest
    ID = '汇多水价设置查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '收费类别'
        FieldName = '查询.收费类别'
      end>
    Left = 504
    Top = 240
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '-44'
      end>
    Left = 388
    Top = 279
  end
  inherited AddRequest: TWVRequest
    ID = '汇多水价设置'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '水价1'
        FieldName = '水价1'
      end
      item
        ParamName = '水价2'
        FieldName = '水价2'
      end
      item
        ParamName = '水价3'
        FieldName = '水价3'
      end>
    Left = 392
    Top = 240
  end
  inherited DeleteRequest: TWVRequest
    ID = '汇多水价设置'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '水价1'
        FieldName = '水价1'
      end
      item
        ParamName = '水价2'
        FieldName = '水价2'
      end
      item
        ParamName = '水价3'
        FieldName = '水价3'
      end>
    Left = 432
    Top = 240
  end
  inherited ChangeRequest: TWVRequest
    ID = '汇多水价设置'
    Bindings = <
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '水价1'
        FieldName = '水价1'
      end
      item
        ParamName = '水价2'
        FieldName = '水价2'
      end
      item
        ParamName = '水价3'
        FieldName = '水价3'
      end>
    Left = 472
    Top = 240
  end
  inherited WVDataSource: TWVDataSource
    Left = 516
    Top = 279
  end
  inherited alDatasetActions: TActionList
    Left = 476
    Top = 276
  end
end
