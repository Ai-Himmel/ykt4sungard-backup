inherited BindingOperCard: TBindingOperCard
  Width = 857
  Height = 542
  Caption = '�Ž�������ԱȨ������'
  inherited pcPages: TRzPageControl
    Width = 857
    Height = 542
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 483
        Width = 853
        Height = 36
        TabOrder = 3
        object Label8: TLabel [0]
          Left = 16
          Top = 13
          Width = 60
          Height = 12
          Caption = '��˲���Ա'
        end
        object Label9: TLabel [1]
          Left = 192
          Top = 13
          Width = 48
          Height = 12
          Caption = '�������'
        end
        inherited btnAdd: TBitBtn [2]
          Left = 679
          Top = 6
          Enabled = False
          TabOrder = 1
        end
        inherited btnChange: TBitBtn [3]
          Left = 247
          Top = 1000
          Enabled = False
          TabOrder = 7
          Visible = False
        end
        inherited btnQuery: TBitBtn [4]
          Left = 594
          Top = 6
          TabOrder = 0
        end
        inherited btnDelete: TBitBtn
          Left = 764
          Top = 6
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 166
          Top = 1000
          TabOrder = 6
          Visible = False
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 8
          Top = 1000
          Width = 169
          Visible = False
        end
        object cbbDelOper: TWVComboBox
          Left = 80
          Top = 8
          Width = 97
          Height = 20
          Style = csDropDownList
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 3
          WorkView = WorkView
          FieldName = '��Ȩ����Ա'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-20'
        end
        object edtDelPwd: TWVEdit
          Left = 246
          Top = 8
          Width = 75
          Height = 20
          Color = clWhite
          MaxLength = 6
          PasswordChar = '*'
          ReadOnly = False
          TabOrder = 4
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 812
        Align = alNone
        TabOrder = 1
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 853
        Height = 450
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�󶨲���Ա'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�󶨿���'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ͻ���'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ͻ�����'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��״̬'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lsafe_level'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sdate2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����Ч��'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semp'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����Ա'
            Width = 80
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 853
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label2: TLabel
          Left = 18
          Top = 10
          Width = 48
          Height = 12
          Caption = '����Ա��'
        end
        object WVComboBox1: TWVComboBox
          Left = 69
          Top = 5
          Width = 156
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '��ѯ.����Ա��'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-30'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      inherited UIPanel2: TUIPanel
        Top = 483
        Width = 853
        TabOrder = 2
        object lbl1: TLabel [0]
          Left = 16
          Top = 13
          Width = 60
          Height = 12
          Caption = '��˲���Ա'
        end
        object lbl2: TLabel [1]
          Left = 192
          Top = 13
          Width = 48
          Height = 12
          Caption = '�������'
        end
        inherited btnOK: TBitBtn
          Left = 681
          TabOrder = 2
        end
        inherited btnCancel: TBitBtn
          Left = 769
          TabOrder = 3
        end
        inherited DBNavigator: TRzDBNavigator
          Left = 359
          Top = 1000
          Hints.Strings = ()
          TabOrder = 5
          Visible = False
        end
        object chkSelectAll: TRzCheckBox
          Left = 328
          Top = 11
          Width = 57
          Height = 17
          Caption = 'ȫѡ'
          FrameColor = 8409372
          HighlightColor = 2203937
          HotTrack = True
          HotTrackColor = 3983359
          HotTrackColorType = htctActual
          State = cbUnchecked
          TabOrder = 4
          OnClick = chkSelectAllClick
        end
        object cbbErrOperNo: TWVComboBox
          Left = 80
          Top = 8
          Width = 97
          Height = 20
          Style = csDropDownList
          Color = clWhite
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ItemHeight = 12
          ParentFont = False
          TabOrder = 0
          WorkView = WorkView
          FieldName = '��Ȩ����Ա'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-20'
        end
        object edtPwd: TWVEdit
          Left = 246
          Top = 8
          Width = 75
          Height = 20
          Color = clWhite
          MaxLength = 6
          PasswordChar = '*'
          ReadOnly = False
          TabOrder = 1
        end
      end
      object pnl1: TPanel
        Left = 179
        Top = 0
        Width = 674
        Height = 483
        Align = alClient
        BevelOuter = bvNone
        Caption = 'pnl1'
        TabOrder = 1
        object Panel2: TPanel
          Left = 0
          Top = 0
          Width = 674
          Height = 127
          Align = alTop
          BevelOuter = bvNone
          Color = 15458000
          TabOrder = 0
          object Label1: TLabel
            Left = 42
            Top = 9
            Width = 36
            Height = 12
            Caption = '�ͻ���'
          end
          object Label3: TLabel
            Left = 255
            Top = 9
            Width = 42
            Height = 12
            Caption = 'ѧ/����'
          end
          object Label4: TLabel
            Left = 249
            Top = 33
            Width = 48
            Height = 12
            Caption = '֤������'
          end
          object WVLabel5: TWVLabel
            Left = 470
            Top = 33
            Width = 48
            Height = 12
            Caption = '�ͻ����'
          end
          object WVLabel6: TWVLabel
            Left = 261
            Top = 80
            Width = 36
            Height = 12
            Caption = '��״̬'
          end
          object WVLabel2: TWVLabel
            Left = 30
            Top = 57
            Width = 48
            Height = 12
            Caption = '�շ����'
          end
          object Label7: TLabel
            Left = 470
            Top = 9
            Width = 48
            Height = 12
            Caption = '�ͻ�����'
          end
          object WVLabel9: TWVLabel
            Left = 30
            Top = 81
            Width = 48
            Height = 12
            Caption = '��ʾ����'
          end
          object WVLabel1: TWVLabel
            Left = 249
            Top = 57
            Width = 48
            Height = 12
            Caption = '��������'
          end
          object WVLabel8: TWVLabel
            Left = 470
            Top = 57
            Width = 48
            Height = 12
            Caption = '��������'
          end
          object Label6: TLabel
            Left = 42
            Top = 105
            Width = 36
            Height = 12
            Caption = '���κ�'
          end
          object Label5: TLabel
            Left = 249
            Top = 104
            Width = 48
            Height = 12
            Caption = '��������'
          end
          object WVLabel3: TWVLabel
            Left = 30
            Top = 33
            Width = 48
            Height = 12
            Caption = '֤������'
          end
          object edtCustNo: TWVEdit
            Left = 86
            Top = 5
            Width = 125
            Height = 20
            Color = clWhite
            MaxLength = 22
            ReadOnly = False
            TabOrder = 0
            Text = '<�ͻ���>'
            WorkView = wvQPubCard
            FieldName = '�ͻ���'
          end
          object WVEdit2: TWVEdit
            Left = 304
            Top = 5
            Width = 125
            Height = 20
            CharCase = ecUpperCase
            Color = clWhite
            ReadOnly = False
            TabOrder = 1
            Text = '<ѧ����>'
            WorkView = wvQPubCard
            FieldName = 'ѧ����'
          end
          object WVEdit3: TWVEdit
            Left = 304
            Top = 29
            Width = 125
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 4
            Text = '<֤������>'
            WorkView = wvQPubCard
            FieldName = '֤������'
          end
          object WVComboBox6: TWVComboBox
            Left = 526
            Top = 29
            Width = 125
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 5
            WorkView = wvQPubCard
            FieldName = '�ͻ����'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-34'
          end
          object WVComboBox2: TWVComboBox
            Left = 304
            Top = 76
            Width = 125
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 9
            WorkView = wvQPubCard
            FieldName = '��״̬'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*17'
          end
          object WVComboBox3: TWVComboBox
            Left = 86
            Top = 53
            Width = 125
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 6
            WorkView = wvQPubCard
            FieldName = '�շ����'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-43'
          end
          object WVEdit8: TWVEdit
            Left = 526
            Top = 5
            Width = 125
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 2
            Text = '<�ͻ�����>'
            WorkView = wvQPubCard
            FieldName = '�ͻ�����'
          end
          object WVComboBox4: TWVComboBox
            Left = 304
            Top = 53
            Width = 125
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 7
            WorkView = wvQPubCard
            FieldName = '��������'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-27'
          end
          object WVComboBox5: TWVComboBox
            Left = 526
            Top = 53
            Width = 125
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 8
            WorkView = wvQPubCard
            FieldName = '����'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-22'
          end
          object WVEdit6: TWVEdit
            Left = 86
            Top = 101
            Width = 125
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 13
            Text = '<�������κ�>'
            WorkView = wvQPubCard
            FieldName = '�������κ�'
          end
          object WVEdit5: TWVEdit
            Left = 304
            Top = 100
            Width = 125
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 12
            Text = '<ע������>'
            WorkView = wvQPubCard
            FieldName = 'ע������'
          end
          object WVEdit4: TWVEdit
            Left = 86
            Top = 77
            Width = 125
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 10
            Text = '<��ʾ����>'
            WorkView = wvQPubCard
            FieldName = '��ʾ����'
          end
          object WVComboBox7: TWVComboBox
            Left = 86
            Top = 29
            Width = 125
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 3
            WorkView = wvQPubCard
            FieldName = '֤������'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*87'
          end
          object btnCardQuery: TBitBtn
            Left = 570
            Top = 95
            Width = 81
            Height = 25
            Hint = '��ѯ/ˢ������'
            Caption = '��ѯ(&Q)'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
            Font.Style = []
            ParentFont = False
            TabOrder = 11
            OnClick = btnCardQueryClick
            Glyph.Data = {
              36040000424D3604000000000000360000002800000010000000100000000100
              2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
              FF00FFFFFF001818180018181800181818001818180018181800181818001818
              1800181818001818180018181800FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
              FF001818180084848400ADADAD00D6D6D600D6D6D600D6D6D600D6D6D600D6D6
              D600D6D6D600CECECE00181818001818180018181800FFFFFF00FFFFFF001818
              1800DEDEDE0018181800ADADAD00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
              DE00DEDEDE005A5A5A000029CE002994FF000029940018181800181818008484
              8400181818005A5A5A00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
              DE005A5A5A000029CE0094CEFF009494FF000029CE001818180018181800D6D6
              D600DEDEDE00DEDEDE00DEDEDE00DEDEDE00D6D6D600A59C9C00A59C9C005A5A
              5A000029CE0094CEFF009494FF000029CE0018181800FFFFFF0018181800DEDE
              DE00DEDEDE00DEDEDE00BDBDBD00636363001818180018181800181818001818
              180094CEFF009494FF000029CE0018181800FFFFFF00FFFFFF0018181800DEDE
              DE00DEDEDE00BDBDBD0063636300FFCE6300FFCE6300FFCE6300FFCE2900FF94
              63002963FF000029CE0018181800FFFFFF00FFFFFF00FFFFFF0018181800DEDE
              DE00BDBDBD0063636300A59C9C00EFC6A500FFFF9400FFFF9400FFCE6300FFCE
              2900FF9463001818180018181800FFFFFF00FFFFFF00FFFFFF0018181800DEDE
              DE00BDBDBD0063636300EFC6A500FFFFCE00FFFF9400FFFF9400FFFF9400FFCE
              6300FFCE29001818180018181800FFFFFF00FFFFFF00FFFFFF0018181800DEDE
              DE00BDBDBD0063636300EFC6A500FFFFCE00FFFF9400FFFF9400FFFF9400FFFF
              9400FFCE29001818180018181800FFFFFF00FFFFFF00FFFFFF0018181800DEDE
              DE00BDBDBD0063636300EFC6A500FFFFCE00FFFF9400FFFF9400FFFF9400FFFF
              9400FFCE29001818180018181800FFFFFF00FFFFFF00FFFFFF0018181800DEDE
              DE00D6D6D60063636300BDBDBD00EFC6A500FFFFCE00FFFF9400FFFF9400EFC6
              A500A59C9C001818180018181800FFFFFF00FFFFFF00FFFFFF0018181800DEDE
              DE00D6D6D600BDBDBD0063636300BDBDBD00EFC6A500EFC6A500EFC6A500A59C
              9C0018181800BDBDBD0018181800FFFFFF00FFFFFF00FFFFFF0018181800DEDE
              DE00D6D6D600D6D6D600BDBDBD00636363006363630063636300636363006363
              6300BDBDBD00DEDEDE0018181800FFFFFF00FFFFFF00FFFFFF0018181800DEDE
              DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00BDBDBD00BDBDBD00BDBDBD00BDBD
              BD00DEDEDE00DEDEDE0018181800FFFFFF00FFFFFF00FFFFFF00181818001818
              1800181818001818180018181800181818001818180018181800181818001818
              1800181818001818180018181800FFFFFF00FFFFFF00FFFFFF00}
          end
        end
        object lvQPubCard: TRzListView
          Left = 0
          Top = 127
          Width = 674
          Height = 356
          Align = alClient
          Checkboxes = True
          Columns = <
            item
              Caption = '��������'
              Width = 100
            end
            item
              Caption = '�ͻ���'
              Width = 60
            end
            item
              Caption = 'ѧ/����'
              Width = 100
            end
            item
              Caption = '����'
              Width = 80
            end
            item
              Caption = '����'
              Width = 60
            end
            item
              Caption = '�ͻ����'
              Width = 80
            end
            item
              Caption = '�շ����'
              Width = 70
            end
            item
              Caption = '����ȫ��'
              Width = 103
            end>
          ColumnClick = False
          FlatScrollBars = True
          GridLines = True
          RowSelect = True
          TabOrder = 1
          ViewStyle = vsReport
          OnCustomDrawItem = lvQPubCardCustomDrawItem
        end
      end
      object rzszpnl1: TRzSizePanel
        Left = 0
        Top = 0
        Width = 179
        Height = 483
        Color = 16119543
        HotSpotVisible = True
        SizeBarWidth = 7
        TabOrder = 0
        UseGradients = True
        object lst1: TRzCheckList
          Left = 0
          Top = 0
          Width = 171
          Height = 483
          Align = alClient
          ItemHeight = 17
          TabOrder = 0
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 132
    Top = 375
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
        Name = '��ѯ.����Ա��'
        Caption = '��ѯ.����Ա��'
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
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '����Ա��'
        Caption = '����Ա��'
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
        DataField = 'semp2'
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
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol0'
      end
      item
        Name = '��Ȩ����Ա'
        Caption = '��Ȩ����Ա'
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
        Name = '��Ȩ����'
        Caption = '��Ȩ����'
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
        MonitorValueChangedFields = 
          '|��ѯ.�Ž������|��ѯ.����Ա��|��ѯ.�Ž�������|��ѯ.����Ա��|��' +
          'ѯ.��������|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|�Ž������|�Ž�����|����Ա��|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Top = 344
  end
  inherited QueryRequest: TWVRequest
    ID = '��ֵ����Ա����Q'
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
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '����Ա��'
        FieldName = '��ѯ.����Ա��'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    Left = 200
    Top = 344
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'semp'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'sname'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'lsafe_level'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-56'
      end
      item
        FieldName = 'sserial0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '17'
      end>
    Left = 100
    Top = 375
  end
  inherited AddRequest: TWVRequest
    ID = '��ֵ����Ա����'
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
        ParamName = '����Ա��'
        FieldName = '����Ա��'
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
        ParamName = '��Ȩ����Ա'
        FieldName = '��Ȩ����Ա'
      end
      item
        ParamName = '��Ȩ����'
        FieldName = '��Ȩ����'
      end>
    Left = 104
    Top = 344
  end
  inherited DeleteRequest: TWVRequest
    ID = '��ֵ����Ա����'
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
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����Ա��'
        FieldName = '����Ա��'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '��Ȩ����Ա'
        FieldName = '��Ȩ����Ա'
      end
      item
        ParamName = '��Ȩ����'
        FieldName = '��Ȩ����'
      end>
    Left = 136
    Top = 344
  end
  inherited ChangeRequest: TWVRequest
    ID = '��ֵ����Ա����'
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
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����Ա��'
        FieldName = '����Ա��'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '��Ȩ����Ա'
        FieldName = '��Ȩ����Ա'
      end
      item
        ParamName = '��Ȩ����'
        FieldName = '��Ȩ����'
      end>
    Top = 344
  end
  inherited WVDataSource: TWVDataSource
    Left = 204
    Top = 375
  end
  inherited alDatasetActions: TActionList
    Left = 164
    Top = 380
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '����Ա��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end>
    Left = 128
    Top = 272
  end
  object WorkView1: TWorkView
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
      end
      item
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = '@Dataset'
      end
      item
        Name = '�������'
        Caption = '�������'
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
        MonitorValueChangedFields = '|��ʼ����|��������|����Ա����|'
      end>
    Left = 92
    Top = 271
  end
  object wvQPubCard: TWorkView
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
      end
      item
        Name = '��ѯ�����'
        Caption = '��ѯ�����'
        FieldType = wftUndefined
        DataType = kdtObject
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�ͻ���'
        Caption = '�ͻ���'
        FieldType = wftUndefined
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
        Name = 'ѧ����'
        Caption = 'ѧ����'
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
        Name = '�ͻ�����'
        Caption = '�ͻ�����'
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
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '֤������'
        Caption = '֤������'
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
        Name = '֤������'
        Caption = '֤������'
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
        Name = '�ͻ����'
        Caption = '�ͻ����'
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
        Name = '�շ����'
        Caption = '�շ����'
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
        Name = '��������'
        Caption = '��������'
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
        Name = '��ʾ����'
        Caption = '��ʾ����'
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
        Name = '�������κ�'
        Caption = '�������κ�'
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
        Name = 'ע������'
        Caption = 'ע������'
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
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
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
        Name = '��״̬'
        Caption = '��״̬'
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
        MonitorValueChangedFields = '|�ͻ���|ѧ����|����|����|���֤��|'
      end>
    Left = 92
    Top = 231
  end
  object wvrQPubCard: TWVRequest
    WorkView = wvQPubCard
    ID = '�ѿ����ͻ���Ϣ��ѯ'
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
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
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
        ParamName = '�������κ�'
        FieldName = '�������κ�'
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
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
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
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
        ParamName = 'ע������'
        FieldName = 'ע������'
      end
      item
        ParamName = '��ʾ����'
        FieldName = '��ʾ����'
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
        ParamName = '��״̬'
        FieldName = '��״̬'
      end>
    Left = 128
    Top = 232
  end
end
