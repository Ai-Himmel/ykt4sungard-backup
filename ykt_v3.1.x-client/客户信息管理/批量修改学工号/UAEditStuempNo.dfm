inherited faqhEditStuempNo: TfaqhEditStuempNo
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 408
    Width = 700
    Height = 81
    TabOrder = 4
    object Label5: TLabel [0]
      Left = 14
      Top = 35
      Width = 60
      Height = 12
      Caption = '表单名称：'
    end
    object lbl1: TLabel [1]
      Left = 8
      Top = 11
      Width = 66
      Height = 12
      Caption = 'Excel路径：'
    end
    object lblFile: TLabel [2]
      Left = 78
      Top = 11
      Width = 611
      Height = 12
      AutoSize = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    inherited btnQuery: TBitBtn
      Left = 432
      Top = 27
      TabOrder = 1
    end
    inherited btnPrint: TBitBtn
      Left = 522
      Top = 27
      Hint = '断开连接'
      Caption = '关闭Excel'
      Enabled = True
      TabOrder = 2
      Glyph.Data = {00000000}
    end
    object btnImport: TImageButton
      Left = 611
      Top = 27
      Width = 75
      Height = 25
      Hint = '导入数据'
      Anchors = [akTop, akRight]
      Caption = '批量修改'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnImportClick
    end
    object btnOpen: TImageButton
      Left = 347
      Top = 27
      Width = 75
      Height = 25
      Hint = '打开Excel文档'
      Anchors = [akTop, akRight]
      Caption = '打开Excel'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnOpenClick
    end
    object edtTable: TWVEdit
      Left = 76
      Top = 31
      Width = 109
      Height = 20
      Color = clInfoBk
      ImeName = '中文 (简体) - 拼音加加3.11'
      ReadOnly = False
      TabOrder = 4
      Text = 'sheet1'
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 60
      Width = 700
      Height = 21
      AutoStyle = False
      BorderColor = clWindow
      BorderInner = fsNone
      BorderOuter = fsNone
      BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
      BorderWidth = 0
      Color = 16184303
      FlatColor = 15458000
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 700
        Height = 21
        FrameStyle = fsStatus
        Align = alClient
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -14
        Font.Name = '宋体'
        Font.Style = [fsBold]
        ParentFont = False
      end
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
    Height = 5
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
  end
  inherited UIPanel2: TUIPanel
    Top = 23
    Width = 700
    Height = 385
    TabOrder = 3
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 385
      ReadOnly = True
    end
  end
  object RzDBGrid1: TRzDBGrid [4]
    Left = 0
    Top = 23
    Width = 700
    Height = 385
    Align = alClient
    DataSource = DataSource
    TabOrder = 2
    TitleFont.Charset = GB2312_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -12
    TitleFont.Name = '宋体'
    TitleFont.Style = []
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
        Name = '原学工号'
        Caption = '原学工号'
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
        Name = '新学工号'
        Caption = '新学工号'
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
        Name = '批量标志'
        Caption = '批量标志'
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
        Name = '操作标志'
        Caption = '操作标志'
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
        MonitorValueChangedFields = '|学工号|身份证号|姓名|'
      end>
    Left = 124
    Top = 191
  end
  inherited MainRequest: TWVRequest
    ID = '批量修改学工号'
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
        ParamName = '原学工号'
        FieldName = '原学工号'
      end
      item
        ParamName = '新学工号'
        FieldName = '新学工号'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '批量标志'
        FieldName = '批量标志'
      end>
    Left = 168
    Top = 192
  end
  inherited WVDBBinder: TWVDBBinder
    DataSource = nil
    FieldName = '查询结果集'
    Left = 200
    Top = 192
  end
  inherited DataSource: TDataSource
    DataSet = qrySource
    Left = 216
    Top = 232
  end
  object conSource: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\Documents and Se' +
      'ttings\Administrator\桌面\新建 Microsoft Office Access 应用程序.' +
      'mdb;Persist Security Info=False'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 128
    Top = 232
  end
  object qrySource: TADOQuery
    Connection = conSource
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from sheet1')
    Left = 168
    Top = 232
  end
  object dlgOpen: TOpenDialog
    Left = 256
    Top = 232
  end
  object dlgSave1: TSaveDialog
    Filter = '文本文件|*.txt'
    Title = '批量修改学工号失败列表'
    Left = 240
    Top = 192
  end
end
