inherited faqhconsumeBalance: TfaqhconsumeBalance
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 453
    Width = 700
    Height = 36
    inherited btnQuery: TBitBtn
      Left = 600
      Top = 6
      Width = 89
      Caption = '消费结算'
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000
        0000CECECE00000000000000000000000000FFEFCE00FFCE9400FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF0000000000CECECE0000000000FFEFCE00FFCE9400CE940000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
        00000000000000000000FFEFCE00FFCE9400CE94000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF0000000000CECECE0000000000000000000000
        000000000000FFEFCE00FFEFCE00CE9400000000000000000000000000000000
        00000000000000000000000000000000000000000000FFEFCE00FFEFCE00FFEF
        CE00FFEFCE00FFEFCE00CE9400000000000000000000000000000000000063CE
        CE0063CECE0063CECE0063CECE0000000000FFEFCE00FF94000000000000FFCE
        9400FFEFCE00FFEFCE0000000000CECECE0000000000FFFFFF000000000063CE
        CE00CEFFFF0094FFFF0094FFFF0000000000FF9400000000000094FFFF000000
        0000FFCE9400FFEFCE0000000000CECECE0000000000FFFFFF000000000063CE
        CE00CEFFFF0094FFFF0094CEFF0094FFFF000000000094FFFF0094CEFF0063CE
        CE0000000000FFCE940000000000CECECE0000000000FFFFFF000000000063CE
        CE00CEFFFF0094FFFF0094FFFF0094FFFF0094FFFF0094CEFF0094FFFF000000
        0000FFEFCE00FF94000000000000CECECE0000000000FFFFFF000000000063CE
        CE00CEFFFF0094FFFF0094FFFF0094FFFF0094CEFF0094FFFF0000000000FFEF
        CE00FF9400000000000000000000CECECE0000000000FFFFFF000000000063CE
        CE00CEFFFF00CEFFFF00CEFFFF00CEFFFF00CEFFFF00CEFFFF00CEFFFF000000
        000000000000FFFFFF0000000000CECECE0000000000FFFFFF000000000063CE
        CE0063CECE0063CECE0063CECE00000000000000000000000000000000000000
        000000000000FFFFFF0000000000CECECE0000000000FFFFFF0000000000CEFF
        FF00CEFFFF00CEFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF0000000000CECECE0000000000FFFFFF00FFFFFF000000
        00000000000000000000FFFFFF00000000000000000000000000000000000000
        0000000000000000000000000000CECECE0000000000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF0000000000CECECE00CECECE00CECECE00CECE
        CE00CECECE00CECECE00BDBDBD0000000000FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
        0000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00}
    end
    inherited btnPrint: TBitBtn
      Left = 490
      Top = 6
      Caption = '结　算'
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    Height = 32
    inherited Image1: TImage
      Width = 700
      Height = 32
    end
    inherited LabRecordCount: TLabel
      Left = 648
      Width = 17
      Visible = False
    end
    object Label3: TLabel
      Left = 10
      Top = 8
      Width = 128
      Height = 16
      AutoSize = False
      Caption = '当前选择的商户：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object lblName: TLabel
      Left = 138
      Top = 8
      Width = 455
      Height = 16
      AutoSize = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -16
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
  end
  object Panel1: TPanel [2]
    Left = 289
    Top = 32
    Width = 411
    Height = 421
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object rb1: TRzGroupBox
      Left = 40
      Top = 56
      Width = 313
      Height = 169
      Caption = '结算参数'
      Color = 16184303
      TabOrder = 0
      ThemeAware = False
      object Label1: TLabel
        Left = 50
        Top = 36
        Width = 64
        Height = 16
        Caption = '操作员号'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label2: TLabel
        Left = 50
        Top = 76
        Width = 64
        Height = 16
        Caption = '操作密码'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel
        Left = 50
        Top = 116
        Width = 64
        Height = 16
        Caption = '结算金额'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object edtOperCode: TWVEdit
        Left = 127
        Top = 32
        Width = 141
        Height = 24
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        ReadOnly = False
        TabOrder = 0
        Text = '<操作员号>'
        WorkView = WorkView
        FieldName = '操作员号'
      end
      object WVEdit2: TWVEdit
        Left = 127
        Top = 72
        Width = 141
        Height = 24
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 6
        ParentFont = False
        PasswordChar = '*'
        ReadOnly = False
        TabOrder = 1
        Text = '<密码>'
        WorkView = WorkView
        FieldName = '密码'
      end
      object WVEdit4: TWVEdit
        Left = 127
        Top = 112
        Width = 141
        Height = 24
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = False
        TabOrder = 2
        Text = '<金额>'
        WorkView = WorkView
        FieldName = '金额'
      end
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 656
    Top = 408
    Width = 44
    Height = 45
    Align = alNone
    Visible = False
    inherited Grid: TRzDBGrid
      Align = alNone
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Caption = '流水号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Caption = '账户余额'
          Visible = True
        end>
    end
  end
  object rzszpnl1: TRzSizePanel [4]
    Left = 0
    Top = 32
    Width = 289
    Height = 421
    Color = 16184303
    HotSpotVisible = True
    SizeBarWidth = 7
    TabOrder = 4
    UseGradients = True
    object tvCust: TRzTreeView
      Left = 0
      Top = 0
      Width = 281
      Height = 421
      SelectionPen.Color = clBtnShadow
      Align = alClient
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      Indent = 19
      ParentFont = False
      TabOrder = 0
      OnClick = tvCustClick
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
        Name = '操作员号'
        Caption = '操作员号'
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
        Name = '密码'
        Caption = '密码'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '商户账号'
        Caption = '商户账号'
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
        Name = '金额'
        Caption = '金额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|操作员号|密码|商户账号|金额|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '消费结算'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '操作员号'
        FieldName = '操作员号'
      end
      item
        ParamName = '密码'
        FieldName = '密码'
      end
      item
        ParamName = '商户账号'
        FieldName = '商户账号'
      end
      item
        ParamName = '金额'
        FieldName = '金额'
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
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 168
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 208
    Top = 256
  end
  object WorkView2: TWorkView
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
      end
      item
        Name = '商户标识'
        Caption = '商户标识'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|商户标识|'
      end>
    Left = 92
    Top = 199
  end
  object QueryRequest2: TWVRequest
    WorkView = WorkView2
    ID = '商户信息主键查询2'
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
        ParamName = '商户标识'
        FieldName = '商户标识'
      end>
    Left = 128
    Top = 200
  end
end
