inherited faqhSetChargePara: TfaqhSetChargePara
  Width = 681
  Height = 477
  Caption = '�շѲ�������'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 418
        Width = 677
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 416
          Top = 6
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 502
          Top = 6
          Enabled = False
          TabOrder = 1
        end
        inherited btnQuery: TBitBtn [2]
          Left = 330
          Top = 6
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Top = 6
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
          Top = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 104
          Top = 11
          Width = 169
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
        Align = alNone
      end
      inherited Grid: TRzDBGrid
        Top = 25
        Width = 677
        Height = 393
        Options = [dgTitles, dgIndicator, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        ReadOnly = True
        Columns = <
          item
            Expanded = False
            FieldName = 'scust_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��λ����'
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ͻ����'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�շ����'
            Width = 100
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 677
        Height = 25
        Align = alTop
        ParentColor = True
        TabOrder = 0
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 56
        Top = 84
        Width = 60
        Height = 12
        Caption = '��λ���ƣ�'
      end
      object Label3: TLabel [1]
        Left = 336
        Top = 84
        Width = 60
        Height = 12
        Caption = '�ͻ����'
      end
      object Label1: TLabel [2]
        Left = 56
        Top = 124
        Width = 60
        Height = 12
        Caption = '�շ����'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        inherited btnOK: TBitBtn
          Left = 505
        end
        inherited btnCancel: TBitBtn
          Left = 593
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object cbbdep: TWVComboBox
        Left = 120
        Top = 80
        Width = 201
        Height = 18
        Style = csOwnerDrawFixed
        Color = clWhite
        ItemHeight = 12
        TabOrder = 1
        WorkView = WorkView
        FieldName = '��λ����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-22'
      end
      object cbbcusttype: TWVComboBox
        Left = 408
        Top = 80
        Width = 193
        Height = 18
        Style = csOwnerDrawFixed
        Color = clWhite
        ItemHeight = 12
        TabOrder = 2
        WorkView = WorkView
        FieldName = '�ͻ����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-41'
      end
      object cbbfeetype: TWVComboBox
        Left = 120
        Top = 120
        Width = 201
        Height = 18
        Style = csOwnerDrawFixed
        Color = clWhite
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView
        FieldName = '�շ����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-43'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 332
    Top = 391
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
        Name = '��ѯ.��λ����'
        Caption = '��ѯ.��λ����'
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
        DataField = 'scust_no'
      end
      item
        Name = '�ͻ����'
        Caption = '�ͻ����'
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
        DataField = 'lvol0'
      end
      item
        Name = '�շ����'
        Caption = '�շ����'
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
        Name = '��λ����'
        Caption = '��λ����'
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
        DataField = 'scust_no'
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
        DataField = 'vsmess'
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
        DataField = '@Return'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.��λ����|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|�ͻ����|�շ����|��λ����|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 120
    Top = 392
  end
  inherited QueryRequest: TWVRequest
    ID = '�շѲ�����ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��λ����'
        FieldName = '��ѯ.��λ����'
      end>
    Left = 264
    Top = 344
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'scust_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'lvol0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-41'
      end
      item
        FieldName = 'lvol1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
      end>
    Left = 164
    Top = 391
  end
  inherited AddRequest: TWVRequest
    ID = '�շѲ�������.����'
    Bindings = <
      item
        ParamName = '��λ����'
        FieldName = '��λ����'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end>
    Left = 120
    Top = 344
  end
  inherited DeleteRequest: TWVRequest
    ID = '�շѲ�������.ɾ��'
    Bindings = <
      item
        ParamName = '��λ����'
        FieldName = '��λ����'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end>
    Left = 168
    Top = 344
  end
  inherited ChangeRequest: TWVRequest
    ID = '�շѲ�������.�޸�'
    Bindings = <
      item
        ParamName = '��λ����'
        FieldName = '��λ����'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end>
    Left = 216
    Top = 344
  end
  inherited WVDataSource: TWVDataSource
    Left = 212
    Top = 391
  end
  inherited alDatasetActions: TActionList
    Left = 260
    Top = 396
  end
end
