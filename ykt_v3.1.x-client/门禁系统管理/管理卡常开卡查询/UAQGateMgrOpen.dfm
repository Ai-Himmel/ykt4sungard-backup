inherited faqhQGateMgrOpen: TfaqhQGateMgrOpen
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
    TabOrder = 1
    object Label1: TLabel
      Left = 30
      Top = 9
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label4: TLabel
      Left = 206
      Top = 9
      Width = 36
      Height = 12
      Caption = '�豸��'
    end
    object Label7: TLabel
      Left = 18
      Top = 33
      Width = 36
      Height = 12
      Caption = '����;'
    end
    object Label13: TLabel
      Left = 194
      Top = 33
      Width = 48
      Height = 12
      Caption = '�������'
    end
    object edtCardNo: TWVEdit
      Left = 60
      Top = 5
      Width = 117
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 0
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object edtDevNo: TWVEdit
      Left = 244
      Top = 5
      Width = 117
      Height = 20
      Color = clWhite
      MaxLength = 22
      ReadOnly = False
      TabOrder = 1
      Text = '<�豸��>'
      WorkView = WorkView
      FieldName = '�豸��'
    end
    object cbbUes: TWVComboBox
      Left = 60
      Top = 29
      Width = 117
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '����;'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*85'
    end
    object cbbOper: TWVComboBox
      Left = 244
      Top = 28
      Width = 117
      Height = 18
      Style = csOwnerDrawFixed
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      WorkView = WorkView
      FieldName = '�������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*44'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 73
    Width = 700
    Height = 380
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 380
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Caption = '����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Caption = '����;'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Caption = '��ɾ��־'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Caption = '�豸��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Caption = '�ͻ���'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ����'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstation0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Caption = '����ʱ��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail'
          PickList.Strings = ()
          Title.Caption = '�ͻ�����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Caption = 'ѧ/����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Caption = '����ȫ��'
          Width = 120
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
        Name = '����'
        Caption = '����'
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
        Name = '�豸��'
        Caption = '�豸��'
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
        Name = '����;'
        Caption = '����;'
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
        Name = '�������'
        Caption = '�������'
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
    ID = '������������ѯ'
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
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '����;'
        FieldName = '����;'
      end
      item
        ParamName = '�豸��'
        FieldName = '�豸��'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol1'
        DataPresentType = 'idobjects'
        DataPresentParam = '85'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'idobjects'
        DataPresentParam = '44'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '-34'
      end>
    Left = 160
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 192
    Top = 256
  end
end
