inherited faqhdevImpManage: TfaqhdevImpManage
  Width = 807
  Height = 477
  Caption = '�豸�������'
  inherited pcPages: TRzPageControl
    Width = 807
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 409
        Width = 803
        Height = 45
        TabOrder = 3
        object Label10: TLabel [0]
          Left = 102
          Top = 9
          Width = 36
          Height = 12
          Caption = '���κ�'
        end
        inherited btnAdd: TBitBtn [1]
          Left = 718
          Caption = '���(&C)'
          Enabled = False
          TabOrder = 5
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
        inherited btnChange: TBitBtn [2]
          Left = 462
          Enabled = False
          TabOrder = 2
        end
        inherited btnQuery: TBitBtn [3]
          Left = 376
        end
        inherited btnDelete: TBitBtn
          Left = 547
          Enabled = False
          TabOrder = 3
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 88
          Top = 32
          Width = 161
          TabOrder = 7
          Visible = False
        end
        object pbstat: TProgressBar
          Left = 0
          Top = 35
          Width = 803
          Height = 10
          Align = alBottom
          Min = 0
          Max = 100
          ParentShowHint = False
          Smooth = True
          ShowHint = False
          TabOrder = 8
        end
        object btnPatchDel: TBitBtn
          Left = 632
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
          Left = 143
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
        Width = 803
      end
      inherited Grid: TRzDBGrid
        Top = 97
        Width = 803
        Height = 312
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'scust_limit'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���κ�'
            Width = 100
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
            FieldName = 'scert_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸����'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol7'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸��;'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lserial0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������ϵͳ'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ϼ��豸���'
            Width = 65
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbranch_code0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'saddr'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ƭ�ṹ'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol8'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������˿ں�'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������˿�����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol6'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�Ƿ�֧�ֿ�Ŀ�շ�'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstation0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'IP��ַ'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ͨѶ��ʽ'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ͨѶ�˿ں�'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������Ϣ'
            Width = 80
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 803
        Height = 79
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label3: TLabel
          Left = 38
          Top = 58
          Width = 36
          Height = 12
          Caption = '���κ�'
        end
        object Label4: TLabel
          Left = 26
          Top = 10
          Width = 48
          Height = 12
          Caption = '�豸����'
        end
        object Label5: TLabel
          Left = 218
          Top = 10
          Width = 72
          Height = 12
          Caption = '�豸������'
        end
        object Label6: TLabel
          Left = 474
          Top = 10
          Width = 48
          Height = 12
          Caption = '�豸����'
        end
        object Label7: TLabel
          Left = 26
          Top = 34
          Width = 48
          Height = 12
          Caption = '�豸����'
        end
        object Label8: TLabel
          Left = 242
          Top = 34
          Width = 48
          Height = 12
          Caption = '�豸��;'
        end
        object Label9: TLabel
          Left = 462
          Top = 34
          Width = 60
          Height = 12
          Caption = '������ϵͳ'
        end
        object Label11: TLabel
          Left = 242
          Top = 58
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object Label12: TLabel
          Left = 474
          Top = 58
          Width = 48
          Height = 12
          Caption = '��Ƭ�ṹ'
        end
        object Label17: TLabel
          Left = 290
          Top = 234
          Width = 6
          Height = 12
        end
        object WVEdit3: TWVEdit
          Left = 84
          Top = 54
          Width = 129
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 8
          Text = '<��ѯ.���κ�>'
          WorkView = WorkView
          FieldName = '��ѯ.���κ�'
        end
        object WVEdit4: TWVEdit
          Left = 84
          Top = 6
          Width = 129
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.�豸����>'
          WorkView = WorkView
          FieldName = '��ѯ.�豸����'
        end
        object WVEdit5: TWVEdit
          Left = 300
          Top = 6
          Width = 142
          Height = 20
          Color = clInfoBk
          MaxLength = 8
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.�豸������>'
          WorkView = WorkView
          FieldName = '��ѯ.�豸������'
        end
        object cbbQEquPhyType: TWVComboBox
          Left = 532
          Top = 7
          Width = 128
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 2
          WorkView = WorkView
          FieldName = '��ѯ.�豸����'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-35'
        end
        object cbbQMachineType: TWVComboBox
          Left = 84
          Top = 31
          Width = 129
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 3
          WorkView = WorkView
          FieldName = '��ѯ.�豸����'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*47'
        end
        object cbbQUseType: TWVComboBox
          Left = 300
          Top = 31
          Width = 143
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 4
          WorkView = WorkView
          FieldName = '��ѯ.�豸��;'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*81'
        end
        object cbbQChildSys: TWVComboBox
          Left = 532
          Top = 31
          Width = 128
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 5
          WorkView = WorkView
          FieldName = '��ѯ.������ϵͳ'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-32'
        end
        object WVComboBox2: TWVComboBox
          Left = 300
          Top = 53
          Width = 143
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 6
          WorkView = WorkView
          FieldName = '��ѯ.��������'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-28'
        end
        object WVComboBox4: TWVComboBox
          Left = 532
          Top = 53
          Width = 129
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 7
          WorkView = WorkView
          FieldName = '��ѯ.��Ƭ�ṹ'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*48'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label20: TLabel [0]
        Left = 330
        Top = 44
        Width = 60
        Height = 12
        Caption = '����˳���'
      end
      object Label21: TLabel [1]
        Left = 51
        Top = 44
        Width = 60
        Height = 12
        Caption = '�������κ�'
      end
      object Label23: TLabel [2]
        Left = 57
        Top = 76
        Width = 54
        Height = 12
        Caption = '�豸����*'
      end
      object Label24: TLabel [3]
        Left = 39
        Top = 140
        Width = 72
        Height = 12
        Caption = '�豸������'
      end
      object Label25: TLabel [4]
        Left = 336
        Top = 76
        Width = 54
        Height = 12
        Caption = '�豸����*'
      end
      object Label26: TLabel [5]
        Left = 336
        Top = 108
        Width = 54
        Height = 12
        Caption = '�豸����*'
      end
      object Label27: TLabel [6]
        Left = 57
        Top = 108
        Width = 54
        Height = 12
        Caption = '�豸��;*'
      end
      object Label28: TLabel [7]
        Left = 324
        Top = 172
        Width = 66
        Height = 12
        Caption = '������ϵͳ*'
      end
      object Label29: TLabel [8]
        Left = 33
        Top = 172
        Width = 78
        Height = 12
        Caption = '�ϼ��豸���*'
      end
      object Label30: TLabel [9]
        Left = 336
        Top = 140
        Width = 54
        Height = 12
        Caption = '��������*'
      end
      object Label31: TLabel [10]
        Left = 342
        Top = 204
        Width = 48
        Height = 12
        Caption = '��Ƭ�ṹ'
      end
      object Label32: TLabel [11]
        Left = 39
        Top = 204
        Width = 72
        Height = 12
        Caption = '�������˿ں�'
      end
      object Label33: TLabel [12]
        Left = 27
        Top = 268
        Width = 84
        Height = 12
        Caption = '�������˿�����'
      end
      object Label35: TLabel [13]
        Left = 342
        Top = 236
        Width = 48
        Height = 12
        Caption = '�豸����'
      end
      object Label36: TLabel [14]
        Left = 540
        Top = 124
        Width = 6
        Height = 12
      end
      object Label37: TLabel [15]
        Left = 342
        Top = 268
        Width = 48
        Height = 12
        Caption = 'ͨѶ��ʽ'
      end
      object Label1: TLabel [16]
        Left = 75
        Top = 236
        Width = 36
        Height = 12
        Caption = 'IP��ַ'
      end
      object Label2: TLabel [17]
        Left = 51
        Top = 300
        Width = 60
        Height = 12
        Caption = 'ͨѶ�˿ں�'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 803
        TabOrder = 17
        inherited btnOK: TBitBtn
          Left = 631
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 719
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object edtPatchNo: TWVEdit
        Left = 118
        Top = 40
        Width = 188
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 0
        Text = '<���κ�>'
        WorkView = WorkView
        FieldName = '���κ�'
        SynchronizeWhenExit = True
      end
      object edtEquName: TWVEdit
        Left = 118
        Top = 72
        Width = 188
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 2
        Text = '<�豸����>'
        WorkView = WorkView
        FieldName = '�豸����'
        SynchronizeWhenExit = True
      end
      object WVEdit24: TWVEdit
        Left = 118
        Top = 136
        Width = 188
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 6
        Text = '<�豸������>'
        WorkView = WorkView
        FieldName = '�豸������'
        SynchronizeWhenExit = True
      end
      object edtUEqu: TWVEdit
        Left = 118
        Top = 168
        Width = 188
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 8
        Text = '<�ϼ��豸���>'
        WorkView = WorkView
        FieldName = '�ϼ��豸���'
        SynchronizeWhenExit = True
      end
      object edtSerPortNo: TWVEdit
        Left = 118
        Top = 199
        Width = 188
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 10
        Text = '<�������˿ں�>'
        WorkView = WorkView
        FieldName = '�������˿ں�'
        SynchronizeWhenExit = True
      end
      object edtIP: TWVEdit
        Left = 118
        Top = 232
        Width = 188
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 13
        Text = '<IP��ַ>'
        WorkView = WorkView
        FieldName = 'IP��ַ'
        SynchronizeWhenExit = True
      end
      object cbbEquPhyType: TWVComboBox
        Left = 398
        Top = 73
        Width = 188
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 3
        Text = '<�豸����>'
        WorkView = WorkView
        FieldName = '�豸����'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '-35'
      end
      object cbbMachineType: TWVComboBox
        Left = 398
        Top = 104
        Width = 188
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 4
        Text = '<�豸����>'
        WorkView = WorkView
        FieldName = '�豸����'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '47'
      end
      object cbbUseType: TWVComboBox
        Left = 118
        Top = 105
        Width = 188
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 5
        Text = '<�豸��;>'
        WorkView = WorkView
        FieldName = '�豸��;'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '81'
      end
      object cbbArea: TWVComboBox
        Left = 398
        Top = 136
        Width = 188
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ItemHeight = 0
        TabOrder = 7
        Text = '<��������>'
        WorkView = WorkView
        FieldName = '��������'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '-28'
      end
      object cbbChildSys: TWVComboBox
        Left = 398
        Top = 169
        Width = 188
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 9
        Text = '<������ϵͳ>'
        WorkView = WorkView
        FieldName = '������ϵͳ'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '-32'
      end
      object WVComboBox8: TWVComboBox
        Left = 398
        Top = 200
        Width = 188
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 11
        Text = '<��Ƭ�ṹ>'
        WorkView = WorkView
        FieldName = '��Ƭ�ṹ'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*48'
      end
      object cbbComm: TWVComboBox
        Left = 398
        Top = 265
        Width = 188
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 15
        Text = '<ͨѶ��ʽ>'
        WorkView = WorkView
        FieldName = 'ͨѶ��ʽ'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*50'
      end
      object edtMachineNo: TWVEdit
        Left = 398
        Top = 231
        Width = 188
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 12
        Text = '<�豸����>'
        WorkView = WorkView
        FieldName = '�豸����'
        SynchronizeWhenExit = True
      end
      object edtSerPortNum: TWVEdit
        Left = 118
        Top = 263
        Width = 188
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 14
        Text = '<�������˿�����>'
        WorkView = WorkView
        FieldName = '�������˿�����'
        SynchronizeWhenExit = True
      end
      object edtCommPortNo: TWVEdit
        Left = 118
        Top = 295
        Width = 188
        Height = 20
        Color = clWhite
        MaxLength = 22
        ReadOnly = False
        TabOrder = 16
        Text = '<ͨѶ�˿ں�>'
        WorkView = WorkView
        FieldName = 'ͨѶ�˿ں�'
        SynchronizeWhenExit = True
      end
      object edtNo: TWVEdit
        Left = 398
        Top = 40
        Width = 188
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 1
        Text = '<����˳���>'
        WorkView = WorkView
        FieldName = '����˳���'
        SynchronizeWhenExit = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 76
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
        Name = '��ѯ.�豸����'
        Caption = '��ѯ.�豸����'
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
        Name = '��ѯ.�豸������'
        Caption = '��ѯ.�豸������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.�豸����'
        Caption = '��ѯ.�豸����'
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
        Name = '��ѯ.�豸����'
        Caption = '��ѯ.�豸����'
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
        Name = '��ѯ.�豸��;'
        Caption = '��ѯ.�豸��;'
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
        Name = '��ѯ.������ϵͳ'
        Caption = '��ѯ.������ϵͳ'
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
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
        Name = '��ѯ.��Ƭ�ṹ'
        Caption = '��ѯ.��Ƭ�ṹ'
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
        DataField = 'lvol4'
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
        Name = '�豸����'
        Caption = '�豸����'
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
        Name = '�豸������'
        Caption = '�豸������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = True
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sphone3'
      end
      item
        Name = '�豸����'
        Caption = '�豸����'
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
        DataField = 'lbank_acc_type'
      end
      item
        Name = '�豸����'
        Caption = '�豸����'
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
        Name = '�豸��;'
        Caption = '�豸��;'
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
        DataField = 'Lvol7'
      end
      item
        Name = '������ϵͳ'
        Caption = '������ϵͳ'
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
        DataField = 'lserial0'
      end
      item
        Name = '�ϼ��豸���'
        Caption = '�ϼ��豸���'
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
        DataField = 'Lvol0'
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
        Name = '��Ƭ�ṹ'
        Caption = '��Ƭ�ṹ'
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
        DataField = 'saddr'
      end
      item
        Name = '�������˿ں�'
        Caption = '�������˿ں�'
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
        DataField = 'lvol8'
      end
      item
        Name = '�������˿�����'
        Caption = '�������˿�����'
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
        Name = '�Ƿ�֧�ֿ�Ŀ�շ�'
        Caption = '�Ƿ�֧�ֿ�Ŀ�շ�'
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
        DataField = 'Lvol6'
      end
      item
        Name = '�豸����'
        Caption = '�豸����'
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
        DataField = 'lvol1'
      end
      item
        Name = 'IP��ַ'
        Caption = 'IP��ַ'
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
        DataField = 'sstation0'
      end
      item
        Name = 'ͨѶ��ʽ'
        Caption = 'ͨѶ��ʽ'
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
        Name = 'ͨѶ�˿ں�'
        Caption = 'ͨѶ�˿ں�'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.������־|��ѯ.����˳���|��ѯ.���κ�|��ѯ.�豸����|��ѯ.��' +
          '��������|��ѯ.�豸����|��ѯ.�豸����|��ѯ.�豸��;|��ѯ.������' +
          'ϵͳ|��ѯ.�ϼ��豸���|��ѯ.��������|��ѯ.��Ƭ�ṹ|��ѯ.��������' +
          '�ں�|��ѯ.�������˿�����|��ѯ.�Ƿ�֧�ֿ�Ŀ�շ�|��ѯ.�豸����|��' +
          'ѯ.|��ѯ.ͨѶ��ʽ|��ѯ.ͨѶ�˿ں�|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|����˳���|���κ�|˳���|�豸����|�豸���|�豸����|�豸����|��' +
          '����;|������ϵͳ|�ϼ���|��������|��Ƭ�ṹ|�������˿ں�|������' +
          '�˿�����|�Ƿ�֧�ֿ�Ŀ�շ�|�豸����||ͨѶ��ʽ|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 8
    Top = 376
  end
  inherited QueryRequest: TWVRequest
    ID = '�豸��Ϣ��ѯ'
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
        ParamName = '���κ�'
        FieldName = '��ѯ.���κ�'
      end
      item
        ParamName = '�豸����'
        FieldName = '��ѯ.�豸����'
      end
      item
        ParamName = '�豸������'
        FieldName = '��ѯ.�豸������'
      end
      item
        ParamName = '�豸����'
        FieldName = '��ѯ.�豸����'
      end
      item
        ParamName = '�豸����'
        FieldName = '��ѯ.�豸����'
      end
      item
        ParamName = '�豸��;'
        FieldName = '��ѯ.�豸��;'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = '��ѯ.������ϵͳ'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��Ƭ�ṹ'
        FieldName = '��ѯ.��Ƭ�ṹ'
      end>
    Left = 136
    Top = 376
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'Lvol7'
        DataPresentType = 'Idobjects'
        DataPresentParam = '81'
      end
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'Idobjects'
        DataPresentParam = '-28'
      end
      item
        FieldName = 'lserial0'
        DataPresentType = 'Idobjects'
        DataPresentParam = '-32'
      end
      item
        FieldName = 'Lvol6'
        DataPresentType = 'Idobjects'
        DataPresentParam = '64'
      end
      item
        FieldName = 'saddr'
        DataPresentType = 'Idobjects'
        DataPresentParam = '48'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'Idobjects'
        DataPresentParam = '50'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-35'
      end
      item
        FieldName = 'sserial1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '47'
      end>
    Left = 44
    Top = 407
  end
  inherited AddRequest: TWVRequest
    ID = '�豸�������'
    Bindings = <
      item
        ParamName = '����˳���'
        FieldName = '����˳���'
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '˳���'
        FieldName = '˳���'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�豸���'
        FieldName = '�豸���'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�豸��;'
        FieldName = '�豸��;'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = '������ϵͳ'
      end
      item
        ParamName = '�ϼ���'
        FieldName = '�ϼ���'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��Ƭ�ṹ'
        FieldName = '��Ƭ�ṹ'
      end
      item
        ParamName = '�������˿ں�'
        FieldName = '�������˿ں�'
      end
      item
        ParamName = '�������˿�����'
        FieldName = '�������˿�����'
      end
      item
        ParamName = '�Ƿ�֧�ֿ�Ŀ�շ�'
        FieldName = '�Ƿ�֧�ֿ�Ŀ�շ�'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = 'ͨѶ��ʽ'
        FieldName = 'ͨѶ��ʽ'
      end
      item
        ParamName = 'ͨѶ�˿ں�'
        FieldName = 'ͨѶ�˿ں�.����'
      end>
    Left = 40
    Top = 376
  end
  inherited DeleteRequest: TWVRequest
    ID = '�豸�������'
    Bindings = <
      item
        ParamName = '����˳���'
        FieldName = '����˳���'
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�豸������'
        FieldName = '�豸������'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�豸��;'
        FieldName = '�豸��;'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = '������ϵͳ'
      end
      item
        ParamName = '�ϼ��豸���'
        FieldName = '�ϼ��豸���'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��Ƭ�ṹ'
        FieldName = '��Ƭ�ṹ'
      end
      item
        ParamName = '�������˿ں�'
        FieldName = '�������˿ں�'
      end
      item
        ParamName = '�������˿�����'
        FieldName = '�������˿�����'
      end
      item
        ParamName = '�Ƿ�֧�ֿ�Ŀ�շ�'
        FieldName = '�Ƿ�֧�ֿ�Ŀ�շ�'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = 'IP��ַ'
        FieldName = 'IP��ַ'
      end
      item
        ParamName = 'ͨѶ��ʽ'
        FieldName = 'ͨѶ��ʽ'
      end
      item
        ParamName = 'ͨѶ�˿ں�'
        FieldName = 'ͨѶ�˿ں�'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 72
    Top = 376
  end
  inherited ChangeRequest: TWVRequest
    ID = '�豸�������'
    Bindings = <
      item
        ParamName = '����˳���'
        FieldName = '����˳���'
      end
      item
        ParamName = '���κ�'
        FieldName = '���κ�'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�豸������'
        FieldName = '�豸������'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�豸��;'
        FieldName = '�豸��;'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = '������ϵͳ'
      end
      item
        ParamName = '�ϼ��豸���'
        FieldName = '�ϼ��豸���'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��Ƭ�ṹ'
        FieldName = '��Ƭ�ṹ'
      end
      item
        ParamName = '�������˿ں�'
        FieldName = '�������˿ں�'
      end
      item
        ParamName = '�������˿�����'
        FieldName = '�������˿�����'
      end
      item
        ParamName = '�Ƿ�֧�ֿ�Ŀ�շ�'
        FieldName = '�Ƿ�֧�ֿ�Ŀ�շ�'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = 'IP��ַ'
        FieldName = 'IP��ַ'
      end
      item
        ParamName = 'ͨѶ��ʽ'
        FieldName = 'ͨѶ��ʽ'
      end
      item
        ParamName = 'ͨѶ�˿ں�'
        FieldName = 'ͨѶ�˿ں�'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 104
    Top = 376
  end
  inherited WVDataSource: TWVDataSource
    Left = 140
    Top = 407
  end
  inherited alDatasetActions: TActionList
    Left = 108
    Top = 404
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
    Left = 8
    Top = 336
  end
  object WVRImpCheck: TWVRequest
    WorkView = WVImpCheck
    ID = '�豸�������'
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
    Left = 40
    Top = 336
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
    Left = 144
    Top = 328
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�豸����ɾ��'
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
    Left = 176
    Top = 328
  end
end
