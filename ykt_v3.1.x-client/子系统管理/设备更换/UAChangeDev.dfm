inherited fqhqChangeDev: TfqhqChangeDev
  Width = 893
  Height = 489
  inherited UIPnlQueryCount: TUIPanel [0]
    Width = 893
    TabOrder = 0
    inherited Image1: TImage
      Width = 893
    end
    inherited LabRecordCount: TLabel
      Font.Color = clBlack
      Visible = False
    end
  end
  inherited UIPanel1: TUIPanel [1]
    Top = 459
    Width = 893
    TabOrder = 2
    inherited btnQuery: TBitBtn
      Left = 804
      Hint = '�����豸'
      Caption = '�����豸'
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 803
      Top = 100
      Visible = False
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 893
    Height = 441
    TabOrder = 1
    inherited Grid: TRzDBGrid
      Left = 104
      Top = 72
      Width = 284
      Height = 170
      Align = alNone
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
    object RzSizePanel1: TRzSizePanel
      Left = 0
      Top = 0
      Width = 454
      Height = 441
      HotSpotVisible = True
      SizeBarWidth = 7
      TabOrder = 1
      UseGradients = True
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 446
        Height = 131
        Align = alTop
        BevelOuter = bvNone
        Color = 16119543
        TabOrder = 0
        object Label1: TLabel
          Left = 34
          Top = 27
          Width = 48
          Height = 12
          Caption = '�豸����'
        end
        object Label3: TLabel
          Left = 230
          Top = 80
          Width = 60
          Height = 12
          Caption = '�豸����ID'
        end
        object Label4: TLabel
          Left = 58
          Top = 53
          Width = 24
          Height = 12
          Caption = '����'
        end
        object Label5: TLabel
          Left = 242
          Top = 29
          Width = 48
          Height = 12
          Caption = '�豸����'
        end
        object Label8: TLabel
          Left = 242
          Top = 53
          Width = 48
          Height = 12
          Caption = '�豸����'
        end
        object Label9: TLabel
          Left = 22
          Top = 80
          Width = 60
          Height = 12
          Caption = '������ϵͳ'
        end
        object Label2: TLabel
          Left = 34
          Top = 5
          Width = 75
          Height = 14
          Caption = '���豸��ѯ'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlue
          Font.Height = -14
          Font.Name = '����'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object lblOld: TLabel
          Left = 22
          Top = 108
          Width = 307
          Height = 12
          AutoSize = False
          Caption = '������ϵͳ'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlue
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object WVEdit1: TWVEdit
          Left = 84
          Top = 23
          Width = 135
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 0
          Text = '<�豸����>'
          WorkView = WorkView
          FieldName = '�豸����'
        end
        object WVEdit3: TWVEdit
          Left = 292
          Top = 76
          Width = 124
          Height = 20
          CharCase = ecUpperCase
          Color = clWhite
          ReadOnly = False
          TabOrder = 5
          Text = '<�豸����ID>'
          WorkView = WorkView
          FieldName = '�豸����ID'
        end
        object WVComboBox3: TWVComboBox
          Left = 84
          Top = 76
          Width = 135
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '������ϵͳ'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-32'
        end
        object WVComboBox5: TWVComboBox
          Left = 292
          Top = 49
          Width = 124
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 3
          WorkView = WorkView
          FieldName = '�豸�����ͺ�'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-35'
        end
        object WVComboBox6: TWVComboBox
          Left = 292
          Top = 23
          Width = 124
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 1
          WorkView = WorkView
          FieldName = '���ʹ���'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*47'
        end
        object edtMachineNo: TWVEdit
          Left = 84
          Top = 50
          Width = 135
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 2
          Text = '<����>'
          WorkView = WorkView
          FieldName = '����'
        end
        object btnOldQuery: TBitBtn
          Left = 340
          Top = 99
          Width = 75
          Height = 25
          Caption = '�� ѯ'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
          TabOrder = 6
          OnClick = btnOldQueryClick
        end
      end
      object rgOld: TRzDBGrid
        Left = 0
        Top = 131
        Width = 446
        Height = 310
        Align = alClient
        Color = clWhite
        DataSource = DataSource
        FixedColor = 15458000
        TabOrder = 1
        TitleFont.Charset = GB2312_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -12
        TitleFont.Name = '����'
        TitleFont.Style = []
        OnCellClick = rgOldCellClick
        OnDrawColumnCell = GridDrawColumnCell
        OnKeyDown = GridKeyDown
        FrameColor = 12164479
        FrameStyle = fsGroove
        FrameVisible = True
        FixedLineColor = 12164479
        LineColor = clBackground
        Columns = <
          item
            Expanded = False
            FieldName = 'lserial1'
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            Title.Alignment = taCenter
            Title.Caption = '�豸��ʶ'
            Width = 68
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no'
            Title.Alignment = taCenter
            Title.Caption = '�豸����'
            Width = 87
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone3'
            Title.Alignment = taCenter
            Title.Caption = '�豸����ID'
            Width = 71
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_code'
            Title.Alignment = taCenter
            Title.Caption = '���ʹ���'
            Width = 72
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            Title.Alignment = taCenter
            Title.Caption = '�������˿�����'
            Width = 69
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt6'
            Title.Alignment = taCenter
            Title.Caption = '�ϼ��豸'
            Width = 68
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scurrency_type'
            Title.Caption = '��Ƭ�ṹ'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            Title.Alignment = taCenter
            Title.Caption = '�������˿ں�'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol4'
            Title.Alignment = taCenter
            Title.Caption = '�豸״̬'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_code2'
            Title.Alignment = taCenter
            Title.Caption = 'ͨѶ�˿ں�'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type'
            Title.Alignment = taCenter
            Title.Caption = '�豸����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstation0'
            Title.Alignment = taCenter
            Title.Caption = 'IP��ַ'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lserial0'
            Title.Alignment = taCenter
            Title.Caption = '������ϵͳ'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            Title.Alignment = taCenter
            Title.Caption = '��ע'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'damt5'
            Title.Caption = '�豸��;'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt4'
            Title.Caption = '�Ƿ�֧�ֿ�Ŀ�շ�'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            Title.Caption = 'ͨѶ���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            Title.Alignment = taCenter
            Title.Caption = '�������κ�'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial1'
            Title.Alignment = taCenter
            Title.Caption = '�������汾'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            Title.Caption = '��ע'
            Width = 120
            Visible = True
          end>
      end
    end
    object pnl1: TPanel
      Left = 454
      Top = 0
      Width = 439
      Height = 441
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 2
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 439
        Height = 131
        Align = alTop
        BevelOuter = bvNone
        Color = 16119543
        TabOrder = 0
        object Label6: TLabel
          Left = 34
          Top = 27
          Width = 48
          Height = 12
          Caption = '�豸����'
        end
        object Label7: TLabel
          Left = 230
          Top = 80
          Width = 60
          Height = 12
          Caption = '�豸����ID'
        end
        object Label10: TLabel
          Left = 58
          Top = 53
          Width = 24
          Height = 12
          Caption = '����'
        end
        object Label11: TLabel
          Left = 242
          Top = 29
          Width = 48
          Height = 12
          Caption = '�豸����'
        end
        object Label12: TLabel
          Left = 242
          Top = 53
          Width = 48
          Height = 12
          Caption = '�豸����'
        end
        object Label13: TLabel
          Left = 22
          Top = 80
          Width = 60
          Height = 12
          Caption = '������ϵͳ'
        end
        object Label14: TLabel
          Left = 34
          Top = 5
          Width = 75
          Height = 14
          Caption = '���豸��ѯ'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlue
          Font.Height = -14
          Font.Name = '����'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object lblNew: TLabel
          Left = 22
          Top = 108
          Width = 307
          Height = 12
          AutoSize = False
          Caption = '������ϵͳ'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlue
          Font.Height = -12
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object WVEdit2: TWVEdit
          Left = 84
          Top = 23
          Width = 135
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 0
          Text = '<�豸����>'
          WorkView = WVNewQry
          FieldName = '�豸����'
        end
        object WVEdit4: TWVEdit
          Left = 292
          Top = 76
          Width = 124
          Height = 20
          CharCase = ecUpperCase
          Color = clWhite
          ReadOnly = False
          TabOrder = 5
          Text = '<�豸����ID>'
          WorkView = WVNewQry
          FieldName = '�豸����ID'
        end
        object WVComboBox1: TWVComboBox
          Left = 84
          Top = 76
          Width = 135
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 4
          WorkView = WVNewQry
          FieldName = '������ϵͳ'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-32'
        end
        object WVComboBox2: TWVComboBox
          Left = 292
          Top = 49
          Width = 124
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 3
          WorkView = WVNewQry
          FieldName = '�豸�����ͺ�'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-35'
        end
        object WVComboBox4: TWVComboBox
          Left = 292
          Top = 23
          Width = 124
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 1
          WorkView = WVNewQry
          FieldName = '���ʹ���'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*47'
        end
        object WVEdit5: TWVEdit
          Left = 84
          Top = 50
          Width = 135
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 2
          Text = '<����>'
          WorkView = WVNewQry
          FieldName = '����'
        end
        object btnNewQry: TBitBtn
          Left = 340
          Top = 99
          Width = 75
          Height = 25
          Caption = '�� ѯ'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
          TabOrder = 6
          OnClick = btnNewQryClick
        end
      end
      object rgNew: TRzDBGrid
        Left = 0
        Top = 131
        Width = 439
        Height = 310
        Align = alClient
        Color = clWhite
        DataSource = DataSource1
        FixedColor = 15458000
        TabOrder = 1
        TitleFont.Charset = GB2312_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -12
        TitleFont.Name = '����'
        TitleFont.Style = []
        OnCellClick = rgNewCellClick
        OnDrawColumnCell = GridDrawColumnCell
        OnKeyDown = GridKeyDown
        FrameColor = 12164479
        FrameStyle = fsGroove
        FrameVisible = True
        FixedLineColor = 12164479
        LineColor = clBackground
        Columns = <
          item
            Expanded = False
            FieldName = 'lserial1'
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol0'
            Title.Alignment = taCenter
            Title.Caption = '�豸��ʶ'
            Width = 68
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scert_no'
            Title.Alignment = taCenter
            Title.Caption = '�豸����'
            Width = 87
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone3'
            Title.Alignment = taCenter
            Title.Caption = '�豸����ID'
            Width = 71
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_code'
            Title.Alignment = taCenter
            Title.Caption = '���ʹ���'
            Width = 72
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            Title.Alignment = taCenter
            Title.Caption = '�������˿�����'
            Width = 69
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt6'
            Title.Alignment = taCenter
            Title.Caption = '�ϼ��豸'
            Width = 68
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scurrency_type'
            Title.Caption = '��Ƭ�ṹ'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol3'
            Title.Alignment = taCenter
            Title.Caption = '�������˿ں�'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol4'
            Title.Alignment = taCenter
            Title.Caption = '�豸״̬'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sbank_code2'
            Title.Alignment = taCenter
            Title.Caption = 'ͨѶ�˿ں�'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type'
            Title.Alignment = taCenter
            Title.Caption = '�豸����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstation0'
            Title.Alignment = taCenter
            Title.Caption = 'IP��ַ'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lserial0'
            Title.Alignment = taCenter
            Title.Caption = '������ϵͳ'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ssectypes'
            Title.Alignment = taCenter
            Title.Caption = '��ע'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'damt5'
            Title.Caption = '�豸��;'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt4'
            Title.Caption = '�Ƿ�֧�ֿ�Ŀ�շ�'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            Title.Caption = 'ͨѶ���'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            Title.Alignment = taCenter
            Title.Caption = '�������κ�'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sserial1'
            Title.Alignment = taCenter
            Title.Caption = '�������汾'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            Title.Caption = '��ע'
            Width = 120
            Visible = True
          end>
      end
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
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
        GroupIndex = 1
        DataField = 'scert_no'
      end
      item
        Name = '�豸����ID'
        Caption = '�豸����ID'
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
        GroupIndex = 1
        DataField = 'sbank_pwd2'
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
        GroupIndex = 1
        DataField = 'lvol1'
      end
      item
        Name = '���ʹ���'
        Caption = '���ʹ���'
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
        DataField = 'sbank_code'
      end
      item
        Name = '�豸�����ͺ�'
        Caption = '�豸�����ͺ�'
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
        DataField = 'lbank_acc_type'
      end
      item
        Name = '������ϵͳ'
        Caption = '������ϵͳ'
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
        DataField = 'lserial0'
      end
      item
        Name = '�豸״̬'
        Caption = '�豸״̬'
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
        Name = '�豸�����ͺ�'
        Caption = '�豸�����ͺ�'
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
        Name = '������ϵͳ'
        Caption = '������ϵͳ'
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
        Name = '�豸��������'
        Caption = '�豸��������'
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
      end>
    Left = 100
    Top = 255
  end
  inherited MainRequest: TWVRequest
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
        ParamName = '������ϵͳ'
        FieldName = '������ϵͳ'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = '�豸�����ͺ�'
      end
      item
        ParamName = '�豸״̬'
        FieldName = '�豸״̬'
      end>
    Left = 136
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lserial1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-28'
      end
      item
        FieldName = 'sbank_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '47'
      end
      item
        FieldName = 'damt6'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-31'
      end
      item
        FieldName = 'scurrency_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '48'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '5'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-35'
      end
      item
        FieldName = 'lserial0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-32'
      end
      item
        FieldName = 'damt5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '81'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '50'
      end>
    Left = 176
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 216
    Top = 256
  end
  object WVDBBinder1: TWVDBBinder
    DataSource = DataSource1
    WorkView = WVNewQry
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lserial1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-28'
      end
      item
        FieldName = 'sbank_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '47'
      end
      item
        FieldName = 'damt6'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-31'
      end
      item
        FieldName = 'scurrency_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '48'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '5'
      end
      item
        FieldName = 'lbank_acc_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-35'
      end
      item
        FieldName = 'lserial0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-32'
      end
      item
        FieldName = 'damt5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '81'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '50'
      end>
    HideUnbindingFields = False
    Left = 160
    Top = 312
  end
  object DataSource1: TDataSource
    OnDataChange = DataSourceDataChange
    Left = 192
    Top = 312
  end
  object WVChange: TWorkView
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
        Name = '���豸'
        Caption = '���豸'
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
        Name = '���豸'
        Caption = '���豸'
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
          '|�豸����|�����豸ע���|�豸���|����|���ʹ���|�ϼ��豸���|�豸' +
          '״̬|�豸�����ͺ�|������ϵͳ|�豸��������|������Ա����|'
      end>
    Left = 92
    Top = 351
  end
  object WVRchange: TWVRequest
    WorkView = WVChange
    ID = '�����豸'
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
        ParamName = '���豸'
        FieldName = '���豸'
      end
      item
        ParamName = '���豸'
        FieldName = '���豸'
      end>
    AfterExec = MainRequestAfterExec
    Left = 128
    Top = 352
  end
  object WVNewQry: TWorkView
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
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|�豸����|�����豸ע���|�豸���|����|���ʹ���|�ϼ��豸���|�豸' +
          '״̬|�豸�����ͺ�|������ϵͳ|�豸��������|������Ա����|'
      end>
    Left = 92
    Top = 311
  end
  object WVRNewQry: TWVRequest
    WorkView = WVNewQry
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
        ParamName = '������ϵͳ'
        FieldName = '������ϵͳ'
      end
      item
        ParamName = '�豸�����ͺ�'
        FieldName = '�豸�����ͺ�'
      end
      item
        ParamName = '�豸״̬'
        FieldName = '�豸״̬'
      end>
    AfterExec = MainRequestAfterExec
    Left = 128
    Top = 312
  end
end
