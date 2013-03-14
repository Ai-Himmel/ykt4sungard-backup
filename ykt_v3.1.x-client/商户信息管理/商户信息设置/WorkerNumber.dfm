object QueryWorkerNumber: TQueryWorkerNumber
  Left = 183
  Top = 215
  Width = 650
  Height = 339
  Caption = '员工信息查询'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object WorkerDBGrid: TDBGrid
    Left = 0
    Top = 50
    Width = 642
    Height = 255
    Align = alClient
    FixedColor = 15458000
    ImeName = ''
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnCellClick = WorkerDBGridCellClick
    Columns = <
      item
        Expanded = False
        FieldName = 'sname2'
        Title.Alignment = taCenter
        Title.Caption = '员工号'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sname'
        Title.Alignment = taCenter
        Title.Caption = '姓名'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol0'
        Title.Alignment = taCenter
        Title.Caption = '员工状态'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_no'
        Title.Alignment = taCenter
        Title.Caption = '单位代码'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_auth'
        Title.Alignment = taCenter
        Title.Caption = '身份证号'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol1'
        Title.Alignment = taCenter
        Title.Caption = '职称代码'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol3'
        Title.Alignment = taCenter
        Title.Caption = '政治面貌'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'smarket_code'
        Title.Alignment = taCenter
        Title.Caption = '性别'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_auth2'
        Title.Alignment = taCenter
        Title.Caption = '联系电话'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol4'
        Title.Alignment = taCenter
        Title.Caption = '员工类别'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scusttypes'
        Title.Alignment = taCenter
        Title.Caption = '联系地址'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ssectypes'
        Title.Alignment = taCenter
        Title.Caption = '备注'
        Visible = True
      end>
  end
  object UIPanel1: TUIPanel
    Left = 0
    Top = 0
    Width = 642
    Height = 50
    Align = alTop
    BevelInner = bvRaised
    BevelOuter = bvLowered
    Color = 16119543
    TabOrder = 1
    object Label1: TLabel
      Left = 14
      Top = 19
      Width = 39
      Height = 13
      AutoSize = False
      Caption = '员工号'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 162
      Top = 19
      Width = 28
      Height = 13
      AutoSize = False
      Caption = '姓名'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 284
      Top = 19
      Width = 50
      Height = 13
      AutoSize = False
      Caption = '身份证号'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object WVEdit1: TWVEdit
      Left = 56
      Top = 16
      Width = 89
      Height = 21
      ImeName = ''
      ReadOnly = False
      TabOrder = 0
    end
    object WVEdit2: TWVEdit
      Left = 192
      Top = 16
      Width = 81
      Height = 21
      ImeName = ''
      ReadOnly = False
      TabOrder = 1
    end
    object WVEdit3: TWVEdit
      Left = 336
      Top = 16
      Width = 121
      Height = 21
      ImeName = ''
      ReadOnly = False
      TabOrder = 2
    end
    object Button1: TButton
      Left = 468
      Top = 16
      Width = 75
      Height = 25
      Caption = '检 索'
      TabOrder = 3
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 552
      Top = 16
      Width = 73
      Height = 25
      Cancel = True
      Caption = '取消'
      ModalResult = 2
      TabOrder = 4
    end
  end
  object WorkView2: TWorkView
    WorkFields = <
      item
        Name = '联系地址'
        Caption = '联系地址'
        FieldType = wftUndefined
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
        Name = '单位代码'
        Caption = '单位代码'
        FieldType = wftUndefined
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
        Name = '姓名'
        Caption = '姓名'
        FieldType = wftUndefined
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
        Name = '员工状态'
        Caption = '员工状态'
        FieldType = wftUndefined
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
        Name = '员工号'
        Caption = '员工号'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sname2'
      end
      item
        Name = '身份证号'
        Caption = '身份证号'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_auth'
      end
      item
        Name = '职称代码'
        Caption = '职称代码'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '民族'
        Caption = '民族'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol2'
      end
      item
        Name = '政治面貌'
        Caption = '政治面貌'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol3'
      end
      item
        Name = '性别'
        Caption = '性别'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'smarket_code'
      end
      item
        Name = '联系电话'
        Caption = '联系电话'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_auth2'
      end
      item
        Name = '员工类别'
        Caption = '员工类别'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol4'
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
        DataField = '@Dataset'
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    Left = 292
    Top = 143
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '员工信息查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '联系地址'
        FieldName = '联系地址'
      end
      item
        ParamName = '单位代码'
        FieldName = '单位代码'
      end
      item
        ParamName = '姓名'
        FieldName = '姓名'
      end
      item
        ParamName = '员工状态'
        FieldName = '员工状态'
      end
      item
        ParamName = '员工号'
        FieldName = '员工号'
      end
      item
        ParamName = '身份证号'
        FieldName = '身份证号'
      end
      item
        ParamName = '职称代码'
        FieldName = '职称代码'
      end
      item
        ParamName = '民族'
        FieldName = '民族'
      end
      item
        ParamName = '政治面貌'
        FieldName = '政治面貌'
      end
      item
        ParamName = '性别'
        FieldName = '性别'
      end
      item
        ParamName = '联系电话'
        FieldName = '联系电话'
      end
      item
        ParamName = '员工类别'
        FieldName = '员工类别'
      end>
    Left = 332
    Top = 143
  end
end
