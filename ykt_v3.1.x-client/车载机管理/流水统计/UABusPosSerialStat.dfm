inherited faqhBusPosSerialStat: TfaqhBusPosSerialStat
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 453
    Width = 700
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 521
      Top = 6
    end
    inherited btnPrint: TBitBtn
      Left = 612
      Top = 6
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    TabOrder = 2
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
    TabOrder = 0
    object Label2: TLabel
      Left = 34
      Top = 9
      Width = 42
      Height = 12
      Caption = 'ѧ/����'
    end
    object Label3: TLabel
      Left = 210
      Top = 9
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label6: TLabel
      Left = 26
      Top = 33
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label1: TLabel
      Left = 346
      Top = 9
      Width = 48
      Height = 12
      Caption = '��ʼ�·�'
    end
    object Label4: TLabel
      Left = 506
      Top = 9
      Width = 48
      Height = 12
      Caption = '�����·�'
    end
    object Label5: TLabel
      Left = 370
      Top = 33
      Width = 24
      Height = 12
      Caption = '���'
    end
    object WVEdit2: TWVEdit
      Left = 79
      Top = 5
      Width = 101
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<ѧ����>'
      WorkView = WorkView
      FieldName = 'ѧ����'
    end
    object WVEdit3: TWVEdit
      Left = 237
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 1
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object edtBDate: TWVEdit
      Left = 398
      Top = 5
      Width = 101
      Height = 20
      Color = clWhite
      MaxLength = 6
      ReadOnly = False
      TabOrder = 2
      Text = '<��ʼ����>'
      WorkView = WorkView
      FieldName = '��ʼ����'
    end
    object edtEDate: TWVEdit
      Left = 557
      Top = 5
      Width = 100
      Height = 20
      Color = clWhite
      MaxLength = 6
      ReadOnly = False
      TabOrder = 3
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object cbbQDept: TWVComboBox
      Left = 79
      Top = 29
      Width = 259
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 20
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '����'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object cbbQType: TComboBox
      Left = 398
      Top = 28
      Width = 101
      Height = 20
      Style = csDropDownList
      ItemHeight = 12
      TabOrder = 4
      Items.Strings = (
        '0-����'
        '1-��ְ��(��ʽ)'
        '2-����'
        '3-�����շ���')
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 73
    Width = 700
    Height = 380
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 380
      Columns = <
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�·�'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�շ����'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spager'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ѧ/����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ˢ���ܴ���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ˢ��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ˢ���ܽ��'
          Width = 80
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
        DataType = kdtInteger
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
        Name = 'ѧ����'
        Caption = 'ѧ����'
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
        Checker.MaxLength = 6
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
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 6
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '���'
        Caption = '���'
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
        MonitorValueChangedFields = '|������־|��������|����ֵ|��Чʱ��|����ʱ��|������λ|'
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '���ػ���ˮͳ��'
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
        ParamName = '�������ݼ�'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '����'
        FieldName = '����'
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
        ParamName = '���'
        FieldName = '���'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'scard0'
        DataPresentType = 'idobjects'
        DataPresentParam = '-43'
      end>
    Left = 240
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 280
    Top = 224
  end
end
