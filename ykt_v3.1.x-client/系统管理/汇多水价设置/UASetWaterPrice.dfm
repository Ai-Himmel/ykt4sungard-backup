inherited faqhSetWaterPrice: TfaqhSetWaterPrice
  Width = 681
  Height = 477
  Caption = '���ˮ������'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 677
        TabOrder = 1
        inherited btnAdd: TBitBtn [0]
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 499
          Enabled = False
          TabOrder = 4
        end
        inherited btnQuery: TBitBtn [2]
          Left = 322
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Width = 161
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
        TabOrder = 3
      end
      inherited Grid: TRzDBGrid
        Top = 49
        Width = 677
        Height = 375
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�շ����'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ˮ��1(��λ:��)'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ˮ��2(��λ:��)'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ˮ��3(��λ:��)'
            Width = 100
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
          Left = 18
          Top = 10
          Width = 48
          Height = 12
          Caption = '�շ����'
        end
        object cbbFee: TWVComboBox
          Left = 72
          Top = 5
          Width = 131
          Height = 20
          Style = csDropDownList
          Color = clBtnHighlight
          ItemHeight = 0
          TabOrder = 0
          Text = '<��ѯ.�շ����>'
          WorkView = WorkView
          FieldName = '��ѯ.�շ����'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-44'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label6: TLabel [0]
        Left = 42
        Top = 100
        Width = 48
        Height = 12
        Caption = '�շ����'
      end
      object Label7: TLabel [1]
        Left = 60
        Top = 137
        Width = 30
        Height = 12
        Caption = 'ˮ��1'
      end
      object Label8: TLabel [2]
        Left = 60
        Top = 175
        Width = 30
        Height = 12
        Caption = 'ˮ��2'
      end
      object Label1: TLabel [3]
        Left = 60
        Top = 212
        Width = 30
        Height = 12
        Caption = 'ˮ��3'
      end
      object Label3: TLabel [4]
        Left = 252
        Top = 138
        Width = 48
        Height = 12
        AutoSize = False
        Caption = '��λ����'
      end
      object Label4: TLabel [5]
        Left = 252
        Top = 176
        Width = 48
        Height = 12
        AutoSize = False
        Caption = '��λ����'
      end
      object Label5: TLabel [6]
        Left = 252
        Top = 212
        Width = 48
        Height = 12
        AutoSize = False
        Caption = '��λ����'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
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
      object cbbFeeType: TWVComboBox
        Left = 97
        Top = 96
        Width = 151
        Height = 20
        Style = csDropDownList
        Color = clBtnHighlight
        ItemHeight = 12
        TabOrder = 1
        WorkView = WorkView
        FieldName = '�շ����'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-44'
      end
      object edtP3: TWVEdit
        Left = 97
        Top = 208
        Width = 151
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 2
        Text = '<ˮ��3>'
        WorkView = WorkView
        FieldName = 'ˮ��3'
        SynchronizeWhenExit = True
      end
      object edtP2: TWVEdit
        Left = 97
        Top = 171
        Width = 151
        Height = 20
        Color = clBtnHighlight
        MaxLength = 22
        ReadOnly = False
        TabOrder = 3
        Text = '<ˮ��2>'
        WorkView = WorkView
        FieldName = 'ˮ��2'
        SynchronizeWhenExit = True
      end
      object edtP1: TWVEdit
        Left = 97
        Top = 133
        Width = 151
        Height = 20
        Color = clBtnHighlight
        MaxLength = 22
        ReadOnly = False
        TabOrder = 4
        Text = '<ˮ��1>'
        WorkView = WorkView
        FieldName = 'ˮ��1'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 428
    Top = 279
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
        Name = '������־'
        Caption = '������־'
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
      end
      item
        Name = 'ˮ��1'
        Caption = 'ˮ��1'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = 'ˮ��2'
        Caption = 'ˮ��2'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = 'ˮ��3'
        Caption = 'ˮ��3'
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
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol2'
      end>
    InvalidColor = clBtnHighlight
    Left = 360
    Top = 240
  end
  inherited QueryRequest: TWVRequest
    ID = '���ˮ�����ò�ѯ'
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
      end>
    Left = 504
    Top = 240
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '-44'
      end>
    Left = 388
    Top = 279
  end
  inherited AddRequest: TWVRequest
    ID = '���ˮ������'
    Bindings = <
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = 'ˮ��1'
        FieldName = 'ˮ��1'
      end
      item
        ParamName = 'ˮ��2'
        FieldName = 'ˮ��2'
      end
      item
        ParamName = 'ˮ��3'
        FieldName = 'ˮ��3'
      end>
    Left = 392
    Top = 240
  end
  inherited DeleteRequest: TWVRequest
    ID = '���ˮ������'
    Bindings = <
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = 'ˮ��1'
        FieldName = 'ˮ��1'
      end
      item
        ParamName = 'ˮ��2'
        FieldName = 'ˮ��2'
      end
      item
        ParamName = 'ˮ��3'
        FieldName = 'ˮ��3'
      end>
    Left = 432
    Top = 240
  end
  inherited ChangeRequest: TWVRequest
    ID = '���ˮ������'
    Bindings = <
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = 'ˮ��1'
        FieldName = 'ˮ��1'
      end
      item
        ParamName = 'ˮ��2'
        FieldName = 'ˮ��2'
      end
      item
        ParamName = 'ˮ��3'
        FieldName = 'ˮ��3'
      end>
    Left = 472
    Top = 240
  end
  inherited WVDataSource: TWVDataSource
    Left = 516
    Top = 279
  end
  inherited alDatasetActions: TActionList
    Left = 476
    Top = 276
  end
end
