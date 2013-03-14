inherited faqhSetUnitInfo: TfaqhSetUnitInfo
  Width = 773
  Height = 465
  Caption = '单位信息设置'
  inherited pcPages: TRzPageControl
    Width = 773
    Height = 465
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      object Splitter1: TSplitter [0]
        Left = 185
        Top = 36
        Width = 5
        Height = 370
        Cursor = crHSplit
      end
      inherited UIPanel1: TUIPanel
        Top = 406
        Width = 769
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 521
          Top = 5
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 604
          Top = 5
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 437
          Top = 5
        end
        inherited btnDelete: TBitBtn
          Left = 688
          Top = 5
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 10
          Top = 5
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 10
          Checked = False
          State = cbUnchecked
          Visible = False
        end
        inherited RBtnAddBrother: TRzRadioButton
          Top = 10
          Anchors = [akLeft, akBottom]
        end
        inherited RbtnAddChild: TRzRadioButton
          Top = 10
          Anchors = [akLeft, akBottom]
        end
      end
      inherited TreeView: TRzTreeView
        Top = 36
        Width = 185
        Height = 370
        Align = alLeft
        DisabledColor = clCaptionText
        Enabled = False
        FrameColor = clCaptionText
        FrameHotColor = clInactiveCaption
        TabOrder = 1
      end
      inherited Grid: TRzDBGrid
        Left = 190
        Top = 36
        Width = 579
        Height = 370
        Align = alClient
        TabOrder = 2
        OnCellClick = GridCellClick
        DisabledColor = clHighlightText
        Columns = <
          item
            Expanded = False
            FieldName = 'sbranch_code0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '所属区域'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '部门代码'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '原部门编码'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '部门名称'
            Width = 132
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '部门全称'
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '上级部门'
            Width = 142
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '英文名称'
            Width = 157
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 769
        Height = 36
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label1: TLabel
          Left = 34
          Top = 12
          Width = 48
          Height = 12
          Caption = '部门代码'
        end
        object WVLabel2: TWVLabel
          Left = 208
          Top = 12
          Width = 48
          Height = 12
          Caption = '部门名称'
        end
        object WVLabel4: TWVLabel
          Left = 440
          Top = 12
          Width = 48
          Height = 12
          Caption = '上级部门'
        end
        object WVEdit1: TWVEdit
          Left = 92
          Top = 9
          Width = 100
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.单位代码>'
          WorkView = WorkView
          FieldName = '查询.单位代码'
        end
        object WVEdit3: TWVEdit
          Left = 268
          Top = 9
          Width = 157
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
          Text = '<查询.单位名称>'
          WorkView = WorkView
          FieldName = '查询.单位名称'
        end
        object WVEdit6: TWVEdit
          Left = 496
          Top = 9
          Width = 97
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 2
          Text = '<查询.上级单位>'
          WorkView = WorkView
          FieldName = '查询.上级单位'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 58
        Top = 45
        Width = 48
        Height = 12
        Caption = '部门代码'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel [1]
        Left = 52
        Top = 125
        Width = 54
        Height = 12
        Caption = '部门名称*'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label5: TLabel [2]
        Left = 58
        Top = 245
        Width = 48
        Height = 12
        Caption = '英文名称'
      end
      object Label6: TLabel [3]
        Left = 452
        Top = 388
        Width = 48
        Height = 12
        Caption = '上级单位'
        Visible = False
      end
      object lbl1: TLabel [4]
        Left = 452
        Top = 356
        Width = 48
        Height = 12
        Caption = '上级单位'
        Visible = False
      end
      object Label3: TLabel [5]
        Left = 58
        Top = 204
        Width = 48
        Height = 12
        Caption = '所属区域'
      end
      object Label7: TLabel [6]
        Left = 46
        Top = 85
        Width = 60
        Height = 12
        Caption = '原部门代码'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label8: TLabel [7]
        Left = 59
        Top = 165
        Width = 48
        Height = 12
        Caption = '部门全称'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      inherited UIPanel2: TUIPanel
        Top = 406
        Width = 769
        TabOrder = 9
        inherited btnOK: TBitBtn
          Left = 597
          Top = 5
          TabOrder = 0
        end
        inherited btnCancel: TBitBtn
          Left = 679
          Top = 5
          TabOrder = 1
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 2
        end
      end
      object edtDeptNO: TWVEdit
        Left = 119
        Top = 40
        Width = 250
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 0
        Text = '<单位代码>'
        WorkView = WorkView
        FieldName = '单位代码'
        SynchronizeWhenExit = True
      end
      object WVEdit4: TWVEdit
        Left = 119
        Top = 120
        Width = 250
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 2
        Text = '<单位名称>'
        WorkView = WorkView
        FieldName = '单位名称'
        SynchronizeWhenExit = True
      end
      object WVEdit5: TWVEdit
        Left = 119
        Top = 240
        Width = 250
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 5
        Text = '<英文名称>'
        WorkView = WorkView
        FieldName = '英文名称'
        SynchronizeWhenExit = True
      end
      object WVComboBox3: TWVComboBox
        Left = 511
        Top = 384
        Width = 250
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 8
        Visible = False
        WorkView = WorkView
        FieldName = '上级单位'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-22'
      end
      object edtDeptNo11: TWVEdit
        Left = 512
        Top = 352
        Width = 73
        Height = 20
        ParentColor = True
        ReadOnly = True
        TabOrder = 6
        Text = '<上级单位>'
        Visible = False
        WorkView = WorkView
        FieldName = '上级单位'
        SynchronizeWhenExit = True
      end
      object edtdeptName: TWVEdit
        Left = 584
        Top = 352
        Width = 177
        Height = 20
        ParentColor = True
        ReadOnly = True
        TabOrder = 7
        Text = '<单位名称>'
        Visible = False
        WorkView = WorkView
        SynchronizeWhenExit = True
      end
      object WVComboBox1: TWVComboBox
        Left = 119
        Top = 200
        Width = 250
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 4
        WorkView = WorkView
        FieldName = '所属区域'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-27'
      end
      object WVEdit2: TWVEdit
        Left = 119
        Top = 80
        Width = 250
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<旧部门代码>'
        WorkView = WorkView
        FieldName = '旧部门代码'
        SynchronizeWhenExit = True
      end
      object WVEdit7: TWVEdit
        Left = 119
        Top = 160
        Width = 250
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 3
        Text = '<部门全称>'
        WorkView = WorkView
        FieldName = '部门全称'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 604
    Top = 327
  end
  inherited QueryRequest: TWVRequest
    ID = '单位信息查询一'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '单位代码'
        FieldName = '查询.单位代码'
      end
      item
        ParamName = '单位名称'
        FieldName = '查询.单位名称'
      end
      item
        ParamName = '上级单位'
        FieldName = '查询.上级单位'
      end
      item
        ParamName = '英文名称'
        FieldName = '查询.英文名称'
      end
      item
        ParamName = '操作类别'
        FieldName = '查询.操作类别'
      end>
    Left = 704
    Top = 288
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'semail2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end>
    Left = 572
    Top = 327
  end
  inherited AddRequest: TWVRequest
    ID = '单位信息设置'
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
        ParamName = '单位代码'
        FieldName = '单位代码'
      end
      item
        ParamName = '单位名称'
        FieldName = '单位名称'
      end
      item
        ParamName = '英文名称'
        FieldName = '英文名称'
      end
      item
        ParamName = '所属区域'
        FieldName = '所属区域'
      end
      item
        ParamName = '上级单位'
        FieldName = '上级单位'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end
      item
        ParamName = '旧部门代码'
        FieldName = '旧部门代码'
      end>
    Left = 608
    Top = 288
  end
  inherited DeleteRequest: TWVRequest
    ID = '单位信息设置'
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
        ParamName = '单位代码'
        FieldName = '单位代码'
      end
      item
        ParamName = '单位名称'
        FieldName = '单位名称'
      end
      item
        ParamName = '英文名称'
        FieldName = '英文名称'
      end
      item
        ParamName = '上级单位'
        FieldName = '上级单位'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end
      item
        ParamName = '所属区域'
        FieldName = '所属区域'
      end>
    Left = 640
    Top = 288
  end
  inherited ChangeRequest: TWVRequest
    ID = '单位信息设置'
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
        ParamName = '单位代码'
        FieldName = '单位代码'
      end
      item
        ParamName = '单位名称'
        FieldName = '单位名称'
      end
      item
        ParamName = '英文名称'
        FieldName = '英文名称'
      end
      item
        ParamName = '上级单位'
        FieldName = '上级单位'
      end
      item
        ParamName = '所属区域'
        FieldName = '所属区域'
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end
      item
        ParamName = '旧部门代码'
        FieldName = '旧部门代码'
      end>
    Left = 672
    Top = 288
  end
  inherited WVDataSource: TWVDataSource
    Left = 676
    Top = 327
  end
  inherited alDatasetActions: TActionList
    Left = 636
    Top = 324
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
        Name = '查询.单位代码'
        Caption = '查询.单位代码'
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
        Name = '查询.单位名称'
        Caption = '查询.单位名称'
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
        Name = '查询.英文名称'
        Caption = '查询.英文名称'
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
        Name = '查询.上级单位'
        Caption = '查询.上级单位'
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
        Name = '查询.操作类别'
        Caption = '查询.操作类别'
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
        Name = '单位代码'
        Caption = '单位代码'
        FieldType = wftUndefined
        DomainName = '非空'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scert_no'
      end
      item
        Name = '英文名称'
        Caption = '英文名称'
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
        DataField = 'ssectypes'
      end
      item
        Name = '单位名称'
        Caption = '单位名称'
        FieldType = wftUndefined
        DomainName = '非空'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scusttypes'
      end
      item
        Name = '上级单位'
        Caption = '上级单位'
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
        DataField = 'semail2'
      end
      item
        Name = '所属区域'
        Caption = '所属区域'
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
        DataField = 'sbranch_code0'
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
        Name = '旧部门代码'
        Caption = '旧部门代码'
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
        DataField = 'scert_no2'
      end
      item
        Name = '部门全称'
        Caption = '部门全称'
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
        MonitorValueChangedFields = '|查询.单位代码|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValidChangedFields = '|单位代码|单位名称|是否院系|'
      end>
    Left = 564
    Top = 288
  end
  object WorkView1: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        FieldType = wftUndefined
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
        Name = '单位代码'
        Caption = '单位代码'
        FieldType = wftUndefined
        DomainName = '非空'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_no'
      end
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|查询.单位代码|'
      end
      item
        MonitorValidChangedFields = '|单位代码|单位名称|是否院系|'
      end>
    Left = 396
    Top = 192
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '单位信息主键查询一'
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
        ParamName = '单位代码'
        FieldName = '单位代码'
      end
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end>
    AfterExec = CheckReturnData
    Left = 432
    Top = 192
  end
end
