inherited faqhMakeCard2Q: TfaqhMakeCard2Q
  Width = 817
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 817
    inherited btnQuery: TBitBtn
      Left = 640
    end
    inherited btnPrint: TBitBtn
      Left = 727
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 817
    inherited Image1: TImage
      Width = 817
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 817
    Height = 31
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left = 18
      Top = 9
      Width = 72
      Height = 12
      Caption = '审核开始日期'
    end
    object Label2: TLabel
      Left = 218
      Top = 9
      Width = 72
      Height = 12
      Caption = '审核结束日期'
    end
    object Label3: TLabel
      Left = 406
      Top = 9
      Width = 84
      Height = 12
      Caption = '二次制卡批次号'
    end
    object Label4: TLabel
      Left = 618
      Top = 9
      Width = 48
      Height = 12
      Caption = '制卡状态'
    end
    object edtBeginDate: TWVEdit
      Left = 100
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 8
      ReadOnly = False
      TabOrder = 0
      Text = '<审核开始日期>'
      WorkView = WorkView
      FieldName = '审核开始日期'
    end
    object edtEndDate: TWVEdit
      Left = 300
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 8
      ReadOnly = False
      TabOrder = 1
      Text = '<审核结束日期>'
      WorkView = WorkView
      FieldName = '审核结束日期'
    end
    object WVEdit3: TWVEdit
      Left = 500
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<二次制卡批次号>'
      WorkView = WorkView
      FieldName = '二次制卡批次号'
    end
    object cbbDept: TWVComboBox
      Left = 671
      Top = 5
      Width = 103
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      DropDownCount = 20
      ImeName = '中文 (简体) - 微软拼音'
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '制卡状态'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*243'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 49
    Width = 817
    Height = 410
    inherited Grid: TRzDBGrid
      Width = 817
      Height = 410
      Columns = <
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '二次制卡批次号'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '制卡数量'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '同步日期'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '制卡开始日期'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '制卡结束日期'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstat_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '制卡状态'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '更新时间'
          Width = 100
          Visible = True
        end>
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
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
      end
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
        Name = '审核开始日期'
        Caption = '审核开始日期'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '审核结束日期'
        Caption = '审核结束日期'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '二次制卡批次号'
        Caption = '二次制卡批次号'
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
        Name = '制卡状态'
        Caption = '制卡状态'
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
        MonitorValueChangedFields = '|审核开始日期|审核结束日期|二次制卡批次号|制卡状态|'
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '二次制卡结果查询'
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
        ParamName = '审核开始日期'
        FieldName = '审核开始日期'
      end
      item
        ParamName = '审核结束日期'
        FieldName = '审核结束日期'
      end
      item
        ParamName = '二次制卡批次号'
        FieldName = '二次制卡批次号'
      end
      item
        ParamName = '制卡状态'
        FieldName = '制卡状态'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sstat_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '243'
      end>
    Left = 168
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 208
    Top = 256
  end
end
