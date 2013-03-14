object QueryWorkerNum: TQueryWorkerNum
  Left = 276
  Top = 165
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = '员工信息查询'
  ClientHeight = 334
  ClientWidth = 591
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 12
    Width = 41
    Height = 13
    AutoSize = False
    Caption = '员工号'
  end
  object Label2: TLabel
    Left = 168
    Top = 12
    Width = 33
    Height = 13
    AutoSize = False
    Caption = '姓名'
  end
  object Label3: TLabel
    Left = 304
    Top = 12
    Width = 57
    Height = 13
    AutoSize = False
    Caption = '身份证号'
  end
  object WVEdit1: TWVEdit
    Left = 56
    Top = 8
    Width = 89
    Height = 21
    Color = clWhite
    ReadOnly = False
    TabOrder = 0
    Text = '<员工号>'
    WorkView = WorkView2
    FieldName = '员工号'
  end
  object WVEdit2: TWVEdit
    Left = 208
    Top = 8
    Width = 81
    Height = 21
    Color = clWhite
    ReadOnly = False
    TabOrder = 1
    Text = '<姓名>'
    WorkView = WorkView2
    FieldName = '姓名'
  end
  object WVEdit3: TWVEdit
    Left = 368
    Top = 8
    Width = 121
    Height = 21
    Color = clWhite
    ReadOnly = False
    TabOrder = 2
    Text = '<身份证号>'
    WorkView = WorkView2
    FieldName = '身份证号'
  end
  object btnQuery: TBitBtn
    Left = 503
    Top = 7
    Width = 75
    Height = 25
    Hint = '查询/刷新数据'
    Anchors = [akTop, akRight]
    Caption = '&Q 查询'
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = '宋体'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = btnQueryClick
  end
  object WorkerDBGrid: TRzDBGrid
    Left = 0
    Top = 40
    Width = 591
    Height = 294
    Align = alBottom
    DataSource = DataSource2
    FixedColor = 15458000
    TabOrder = 4
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnDblClick = WorkerDBGridDblClick
    FrameColor = 12164479
    FrameVisible = True
    FixedLineColor = 12164479
    LineColor = clInactiveCaption
    Columns = <
      item
        Expanded = False
        FieldName = 'sname2'
        Title.Alignment = taCenter
        Title.Caption = '工号'
        Width = 71
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sname'
        Title.Alignment = taCenter
        Title.Caption = '姓名'
        Width = 68
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'smarket_code'
        Title.Alignment = taCenter
        Title.Caption = '性别'
        Width = 40
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_no'
        Title.Alignment = taCenter
        Title.Caption = '单位'
        Width = 109
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol4'
        Title.Alignment = taCenter
        Title.Caption = '类别'
        Width = 67
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol1'
        Title.Alignment = taCenter
        Title.Caption = '职称'
        Width = 87
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol3'
        Title.Alignment = taCenter
        Title.Caption = '政治面貌'
        Width = 60
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol2'
        Title.Alignment = taCenter
        Title.Caption = '民族'
        Width = 53
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol0'
        Title.Alignment = taCenter
        Title.Caption = '状态'
        Width = 60
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_auth'
        Title.Alignment = taCenter
        Title.Caption = '身份证号'
        Width = 158
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sphone3'
        Title.Alignment = taCenter
        Title.Caption = '注册时间'
        Width = 109
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scust_auth2'
        Title.Alignment = taCenter
        Title.Caption = '联系电话'
        Width = 115
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scusttypes'
        Title.Alignment = taCenter
        Title.Caption = '联系地址'
        Width = 288
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ssectypes'
        Title.Alignment = taCenter
        Title.Caption = '备注'
        Width = 359
        Visible = True
      end>
  end
  object DataSource2: TDataSource
    Left = 156
    Top = 271
  end
  object WVDBBinder2: TWVDBBinder
    DataSource = DataSource2
    WorkView = WorkView2
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'scust_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'lvol1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2002'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2001'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2004'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '39'
      end
      item
        FieldName = 'lvol0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '11'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '33'
      end>
    HideUnbindingFields = False
    Left = 124
    Top = 271
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
    Left = 92
    Top = 271
  end
  object WorkView2: TWorkView
    WorkFields = <
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
    Left = 60
    Top = 271
  end
end
