inherited faqhsetGateOpenAlong: TfaqhsetGateOpenAlong
  Width = 816
  Height = 542
  Caption = '����ʱ�������'
  inherited pcPages: TRzPageControl
    Width = 816
    Height = 542
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 483
        Width = 812
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 638
          Top = 6
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 470
          Top = 6
          Enabled = False
          TabOrder = 1
          Visible = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 553
          Top = 6
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = 723
          Top = 6
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 254
          Top = 6
          Visible = False
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 8
          Top = 11
          Width = 177
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 812
        Align = alNone
        TabOrder = 1
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 812
        Height = 450
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Caption = '�Ž������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ʱ���ܱ��'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�Ž�����'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ʱ��������'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '״̬'
            Width = 60
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 812
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
          Visible = False
        end
        object WVComboBox1: TWVComboBox
          Left = 69
          Top = 5
          Width = 156
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ItemHeight = 0
          TabOrder = 0
          Text = '<>'
          Visible = False
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-30'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      inherited UIPanel2: TUIPanel
        Top = 483
        Width = 812
        TabOrder = 2
        inherited btnOK: TBitBtn
          Left = 640
        end
        inherited btnCancel: TBitBtn
          Left = 728
        end
        inherited DBNavigator: TRzDBNavigator
          Left = 791
          Hints.Strings = ()
          Visible = False
        end
        object chkSelectAll: TRzCheckBox
          Left = 184
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
          TabOrder = 3
          OnClick = chkSelectAllClick
        end
        object chkReSelect: TRzCheckBox
          Left = 264
          Top = 11
          Width = 57
          Height = 17
          Caption = '��ѡ'
          FrameColor = 8409372
          HighlightColor = 2203937
          HotTrack = True
          HotTrackColor = 3983359
          HotTrackColorType = htctActual
          State = cbUnchecked
          TabOrder = 4
          Visible = False
          OnClick = chkReSelectClick
        end
      end
      object pnl1: TPanel
        Left = 179
        Top = 0
        Width = 633
        Height = 483
        Align = alClient
        BevelOuter = bvNone
        Caption = 'pnl1'
        TabOrder = 1
        object Panel2: TPanel
          Left = 0
          Top = 0
          Width = 633
          Height = 121
          Align = alTop
          BevelOuter = bvNone
          Color = 16119543
          TabOrder = 0
          object Label10: TLabel
            Left = 2
            Top = 5
            Width = 112
            Height = 16
            Caption = '����ʱ�������'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = '����'
            Font.Style = []
            ParentFont = False
          end
          object Label1: TLabel
            Left = 2
            Top = 41
            Width = 48
            Height = 12
            Caption = '�豸����'
          end
          object Label6: TLabel
            Left = 2
            Top = 68
            Width = 48
            Height = 12
            Caption = '�豸����'
          end
          object Label11: TLabel
            Left = 464
            Top = 41
            Width = 60
            Height = 12
            Caption = '�豸����ID'
          end
          object Label12: TLabel
            Left = 441
            Top = 67
            Width = 84
            Height = 12
            Caption = '�ϼ��豸����ID'
          end
          object Label3: TLabel
            Left = 266
            Top = 11
            Width = 48
            Height = 12
            Caption = '�豸״̬'
            Visible = False
          end
          object Label4: TLabel
            Left = 14
            Top = 95
            Width = 36
            Height = 12
            Caption = '��ϵͳ'
          end
          object Label5: TLabel
            Left = 210
            Top = 69
            Width = 72
            Height = 12
            Caption = '�豸��������'
          end
          object Label7: TLabel
            Left = 210
            Top = 43
            Width = 72
            Height = 12
            Caption = '�豸�����ͺ�'
          end
          object WVEdit1: TWVEdit
            Left = 52
            Top = 37
            Width = 157
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 1
            Text = '<�豸����>'
            WorkView = WorkView2
            FieldName = '�豸����'
          end
          object cbbScode: TWVComboBox
            Left = 52
            Top = 64
            Width = 157
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 5
            WorkView = WorkView2
            FieldName = '���ʹ���'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*47'
          end
          object WVEdit3: TWVEdit
            Left = 526
            Top = 37
            Width = 100
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 2
            Text = '<�豸����ID>'
            WorkView = WorkView2
            FieldName = '�豸����ID'
          end
          object WVEdit6: TWVEdit
            Left = 526
            Top = 63
            Width = 100
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 4
            Text = '<�ϼ��豸����ID>'
            WorkView = WorkView2
            FieldName = '�ϼ��豸����ID'
          end
          object WVComboBox5: TWVComboBox
            Left = 284
            Top = 39
            Width = 153
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 3
            WorkView = WorkView2
            FieldName = '�豸�����ͺ�'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-35'
          end
          object WVComboBox2: TWVComboBox
            Left = 316
            Top = 7
            Width = 156
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 0
            Visible = False
            WorkView = WorkView2
            FieldName = '�豸״̬'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*5'
          end
          object WVComboBox3: TWVComboBox
            Left = 52
            Top = 91
            Width = 157
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 8
            WorkView = WorkView2
            FieldName = '������ϵͳ'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-32'
          end
          object WVComboBox4: TWVComboBox
            Left = 284
            Top = 65
            Width = 153
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 6
            WorkView = WorkView2
            FieldName = '�豸��������'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-28'
          end
          object btnEquQuery: TBitBtn
            Left = 551
            Top = 88
            Width = 75
            Height = 25
            Hint = 'ȷ�ϲ���'
            Caption = '�豸��ѯ'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
            Font.Style = []
            ParentFont = False
            TabOrder = 7
            OnClick = btnEquQueryClick
          end
        end
        object lvGate: TRzListView
          Left = 0
          Top = 121
          Width = 633
          Height = 362
          Align = alClient
          Checkboxes = True
          Columns = <
            item
              Caption = '�Ž������'
              Width = 80
            end
            item
              Caption = '�Ž�������'
              Width = 150
            end
            item
              Caption = '�豸������'
              Width = 90
            end
            item
              Caption = '������ϵͳ'
              Width = 90
            end
            item
              Caption = '��������'
              Width = 202
            end>
          ColumnClick = False
          GridLines = True
          MultiSelect = True
          ReadOnly = True
          RowSelect = True
          SortType = stBoth
          TabOrder = 1
          ViewStyle = vsReport
          OnCustomDrawItem = lvGateCustomDrawItem
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
        Name = '��ѯ.ʱ���ܱ��'
        Caption = '��ѯ.ʱ���ܱ��'
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
        Name = '��ѯ.�Ž������'
        Caption = '��ѯ.�Ž������'
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
        Name = '�Ž������'
        Caption = '�Ž������'
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
      end
      item
        Name = 'ʱ���ܱ��'
        Caption = 'ʱ���ܱ��'
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
    ID = '����ʱ��β�ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ʱ���ܱ��'
        FieldName = '��ѯ.ʱ���ܱ��'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�Ž������'
        FieldName = '��ѯ.�Ž������'
      end>
    Left = 200
    Top = 344
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '84'
      end>
    Left = 100
    Top = 375
  end
  inherited AddRequest: TWVRequest
    ID = '����ʱ�������'
    Bindings = <
      item
        ParamName = '�Ž������'
        FieldName = '�Ž������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'ʱ���ܱ��'
        FieldName = 'ʱ���ܱ��'
      end>
    Left = 104
    Top = 344
  end
  inherited DeleteRequest: TWVRequest
    ID = '����ʱ�������'
    Bindings = <
      item
        ParamName = '�Ž������'
        FieldName = '�Ž������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'ʱ���ܱ��'
        FieldName = 'ʱ���ܱ��'
      end>
    Left = 136
    Top = 344
  end
  inherited ChangeRequest: TWVRequest
    ID = '����ʱ�������'
    Bindings = <
      item
        ParamName = '�Ž������'
        FieldName = '�Ž������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = 'ʱ���ܱ��'
        FieldName = 'ʱ���ܱ��'
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
  object MainRequest2: TWVRequest
    WorkView = WorkView2
    ID = '�豸�ǹؼ��ֲ�ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�豸����'
        FieldName = '�豸����'
      end
      item
        ParamName = '�����豸ע���'
        FieldName = '�����豸ע���'
      end
      item
        ParamName = '�豸����ID'
        FieldName = '�豸����ID'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '���ʹ���'
        FieldName = '���ʹ���'
      end
      item
        ParamName = '�ϼ��豸����ID'
        FieldName = '�ϼ��豸����ID'
      end
      item
        ParamName = '�豸״̬'
        FieldName = '�豸״̬'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = '�豸�����ͺ�'
      end
      item
        ParamName = '������ϵͳ'
        FieldName = '������ϵͳ'
      end
      item
        ParamName = '�豸��������'
        FieldName = '�豸��������'
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
    Left = 128
    Top = 224
  end
  object WorkView2: TWorkView
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
        Name = '�豸����'
        Caption = '�豸����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scert_no'
      end
      item
        Name = '�����豸ע���'
        Caption = '�����豸ע���'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_pwd'
      end
      item
        Name = '�豸����ID'
        Caption = '�豸����ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'sbank_pwd2'
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
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '���ʹ���'
        Caption = '���ʹ���'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'sbank_code'
      end
      item
        Name = '�ϼ��豸����ID'
        Caption = '�ϼ��豸����ID'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = True
        GroupIndex = 1
        DataField = 'sdate1'
      end
      item
        Name = '�豸״̬'
        Caption = '�豸״̬'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol4'
      end
      item
        Name = '�豸�����ͺ�'
        Caption = '�豸�����ͺ�'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lbank_acc_type'
      end
      item
        Name = '������ϵͳ'
        Caption = '������ϵͳ'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial0'
      end
      item
        Name = '�豸��������'
        Caption = '�豸��������'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lserial1'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|�豸����|�����豸ע���|�豸���|����|���ʹ���|�ϼ��豸���|�豸' +
          '״̬|�豸�����ͺ�|������ϵͳ|�豸��������|������Ա����|'
      end>
    Left = 92
    Top = 223
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
        DataField = '@Return'
      end
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
        Name = '��ѯ.ʱ�������'
        Caption = '��ѯ.ʱ�������'
        FieldType = wftUndefined
        DataType = kdtInteger
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
        Name = '��ѯ.ʱ���������'
        Caption = '��ѯ.ʱ���������'
        FieldType = wftUndefined
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
        Name = '��ѯ.��һ����'
        Caption = '��ѯ.��һ����'
        FieldType = wftUndefined
        DataType = kdtInteger
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
        Name = '��ѯ.�ܶ�����'
        Caption = '��ѯ.�ܶ�����'
        FieldType = wftUndefined
        DataType = kdtInteger
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
        FieldType = wftUndefined
        DataType = kdtInteger
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
        FieldType = wftUndefined
        DataType = kdtInteger
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
        FieldType = wftUndefined
        DataType = kdtInteger
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
        FieldType = wftUndefined
        DataType = kdtInteger
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
        FieldType = wftUndefined
        DataType = kdtInteger
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
        Name = 'ʱ�������'
        Caption = 'ʱ�������'
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
        DataField = 'lvol0'
      end
      item
        Name = 'ʱ�������'
        Caption = 'ʱ�������'
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
        DataField = 'semail'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        Name = '��һ����'
        Caption = '��һ����'
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
        DataField = 'lvol1'
      end
      item
        Name = '�ܶ�����'
        Caption = '�ܶ�����'
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
        DataField = 'lvol2'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        DataField = 'lvol3'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        DataField = 'lvol4'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        Name = '��������'
        Caption = '��������'
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
        DataField = 'lvol6'
      end
      item
        Name = '��������'
        Caption = '��������'
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
        DataField = 'lvol7'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.ʱ�������|��ѯ.ʱ���������|��ѯ.��һ����|��ѯ.�ܶ���' +
          '���|��ѯ.��������|��ѯ.��������|��ѯ.��������|��ѯ.������' +
          '���|��ѯ.��������|��ѯ.��־|'
      end
      item
        MonitorValueChangedFields = 
          '|ʱ�������|ʱ�������|��־|��һ����|�ܶ�����|��������|' +
          '��������|��������|��������|��������|'
      end>
    Left = 88
    Top = 256
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '��ʱ��β�ѯ'
    Bindings = <
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ʱ�������'
        FieldName = '��ѯ.ʱ�������'
      end
      item
        ParamName = 'ʱ���������'
        FieldName = '��ѯ.ʱ���������'
      end
      item
        ParamName = '��һ����'
        FieldName = '��ѯ.��һ����'
      end
      item
        ParamName = '�ܶ�����'
        FieldName = '��ѯ.�ܶ�����'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end>
    AfterExec = CheckReturnData
    Left = 128
    Top = 256
  end
end
