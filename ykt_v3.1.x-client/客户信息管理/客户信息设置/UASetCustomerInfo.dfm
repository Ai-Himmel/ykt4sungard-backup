inherited faqhSetCustomerInfo: TfaqhSetCustomerInfo
  Width = 788
  Height = 500
  Caption = '�ͻ���Ϣ����'
  inherited pcPages: TRzPageControl
    Width = 788
    Height = 500
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 441
        Width = 784
        Height = 36
        TabOrder = 3
        inherited btnDelete: TBitBtn [0]
          Left = 702
          Top = 5
        end
        inherited btnAdd: TBitBtn
          Left = 532
          Top = 5
        end
        inherited btnChange: TBitBtn
          Left = 617
          Top = 5
        end
        inherited btnQuery: TBitBtn [3]
          Left = 447
          Top = 5
        end
        inherited btnViewDetail: TBitBtn
          Left = 10
          Top = 5
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Top = 10
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 784
      end
      inherited Grid: TRzDBGrid
        Top = 97
        Width = 784
        Height = 344
        DragCursor = crHandPoint
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'sbranch_code0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'У��'
            Width = 83
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ͻ���'
            Width = 62
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ѧ/����'
            Width = 83
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ͻ�����'
            Width = 96
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smarket_code2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�Ա�'
            Width = 66
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ͻ����'
            Width = 74
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�շ����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����ȫ��'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_no2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'רҵ'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scard1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�༶'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '״̬'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ע������'
            Width = 93
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smarket_code'
            PickList.Strings = ()
            Title.Caption = '֤������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '֤��֤��'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snation_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_type2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ϵ�绰'
            Width = 60
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
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ϵ��ַ'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ѧ����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'Ԥ��ע������'
            Width = 70
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 784
        Height = 79
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label1: TLabel
          Left = 54
          Top = 9
          Width = 36
          Height = 12
          Caption = '�ͻ���'
        end
        object WVLabel4: TWVLabel
          Left = 461
          Top = 9
          Width = 48
          Height = 12
          Caption = '�ͻ�����'
        end
        object WVLabel5: TWVLabel
          Left = 263
          Top = 33
          Width = 48
          Height = 12
          Caption = '֤������'
        end
        object WVLabel6: TWVLabel
          Left = 269
          Top = 9
          Width = 42
          Height = 12
          Caption = 'ѧ/����'
        end
        object WVLabel7: TWVLabel
          Left = 263
          Top = 57
          Width = 48
          Height = 12
          Caption = 'ע������'
        end
        object WVLabel8: TWVLabel
          Left = 42
          Top = 57
          Width = 48
          Height = 12
          Caption = '�ͻ����'
        end
        object WVLabel9: TWVLabel
          Left = 42
          Top = 33
          Width = 48
          Height = 12
          Caption = '�շ����'
        end
        object WVLabel10: TWVLabel
          Left = 473
          Top = 32
          Width = 36
          Height = 12
          Caption = '���κ�'
        end
        object WVLabel11: TWVLabel
          Left = 461
          Top = 56
          Width = 48
          Height = 12
          Caption = '�����༶'
        end
        object WVEdit3: TWVEdit
          Left = 95
          Top = 4
          Width = 120
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.�ͻ���>'
          WorkView = WorkView
          FieldName = '��ѯ.�ͻ���'
        end
        object WVEdit7: TWVEdit
          Left = 519
          Top = 4
          Width = 120
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 2
          Text = '<��ѯ.�ͻ�����>'
          WorkView = WorkView
          FieldName = '��ѯ.�ͻ�����'
        end
        object WVEdit9: TWVEdit
          Left = 319
          Top = 28
          Width = 120
          Height = 20
          Color = clWhite
          MaxLength = 18
          ReadOnly = False
          TabOrder = 4
          Text = '<��ѯ.��ϵ�����֤��>'
          WorkView = WorkView
          FieldName = '��ѯ.��ϵ�����֤��'
        end
        object WVEdit10: TWVEdit
          Left = 319
          Top = 4
          Width = 120
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.��ϵ��ѧ����>'
          WorkView = WorkView
          FieldName = '��ѯ.��ϵ��ѧ����'
        end
        object WVEdit15: TWVEdit
          Left = 319
          Top = 52
          Width = 120
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 7
          Text = '<��ѯ.ע������>'
          WorkView = WorkView
          FieldName = '��ѯ.ע������'
        end
        object WVComboBox1: TWVComboBox
          Left = 95
          Top = 52
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 6
          Text = '<��ѯ.�ͻ����>'
          WorkView = WorkView
          FieldName = '��ѯ.�ͻ����'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-34'
        end
        object WVComboBox5: TWVComboBox
          Left = 95
          Top = 28
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          TabOrder = 3
          Text = '<��ѯ.�շ����>'
          WorkView = WorkView
          FieldName = '��ѯ.�շ����'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-43'
        end
        object WVEdit16: TWVEdit
          Left = 519
          Top = 28
          Width = 120
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 5
          Text = '<��ѯ.���κ�>'
          WorkView = WorkView
          FieldName = '��ѯ.���κ�'
        end
        object WVEdit17: TWVEdit
          Left = 519
          Top = 52
          Width = 120
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 8
          Text = '<��ѯ.�༶>'
          WorkView = WorkView
          FieldName = '��ѯ.�༶'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 62
        Top = 421
        Width = 48
        Height = 12
        Caption = '�ͻ��� *'
        Visible = False
      end
      object Label3: TLabel [1]
        Left = 526
        Top = 44
        Width = 60
        Height = 12
        Caption = '�ͻ���� *'
      end
      object Label4: TLabel [2]
        Left = 74
        Top = 84
        Width = 36
        Height = 12
        Caption = 'У�� *'
      end
      object Label5: TLabel [3]
        Left = 50
        Top = 44
        Width = 60
        Height = 12
        Caption = '�ͻ����� *'
      end
      object Label6: TLabel [4]
        Left = 68
        Top = 124
        Width = 42
        Height = 12
        Caption = 'ѧ/����'
      end
      object Label7: TLabel [5]
        Left = 294
        Top = 84
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Label8: TLabel [6]
        Left = 538
        Top = 203
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Label9: TLabel [7]
        Left = 318
        Top = 124
        Width = 24
        Height = 12
        Caption = '�Ա�'
      end
      object Label10: TLabel [8]
        Left = 86
        Top = 164
        Width = 24
        Height = 12
        Caption = '����'
      end
      object Label11: TLabel [9]
        Left = 538
        Top = 163
        Width = 48
        Height = 12
        Caption = '֤������'
      end
      object Label12: TLabel [10]
        Left = 62
        Top = 204
        Width = 48
        Height = 12
        Caption = '��ϵ�绰'
      end
      object Label13: TLabel [11]
        Left = 64
        Top = 285
        Width = 48
        Height = 12
        Caption = '��ϵ��ַ'
      end
      object Label14: TLabel [12]
        Left = 514
        Top = 242
        Width = 72
        Height = 12
        Caption = 'Ԥ��ע������'
      end
      object WVLabel2: TWVLabel [13]
        Left = 86
        Top = 244
        Width = 24
        Height = 12
        Caption = '�༶'
      end
      object Label17: TLabel [14]
        Left = 282
        Top = 44
        Width = 60
        Height = 12
        Caption = '�շ���� *'
      end
      object Label18: TLabel [15]
        Left = 562
        Top = 84
        Width = 24
        Height = 12
        Caption = 'רҵ'
      end
      object Label15: TLabel [16]
        Left = 562
        Top = 124
        Width = 24
        Height = 12
        Caption = '����'
      end
      object Label19: TLabel [17]
        Left = 294
        Top = 164
        Width = 48
        Height = 12
        Caption = '֤������'
      end
      object Label20: TLabel [18]
        Left = 562
        Top = 282
        Width = 24
        Height = 12
        Caption = '�ʱ�'
      end
      object Label21: TLabel [19]
        Left = 318
        Top = 204
        Width = 24
        Height = 12
        Caption = '�ֻ�'
      end
      object Label22: TLabel [20]
        Left = 294
        Top = 244
        Width = 48
        Height = 12
        Caption = '��У����'
      end
      inherited UIPanel2: TUIPanel
        Top = 441
        Width = 784
        TabOrder = 23
        inherited btnOK: TBitBtn
          Left = 600
          Top = 5
          Enabled = False
          TabOrder = 0
        end
        inherited btnCancel: TBitBtn
          Left = 693
          Top = 5
          TabOrder = 1
        end
        inherited DBNavigator: TRzDBNavigator
          Left = 34
          Hints.Strings = ()
          TabOrder = 2
        end
      end
      object cbbCustType: TWVComboBox
        Left = 592
        Top = 40
        Width = 161
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 2
        WorkView = WorkView
        FieldName = '�ͻ����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-34'
      end
      object WVComboBox4: TWVComboBox
        Left = 121
        Top = 80
        Width = 147
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 7
        WorkView = WorkView
        FieldName = '�ͻ���������'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-27'
      end
      object WVEdit5: TWVEdit
        Left = 121
        Top = 40
        Width = 147
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 0
        Text = '<�ͻ�����>'
        WorkView = WorkView
        FieldName = '�ͻ�����'
        SynchronizeWhenExit = True
      end
      object cbbDept: TWVComboBox
        Left = 353
        Top = 79
        Width = 159
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 5
        WorkView = WorkView
        FieldName = '��ϵ�˰༶���ź�'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-22'
      end
      object WVEdit8: TWVEdit
        Left = 592
        Top = 197
        Width = 161
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 14
        Text = '<��������>'
        WorkView = WorkView
        FieldName = '��������'
        SynchronizeWhenExit = True
      end
      object WVComboBox9: TWVComboBox
        Left = 353
        Top = 118
        Width = 159
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 8
        WorkView = WorkView
        FieldName = '��ϵ���Ա�'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*39'
      end
      object WVComboBox10: TWVComboBox
        Left = 121
        Top = 159
        Width = 147
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 13
        WorkView = WorkView
        FieldName = '��ϵ������'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*2001'
      end
      object edtIdCardNo: TWVEdit
        Left = 592
        Top = 156
        Width = 161
        Height = 20
        Color = clWhite
        MaxLength = 20
        ReadOnly = False
        TabOrder = 11
        Text = '<��ϵ�����֤��>'
        WorkView = WorkView
        FieldName = '��ϵ�����֤��'
        SynchronizeWhenExit = True
      end
      object WVEdit12: TWVEdit
        Left = 121
        Top = 199
        Width = 147
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 15
        Text = '<��ϵ�绰>'
        WorkView = WorkView
        FieldName = '��ϵ�绰'
        SynchronizeWhenExit = True
      end
      object WVEdit13: TWVEdit
        Left = 120
        Top = 280
        Width = 393
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 21
        Text = '<��ϵ��ַ>'
        WorkView = WorkView
        FieldName = '��ϵ��ַ'
        SynchronizeWhenExit = True
      end
      object edtDestoryDate: TWVEdit
        Left = 593
        Top = 238
        Width = 159
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 17
        Text = '<Ԥ��ע��ʱ��>'
        WorkView = WorkView
        FieldName = 'Ԥ��ע��ʱ��'
        SynchronizeWhenExit = True
      end
      object WVEdit2: TWVEdit
        Left = 121
        Top = 240
        Width = 147
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 18
        Text = '<��ϵ�˰༶��������>'
        WorkView = WorkView
        FieldName = '��ϵ�˰༶��������'
      end
      object WVEdit4: TWVEdit
        Left = 120
        Top = 416
        Width = 89
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 22
        Text = '<�ͻ���>'
        Visible = False
        WorkView = WorkView
        FieldName = '�ͻ���'
      end
      object WVEdit6: TWVEdit
        Left = 121
        Top = 119
        Width = 147
        Height = 20
        CharCase = ecUpperCase
        Color = clWhite
        ReadOnly = False
        TabOrder = 10
        Text = '<��ϵ��ѧ�Ż�Ա����>'
        WorkView = WorkView
        FieldName = '��ϵ��ѧ�Ż�Ա����'
        SynchronizeWhenExit = True
      end
      object cbbFeeType: TWVComboBox
        Left = 353
        Top = 40
        Width = 159
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 1
        WorkView = WorkView
        FieldName = '�շ����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-43'
      end
      object cbbSpec: TWVComboBox
        Left = 592
        Top = 79
        Width = 161
        Height = 18
        Style = csOwnerDrawFixed
        Color = clWhite
        ItemHeight = 12
        TabOrder = 6
        WorkView = WorkView
        FieldName = 'רҵ'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-23'
      end
      object WVComboBox2: TWVComboBox
        Left = 592
        Top = 118
        Width = 161
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 9
        WorkView = WorkView
        FieldName = '����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*89'
      end
      object cbbIdCardType: TWVComboBox
        Left = 353
        Top = 158
        Width = 159
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 12
        WorkView = WorkView
        FieldName = '֤������'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*87'
      end
      object WVEdit14: TWVEdit
        Left = 593
        Top = 278
        Width = 160
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 20
        Text = '<�ʱ�>'
        WorkView = WorkView
        FieldName = '�ʱ�'
        SynchronizeWhenExit = True
      end
      object WVEdit18: TWVEdit
        Left = 353
        Top = 199
        Width = 159
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 16
        Text = '<�ֻ�>'
        WorkView = WorkView
        FieldName = '�ֻ�'
        SynchronizeWhenExit = True
      end
      object edtInDate: TWVEdit
        Left = 353
        Top = 240
        Width = 159
        Height = 20
        Color = clWhite
        MaxLength = 8
        ReadOnly = False
        TabOrder = 19
        Text = '<��ѧ����>'
        WorkView = WorkView
        FieldName = '��ѧ����'
        SynchronizeWhenExit = True
      end
      object cbb1: TKSFilterComboBox
        Left = 353
        Top = 77
        Width = 159
        Height = 22
        ListFont.Charset = GB2312_CHARSET
        ListFont.Color = clWindowText
        ListFont.Height = -12
        ListFont.Name = '����'
        ListFont.Style = []
        OnFilterItems = cbb1FilterItems
        TabOrder = 3
      end
      object cbb2: TKSFilterComboBox
        Left = 592
        Top = 77
        Width = 162
        Height = 22
        ListFont.Charset = GB2312_CHARSET
        ListFont.Color = clWindowText
        ListFont.Height = -12
        ListFont.Name = '����'
        ListFont.Style = []
        OnFilterItems = cbb2FilterItems
        TabOrder = 4
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 468
    Top = 31
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
        DataField = '@Return'
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
        DataField = 'vsmess'
      end
      item
        Name = '��ϵ��ַ'
        Caption = '��ϵ��ַ'
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
        DataField = 'scusttypes'
      end
      item
        Name = '�ͻ���������'
        Caption = '�ͻ���������'
        FieldType = wftUndefined
        DomainName = 'ѡ����Ŀ'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbranch_code0'
      end
      item
        Name = 'Ԥ��ע��ʱ��'
        Caption = 'Ԥ��ע��ʱ��'
        FieldType = wftUndefined
        DomainName = '����У��'
        Features.Strings = ()
        DataType = kdtString
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
        DataField = 'sdate2'
      end
      item
        Name = '��ϵ�˰༶��������'
        Caption = '��ϵ�˰༶��������'
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
        DataField = 'scard1'
      end
      item
        Name = '��ϵ�˰༶���ź�'
        Caption = '��ϵ�˰༶���ź�'
        FieldType = wftUndefined
        DomainName = 'ѡ����Ŀ'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scert_no'
      end
      item
        Name = '��ע'
        Caption = '��ע'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 100
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'ssectypes'
      end
      item
        Name = '�ͻ���'
        Caption = '�ͻ���'
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
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '�ͻ�����'
        Caption = '�ͻ�����'
        FieldType = wftUndefined
        DomainName = '�ǿ�'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sall_name'
      end
      item
        Name = '�ͻ����'
        Caption = '�ͻ����'
        FieldType = wftUndefined
        DomainName = 'ѡ����Ŀ'
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol3'
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
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '��ϵ������'
        Caption = '��ϵ������'
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
        DataField = 'sname2'
      end
      item
        Name = '��ϵ�����֤��'
        Caption = '��ϵ�����֤��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 20
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'scust_auth'
      end
      item
        Name = 'רҵ'
        Caption = 'רҵ'
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
        DataField = 'scust_no2'
      end
      item
        Name = '��ϵ������'
        Caption = '��ϵ������'
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
        DataField = 'scust_type2'
      end
      item
        Name = '��ϵ���Ա�'
        Caption = '��ϵ���Ա�'
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
        DataField = 'smarket_code2'
      end
      item
        Name = '��ϵ��ѧ�Ż�Ա����'
        Caption = '��ϵ��ѧ�Ż�Ա����'
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
        DataField = 'scust_auth2'
      end
      item
        Name = '��ϵ�绰'
        Caption = '��ϵ�绰'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sphone'
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
        DataField = 'snation_code'
      end
      item
        Name = '�ֻ�'
        Caption = '�ֻ�'
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
        DataField = 'sphone2'
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
        DataField = 'semail'
      end
      item
        Name = '�ʱ�'
        Caption = '�ʱ�'
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
        DataField = 'spost_code'
      end
      item
        Name = '��ѧ����'
        Caption = '��ѧ����'
        FieldType = wftUndefined
        DomainName = '����У��'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sdate1'
      end
      item
        Name = '֤������'
        Caption = '֤������'
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
        DataField = 'smarket_code'
      end
      item
        Name = '��ѯ.�ͻ���'
        Caption = '��ѯ.�ͻ���'
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
      end
      item
        Name = '��ѯ.�ͻ����'
        Caption = '��ѯ.�ͻ����'
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
      end
      item
        Name = '��ѯ.�ͻ�״̬'
        Caption = '��ѯ.�ͻ�״̬'
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
      end
      item
        Name = '��ѯ.�ͻ���������'
        Caption = '��ѯ.�ͻ���������'
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
      end
      item
        Name = '��ѯ.�ͻ�����'
        Caption = '��ѯ.�ͻ�����'
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
      end
      item
        Name = '��ѯ.��ϵ��ѧ����'
        Caption = '��ѯ.��ϵ��ѧ����'
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
      end
      item
        Name = '��ѯ.��ϵ�˵�λ��'
        Caption = '��ѯ.��ϵ�˵�λ��'
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
      end
      item
        Name = '��ѯ.ע������'
        Caption = '��ѯ.ע������'
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
      end
      item
        Name = '��ѯ.��ϵ���Ա�'
        Caption = '��ѯ.��ϵ���Ա�'
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
      end
      item
        Name = '��ѯ.��ϵ������'
        Caption = '��ѯ.��ϵ������'
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
      end
      item
        Name = '��ѯ.��ϵ�����֤��'
        Caption = '��ѯ.��ϵ�����֤��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 18
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.��ϵ��ַ'
        Caption = '��ѯ.��ϵ��ַ'
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
      end
      item
        Name = '��ѯ.��ϵ�˵�λ����'
        Caption = '��ѯ.��ϵ�˵�λ����'
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
      end
      item
        Name = '��ѯ.�շ����'
        Caption = '��ѯ.�շ����'
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
        Name = '��ѯ.���κ�'
        Caption = '��ѯ.���κ�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ѯ.�༶'
        Caption = '��ѯ.�༶'
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
        MonitorValueChangedFields = '|��ѯ.�ͻ���|'
      end
      item
        MonitorValueChangedFields = '|�ͻ�����|�ͻ����|�շ����|��ϵ��ѧ�Ż�Ա����|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 320
    Top = 8
  end
  inherited QueryRequest: TWVRequest
    ID = '�ͻ���Ϣ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ͻ���'
        FieldName = '��ѯ.�ͻ���'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '��ѯ.�ͻ����'
      end
      item
        ParamName = '�ͻ���������'
        FieldName = '��ѯ.�ͻ���������'
      end
      item
        ParamName = '�ͻ�״̬'
        FieldName = '��ѯ.�ͻ�״̬'
      end
      item
        ParamName = '��ϵ�˵�λ��'
        FieldName = '��ѯ.��ϵ�˵�λ��'
      end
      item
        ParamName = '��ϵ������'
        FieldName = '��ѯ.��ϵ������'
      end
      item
        ParamName = '��ϵ�����֤��'
        FieldName = '��ѯ.��ϵ�����֤��'
      end
      item
        ParamName = '��ϵ���Ա�'
        FieldName = '��ѯ.��ϵ���Ա�'
      end
      item
        ParamName = '��ϵ��ѧ����'
        FieldName = '��ѯ.��ϵ��ѧ����'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '��ѯ.�ͻ�����'
      end
      item
        ParamName = '�շ����'
        FieldName = '��ѯ.�շ����'
      end
      item
        ParamName = '���κ�'
        FieldName = '��ѯ.���κ�'
      end
      item
        ParamName = '�༶'
        FieldName = '��ѯ.�༶'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'ע������'
        FieldName = '��ѯ.ע������'
      end>
    Left = 472
    Top = 8
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-34'
      end
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'scert_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'smarket_code2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '39'
      end
      item
        FieldName = 'scust_type2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2001'
      end
      item
        FieldName = 'scard1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '15'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
      end
      item
        FieldName = 'scust_no2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-23'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '87'
      end
      item
        FieldName = 'snation_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '89'
      end>
    Left = 428
    Top = 47
  end
  inherited AddRequest: TWVRequest
    ID = '�ͻ���Ϣ����'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ϵ��ַ'
        FieldName = '��ϵ��ַ'
      end
      item
        ParamName = '�ͻ���������'
        FieldName = '�ͻ���������'
      end
      item
        ParamName = 'Ԥ��ע��ʱ��'
        FieldName = 'Ԥ��ע��ʱ��'
      end
      item
        ParamName = '��ϵ�˰༶��������'
        FieldName = '��ϵ�˰༶��������'
      end
      item
        ParamName = '��ϵ�˰༶���ź�'
        FieldName = '��ϵ�˰༶���ź�'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
      end
      item
        ParamName = '��ϵ������'
        FieldName = '��ϵ������'
      end
      item
        ParamName = '��ϵ�����֤��'
        FieldName = '��ϵ�����֤��'
      end
      item
        ParamName = '��ϵ������'
        FieldName = '��ϵ������'
      end
      item
        ParamName = '��ϵ���Ա�'
        FieldName = '��ϵ���Ա�'
      end
      item
        ParamName = '��ϵ��ѧ�Ż�Ա����'
        FieldName = '��ϵ��ѧ�Ż�Ա����'
      end
      item
        ParamName = '��ϵ�绰'
        FieldName = '��ϵ�绰'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = 'רҵ'
        FieldName = 'רҵ'
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
      end
      item
        ParamName = '�ֻ�'
        FieldName = '�ֻ�'
      end
      item
        ParamName = '�ʱ�'
        FieldName = '�ʱ�'
      end
      item
        ParamName = '��ѧ����'
        FieldName = '��ѧ����'
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end>
    Left = 360
    Top = 8
  end
  inherited DeleteRequest: TWVRequest
    ID = '�ͻ���Ϣ����'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ϵ��ַ'
        FieldName = '��ϵ��ַ'
      end
      item
        ParamName = '�ͻ���������'
        FieldName = '�ͻ���������'
      end
      item
        ParamName = 'Ԥ��ע��ʱ��'
        FieldName = 'Ԥ��ע��ʱ��'
      end
      item
        ParamName = '��ϵ�˰༶��������'
        FieldName = '��ϵ�˰༶��������'
      end
      item
        ParamName = '��ϵ�˰༶���ź�'
        FieldName = '��ϵ�˰༶���ź�'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
      end
      item
        ParamName = '��ϵ������'
        FieldName = '��ϵ������'
      end
      item
        ParamName = '��ϵ�����֤��'
        FieldName = '��ϵ�����֤��'
      end
      item
        ParamName = '��ϵ������'
        FieldName = '��ϵ������'
      end
      item
        ParamName = '��ϵ���Ա�'
        FieldName = '��ϵ���Ա�'
      end
      item
        ParamName = '��ϵ��ѧ�Ż�Ա����'
        FieldName = '��ϵ��ѧ�Ż�Ա����'
      end
      item
        ParamName = '��ϵ�绰'
        FieldName = '��ϵ�绰'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = 'רҵ'
        FieldName = 'רҵ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�ֻ�'
        FieldName = '�ֻ�'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�ʱ�'
        FieldName = '�ʱ�'
      end
      item
        ParamName = '��ѧ����'
        FieldName = '��ѧ����'
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
      end>
    Left = 400
    Top = 8
  end
  inherited ChangeRequest: TWVRequest
    ID = '�ͻ���Ϣ����'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ϵ��ַ'
        FieldName = '��ϵ��ַ'
      end
      item
        ParamName = '�ͻ���������'
        FieldName = '�ͻ���������'
      end
      item
        ParamName = 'Ԥ��ע��ʱ��'
        FieldName = 'Ԥ��ע��ʱ��'
      end
      item
        ParamName = '��ϵ�˰༶��������'
        FieldName = '��ϵ�˰༶��������'
      end
      item
        ParamName = '��ϵ�˰༶���ź�'
        FieldName = '��ϵ�˰༶���ź�'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
      end
      item
        ParamName = '��ϵ������'
        FieldName = '��ϵ������'
      end
      item
        ParamName = '��ϵ�����֤��'
        FieldName = '��ϵ�����֤��'
      end
      item
        ParamName = '��ϵ������'
        FieldName = '��ϵ������'
      end
      item
        ParamName = '��ϵ���Ա�'
        FieldName = '��ϵ���Ա�'
      end
      item
        ParamName = '��ϵ��ѧ�Ż�Ա����'
        FieldName = '��ϵ��ѧ�Ż�Ա����'
      end
      item
        ParamName = '��ϵ�绰'
        FieldName = '��ϵ�绰'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = 'רҵ'
        FieldName = 'רҵ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�ֻ�'
        FieldName = '�ֻ�'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�ʱ�'
        FieldName = '�ʱ�'
      end
      item
        ParamName = '��ѧ����'
        FieldName = '��ѧ����'
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
      end>
    Left = 440
    Top = 8
  end
  inherited WVDataSource: TWVDataSource
    Left = 532
    Top = 23
  end
  inherited alDatasetActions: TActionList
    Left = 500
    Top = 31
  end
end
