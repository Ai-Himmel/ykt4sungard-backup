inherited faQueryAreaTable: TfaQueryAreaTable
  Width = 709
  Height = 453
  object WVLabel4: TWVLabel [0]
    Left = 160
    Top = 144
    Width = 48
    Height = 12
    Caption = 'WVLabel4'
  end
  inherited upnlBottom: TUIPanel
    Top = 416
    Width = 709
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
        btnDesign
        btnOpenRpt)
    end
    inherited btnQuery: TBitBtn
      Left = 608
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 709
    inherited Image1: TImage
      Width = 709
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 709
    Height = 398
    inherited Grid: TRzDBGrid
      Top = 128
      Width = 709
      Height = 270
      Align = alNone
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
      TabOrder = 2
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '区域号'
          Width = 74
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '区域名称'
          Width = 79
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '父区域'
          Width = 75
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '区域级别'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scusttypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '详细地址'
          Width = 124
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ssectypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '备注'
          Width = 130
          Visible = True
        end>
    end
    inherited rmprvwP: TRMPreview
      Top = 41
      Width = 709
      Height = 357
      TabOrder = 1
    end
    object pnlRptQ: TPanel
      Left = 0
      Top = 0
      Width = 709
      Height = 41
      Align = alTop
      BevelOuter = bvNone
      Color = 14999516
      TabOrder = 0
      object lbl2: TLabel
        Left = 210
        Top = 14
        Width = 12
        Height = 12
        Caption = '至'
      end
      object Label5: TLabel
        Left = 322
        Top = 13
        Width = 48
        Height = 12
        Caption = '汇总级别'
      end
      object chkAcc: TCheckBox
        Left = 592
        Top = 11
        Width = 97
        Height = 17
        Caption = '含未入账凭证'
        TabOrder = 5
        Visible = False
      end
      object rgQType: TRzRadioGroup
        Left = 8
        Top = 8
        Width = 101
        Height = 17
        Color = 14999516
        Columns = 2
        GroupStyle = gsTopLine
        ItemIndex = 1
        Items.Strings = (
          '月份'
          '日期')
        TabOrder = 0
        ThemeAware = False
        OnClick = rgQTypeClick
      end
      object edtBeginDate: TWVEdit
        Left = 115
        Top = 8
        Width = 90
        Height = 20
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        MaxLength = 22
        ReadOnly = False
        TabOrder = 1
        Text = '<开始日期>'
        WorkView = WorkView
        FieldName = '开始日期'
      end
      object edtEndDate: TWVEdit
        Left = 227
        Top = 8
        Width = 90
        Height = 20
        Color = clWhite
        ImeName = '中文 (简体) - 微软拼音'
        MaxLength = 22
        ReadOnly = False
        TabOrder = 2
        Text = '<结束日期>'
        WorkView = WorkView
        FieldName = '结束日期'
      end
      object chkShowSub: TCheckBox
        Left = 472
        Top = 11
        Width = 121
        Height = 17
        Caption = '显示未交易的科目'
        TabOrder = 4
      end
      object cbbLeval: TWVComboBox
        Left = 372
        Top = 9
        Width = 93
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView
        FieldName = '科目级别'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '-70'
      end
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
        DataField = '@Return'
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
        DataField = '@Dataset'
      end
      item
        Name = '开始日期'
        Caption = '开始日期'
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
      end
      item
        Name = '结束日期'
        Caption = '结束日期'
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
      end
      item
        Name = '科目级别'
        Caption = '科目级别'
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
        Name = '包含未入账'
        Caption = '包含未入账'
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
        Name = '查询方式'
        Caption = '查询方式'
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
        Name = '显示未交易'
        Caption = '显示未交易'
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
    Top = 183
  end
  inherited MainRequest: TWVRequest
    ID = '科目汇总报表'
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
        ParamName = '开始日期'
        FieldName = '开始日期'
      end
      item
        ParamName = '结束日期'
        FieldName = '结束日期'
      end
      item
        ParamName = '科目级别'
        FieldName = '科目级别'
      end
      item
        ParamName = '包含未入账'
        FieldName = '包含未入账'
      end
      item
        ParamName = '查询方式'
        FieldName = '查询方式'
      end
      item
        ParamName = '显示未交易'
        FieldName = '显示未交易'
      end>
    Left = 104
    Top = 184
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Left = 144
    Top = 184
  end
  inherited DataSource: TDataSource
    Left = 184
    Top = 184
  end
  inherited rptReport: TRMReport
    ReportData = {}
  end
  inherited rmDS: TRMDBDataSet
    DataSet = zqry1
  end
  object zqry1: TZQuery
    Connection = cmAccountMgrImp.conFB
    SQL.Strings = (
      'select * from subjtot order by lineno')
    Params = <>
    Left = 259
    Top = 89
  end
end
