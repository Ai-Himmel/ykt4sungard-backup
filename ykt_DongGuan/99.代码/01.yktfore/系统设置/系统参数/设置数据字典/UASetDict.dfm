inherited faqhSetDict: TfaqhSetDict
  Width = 664
  Height = 425
  Caption = '���������ֵ�'
  inherited pcPages: TRzPageControl
    Width = 664
    Height = 425
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 366
        Width = 660
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 408
          Top = 5
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 490
          Top = 5
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 325
          Top = 5
        end
        inherited btnDelete: TBitBtn
          Left = 571
          Top = 5
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 10
          Top = 5
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 92
          Top = 10
          Visible = False
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 839
        Align = alNone
        TabOrder = 2
      end
      inherited Grid: TRzDBGrid
        Top = 36
        Width = 660
        Height = 330
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        ReadOnly = True
        FramingPreference = fpCustomFraming
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '�������'
            Width = 87
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_acc2'
            PickList.Strings = ()
            Title.Caption = '��������'
            Width = 147
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sorder0'
            PickList.Strings = ()
            Title.Caption = '�ֵ����'
            Width = 73
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_acc'
            PickList.Strings = ()
            Title.Caption = '�ֵ�����'
            Width = 202
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 660
        Height = 36
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label3: TLabel
          Left = 449
          Top = 11
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label4: TLabel
          Left = 17
          Top = 11
          Width = 48
          Height = 12
          Caption = '�������'
        end
        object Label5: TLabel
          Left = 233
          Top = 11
          Width = 48
          Height = 12
          Caption = '�ֵ����'
        end
        object edtSName: TWVEdit
          Left = 501
          Top = 7
          Width = 148
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.����>'
          WorkView = WorkView
          FieldName = '��ѯ.����'
          SynchronizeWhenExit = True
        end
        object edtSCode: TWVEdit
          Left = 69
          Top = 7
          Width = 148
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.�������>'
          WorkView = WorkView
          FieldName = '��ѯ.�������'
          SynchronizeWhenExit = True
        end
        object edtBCode: TWVEdit
          Left = 285
          Top = 7
          Width = 148
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 2
          Text = '<��ѯ.С�����>'
          WorkView = WorkView
          FieldName = '��ѯ.С�����'
          SynchronizeWhenExit = True
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Labeldict_no2: TLabel [0]
        Left = 57
        Top = 100
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Labeldict_value3: TLabel [1]
        Left = 57
        Top = 141
        Width = 48
        Height = 12
        Caption = '�ֵ����'
      end
      object Labeldict_caption4: TLabel [2]
        Left = 56
        Top = 181
        Width = 48
        Height = 12
        Caption = '�ֵ�����'
      end
      object Label1: TLabel [3]
        Left = 57
        Top = 60
        Width = 48
        Height = 12
        Caption = '�������'
      end
      inherited UIPanel2: TUIPanel
        Top = 366
        Width = 660
        TabOrder = 4
        inherited btnOK: TBitBtn
          Left = 489
          Top = 5
        end
        inherited btnCancel: TBitBtn
          Left = 570
          Top = 5
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object WVEditdict_value3: TWVEdit
        Left = 117
        Top = 136
        Width = 300
        Height = 20
        Color = clInfoBk
        MaxLength = 10
        ReadOnly = False
        TabOrder = 2
        Text = '<������루�ֵ䵥Ԫ���룩>'
        WorkView = WorkView
        FieldName = '������루�ֵ䵥Ԫ���룩'
        SynchronizeWhenExit = True
      end
      object WVEditdict_caption4: TWVEdit
        Left = 117
        Top = 176
        Width = 300
        Height = 20
        Color = clInfoBk
        MaxLength = 40
        ReadOnly = False
        TabOrder = 3
        Text = '<�������ƣ��ֵ䵥Ԫ���ݣ�>'
        WorkView = WorkView
        FieldName = '�������ƣ��ֵ䵥Ԫ���ݣ�'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit1: TWVDigitalEdit
        Left = 117
        Top = 55
        Width = 300
        Height = 20
        RedNegative = True
        Enabled = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '��Ŀ���ƣ��ֵ���ࣩ'
      end
      object WVEdit2: TWVEdit
        Left = 117
        Top = 96
        Width = 300
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<��������>'
        WorkView = WorkView
        FieldName = '��������'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 172
    Top = 343
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
        Name = '��ѯ.����'
        Caption = '��ѯ.����'
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
        Name = '��Ŀ���ƣ��ֵ���ࣩ'
        Caption = '�ֵ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 1
        Checker.MaxLength = 0
        Checker.Min = 1
        Checker.Max = 9999
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '������루�ֵ䵥Ԫ���룩'
        Caption = '�ֵ䵥Ԫ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 1
        Checker.MaxLength = 10
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sorder0'
      end
      item
        Name = '�������ƣ��ֵ䵥Ԫ���ݣ�'
        Caption = '�ֵ䵥Ԫ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 40
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sbank_acc'
      end
      item
        Name = '��������'
        Caption = '��������'
        FieldType = wftUndefined
        DomainName = '����'
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
        DataField = 'sbank_acc2'
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
      end
      item
        Name = '��ѯ.�������'
        Caption = '��ѯ.�������'
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
        Name = '��ѯ.С�����'
        Caption = '��ѯ.С�����'
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
        MonitorValueChangedFields = '|��ѯ.��Ŀ���ƣ��ֵ���ࣩ|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|��Ŀ���ƣ��ֵ���ࣩ|������루�ֵ䵥Ԫ���룩|�������ƣ��ֵ䵥' +
          'Ԫ���ݣ�|����Ա|'
        GroupIndex = 1
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Top = 344
  end
  inherited QueryRequest: TWVRequest
    ID = '��ѯ�����ֵ�'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '����'
        FieldName = '��ѯ.����'
      end
      item
        ParamName = 'С�����'
        FieldName = '��ѯ.С�����'
      end
      item
        ParamName = '�������'
        FieldName = '��ѯ.�������'
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
    Left = 108
    Top = 343
  end
  inherited AddRequest: TWVRequest
    ID = '���������ֵ�'
    Bindings = <
      item
        ParamName = '��Ŀ���ƣ��ֵ���ࣩ'
        FieldName = '��Ŀ���ƣ��ֵ���ࣩ'
      end
      item
        ParamName = '������루�ֵ䵥Ԫ���룩'
        FieldName = '������루�ֵ䵥Ԫ���룩'
      end
      item
        ParamName = '�������ƣ��ֵ䵥Ԫ���ݣ�'
        FieldName = '�������ƣ��ֵ䵥Ԫ���ݣ�'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
        DefaultValue = '1'
      end>
    Left = 72
    Top = 312
  end
  inherited DeleteRequest: TWVRequest
    ID = '���������ֵ�'
    Bindings = <
      item
        ParamName = '��Ŀ���ƣ��ֵ���ࣩ'
        FieldName = '��Ŀ���ƣ��ֵ���ࣩ'
      end
      item
        ParamName = '������루�ֵ䵥Ԫ���룩'
        FieldName = '������루�ֵ䵥Ԫ���룩'
      end
      item
        ParamName = '�������ƣ��ֵ䵥Ԫ���ݣ�'
        FieldName = '�������ƣ��ֵ䵥Ԫ���ݣ�'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
        DefaultValue = '3'
      end>
    Left = 104
    Top = 312
  end
  inherited ChangeRequest: TWVRequest
    ID = '���������ֵ�'
    Bindings = <
      item
        ParamName = '��Ŀ���ƣ��ֵ���ࣩ'
        FieldName = '��Ŀ���ƣ��ֵ���ࣩ'
      end
      item
        ParamName = '������루�ֵ䵥Ԫ���룩'
        FieldName = '������루�ֵ䵥Ԫ���룩'
      end
      item
        ParamName = '�������ƣ��ֵ䵥Ԫ���ݣ�'
        FieldName = '�������ƣ��ֵ䵥Ԫ���ݣ�'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
        DefaultValue = '2'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 136
    Top = 312
  end
  inherited WVDataSource: TWVDataSource
    Left = 140
    Top = 343
  end
  inherited alDatasetActions: TActionList
    Left = 204
    Top = 343
  end
end
