inherited faqhSetModuleAuth: TfaqhSetModuleAuth
  Width = 681
  Height = 477
  Caption = '����Ȩ��ģ��'
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
          Left = 416
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 502
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 330
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
        Align = alNone
        TabOrder = 2
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 677
        Height = 391
        Columns = <
          item
            Expanded = False
            FieldName = 'sbank_code'
            PickList.Strings = ()
            Title.Caption = 'ģ�����'
            Width = 134
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth2'
            PickList.Strings = ()
            Title.Caption = 'ģ������'
            Width = 181
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 677
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Labelmodule_code2: TLabel
          Left = 42
          Top = 10
          Width = 48
          Height = 12
          Caption = 'Ȩ��ģ��'
        end
        object WVEditmodule_code2: TWVEdit
          Left = 100
          Top = 6
          Width = 100
          Height = 20
          Enabled = False
          ParentColor = True
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.ģ�����>'
          Visible = False
          WorkView = WorkView
          FieldName = '��ѯ.ģ�����'
        end
        object WVComboBox1: TWVComboBox
          Left = 100
          Top = 6
          Width = 125
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 0
          TabOrder = 1
          Text = '<��ѯ.ģ�����>'
          WorkView = WorkView
          FieldName = '��ѯ.ģ�����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-29'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 2
        inherited btnOK: TBitBtn
          Left = 501
        end
        inherited btnCancel: TBitBtn
          Left = 589
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object Panel2: TPanel
        Left = 0
        Top = 105
        Width = 677
        Height = 313
        Align = alClient
        BevelOuter = bvNone
        ParentColor = True
        TabOrder = 1
        inline faAuth1: TfaAuth
          Left = 83
          Width = 594
          Height = 313
          Align = alClient
          TabOrder = 1
          inherited TreeView: TTreeView
            Width = 594
            Height = 313
            OnKeyDown = faAuth1TreeViewKeyDown
          end
          inherited ImageList: TImageList
            Left = 184
            Top = 32
          end
        end
        object Panel4: TPanel
          Left = 0
          Top = 0
          Width = 83
          Height = 313
          Align = alLeft
          BevelOuter = bvNone
          ParentColor = True
          TabOrder = 0
          object Label1: TLabel
            Left = 25
            Top = 3
            Width = 48
            Height = 12
            Caption = '�˵�Ȩ��'
          end
        end
      end
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 677
        Height = 105
        Align = alTop
        BevelOuter = bvNone
        ParentColor = True
        TabOrder = 0
        object Labelmodule_name4: TLabel
          Left = 26
          Top = 68
          Width = 48
          Height = 12
          Caption = 'ģ������'
        end
        object Labelmodule_code3: TLabel
          Left = 26
          Top = 28
          Width = 48
          Height = 12
          Caption = 'ģ�����'
        end
        object WVEditmodule_name4: TWVEdit
          Left = 84
          Top = 64
          Width = 100
          Height = 20
          Color = clInfoBk
          MaxLength = 20
          ReadOnly = False
          TabOrder = 1
          Text = '<ģ������>'
          WorkView = WorkView
          FieldName = 'ģ������'
          SynchronizeWhenExit = True
        end
        object WVEditmodule_code3: TWVEdit
          Left = 84
          Top = 24
          Width = 100
          Height = 20
          Color = clInfoBk
          MaxLength = 6
          ReadOnly = False
          TabOrder = 0
          Text = '<ģ�����>'
          WorkView = WorkView
          FieldName = 'ģ�����'
          SynchronizeWhenExit = True
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 276
    Top = 199
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
        Name = '��ѯ.ģ�����'
        Caption = '��ѯ.ģ�����'
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
        Name = 'ģ�����'
        Caption = 'ģ�����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 1
        Checker.MaxLength = 6
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sbank_code'
      end
      item
        Name = 'ģ������'
        Caption = 'ģ������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 1
        Checker.MaxLength = 20
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'scust_auth2'
      end
      item
        Name = '�˵�Ȩ��1'
        Caption = '�˵�Ȩ��1'
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
        Name = '�˵�Ȩ��2'
        Caption = '�˵�Ȩ��2'
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
        DataField = 'vsvarstr1'
      end
      item
        Name = '�˵�Ȩ��3'
        Caption = '�˵�Ȩ��3'
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
        DataField = 'vsvarstr2'
      end
      item
        Name = '�˵�Ȩ��4'
        Caption = '�˵�Ȩ��4'
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
        DataField = 'vsvarstr3'
      end
      item
        Name = '����Ȩ��'
        Caption = '����Ȩ��'
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
        DataField = 'usset1'
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
        MonitorValueChangedFields = '|ģ�����|ģ������|�˵�Ȩ��|����Ȩ��|'
        GroupIndex = 1
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 192
    Top = 160
  end
  inherited QueryRequest: TWVRequest
    ID = 'Ȩ��ģ���ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ģ�����'
        FieldName = '��ѯ.ģ�����'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 352
    Top = 160
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 236
    Top = 199
  end
  inherited AddRequest: TWVRequest
    ID = '����Ȩ��ģ��'
    Bindings = <
      item
        ParamName = 'ģ�����'
        FieldName = 'ģ�����'
      end
      item
        ParamName = 'ģ������'
        FieldName = 'ģ������'
      end
      item
        ParamName = '����Ȩ��'
        FieldName = '����Ȩ��'
      end
      item
        ParamName = '�˵�Ȩ��1'
        FieldName = '�˵�Ȩ��1'
      end
      item
        ParamName = '�˵�Ȩ��2'
        FieldName = '�˵�Ȩ��2'
      end
      item
        ParamName = '�˵�Ȩ��3'
        FieldName = '�˵�Ȩ��3'
      end
      item
        ParamName = '�˵�Ȩ��4'
        FieldName = '�˵�Ȩ��4'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 232
    Top = 160
  end
  inherited DeleteRequest: TWVRequest
    ID = '����Ȩ��ģ��'
    Bindings = <
      item
        ParamName = 'ģ�����'
        FieldName = 'ģ�����'
      end
      item
        ParamName = 'ģ������'
        FieldName = 'ģ������'
      end
      item
        ParamName = '����Ȩ��'
        FieldName = '����Ȩ��'
      end
      item
        ParamName = '�˵�Ȩ��1'
        FieldName = '�˵�Ȩ��1'
      end
      item
        ParamName = '�˵�Ȩ��2'
        FieldName = '�˵�Ȩ��2'
      end
      item
        ParamName = '�˵�Ȩ��3'
        FieldName = '�˵�Ȩ��3'
      end
      item
        ParamName = '�˵�Ȩ��4'
        FieldName = '�˵�Ȩ��4'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 272
    Top = 160
  end
  inherited ChangeRequest: TWVRequest
    ID = '����Ȩ��ģ��'
    Bindings = <
      item
        ParamName = 'ģ�����'
        FieldName = 'ģ�����'
      end
      item
        ParamName = 'ģ������'
        FieldName = 'ģ������'
      end
      item
        ParamName = '����Ȩ��'
        FieldName = '����Ȩ��'
      end
      item
        ParamName = '�˵�Ȩ��1'
        FieldName = '�˵�Ȩ��1'
      end
      item
        ParamName = '�˵�Ȩ��2'
        FieldName = '�˵�Ȩ��2'
      end
      item
        ParamName = '�˵�Ȩ��3'
        FieldName = '�˵�Ȩ��3'
      end
      item
        ParamName = '�˵�Ȩ��4'
        FieldName = '�˵�Ȩ��4'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 312
    Top = 160
  end
  inherited WVDataSource: TWVDataSource
    Left = 356
    Top = 199
  end
  inherited alDatasetActions: TActionList
    Left = 316
    Top = 196
  end
end
