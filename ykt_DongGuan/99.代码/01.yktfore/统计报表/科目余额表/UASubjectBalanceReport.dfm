inherited faqhSubjectBalanceReport: TfaqhSubjectBalanceReport
  Width = 702
  Height = 517
  inherited upnlBottom: TUIPanel
    Top = 480
    Width = 702
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
      Left = 608
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 702
    inherited Image1: TImage
      Width = 702
    end
    inherited LabRecordCount: TLabel
      Visible = False
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 702
    Height = 31
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object lbl1: TLabel
      Left = 32
      Top = 10
      Width = 24
      Height = 12
      Caption = '科目'
    end
    object lblBusiName: TLabel
      Left = 104
      Top = 7
      Width = 6
      Height = 12
      Font.Charset = GB2312_CHARSET
      Font.Color = clMaroon
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object WVLabel1: TWVLabel
      Left = 290
      Top = 10
      Width = 48
      Height = 12
      Caption = '开始日期'
    end
    object WVLabel2: TWVLabel
      Left = 432
      Top = 10
      Width = 48
      Height = 12
      Caption = '结束日期'
    end
    object edtBeginDate: TWVEdit
      Left = 344
      Top = 6
      Width = 81
      Height = 20
      Color = clWhite
      ImeName = '中文 (简体) - 微软拼音'
      ReadOnly = False
      TabOrder = 1
      Text = '<开始日期>'
      WorkView = WorkView
      FieldName = '开始日期'
    end
    object edtEndDate: TWVEdit
      Left = 488
      Top = 6
      Width = 89
      Height = 20
      Color = clWhite
      ImeName = '中文 (简体) - 微软拼音'
      ReadOnly = False
      TabOrder = 2
      Text = '<结束日期>'
      WorkView = WorkView
      FieldName = '结束日期'
    end
    object cbbBusiName: TWVComboBox
      Left = 64
      Top = 5
      Width = 217
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      DropDownCount = 20
      ImeName = '紫光拼音输入法'
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '科目号'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-25'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 49
    Width = 702
    Height = 431
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 702
      Height = 431
      Columns = <
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '科目号'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '科目名称'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Caption = '结算日期'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '期初借方余额'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '期初贷方余额'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '借方发生额'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '贷方发生额'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '期末借方余额'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt6'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '期末贷方余额'
          Width = 80
          Visible = True
        end>
    end
    inherited rmprvwP: TRMPreview
      Width = 702
      Height = 431
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
      end
      item
        Name = '科目号'
        Caption = '科目号'
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
        GroupIndex = 1
      end
      item
        Name = '开始日期'
        Caption = '开始日期'
        FieldType = wftUndefined
        DomainName = '日期校验'
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
        DomainName = '日期校验'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|开始日期|结束日期|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 156
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '科目余额表'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '科目号'
        FieldName = '科目号'
      end
      item
        ParamName = '开始日期'
        FieldName = '开始日期'
      end
      item
        ParamName = '结束日期'
        FieldName = '结束日期'
      end>
    Left = 192
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'damt1'
        DataPresentType = '货币'
      end
      item
        FieldName = 'damt2'
        DataPresentType = '货币'
      end
      item
        FieldName = 'damt3'
        DataPresentType = '货币'
      end
      item
        FieldName = 'damt4'
        DataPresentType = '货币'
      end
      item
        FieldName = 'damt5'
        DataPresentType = '货币'
      end
      item
        FieldName = 'damt6'
        DataPresentType = '货币'
      end>
    Left = 224
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 344
    Top = 224
  end
  inherited rptReport: TRMReport
    ReportData = {}
  end
  inherited rmDS: TRMDBDataSet
    DataSet = ztbl1
  end
  object ztbl1: TZTable
    Connection = dmReportImp.conSLite
    SortedFields = 'ACCDATE Desc,SUBJNO Asc'
    SortType = stIgnored
    TableName = 'T_RPTSUBJBAL'
    IndexFieldNames = 'ACCDATE Desc,SUBJNO Asc'
    Left = 411
    Top = 92
  end
end
