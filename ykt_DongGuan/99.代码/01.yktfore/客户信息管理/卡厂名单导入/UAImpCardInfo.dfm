inherited faqhImpCardInfo: TfaqhImpCardInfo
  Width = 643
  Height = 433
  inherited UIPanel1: TUIPanel
    Top = 370
    Width = 643
    Height = 63
    TabOrder = 2
    object lbl1: TLabel [0]
      Left = 8
      Top = 11
      Width = 60
      Height = 12
      Caption = '文件路径：'
    end
    object lblFile: TLabel [1]
      Left = 78
      Top = 11
      Width = 563
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
      Left = 454
      Width = 82
      Hint = '打开文件'
      Caption = '打开文件'
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 442
      Top = 1000
      Width = 97
      Hint = '断开连接'
      Caption = '关闭Excel'
      Enabled = True
      Visible = False
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
    object btnImport: TBitBtn
      Left = 546
      Top = 3
      Width = 82
      Height = 25
      Hint = '导入数据'
      Anchors = [akTop, akRight]
      Caption = '&I 导入'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
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
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 42
      Width = 643
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
      TabOrder = 4
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 643
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
    object pbStatues: TProgressBar
      Left = 0
      Top = 32
      Width = 643
      Height = 10
      Align = alBottom
      Min = 0
      Max = 100
      TabOrder = 3
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 643
    inherited Image1: TImage
      Width = 643
    end
    inherited LabRecordCount: TLabel
      Visible = False
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 643
    Height = 352
    TabOrder = 0
    inherited Grid: TRzDBGrid
      Width = 643
      Height = 352
      ReadOnly = True
    end
    object mmoList: TMemo
      Left = 0
      Top = 0
      Width = 643
      Height = 352
      Align = alClient
      ScrollBars = ssBoth
      TabOrder = 1
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
        Name = '物理卡号'
        Caption = '物理卡号'
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
        Name = '业务编号'
        Caption = '业务编号'
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
        Name = '资源号'
        Caption = '资源号'
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
        Name = '应用序列号'
        Caption = '应用序列号'
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
        Name = 'UCID'
        Caption = 'UCID'
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
        Name = '激活码'
        Caption = '激活码'
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
    ID = '卡厂数据导入'
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
        ParamName = '物理卡号'
        FieldName = '物理卡号'
      end
      item
        ParamName = '业务编号'
        FieldName = '业务编号'
      end
      item
        ParamName = '资源号'
        FieldName = '资源号'
      end
      item
        ParamName = '应用序列号'
        FieldName = '应用序列号'
      end
      item
        ParamName = 'UCID'
        FieldName = 'UCID'
      end
      item
        ParamName = '激活码'
        FieldName = '激活码'
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
    Left = 240
    Top = 192
  end
  object dlgOpen: TOpenDialog
    Filter = '文本文件(*.txt)|*.txt'
    Title = '卡厂数据文件导入'
    Left = 280
    Top = 192
  end
  object dlgSave1: TSaveDialog
    Filter = '文本文件(*.txt)|*.txt'
    Title = '卡厂数据导入失败记录'
    Left = 320
    Top = 194
  end
end
