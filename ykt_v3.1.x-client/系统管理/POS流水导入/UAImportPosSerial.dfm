inherited faqhPosSerialImport: TfaqhPosSerialImport
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 408
    Width = 700
    Height = 81
    object Label5: TLabel [0]
      Left = 14
      Top = 35
      Width = 60
      Height = 12
      Caption = '�����ƣ�'
    end
    object lbl1: TLabel [1]
      Left = 8
      Top = 11
      Width = 66
      Height = 12
      Caption = 'Excel·����'
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
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    inherited btnQuery: TBitBtn
      Left = 403
      Top = 27
      Width = 85
    end
    inherited btnPrint: TBitBtn
      Left = 496
      Top = 27
      Width = 100
      Hint = '�Ͽ�����'
      Caption = '�ر�Excel'
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
    object btnImport: TBitBtn
      Left = 603
      Top = 27
      Width = 85
      Height = 25
      Hint = '��������'
      Anchors = [akTop, akRight]
      Caption = '�� ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
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
    object btnOpen: TBitBtn
      Left = 296
      Top = 27
      Width = 100
      Height = 25
      Hint = '��Excel�ĵ�'
      Anchors = [akTop, akRight]
      Caption = '��Excel'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
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
      Font.Name = '����'
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
        Font.Name = '����'
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
    Height = 27
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
  end
  inherited UIPanel2: TUIPanel
    Top = 45
    Width = 700
    Height = 363
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 363
      ReadOnly = True
    end
  end
  object RzDBGrid1: TRzDBGrid [4]
    Left = 0
    Top = 45
    Width = 700
    Height = 363
    Align = alClient
    DataSource = DataSource
    TabOrder = 4
    TitleFont.Charset = GB2312_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -12
    TitleFont.Name = '����'
    TitleFont.Style = []
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '������'
        Caption = '������'
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
        Name = '������Ϣ'
        Caption = '������Ϣ'
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
        Name = '���κ�'
        Caption = '���κ�'
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
        Name = '���'
        Caption = '���'
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
        Name = '�Ƿ������'
        Caption = '�Ƿ������'
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
        Name = '��������'
        Caption = '��������'
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
        Name = '����ʱ��'
        Caption = '����ʱ��'
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
        Name = '�豸������'
        Caption = '�豸������'
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
        Name = '�豸��ˮ��'
        Caption = '�豸��ˮ��'
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
        Name = '�̻�����'
        Caption = '�̻�����'
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
        Name = '������'
        Caption = '������'
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
        Name = '����'
        Caption = '����'
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
        Name = 'Ǯ����'
        Caption = 'Ǯ����'
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
        Name = '�����״���'
        Caption = '�����״���'
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
        Name = '������ǰ���'
        Caption = '������ǰ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�����׺����'
        Caption = '�����׺����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '������'
        Caption = '������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�����'
        Caption = '�����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '���ױ��'
        Caption = '���ױ��'
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
        MonitorValueChangedFields = '|ѧ����|���֤��|����|'
      end>
    Left = 124
    Top = 191
  end
  inherited MainRequest: TWVRequest
    ID = 'Pos��ˮ����'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
        Direction = bdBiDirection
      end
      item
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = '�Ƿ������'
        FieldName = '�Ƿ������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
      end
      item
        ParamName = '�豸������'
        FieldName = '�豸������'
      end
      item
        ParamName = '�豸��ˮ��'
        FieldName = '�豸��ˮ��'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'Ǯ����'
      end
      item
        ParamName = '�����״���'
        FieldName = '�����״���'
      end
      item
        ParamName = '������ǰ���'
        FieldName = '������ǰ���'
      end
      item
        ParamName = '�����׺����'
        FieldName = '�����׺����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '���ױ��'
        FieldName = '���ױ��'
      end>
    Left = 168
    Top = 192
  end
  inherited WVDBBinder: TWVDBBinder
    DataSource = nil
    FieldName = '��ѯ�����'
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
      'ttings\Administrator\����\�½� Microsoft Office Access Ӧ�ó���.' +
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
