inherited faqhSetGateMgrOpen: TfaqhSetGateMgrOpen
  Width = 871
  Height = 547
  inherited UIPnlQueryCount: TUIPanel [0]
    Width = 871
    inherited Image1: TImage
      Width = 871
    end
    inherited LabRecordCount: TLabel
      Font.Color = clBlack
      Visible = False
    end
  end
  inherited UIPanel1: TUIPanel [1]
    Top = 513
    Width = 871
    Height = 34
    object WVLabel1: TWVLabel [0]
      Left = 8
      Top = 12
      Width = 36
      Height = 12
      Caption = '����;'
    end
    object WVLabel2: TWVLabel [1]
      Left = 152
      Top = 12
      Width = 48
      Height = 12
      Caption = '�������'
    end
    inherited btnQuery: TBitBtn
      Left = 782
      Height = 26
      Caption = '�� ��'
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 781
      Top = 300
      TabOrder = 3
      Visible = False
    end
    object cbbUse: TWVComboBox
      Left = 48
      Top = 7
      Width = 89
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 2
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '85'
    end
    object cbbOperType: TWVComboBox
      Left = 208
      Top = 6
      Width = 89
      Height = 20
      Style = csDropDownList
      Color = clWhite
      ItemHeight = 12
      TabOrder = 1
      DataPresentType = 'IDOBJECTS'
      AutoDropDown = False
      ItemsDataEntry = '44'
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 871
    Height = 495
    inherited Grid: TRzDBGrid
      Left = 40
      Top = 240
      Width = 153
      Height = 137
      Align = alNone
      TabOrder = 2
      Columns = <
        item
          Expanded = False
          FieldName = 'lserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸��ʶ'
          Width = 68
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸����'
          Width = 87
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸����ID'
          Width = 71
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���ʹ���'
          Width = 72
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������˿�����'
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt6'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ϼ��豸'
          Width = 68
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scurrency_type'
          PickList.Strings = ()
          Title.Caption = '��Ƭ�ṹ'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������˿ں�'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�豸״̬'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sbank_code2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ͨѶ�˿ں�'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type'
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
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ϵͳ'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ssectypes'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ע'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'damt5'
          PickList.Strings = ()
          Title.Caption = '�豸��;'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt4'
          PickList.Strings = ()
          Title.Caption = '�Ƿ�֧�ֿ�Ŀ�շ�'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Caption = 'ͨѶ���'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������κ�'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������汾'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Caption = '��ע'
          Width = 120
          Visible = True
        end>
    end
    object spnl1: TRzSizePanel
      Left = 0
      Top = 0
      Width = 411
      Height = 495
      Color = 15458000
      HotSpotVisible = True
      SizeBarWidth = 7
      TabOrder = 0
      UseGradients = True
      object pnlDevInfo: TPanel
        Left = 0
        Top = 0
        Width = 403
        Height = 495
        Align = alClient
        BevelOuter = bvNone
        Color = 15458000
        TabOrder = 0
        object pnl1: TPanel
          Left = 0
          Top = 0
          Width = 403
          Height = 97
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object Label6: TLabel
            Left = 15
            Top = 9
            Width = 42
            Height = 12
            Caption = 'ѧ/����'
          end
          object Label7: TLabel
            Left = 9
            Top = 57
            Width = 48
            Height = 12
            Caption = '�ͻ�����'
          end
          object WVLabel5: TWVLabel
            Left = 192
            Top = 9
            Width = 48
            Height = 12
            Caption = '�ͻ����'
          end
          object WVLabel9: TWVLabel
            Left = 9
            Top = 32
            Width = 48
            Height = 12
            Caption = '��ʾ����'
          end
          object WVLabel8: TWVLabel
            Left = 192
            Top = 33
            Width = 48
            Height = 12
            Caption = '��������'
          end
          object WVEdit4: TWVEdit
            Left = 59
            Top = 5
            Width = 118
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 0
            Text = '<ѧ����>'
            WorkView = WorkView1
            FieldName = 'ѧ����'
          end
          object WVEdit8: TWVEdit
            Left = 59
            Top = 53
            Width = 118
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 4
            Text = '<�ͻ�����>'
            WorkView = WorkView1
            FieldName = '�ͻ�����'
          end
          object WVComboBox6: TWVComboBox
            Left = 243
            Top = 5
            Width = 143
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 1
            WorkView = WorkView1
            FieldName = '�ͻ����'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-34'
          end
          object WVEdit5: TWVEdit
            Left = 59
            Top = 29
            Width = 118
            Height = 20
            Color = clWhite
            ReadOnly = False
            TabOrder = 2
            Text = '<��ʾ����>'
            WorkView = WorkView1
            FieldName = '��ʾ����'
          end
          object WVComboBox5: TWVComboBox
            Left = 243
            Top = 29
            Width = 143
            Height = 20
            Style = csDropDownList
            Color = clWhite
            ItemHeight = 12
            TabOrder = 3
            WorkView = WorkView1
            FieldName = '����'
            DataPresentType = 'IDOBJECTS'
            AutoDropDown = False
            ItemsDataEntry = '*-22'
          end
          object btnCardQuery: TBitBtn
            Left = 306
            Top = 55
            Width = 79
            Height = 25
            Hint = '��ѯ/ˢ������'
            Anchors = [akTop, akRight]
            Caption = '����ѯ'
            Font.Charset = GB2312_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = '����'
            Font.Style = []
            ParentFont = False
            TabOrder = 5
            OnClick = btnCardQueryClick
          end
          object chkCustAll: TCheckBox
            Left = 8
            Top = 77
            Width = 97
            Height = 17
            Caption = 'ȫѡ'
            TabOrder = 6
            OnClick = chkCustAllClick
          end
        end
        object lvCard: TListView
          Left = 0
          Top = 97
          Width = 403
          Height = 398
          Align = alClient
          Checkboxes = True
          Columns = <
            item
              Caption = 'ѡ��'
              Width = 40
            end
            item
              Caption = '�ͻ���'
              Width = 60
            end
            item
              Caption = '����'
              Width = 60
            end
            item
              Caption = 'ѧ/����'
              Width = 80
            end
            item
              Caption = '�ͻ�����'
              Width = 100
            end
            item
              Caption = '�ͻ����'
              Width = 80
            end
            item
              Caption = '������'
              Width = 60
            end
            item
              Caption = '��״̬'
            end>
          ColumnClick = False
          FlatScrollBars = True
          GridLines = True
          TabOrder = 1
          ViewStyle = vsReport
        end
      end
    end
    object pnlCardInfo: TPanel
      Left = 411
      Top = 0
      Width = 460
      Height = 495
      Align = alClient
      BevelOuter = bvNone
      Color = 15458000
      TabOrder = 1
      object pnlCardQuery: TPanel
        Left = 0
        Top = 0
        Width = 460
        Height = 97
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object Label4: TLabel
          Left = 30
          Top = 10
          Width = 48
          Height = 12
          Caption = '�豸����'
        end
        object Label1: TLabel
          Left = 6
          Top = 34
          Width = 72
          Height = 12
          Caption = '�ϼ�������'
        end
        object Label2: TLabel
          Left = 229
          Top = 34
          Width = 72
          Height = 12
          Caption = '�豸������'
        end
        object Label5: TLabel
          Left = 241
          Top = 10
          Width = 60
          Height = 12
          Caption = '������ϵͳ'
        end
        object Label3: TLabel
          Left = 30
          Top = 58
          Width = 48
          Height = 12
          Caption = '�豸����'
        end
        object WVComboBox18: TWVComboBox
          Left = 84
          Top = 6
          Width = 133
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '�豸����'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*47'
        end
        object WVEdit1: TWVEdit
          Left = 84
          Top = 30
          Width = 133
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 2
          Text = '<�ϼ��豸>'
          WorkView = WorkView
          FieldName = '�ϼ��豸'
        end
        object WVComboBox17: TWVComboBox
          Left = 312
          Top = 6
          Width = 133
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 1
          WorkView = WorkView
          FieldName = '��ϵͳ'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-32'
        end
        object WVEdit2: TWVEdit
          Left = 312
          Top = 30
          Width = 133
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 3
          Text = '<�豸������>'
          WorkView = WorkView
          FieldName = '�豸������'
        end
        object WVEdit3: TWVEdit
          Left = 84
          Top = 54
          Width = 133
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 4
          Text = '<�豸����>'
          WorkView = WorkView
          FieldName = '�豸����'
        end
        object btnDevQuery: TBitBtn
          Left = 365
          Top = 55
          Width = 79
          Height = 25
          Hint = '��ѯ/ˢ������'
          Anchors = [akTop, akRight]
          Caption = '�豸��ѯ'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
          OnClick = btnDevQueryClick
        end
        object chkDevall: TCheckBox
          Left = 32
          Top = 77
          Width = 97
          Height = 17
          Caption = 'ȫѡ'
          TabOrder = 6
          OnClick = chkDevallClick
        end
      end
      object lvEqu: TListView
        Left = 0
        Top = 97
        Width = 460
        Height = 398
        Align = alClient
        Checkboxes = True
        Columns = <
          item
            Caption = 'ѡ��'
            Width = 40
          end
          item
            Caption = '�豸���'
            Width = 60
          end
          item
            Caption = '�豸������'
            Width = 120
          end
          item
            Caption = '�豸����'
            Width = 200
          end
          item
            Caption = '�ϼ��豸'
            Width = 120
          end
          item
            Caption = '�豸����'
            Width = 80
          end
          item
            Caption = '������ϵͳ'
            Width = 80
          end>
        ColumnClick = False
        FlatScrollBars = True
        GridLines = True
        TabOrder = 1
        ViewStyle = vsReport
      end
    end
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
      end
      item
        Name = '�ϼ��豸'
        Caption = '�ϼ��豸'
        FieldType = wftUndefined
        Features.Strings = ()
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
      end
      item
        Name = '�豸����'
        Caption = '�豸����'
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
        Name = '�豸����'
        Caption = '�豸����'
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
        Name = '��ϵͳ'
        Caption = '��ϵͳ'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
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
          '|�豸����|�����豸ע���|�豸���|����|���ʹ���|�ϼ��豸���|�豸' +
          '״̬|�豸�����ͺ�|������ϵͳ|�豸��������|������Ա����|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 76
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '�豸��ѯ'
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
        ParamName = '�ϼ��豸'
        FieldName = '�ϼ��豸'
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
        ParamName = '��ϵͳ'
        FieldName = '��ϵͳ'
      end>
    Left = 120
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 184
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 232
    Top = 256
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
        DataField = 'lvol3'
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|�ͻ���|ѧ����|����|����|���֤��|'
      end>
    Left = 76
    Top = 303
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '�ѿ����ͻ���Ϣ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
        DefaultValue = 0
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
        DefaultValue = 0
      end
      item
        ParamName = '�ͻ�����'
        FieldName = '�ͻ�����'
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
        DefaultValue = 0
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
        DefaultValue = 0
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'Ǯ����'
        DefaultValue = 0
      end>
    AfterExec = MainRequestAfterExec
    Left = 112
    Top = 304
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
        Name = '�豸��'
        Caption = '�豸��'
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
        Name = '����;'
        Caption = '����;'
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
        Name = '�������'
        Caption = '�������'
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
          '|�豸����|�����豸ע���|�豸���|����|���ʹ���|�ϼ��豸���|�豸' +
          '״̬|�豸�����ͺ�|������ϵͳ|�豸��������|������Ա����|'
      end>
    Left = 68
    Top = 359
  end
  object WVRequest2: TWVRequest
    WorkView = WorkView2
    ID = '��������������'
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
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '�豸��'
        FieldName = '�豸��'
      end
      item
        ParamName = '����;'
        FieldName = '����;'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '������־'
        FieldName = '������־'
      end>
    AfterExec = MainRequestAfterExec
    Left = 112
    Top = 360
  end
  object dlgSave1: TSaveDialog
    Filter = '�ı��ļ�(*.txt)|*.txt'
    Title = '���ó�������ʧ����Ϣ'
    Left = 192
    Top = 362
  end
end
