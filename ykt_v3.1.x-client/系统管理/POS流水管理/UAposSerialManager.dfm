inherited faqhposSerialManager: TfaqhposSerialManager
  Width = 775
  Height = 478
  Caption = 'POS��ˮ����'
  inherited pcPages: TRzPageControl
    Width = 775
    Height = 478
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 425
        Width = 771
        TabOrder = 3
        object Label33: TLabel [0]
          Left = 102
          Top = 9
          Width = 36
          Height = 12
          Caption = '���κ�'
        end
        inherited btnAdd: TBitBtn [1]
          Left = 334
          Enabled = False
        end
        inherited btnChange: TBitBtn [2]
          Left = 421
          Enabled = False
        end
        inherited btnQuery: TBitBtn [3]
          Left = 248
        end
        inherited btnDelete: TBitBtn
          Left = 507
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 24
          Top = 24
          Width = 161
          TabOrder = 8
          Visible = False
        end
        object btnCheck: TBitBtn
          Left = 680
          Top = 3
          Width = 79
          Height = 25
          Hint = '���Pos��ˮ'
          Anchors = [akTop, akRight]
          Caption = '���(&C)'
          Enabled = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
          TabOrder = 6
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
        object btnPatchDel: TBitBtn
          Left = 594
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
          TabOrder = 5
          OnClick = btnPatchDelClick
        end
        object edtDelPatchNo: TWVEdit
          Left = 143
          Top = 5
          Width = 98
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 7
          Text = '<���κ�>'
          WorkView = WorkView1
          FieldName = '���κ�'
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 771
      end
      inherited Grid: TRzDBGrid
        Top = 97
        Width = 771
        Height = 328
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
            Title.Caption = '���״̬'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������Ա'
            Width = 71
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���κ�'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stime2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����ʱ��'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Semp_no2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��˲���Ա'
            Width = 70
            Visible = True
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
        Width = 771
        Height = 79
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label1: TLabel
          Left = 42
          Top = 10
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label3: TLabel
          Left = 218
          Top = 10
          Width = 72
          Height = 12
          Caption = '�豸������'
        end
        object Label4: TLabel
          Left = 430
          Top = 10
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
          Left = 254
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
          Left = 253
          Top = 58
          Width = 36
          Height = 12
          Caption = '���κ�'
        end
        object Label9: TLabel
          Left = 442
          Top = 34
          Width = 48
          Height = 12
          Caption = '���״̬'
        end
        object edtQDate: TWVEdit
          Left = 100
          Top = 6
          Width = 103
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.��������>'
          WorkView = WorkView
          FieldName = '��ѯ.��������'
        end
        object WVEdit3: TWVEdit
          Left = 300
          Top = 6
          Width = 103
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
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
          Left = 500
          Top = 29
          Width = 103
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '��ˮ״̬'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*135'
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
          Left = 300
          Top = 77
          Width = 103
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 8
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
          TabOrder = 4
          Text = '<��ѯ.�̻�����>'
          WorkView = WorkView
          FieldName = '��ѯ.�̻�����'
        end
        object edtSeriNo: TWVEdit
          Left = 500
          Top = 6
          Width = 103
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 2
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
          TabOrder = 5
          Text = '<��ѯ.����>'
          WorkView = WorkView
          FieldName = '��ѯ.����'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label15: TLabel [0]
        Left = 42
        Top = 124
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Label16: TLabel [1]
        Left = 276
        Top = 124
        Width = 48
        Height = 12
        Caption = '����ʱ��'
      end
      object Label17: TLabel [2]
        Left = 30
        Top = 164
        Width = 60
        Height = 12
        Caption = '�豸��ˮ��'
      end
      object Label18: TLabel [3]
        Left = 288
        Top = 164
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
        Left = 66
        Top = 84
        Width = 24
        Height = 12
        Caption = '����'
      end
      object Label21: TLabel [6]
        Left = 510
        Top = 84
        Width = 36
        Height = 12
        Caption = 'Ǯ����'
      end
      object Label22: TLabel [7]
        Left = 264
        Top = 84
        Width = 60
        Height = 12
        Caption = '�����״���'
      end
      object Label23: TLabel [8]
        Left = 252
        Top = 204
        Width = 72
        Height = 12
        Caption = '������ǰ���'
      end
      object Label24: TLabel [9]
        Left = 474
        Top = 204
        Width = 72
        Height = 12
        Caption = '�����׺����'
      end
      object Label25: TLabel [10]
        Left = 54
        Top = 204
        Width = 36
        Height = 12
        Caption = '������'
      end
      object Label26: TLabel [11]
        Left = 56
        Top = 244
        Width = 36
        Height = 12
        Caption = '����'
      end
      object Label27: TLabel [12]
        Left = 498
        Top = 164
        Width = 48
        Height = 12
        Caption = '���ױ��'
      end
      object Label10: TLabel [13]
        Left = 474
        Top = 124
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
      inherited UIPanel2: TUIPanel
        Top = 419
        Width = 771
        TabOrder = 14
        inherited btnOK: TBitBtn
          Left = 599
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 687
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object edtDate: TWVEdit
        Left = 94
        Top = 120
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 3
        Text = '<��������>'
        WorkView = WorkView
        FieldName = '��������'
        SynchronizeWhenExit = True
      end
      object edtTime: TWVEdit
        Left = 334
        Top = 120
        Width = 100
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 4
        Text = '<����ʱ��>'
        WorkView = WorkView
        FieldName = '����ʱ��'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit23: TWVDigitalEdit
        Left = 334
        Top = 200
        Width = 100
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
        FieldName = '������ǰ���'
        SynchronizeByValue = True
      end
      object WVDigitalEdit24: TWVDigitalEdit
        Left = 558
        Top = 199
        Width = 103
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
        FieldName = '�����׺����'
        SynchronizeByValue = True
      end
      object WVDigitalEdit25: TWVDigitalEdit
        Left = 94
        Top = 200
        Width = 100
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
      object WVEdit4: TWVEdit
        Left = 558
        Top = 120
        Width = 103
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 5
        Text = '<�豸������>'
        WorkView = WorkView
        FieldName = '�豸������'
        SynchronizeWhenExit = True
      end
      object WVComboBox1: TWVComboBox
        Left = 558
        Top = 158
        Width = 103
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ItemHeight = 0
        TabOrder = 6
        Text = '<���ױ��>'
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
        ItemHeight = 0
        TabOrder = 13
        Text = '<������>'
        Visible = False
        WorkView = WorkView
        FieldName = '������'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-8'
      end
      object edtCardNo: TWVEdit
        Left = 94
        Top = 80
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 0
        Text = '<����>'
        WorkView = WorkView
        FieldName = '����'
        SynchronizeWhenExit = True
      end
      object edtTradeNum: TWVEdit
        Left = 334
        Top = 80
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 1
        Text = '<�����״���>'
        WorkView = WorkView
        FieldName = '�����״���'
        SynchronizeWhenExit = True
      end
      object edtPackageNo: TWVEdit
        Left = 558
        Top = 80
        Width = 103
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 2
        Text = '<Ǯ����>'
        WorkView = WorkView
        FieldName = 'Ǯ����'
        SynchronizeWhenExit = True
      end
      object edtDevNo: TWVEdit
        Left = 94
        Top = 160
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 7
        Text = '<�豸��ˮ��>'
        WorkView = WorkView
        FieldName = '�豸��ˮ��'
        SynchronizeWhenExit = True
      end
      object edtBusiCardNo: TWVEdit
        Left = 334
        Top = 160
        Width = 100
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 8
        Text = '<�̻�����>'
        WorkView = WorkView
        FieldName = '�̻�����'
        SynchronizeWhenExit = True
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
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
    ID = 'POS��ˮ��ѯ'
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
        FieldName = '��ˮ״̬'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
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
        DataPresentParam = '135'
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
    ID = 'POS��ˮ����'
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
    ID = 'POS��ˮ����'
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
      end>
    Left = 552
    Top = 16
  end
  inherited ChangeRequest: TWVRequest
    ID = 'POS��ˮ����'
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
  object WVCheck: TWorkView
    WorkFields = <
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
        DataField = '@Return'
      end
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
        DataField = 'vsmess'
      end
      item
        Name = '���κ�'
        Caption = '���κ�'
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
        Name = '����'
        Caption = '����'
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
        Name = 'Ǯ����'
        Caption = 'Ǯ����'
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
        Name = '���״���'
        Caption = '���״���'
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
          '|��ѯ.��������|��ѯ.����ʱ��|��ѯ.�豸������|��ѯ.�豸��ˮ��|' +
          '��ѯ.�̻�����|��ѯ.������|��ѯ.����|��ѯ.Ǯ����|��ѯ.�����״���|' +
          '��ѯ.������ǰ���|��ѯ.�����׺����|��ѯ.������|��ѯ.�����|��ѯ' +
          '.���ױ��|'
      end
      item
        MonitorValueChangedFields = 
          '|��������|����ʱ��|�豸��ˮ��|�̻�����|������|����|Ǯ����|������' +
          '����|������ǰ���|�����׺����|������|�����|���ױ��|��ˮ״̬|' +
          '�������Ա|�������κ�|�������|��������|����ʱ��|��˲���Ա|����' +
          '����|�ն˱��|'
      end>
    Left = 480
    Top = 112
  end
  object WVRCheck: TWVRequest
    WorkView = WVCheck
    ID = 'Pos��ˮ���1'
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
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'Ǯ����'
      end
      item
        ParamName = '���״���'
        FieldName = '���״���'
      end>
    AfterExec = CheckReturnData
    Left = 520
    Top = 112
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
    Left = 488
    Top = 152
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = 'pos��ˮ����ɾ��'
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
    Left = 520
    Top = 152
  end
end
