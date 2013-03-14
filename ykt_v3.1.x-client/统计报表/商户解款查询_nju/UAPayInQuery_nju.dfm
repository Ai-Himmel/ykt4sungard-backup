inherited faqhBusiPayInQuery_nju: TfaqhBusiPayInQuery_nju
  Width = 716
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 716
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 539
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 626
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 716
    TabOrder = 2
    inherited Image1: TImage
      Width = 716
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 716
    Height = 28
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object WVLabel1: TWVLabel
      Left = 322
      Top = 8
      Width = 48
      Height = 12
      Caption = '解款年份'
    end
    object lblBusiname: TLabel
      Left = 8
      Top = 8
      Width = 297
      Height = 12
      AutoSize = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object edtBeginDate: TWVEdit
      Left = 376
      Top = 4
      Width = 81
      Height = 20
      Color = clWhite
      ImeName = '中文 (简体) - 微软拼音'
      ReadOnly = False
      TabOrder = 0
      Text = '<开始日期>'
      WorkView = WorkView
      FieldName = '解款年份'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 46
    Width = 716
    Height = 413
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Width = 507
      Height = 413
      Columns = <
        item
          Expanded = False
          FieldName = 'Lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '商户号'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '商户名'
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '结算期间(年月)'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '解款金额'
          Width = 70
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '解款日期'
          Width = 70
          Visible = True
        end
        item
          Alignment = taRightJustify
          Expanded = False
          FieldName = 'semp_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '解款操作员'
          Width = 80
          Visible = True
        end>
    end
    inherited RzSizePanel1: TRzSizePanel
      Height = 413
      inherited tvTree: TRzTreeView
        Height = 413
        OnClick = tvCustClick
      end
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
        Name = '商户号'
        Caption = '商户号'
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
        Name = '解款年份'
        Caption = '解款年份'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|网点号|操作员号|卡类型|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 244
    Top = 135
  end
  inherited MainRequest: TWVRequest
    ID = '商户解款信息查询_nju'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '商户号'
        FieldName = '商户号'
      end
      item
        ParamName = '解款年份'
        FieldName = '解款年份'
      end>
    Left = 280
    Top = 136
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end>
    Left = 312
    Top = 136
  end
  inherited DataSource: TDataSource
    Left = 344
    Top = 136
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
    Left = 280
    Top = 216
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
    Left = 244
    Top = 215
  end
end
