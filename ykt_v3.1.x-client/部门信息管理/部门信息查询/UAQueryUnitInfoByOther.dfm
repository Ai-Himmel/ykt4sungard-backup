inherited faqhQueryUnitInfoByOther: TfaqhQueryUnitInfoByOther
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 453
    Width = 700
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 527
      Top = 5
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 610
      Top = 5
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 55
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label2: TLabel
      Left = 228
      Top = 9
      Width = 48
      Height = 12
      Caption = '部门名称'
    end
    object Label3: TLabel
      Left = 450
      Top = 9
      Width = 48
      Height = 12
      Caption = '英文名称'
    end
    object Label4: TLabel
      Left = 34
      Top = 33
      Width = 48
      Height = 12
      Caption = '上级部门'
    end
    object WVLabel1: TWVLabel
      Left = 34
      Top = 9
      Width = 48
      Height = 12
      Caption = '部门代码'
    end
    object WVEdit2: TWVEdit
      Left = 286
      Top = 4
      Width = 149
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<单位名称>'
      WorkView = WorkView
      FieldName = '单位名称'
    end
    object WVEdit3: TWVEdit
      Left = 510
      Top = 4
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<英文名称>'
      WorkView = WorkView
      FieldName = '英文名称'
    end
    object WVEdit1: TWVEdit
      Left = 92
      Top = 4
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<单位代码>'
      WorkView = WorkView
      FieldName = '单位代码'
    end
    object WVComboBox3: TWVComboBox
      Left = 92
      Top = 28
      Width = 345
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '上级单位'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 73
    Width = 700
    Height = 380
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 380
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
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ssectypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '英文名称'
          Width = 132
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '上级部门'
          Width = 119
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Caption = '部门全称'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no2'
          PickList.Strings = ()
          Title.Caption = '旧部门代码'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit2'
          PickList.Strings = ()
          Title.Caption = '最后修改时间'
          Width = 100
          Visible = True
        end>
    end
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
        Name = '单位代码'
        Caption = '单位代码'
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
        Name = '单位名称'
        Caption = '单位名称'
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
        DataField = 'vsvarstr0'
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
        DataField = 'scust_no2'
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
        GroupIndex = 1
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|是否院系|单位名称|英文名称|上级单位|单位级别|是否有效|备注|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 220
    Top = 247
  end
  inherited MainRequest: TWVRequest
    ID = '单位信息查询一'
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
      end>
    Left = 184
    Top = 248
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'semail2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end>
    Left = 256
    Top = 248
  end
  inherited DataSource: TDataSource
    Left = 288
    Top = 248
  end
end
