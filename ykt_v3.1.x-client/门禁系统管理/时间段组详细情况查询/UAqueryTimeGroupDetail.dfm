inherited faqhqueryTimeGroupDetail: TfaqhqueryTimeGroupDetail
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    inherited btnQuery: TBitBtn
      Left = 523
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 610
    end
  end
  inherited Grid: TRzDBGrid
    Top = 78
    Width = 700
    Height = 381
    Columns = <
      item
        Expanded = False
        FieldName = 'lvol0'
        PickList.Strings = ()
        Title.Caption = '时间段组编号'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol2'
        PickList.Strings = ()
        Title.Caption = '时间段编号'
        Width = 70
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'semail'
        PickList.Strings = ()
        Title.Caption = '时间段组名'
        Width = 150
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'semail2'
        PickList.Strings = ()
        Title.Caption = '时间段名称'
        Width = 150
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sdate1'
        PickList.Strings = ()
        Title.Caption = '起始时间'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sdate2'
        PickList.Strings = ()
        Title.Caption = '结束时间'
        Width = 80
        Visible = True
      end>
  end
  object Panel2: TPanel [2]
    Left = 0
    Top = 0
    Width = 700
    Height = 25
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 4
    object Label2: TLabel
      Left = 34
      Top = 5
      Width = 160
      Height = 16
      Caption = '时间段组详细情况查询'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = '黑体'
      Font.Style = []
      ParentFont = False
    end
  end
  object Panel1: TPanel [3]
    Left = 0
    Top = 43
    Width = 700
    Height = 35
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left = 18
      Top = 11
      Width = 72
      Height = 12
      Caption = '时间段组编号'
    end
    object edtNo: TWVDigitalEdit
      Left = 92
      Top = 7
      Width = 100
      Height = 20
      AllowPoint = True
      AllowNegative = True
      UserSeprator = True
      Precision = 0
      MaxIntLen = 10
      Color = clInfoBk
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 0
      TabStop = True
      Text = '0'
      WorkView = WorkView
      FieldName = '时间段组编号'
      SynchronizeByValue = True
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Top = 25
    Width = 700
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
        Name = '时间段组编号'
        Caption = '时间段组编号'
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
        Name = '星期'
        Caption = '星期'
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
        MonitorValueChangedFields = '|时间段组编号|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '时间段组详细情况查询'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '时间段组编号'
        FieldName = '时间段组编号'
      end
      item
        ParamName = '星期'
        FieldName = '星期'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 232
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 264
    Top = 224
  end
end
