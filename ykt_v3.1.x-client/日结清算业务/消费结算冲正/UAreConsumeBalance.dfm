inherited faqhreConsumeBalance: TfaqhreConsumeBalance
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 453
    Width = 700
    Height = 36
    object Label1: TLabel [0]
      Left = 18
      Top = 12
      Width = 48
      Height = 12
      Caption = '����Ա��'
    end
    object Label2: TLabel [1]
      Left = 194
      Top = 12
      Width = 24
      Height = 12
      Caption = '����'
    end
    inherited btnQuery: TBitBtn
      Left = 525
      Top = 6
    end
    inherited btnPrint: TBitBtn
      Left = 614
      Top = 6
      Caption = '�������'
      Glyph.Data = {00000000}
    end
    object edtOperCode: TWVEdit
      Left = 76
      Top = 8
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<����Ա��>'
      WorkView = WorkView
      FieldName = '����Ա��'
    end
    object WVEdit2: TWVEdit
      Left = 228
      Top = 8
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 3
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
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
    Height = 29
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label13: TLabel
      Left = 18
      Top = 10
      Width = 60
      Height = 12
      Caption = '����Ա����'
    end
    object WVComboBox1: TWVComboBox
      Left = 85
      Top = 5
      Width = 196
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 0
      FieldName = '����Ա����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-30'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 47
    Width = 700
    Height = 406
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 406
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = '��ˮ��'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Caption = '��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder1'
          PickList.Strings = ()
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Caption = '����ʱ��'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial2'
          PickList.Strings = ()
          Title.Caption = '����Ա'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Caption = '���׽��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstation0'
          PickList.Strings = ()
          Title.Caption = '�����˺�'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstation1'
          PickList.Strings = ()
          Title.Caption = '�����˺�'
          Width = 120
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
        Name = '����Ա��'
        Caption = '����Ա��'
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
        GetPrevChar = '*'
      end
      item
        Name = '������ˮ��'
        Caption = '������ˮ��'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|����Ա��|����|������ˮ��|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '���ѽ������'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '����Ա��'
        FieldName = '����Ա��'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '������ˮ��'
        FieldName = '������ˮ��'
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    WorkView = WorkView1
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-38'
      end
      item
        FieldName = 'sserial2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-30'
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
        Name = '�ɼ���ʼ����'
        Caption = '�ɼ���ʼ����'
        FieldType = wftUndefined
        DomainName = '����У��*'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        Checker.Required = False
        GetPrevChar = '*'
      end
      item
        Name = '�ɼ���ʼʱ��'
        Caption = '�ɼ���ʼʱ��'
        FieldType = wftUndefined
        DomainName = 'ʱ��У��'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        Checker.Required = False
        GetPrevChar = '*'
      end
      item
        Name = '�ɼ���������'
        Caption = '�ɼ���������'
        FieldType = wftUndefined
        DomainName = '����У��*'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        Checker.Required = False
        GetPrevChar = '*'
      end
      item
        Name = '�ɼ�����ʱ��'
        Caption = '�ɼ�����ʱ��'
        FieldType = wftUndefined
        DomainName = 'ʱ��У��'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        Checker.Required = False
        GetPrevChar = '*'
      end
      item
        Name = '��ˮ��'
        Caption = '��ˮ��'
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
        Name = '�ϴ�����ˮ��'
        Caption = '�ϴ�����ˮ��'
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
        Name = '���״���'
        Caption = '���״���'
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
        Name = '��ˮ״̬'
        Caption = '��ˮ״̬'
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
        Name = '�ϴ�����վ��ʶ'
        Caption = '�ϴ�����վ��ʶ'
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
        Name = '���׷����豸��ʶ'
        Caption = '���׷����豸��ʶ'
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
        Name = '���׿���'
        Caption = '���׿���'
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
        Name = '�ͻ���ʶ'
        Caption = '�ͻ���ʶ'
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
        Name = '����Ա����'
        Caption = '����Ա����'
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
        GetPrevChar = '*'
      end
      item
        Name = '�豸����ID'
        Caption = '�豸����ID'
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
        MonitorValidChangedFields = '|�ɼ���ʼ����|�ɼ���ʼʱ��|�ɼ���������|�ɼ�����ʱ��|'
      end>
    Left = 92
    Top = 207
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '������ˮ��ϸ��Ϣ��ѯ������'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ɼ���ʼ����'
        FieldName = '�ɼ���ʼ����'
      end
      item
        ParamName = '�ɼ���ʼʱ��'
        FieldName = '�ɼ���ʼʱ��'
      end
      item
        ParamName = '�ɼ���������'
        FieldName = '�ɼ���������'
      end
      item
        ParamName = '�ɼ�����ʱ��'
        FieldName = '�ɼ�����ʱ��'
      end
      item
        ParamName = '��ˮ��'
        FieldName = '��ˮ��'
      end
      item
        ParamName = '�ϴ�����ˮ��'
        FieldName = '�ϴ�����ˮ��'
      end
      item
        ParamName = '���״���'
        FieldName = '���״���'
      end
      item
        ParamName = '��ˮ״̬'
        FieldName = '��ˮ״̬'
      end
      item
        ParamName = '�ϴ�����վ��ʶ'
        FieldName = '�ϴ�����վ��ʶ'
      end
      item
        ParamName = '���׷����豸��ʶ'
        FieldName = '���׷����豸��ʶ'
      end
      item
        ParamName = '���׿���'
        FieldName = '���׿���'
      end
      item
        ParamName = '�ͻ���ʶ'
        FieldName = '�ͻ���ʶ'
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
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
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '�豸����ID'
        FieldName = '�豸����ID'
      end>
    AfterExec = MainRequestAfterExec
    Left = 128
    Top = 208
  end
end
