inherited faqhaccountTradeQuery: TfaqhaccountTradeQuery
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 523
      TabOrder = 1
    end
    inherited btnPrint: TBitBtn
      Left = 610
      TabOrder = 2
    end
    object btnReadCard: TBitBtn
      Left = 435
      Top = 3
      Width = 79
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '读卡查询'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnReadCardClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    TabOrder = 2
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 151
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object Label1: TLabel
      Left = 18
      Top = 33
      Width = 72
      Height = 12
      Caption = '记账开始日期'
    end
    object Label2: TLabel
      Left = 218
      Top = 33
      Width = 72
      Height = 12
      Caption = '记账结束日期'
    end
    object Label3: TLabel
      Left = 18
      Top = 9
      Width = 72
      Height = 12
      Caption = '交易开始日期'
    end
    object Label4: TLabel
      Left = 218
      Top = 9
      Width = 72
      Height = 12
      Caption = '交易结束日期'
    end
    object Label5: TLabel
      Left = 454
      Top = 9
      Width = 36
      Height = 12
      Caption = '科目号'
    end
    object Label6: TLabel
      Left = 466
      Top = 33
      Width = 24
      Height = 12
      Caption = '账号'
    end
    object Label7: TLabel
      Left = 54
      Top = 57
      Width = 36
      Height = 12
      Caption = '帐户名'
    end
    object Label8: TLabel
      Left = 242
      Top = 57
      Width = 48
      Height = 12
      Caption = '终端编号'
    end
    object Label9: TLabel
      Left = 430
      Top = 57
      Width = 60
      Height = 12
      Caption = '终端流水号'
    end
    object Label10: TLabel
      Left = 454
      Top = 81
      Width = 36
      Height = 12
      Caption = '交易码'
    end
    object Label11: TLabel
      Left = 242
      Top = 81
      Width = 48
      Height = 12
      Caption = '凭证号码'
    end
    object Label12: TLabel
      Left = 54
      Top = 81
      Width = 36
      Height = 12
      Caption = '商户号'
    end
    object Label13: TLabel
      Left = 42
      Top = 105
      Width = 48
      Height = 12
      Caption = '显示卡号'
    end
    object Label14: TLabel
      Left = 266
      Top = 105
      Width = 24
      Height = 12
      Caption = '卡号'
    end
    object Label15: TLabel
      Left = 454
      Top = 105
      Width = 36
      Height = 12
      Caption = '操作员'
    end
    object Label16: TLabel
      Left = 48
      Top = 129
      Width = 42
      Height = 12
      Caption = '学/工号'
    end
    object edtJbDate: TWVEdit
      Left = 100
      Top = 29
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 3
      Text = '<记账开始日期>'
      WorkView = WorkView
      FieldName = '记账开始日期'
    end
    object edtJEDate: TWVEdit
      Left = 300
      Top = 29
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 4
      Text = '<记账截止日期>'
      WorkView = WorkView
      FieldName = '记账截止日期'
    end
    object edtTBDate: TWVEdit
      Left = 100
      Top = 5
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<交易开始日期>'
      WorkView = WorkView
      FieldName = '交易开始日期'
    end
    object edtTEdate: TWVEdit
      Left = 300
      Top = 5
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<交易截止日期>'
      WorkView = WorkView
      FieldName = '交易截止日期'
    end
    object WVEdit6: TWVEdit
      Left = 501
      Top = 29
      Width = 141
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 5
      Text = '<账号>'
      WorkView = WorkView
      FieldName = '账号'
    end
    object WVEdit7: TWVEdit
      Left = 100
      Top = 53
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 6
      Text = '<帐户名>'
      WorkView = WorkView
      FieldName = '帐户名'
    end
    object edtSeriId: TWVEdit
      Left = 501
      Top = 53
      Width = 141
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 8
      Text = '<终端流水号>'
      WorkView = WorkView
      FieldName = '终端流水号'
    end
    object WVEdit11: TWVEdit
      Left = 300
      Top = 77
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 10
      Text = '<凭证号码>'
      WorkView = WorkView
      FieldName = '凭证号码'
    end
    object edtBusiId: TWVEdit
      Left = 100
      Top = 77
      Width = 112
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 9
      Text = '<商户号>'
      WorkView = WorkView
      FieldName = '商户号'
    end
    object WVEdit13: TWVEdit
      Left = 100
      Top = 101
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 12
      Text = '<显示卡号>'
      WorkView = WorkView
      FieldName = '显示卡号'
    end
    object edtCardNo: TWVEdit
      Left = 300
      Top = 101
      Width = 112
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 13
      Text = '<卡号>'
      WorkView = WorkView
      FieldName = '卡号'
    end
    object WVComboBox3: TWVComboBox
      Left = 501
      Top = 77
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 11
      WorkView = WorkView
      FieldName = '交易码'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-16'
    end
    object WVComboBox1: TWVComboBox
      Left = 501
      Top = 5
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      WorkView = WorkView
      FieldName = '科目号'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-25'
    end
    object WVComboBox4: TWVComboBox
      Left = 501
      Top = 101
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 14
      WorkView = WorkView
      FieldName = '操作员'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-30'
    end
    object edtStationNo: TWVEdit
      Left = 300
      Top = 53
      Width = 112
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 7
      Text = '<终端编号>'
      WorkView = WorkView
      FieldName = '终端编号'
    end
    object WVEdit1: TWVEdit
      Left = 100
      Top = 125
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 15
      Text = '<学工号>'
      WorkView = WorkView
      FieldName = '学工号'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 169
    Width = 700
    Height = 290
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 290
      Columns = <
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '记账日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '记账时间'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lwithdraw_flag'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '终端编号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '终端流水号'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lsafe_level'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '子流水号'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易时间'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol9'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '凭证类型'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '凭证号码'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易码'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易类型'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '摘要'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '科目号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '帐号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spager'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '学/工号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbankname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '帐户名'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smain_flag'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '借贷'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '发生额'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '余额'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '对方科目号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '对方账号'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbankname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '对方帐户名'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semp'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '操作员代码'
          Width = 60
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
        Name = '记账开始日期'
        Caption = '记账开始日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
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
        Name = '记账截止日期'
        Caption = '记账截止日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
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
        Name = '交易开始日期'
        Caption = '交易开始日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
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
        Name = '交易截止日期'
        Caption = '交易截止日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
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
        Name = '科目号'
        Caption = '科目号'
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
        Name = '账号'
        Caption = '账号'
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
        Name = '帐户名'
        Caption = '帐户名'
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
        Name = '终端编号'
        Caption = '终端编号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '终端流水号'
        Caption = '终端流水号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '交易码'
        Caption = '交易码'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '凭证号码'
        Caption = '凭证号码'
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
        Name = '商户号'
        Caption = '商户号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '显示卡号'
        Caption = '显示卡号'
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
        Name = '卡号'
        Caption = '卡号'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '操作员'
        Caption = '操作员'
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
        Name = '学工号'
        Caption = '学工号'
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
        MonitorValueChangedFields = 
          '|记账开始日期|记账截止日期|交易开始日期|交易截止日期|科目号|账号' +
          '|帐户名|终端编号|终端流水号|交易码|凭证号码|商户号|显示卡号|卡号' +
          '|钱包号|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '帐户交易明细查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '记账开始日期'
        FieldName = '记账开始日期'
      end
      item
        ParamName = '记账截止日期'
        FieldName = '记账截止日期'
      end
      item
        ParamName = '交易开始日期'
        FieldName = '交易开始日期'
      end
      item
        ParamName = '交易截止日期'
        FieldName = '交易截止日期'
      end
      item
        ParamName = '科目号'
        FieldName = '科目号'
      end
      item
        ParamName = '账号'
        FieldName = '账号'
      end
      item
        ParamName = '帐户名'
        FieldName = '帐户名'
      end
      item
        ParamName = '终端编号'
        FieldName = '终端编号'
      end
      item
        ParamName = '终端流水号'
        FieldName = '终端流水号'
      end
      item
        ParamName = '交易码'
        FieldName = '交易码'
      end
      item
        ParamName = '凭证号码'
        FieldName = '凭证号码'
      end
      item
        ParamName = '商户号'
        FieldName = '商户号'
      end
      item
        ParamName = '显示卡号'
        FieldName = '显示卡号'
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '操作员'
        FieldName = '操作员'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'scust_auth'
        DataPresentType = 'idobjects'
        DataPresentParam = '-25'
      end
      item
        FieldName = 'lwithdraw_flag'
        DataPresentType = 'idobjects'
        DataPresentParam = '-9'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '-38'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '-10'
      end
      item
        FieldName = 'lbank_acc_type2'
        DataPresentType = 'idobjects'
        DataPresentParam = '-55'
      end
      item
        FieldName = 'smain_flag'
        DataPresentType = 'idobjects'
        DataPresentParam = '26'
      end
      item
        FieldName = 'lvol9'
        DataPresentType = 'idobjects'
        DataPresentParam = '63'
      end
      item
        FieldName = 'scust_auth2'
        DataPresentType = 'idobjects'
        DataPresentParam = '-25'
      end>
    Left = 160
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 192
    Top = 256
  end
end
