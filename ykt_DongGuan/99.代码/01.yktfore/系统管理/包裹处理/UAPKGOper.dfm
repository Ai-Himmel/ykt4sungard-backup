inherited faqhPKGOper: TfaqhPKGOper
  Width = 1078
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 1078
    TabOrder = 2
    inherited btnQuery: TBitBtn
      Left = 901
      Top = 100
      Enabled = False
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 988
      Top = 100
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 1078
    TabOrder = 0
    inherited Image1: TImage
      Width = 1078
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 561
    Height = 441
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Top = 49
      Width = 561
      Height = 352
      Color = clWhite
      OnCellClick = GridCellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'scust_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ID'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���͵�λ'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����ļ���'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������'
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���д���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ļ�����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstock_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstock_code2'
          PickList.Strings = ()
          Title.Caption = '�������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr1'
          PickList.Strings = ()
          Title.Caption = '��ע'
          Width = 120
          Visible = True
        end>
    end
    object Panel1: TPanel
      Left = 0
      Top = 0
      Width = 561
      Height = 49
      Align = alTop
      BevelOuter = bvNone
      ParentColor = True
      TabOrder = 1
      object Label4: TLabel
        Left = 5
        Top = 29
        Width = 72
        Height = 12
        Caption = '���տ�ʼ����'
      end
      object Label6: TLabel
        Left = 370
        Top = 29
        Width = 48
        Height = 12
        Caption = '����״̬'
      end
      object Label7: TLabel
        Left = 185
        Top = 29
        Width = 72
        Height = 12
        Caption = '���ս�������'
      end
      object edtBDate: TWVEdit
        Left = 79
        Top = 25
        Width = 101
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 2
        Text = '<��ʼ����>'
        WorkView = WorkView
        FieldName = '��ʼ����'
      end
      object WVComboBox3: TWVComboBox
        Left = 422
        Top = 25
        Width = 105
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 0
        WorkView = WorkView
        FieldName = '����״̬'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*235'
      end
      object edtEDate: TWVEdit
        Left = 259
        Top = 25
        Width = 102
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<��������>'
        WorkView = WorkView
        FieldName = '��������'
      end
      object pnl1: TPanel
        Left = 0
        Top = 0
        Width = 561
        Height = 20
        Align = alTop
        Alignment = taLeftJustify
        Caption = ' >>>������Ϣ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
      end
    end
    object pnlPKGbtm: TPanel
      Left = 0
      Top = 401
      Width = 561
      Height = 40
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 2
      object grp1: TGroupBox
        Left = 0
        Top = 0
        Width = 281
        Height = 40
        Align = alLeft
        Caption = '״̬�޸�'
        TabOrder = 0
        object Label1: TLabel
          Left = 6
          Top = 17
          Width = 48
          Height = 12
          Caption = '����״̬'
        end
        object lbl1: TLabel
          Left = 142
          Top = 17
          Width = 24
          Height = 12
          Caption = '��ע'
        end
        object WVComboBox1: TWVComboBox
          Left = 58
          Top = 14
          Width = 79
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 0
          WorkView = WVPKGOper
          FieldName = '����״̬'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*235'
        end
        object edt1: TWVEdit
          Left = 167
          Top = 14
          Width = 106
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
          Text = '<��ע>'
          WorkView = WVPKGOper
          FieldName = '��ע'
        end
      end
      object btnPKGQuery: TBitBtn
        Left = 314
        Top = 8
        Width = 70
        Height = 25
        Hint = '��ѯ/ˢ������'
        Anchors = [akTop, akRight]
        Caption = '������ѯ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = btnPKGQueryClick
      end
      object btnUStatus: TBitBtn
        Left = 394
        Top = 7
        Width = 70
        Height = 25
        Hint = '����״̬�޸�'
        Anchors = [akTop, akRight]
        Caption = '״̬�޸�'
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = btnUStatusClick
      end
      object btnDelPKG: TBitBtn
        Left = 474
        Top = 7
        Width = 70
        Height = 25
        Hint = '����ɾ��'
        Anchors = [akTop, akRight]
        Caption = '����ɾ��'
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = btnDelPKGClick
      end
    end
  end
  object RzSizePanel1: TRzSizePanel [3]
    Left = 561
    Top = 18
    Width = 517
    Height = 441
    Align = alRight
    HotSpotVisible = True
    SizeBarWidth = 7
    TabOrder = 3
    UseGradients = True
    object Panel2: TPanel
      Left = 8
      Top = 0
      Width = 509
      Height = 49
      Align = alTop
      BevelOuter = bvNone
      ParentColor = True
      TabOrder = 0
      object Label3: TLabel
        Left = 2
        Top = 29
        Width = 48
        Height = 12
        Caption = '����״̬'
      end
      object WVComboBox2: TWVComboBox
        Left = 54
        Top = 25
        Width = 105
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 0
        WorkView = WVFileQ
        FieldName = '����״̬'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*235'
      end
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 509
        Height = 20
        Align = alTop
        Alignment = taLeftJustify
        Caption = ' >>>�����ļ���Ϣ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
      end
    end
    object GridFile: TRzDBGrid
      Left = 8
      Top = 49
      Width = 509
      Height = 352
      Align = alClient
      Color = clWhite
      DataSource = DataSource1
      FixedColor = 15458000
      TabOrder = 1
      TitleFont.Charset = GB2312_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -12
      TitleFont.Name = '����'
      TitleFont.Style = []
      OnDrawColumnCell = GridDrawColumnCell
      OnKeyDown = GridKeyDown
      FrameColor = 12164479
      FrameStyle = fsGroove
      FrameVisible = True
      FixedLineColor = 12164479
      LineColor = clBackground
      Columns = <
        item
          Expanded = False
          FieldName = 'scust_no'
          Title.Alignment = taCenter
          Title.Caption = '����ID'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          Title.Alignment = taCenter
          Title.Caption = '�ļ����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          Title.Alignment = taCenter
          Title.Caption = '�ļ���'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          Title.Alignment = taCenter
          Title.Caption = '���'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          Title.Alignment = taCenter
          Title.Caption = '�̻����'
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          Title.Alignment = taCenter
          Title.Caption = '��¼����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          Title.Alignment = taCenter
          Title.Caption = '�ܽ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime1'
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstock_code'
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstock_code2'
          Title.Caption = '�������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr1'
          Title.Caption = '��ע'
          Width = 120
          Visible = True
        end>
    end
    object Panel4: TPanel
      Left = 8
      Top = 401
      Width = 509
      Height = 40
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 2
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 267
        Height = 40
        Align = alLeft
        Caption = '״̬�޸�'
        TabOrder = 0
        object Label8: TLabel
          Left = 6
          Top = 17
          Width = 48
          Height = 12
          Caption = '����״̬'
        end
        object Label2: TLabel
          Left = 134
          Top = 17
          Width = 24
          Height = 12
          Caption = '��ע'
        end
        object WVComboBox4: TWVComboBox
          Left = 58
          Top = 14
          Width = 74
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 0
          WorkView = WVFileOper
          FieldName = '����״̬'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*235'
        end
        object WVEdit1: TWVEdit
          Left = 161
          Top = 14
          Width = 101
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
          Text = '<��ע>'
          WorkView = WVFileOper
          FieldName = '��ע'
        end
      end
      object btnFileU: TBitBtn
        Left = 349
        Top = 7
        Width = 71
        Height = 25
        Hint = '�ļ�״̬�޸�'
        Anchors = [akTop, akRight]
        Caption = '״̬�޸�'
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = btnFileUClick
      end
      object btnFileDel: TBitBtn
        Left = 429
        Top = 7
        Width = 71
        Height = 25
        Hint = '����ɾ��'
        Anchors = [akTop, akRight]
        Caption = '�ļ�ɾ��'
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = btnFileDelClick
      end
      object btnFileQuery: TBitBtn
        Left = 270
        Top = 8
        Width = 71
        Height = 25
        Hint = '��ѯ/ˢ������'
        Anchors = [akTop, akRight]
        Caption = '�ļ���ѯ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = btnFileQueryClick
      end
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
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
        Name = '��������'
        Caption = '��������'
        FieldType = wftUndefined
        DomainName = '����У��'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        MonitorValueChangedFields = '|��������|'
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ʼ����'
        Caption = '��ʼ����'
        FieldType = wftUndefined
        DomainName = '����У��'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        MonitorValueChangedFields = '|��ʼ����|'
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '����״̬'
        Caption = '����״̬'
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
        Name = '������־'
        Caption = '������־'
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
        MonitorValueChangedFields = '|վ���|վ����ˮ��|����Ա|��������|������|��ˮ״̬|'
      end>
    Left = 92
    Top = 215
  end
  inherited MainRequest: TWVRequest
    ID = '������ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ʼ����'
        FieldName = '��ʼ����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '����״̬'
        FieldName = '����״̬'
      end>
    Left = 128
    Top = 216
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lwithdraw_flag'
        DataPresentType = 'idobjects'
        DataPresentParam = '-33'
      end
      item
        FieldName = 'sstock_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '235'
      end
      item
        FieldName = 'sstock_code2'
        DataPresentType = 'idobjects'
        DataPresentParam = '232'
      end>
    Left = 160
    Top = 216
  end
  inherited DataSource: TDataSource
    Left = 192
    Top = 216
  end
  object WVRPKGOper: TWVRequest
    WorkView = WVPKGOper
    ID = '��������'
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
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '����״̬'
        FieldName = '����״̬'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end>
    AfterExec = MainRequestAfterExec
    Left = 128
    Top = 296
  end
  object WVPKGOper: TWorkView
    WorkFields = <
      item
        Name = '������'
        Caption = '������'
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
        Name = '������Ϣ'
        Caption = '������Ϣ'
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
        Name = '�������'
        Caption = '�������'
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
        Name = '����״̬'
        Caption = '����״̬'
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
        Name = '������־'
        Caption = '������־'
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
        Name = '��ע'
        Caption = '��ע'
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
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|վ���|վ����ˮ��|����Ա|��������|������|��ˮ״̬|'
      end>
    Left = 92
    Top = 295
  end
  object WVFileQ: TWorkView
    WorkFields = <
      item
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '����״̬'
        Caption = '����״̬'
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
        Name = '������־'
        Caption = '������־'
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
        Name = '�������'
        Caption = '�������'
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
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|վ���|վ����ˮ��|����Ա|��������|������|��ˮ״̬|'
      end>
    Left = 604
    Top = 207
  end
  object WVRFileQ: TWVRequest
    WorkView = WVFileQ
    ID = '�ļ���ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '����״̬'
        FieldName = '����״̬'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    AfterExec = MainRequestAfterExec
    Left = 640
    Top = 208
  end
  object WVDBBinder1: TWVDBBinder
    DataSource = DataSource1
    WorkView = WVFileQ
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lwithdraw_flag'
        DataPresentType = 'idobjects'
        DataPresentParam = '-33'
      end
      item
        FieldName = 'sstock_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '235'
      end
      item
        FieldName = 'sstock_code2'
        DataPresentType = 'idobjects'
        DataPresentParam = '232'
      end>
    HideUnbindingFields = False
    Left = 672
    Top = 208
  end
  object DataSource1: TDataSource
    OnDataChange = DataSourceDataChange
    Left = 704
    Top = 208
  end
  object WVFileOper: TWorkView
    WorkFields = <
      item
        Name = '������'
        Caption = '������'
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
        Name = '������Ϣ'
        Caption = '������Ϣ'
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
        Name = '�������'
        Caption = '�������'
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
        Name = '����״̬'
        Caption = '����״̬'
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
        Name = '������־'
        Caption = '������־'
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
        Name = '��ע'
        Caption = '��ע'
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
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|վ���|վ����ˮ��|����Ա|��������|������|��ˮ״̬|'
      end>
    Left = 604
    Top = 247
  end
  object WVRFileOper: TWVRequest
    WorkView = WVFileOper
    ID = '�ļ�����'
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
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '����״̬'
        FieldName = '����״̬'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end>
    AfterExec = MainRequestAfterExec
    Left = 640
    Top = 248
  end
end
