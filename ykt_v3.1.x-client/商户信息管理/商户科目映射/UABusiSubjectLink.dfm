inherited faqhBusiSubjectLink: TfaqhBusiSubjectLink
  Width = 805
  Height = 541
  Caption = '�̻���Ŀӳ��'
  inherited pcPages: TRzPageControl
    Width = 805
    Height = 541
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 488
        Width = 801
        inherited btnAdd: TBitBtn [0]
          Left = 539
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 627
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 446
        end
        inherited btnDelete: TBitBtn
          Left = 712
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 88
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 801
      end
      inherited Grid: TRzDBGrid
        Width = 801
        Height = 470
        Columns = <
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
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ӧ��Ŀ��'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ӧ��Ŀ����'
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbankname'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_acc'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�����˺�'
            Width = 120
            Visible = True
          end>
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label6: TLabel [0]
        Left = 86
        Top = 68
        Width = 36
        Height = 12
        Caption = '�̻���'
      end
      object Label7: TLabel [1]
        Left = 74
        Top = 110
        Width = 48
        Height = 12
        Caption = '�̻�����'
      end
      object Label8: TLabel [2]
        Left = 74
        Top = 151
        Width = 48
        Height = 12
        Caption = '��Ӧ��Ŀ'
      end
      object Label10: TLabel [3]
        Left = 74
        Top = 194
        Width = 48
        Height = 12
        Caption = '��������'
      end
      object Label1: TLabel [4]
        Left = 74
        Top = 236
        Width = 48
        Height = 12
        Caption = '�����˺�'
      end
      object btnSelect: TSpeedButton [5]
        Left = 282
        Top = 62
        Width = 23
        Height = 22
        Caption = '>>>'
        Flat = True
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        OnClick = btnSelectClick
      end
      inherited UIPanel2: TUIPanel
        Top = 482
        Width = 801
        TabOrder = 6
        inherited btnOK: TBitBtn
          Left = 625
        end
        inherited btnCancel: TBitBtn
          Left = 713
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtBusiId: TWVDigitalEdit
        Left = 132
        Top = 64
        Width = 149
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        BiDiMode = bdRightToLeft
        Color = clInfoBk
        ParentBiDiMode = False
        ParentColor = False
        TabOrder = 1
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '�̻���'
        SynchronizeByValue = True
      end
      object edtBusiName: TWVEdit
        Left = 132
        Top = 105
        Width = 173
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 2
        Text = '<�̻�����>'
        WorkView = WorkView
        FieldName = '�̻�����'
        SynchronizeWhenExit = True
      end
      object WVEdit10: TWVEdit
        Left = 132
        Top = 189
        Width = 173
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 4
        Text = '<��������>'
        WorkView = WorkView
        FieldName = '��������'
        SynchronizeWhenExit = True
      end
      object WVEdit1: TWVEdit
        Left = 132
        Top = 230
        Width = 173
        Height = 20
        Color = clWhite
        ReadOnly = False
        TabOrder = 5
        Text = '<�����˺�>'
        WorkView = WorkView
        FieldName = '�����˺�'
        SynchronizeWhenExit = True
      end
      object pnl1: TPanel
        Left = 305
        Top = 62
        Width = 489
        Height = 369
        Color = 16119543
        TabOrder = 0
        object pnl2: TPanel
          Left = 1
          Top = 1
          Width = 487
          Height = 9
          Align = alTop
          Color = 16119543
          TabOrder = 0
        end
        object pnl3: TPanel
          Left = 1
          Top = 327
          Width = 487
          Height = 41
          Align = alBottom
          Color = 16119543
          TabOrder = 2
          object btnQry: TBitBtn
            Left = 228
            Top = 8
            Width = 75
            Height = 25
            Hint = 'ȷ�ϲ���'
            Anchors = [akTop, akRight]
            Caption = '&Q ��ѯ'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            OnClick = btnQryClick
          end
          object btnSel: TBitBtn
            Left = 316
            Top = 8
            Width = 75
            Height = 25
            Hint = 'ȷ�ϲ���'
            Anchors = [akTop, akRight]
            Caption = '&S ѡ��'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
            Font.Style = []
            ParentFont = False
            TabOrder = 2
            OnClick = btnSelClick
          end
          object btnCommon: TBitBtn
            Left = 20
            Top = 8
            Width = 75
            Height = 25
            Hint = 'ȷ�ϲ���'
            Anchors = [akTop, akRight]
            Caption = 'ͨ���̻�'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = btnCommonClick
          end
          object btnCnl: TBitBtn
            Left = 404
            Top = 8
            Width = 75
            Height = 25
            Hint = 'ȷ�ϲ���'
            Anchors = [akTop, akRight]
            Caption = 'ȡ ��'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
            Font.Style = []
            ParentFont = False
            TabOrder = 3
            OnClick = btnCnlClick
          end
        end
        object RzDBGrid1: TRzDBGrid
          Left = 1
          Top = 10
          Width = 487
          Height = 317
          Align = alClient
          DataSource = DataSource1
          FixedColor = 15458000
          ImeName = 'ƴ���ӼӼ��ϰ�'
          TabOrder = 1
          TitleFont.Charset = GB2312_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -12
          TitleFont.Name = '����'
          TitleFont.Style = []
          OnKeyDown = GridKeyDown
          FrameColor = 12164479
          FrameStyle = fsGroove
          FrameVisible = True
          FixedLineColor = 12164479
          LineColor = clBackground
          Columns = <
            item
              Expanded = False
              FieldName = 'sbranch_code0'
              Title.Alignment = taCenter
              Title.Caption = 'У��'
              Width = 100
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'lvol3'
              Title.Alignment = taCenter
              Title.Caption = '�̻���'
              Width = 50
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'sall_name'
              Title.Alignment = taCenter
              Title.Caption = '�̻�����'
              Width = 110
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'lvol7'
              Title.Alignment = taCenter
              Title.Caption = '�̻����'
              Width = 50
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'smain_flag2'
              Title.Alignment = taCenter
              Title.Caption = 'ĩ���̻�'
              Visible = False
            end
            item
              Expanded = False
              FieldName = 'smain_flag'
              Title.Alignment = taCenter
              Title.Caption = '��������'
              Width = 60
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'scust_type'
              Title.Alignment = taCenter
              Title.Caption = '�մ���'
              Width = 60
              Visible = True
            end>
        end
      end
      object cbbSubJNo: TWVComboBox
        Left = 132
        Top = 145
        Width = 173
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ImeName = '�Ϲ�ƴ�����뷨'
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView
        FieldName = '��Ӧ��Ŀ��'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-71'
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 412
    Top = 319
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
        Name = '��־'
        Caption = '��־'
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
        Name = '��ѯ.�̻���'
        Caption = '��ѯ.�̻���'
        FieldType = wftUndefined
        Features.Strings = ()
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
        Name = '��ѯ.��Ӧ��Ŀ����'
        Caption = '��ѯ.��Ӧ��Ŀ����'
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
        Name = '��ѯ.�����˺�'
        Caption = '��ѯ.�����˺�'
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
        DataField = 'lvol3'
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
        Name = '��Ӧ��Ŀ��'
        Caption = '��Ӧ��Ŀ��'
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
        Name = '��Ӧ��Ŀ����'
        Caption = '��Ӧ��Ŀ����'
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
        DataField = 'sbankname'
      end
      item
        Name = '�����˺�'
        Caption = '�����˺�'
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
        GroupIndex = 1
        DataField = 'sbank_acc'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.��־|��ѯ.�̻���|��ѯ.��Ӧ��Ŀ����|��ѯ.��������|��ѯ.����' +
          '�˺�|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|�̻���|�̻�����|��Ӧ��Ŀ��|��Ӧ��Ŀ����|��������|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 344
    Top = 280
  end
  inherited QueryRequest: TWVRequest
    ID = '�̻���Ŀӳ���ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '�̻���'
        FieldName = '��ѯ.�̻���'
      end
      item
        ParamName = '��Ӧ��Ŀ����'
        FieldName = '��ѯ.��Ӧ��Ŀ����'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '�����˺�'
        FieldName = '��ѯ.�����˺�'
      end>
    Left = 472
    Top = 280
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 380
    Top = 319
  end
  inherited AddRequest: TWVRequest
    ID = '�̻���Ŀӳ��'
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
        ParamName = '��Ӧ��Ŀ��'
        FieldName = '��Ӧ��Ŀ��'
      end
      item
        ParamName = '��Ӧ��Ŀ����'
        FieldName = '��Ӧ��Ŀ����'
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
        ParamName = '��־'
        FieldName = '��־'
      end>
    Left = 376
    Top = 280
  end
  inherited DeleteRequest: TWVRequest
    ID = '�̻���Ŀӳ��'
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
        ParamName = '��Ӧ��Ŀ��'
        FieldName = '��Ӧ��Ŀ��'
      end
      item
        ParamName = '��Ӧ��Ŀ����'
        FieldName = '��Ӧ��Ŀ����'
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
        ParamName = '��־'
        FieldName = '��־'
      end>
    Left = 408
    Top = 280
  end
  inherited ChangeRequest: TWVRequest
    ID = '�̻���Ŀӳ��'
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
        ParamName = '��Ӧ��Ŀ��'
        FieldName = '��Ӧ��Ŀ��'
      end
      item
        ParamName = '��Ӧ��Ŀ����'
        FieldName = '��Ӧ��Ŀ����'
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
        ParamName = '��־'
        FieldName = '��־'
      end>
    Left = 440
    Top = 280
  end
  inherited WVDataSource: TWVDataSource
    Left = 476
    Top = 319
  end
  inherited alDatasetActions: TActionList
    Left = 444
    Top = 316
  end
  object WorkView1: TWorkView
    WorkFields = <
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
        Name = '�̻���ʶ'
        Caption = '�̻���ʶ'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol5'
      end
      item
        Name = '���̻���ʶ'
        Caption = '���̻���ʶ'
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
        Name = '�̻�����'
        Caption = '�̻�����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'scard1'
      end
      item
        Name = '�̻����'
        Caption = '�̻����'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'lvol7'
      end
      item
        Name = '�Ƿ�Ϊ��������'
        Caption = '�Ƿ�Ϊ��������'
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
        Name = '�Ƿ�ΪҶ�ڵ�'
        Caption = '�Ƿ�ΪҶ�ڵ�'
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
        Name = '�մ���'
        Caption = '�մ���'
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
          '|�̻���ʶ|�ͻ���|���̻���ʶ|�̻�����|�̻����|�Ƿ�ΪҶ�ڵ�|�̻�' +
          '״̬|������Ա����|����������|�������Ա�|�������������|��������' +
          '��֤��|��ϵ�绰|��ϵ��ַ|�Ƿ���ȡ�����|��ȡ���ѹ���ѱ���|�̻�' +
          '����Ѽ��㷽ʽ|�̻�˰�Ѽ��㷽ʽ|ע��ʱ��|��ע|'
      end>
    Left = 380
    Top = 359
  end
  object MainRequest: TWVRequest
    WorkView = WorkView1
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
        ParamName = '�̻����'
        FieldName = '�̻����'
      end
      item
        ParamName = '�Ƿ�Ϊ��������'
        FieldName = '�Ƿ�Ϊ��������'
      end
      item
        ParamName = '�Ƿ�ΪҶ�ڵ�'
        FieldName = '�Ƿ�ΪҶ�ڵ�'
      end
      item
        ParamName = '�մ���'
        FieldName = '�մ���'
      end>
    Left = 416
    Top = 360
  end
  object WVDBBinder: TWVDBBinder
    DataSource = DataSource1
    WorkView = WorkView1
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
        FieldName = 'smain_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'scust_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end>
    HideUnbindingFields = False
    Left = 456
    Top = 360
  end
  object DataSource1: TDataSource
    OnDataChange = DataSourceDataChange
    Left = 488
    Top = 360
  end
end
