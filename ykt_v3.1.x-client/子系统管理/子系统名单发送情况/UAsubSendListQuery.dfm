inherited faqhsubSendListQuery: TfaqhsubSendListQuery
  Width = 776
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 776
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 599
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 686
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 776
    inherited Image1: TImage
      Width = 776
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 776
    Height = 30
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 14
      Top = 10
      Width = 36
      Height = 12
      Caption = '��ϵͳ'
    end
    object Label2: TLabel
      Left = 178
      Top = 10
      Width = 48
      Height = 12
      Caption = '���׿���'
    end
    object Label3: TLabel
      Left = 318
      Top = 10
      Width = 36
      Height = 12
      Caption = 'ѧ����'
    end
    object Label4: TLabel
      Left = 458
      Top = 10
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label5: TLabel
      Left = 634
      Top = 10
      Width = 24
      Height = 12
      Caption = '״̬'
    end
    object WVEdit2: TWVEdit
      Left = 228
      Top = 5
      Width = 77
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<���׿���>'
      WorkView = WorkView
      FieldName = '���׿���'
    end
    object WVEdit3: TWVEdit
      Left = 356
      Top = 5
      Width = 93
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<ѧ����>'
      WorkView = WorkView
      FieldName = 'ѧ����'
    end
    object WVComboBox1: TWVComboBox
      Left = 56
      Top = 5
      Width = 113
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = '��ϵͳ'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-47'
    end
    object WVComboBox2: TWVComboBox
      Left = 512
      Top = 5
      Width = 113
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '��������'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*73'
    end
    object WVComboBox3: TWVComboBox
      Left = 664
      Top = 5
      Width = 81
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 4
      WorkView = WorkView
      FieldName = '״̬'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*68'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 48
    Width = 776
    Height = 411
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 776
      Height = 411
      Columns = <
        item
          Expanded = False
          FieldName = 'Lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ϵͳ��ʶ'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ϵͳ����'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���׿���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ѧ����'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�汾'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '״̬'
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
        Name = '��ϵͳ'
        Caption = '��ϵͳ'
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
        Name = '���׿���'
        Caption = '���׿���'
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
        Name = '״̬'
        Caption = '״̬'
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
        MonitorValueChangedFields = '|��ϵͳ|���׿���|ѧ����|ģ������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '��ϵͳ�����������'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ϵͳ'
        FieldName = '��ϵͳ'
      end
      item
        ParamName = '���׿���'
        FieldName = '���׿���'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '״̬'
        FieldName = '״̬'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol2'
        DataPresentType = 'idobjects'
        DataPresentParam = '73'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '68'
      end>
    Left = 168
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 208
    Top = 256
  end
end
