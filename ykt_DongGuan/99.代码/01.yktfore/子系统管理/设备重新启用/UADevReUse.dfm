inherited faqhDevReUse: TfaqhDevReUse
  Width = 700
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 700
    inherited btnQuery: TBitBtn
      Left = 435
    end
    inherited btnPrint: TBitBtn
      Left = 610
    end
    object btnReUse: TBitBtn
      Left = 523
      Top = 3
      Width = 79
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '��������'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnReUseClick
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
    Height = 87
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label2: TLabel
      Left = 42
      Top = 10
      Width = 48
      Height = 12
      Caption = '�豸���'
    end
    object Label5: TLabel
      Left = 30
      Top = 34
      Width = 60
      Height = 12
      Caption = '�ն����к�'
    end
    object Label8: TLabel
      Left = 42
      Top = 58
      Width = 48
      Height = 12
      Caption = '�豸����'
    end
    object Label3: TLabel
      Left = 236
      Top = 10
      Width = 60
      Height = 12
      Caption = '�����̻���'
    end
    object Label6: TLabel
      Left = 248
      Top = 34
      Width = 48
      Height = 12
      Caption = '�豸�ͺ�'
    end
    object Label10: TLabel
      Left = 248
      Top = 58
      Width = 48
      Height = 12
      Caption = '�豸״̬'
    end
    object Label9: TLabel
      Left = 446
      Top = 58
      Width = 48
      Height = 12
      Caption = '�豸��;'
    end
    object Label7: TLabel
      Left = 446
      Top = 34
      Width = 48
      Height = 12
      Caption = '�豸����'
    end
    object Label4: TLabel
      Left = 434
      Top = 10
      Width = 60
      Height = 12
      Caption = '�豸�ն˺�'
    end
    object WVEdit8: TWVEdit
      Left = 100
      Top = 54
      Width = 115
      Height = 20
      ReadOnly = False
      TabOrder = 0
      Text = '<��ѯ.�豸����>'
      WorkView = WorkView1
      FieldName = '��ѯ.�豸����'
    end
    object WVEdit5: TWVEdit
      Left = 100
      Top = 30
      Width = 115
      Height = 20
      ReadOnly = False
      TabOrder = 1
      Text = '<��ѯ.�ն����к�>'
      WorkView = WorkView1
      FieldName = '��ѯ.�ն����к�'
    end
    object edtPosIdQ: TWVEdit
      Left = 100
      Top = 6
      Width = 115
      Height = 20
      ReadOnly = False
      TabOrder = 2
      Text = '<��ѯ.�豸���>'
      WorkView = WorkView1
      FieldName = '��ѯ.�豸���'
    end
    object edtBusiIdQ: TWVEdit
      Left = 300
      Top = 6
      Width = 121
      Height = 20
      MaxLength = 22
      ReadOnly = False
      TabOrder = 3
      Text = '<��ѯ.�����̻���>'
      WorkView = WorkView1
      FieldName = '��ѯ.�����̻���'
    end
    object WVComboBox3: TWVComboBox
      Left = 300
      Top = 30
      Width = 121
      Height = 20
      Style = csDropDownList
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 4
      WorkView = WorkView1
      FieldName = '��ѯ.�豸�ͺ�'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*223'
    end
    object WVComboBox1: TWVComboBox
      Left = 300
      Top = 54
      Width = 121
      Height = 20
      Style = csDropDownList
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView1
      FieldName = '��ѯ.�豸״̬'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*220'
    end
    object WVEdit4: TWVEdit
      Left = 500
      Top = 6
      Width = 121
      Height = 20
      ReadOnly = False
      TabOrder = 6
      Text = '<��ѯ.�豸�ն˺�>'
      WorkView = WorkView1
      FieldName = '��ѯ.�豸�ն˺�'
    end
    object WVComboBox2: TWVComboBox
      Left = 500
      Top = 30
      Width = 121
      Height = 20
      Style = csDropDownList
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView1
      FieldName = '��ѯ.�豸����'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*221'
    end
    object WVComboBox4: TWVComboBox
      Left = 500
      Top = 54
      Width = 121
      Height = 20
      Style = csDropDownList
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 8
      WorkView = WorkView1
      FieldName = '��ѯ.��;'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*222'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 105
    Width = 700
    Height = 354
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 354
      Columns = <
        item
          Expanded = False
          FieldName = 'sstock_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸���'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����̻���'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸�ն˺�'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ն����к�'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸�ͺ�'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spost_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbankname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸����'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��;'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸״̬'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ע������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ɾ������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ʱ��'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ע'
          Width = 70
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
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�豸���'
        Caption = '�豸���'
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
        Name = '�豸״̬'
        Caption = '�豸״̬'
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
    InvalidColor = clWhite
    Left = 140
    Top = 239
  end
  inherited MainRequest: TWVRequest
    ID = '�豸ά��'
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
        ParamName = '�豸���'
        FieldName = '�豸���'
      end
      item
        ParamName = '�豸״̬'
        FieldName = '�豸״̬'
      end>
    Left = 176
    Top = 240
  end
  inherited WVDBBinder: TWVDBBinder
    WorkView = WorkView1
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sstock_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '229'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'idobjects'
        DataPresentParam = '223'
      end
      item
        FieldName = 'spost_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '221'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'idobjects'
        DataPresentParam = '222'
      end
      item
        FieldName = 'sstatus0'
        DataPresentType = 'idobjects'
        DataPresentParam = '220'
      end>
    Left = 208
    Top = 200
  end
  inherited DataSource: TDataSource
    Left = 240
    Top = 200
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
        Name = '��ѯ�����'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
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
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sstat_type'
      end
      item
        Name = '��ѯ.�豸���'
        Caption = '��ѯ.�豸���'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�����̻���'
        Caption = '��ѯ.�����̻���'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�豸�ն˺�'
        Caption = '��ѯ.�豸�ն˺�'
        FieldType = wftUndefined
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
        Name = '��ѯ.�ն����к�'
        Caption = '��ѯ.�ն����к�'
        FieldType = wftUndefined
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
        Name = '��ѯ.�豸�ͺ�'
        Caption = '��ѯ.�豸�ͺ�'
        FieldType = wftUndefined
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
        Name = '��ѯ.�豸����'
        Caption = '��ѯ.�豸����'
        FieldType = wftUndefined
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
        Name = '��ѯ.�豸����'
        Caption = '��ѯ.�豸����'
        FieldType = wftUndefined
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
        Name = '��ѯ.��;'
        Caption = '��ѯ.��;'
        FieldType = wftUndefined
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
        Name = '��ѯ.�豸״̬'
        Caption = '��ѯ.�豸״̬'
        FieldType = wftUndefined
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
    WorkProcesses = <>
    FieldsMonitors = <>
    InvalidColor = clWindow
    Left = 144
    Top = 200
  end
  object QueryRequest: TWVRequest
    WorkView = WorkView1
    ID = 'POS��Ϣά����ѯ'
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
        ParamName = '�豸���'
        FieldName = '��ѯ.�豸���'
      end
      item
        ParamName = '�����̻���'
        FieldName = '��ѯ.�����̻���'
      end
      item
        ParamName = '�豸�ն˺�'
        FieldName = '��ѯ.�豸�ն˺�'
      end
      item
        ParamName = '�ն����к�'
        FieldName = '��ѯ.�ն����к�'
      end
      item
        ParamName = '�豸�ͺ�'
        FieldName = '��ѯ.�豸�ͺ�'
      end
      item
        ParamName = '�豸����'
        FieldName = '��ѯ.�豸����'
      end
      item
        ParamName = '�豸����'
        FieldName = '��ѯ.�豸����'
      end
      item
        ParamName = '��;'
        FieldName = '��ѯ.��;'
      end
      item
        ParamName = '�豸״̬'
        FieldName = '��ѯ.�豸״̬'
      end>
    Left = 176
    Top = 200
  end
end
