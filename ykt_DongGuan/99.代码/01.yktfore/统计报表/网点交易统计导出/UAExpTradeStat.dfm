inherited faqhExpTradeStat: TfaqhExpTradeStat
  Width = 754
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 447
    Width = 754
    Height = 42
    object Label2: TLabel [0]
      Left = 13
      Top = 9
      Width = 48
      Height = 12
      AutoSize = False
      Caption = '保存目录'
    end
    inherited btnQuery: TBitBtn
      Left = 577
    end
    inherited btnPrint: TBitBtn
      Left = 664
      Hint = '导出统计列表'
      Caption = '导出Excel'
      Enabled = True
      Glyph.Data = {00000000}
    end
    object edtFilePath: TEdit
      Left = 64
      Top = 4
      Width = 297
      Height = 20
      TabOrder = 2
      Text = 'C:\网点交易统计'
    end
    object pbStatues: TProgressBar
      Left = 0
      Top = 32
      Width = 754
      Height = 10
      Align = alBottom
      Min = 0
      Max = 100
      TabOrder = 3
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 754
    inherited Image1: TImage
      Width = 754
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 754
    Height = 31
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left = 302
      Top = 9
      Width = 36
      Height = 12
      Caption = '网点号'
    end
    object lbl1: TLabel
      Left = 506
      Top = 8
      Width = 48
      Height = 12
      Caption = '交易类型'
    end
    object WVLabel1: TWVLabel
      Left = 10
      Top = 8
      Width = 48
      Height = 12
      Caption = '开始日期'
    end
    object WVLabel2: TWVLabel
      Left = 152
      Top = 8
      Width = 48
      Height = 12
      Caption = '结束日期'
    end
    object cbbNetInfo: TWVComboBox
      Left = 339
      Top = 5
      Width = 155
      Height = 18
      Style = csOwnerDrawFixed
      Color = clWhite
      DropDownCount = 20
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '网点号'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-2'
    end
    object cbb1: TWVComboBox
      Left = 556
      Top = 4
      Width = 117
      Height = 20
      Style = csDropDownList
      Color = clWhite
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ItemHeight = 12
      ParentFont = False
      TabOrder = 1
      WorkView = WorkView
      FieldName = '交易类型'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-7'
    end
    object edtBeginDate: TWVEdit
      Left = 64
      Top = 4
      Width = 81
      Height = 20
      Color = clWhite
      ImeName = '中文 (简体) - 微软拼音'
      ReadOnly = False
      TabOrder = 2
      Text = '<开始日期>'
      WorkView = WorkView
      FieldName = '开始日期'
    end
    object edtEndDate: TWVEdit
      Left = 208
      Top = 4
      Width = 89
      Height = 20
      Color = clWhite
      ImeName = '中文 (简体) - 微软拼音'
      ReadOnly = False
      TabOrder = 3
      Text = '<结束日期>'
      WorkView = WorkView
      FieldName = '结束日期'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 49
    Width = 754
    Height = 398
    inherited Grid: TRzDBGrid
      Width = 754
      Height = 398
      Columns = <
        item
          Expanded = False
          FieldName = 'snote2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '批次号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户号'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '卡号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '应用序列号'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '卡有效期'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sroom_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '发卡部门'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '卡类型'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '姓名'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sroom_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '证件类型'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spager'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '证件号码'
          Width = 100
          Visible = True
        end>
    end
    object lvData: TRzListView
      Left = 0
      Top = 0
      Width = 754
      Height = 398
      Align = alClient
      Columns = <
        item
          Caption = '统计日期'
          Width = 80
        end
        item
          Caption = '所属区域'
          Width = 80
        end
        item
          Caption = '渠道编码'
          Width = 80
        end
        item
          Caption = '网点号'
          Width = 70
        end
        item
          Alignment = taCenter
          Caption = '网点名称'
          Width = 200
        end
        item
          Alignment = taCenter
          Caption = '交易类型'
          Width = 100
        end
        item
          Alignment = taCenter
          Caption = '交易次数'
          Width = 90
        end
        item
          Alignment = taCenter
          Caption = '交易金额'
          Width = 33
        end>
      GridLines = True
      TabOrder = 1
      ViewStyle = vsReport
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
        Name = '开始日期'
        Caption = '开始日期'
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
        Name = '结束日期'
        Caption = '结束日期'
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
        Name = '网点号'
        Caption = '网点号'
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
        Name = '交易类型'
        Caption = '交易类型'
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
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|批次号|'
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '网点交易统计'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
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
        ParamName = '网点号'
        FieldName = '网点号'
      end
      item
        ParamName = '交易类型'
        FieldName = '交易类型'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
    Bindings = <
      item
        FieldName = 'sroom_no2'
        DataPresentType = 'idobjects'
        DataPresentParam = '210'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'idobjects'
        DataPresentParam = '-5'
      end
      item
        FieldName = 'sroom_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '201'
      end>
    Left = 168
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 200
    Top = 256
  end
end
