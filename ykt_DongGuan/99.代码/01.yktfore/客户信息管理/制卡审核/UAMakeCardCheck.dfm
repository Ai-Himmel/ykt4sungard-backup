inherited faqhMakeCardCheck: TfaqhMakeCardCheck
  Width = 800
  Height = 499
  inherited UIPanel1: TUIPanel
    Top = 411
    Width = 800
    Height = 88
    object Label1: TLabel [0]
      Left = 64
      Top = 10
      Width = 48
      Height = 12
      Caption = 'Ӧ������'
    end
    object Label2: TLabel [1]
      Left = 64
      Top = 34
      Width = 48
      Height = 12
      Caption = '���ұ���'
    end
    object Label3: TLabel [2]
      Left = 224
      Top = 10
      Width = 48
      Height = 12
      Caption = '���б���'
    end
    object Label5: TLabel [3]
      Left = 224
      Top = 34
      Width = 48
      Height = 12
      Caption = '�ƿ�����'
    end
    inherited btnQuery: TBitBtn
      Left = 535
      Top = 24
    end
    inherited btnPrint: TBitBtn
      Left = 710
      Top = 24
    end
    object btnCheck: TBitBtn
      Left = 623
      Top = 24
      Width = 79
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '���ͨ��'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnCheckClick
    end
    object chkSelect: TCheckBox
      Left = 8
      Top = 8
      Width = 57
      Height = 17
      Caption = 'ȫѡ'
      TabOrder = 3
      OnClick = chkSelectClick
    end
    object btnClear: TBitBtn
      Left = 447
      Top = 24
      Width = 79
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '����б�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btnClearClick
    end
    object stat1: TStatusBar
      Left = 0
      Top = 65
      Width = 800
      Height = 23
      Panels = <
        item
          Width = 1000
        end>
      SimplePanel = False
    end
    object pbStatues: TProgressBar
      Left = 0
      Top = 55
      Width = 800
      Height = 10
      Align = alBottom
      Min = 0
      Max = 100
      TabOrder = 6
    end
    object cbbApp: TWVComboBox
      Left = 116
      Top = 6
      Width = 99
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView
      FieldName = 'Ӧ������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*236'
    end
    object cbbFact: TWVComboBox
      Left = 116
      Top = 30
      Width = 99
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 8
      WorkView = WorkView
      FieldName = '����'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-80'
    end
    object cbbCity: TWVComboBox
      Left = 276
      Top = 6
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 9
      WorkView = WorkView
      FieldName = '���б���'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*238'
    end
    object WVComboBox1: TWVComboBox
      Left = 276
      Top = 30
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 10
      WorkView = WorkView
      FieldName = '����'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*242'
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 800
    inherited Image1: TImage
      Width = 800
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 800
    Height = 40
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label4: TLabel
      Left = 18
      Top = 18
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label9: TLabel
      Left = 396
      Top = 18
      Width = 72
      Height = 12
      Caption = '���뿪ʼ����'
    end
    object Label10: TLabel
      Left = 224
      Top = 18
      Width = 36
      Height = 12
      Caption = '�����'
    end
    object Label11: TLabel
      Left = 582
      Top = 18
      Width = 72
      Height = 12
      Caption = '�����������'
    end
    object cbbDept: TWVComboBox
      Left = 73
      Top = 14
      Width = 125
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 20
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView1
      FieldName = '��������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*210'
    end
    object edtBeginDate: TWVEdit
      Left = 473
      Top = 14
      Width = 99
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<��ʼ����>'
      WorkView = WorkView1
      FieldName = '��ʼ����'
    end
    object cbbIDType: TWVComboBox
      Left = 265
      Top = 14
      Width = 120
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 1
      WorkView = WorkView1
      FieldName = '�������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-1'
    end
    object edtEndDate: TWVEdit
      Left = 659
      Top = 14
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 3
      Text = '<��������>'
      WorkView = WorkView1
      FieldName = '��������'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 58
    Width = 800
    Height = 353
    inherited Grid: TRzDBGrid
      Width = 800
      Height = 353
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ���'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sroom_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������Ч����(��)'
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
          FieldName = 'sstatus0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ԥ����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sroom_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֤������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spager'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֤������'
          Width = 100
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
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Ա�'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�绰'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ֻ�'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��λ����'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Ļ��̶�'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ò'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������Դ'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ʩ'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snation_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_addr'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������ڵ�����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������ڵ�'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ס����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ס��ַ'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ס����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�״ε��ﱾ������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smarket_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Ƿ�ɾ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstock_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ɾ������'
          Width = 60
          Visible = True
        end>
    end
    object lvInfo: TRzListView
      Left = 0
      Top = 0
      Width = 800
      Height = 353
      Align = alClient
      Checkboxes = True
      Columns = <
        item
          Caption = '��������'
          Width = 150
        end
        item
          Caption = '�ͻ���'
          Width = 80
        end
        item
          Alignment = taCenter
          Caption = '����'
          Width = 90
        end
        item
          Alignment = taCenter
          Caption = 'Ӧ�����к�'
          Width = 120
        end
        item
          Alignment = taCenter
          Caption = '�����'
          Width = 90
        end
        item
          Alignment = taCenter
          Caption = '��ֵ���'
          Width = 1
        end
        item
          Alignment = taCenter
          Caption = '����'
          Width = 90
        end
        item
          Alignment = taCenter
          Caption = '֤������'
          Width = 120
        end
        item
          Alignment = taCenter
          Caption = '֤������'
          Width = 154
        end
        item
          Caption = '��ID'
          Width = 5
        end>
      FlatScrollBars = True
      FrameVisible = True
      GridLines = True
      RowSelect = True
      TabOrder = 1
      ViewStyle = vsReport
    end
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
        DataField = '@Return'
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
        DataField = 'vsmess'
      end
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
        Name = '������־'
        Caption = '������־'
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
        Name = '�ͻ���'
        Caption = '�ͻ���'
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
        Name = '�����к�'
        Caption = '�����к�'
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
        Name = 'Ӧ������'
        Caption = 'Ӧ������'
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
        Name = '���б���'
        Caption = '���б���'
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
        MonitorValueChangedFields = '|������־|�ͻ���|Ԥ����|'
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '�ƿ����'
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
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '�����к�'
        FieldName = '�����к�'
        DefaultValue = 0
      end
      item
        ParamName = 'Ӧ������'
        FieldName = 'Ӧ������'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = '����'
        DefaultValue = 0
      end
      item
        ParamName = '���б���'
        FieldName = '���б���'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = '����'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    WorkView = WorkView1
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sroom_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '201'
      end
      item
        FieldName = 'sstatus0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '200'
      end
      item
        FieldName = 'scust_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '202'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '203'
      end
      item
        FieldName = 'sstatus2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '204'
      end
      item
        FieldName = 'sstatus3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '205'
      end
      item
        FieldName = 'sstatus4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '206'
      end
      item
        FieldName = 'sserial0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '207'
      end
      item
        FieldName = 'snation_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '208'
      end
      item
        FieldName = 'sserial1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '209'
      end
      item
        FieldName = 'sserial2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '211'
      end
      item
        FieldName = 'sserial3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '212'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '213'
      end
      item
        FieldName = 'sroom_no2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '210'
      end>
    Left = 240
    Top = 280
  end
  inherited DataSource: TDataSource
    Left = 272
    Top = 280
  end
  object QueryRequest: TWVRequest
    WorkView = WorkView1
    ID = '�ƿ���˲�ѯ'
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
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��ʼ����'
        FieldName = '��ʼ����'
      end>
    Left = 208
    Top = 280
  end
  object WorkView1: TWorkView
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
        Name = '��ѯ�����'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '������־'
        Caption = '������־'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sstat_type'
      end
      item
        Name = '��ʼ����'
        Caption = '��ʼ����'
        FieldType = wftUndefined
        DataType = kdtString
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
        Name = '��������'
        Caption = '��������'
        FieldType = wftUndefined
        DataType = kdtString
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
        Name = '��������'
        Caption = '��������'
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
    Left = 168
    Top = 280
  end
  object dlgSave1: TSaveDialog
    Title = '���ʧ����Ϣ'
    Left = 216
    Top = 313
  end
end
