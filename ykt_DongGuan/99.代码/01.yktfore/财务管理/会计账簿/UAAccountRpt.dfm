inherited faAccountRpt: TfaAccountRpt
  Width = 784
  Height = 453
  object WVLabel4: TWVLabel [0]
    Left = 160
    Top = 144
    Width = 48
    Height = 12
    Caption = 'WVLabel4'
  end
  inherited pcPages: TRzPageControl
    Width = 784
    Height = 453
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 394
        Width = 780
        Height = 36
        TabOrder = 3
        inherited btnQuery: TBitBtn
          Left = 608
          Top = 5
          TabOrder = 0
        end
        inherited btnAdd: TBitBtn
          Left = 550
          Top = 1000
          TabOrder = 4
          Visible = False
        end
        inherited btnChange: TBitBtn
          Left = 697
          Top = 5
          Hint = '查看报表'
          Caption = '查看报表'
          TabOrder = 1
          Glyph.Data = {00000000}
        end
        inherited btnDelete: TBitBtn
          Left = 827
          Top = 1000
          TabOrder = 5
          Visible = False
        end
        inherited btnViewDetail: TBitBtn
          Top = 1000
          TabOrder = 2
          Visible = False
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Top = 1000
          TabOrder = 3
          Visible = False
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 780
      end
      inherited Grid: TRzDBGrid
        Top = 49
        Width = 780
        Height = 345
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        TabOrder = 2
        OnCellClick = GridCellClick
        Columns = <
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '科目号'
            Width = 74
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '科目名称'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '账簿类型'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '账簿类型'
            Width = 121
            Visible = True
          end>
      end
      object pnlQry: TPanel
        Left = 0
        Top = 18
        Width = 780
        Height = 31
        Align = alTop
        BevelInner = bvSpace
        BevelOuter = bvLowered
        Color = 14999516
        TabOrder = 1
        object Label5: TLabel
          Left = 18
          Top = 9
          Width = 48
          Height = 12
          Caption = '账簿类型'
        end
        object cbbStatus: TWVComboBox
          Left = 68
          Top = 5
          Width = 125
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 0
          Text = '<账簿类型>'
          WorkView = WorkView
          FieldName = '账簿类型'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '166'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      inherited UIPanel2: TUIPanel
        Top = 392
        Width = 780
        Height = 38
        TabOrder = 2
        inherited btnOK: TBitBtn
          Left = 595
          Caption = '报表查询'
          Glyph.Data = {00000000}
        end
        inherited btnCancel: TBitBtn
          Left = 688
          Hint = '关闭该界面，返回操作'
          Caption = '返回(&C)'
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
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
      end
      inherited rmprvwP: TRMPreview
        Top = 41
        Width = 780
        Height = 351
        TabOrder = 1
      end
      object pnlRptQ: TPanel
        Left = 0
        Top = 0
        Width = 780
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
        object lblAccType: TLabel
          Left = 330
          Top = 12
          Width = 60
          Height = 14
          Caption = '账簿类型'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '宋体'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object chkAcc: TCheckBox
          Left = 656
          Top = 11
          Width = 97
          Height = 17
          Caption = '含未入账凭证'
          TabOrder = 3
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
          WorkView = wv850061
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
          WorkView = wv850061
          FieldName = '结束日期'
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 248
    Top = 320
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
        Name = '账簿类型'
        Caption = '账簿类型'
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
    Left = 176
    Top = 319
  end
  inherited QueryRequest: TWVRequest
    ID = '会计账簿查询'
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
        ParamName = '账簿类型'
        FieldName = '账簿类型'
      end>
    Top = 312
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'lvol1'
        DataPresentType = 'idobjects'
        DataPresentParam = '166'
      end>
  end
  inherited rmhtmxprt1: TRMHTMExport
    Left = 107
    Top = 277
  end
  inherited rmbmpxprt1: TRMBMPExport
    Left = 139
    Top = 277
  end
  inherited rmjpgxprt1: TRMJPEGExport
    Left = 171
    Top = 277
  end
  inherited rmxlsxprt1: TRMXLSExport
    Left = 203
    Top = 277
  end
  inherited ImageList1: TImageList
    Left = 234
    Top = 277
  end
  inherited SaveDialog: TSaveDialog
    Left = 272
    Top = 274
  end
  inherited dlgOpenRpt: TOpenDialog
    Left = 307
    Top = 277
  end
  inherited rmdsgnrD: TRMDesigner
    Left = 416
    Top = 274
  end
  inherited rmDS1: TRMDBDataSet
    DataSet = zqry1
    Left = 380
    Top = 271
  end
  inherited rptQRpt: TRMReport
    Left = 348
    Top = 271
    ReportData = {}
  end
  object zqry1: TZQuery
    Connection = cmAccountMgrImp.conFB
    SQL.Strings = (
      'select * from accountquery order by lineno')
    Params = <>
    Left = 451
    Top = 273
  end
  object wv850061: TWorkView
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
        DataField = '@Return'
      end
      item
        Name = '返回信息'
        Caption = '返回信息'
        FieldType = wftUndefined
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
        Name = '科目号'
        Caption = '科目号'
        FieldType = wftUndefined
        DataType = kdtString
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
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    Left = 112
    Top = 151
  end
  object wvr850061: TWVRequest
    WorkView = wv850061
    ID = '总分类账查询'
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
        ParamName = '科目号'
        FieldName = '科目号'
      end
      item
        ParamName = '包含未入账'
        FieldName = '包含未入账'
      end>
    AfterExec = CheckReturnData
    Left = 112
    Top = 184
  end
  object wvr850062: TWVRequest
    WorkView = wv850062
    ID = '日记账查询'
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
        ParamName = '科目号'
        FieldName = '科目号'
      end
      item
        ParamName = '包含未入账'
        FieldName = '包含未入账'
      end>
    AfterExec = CheckReturnData
    Left = 144
    Top = 184
  end
  object wv850062: TWorkView
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
        DataField = '@Return'
      end
      item
        Name = '返回信息'
        Caption = '返回信息'
        FieldType = wftUndefined
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
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '结束日期'
        Caption = '结束日期'
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
        Name = '科目号'
        Caption = '科目号'
        FieldType = wftUndefined
        DataType = kdtString
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
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    Left = 144
    Top = 151
  end
  object wvr850063: TWVRequest
    WorkView = wv850063
    ID = '明细分类帐查询'
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
        ParamName = '科目号'
        FieldName = '科目号'
      end
      item
        ParamName = '包含未入账'
        FieldName = '包含未入账'
      end
      item
        ParamName = '查询方式'
        FieldName = '查询方式'
      end>
    AfterExec = CheckReturnData
    Left = 176
    Top = 184
  end
  object wv850063: TWorkView
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
        DataField = '@Return'
      end
      item
        Name = '返回信息'
        Caption = '返回信息'
        FieldType = wftUndefined
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
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '结束日期'
        Caption = '结束日期'
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
        Name = '科目号'
        Caption = '科目号'
        FieldType = wftUndefined
        DataType = kdtString
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
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    Left = 176
    Top = 151
  end
end
