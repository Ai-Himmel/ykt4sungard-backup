inherited faqhQueryUnitInfoByOther: TfaqhQueryUnitInfoByOther
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 453
    Width = 700
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 527
      Top = 5
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 610
      Top = 5
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
    Height = 55
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label2: TLabel
      Left = 228
      Top = 9
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label3: TLabel
      Left = 450
      Top = 9
      Width = 48
      Height = 12
      Caption = 'Ӣ������'
    end
    object Label4: TLabel
      Left = 34
      Top = 33
      Width = 48
      Height = 12
      Caption = '�ϼ�����'
    end
    object WVLabel1: TWVLabel
      Left = 34
      Top = 9
      Width = 48
      Height = 12
      Caption = '���Ŵ���'
    end
    object WVEdit2: TWVEdit
      Left = 286
      Top = 4
      Width = 149
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<��λ����>'
      WorkView = WorkView
      FieldName = '��λ����'
    end
    object WVEdit3: TWVEdit
      Left = 510
      Top = 4
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<Ӣ������>'
      WorkView = WorkView
      FieldName = 'Ӣ������'
    end
    object WVEdit1: TWVEdit
      Left = 92
      Top = 4
      Width = 120
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<��λ����>'
      WorkView = WorkView
      FieldName = '��λ����'
    end
    object WVComboBox3: TWVComboBox
      Left = 92
      Top = 28
      Width = 345
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '�ϼ���λ'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 73
    Width = 700
    Height = 380
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 380
      Columns = <
        item
          Expanded = False
          FieldName = 'sbranch_code0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���Ŵ���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ԭ���ű���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scusttypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ssectypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ӣ������'
          Width = 132
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ϼ�����'
          Width = 119
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Caption = '����ȫ��'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no2'
          PickList.Strings = ()
          Title.Caption = '�ɲ��Ŵ���'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit2'
          PickList.Strings = ()
          Title.Caption = '����޸�ʱ��'
          Width = 100
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
        Name = '��λ����'
        Caption = '��λ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_no'
      end
      item
        Name = '��λ����'
        Caption = '��λ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'ssectypes'
      end
      item
        Name = 'Ӣ������'
        Caption = 'Ӣ������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'vsvarstr0'
      end
      item
        Name = '�ϼ���λ'
        Caption = '�ϼ���λ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scust_no2'
      end
      item
        Name = '�������'
        Caption = '�������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�Ƿ�Ժϵ|��λ����|Ӣ������|�ϼ���λ|��λ����|�Ƿ���Ч|��ע|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 220
    Top = 247
  end
  inherited MainRequest: TWVRequest
    ID = '��λ��Ϣ��ѯһ'
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
        ParamName = '��λ����'
        FieldName = '��λ����'
      end
      item
        ParamName = '��λ����'
        FieldName = '��λ����'
      end
      item
        ParamName = 'Ӣ������'
        FieldName = 'Ӣ������'
      end
      item
        ParamName = '�ϼ���λ'
        FieldName = '�ϼ���λ'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 184
    Top = 248
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'semail2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end>
    Left = 256
    Top = 248
  end
  inherited DataSource: TDataSource
    Left = 288
    Top = 248
  end
end
