inherited faqhGateListQuery: TfaqhGateListQuery
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
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 610
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
    Height = 121
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object Label1: TLabel
      Left = 30
      Top = 9
      Width = 60
      Height = 12
      Caption = '�Ž�������'
    end
    object Label2: TLabel
      Left = 242
      Top = 9
      Width = 48
      Height = 12
      Caption = '�Ž����'
    end
    object Label3: TLabel
      Left = 470
      Top = 9
      Width = 42
      Height = 12
      Caption = 'ѧ/����'
    end
    object Label4: TLabel
      Left = 66
      Top = 33
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label5: TLabel
      Left = 266
      Top = 33
      Width = 24
      Height = 12
      Caption = 'Ժϵ'
    end
    object Label6: TLabel
      Left = 478
      Top = 33
      Width = 36
      Height = 12
      Caption = '�ͻ���'
    end
    object Label7: TLabel
      Left = 42
      Top = 57
      Width = 48
      Height = 12
      Caption = '�ͻ����'
    end
    object Label8: TLabel
      Left = 242
      Top = 57
      Width = 48
      Height = 12
      Caption = '�շ����'
    end
    object Label9: TLabel
      Left = 466
      Top = 81
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label10: TLabel
      Left = 66
      Top = 81
      Width = 24
      Height = 12
      Caption = '�༶'
    end
    object Label11: TLabel
      Left = 266
      Top = 81
      Width = 24
      Height = 12
      Caption = 'רҵ'
    end
    object Label12: TLabel
      Left = 466
      Top = 57
      Width = 48
      Height = 12
      Caption = '�´�״̬'
    end
    object Label13: TLabel
      Left = 42
      Top = 105
      Width = 48
      Height = 12
      Caption = '��ɾ��־'
    end
    object WVEdit1: TWVEdit
      Left = 100
      Top = 5
      Width = 117
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 0
      Text = '<�Ž�������>'
      WorkView = WorkView
      FieldName = '�Ž�������'
    end
    object WVEdit2: TWVEdit
      Left = 300
      Top = 5
      Width = 141
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<�Ž��豸���>'
      WorkView = WorkView
      FieldName = '�Ž��豸���'
    end
    object WVEdit3: TWVEdit
      Left = 524
      Top = 5
      Width = 139
      Height = 20
      CharCase = ecUpperCase
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<ѧ����>'
      WorkView = WorkView
      FieldName = 'ѧ����'
    end
    object WVEdit4: TWVEdit
      Left = 100
      Top = 29
      Width = 117
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 4
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object WVEdit6: TWVEdit
      Left = 524
      Top = 29
      Width = 139
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 5
      Text = '<�ͻ���>'
      WorkView = WorkView
      FieldName = '�ͻ���'
    end
    object WVEdit10: TWVEdit
      Left = 100
      Top = 77
      Width = 117
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 9
      Text = '<�༶>'
      WorkView = WorkView
      FieldName = '�༶'
    end
    object cbbDep: TWVComboBox
      Left = 300
      Top = 28
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = 'Ժϵ����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-22'
    end
    object cbbFeeType: TWVComboBox
      Left = 300
      Top = 53
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView
      FieldName = '�շ�����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-43'
    end
    object cbbCustType: TWVComboBox
      Left = 100
      Top = 53
      Width = 117
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView
      FieldName = '�շ�����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-34'
    end
    object WVComboBox6: TWVComboBox
      Left = 300
      Top = 78
      Width = 141
      Height = 18
      Style = csOwnerDrawFixed
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 11
      WorkView = WorkView
      FieldName = 'רҵ����'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-23'
    end
    object WVComboBox1: TWVComboBox
      Left = 524
      Top = 77
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 10
      WorkView = WorkView
      FieldName = '��������'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*133'
    end
    object WVComboBox2: TWVComboBox
      Left = 524
      Top = 53
      Width = 141
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 8
      WorkView = WorkView
      FieldName = '״̬'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*84'
    end
    object WVComboBox3: TWVComboBox
      Left = 100
      Top = 100
      Width = 117
      Height = 18
      Style = csOwnerDrawFixed
      Color = clWhite
      ItemHeight = 12
      TabOrder = 12
      FieldName = '��ɾ��־'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*44'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 139
    Width = 700
    Height = 314
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 314
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = '�Ž����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail2'
          PickList.Strings = ()
          Title.Caption = '�Ž�������'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Caption = 'ѧ/����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail'
          PickList.Strings = ()
          Title.Caption = '����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Caption = '�ͻ���'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol8'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ɾ��־'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol9'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ʱ����'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Caption = '�´�״̬'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Caption = '�ͻ����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Caption = '�շ����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstat_type'
          PickList.Strings = ()
          Title.Caption = '��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Caption = '��״̬'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Caption = '���κ�'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sstation0'
          PickList.Strings = ()
          Title.Caption = 'Ժϵ'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstation1'
          PickList.Strings = ()
          Title.Caption = 'רҵ'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Caption = '�༶'
          Width = 80
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
        Name = '�Ž�������'
        Caption = '�Ž�������'
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
        Name = '�Ž��豸���'
        Caption = '�Ž��豸���'
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
        Name = 'Ժϵ����'
        Caption = 'Ժϵ����'
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
        Name = '�ͻ�����'
        Caption = '�ͻ�����'
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
        Name = '�շ�����'
        Caption = '�շ�����'
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
        Name = '�༶'
        Caption = '�༶'
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
        Name = 'רҵ����'
        Caption = 'רҵ����'
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
        Name = '״̬'
        Caption = '״̬'
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
        Name = '����Ա'
        Caption = '����Ա'
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
        Name = '��ɾ��־'
        Caption = '��ɾ��־'
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
        MonitorValueChangedFields = 
          '|�Ž�������|�Ž��豸���|ѧ����|����|Ժϵ����|�ͻ���|�ͻ�����|��' +
          '������|ҽԺ�շѷ�ʽ|�༶|רҵ����|״̬|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '�Ž���Ա������ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�Ž�������'
        FieldName = '�Ž�������'
      end
      item
        ParamName = '�Ž��豸���'
        FieldName = '�Ž��豸���'
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
        ParamName = 'Ժϵ����'
        FieldName = 'Ժϵ����'
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
        ParamName = '�շ�����'
        FieldName = '�շ�����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�༶'
        FieldName = '�༶'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'רҵ����'
      end
      item
        ParamName = '״̬'
        FieldName = '״̬'
      end
      item
        ParamName = '����Ա'
        FieldName = '����Ա'
      end
      item
        ParamName = '��ɾ��־'
        FieldName = '��ɾ��־'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '-34'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'idobjects'
        DataPresentParam = '-43'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '66'
      end
      item
        FieldName = 'sstation0'
        DataPresentType = 'idobjects'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'sstation1'
        DataPresentType = 'idobjects'
        DataPresentParam = '-23'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '84'
      end
      item
        FieldName = 'lvol8'
        DataPresentType = 'idobjects'
        DataPresentParam = '44'
      end
      item
        FieldName = 'sstat_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '133'
      end>
    Left = 160
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 192
    Top = 256
  end
end
