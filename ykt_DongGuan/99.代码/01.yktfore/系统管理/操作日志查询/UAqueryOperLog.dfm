inherited faqhqueryOperLog: TfaqhqueryOperLog
  Width = 755
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 755
    TabOrder = 3
    inherited btnQuery: TBitBtn
      Left = 578
      Enabled = False
    end
    inherited btnPrint: TBitBtn
      Left = 665
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 755
    TabOrder = 0
    inherited Image1: TImage
      Width = 755
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 755
    Height = 55
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 2
    object Label1: TLabel
      Left = 30
      Top = 9
      Width = 36
      Height = 12
      Caption = 'վ���'
    end
    object Label2: TLabel
      Left = 574
      Top = 9
      Width = 60
      Height = 12
      Caption = 'վ����ˮ��'
    end
    object Label3: TLabel
      Left = 406
      Top = 9
      Width = 36
      Height = 12
      Caption = '����Ա'
    end
    object Label4: TLabel
      Left = 18
      Top = 33
      Width = 48
      Height = 12
      Caption = '��ʼ����'
    end
    object Label5: TLabel
      Left = 406
      Top = 33
      Width = 36
      Height = 12
      Caption = '������'
    end
    object Label6: TLabel
      Left = 218
      Top = 9
      Width = 48
      Height = 12
      Caption = '��ˮ״̬'
    end
    object Label7: TLabel
      Left = 217
      Top = 34
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object edtBDate: TWVEdit
      Left = 76
      Top = 29
      Width = 121
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 5
      Text = '<��ʼ����>'
      WorkView = WorkView
      FieldName = '��ʼ����'
    end
    object WVComboBox6: TWVComboBox
      Left = 76
      Top = 5
      Width = 121
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView
      FieldName = 'վ���'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-33'
    end
    object WVComboBox1: TWVComboBox
      Left = 448
      Top = 5
      Width = 116
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      MaxLength = 8
      TabOrder = 2
      WorkView = WorkView
      FieldName = '����Ա'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-30'
    end
    object WVComboBox2: TWVComboBox
      Left = 448
      Top = 29
      Width = 281
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView
      FieldName = '������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-38'
    end
    object WVComboBox3: TWVComboBox
      Left = 275
      Top = 5
      Width = 121
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 1
      WorkView = WorkView
      FieldName = '��ˮ״̬'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*20'
    end
    object edtEDate: TWVEdit
      Left = 275
      Top = 28
      Width = 121
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 4
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object edtMoney: TWVDigitalEdit
      Left = 640
      Top = 5
      Width = 86
      Height = 20
      AllowPoint = True
      AllowNegative = True
      UserSeprator = True
      Precision = 0
      MaxIntLen = 12
      ParentColor = False
      TabOrder = 3
      TabStop = True
      Text = '0'
      WorkView = WorkView
      FieldName = 'վ����ˮ��'
      SynchronizeByValue = True
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 73
    Width = 755
    Height = 386
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Width = 755
      Height = 386
      Columns = <
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lwithdraw_flag'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'վ���'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'վ����ˮ��'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semp_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����Ա'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semp_no2'
          PickList.Strings = ()
          Title.Caption = '��˲���Ա'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���׽��'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ˮ״̬'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lsafe_level'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ע'
          Width = 200
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Vsvarstr1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������ݰ�'
          Width = 200
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
        Name = 'վ���'
        Caption = 'վ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = 'վ����ˮ��'
        Caption = 'վ����ˮ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DefaultValue = 0
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
        MonitorValueChangedFields = '|��ʼ����|'
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
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
        DefaultValue = 0
        GetPrevChar = '*'
      end
      item
        Name = '��ˮ״̬'
        Caption = '��ˮ״̬'
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
        DomainName = '����У��'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        MonitorValueChangedFields = '|��������|'
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|վ���|վ����ˮ��|����Ա|��������|������|��ˮ״̬|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '������־��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'վ���'
        FieldName = 'վ���'
      end
      item
        ParamName = 'վ����ˮ��'
        FieldName = 'վ����ˮ��'
      end
      item
        ParamName = '����Ա'
        FieldName = '����Ա'
      end
      item
        ParamName = '��ʼ����'
        FieldName = '��ʼ����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��ˮ״̬'
        FieldName = '��ˮ״̬'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lwithdraw_flag'
        DataPresentType = 'idobjects'
        DataPresentParam = '-33'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '20'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-21'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '-38'
      end
      item
        FieldName = 'semp_no2'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end>
    Left = 160
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 192
    Top = 256
  end
end
