inherited faqhsetMesList: TfaqhsetMesList
  Width = 681
  Height = 477
  Caption = '��Ϣ���й���'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 414
        Width = 677
        Height = 40
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 179
          Top = 7
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 499
          Top = 7
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 410
          Top = 7
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Top = 7
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
          Top = 7
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 12
          Width = 169
          Visible = False
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 97
        Width = 677
        Height = 317
        TabOrder = 2
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
            FieldName = 'Lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ϣ���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ϣ״̬'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ϣ����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ϵͳ���'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol9'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����ʹ���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol5'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ϣ����ʱ��'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ϣ��ʼ����ʱ��'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ϣ�������ʱ��'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol6'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������Ϣ'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol7'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol8'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���׿���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ɾ����־'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'Lvol10'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���մ���'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol11'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol12'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ϣ����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr1'
            PickList.Strings = ()
            Title.Caption = '��������'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr2'
            PickList.Strings = ()
            Title.Caption = 'Ӧ������'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lserial0'
            PickList.Strings = ()
            Title.Caption = '�ѷ��ʹ���'
            Width = 80
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 79
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label2: TLabel
          Left = 218
          Top = 10
          Width = 48
          Height = 12
          Caption = '��Ϣ���'
        end
        object Label3: TLabel
          Left = 54
          Top = 34
          Width = 36
          Height = 12
          Caption = '������'
        end
        object Label4: TLabel
          Left = 42
          Top = 10
          Width = 48
          Height = 12
          Caption = '��Ϣ״̬'
        end
        object Label6: TLabel
          Left = 398
          Top = 34
          Width = 60
          Height = 12
          Caption = '��ϵͳ���'
        end
        object Label7: TLabel
          Left = 42
          Top = 58
          Width = 48
          Height = 12
          Caption = '�豸���'
        end
        object Label8: TLabel
          Left = 410
          Top = 10
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label1: TLabel
          Left = 218
          Top = 33
          Width = 48
          Height = 12
          Caption = '��Ϣ����'
        end
        object WVDigitalEdit2: TWVDigitalEdit
          Left = 276
          Top = 6
          Width = 100
          Height = 20
          AllowNegative = True
          Precision = 0
          MaxIntLen = 10
          Color = clInfoBk
          ParentColor = False
          TabOrder = 1
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '��ѯ.��Ϣ���'
          SynchronizeByValue = True
        end
        object WVEdit8: TWVEdit
          Left = 468
          Top = 6
          Width = 129
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 2
          Text = '<��ѯ.��������>'
          WorkView = WorkView
          FieldName = '��ѯ.��������'
        end
        object WVComboBox4: TWVComboBox
          Left = 100
          Top = 55
          Width = 277
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 6
          WorkView = WorkView
          FieldName = '��ѯ.�豸���'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-31'
        end
        object WVComboBox1: TWVComboBox
          Left = 468
          Top = 29
          Width = 129
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '��ѯ.��ϵͳ���'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-47'
        end
        object WVComboBox2: TWVComboBox
          Left = 100
          Top = 6
          Width = 101
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '��ѯ.��Ϣ״̬'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*103'
        end
        object WVComboBox6: TWVComboBox
          Left = 276
          Top = 29
          Width = 101
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '��ѯ.��Ϣ����'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*104'
        end
        object WVDigitalEdit1: TWVDigitalEdit
          Left = 100
          Top = 30
          Width = 100
          Height = 20
          AllowNegative = True
          Precision = 0
          MaxIntLen = 10
          Color = clInfoBk
          ParentColor = False
          TabOrder = 5
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '��ѯ.������'
          SynchronizeByValue = True
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label10: TLabel [0]
        Left = 74
        Top = 84
        Width = 48
        Height = 12
        Caption = '��Ϣ���'
      end
      object Label12: TLabel [1]
        Left = 74
        Top = 164
        Width = 48
        Height = 12
        Caption = '��Ϣ״̬'
      end
      object Label23: TLabel [2]
        Left = 50
        Top = 124
        Width = 72
        Height = 12
        Caption = '����ʹ���'
      end
      object Label28: TLabel [3]
        Left = 42
        Top = 5
        Width = 96
        Height = 16
        Caption = '��Ϣ���й���'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 3
        inherited btnOK: TBitBtn
          Left = 505
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 593
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object edtId: TWVDigitalEdit
        Left = 132
        Top = 80
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '��Ϣ���'
        SynchronizeByValue = True
      end
      object edtNum: TWVDigitalEdit
        Left = 132
        Top = 120
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 1
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '����ʹ���'
        SynchronizeByValue = True
      end
      object cbbStat: TWVComboBox
        Left = 132
        Top = 159
        Width = 101
        Height = 20
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 2
        Text = '<��Ϣ״̬>'
        WorkView = WorkView
        FieldName = '��Ϣ״̬'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*103'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 492
    Top = 223
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '��ѯ�����'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Features.Strings = ()
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
        Features.Strings = ()
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
        Features.Strings = ()
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
        Name = '��ѯ.��Ϣ���'
        Caption = '��ѯ.��Ϣ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.������'
        Caption = '��ѯ.������'
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
        Name = '��ѯ.��Ϣ״̬'
        Caption = '��ѯ.��Ϣ״̬'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.��Ϣ����'
        Caption = '��ѯ.��Ϣ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.��ϵͳ���'
        Caption = '��ѯ.��ϵͳ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�豸���'
        Caption = '��ѯ.�豸���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 9
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
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��Ϣ���'
        Caption = '��Ϣ���'
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
        GroupIndex = 1
        DataField = 'Lvol0'
      end
      item
        Name = '��Ϣ״̬'
        Caption = '��Ϣ״̬'
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
        GroupIndex = 1
        DataField = 'Lvol2'
      end
      item
        Name = '����ʹ���'
        Caption = '����ʹ���'
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
        GroupIndex = 1
        DataField = 'Lvol9'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.��������|��ѯ.��Ϣ���|��ѯ.������|��ѯ.��Ϣ״̬|��ѯ.��Ϣ' +
          '����|��ѯ.��ϵͳ���|��ѯ.�豸���|��ѯ.��������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|��������|��Ϣ���|������|��Ϣ״̬|��Ϣ����|��ϵͳ���|�豸���|' +
          '��Ϣ����ʱ��|��Ϣ��ʼ����ʱ��|��Ϣ�������ʱ��|������|������Ϣ|' +
          '��������|���׿���|����ʹ���|ɾ����־|���մ���|���|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 424
    Top = 184
  end
  inherited QueryRequest: TWVRequest
    ID = '��Ϣ���в�ѯ'
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
        ParamName = '��Ϣ���'
        FieldName = '��ѯ.��Ϣ���'
      end
      item
        ParamName = '������'
        FieldName = '��ѯ.������'
      end
      item
        ParamName = '��Ϣ״̬'
        FieldName = '��ѯ.��Ϣ״̬'
      end
      item
        ParamName = '��Ϣ����'
        FieldName = '��ѯ.��Ϣ����'
      end
      item
        ParamName = '��ϵͳ���'
        FieldName = '��ѯ.��ϵͳ���'
      end
      item
        ParamName = '�豸���'
        FieldName = '��ѯ.�豸���'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end>
    Left = 552
    Top = 184
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol1'
        DataPresentType = 'idobjects'
        DataPresentParam = '-38'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'idobjects'
        DataPresentParam = '103'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '104'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'idobjects'
        DataPresentParam = '-47'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '-31'
      end
      item
        FieldName = 'lvol12'
        DataPresentType = 'idobjects'
        DataPresentParam = '105'
      end>
    Left = 460
    Top = 223
  end
  inherited AddRequest: TWVRequest
    ID = '��Ϣ���й���'
    Bindings = <
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��Ϣ���'
        FieldName = '��Ϣ���'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��Ϣ״̬'
        FieldName = '��Ϣ״̬'
      end
      item
        ParamName = '��Ϣ����'
        FieldName = '��Ϣ����'
      end
      item
        ParamName = '��ϵͳ���'
        FieldName = '��ϵͳ���'
      end
      item
        ParamName = '�豸���'
        FieldName = '�豸���'
      end
      item
        ParamName = '��Ϣ����ʱ��'
        FieldName = '��Ϣ����ʱ��'
      end
      item
        ParamName = '��Ϣ��ʼ����ʱ��'
        FieldName = '��Ϣ��ʼ����ʱ��'
      end
      item
        ParamName = '��Ϣ�������ʱ��'
        FieldName = '��Ϣ�������ʱ��'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '���׿���'
        FieldName = '���׿���'
      end
      item
        ParamName = '����ʹ���'
        FieldName = '����ʹ���'
      end
      item
        ParamName = 'ɾ����־'
        FieldName = 'ɾ����־'
      end
      item
        ParamName = '���մ���'
        FieldName = '���մ���'
      end
      item
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = '��Ϣ����'
        FieldName = '��Ϣ����'
      end>
    Left = 456
    Top = 184
  end
  inherited DeleteRequest: TWVRequest
    ID = '��Ϣ���й���'
    Bindings = <
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��Ϣ���'
        FieldName = '��Ϣ���'
      end
      item
        ParamName = '����ʹ���'
        FieldName = '����ʹ���'
      end
      item
        ParamName = '��Ϣ״̬'
        FieldName = '��Ϣ״̬'
      end>
    Left = 488
    Top = 184
  end
  inherited ChangeRequest: TWVRequest
    ID = '��Ϣ���й���'
    Bindings = <
      item
        ParamName = '��Ϣ���'
        FieldName = '��Ϣ���'
      end
      item
        ParamName = '��Ϣ״̬'
        FieldName = '��Ϣ״̬'
      end
      item
        ParamName = '����ʹ���'
        FieldName = '����ʹ���'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 520
    Top = 184
  end
  inherited WVDataSource: TWVDataSource
    Left = 556
    Top = 223
  end
  inherited alDatasetActions: TActionList
    Left = 524
    Top = 228
  end
end
