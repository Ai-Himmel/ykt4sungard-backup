inherited faqhSetCustInfo: TfaqhSetCustInfo
  Width = 840
  Height = 542
  Caption = '�ͻ���Ϣά��'
  inherited pcPages: TRzPageControl
    Width = 840
    Height = 542
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 489
        Width = 836
        TabOrder = 1
        inherited btnAdd: TBitBtn [0]
          Left = 570
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 658
          Enabled = False
          TabOrder = 4
        end
        inherited btnQuery: TBitBtn [2]
          Left = 481
        end
        inherited btnDelete: TBitBtn
          Left = 747
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 22
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 112
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 836
        TabOrder = 3
      end
      inherited Grid: TRzDBGrid
        Top = 105
        Width = 836
        Height = 384
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ͻ���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scard0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sroom_no2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ч����(��)'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����״̬'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'Ԥ����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sroom_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '֤������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spager'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '֤������'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���(cm)'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_type'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�Ա�'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�绰'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ֻ�'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��λ����'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sorder0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����״̬'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sorder1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�Ļ��̶�'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sorder2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������ò'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������Դ'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snation_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_addr'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������ڵ�����'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������ڵ�'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ס����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ס��ַ'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ס����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�״ε��ﱾ������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����ʱ��'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smarket_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�Ƿ�ɾ��'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstock_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ɾ������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���ŷ����'
            Width = 90
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 836
        Height = 87
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label4: TLabel
          Left = 42
          Top = 18
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label7: TLabel
          Left = 42
          Top = 66
          Width = 48
          Height = 12
          Caption = '����״̬'
        end
        object Label9: TLabel
          Left = 234
          Top = 18
          Width = 24
          Height = 12
          Caption = '����'
        end
        object Label10: TLabel
          Left = 402
          Top = 18
          Width = 48
          Height = 12
          Caption = '֤������'
        end
        object Label11: TLabel
          Left = 602
          Top = 18
          Width = 48
          Height = 12
          Caption = '֤������'
        end
        object Label12: TLabel
          Left = 42
          Top = 42
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label14: TLabel
          Left = 234
          Top = 42
          Width = 24
          Height = 12
          Caption = '�Ա�'
        end
        object Label15: TLabel
          Left = 426
          Top = 42
          Width = 24
          Height = 12
          Caption = '�绰'
        end
        object Label16: TLabel
          Left = 626
          Top = 42
          Width = 24
          Height = 12
          Caption = '�ֻ�'
        end
        object Label17: TLabel
          Left = 210
          Top = 66
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object WVEdit9: TWVEdit
          Left = 268
          Top = 14
          Width = 120
          Height = 20
          Color = clInfoBk
          MaxLength = 20
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.����>'
          WorkView = WorkView
          FieldName = '��ѯ.����'
        end
        object WVEdit11: TWVEdit
          Left = 660
          Top = 14
          Width = 132
          Height = 20
          Color = clInfoBk
          MaxLength = 20
          ReadOnly = False
          TabOrder = 3
          Text = '<��ѯ.֤������>'
          WorkView = WorkView
          FieldName = '��ѯ.֤������'
        end
        object edtBirthdayQ: TWVEdit
          Left = 100
          Top = 38
          Width = 105
          Height = 20
          Color = clInfoBk
          MaxLength = 9
          ReadOnly = False
          TabOrder = 4
          Text = '<��ѯ.��������>'
          WorkView = WorkView
          FieldName = '��ѯ.��������'
        end
        object WVEdit15: TWVEdit
          Left = 460
          Top = 38
          Width = 120
          Height = 20
          Color = clInfoBk
          MaxLength = 20
          ReadOnly = False
          TabOrder = 6
          Text = '<��ѯ.�绰>'
          WorkView = WorkView
          FieldName = '��ѯ.�绰'
        end
        object WVEdit16: TWVEdit
          Left = 660
          Top = 38
          Width = 132
          Height = 20
          Color = clInfoBk
          MaxLength = 20
          ReadOnly = False
          TabOrder = 7
          Text = '<��ѯ.�ֻ�>'
          WorkView = WorkView
          FieldName = '��ѯ.�ֻ�'
        end
        object WVEdit17: TWVEdit
          Left = 268
          Top = 62
          Width = 120
          Height = 20
          Color = clInfoBk
          MaxLength = 40
          ReadOnly = False
          TabOrder = 9
          Text = '<��ѯ.��������>'
          WorkView = WorkView
          FieldName = '��ѯ.��������'
        end
        object cbbIDTypeQ: TWVComboBox
          Left = 460
          Top = 14
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '��ѯ.֤������'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*201'
        end
        object cbbDept: TWVComboBox
          Left = 100
          Top = 14
          Width = 105
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          DropDownCount = 20
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '��ѯ.��������'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*210'
        end
        object cbb1: TWVComboBox
          Left = 100
          Top = 62
          Width = 105
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 8
          WorkView = WorkView
          FieldName = '��ѯ.����״̬'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*200'
        end
        object WVComboBox1: TWVComboBox
          Left = 268
          Top = 38
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 5
          WorkView = WorkView
          FieldName = '��ѯ.�Ա�'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*202'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label37: TLabel [0]
        Left = 30
        Top = 12
        Width = 36
        Height = 12
        Caption = '�ͻ���'
        Visible = False
      end
      inherited UIPanel2: TUIPanel
        Top = 483
        Width = 836
        TabOrder = 4
        inherited btnOK: TBitBtn
          Left = 660
        end
        inherited btnCancel: TBitBtn
          Left = 748
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object WVDigitalEdit37: TWVDigitalEdit
        Left = 76
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
        TabOrder = 3
        TabStop = True
        Text = '0'
        Visible = False
        WorkView = WorkView
        FieldName = '�ͻ���'
        SynchronizeByValue = True
      end
      object grpBaseInfo: TGroupBox
        Left = 16
        Top = 40
        Width = 649
        Height = 249
        Caption = '������Ϣ'
        TabOrder = 0
        object Label44: TLabel
          Left = 66
          Top = 29
          Width = 24
          Height = 12
          Caption = '����'
        end
        object Label49: TLabel
          Left = 276
          Top = 29
          Width = 24
          Height = 12
          Caption = '�Ա�'
        end
        object Label56: TLabel
          Left = 452
          Top = 29
          Width = 48
          Height = 12
          Caption = '������ò'
        end
        object Label47: TLabel
          Left = 42
          Top = 93
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label45: TLabel
          Left = 42
          Top = 61
          Width = 48
          Height = 12
          Caption = '֤������'
        end
        object Label46: TLabel
          Left = 252
          Top = 61
          Width = 48
          Height = 12
          Caption = '֤������'
        end
        object Label48: TLabel
          Left = 252
          Top = 93
          Width = 48
          Height = 12
          Caption = '���(CM)'
        end
        object Label55: TLabel
          Left = 452
          Top = 93
          Width = 48
          Height = 12
          Caption = '�Ļ��̶�'
        end
        object Label60: TLabel
          Left = 476
          Top = 125
          Width = 24
          Height = 12
          Caption = '����'
        end
        object Label54: TLabel
          Left = 42
          Top = 125
          Width = 48
          Height = 12
          Caption = '����״̬'
        end
        object Label59: TLabel
          Left = 276
          Top = 125
          Width = 24
          Height = 12
          Caption = '����'
        end
        object Label62: TLabel
          Left = 42
          Top = 150
          Width = 48
          Height = 24
          Alignment = taRightJustify
          BiDiMode = bdLeftToRight
          Caption = '�������ڵ�����'
          ParentBiDiMode = False
          WordWrap = True
        end
        object Label63: TLabel
          Left = 240
          Top = 156
          Width = 60
          Height = 12
          Caption = '�������ڵ�'
        end
        object Label61: TLabel
          Left = 66
          Top = 189
          Width = 24
          Height = 12
          Caption = '����'
        end
        object Label67: TLabel
          Left = 252
          Top = 181
          Width = 48
          Height = 24
          Caption = '�״ε��ﱾ������'
          WordWrap = True
        end
        object Label50: TLabel
          Left = 476
          Top = 189
          Width = 24
          Height = 12
          Caption = '�绰'
        end
        object Label51: TLabel
          Left = 276
          Top = 221
          Width = 24
          Height = 12
          Caption = '�ֻ�'
        end
        object Label53: TLabel
          Left = 42
          Top = 221
          Width = 48
          Height = 12
          Caption = '��λ����'
        end
        object Label52: TLabel
          Left = 452
          Top = 221
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object WVEdit44: TWVEdit
          Left = 98
          Top = 24
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<����>'
          WorkView = WorkView
          FieldName = '����'
          SynchronizeWhenExit = True
        end
        object edtBirthday: TWVEdit
          Left = 98
          Top = 87
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 5
          Text = '<��������>'
          WorkView = WorkView
          FieldName = '��������'
          SynchronizeWhenExit = True
        end
        object edtIdNo: TWVEdit
          Left = 305
          Top = 56
          Width = 323
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 4
          Text = '<֤������>'
          WorkView = WorkView
          FieldName = '֤������'
          SynchronizeWhenExit = True
        end
        object edtHeight: TWVEdit
          Left = 305
          Top = 87
          Width = 123
          Height = 20
          Color = clInfoBk
          MaxLength = 22
          ReadOnly = False
          TabOrder = 6
          Text = '<���>'
          WorkView = WorkView
          FieldName = '���'
          SynchronizeWhenExit = True
        end
        object WVEdit63: TWVEdit
          Left = 305
          Top = 152
          Width = 323
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 12
          Text = '<�������ڵ�>'
          WorkView = WorkView
          FieldName = '�������ڵ�'
          SynchronizeWhenExit = True
        end
        object WVEdit61: TWVEdit
          Left = 98
          Top = 182
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 13
          Text = '<����>'
          WorkView = WorkView
          FieldName = '����'
          SynchronizeWhenExit = True
        end
        object edtArriveDate: TWVEdit
          Left = 305
          Top = 183
          Width = 123
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 14
          Text = '<�״ε��ﱾ������>'
          WorkView = WorkView
          FieldName = '�״ε��ﱾ������'
          SynchronizeWhenExit = True
        end
        object WVEdit50: TWVEdit
          Left = 508
          Top = 183
          Width = 120
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 15
          Text = '<�绰>'
          WorkView = WorkView
          FieldName = '�绰'
          SynchronizeWhenExit = True
        end
        object WVEdit51: TWVEdit
          Left = 305
          Top = 215
          Width = 123
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 17
          Text = '<�ֻ�>'
          WorkView = WorkView
          FieldName = '�ֻ�'
          SynchronizeWhenExit = True
        end
        object WVEdit53: TWVEdit
          Left = 98
          Top = 215
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 16
          Text = '<��λ����>'
          WorkView = WorkView
          FieldName = '��λ����'
          SynchronizeWhenExit = True
        end
        object WVEdit52: TWVEdit
          Left = 508
          Top = 215
          Width = 120
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 18
          Text = '<��������>'
          WorkView = WorkView
          FieldName = '��������'
          SynchronizeWhenExit = True
        end
        object cbbSex: TWVComboBox
          Tag = 1
          Left = 305
          Top = 24
          Width = 123
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 1
          WorkView = WorkView
          FieldName = '�Ա�'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*202'
        end
        object WVComboBox3: TWVComboBox
          Left = 508
          Top = 24
          Width = 122
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '������ò'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*205'
        end
        object cbbIdType: TWVComboBox
          Left = 98
          Top = 56
          Width = 135
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '֤������'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*201'
        end
        object WVComboBox5: TWVComboBox
          Left = 98
          Top = 119
          Width = 135
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 8
          WorkView = WorkView
          FieldName = '����״̬'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*203'
        end
        object WVComboBox6: TWVComboBox
          Left = 305
          Top = 119
          Width = 123
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 9
          WorkView = WorkView
          FieldName = '����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*208'
        end
        object WVComboBox7: TWVComboBox
          Left = 508
          Top = 119
          Width = 122
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 10
          WorkView = WorkView
          FieldName = '����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*209'
        end
        object WVComboBox8: TWVComboBox
          Left = 508
          Top = 87
          Width = 122
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 7
          WorkView = WorkView
          FieldName = '�Ļ��̶�'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*204'
        end
        object WVComboBox11: TWVComboBox
          Left = 98
          Top = 151
          Width = 135
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 11
          WorkView = WorkView
          FieldName = '�������ڵ�����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*211'
        end
      end
      object grpAddr: TGroupBox
        Left = 16
        Top = 304
        Width = 649
        Height = 81
        Caption = '��ס��Ϣ'
        TabOrder = 1
        object Label57: TLabel
          Left = 42
          Top = 29
          Width = 48
          Height = 12
          Caption = '������Դ'
        end
        object Label66: TLabel
          Left = 252
          Top = 29
          Width = 48
          Height = 12
          Caption = '��ס����'
        end
        object Label64: TLabel
          Left = 452
          Top = 29
          Width = 48
          Height = 12
          Caption = '��ס����'
        end
        object Label65: TLabel
          Left = 42
          Top = 57
          Width = 48
          Height = 12
          Caption = '��ס��ַ'
        end
        object edtLiveDate: TWVEdit
          Left = 305
          Top = 24
          Width = 123
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<��ס����>'
          WorkView = WorkView
          FieldName = '��ס����'
          SynchronizeWhenExit = True
        end
        object WVEdit65: TWVEdit
          Left = 98
          Top = 53
          Width = 530
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 3
          Text = '<��ס��ַ>'
          WorkView = WorkView
          FieldName = '��ס��ַ'
          SynchronizeWhenExit = True
        end
        object WVComboBox9: TWVComboBox
          Left = 98
          Top = 24
          Width = 135
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '������Դ'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*206'
        end
        object WVComboBox10: TWVComboBox
          Left = 508
          Top = 24
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '��ס����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*212'
        end
      end
      object grpCardInfo: TGroupBox
        Left = 16
        Top = 392
        Width = 649
        Height = 81
        Caption = '������Ϣ'
        TabOrder = 2
        object Label41: TLabel
          Left = 42
          Top = 55
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label39: TLabel
          Left = 42
          Top = 27
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label40: TLabel
          Left = 251
          Top = 19
          Width = 48
          Height = 24
          Caption = '������Ч����(��)'
          WordWrap = True
        end
        object Label38: TLabel
          Left = 468
          Top = 69
          Width = 24
          Height = 12
          Caption = '����'
          Visible = False
        end
        object Label1: TLabel
          Left = 452
          Top = 27
          Width = 48
          Height = 12
          Caption = '�������'
        end
        object Label2: TLabel
          Left = 240
          Top = 53
          Width = 60
          Height = 12
          Caption = '���ŷ����'
        end
        object edtAppDate: TWVEdit
          Left = 98
          Top = 50
          Width = 135
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 2
          Text = '<��������>'
          WorkView = WorkView
          FieldName = '��������'
          SynchronizeWhenExit = True
        end
        object WVDigitalEdit40: TWVDigitalEdit
          Left = 305
          Top = 21
          Width = 123
          Height = 20
          AllowPoint = True
          AllowNegative = True
          UserSeprator = True
          Precision = 0
          MaxIntLen = 10
          Color = clInfoBk
          ParentColor = False
          TabOrder = 1
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '������Ч����(��)'
          SynchronizeByValue = True
        end
        object WVEdit38: TWVEdit
          Left = 497
          Top = 64
          Width = 123
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 3
          Text = '<����>'
          Visible = False
          WorkView = WorkView
          FieldName = '����'
          SynchronizeWhenExit = True
        end
        object WVComboBox2: TWVComboBox
          Left = 98
          Top = 22
          Width = 135
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          DropDownCount = 20
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '��������'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*210'
        end
        object cbbCardType: TWVComboBox
          Left = 508
          Top = 22
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          DropDownCount = 20
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '�������'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-5'
        end
        object WVEdit1: TWVEdit
          Left = 305
          Top = 48
          Width = 123
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 5
          Text = '<���ŷ����>'
          WorkView = WorkView
          FieldName = '���ŷ����'
          SynchronizeWhenExit = True
        end
      end
      object grpPhoto: TGroupBox
        Left = 680
        Top = 40
        Width = 137
        Height = 185
        Caption = '��Ƭ��Ϣ'
        TabOrder = 5
        Visible = False
        object imgPhoto: TImage
          Left = 8
          Top = 16
          Width = 120
          Height = 160
          Picture.Data = {
            0A544A504547496D6167659B050000FFD8FFE000104A46494600010101006000
            600000FFDB0043000D09090A0A0A0E0B0B0E140D0B0D1417110E0E11171B1515
            1515151B1B1517171717151B1A1E2021201E1A27272A2A272735353535353636
            3636363636363636FFDB0043010E0D0D1111111711111717131413171D191A1A
            191D261D1D1E1D1D262C2420202020242C282B2626262B282F2F2C2C2F2F3636
            36363636363636363636363636FFC00011080070005403011100021101031101
            FFC4001B00000203010101000000000000000000000005010406070302FFC400
            4010000103020303080608040700000000000100020304110512210631411322
            32516171819114162352A1C1333435547292B1F02443D1D2536273A2B2E1F1FF
            C40014010100000000000000000000000000000000FFC4001411010000000000
            0000000000000000000000FFDA000C03010002110311003F00D1A01008250082
            104A0840201008250083E6495B18B9F068DE7C38A057518DB5AEB40DCEDB0B93
            A6A8293F16AC7DB9F6B6BA0DE83C1B553B0B8B6423374ADC507B4389D4C31F26
            D22DD76D77DCF1081A5362F14EFC8E696389E6F107C8206080B202C825041360
            7CD066F10AD3552E976B1BA0693C7C10544020104209DC81AE1B8A4BCA470CB6
            730F35AEE20F040ED00825055C46734F4AF7817E1DD7D1066105AC3F0CABC4A5
            E4E9D97B749E746B7BCFECA0D452EC552B403552BA57FBACE6B7E37282E1D92C
            1C8B726EEFCEEF9E8817576C536D9A8663987F2E5F93C0FD420CB54534D4B298
            67618E46EF69D104D1FD662ED7B47C7FED06B100825056C41A1D47303BB21F31
            AA0CC451BE69191305DF23835A3B4E83CD074CC3A822C3E9594F10E88E73B8B8
            F12822BF13A4C3D99EA64C97E88DEE3DC02058CDB1C29CECA79460F78B34F269
            27E081D41510D4442585E248DDB9C0DD02BDA4C2995D46F91A3F8880678DC379
            B6F6F920C361FF005B87F1041AB4020941F12B43A37B4EE2083E21020D9E607E
            2F4A0EECF7FCA0B87E883A3A0E7BB533BE5C5A60E3CD8F2B59D832827E281420
            D86C3998C5557BF237664FC5ADEDF041A83AEFE28397537D6A3CA74E506A7AAE
            835A8041281263F2CCD7C4C0E223209D389DC502AA7A8969A56CD0BB24ADDCED
            0DB81EBEB417FD65C63EF27C9BFD1050A8A896A6574D33B3C8FE93BE1C1031C1
            3009F157673ECE95A6CE9389FF002B506F292920A385B053B43236F0EDE249EB
            414B1FC523C3A89E737B6906589BC6E74BF820E77F2DC83631B488DA0EF005D0
            7DA0940BF1AA6E5E94B9BD388E6F0E2833282507DC113A696385BD291CD60EF7
            1B20EA14D4F1D340C862196360B01F340A3683684619EC2101F54F17B9DCC1D6
            6DC7B10622A6AA7AA90CD3BCC921DE4FEEC83D30EA7F48AB8D9BDA0E67770DE8
            3596402094020478960F0C71C9511B88035E4F86A6C812A0B98280714A407FC5
            67C08283A620E77B4AE2EC66A6FAD8B47FB1A815A0D561D41152442C3DA380CE
            E3BEFC420B8804128041E73442689F11DCF041418F9E17C1298A4167B74FFC41
            E94351E8B570D45B3724F0ECB7DF6F341A7F5E62FBA3BF38FED419BC4EB05756
            CB521B90484736F7B6806FF04061D48FAAA86B40BB1A4179E000D4A0D620104A
            094108040AB682367A207D867CE05FC0A0474749256D4329A2B72921B36FA0D3
            5EAEC40E3D4CC57AE2FCC7FB502AC42826C3AA3D1E7B1900079BA8D77207F826
            4F408F2EF17CFD77B9417EC80B2094020A73E2D43068E903CFBADE77E9A205F2
            ED20FE4C3E2F3FD102FADC56A2B581920686839B9B7E17EBEF41EDB37F6CD2FE
            277FC5C83A3A0C0ED87DAEEFF4D9F340B292BA7A371313B43BDA777920BECDA3
            A91F491B5C3B2E105C87682924D240633DBA8F82060CABA690666CAC23BD0652
            AB10A9AAFA579CBEE0E8F971415D008041F70CF2D3C82585C592B7A2E1E482EF
            AC18BFDE9E82A54D54F55272B3BCC921D331EC41E48040203F7C500804020100
            804020100804020FFFD9}
          Stretch = True
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 340
    Top = 311
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
        GroupIndex = 1
        DataField = 'sstat_type'
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
        Name = '��ѯ.����״̬'
        Caption = '��ѯ.����״̬'
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
        Checker.MaxLength = 20
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.֤������'
        Caption = '��ѯ.֤������'
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
        Name = '��ѯ.֤������'
        Caption = '��ѯ.֤������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 20
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
        Name = '��ѯ.�Ա�'
        Caption = '��ѯ.�Ա�'
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
        Checker.MaxLength = 20
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
        Checker.MaxLength = 20
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
        Checker.MaxLength = 40
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
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
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol0'
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
        DataField = 'scard0'
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
        DataField = 'sroom_no2'
      end
      item
        Name = '������Ч����(��)'
        Caption = '������Ч����(��)'
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
        Name = 'Ԥ����'
        Caption = 'Ԥ����'
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
        DataField = 'snote'
      end
      item
        Name = '֤������'
        Caption = '֤������'
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
        DataField = 'sroom_no'
      end
      item
        Name = '֤������'
        Caption = '֤������'
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
        Name = '���'
        Caption = '���'
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
        DataField = 'lvol2'
      end
      item
        Name = '�Ա�'
        Caption = '�Ա�'
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
        DataField = 'scust_type'
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
        DataField = 'semail'
      end
      item
        Name = '��λ����'
        Caption = '��λ����'
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
        DataField = 'sorder0'
      end
      item
        Name = '�Ļ��̶�'
        Caption = '�Ļ��̶�'
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
        DataField = 'sorder1'
      end
      item
        Name = '������ò'
        Caption = '������ò'
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
        DataField = 'sorder2'
      end
      item
        Name = '������Դ'
        Caption = '������Դ'
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
        DataField = 'sserial0'
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
        DataField = 'snation_code'
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
        DataField = 'sserial1'
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
        DataField = 'scert_addr'
      end
      item
        Name = '�������ڵ�����'
        Caption = '�������ڵ�����'
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
        Name = '�������ڵ�'
        Caption = '�������ڵ�'
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
        Name = '��ס����'
        Caption = '��ס����'
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
        DataField = 'sserial3'
      end
      item
        Name = '��ס��ַ'
        Caption = '��ס��ַ'
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
        Name = '��ס����'
        Caption = '��ס����'
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
        DataField = 'sdate2'
      end
      item
        Name = '�״ε��ﱾ������'
        Caption = '�״ε��ﱾ������'
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
        DataField = 'sdate3'
      end
      item
        Name = '����ʱ��'
        Caption = '����ʱ��'
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
        Name = '�Ƿ�ɾ��'
        Caption = '�Ƿ�ɾ��'
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
        DataField = 'smarket_code'
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
        GroupIndex = 1
        DataField = 'semp_no'
      end
      item
        Name = '���ŷ����'
        Caption = '���ŷ����'
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
        DataField = 'semail2'
      end>
    Left = 64
    Top = 312
  end
  inherited QueryRequest: TWVRequest
    ID = '�ͻ���Ϣά����ѯ'
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
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '����״̬'
        FieldName = '��ѯ.����״̬'
      end
      item
        ParamName = '����'
        FieldName = '��ѯ.����'
      end
      item
        ParamName = '֤������'
        FieldName = '��ѯ.֤������'
      end
      item
        ParamName = '֤������'
        FieldName = '��ѯ.֤������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '�Ա�'
        FieldName = '��ѯ.�Ա�'
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
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end>
    Left = 224
    Top = 312
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sroom_no'
        WVFieldName = '֤������'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '201'
      end
      item
        FieldName = 'sstatus0'
        WVFieldName = '����״̬'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '200'
      end
      item
        FieldName = 'scust_type'
        WVFieldName = '�Ա�'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '202'
      end
      item
        FieldName = 'sorder0'
        WVFieldName = '����״̬'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '203'
      end
      item
        FieldName = 'sorder1'
        WVFieldName = '�Ļ��̶�'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '204'
      end
      item
        FieldName = 'sorder2'
        WVFieldName = '������ò'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '205'
      end
      item
        FieldName = 'sserial0'
        WVFieldName = '������Դ'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '206'
      end
      item
        FieldName = 'snation_code'
        WVFieldName = '����'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '208'
      end
      item
        FieldName = 'sserial1'
        WVFieldName = '����'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '209'
      end
      item
        FieldName = 'sserial2'
        WVFieldName = '�������ڵ�����'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '211'
      end
      item
        FieldName = 'sserial3'
        WVFieldName = '��ס����'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '212'
      end
      item
        FieldName = 'smarket_code'
        WVFieldName = '�Ƿ�ɾ��'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '213'
      end
      item
        FieldName = 'sroom_no2'
        WVFieldName = '��������'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '210'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-5'
      end>
    Left = 300
    Top = 311
  end
  inherited AddRequest: TWVRequest
    ID = '�ͻ���Ϣά��'
    Bindings = <
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '������Ч����(��)'
        FieldName = '������Ч����(��)'
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
        ParamName = 'Ԥ����'
        FieldName = 'Ԥ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = '�Ա�'
        FieldName = '�Ա�'
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
        ParamName = '��λ����'
        FieldName = '��λ����'
      end
      item
        ParamName = '����״̬'
        FieldName = '����״̬'
      end
      item
        ParamName = '�Ļ��̶�'
        FieldName = '�Ļ��̶�'
      end
      item
        ParamName = '������ò'
        FieldName = '������ò'
      end
      item
        ParamName = '������Դ'
        FieldName = '������Դ'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�������ڵ�����'
        FieldName = '�������ڵ�����'
      end
      item
        ParamName = '�������ڵ�'
        FieldName = '�������ڵ�'
      end
      item
        ParamName = '��ס����'
        FieldName = '��ס����'
      end
      item
        ParamName = '��ס��ַ'
        FieldName = '��ס��ַ'
      end
      item
        ParamName = '��ס����'
        FieldName = '��ס����'
      end
      item
        ParamName = '�״ε��ﱾ������'
        FieldName = '�״ε��ﱾ������'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
      end
      item
        ParamName = '�Ƿ�ɾ��'
        FieldName = '�Ƿ�ɾ��'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '���ŷ����'
        FieldName = '���ŷ����'
      end>
    Left = 104
    Top = 312
  end
  inherited DeleteRequest: TWVRequest
    ID = '�ͻ���Ϣά��'
    Bindings = <
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '������Ч����(��)'
        FieldName = '������Ч����(��)'
        DefaultValue = 0
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
        ParamName = 'Ԥ����'
        FieldName = 'Ԥ����'
        DefaultValue = 0
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '���'
        FieldName = '���'
        DefaultValue = 0
      end
      item
        ParamName = '�Ա�'
        FieldName = '�Ա�'
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
        ParamName = '��λ����'
        FieldName = '��λ����'
      end
      item
        ParamName = '����״̬'
        FieldName = '����״̬'
      end
      item
        ParamName = '�Ļ��̶�'
        FieldName = '�Ļ��̶�'
      end
      item
        ParamName = '������ò'
        FieldName = '������ò'
      end
      item
        ParamName = '������Դ'
        FieldName = '������Դ'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�������ڵ�����'
        FieldName = '�������ڵ�����'
      end
      item
        ParamName = '�������ڵ�'
        FieldName = '�������ڵ�'
      end
      item
        ParamName = '��ס����'
        FieldName = '��ס����'
      end
      item
        ParamName = '��ס��ַ'
        FieldName = '��ס��ַ'
      end
      item
        ParamName = '��ס����'
        FieldName = '��ס����'
      end
      item
        ParamName = '�״ε��ﱾ������'
        FieldName = '�״ε��ﱾ������'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
      end
      item
        ParamName = '�Ƿ�ɾ��'
        FieldName = '�Ƿ�ɾ��'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '���ŷ����'
        FieldName = '���ŷ����'
      end>
    Left = 144
    Top = 312
  end
  inherited ChangeRequest: TWVRequest
    ID = '�ͻ���Ϣά��'
    Bindings = <
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '������Ч����(��)'
        FieldName = '������Ч����(��)'
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
        ParamName = 'Ԥ����'
        FieldName = 'Ԥ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = '�Ա�'
        FieldName = '�Ա�'
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
        ParamName = '��λ����'
        FieldName = '��λ����'
      end
      item
        ParamName = '����״̬'
        FieldName = '����״̬'
      end
      item
        ParamName = '�Ļ��̶�'
        FieldName = '�Ļ��̶�'
      end
      item
        ParamName = '������ò'
        FieldName = '������ò'
      end
      item
        ParamName = '������Դ'
        FieldName = '������Դ'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�������ڵ�����'
        FieldName = '�������ڵ�����'
      end
      item
        ParamName = '�������ڵ�'
        FieldName = '�������ڵ�'
      end
      item
        ParamName = '��ס����'
        FieldName = '��ס����'
      end
      item
        ParamName = '��ס��ַ'
        FieldName = '��ס��ַ'
      end
      item
        ParamName = '��ס����'
        FieldName = '��ס����'
      end
      item
        ParamName = '�״ε��ﱾ������'
        FieldName = '�״ε��ﱾ������'
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
      end
      item
        ParamName = '�Ƿ�ɾ��'
        FieldName = '�Ƿ�ɾ��'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '���ŷ����'
        FieldName = '���ŷ����'
      end>
    Left = 184
    Top = 312
  end
  inherited WVDataSource: TWVDataSource
    Left = 260
    Top = 311
  end
  inherited alDatasetActions: TActionList
    Left = 380
    Top = 316
  end
end
