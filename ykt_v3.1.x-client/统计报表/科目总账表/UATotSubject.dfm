inherited faqhTotSubject: TfaqhTotSubject
  Width = 699
  Height = 489
  inherited upnlBottom: TUIPanel
    Top = 452
    Width = 699
    TabOrder = 3
    inherited tlb1: TRzToolbar
      ToolbarControls = (
        btn100
        btnPageWidth
        rzspcr1
        btnFirst
        btnprevious
        btnNext
        btnLast
        rzspcr2
        btnExpXls
        btnPagePrint
        btnSetup
        rzspcr3
        btnDesign)
    end
    inherited btnQuery: TBitBtn
      Left = 607
    end
  end
  inherited UIPnlQueryCount: TUIPanel
    Width = 699
    inherited Image1: TImage
      Width = 699
    end
    inherited LabRecordCount: TLabel
      Visible = False
    end
  end
  object Panel1: TPanel [2]
    Left = 0
    Top = 18
    Width = 699
    Height = 28
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 1
    object Label1: TLabel
      Left = 74
      Top = 8
      Width = 48
      Height = 12
      Caption = '��ʼ����'
    end
    object Label2: TLabel
      Left = 264
      Top = 8
      Width = 48
      Height = 12
      Caption = '��������'
    end
    object cbbSubName: TWVComboBox
      Left = 56
      Top = 1000
      Width = 193
      Height = 20
      Style = csDropDownList
      Color = clWhite
      DropDownCount = 20
      ImeName = '�Ϲ�ƴ�����뷨'
      ItemHeight = 12
      TabOrder = 3
      WorkView = WorkView
      FieldName = '��ƿ�Ŀ'
      DataPresentType = 'IDOBJECTS'
      SeperatedStr = '-'
      AutoDropDown = False
      ItemsDataEntry = '*-25'
    end
    object edtBeginDate: TWVEdit
      Left = 131
      Top = 3
      Width = 120
      Height = 20
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ReadOnly = False
      TabOrder = 0
      Text = '<��ʼ����>'
      WorkView = WorkView
      FieldName = '��ʼ����'
    end
    object edtEndDate: TWVEdit
      Left = 320
      Top = 3
      Width = 120
      Height = 20
      Color = clWhite
      ImeName = '���� (����) - ΢��ƴ��'
      ReadOnly = False
      TabOrder = 1
      Text = '<��������>'
      WorkView = WorkView
      FieldName = '��������'
    end
    object chkSelectall: TCheckBox
      Left = 8
      Top = 5
      Width = 49
      Height = 17
      Caption = 'ȫѡ'
      TabOrder = 2
      OnClick = chkSelectallClick
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 46
    Width = 699
    Height = 406
    TabOrder = 2
    inherited Grid: TRzDBGrid
      Left = 193
      Width = 506
      Height = 406
      TabOrder = 2
      Columns = <
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ƿ�Ŀ'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sall_name'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��Ŀ����'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'Lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��'
          Width = 40
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��'
          Width = 20
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Lvol3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��'
          Width = 20
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'snote'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ժҪ'
          Width = 200
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���״���'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�跽������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����������'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt3'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�跽���'
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt4'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�������'
          Width = 70
          Visible = True
        end>
    end
    inherited rmprvwP: TRMPreview
      Left = 193
      Width = 506
      Height = 406
      TabOrder = 1
    end
    object rzszpnl1: TRzSizePanel
      Left = 0
      Top = 0
      Width = 193
      Height = 406
      HotSpotVisible = True
      SizeBarWidth = 7
      TabOrder = 0
      UseGradients = True
      object lvSub: TListView
        Left = 0
        Top = 0
        Width = 185
        Height = 406
        Align = alClient
        Checkboxes = True
        Columns = <
          item
            Caption = '��Ŀ��'
            Width = 60
          end
          item
            Caption = '��Ŀ����'
            Width = 120
          end>
        GridLines = True
        ReadOnly = True
        SortType = stBoth
        TabOrder = 0
        ViewStyle = vsReport
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
        Name = '��ƿ�Ŀ'
        Caption = '��ƿ�Ŀ'
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
        Name = '��ʼ����'
        Caption = '��ʼ����'
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
        Name = '��������'
        Caption = '��������'
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
        MonitorValueChangedFields = '|��ʼ����|��������|����Ա����|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end>
    Left = 92
    Top = 255
  end
  inherited MainRequest: TWVRequest
    ID = '��Ŀ���˱�'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ƿ�Ŀ'
        FieldName = '��ƿ�Ŀ'
      end
      item
        ParamName = '��������'
        FieldName = '��������'
      end
      item
        ParamName = '��ʼ����'
        FieldName = '��ʼ����'
      end>
    Left = 128
    Top = 256
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'damt1'
        DataPresentType = '����'
      end
      item
        FieldName = 'damt2'
        DataPresentType = '����'
      end
      item
        FieldName = 'damt3'
        DataPresentType = '����'
      end
      item
        FieldName = 'damt4'
        DataPresentType = '����'
      end>
    Left = 160
    Top = 256
  end
  inherited DataSource: TDataSource
    Left = 192
    Top = 256
  end
  inherited rptReport: TRMReport
    ReportData = {}
  end
  inherited rmDS: TRMDBDataSet
    DataSet = zqry1
  end
  object zqry1: TZQuery
    Connection = dmReportImp.conSLite
    SQL.Strings = (
      
        'select t1.accdate,t1.subjno,t1.subjname,t1.summary,t1.transcnt,t' +
        '1.dramt,t1.cramt,t1.drbal,t1.crbal'
      'from  t_rptsubjledger t1'
      'order by t1.accdate desc ,t1.subjno asc')
    Params = <>
    Left = 291
    Top = 129
  end
end
