inherited faqhBankCardLinkBind: TfaqhBankCardLinkBind
  Width = 770
  Height = 463
  inherited UIPanel1: TUIPanel
    Top = 427
    Width = 770
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 419
      Top = 5
    end
    inherited btnPrint: TBitBtn
      Left = 680
      Top = 100
      Enabled = True
      TabOrder = 5
    end
    object btnBinding: TBitBtn
      Left = 506
      Top = 5
      Width = 79
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = '�� ��'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnBindingClick
    end
    object chkSelectAll: TCheckBox
      Left = 16
      Top = 8
      Width = 57
      Height = 17
      Caption = 'ȫѡ'
      TabOrder = 4
      OnClick = chkSelectAllClick
    end
    object btnCloseBinding: TBitBtn
      Left = 594
      Top = 5
      Width = 79
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = '�����'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnCloseBindingClick
    end
    object btnSynoData: TBitBtn
      Left = 682
      Top = 5
      Width = 79
      Height = 25
      Hint = '��ѯ/ˢ������'
      Anchors = [akTop, akRight]
      Caption = 'ͬ������'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnSynoDataClick
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
    Height = 55
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label6: TLabel
      Left = 40
      Top = 10
      Width = 42
      Height = 12
      Caption = 'ѧ/����'
    end
    object Label13: TLabel
      Left = 34
      Top = 34
      Width = 48
      Height = 12
      Caption = '���п���'
    end
    object Label8: TLabel
      Left = 218
      Top = 34
      Width = 48
      Height = 12
      Caption = '����״̬'
    end
    object Label9: TLabel
      Left = 218
      Top = 10
      Width = 48
      Height = 12
      Caption = '�ͻ�����'
    end
    object Label3: TLabel
      Left = 414
      Top = 10
      Width = 36
      Height = 12
      Caption = '���κ�'
    end
    object Label7: TLabel
      Left = 590
      Top = 10
      Width = 36
      Height = 12
      Caption = '�ͻ���'
    end
    object WVEdit6: TWVEdit
      Left = 92
      Top = 6
      Width = 119
      Height = 20
      CharCase = ecUpperCase
      Color = clInfoBk
      MaxLength = 50
      ReadOnly = False
      TabOrder = 0
      Text = '<��ѯ.ѧ����>'
      WorkView = WorkView1
      FieldName = '��ѯ.ѧ����'
    end
    object WVEdit13: TWVEdit
      Left = 92
      Top = 30
      Width = 119
      Height = 20
      Color = clInfoBk
      MaxLength = 50
      ReadOnly = False
      TabOrder = 4
      Text = '<��ѯ.���п���>'
      WorkView = WorkView1
      FieldName = '��ѯ.���п���'
    end
    object WVEdit9: TWVEdit
      Left = 276
      Top = 6
      Width = 118
      Height = 20
      Color = clInfoBk
      MaxLength = 50
      ReadOnly = False
      TabOrder = 1
      Text = '<��ѯ.�ͻ�����>'
      WorkView = WorkView1
      FieldName = '��ѯ.�ͻ�����'
    end
    object cbbQFeeType: TWVComboBox
      Left = 276
      Top = 32
      Width = 118
      Height = 18
      Style = csOwnerDrawFixed
      Color = clWhite
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView1
      FieldName = '��ѯ.��״̬'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*10'
    end
    object WVEdit3: TWVEdit
      Left = 460
      Top = 6
      Width = 125
      Height = 20
      Color = clInfoBk
      MaxLength = 50
      ReadOnly = False
      TabOrder = 2
      Text = '<��ѯ.���κ�>'
      WorkView = WorkView1
      FieldName = '��ѯ.���κ�'
    end
    object edtCustNo: TWVEdit
      Left = 636
      Top = 6
      Width = 123
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 3
      Text = '<��ѯ.�ͻ���>'
      WorkView = WorkView1
      FieldName = '��ѯ.�ͻ���'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 73
    Width = 770
    Height = 354
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 770
      Height = 354
      TabOrder = 1
    end
    object lv1: TRzListView
      Left = 0
      Top = 0
      Width = 770
      Height = 354
      Align = alClient
      AlphaSortAll = True
      Checkboxes = True
      Columns = <
        item
          Caption = '��¼��'
          Width = 80
        end
        item
          Caption = '�������κ�'
          Width = 80
        end
        item
          Caption = '����Ա'
          Width = 60
        end
        item
          Caption = '�ͻ���'
          Width = 70
        end
        item
          Caption = 'ѧ/����'
          Width = 80
        end
        item
          Caption = '�ͻ�����'
          Width = 80
        end
        item
          Caption = '���п���'
          Width = 120
        end
        item
          Caption = '��������'
          Width = 60
        end
        item
          Caption = '����״̬'
          Width = 60
        end
        item
          Caption = '��ע'
          Width = 59
        end>
      GridLines = True
      TabOrder = 0
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
      end
      item
        Name = '��¼��'
        Caption = '��¼��'
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
        MonitorValueChangedFields = 
          '|�ͻ����|�ͻ�״̬|����|�ͻ�����|��ϵ��ѧ�Ż�Ա����|��ϵ�˰༶��' +
          '����|��ϵ������|��ϵ���Ա�|��ϵ���������|��ϵ�����֤��|��ϵ��' +
          '��|��ϵ��ַ|ע��ʱ��|Ԥ��ע��ʱ��|'
      end>
    Left = 84
    Top = 319
  end
  inherited MainRequest: TWVRequest
    ID = '���п�������'
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
        ParamName = '��¼��'
        FieldName = '��¼��'
      end
      item
        ParamName = '����'
        FieldName = '����'
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
  object QueryRequest: TWVRequest
    WorkView = WorkView1
    ID = '���п��󶨲�ѯ����'
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
        ParamName = '��״̬'
        FieldName = '��ѯ.��״̬'
      end
      item
        ParamName = '���κ�'
        FieldName = '��ѯ.���κ�'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '��ѯ.�ͻ�����'
      end
      item
        ParamName = 'ѧ����'
        FieldName = '��ѯ.ѧ����'
      end
      item
        ParamName = '���д���'
        FieldName = '��ѯ.���д���'
      end
      item
        ParamName = '���п���'
        FieldName = '��ѯ.���п���'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '��ѯ.�ͻ���'
      end>
    Left = 120
    Top = 264
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
        GroupIndex = 1
        DataField = '@Dataset'
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
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.���κ�'
        Caption = '��ѯ.���κ�'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�ͻ���'
        Caption = '��ѯ.�ͻ���'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
      end
      item
        Name = '��ѯ.ѧ����'
        Caption = '��ѯ.ѧ����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�ͻ�����'
        Caption = '��ѯ.�ͻ�����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.���п���'
        Caption = '��ѯ.���п���'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.���д���'
        Caption = '��ѯ.���д���'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.��״̬'
        Caption = '��ѯ.��״̬'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '��¼��'
        Caption = '��¼��'
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
        GroupIndex = 1
        DataField = 'sname2'
      end
      item
        Name = 'ѧ����'
        Caption = 'ѧ����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'spager'
      end
      item
        Name = '���п���'
        Caption = '���п���'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'Scard0'
      end
      item
        Name = '���κ�'
        Caption = '���κ�'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_limit'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.������־|��ѯ.��������|��ѯ.���κ�|��ѯ.����˳���|��ѯ.��' +
          '�����Ա|��ѯ.ѧ����|��ѯ.�ͻ�����|��ѯ.�շ����|��ѯ.�ͻ�����|' +
          '��ѯ.�������|��ѯ.���Ŵ���|��ѯ.רҵ����|��ѯ.�༶|��ѯ.֤����' +
          '��|��ѯ.֤������|��ѯ.�Ա�|��ѯ.����|��ѯ.����|��ѯ.��������|��' +
          'ѯ.�绰|��ѯ.�ֻ�|��ѯ.��ַ|��ѯ.��������|��ѯ.��У����|��ѯ.Ԥ' +
          '����У����|'
      end
      item
        MonitorValueChangedFields = 
          '|��������|���κ�|����˳���|�������Ա|ѧ����|�ͻ�����|�շ����|' +
          '�ͻ�����|�������|���Ŵ���|רҵ����|�༶|֤������|֤������|�Ա�|' +
          '����|����|��������|�绰|�ֻ�|��ַ|��������|��У����|'
      end>
    Left = 80
    Top = 264
  end
  object dlgSave1: TSaveDialog
    Filter = '�ı��ļ�(*.txt)|*.txt'
    Title = '����ʧ�ܼ�¼'
    Left = 232
    Top = 321
  end
end
