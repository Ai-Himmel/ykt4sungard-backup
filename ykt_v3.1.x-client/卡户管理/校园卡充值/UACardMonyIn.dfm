inherited faqhCardMonyIn: TfaqhCardMonyIn
  Width = 655
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 18
    Width = 655
    Height = 471
    Align = alClient
    Color = 16184303
    object RzStatusPane2: TRzStatusPane [0]
      Left = 0
      Top = 450
      Width = 655
      Height = 21
      FrameStyle = fsStatus
      Align = alBottom
      Color = 16184303
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
    end
    inherited btnQuery: TBitBtn
      Left = 30
      Top = 419
      TabOrder = 5
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 29
      Top = 387
      TabOrder = 2
      Visible = False
    end
    object btnReadCardInfo: TBitBtn
      Left = 344
      Top = 403
      Width = 110
      Height = 25
      Hint = '��ȡ����Ϣ'
      Caption = '������Ϣ(&R)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnReadCardInfoClick
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000000000000000000000000000000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FF000000FF000000FF000000FF000000FFFFFF00FFFFFF007B7B
        7B007B7B7B007B7B7B00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FF000000FF000000FF000000FFFFFF00FFFFFF00FFFFFF007B7B
        7B007B7B7B007B7B7B007B7B7B00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FF000000FF000000FF000000FF000000FFFFFF00FFFFFF007B7B
        7B007B7B7B007B7B7B00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FF000000FF000000FF000000FFFFFF00FFFFFF00FFFFFF007B7B
        7B007B7B7B00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FF000000FF000000FF000000FF000000FF000000FFFFFF007B7B
        7B007B7B7B007B7B7B00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00000000000000000000000000FFFFFF00FFFFFF00FFFFFF000000
        00000000000000000000FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF007B7B
        7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B
        7B007B7B7B007B7B7B007B7B7B007B7B7B0000000000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
    end
    object grp1: TGroupBox
      Left = 184
      Top = 72
      Width = 401
      Height = 193
      Caption = '����Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object WVLabel5: TWVLabel
        Left = 300
        Top = 128
        Width = 14
        Height = 14
        Caption = 'Ԫ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object WVLabel10: TWVLabel
        Left = 300
        Top = 160
        Width = 14
        Height = 14
        Caption = 'Ԫ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object RzStatusPane1: TRzStatusPane
        Left = 13
        Top = 26
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��    ��'
      end
      object RzStatusPane3: TRzStatusPane
        Left = 13
        Top = 58
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '���׿���'
      end
      object RzStatusPane4: TRzStatusPane
        Left = 13
        Top = 90
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'ѧ/����'
      end
      object RzStatusPane5: TRzStatusPane
        Left = 13
        Top = 122
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��ֵǰ���'
      end
      object RzStatusPane6: TRzStatusPane
        Left = 13
        Top = 154
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��ֵ�����'
      end
      object edtName: TRzEdit
        Left = 132
        Top = 27
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
      end
      object edtCardNo: TRzEdit
        Left = 132
        Top = 59
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
      end
      object edtStuempNo: TRzEdit
        Left = 132
        Top = 91
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
      end
      object edtCardMoney: TRzEdit
        Left = 132
        Top = 123
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 3
      end
      object edtAfterMoney: TRzEdit
        Left = 132
        Top = 155
        Width = 161
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        FrameVisible = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 4
      end
    end
    object grp2: TGroupBox
      Left = 184
      Top = 272
      Width = 401
      Height = 121
      Caption = '��ֵ��Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      object WVLabel3: TWVLabel
        Left = 297
        Top = 89
        Width = 14
        Height = 14
        Caption = 'Ԫ'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object RzStatusPane7: TRzStatusPane
        Left = 13
        Top = 84
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��ֵ���'
      end
      object RzStatusPane8: TRzStatusPane
        Left = 13
        Top = 51
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'Ʊ�ݺ���'
      end
      object RzStatusPane9: TRzStatusPane
        Left = 13
        Top = 19
        Width = 116
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��ֵ����'
      end
      object lblTip: TLabel
        Left = 13
        Top = 113
        Width = 66
        Height = 19
        Caption = 'lblTip'
        Font.Charset = GB2312_CHARSET
        Font.Color = clMaroon
        Font.Height = -19
        Font.Name = '����'
        Font.Style = [fsBold]
        ParentFont = False
        Visible = False
      end
      object WVLabel1: TWVLabel
        Left = 297
        Top = 25
        Width = 70
        Height = 14
        Caption = '(����ѡ��)'
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
      end
      object cbbType: TWVComboBox
        Tag = 2
        Left = 134
        Top = 20
        Width = 158
        Height = 22
        Style = csDropDownList
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ImeName = '���� (����) - ΢��ƴ��'
        ItemHeight = 14
        ParentFont = False
        TabOrder = 0
        OnChange = cbbTypeChange
        OnKeyDown = cbbTypeKeyDown
        WorkView = WorkView
        FieldName = '��ֵ����'
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '63'
      end
      object edtTicketNo: TWVEdit
        Left = 134
        Top = 52
        Width = 158
        Height = 22
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        ReadOnly = False
        TabOrder = 1
        Text = '<Ʊ�ݺ���>'
        WorkView = WorkView
        FieldName = 'Ʊ�ݺ���'
      end
      object edtmoneymoneymoney: TRzNumericEdit
        Left = 133
        Top = 1000
        Width = 136
        Height = 22
        TabOrder = 4
        DisplayFormat = ',0;(,0)'
      end
      object edtmoney: TWVDigitalEdit
        Left = 134
        Top = 85
        Width = 158
        Height = 21
        AllowPoint = True
        Precision = 2
        ParentColor = False
        TabOrder = 2
        TabStop = True
        Text = '0'
        OnKeyDown = edtmoneyKeyDown
        WorkView = WorkView
        FieldName = '��ֵ���'
      end
      object chkSaveMoney: TCheckBox
        Left = 312
        Top = 88
        Width = 75
        Height = 17
        Caption = '�������'
        TabOrder = 3
      end
    end
    object btnMoneyIn: TBitBtn
      Left = 472
      Top = 403
      Width = 110
      Height = 25
      Hint = 'У԰����ֵ'
      Caption = '����ֵ(&F)'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btnMoneyInClick
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF009C3100009C310000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF009C310000CE6300009C310000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF009C310000CE630000CE6300009C310000CE9C6300CE9C6300CE9C
        6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300FFFFFF00FFFF
        FF009C310000CE630000CE630000CE6300009C310000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF009C31
        0000CE630000CE630000CE630000CE6300009C310000E7E7E700E7E7E700E7E7
        E700E7E7E700E7E7E700E7E7E700E7E7E700FFFFFF00CE9C63009C310000CE63
        0000CE630000CE630000CE630000CE6300009C310000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF009C31
        0000CE630000CE630000CE630000CE6300009C310000E7E7E700E7E7E700E7E7
        E700E7E7E700E7E7E700E7E7E700E7E7E700FFFFFF00CE9C6300FFFFFF00FFFF
        FF009C310000CE630000CE630000CE6300009C310000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFF
        FF00FFFFFF009C310000CE630000CE6300009C310000E7E7E700E7E7E700E7E7
        E700E7E7E700E7E7E700E7E7E700E7E7E700FFFFFF00CE9C6300FFFFFF00FFFF
        FF00FFFFFF00FFFFFF009C310000CE6300009C310000FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00CE9C63009C3100009C310000E7E7E700E7E7E700E7E7
        E700E7E7E700E7E7E700E7E7E700E7E7E700FFFFFF00CE9C6300FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00CE9C6300FFFFFF00E7E7E700E7E7E700E7E7E700E7E7
        E700E7E7E700E7E7E700E7E7E700E7E7E700FFFFFF00CE9C6300FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CE9C6300FFFFFF00FFFF
        FF00FFFFFF00FFFFFF00CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C
        6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300CE9C6300}
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 655
    inherited Image1: TImage
      Width = 655
    end
    inherited LabRecordCount: TLabel
      Visible = False
    end
  end
  inherited UIPanel2: TUIPanel
    Left = 8
    Top = 360
    Width = 73
    Height = 17
    Align = alNone
    Visible = False
    inherited Grid: TRzDBGrid
      Left = 56
      Top = 464
      Width = 233
      Height = 41
      Align = alNone
      Visible = False
      Columns = <
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 75
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Ա�'
          Width = 52
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ѧ/����'
          Width = 72
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ���'
          Width = 82
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ�״̬'
          Width = 88
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ����'
          Width = 88
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
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʶ'
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������'
          Width = 78
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������'
          Width = 94
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstation0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ʺ�'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'scust_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��λ'
          Width = 84
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ע��ʱ��'
          Width = 81
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ϵ�绰'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���֤��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 81
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���ɱ���'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����Ϣ��ע'
          Width = 86
          Visible = True
        end>
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
      end
      item
        Name = '������'
        Caption = '������'
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
        Name = '�뿨���'
        Caption = '�뿨���'
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
        Name = '���״���'
        Caption = '���״���'
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
        Name = '��ֵ����'
        Caption = '��ֵ����'
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
        Name = 'Ʊ�ݺ���'
        Caption = 'Ʊ�ݺ���'
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
        Name = '��ֵ���'
        Caption = '��ֵ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = True
        Checker.UpperCase = False
      end
      item
        Name = '��ˮ��'
        Caption = '��ˮ��'
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
        Name = 'ҵ������'
        Caption = 'ҵ������'
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
        Name = '�������'
        Caption = '�������'
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
        Name = '�ն˱��'
        Caption = '�ն˱��'
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
        MonitorValueChangedFields = '|�ͻ���|ѧ����|����|����|���֤��|'
      end>
    Left = 36
    Top = 31
  end
  inherited MainRequest: TWVRequest
    ID = '����ֵ'
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
        Direction = bdBiDirection
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '�뿨���'
        FieldName = '�뿨���'
      end
      item
        ParamName = '���״���'
        FieldName = '���״���'
      end
      item
        ParamName = '��ֵ����'
        FieldName = '��ֵ����'
      end
      item
        ParamName = 'Ʊ�ݺ���'
        FieldName = 'Ʊ�ݺ���'
      end
      item
        ParamName = '��ֵ���'
        FieldName = '��ֵ���'
      end
      item
        ParamName = '��ˮ��'
        FieldName = '��ˮ��'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'ҵ������'
        Direction = bdParam2Field
      end
      item
        ParamName = '�������'
        FieldName = '�������'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ն˱��'
        FieldName = '�ն˱��'
        Direction = bdParam2Field
      end>
    Left = 72
    Top = 32
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 40
    Top = 424
  end
  inherited DataSource: TDataSource
    Left = 72
    Top = 424
  end
  object WVRcashOperCancel: TWVRequest
    WorkView = WVcashOperCancel
    ID = '��ֵ֧ȡ����'
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
        ParamName = '��ˮ��'
        FieldName = '��ˮ��'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'ҵ������'
      end
      item
        ParamName = '�ն˱��'
        FieldName = '�ն˱��'
      end>
    AfterExec = MainRequestAfterExec
    Left = 80
    Top = 72
  end
  object WVcashOperCancel: TWorkView
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
        Name = 'ҵ������'
        Caption = 'ҵ������'
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
        Name = '��ˮ��'
        Caption = '��ˮ��'
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
        Name = '�ն˱��'
        Caption = '�ն˱��'
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
    FieldsMonitors = <>
    Left = 40
    Top = 72
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
      end
      item
        Name = '������'
        Caption = '������'
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
    Left = 44
    Top = 111
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
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
        ParamName = '������'
        FieldName = '������'
      end>
    AfterExec = MainRequestAfterExec
    Left = 80
    Top = 112
  end
  object wvrUpdate: TWVRequest
    WorkView = wvUpdate
    ID = '���¿���Ϣ'
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
        Direction = bdBiDirection
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��ʾ����'
        FieldName = '��ʾ����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ͻ����'
        FieldName = '�ͻ����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�շ����'
        FieldName = '�շ����'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'ѧ����'
        Direction = bdParam2Field
      end
      item
        ParamName = '����'
        FieldName = '����'
        Direction = bdParam2Field
      end
      item
        ParamName = '���Ŵ���'
        FieldName = '���Ŵ���'
        Direction = bdParam2Field
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
        Direction = bdParam2Field
      end
      item
        ParamName = '�Ա�'
        FieldName = '�Ա�'
        Direction = bdParam2Field
      end
      item
        ParamName = '����������'
        FieldName = '����������'
        Direction = bdBiDirection
      end
      item
        ParamName = '�����'
        FieldName = '�����'
        Direction = bdBiDirection
      end
      item
        ParamName = '���״���'
        FieldName = '���״���'
        Direction = bdBiDirection
      end
      item
        ParamName = '�������κ�'
        FieldName = '�������κ�'
        Direction = bdParam2Field
      end
      item
        ParamName = '������'
        FieldName = '������'
        Direction = bdParam2Field
      end
      item
        ParamName = '�����޶�'
        FieldName = '�����޶�'
        Direction = bdParam2Field
      end
      item
        ParamName = '���޶�'
        FieldName = '���޶�'
        Direction = bdParam2Field
      end
      item
        ParamName = '�����޶�'
        FieldName = '�����޶�'
      end
      item
        ParamName = '�뵥���޶�'
        FieldName = '�뵥���޶�'
      end>
    AfterExec = MainRequestAfterExec
    Left = 80
    Top = 152
  end
  object wvUpdate: TWorkView
    WorkFields = <
      item
        Name = '������'
        Caption = '������'
        FieldType = wftUndefined
        DataType = kdtInt64
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
        Name = '������'
        Caption = '������'
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
        Name = '���Ŵ���'
        Caption = '���Ŵ���'
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
        Name = '�Ա�'
        Caption = '�Ա�'
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
        Name = '����������'
        Caption = '����������'
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
        Name = '�����'
        Caption = '�����'
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
        Name = '���״���'
        Caption = '���״���'
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
        Name = '�������κ�'
        Caption = '�������κ�'
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
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�����޶�'
        Caption = '�����޶�'
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
        Name = '���޶�'
        Caption = '���޶�'
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
        Name = '�뵥���޶�'
        Caption = '�뵥���޶�'
        FieldType = wftUndefined
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�����޶�'
        Caption = '�����޶�'
        FieldType = wftUndefined
        DataType = kdtFloat
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
        MonitorValueChangedFields = '|����ʶ|'
      end>
    Left = 44
    Top = 151
  end
end
