inherited faqhReturnMoney: TfaqhReturnMoney
  Width = 700
  Height = 426
  inherited UIPanel1: TUIPanel
    Top = 374
    Width = 700
    Height = 52
    object RzStatusPane2: TRzStatusPane [0]
      Left = 0
      Top = 31
      Width = 700
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
    object lbl1: TLabel [1]
      Left = 16
      Top = 11
      Width = 57
      Height = 12
      AutoSize = False
      Caption = '����ԭ��'
    end
    inherited btnQuery: TBitBtn
      Left = 443
    end
    inherited btnPrint: TBitBtn
      Left = 530
      Hint = '��ֵ����'
      Caption = '��ֵ����'
      Glyph.Data = {00000000}
    end
    object btnReadCard: TBitBtn
      Left = 355
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
      TabOrder = 2
      OnClick = btnReadCardClick
    end
    object chkPrint: TCheckBox
      Left = 240
      Top = 8
      Width = 73
      Height = 17
      Caption = '��ӡ��ִ'
      Checked = True
      State = cbChecked
      TabOrder = 3
      Visible = False
    end
    object btnRePrint: TBitBtn
      Left = 618
      Top = 3
      Width = 79
      Height = 25
      Hint = '��ֵ����'
      Anchors = [akTop, akRight]
      Caption = '�ش��ִ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btnRePrintClick
    end
    object edtReason: TWVEdit
      Left = 68
      Top = 7
      Width = 153
      Height = 20
      Color = clWhite
      ReadOnly = False
      TabOrder = 5
      Text = '<��ע>'
      WorkView = WVRtnMoney
      FieldName = '��ע'
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    inherited Image1: TImage
      Width = 700
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 700
    Height = 79
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 3
    object Label1: TLabel
      Left = 42
      Top = 9
      Width = 48
      Height = 12
      Caption = '��ʼ����'
    end
    object Label2: TLabel
      Left = 242
      Top = 9
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object Label3: TLabel
      Left = 254
      Top = 57
      Width = 36
      Height = 12
      Caption = '����Ա'
    end
    object Label4: TLabel
      Left = 30
      Top = 33
      Width = 60
      Height = 12
      Caption = 'Ӧ�����к�'
    end
    object Label5: TLabel
      Left = 266
      Top = 33
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label6: TLabel
      Left = 414
      Top = 33
      Width = 60
      Height = 12
      Caption = '��������'
    end
    object Label7: TLabel
      Left = 438
      Top = 9
      Width = 36
      Height = 12
      Caption = '������'
    end
    object Label13: TLabel
      Left = 54
      Top = 57
      Width = 36
      Height = 12
      Caption = '������'
    end
    object edtBeginDate: TWVEdit
      Left = 100
      Top = 5
      Width = 118
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 0
      Text = '<��ʼ����>'
      WorkView = WorkView
      FieldName = '��ʼ����'
    end
    object edtEndDate: TWVEdit
      Left = 300
      Top = 5
      Width = 112
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 1
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object edtAppSerialNo: TWVEdit
      Left = 100
      Top = 29
      Width = 118
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 2
      Text = '<Ӧ�����к�>'
      WorkView = WorkView
      FieldName = 'Ӧ�����к�'
    end
    object edtCardNo: TWVEdit
      Left = 300
      Top = 29
      Width = 112
      Height = 20
      Color = clInfoBk
      MaxLength = 22
      ReadOnly = False
      TabOrder = 3
      Text = '<����>'
      WorkView = WorkView
      FieldName = '����'
    end
    object WVEdit6: TWVEdit
      Left = 484
      Top = 29
      Width = 112
      Height = 20
      Color = clInfoBk
      ReadOnly = False
      TabOrder = 4
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object cbbIDType: TWVComboBox
      Left = 484
      Top = 5
      Width = 112
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 5
      WorkView = WorkView
      FieldName = '������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-1'
    end
    object WVComboBox3: TWVComboBox
      Left = 100
      Top = 53
      Width = 117
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 20
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 6
      WorkView = WorkView
      FieldName = '������'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-15'
    end
    object WVComboBox1: TWVComboBox
      Left = 300
      Top = 53
      Width = 112
      Height = 20
      Style = csDropDownList
      Color = clInfoBk
      DropDownCount = 20
      ImeName = '���� (����) - ΢��ƴ��'
      ItemHeight = 12
      TabOrder = 7
      WorkView = WorkView
      FieldName = '����Ա��'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-21'
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 97
    Width = 700
    Height = 277
    inherited Grid: TRzDBGrid
      Width = 700
      Height = 277
      Columns = <
        item
          Expanded = False
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scert_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���ײο���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'stime1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lbank_acc_type2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����Ա'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����Ա��ˮ��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ֵǰ����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol6'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ǰ����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���׽��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ǰ�����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���׺����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�˻����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'spost_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���״���'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lsafe_level'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ӧ�����к�'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ն˱��'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lcert_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����״̬'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sstatus2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'д��״̬'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lsafe_level2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'vsvarstr0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ԭ��'
          Width = 80
          Visible = True
        end>
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
        Name = '��ʼ����'
        Caption = '��ʼ����'
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
      end
      item
        Name = 'Ӧ�����к�'
        Caption = 'Ӧ�����к�'
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
        Name = '����'
        Caption = '����'
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
      end
      item
        Name = '������'
        Caption = '������'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ʼ����|��������|Ӧ�����к�|����|������|'
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '��ֵ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ʼ����'
        FieldName = '��ʼ����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����Ա��'
        FieldName = '����Ա��'
        DefaultValue = ''
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'Ӧ�����к�'
      end
      item
        ParamName = '����'
        FieldName = '����'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lsafe_level'
        DataPresentType = 'idobjects'
        DataPresentParam = '-1'
      end
      item
        FieldName = 'lcert_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '-2'
      end
      item
        FieldName = 'sstatus1'
        DataPresentType = 'idobjects'
        DataPresentParam = '226'
      end
      item
        FieldName = 'sstatus2'
        DataPresentType = 'idobjects'
        DataPresentParam = '227'
      end
      item
        FieldName = 'spost_code'
        DataPresentType = 'idobjects'
        DataPresentParam = '-8'
      end
      item
        FieldName = 'lvol4'
        DataPresentType = 'idobjects'
        DataPresentParam = '-7'
      end
      item
        FieldName = 'lbank_acc_type2'
        DataPresentType = 'idobjects'
        DataPresentParam = '-21'
      end>
    Left = 160
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 192
    Top = 256
  end
  object WVRtnMoney: TWorkView
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
        Name = '����ʱ��'
        Caption = '����ʱ��'
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
        Name = 'sam�ն˺�'
        Caption = 'sam�ն˺�'
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
        Name = '����ǰ��ֵ����'
        Caption = '����ǰ��ֵ����'
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
        Name = '����ǰ���Ѵ���'
        Caption = '����ǰ���Ѵ���'
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
        Name = '�ϱ�sam�ն˺�'
        Caption = '�ϱ�sam�ն˺�'
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
        Name = '�ϱ�����'
        Caption = '�ϱ�����'
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
        Name = '�ϱʽ��'
        Caption = '�ϱʽ��'
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
        Name = '�ϱ�����'
        Caption = '�ϱ�����'
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
        Name = '�ϱ�ʱ��'
        Caption = '�ϱ�ʱ��'
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
        Name = '����Ա���'
        Caption = '����Ա���'
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
        Name = '����Ա��ˮ'
        Caption = '����Ա��ˮ'
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
        Name = '����ʱ��'
        Caption = '����ʱ��'
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
        Name = '�ֻ�'
        Caption = '�ֻ�'
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
        Name = '�ο���'
        Caption = '�ο���'
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
        Name = '��ע'
        Caption = '��ע'
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
        MonitorValueChangedFields = '|��ʼ����|��������|Ӧ�����к�|����|������|'
      end>
    Left = 92
    Top = 295
  end
  object WVRRtnMoney: TWVRequest
    WorkView = WVRtnMoney
    ID = '��ֵ����'
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
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
      end
      item
        ParamName = 'sam�ն˺�'
        FieldName = 'sam�ն˺�'
        Direction = bdBiDirection
      end
      item
        ParamName = 'Ӧ�����к�'
        FieldName = 'Ӧ�����к�'
        Direction = bdBiDirection
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '����ǰ��ֵ����'
        FieldName = '����ǰ��ֵ����'
      end
      item
        ParamName = '����ǰ���Ѵ���'
        FieldName = '����ǰ���Ѵ���'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
        Direction = bdBiDirection
      end
      item
        ParamName = '�ϱ�sam�ն˺�'
        FieldName = '�ϱ�sam�ն˺�'
      end
      item
        ParamName = '�ϱ�����'
        FieldName = '�ϱ�����'
      end
      item
        ParamName = '�ϱʽ��'
        FieldName = '�ϱʽ��'
      end
      item
        ParamName = '�ϱ�����'
        FieldName = '�ϱ�����'
      end
      item
        ParamName = '�ϱ�ʱ��'
        FieldName = '�ϱ�ʱ��'
      end
      item
        ParamName = '����Ա���'
        FieldName = '����Ա���'
      end
      item
        ParamName = '����Ա��ˮ'
        FieldName = '����Ա��ˮ'
        Direction = bdBiDirection
      end
      item
        ParamName = '��������'
        FieldName = '��������'
        Direction = bdBiDirection
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
        Direction = bdBiDirection
      end
      item
        ParamName = '�����'
        FieldName = '�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ֻ�'
        FieldName = '�ֻ�'
        Direction = bdParam2Field
      end
      item
        ParamName = '����'
        FieldName = '����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ο���'
        FieldName = '�ο���'
        Direction = bdBiDirection
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��ע'
        FieldName = '��ע'
      end>
    AfterExec = MainRequestAfterExec
    Left = 128
    Top = 296
  end
end
