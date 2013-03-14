inherited faqhBusiGatherReport: TfaqhBusiGatherReport
  Width = 745
  Height = 470
  inherited upnlBottom: TUIPanel
    Top = 433
    Width = 745
    TabOrder = 3
    inherited tlb1: TRzToolbar
      ToolbarControls = (
        btn100
        btnPageWidth
        rzspcr1
        btnFirst
        btnprevious
        btnNext
        btnLast
        rzspcr2
        btnExpXls
        btnPagePrint
        btnSetup
        rzspcr3
        btnDesign)
    end
    inherited btnQuery: TBitBtn
      Left = 648
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 745
    inherited Image1: TImage
      Width = 745
    end
    inherited LabRecordCount: TLabel
      Width = 169
      Visible = False
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 48
    Width = 745
    Height = 385
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Top = 25
      Width = 536
      Height = 360
      Columns = <
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '商户名'
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '摘要'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '交易次数'
          Width = 60
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'sserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '收入'
          Width = 80
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'sserial2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '支出'
          Width = 80
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'sserial3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '结算金额'
          Width = 80
          Visible = True
        end>
    end
    inherited rmprvwP: TRMPreview
      Top = 25
      Width = 536
      Height = 360
      TabOrder = 3
    end
    inherited RzSizePanel1: TRzSizePanel
      Top = 25
      Height = 360
      TabOrder = 1
      inherited tvTree: TRzTreeView
        Height = 360
        OnClick = tvtreeClick
      end
    end
    object pnl1: TPanel
      Left = 0
      Top = 0
      Width = 745
      Height = 25
      Align = alTop
      Alignment = taLeftJustify
      BevelOuter = bvNone
      Color = 15458000
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
    end
  end
  object Panel1: TPanel [3]
    Left = 0
    Top = 18
    Width = 745
    Height = 30
    Align = alTop
    Color = 16184303
    TabOrder = 1
    object lbl1: TLabel
      Left = 24
      Top = 8
      Width = 48
      Height = 12
      Caption = '开始日期'
    end
    object Label1: TLabel
      Left = 200
      Top = 8
      Width = 48
      Height = 12
      Caption = '结束日期'
    end
    object lbl2: TLabel
      Left = 376
      Top = 8
      Width = 48
      Height = 12
      Caption = '显示级别'
    end
    object Label2: TLabel
      Left = 560
      Top = 9
      Width = 48
      Height = 12
      Caption = '商户类型'
    end
    object edtBeginDate: TWVEdit
      Left = 81
      Top = 4
      Width = 96
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<开始日期>'
      WorkView = WorkView
      FieldName = '开始日期'
    end
    object edtEndDate: TWVEdit
      Left = 257
      Top = 4
      Width = 96
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<结束日期>'
      WorkView = WorkView
      FieldName = '结束日期'
    end
    object cbbleave: TComboBox
      Left = 432
      Top = 4
      Width = 105
      Height = 20
      ItemHeight = 12
      TabOrder = 2
    end
    object cbbType: TWVComboBox
      Left = 616
      Top = 4
      Width = 129
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 20
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '商户类型'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*24'
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
        Name = '商户账号'
        Caption = '商户账号'
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
      end
      item
        Name = '开始日期'
        Caption = '开始日期'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
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
      end
      item
        Name = '结束日期'
        Caption = '结束日期'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
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
      end
      item
        Name = '级别'
        Caption = '级别'
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
        Name = '商户类型'
        Caption = '商户类型'
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
        MonitorValueChangedFields = '|操作员号|密码|商户账号|金额|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '商户汇总结算表'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '商户帐号'
        FieldName = '商户账号'
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
      end
      item
        ParamName = '开始日期'
        FieldName = '开始日期'
      end
      item
        ParamName = '结束日期'
        FieldName = '结束日期'
      end
      item
        ParamName = '级别'
        FieldName = '级别'
      end
      item
        ParamName = '商户类型'
        FieldName = '商户类型'
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
  inherited rptReport: TRMReport
    ReportData = {}
  end
  inherited rmDS: TRMDBDataSet
    DataSet = ztbl1
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
  object ztbl1: TZTable
    Connection = dmReportImp.conSLite
    SortedFields = 'SORTID'
    TableName = 't_rptdailyacc'
    IndexFieldNames = 'SORTID Asc'
    Left = 408
    Top = 92
  end
end
