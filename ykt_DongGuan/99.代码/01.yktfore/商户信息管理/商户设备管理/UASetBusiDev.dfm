inherited faqhSetBusiDev: TfaqhSetBusiDev
  Width = 839
  Height = 477
  Caption = '�̻��豸����'
  inherited pcPages: TRzPageControl
    Width = 839
    Height = 477
    ActivePage = tsQuery
    TabIndex = 0
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 835
        TabOrder = 1
        inherited btnAdd: TBitBtn [0]
          Left = 573
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 661
          Enabled = False
          TabOrder = 4
        end
        inherited btnQuery: TBitBtn [2]
          Left = 485
        end
        inherited btnDelete: TBitBtn
          Left = 746
          Enabled = False
          TabOrder = 2
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 835
        TabOrder = 3
      end
      inherited Grid: TRzDBGrid
        Top = 73
        Width = 835
        Height = 351
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
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
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸�ն����к�'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ʡ�豸�ն����к�'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstock_code'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�豸����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scurrency_type'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '״̬'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ע������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ͣ������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���豸���'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ע'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������ʱ��'
            Width = 80
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 835
        Height = 55
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label3: TLabel
          Left = 22
          Top = 10
          Width = 84
          Height = 12
          Caption = '�豸�ն����к�'
        end
        object Label4: TLabel
          Left = 10
          Top = 34
          Width = 96
          Height = 12
          Caption = 'ʡ�豸�ն����к�'
        end
        object Label5: TLabel
          Left = 282
          Top = 10
          Width = 48
          Height = 12
          Caption = '�豸����'
        end
        object Label6: TLabel
          Left = 306
          Top = 34
          Width = 24
          Height = 12
          Caption = '״̬'
        end
        object WVEdit3: TWVEdit
          Left = 116
          Top = 6
          Width = 133
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.�豸�ն����к�>'
          WorkView = WorkView
          FieldName = '��ѯ.�豸�ն����к�'
        end
        object WVEdit4: TWVEdit
          Left = 116
          Top = 30
          Width = 133
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.ʡ�豸�ն����к�>'
          WorkView = WorkView
          FieldName = '��ѯ.ʡ�豸�ն����к�'
        end
        object WVComboBox3: TWVComboBox
          Left = 340
          Top = 3
          Width = 141
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '��ѯ.�豸����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*221'
        end
        object WVComboBox4: TWVComboBox
          Left = 340
          Top = 27
          Width = 141
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '���� (����) - ΢��ƴ��'
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '��ѯ.״̬'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*239'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label10: TLabel [0]
        Left = 78
        Top = 60
        Width = 36
        Height = 12
        Caption = '�̻���'
      end
      object Label13: TLabel [1]
        Left = 84
        Top = 164
        Width = 6
        Height = 12
        Caption = '�'
      end
      object Label14: TLabel [2]
        Left = 66
        Top = 166
        Width = 48
        Height = 12
        Caption = '�豸����'
      end
      object Label1: TLabel [3]
        Left = 18
        Top = 130
        Width = 96
        Height = 12
        Caption = 'ʡ�豸�ն����к�'
      end
      object btnQBusi: TSpeedButton [4]
        Left = 243
        Top = 56
        Width = 23
        Height = 22
        Caption = '>>>'
        Flat = True
        OnClick = btnQBusiClick
      end
      object Label2: TLabel [5]
        Left = 66
        Top = 96
        Width = 48
        Height = 12
        Caption = '�̻�����'
      end
      object Label7: TLabel [6]
        Left = 90
        Top = 200
        Width = 24
        Height = 12
        Caption = '��ע'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 835
        TabOrder = 3
        inherited btnOK: TBitBtn
          Left = 659
        end
        inherited btnCancel: TBitBtn
          Left = 747
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtSSNo: TWVEdit
        Left = 124
        Top = 126
        Width = 277
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<ʡ�豸�ն����к�>'
        WorkView = WorkView
        FieldName = 'ʡ�豸�ն����к�'
        SynchronizeWhenExit = True
      end
      object cbbDevType: TWVComboBox
        Left = 124
        Top = 161
        Width = 277
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 12
        TabOrder = 2
        WorkView = WorkView
        FieldName = '�豸����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*221'
      end
      object edtBusiName: TWVEdit
        Left = 124
        Top = 92
        Width = 277
        Height = 20
        Enabled = False
        ParentColor = True
        ReadOnly = False
        TabOrder = 4
        SynchronizeWhenExit = True
      end
      object WVEdit2: TWVEdit
        Left = 124
        Top = 196
        Width = 277
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 5
        Text = '<��ע>'
        WorkView = WorkView
        FieldName = '��ע'
        SynchronizeWhenExit = True
      end
      object pnlBusiQ: TPanel
        Left = 270
        Top = 56
        Width = 539
        Height = 353
        TabOrder = 6
        object Panel2: TPanel
          Left = 1
          Top = 1
          Width = 537
          Height = 79
          Align = alTop
          BevelOuter = bvNone
          ParentColor = True
          TabOrder = 0
          object Label9: TLabel
            Left = 230
            Top = 10
            Width = 60
            Height = 12
            Caption = '�����̻���'
          end
          object Label11: TLabel
            Left = 30
            Top = 34
            Width = 60
            Height = 12
            Caption = 'ʡ�̻����'
          end
          object Label12: TLabel
            Left = 42
            Top = 10
            Width = 48
            Height = 12
            Caption = '�̻�����'
          end
          object Label17: TLabel
            Left = 242
            Top = 58
            Width = 48
            Height = 12
            Caption = '�̻�����'
          end
          object Label18: TLabel
            Left = 42
            Top = 58
            Width = 48
            Height = 12
            Caption = '��ҵ����'
          end
          object Label25: TLabel
            Left = 242
            Top = 34
            Width = 48
            Height = 12
            Caption = '�̻�״̬'
          end
          object WVEdit7: TWVEdit
            Left = 300
            Top = 6
            Width = 120
            Height = 20
            Color = clInfoBk
            ReadOnly = False
            TabOrder = 1
            Text = '<��ѯ.�����̻���>'
            WorkView = WorkView1
            FieldName = '��ѯ.�����̻���'
          end
          object WVEdit8: TWVEdit
            Left = 100
            Top = 30
            Width = 121
            Height = 20
            Color = clInfoBk
            ReadOnly = False
            TabOrder = 2
            Text = '<��ѯ.ʡ�̻����>'
            WorkView = WorkView1
            FieldName = '��ѯ.ʡ�̻����'
          end
          object WVEdit9: TWVEdit
            Left = 100
            Top = 6
            Width = 121
            Height = 20
            Color = clInfoBk
            ReadOnly = False
            TabOrder = 0
            Text = '<��ѯ.�̻���>'
            WorkView = WorkView1
            FieldName = '��ѯ.�̻���'
          end
          object WVComboBox8: TWVComboBox
            Left = 300
            Top = 30
            Width = 120
            Height = 20
            Style = csDropDownList
            Color = clInfoBk
            ImeName = '���� (����) - ΢��ƴ��'
            ItemHeight = 12
            TabOrder = 3
            WorkView = WorkView1
            FieldName = '��ѯ.�̻�״̬'
            DataPresentType = 'IDOBJECTS'
            SeperatedStr = '-'
            AutoDropDown = False
            ItemsDataEntry = '*224'
          end
          object WVComboBox1: TWVComboBox
            Left = 300
            Top = 54
            Width = 120
            Height = 20
            Style = csDropDownList
            Color = clInfoBk
            ImeName = '���� (����) - ΢��ƴ��'
            ItemHeight = 12
            TabOrder = 5
            WorkView = WorkView1
            FieldName = '��ѯ.�̻�����'
            DataPresentType = 'IDOBJECTS'
            SeperatedStr = '-'
            AutoDropDown = False
            ItemsDataEntry = '*216'
          end
          object WVComboBox2: TWVComboBox
            Left = 100
            Top = 54
            Width = 121
            Height = 20
            Style = csDropDownList
            Color = clInfoBk
            ImeName = '���� (����) - ΢��ƴ��'
            ItemHeight = 12
            TabOrder = 4
            WorkView = WorkView1
            FieldName = '��ѯ.��ҵ����'
            DataPresentType = 'IDOBJECTS'
            SeperatedStr = '-'
            AutoDropDown = False
            ItemsDataEntry = '*217'
          end
          object btnQ: TButton
            Left = 436
            Top = 50
            Width = 65
            Height = 25
            Caption = '�� ѯ'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
            Font.Style = []
            ParentFont = False
            TabOrder = 6
            OnClick = btnQClick
          end
        end
        object Grid1: TRzDBGrid
          Left = 1
          Top = 80
          Width = 537
          Height = 236
          Align = alClient
          Color = clWhite
          DataSource = DataSource1
          FixedColor = 15458000
          ImeName = 'ƴ���ӼӼ��ϰ�'
          TabOrder = 1
          TitleFont.Charset = GB2312_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -12
          TitleFont.Name = '����'
          TitleFont.Style = []
          OnDrawColumnCell = Grid1DrawColumnCell
          OnDblClick = Grid1DblClick
          FrameColor = 12164479
          FrameStyle = fsGroove
          FrameVisible = True
          FixedLineColor = 12164479
          LineColor = clBackground
          Columns = <
            item
              Expanded = False
              FieldName = 'lvol0'
              Title.Alignment = taCenter
              Title.Caption = '�̻����'
              Width = 60
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sname'
              Title.Alignment = taCenter
              Title.Caption = '�����̻���'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sname2'
              Title.Alignment = taCenter
              Title.Caption = 'ʡ�̻����'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'snote'
              Title.Alignment = taCenter
              Title.Caption = '�̻�����'
              Width = 90
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'snote2'
              Title.Alignment = taCenter
              Title.Caption = '�̻�Ӣ������'
              Width = 80
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'semail'
              Title.Alignment = taCenter
              Title.Caption = '�̻����'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sbranch_code0'
              Title.Alignment = taCenter
              Title.Caption = '�̻�����'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sbranch_code1'
              Title.Alignment = taCenter
              Title.Caption = '��ҵ����'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sbankname'
              Title.Alignment = taCenter
              Title.Caption = '��ϵ��'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sphone'
              Title.Alignment = taCenter
              Title.Caption = '�绰'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sphone2'
              Title.Alignment = taCenter
              Title.Caption = '�ֻ�'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'semail2'
              Title.Alignment = taCenter
              Title.Caption = '��������'
              Width = 90
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sphone3'
              Title.Alignment = taCenter
              Title.Caption = '����'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'vsvarstr0'
              Title.Alignment = taCenter
              Title.Caption = 'Ӫҵ��ַ'
              Width = 100
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'spost_code'
              Title.Alignment = taCenter
              Title.Caption = '��������'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'damt0'
              Title.Alignment = taCenter
              Title.Caption = '�������'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'vsvarstr1'
              Title.Alignment = taCenter
              Title.Caption = '��������'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'spager'
              Title.Alignment = taCenter
              Title.Caption = '�����˺�'
              Width = 90
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sbankname2'
              Title.Alignment = taCenter
              Title.Caption = '�����ʻ���'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'scert_no'
              Title.Alignment = taCenter
              Title.Caption = '���к�'
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sdate0'
              Title.Alignment = taCenter
              Title.Caption = '��������'
              Width = 60
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sdate1'
              Title.Alignment = taCenter
              Title.Caption = '��������'
              Width = 60
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sstatus1'
              Title.Alignment = taCenter
              Title.Caption = '�̻�״̬'
              Width = 70
              Visible = True
            end>
        end
        object pnl1: TPanel
          Left = 1
          Top = 316
          Width = 537
          Height = 36
          Align = alBottom
          TabOrder = 2
          object btnSelect: TButton
            Left = 392
            Top = 5
            Width = 65
            Height = 25
            Caption = 'ѡ  ��'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = btnSelectClick
          end
          object btnCan: TButton
            Left = 464
            Top = 5
            Width = 65
            Height = 25
            Caption = 'ȡ ��'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            OnClick = btnCanClick
          end
        end
      end
      object edtBusiId: TWVEdit
        Left = 124
        Top = 57
        Width = 118
        Height = 20
        Color = clInfoBk
        MaxLength = 22
        ReadOnly = False
        TabOrder = 0
        Text = '<�̻���>'
        WorkView = WorkView
        FieldName = '�̻���'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 124
    Top = 295
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
        Name = '��ѯ.�̻���'
        Caption = '��ѯ.�̻���'
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
        Name = '��ѯ.�豸�ն����к�'
        Caption = '��ѯ.�豸�ն����к�'
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
        Name = '��ѯ.ʡ�豸�ն����к�'
        Caption = '��ѯ.ʡ�豸�ն����к�'
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
        Name = '��ѯ.״̬'
        Caption = '��ѯ.״̬'
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
        Name = '��ѯ.ע������'
        Caption = '��ѯ.ע������'
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
        Name = '��ѯ.ͣ������'
        Caption = '��ѯ.ͣ������'
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
        Name = '�̻���'
        Caption = '�̻���'
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
        Name = '�豸�ն����к�'
        Caption = '�豸�ն����к�'
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
        DataField = 'scust_auth'
      end
      item
        Name = 'ʡ�豸�ն����к�'
        Caption = 'ʡ�豸�ն����к�'
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
        DataField = 'scust_auth2'
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
        DataField = 'sstock_code'
      end
      item
        Name = '״̬'
        Caption = '״̬'
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
        DataField = 'scurrency_type'
      end
      item
        Name = 'ע������'
        Caption = 'ע������'
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
        Name = 'ͣ������'
        Caption = 'ͣ������'
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
        Name = '���豸���'
        Caption = '���豸���'
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
        Name = '��ע'
        Caption = '��ע'
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
        Name = '������ʱ��'
        Caption = '������ʱ��'
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
        DataField = 'scust_limit2'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.������־|��ѯ.�̻���|��ѯ.�豸�ն����к�|��ѯ.ʡ�豸�ն���' +
          '�к�|��ѯ.�豸����|��ѯ.״̬|��ѯ.ע������|��ѯ.��������|��ѯ.ͣ' +
          '������|'
      end
      item
        MonitorValueChangedFields = 
          '|�̻���|�̻�����|�豸�ն����к�|�|�豸����|״̬|ע������|������' +
          '��|ͣ������|���豸���|��ע|'
      end>
    Left = 56
    Top = 264
  end
  inherited QueryRequest: TWVRequest
    ID = '�̻��豸�����ѯ'
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
        ParamName = '�̻���'
        FieldName = '��ѯ.�̻���'
        DefaultValue = 0
      end
      item
        ParamName = '�豸�ն����к�'
        FieldName = '��ѯ.�豸�ն����к�'
      end
      item
        ParamName = 'ʡ�豸�ն����к�'
        FieldName = '��ѯ.ʡ�豸�ն����к�'
      end
      item
        ParamName = '�豸����'
        FieldName = '��ѯ.�豸����'
      end
      item
        ParamName = '״̬'
        FieldName = '��ѯ.״̬'
      end
      item
        ParamName = 'ע������'
        FieldName = '��ѯ.ע������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = 'ͣ������'
        FieldName = '��ѯ.ͣ������'
      end>
    Left = 192
    Top = 264
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sstock_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '221'
      end
      item
        FieldName = 'scurrency_type'
        DataPresentType = 'idobjects'
        DataPresentParam = '239'
      end>
    Left = 84
    Top = 295
  end
  inherited AddRequest: TWVRequest
    ID = '�̻��豸����'
    Bindings = <
      item
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '�豸�ն����к�'
        FieldName = '�豸�ն����к�'
      end
      item
        ParamName = 'ʡ�豸�ն����к�'
        FieldName = 'ʡ�豸�ն����к�'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '״̬'
        FieldName = '״̬'
      end
      item
        ParamName = 'ע������'
        FieldName = 'ע������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'ͣ������'
        FieldName = 'ͣ������'
      end
      item
        ParamName = '���豸���'
        FieldName = '���豸���'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end
      item
        ParamName = '������ʱ��'
        FieldName = '������ʱ��'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 88
    Top = 264
  end
  inherited DeleteRequest: TWVRequest
    ID = '�̻��豸����'
    Bindings = <
      item
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '�豸�ն����к�'
        FieldName = '�豸�ն����к�'
      end
      item
        ParamName = 'ʡ�豸�ն����к�'
        FieldName = 'ʡ�豸�ն����к�'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '״̬'
        FieldName = '״̬'
      end
      item
        ParamName = 'ע������'
        FieldName = 'ע������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'ͣ������'
        FieldName = 'ͣ������'
      end
      item
        ParamName = '���豸���'
        FieldName = '���豸���'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 120
    Top = 264
  end
  inherited ChangeRequest: TWVRequest
    ID = '�̻��豸����'
    Bindings = <
      item
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '�豸�ն����к�'
        FieldName = '�豸�ն����к�'
      end
      item
        ParamName = 'ʡ�豸�ն����к�'
        FieldName = 'ʡ�豸�ն����к�'
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '״̬'
        FieldName = '״̬'
      end
      item
        ParamName = 'ע������'
        FieldName = 'ע������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'ͣ������'
        FieldName = 'ͣ������'
      end
      item
        ParamName = '���豸���'
        FieldName = '���豸���'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end
      item
        ParamName = '������ʱ��'
        FieldName = '������ʱ��'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    Left = 152
    Top = 264
  end
  inherited WVDataSource: TWVDataSource
    Left = 156
    Top = 303
  end
  inherited alDatasetActions: TActionList
    Left = 196
    Top = 300
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
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
        DefaultValue = 0
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
    AfterExec = CheckReturnData
    Left = 400
    Top = 8
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
        Name = '�������.����'
        Caption = '�������.����'
        FieldType = wftUndefined
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
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.������־|��ѯ.�̻����|��ѯ.�����̻���|��ѯ.ʡ�̻����|��' +
          'ѯ.�̻���|��ѯ.�̻�Ӣ������|��ѯ.�̻����|��ѯ.�̻�����|��ѯ.��' +
          'ҵ����|��ѯ.��ϵ��|��ѯ.�绰|��ѯ.�ֻ�|��ѯ.��������|��ѯ.����|' +
          '��ѯ.Ӫҵ��ַ|��ѯ.��������|��ѯ.�������|��ѯ.��������|��ѯ.��' +
          '���˺�|��ѯ.�����ʻ���|��ѯ.���к�|��ѯ.��������|��ѯ.��������|' +
          '��ѯ.����״̬|��ѯ.�̻�״̬|'
      end
      item
        MonitorValueChangedFields = 
          '|�̻����|�����̻���|ʡ�̻����|�̻���|�̻�Ӣ������|�̻����|��' +
          '������|��ҵ����|��ϵ��|�绰|�ֻ�|��������|����|Ӫҵ��ַ|��������' +
          '|�������|��������|�����˺�|�����ʻ���|���к�|��������|��������|' +
          '����״̬|'
      end>
    Left = 368
    Top = 8
  end
  object WVDBBinder1: TWVDBBinder
    DataSource = DataSource1
    WorkView = WorkView1
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
        FieldName = 'sstatus1'
        WVFieldName = '�̻�״̬'
        DataPresentType = 'idobjects'
        DataPresentParam = '224'
      end>
    HideUnbindingFields = False
    Left = 436
    Top = 7
  end
  object DataSource1: TDataSource
    OnStateChange = DataSourceStateChange
    OnDataChange = DataSourceDataChange
    Left = 468
    Top = 7
  end
end
