inherited faqhsetCardFee: TfaqhsetCardFee
  Width = 681
  Height = 477
  Caption = '�����շ�����'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 677
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 504
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 238
          Enabled = False
          Visible = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 418
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 88
          Width = 169
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
        TabOrder = 2
      end
      inherited Grid: TRzDBGrid
        Top = 49
        Width = 677
        Height = 375
        TabOrder = 1
        Columns = <
          item
            Expanded = False
            FieldName = 'lsafe_level'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�����'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�շ����'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����Ա'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��󱣴�ʱ��'
            Width = 150
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 31
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label2: TLabel
          Left = 26
          Top = 10
          Width = 48
          Height = 12
          Caption = '�շ����'
        end
        object Label4: TLabel
          Left = 230
          Top = 10
          Width = 36
          Height = 12
          Caption = '�����'
        end
        object WVComboBox4: TWVComboBox
          Left = 84
          Top = 5
          Width = 131
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '��ѯ.�շ����'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-43'
        end
        object WVComboBox5: TWVComboBox
          Left = 276
          Top = 5
          Width = 131
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 1
          WorkView = WorkView
          FieldName = '��ѯ.������'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-5'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label11: TLabel [0]
        Left = 60
        Top = 108
        Width = 54
        Height = 12
        Caption = '�շ����*'
      end
      object Label13: TLabel [1]
        Left = 72
        Top = 76
        Width = 42
        Height = 12
        Caption = '�����*'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 2
        inherited btnOK: TBitBtn
          Left = 505
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 593
          TabOrder = 2
          TabStop = True
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object cbbCardType: TWVComboBox
        Left = 124
        Top = 69
        Width = 131
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 0
        WorkView = WorkView
        FieldName = '������'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-5'
      end
      object cbbFee: TWVComboBox
        Left = 124
        Top = 102
        Width = 131
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 1
        WorkView = WorkView
        FieldName = '�շ����'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-43'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 556
    Top = 407
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
        Name = '��ѯ.�շ����'
        Caption = '��ѯ.�շ����'
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
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '������־'
        Caption = '������־'
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
        DataField = 'sstatus0'
      end
      item
        Name = '������'
        Caption = '������'
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
        DataField = 'lsafe_level'
      end
      item
        Name = '�շ����'
        Caption = '�շ����'
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
        DataField = 'lvol5'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.������־|��ѯ.�շ����|��ѯ.������|��ѯ.������|��ѯ.������' +
          '��|��ѯ.�շѷ�ʽ|��ѯ.�շѽ��|��ѯ.�շ�˳��|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|��������|������־|�շ����|������|������|��������|�շѷ�ʽ|�շ�' +
          '���|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 472
    Top = 368
  end
  inherited QueryRequest: TWVRequest
    ID = '�����շ����ò�ѯ'
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
        ParamName = '�շ����'
        FieldName = '��ѯ.�շ����'
      end
      item
        ParamName = '������'
        FieldName = '��ѯ.������'
      end>
    Left = 632
    Top = 368
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-44'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'lsafe_level'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-56'
      end>
    Left = 508
    Top = 399
  end
  inherited AddRequest: TWVRequest
    ID = '�����շ�����'
    Bindings = <
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end>
    Left = 512
    Top = 368
  end
  inherited DeleteRequest: TWVRequest
    ID = '�����շ�����'
    Bindings = <
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end>
    Left = 552
    Top = 368
  end
  inherited ChangeRequest: TWVRequest
    ID = '�����շ�����'
    Bindings = <
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end>
    Left = 592
    Top = 368
  end
  inherited WVDataSource: TWVDataSource
    Left = 636
    Top = 399
  end
  inherited alDatasetActions: TActionList
    Left = 596
    Top = 404
  end
end
