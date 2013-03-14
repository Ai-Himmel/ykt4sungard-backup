inherited faqhBankBingdingQuery: TfaqhBankBingdingQuery
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 523
    end
    inherited btnPrint: TBitBtn
      Left = 610
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
    Height = 103
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 30
      Top = 9
      Width = 60
      Height = 12
      Caption = '交易参考号'
    end
    object Label2: TLabel
      Left = 30
      Top = 33
      Width = 60
      Height = 12
      Caption = '导入批次号'
    end
    object Label3: TLabel
      Left = 218
      Top = 9
      Width = 72
      Height = 12
      Caption = '交易开始日期'
    end
    object Label4: TLabel
      Left = 418
      Top = 9
      Width = 72
      Height = 12
      Caption = '交易结束日期'
    end
    object Label5: TLabel
      Left = 254
      Top = 33
      Width = 36
      Height = 12
      Caption = '客户号'
    end
    object Label6: TLabel
      Left = 448
      Top = 33
      Width = 42
      Height = 12
      Caption = '学/工号'
    end
    object Label7: TLabel
      Left = 42
      Top = 57
      Width = 48
      Height = 12
      Caption = '银行卡号'
    end
    object Label9: TLabel
      Left = 442
      Top = 57
      Width = 48
      Height = 12
      Caption = '增删标志'
    end
    object Label10: TLabel
      Left = 254
      Top = 57
      Width = 36
      Height = 12
      Caption = '错误码'
    end
    object Label8: TLabel
      Left = 42
      Top = 81
      Width = 48
      Height = 12
      Caption = '操作类型'
    end
    object WVEdit1: TWVEdit
      Left = 100
      Top = 5
      Width = 100
      Height = 20
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 0
      Text = '<交易参考号>'
      WorkView = WorkView
      FieldName = '交易参考号'
    end
    object WVEdit2: TWVEdit
      Left = 100
      Top = 29
      Width = 100
      Height = 20
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 3
      Text = '<导入批次号>'
      WorkView = WorkView
      FieldName = '导入批次号'
    end
    object edtBeginDate: TWVEdit
      Left = 300
      Top = 5
      Width = 100
      Height = 20
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 1
      Text = '<交易开始日期>'
      WorkView = WorkView
      FieldName = '交易开始日期'
    end
    object edtEndDate: TWVEdit
      Left = 500
      Top = 5
      Width = 100
      Height = 20
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 2
      Text = '<交易结束日期>'
      WorkView = WorkView
      FieldName = '交易结束日期'
    end
    object edtCustNo: TWVEdit
      Left = 300
      Top = 29
      Width = 100
      Height = 20
      Color = clBtnHighlight
      MaxLength = 22
      ReadOnly = False
      TabOrder = 4
      Text = '<客户号>'
      WorkView = WorkView
      FieldName = '客户号'
    end
    object WVEdit6: TWVEdit
      Left = 500
      Top = 29
      Width = 100
      Height = 20
      CharCase = ecUpperCase
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 5
      Text = '<学号>'
      WorkView = WorkView
      FieldName = '学号'
    end
    object WVEdit7: TWVEdit
      Left = 100
      Top = 53
      Width = 100
      Height = 20
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 6
      Text = '<银行卡号>'
      WorkView = WorkView
      FieldName = '银行卡号'
    end
    object edtErrorCode: TWVEdit
      Left = 300
      Top = 53
      Width = 100
      Height = 20
      Color = clBtnHighlight
      MaxLength = 22
      ReadOnly = False
      TabOrder = 7
      Text = '<错误码>'
      WorkView = WorkView
      FieldName = '错误码'
    end
    object cbbQFeeType: TWVComboBox
      Left = 500
      Top = 53
      Width = 101
      Height = 18
      Style = csOwnerDrawFixed
      Color = clBtnHighlight
      ItemHeight = 12
      TabOrder = 8
      WorkView = WorkView
      FieldName = '增删标志'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*44'
    end
    object WVComboBox1: TWVComboBox
      Left = 100
      Top = 77
      Width = 101
      Height = 18
      Style = csOwnerDrawFixed
      Color = clBtnHighlight
      ItemHeight = 12
      TabOrder = 9
      WorkView = WorkView
      FieldName = '操作类型'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*33'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 121
    Width = 700
    Height = 338
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 338
      Columns = <
        item
          Expanded = False
          FieldName = 'lwithdraw_flag'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '终端号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易参考号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '导入批次号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易日期'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易时间'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户号'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Spager'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '学/工号'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '姓名'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '银行卡号'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '操作类型'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol9'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '增删标志'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semp_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '操作员号'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lsafe_level'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '错误码'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ssectypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '备注'
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
        Name = '交易参考号'
        Caption = '交易参考号'
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
        Name = '导入批次号'
        Caption = '导入批次号'
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
        Name = '交易开始日期'
        Caption = '交易开始日期'
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
        Name = '交易结束日期'
        Caption = '交易结束日期'
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
        Name = '客户号'
        Caption = '客户号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '学号'
        Caption = '学号'
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
        Name = '银行卡号'
        Caption = '银行卡号'
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
        Name = '操作类型'
        Caption = '操作类型'
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
        Name = '增删标志'
        Caption = '增删标志'
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
        Name = '错误码'
        Caption = '错误码'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end>
    InvalidColor = clBtnHighlight
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '银行卡绑定流水查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '交易参考号'
        FieldName = '交易参考号'
      end
      item
        ParamName = '导入批次号'
        FieldName = '导入批次号'
      end
      item
        ParamName = '交易开始日期'
        FieldName = '交易开始日期'
      end
      item
        ParamName = '交易结束日期'
        FieldName = '交易结束日期'
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '学号'
        FieldName = '学号'
      end
      item
        ParamName = '银行卡号'
        FieldName = '银行卡号'
      end
      item
        ParamName = '操作类型'
        FieldName = '操作类型'
      end
      item
        ParamName = '增删标志'
        FieldName = '增删标志'
      end
      item
        ParamName = '错误码'
        FieldName = '错误码'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '33'
      end
      item
        FieldName = 'lvol9'
        DataPresentType = 'idobjects'
        DataPresentParam = '44'
      end>
    Left = 240
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 280
    Top = 224
  end
end
