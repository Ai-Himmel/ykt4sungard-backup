inherited faqhMakeCard2Q: TfaqhMakeCard2Q
  Width = 817
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 817
    inherited btnQuery: TBitBtn
      Left = 640
    end
    inherited btnPrint: TBitBtn
      Left = 727
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 817
    inherited Image1: TImage
      Width = 817
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 817
    Height = 31
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left = 18
      Top = 9
      Width = 72
      Height = 12
      Caption = '��˿�ʼ����'
    end
    object Label2: TLabel
      Left = 218
      Top = 9
      Width = 72
      Height = 12
      Caption = '��˽�������'
    end
    object Label3: TLabel
      Left = 406
      Top = 9
      Width = 84
      Height = 12
      Caption = '�����ƿ����κ�'
    end
    object Label4: TLabel
      Left = 618
      Top = 9
      Width = 48
      Height = 12
      Caption = '�ƿ�״̬'
    end
    object edtBeginDate: TWVEdit
      Left = 100
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 8
      ReadOnly = False
      TabOrder = 0
      Text = '<��˿�ʼ����>'
      WorkView = WorkView
      FieldName = '��˿�ʼ����'
    end
    object edtEndDate: TWVEdit
      Left = 300
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 8
      ReadOnly = False
      TabOrder = 1
      Text = '<��˽�������>'
      WorkView = WorkView
      FieldName = '��˽�������'
    end
    object WVEdit3: TWVEdit
      Left = 500
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<�����ƿ����κ�>'
      WorkView = WorkView
      FieldName = '�����ƿ����κ�'
    end
    object cbbDept: TWVComboBox
      Left = 671
      Top = 5
      Width = 103
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      DropDownCount = 20
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '�ƿ�״̬'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*243'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 49
    Width = 817
    Height = 410
    inherited Grid: TRzDBGrid
      Width = 817
      Height = 410
      Columns = <
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����ƿ����κ�'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ƿ�����'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ͬ������'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ƿ���ʼ����'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ƿ���������'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstat_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ƿ�״̬'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 100
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
        Name = '��˿�ʼ����'
        Caption = '��˿�ʼ����'
        FieldType = wftUndefined
        Features.Strings = ()
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
        GetPrevChar = '*'
      end
      item
        Name = '��˽�������'
        Caption = '��˽�������'
        FieldType = wftUndefined
        Features.Strings = ()
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
        GetPrevChar = '*'
      end
      item
        Name = '�����ƿ����κ�'
        Caption = '�����ƿ����κ�'
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
        Name = '�ƿ�״̬'
        Caption = '�ƿ�״̬'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��˿�ʼ����|��˽�������|�����ƿ����κ�|�ƿ�״̬|'
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '�����ƿ������ѯ'
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
        ParamName = '��˿�ʼ����'
        FieldName = '��˿�ʼ����'
      end
      item
        ParamName = '��˽�������'
        FieldName = '��˽�������'
      end
      item
        ParamName = '�����ƿ����κ�'
        FieldName = '�����ƿ����κ�'
      end
      item
        ParamName = '�ƿ�״̬'
        FieldName = '�ƿ�״̬'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sstat_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '243'
      end>
    Left = 168
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 208
    Top = 256
  end
end
