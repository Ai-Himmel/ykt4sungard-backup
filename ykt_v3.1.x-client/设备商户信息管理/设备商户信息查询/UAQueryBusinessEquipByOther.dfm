inherited faqhQueryBusinessEquipByOther: TfaqhQueryBusinessEquipByOther
  Width = 801
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 453
    Width = 801
    Height = 36
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 621
      Top = 5
    end
    inherited btnPrint: TBitBtn
      Left = 711
      Top = 5
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 801
    inherited Image1: TImage
      Width = 801
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 801
    Height = 87
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 2
    object Label1: TLabel
      Left = 57
      Top = 13
      Width = 48
      Height = 12
      Caption = '�豸��ʶ'
    end
    object Label3: TLabel
      Left = 33
      Top = 39
      Width = 72
      Height = 12
      Caption = '�豸��������'
    end
    object Label5: TLabel
      Left = 33
      Top = 64
      Width = 72
      Height = 12
      Caption = 'ʹ�ý���ʱ��'
    end
    object Label6: TLabel
      Left = 414
      Top = 39
      Width = 72
      Height = 12
      Caption = '�豸ͣ������'
    end
    object Label10: TLabel
      Left = 274
      Top = 66
      Width = 114
      Height = 12
      Caption = '����6λ����(hhddss)'
    end
    object WVLabel1: TWVLabel
      Left = 272
      Top = 40
      Width = 126
      Height = 12
      Caption = '����8λ����(yyyymmdd)'
    end
    object WVLabel2: TWVLabel
      Left = 629
      Top = 40
      Width = 126
      Height = 12
      Caption = '����8λ����(yyyymmdd)'
    end
    object Label7: TLabel
      Left = 438
      Top = 12
      Width = 48
      Height = 12
      Caption = '�̻�����'
    end
    object Label2: TLabel
      Left = 438
      Top = 63
      Width = 48
      Height = 12
      Caption = 'ʹ��״̬'
    end
    object edtBDate: TWVEdit
      Left = 119
      Top = 34
      Width = 146
      Height = 20
      Color = clWhite
      MaxLength = 8
      ReadOnly = False
      TabOrder = 2
      Text = '<ʹ�ÿ�ʼ����>'
      WorkView = WorkView
      FieldName = 'ʹ�ÿ�ʼ����'
    end
    object edtETime: TWVEdit
      Left = 119
      Top = 58
      Width = 146
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 4
      Text = '<ʹ�ý���ʱ��>'
      WorkView = WorkView
      FieldName = 'ʹ�ý���ʱ��'
    end
    object edtEDate: TWVEdit
      Left = 500
      Top = 34
      Width = 122
      Height = 20
      Color = clWhite
      MaxLength = 8
      ReadOnly = False
      TabOrder = 3
      Text = '<ʹ�ý�������>'
      WorkView = WorkView
      FieldName = 'ʹ�ý�������'
    end
    object WVEdit1: TWVEdit
      Left = 500
      Top = 7
      Width = 122
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 0
      Text = '<�̻�����>'
      WorkView = WorkView
      FieldName = '�̻�����'
    end
    object WVComboBox2: TWVComboBox
      Left = 500
      Top = 58
      Width = 122
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = 'ʹ��״̬'
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '*115'
    end
    object edtId: TWVDigitalEdit
      Left = 119
      Top = 9
      Width = 146
      Height = 20
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 1
      TabStop = True
      Text = '0'
      WorkView = WorkView
      FieldName = '�豸��ʶ'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 105
    Width = 801
    Height = 348
    inherited Grid: TRzDBGrid
      Width = 801
      Height = 348
      Columns = <
        item
          Expanded = False
          FieldName = 'Lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸����'
          Width = 84
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�̻�����'
          Width = 93
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ʹ�ÿ�ʼʱ��'
          Width = 96
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ʹ�ý���ʱ��'
          Width = 88
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸��������'
          Width = 98
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸ͣ������'
          Width = 89
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ʹ��״̬'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ssectypes'
          PickList.Strings = ()
          Title.Caption = '��ע'
          Width = 100
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
        Name = '�豸��ʶ'
        Caption = '�豸��ʶ'
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
      end
      item
        Name = 'ʹ�ÿ�ʼ����'
        Caption = 'ʹ�ÿ�ʼ����'
        FieldType = wftUndefined
        DomainName = '����У��'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = 'ʹ�ý�������'
        Caption = 'ʹ�ý�������'
        FieldType = wftUndefined
        DomainName = '����У��'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
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
      end
      item
        Name = 'ʹ��״̬'
        Caption = 'ʹ��״̬'
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
        Name = 'ʹ�ý���ʱ��'
        Caption = 'ʹ�ý���ʱ��'
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
        Name = '�̻����'
        Caption = '�̻����'
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
        MonitorValueChangedFields = '|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 148
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '�豸�̻���Ϣ��������ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ʹ�ÿ�ʼ����'
        FieldName = 'ʹ�ÿ�ʼ����'
      end
      item
        ParamName = '�豸��ʶ'
        FieldName = '�豸��ʶ'
      end
      item
        ParamName = 'ʹ�ý�������'
        FieldName = 'ʹ�ý�������'
      end
      item
        ParamName = 'ʹ�ý���ʱ��'
        FieldName = 'ʹ�ý���ʱ��'
      end
      item
        ParamName = 'ʹ��״̬'
        FieldName = 'ʹ��״̬'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '�̻����'
        FieldName = '�̻����'
      end>
    Left = 184
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-31'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '115'
      end>
    Left = 220
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 264
    Top = 256
  end
end
