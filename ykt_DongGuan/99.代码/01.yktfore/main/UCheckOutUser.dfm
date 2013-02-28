inherited FrmCheckOutUser: TFrmCheckOutUser
  Width = 700
  Height = 489
  inherited pcPages: TRzPageControl
    Width = 700
    Height = 489
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 430
        Width = 696
        Height = 36
        TabOrder = 2
        inherited btnQuery: TBitBtn
          Left = 519
          Top = 5
          TabOrder = 3
        end
        inherited btnAdd: TBitBtn
          Left = 387
          TabOrder = 2
          Visible = False
        end
        inherited btnChange: TBitBtn
          Left = 601
          Top = 5
          Caption = '签出(&U)'
          TabOrder = 4
        end
        inherited btnDelete: TBitBtn
          Left = 304
          TabOrder = 1
          Visible = False
        end
        inherited btnViewDetail: TBitBtn
          TabOrder = 0
          Visible = False
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Visible = False
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 696
        TabOrder = 0
        inherited LabRecordCount: TLabel
          Left = 8
        end
      end
      inherited Grid: TRzDBGrid
        Width = 696
        Height = 412
        ReadOnly = True
        TabOrder = 1
        Columns = <
          item
            Expanded = False
            FieldName = 'scust_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '操作员代码'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '姓名'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lwithdraw_flag'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '登陆站点'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '登陆状态'
            Width = 100
            Visible = True
          end>
      end
    end
    inherited tsEdit: TRzTabSheet
      object Labeloper_code2: TLabel [0]
        Left = 78
        Top = 61
        Width = 24
        Height = 12
        Caption = '代码'
      end
      object Labelif_station9: TLabel [1]
        Left = 54
        Top = 140
        Width = 48
        Height = 12
        Caption = '登陆站点'
      end
      object Labelif_access10: TLabel [2]
        Left = 54
        Top = 180
        Width = 48
        Height = 12
        Caption = '登陆状态'
      end
      object Labeloper_name3: TLabel [3]
        Left = 78
        Top = 100
        Width = 24
        Height = 12
        Caption = '姓名'
      end
      inherited UIPanel2: TUIPanel
        Top = 430
        Width = 696
        TabOrder = 4
        inherited btnOK: TBitBtn
          Left = 531
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 615
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object edtOperCode: TWVEdit
        Left = 120
        Top = 57
        Width = 136
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 0
        Text = '<操作员代码>'
        WorkView = WorkView
        FieldName = '操作员代码'
        SynchronizeWhenExit = True
      end
      object cbbStation: TWVComboBox
        Left = 120
        Top = 138
        Width = 136
        Height = 18
        Style = csOwnerDrawFixed
        Color = clWhite
        ItemHeight = 12
        TabOrder = 2
        WorkView = WorkView
        FieldName = '登陆站点'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-33'
      end
      object cbbStat: TWVComboBox
        Left = 120
        Top = 176
        Width = 136
        Height = 18
        Style = csOwnerDrawFixed
        Color = clWhite
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView
        FieldName = '登陆状态'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '111'
      end
      object edtOpername: TWVEdit
        Left = 120
        Top = 98
        Width = 136
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<操作员姓名>'
        WorkView = WorkView
        FieldName = '操作员姓名'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 488
    Top = 176
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '返回信息'
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
        Name = '返回码'
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
        Name = '查询结果集'
        Caption = '查询结果集'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtObject
        OwnObject = True
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = '@Dataset'
      end
      item
        Name = '操作类别.增加'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '3'
      end
      item
        Name = '查询.操作员代码'
        Caption = '查询.操作员代码'
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
        Name = '操作员代码'
        Caption = '操作员代码'
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
        DataField = 'scust_no'
      end
      item
        Name = '操作员姓名'
        Caption = '操作员姓名'
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
        DataField = 'sname'
      end
      item
        Name = '登陆站点'
        Caption = '登陆站点'
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
        DataField = 'lwithdraw_flag'
      end
      item
        Name = '登陆状态'
        Caption = '登陆状态'
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
        DataField = 'sstatus4'
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
      end>
    FieldsMonitors = <
      item
      end>
    Left = 428
    Top = 143
  end
  inherited QueryRequest: TWVRequest
    ID = '签出操作员查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
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
        ParamName = '操作员代码'
        FieldName = '查询.操作员代码'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end>
    Left = 456
    Top = 144
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sstatus4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '111'
      end
      item
        FieldName = 'lwithdraw_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-33'
      end>
    Left = 457
    Top = 175
  end
  inherited AddRequest: TWVRequest
    ID = '操作员签出'
    Left = 520
    Top = 144
  end
  inherited DeleteRequest: TWVRequest
    ID = '操作员查询'
    Left = 552
    Top = 144
  end
  inherited ChangeRequest: TWVRequest
    ID = '操作员签出'
    Bindings = <
      item
        ParamName = '普通操作员号'
        FieldName = '操作员代码'
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
    Left = 488
    Top = 144
  end
  inherited WVDataSource: TWVDataSource
    Left = 553
    Top = 175
  end
  inherited alDatasetActions: TActionList
    Left = 520
    Top = 177
  end
end
