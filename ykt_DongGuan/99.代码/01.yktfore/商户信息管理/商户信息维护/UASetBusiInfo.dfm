inherited faqhSetBusiInfo: TfaqhSetBusiInfo
  Width = 725
  Height = 481
  Caption = '�̻���Ϣά��'
  inherited pcPages: TRzPageControl
    Width = 725
    Height = 481
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 428
        Width = 721
        TabOrder = 1
        inherited btnAdd: TBitBtn [0]
          Left = 455
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 543
          Enabled = False
          TabOrder = 4
        end
        inherited btnQuery: TBitBtn [2]
          Left = 366
        end
        inherited btnDelete: TBitBtn
          Left = 632
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 721
        TabOrder = 3
      end
      inherited Grid: TRzDBGrid
        Top = 105
        Width = 721
        Height = 323
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�����̻���'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ʡ�̻����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻�����'
            Width = 172
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻�Ӣ������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbranch_code0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻�����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbranch_code1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ҵ����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbankname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ϵ��'
            Width = 70
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
            FieldName = 'semail2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 90
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
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'Ӫҵ��ַ'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spost_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spager'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�����˺�'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbankname2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�����ʻ���'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���к�'
            Width = 70
            Visible = True
          end
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
            FieldName = 'sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻�״̬'
            Width = 70
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 721
        Height = 87
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label2: TLabel
          Left = 42
          Top = 10
          Width = 48
          Height = 12
          Caption = '�̻����'
        end
        object Label3: TLabel
          Left = 230
          Top = 10
          Width = 60
          Height = 12
          Caption = '�����̻���'
        end
        object Label4: TLabel
          Left = 30
          Top = 34
          Width = 60
          Height = 12
          Caption = 'ʡ�̻����'
        end
        object Label5: TLabel
          Left = 242
          Top = 34
          Width = 48
          Height = 12
          Caption = '�̻�����'
        end
        object Label6: TLabel
          Left = 418
          Top = 34
          Width = 72
          Height = 12
          Caption = '�̻�Ӣ������'
        end
        object Label7: TLabel
          Left = 42
          Top = 58
          Width = 48
          Height = 12
          Caption = '�̻����'
        end
        object Label8: TLabel
          Left = 242
          Top = 58
          Width = 48
          Height = 12
          Caption = '�̻�����'
        end
        object Label9: TLabel
          Left = 442
          Top = 58
          Width = 48
          Height = 12
          Caption = '��ҵ����'
        end
        object Label25: TLabel
          Left = 442
          Top = 10
          Width = 48
          Height = 12
          Caption = '�̻�״̬'
        end
        object WVEdit3: TWVEdit
          Left = 300
          Top = 6
          Width = 114
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.�����̻���>'
          WorkView = WorkView
          FieldName = '��ѯ.�����̻���'
        end
        object WVEdit4: TWVEdit
          Left = 100
          Top = 30
          Width = 124
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.ʡ�̻����>'
          WorkView = WorkView
          FieldName = '��ѯ.ʡ�̻����'
        end
        object WVEdit5: TWVEdit
          Left = 300
          Top = 30
          Width = 114
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 2
          Text = '<��ѯ.�̻���>'
          WorkView = WorkView
          FieldName = '��ѯ.�̻���'
        end
        object WVEdit6: TWVEdit
          Left = 500
          Top = 30
          Width = 120
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 3
          Text = '<��ѯ.�̻�Ӣ������>'
          WorkView = WorkView
          FieldName = '��ѯ.�̻�Ӣ������'
        end
        object WVEdit7: TWVEdit
          Left = 100
          Top = 54
          Width = 124
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 4
          Text = '<��ѯ.�̻����>'
          WorkView = WorkView
          FieldName = '��ѯ.�̻����'
        end
        object edtBusiId: TWVEdit
          Left = 100
          Top = 6
          Width = 124
          Height = 20
          Color = clInfoBk
          MaxLength = 22
          ReadOnly = False
          TabOrder = 5
          Text = '<��ѯ.�̻����>'
          WorkView = WorkView
          FieldName = '��ѯ.�̻����'
        end
        object WVComboBox8: TWVComboBox
          Left = 500
          Top = 6
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 6
          WorkView = WorkView
          FieldName = '��ѯ.�̻�״̬'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*224'
        end
        object WVComboBox1: TWVComboBox
          Left = 300
          Top = 54
          Width = 114
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 7
          WorkView = WorkView
          FieldName = '��ѯ.�̻�����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*216'
        end
        object WVComboBox2: TWVComboBox
          Left = 500
          Top = 54
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 8
          WorkView = WorkView
          FieldName = '��ѯ.��ҵ����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*217'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label26: TLabel [0]
        Left = 74
        Top = 12
        Width = 48
        Height = 12
        Caption = '�̻����'
        Visible = False
      end
      inherited UIPanel2: TUIPanel
        Top = 422
        Width = 721
        TabOrder = 1
        inherited btnOK: TBitBtn
          Left = 545
        end
        inherited btnCancel: TBitBtn
          Left = 633
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object WVDigitalEdit26: TWVDigitalEdit
        Left = 132
        Top = 8
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        Visible = False
        WorkView = WorkView
        FieldName = '�̻����'
        SynchronizeByValue = True
      end
      object grp1: TGroupBox
        Left = 48
        Top = 32
        Width = 617
        Height = 121
        Caption = '������Ϣ'
        TabOrder = 2
        object Label28: TLabel
          Left = 22
          Top = 26
          Width = 60
          Height = 12
          Caption = 'ʡ�̻����'
        end
        object Label27: TLabel
          Left = 222
          Top = 26
          Width = 60
          Height = 12
          Caption = '�����̻���'
        end
        object Label29: TLabel
          Left = 418
          Top = 26
          Width = 48
          Height = 12
          Caption = '�̻�����'
        end
        object Label30: TLabel
          Left = 10
          Top = 59
          Width = 72
          Height = 12
          Caption = '�̻�Ӣ������'
        end
        object Label31: TLabel
          Left = 234
          Top = 59
          Width = 48
          Height = 12
          Caption = '�̻����'
        end
        object Label32: TLabel
          Left = 418
          Top = 59
          Width = 48
          Height = 12
          Caption = '�̻�����'
        end
        object Label33: TLabel
          Left = 34
          Top = 93
          Width = 48
          Height = 12
          Caption = '��ҵ����'
        end
        object Label47: TLabel
          Left = 418
          Top = 93
          Width = 6
          Height = 12
          Caption = '%'
        end
        object Label41: TLabel
          Left = 234
          Top = 93
          Width = 48
          Height = 12
          Caption = '�������'
        end
        object WVEdit28: TWVEdit
          Left = 84
          Top = 21
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<ʡ�̻����>'
          WorkView = WorkView
          FieldName = 'ʡ�̻����'
          SynchronizeWhenExit = True
        end
        object WVEdit27: TWVEdit
          Left = 284
          Top = 21
          Width = 125
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<�����̻���>'
          WorkView = WorkView
          FieldName = '�����̻���'
          SynchronizeWhenExit = True
        end
        object edtBusiName: TWVEdit
          Left = 468
          Top = 21
          Width = 141
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 2
          Text = '<�̻���>'
          WorkView = WorkView
          FieldName = '�̻���'
          SynchronizeWhenExit = True
        end
        object edtBusiEngName: TWVEdit
          Left = 84
          Top = 55
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 3
          Text = '<�̻�Ӣ������>'
          WorkView = WorkView
          FieldName = '�̻�Ӣ������'
          SynchronizeWhenExit = True
        end
        object WVEdit31: TWVEdit
          Left = 284
          Top = 55
          Width = 125
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 4
          Text = '<�̻����>'
          WorkView = WorkView
          FieldName = '�̻����'
          SynchronizeWhenExit = True
        end
        object WVEdit47: TWVEdit
          Left = 468
          Top = 113
          Width = 129
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 5
          Text = '<��������>'
          Visible = False
          WorkView = WorkView
          FieldName = '��������'
          SynchronizeWhenExit = True
        end
        object WVDigitalEdit41: TWVDigitalEdit
          Left = 284
          Top = 89
          Width = 125
          Height = 20
          AllowPoint = True
          AllowNegative = True
          UserSeprator = True
          Precision = 2
          MaxIntLen = 10
          Color = clInfoBk
          ParentColor = False
          TabOrder = 6
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '�������'
          SynchronizeByValue = True
        end
        object cbb1: TWVComboBox
          Left = 468
          Top = 54
          Width = 141
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 7
          WorkView = WorkView
          FieldName = '�̻�����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*216'
        end
        object WVComboBox3: TWVComboBox
          Left = 84
          Top = 89
          Width = 135
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 8
          WorkView = WorkView
          FieldName = '��ҵ����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*217'
        end
      end
      object GroupBox1: TGroupBox
        Left = 48
        Top = 160
        Width = 617
        Height = 113
        Caption = '��ϵ����Ϣ'
        TabOrder = 3
        object Label34: TLabel
          Left = 46
          Top = 25
          Width = 36
          Height = 12
          Caption = '��ϵ��'
        end
        object Label35: TLabel
          Left = 258
          Top = 25
          Width = 24
          Height = 12
          Caption = '�绰'
        end
        object Label36: TLabel
          Left = 442
          Top = 25
          Width = 24
          Height = 12
          Caption = '�ֻ�'
        end
        object Label37: TLabel
          Left = 34
          Top = 55
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label38: TLabel
          Left = 258
          Top = 55
          Width = 24
          Height = 12
          Caption = '����'
        end
        object Label39: TLabel
          Left = 34
          Top = 85
          Width = 48
          Height = 12
          Caption = 'Ӫҵ��ַ'
        end
        object Label40: TLabel
          Left = 418
          Top = 85
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object WVEdit34: TWVEdit
          Left = 84
          Top = 21
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<��ϵ��>'
          WorkView = WorkView
          FieldName = '��ϵ��'
          SynchronizeWhenExit = True
        end
        object WVEdit35: TWVEdit
          Left = 284
          Top = 21
          Width = 125
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<�绰>'
          WorkView = WorkView
          FieldName = '�绰'
          SynchronizeWhenExit = True
        end
        object WVEdit36: TWVEdit
          Left = 468
          Top = 21
          Width = 141
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 2
          Text = '<�ֻ�>'
          WorkView = WorkView
          FieldName = '�ֻ�'
          SynchronizeWhenExit = True
        end
        object WVEdit37: TWVEdit
          Left = 84
          Top = 51
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 3
          Text = '<��������>'
          WorkView = WorkView
          FieldName = '��������'
          SynchronizeWhenExit = True
        end
        object WVEdit38: TWVEdit
          Left = 284
          Top = 51
          Width = 125
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 4
          Text = '<����>'
          WorkView = WorkView
          FieldName = '����'
          SynchronizeWhenExit = True
        end
        object WVEdit39: TWVEdit
          Left = 84
          Top = 81
          Width = 325
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 5
          Text = '<Ӫҵ��ַ>'
          WorkView = WorkView
          FieldName = 'Ӫҵ��ַ'
          SynchronizeWhenExit = True
        end
        object WVEdit40: TWVEdit
          Left = 468
          Top = 80
          Width = 141
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 6
          Text = '<��������>'
          WorkView = WorkView
          FieldName = '��������'
          SynchronizeWhenExit = True
        end
      end
      object grp2: TGroupBox
        Left = 48
        Top = 280
        Width = 617
        Height = 81
        Caption = '����������Ϣ'
        TabOrder = 4
        object Label42: TLabel
          Left = 34
          Top = 21
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label43: TLabel
          Left = 418
          Top = 21
          Width = 48
          Height = 12
          Caption = '�����˺�'
        end
        object Label44: TLabel
          Left = 22
          Top = 53
          Width = 60
          Height = 12
          Caption = '�����ʻ���'
        end
        object Label45: TLabel
          Left = 430
          Top = 53
          Width = 36
          Height = 12
          Caption = '���к�'
        end
        object WVEdit43: TWVEdit
          Left = 468
          Top = 17
          Width = 141
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<�����˺�>'
          WorkView = WorkView
          FieldName = '�����˺�'
          SynchronizeWhenExit = True
        end
        object WVEdit44: TWVEdit
          Left = 84
          Top = 49
          Width = 325
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 2
          Text = '<�����ʻ���>'
          WorkView = WorkView
          FieldName = '�����ʻ���'
          SynchronizeWhenExit = True
        end
        object WVEdit45: TWVEdit
          Left = 468
          Top = 49
          Width = 141
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<���к�>'
          WorkView = WorkView
          FieldName = '���к�'
          SynchronizeWhenExit = True
        end
        object edt1: TWVEdit
          Left = 84
          Top = 17
          Width = 325
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 3
          Text = '<��������>'
          WorkView = WorkView
          FieldName = '��������'
          SynchronizeWhenExit = True
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 492
    Top = 39
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
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�̻����'
        Caption = '��ѯ.�̻����'
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
        Name = '��ѯ.�����̻���'
        Caption = '��ѯ.�����̻���'
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
        Name = '��ѯ.�̻�״̬'
        Caption = '��ѯ.�̻�״̬'
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
        Name = '��ѯ.ʡ�̻����'
        Caption = '��ѯ.ʡ�̻����'
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
        Name = '��ѯ.�̻���'
        Caption = '��ѯ.�̻���'
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
        Name = '��ѯ.�̻�Ӣ������'
        Caption = '��ѯ.�̻�Ӣ������'
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
        Name = '��ѯ.�̻����'
        Caption = '��ѯ.�̻����'
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
        Name = '��ѯ.�̻�����'
        Caption = '��ѯ.�̻�����'
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
        Name = '��ѯ.��ҵ����'
        Caption = '��ѯ.��ҵ����'
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
        Name = '�̻����'
        Caption = '�̻����'
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
        Name = '�����̻���'
        Caption = '�����̻���'
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
        DataField = 'sname'
      end
      item
        Name = 'ʡ�̻����'
        Caption = 'ʡ�̻����'
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
        DataField = 'sname2'
      end
      item
        Name = '�̻���'
        Caption = '�̻���'
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
        DataField = 'snote'
      end
      item
        Name = '�̻�Ӣ������'
        Caption = '�̻�Ӣ������'
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
        DataField = 'snote2'
      end
      item
        Name = '�̻����'
        Caption = '�̻����'
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
        DataField = 'semail'
      end
      item
        Name = '�̻�����'
        Caption = '�̻�����'
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
        Name = '��ҵ����'
        Caption = '��ҵ����'
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
        DataField = 'sbranch_code1'
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
        DataField = 'sbankname'
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
        DataField = 'semail2'
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
        Name = 'Ӫҵ��ַ'
        Caption = 'Ӫҵ��ַ'
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
        DataField = 'spost_code'
      end
      item
        Name = '�������'
        Caption = '�������'
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
        DataField = 'vsvarstr1'
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
        DataField = 'spager'
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
        DataField = 'sbankname2'
      end
      item
        Name = '���к�'
        Caption = '���к�'
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
        DataField = 'scert_no'
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
        DataField = 'sdate0'
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
        DataField = 'sdate1'
      end
      item
        Name = '����״̬'
        Caption = '����״̬'
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
        Name = '�̻�״̬'
        Caption = '�̻�״̬'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.������־|��ѯ.�̻����|��ѯ.�����̻���|��ѯ.ʡ�̻����|��' +
          'ѯ.�̻���|��ѯ.�̻�Ӣ������|��ѯ.�̻����|��ѯ.�̻�����|��ѯ.��' +
          'ҵ����|��ѯ.��ϵ��|��ѯ.�绰|��ѯ.�ֻ�|��ѯ.��������|��ѯ.����|' +
          '��ѯ.Ӫҵ��ַ|��ѯ.��������|��ѯ.�������|��ѯ.��������|��ѯ.��' +
          '���˺�|��ѯ.�����ʻ���|��ѯ.���к�|��ѯ.��������|��ѯ.��������|' +
          '��ѯ.����״̬|��ѯ.�̻�״̬|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|�̻����|�����̻���|ʡ�̻����|�̻���|�̻�Ӣ������|�̻����|��' +
          '������|��ҵ����|��ϵ��|�绰|�ֻ�|��������|����|Ӫҵ��ַ|��������' +
          '|�������|��������|�����˺�|�����ʻ���|���к�|��������|��������|' +
          '����״̬|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 368
    Top = 8
  end
  inherited QueryRequest: TWVRequest
    ID = '�̻���Ϣά����ѯ'
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
        ParamName = '�̻����'
        FieldName = '��ѯ.�̻����'
      end
      item
        ParamName = '�����̻���'
        FieldName = '��ѯ.�����̻���'
      end
      item
        ParamName = '�̻�״̬'
        FieldName = '��ѯ.�̻�״̬'
      end
      item
        ParamName = 'ʡ�̻����'
        FieldName = '��ѯ.ʡ�̻����'
      end
      item
        ParamName = '�̻���'
        FieldName = '��ѯ.�̻���'
      end
      item
        ParamName = '�̻�Ӣ������'
        FieldName = '��ѯ.�̻�Ӣ������'
      end
      item
        ParamName = '�̻����'
        FieldName = '��ѯ.�̻����'
      end
      item
        ParamName = '�̻�����'
        FieldName = '��ѯ.�̻�����'
      end
      item
        ParamName = '��ҵ����'
        FieldName = '��ѯ.��ҵ����'
      end>
    Left = 528
    Top = 8
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sbranch_code0'
        WVFieldName = '�̻�����'
        DataPresentType = 'idobjects'
        DataPresentParam = '216'
      end
      item
        FieldName = 'sbranch_code1'
        WVFieldName = '��ҵ����'
        DataPresentType = 'idobjects'
        DataPresentParam = '217'
      end
      item
        FieldName = 'scust_auth'
        WVFieldName = '��������'
        DataPresentType = 'idobjects'
        DataPresentParam = '218'
      end
      item
        FieldName = 'sstatus1'
        WVFieldName = '�̻�״̬'
        DataPresentType = 'idobjects'
        DataPresentParam = '224'
      end>
    Left = 412
    Top = 39
  end
  inherited AddRequest: TWVRequest
    ID = '�̻���Ϣά��'
    Bindings = <
      item
        ParamName = '�̻����'
        FieldName = '�̻����'
      end
      item
        ParamName = '�����̻���'
        FieldName = '�����̻���'
      end
      item
        ParamName = 'ʡ�̻����'
        FieldName = 'ʡ�̻����'
      end
      item
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '�̻�Ӣ������'
        FieldName = '�̻�Ӣ������'
      end
      item
        ParamName = '�̻����'
        FieldName = '�̻����'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '��ҵ����'
        FieldName = '��ҵ����'
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
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'Ӫҵ��ַ'
        FieldName = 'Ӫҵ��ַ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
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
        ParamName = '���к�'
        FieldName = '���к�'
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
        ParamName = '����״̬'
        FieldName = '����״̬'
      end
      item
        ParamName = '�̻�״̬'
        FieldName = '�̻�״̬'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 408
    Top = 8
  end
  inherited DeleteRequest: TWVRequest
    ID = '�̻���Ϣά��'
    Bindings = <
      item
        ParamName = '�̻����'
        FieldName = '�̻����'
      end
      item
        ParamName = '�����̻���'
        FieldName = '�����̻���'
      end
      item
        ParamName = 'ʡ�̻����'
        FieldName = 'ʡ�̻����'
      end
      item
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '�̻�Ӣ������'
        FieldName = '�̻�Ӣ������'
      end
      item
        ParamName = '�̻����'
        FieldName = '�̻����'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '��ҵ����'
        FieldName = '��ҵ����'
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
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'Ӫҵ��ַ'
        FieldName = 'Ӫҵ��ַ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
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
        ParamName = '���к�'
        FieldName = '���к�'
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
        ParamName = '����״̬'
        FieldName = '����״̬'
      end
      item
        ParamName = '�̻�״̬'
        FieldName = '�̻�״̬'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 448
    Top = 8
  end
  inherited ChangeRequest: TWVRequest
    ID = '�̻���Ϣά��'
    Bindings = <
      item
        ParamName = '�̻����'
        FieldName = '�̻����'
      end
      item
        ParamName = '�����̻���'
        FieldName = '�����̻���'
      end
      item
        ParamName = 'ʡ�̻����'
        FieldName = 'ʡ�̻����'
      end
      item
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '�̻�Ӣ������'
        FieldName = '�̻�Ӣ������'
      end
      item
        ParamName = '�̻����'
        FieldName = '�̻����'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '��ҵ����'
        FieldName = '��ҵ����'
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
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'Ӫҵ��ַ'
        FieldName = 'Ӫҵ��ַ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
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
        ParamName = '���к�'
        FieldName = '���к�'
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
        ParamName = '����״̬'
        FieldName = '����״̬'
      end
      item
        ParamName = '�̻�״̬'
        FieldName = '�̻�״̬'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 488
    Top = 8
  end
  inherited WVDataSource: TWVDataSource
    Left = 532
    Top = 39
  end
  inherited alDatasetActions: TActionList
    Left = 452
    Top = 36
  end
end
