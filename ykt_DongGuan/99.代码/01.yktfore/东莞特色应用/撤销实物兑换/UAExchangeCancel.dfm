inherited faqExchangeCancel: TfaqExchangeCancel
  Width = 712
  Height = 547
  inherited UIPanel1: TUIPanel
    Top = 520
    Width = 712
    Height = 27
    object rzstspnInfo: TRzStatusPane [0]
      Left = 0
      Top = 4
      Width = 712
      Height = 23
      FrameStyle = fsStatus
      Align = alBottom
      Font.Charset = GB2312_CHARSET
      Font.Color = clRed
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
    end
    inherited btnQuery: TBitBtn
      Left = 536
      Top = 1000
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 622
      Top = 1000
      Caption = '���´�ӡ'
      Visible = False
      Glyph.Data = {00000000}
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 712
    inherited Image1: TImage
      Width = 712
    end
    inherited LabRecordCount: TLabel
      Visible = False
    end
  end
  inherited UIPanel2: TUIPanel
    Width = 712
    Height = 502
    object Label1: TLabel [0]
      Left = 144
      Top = 48
      Width = 385
      Height = 16
      AutoSize = False
      Caption = '��ʾ��ֻ�ܳ������һ�ʳɹ��Ľ��ף������������'
      Font.Charset = GB2312_CHARSET
      Font.Color = clRed
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    inherited Grid: TRzDBGrid
      Left = 208
      Top = 1000
      Width = 233
      Height = 113
      Align = alNone
      Visible = False
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ���'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sroom_no2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sroom_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֤������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'spager'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '֤������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sphone'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�绰'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sphone2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ֻ�'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'scard0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sphone3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'Ӧ�����к�'
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sorder0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��Ƭ�汾'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sdate1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ƿ�����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������κ�'
          Width = 70
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
          FieldName = 'sdate3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���ɱ���'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���˻����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ʵ�����'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ֵ�ܽ��'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'damt4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����ܽ��'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ֵ����'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���Ѵ���'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol6'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ֵ�ܱ���'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol7'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����ܱ���'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol8'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '������ն˺�'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'stime0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�����ʱ��'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sstatus0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ֵд��ʧ�ܱ�־'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol9'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ʧ��־'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'semp_pwd'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ʧ����'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'semp_pwd2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ʧ��Ч����'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sstock_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ɾ������'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'smarket_code'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ɾ����־'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����ʱ��'
          Visible = False
        end>
    end
    object rgExType: TRzRadioGroup
      Left = 144
      Top = 248
      Width = 433
      Height = 77
      BevelWidth = 3
      Caption = 'ʵ��һ����'
      Columns = 2
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = '����'
      Font.Style = []
      ItemHeight = 25
      ItemIndex = 0
      Items.Strings = (
        'ˢ���һ�'
        '���Ŷһ�')
      ParentFont = False
      TabOrder = 1
      OnClick = rgExTypeClick
      object Label2: TLabel
        Left = 8
        Top = 49
        Width = 80
        Height = 16
        AutoSize = False
        Caption = '�������ݣ�'
      end
      object edtMInfo: TEdit
        Left = 88
        Top = 45
        Width = 217
        Height = 24
        ReadOnly = True
        TabOrder = 0
      end
    end
    object RzGroupBox1: TRzGroupBox
      Left = 144
      Top = 72
      Width = 433
      Height = 171
      Caption = '�������׷�����Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      object lbl1: TLabel
        Left = 8
        Top = 24
        Width = 80
        Height = 16
        AutoSize = False
        Caption = '�ֻ����룺'
      end
      object lbl2: TLabel
        Left = 8
        Top = 56
        Width = 80
        Height = 16
        AutoSize = False
        Caption = 'ԭ��ˮ�ţ�'
      end
      object lbl3: TLabel
        Left = 8
        Top = 88
        Width = 80
        Height = 16
        AutoSize = False
        Caption = 'ƽ̨��ˮ��'
      end
      object lbl4: TLabel
        Left = 8
        Top = 120
        Width = 80
        Height = 16
        AutoSize = False
        Caption = '֧����Ϣ��'
      end
      object lblPhone: TLabel
        Left = 88
        Top = 24
        Width = 337
        Height = 16
        AutoSize = False
        Caption = '�ֻ����룺'
      end
      object lblOldSerial: TLabel
        Left = 88
        Top = 56
        Width = 337
        Height = 16
        AutoSize = False
        Caption = '�ֻ����룺'
      end
      object lblTradeSerial: TLabel
        Left = 88
        Top = 88
        Width = 337
        Height = 16
        AutoSize = False
        Caption = '�ֻ����룺'
      end
      object lblInfo: TLabel
        Left = 88
        Top = 120
        Width = 337
        Height = 48
        AutoSize = False
        Caption = 
          '�ֻ����룺�ֻ����룺�ֻ����룺�ֻ����룺�ֻ����룺�ֻ����룺�ֻ�' +
          '���룺�ֻ����룺�ֻ����룺�ֻ����룺�ֻ����룺�ֻ����룺�ֻ�����' +
          '���ֻ����룺�ֻ����룺�ֻ����룺�ֻ����룺�ֻ����룺�ֻ����룺��' +
          '�����룺�ֻ����룺�ֻ����룺�ֻ����룺�ֻ����룺�ֻ����룺�ֻ���' +
          '�룺�ֻ����룺�ֻ����룺�ֻ����룺�ֻ����룺�ֻ����룺�ֻ����룺' +
          '�ֻ����룺�ֻ����룺�ֻ����룺�ֻ����룺'
        WordWrap = True
      end
    end
    object btnPayFee: TBitBtn
      Left = 456
      Top = 337
      Width = 119
      Height = 29
      Hint = '���׳���'
      Caption = '����ʵ��һ�'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnPayFeeClick
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
        Name = '���'
        Caption = '���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.DefaultValid = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|�ͻ���|����|֤������|֤������|��������|�绰|�ֻ�|����|�������' +
          '��|������|�ƿ�����|�������κ�|'
      end>
    InvalidColor = clWhite
    Left = 4
    Top = 65535
  end
  inherited MainRequest: TWVRequest
    ID = '�˻���Ϣ��ѯ'
    Bindings = <
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
        ParamName = '֤������'
        FieldName = '֤������'
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '�绰'
        FieldName = '�绰'
      end
      item
        ParamName = '�ֻ�'
        FieldName = '�ֻ�'
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
        ParamName = '�ƿ�����'
        FieldName = '�ƿ�����'
      end
      item
        ParamName = '�����к�'
        FieldName = '�����к�'
      end
      item
        ParamName = '��״̬'
        FieldName = '��״̬'
        DefaultValue = 0
      end
      item
        ParamName = '��ѯ���'
        FieldName = '��ѯ���'
      end>
    Left = 40
    Top = 0
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sroom_no2'
        DataPresentType = 'idobjects'
        DataPresentParam = '210'
      end
      item
        FieldName = 'sroom_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '201'
      end
      item
        FieldName = 'lvol1'
        DataPresentType = 'idobjects'
        DataPresentParam = '-1'
      end
      item
        FieldName = 'lvol3'
        DataPresentType = 'idobjects'
        DataPresentParam = '-4'
      end
      item
        FieldName = 'lvol9'
        DataPresentType = 'idobjects'
        DataPresentParam = '225'
      end>
    Left = 72
    Top = 0
  end
  inherited DataSource: TDataSource
    Left = 104
    Top = 0
  end
  object idhtp1: TIdHTTP
    MaxLineAction = maException
    AllowCookies = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.ContentRangeEnd = 0
    Request.ContentRangeStart = 0
    Request.Accept = 'text/html, */*'
    Request.BasicAuthentication = False
    Request.UserAgent = 'Mozilla/3.0 (compatible; Indy Library)'
    HTTPOptions = [hoForceEncodeParams]
    Left = 144
  end
end
