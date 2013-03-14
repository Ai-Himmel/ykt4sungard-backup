inherited faqhSetChargeType: TfaqhSetChargeType
  Width = 681
  Height = 477
  Caption = '收费类别设置'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    ActivePage = tsEdit
    TabIndex = 1
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 418
        Width = 677
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 416
          Top = 6
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 502
          Top = 6
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 330
          Top = 6
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Top = 6
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
          Top = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 11
          Width = 165
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 53
        Width = 677
        Height = 365
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Caption = '收费编号'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '收费名称'
            Width = 276
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '是否收搭伙费'
            Width = 120
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 35
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label1: TLabel
          Left = 20
          Top = 11
          Width = 48
          Height = 12
          Caption = '收费名称'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          ParentFont = False
        end
        object WVEdit1: TWVEdit
          Left = 80
          Top = 6
          Width = 179
          Height = 20
          Color = clInfoBk
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '宋体'
          Font.Style = []
          MaxLength = 9
          ParentFont = False
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.收费类别>'
          WorkView = WorkView
          FieldName = '查询.收费类别'
          SynchronizeWhenExit = True
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label5: TLabel [0]
        Left = 164
        Top = 130
        Width = 63
        Height = 14
        Caption = '收费名称*'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label2: TLabel [1]
        Left = 164
        Top = 98
        Width = 63
        Height = 14
        Caption = '收费编号*'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel [2]
        Left = 418
        Top = 98
        Width = 126
        Height = 14
        Caption = '编号值在10-255之间'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 4
        inherited btnOK: TBitBtn
          Left = 505
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 593
          TabOrder = 2
          TabStop = True
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object edtName: TWVEdit
        Left = 233
        Top = 123
        Width = 179
        Height = 22
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        ReadOnly = False
        TabOrder = 1
        Text = '<收费类别>'
        WorkView = WorkView
        FieldName = '收费类别'
        SynchronizeWhenExit = True
      end
      object chkif: TRzCheckBox
        Left = 232
        Top = 160
        Width = 115
        Height = 17
        Caption = '是否收搭伙费'
        FrameColor = 8409372
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        HighlightColor = 2203937
        HotTrack = True
        HotTrackColor = 3983359
        HotTrackColorType = htctActual
        ParentFont = False
        State = cbUnchecked
        TabOrder = 2
        OnClick = chkifClick
      end
      object edtId: TWVDigitalEdit
        Left = 233
        Top = 94
        Width = 179
        Height = 20
        AllowPoint = True
        AllowNegative = True
        Precision = 0
        MaxIntLen = 3
        ParentColor = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '类别标志'
        SynchronizeByValue = True
      end
      object cbbfeetype: TWVComboBox
        Left = 240
        Top = 256
        Width = 201
        Height = 18
        Style = csOwnerDrawFixed
        Color = clWhite
        ItemHeight = 12
        TabOrder = 3
        Visible = False
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-43'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 252
    Top = 359
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '查询结果集'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '操作类别.增加'
        Caption = '操作类别.增加'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '1'
      end
      item
        Name = '操作类别.删除'
        Caption = '操作类别.删除'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '2'
      end
      item
        Name = '操作类别.修改'
        Caption = '操作类别.修改'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '3'
      end
      item
        Name = '查询.收费类别'
        Caption = '查询.收费类别'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        DataField = 'scust_no'
      end
      item
        Name = '查询.是否收搭伙费'
        Caption = '查询.交易类别'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sname'
      end
      item
        Name = '类别标志'
        Caption = '类别标志'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 2
        Checker.MaxLength = 3
        Checker.Min = 10
        Checker.Max = 255
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '收费类别'
        Caption = '收费类别'
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
        GroupIndex = 1
        DataField = 'scusttypes'
      end
      item
        Name = '是否收搭伙费'
        Caption = '是否收搭伙费'
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
        DataField = 'sname'
      end
      item
        Name = '标志'
        Caption = '标志'
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
        DataField = 'sstatus0'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|查询.收费类别|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 88
    Top = 360
  end
  inherited QueryRequest: TWVRequest
    ID = '收费类别设置'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '收费类别'
        FieldName = '查询.收费类别'
      end
      item
        ParamName = '是否收搭伙费'
        FieldName = '查询.是否收搭伙费'
      end
      item
        ParamName = '类别标志'
        FieldName = '类别标志'
      end
      item
        ParamName = '标志'
        FieldName = '标志'
      end>
    Left = 208
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sall_name'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end>
    Left = 132
    Top = 359
  end
  inherited AddRequest: TWVRequest
    ID = '收费类别设置'
    Bindings = <
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '是否收搭伙费'
        FieldName = '是否收搭伙费'
      end
      item
        ParamName = '类别标志'
        FieldName = '类别标志'
      end
      item
        ParamName = '标志'
        FieldName = '标志'
      end>
    Left = 88
  end
  inherited DeleteRequest: TWVRequest
    ID = '收费类别设置'
    Bindings = <
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '是否收搭伙费'
        FieldName = '是否收搭伙费'
      end
      item
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '类别标志'
        FieldName = '类别标志'
      end>
    Left = 128
  end
  inherited ChangeRequest: TWVRequest
    ID = '收费类别设置'
    Bindings = <
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '是否收搭伙费'
        FieldName = '是否收搭伙费'
      end
      item
        ParamName = '标志'
        FieldName = '标志'
      end
      item
        ParamName = '类别标志'
        FieldName = '类别标志'
      end>
  end
  inherited WVDataSource: TWVDataSource
    Left = 212
    Top = 359
  end
  inherited alDatasetActions: TActionList
    Left = 172
    Top = 356
  end
end
