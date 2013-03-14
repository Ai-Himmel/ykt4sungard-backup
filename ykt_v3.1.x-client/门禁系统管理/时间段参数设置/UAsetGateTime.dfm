inherited faqhsetGateTime: TfaqhsetGateTime
  Width = 681
  Height = 477
  Caption = '时间段参数设置'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 418
        Width = 677
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 504
          Top = 6
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 591
          Top = 6
          Enabled = False
          TabOrder = 1
        end
        inherited btnQuery: TBitBtn [2]
          Left = 418
          Top = 6
        end
        inherited btnDelete: TBitBtn
          Left = 316
          Top = 6
          Enabled = False
          TabOrder = 2
          Visible = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
          Top = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 11
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
        Align = alNone
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 677
        Height = 385
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '标识'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '时间段名称'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '开始时间'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '结束时间'
            Width = 100
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 677
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label1: TLabel
          Left = 142
          Top = 10
          Width = 60
          Height = 12
          Caption = '时间段名称'
        end
        object Label4: TLabel
          Left = 34
          Top = 10
          Width = 24
          Height = 12
          Caption = '标识'
        end
        object WVEdit1: TWVEdit
          Left = 204
          Top = 6
          Width = 100
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 0
          Text = '<查询.时间段名称>'
          WorkView = WorkView
          FieldName = '查询.时间段名称'
        end
        object WVDigitalEdit4: TWVDigitalEdit
          Left = 68
          Top = 6
          Width = 61
          Height = 20
          AllowPoint = True
          AllowNegative = True
          UserSeprator = True
          Precision = 0
          MaxIntLen = 10
          Color = clInfoBk
          ParentColor = False
          TabOrder = 1
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '查询.标识'
          SynchronizeByValue = True
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label6: TLabel [0]
        Left = 184
        Top = 164
        Width = 70
        Height = 14
        Caption = '时间段名称'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label7: TLabel [1]
        Left = 198
        Top = 204
        Width = 56
        Height = 14
        Caption = '开始时间'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label8: TLabel [2]
        Left = 198
        Top = 244
        Width = 56
        Height = 14
        Caption = '结束时间'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label10: TLabel [3]
        Left = 42
        Top = 5
        Width = 112
        Height = 16
        Caption = '时间段参数设置'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '黑体'
        Font.Style = []
        ParentFont = False
      end
      object Label5: TLabel [4]
        Left = 226
        Top = 130
        Width = 28
        Height = 14
        Caption = '标识'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label11: TLabel [5]
        Left = 366
        Top = 204
        Width = 84
        Height = 14
        Caption = '时间格式hhmm'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
      end
      object Label12: TLabel [6]
        Left = 366
        Top = 244
        Width = 84
        Height = 14
        Caption = '时间格式hhmm'
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
        TabOrder = 3
        inherited btnOK: TBitBtn
          Left = 505
        end
        inherited btnCancel: TBitBtn
          Left = 593
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtName: TWVEdit
        Left = 260
        Top = 160
        Width = 237
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
        Text = '<时间段名称>'
        WorkView = WorkView
        FieldName = '时间段名称'
        SynchronizeWhenExit = True
      end
      object edtBTime: TWVEdit
        Left = 260
        Top = 200
        Width = 100
        Height = 22
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 4
        ParentFont = False
        ReadOnly = False
        TabOrder = 1
        Text = '<开始时间>'
        WorkView = WorkView
        FieldName = '开始时间'
        SynchronizeWhenExit = True
      end
      object edtETime: TWVEdit
        Left = 260
        Top = 240
        Width = 100
        Height = 22
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        MaxLength = 4
        ParentFont = False
        ReadOnly = False
        TabOrder = 2
        Text = '<结束时间>'
        WorkView = WorkView
        FieldName = '结束时间'
        SynchronizeWhenExit = True
      end
      object edtNo: TWVDigitalEdit
        Left = 260
        Top = 126
        Width = 101
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        TabOrder = 4
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '标识'
        SynchronizeByValue = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 332
    Top = 327
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
        Name = '查询.时间段名称'
        Caption = '查询.时间段名称'
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
      end
      item
        Name = '查询.开始时间'
        Caption = '查询.开始时间'
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
      end
      item
        Name = '查询.结束时间'
        Caption = '查询.结束时间'
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
      end
      item
        Name = '查询.标识'
        Caption = '查询.标识'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '交易类型'
        Caption = '交易类型'
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
      end
      item
        Name = '时间段名称'
        Caption = '时间段名称'
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
        GroupIndex = 1
        DataField = 'semail'
      end
      item
        Name = '开始时间'
        Caption = '开始时间'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 4
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sdate0'
      end
      item
        Name = '结束时间'
        Caption = '结束时间'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 4
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sdate1'
      end
      item
        Name = '标识'
        Caption = '标识'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol0'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|查询.时间段名称|查询.开始时间|查询.结束时间|查询.标识|查询.交易' +
          '类型|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|时间段名称|开始时间|结束时间|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 240
  end
  inherited QueryRequest: TWVRequest
    ID = '时间段参数查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '时间段名称'
        FieldName = '查询.时间段名称'
      end
      item
        ParamName = '开始时间'
        FieldName = '查询.开始时间'
      end
      item
        ParamName = '结束时间'
        FieldName = '查询.结束时间'
      end
      item
        ParamName = '标识'
        FieldName = '查询.标识'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 368
    Top = 288
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 300
    Top = 327
  end
  inherited AddRequest: TWVRequest
    ID = '时间段参数设置'
    Bindings = <
      item
        ParamName = '时间段名称'
        FieldName = '时间段名称'
      end
      item
        ParamName = '开始时间'
        FieldName = '开始时间'
      end
      item
        ParamName = '结束时间'
        FieldName = '结束时间'
      end
      item
        ParamName = '标识'
        FieldName = '标识'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 272
    Top = 288
  end
  inherited DeleteRequest: TWVRequest
    ID = '时间段参数设置'
    Bindings = <
      item
        ParamName = '时间段名称'
        FieldName = '时间段名称'
      end
      item
        ParamName = '开始时间'
        FieldName = '开始时间'
      end
      item
        ParamName = '结束时间'
        FieldName = '结束时间'
      end
      item
        ParamName = '标识'
        FieldName = '标识'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 304
    Top = 288
  end
  inherited ChangeRequest: TWVRequest
    ID = '时间段参数设置'
    Bindings = <
      item
        ParamName = '时间段名称'
        FieldName = '时间段名称'
      end
      item
        ParamName = '开始时间'
        FieldName = '开始时间'
      end
      item
        ParamName = '结束时间'
        FieldName = '结束时间'
      end
      item
        ParamName = '标识'
        FieldName = '标识'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 336
    Top = 288
  end
  inherited WVDataSource: TWVDataSource
    Left = 396
    Top = 327
  end
  inherited alDatasetActions: TActionList
    Left = 364
    Top = 324
  end
end
