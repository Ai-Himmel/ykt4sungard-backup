inherited faqhdownSublidyList: TfaqhdownSublidyList
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 414
    Width = 700
    Height = 75
    TabOrder = 4
    object lbl1: TLabel [0]
      Left = 14
      Top = 11
      Width = 66
      Height = 12
      Caption = 'Excel路径：'
    end
    object lblFile: TLabel [1]
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
    object Label3: TLabel [2]
      Left = 14
      Top = 35
      Width = 48
      Height = 12
      Caption = '表单名称'
    end
    object RzStatusPane1: TRzStatusPane [3]
      Left = 0
      Top = 54
      Width = 700
      Height = 21
      FrameStyle = fsStatus
      Align = alBottom
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
    end
    inherited btnQuery: TBitBtn
      Left = 408
      Top = 27
      TabOrder = 1
    end
    inherited btnPrint: TBitBtn
      Left = 499
      Top = 27
      Width = 100
      Caption = '关闭Excel'
      Enabled = True
      TabOrder = 2
      Glyph.Data = {
        36030000424D3603000000000000360000002800000010000000100000000100
        18000000000000030000120B0000120B00000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFB0A090604830604830604830D7D1CBFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFB0A090FFFFFFB0
        A0909078707058406050409C8C7AC7BDB2DBD5CFB7A79F9B8C7CFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFB0A090FFFFFFFFFFFFFFF8FFF0E0E0B098907060506050
        40604830807060776859FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFB0A090FFFFFFFF
        FFFFFFFFFFFFF8F0F0F0F0E0D8D0D0C0B0C0B0A0B0A8A068533B207840107030
        107030106830106030106030105830105030205030204830FFF0F0F0E8E0F0E0
        E0F0D8D0C0A890604830208040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFF105030FFF8F0F0F0F0F0E8E0F0D8D0B0A090604830308840FFFFFF
        FFFFFFFFFFFFFFFFFF80A880207040206030608060105030FFFFFFFFF8F0F0E8
        E0F0E0E0B0A09060483040905090C09020784020704020603090C09040904020
        6840A0B0A0105830FFFFFFFFF8FFF0F0F0F0E8E0B0A090604830409850FFFFFF
        90C09050A05090C89050A060207040709870E0E8E0106030FFFFFFFFFFFFFFF8
        F0F0F0F0B0A09060483050A060FFFFFFD0E0D090C8A050A060208040206830C0
        D0C0FFFFFF106030FFFFFFFFFFFFFFFFFFFFF8F0B0A09060483060A860E0F0E0
        90C89060B07030884070A87050A060408840D0E0D0106830FFFFFFFFFFFFFFFF
        FFFFFFFFB0A09060483060B07090C09060A860409850FFFFFFD0D8D050986050
        9860A0B0A0107030FFFFFFFFFFFFFFFFFFB0A090B0A09060483060B070FFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF107030FFFFFFFFFFFFB0A0
        9060483060483060483060B07060B07060A86050A06050986040905030905030
        8840208040207840FFFFFFFFFFFFC0A890D0C8C0604830E4D2C9FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFE0C0B0FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC0A8
        A0604830E4D2C9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE0C0B0E0C0B0E0
        C0B0E0C0B0E0C0B0D0C0B0D0B8B0D0B0A0E4D2C9FFFFFFFFFFFF}
    end
    object edtTable: TWVEdit
      Left = 76
      Top = 31
      Width = 109
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 4
      Text = 'sheet1'
    end
    object btnOpen: TBitBtn
      Left = 296
      Top = 27
      Width = 100
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
      Glyph.Data = {
        36030000424D3603000000000000360000002800000010000000100000000100
        18000000000000030000120B0000120B00000000000000000000407050407050
        4070503070403070403070403068403068403068402060302060302060302050
        3020503020503020503040705070A88060A07060A07060987060987050987050
        987050906050906050906040905040905030905030905020503040785070A880
        F0F0F0F0F0F0E0F0E0E0F0E0E0F0E0E0F0E0E0E8E0E0E8E0E0E8E0E0E8E0E0E8
        E0E0E8E030905020503040785070A880F0F8F0F0F0F0F0F0F0E0F0E0E0F0E0E0
        F0E0E0F0E0E0E8E0E0E8E0E0E8E0E0E8E0E0E8E040905020503040806070B080
        F0F8F0F0F8F0F0F0F0F0F0F0F0F0F0E0F0E080A8903050303050303050303050
        30E0E8E040905020503050886080B890F0F8F050A86030503030503030503030
        503020782070B870509060509850206030E0E8E050906020603050906080C090
        F0F8F0F0F8F050A86060B07050A86020782080C08050906050985020603080A8
        90E0E8E050906020603050987090B890F0F8F0F0F8F0F0F8F050A86030883080
        C090509060509850206030609860609860E0F0E050906020603060987090C8A0
        FFF8FFF0F8F0F0F8F030883090C8A060A86050A860307040006800E0F0E0E0F0
        E0E0F0E050987030684060A07090C8A0FFFFFFFFF8FF409040A0D0A070B87060
        A86040885050A860308830006800E0F0E0E0F0E050987030684070A880A0D0A0
        FFFFFF509850B0D8B070B88070B88050906050806060B07050A8603088300068
        00E0F0E060987030704070A880A0D0A0FFFFFF60B07060B07060B070509860F0
        F8F0F0F8F0508060508060508060508060F0F0F060987030704070B080B0D8B0
        FFFFFFFFFFFFFFFFFFFFFFFFFFF8FFFFF8FFF0F8F0F0F8F0F0F8F0F0F8F0F0F8
        F0F0F0F060A07040705080B890B0D8B0FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        F8FFFFF8FFF0F8F0F0F8F0F0F8F0F0F8F0F0F8F060A07040705080B890B0D8B0
        B0D8B0A0D0A0A0D0A090C8A090C8A090C8A090B89080C09080B89070B08070A8
        8070A88070A88040705080C09080B89070B08070A88070A88060A07060987050
        9870509060508860508860408060407850407850407050407050}
    end
    object btnImport: TBitBtn
      Left = 611
      Top = 27
      Width = 79
      Height = 25
      Hint = '导入数据'
      Anchors = [akTop, akRight]
      Caption = '导入(&I)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnImportClick
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF000000FF000000FF00FFFFFF00FFFFFF00FFFFFF007B0000007B00
        00007B0000007B0000007B0000007B0000007B0000007B0000007B000000FFFF
        FF000000FF000000FF000000FF000000FF000000FF00FFFFFF007B000000FFFF
        FF00FFFFFF00BDBDBD00FFFFFF00FFFFFF00BDBDBD00FFFFFF00FFFFFF000000
        FF000000FF000000FF000000FF000000FF000000FF000000FF007B000000FFFF
        FF00FFFFFF00BDBDBD00FFFFFF00FFFFFF00BDBDBD00FFFFFF00FFFFFF00BDBD
        BD000000FF000000FF000000FF000000FF000000FF000000FF007B000000BDBD
        BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD007B00
        0000FFFFFF000000FF000000FF00FFFFFF000000FF000000FF007B000000FFFF
        FF00FFFFFF00BDBDBD00FFFFFF00FFFFFF00BDBDBD00FFFFFF00FFFFFF007B00
        0000FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF000000FF007B000000FFFF
        FF00FFFFFF00BDBDBD00FFFFFF00FFFFFF00BDBDBD00FFFFFF00FFFFFF007B00
        00007B0000007B000000FFFFFF00FFFFFF000000FF000000FF007B0000007B00
        00007B0000007B0000007B0000007B0000007B0000007B0000007B0000007B00
        0000FFFFFF00FFFFFF007B0000000000FF000000FF000000FF007B0000007B00
        00007B0000007B0000007B0000007B000000FFFF00007B000000FFFF00007B00
        0000FFFFFF00FFFFFF007B0000000000FF000000FF000000FF007B0000007B00
        00007B0000007B0000007B0000007B0000007B0000007B0000007B0000007B00
        0000BDBDBD00BDBDBD007B0000000000FF000000FF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF007B000000FFFFFF00FFFFFF00BDBDBD00FFFFFF00FFFFFF00BDBD
        BD00FFFFFF00FFFFFF007B000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF007B000000FFFFFF00FFFFFF00BDBDBD00FFFFFF00FFFFFF00BDBD
        BD00FFFFFF00FFFFFF007B000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF007B0000007B0000007B0000007B0000007B0000007B0000007B00
        00007B0000007B0000007B000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF007B0000007B0000007B0000007B0000007B0000007B000000FFFF
        00007B000000FFFF00007B000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF007B0000007B0000007B0000007B0000007B0000007B0000007B00
        00007B0000007B0000007B000000FFFFFF00FFFFFF00FFFFFF00}
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    TabOrder = 0
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 10
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
  end
  inherited UIPanel2: TUIPanel
    Top = 28
    Width = 700
    Height = 386
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 386
    end
  end
  object grid1: TRzDBGrid [4]
    Left = 0
    Top = 28
    Width = 700
    Height = 386
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
        Name = '学工号'
        Caption = '学工号'
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
        Name = '补助批次号'
        Caption = '补助批次号'
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
        Name = '导入批次号'
        Caption = '导入批次号'
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
        Name = '顺序号'
        Caption = '顺序号'
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
        Name = '补助金额'
        Caption = '补助金额'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
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
        Name = '截止日期'
        Caption = '截止日期'
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
        Name = '操作员'
        Caption = '操作员'
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
        Name = '导入标志'
        Caption = '导入标志'
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
        Name = '客户号'
        Caption = '客户号'
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
        MonitorValueChangedFields = 
          '|学工号|补助批次号|导入批次号|顺序号|补助金额|截止日期|操作员|导' +
          '入标志|'
      end>
    Left = 124
    Top = 247
  end
  inherited MainRequest: TWVRequest
    ID = '补助信息导入'
    Bindings = <
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '补助批次号'
        FieldName = '补助批次号'
      end
      item
        ParamName = '导入批次号'
        FieldName = '导入批次号'
      end
      item
        ParamName = '顺序号'
        FieldName = '顺序号'
      end
      item
        ParamName = '补助金额'
        FieldName = '补助金额'
      end
      item
        ParamName = '截止日期'
        FieldName = '截止日期'
      end
      item
        ParamName = '操作员'
        FieldName = '操作员'
      end
      item
        ParamName = '导入标志'
        FieldName = '导入标志'
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
        ParamName = '导入批次号'
        FieldName = '导入批次号'
        Direction = bdParam2Field
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end>
    Left = 160
    Top = 248
  end
  inherited WVDBBinder: TWVDBBinder
    DataSource = nil
    FieldName = '查询结果集'
    Left = 200
    Top = 248
  end
  inherited DataSource: TDataSource
    DataSet = qrySource
    Left = 208
    Top = 296
  end
  object conSource: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\Documents and Se' +
      'ttings\Administrator\桌面\新建 Microsoft Office Access 应用程序.' +
      'mdb;Persist Security Info=False'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 120
    Top = 296
  end
  object qrySource: TADOQuery
    Connection = conSource
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from sheet1')
    Left = 160
    Top = 296
  end
  object dlgOpen: TOpenDialog
    Left = 248
    Top = 296
  end
  object dlgSave1: TSaveDialog
    Left = 296
    Top = 296
  end
end
