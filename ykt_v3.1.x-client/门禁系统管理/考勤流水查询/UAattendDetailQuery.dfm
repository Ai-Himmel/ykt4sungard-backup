inherited faqhattendDetailQuery: TfaqhattendDetailQuery
  Width = 809
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 809
    inherited btnQuery: TBitBtn
      Left = 632
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 719
    end
  end
  inherited Grid: TRzDBGrid
    Top = 113
    Width = 809
    Height = 346
    Columns = <
      item
        Expanded = False
        FieldName = 'lserial0'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '��ˮ��'
        Width = 55
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sall_name'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '��������'
        Width = 150
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol0'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '�ͻ���'
        Width = 55
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'scert_no'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = 'ѧ����'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lvol1'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '����'
        Width = 53
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sname'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '����'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sdate0'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '��������'
        Width = 68
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'stime0'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '����ʱ��'
        Width = 71
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'sphone'
        PickList.Strings = ()
        Title.Alignment = taCenter
        Title.Caption = '�����豸'
        Width = 80
        Visible = True
      end>
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 809
    Height = 95
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left = 66
      Top = 9
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label2: TLabel
      Left = 303
      Top = 9
      Width = 36
      Height = 12
      Caption = '�ͻ���'
    end
    object Label3: TLabel
      Left = 494
      Top = 9
      Width = 36
      Height = 12
      Caption = 'ѧ����'
    end
    object Label4: TLabel
      Left = 66
      Top = 57
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label5: TLabel
      Left = 66
      Top = 33
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label6: TLabel
      Left = 290
      Top = 33
      Width = 48
      Height = 12
      Caption = '��ʼ����'
    end
    object Label7: TLabel
      Left = 482
      Top = 33
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label8: TLabel
      Left = 291
      Top = 57
      Width = 48
      Height = 12
      Caption = '��ʼʱ��'
    end
    object Label9: TLabel
      Left = 482
      Top = 57
      Width = 48
      Height = 12
      Caption = '����ʱ��'
    end
    object Label10: TLabel
      Left = 42
      Top = 81
      Width = 276
      Height = 12
      Caption = '��ʾ��Ϣ�����ڸ�ʽ(yyyymmdd)��ʱ���ʽ(hhmmss)'
    end
    object edtCustNo: TWVEdit
      Left = 349
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<�ͻ���>'
      WorkView = WorkView
      FieldName = '�ͻ���'
    end
    object WVEdit3: TWVEdit
      Left = 540
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 1
      Text = '<ѧ����>'
      WorkView = WorkView
      FieldName = 'ѧ����'
    end
    object edtCardNo: TWVEdit
      Left = 100
      Top = 53
      Width = 165
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 2
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object WVEdit5: TWVEdit
      Left = 100
      Top = 29
      Width = 166
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 3
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object edtBeginDate: TWVEdit
      Left = 348
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 4
      Text = '<��ʼ����>'
      WorkView = WorkView
      FieldName = '��ʼ����'
    end
    object edtEndDate: TWVEdit
      Left = 540
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 5
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object WVEdit8: TWVEdit
      Left = 349
      Top = 53
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 6
      Text = '<��ʼʱ��>'
      WorkView = WorkView
      FieldName = '��ʼʱ��'
    end
    object WVEdit9: TWVEdit
      Left = 540
      Top = 53
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 7
      Text = '<����ʱ��>'
      WorkView = WorkView
      FieldName = '����ʱ��'
    end
    object WVComboBox6: TWVComboBox
      Tag = 1
      Left = 100
      Top = 6
      Width = 167
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 8
      WorkView = WorkView
      FieldName = '��������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 809
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
        Name = 'ѧ����'
        Caption = 'ѧ����'
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
        Name = '����'
        Caption = '����'
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
        Name = '��ʼ����'
        Caption = '��ʼ����'
        FieldType = wftUndefined
        DomainName = '����У��'
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
        DomainName = '����У��'
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
        Name = '��ʼʱ��'
        Caption = '��ʼʱ��'
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
        Name = '����ʱ��'
        Caption = '����ʱ��'
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
        MonitorValueChangedFields = '|��������|ѧ����|����|��ʼ����|��������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '������ˮ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
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
        ParamName = '��ʼʱ��'
        FieldName = '��ʼʱ��'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sall_name'
        DataPresentType = 'idobjects'
        DataPresentParam = '-22'
      end>
    Left = 232
    Top = 224
  end
  inherited DataSource: TDataSource
    Left = 264
    Top = 224
  end
end
