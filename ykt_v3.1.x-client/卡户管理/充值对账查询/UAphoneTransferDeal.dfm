inherited faqhphoneTransferDeal: TfaqhphoneTransferDeal
  Width = 753
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 448
    Width = 753
    Height = 41
    TabOrder = 4
    inherited btnQuery: TBitBtn
      Left = 488
      Top = 8
      Enabled = False
      TabOrder = 1
    end
    inherited btnPrint: TBitBtn
      Left = 575
      Top = 8
      TabOrder = 2
    end
    object chkSelectAll: TCheckBox
      Left = 16
      Top = 13
      Width = 57
      Height = 17
      Caption = '全选'
      TabOrder = 4
      OnClick = chkSelectAllClick
    end
    object btnDeal: TImageButton
      Left = 664
      Top = 8
      Width = 75
      Height = 25
      Hint = '对账处理'
      Anchors = [akTop, akRight]
      Caption = '对账处理'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnDealClick
    end
    object GroupBox1: TGroupBox
      Left = 96
      Top = -3
      Width = 305
      Height = 41
      TabOrder = 0
      object Label8: TLabel
        Left = 10
        Top = 18
        Width = 84
        Height = 12
        Caption = '手工对账日期：'
      end
      object dtpDate: TDateTimePicker
        Left = 96
        Top = 13
        Width = 105
        Height = 20
        CalAlignment = dtaLeft
        Date = 39373.412233588
        Time = 39373.412233588
        DateFormat = dfShort
        DateMode = dmComboBox
        Kind = dtkDate
        ParseInput = False
        TabOrder = 1
      end
      object btnTrans: TImageButton
        Left = 208
        Top = 11
        Width = 75
        Height = 25
        Hint = '手工对账'
        Anchors = [akTop, akRight]
        Caption = '手工对账'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = btnTransClick
      end
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 753
    inherited Image1: TImage
      Width = 753
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 753
    Height = 54
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 42
      Top = 9
      Width = 48
      Height = 12
      Caption = '交易日期'
    end
    object Label2: TLabel
      Left = 222
      Top = 9
      Width = 36
      Height = 12
      Caption = '客户号'
    end
    object Label3: TLabel
      Left = 418
      Top = 9
      Width = 24
      Height = 12
      Caption = '卡号'
    end
    object Label4: TLabel
      Left = 42
      Top = 33
      Width = 48
      Height = 12
      Caption = '手机号码'
    end
    object Label5: TLabel
      Left = 234
      Top = 33
      Width = 24
      Height = 12
      Caption = '姓名'
    end
    object Label6: TLabel
      Left = 394
      Top = 33
      Width = 48
      Height = 12
      Caption = '对账状态'
    end
    object Label7: TLabel
      Left = 570
      Top = 33
      Width = 48
      Height = 12
      Caption = '处理状态'
    end
    object WVEdit1: TWVEdit
      Left = 100
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 0
      Text = '<交易日期>'
      WorkView = WorkView
      FieldName = '交易日期'
    end
    object edtCustNo: TWVEdit
      Left = 268
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<客户号>'
      WorkView = WorkView
      FieldName = '客户号'
    end
    object edtCardNo: TWVEdit
      Left = 452
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 2
      Text = '<卡号>'
      WorkView = WorkView
      FieldName = '卡号'
    end
    object WVEdit4: TWVEdit
      Left = 100
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 5
      Text = '<手机号码>'
      WorkView = WorkView
      FieldName = '手机号码'
    end
    object WVEdit5: TWVEdit
      Left = 268
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 6
      Text = '<姓名>'
      WorkView = WorkView
      FieldName = '姓名'
    end
    object cbbCustType: TWVComboBox
      Left = 452
      Top = 28
      Width = 102
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ImeName = '紫光拼音输入法'
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '对账状态'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*93'
    end
    object WVComboBox1: TWVComboBox
      Left = 629
      Top = 28
      Width = 100
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ImeName = '紫光拼音输入法'
      ItemHeight = 12
      TabOrder = 4
      WorkView = WorkView
      FieldName = '处理状态'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*94'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 72
    Width = 753
    Height = 376
    TabOrder = 3
    inherited Grid: TRzDBGrid
      Width = 753
      Height = 376
      Columns = <
        item
          Expanded = False
          FieldName = 'sorder0'
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
          Title.Caption = '卡号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户号'
          Width = 80
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
          FieldName = 'lserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '流水号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易金额'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '手机号码'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '对账状态'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '处理状态'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '处理操作员'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '处理日期'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '处理时间'
          Width = 80
          Visible = True
        end>
    end
  end
  object lvSerial: TRzListView [4]
    Left = 0
    Top = 72
    Width = 753
    Height = 376
    Align = alClient
    Checkboxes = True
    Columns = <
      item
        Caption = '流水号'
        Width = 80
      end
      item
        Caption = '客户号'
        Width = 80
      end
      item
        Caption = '卡号'
        Width = 80
      end
      item
        Caption = '客户姓名'
        Width = 80
      end
      item
        Caption = '交易日期'
        Width = 80
      end
      item
        Caption = '交易时间'
        Width = 80
      end
      item
        Caption = '交易金额'
        Width = 80
      end
      item
        Caption = '手机号码'
        Width = 100
      end
      item
        Caption = '对账状态'
        Width = 80
      end
      item
        Caption = '处理状态'
        Width = 80
      end
      item
        Caption = '处理操作员'
        Width = 100
      end
      item
        Caption = '处理日期'
        Width = 80
      end
      item
        Caption = '处理时间'
        Width = 80
      end>
    ColumnClick = False
    FlatScrollBars = True
    GridLines = True
    RowSelect = True
    TabOrder = 2
    ViewStyle = vsReport
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
        Name = '交易日期'
        Caption = '交易日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
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
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '手机号码'
        Caption = '手机号码'
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
        Name = '姓名'
        Caption = '姓名'
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
        Name = '对账状态'
        Caption = '对账状态'
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
        Name = '处理状态'
        Caption = '处理状态'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|手机号码|姓名|对账状态|处理状态|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '移动充值对账查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '交易日期'
        FieldName = '交易日期'
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '手机号码'
        FieldName = '手机号码'
      end
      item
        ParamName = '姓名'
        FieldName = '姓名'
      end
      item
        ParamName = '对账状态'
        FieldName = '对账状态'
      end
      item
        ParamName = '处理状态'
        FieldName = '处理状态'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '93'
      end
      item
        FieldName = 'sstatus2'
        DataPresentType = 'idobjects'
        DataPresentParam = '94'
      end>
    Left = 240
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 280
    Top = 224
  end
  object WorkView1: TWorkView
    WorkFields = <
      item
        Name = '交易日期'
        Caption = '交易日期'
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
        Name = '交易流水号'
        Caption = '交易流水号'
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
        Name = '卡号'
        Caption = '卡号'
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
        Name = '操作员'
        Caption = '操作员'
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
        MonitorValueChangedFields = '|'
      end>
    Left = 164
    Top = 103
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '移动充值对账处理'
    Bindings = <
      item
        ParamName = '交易日期'
        FieldName = '交易日期'
      end
      item
        ParamName = '交易流水号'
        FieldName = '交易流水号'
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
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 104
  end
  object WorkView2: TWorkView
    WorkFields = <
      item
        Name = '对账日期'
        Caption = '对账日期'
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
        MonitorValueChangedFields = '|'
      end>
    Left = 164
    Top = 143
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '手工对账'
    Bindings = <
      item
        ParamName = '对账日期'
        FieldName = '对账日期'
      end
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 144
  end
end
