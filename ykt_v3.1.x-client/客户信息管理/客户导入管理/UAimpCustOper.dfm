inherited faqhimpCustOper: TfaqhimpCustOper
  Width = 773
  Height = 477
  Caption = '�ͻ��������'
  inherited pcPages: TRzPageControl
    Width = 773
    Height = 477
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 410
        Width = 769
        Height = 44
        TabOrder = 3
        object Label33: TLabel [0]
          Left = 262
          Top = 9
          Width = 36
          Height = 12
          Caption = '���κ�'
        end
        inherited btnAdd: TBitBtn [1]
          Left = 427
          Top = 1000
          Enabled = False
          TabOrder = 9
          Visible = False
        end
        inherited btnChange: TBitBtn [2]
          Left = 419
          Enabled = False
          TabOrder = 2
        end
        inherited btnQuery: TBitBtn [3]
          Left = 334
        end
        inherited btnDelete: TBitBtn
          Left = 504
          Enabled = False
          TabOrder = 3
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 88
          Width = 161
          TabOrder = 7
        end
        object btnCheck: TBitBtn
          Left = 677
          Top = 3
          Width = 79
          Height = 25
          Hint = '����һ����Ŀ'
          Anchors = [akTop, akRight]
          Caption = '���(&C)'
          Enabled = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
          OnClick = btnCheckClick
          Glyph.Data = {
            36030000424D3603000000000000360000002800000010000000100000000100
            18000000000000030000120B0000120B00000000000000000000FFFFFFFFFFFF
            FFFFFFCBD9CF509050408040306830305030203820202820B7C6B7FFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF70A08090E8B080E8A080E0A040
            905050B070509060304030B05040A04030A03020872C1DD3CDCBFFFFFFFFFFFF
            FFFFFF80B080C0E8D090F0B080B080C0D8C040905050A870406040FF9890C058
            50F05840E05030902810FFFFFFFFFFFFFFFFFFCBD5CF80B89070B070F0F0F0FF
            F8FF70A070407840D08870E09080F0B8B0C05850E05840A03820DBECF37AADBD
            598FA66080904068705050505050506060603B774AA66859C06860F0F8F0FFF8
            FFC05850B04830F0F0F06297B250B0D080D8F080B8C0000000B0B0B0B0B8B090
            98905058506F6F6F606060505850606060B04830CFBDB7FFFFFF5090B050D8FF
            90E8FF302830201820E0E0E0D0D0D0B0B0B0909890605860D0D0D0B0B0B09098
            90505850878787FFFFFF5090B050D0FF90E8F0404840403840C0C0C0E0E0E0D0
            D0D0B0B0B0706870E0E0E0D0D0D0B0B0B0909890605860FFFFFF5098B050D0FF
            90E8F0607070505850505050606060504850D0D0D0707070C0C0C0E0E0E0D0D0
            D0B0B0B0706870FFFFFF6098B050D0FF90E8F080B8C0606060807880A098A080
            8880404840404840505050606060504850D0D0D0777777FFFFFF6098B050D0FF
            90E0F0A0E0F060A0B0507880808080707880405060605860807880A098A08088
            80404840A4A4A4FFFFFF60A0C050D0FF90E0F0A0E8F070D8F020B8F000A8F000
            A0E0306890B7BAB77C847C808080778077ABAFABEFF0EFFFFFFF60A0C040D0F0
            90E0F0A0E8F070D8F020B8F000A8F000A0E0307090FFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFF904820FFFFFF70A8C050D8FFA0F0FFB0F0FFA0F0FF90E8FF70D8F040
            C0F0408090FFFFFFF6E3D8904820FFFFFFF9ECE5D06830FFFFFF80B0C0A0E0F0
            C0F8FFC0F8FFC0F8FFC0F8FFC0F8FFA0E0F06090A0FFFFFFA048209048209048
            20D06830F9ECE5FFFFFFD5EAED97C4D970A8C070A0B070A0B07098B070A0B081
            B3BAC0DCE3FFFFFFF6E3D8904820FFFFFFFFFFFFFFFFFFFFFFFF}
        end
        object pbStat: TProgressBar
          Left = 0
          Top = 34
          Width = 769
          Height = 10
          Align = alBottom
          Min = 0
          Max = 100
          TabOrder = 8
        end
        object btnPatchDel: TBitBtn
          Left = 591
          Top = 3
          Width = 79
          Height = 25
          Hint = 'ɾ����ǰѡ�е���Ŀ'
          Anchors = [akTop, akRight]
          Caption = '����ɾ��'
          Enabled = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
          OnClick = btnPatchDelClick
        end
        object edtDelPatchNo: TWVEdit
          Left = 303
          Top = 5
          Width = 98
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 6
          Text = '<���κ�>'
          WorkView = WorkView1
          FieldName = '���κ�'
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 769
      end
      inherited Grid: TRzDBGrid
        Top = 121
        Width = 769
        Height = 289
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'Sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���κ�'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol4'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����˳���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������Ա'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spager'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ѧ����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lsafe_level2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ͻ����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ͻ��������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�շ����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ͻ�����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbranch_code0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'У��'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no2'
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
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smarket_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '֤������'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '֤������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smarket_code2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�Ա�'
            Width = 50
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
            FieldName = 'scust_type2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
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
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ַ'
            Width = 80
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
          end
          item
            Expanded = False
            FieldName = 'Sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��У����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'Ԥ����У����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Caption = '������Ϣ'
            Width = 150
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 769
        Height = 103
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label3: TLabel
          Left = 454
          Top = 10
          Width = 36
          Height = 12
          Caption = '���κ�'
        end
        object Label5: TLabel
          Left = 22
          Top = 34
          Width = 60
          Height = 12
          Caption = '�������Ա'
        end
        object Label6: TLabel
          Left = 46
          Top = 10
          Width = 36
          Height = 12
          Caption = 'ѧ����'
        end
        object Label7: TLabel
          Left = 242
          Top = 34
          Width = 48
          Height = 12
          Caption = '�ͻ����'
        end
        object Label8: TLabel
          Left = 442
          Top = 34
          Width = 48
          Height = 12
          Caption = '�շ����'
        end
        object Label9: TLabel
          Left = 242
          Top = 10
          Width = 48
          Height = 12
          Caption = '�ͻ�����'
        end
        object Label10: TLabel
          Left = 58
          Top = 58
          Width = 24
          Height = 12
          Caption = 'У��'
        end
        object Label11: TLabel
          Left = 242
          Top = 58
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label12: TLabel
          Left = 442
          Top = 58
          Width = 48
          Height = 12
          Caption = 'רҵ����'
        end
        object Label13: TLabel
          Left = 58
          Top = 82
          Width = 24
          Height = 12
          Caption = '�༶'
        end
        object Label14: TLabel
          Left = 242
          Top = 82
          Width = 48
          Height = 12
          Caption = '֤������'
        end
        object Label15: TLabel
          Left = 442
          Top = 82
          Width = 48
          Height = 12
          Caption = '֤������'
        end
        object WVEdit3: TWVEdit
          Left = 500
          Top = 6
          Width = 151
          Height = 20
          Color = clInfoBk
          MaxLength = 50
          ReadOnly = False
          TabOrder = 2
          Text = '<��ѯ.���κ�>'
          WorkView = WorkView
          FieldName = '��ѯ.���κ�'
        end
        object WVEdit5: TWVEdit
          Left = 92
          Top = 31
          Width = 138
          Height = 20
          Color = clInfoBk
          MaxLength = 50
          ReadOnly = False
          TabOrder = 3
          Text = '<��ѯ.�������Ա>'
          WorkView = WorkView
          FieldName = '��ѯ.�������Ա'
        end
        object WVEdit6: TWVEdit
          Left = 92
          Top = 6
          Width = 138
          Height = 20
          CharCase = ecUpperCase
          Color = clInfoBk
          MaxLength = 50
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.ѧ����>'
          WorkView = WorkView
          FieldName = '��ѯ.ѧ����'
        end
        object WVEdit9: TWVEdit
          Left = 300
          Top = 6
          Width = 136
          Height = 20
          Color = clInfoBk
          MaxLength = 50
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.�ͻ�����>'
          WorkView = WorkView
          FieldName = '��ѯ.�ͻ�����'
        end
        object WVEdit13: TWVEdit
          Left = 92
          Top = 78
          Width = 138
          Height = 20
          Color = clInfoBk
          MaxLength = 50
          ReadOnly = False
          TabOrder = 10
          Text = '<��ѯ.�༶>'
          WorkView = WorkView
          FieldName = '��ѯ.�༶'
        end
        object WVEdit15: TWVEdit
          Left = 500
          Top = 78
          Width = 151
          Height = 20
          Color = clInfoBk
          MaxLength = 50
          ReadOnly = False
          TabOrder = 11
          Text = '<��ѯ.֤������>'
          WorkView = WorkView
          FieldName = '��ѯ.֤������'
        end
        object cbbQFeeType: TWVComboBox
          Left = 500
          Top = 31
          Width = 151
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 5
          WorkView = WorkView
          FieldName = '��ѯ.�շ����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '-43'
        end
        object cbbQCustType: TWVComboBox
          Left = 300
          Top = 31
          Width = 136
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '��ѯ.�ͻ�����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '-34'
        end
        object WVComboBox4: TWVComboBox
          Left = 92
          Top = 55
          Width = 138
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 7
          WorkView = WorkView
          FieldName = '��ѯ.�������'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '-27'
        end
        object WVComboBox7: TWVComboBox
          Left = 300
          Top = 54
          Width = 136
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 6
          WorkView = WorkView
          FieldName = '��ѯ.���Ŵ���'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-22'
        end
        object WVComboBox6: TWVComboBox
          Left = 500
          Top = 55
          Width = 151
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 8
          WorkView = WorkView
          FieldName = '��ѯ.רҵ����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-23'
        end
        object cbbQIdCardType: TWVComboBox
          Left = 300
          Top = 77
          Width = 136
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 9
          WorkView = WorkView
          FieldName = '��ѯ.֤������'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*87'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label1: TLabel [0]
        Left = 50
        Top = 44
        Width = 60
        Height = 12
        Caption = '�ͻ����� *'
      end
      object Label4: TLabel [1]
        Left = 74
        Top = 84
        Width = 36
        Height = 12
        Caption = 'У�� *'
      end
      object Label2: TLabel [2]
        Left = 294
        Top = 84
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Label17: TLabel [3]
        Left = 282
        Top = 44
        Width = 60
        Height = 12
        Caption = '�շ���� *'
      end
      object Label18: TLabel [4]
        Left = 570
        Top = 84
        Width = 24
        Height = 12
        Caption = 'רҵ'
      end
      object Label16: TLabel [5]
        Left = 534
        Top = 44
        Width = 60
        Height = 12
        Caption = '�ͻ���� *'
      end
      object Label19: TLabel [6]
        Left = 570
        Top = 124
        Width = 24
        Height = 12
        Caption = '����'
      end
      object Label20: TLabel [7]
        Left = 318
        Top = 124
        Width = 24
        Height = 12
        Caption = '�Ա�'
      end
      object Label21: TLabel [8]
        Left = 68
        Top = 124
        Width = 42
        Height = 12
        Caption = 'ѧ/����'
      end
      object Label22: TLabel [9]
        Left = 86
        Top = 164
        Width = 24
        Height = 12
        Caption = '����'
      end
      object Label23: TLabel [10]
        Left = 294
        Top = 164
        Width = 48
        Height = 12
        Caption = '֤������'
      end
      object Label24: TLabel [11]
        Left = 546
        Top = 163
        Width = 48
        Height = 12
        Caption = '֤������'
      end
      object Label25: TLabel [12]
        Left = 546
        Top = 203
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Label26: TLabel [13]
        Left = 294
        Top = 244
        Width = 48
        Height = 12
        Caption = '��У����'
      end
      object Label27: TLabel [14]
        Left = 318
        Top = 204
        Width = 24
        Height = 12
        Caption = '�ֻ�'
      end
      object WVLabel2: TWVLabel [15]
        Left = 86
        Top = 244
        Width = 24
        Height = 12
        Caption = '�༶'
      end
      object Label28: TLabel [16]
        Left = 86
        Top = 204
        Width = 24
        Height = 12
        Caption = '�绰'
      end
      object Label29: TLabel [17]
        Left = 318
        Top = 285
        Width = 24
        Height = 12
        Caption = '��ַ'
      end
      object Label30: TLabel [18]
        Left = 522
        Top = 242
        Width = 72
        Height = 12
        Caption = 'Ԥ��ע��ʱ��'
      end
      object Label31: TLabel [19]
        Left = 570
        Top = 282
        Width = 24
        Height = 12
        Caption = '�ʱ�'
      end
      object Label32: TLabel [20]
        Left = 62
        Top = 421
        Width = 48
        Height = 12
        Caption = '�ͻ��� *'
        Visible = False
      end
      object lbl1: TLabel [21]
        Left = 522
        Top = 18
        Width = 72
        Height = 12
        Caption = '�ͻ��������'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 769
        TabOrder = 23
        inherited btnOK: TBitBtn
          Left = 597
        end
        inherited btnCancel: TBitBtn
          Left = 685
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtCustName: TWVEdit
        Left = 121
        Top = 40
        Width = 147
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<�ͻ�����>'
        WorkView = WorkView
        FieldName = '�ͻ�����'
        SynchronizeWhenExit = True
      end
      object cbbArea: TWVComboBox
        Left = 121
        Top = 80
        Width = 147
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 6
        WorkView = WorkView
        FieldName = '�������'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-27'
      end
      object cbbFeeType: TWVComboBox
        Left = 353
        Top = 40
        Width = 159
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 2
        WorkView = WorkView
        FieldName = '�շ����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-43'
      end
      object WVComboBox3: TWVComboBox
        Left = 353
        Top = 79
        Width = 159
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 5
        WorkView = WorkView
        FieldName = '���Ŵ���'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-22'
      end
      object WVComboBox5: TWVComboBox
        Left = 603
        Top = 78
        Width = 161
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 4
        WorkView = WorkView
        FieldName = 'רҵ����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-23'
      end
      object cbbCustType: TWVComboBox
        Left = 603
        Top = 40
        Width = 161
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView
        FieldName = '�ͻ�����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '-34'
      end
      object WVComboBox9: TWVComboBox
        Left = 603
        Top = 117
        Width = 161
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 7
        WorkView = WorkView
        FieldName = '����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*89'
      end
      object WVComboBox10: TWVComboBox
        Left = 353
        Top = 118
        Width = 159
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 8
        WorkView = WorkView
        FieldName = '�Ա�'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*39'
      end
      object WVEdit2: TWVEdit
        Left = 121
        Top = 119
        Width = 147
        Height = 20
        CharCase = ecUpperCase
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 9
        Text = '<ѧ����>'
        WorkView = WorkView
        FieldName = 'ѧ����'
        SynchronizeWhenExit = True
      end
      object WVComboBox11: TWVComboBox
        Left = 121
        Top = 159
        Width = 147
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 12
        WorkView = WorkView
        FieldName = '����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*2001'
      end
      object cbbIdCardType: TWVComboBox
        Left = 353
        Top = 158
        Width = 159
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 12
        TabOrder = 11
        WorkView = WorkView
        FieldName = '֤������'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*87'
      end
      object WVEdit8: TWVEdit
        Left = 603
        Top = 197
        Width = 161
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 13
        Text = '<��������>'
        WorkView = WorkView
        FieldName = '��������'
        SynchronizeWhenExit = True
      end
      object WVEdit18: TWVEdit
        Left = 353
        Top = 199
        Width = 159
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 15
        Text = '<�ֻ�>'
        WorkView = WorkView
        FieldName = '�ֻ�'
        SynchronizeWhenExit = True
      end
      object WVEdit4: TWVEdit
        Left = 353
        Top = 240
        Width = 159
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 18
        Text = '<��У����>'
        WorkView = WorkView
        FieldName = '��У����'
        SynchronizeWhenExit = True
      end
      object WVEdit12: TWVEdit
        Left = 121
        Top = 199
        Width = 147
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 14
        Text = '<�绰>'
        WorkView = WorkView
        FieldName = '�绰'
        SynchronizeWhenExit = True
      end
      object WVEdit7: TWVEdit
        Left = 121
        Top = 240
        Width = 147
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 17
        Text = '<�༶>'
        WorkView = WorkView
        FieldName = '�༶'
      end
      object WVEdit10: TWVEdit
        Left = 353
        Top = 280
        Width = 159
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 20
        Text = '<��ַ>'
        WorkView = WorkView
        FieldName = '��ַ'
        SynchronizeWhenExit = True
      end
      object WVEdit14: TWVEdit
        Left = 603
        Top = 278
        Width = 161
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 19
        Text = '<��������>'
        WorkView = WorkView
        FieldName = '��������'
        SynchronizeWhenExit = True
      end
      object edtDestoryDate: TWVEdit
        Left = 603
        Top = 238
        Width = 161
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 16
        Text = '<Ԥ����У����>'
        WorkView = WorkView
        FieldName = 'Ԥ����У����'
        SynchronizeWhenExit = True
      end
      object WVEdit11: TWVEdit
        Left = 120
        Top = 344
        Width = 89
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 21
        Text = '<���κ�>'
        Visible = False
        WorkView = WorkView
        FieldName = '���κ�'
      end
      object edtIdCardNo: TWVEdit
        Left = 603
        Top = 157
        Width = 161
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 10
        Text = '<֤������>'
        WorkView = WorkView
        FieldName = '֤������'
        SynchronizeWhenExit = True
      end
      object WVEdit16: TWVEdit
        Left = 120
        Top = 384
        Width = 89
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 22
        Text = '<����˳���>'
        Visible = False
        WorkView = WorkView
        FieldName = '����˳���'
      end
      object WVEdit1: TWVEdit
        Left = 603
        Top = 17
        Width = 161
        Height = 15
        BorderStyle = bsNone
        ParentColor = True
        ReadOnly = True
        TabOrder = 0
        Text = '<�ͻ��������>'
        WorkView = WorkView
        FieldName = '�ͻ��������'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 364
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
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
        DataField = '@Dataset'
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
        Checker.MaxLength = 50
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
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.���κ�'
        Caption = '��ѯ.���κ�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.����˳���'
        Caption = '��ѯ.����˳���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�������Ա'
        Caption = '��ѯ.�������Ա'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.ѧ����'
        Caption = '��ѯ.ѧ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�ͻ�����'
        Caption = '��ѯ.�ͻ�����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
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
        Checker.MaxLength = 50
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
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�������'
        Caption = '��ѯ.�������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.���Ŵ���'
        Caption = '��ѯ.���Ŵ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.רҵ����'
        Caption = '��ѯ.רҵ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�༶'
        Caption = '��ѯ.�༶'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
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
        Checker.MaxLength = 50
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
        Checker.MaxLength = 50
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
        Checker.MaxLength = 50
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
        Checker.MaxLength = 50
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
        Checker.MaxLength = 50
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
        Checker.MaxLength = 50
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
        Checker.MaxLength = 50
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
        Checker.MaxLength = 50
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
        Checker.MaxLength = 50
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
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.��У����'
        Caption = '��ѯ.��У����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.Ԥ����У����'
        Caption = '��ѯ.Ԥ����У����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 50
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
        DataField = 'Sdate0'
      end
      item
        Name = '���κ�'
        Caption = '���κ�'
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
        DataField = 'scust_limit'
      end
      item
        Name = '����˳���'
        Caption = '����˳���'
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
        DataField = 'Lvol4'
      end
      item
        Name = '�������Ա'
        Caption = '�������Ա'
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
        DataField = 'Semp_no'
      end
      item
        Name = 'ѧ����'
        Caption = 'ѧ����'
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
        Name = '�ͻ�����'
        Caption = '�ͻ�����'
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
        DataField = 'lsafe_level2'
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
        Name = '�ͻ�����'
        Caption = '�ͻ�����'
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
        Name = '�������'
        Caption = '�������'
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
        Name = '���Ŵ���'
        Caption = '���Ŵ���'
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
        Name = 'רҵ����'
        Caption = 'רҵ����'
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
        DataField = 'scert_no2'
      end
      item
        Name = '�༶'
        Caption = '�༶'
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
        DataField = 'scard1'
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
        DataField = 'smarket_code2'
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
        DataField = 'semail2'
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
        DataField = 'smarket_code'
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
        DataField = 'scust_type2'
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
        Name = '��У����'
        Caption = '��У����'
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
        DataField = 'Sdate1'
      end
      item
        Name = 'Ԥ����У����'
        Caption = 'Ԥ����У����'
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
        DataField = 'sdate2'
      end
      item
        Name = '�ͻ��������'
        Caption = '�ͻ��������'
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
          '|��ѯ.������־|��ѯ.��������|��ѯ.���κ�|��ѯ.����˳���|��ѯ.��' +
          '�����Ա|��ѯ.ѧ����|��ѯ.�ͻ�����|��ѯ.�շ����|��ѯ.�ͻ�����|' +
          '��ѯ.�������|��ѯ.���Ŵ���|��ѯ.רҵ����|��ѯ.�༶|��ѯ.֤����' +
          '��|��ѯ.֤������|��ѯ.�Ա�|��ѯ.����|��ѯ.����|��ѯ.��������|��' +
          'ѯ.�绰|��ѯ.�ֻ�|��ѯ.��ַ|��ѯ.��������|��ѯ.��У����|��ѯ.Ԥ' +
          '����У����|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|��������|���κ�|����˳���|�������Ա|ѧ����|�ͻ�����|�շ����|' +
          '�ͻ�����|�������|���Ŵ���|רҵ����|�༶|֤������|֤������|�Ա�|' +
          '����|����|��������|�绰|�ֻ�|��ַ|��������|��У����|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 336
    Top = 248
  end
  inherited QueryRequest: TWVRequest
    ID = '����ͻ���Ϣ��ѯ'
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
        ParamName = '���κ�'
        FieldName = '��ѯ.���κ�'
      end
      item
        ParamName = '����˳���'
        FieldName = '��ѯ.����˳���'
      end
      item
        ParamName = '�������Ա'
        FieldName = '��ѯ.�������Ա'
      end
      item
        ParamName = 'ѧ����'
        FieldName = '��ѯ.ѧ����'
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
        ParamName = '�ͻ�����'
        FieldName = '��ѯ.�ͻ�����'
      end
      item
        ParamName = '�������'
        FieldName = '��ѯ.�������'
      end
      item
        ParamName = '���Ŵ���'
        FieldName = '��ѯ.���Ŵ���'
      end
      item
        ParamName = 'רҵ����'
        FieldName = '��ѯ.רҵ����'
      end
      item
        ParamName = '�༶'
        FieldName = '��ѯ.�༶'
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
        ParamName = '�Ա�'
        FieldName = '��ѯ.�Ա�'
      end
      item
        ParamName = '����'
        FieldName = '��ѯ.����'
      end
      item
        ParamName = '����'
        FieldName = '��ѯ.����'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
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
        ParamName = '��ַ'
        FieldName = '��ѯ.��ַ'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��У����'
        FieldName = '��ѯ.��У����'
      end
      item
        ParamName = 'Ԥ����У����'
        FieldName = '��ѯ.Ԥ����У����'
      end>
    Left = 464
    Top = 248
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lsafe_level2'
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
        FieldName = 'lvol2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '15'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-43'
      end
      item
        FieldName = 'scert_no2'
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
    Left = 396
  end
  inherited AddRequest: TWVRequest
    ID = '����ͻ�����'
    Bindings = <
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '����˳���'
        FieldName = '����˳���'
      end
      item
        ParamName = '�������Ա'
        FieldName = '�������Ա'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '���Ŵ���'
        FieldName = '���Ŵ���'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'רҵ����'
      end
      item
        ParamName = '�༶'
        FieldName = '�༶'
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
        ParamName = '�Ա�'
        FieldName = '�Ա�'
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
        ParamName = '��������'
        FieldName = '��������'
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
        ParamName = '��ַ'
        FieldName = '��ַ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��У����'
        FieldName = '��У����'
      end
      item
        ParamName = 'Ԥ����У����'
        FieldName = 'Ԥ����У����'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 368
    Top = 248
  end
  inherited DeleteRequest: TWVRequest
    ID = '����ͻ�����'
    Bindings = <
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '����˳���'
        FieldName = '����˳���'
      end
      item
        ParamName = '�������Ա'
        FieldName = '�������Ա'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '���Ŵ���'
        FieldName = '���Ŵ���'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'רҵ����'
      end
      item
        ParamName = '�༶'
        FieldName = '�༶'
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
        ParamName = '�Ա�'
        FieldName = '�Ա�'
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
        ParamName = '��������'
        FieldName = '��������'
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
        ParamName = '��ַ'
        FieldName = '��ַ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��У����'
        FieldName = '��У����'
      end
      item
        ParamName = 'Ԥ����У����'
        FieldName = 'Ԥ����У����'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 400
    Top = 248
  end
  inherited ChangeRequest: TWVRequest
    ID = '����ͻ�����'
    Bindings = <
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '����˳���'
        FieldName = '����˳���'
      end
      item
        ParamName = '�������Ա'
        FieldName = '�������Ա'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '���Ŵ���'
        FieldName = '���Ŵ���'
      end
      item
        ParamName = 'רҵ����'
        FieldName = 'רҵ����'
      end
      item
        ParamName = '�༶'
        FieldName = '�༶'
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
        ParamName = '�Ա�'
        FieldName = '�Ա�'
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
        ParamName = '��������'
        FieldName = '��������'
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
        ParamName = '��ַ'
        FieldName = '��ַ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��У����'
        FieldName = '��У����'
      end
      item
        ParamName = 'Ԥ����У����'
        FieldName = 'Ԥ����У����'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 432
    Top = 248
  end
  inherited WVDataSource: TWVDataSource
    Left = 468
  end
  inherited alDatasetActions: TActionList
    Left = 428
    Top = 284
  end
  object WVRImpCheck: TWVRequest
    WorkView = WVImpCheck
    ID = '�ͻ�������Ϣ����.���'
    Bindings = <
      item
        ParamName = '�������κ�'
        FieldName = '�������κ�'
      end
      item
        ParamName = '����˳���'
        FieldName = '����˳���'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    AfterExec = CheckReturnData
    Left = 368
    Top = 208
  end
  object WVImpCheck: TWorkView
    WorkFields = <
      item
        Name = '��ѯ�����'
        FieldType = wftUndefined
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
        Name = '�������κ�'
        Caption = '�������κ�'
        FieldType = wftUndefined
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
        DataField = 'scust_limit'
      end
      item
        Name = '����˳���'
        Caption = '����˳���'
        FieldType = wftUndefined
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
        DataField = 'Lvol1'
      end
      item
        Name = '������־'
        Caption = '������־'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.������־|��ѯ.�������κ�|��ѯ.����˳���|��ѯ.��¼��|��ѯ.' +
          '�豸���|��ѯ.�豸������|��ѯ.�豸����|��ѯ.�̻����|��ѯ.�̻�' +
          '����|��ѯ.��ʼʱ��|��ѯ.����ʱ��|��ѯ.��������|��ѯ.ͣ������|��' +
          'ѯ.��ע|'
      end
      item
        MonitorValueChangedFields = 
          '|�������κ�|����˳���|��¼��|�豸���|�豸������|�豸����|��' +
          '�����|�̻�����|��ʼʱ��|����ʱ��|��������|ͣ������|'
      end>
    Left = 336
    Top = 208
  end
  object WorkView1: TWorkView
    WorkFields = <
      item
        Name = '������Ϣ'
        Caption = '������Ϣ'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
      end
      item
        Name = '���κ�'
        Caption = '���κ�'
        FieldType = wftUndefined
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
        DataField = 'scust_limit'
      end
      item
        Name = '������־'
        Caption = '������־'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '������־'
        Caption = '������־'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '������'
        Caption = '������'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.������־|��ѯ.�������κ�|��ѯ.����˳���|��ѯ.��¼��|��ѯ.' +
          '�豸���|��ѯ.�豸������|��ѯ.�豸����|��ѯ.�̻����|��ѯ.�̻�' +
          '����|��ѯ.��ʼʱ��|��ѯ.����ʱ��|��ѯ.��������|��ѯ.ͣ������|��' +
          'ѯ.��ע|'
      end
      item
        MonitorValueChangedFields = 
          '|�������κ�|����˳���|��¼��|�豸���|�豸������|�豸����|��' +
          '�����|�̻�����|��ʼʱ��|����ʱ��|��������|ͣ������|'
      end>
    Left = 336
    Top = 328
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�ͻ�����ɾ��'
    Bindings = <
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '������Ϣ'
        FieldName = '������Ϣ'
        Direction = bdParam2Field
      end>
    AfterExec = CheckReturnData
    Left = 368
    Top = 328
  end
end
