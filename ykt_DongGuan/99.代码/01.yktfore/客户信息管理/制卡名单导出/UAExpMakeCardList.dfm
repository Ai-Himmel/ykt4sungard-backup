inherited faqhExpMakeCardList: TfaqhExpMakeCardList
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 447
    Width = 700
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
      Left = 523
    end
    inherited btnPrint: TBitBtn
      Left = 610
      Hint = '导出制卡名单及照片'
      Caption = '导出名单'
      Glyph.Data = {00000000}
    end
    object edtFilePath: TEdit
      Left = 64
      Top = 4
      Width = 297
      Height = 20
      TabOrder = 2
      Text = 'D:\制卡名单'
    end
    object pbStatues: TProgressBar
      Left = 0
      Top = 32
      Width = 700
      Height = 10
      Align = alBottom
      Min = 0
      Max = 100
      TabOrder = 3
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 35
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left = 22
      Top = 9
      Width = 36
      Height = 12
      Caption = '批次号'
    end
    object Label4: TLabel
      Left = 250
      Top = 10
      Width = 48
      Height = 12
      Caption = '发卡部门'
    end
    object Label10: TLabel
      Left = 456
      Top = 10
      Width = 36
      Height = 12
      Caption = '卡类别'
    end
    object WVEdit1: TWVEdit
      Left = 68
      Top = 5
      Width = 157
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 0
      Text = '<批次号>'
      WorkView = WorkView
      FieldName = '批次号'
    end
    object cbbDept: TWVComboBox
      Left = 305
      Top = 6
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 20
      ImeName = '中文 (简体) - 微软拼音'
      ItemHeight = 12
      TabOrder = 1
      WorkView = WorkView
      FieldName = '发卡部门'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*210'
    end
    object cbbIDType: TWVComboBox
      Left = 497
      Top = 6
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ImeName = '中文 (简体) - 微软拼音'
      ItemHeight = 12
      TabOrder = 2
      WorkView = WorkView
      FieldName = '卡类别'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-1'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 53
    Width = 700
    Height = 394
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 394
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
      Width = 700
      Height = 394
      Align = alClient
      Columns = <
        item
          Caption = '批次号'
          Width = 120
        end
        item
          Alignment = taCenter
          Caption = '客户号'
          Width = 90
        end
        item
          Alignment = taCenter
          Caption = '卡号'
          Width = 100
        end
        item
          Alignment = taCenter
          Caption = '应用序列号'
          Width = 120
        end
        item
          Alignment = taCenter
          Caption = '卡片管理号'
          Width = 120
        end
        item
          Alignment = taCenter
          Caption = '卡有效期'
          Width = 80
        end
        item
          Caption = '发卡部门'
          Width = 100
        end
        item
          Alignment = taCenter
          Caption = '卡类别'
          Width = 80
        end
        item
          Alignment = taCenter
          Caption = '姓名'
          Width = 100
        end
        item
          Alignment = taCenter
          Caption = '证件类型'
          Width = 80
        end
        item
          Alignment = taCenter
          Caption = '证件号码'
          Width = 120
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
        Name = '批次号'
        Caption = '批次号'
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
        Name = '发卡部门'
        Caption = '发卡部门'
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
        Name = '卡类别'
        Caption = '卡类别'
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
        MonitorValueChangedFields = '|批次号|'
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '制卡名单导出'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '批次号'
        FieldName = '批次号'
      end
      item
        ParamName = '发卡部门'
        FieldName = '发卡部门'
      end
      item
        ParamName = '卡类别'
        FieldName = '卡类别'
        DefaultValue = 0
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
