inherited faqhSetOperStation: TfaqhSetOperStation
  Width = 771
  Height = 479
  Caption = '�������Ա��¼վ��'
  inherited pcPages: TRzPageControl
    Width = 771
    Height = 479
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 420
        Width = 767
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 594
          Top = 5
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 307
          Top = 5
          Enabled = False
          TabOrder = 3
          Visible = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 511
          Top = 5
        end
        inherited btnDelete: TBitBtn
          Left = 677
          Top = 5
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 18
          Top = 5
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 106
          Top = 10
          Width = 175
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 767
        Align = alNone
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 767
        Height = 387
        Columns = <
          item
            Expanded = False
            FieldName = 'scust_no'
            PickList.Strings = ()
            Title.Caption = '����Ա'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Caption = 'վ���'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone'
            PickList.Strings = ()
            Title.Caption = 'IP��ַ'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scard1'
            PickList.Strings = ()
            Title.Caption = '������'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Caption = 'վ������'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote'
            PickList.Strings = ()
            Title.Caption = '��ע'
            Width = -1
            Visible = False
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 767
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Labeloper_code1: TLabel
          Left = 34
          Top = 13
          Width = 36
          Height = 12
          Caption = '����Ա'
        end
        object Labelsite_no2: TLabel
          Left = 254
          Top = 13
          Width = 36
          Height = 12
          Caption = 'վ���'
        end
        object WVComboBox1: TWVComboBox
          Left = 79
          Top = 8
          Width = 101
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '��ѯ.����Ա'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-30'
        end
        object WVComboBox6: TWVComboBox
          Left = 299
          Top = 8
          Width = 100
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 1
          WorkView = WorkView
          FieldName = '��ѯ.վ���'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-33'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Labeloper_code3: TLabel [0]
        Left = 26
        Top = 29
        Width = 36
        Height = 12
        Caption = '����Ա'
      end
      object Labelsite_no4: TLabel [1]
        Left = 26
        Top = 69
        Width = 36
        Height = 12
        Caption = 'վ���'
      end
      inherited UIPanel2: TUIPanel
        Top = 420
        Width = 767
        inherited btnOK: TBitBtn
          Left = 596
          Top = 5
        end
        inherited btnCancel: TBitBtn
          Left = 677
          Top = 5
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object WVComboBox3: TWVComboBox
        Left = 72
        Top = 24
        Width = 157
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 0
        TabOrder = 1
        Text = '<����Ա>'
        WorkView = WorkView
        FieldName = '����Ա'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '-30'
      end
      object WVComboBox2: TWVComboBox
        Left = 72
        Top = 64
        Width = 156
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 0
        TabOrder = 2
        Text = '<վ���>'
        WorkView = WorkView
        FieldName = 'վ���'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '-33'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 72
    Top = 375
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
        Name = '��ѯ.����Ա'
        Caption = '��ѯ.����Ա'
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
      end
      item
        Name = '��ѯ.վ���'
        Caption = '��ѯ.վ���'
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
        Name = '����Ա'
        Caption = '����Ա'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 1
        Checker.MaxLength = 100
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'scust_no'
      end
      item
        Name = 'վ���'
        Caption = 'վ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 1
        Checker.MaxLength = 111
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '�������'
        Caption = '�������'
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
        DataField = 'sstatus0'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.����Ա|��ѯ.վ���|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|����Ա|վ���|'
        GroupIndex = 1
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Top = 344
  end
  inherited QueryRequest: TWVRequest
    ID = '����Ա��¼վ���ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '����Ա'
        FieldName = '��ѯ.����Ա'
      end
      item
        ParamName = 'վ���'
        FieldName = '��ѯ.վ���'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 168
    Top = 312
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'scust_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end>
    Top = 343
  end
  inherited AddRequest: TWVRequest
    ID = '�������Ա��¼վ��'
    Bindings = <
      item
        ParamName = '����Ա'
        FieldName = '����Ա'
      end
      item
        ParamName = 'վ���'
        FieldName = 'վ���'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 72
    Top = 312
  end
  inherited DeleteRequest: TWVRequest
    ID = '�������Ա��¼վ��'
    Bindings = <
      item
        ParamName = '����Ա'
        FieldName = '����Ա'
      end
      item
        ParamName = 'վ���'
        FieldName = 'վ���'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 104
    Top = 312
  end
  inherited ChangeRequest: TWVRequest
    ID = '�������Ա��¼վ��'
    Bindings = <
      item
        ParamName = '����Ա'
        FieldName = '����Ա'
      end
      item
        ParamName = 'վ���'
        FieldName = 'վ���'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 136
    Top = 312
  end
  inherited WVDataSource: TWVDataSource
    Left = 136
    Top = 343
  end
  inherited alDatasetActions: TActionList
    Left = 168
    Top = 342
  end
end
