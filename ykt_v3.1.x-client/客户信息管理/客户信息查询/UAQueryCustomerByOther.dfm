inherited faqhQueryCustomerByOther: TfaqhQueryCustomerByOther
  Width = 770
  Height = 463
  inherited UIPanel1: TUIPanel
    Top = 427
    Width = 770
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 507
      Top = 5
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 680
      Top = 5
      TabOrder = 2
    end
    object btnPhoto: TBitBtn
      Left = 594
      Top = 5
      Width = 79
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = 'ȡ��Ƭ(&S)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnPhotoClick
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 770
    inherited Image1: TImage
      Width = 770
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 770
    Height = 135
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 17
      Top = 39
      Width = 48
      Height = 12
      Caption = '�ͻ����'
    end
    object Label2: TLabel
      Left = 454
      Top = 39
      Width = 48
      Height = 12
      Caption = '�ͻ�״̬'
    end
    object Label3: TLabel
      Left = 236
      Top = 87
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label4: TLabel
      Left = 454
      Top = 15
      Width = 48
      Height = 12
      Caption = '�ͻ�����'
    end
    object Label5: TLabel
      Left = 242
      Top = 15
      Width = 42
      Height = 12
      Caption = 'ѧ/����'
    end
    object Label6: TLabel
      Left = 236
      Top = 63
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label8: TLabel
      Left = 41
      Top = 63
      Width = 24
      Height = 12
      Caption = '�Ա�'
    end
    object Label9: TLabel
      Left = 478
      Top = 63
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label10: TLabel
      Left = 17
      Top = 87
      Width = 48
      Height = 12
      Caption = '֤������'
    end
    object Label11: TLabel
      Left = 236
      Top = 111
      Width = 48
      Height = 12
      Caption = 'ע������'
    end
    object WVLabel2: TWVLabel
      Left = 29
      Top = 15
      Width = 36
      Height = 12
      Caption = '�ͻ���'
    end
    object WVLabel1: TWVLabel
      Left = 29
      Top = 111
      Width = 36
      Height = 12
      Caption = '���κ�'
    end
    object Label13: TLabel
      Left = 236
      Top = 39
      Width = 48
      Height = 12
      Caption = '�շ����'
    end
    object WVLabel3: TWVLabel
      Left = 478
      Top = 111
      Width = 24
      Height = 12
      Caption = '�༶'
    end
    object Label7: TLabel
      Left = 478
      Top = 87
      Width = 24
      Height = 12
      Caption = 'רҵ'
    end
    object imgPhoto: TImage
      Left = 657
      Top = 12
      Width = 84
      Height = 112
      Stretch = True
    end
    object WVComboBox1: TWVComboBox
      Left = 77
      Top = 34
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '�ͻ����'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-34'
    end
    object WVComboBox2: TWVComboBox
      Left = 508
      Top = 34
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '�ͻ�״̬'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*15'
    end
    object WVComboBox3: TWVComboBox
      Left = 291
      Top = 82
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 12
      WorkView = WorkView
      FieldName = '�ͻ���������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-27'
    end
    object WVEdit4: TWVEdit
      Left = 508
      Top = 10
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<�ͻ�����>'
      WorkView = WorkView
      FieldName = '�ͻ�����'
    end
    object WVEdit5: TWVEdit
      Left = 291
      Top = 10
      Width = 142
      Height = 20
      CharCase = ecUpperCase
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<��ϵ��ѧ����>'
      WorkView = WorkView
      FieldName = '��ϵ��ѧ����'
    end
    object cbbDeptName: TWVComboBox
      Left = 291
      Top = 58
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 8
      Visible = False
      WorkView = WorkView
      FieldName = '��ϵ�˵�λ��'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object WVComboBox8: TWVComboBox
      Left = 77
      Top = 58
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView
      FieldName = '��ϵ���Ա�'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*39'
    end
    object WVComboBox9: TWVComboBox
      Left = 508
      Top = 58
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 9
      WorkView = WorkView
      FieldName = '��ϵ������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*2001'
    end
    object WVEdit10: TWVEdit
      Left = 77
      Top = 82
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 11
      Text = '<��ϵ�����֤��>'
      WorkView = WorkView
      FieldName = '��ϵ�����֤��'
    end
    object WVEdit11: TWVEdit
      Left = 291
      Top = 106
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 15
      Text = '<ע������>'
      WorkView = WorkView
      FieldName = 'ע������'
    end
    object WVEdit2: TWVEdit
      Left = 77
      Top = 10
      Width = 142
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<�ͻ���>'
      WorkView = WorkView
      FieldName = '�ͻ���'
    end
    object WVEdit1: TWVEdit
      Left = 77
      Top = 106
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 14
      Text = '<���κ�>'
      WorkView = WorkView
      FieldName = '���κ�'
    end
    object WVComboBox4: TWVComboBox
      Left = 291
      Top = 34
      Width = 142
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 4
      WorkView = WorkView
      FieldName = '�շ����'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-43'
    end
    object WVEdit3: TWVEdit
      Left = 508
      Top = 106
      Width = 142
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 16
      Text = '<�༶>'
      WorkView = WorkView
      FieldName = '�༶'
    end
    object cbbSpec: TWVComboBox
      Left = 510
      Top = 82
      Width = 139
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 13
      Visible = False
      WorkView = WorkView
      FieldName = 'רҵ'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-23'
    end
    object cbb1: TKSFilterComboBox
      Left = 291
      Top = 57
      Width = 142
      Height = 22
      ListFont.Charset = GB2312_CHARSET
      ListFont.Color = clWindowText
      ListFont.Height = -12
      ListFont.Name = '����'
      ListFont.Style = []
      OnFilterItems = cbb1FilterItems
      TabOrder = 6
    end
    object cbb2: TKSFilterComboBox
      Left = 508
      Top = 81
      Width = 142
      Height = 22
      ListFont.Charset = GB2312_CHARSET
      ListFont.Color = clWindowText
      ListFont.Height = -12
      ListFont.Name = '����'
      ListFont.Style = []
      OnFilterItems = cbb2FilterItems
      TabOrder = 10
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 153
    Width = 770
    Height = 274
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 770
      Height = 274
      Columns = <
        item
          Expanded = False
          FieldName = 'sbranch_code0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 91
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ���'
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���κ�'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ѧ/����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ�����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstat_type'
          PickList.Strings = ()
          Title.Caption = '����Ǯ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smarket_code2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Ա�'
          Width = 40
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ����'
          Width = 61
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�շ����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 128
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ȫ��'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'רҵ'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ�״̬'
          Width = 57
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ע������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard1'
          PickList.Strings = ()
          Title.Caption = '�༶'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ϵ��'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'snation_code'
          PickList.Strings = ()
          Title.Caption = '����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_type2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smarket_code'
          PickList.Strings = ()
          Title.Caption = '֤������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֤������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ϵ�绰'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone2'
          PickList.Strings = ()
          Title.Caption = '�ֻ�'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail'
          PickList.Strings = ()
          Title.Caption = '��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scusttypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ϵ��ַ'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spost_code'
          PickList.Strings = ()
          Title.Caption = '�ʱ�'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Caption = '��ѧ����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Caption = 'Ԥ����У����'
          Width = 70
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
        OwnObject = True
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
        Name = '�ͻ���'
        Caption = '�ͻ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '�ͻ�����'
        Caption = '�ͻ�����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '�ͻ�״̬'
        Caption = '�ͻ�״̬'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '�ͻ����'
        Caption = '�ͻ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '�շ����'
        Caption = '�շ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '��ϵ�˵�λ��'
        Caption = '��ϵ�˵�λ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '��ϵ���Ա�'
        Caption = '��ϵ���Ա�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '��ϵ��ѧ����'
        Caption = '��ϵ��ѧ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '��ϵ������'
        Caption = '��ϵ������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '��ϵ�����֤��'
        Caption = '��ϵ�����֤��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '�ͻ���������'
        Caption = '�ͻ���������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
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
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = 'ע������'
        Caption = 'ע������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
      end
      item
        Name = '�༶'
        Caption = '�༶'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
        GroupIndex = 1
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
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
      end
      item
        Name = 'רҵ'
        Caption = 'רҵ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GoNextWhenPressEnter = False
        ArrowSwitchFocus = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|�ͻ����|�ͻ�״̬|����|�ͻ�����|��ϵ��ѧ�Ż�Ա����|��ϵ�˰༶��' +
          '����|��ϵ������|��ϵ���Ա�|��ϵ���������|��ϵ�����֤��|��ϵ��' +
          '��|��ϵ��ַ|ע��ʱ��|Ԥ��ע��ʱ��|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 84
    Top = 319
  end
  inherited MainRequest: TWVRequest
    ID = '�ͻ���Ϣ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
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
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
      end
      item
        ParamName = '�ͻ�״̬'
        FieldName = '�ͻ�״̬'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '�ͻ���������'
        FieldName = '�ͻ���������'
      end
      item
        ParamName = '��ϵ��ѧ����'
        FieldName = '��ϵ��ѧ����'
      end
      item
        ParamName = '��ϵ�˵�λ��'
        FieldName = '��ϵ�˵�λ��'
      end
      item
        ParamName = '��ϵ���Ա�'
        FieldName = '��ϵ���Ա�'
      end
      item
        ParamName = '��ϵ������'
        FieldName = '��ϵ������'
      end
      item
        ParamName = '��ϵ�����֤��'
        FieldName = '��ϵ�����֤��'
      end
      item
        ParamName = 'ע������'
        FieldName = 'ע������'
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '�༶'
        FieldName = '�༶'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'רҵ'
        FieldName = 'רҵ'
      end>
    Left = 120
    Top = 320
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-34'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '15'
      end
      item
        FieldName = 'scust_type2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2001'
      end
      item
        FieldName = 'smarket_code2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '39'
      end
      item
        FieldName = 'scert_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'scust_no2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-23'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '87'
      end
      item
        FieldName = 'snation_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '89'
      end
      item
        FieldName = 'sstat_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '125'
      end>
    Left = 192
    Top = 320
  end
  inherited DataSource: TDataSource
    Top = 320
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '��Ƭ��ѯ'
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
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '�ļ���'
        FieldName = '�ļ���'
        Direction = bdParam2Field
      end>
    AfterExec = MainRequestAfterExec
    Left = 120
    Top = 360
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
        Name = '�ͻ���'
        Caption = '�ͻ���'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '�ļ���'
        Caption = '�ļ���'
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
          '|�ͻ����|�ͻ�״̬|����|�ͻ�����|��ϵ��ѧ�Ż�Ա����|��ϵ�˰༶��' +
          '����|��ϵ������|��ϵ���Ա�|��ϵ���������|��ϵ�����֤��|��ϵ��' +
          '��|��ϵ��ַ|ע��ʱ��|Ԥ��ע��ʱ��|'
      end>
    Left = 84
    Top = 359
  end
end
