inherited faqAnonGetCardNew: TfaqAnonGetCardNew
  Width = 712
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 435
    Width = 712
    Height = 54
    object Label13: TLabel [0]
      Left = 74
      Top = 10
      Width = 48
      Height = 12
      Caption = 'Ԥ����'
    end
    object rzstspn1: TRzStatusPane [1]
      Left = 0
      Top = 31
      Width = 712
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
      Left = 448
    end
    inherited btnPrint: TBitBtn
      Left = 622
      Caption = '���´�ӡ'
      Glyph.Data = {00000000}
    end
    object btnReadCard: TBitBtn
      Left = 361
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
      TabOrder = 2
      OnClick = btnReadCardClick
    end
    object btnGetCard: TBitBtn
      Left = 535
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
      TabOrder = 3
      OnClick = btnGetCardClick
    end
    object chkPrint: TCheckBox
      Left = 8
      Top = 8
      Width = 65
      Height = 17
      Caption = '��ӡ�ص�'
      Checked = True
      State = cbChecked
      TabOrder = 4
      Visible = False
    end
    object edtMoney: TWVEdit
      Left = 128
      Top = 5
      Width = 107
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 5
      Text = '<Ԥ����>'
      WorkView = WorkView1
      FieldName = 'Ԥ����'
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
    Height = 103
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left = 54
      Top = 9
      Width = 36
      Height = 12
      Caption = '�ͻ���'
    end
    object Label2: TLabel
      Left = 266
      Top = 9
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label3: TLabel
      Left = 442
      Top = 9
      Width = 48
      Height = 12
      Caption = '֤������'
    end
    object Label4: TLabel
      Left = 42
      Top = 33
      Width = 48
      Height = 12
      Caption = '֤������'
    end
    object Label5: TLabel
      Left = 242
      Top = 33
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label6: TLabel
      Left = 466
      Top = 33
      Width = 24
      Height = 12
      Caption = '�绰'
    end
    object Label7: TLabel
      Left = 66
      Top = 57
      Width = 24
      Height = 12
      Caption = '�ֻ�'
    end
    object Label8: TLabel
      Left = 266
      Top = 57
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label9: TLabel
      Left = 430
      Top = 57
      Width = 60
      Height = 12
      Caption = '��������'
    end
    object Label10: TLabel
      Left = 54
      Top = 81
      Width = 36
      Height = 12
      Caption = '�����'
    end
    object Label11: TLabel
      Left = 242
      Top = 81
      Width = 48
      Height = 12
      Caption = '�ƿ�����'
    end
    object Label12: TLabel
      Left = 430
      Top = 81
      Width = 60
      Height = 12
      Caption = 'Ӧ�����к�'
    end
    object edtCustNo: TWVEdit
      Left = 100
      Top = 5
      Width = 133
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<�ͻ���>'
      WorkView = WorkView
      FieldName = '�ͻ���'
    end
    object WVEdit2: TWVEdit
      Left = 300
      Top = 5
      Width = 124
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object WVEdit4: TWVEdit
      Left = 100
      Top = 29
      Width = 133
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<֤������>'
      WorkView = WorkView
      FieldName = '֤������'
    end
    object WVEdit6: TWVEdit
      Left = 500
      Top = 29
      Width = 134
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 3
      Text = '<�绰>'
      WorkView = WorkView
      FieldName = '�绰'
    end
    object WVEdit7: TWVEdit
      Left = 100
      Top = 53
      Width = 133
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 4
      Text = '<�ֻ�>'
      WorkView = WorkView
      FieldName = '�ֻ�'
    end
    object WVEdit8: TWVEdit
      Left = 300
      Top = 53
      Width = 124
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 5
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object WVEdit9: TWVEdit
      Left = 500
      Top = 53
      Width = 134
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 6
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object WVEdit11: TWVEdit
      Left = 300
      Top = 77
      Width = 124
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 7
      Text = '<�ƿ�����>'
      WorkView = WorkView
      FieldName = '�ƿ�����'
    end
    object edtAppNo: TWVEdit
      Left = 500
      Top = 77
      Width = 134
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 8
      Text = '<�����к�>'
      WorkView = WorkView
      FieldName = '�����к�'
    end
    object cbbDept: TWVComboBox
      Left = 300
      Top = 29
      Width = 124
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 20
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 9
      WorkView = WorkView
      FieldName = '��������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*210'
    end
    object WVComboBox1: TWVComboBox
      Left = 500
      Top = 5
      Width = 134
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 20
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 10
      WorkView = WorkView
      FieldName = '֤������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*201'
    end
    object WVComboBox2: TWVComboBox
      Left = 100
      Top = 77
      Width = 133
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 20
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 11
      WorkView = WorkView
      FieldName = '������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-1'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 121
    Width = 712
    Height = 314
    inherited Grid: TRzDBGrid
      Width = 712
      Height = 314
      OnCellClick = GridCellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ���'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sroom_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sroom_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֤������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'spager'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֤������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�绰'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sphone2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ֻ�'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ӧ�����к�'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��Ƭ�汾'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ƿ�����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������κ�'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���ɱ���'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���˻����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ʵ�����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ֵ�ܽ��'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'damt4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����ܽ��'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ֵ����'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���Ѵ���'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol6'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ֵ�ܱ���'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol7'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����ܱ���'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol8'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ն˺�'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����ʱ��'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sstatus0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ֵд��ʧ�ܱ�־'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol9'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ʧ��־'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'semp_pwd'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ʧ����'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'semp_pwd2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ʧ��Ч����'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sstock_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ɾ������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'smarket_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ɾ����־'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Visible = False
        end>
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
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '֤������'
        Caption = '֤������'
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
        Name = '֤������'
        Caption = '֤������'
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
        Name = '��������'
        Caption = '��������'
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
        Name = '�绰'
        Caption = '�绰'
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
        Name = '�ֻ�'
        Caption = '�ֻ�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
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
        Name = '��������'
        Caption = '��������'
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
        Name = '������'
        Caption = '������'
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
        Name = '�ƿ�����'
        Caption = '�ƿ�����'
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
        Name = '�����к�'
        Caption = '�����к�'
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
        Name = '��״̬'
        Caption = '��״̬'
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
        Name = '��ѯ���'
        Caption = '��ѯ���'
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
        MonitorValueChangedFields = 
          '|�ͻ���|����|֤������|֤������|��������|�绰|�ֻ�|����|�������' +
          '��|������|�ƿ�����|�������κ�|'
      end>
    InvalidColor = clWhite
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '�˻���Ϣ��ѯ'
    Bindings = <
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
        ParamName = '֤������'
        FieldName = '֤������'
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�绰'
        FieldName = '�绰'
      end
      item
        ParamName = '�ֻ�'
        FieldName = '�ֻ�'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '�ƿ�����'
        FieldName = '�ƿ�����'
      end
      item
        ParamName = '�����к�'
        FieldName = '�����к�'
      end
      item
        ParamName = '��״̬'
        FieldName = '��״̬'
        DefaultValue = 0
      end
      item
        ParamName = '��ѯ���'
        FieldName = '��ѯ���'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sroom_no2'
        DataPresentType = 'idobjects'
        DataPresentParam = '210'
      end
      item
        FieldName = 'sroom_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '201'
      end
      item
        FieldName = 'lvol1'
        DataPresentType = 'idobjects'
        DataPresentParam = '-1'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '-4'
      end
      item
        FieldName = 'lvol9'
        DataPresentType = 'idobjects'
        DataPresentParam = '225'
      end>
    Left = 160
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 192
    Top = 256
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
        Name = 'Ԥ����'
        Caption = 'Ԥ����'
        FieldType = wftUndefined
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
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = 'psam����'
        Caption = 'psam����'
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
        Name = '������ˮ��'
        Caption = '������ˮ��'
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
        Name = '����ʱ��'
        Caption = '����ʱ��'
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
        Name = '�����'
        Caption = '�����'
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
        Name = '��ֵ����'
        Caption = '��ֵ����'
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
        Name = '���Ѵ���'
        Caption = '���Ѵ���'
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
        Name = '�����'
        Caption = '�����'
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
        Name = '������ˮ'
        Caption = '������ˮ'
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
        Name = '������'
        Caption = '������'
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
    Left = 92
    Top = 287
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
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
      end
      item
        ParamName = '�����к�'
        FieldName = '�����к�'
      end
      item
        ParamName = 'psam����'
        FieldName = 'psam����'
      end
      item
        ParamName = '������ˮ��'
        FieldName = '������ˮ��'
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
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '��ֵ����'
        FieldName = '��ֵ����'
      end
      item
        ParamName = '���Ѵ���'
        FieldName = '���Ѵ���'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '������ˮ'
        FieldName = '������ˮ'
        Direction = bdParam2Field
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end>
    AfterExec = MainRequestAfterExec
    Left = 128
    Top = 288
  end
  object WVRequest2: TWVRequest
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
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end>
    AfterExec = MainRequestAfterExec
    Left = 128
    Top = 328
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
      end
      item
        Name = '�����'
        Caption = '�����'
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
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|������־|�ͻ���|Ԥ����|'
      end>
    Left = 92
    Top = 327
  end
end
