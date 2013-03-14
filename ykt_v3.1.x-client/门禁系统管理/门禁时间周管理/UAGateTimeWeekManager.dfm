inherited faqhGateTimeWeekManager: TfaqhGateTimeWeekManager
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 435
    end
    inherited btnPrint: TBitBtn
      Left = 610
      TabOrder = 2
    end
    object btnDelete: TBitBtn
      Left = 523
      Top = 3
      Width = 75
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '&D 删除'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnDeleteClick
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
      Left = 30
      Top = 9
      Width = 60
      Height = 12
      Caption = '控制器编号'
    end
    object Label3: TLabel
      Left = 230
      Top = 9
      Width = 60
      Height = 12
      Caption = '控制器名称'
    end
    object Label7: TLabel
      Left = 442
      Top = 9
      Width = 48
      Height = 12
      Caption = '设备机型'
    end
    object Label10: TLabel
      Left = 230
      Top = 33
      Width = 60
      Height = 12
      Caption = '时间周名称'
    end
    object Label12: TLabel
      Left = 54
      Top = 34
      Width = 36
      Height = 12
      Caption = '子系统'
    end
    object WVEdit2: TWVEdit
      Left = 100
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<控制器编号>'
      WorkView = WorkView
      FieldName = '控制器编号'
    end
    object WVEdit3: TWVEdit
      Left = 300
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<控制器名称>'
      WorkView = WorkView
      FieldName = '控制器名称'
    end
    object WVEdit10: TWVEdit
      Left = 300
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 4
      Text = '<时间周名称>'
      WorkView = WorkView
      FieldName = '时间周名称'
    end
    object WVComboBox7: TWVComboBox
      Left = 100
      Top = 28
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '子系统'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-32'
    end
    object cbbScode: TWVComboBox
      Left = 500
      Top = 4
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '设备机型'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*47'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 73
    Width = 700
    Height = 386
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 386
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Caption = '控制器编号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Caption = '控制器名称'
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Caption = '设备编号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'saddr'
          PickList.Strings = ()
          Title.Caption = '设备名称'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Caption = '时间周编号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'saddr2'
          PickList.Strings = ()
          Title.Caption = '时间周名称'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spost_code'
          PickList.Strings = ()
          Title.Caption = '设备机型'
          Width = 90
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
        Name = '操作类别'
        Caption = '操作类别'
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
        Name = '控制器编号'
        Caption = '控制器编号'
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
      end
      item
        Name = '控制器名称'
        Caption = '控制器名称'
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
        Name = '设备物理编号'
        Caption = '设备物理编号'
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
        Name = '设备名称'
        Caption = '设备名称'
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
        Name = '设备物理型号'
        Caption = '设备物理型号'
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
        Name = '设备机型'
        Caption = '设备机型'
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
        Name = '所属区域'
        Caption = '所属区域'
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
        Name = '时间周编号'
        Caption = '时间周编号'
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
      end
      item
        Name = '时间周名称'
        Caption = '时间周名称'
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
        Name = '子系统'
        Caption = '子系统'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|操作类别|控制器编号|控制器名称|设备物理编号|设备名称|设备物理型' +
          '号|设备机型|所属区域|时间周编号|时间周名称|子系统|'
      end>
    Left = 156
    Top = 239
  end
  inherited MainRequest: TWVRequest
    ID = '门禁时间周管理'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end
      item
        ParamName = '控制器编号'
        FieldName = '控制器编号'
      end
      item
        ParamName = '控制器名称'
        FieldName = '控制器名称'
      end
      item
        ParamName = '设备物理编号'
        FieldName = '设备物理编号'
      end
      item
        ParamName = '设备名称'
        FieldName = '设备名称'
      end
      item
        ParamName = '设备物理型号'
        FieldName = '设备物理型号'
      end
      item
        ParamName = '设备机型'
        FieldName = '设备机型'
      end
      item
        ParamName = '所属区域'
        FieldName = '所属区域'
      end
      item
        ParamName = '时间周编号'
        FieldName = '时间周编号'
      end
      item
        ParamName = '时间周名称'
        FieldName = '时间周名称'
      end
      item
        ParamName = '子系统'
        FieldName = '子系统'
      end>
    Left = 192
    Top = 240
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'spost_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '47'
      end>
    Left = 224
    Top = 240
  end
  inherited DataSource: TDataSource
    Left = 256
    Top = 240
  end
  object WorkView1: TWorkView
    WorkFields = <
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
        DataField = '@Return'
      end
      item
        Name = '查询结果集'
        Caption = '查询结果集'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '操作类别'
        Caption = '操作类别'
        FieldType = wftUndefined
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
        Name = '控制器编号'
        Caption = '控制器编号'
        FieldType = wftUndefined
        DataType = kdtInteger
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
        Name = '设备编号'
        Caption = '设备编号'
        FieldType = wftUndefined
        DataType = kdtInteger
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
        Name = '时间周编号'
        Caption = '时间周编号'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|操作类别|控制器编号|控制器名称|设备物理编号|设备名称|设备物理型' +
          '号|设备机型|所属区域|时间周编号|时间周名称|子系统|'
      end>
    Left = 156
    Top = 311
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '门禁时间周删除'
    Bindings = <
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作类别'
        FieldName = '操作类别'
      end
      item
        ParamName = '控制器编号'
        FieldName = '控制器编号'
      end
      item
        ParamName = '设备编号'
        FieldName = '设备编号'
      end
      item
        ParamName = '时间周编号'
        FieldName = '时间周编号'
      end>
    AfterExec = MainRequestAfterExec
    Left = 192
    Top = 312
  end
end
