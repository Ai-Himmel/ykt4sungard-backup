inherited faqhcardLibNotBalance: TfaqhcardLibNotBalance
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    TabOrder = 3
    object Label9: TLabel [0]
      Left = 14
      Top = 8
      Width = 48
      Height = 12
      Caption = '����ʽ'
    end
    inherited btnQuery: TBitBtn
      Left = 435
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 610
      TabOrder = 2
    end
    object cbbBalanceType: TWVComboBox
      Left = 67
      Top = 4
      Width = 110
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView1
      FieldName = 'ƽ�ʷ�ʽ'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '137'
    end
    object btnBalance: TBitBtn
      Left = 522
      Top = 3
      Width = 79
      Height = 25
      Hint = '��ӡ'
      Anchors = [akTop, akRight]
      Caption = '�� ��'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnBalanceClick
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
    Height = 79
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 66
      Top = 9
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label2: TLabel
      Left = 254
      Top = 9
      Width = 36
      Height = 12
      Caption = '�ͻ���'
    end
    object Label3: TLabel
      Left = 418
      Top = 9
      Width = 72
      Height = 12
      Caption = '���ⲻƽ����'
    end
    object Label4: TLabel
      Left = 18
      Top = 33
      Width = 72
      Height = 12
      Caption = '��ƽ��ֵ'
    end
    object Label5: TLabel
      Left = 242
      Top = 33
      Width = 48
      Height = 12
      Caption = 'ͳ������'
    end
    object Label6: TLabel
      Left = 442
      Top = 33
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label7: TLabel
      Left = 30
      Top = 57
      Width = 60
      Height = 12
      Caption = '�������Ա'
    end
    object Label8: TLabel
      Left = 242
      Top = 57
      Width = 48
      Height = 12
      Caption = '����״̬'
    end
    object Label10: TLabel
      Left = 442
      Top = 55
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object edtCardNo: TWVEdit
      Left = 100
      Top = 5
      Width = 124
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object edtCustNo: TWVEdit
      Left = 299
      Top = 5
      Width = 113
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 2
      Text = '<�ͻ���>'
      WorkView = WorkView
      FieldName = '�ͻ���'
    end
    object edtValue: TWVEdit
      Left = 100
      Top = 29
      Width = 124
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 3
      Text = '<��ƽ��ֵ>'
      WorkView = WorkView
      FieldName = '��ƽ��ֵ'
    end
    object edtStatDate: TWVEdit
      Left = 299
      Top = 29
      Width = 113
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 4
      Text = '<ͳ������>'
      WorkView = WorkView
      FieldName = 'ͳ������'
    end
    object edtBalanceDate: TWVEdit
      Left = 497
      Top = 29
      Width = 116
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 5
      Text = '<ƽ������>'
      WorkView = WorkView
      FieldName = 'ƽ������'
    end
    object WVComboBox1: TWVComboBox
      Left = 497
      Top = 4
      Width = 116
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '���ⲻƽ����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*136'
    end
    object WVComboBox2: TWVComboBox
      Left = 299
      Top = 52
      Width = 113
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView
      FieldName = 'ƽ��״̬'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*138'
    end
    object WVComboBox3: TWVComboBox
      Left = 101
      Top = 53
      Width = 124
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      MaxLength = 8
      TabOrder = 8
      WorkView = WorkView
      FieldName = 'ƽ�˲���Ա'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-30'
    end
    object WVComboBox4: TWVComboBox
      Left = 497
      Top = 51
      Width = 116
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView
      FieldName = '��������'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-27'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 97
    Width = 700
    Height = 362
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 362
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ���'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ƽ���'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�˻����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����״���'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ͳ������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ͳ��ʱ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ƽ�˿�ʼ����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ƽ�˽�ֹ����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ڼ�����ȱʧ���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt6'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ڼ��ֵȱʧ���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol7'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ڼ�ȱʧ��¼����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt7'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ڼ�ȱʧ�ܽ��'
          Width = 80
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
          FieldName = 'Semp_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������Ա'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Sstatus3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ע'
          Width = 80
          Visible = True
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '���ⲻƽ����'
        Caption = '���ⲻƽ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ƽ��ֵ'
        Caption = '��ƽ��ֵ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'ͳ������'
        Caption = 'ͳ������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'ƽ������'
        Caption = 'ƽ������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'ƽ�˲���Ա'
        Caption = 'ƽ�˲���Ա'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'ƽ��״̬'
        Caption = 'ƽ��״̬'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|����|�ͻ���|���ⲻƽ����|��ƽ��ֵ|ͳ������|ƽ������|ƽ�˲�' +
          '��Ա|ƽ��״̬|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '���ⲻƽ�����ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '���ⲻƽ����'
        FieldName = '���ⲻƽ����'
      end
      item
        ParamName = '��ƽ��ֵ'
        FieldName = '��ƽ��ֵ'
      end
      item
        ParamName = 'ͳ������'
        FieldName = 'ͳ������'
      end
      item
        ParamName = 'ƽ������'
        FieldName = 'ƽ������'
      end
      item
        ParamName = 'ƽ�˲���Ա'
        FieldName = 'ƽ�˲���Ա'
      end
      item
        ParamName = 'ƽ��״̬'
        FieldName = 'ƽ��״̬'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'Sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '136'
      end
      item
        FieldName = 'sstatus3'
        DataPresentType = 'idobjects'
        DataPresentParam = '138'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end>
    Left = 232
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 272
    Top = 224
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
      end
      item
        Name = '����'
        Caption = '����'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'ͳ������'
        Caption = 'ͳ������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = 'ƽ�ʷ�ʽ'
        Caption = 'ƽ�ʷ�ʽ'
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
        MonitorValueChangedFields = 
          '|����|�ͻ���|���ⲻƽ����|��ƽ��ֵ|ͳ������|ƽ������|ƽ�˲�' +
          '��Ա|ƽ��״̬|'
      end>
    Left = 164
    Top = 271
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '���ⲻƽ����'
    Bindings = <
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'ͳ������'
        FieldName = 'ͳ������'
      end
      item
        ParamName = 'ƽ�˷�ʽ'
        FieldName = 'ƽ�ʷ�ʽ'
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end>
    AfterExec = MainRequestAfterExec
    Left = 200
    Top = 272
  end
end
