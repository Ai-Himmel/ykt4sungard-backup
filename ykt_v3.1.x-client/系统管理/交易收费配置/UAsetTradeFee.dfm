inherited faqhsetTradeFee: TfaqhsetTradeFee
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
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 88
          Width = 169
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 81
        Width = 677
        Height = 343
        TabOrder = 2
        Columns = <
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
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lsafe_level'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�շѷ�ʽ'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�շѽ��'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�շ�˳��'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            PickList.Strings = ()
            Title.Caption = '�շ�˵��'
            Width = 200
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 63
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label2: TLabel
          Left = 26
          Top = 10
          Width = 48
          Height = 12
          Caption = '�շ����'
        end
        object Label3: TLabel
          Left = 238
          Top = 10
          Width = 36
          Height = 12
          Caption = '������'
        end
        object Label4: TLabel
          Left = 422
          Top = 10
          Width = 36
          Height = 12
          Caption = '������'
        end
        object Label5: TLabel
          Left = 26
          Top = 34
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label6: TLabel
          Left = 226
          Top = 34
          Width = 48
          Height = 12
          Caption = '�շѷ�ʽ'
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
          ItemsDataEntry = '*-44'
        end
        object WVComboBox1: TWVComboBox
          Left = 84
          Top = 29
          Width = 131
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '��ѯ.��������'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-7'
        end
        object WVComboBox2: TWVComboBox
          Left = 284
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
          ItemsDataEntry = '*-6'
        end
        object WVComboBox3: TWVComboBox
          Left = 284
          Top = 29
          Width = 131
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '��ѯ.�շѷ�ʽ'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*120'
        end
        object WVComboBox5: TWVComboBox
          Left = 468
          Top = 5
          Width = 131
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '��ѯ.������'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-56'
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
      object Label12: TLabel [1]
        Left = 72
        Top = 140
        Width = 42
        Height = 12
        Caption = '������*'
      end
      object Label13: TLabel [2]
        Left = 72
        Top = 76
        Width = 42
        Height = 12
        Caption = '������*'
      end
      object Label14: TLabel [3]
        Left = 60
        Top = 172
        Width = 54
        Height = 12
        Caption = '��������*'
      end
      object Label15: TLabel [4]
        Left = 65
        Top = 204
        Width = 48
        Height = 12
        Caption = '�շѷ�ʽ'
      end
      object lblBit: TLabel [5]
        Left = 65
        Top = 236
        Width = 48
        Height = 12
        Caption = '�շѽ��'
      end
      object Label1: TLabel [6]
        Left = 68
        Top = 348
        Width = 48
        Height = 12
        Caption = '�շ�˳��'
        Visible = False
      end
      object lbl1: TLabel [7]
        Left = 72
        Top = 40
        Width = 189
        Height = 14
        Caption = '��ʾ�������ֶβ�����Ĭ��Ϊ0'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 7
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
      object edtMoney: TWVDigitalEdit
        Left = 124
        Top = 231
        Width = 131
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 5
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '�շѽ��'
        SynchronizeByValue = True
      end
      object cbbTradeCode: TWVComboBox
        Left = 124
        Top = 133
        Width = 131
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 2
        WorkView = WorkView
        FieldName = '������'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-6'
      end
      object cbbFeeType: TWVComboBox
        Left = 124
        Top = 198
        Width = 131
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 4
        OnChange = cbbFeeTypeChange
        WorkView = WorkView
        FieldName = '�շѷ�ʽ'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*120'
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
        ItemsDataEntry = '*-56'
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
        ItemsDataEntry = '*-44'
      end
      object cbbTradeType: TWVComboBox
        Left = 124
        Top = 166
        Width = 131
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 3
        OnChange = cbbTradeTypeChange
        WorkView = WorkView
        FieldName = '��������'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-7'
      end
      object WVComboBox11: TWVComboBox
        Left = 124
        Top = 343
        Width = 131
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 6
        Visible = False
        WorkView = WorkView
        FieldName = '�շ�˳��'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-28'
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
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
        Name = '��ѯ.�շѷ�ʽ'
        Caption = '��ѯ.�շѷ�ʽ'
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
        Name = '��ѯ.�շѽ��'
        Caption = '��ѯ.�շѽ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
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
        Name = '��ѯ.�շ�˳��'
        Caption = '��ѯ.�շ�˳��'
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
        DataField = 'lvol0'
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
        Name = '��������'
        Caption = '��������'
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
        Name = '�շѷ�ʽ'
        Caption = '�շѷ�ʽ'
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
        Name = '�շѽ��'
        Caption = '�շѽ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'damt0'
      end
      item
        Name = '�շ�˳��'
        Caption = '�շ�˳��'
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
        DataField = 'Lvol3'
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
    ID = '�����շѲ�ѯ'
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
      end
      item
        ParamName = '������'
        FieldName = '��ѯ.������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '�շѷ�ʽ'
        FieldName = '��ѯ.�շѷ�ʽ'
      end
      item
        ParamName = '�շѽ��'
        FieldName = '��ѯ.�շѽ��'
      end
      item
        ParamName = '�շ�˳��'
        FieldName = '��ѯ.�շ�˳��'
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
        FieldName = 'lvol0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-6'
      end
      item
        FieldName = 'lsafe_level'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-56'
      end
      item
        FieldName = 'lvol1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-7'
      end
      item
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '120'
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
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�շѷ�ʽ'
        FieldName = '�շѷ�ʽ'
      end
      item
        ParamName = '�շѽ��'
        FieldName = '�շѽ��'
      end
      item
        ParamName = '�շ�˳��'
        FieldName = '�շ�˳��'
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
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�շѷ�ʽ'
        FieldName = '�շѷ�ʽ'
      end
      item
        ParamName = '�շѽ��'
        FieldName = '�շѽ��'
      end
      item
        ParamName = '�շ�˳��'
        FieldName = '�շ�˳��'
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
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�շѷ�ʽ'
        FieldName = '�շѷ�ʽ'
      end
      item
        ParamName = '�շѽ��'
        FieldName = '�շѽ��'
      end
      item
        ParamName = '�շ�˳��'
        FieldName = '�շ�˳��'
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
