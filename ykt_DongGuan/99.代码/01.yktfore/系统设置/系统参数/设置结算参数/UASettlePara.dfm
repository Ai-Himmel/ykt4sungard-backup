inherited faqhSettlePara: TfaqhSettlePara
  Width = 681
  Height = 477
  Caption = '���ý������'
  inherited pcPages: TPageControl
    Width = 681
    Height = 477
    ActivePage = tsEdit
    inherited tsQuery: TTabSheet
      inherited UIPanel1: TUIPanel
        Top = 420
        Width = 673
        TabOrder = 1
        inherited btnAdd: TBitBtn [0]
          Left = 415
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 503
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 322
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
        end
      end
      inherited Grid: TDBGrid
        Top = 60
        Width = 673
        Height = 360
        TabOrder = 2
        OnDrawColumnCell = GridDrawColumnCell
        Columns = <
          item
            Expanded = False
            FieldName = 'sserial2'
            PickList.Strings = ()
            Title.Caption = 'ϯλ����'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial1'
            PickList.Strings = ()
            Title.Caption = '��������'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial0'
            PickList.Strings = ()
            Title.Caption = '��������ֵ'
            Width = 83
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote'
            PickList.Strings = ()
            Title.Caption = '����'
            Width = 263
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 673
        Height = 60
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label8: TLabel
          Left = 40
          Top = 5
          Width = 96
          Height = 16
          Caption = '���������ѯ'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label2: TLabel
          Left = 42
          Top = 34
          Width = 48
          Height = 12
          Caption = 'ϯλ����'
        end
        object Label3: TLabel
          Left = 242
          Top = 34
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object WVEdit1: TWVEdit
          Left = 100
          Top = 30
          Width = 100
          Height = 20
          Enabled = False
          ImeName = ''
          ParentColor = True
          ReadOnly = False
          TabOrder = 2
          Text = '<��ѯ.��ѯ��־��1�����㣻2�����ף�>'
          Visible = False
          WorkView = WorkView
          FieldName = '��ѯ.��ѯ��־��1�����㣻2�����ף�'
        end
        object WVEdit2: TWVEdit
          Left = 100
          Top = 30
          Width = 100
          Height = 20
          Enabled = False
          ImeName = ''
          ParentColor = True
          ReadOnly = False
          TabOrder = 3
          Text = '<��ѯ.ϯ_λ>'
          Visible = False
          WorkView = WorkView
          FieldName = '��ѯ.ϯ_λ'
        end
        object WVEdit3: TWVEdit
          Left = 300
          Top = 30
          Width = 100
          Height = 20
          Color = clInfoBk
          ImeName = ''
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.��������>'
          WorkView = WorkView
          FieldName = '��ѯ.��������'
        end
        object WVComboBox2: TWVComboBox
          Left = 100
          Top = 30
          Width = 100
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = ''
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '��ѯ.ϯ_λ'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-23'
        end
      end
    end
    inherited tsEdit: TTabSheet
      object Label4: TLabel [0]
        Left = 42
        Top = 44
        Width = 48
        Height = 12
        Caption = 'ϯλ����'
      end
      object Label5: TLabel [1]
        Left = 42
        Top = 84
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Label6: TLabel [2]
        Left = 42
        Top = 124
        Width = 48
        Height = 12
        Caption = '�� �� ֵ'
      end
      object Label9: TLabel [3]
        Left = 40
        Top = 5
        Width = 96
        Height = 16
        Caption = '���ý������'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label_snote: TLabel [4]
        Left = 42
        Top = 164
        Width = 48
        Height = 12
        Caption = '��    ��'
      end
      inherited UIPanel2: TUIPanel
        Top = 414
        Width = 673
        TabOrder = 4
        inherited btnOK: TBitBtn
          Left = 501
        end
        inherited btnCancel: TBitBtn
          Left = 589
        end
        inherited DBNavigator: TDBNavigator
          Hints.Strings = ()
        end
      end
      object WVEdit4: TWVEdit
        Left = 108
        Top = 40
        Width = 100
        Height = 20
        Enabled = False
        ImeName = ''
        ParentColor = True
        ReadOnly = False
        TabOrder = 3
        Text = '<ϯ_λ_��_��>'
        Visible = False
        WorkView = WorkView
        FieldName = 'ϯ_λ_��_��'
        SynchronizeWhenExit = True
      end
      object WVEdit5: TWVEdit
        Left = 108
        Top = 80
        Width = 100
        Height = 20
        Color = clInfoBk
        ImeName = ''
        MaxLength = 10
        ReadOnly = False
        TabOrder = 1
        Text = '<��������>'
        WorkView = WorkView
        FieldName = '��������'
        SynchronizeWhenExit = True
      end
      object WVEdit6: TWVEdit
        Left = 108
        Top = 120
        Width = 100
        Height = 20
        Color = clInfoBk
        ImeName = ''
        MaxLength = 10
        ReadOnly = False
        TabOrder = 2
        Text = '<��������ֵ>'
        WorkView = WorkView
        FieldName = '��������ֵ'
        SynchronizeWhenExit = True
      end
      object WVComboBox1: TWVComboBox
        Left = 108
        Top = 40
        Width = 101
        Height = 20
        Color = clInfoBk
        ImeName = ''
        ItemHeight = 12
        TabOrder = 0
        Text = '<ϯ_λ_��_��>'
        OnExit = WVComboBox1Exit
        WorkView = WorkView
        FieldName = 'ϯ_λ_��_��'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-23'
      end
      object WVEdit_snote: TWVEdit
        Left = 108
        Top = 160
        Width = 277
        Height = 20
        Color = clWhite
        ImeName = ''
        ReadOnly = False
        TabOrder = 5
        Text = '<����>'
        WorkView = WorkView
        FieldName = '����'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 260
    Top = 383
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
        DefaultValue = '3'
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
        DefaultValue = '2'
      end
      item
        Name = '��ѯ.��ѯ��־��1�����㣻2�����ף�'
        Caption = '��ѯ.��ѯ��־��1�����㣻2�����ף�'
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
        Name = '��ѯ.ϯ_λ'
        Caption = '��ѯ.ϯ_λ'
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
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
        Name = 'ϯ_λ_��_��'
        Caption = 'ϯ_λ_��_��'
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
        DataField = 'sserial2'
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
        Checker.MinLength = 1
        Checker.MaxLength = 10
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sserial1'
      end
      item
        Name = '��������ֵ'
        Caption = '��������ֵ'
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
        DataField = 'sserial0'
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
        Name = '����'
        Caption = '����'
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
        DataField = 'snote'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.��ѯ��־��1�����㣻2�����ף�|��ѯ.ϯλ����|��ѯ.��������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|ϯλ����|��������|��������ֵ|����Ա|'
        GroupIndex = 1
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Top = 344
  end
  inherited QueryRequest: TWVRequest
    ID = '���������ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ѯ��־��1�����㣻2�����ף�'
        FieldName = '��ѯ.��ѯ��־��1�����㣻2�����ף�'
        DefaultValue = '1'
      end
      item
        ParamName = 'ϯλ����'
        FieldName = '��ѯ.ϯ_λ'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end>
    Left = 472
    Top = 344
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 164
    Top = 383
  end
  inherited AddRequest: TWVRequest
    ID = '���ý������'
    Bindings = <
      item
        ParamName = 'ϯλ����'
        FieldName = 'ϯ_λ_��_��'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��������ֵ'
        FieldName = '��������ֵ'
      end
      item
        ParamName = '�������'
        FieldName = '�������.����'
        DefaultValue = '1'
      end>
    Top = 360
  end
  inherited DeleteRequest: TWVRequest
    ID = '���ý������'
    Bindings = <
      item
        ParamName = 'ϯλ����'
        FieldName = 'ϯ_λ_��_��'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��������ֵ'
        FieldName = '��������ֵ'
      end
      item
        ParamName = '�������'
        FieldName = '�������.ɾ��'
        DefaultValue = '3'
      end>
    Left = 216
    Top = 344
  end
  inherited ChangeRequest: TWVRequest
    ID = '���ý������'
    Bindings = <
      item
        ParamName = 'ϯλ����'
        FieldName = 'ϯ_λ_��_��'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��������ֵ'
        FieldName = '��������ֵ'
      end
      item
        ParamName = '�������'
        FieldName = '�������.�޸�'
        DefaultValue = '2'
      end>
    Left = 384
    Top = 336
  end
  inherited WVDataSource: TWVDataSource
    Left = 540
    Top = 375
  end
  inherited alDatasetActions: TActionList
    Left = 332
    Top = 396
  end
end
