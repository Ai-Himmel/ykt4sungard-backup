inherited faqhQueryEquipmentByOther: TfaqhQueryEquipmentByOther
  Width = 644
  Height = 489
  object Panel1: TPanel [0]
    Left = 0
    Top = 18
    Width = 644
    Height = 111
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 26
      Top = 9
      Width = 48
      Height = 12
      Caption = '�豸����'
    end
    object Label3: TLabel
      Left = 432
      Top = 9
      Width = 60
      Height = 12
      Caption = '�豸����ID'
    end
    object Label4: TLabel
      Left = 50
      Top = 35
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label5: TLabel
      Left = 242
      Top = 11
      Width = 48
      Height = 12
      Caption = '�豸����'
    end
    object Label6: TLabel
      Left = 408
      Top = 35
      Width = 84
      Height = 12
      Caption = '�ϼ��豸����ID'
    end
    object Label7: TLabel
      Left = 402
      Top = 87
      Width = 48
      Height = 12
      Caption = '�豸״̬'
      Visible = False
    end
    object Label8: TLabel
      Left = 242
      Top = 35
      Width = 48
      Height = 12
      Caption = '�豸����'
    end
    object Label9: TLabel
      Left = 14
      Top = 62
      Width = 60
      Height = 12
      Caption = '������ϵͳ'
    end
    object Label10: TLabel
      Left = 242
      Top = 61
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label2: TLabel
      Left = 432
      Top = 61
      Width = 60
      Height = 12
      Caption = '�������κ�'
    end
    object Label11: TLabel
      Left = 26
      Top = 86
      Width = 48
      Height = 12
      Caption = '�豸��ʶ'
    end
    object WVEdit1: TWVEdit
      Left = 84
      Top = 5
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<�豸����>'
      WorkView = WorkView
      FieldName = '�豸����'
    end
    object WVEdit3: TWVEdit
      Left = 500
      Top = 5
      Width = 100
      Height = 20
      CharCase = ecUpperCase
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<�豸����ID>'
      WorkView = WorkView
      FieldName = '�豸����ID'
    end
    object WVEdit6: TWVEdit
      Left = 500
      Top = 31
      Width = 100
      Height = 20
      CharCase = ecUpperCase
      Color = clWhite
      ReadOnly = False
      TabOrder = 5
      Text = '<�ϼ��豸����ID>'
      WorkView = WorkView
      FieldName = '�ϼ��豸����ID'
    end
    object WVComboBox1: TWVComboBox
      Left = 468
      Top = 83
      Width = 112
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 10
      Visible = False
      WorkView = WorkView
      FieldName = '�豸״̬'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*5'
    end
    object WVComboBox2: TWVComboBox
      Left = 300
      Top = 57
      Width = 105
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView
      FieldName = '�豸��������'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-28'
    end
    object WVComboBox3: TWVComboBox
      Left = 84
      Top = 58
      Width = 112
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView
      FieldName = '������ϵͳ'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-32'
    end
    object WVComboBox5: TWVComboBox
      Left = 300
      Top = 31
      Width = 105
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 4
      WorkView = WorkView
      FieldName = '�豸�����ͺ�'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*-35'
    end
    object WVComboBox6: TWVComboBox
      Left = 300
      Top = 5
      Width = 105
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 1
      WorkView = WorkView
      FieldName = '���ʹ���'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*47'
    end
    object edtMachineNo: TWVEdit
      Left = 84
      Top = 32
      Width = 112
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 3
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object WVEdit2: TWVEdit
      Left = 500
      Top = 57
      Width = 100
      Height = 20
      CharCase = ecUpperCase
      Color = clWhite
      ReadOnly = False
      TabOrder = 8
      Text = '<�������κ�>'
      WorkView = WorkView
      FieldName = '�������κ�'
    end
    object WVEdit4: TWVEdit
      Left = 84
      Top = 83
      Width = 112
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 9
      Text = '<�豸��ʶ>'
      WorkView = WorkView
      FieldName = '�豸��ʶ'
    end
  end
  inherited UIPnlQueryCount: TUIPanel [1]
    Width = 644
    inherited Image1: TImage
      Width = 644
    end
    inherited LabRecordCount: TLabel
      Font.Color = clBlack
    end
  end
  inherited UIPanel1: TUIPanel [2]
    Top = 459
    Width = 644
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 467
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 554
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 129
    Width = 644
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 644
      Columns = <
        item
          Expanded = False
          FieldName = 'lserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸��ʶ'
          Width = 68
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸����'
          Width = 87
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸����ID'
          Width = 71
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���ʹ���'
          Width = 72
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������˿�����'
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt6'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ϼ��豸'
          Width = 68
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scurrency_type'
          PickList.Strings = ()
          Title.Caption = '��Ƭ�ṹ'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������˿ں�'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸״̬'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_code2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ͨѶ�˿ں�'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstation0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'IP��ַ'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ϵͳ'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ssectypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ע'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'damt5'
          PickList.Strings = ()
          Title.Caption = '�豸��;'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt4'
          PickList.Strings = ()
          Title.Caption = '�Ƿ�֧�ֿ�Ŀ�շ�'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Caption = 'ͨѶ���'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������κ�'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������汾'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Caption = '��ע'
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
        Name = '�豸����'
        Caption = '�豸����'
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
        DataField = 'scert_no'
      end
      item
        Name = '�����豸ע���'
        Caption = '�����豸ע���'
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
        DataField = 'sbank_pwd'
      end
      item
        Name = '�豸����ID'
        Caption = '�豸����ID'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'sbank_pwd2'
      end
      item
        Name = '����'
        Caption = '����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
        DataField = 'lvol1'
      end
      item
        Name = '���ʹ���'
        Caption = '���ʹ���'
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
        DataField = 'sbank_code'
      end
      item
        Name = '�ϼ��豸����ID'
        Caption = '�ϼ��豸����ID'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'sdate1'
      end
      item
        Name = '�豸״̬'
        Caption = '�豸״̬'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol4'
      end
      item
        Name = '�豸�����ͺ�'
        Caption = '�豸�����ͺ�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lbank_acc_type'
      end
      item
        Name = '������ϵͳ'
        Caption = '������ϵͳ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial0'
      end
      item
        Name = '�豸��������'
        Caption = '�豸��������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial1'
      end
      item
        Name = '�豸��ʶ'
        Caption = '�豸��ʶ'
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
        DataField = 'sserial0'
      end
      item
        Name = '�������κ�'
        Caption = '�������κ�'
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
          '|�豸����|�����豸ע���|�豸���|����|���ʹ���|�ϼ��豸���|�豸' +
          '״̬|�豸�����ͺ�|������ϵͳ|�豸��������|������Ա����|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 76
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '�豸�ǹؼ��ֲ�ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�����豸ע���'
        FieldName = '�����豸ע���'
      end
      item
        ParamName = '�豸����ID'
        FieldName = '�豸����ID'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '���ʹ���'
        FieldName = '���ʹ���'
      end
      item
        ParamName = '�ϼ��豸����ID'
        FieldName = '�ϼ��豸����ID'
      end
      item
        ParamName = '�豸״̬'
        FieldName = '�豸״̬'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = '�豸�����ͺ�'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = '������ϵͳ'
      end
      item
        ParamName = '�豸��������'
        FieldName = '�豸��������'
      end
      item
        ParamName = '�豸��ʶ'
        FieldName = '�豸��ʶ'
      end
      item
        ParamName = '�������κ�'
        FieldName = '�������κ�'
      end>
    Left = 136
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lserial1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-28'
      end
      item
        FieldName = 'sbank_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '47'
      end
      item
        FieldName = 'damt6'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-31'
      end
      item
        FieldName = 'scurrency_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '48'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '5'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-35'
      end
      item
        FieldName = 'lserial0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-32'
      end
      item
        FieldName = 'damt5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '81'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '50'
      end>
    Left = 184
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 232
    Top = 256
  end
end
