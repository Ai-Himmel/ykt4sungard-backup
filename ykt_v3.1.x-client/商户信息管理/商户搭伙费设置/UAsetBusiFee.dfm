inherited faqhsetBusiFee: TfaqhsetBusiFee
  Width = 775
  Height = 512
  Caption = '������������'
  inherited pcPages: TRzPageControl
    Width = 775
    Height = 512
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 459
        Width = 771
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 509
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 597
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 424
        end
        inherited btnDelete: TBitBtn
          Left = 682
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 182
          Visible = False
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 8
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 771
      end
      inherited Grid: TRzDBGrid
        Top = 49
        Width = 771
        Height = 410
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'Lvol3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻���'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻�����'
            Width = 150
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
            FieldName = 'drate0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻�����(%)'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'drate1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ѧУ����(%)'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����Ա'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_limit2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����޸�ʱ��'
            Width = 120
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 771
        Height = 31
        Align = alTop
        ParentColor = True
        TabOrder = 1
        object Label2: TLabel
          Left = 26
          Top = 10
          Width = 48
          Height = 12
          Caption = '�̻����'
        end
        object Label4: TLabel
          Left = 234
          Top = 10
          Width = 48
          Height = 12
          Caption = '�շ����'
        end
        object edtQBid: TWVEdit
          Left = 80
          Top = 7
          Width = 115
          Height = 20
          BiDiMode = bdRightToLeft
          Color = clWhite
          MaxLength = 9
          ParentBiDiMode = False
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.���>'
          WorkView = WorkView
          FieldName = '��ѯ.���'
          SynchronizeWhenExit = True
        end
        object WVComboBox1: TWVComboBox
          Left = 292
          Top = 6
          Width = 150
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ImeName = '�Ϲ�ƴ�����뷨'
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '��ѯ.�շ����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-43'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object Label7: TLabel [0]
        Left = 42
        Top = 84
        Width = 54
        Height = 12
        Caption = '�̻����*'
      end
      object Label8: TLabel [1]
        Left = 42
        Top = 148
        Width = 54
        Height = 12
        Caption = '�շ����*'
      end
      object Label9: TLabel [2]
        Left = 42
        Top = 180
        Width = 54
        Height = 12
        Caption = '�̻�����*'
      end
      object Label1: TLabel [3]
        Left = 48
        Top = 116
        Width = 48
        Height = 12
        Caption = '�̻�����'
      end
      object btnSelect: TSpeedButton [4]
        Left = 226
        Top = 78
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
      object lbl1: TLabel [5]
        Left = 40
        Top = 56
        Width = 222
        Height = 12
        Caption = '˵��������̻����Ϊ0��Ϊͨ�÷�������'
      end
      object Label3: TLabel [6]
        Left = 242
        Top = 180
        Width = 15
        Height = 12
        AutoSize = False
        Caption = '%'
      end
      object Label5: TLabel [7]
        Left = 42
        Top = 212
        Width = 54
        Height = 12
        Caption = 'ѧУ����*'
      end
      object Label6: TLabel [8]
        Left = 242
        Top = 212
        Width = 15
        Height = 12
        AutoSize = False
        Caption = '%'
      end
      inherited UIPanel2: TUIPanel
        Top = 453
        Width = 771
        TabOrder = 5
        inherited btnOK: TBitBtn
          Left = 595
        end
        inherited btnCancel: TBitBtn
          Left = 683
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtBusiRate: TWVDigitalEdit
        Left = 100
        Top = 176
        Width = 133
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 4
        ParentColor = False
        TabOrder = 4
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = '����'
        SynchronizeByValue = True
      end
      object edtBusiName: TWVEdit
        Left = 100
        Top = 112
        Width = 149
        Height = 20
        ParentColor = True
        ReadOnly = True
        TabOrder = 2
        Text = '<�̻�����>'
        WorkView = WorkView
        FieldName = '�̻�����'
        SynchronizeWhenExit = True
      end
      object pnl1: TPanel
        Left = 256
        Top = 80
        Width = 489
        Height = 369
        Color = 16119543
        TabOrder = 1
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
          OnDrawColumnCell = RzDBGrid1DrawColumnCell
          OnDblClick = RzDBGrid1DblClick
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
      object edtBusiId: TWVEdit
        Left = 100
        Top = 80
        Width = 127
        Height = 20
        MaxLength = 22
        ParentColor = True
        ReadOnly = True
        TabOrder = 0
        Text = '<�̻���>'
        WorkView = WorkView
        FieldName = '�̻���'
        SynchronizeWhenExit = True
      end
      object cbbFeeType: TWVComboBox
        Left = 100
        Top = 143
        Width = 150
        Height = 20
        Style = csDropDownList
        Color = clWhite
        ImeName = '�Ϲ�ƴ�����뷨'
        ItemHeight = 12
        TabOrder = 3
        WorkView = WorkView
        FieldName = '�շ����'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*-43'
      end
      object edtSRate: TWVDigitalEdit
        Left = 100
        Top = 208
        Width = 133
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 4
        ParentColor = False
        TabOrder = 6
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = 'ѧУ����'
        SynchronizeByValue = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 324
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
        Name = '��ѯ.���'
        Caption = '��ѯ.���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.Min = -1
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
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
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
      end
      item
        Name = '�̻�����'
        Caption = '�̻�����'
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
      end
      item
        Name = '�̻���'
        Caption = '�̻���'
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
        DataField = 'lvol3'
      end
      item
        Name = '�շ����'
        Caption = '�շ����'
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
        DataField = 'lvol5'
      end
      item
        Name = '����'
        Caption = '����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 2
        Checker.Max = 100
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'drate0'
      end
      item
        Name = 'ѧУ����'
        Caption = 'ѧУ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GroupIndex = 1
        DataField = 'drate1'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.Ӫҵ��|��ѯ.�ۿ۱���|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|��־|���|Ӫҵ��|�ۿ۱���|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 232
    Top = 248
  end
  inherited QueryRequest: TWVRequest
    ID = '�̻����Ѳ�ѯ'
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
        FieldName = '��ѯ.���'
      end
      item
        ParamName = '�շ����'
        FieldName = '��ѯ.�շ����'
      end>
    Left = 408
    Top = 248
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '-43'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end>
    Left = 284
  end
  inherited AddRequest: TWVRequest
    ID = '�̻���������'
    Bindings = <
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'ѧУ����'
        FieldName = 'ѧУ����'
      end>
    Left = 280
    Top = 248
  end
  inherited DeleteRequest: TWVRequest
    ID = '�̻���������'
    Bindings = <
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'ѧУ����'
        FieldName = 'ѧУ����'
      end>
    Left = 328
    Top = 248
  end
  inherited ChangeRequest: TWVRequest
    ID = '�̻���������'
    Bindings = <
      item
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = 'ѧУ����'
        FieldName = 'ѧУ����'
      end>
    Left = 368
    Top = 248
  end
  inherited WVDataSource: TWVDataSource
    Left = 404
  end
  inherited alDatasetActions: TActionList
    Left = 364
    Top = 284
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
    Left = 544
    Top = 360
  end
  object DataSource1: TDataSource
    OnDataChange = DataSourceDataChange
    Left = 576
    Top = 360
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
    Left = 512
    Top = 360
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
    Left = 476
    Top = 359
  end
end
