inherited faqhQueryBusinessByOther: TfaqhQueryBusinessByOther
  Width = 680
  Height = 463
  inherited UIPanel1: TUIPanel
    Top = 433
    Width = 680
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 503
    end
    inherited btnPrint: TBitBtn
      Left = 590
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 680
    inherited Image1: TImage
      Width = 680
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 680
    Height = 87
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label2: TLabel
      Left = 70
      Top = 9
      Width = 36
      Height = 12
      Caption = '�̻���'
    end
    object Label3: TLabel
      Left = 265
      Top = 9
      Width = 60
      Height = 12
      Caption = '�ϼ��̻���'
    end
    object Label4: TLabel
      Left = 490
      Top = 9
      Width = 48
      Height = 12
      Caption = '�̻�����'
    end
    object Label5: TLabel
      Left = 58
      Top = 38
      Width = 48
      Height = 12
      Caption = '�̻�����'
    end
    object Label6: TLabel
      Left = 490
      Top = 37
      Width = 48
      Height = 12
      Caption = 'ĩ���̻�'
      Visible = False
    end
    object Label9: TLabel
      Left = 70
      Top = 66
      Width = 36
      Height = 12
      Caption = '��ϵ��'
    end
    object Label11: TLabel
      Left = 469
      Top = 217
      Width = 60
      Height = 12
      Caption = '����������'
      Visible = False
    end
    object Label12: TLabel
      Left = 241
      Top = 62
      Width = 84
      Height = 12
      Caption = '��ϵ��֤������'
    end
    object Label14: TLabel
      Left = 468
      Top = 249
      Width = 48
      Height = 12
      Caption = '��ϵ��ַ'
      Visible = False
    end
    object Label20: TLabel
      Left = 88
      Top = 225
      Width = 24
      Height = 12
      Caption = '��ע'
      Visible = False
    end
    object Label1: TLabel
      Left = 4
      Top = 248
      Width = 108
      Height = 12
      Caption = '�̻�����Ѽ��㷽ʽ'
      Visible = False
    end
    object Label17: TLabel
      Left = 236
      Top = 248
      Width = 96
      Height = 12
      Caption = '�̻�˰�Ѽ��㷽ʽ'
      Visible = False
    end
    object Label18: TLabel
      Left = 277
      Top = 36
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object WVEdit2: TWVEdit
      Left = 116
      Top = 5
      Width = 121
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<�̻���ʶ>'
      OnChange = WVEdit2Change
      WorkView = WorkView
      FieldName = '�̻���ʶ'
    end
    object WVEdit3: TWVEdit
      Left = 332
      Top = 5
      Width = 121
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<���̻���ʶ>'
      OnChange = WVEdit3Change
      WorkView = WorkView
      FieldName = '���̻���ʶ'
    end
    object WVEdit4: TWVEdit
      Left = 552
      Top = 5
      Width = 105
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 2
      Text = '<�̻�����>'
      WorkView = WorkView
      FieldName = '�̻�����'
    end
    object WVEdit9: TWVEdit
      Left = 116
      Top = 61
      Width = 121
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 7
      Text = '<����������>'
      WorkView = WorkView
      FieldName = '����������'
    end
    object WVEdit12: TWVEdit
      Left = 332
      Top = 57
      Width = 121
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 6
      Text = '<���������֤��>'
      WorkView = WorkView
      FieldName = '���������֤��'
    end
    object WVEdit14: TWVEdit
      Left = 540
      Top = 245
      Width = 100
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 12
      Text = '<��ϵ��ַ>'
      Visible = False
      WorkView = WorkView
      FieldName = '��ϵ��ַ'
    end
    object WVEdit20: TWVEdit
      Left = 136
      Top = 221
      Width = 297
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 9
      Text = '<��ע>'
      Visible = False
      WorkView = WorkView
      FieldName = '��ע'
    end
    object WVComboBox1: TWVComboBox
      Left = 116
      Top = 33
      Width = 121
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '�̻����'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*14'
    end
    object WVComboBox2: TWVComboBox
      Left = 552
      Top = 31
      Width = 105
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 4
      Visible = False
      WorkView = WorkView
      FieldName = '�Ƿ�ΪҶ�ڵ�'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*2'
    end
    object WVComboBox5: TWVComboBox
      Left = 548
      Top = 213
      Width = 101
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 8
      Visible = False
      WorkView = WorkView
      FieldName = '����������'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*34'
    end
    object WVEdit1: TWVEdit
      Left = 136
      Top = 244
      Width = 89
      Height = 20
      ReadOnly = False
      TabOrder = 10
      Text = 'WVEdit1'
      Visible = False
    end
    object WVEdit6: TWVEdit
      Left = 348
      Top = 244
      Width = 97
      Height = 20
      ReadOnly = False
      TabOrder = 11
      Text = 'WVEdit6'
      Visible = False
    end
    object WVComboBox6: TWVComboBox
      Left = 332
      Top = 31
      Width = 121
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '�Ƿ�Ϊ��������'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*2'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 105
    Width = 680
    Height = 328
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 680
      Height = 328
      Columns = <
        item
          Expanded = False
          FieldName = 'sbranch_code0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�̻���'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�̻��ʺ�'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�̻�����'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol7'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�̻�����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smain_flag2'
          PickList.Strings = ()
          Title.Caption = 'ĩ���̻�'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'smain_flag'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�մ���'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smarket_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ӷ������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'drate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ӷ�����(%)'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'drate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ɱ���(%)'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Caption = '�ʻ����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���д���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_acc2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����ʺ�'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbankname2'
          PickList.Strings = ()
          Title.Caption = '�����ʻ���'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ϼ��̻�'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ϼ��̻���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Caption = '��ϵ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smarket_code2'
          PickList.Strings = ()
          Title.Caption = '֤������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail2'
          PickList.Strings = ()
          Title.Caption = '֤������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone2'
          PickList.Strings = ()
          Title.Caption = '�ֻ�'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail'
          PickList.Strings = ()
          Title.Caption = '��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scusttypes'
          PickList.Strings = ()
          Title.Caption = '��ַ'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spost_code'
          PickList.Strings = ()
          Title.Caption = '�ʱ�'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no'
          PickList.Strings = ()
          Title.Caption = '����'
          Width = 60
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
        Name = '������־'
        Caption = '������־'
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
        Name = '�̻���ʶ'
        Caption = '�̻���ʶ'
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
        DataField = 'lvol5'
      end
      item
        Name = '���̻���ʶ'
        Caption = '���̻���ʶ'
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
        DataField = 'lvol1'
      end
      item
        Name = '�̻�����'
        Caption = '�̻�����'
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
        DataField = 'scard1'
      end
      item
        Name = '�̻����'
        Caption = '�̻����'
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
        DataField = 'sstat_type'
      end
      item
        Name = '�Ƿ�Ϊ��������'
        Caption = '�Ƿ�Ϊ��������'
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
        Name = '�Ƿ�ΪҶ�ڵ�'
        Caption = '�Ƿ�ΪҶ�ڵ�'
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
        DataField = 'smarket_code2'
      end
      item
        Name = '����������'
        Caption = '����������'
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
        DataField = 'sname'
      end
      item
        Name = '���������֤��'
        Caption = '���������֤��'
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
        DataField = 'sname2'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|�̻���ʶ|�ͻ���|���̻���ʶ|�̻�����|�̻����|�Ƿ�ΪҶ�ڵ�|�̻�' +
          '״̬|������Ա����|����������|�������Ա�|�������������|��������' +
          '��֤��|��ϵ�绰|��ϵ��ַ|�Ƿ���ȡ�����|��ȡ���ѹ���ѱ���|�̻�' +
          '����Ѽ��㷽ʽ|�̻�˰�Ѽ��㷽ʽ|ע��ʱ��|��ע|'
      end>
    Left = 180
    Top = 359
  end
  inherited MainRequest: TWVRequest
    ID = '�̻���Ϣ��������ѯ'
    Bindings = <
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
        ParamName = '�̻���ʶ'
        FieldName = '�̻���ʶ'
      end
      item
        ParamName = '���̻���ʶ'
        FieldName = '���̻���ʶ'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '�̻����'
        FieldName = '�̻����'
      end
      item
        ParamName = '�Ƿ�Ϊ��������'
        FieldName = '�Ƿ�Ϊ��������'
      end
      item
        ParamName = '�Ƿ�ΪҶ�ڵ�'
        FieldName = '�Ƿ�ΪҶ�ڵ�'
      end
      item
        ParamName = '����������'
        FieldName = '����������'
      end
      item
        ParamName = '���������֤��'
        FieldName = '���������֤��'
      end>
    Left = 216
    Top = 360
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'lvol7'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '14'
      end
      item
        FieldName = 'smain_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '91'
      end
      item
        FieldName = 'scert_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'smarket_code2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '87'
      end
      item
        FieldName = 'scust_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'sbank_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '110'
      end>
    Left = 248
    Top = 360
  end
  inherited DataSource: TDataSource
    Left = 280
    Top = 360
  end
end
