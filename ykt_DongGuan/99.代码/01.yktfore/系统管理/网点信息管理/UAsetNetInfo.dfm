inherited faqhsetNetInfo: TfaqhsetNetInfo
  Width = 706
  Height = 477
  Caption = '������Ϣ����'
  inherited pcPages: TRzPageControl
    Width = 706
    Height = 477
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 702
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 436
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 524
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 347
        end
        inherited btnDelete: TBitBtn
          Left = 613
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 104
          Width = 177
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 702
      end
      inherited Grid: TRzDBGrid
        Top = 57
        Width = 702
        Height = 367
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'sbranch_code0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���д���'
            Width = -1
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sbank_acc'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�����˺�'
            Width = -1
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sbankname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�����ʻ���'
            Width = -1
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ϵ��'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�绰'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ֻ�'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ַ'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spost_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 60
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 702
        Height = 39
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label1: TLabel
          Left = 18
          Top = 10
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label5: TLabel
          Left = 242
          Top = 10
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label6: TLabel
          Left = 442
          Top = 10
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object WVEdit5: TWVEdit
          Left = 292
          Top = 6
          Width = 133
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.��������>'
          WorkView = WorkView
          FieldName = '��ѯ.��������'
        end
        object WVComboBox1: TWVComboBox
          Left = 496
          Top = 6
          Width = 121
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '��ѯ.��������'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*107'
        end
        object WVComboBox2: TWVComboBox
          Left = 72
          Top = 6
          Width = 145
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '��ѯ.��������'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-28'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label16: TLabel [0]
        Left = 42
        Top = 82
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Label17: TLabel [1]
        Left = 54
        Top = 44
        Width = 36
        Height = 12
        Caption = '�����'
      end
      object Label20: TLabel [2]
        Left = 252
        Top = 44
        Width = 54
        Height = 12
        Caption = '��������*'
      end
      object Label21: TLabel [3]
        Left = 479
        Top = 44
        Width = 54
        Height = 12
        Caption = '��������*'
      end
      object Label22: TLabel [4]
        Left = 58
        Top = 348
        Width = 48
        Height = 12
        Caption = '���д���'
        Visible = False
      end
      object Label23: TLabel [5]
        Left = 274
        Top = 348
        Width = 48
        Height = 12
        Caption = '�����˺�'
        Visible = False
      end
      object Label24: TLabel [6]
        Left = 489
        Top = 348
        Width = 60
        Height = 12
        Caption = '�����ʻ���'
        Visible = False
      end
      object Label25: TLabel [7]
        Left = 54
        Top = 124
        Width = 36
        Height = 12
        Caption = '��ϵ��'
      end
      object Label26: TLabel [8]
        Left = 282
        Top = 124
        Width = 24
        Height = 12
        Caption = '�绰'
      end
      object Label27: TLabel [9]
        Left = 509
        Top = 124
        Width = 24
        Height = 12
        Caption = '�ֻ�'
      end
      object Label28: TLabel [10]
        Left = 66
        Top = 164
        Width = 24
        Height = 12
        Caption = '����'
      end
      object Label29: TLabel [11]
        Left = 66
        Top = 204
        Width = 24
        Height = 12
        Caption = '��ַ'
      end
      object Label2: TLabel [12]
        Left = 258
        Top = 164
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Label3: TLabel [13]
        Left = 282
        Top = 82
        Width = 24
        Height = 12
        Caption = '����'
      end
      object Label4: TLabel [14]
        Left = 485
        Top = 82
        Width = 48
        Height = 12
        Caption = '��������'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 702
        TabOrder = 16
        inherited btnOK: TBitBtn
          Left = 530
        end
        inherited btnCancel: TBitBtn
          Left = 618
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtNetId: TWVDigitalEdit
        Left = 100
        Top = 40
        Width = 137
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
        FieldName = 'վ���'
        SynchronizeByValue = True
      end
      object edtName: TWVEdit
        Left = 317
        Top = 40
        Width = 151
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<��������>'
        WorkView = WorkView
        FieldName = '��������'
        SynchronizeWhenExit = True
      end
      object WVEdit23: TWVEdit
        Left = 333
        Top = 342
        Width = 151
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 7
        Text = '<�����˺�>'
        Visible = False
        WorkView = WorkView
        FieldName = '�����˺�'
        SynchronizeWhenExit = True
      end
      object WVEdit24: TWVEdit
        Left = 555
        Top = 342
        Width = 130
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 8
        Text = '<�����ʻ���>'
        Visible = False
        WorkView = WorkView
        FieldName = '�����ʻ���'
        SynchronizeWhenExit = True
      end
      object WVEdit25: TWVEdit
        Left = 100
        Top = 119
        Width = 137
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 9
        Text = '<��ϵ��>'
        WorkView = WorkView
        FieldName = '��ϵ��'
        SynchronizeWhenExit = True
      end
      object WVEdit26: TWVEdit
        Left = 317
        Top = 119
        Width = 151
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 10
        Text = '<�绰>'
        WorkView = WorkView
        FieldName = '�绰'
        SynchronizeWhenExit = True
      end
      object WVEdit27: TWVEdit
        Left = 539
        Top = 119
        Width = 130
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 11
        Text = '<�ֻ�>'
        WorkView = WorkView
        FieldName = '�ֻ�'
        SynchronizeWhenExit = True
      end
      object WVEdit28: TWVEdit
        Left = 100
        Top = 160
        Width = 137
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 12
        Text = '<����>'
        WorkView = WorkView
        FieldName = '����'
        SynchronizeWhenExit = True
      end
      object WVEdit29: TWVEdit
        Left = 100
        Top = 200
        Width = 368
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 14
        Text = '<��ַ>'
        WorkView = WorkView
        FieldName = '��ַ'
        SynchronizeWhenExit = True
      end
      object WVComboBox4: TWVComboBox
        Left = 100
        Top = 78
        Width = 137
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView
        FieldName = '��������'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-28'
      end
      object cbbNetType: TWVComboBox
        Left = 539
        Top = 38
        Width = 130
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 2
        WorkView = WorkView
        FieldName = '��������'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*107'
      end
      object WVComboBox3: TWVComboBox
        Left = 116
        Top = 342
        Width = 137
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 6
        Visible = False
        WorkView = WorkView
        FieldName = '���д���'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*218'
      end
      object cbbNetId: TWVComboBox
        Left = 83
        Top = 318
        Width = 130
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 15
        Visible = False
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*-2'
      end
      object WVEdit1: TWVEdit
        Left = 317
        Top = 160
        Width = 151
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 13
        Text = '<��������>'
        WorkView = WorkView
        FieldName = '��������'
        SynchronizeWhenExit = True
      end
      object WVComboBox5: TWVComboBox
        Left = 317
        Top = 78
        Width = 151
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 4
        WorkView = WorkView
        FieldName = '����'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*231'
      end
      object WVEdit2: TWVEdit
        Left = 539
        Top = 78
        Width = 130
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 5
        Text = '<��������>'
        WorkView = WorkView
        FieldName = '��������'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 356
    Top = 351
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
        Name = '��ѯ.վ���'
        Caption = '��ѯ.վ���'
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
        Name = '��ѯ.����Ա'
        Caption = '��ѯ.����Ա'
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
        Name = '��ѯ.���д���'
        Caption = '��ѯ.���д���'
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
        Name = '��ѯ.�����˺�'
        Caption = '��ѯ.�����˺�'
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
        Name = '��ѯ.�����ʻ���'
        Caption = '��ѯ.�����ʻ���'
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
        Name = '��ѯ.��ϵ��'
        Caption = '��ѯ.��ϵ��'
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
        Name = '��ѯ.�绰'
        Caption = '��ѯ.�绰'
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
        Name = '��ѯ.�ֻ�'
        Caption = '��ѯ.�ֻ�'
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
        Name = '��ѯ.����'
        Caption = '��ѯ.����'
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
        Name = '��ѯ.��ַ'
        Caption = '��ѯ.��ַ'
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
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sbranch_code0'
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lbank_acc_type2'
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'semp_no'
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
        DataField = 'sstatus0'
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
        DataField = 'vsvarstr2'
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
        DataField = 'sstatus1'
      end
      item
        Name = '���д���'
        Caption = '���д���'
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
        DataField = 'sbank_code'
      end
      item
        Name = '�����˺�'
        Caption = '�����˺�'
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
        DataField = 'sbank_acc'
      end
      item
        Name = '�����ʻ���'
        Caption = '�����ʻ���'
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
        DataField = 'sbankname'
      end
      item
        Name = '��ϵ��'
        Caption = '��ϵ��'
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
        DataField = 'sall_name'
      end
      item
        Name = '�绰'
        Caption = '�绰'
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
        DataField = 'sphone'
      end
      item
        Name = '�ֻ�'
        Caption = '�ֻ�'
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
        DataField = 'sphone2'
      end
      item
        Name = '����'
        Caption = '����'
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
        DataField = 'sphone3'
      end
      item
        Name = '��ַ'
        Caption = '��ַ'
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
        DataField = 'scusttypes'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        DataField = 'spost_code'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        DataField = 'snote2'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.��������|��ѯ.վ���|��ѯ.����Ա|��ѯ.��������|��ѯ.������' +
          '��|��ѯ.��������|��ѯ.���д���|��ѯ.�����˺�|��ѯ.�����ʻ���|��' +
          'ѯ.��ϵ��|��ѯ.�绰|��ѯ.�ֻ�|��ѯ.����|��ѯ.��ַ|��ѯ.��������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|��������|վ���|����Ա|��������|��������|��������|���д���|����' +
          '�˺�|�����ʻ���|��ϵ��|�绰|�ֻ�|����|��ַ|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 280
    Top = 312
  end
  inherited QueryRequest: TWVRequest
    ID = '������Ϣ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = 'վ���'
        FieldName = '��ѯ.վ���'
      end
      item
        ParamName = '����Ա'
        FieldName = '��ѯ.����Ա'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '���д���'
        FieldName = '��ѯ.���д���'
      end
      item
        ParamName = '�����˺�'
        FieldName = '��ѯ.�����˺�'
      end
      item
        ParamName = '�����ʻ���'
        FieldName = '��ѯ.�����ʻ���'
      end
      item
        ParamName = '��ϵ��'
        FieldName = '��ѯ.��ϵ��'
      end
      item
        ParamName = '�绰'
        FieldName = '��ѯ.�绰'
      end
      item
        ParamName = '�ֻ�'
        FieldName = '��ѯ.�ֻ�'
      end
      item
        ParamName = '����'
        FieldName = '��ѯ.����'
      end
      item
        ParamName = '��ַ'
        FieldName = '��ѯ.��ַ'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end>
    Left = 440
    Top = 312
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '107'
      end
      item
        FieldName = 'sbank_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '218'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'idobjects'
        DataPresentParam = '-28'
      end
      item
        FieldName = 'snote2'
        DataPresentType = 'idobjects'
        DataPresentParam = '231'
      end>
    Left = 316
    Top = 351
  end
  inherited AddRequest: TWVRequest
    ID = '������Ϣ����'
    Bindings = <
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'վ���'
        FieldName = 'վ���'
      end
      item
        ParamName = '����Ա'
        FieldName = '����Ա'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '���д���'
        FieldName = '���д���'
      end
      item
        ParamName = '�����˺�'
        FieldName = '�����˺�'
      end
      item
        ParamName = '�����ʻ���'
        FieldName = '�����ʻ���'
      end
      item
        ParamName = '��ϵ��'
        FieldName = '��ϵ��'
      end
      item
        ParamName = '�绰'
        FieldName = '�绰'
      end
      item
        ParamName = '�ֻ�'
        FieldName = '�ֻ�'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '��ַ'
        FieldName = '��ַ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end>
    Left = 320
    Top = 312
  end
  inherited DeleteRequest: TWVRequest
    ID = '������Ϣ����'
    Bindings = <
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'վ���'
        FieldName = 'վ���'
      end
      item
        ParamName = '����Ա'
        FieldName = '����Ա'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '���д���'
        FieldName = '���д���'
      end
      item
        ParamName = '�����˺�'
        FieldName = '�����˺�'
      end
      item
        ParamName = '�����ʻ���'
        FieldName = '�����ʻ���'
      end
      item
        ParamName = '��ϵ��'
        FieldName = '��ϵ��'
      end
      item
        ParamName = '�绰'
        FieldName = '�绰'
      end
      item
        ParamName = '�ֻ�'
        FieldName = '�ֻ�'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '��ַ'
        FieldName = '��ַ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end>
    Left = 360
    Top = 312
  end
  inherited ChangeRequest: TWVRequest
    ID = '������Ϣ����'
    Bindings = <
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'վ���'
        FieldName = 'վ���'
      end
      item
        ParamName = '����Ա'
        FieldName = '����Ա'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '���д���'
        FieldName = '���д���'
      end
      item
        ParamName = '�����˺�'
        FieldName = '�����˺�'
      end
      item
        ParamName = '�����ʻ���'
        FieldName = '�����ʻ���'
      end
      item
        ParamName = '��ϵ��'
        FieldName = '��ϵ��'
      end
      item
        ParamName = '�绰'
        FieldName = '�绰'
      end
      item
        ParamName = '�ֻ�'
        FieldName = '�ֻ�'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '��ַ'
        FieldName = '��ַ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end>
    Left = 400
    Top = 312
  end
  inherited WVDataSource: TWVDataSource
    Left = 436
    Top = 351
  end
  inherited alDatasetActions: TActionList
    Left = 396
    Top = 348
  end
end
