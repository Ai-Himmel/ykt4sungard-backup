inherited faqhSetBusinessInfo: TfaqhSetBusinessInfo
  Width = 808
  Height = 511
  Caption = '�̻���Ϣ����'
  inherited pcPages: TRzPageControl
    Width = 808
    Height = 511
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      object Label30: TLabel [0]
        Left = 344
        Top = 64
        Width = 128
        Height = 16
        Caption = '�����ѡ���̻�'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object Splitter1: TSplitter [1]
        Left = 273
        Top = 33
        Width = 4
        Height = 425
        Cursor = crHSplit
      end
      object Panel1: TPanel [2]
        Left = 0
        Top = 0
        Width = 804
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label1: TLabel
          Left = 22
          Top = 10
          Width = 36
          Height = 12
          Caption = '�̻���'
        end
        object Label25: TLabel
          Left = 202
          Top = 10
          Width = 48
          Height = 12
          Caption = '�̻�����'
        end
        object Label26: TLabel
          Left = 396
          Top = 10
          Width = 48
          Height = 12
          Caption = '�̻����'
        end
        object Label27: TLabel
          Left = 586
          Top = 9
          Width = 48
          Height = 12
          Caption = '��������'
        end
        object WVEdit2: TWVEdit
          Left = 260
          Top = 6
          Width = 120
          Height = 20
          Color = clWhite
          ImeName = '���� (����) - ΢��ƴ��'
          ReadOnly = False
          TabOrder = 2
          Text = '<��ѯ.�̻�����>'
          WorkView = WorkView
          FieldName = '��ѯ.�̻�����'
          SynchronizeWhenExit = True
        end
        object WVComboBox8: TWVComboBox
          Left = 456
          Top = 6
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '��ѯ.�̻����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*14'
        end
        object WVComboBox9: TWVComboBox
          Left = 644
          Top = 5
          Width = 120
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '��ѯ.�Ƿ�Ϊ��������'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*2'
        end
        object edtBusiId: TWVEdit
          Left = 68
          Top = 6
          Width = 120
          Height = 20
          Color = clWhite
          ImeName = '���� (����) - ΢��ƴ��'
          MaxLength = 22
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.�̻���ʶ>'
          WorkView = WorkView
          FieldName = '��ѯ.�̻���ʶ'
          SynchronizeWhenExit = True
        end
      end
      inherited UIPanel1: TUIPanel
        Top = 458
        Width = 804
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 543
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 629
        end
        inherited btnQuery: TBitBtn [2]
          Left = 457
        end
        inherited btnDelete: TBitBtn
          Left = 715
          Hint = 'ע����ǰѡ�е���Ŀ'
          Caption = 'ע��(&D)'
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 90
          Width = 159
        end
        inherited RBtnAddBrother: TRzRadioButton
          Left = 336
        end
        inherited RbtnAddChild: TRzRadioButton
          Left = 256
        end
      end
      inherited TreeView: TRzTreeView
        Top = 33
        Width = 273
        Height = 425
        Align = alLeft
        DragMode = dmManual
        TabOrder = 1
      end
      inherited Grid: TRzDBGrid
        Left = 277
        Top = 33
        Width = 527
        Height = 425
        Align = alClient
        ImeName = ''
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        TabOrder = 2
        OnCellClick = GridCellClick
        Columns = <
          item
            Expanded = False
            FieldName = 'sbranch_code0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻�����'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol7'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻�����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smain_flag2'
            PickList.Strings = ()
            Title.Caption = 'ĩ���̻�'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'smain_flag'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_type'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�մ���'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smarket_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'Ӷ������'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'drate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'Ӷ�����(%)'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'drate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ɱ���(%)'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���д���'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_acc2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�����ʺ�'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbankname2'
            PickList.Strings = ()
            Title.Caption = '�����ʻ���'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ϼ��̻�'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ϼ��̻���'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Caption = '��ϵ��'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'smarket_code2'
            PickList.Strings = ()
            Title.Caption = '֤������'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail2'
            PickList.Strings = ()
            Title.Caption = '֤������'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone2'
            PickList.Strings = ()
            Title.Caption = '�ֻ�'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Caption = '��������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Caption = '��ַ'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spost_code'
            PickList.Strings = ()
            Title.Caption = '�ʱ�'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no'
            PickList.Strings = ()
            Title.Caption = '����'
            Width = 60
            Visible = True
          end>
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label2: TLabel [0]
        Left = 312
        Top = 41
        Width = 42
        Height = 12
        Caption = '�̻���*'
      end
      object Label10: TLabel [1]
        Left = 330
        Top = 236
        Width = 24
        Height = 12
        Caption = '�绰'
      end
      object Label11: TLabel [2]
        Left = 51
        Top = 202
        Width = 36
        Height = 12
        Caption = '��ϵ��'
      end
      object Label12: TLabel [3]
        Left = 306
        Top = 203
        Width = 48
        Height = 12
        Caption = '֤������'
      end
      object Label13: TLabel [4]
        Left = 585
        Top = 235
        Width = 24
        Height = 12
        Caption = '�ֻ�'
      end
      object Label15: TLabel [5]
        Left = 39
        Top = 267
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Label16: TLabel [6]
        Left = 306
        Top = 268
        Width = 48
        Height = 12
        Caption = '��ϵ��ַ'
      end
      object WVLabel1: TWVLabel [7]
        Left = 585
        Top = 268
        Width = 24
        Height = 12
        Caption = '�ʱ�'
      end
      object Bevel1: TBevel [8]
        Left = 32
        Top = 189
        Width = 753
        Height = 2
        Shape = bsFrame
        Style = bsRaised
      end
      object Label32: TLabel [9]
        Left = 39
        Top = 235
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Label4: TLabel [10]
        Left = 45
        Top = 41
        Width = 42
        Height = 12
        Caption = '���̻�*'
      end
      object Label6: TLabel [11]
        Left = 300
        Top = 73
        Width = 54
        Height = 12
        Caption = '�̻�����*'
      end
      object Label7: TLabel [12]
        Left = 33
        Top = 106
        Width = 54
        Height = 12
        Caption = '��������*'
      end
      object Label31: TLabel [13]
        Left = 57
        Top = 73
        Width = 30
        Height = 12
        Caption = '����*'
      end
      object Label5: TLabel [14]
        Left = 553
        Top = 41
        Width = 54
        Height = 12
        Caption = '�̻�����*'
      end
      object Label14: TLabel [15]
        Left = 561
        Top = 203
        Width = 48
        Height = 12
        Caption = '֤������'
      end
      object Label22: TLabel [16]
        Left = 306
        Top = 171
        Width = 48
        Height = 12
        Caption = '�����ʺ�'
      end
      object Label37: TLabel [17]
        Left = 33
        Top = 138
        Width = 54
        Height = 12
        Caption = 'Ӷ������*'
      end
      object Label35: TLabel [18]
        Left = 306
        Top = 138
        Width = 48
        Height = 12
        Caption = 'Ӷ�����'
      end
      object Label36: TLabel [19]
        Left = 516
        Top = 135
        Width = 6
        Height = 12
        Caption = '%'
      end
      object Label18: TLabel [20]
        Left = 282
        Top = 106
        Width = 72
        Height = 12
        Caption = '�����ɱ���'
      end
      object Label24: TLabel [21]
        Left = 39
        Top = 170
        Width = 48
        Height = 12
        Caption = '���д���'
      end
      object Label38: TLabel [22]
        Left = 549
        Top = 170
        Width = 60
        Height = 12
        Caption = '�����ʻ���'
      end
      object Bevel2: TBevel [23]
        Left = 32
        Top = 155
        Width = 753
        Height = 2
        Shape = bsFrame
        Style = bsRaised
      end
      object Label3: TLabel [24]
        Left = 516
        Top = 105
        Width = 6
        Height = 12
        Caption = '%'
      end
      object Label8: TLabel [25]
        Left = 561
        Top = 74
        Width = 48
        Height = 12
        Caption = '�մ���'
      end
      inherited UIPanel2: TUIPanel
        Top = 452
        Width = 804
        TabOrder = 22
        inherited btnOK: TBitBtn
          Left = 620
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          OnClick = DBNavigatorClick
        end
      end
      object WVEdit10: TWVEdit
        Left = 360
        Top = 231
        Width = 150
        Height = 20
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 14
        ReadOnly = False
        TabOrder = 17
        Text = '<�绰>'
        WorkView = WorkView
        FieldName = '�绰'
        SynchronizeWhenExit = True
      end
      object WVEdit11: TWVEdit
        Left = 96
        Top = 198
        Width = 173
        Height = 20
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ReadOnly = False
        TabOrder = 13
        Text = '<��ϵ��>'
        WorkView = WorkView
        FieldName = '��ϵ��'
        SynchronizeWhenExit = True
      end
      object WVEdit15: TWVEdit
        Left = 96
        Top = 264
        Width = 173
        Height = 20
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ReadOnly = False
        TabOrder = 19
        Text = '<��������>'
        WorkView = WorkView
        FieldName = '��������'
        SynchronizeWhenExit = True
      end
      object WVEdit16: TWVEdit
        Left = 360
        Top = 264
        Width = 150
        Height = 20
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ReadOnly = False
        TabOrder = 20
        Text = '<��ַ>'
        WorkView = WorkView
        FieldName = '��ַ'
        SynchronizeWhenExit = True
      end
      object cbbBusiType: TWVComboBox
        Left = 360
        Top = 69
        Width = 150
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 0
        TabOrder = 3
        Text = '<�̻�����>'
        OnChange = cbbBusiTypeChange
        WorkView = WorkView
        FieldName = '�̻�����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*14'
      end
      object WVComboBox5: TWVComboBox
        Left = 360
        Top = 199
        Width = 150
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 0
        TabOrder = 15
        Text = '<֤������>'
        WorkView = WorkView
        FieldName = '֤������'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '*87'
      end
      object WVEdit1: TWVEdit
        Left = 617
        Top = 264
        Width = 150
        Height = 20
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 6
        ReadOnly = False
        TabOrder = 21
        Text = '<�ʱ�>'
        WorkView = WorkView
        FieldName = '�ʱ�'
      end
      object edtId: TWVEdit
        Left = 360
        Top = 37
        Width = 150
        Height = 20
        Color = clInfoBk
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ReadOnly = False
        TabOrder = 1
        Text = '<�̻���ʶ>'
        WorkView = WorkView
        FieldName = '�̻���ʶ'
        SynchronizeWhenExit = True
      end
      object WVComboBox13: TWVComboBox
        Left = 96
        Top = 231
        Width = 173
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '�Ϲ�ƴ�����뷨'
        ItemHeight = 0
        TabOrder = 16
        Text = '<����>'
        WorkView = WorkView
        FieldName = '����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-22'
      end
      object edtPId: TWVEdit
        Left = 96
        Top = 37
        Width = 173
        Height = 20
        Color = clInfoBk
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ReadOnly = False
        TabOrder = 0
        Text = '<���̻���ʶ>'
        WorkView = WorkView
        FieldName = '���̻���ʶ'
      end
      object WVEdit5: TWVEdit
        Left = 616
        Top = 38
        Width = 151
        Height = 20
        Color = clInfoBk
        ImeName = '���� (����) - ΢��ƴ��'
        ReadOnly = False
        TabOrder = 2
        Text = '<�̻�����>'
        WorkView = WorkView
        FieldName = '�̻�����'
        SynchronizeWhenExit = True
      end
      object cbbCheckSelf: TWVComboBox
        Left = 96
        Top = 103
        Width = 173
        Height = 18
        Style = csOwnerDrawFixed
        Color = clInfoBk
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 12
        TabOrder = 7
        Text = '<��������>'
        OnChange = cbbCheckSelfChange
        WorkView = WorkView
        FieldName = '��������'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
      object WVComboBox12: TWVComboBox
        Left = 96
        Top = 70
        Width = 173
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ImeName = '�Ϲ�ƴ�����뷨'
        ItemHeight = 0
        TabOrder = 4
        Text = '<����>'
        WorkView = WorkView
        FieldName = '����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-27'
      end
      object WVEdit14: TWVEdit
        Left = 617
        Top = 198
        Width = 150
        Height = 20
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ReadOnly = False
        TabOrder = 14
        Text = '<֤������>'
        WorkView = WorkView
        FieldName = '֤������'
        SynchronizeWhenExit = True
      end
      object edtBankAccNo: TWVEdit
        Left = 360
        Top = 166
        Width = 150
        Height = 20
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ReadOnly = False
        TabOrder = 11
        Text = '<�����ʺ�>'
        WorkView = WorkView
        FieldName = '�����ʺ�'
        SynchronizeWhenExit = True
      end
      object cbbEmpRateType: TWVComboBox
        Left = 96
        Top = 134
        Width = 173
        Height = 18
        Style = csOwnerDrawFixed
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 12
        TabOrder = 9
        Text = '<Ӷ������>'
        WorkView = WorkView
        FieldName = 'Ӷ������'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*91'
      end
      object edtEmpRate: TWVEdit
        Left = 360
        Top = 133
        Width = 150
        Height = 20
        Color = clWhite
        DragKind = dkDock
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ReadOnly = False
        TabOrder = 8
        Text = '<Ӷ�����>'
        WorkView = WorkView
        FieldName = 'Ӷ�����'
      end
      object edtFee: TWVEdit
        Left = 360
        Top = 101
        Width = 150
        Height = 20
        Color = clWhite
        DragKind = dkDock
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ReadOnly = False
        TabOrder = 6
        Text = '<�����ɱ���>'
        WorkView = WorkView
        FieldName = '�����ɱ���'
      end
      object edtBankAccName: TWVEdit
        Left = 617
        Top = 165
        Width = 150
        Height = 20
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ReadOnly = False
        TabOrder = 10
        Text = '<�����ʻ���>'
        WorkView = WorkView
        FieldName = '�����ʻ���'
        SynchronizeWhenExit = True
      end
      object WVEdit4: TWVEdit
        Left = 617
        Top = 231
        Width = 150
        Height = 20
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 15
        ReadOnly = False
        TabOrder = 18
        Text = '<�ֻ�>'
        WorkView = WorkView
        FieldName = '�ֻ�'
        SynchronizeWhenExit = True
      end
      object cbbBankCode: TWVComboBox
        Left = 96
        Top = 167
        Width = 173
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '�Ϲ�ƴ�����뷨'
        ItemHeight = 0
        TabOrder = 12
        Text = '<���д���>'
        WorkView = WorkView
        FieldName = '���д���'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*110'
      end
      object cbbDhf: TWVComboBox
        Left = 616
        Top = 71
        Width = 153
        Height = 18
        Style = csOwnerDrawFixed
        Color = clWhite
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 12
        TabOrder = 5
        Text = '<�Ƿ��մ���>'
        OnChange = cbbCheckSelfChange
        WorkView = WorkView
        FieldName = '�Ƿ��մ���'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*2'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 68
    Top = 375
  end
  inherited QueryRequest: TWVRequest
    ID = '�̻���Ϣ��������ѯ'
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
        ParamName = '�̻���ʶ'
        FieldName = '��ѯ.�̻���ʶ'
        DefaultValue = 0
      end
      item
        ParamName = '���̻���ʶ'
        FieldName = '��ѯ.���̻���ʶ'
      end
      item
        ParamName = '�̻�����'
        FieldName = '��ѯ.�̻�����'
      end
      item
        ParamName = '�̻����'
        FieldName = '��ѯ.�̻����'
      end
      item
        ParamName = '�Ƿ�Ϊ��������'
        FieldName = '��ѯ.�Ƿ�Ϊ��������'
      end
      item
        ParamName = '�Ƿ�ΪҶ�ڵ�'
        FieldName = '��ѯ.�Ƿ�ΪҶ�ڵ�'
      end>
    Left = 72
    Top = 344
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sbranch_code0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-27'
      end
      item
        FieldName = 'lvol7'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '14'
      end
      item
        FieldName = 'smain_flag2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'smain_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '91'
      end
      item
        FieldName = 'scert_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end
      item
        FieldName = 'smarket_code2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '87'
      end
      item
        FieldName = 'sbank_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '110'
      end
      item
        FieldName = 'scust_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'lvol1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-39'
      end>
    Left = 100
    Top = 375
  end
  inherited AddRequest: TWVRequest
    ID = '�̻���Ϣ����'
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
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = '�̻���ʶ'
      end
      item
        ParamName = '���̻���ʶ'
        FieldName = '���̻���ʶ'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
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
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��ϵ��'
        FieldName = '��ϵ��'
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
        ParamName = '��ַ'
        FieldName = '��ַ'
      end
      item
        ParamName = '�ʱ�'
        FieldName = '�ʱ�'
      end
      item
        ParamName = 'Ӷ������'
        FieldName = 'Ӷ������'
      end
      item
        ParamName = 'Ӷ�����'
        FieldName = 'Ӷ�����'
      end
      item
        ParamName = '�����ɱ���'
        FieldName = '�����ɱ���'
      end
      item
        ParamName = '���д���'
        FieldName = '���д���'
      end
      item
        ParamName = '�����ʺ�'
        FieldName = '�����ʺ�'
      end
      item
        ParamName = '�����ʻ���'
        FieldName = '�����ʻ���'
      end
      item
        ParamName = 'ĩ���̻�'
        FieldName = 'ĩ���̻�'
      end
      item
        ParamName = '�Ƿ��մ���'
        FieldName = '�Ƿ��մ���'
      end>
    Top = 344
  end
  inherited DeleteRequest: TWVRequest
    ID = '�̻���Ϣ����'
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
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = '�̻���ʶ'
      end
      item
        ParamName = '���̻���ʶ'
        FieldName = '���̻���ʶ'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
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
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��ϵ��'
        FieldName = '��ϵ��'
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
        ParamName = '��ַ'
        FieldName = '��ַ'
      end
      item
        ParamName = '�ʱ�'
        FieldName = '�ʱ�'
      end
      item
        ParamName = 'Ӷ������'
        FieldName = 'Ӷ������'
      end
      item
        ParamName = 'Ӷ�����'
        FieldName = 'Ӷ�����'
      end
      item
        ParamName = '�����ɱ���'
        FieldName = '�����ɱ���'
      end
      item
        ParamName = '���д���'
        FieldName = '���д���'
      end
      item
        ParamName = '�����ʺ�'
        FieldName = '�����ʺ�'
      end
      item
        ParamName = '�����ʻ���'
        FieldName = '�����ʻ���'
      end
      item
        ParamName = 'ĩ���̻�'
        FieldName = 'ĩ���̻�'
      end
      item
        ParamName = '�Ƿ��մ���'
        FieldName = '�Ƿ��մ���'
      end>
    Top = 344
  end
  inherited ChangeRequest: TWVRequest
    ID = '�̻���Ϣ����'
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
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = '�̻���ʶ'
      end
      item
        ParamName = '���̻���ʶ'
        FieldName = '���̻���ʶ'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
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
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��ϵ��'
        FieldName = '��ϵ��'
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
        ParamName = '��ַ'
        FieldName = '��ַ'
      end
      item
        ParamName = '�ʱ�'
        FieldName = '�ʱ�'
      end
      item
        ParamName = 'Ӷ������'
        FieldName = 'Ӷ������'
      end
      item
        ParamName = 'Ӷ�����'
        FieldName = 'Ӷ�����'
      end
      item
        ParamName = '�����ɱ���'
        FieldName = '�����ɱ���'
      end
      item
        ParamName = '���д���'
        FieldName = '���д���'
      end
      item
        ParamName = '�����ʺ�'
        FieldName = '�����ʺ�'
      end
      item
        ParamName = '�����ʻ���'
        FieldName = '�����ʻ���'
      end
      item
        ParamName = 'ĩ���̻�'
        FieldName = 'ĩ���̻�'
      end
      item
        ParamName = '�Ƿ��մ���'
        FieldName = '�Ƿ��մ���'
      end>
    Left = 168
    Top = 344
  end
  inherited WVDataSource: TWVDataSource
    Left = 168
    Top = 376
  end
  inherited alDatasetActions: TActionList
    Left = 132
    Top = 376
  end
  inherited WorkView: TWorkView
    WorkFields = <
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
        Name = '��ѯ.�̻���ʶ'
        Caption = '��ѯ.�̻���ʶ'
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
        DataField = 'lvol5'
      end
      item
        Name = '��ѯ.�̻�����'
        Caption = '��ѯ.�̻�����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'scard1'
      end
      item
        Name = '��ѯ.�̻����'
        Caption = '��ѯ.�̻����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sstat_type'
      end
      item
        Name = '��ѯ.�Ƿ�Ϊ��������'
        Caption = '��ѯ.�Ƿ�Ϊ��������'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'smain_flag'
      end
      item
        Name = '��ѯ.�Ƿ�ΪҶ�ڵ�'
        Caption = '��ѯ.�Ƿ�ΪҶ�ڵ�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'smarket_code2'
      end
      item
        Name = '��ѯ.���̻���ʶ'
        Caption = '��ѯ.���̻���ʶ'
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
      end
      item
        Name = '�̻���ʶ'
        Caption = '�̻���ʶ'
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
        DataField = 'lvol3'
      end
      item
        Name = '���̻���ʶ'
        Caption = '���̻���ʶ'
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
        DataField = 'sall_name'
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
        DataField = 'sbranch_code0'
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
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'scert_no'
      end
      item
        Name = '�̻�����'
        Caption = '�̻�����'
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
        DataField = 'lvol7'
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
        DataField = 'smain_flag'
      end
      item
        Name = '��ϵ��'
        Caption = '��ϵ��'
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'semail2'
      end
      item
        Name = '�绰'
        Caption = '�绰'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 14
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
        Checker.MinLength = 0
        Checker.MaxLength = 15
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
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'semail'
      end
      item
        Name = '��ַ'
        Caption = '��ַ'
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
        DataField = 'scusttypes'
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
        Checker.MaxLength = 6
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'spost_code'
      end
      item
        Name = 'Ӷ������'
        Caption = 'Ӷ������'
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
        DataField = 'smarket_code'
      end
      item
        Name = 'Ӷ�����'
        Caption = 'Ӷ�����'
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
        DataField = 'drate0'
      end
      item
        Name = '�����ɱ���'
        Caption = '�����ɱ���'
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
        DataField = 'drate1'
      end
      item
        Name = '���д���'
        Caption = '���д���'
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
        DataField = 'sbank_code'
      end
      item
        Name = '�����ʺ�'
        Caption = '�����ʺ�'
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
        DataField = 'sbank_acc2'
      end
      item
        Name = '�����ʻ���'
        Caption = '�����ʻ���'
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
        DataField = 'sbankname2'
      end
      item
        Name = 'ĩ���̻�'
        Caption = 'ĩ���̻�'
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
        DataField = 'smain_flag2'
      end
      item
        Name = '�Ƿ��մ���'
        Caption = '�Ƿ��մ���'
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
        DataField = 'scust_type'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|�̻���ʶ|���̻���ʶ|�̻�����|�̻����|�Ƿ�Ϊ��������|�Ƿ�ΪҶ��' +
          '��|�̻�״̬|����������|�Ƿ���ȡ�����|У��|��ϵ�˰༶���ź�|��' +
          '������|'
      end>
    Left = 40
    Top = 344
  end
  object WorkView1: TWorkView
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
        Name = '�̻���ʶ'
        Caption = '�̻���ʶ'
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
        DataField = 'lvol5'
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
          '|�̻���ʶ|���̻���ʶ|�̻�����|�̻����|�Ƿ�Ϊ��������|�Ƿ�ΪҶ��' +
          '��|�̻�״̬|����������|�Ƿ���ȡ�����|У��|��ϵ�˰༶���ź�|��' +
          '������|'
      end>
    Left = 72
    Top = 408
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�̻���Ϣ������ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�̻���ʶ'
        FieldName = '�̻���ʶ'
        DefaultValue = 0
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    AfterExec = CheckReturnData
    Left = 104
    Top = 408
  end
end
