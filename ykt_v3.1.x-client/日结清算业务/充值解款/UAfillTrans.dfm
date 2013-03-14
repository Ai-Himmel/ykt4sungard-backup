inherited faqhfillTrans: TfaqhfillTrans
  Width = 667
  Height = 491
  inherited UIPanel1: TUIPanel
    Top = 455
    Width = 667
    Height = 36
    inherited btnQuery: TBitBtn
      Left = 496
      Top = 6
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 281
      Visible = False
    end
    object btnTrans: TBitBtn
      Left = 585
      Top = 6
      Width = 75
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '充值解款'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnQueryClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 667
    inherited Image1: TImage
      Width = 667
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 667
    Height = 437
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left = 250
      Top = 193
      Width = 56
      Height = 14
      Caption = '操作员号'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 278
      Top = 225
      Width = 28
      Height = 14
      Caption = '密码'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 250
      Top = 161
      Width = 56
      Height = 14
      Caption = '解款金额'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 278
      Top = 257
      Width = 28
      Height = 14
      Caption = '备注'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 250
      Top = 129
      Width = 56
      Height = 14
      Caption = '解款账号'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object edtOperCode: TWVEdit
      Left = 316
      Top = 189
      Width = 187
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
      Text = '<操作员号>'
      WorkView = WorkView
      FieldName = '操作员号'
    end
    object WVEdit2: TWVEdit
      Left = 316
      Top = 221
      Width = 187
      Height = 22
      Color = clInfoBk
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
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
    object WVEdit5: TWVEdit
      Left = 316
      Top = 253
      Width = 187
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
      Text = '<备注>'
      WorkView = WorkView
      FieldName = '备注'
    end
    object WVEdit4: TWVEdit
      Left = 316
      Top = 157
      Width = 187
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
      TabOrder = 3
      Text = '<金额>'
      WorkView = WorkView
      FieldName = '金额'
    end
    object WVComboBox3: TWVComboBox
      Left = 316
      Top = 127
      Width = 188
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      MaxLength = 8
      TabOrder = 4
      WorkView = WorkView
      FieldName = '食堂账号'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-49'
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 616
    Top = 408
    Width = 51
    Height = 50
    Align = alNone
    Visible = False
    inherited Grid: TRzDBGrid
      Align = alNone
      Columns = <
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Caption = '剩余金额'
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
        Name = '食堂账号'
        Caption = '食堂账号'
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
        Name = '备注'
        Caption = '备注'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|操作员号|密码|食堂账号|金额|备注|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 12
    Top = 311
  end
  inherited MainRequest: TWVRequest
    ID = '充值解款'
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
        ParamName = '操作员号'
        FieldName = '操作员号'
      end
      item
        ParamName = '密码'
        FieldName = '密码'
      end
      item
        ParamName = '食堂账号'
        FieldName = '食堂账号'
      end
      item
        ParamName = '金额'
        FieldName = '金额'
      end
      item
        ParamName = '备注'
        FieldName = '备注'
      end>
    Left = 48
    Top = 312
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 88
    Top = 312
  end
  inherited DataSource: TDataSource
    Left = 128
    Top = 312
  end
end
