inherited faqhwaterTrans_cqcsgl: TfaqhwaterTrans_cqcsgl
  Width = 700
  Height = 552
  inherited UIPanel1: TUIPanel
    Top = 516
    Width = 700
    Height = 36
    TabOrder = 3
    object rzstspnStat: TRzStatusPane [0]
      Left = 0
      Top = 12
      Width = 700
      Height = 24
      FrameStyle = fsStatus
      Align = alBottom
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    inherited btnQuery: TBitBtn
      Left = 96
      Top = 1000
      Width = 90
      Caption = '������Ϣ(&R)'
      TabOrder = 1
      Visible = False
      Glyph.Data = {00000000}
    end
    inherited btnPrint: TBitBtn
      Left = 10
      Top = 1000
      TabOrder = 0
      Visible = False
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 700
    inherited Image1: TImage
      Width = 700
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 700
    Height = 498
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Align = alNone
      Columns = <
        item
          Expanded = False
          FieldName = 'Lvol0'
          PickList.Strings = ()
          Title.Caption = '��̨��ˮ��'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol1'
          PickList.Strings = ()
          Title.Caption = '��ˮ��̨��ˮ��'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt0'
          PickList.Strings = ()
          Title.Caption = '��Ǯ������ֵ'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Damt2'
          PickList.Strings = ()
          Title.Caption = 'СǮ������ֵ'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol9'
          PickList.Strings = ()
          Title.Caption = '��Ǯ������'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Caption = 'СǮ������'
          Visible = True
        end>
    end
  end
  object Panel1: TPanel [3]
    Left = 0
    Top = 18
    Width = 700
    Height = 498
    Align = alClient
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 184
      Top = 72
      Width = 377
      Height = 290
      Caption = '����Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object RzStatusPane3: TRzStatusPane
        Left = 13
        Top = 62
        Width = 130
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
      object RzStatusPane1: TRzStatusPane
        Left = 13
        Top = 94
        Width = 130
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
      object RzStatusPane2: TRzStatusPane
        Left = 13
        Top = 126
        Width = 130
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
      object RzStatusPane4: TRzStatusPane
        Left = 13
        Top = 158
        Width = 130
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'ת��ǰ��Ǯ�����'
      end
      object RzStatusPane5: TRzStatusPane
        Left = 13
        Top = 222
        Width = 130
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'ת��ǰСǮ�����'
      end
      object rzstspn1: TRzStatusPane
        Left = 13
        Top = 30
        Width = 130
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '������'
      end
      object rzstspn2: TRzStatusPane
        Left = 13
        Top = 190
        Width = 130
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'ת�˺��Ǯ�����'
      end
      object rzstspn3: TRzStatusPane
        Left = 13
        Top = 254
        Width = 130
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'ת�˺�СǮ�����'
      end
      object edtsmlMoney: TWVEdit
        Left = 148
        Top = 223
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 6
      end
      object edtMoney: TWVEdit
        Left = 148
        Top = 159
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 4
      end
      object edtStuempNo: TWVEdit
        Left = 148
        Top = 127
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 3
      end
      object edtName: TWVEdit
        Left = 148
        Top = 95
        Width = 157
        Height = 22
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentColor = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
      end
      object edtCardNo: TWVEdit
        Left = 148
        Top = 63
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
      end
      object edtPhyId: TWVEdit
        Left = 148
        Top = 31
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
      end
      object edtAfterMoney: TWVEdit
        Left = 148
        Top = 191
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 5
      end
      object edtAfterSmlMoney: TWVEdit
        Left = 148
        Top = 255
        Width = 157
        Height = 22
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 7
      end
    end
    object grp1: TGroupBox
      Left = 184
      Top = 368
      Width = 377
      Height = 57
      Caption = 'ת����Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      object RzStatusPane6: TRzStatusPane
        Left = 13
        Top = 25
        Width = 130
        Height = 24
        FrameStyle = fsStatus
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'ת�˽��'
      end
      object edtAddMoney: TWVEdit
        Left = 148
        Top = 25
        Width = 157
        Height = 22
        Color = clBtnHighlight
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = '����'
        Font.Style = []
        MaxLength = 22
        ParentFont = False
        ReadOnly = False
        TabOrder = 0
        OnKeyPress = edtAddMoneyKeyPress
      end
    end
    object btnTran: TBitBtn
      Left = 471
      Top = 437
      Width = 90
      Height = 25
      Hint = '��ѯ/ˢ������'
      Caption = 'ת��(&T)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnTranClick
    end
    object btnReadCard: TButton
      Left = 352
      Top = 437
      Width = 90
      Height = 25
      Caption = '������Ϣ(&R)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnReadCardClick
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
      end
      item
        Name = '�ն˺�'
        Caption = '�ն˺�'
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
        Name = 'ʱ���'
        Caption = 'ʱ���'
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
        Name = '���ײο���'
        Caption = '���ײο���'
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
        Name = '�����'
        Caption = '�����'
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
          '|���׿���|��ֵ���|����Ա����|��Ǯ�����|��Ǯ������|СǮ������|' +
          'СǮ�����|'
      end>
    Left = 36
    Top = 231
  end
  inherited MainRequest: TWVRequest
    ID = '���ײο���_cqcsgl'
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
        ParamName = '�ն˺�'
        FieldName = '�ն˺�'
      end
      item
        ParamName = 'ʱ���'
        FieldName = 'ʱ���'
      end
      item
        ParamName = '���ײο���'
        FieldName = '���ײο���'
        Direction = bdParam2Field
      end
      item
        ParamName = '�����'
        FieldName = '�����'
        Direction = bdParam2Field
      end>
    Left = 80
    Top = 232
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Left = 80
    Top = 264
  end
  inherited DataSource: TDataSource
    Left = 80
    Top = 296
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
        Name = '�ն˺�'
        Caption = '�ն˺�'
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
        Name = '���ײο���'
        Caption = '���ײο���'
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
        Name = 'СǮ�����'
        Caption = 'СǮ�����'
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
        Name = 'ת�˽��'
        Caption = 'ת�˽��'
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
        Name = '֧������'
        Caption = '֧������'
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
        Name = '�ն���ˮ��'
        Caption = '�ն���ˮ��'
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
        Name = '����ֵ'
        Caption = '����ֵ'
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
        Name = '�ۿ���'
        Caption = '�ۿ���'
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
        Name = '��д���'
        Caption = '��д���'
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
        Name = 'СǮ�����'
        Caption = 'СǮ�����'
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
        MonitorValueChangedFields = '|�ͻ���|ѧ����|����|����|���֤��|'
      end>
    Left = 44
    Top = 151
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = 'ˮ��ת��_cqcsgl'
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
        ParamName = '�ն˺�'
        FieldName = '�ն˺�'
      end
      item
        ParamName = '���ײο���'
        FieldName = '���ײο���'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
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
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '���״���'
        FieldName = '���״���'
      end
      item
        ParamName = 'СǮ�����'
        FieldName = 'СǮ�����'
      end
      item
        ParamName = 'ת�˽��'
        FieldName = 'ת�˽��'
      end
      item
        ParamName = '֧������'
        FieldName = '֧������'
      end
      item
        ParamName = '�ն���ˮ��'
        FieldName = '�ն���ˮ��'
        Direction = bdParam2Field
      end
      item
        ParamName = '��������'
        FieldName = '��������'
        Direction = bdParam2Field
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
        Direction = bdParam2Field
      end
      item
        ParamName = '����ֵ'
        FieldName = '����ֵ'
        Direction = bdParam2Field
      end
      item
        ParamName = '�ۿ���'
        FieldName = '�ۿ���'
        Direction = bdParam2Field
      end
      item
        ParamName = '��д���'
        FieldName = '��д���'
        Direction = bdParam2Field
      end
      item
        ParamName = 'СǮ�����'
        FieldName = 'СǮ�����'
        Direction = bdParam2Field
      end>
    AfterExec = MainRequestAfterExec
    Left = 80
    Top = 152
  end
  object WVRcashOperCancel: TWVRequest
    WorkView = WVcashOperCancel
    ID = 'ʧ����Ϣ_cqcsgl'
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
        ParamName = '���ײο���'
        FieldName = '���ײο���'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end>
    AfterExec = MainRequestAfterExec
    Left = 80
    Top = 192
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
        Name = '���ײο���'
        Caption = '���ײο���'
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
      end>
    WorkProcesses = <>
    FieldsMonitors = <>
    Left = 40
    Top = 192
  end
end
