inherited faqhsetCardType: TfaqhsetCardType
  Width = 744
  Height = 477
  Caption = '���������'
  inherited pcPages: TRzPageControl
    Width = 744
    Height = 477
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 414
        Width = 740
        Height = 40
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 474
          Top = 7
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 562
          Top = 7
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 385
          Top = 7
        end
        inherited btnDelete: TBitBtn
          Left = 651
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
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 740
      end
      inherited Grid: TRzDBGrid
        Top = 41
        Width = 740
        Height = 373
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�����'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���������'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���ɱ���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'Ԥ����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���ʳ�ֵ�޶�'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���޶�'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smarket_code2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�Ƿ�������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ܷ�����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ܷ񲹰�'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̶�����Ч��'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�Ƿ�֧�ֶ�Ǯ��'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'smarket_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ʹ��״̬'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ч����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Caption = '�������շ����'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'vsvarstr1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���õ��շ����'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��;'
            Visible = False
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 740
        Height = 23
        Align = alTop
        ParentColor = True
        TabOrder = 1
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label14: TLabel [0]
        Left = 102
        Top = 52
        Width = 36
        Height = 12
        Caption = '�����'
      end
      object Label15: TLabel [1]
        Left = 90
        Top = 110
        Width = 48
        Height = 12
        Caption = '���ɱ���'
      end
      object Label16: TLabel [2]
        Left = 74
        Top = 81
        Width = 66
        Height = 12
        Caption = '���������*'
      end
      object Label17: TLabel [3]
        Left = 90
        Top = 309
        Width = 48
        Height = 12
        Caption = 'Ԥ����'
      end
      object Label18: TLabel [4]
        Left = 90
        Top = 164
        Width = 48
        Height = 12
        Caption = '�ܷ�����'
      end
      object Label19: TLabel [5]
        Left = 90
        Top = 250
        Width = 48
        Height = 12
        Caption = '�ܷ񲹰�'
      end
      object Label20: TLabel [6]
        Left = 66
        Top = 221
        Width = 72
        Height = 12
        Caption = '�̶�����Ч��'
      end
      object Label21: TLabel [7]
        Left = 406
        Top = 278
        Width = 84
        Height = 12
        Caption = '�Ƿ�֧�ֶ�Ǯ��'
        Visible = False
      end
      object Label23: TLabel [8]
        Left = 90
        Top = 192
        Width = 48
        Height = 12
        Caption = '��Ч����'
      end
      object Label1: TLabel [9]
        Left = 78
        Top = 279
        Width = 60
        Height = 12
        Caption = '�Ƿ�������'
      end
      object Label2: TLabel [10]
        Left = 405
        Top = 334
        Width = 84
        Height = 12
        Caption = '�������շ����'
        Visible = False
      end
      object WVLabel3: TWVLabel [11]
        Left = 80
        Top = 137
        Width = 60
        Height = 12
        Caption = '���������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel [12]
        Left = 66
        Top = 338
        Width = 72
        Height = 12
        Caption = '���ʳ�ֵ�޶�'
      end
      object Label4: TLabel [13]
        Left = 102
        Top = 367
        Width = 36
        Height = 12
        Caption = '���޶�'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 740
        TabOrder = 13
        inherited btnOK: TBitBtn
          Left = 568
        end
        inherited btnCancel: TBitBtn
          Left = 656
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtCardType: TWVDigitalEdit
        Left = 150
        Top = 48
        Width = 187
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
        FieldName = '�����'
        SynchronizeByValue = True
      end
      object WVDigitalEdit15: TWVDigitalEdit
        Left = 150
        Top = 106
        Width = 187
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 3
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '���ɱ���'
        SynchronizeByValue = True
      end
      object edtName: TWVEdit
        Left = 150
        Top = 77
        Width = 187
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<���������>'
        WorkView = WorkView
        FieldName = '���������'
        SynchronizeWhenExit = True
      end
      object WVEdit17: TWVEdit
        Left = 150
        Top = 305
        Width = 187
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 11
        Text = '<Ԥ����>'
        WorkView = WorkView
        FieldName = 'Ԥ����'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit23: TWVDigitalEdit
        Left = 150
        Top = 188
        Width = 187
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 5
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '��Ч����'
        SynchronizeByValue = True
      end
      object WVComboBox1: TWVComboBox
        Left = 150
        Top = 160
        Width = 187
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 4
        WorkView = WorkView
        FieldName = '�ܷ�����'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object WVComboBox3: TWVComboBox
        Left = 150
        Top = 216
        Width = 187
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 6
        WorkView = WorkView
        FieldName = '�ܷ��ʧ'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object WVComboBox4: TWVComboBox
        Left = 150
        Top = 245
        Width = 187
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 7
        WorkView = WorkView
        FieldName = '�ܷ񲹰�'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object WVComboBox5: TWVComboBox
        Left = 502
        Top = 274
        Width = 187
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 8
        Visible = False
        WorkView = WorkView
        FieldName = '�Ƿ�֧�ֶ�Ǯ��'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object cbbNMK: TWVComboBox
        Left = 150
        Top = 275
        Width = 187
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 9
        OnChange = cbbNMKChange
        WorkView = WorkView
        FieldName = '�Ƿ�������'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object cbbFeeType: TWVComboBox
        Left = 502
        Top = 330
        Width = 187
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 10
        Visible = False
        WorkView = WorkView
        FieldName = 'Ĭ���շ����'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-43'
      end
      object cbbCardType: TWVComboBox
        Left = 150
        Top = 414
        Width = 187
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 12
        Visible = False
        WorkView = WorkView
        FieldName = 'Ĭ���շ����'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-43'
      end
      object cbbPhyType: TWVComboBox
        Left = 150
        Top = 133
        Width = 187
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 2
        WorkView = WorkView
        FieldName = '���������'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-4'
      end
      object WVEdit1: TWVEdit
        Left = 150
        Top = 334
        Width = 187
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 14
        Text = '<�����޶�>'
        WorkView = WorkView
        FieldName = '�����޶�'
        SynchronizeWhenExit = True
      end
      object WVEdit2: TWVEdit
        Left = 150
        Top = 363
        Width = 187
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 15
        Text = '<���޶�>'
        WorkView = WorkView
        FieldName = '���޶�'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 556
    Top = 207
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
        GroupIndex = 1
        DataField = 'Sstatus0'
      end
      item
        Name = '�����'
        Caption = '�����'
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
        DataField = 'lvol0'
      end
      item
        Name = '���ɱ���'
        Caption = '���ɱ���'
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
        DataField = 'lvol1'
      end
      item
        Name = '���������'
        Caption = '���������'
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
        GroupIndex = 1
        DataField = 'sname'
      end
      item
        Name = '��;'
        Caption = '��;'
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
        GroupIndex = 1
        DataField = 'vsvarstr0'
      end
      item
        Name = '�ܷ�����'
        Caption = '�ܷ�����'
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
        GroupIndex = 1
        DataField = 'sstatus1'
      end
      item
        Name = '�ܷ񲹰�'
        Caption = '�ܷ񲹰�'
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
        GroupIndex = 1
        DataField = 'sstatus2'
      end
      item
        Name = '�ܷ��ʧ'
        Caption = '�ܷ��ʧ'
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
        GroupIndex = 1
        DataField = 'sstatus3'
      end
      item
        Name = '�Ƿ�֧�ֶ�Ǯ��'
        Caption = '�Ƿ�֧�ֶ�Ǯ��'
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
        GroupIndex = 1
        DataField = 'sstatus4'
      end
      item
        Name = 'ʹ��״̬'
        Caption = 'ʹ��״̬'
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
        GroupIndex = 1
        DataField = 'smarket_code'
      end
      item
        Name = '��Ч����'
        Caption = '��Ч����'
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
        DataField = 'lvol2'
      end
      item
        Name = '���õ��շ����'
        Caption = '���õ��շ����'
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
        GroupIndex = 1
        DataField = 'vsvarstr1'
      end
      item
        Name = '�Ƿ�������'
        Caption = '�Ƿ�������'
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
        GroupIndex = 1
        DataField = 'smarket_code2'
      end
      item
        Name = 'Ĭ���շ����'
        Caption = 'Ĭ���շ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '���������'
        Caption = '���������'
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
        DataField = 'lvol3'
      end
      item
        Name = 'Ԥ����'
        Caption = 'Ԥ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
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
        DataField = 'damt0'
      end
      item
        Name = '�����޶�'
        Caption = '�����޶�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
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
        DataField = 'damt1'
      end
      item
        Name = '���޶�'
        Caption = '���޶�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
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
        DataField = 'damt2'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.��������|��ѯ.�����|��ѯ.���������|��ѯ.���ɱ���|��ѯ.ʹ' +
          '��״̬|��ѯ.�ܷ�����|��ѯ.��;|��ѯ.�ܷ񲹰�|��ѯ.�ܷ��ʧ|��ѯ.' +
          '�Ƿ�֧�ֶ�Ǯ��|��ѯ.��Ч����|��ѯ.���õ��շ����|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|��������|�����|���ɱ���|���������|��;|�ܷ�����|�ܷ񲹰�|�ܷ�' +
          '��ʧ|�Ƿ�֧�ֶ�Ǯ��|ʹ��״̬|��Ч����|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 472
    Top = 160
  end
  inherited QueryRequest: TWVRequest
    ID = '������ѯ'
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
        ParamName = '�����'
        FieldName = '�����'
        DefaultValue = 0
      end>
    Left = 632
    Top = 160
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '2'
      end
      item
        FieldName = 'sstatus2'
        DataPresentType = 'idobjects'
        DataPresentParam = '2'
      end
      item
        FieldName = 'sstatus3'
        DataPresentType = 'idobjects'
        DataPresentParam = '2'
      end
      item
        FieldName = 'sstatus4'
        DataPresentType = 'idobjects'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '-43'
      end
      item
        FieldName = 'smarket_code2'
        DataPresentType = 'idobjects'
        DataPresentParam = '2'
      end>
    Left = 516
    Top = 207
  end
  inherited AddRequest: TWVRequest
    ID = '���������'
    Bindings = <
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '���ɱ���'
        FieldName = '���ɱ���'
      end
      item
        ParamName = '���������'
        FieldName = '���������'
      end
      item
        ParamName = '��;'
        FieldName = '��;'
      end
      item
        ParamName = '�ܷ�����'
        FieldName = '�ܷ�����'
      end
      item
        ParamName = '�ܷ񲹰�'
        FieldName = '�ܷ񲹰�'
      end
      item
        ParamName = '�ܷ��ʧ'
        FieldName = '�ܷ��ʧ'
      end
      item
        ParamName = '�Ƿ�֧�ֶ�Ǯ��'
        FieldName = '�Ƿ�֧�ֶ�Ǯ��'
      end
      item
        ParamName = 'ʹ��״̬'
        FieldName = 'ʹ��״̬'
      end
      item
        ParamName = '��Ч����'
        FieldName = '��Ч����'
      end
      item
        ParamName = '���õ��շ����'
        FieldName = '���õ��շ����'
      end
      item
        ParamName = 'Ĭ���շ����'
        FieldName = 'Ĭ���շ����'
      end
      item
        ParamName = '�Ƿ�������'
        FieldName = '�Ƿ�������'
      end
      item
        ParamName = '���������'
        FieldName = '���������'
      end
      item
        ParamName = 'Ԥ����'
        FieldName = 'Ԥ����'
      end
      item
        ParamName = '���޶�'
        FieldName = '���޶�'
      end
      item
        ParamName = '�����޶�'
        FieldName = '�����޶�'
      end>
    Left = 512
    Top = 160
  end
  inherited DeleteRequest: TWVRequest
    ID = '���������'
    Bindings = <
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '���ɱ���'
        FieldName = '���ɱ���'
      end
      item
        ParamName = '���������'
        FieldName = '���������'
      end
      item
        ParamName = '��;'
        FieldName = '��;'
      end
      item
        ParamName = '�ܷ�����'
        FieldName = '�ܷ�����'
      end
      item
        ParamName = '�ܷ񲹰�'
        FieldName = '�ܷ񲹰�'
      end
      item
        ParamName = '�ܷ��ʧ'
        FieldName = '�ܷ��ʧ'
      end
      item
        ParamName = '�Ƿ�֧�ֶ�Ǯ��'
        FieldName = '�Ƿ�֧�ֶ�Ǯ��'
      end
      item
        ParamName = 'ʹ��״̬'
        FieldName = 'ʹ��״̬'
      end
      item
        ParamName = '��Ч����'
        FieldName = '��Ч����'
      end
      item
        ParamName = '���õ��շ����'
        FieldName = '���õ��շ����'
      end
      item
        ParamName = '�Ƿ�������'
        FieldName = '�Ƿ�������'
      end
      item
        ParamName = 'Ĭ���շ����'
        FieldName = 'Ĭ���շ����'
      end
      item
        ParamName = '���������'
        FieldName = '���������'
      end
      item
        ParamName = 'Ԥ����'
        FieldName = 'Ԥ����'
      end
      item
        ParamName = '�����޶�'
        FieldName = '�����޶�'
      end
      item
        ParamName = '���޶�'
        FieldName = '���޶�'
      end>
    Left = 552
    Top = 160
  end
  inherited ChangeRequest: TWVRequest
    ID = '���������'
    Bindings = <
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '���ɱ���'
        FieldName = '���ɱ���'
      end
      item
        ParamName = '���������'
        FieldName = '���������'
      end
      item
        ParamName = '��;'
        FieldName = '��;'
      end
      item
        ParamName = '�ܷ�����'
        FieldName = '�ܷ�����'
      end
      item
        ParamName = '�ܷ񲹰�'
        FieldName = '�ܷ񲹰�'
      end
      item
        ParamName = '�ܷ��ʧ'
        FieldName = '�ܷ��ʧ'
      end
      item
        ParamName = '�Ƿ�֧�ֶ�Ǯ��'
        FieldName = '�Ƿ�֧�ֶ�Ǯ��'
      end
      item
        ParamName = 'ʹ��״̬'
        FieldName = 'ʹ��״̬'
      end
      item
        ParamName = '��Ч����'
        FieldName = '��Ч����'
      end
      item
        ParamName = '���õ��շ����'
        FieldName = '���õ��շ����'
      end
      item
        ParamName = '�Ƿ�������'
        FieldName = '�Ƿ�������'
      end
      item
        ParamName = 'Ĭ���շ����'
        FieldName = 'Ĭ���շ����'
      end
      item
        ParamName = '���������'
        FieldName = '���������'
      end
      item
        ParamName = 'Ԥ����'
        FieldName = 'Ԥ����'
      end
      item
        ParamName = '���޶�'
        FieldName = '���޶�'
      end
      item
        ParamName = '�����޶�'
        FieldName = '�����޶�'
      end>
    Left = 592
    Top = 160
  end
  inherited WVDataSource: TWVDataSource
    Left = 636
    Top = 207
  end
  inherited alDatasetActions: TActionList
    Left = 596
    Top = 204
  end
end
