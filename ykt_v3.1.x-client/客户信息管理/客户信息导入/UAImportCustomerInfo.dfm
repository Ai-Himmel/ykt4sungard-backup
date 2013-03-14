inherited faqhImportCustomerInfo: TfaqhImportCustomerInfo
  Width = 712
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 402
    Width = 712
    Height = 87
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
      Left = 331
      Top = 27
      Width = 82
      TabOrder = 1
    end
    inherited btnPrint: TBitBtn
      Left = 511
      Top = 27
      Width = 97
      Hint = '断开连接'
      Caption = '关闭Excel'
      Enabled = True
      TabOrder = 3
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
      Left = 615
      Top = 27
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
      TabOrder = 4
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
    object btnOpen: TBitBtn
      Left = 228
      Top = 27
      Width = 97
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
    object edtTable: TWVEdit
      Left = 76
      Top = 31
      Width = 109
      Height = 20
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 5
      Text = 'sheet1'
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 66
      Width = 712
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
      TabOrder = 7
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 712
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
      Top = 56
      Width = 712
      Height = 10
      Align = alBottom
      Min = 0
      Max = 100
      TabOrder = 6
    end
    object btnCheck: TBitBtn
      Left = 420
      Top = 27
      Width = 85
      Height = 25
      Hint = '查询/刷新数据'
      Anchors = [akTop, akRight]
      Caption = '检测(C)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnCheckClick
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000
        0000CECECE00000000000000000000000000FFEFCE00FFCE9400FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF0000000000CECECE0000000000FFEFCE00FFCE9400CE940000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
        00000000000000000000FFEFCE00FFCE9400CE94000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF0000000000CECECE0000000000000000000000
        000000000000FFEFCE00FFEFCE00CE9400000000000000000000000000000000
        00000000000000000000000000000000000000000000FFEFCE00FFEFCE00FFEF
        CE00FFEFCE00FFEFCE00CE9400000000000000000000000000000000000063CE
        CE0063CECE0063CECE0063CECE0000000000FFEFCE00FF94000000000000FFCE
        9400FFEFCE00FFEFCE0000000000CECECE0000000000FFFFFF000000000063CE
        CE00CEFFFF0094FFFF0094FFFF0000000000FF9400000000000094FFFF000000
        0000FFCE9400FFEFCE0000000000CECECE0000000000FFFFFF000000000063CE
        CE00CEFFFF0094FFFF0094CEFF0094FFFF000000000094FFFF0094CEFF0063CE
        CE0000000000FFCE940000000000CECECE0000000000FFFFFF000000000063CE
        CE00CEFFFF0094FFFF0094FFFF0094FFFF0094FFFF0094CEFF0094FFFF000000
        0000FFEFCE00FF94000000000000CECECE0000000000FFFFFF000000000063CE
        CE00CEFFFF0094FFFF0094FFFF0094FFFF0094CEFF0094FFFF0000000000FFEF
        CE00FF9400000000000000000000CECECE0000000000FFFFFF000000000063CE
        CE00CEFFFF00CEFFFF00CEFFFF00CEFFFF00CEFFFF00CEFFFF00CEFFFF000000
        000000000000FFFFFF0000000000CECECE0000000000FFFFFF000000000063CE
        CE0063CECE0063CECE0063CECE00000000000000000000000000000000000000
        000000000000FFFFFF0000000000CECECE0000000000FFFFFF0000000000CEFF
        FF00CEFFFF00CEFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF0000000000CECECE0000000000FFFFFF00FFFFFF000000
        00000000000000000000FFFFFF00000000000000000000000000000000000000
        0000000000000000000000000000CECECE0000000000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF0000000000CECECE00CECECE00CECECE00CECE
        CE00CECECE00CECECE00BDBDBD0000000000FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
        0000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00}
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 712
    inherited Image1: TImage
      Width = 712
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 712
    Height = 27
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 54
      Top = 9
      Width = 36
      Height = 12
      Caption = '学工号'
    end
    object Label2: TLabel
      Left = 242
      Top = 9
      Width = 48
      Height = 12
      Caption = '证件号码'
    end
    object Label3: TLabel
      Left = 466
      Top = 9
      Width = 24
      Height = 12
      Caption = '姓名'
    end
    object edtNo: TWVEdit
      Left = 100
      Top = 5
      Width = 100
      Height = 20
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 8
    end
    object edtCardNo: TWVEdit
      Left = 300
      Top = 5
      Width = 100
      Height = 20
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 9
    end
    object edtName: TWVEdit
      Left = 500
      Top = 5
      Width = 100
      Height = 20
      Color = clBtnHighlight
      ReadOnly = False
      TabOrder = 10
    end
    object cbbFeeType: TWVComboBox
      Left = 672
      Top = 1
      Width = 88
      Height = 18
      Style = csOwnerDrawFixed
      Color = clWhite
      ItemHeight = 12
      TabOrder = 6
      Visible = False
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '-43'
    end
    object cbbCustType: TWVComboBox
      Left = 664
      Top = 1
      Width = 97
      Height = 18
      Style = csOwnerDrawFixed
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      Visible = False
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '-34'
    end
    object cbbArea: TWVComboBox
      Left = 672
      Top = 1
      Width = 89
      Height = 18
      Style = csOwnerDrawFixed
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 7
      Visible = False
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '-27'
    end
    object cbbDept: TWVComboBox
      Left = 664
      Top = 1
      Width = 97
      Height = 18
      Style = csOwnerDrawFixed
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 4
      Visible = False
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '-22'
    end
    object cbbSpec: TWVComboBox
      Left = 672
      Top = 1
      Width = 89
      Height = 18
      Style = csOwnerDrawFixed
      Color = clWhite
      ItemHeight = 12
      TabOrder = 5
      Visible = False
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '-23'
    end
    object cbbNation: TWVComboBox
      Left = 664
      Top = -1
      Width = 97
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 0
      Visible = False
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '89'
    end
    object cbbPeople: TWVComboBox
      Left = 664
      Top = -1
      Width = 97
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 1
      Visible = False
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '2001'
    end
    object cbbCertType: TWVComboBox
      Left = 664
      Top = -1
      Width = 97
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      Visible = False
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '87'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 45
    Width = 712
    Height = 357
    TabOrder = 3
    inherited Grid: TRzDBGrid
      Width = 712
      Height = 357
      ReadOnly = True
    end
  end
  object RzDBGrid1: TRzDBGrid [4]
    Left = 0
    Top = 45
    Width = 712
    Height = 357
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
        Name = '批次号'
        Caption = '批次号'
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
        Name = '序号'
        Caption = '序号'
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
        Name = '是否传送完毕'
        Caption = '是否传送完毕'
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
      end
      item
        Name = '学工号'
        Caption = '学工号'
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
        Name = '客户类别'
        Caption = '客户类别'
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
        Name = '收费类别'
        Caption = '收费类别'
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
        Name = '姓名'
        Caption = '姓名'
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
        Name = '校区'
        Caption = '校区'
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
        Name = '所属部门'
        Caption = '所属部门'
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
        Name = '专业'
        Caption = '专业'
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
        Name = '班级'
        Caption = '班级'
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
        Name = '证件类型'
        Caption = '证件类型'
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
        Name = '证件号码'
        Caption = '证件号码'
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
        Name = '性别'
        Caption = '性别'
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
        Name = '国籍'
        Caption = '国籍'
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
        Name = '民族'
        Caption = '民族'
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
        Name = '电子邮箱'
        Caption = '电子邮箱'
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
        Name = '电话'
        Caption = '电话'
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
        Name = '手机'
        Caption = '手机'
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
        Name = '地址'
        Caption = '地址'
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
        Name = '邮编'
        Caption = '邮编'
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
        Name = '入校日期'
        Caption = '入校日期'
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
        Name = '预计离校日期'
        Caption = '预计离校日期'
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
    ID = '客户信息导入'
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
        ParamName = '批次号'
        FieldName = '批次号'
        Direction = bdBiDirection
      end
      item
        ParamName = '序号'
        FieldName = '序号'
      end
      item
        ParamName = '是否传送完毕'
        FieldName = '是否传送完毕'
      end
      item
        ParamName = '操作标志'
        FieldName = '操作标志'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '客户类别'
        FieldName = '客户类别'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '姓名'
        FieldName = '姓名'
      end
      item
        ParamName = '校区'
        FieldName = '校区'
      end
      item
        ParamName = '所属部门'
        FieldName = '所属部门'
      end
      item
        ParamName = '专业'
        FieldName = '专业'
      end
      item
        ParamName = '班级'
        FieldName = '班级'
      end
      item
        ParamName = '证件类型'
        FieldName = '证件类型'
      end
      item
        ParamName = '证件号码'
        FieldName = '证件号码'
      end
      item
        ParamName = '性别'
        FieldName = '性别'
      end
      item
        ParamName = '民族'
        FieldName = '民族'
      end
      item
        ParamName = '国籍'
        FieldName = '国籍'
      end
      item
        ParamName = '电子邮箱'
        FieldName = '电子邮箱'
      end
      item
        ParamName = '电话'
        FieldName = '电话'
      end
      item
        ParamName = '手机'
        FieldName = '手机'
      end
      item
        ParamName = '地址'
        FieldName = '地址'
      end
      item
        ParamName = '邮编'
        FieldName = '邮编'
      end
      item
        ParamName = '入校日期'
        FieldName = '入校日期'
      end
      item
        ParamName = '预计离校日期'
        FieldName = '预计离校日期'
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
end
