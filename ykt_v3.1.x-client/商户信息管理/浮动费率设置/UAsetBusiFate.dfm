inherited faqhsetBusiFate: TfaqhsetBusiFate
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
          Left = 597
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 293
          Enabled = False
          TabOrder = 0
          Visible = False
        end
        inherited btnQuery: TBitBtn [2]
          Left = 512
          TabOrder = 2
        end
        inherited btnDelete: TBitBtn
          Left = 682
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 382
          TabOrder = 1
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
            FieldName = 'lserial0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻�����'
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Caption = 'Ӫҵ��'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ۿ۱���(%)'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ע'
            Width = 350
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
        object Label3: TLabel
          Left = 206
          Top = 10
          Width = 36
          Height = 12
          Caption = 'Ӫҵ��'
        end
        object Label4: TLabel
          Left = 386
          Top = 10
          Width = 66
          Height = 12
          Caption = '�ۿ۱���(%)'
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
          TabOrder = 2
          Text = '<��ѯ.���>'
          WorkView = WorkView
          FieldName = '��ѯ.���'
          SynchronizeWhenExit = True
        end
        object edtMoney: TWVEdit
          Left = 248
          Top = 6
          Width = 115
          Height = 20
          BiDiMode = bdRightToLeft
          Color = clWhite
          MaxLength = 9
          ParentBiDiMode = False
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.Ӫҵ��>'
          WorkView = WorkView
          FieldName = '��ѯ.Ӫҵ��'
          SynchronizeWhenExit = True
        end
        object WVDigitalEdit1: TWVDigitalEdit
          Left = 460
          Top = 6
          Width = 107
          Height = 20
          AllowPoint = True
          UserSeprator = True
          Precision = 2
          MaxIntLen = 10
          ParentColor = False
          TabOrder = 1
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '��ѯ.�ۿ۱���'
          SynchronizeByValue = True
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object lblMemo: TLabel [0]
        Left = 66
        Top = 212
        Width = 24
        Height = 12
        Caption = '��ע'
      end
      object Label7: TLabel [1]
        Left = 42
        Top = 84
        Width = 48
        Height = 12
        Caption = '�̻����'
      end
      object Label8: TLabel [2]
        Left = 54
        Top = 148
        Width = 36
        Height = 12
        Caption = 'Ӫҵ��'
      end
      object Label9: TLabel [3]
        Left = 42
        Top = 180
        Width = 48
        Height = 12
        Caption = '�ۿ۱���'
      end
      object Label1: TLabel [4]
        Left = 42
        Top = 116
        Width = 48
        Height = 12
        Caption = '�̻�����'
      end
      object btnSelect: TSpeedButton [5]
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
      object lbl1: TLabel [6]
        Left = 40
        Top = 56
        Width = 222
        Height = 12
        Caption = '˵��������̻����Ϊ0��Ϊͨ�÷�������'
      end
      object Label10: TLabel [7]
        Left = 250
        Top = 180
        Width = 6
        Height = 12
        Caption = '%'
      end
      inherited UIPanel2: TUIPanel
        Top = 453
        Width = 771
        TabOrder = 6
        inherited btnOK: TBitBtn
          Left = 595
          TabOrder = 1
        end
        inherited btnCancel: TBitBtn
          Left = 683
          TabOrder = 2
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
          TabOrder = 0
        end
      end
      object edtMemo: TWVEdit
        Left = 99
        Top = 208
        Width = 390
        Height = 20
        ParentColor = True
        ReadOnly = True
        TabOrder = 5
        Text = '<��ע>'
        WorkView = WorkView
        FieldName = '��ע'
        SynchronizeWhenExit = True
      end
      object WVDigitalEdit8: TWVDigitalEdit
        Left = 100
        Top = 144
        Width = 149
        Height = 20
        AllowPoint = True
        UserSeprator = True
        Precision = 0
        MaxIntLen = 10
        ParentColor = False
        TabOrder = 3
        TabStop = True
        Text = '0'
        WorkView = WorkView
        FieldName = 'Ӫҵ��'
        SynchronizeByValue = True
      end
      object edtBusiRate: TWVDigitalEdit
        Left = 100
        Top = 176
        Width = 149
        Height = 20
        AllowPoint = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        Color = clBtnHighlight
        ParentColor = False
        TabOrder = 4
        TabStop = True
        Text = '0'
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
        Text = '<���>'
        WorkView = WorkView
        FieldName = '���'
        SynchronizeWhenExit = True
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
        Name = '��ѯ.Ӫҵ��'
        Caption = '��ѯ.Ӫҵ��'
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
        Name = '��ѯ.�ۿ۱���'
        Caption = '��ѯ.�ۿ۱���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 9
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
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
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'Sstatus0'
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
        DataField = 'lserial0'
      end
      item
        Name = 'Ӫҵ��'
        Caption = 'Ӫҵ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '�ۿ۱���'
        Caption = '�ۿ۱���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'damt1'
      end
      item
        Name = '��ע'
        Caption = '��ע'
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
        DataField = 'ssectypes'
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
    ID = '�������ʲ�ѯ'
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
        ParamName = '���'
        FieldName = '��ѯ.���'
      end
      item
        ParamName = 'Ӫҵ��'
        FieldName = '��ѯ.Ӫҵ��'
      end
      item
        ParamName = '�ۿ۱���'
        FieldName = '��ѯ.�ۿ۱���'
      end>
    Left = 408
    Top = 248
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 284
  end
  inherited AddRequest: TWVRequest
    ID = '������������'
    Bindings = <
      item
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = 'Ӫҵ��'
        FieldName = 'Ӫҵ��'
      end
      item
        ParamName = '�ۿ۱���'
        FieldName = '�ۿ۱���'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end>
    Left = 280
    Top = 248
  end
  inherited DeleteRequest: TWVRequest
    ID = '������������'
    Bindings = <
      item
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = 'Ӫҵ��'
        FieldName = 'Ӫҵ��'
      end
      item
        ParamName = '�ۿ۱���'
        FieldName = '�ۿ۱���'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end>
    Left = 328
    Top = 248
  end
  inherited ChangeRequest: TWVRequest
    ID = '������������'
    Bindings = <
      item
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '���'
        FieldName = '���'
      end
      item
        ParamName = 'Ӫҵ��'
        FieldName = 'Ӫҵ��'
      end
      item
        ParamName = '�ۿ۱���'
        FieldName = '�ۿ۱���'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע.�޸�'
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
        ParamName = '��������'
        FieldName = 'Ӷ������'
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
        Name = 'Ӷ������'
        Caption = 'Ӷ������'
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
