inherited faqhPayDetailQ: TfaqhPayDetailQ
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    inherited btnQuery: TBitBtn
      Left = 523
    end
    inherited btnPrint: TBitBtn
      Left = 610
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
    TabOrder = 3
    object Label1: TLabel
      Left = 30
      Top = 9
      Width = 60
      Height = 12
      Caption = '�������κ�'
    end
    object Label2: TLabel
      Left = 230
      Top = 9
      Width = 60
      Height = 12
      Caption = '������ˮ��'
    end
    object Label3: TLabel
      Left = 442
      Top = 9
      Width = 48
      Height = 12
      Caption = 'ί������'
    end
    object Label4: TLabel
      Left = 42
      Top = 33
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label5: TLabel
      Left = 254
      Top = 33
      Width = 36
      Height = 12
      Caption = '�̻���'
    end
    object Label6: TLabel
      Left = 430
      Top = 33
      Width = 60
      Height = 12
      Caption = '�տ�˻�'
    end
    object Label7: TLabel
      Left = 18
      Top = 57
      Width = 72
      Height = 12
      Caption = '�տ�˻���'
    end
    object Label8: TLabel
      Left = 206
      Top = 57
      Width = 84
      Height = 12
      Caption = '�տ��˿����к�'
    end
    object Label9: TLabel
      Left = 442
      Top = 57
      Width = 48
      Height = 12
      Caption = '����״̬'
    end
    object WVEdit1: TWVEdit
      Left = 100
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 0
      Text = '<�������κ�>'
      WorkView = WorkView
      FieldName = '�������κ�'
    end
    object WVEdit2: TWVEdit
      Left = 300
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 1
      Text = '<������ˮ��>'
      WorkView = WorkView
      FieldName = '������ˮ��'
    end
    object edtDDate: TWVEdit
      Left = 500
      Top = 5
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<ί������>'
      WorkView = WorkView
      FieldName = 'ί������'
    end
    object edtCdate: TWVEdit
      Left = 100
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 3
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object edtBusiId: TWVEdit
      Left = 300
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 4
      Text = '<�̻���>'
      WorkView = WorkView
      FieldName = '�̻���'
    end
    object WVEdit6: TWVEdit
      Left = 500
      Top = 29
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 5
      Text = '<�տ�˻�>'
      WorkView = WorkView
      FieldName = '�տ�˻�'
    end
    object WVEdit7: TWVEdit
      Left = 100
      Top = 53
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 6
      Text = '<�տ�˻���>'
      WorkView = WorkView
      FieldName = '�տ�˻���'
    end
    object WVEdit8: TWVEdit
      Left = 300
      Top = 53
      Width = 100
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 7
      Text = '<�տ��˿����к�>'
      WorkView = WorkView
      FieldName = '�տ��˿����к�'
    end
    object cbbNetInfo: TWVComboBox
      Left = 499
      Top = 53
      Width = 102
      Height = 18
      Style = csOwnerDrawFixed
      Color = clInfoBk
      DropDownCount = 20
      ItemHeight = 12
      TabOrder = 8
      WorkView = WorkView
      FieldName = '����״̬'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*251'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 97
    Width = 700
    Height = 362
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 362
      Columns = <
        item
          Expanded = False
          FieldName = 'spager'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������κ�'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ˮ��'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ί������'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�û����'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�տ�̻���'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�տ�˻�'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbankname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�տ�˻���'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�տ��˿����к�'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ˮ��'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstat_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ע'
          Width = 90
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
        Name = '�������κ�'
        Caption = '�������κ�'
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
        Name = '������ˮ��'
        Caption = '������ˮ��'
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
        Name = 'ί������'
        Caption = 'ί������'
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
        Name = '�̻���'
        Caption = '�̻���'
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
        Name = '�տ�˻�'
        Caption = '�տ�˻�'
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
        Name = '�տ�˻���'
        Caption = '�տ�˻���'
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
        Name = '�տ��˿����к�'
        Caption = '�տ��˿����к�'
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
        Name = '����״̬'
        Caption = '����״̬'
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
        MonitorValueChangedFields = 
          '|�������κ�|������ˮ��|ί������|��������|�̻���|�տ�˻�|�տ�' +
          '���˻���|�տ��˿����к�|����״̬|'
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '������ϸ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�������κ�'
        FieldName = '�������κ�'
      end
      item
        ParamName = '������ˮ��'
        FieldName = '������ˮ��'
      end
      item
        ParamName = 'ί������'
        FieldName = 'ί������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '�տ�˻�'
        FieldName = '�տ�˻�'
      end
      item
        ParamName = '�տ�˻���'
        FieldName = '�տ�˻���'
      end
      item
        ParamName = '�տ��˿����к�'
        FieldName = '�տ��˿����к�'
      end
      item
        ParamName = '����״̬'
        FieldName = '����״̬'
      end>
    Left = 136
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 168
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 200
    Top = 256
  end
end
