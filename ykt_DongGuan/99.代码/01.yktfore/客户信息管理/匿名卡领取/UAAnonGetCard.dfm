inherited faqhAnonGetCard: TfaqhAnonGetCard
  Width = 806
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 435
    Width = 806
    Height = 54
    object Label2: TLabel [0]
      Left = 106
      Top = 10
      Width = 48
      Height = 12
      Caption = '�շѽ��'
    end
    object rzstspn1: TRzStatusPane [1]
      Left = 0
      Top = 31
      Width = 806
      Height = 23
      FrameStyle = fsStatus
      Align = alBottom
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    inherited btnQuery: TBitBtn
      Left = 541
    end
    inherited btnPrint: TBitBtn
      Left = 716
    end
    object btnGetCard: TBitBtn
      Left = 629
      Top = 3
      Width = 79
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '�� ��'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnGetCardClick
    end
    object chkPrint: TCheckBox
      Left = 8
      Top = 8
      Width = 73
      Height = 17
      Caption = '��ӡ�ص�'
      Checked = True
      State = cbChecked
      TabOrder = 3
    end
    object btnReadCard: TBitBtn
      Left = 453
      Top = 3
      Width = 79
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '������ѯ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object edtMoney: TWVEdit
      Left = 160
      Top = 5
      Width = 107
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 5
      Text = '<Ԥ����>'
      WorkView = WorkView
      FieldName = 'Ԥ����'
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 806
    inherited Image1: TImage
      Width = 806
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 806
    Height = 87
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
    object Label12: TLabel
      Left = 18
      Top = 42
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label7: TLabel
      Left = 18
      Top = 66
      Width = 48
      Height = 12
      Caption = '����״̬'
    end
    object Label9: TLabel
      Left = 386
      Top = 18
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label14: TLabel
      Left = 218
      Top = 42
      Width = 24
      Height = 12
      Caption = '�Ա�'
    end
    object Label17: TLabel
      Left = 194
      Top = 66
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label15: TLabel
      Left = 386
      Top = 42
      Width = 24
      Height = 12
      Caption = '�绰'
    end
    object Label10: TLabel
      Left = 194
      Top = 18
      Width = 48
      Height = 12
      Caption = '֤������'
    end
    object Label16: TLabel
      Left = 569
      Top = 42
      Width = 24
      Height = 12
      Caption = '�ֻ�'
    end
    object Label11: TLabel
      Left = 545
      Top = 18
      Width = 48
      Height = 12
      Caption = '֤������'
    end
    object Label1: TLabel
      Left = 386
      Top = 66
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label3: TLabel
      Left = 533
      Top = 66
      Width = 60
      Height = 12
      Caption = 'Ӧ�����к�'
    end
    object cbb1: TWVComboBox
      Left = 76
      Top = 62
      Width = 112
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 8
      WorkView = WorkView1
      FieldName = '��ѯ.����״̬'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*200'
    end
    object edtBirthdayQ: TWVEdit
      Left = 76
      Top = 38
      Width = 112
      Height = 20
      Color = clInfoBk
      MaxLength = 9
      ReadOnly = False
      TabOrder = 4
      Text = '<��ѯ.��������>'
      WorkView = WorkView1
      FieldName = '��ѯ.��������'
    end
    object cbbDept: TWVComboBox
      Left = 76
      Top = 14
      Width = 112
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView1
      FieldName = '��ѯ.��������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*210'
    end
    object WVEdit17: TWVEdit
      Left = 252
      Top = 62
      Width = 116
      Height = 20
      Color = clInfoBk
      MaxLength = 9
      ReadOnly = False
      TabOrder = 9
      Text = '<��ѯ.��������>'
      WorkView = WorkView1
      FieldName = '��ѯ.��������'
    end
    object WVComboBox1: TWVComboBox
      Left = 252
      Top = 38
      Width = 116
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView1
      FieldName = '��ѯ.�Ա�'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*202'
    end
    object WVEdit9: TWVEdit
      Left = 420
      Top = 14
      Width = 107
      Height = 20
      Color = clInfoBk
      MaxLength = 9
      ReadOnly = False
      TabOrder = 2
      Text = '<��ѯ.����>'
      WorkView = WorkView1
      FieldName = '��ѯ.����'
    end
    object cbbIDType: TWVComboBox
      Left = 252
      Top = 14
      Width = 116
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 1
      WorkView = WorkView1
      FieldName = '��ѯ.֤������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*201'
    end
    object WVEdit15: TWVEdit
      Left = 420
      Top = 38
      Width = 107
      Height = 20
      Color = clInfoBk
      MaxLength = 9
      ReadOnly = False
      TabOrder = 6
      Text = '<��ѯ.�绰>'
      WorkView = WorkView1
      FieldName = '��ѯ.�绰'
    end
    object WVEdit11: TWVEdit
      Left = 599
      Top = 14
      Width = 132
      Height = 20
      Color = clInfoBk
      MaxLength = 9
      ReadOnly = False
      TabOrder = 3
      Text = '<��ѯ.֤������>'
      WorkView = WorkView1
      FieldName = '��ѯ.֤������'
    end
    object WVEdit16: TWVEdit
      Left = 599
      Top = 38
      Width = 132
      Height = 20
      Color = clInfoBk
      MaxLength = 9
      ReadOnly = False
      TabOrder = 7
      Text = '<��ѯ.�ֻ�>'
      WorkView = WorkView1
      FieldName = '��ѯ.�ֻ�'
    end
    object WVEdit1: TWVEdit
      Left = 420
      Top = 61
      Width = 107
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 10
      Text = '<��ѯ.����>'
      WorkView = WorkView1
      FieldName = '��ѯ.����'
    end
    object WVEdit2: TWVEdit
      Left = 599
      Top = 61
      Width = 132
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 11
      Text = '<Ӧ�����к�>'
      WorkView = WorkView1
      FieldName = 'Ӧ�����к�'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 105
    Width = 806
    inherited Grid: TRzDBGrid
      Width = 806
      OnCellClick = GridCellClick
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
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ӧ�����к�'
          Width = 90
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
        Name = 'Ԥ����'
        Caption = 'Ԥ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
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
    ID = '�ɷ��쿨'
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
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = 'Ԥ����'
        FieldName = 'Ԥ����'
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
    ID = '�ͻ���Ϣά����ѯ'
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
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '����״̬'
        FieldName = '��ѯ.����״̬'
      end
      item
        ParamName = '����'
        FieldName = '��ѯ.����'
      end
      item
        ParamName = '֤������'
        FieldName = '��ѯ.֤������'
      end
      item
        ParamName = '֤������'
        FieldName = '��ѯ.֤������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '�Ա�'
        FieldName = '��ѯ.�Ա�'
      end
      item
        ParamName = '�绰'
        FieldName = '��ѯ.�绰'
      end
      item
        ParamName = '�ֻ�'
        FieldName = '��ѯ.�ֻ�'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '����'
        FieldName = '��ѯ.����'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'Ӧ�����к�'
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
        Name = '�������.����'
        Caption = '�������.����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '1'
      end
      item
        Name = '�������.ɾ��'
        Caption = '�������.ɾ��'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '2'
      end
      item
        Name = '�������.�޸�'
        Caption = '�������.�޸�'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = '3'
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.����״̬'
        Caption = '��ѯ.����״̬'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.����'
        Caption = '��ѯ.����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.֤������'
        Caption = '��ѯ.֤������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.֤������'
        Caption = '��ѯ.֤������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�Ա�'
        Caption = '��ѯ.�Ա�'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�绰'
        Caption = '��ѯ.�绰'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�ֻ�'
        Caption = '��ѯ.�ֻ�'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.����'
        Caption = '��ѯ.����'
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
        Name = 'Ӧ�����к�'
        Caption = 'Ӧ�����к�'
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
    FieldsMonitors = <>
    Left = 168
    Top = 280
  end
  object rpt1: TRMReport
    InitialZoom = pzDefault
    PreviewButtons = [pbZoom, pbLoad, pbSave, pbPrint, pbFind, pbPageSetup, pbExit, pbSaveToXLS]
    DefaultCopies = 0
    DefaultCollate = False
    SaveReportOptions.RegistryPath = 'ReportMachine\ReportSettings\'
    Left = 240
    Top = 226
    ReportData = {}
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView2
    ID = '�ɷѲ�ѯ'
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
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'Ԥ�����'
        FieldName = 'Ԥ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ɷ���Ϣ'
        FieldName = '�ɷ���Ϣ'
        Direction = bdParam2Field
      end>
    AfterExec = MainRequestAfterExec
    Left = 208
    Top = 320
  end
  object WorkView2: TWorkView
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
        Name = '�ͻ���'
        Caption = '�ͻ���'
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
        Name = '����'
        Caption = '����'
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
        Name = 'Ԥ�����'
        Caption = 'Ԥ�����'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�ɷ���Ϣ'
        Caption = '�ɷ���Ϣ'
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
        MonitorValueChangedFields = '|������־|�ͻ���|Ԥ����|'
      end>
    Left = 172
    Top = 319
  end
end
