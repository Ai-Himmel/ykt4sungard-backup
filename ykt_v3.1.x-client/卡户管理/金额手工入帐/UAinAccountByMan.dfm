inherited faqhinAccountByMan: TfaqhinAccountByMan
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 437
    Width = 700
    Height = 52
    TabOrder = 3
    object RzStatusPane1: TRzStatusPane [0]
      Left = 0
      Top = 31
      Width = 700
      Height = 21
      FrameStyle = fsStatus
      Align = alBottom
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
    end
    inherited btnQuery: TBitBtn
      Left = 611
      Hint = '手工入帐'
      TabOrder = 1
    end
    inherited btnPrint: TBitBtn
      Left = 18
      TabOrder = 0
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    inherited Image1: TImage
      Width = 700
    end
    inherited LabRecordCount: TLabel
      Visible = False
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 419
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 154
      Top = 41
      Width = 56
      Height = 14
      Caption = '借方账号'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 154
      Top = 105
      Width = 56
      Height = 14
      Caption = '贷方账号'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 154
      Top = 169
      Width = 56
      Height = 14
      Caption = '发生金额'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 126
      Top = 201
      Width = 84
      Height = 14
      Caption = '审核操作员号'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label7: TLabel
      Left = 112
      Top = 233
      Width = 98
      Height = 14
      Caption = '审核操作员密码'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 126
      Top = 73
      Width = 84
      Height = 14
      Caption = '借方账户名称'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label9: TLabel
      Left = 126
      Top = 137
      Width = 84
      Height = 14
      Caption = '贷方账户名称'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object edtJNo: TWVEdit
      Left = 220
      Top = 37
      Width = 213
      Height = 22
      Color = clInfoBk
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      ReadOnly = False
      TabOrder = 0
      Text = '<借方账号>'
      OnExit = edtJNoExit
      WorkView = WorkView
      FieldName = '借方账号'
    end
    object edtDNO: TWVEdit
      Left = 220
      Top = 101
      Width = 213
      Height = 22
      Color = clInfoBk
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      ReadOnly = False
      TabOrder = 2
      Text = '<贷方账号>'
      OnExit = edtDNOExit
      WorkView = WorkView
      FieldName = '贷方账号'
    end
    object edtMoney: TWVEdit
      Left = 220
      Top = 165
      Width = 213
      Height = 22
      Color = clInfoBk
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      MaxLength = 22
      ParentFont = False
      ReadOnly = False
      TabOrder = 4
      Text = '<发生金额>'
      WorkView = WorkView
      FieldName = '发生金额'
    end
    object edtpass: TWVEdit
      Left = 220
      Top = 229
      Width = 213
      Height = 22
      Color = clInfoBk
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      PasswordChar = '*'
      ReadOnly = False
      TabOrder = 6
    end
    object edtJName: TWVEdit
      Left = 220
      Top = 69
      Width = 213
      Height = 22
      Color = clInfoBk
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
    end
    object edtDName: TWVEdit
      Left = 220
      Top = 133
      Width = 213
      Height = 22
      Color = clInfoBk
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 3
    end
    object cbbErrOperNo: TWVComboBox
      Left = 221
      Top = 196
      Width = 212
      Height = 22
      Style = csDropDownList
      Color = clInfoBk
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ItemHeight = 14
      ParentFont = False
      TabOrder = 5
      WorkView = WorkView
      FieldName = '错账操作员号'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-20'
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 528
    Top = 370
    Width = 97
    Height = 31
    Align = alNone
    TabOrder = 2
    Visible = False
    inherited Grid: TRzDBGrid
      Width = 33
      Height = 17
      Align = alNone
      DataSource = nil
      Visible = False
      Columns = <
        item
          Expanded = False
          FieldName = 'semp_pwd'
          PickList.Strings = ()
          Title.Caption = '错账操作员密码'
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
        Name = '借方账号'
        Caption = '借方账号'
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
        Name = '贷方账号'
        Caption = '贷方账号'
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
        Name = '发生金额'
        Caption = '发生金额'
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
        Name = '工作站号'
        Caption = '工作站号'
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
        Name = '错账操作员号'
        Caption = '错账操作员号'
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
        Name = '错账操作员密码'
        Caption = '错账操作员密码'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|借方账号|贷方账号|发生金额|工作站号|操作员号|错账操作员号|错账' +
          '操作员密码|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 420
    Top = 31
  end
  inherited MainRequest: TWVRequest
    ID = '金额手工入帐'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '借方账号'
        FieldName = '借方账号'
      end
      item
        ParamName = '贷方账号'
        FieldName = '贷方账号'
      end
      item
        ParamName = '发生金额'
        FieldName = '发生金额'
      end
      item
        ParamName = '工作站号'
        FieldName = '工作站号'
      end
      item
        ParamName = '操作员号'
        FieldName = '操作员号'
      end
      item
        ParamName = '错账操作员号'
        FieldName = '错账操作员号'
      end
      item
        ParamName = '错账操作员密码'
        FieldName = '错账操作员密码'
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
    Left = 456
    Top = 32
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 496
    Top = 32
  end
  inherited DataSource: TDataSource
    Left = 536
    Top = 32
  end
  object WorkView1: TWorkView
    WorkFields = <
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
        Name = '账号'
        Caption = '账号'
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
        Name = '名称'
        Caption = '名称'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|借方账号|贷方账号|发生金额|工作站号|操作员号|错账操作员号|错账' +
          '操作员密码|'
      end>
    Left = 492
    Top = 127
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '金额手工入帐查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '账号'
        FieldName = '账号'
      end
      item
        ParamName = '名称'
        FieldName = '名称'
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
      end>
    AfterExec = MainRequestAfterExec
    Left = 456
    Top = 128
  end
end
