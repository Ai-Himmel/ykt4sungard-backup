inherited faqhDealBankAcc: TfaqhDealBankAcc
  Width = 751
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 448
    Width = 751
    Height = 41
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 574
      Top = 11
    end
    inherited btnPrint: TBitBtn
      Left = 661
      Top = 1000
      Visible = False
    end
    object grpResult: TGroupBox
      Left = 0
      Top = 0
      Width = 385
      Height = 41
      Align = alLeft
      Caption = '�������'
      TabOrder = 2
      object Label1: TLabel
        Left = 7
        Top = 18
        Width = 48
        Height = 12
        Caption = '����״̬'
      end
      object Label3: TLabel
        Left = 183
        Top = 18
        Width = 24
        Height = 12
        Caption = '��ע'
      end
      object WVComboBox1: TWVComboBox
        Left = 60
        Top = 14
        Width = 109
        Height = 20
        Style = csDropDownList
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 0
        WorkView = WVDeal
        FieldName = '����״̬'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*171'
      end
      object edtMemo: TWVEdit
        Left = 212
        Top = 13
        Width = 165
        Height = 20
        CharCase = ecUpperCase
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<��ע>'
        WorkView = WVDeal
        FieldName = '��ע'
      end
    end
    object btnDeal: TBitBtn
      Left = 662
      Top = 11
      Width = 79
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '�� ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnDealClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 751
    TabOrder = 2
    inherited Image1: TImage
      Width = 751
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 751
    Height = 55
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object Label2: TLabel
      Left = 18
      Top = 9
      Width = 48
      Height = 12
      Caption = '��ʼ����'
    end
    object lbl1: TLabel
      Left = 376
      Top = 9
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object lbl2: TLabel
      Left = 194
      Top = 9
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object lbl3: TLabel
      Left = 18
      Top = 33
      Width = 48
      Height = 12
      Caption = '����״̬'
    end
    object lbl4: TLabel
      Left = 194
      Top = 33
      Width = 48
      Height = 12
      Caption = '����״̬'
    end
    object edtBeginDate: TWVEdit
      Left = 68
      Top = 5
      Width = 109
      Height = 20
      CharCase = ecUpperCase
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<��ʼ����>'
      WorkView = WorkView
      FieldName = '��ʼ����'
    end
    object cbbOperTrans: TWVComboBox
      Left = 428
      Top = 5
      Width = 133
      Height = 20
      Style = csDropDownList
      Color = clWhite
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ItemHeight = 12
      ParentFont = False
      TabOrder = 1
      WorkView = WorkView
      FieldName = '���б��'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-18'
    end
    object edtEndDate: TWVEdit
      Left = 244
      Top = 5
      Width = 109
      Height = 20
      CharCase = ecUpperCase
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object cbb1: TWVComboBox
      Left = 68
      Top = 29
      Width = 109
      Height = 20
      Style = csDropDownList
      Color = clWhite
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ItemHeight = 12
      ParentFont = False
      TabOrder = 3
      WorkView = WorkView
      FieldName = '����״̬'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*170'
    end
    object cbb2: TWVComboBox
      Left = 244
      Top = 29
      Width = 109
      Height = 20
      Style = csDropDownList
      Color = clWhite
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ItemHeight = 12
      ParentFont = False
      TabOrder = 4
      WorkView = WorkView
      FieldName = '����״̬'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*171'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 73
    Width = 751
    Height = 375
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Width = 751
      Height = 375
      Columns = <
        item
          Expanded = False
          FieldName = 'lbank_acc_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�˵�����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ע'
          Width = 200
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����ܽ��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'һ��ͨ������'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'һ��ͨ�ܽ��'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��¼����ʱ��'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��¼����ʱ��'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scusttypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���ж����ļ���'
          Width = 200
          Visible = True
        end>
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
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
        Name = '��ʼ����'
        Caption = '��ʼ����'
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
        Name = '���б��'
        Caption = '���б��'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|ѧ��|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '���ж��˲�ѯ'
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
        ParamName = '��ʼ����'
        FieldName = '��ʼ����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '���б��'
        FieldName = '���б��'
      end
      item
        ParamName = '����״̬'
        FieldName = '����״̬'
      end
      item
        ParamName = '����״̬'
        FieldName = '����״̬'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '-18'
      end
      item
        FieldName = 'sorder0'
        DataPresentType = 'idobjects'
        DataPresentParam = '170'
      end
      item
        FieldName = 'sorder1'
        DataPresentType = 'idobjects'
        DataPresentParam = '171'
      end>
    Left = 240
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 280
    Top = 224
  end
  object WVDeal: TWorkView
    WorkFields = <
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
        Name = '�˵�����'
        Caption = '�˵�����'
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
        Name = '���б��'
        Caption = '���б��'
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
        MonitorValueChangedFields = '|ѧ��|'
      end>
    Left = 164
    Top = 255
  end
  object WVRDeal: TWVRequest
    WorkView = WVDeal
    ID = '���ж��˴���'
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
        ParamName = '�˵�����'
        FieldName = '�˵�����'
      end
      item
        ParamName = '���б��'
        FieldName = '���б��'
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
    Left = 200
    Top = 256
  end
end
