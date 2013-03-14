inherited faqhSetSpeInfoByKey: TfaqhSetSpeInfoByKey
  Width = 681
  Height = 477
  Caption = '专业信息设置'
  inherited pcPages: TPageControl
    Width = 681
    Height = 477
    inherited tsQuery: TTabSheet
      inherited UIPanel1: TUIPanel
        Top = 420
        Width = 673
        TabOrder = 1
        inherited btnAdd: TBitBtn [0]
          Left = 415
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 503
          Enabled = False
          TabOrder = 1
        end
        inherited btnQuery: TBitBtn [2]
          Left = 322
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
          TabOrder = 2
        end
      end
      inherited Grid: TDBGrid
        Left = 0
        Top = 97
        Width = 673
        Height = 323
        Align = alClient
        TabOrder = 2
        OnDrawColumnCell = GridDrawColumnCell
        Columns = <
      item
        Expanded = False
        FieldName = 'sstation0'
        PickList.Strings = ()
        Title.Caption = '专业代码'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sname'
        PickList.Strings = ()
        Title.Caption = '专业名称'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'usset2'
        PickList.Strings = ()
        Title.Caption = '备注'
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
        object Label4: TLabel
          Left = 42
          Top = 5
          Width = 128
          Height = 16
          Caption = '专业信息查询'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = '黑体'
          Font.Style = []
          ParentFont = False
        end
    object Label1: TLabel
      Left    = 42
      Top     = 34
      Width   = 48
      Height  = 12
      Caption = '专业代码'
    end
    object WVComboBox1: TWVComboBox
      Left = 100
      Top = 30
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '查询.专业代码'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '10'
    end
      end
    end
    inherited tsEdit: TTabSheet
    object Label2: TLabel [0]
      Left    = 42
      Top     = 44
      Width   = 48
      Height  = 12
      Caption = '专业代码'
    end
    object Label3: TLabel [1]
      Left    = 292
      Top     = 44
      Width   = 48
      Height  = 12
      Caption = '专业名称'
    end
      object Label5: TLabel [2]
        Left = 42
        Top = 5
        Width = 128
        Height = 16
        Caption = '专业信息设置'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '黑体'
        Font.Style = []
        ParentFont = False
      end
      inherited UIPanel2: TUIPanel
        Top = 414
        Width = 673
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
    object WVEdit2: TWVEdit
      Left = 100
      Top = 40
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = ''
      WorkView = WorkView
      FieldName = '专业代码'
	  SynchronizeWhenExit = True
    end
    object WVEdit3: TWVEdit
      Left = 350
      Top = 40
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = ''
      WorkView = WorkView
      FieldName = '专业名称'
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
        Name = '查询.专业代码'
        Caption = '查询.专业代码'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 20
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GetPrevChar = '*'
      end
      item
        Name = '专业代码'
        Caption = '专业代码'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GroupIndex = 1
        DataField = 'sstation0'
		GetPrevChar = '*'
      end
      item
        Name = '专业名称'
        Caption = '专业名称'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GroupIndex = 1
        DataField = 'sname'
		GetPrevChar = '*'
      end
      item
        Name = '备注'
        Caption = '备注'
        FieldType = wftUndefined
        DomainName = ''
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Min = 0
        Checker.Max = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
		GroupIndex = 1
        DataField = 'usset2'
		GetPrevChar = '*'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|查询.专业代码|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|专业代码|专业名称|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Top = 344
  end
  inherited QueryRequest: TWVRequest
    ID = '专业信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '专业代码'
        FieldName = '查询.专业代码'
      end>
    Left = 472
    Top = 344
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
>
    Left = 164
    Top = 383
  end
  inherited AddRequest: TWVRequest
    ID = '专业信息设置'
    Bindings = <
      item
        ParamName = '专业代码'
        FieldName = '专业代码'
      end
      item
        ParamName = '专业名称'
        FieldName = '专业名称'
      end
      item
        ParamName = '备注'
        FieldName = '备注.增加'
      end>
    Top = 360
  end
  inherited DeleteRequest: TWVRequest
    ID = '专业信息设置'
    Bindings = <
      item
        ParamName = '专业代码'
        FieldName = '专业代码'
      end
      item
        ParamName = '专业名称'
        FieldName = '专业名称'
      end
      item
        ParamName = '备注'
        FieldName = '备注.删除'
      end>
    Left = 216
    Top = 344
  end
  inherited ChangeRequest: TWVRequest
    ID = '专业信息设置'
    Bindings = <
      item
        ParamName = '专业代码'
        FieldName = '专业代码'
      end
      item
        ParamName = '专业名称'
        FieldName = '专业名称'
      end
      item
        ParamName = '备注'
        FieldName = '备注.修改'
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