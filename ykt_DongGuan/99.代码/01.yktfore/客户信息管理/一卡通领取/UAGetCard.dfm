inherited faqhGetCard: TfaqhGetCard
  Width = 811
  Height = 489
  inherited UIPanel1: TUIPanel
    Top = 459
    Width = 811
    inherited btnQuery: TBitBtn
      Left = 546
    end
    inherited btnPrint: TBitBtn
      Left = 721
    end
    object btnGetCard: TBitBtn
      Left = 634
      Top = 3
      Width = 79
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '�� ��'
      Enabled = False
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnGetCardClick
    end
    object chkPrint: TCheckBox
      Left = 8
      Top = 8
      Width = 73
      Height = 17
      Caption = '��ӡ�ص�'
      Checked = True
      State = cbChecked
      TabOrder = 3
    end
    object btnReadCard: TBitBtn
      Left = 458
      Top = 3
      Width = 79
      Height = 25
      Anchors = [akTop, akRight]
      Caption = '������ѯ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 811
    inherited Image1: TImage
      Width = 811
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 811
    Height = 87
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label4: TLabel
      Left = 18
      Top = 18
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label12: TLabel
      Left = 18
      Top = 42
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label7: TLabel
      Left = 18
      Top = 66
      Width = 48
      Height = 12
      Caption = '����״̬'
    end
    object Label9: TLabel
      Left = 386
      Top = 18
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label14: TLabel
      Left = 218
      Top = 42
      Width = 24
      Height = 12
      Caption = '�Ա�'
    end
    object Label17: TLabel
      Left = 194
      Top = 66
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label15: TLabel
      Left = 386
      Top = 42
      Width = 24
      Height = 12
      Caption = '�绰'
    end
    object Label10: TLabel
      Left = 194
      Top = 18
      Width = 48
      Height = 12
      Caption = '֤������'
    end
    object Label16: TLabel
      Left = 567
      Top = 42
      Width = 24
      Height = 12
      Caption = '�ֻ�'
    end
    object Label11: TLabel
      Left = 543
      Top = 18
      Width = 48
      Height = 12
      Caption = '֤������'
    end
    object imgPhoto: TImage
      Left = 743
      Top = 4
      Width = 60
      Height = 80
      Picture.Data = {
        0A544A504547496D6167659B050000FFD8FFE000104A46494600010101006000
        600000FFDB0043000D09090A0A0A0E0B0B0E140D0B0D1417110E0E11171B1515
        1515151B1B1517171717151B1A1E2021201E1A27272A2A272735353535353636
        3636363636363636FFDB0043010E0D0D1111111711111717131413171D191A1A
        191D261D1D1E1D1D262C2420202020242C282B2626262B282F2F2C2C2F2F3636
        36363636363636363636363636FFC00011080070005403011100021101031101
        FFC4001B00000203010101000000000000000000000005010406070302FFC400
        4010000103020303080608040700000000000100020304110512210631411322
        32516171819114162352A1C1333435547292B1F02443D1D2536273A2B2E1F1FF
        C40014010100000000000000000000000000000000FFC4001411010000000000
        0000000000000000000000FFDA000C03010002110311003F00D1A01008250082
        104A0840201008250083E6495B18B9F068DE7C38A057518DB5AEB40DCEDB0B93
        A6A8293F16AC7DB9F6B6BA0DE83C1B553B0B8B6423374ADC507B4389D4C31F26
        D22DD76D77DCF1081A5362F14EFC8E696389E6F107C8206080B202C825041360
        7CD066F10AD3552E976B1BA0693C7C10544020104209DC81AE1B8A4BCA470CB6
        730F35AEE20F040ED00825055C46734F4AF7817E1DD7D1066105AC3F0CABC4A5
        E4E9D97B749E746B7BCFECA0D452EC552B403552BA57FBACE6B7E37282E1D92C
        1C8B726EEFCEEF9E8817576C536D9A8663987F2E5F93C0FD420CB54534D4B298
        67618E46EF69D104D1FD662ED7B47C7FED06B100825056C41A1D47303BB21F31
        AA0CC451BE69191305DF23835A3B4E83CD074CC3A822C3E9594F10E88E73B8B8
        F12822BF13A4C3D99EA64C97E88DEE3DC02058CDB1C29CECA79460F78B34F269
        27E081D41510D4442585E248DDB9C0DD02BDA4C2995D46F91A3F8880678DC379
        B6F6F920C361FF005B87F1041AB4020941F12B43A37B4EE2083E21020D9E607E
        2F4A0EECF7FCA0B87E883A3A0E7BB533BE5C5A60E3CD8F2B59D832827E281420
        D86C3998C5557BF237664FC5ADEDF041A83AEFE28397537D6A3CA74E506A7AAE
        835A8041281263F2CCD7C4C0E223209D389DC502AA7A8969A56CD0BB24ADDCED
        0DB81EBEB417FD65C63EF27C9BFD1050A8A896A6574D33B3C8FE93BE1C1031C1
        3009F157673ECE95A6CE9389FF002B506F292920A385B053B43236F0EDE249EB
        414B1FC523C3A89E737B6906589BC6E74BF820E77F2DC83631B488DA0EF005D0
        7DA0940BF1AA6E5E94B9BD388E6F0E2833282507DC113A696385BD291CD60EF7
        1B20EA14D4F1D340C862196360B01F340A3683684619EC2101F54F17B9DCC1D6
        6DC7B10622A6AA7AA90CD3BCC921DE4FEEC83D30EA7F48AB8D9BDA0E67770DE8
        3596402094020478960F0C71C9511B88035E4F86A6C812A0B98280714A407FC5
        67C08283A620E77B4AE2EC66A6FAD8B47FB1A815A0D561D41152442C3DA380CE
        E3BEFC420B8804128041E73442689F11DCF041418F9E17C1298A4167B74FFC41
        E94351E8B570D45B3724F0ECB7DF6F341A7F5E62FBA3BF38FED419BC4EB05756
        CB521B90484736F7B6806FF04061D48FAAA86B40BB1A4179E000D4A0D620104A
        094108040AB682367A207D867CE05FC0A0474749256D4329A2B72921B36FA0D3
        5EAEC40E3D4CC57AE2FCC7FB502AC42826C3AA3D1E7B1900079BA8D77207F826
        4F408F2EF17CFD77B9417EC80B2094020A73E2D43068E903CFBADE77E9A205F2
        ED20FE4C3E2F3FD102FADC56A2B581920686839B9B7E17EBEF41EDB37F6CD2FE
        277FC5C83A3A0C0ED87DAEEFF4D9F340B292BA7A371313B43BDA777920BECDA3
        A91F491B5C3B2E105C87682924D240633DBA8F82060CABA690666CAC23BD0652
        AB10A9AAFA579CBEE0E8F971415D008041F70CF2D3C82585C592B7A2E1E482EF
        AC18BFDE9E82A54D54F55272B3BCC921D331EC41E48040203F7C500804020100
        804020100804020FFFD9}
      Stretch = True
    end
    object Label1: TLabel
      Left = 386
      Top = 66
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label2: TLabel
      Left = 531
      Top = 66
      Width = 60
      Height = 12
      Caption = 'Ӧ�����к�'
    end
    object cbb1: TWVComboBox
      Left = 76
      Top = 62
      Width = 112
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 8
      WorkView = WorkView1
      FieldName = '��ѯ.����״̬'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*200'
    end
    object edtBirthdayQ: TWVEdit
      Left = 76
      Top = 38
      Width = 112
      Height = 20
      Color = clInfoBk
      MaxLength = 9
      ReadOnly = False
      TabOrder = 4
      Text = '<��ѯ.��������>'
      WorkView = WorkView1
      FieldName = '��ѯ.��������'
    end
    object cbbDept: TWVComboBox
      Left = 76
      Top = 14
      Width = 112
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 0
      WorkView = WorkView1
      FieldName = '��ѯ.��������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*210'
    end
    object WVEdit17: TWVEdit
      Left = 252
      Top = 62
      Width = 116
      Height = 20
      Color = clInfoBk
      MaxLength = 9
      ReadOnly = False
      TabOrder = 9
      Text = '<��ѯ.��������>'
      WorkView = WorkView1
      FieldName = '��ѯ.��������'
    end
    object WVComboBox1: TWVComboBox
      Left = 252
      Top = 38
      Width = 116
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView1
      FieldName = '��ѯ.�Ա�'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*202'
    end
    object WVEdit9: TWVEdit
      Left = 420
      Top = 14
      Width = 107
      Height = 20
      Color = clInfoBk
      MaxLength = 9
      ReadOnly = False
      TabOrder = 2
      Text = '<��ѯ.����>'
      WorkView = WorkView1
      FieldName = '��ѯ.����'
    end
    object cbbIDType: TWVComboBox
      Left = 252
      Top = 14
      Width = 116
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 1
      WorkView = WorkView1
      FieldName = '��ѯ.֤������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*201'
    end
    object WVEdit15: TWVEdit
      Left = 420
      Top = 38
      Width = 107
      Height = 20
      Color = clInfoBk
      MaxLength = 9
      ReadOnly = False
      TabOrder = 6
      Text = '<��ѯ.�绰>'
      WorkView = WorkView1
      FieldName = '��ѯ.�绰'
    end
    object WVEdit11: TWVEdit
      Left = 597
      Top = 14
      Width = 139
      Height = 20
      Color = clInfoBk
      MaxLength = 9
      ReadOnly = False
      TabOrder = 3
      Text = '<��ѯ.֤������>'
      WorkView = WorkView1
      FieldName = '��ѯ.֤������'
    end
    object WVEdit16: TWVEdit
      Left = 597
      Top = 38
      Width = 139
      Height = 20
      Color = clInfoBk
      MaxLength = 9
      ReadOnly = False
      TabOrder = 7
      Text = '<��ѯ.�ֻ�>'
      WorkView = WorkView1
      FieldName = '��ѯ.�ֻ�'
    end
    object WVEdit1: TWVEdit
      Left = 420
      Top = 61
      Width = 107
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 10
      Text = '<��ѯ.����>'
      WorkView = WorkView1
      FieldName = '��ѯ.����'
    end
    object WVEdit2: TWVEdit
      Left = 597
      Top = 61
      Width = 139
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 11
      Text = '<Ӧ�����к�>'
      WorkView = WorkView1
      FieldName = 'Ӧ�����к�'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 105
    Width = 811
    Height = 354
    inherited Grid: TRzDBGrid
      Width = 811
      Height = 354
      OnCellClick = GridCellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ���'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ӧ�����к�'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sroom_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������Ч����(��)'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ԥ����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sroom_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֤������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spager'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֤������'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Ա�'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�绰'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ֻ�'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'semail'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��λ����'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Ļ��̶�'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ò'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������Դ'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ʩ'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snation_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_addr'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������ڵ�����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������ڵ�'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ס����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'vsvarstr2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ס��ַ'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ס����'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�״ε��ﱾ������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'smarket_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Ƿ�ɾ��'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstock_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ɾ������'
          Width = 60
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
        Name = '�ͻ���'
        Caption = '�ͻ���'
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
        Name = 'Ԥ����'
        Caption = 'Ԥ����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Constrained = True
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|������־|�ͻ���|Ԥ����|'
      end>
    Left = 164
    Top = 223
  end
  inherited MainRequest: TWVRequest
    ID = '�ɷ��쿨'
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
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '�ͻ���'
        FieldName = '�ͻ���'
      end
      item
        ParamName = 'Ԥ����'
        FieldName = 'Ԥ����'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end>
    Left = 200
    Top = 224
  end
  inherited WVDBBinder: TWVDBBinder
    WorkView = WorkView1
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sroom_no'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '201'
      end
      item
        FieldName = 'sstatus0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '200'
      end
      item
        FieldName = 'scust_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '202'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '203'
      end
      item
        FieldName = 'sstatus2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '204'
      end
      item
        FieldName = 'sstatus3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '205'
      end
      item
        FieldName = 'sstatus4'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '206'
      end
      item
        FieldName = 'sserial0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '207'
      end
      item
        FieldName = 'snation_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '208'
      end
      item
        FieldName = 'sserial1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '209'
      end
      item
        FieldName = 'sserial2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '211'
      end
      item
        FieldName = 'sserial3'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '212'
      end
      item
        FieldName = 'smarket_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '213'
      end
      item
        FieldName = 'sroom_no2'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '210'
      end>
    Left = 240
    Top = 280
  end
  inherited DataSource: TDataSource
    Left = 272
    Top = 280
  end
  object QueryRequest: TWVRequest
    WorkView = WorkView1
    ID = '�ͻ���Ϣά����ѯ'
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
        ParamName = '������־'
        FieldName = '������־'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '����״̬'
        FieldName = '��ѯ.����״̬'
      end
      item
        ParamName = '����'
        FieldName = '��ѯ.����'
      end
      item
        ParamName = '֤������'
        FieldName = '��ѯ.֤������'
      end
      item
        ParamName = '֤������'
        FieldName = '��ѯ.֤������'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '�Ա�'
        FieldName = '��ѯ.�Ա�'
      end
      item
        ParamName = '�绰'
        FieldName = '��ѯ.�绰'
      end
      item
        ParamName = '�ֻ�'
        FieldName = '��ѯ.�ֻ�'
      end
      item
        ParamName = '��������'
        FieldName = '��ѯ.��������'
      end
      item
        ParamName = '����'
        FieldName = '��ѯ.����'
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'Ӧ�����к�'
      end>
    Left = 208
    Top = 280
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
        GroupIndex = 1
        DataField = 'sstat_type'
      end
      item
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
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
        Name = '��ѯ.����״̬'
        Caption = '��ѯ.����״̬'
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
        Name = '��ѯ.����'
        Caption = '��ѯ.����'
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
        Name = '��ѯ.֤������'
        Caption = '��ѯ.֤������'
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
        Name = '��ѯ.֤������'
        Caption = '��ѯ.֤������'
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
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
        Name = '��ѯ.�Ա�'
        Caption = '��ѯ.�Ա�'
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
        Name = '��ѯ.�绰'
        Caption = '��ѯ.�绰'
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
        Name = '��ѯ.�ֻ�'
        Caption = '��ѯ.�ֻ�'
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
        Name = '��ѯ.��������'
        Caption = '��ѯ.��������'
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
        Name = '��ѯ.����'
        Caption = '��ѯ.����'
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
        Name = 'Ӧ�����к�'
        Caption = 'Ӧ�����к�'
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
    FieldsMonitors = <>
    Left = 168
    Top = 280
  end
  object rpt1: TRMReport
    InitialZoom = pzDefault
    PreviewButtons = [pbZoom, pbLoad, pbSave, pbPrint, pbFind, pbPageSetup, pbExit, pbSaveToXLS]
    DefaultCopies = 0
    DefaultCollate = False
    SaveReportOptions.RegistryPath = 'ReportMachine\ReportSettings\'
    Left = 240
    Top = 226
    ReportData = {}
  end
end
