inherited faqhposSerManager: TfaqhposSerManager
  Width = 681
  Height = 478
  Caption = 'POS�쳣��ˮ����'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 478
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 425
        Width = 677
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 272
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 502
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 418
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 104
          Width = 161
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 121
        Width = 677
        Height = 304
        ImeName = ''
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����ʱ��'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lserial0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸��ˮ��'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lwithdraw_flag'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'Ǯ����'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol6'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�����״���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Damt3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������ǰ���'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Damt4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�����׺����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol11'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���ױ��'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ˮ״̬'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������Ա'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������κ�'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ɼ�����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ɼ�ʱ��'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Semp_no2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��˲���Ա'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'Sdate3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lwithdraw_flag'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ն˱��'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lserial1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ն���ˮ��'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Caption = '������Ϣ'
            Width = 100
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 103
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label1: TLabel
          Left = 18
          Top = 10
          Width = 72
          Height = 12
          Caption = '���׿�ʼ����'
        end
        object Label3: TLabel
          Left = 418
          Top = 10
          Width = 72
          Height = 12
          Caption = '�豸������'
        end
        object Label4: TLabel
          Left = 430
          Top = 34
          Width = 60
          Height = 12
          Caption = '�豸��ˮ��'
        end
        object Label5: TLabel
          Left = 54
          Top = 34
          Width = 36
          Height = 12
          Caption = '�̻���'
        end
        object Label6: TLabel
          Left = 462
          Top = 82
          Width = 36
          Height = 12
          Caption = '������'
          Visible = False
        end
        object Label7: TLabel
          Left = 266
          Top = 34
          Width = 24
          Height = 12
          Caption = '����'
        end
        object Label14: TLabel
          Left = 42
          Top = 58
          Width = 48
          Height = 12
          Caption = '���ױ��'
        end
        object Label2: TLabel
          Left = 231
          Top = 58
          Width = 60
          Height = 12
          Caption = '�������κ�'
        end
        object Label9: TLabel
          Left = 242
          Top = 82
          Width = 48
          Height = 12
          Caption = '��ˮ״̬'
        end
        object Label8: TLabel
          Left = 218
          Top = 10
          Width = 72
          Height = 12
          Caption = '���׽�������'
        end
        object Label12: TLabel
          Left = 42
          Top = 82
          Width = 48
          Height = 12
          Caption = '�豸���'
        end
        object edtQDate: TWVEdit
          Left = 100
          Top = 6
          Width = 103
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.���׿�ʼ����>'
          WorkView = WorkView
          FieldName = '��ѯ.���׿�ʼ����'
        end
        object WVEdit3: TWVEdit
          Left = 500
          Top = 6
          Width = 103
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 2
          Text = '<��ѯ.�豸������>'
          WorkView = WorkView
          FieldName = '��ѯ.�豸������'
        end
        object WVEdit2: TWVEdit
          Left = 300
          Top = 54
          Width = 103
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 7
          Text = '<��ѯ.�������κ�>'
          WorkView = WorkView
          FieldName = '��ѯ.�������κ�'
        end
        object WVComboBox6: TWVComboBox
          Left = 300
          Top = 77
          Width = 103
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 8
          WorkView = WorkView
          FieldName = '��ѯ.��ˮ״̬'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*3'
        end
        object WVComboBox2: TWVComboBox
          Left = 100
          Top = 53
          Width = 103
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 6
          WorkView = WorkView
          FieldName = '��ѯ.���ױ��'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*130'
        end
        object WVComboBox3: TWVComboBox
          Left = 508
          Top = 77
          Width = 103
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 9
          Visible = False
          WorkView = WorkView
          FieldName = '��ѯ.������'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-8'
        end
        object edtBusiNo: TWVEdit
          Left = 100
          Top = 30
          Width = 103
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 3
          Text = '<��ѯ.�̻�����>'
          WorkView = WorkView
          FieldName = '��ѯ.�̻�����'
        end
        object edtSeriNo: TWVEdit
          Left = 500
          Top = 30
          Width = 103
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 5
          Text = '<��ѯ.�豸��ˮ��>'
          WorkView = WorkView
          FieldName = '��ѯ.�豸��ˮ��'
        end
        object edtQCardNo: TWVEdit
          Left = 300
          Top = 30
          Width = 103
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 4
          Text = '<��ѯ.����>'
          WorkView = WorkView
          FieldName = '��ѯ.����'
        end
        object edtQEdate: TWVEdit
          Left = 300
          Top = 6
          Width = 103
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.���׽�������>'
          WorkView = WorkView
          FieldName = '��ѯ.���׽�������'
        end
        object edtDevid: TWVEdit
          Left = 100
          Top = 78
          Width = 103
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 10
          Text = '<��ѯ.�豸���>'
          WorkView = WorkView
          FieldName = '��ѯ.�豸���'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label15: TLabel [0]
        Left = 40
        Top = 76
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Label16: TLabel [1]
        Left = 40
        Top = 118
        Width = 48
        Height = 12
        Caption = '����ʱ��'
      end
      object Label17: TLabel [2]
        Left = 486
        Top = 76
        Width = 60
        Height = 12
        Caption = '�豸��ˮ��'
      end
      object Label18: TLabel [3]
        Left = 286
        Top = 160
        Width = 36
        Height = 12
        Caption = '�̻���'
      end
      object Label19: TLabel [4]
        Left = 46
        Top = 308
        Width = 36
        Height = 12
        Caption = '������'
        Visible = False
      end
      object Label20: TLabel [5]
        Left = 298
        Top = 118
        Width = 24
        Height = 12
        Caption = '����'
      end
      object Label21: TLabel [6]
        Left = 510
        Top = 118
        Width = 36
        Height = 12
        Caption = 'Ǯ����'
      end
      object Label22: TLabel [7]
        Left = 28
        Top = 160
        Width = 60
        Height = 12
        Caption = '�����״���'
      end
      object Label23: TLabel [8]
        Left = 250
        Top = 202
        Width = 72
        Height = 12
        Caption = '������ǰ���'
      end
      object Label24: TLabel [9]
        Left = 474
        Top = 202
        Width = 72
        Height = 12
        Caption = '�����׺����'
      end
      object Label25: TLabel [10]
        Left = 52
        Top = 202
        Width = 36
        Height = 12
        Caption = '������'
      end
      object Label26: TLabel [11]
        Left = 52
        Top = 244
        Width = 36
        Height = 12
        Caption = '����'
      end
      object Label27: TLabel [12]
        Left = 498
        Top = 160
        Width = 48
        Height = 12
        Caption = '���ױ��'
      end
      object Label10: TLabel [13]
        Left = 250
        Top = 76
        Width = 72
        Height = 12
        Caption = '�豸������'
      end
      object lbl1: TLabel [14]
        Left = 66
        Top = 36
        Width = 280
        Height = 14
        Caption = '��ʾ�������� = ������ǰ���-�����׺���'
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Label11: TLabel [15]
        Left = 274
        Top = 245
        Width = 48
        Height = 12
        Caption = '��ˮ״̬'
      end
      inherited UIPanel2: TUIPanel
        Top = 419
        Width = 677
        TabOrder = 15
        inherited btnOK: TBitBtn
          Left = 505
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 593
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object edtDate: TWVEdit
        Left = 94
        Top = 72
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 0
        Text = '<��������>'
        WorkView = WorkView
        FieldName = '��������'
        SynchronizeWhenExit = True
      end
      object edtTime: TWVEdit
        Left = 94
        Top = 114
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 3
        Text = '<����ʱ��>'
        WorkView = WorkView
        FieldName = '����ʱ��'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit23: TWVDigitalEdit
        Left = 334
        Top = 198
        Width = 103
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        ParentColor = False
        TabOrder = 10
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '������ǰ���'
        SynchronizeByValue = True
      end
      object WVDigitalEdit24: TWVDigitalEdit
        Left = 558
        Top = 198
        Width = 103
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        ParentColor = False
        TabOrder = 11
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '�����׺����'
        SynchronizeByValue = True
      end
      object WVDigitalEdit25: TWVDigitalEdit
        Left = 94
        Top = 198
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        ParentColor = False
        TabOrder = 9
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '������'
        SynchronizeByValue = True
      end
      object WVDigitalEdit26: TWVDigitalEdit
        Left = 94
        Top = 240
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        ParentColor = False
        TabOrder = 12
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '�����'
        SynchronizeByValue = True
      end
      object edtPhyId: TWVEdit
        Left = 334
        Top = 72
        Width = 103
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 1
        Text = '<�豸������>'
        WorkView = WorkView
        FieldName = '�豸������'
        SynchronizeWhenExit = True
      end
      object WVComboBox1: TWVComboBox
        Left = 558
        Top = 156
        Width = 103
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 8
        WorkView = WorkView
        FieldName = '���ױ��'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*130'
      end
      object WVComboBox4: TWVComboBox
        Left = 94
        Top = 303
        Width = 103
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 14
        Visible = False
        WorkView = WorkView
        FieldName = '������'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-8'
      end
      object edtCardNo: TWVEdit
        Left = 334
        Top = 114
        Width = 103
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 4
        Text = '<����>'
        WorkView = WorkView
        FieldName = '����'
        SynchronizeWhenExit = True
      end
      object edtTradeNum: TWVEdit
        Left = 94
        Top = 156
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 6
        Text = '<�����״���>'
        WorkView = WorkView
        FieldName = '�����״���'
        SynchronizeWhenExit = True
      end
      object edtPackageNo: TWVEdit
        Left = 558
        Top = 114
        Width = 103
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 5
        Text = '<Ǯ����>'
        WorkView = WorkView
        FieldName = 'Ǯ����'
        SynchronizeWhenExit = True
      end
      object edtDevNo: TWVEdit
        Left = 558
        Top = 72
        Width = 103
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 2
        Text = '<�豸��ˮ��>'
        WorkView = WorkView
        FieldName = '�豸��ˮ��'
        SynchronizeWhenExit = True
      end
      object edtBusiCardNo: TWVEdit
        Left = 334
        Top = 156
        Width = 103
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 7
        Text = '<�̻�����>'
        WorkView = WorkView
        FieldName = '�̻�����'
        SynchronizeWhenExit = True
      end
      object WVComboBox5: TWVComboBox
        Left = 334
        Top = 240
        Width = 103
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 12
        TabOrder = 13
        WorkView = WorkView
        FieldName = '��ˮ״̬'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*3'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 556
    Top = 47
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
        Name = '��ѯ.���׿�ʼ����'
        Caption = '��ѯ.���׿�ʼ����'
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
      end
      item
        Name = '��ѯ.���׽�������'
        Caption = '��ѯ.���׽�������'
        FieldType = wftUndefined
        DomainName = '����У��'
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
        Name = '��ѯ.�豸������'
        Caption = '��ѯ.�豸������'
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
        Name = '��ѯ.�豸��ˮ��'
        Caption = '��ѯ.�豸��ˮ��'
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
        Name = '��ѯ.�̻�����'
        Caption = '��ѯ.�̻�����'
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
        Name = '��ѯ.������'
        Caption = '��ѯ.������'
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
        Name = '��ѯ.����'
        Caption = '��ѯ.����'
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
        Name = '��ѯ.���ױ��'
        Caption = '��ѯ.���ױ��'
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
        Name = '��ѯ.����ʱ��'
        Caption = '��ѯ.����ʱ��'
        FieldType = wftUndefined
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
      end
      item
        Name = '��ѯ.��ˮ״̬'
        Caption = '��ѯ.��ˮ״̬'
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
        Name = '��ѯ.�������κ�'
        Caption = '��ѯ.�������κ�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'scust_limit'
      end
      item
        Name = '��ѯ.�豸���'
        Caption = '��ѯ.�豸���'
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
      end
      item
        Name = '�������κ�'
        Caption = '�������κ�'
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
        DataField = 'scust_limit'
      end
      item
        Name = '�������'
        Caption = '�������'
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
        DataField = 'Lvol1'
      end
      item
        Name = '��ˮ״̬'
        Caption = '��ˮ״̬'
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
        DataField = 'sstatus1'
      end
      item
        Name = '����'
        Caption = '����'
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
        DataField = 'lvol0'
      end
      item
        Name = '�����״���'
        Caption = '�����״���'
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
        DataField = 'lvol6'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        DataField = 'sdate0'
      end
      item
        Name = '����ʱ��'
        Caption = '����ʱ��'
        FieldType = wftUndefined
        DomainName = 'ʱ��У��'
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
        DataField = 'stime0'
      end
      item
        Name = '�豸������'
        Caption = '�豸������'
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
        DataField = 'sname'
      end
      item
        Name = '�豸��ˮ��'
        Caption = '�豸��ˮ��'
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
        DataField = 'lserial0'
      end
      item
        Name = '�̻�����'
        Caption = '�̻�����'
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
        DataField = 'Lvol2'
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
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lbank_acc_type'
      end
      item
        Name = 'Ǯ����'
        Caption = 'Ǯ����'
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
        DataField = 'lvol3'
      end
      item
        Name = '������ǰ���'
        Caption = '������ǰ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'Damt3'
      end
      item
        Name = '�����׺����'
        Caption = '�����׺����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'Damt4'
      end
      item
        Name = '������'
        Caption = '������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'damt0'
      end
      item
        Name = '�����'
        Caption = '�����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'damt1'
      end
      item
        Name = '������־'
        Caption = '������־'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'Sstatus1'
      end
      item
        Name = '���ױ��'
        Caption = '���ױ��'
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
        DataField = 'lvol11'
      end
      item
        Name = '����������'
        Caption = '����������'
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
        Name = '���豸������'
        Caption = '���豸������'
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
        Name = '���豸��ˮ��'
        Caption = '���豸��ˮ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.��������|��ѯ.����ʱ��|��ѯ.�豸������|��ѯ.�豸��ˮ��|' +
          '��ѯ.�̻�����|��ѯ.������|��ѯ.����|��ѯ.Ǯ����|��ѯ.�����״���|' +
          '��ѯ.������ǰ���|��ѯ.�����׺����|��ѯ.������|��ѯ.�����|��ѯ' +
          '.���ױ��|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|��������|����ʱ��|�豸��ˮ��|�̻�����|������|����|Ǯ����|������' +
          '����|������ǰ���|�����׺����|������|�����|���ױ��|��ˮ״̬|' +
          '�������Ա|�������κ�|�������|��������|����ʱ��|��˲���Ա|����' +
          '����|�ն˱��|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 480
    Top = 16
  end
  inherited QueryRequest: TWVRequest
    ID = 'POS�쳣��ˮ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '���׿�ʼ����'
        FieldName = '��ѯ.���׿�ʼ����'
      end
      item
        ParamName = '���׽�������'
        FieldName = '��ѯ.���׽�������'
      end
      item
        ParamName = '�豸������'
        FieldName = '��ѯ.�豸������'
      end
      item
        ParamName = '�豸��ˮ��'
        FieldName = '��ѯ.�豸��ˮ��'
      end
      item
        ParamName = '�̻�����'
        FieldName = '��ѯ.�̻�����'
      end
      item
        ParamName = '������'
        FieldName = '��ѯ.������'
      end
      item
        ParamName = '����'
        FieldName = '��ѯ.����'
      end
      item
        ParamName = '���ױ��'
        FieldName = '��ѯ.���ױ��'
      end
      item
        ParamName = '�������κ�'
        FieldName = '��ѯ.�������κ�'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '��ˮ״̬'
        FieldName = '��ѯ.��ˮ״̬'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�豸���'
        FieldName = '��ѯ.�豸���'
      end>
    Left = 616
    Top = 16
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol11'
        DataPresentType = 'idobjects'
        DataPresentParam = '130'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '-8'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '3'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'semp_no2'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end>
    Left = 524
    Top = 47
  end
  inherited AddRequest: TWVRequest
    ID = 'POS�쳣��ˮ����'
    Bindings = <
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�����״���'
        FieldName = '�����״���'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
      end
      item
        ParamName = '�豸������'
        FieldName = '�豸������'
      end
      item
        ParamName = '�豸��ˮ��'
        FieldName = '�豸��ˮ��'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'Ǯ����'
      end
      item
        ParamName = '������ǰ���'
        FieldName = '������ǰ���'
      end
      item
        ParamName = '�����׺����'
        FieldName = '�����׺����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '���ױ��'
        FieldName = '���ױ��'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 520
    Top = 16
  end
  inherited DeleteRequest: TWVRequest
    ID = 'POS�쳣��ˮ����'
    Bindings = <
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�����״���'
        FieldName = '�����״���'
      end
      item
        ParamName = '�������κ�'
        FieldName = '�������κ�'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�豸��ˮ��'
        FieldName = '�豸��ˮ��'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'Ǯ����'
      end
      item
        ParamName = '������ǰ���'
        FieldName = '������ǰ���'
      end
      item
        ParamName = '�����׺����'
        FieldName = '�����׺����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '���ױ��'
        FieldName = '���ױ��'
      end
      item
        ParamName = '����������'
        FieldName = '����������'
      end
      item
        ParamName = '���豸��ˮ��'
        FieldName = '���豸��ˮ��'
      end
      item
        ParamName = '���豸������'
        FieldName = '���豸������'
      end>
    Left = 552
    Top = 16
  end
  inherited ChangeRequest: TWVRequest
    ID = 'POS�쳣��ˮ����'
    Bindings = <
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�����״���'
        FieldName = '�����״���'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
      end
      item
        ParamName = '�豸������'
        FieldName = '�豸������'
      end
      item
        ParamName = '�豸��ˮ��'
        FieldName = '�豸��ˮ��'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'Ǯ����'
      end
      item
        ParamName = '������ǰ���'
        FieldName = '������ǰ���'
      end
      item
        ParamName = '�����׺����'
        FieldName = '�����׺����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '���ױ��'
        FieldName = '���ױ��'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '����������'
        FieldName = '����������'
      end
      item
        ParamName = '���豸��ˮ��'
        FieldName = '���豸��ˮ��'
      end
      item
        ParamName = '���豸������'
        FieldName = '���豸������'
      end
      item
        ParamName = '��ˮ״̬'
        FieldName = '��ˮ״̬'
      end>
    Left = 584
    Top = 16
  end
  inherited WVDataSource: TWVDataSource
    Left = 628
    Top = 47
  end
  inherited alDatasetActions: TActionList
    Left = 588
    Top = 44
  end
end
