inherited faqhsetFillBusiInfo: TfaqhsetFillBusiInfo
  Width = 681
  Height = 477
  Caption = '��ֵ�̻���Ϣ����'
  inherited pcPages: TRzPageControl
    Width = 681
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 402
        Width = 677
        Height = 52
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 416
          Enabled = False
          TabOrder = 3
        end
        inherited btnChange: TBitBtn [1]
          Left = 502
          Enabled = False
          TabOrder = 1
        end
        inherited btnQuery: TBitBtn [2]
          Left = 330
        end
        inherited btnDelete: TBitBtn
          Left = 588
          Enabled = False
          TabOrder = 2
        end
        inherited btnViewDetail: TBitBtn
          Left = 6
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 88
        end
        object StatusBar: TRzStatusBar
          Left = 0
          Top = 31
          Width = 677
          Height = 21
          AutoStyle = False
          BorderColor = clWindow
          BorderInner = fsNone
          BorderOuter = fsNone
          BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
          BorderWidth = 0
          Color = 16184303
          FlatColor = 15458000
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlue
          Font.Height = -14
          Font.Name = '����'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 6
          object RzStatusPane1: TRzStatusPane
            Left = 0
            Top = 0
            Width = 677
            Height = 21
            FrameStyle = fsStatus
            Align = alClient
            Font.Charset = GB2312_CHARSET
            Font.Color = clBlue
            Font.Height = -14
            Font.Name = '����'
            Font.Style = [fsBold]
            ParentFont = False
          end
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 677
      end
      inherited Grid: TRzDBGrid
        Top = 73
        Width = 677
        Height = 329
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻���'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'vsvarstr0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�̻�����'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sall_name'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����������'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������֤������'
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'snote'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '������֤������'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ɱ���(%)'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Caption = '�̻�״̬'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sorder0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sorder1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ʻ����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ۼƴ�����'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ۼƴ����'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt3'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ۼ���ɽ��'
            Width = 60
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 677
        Height = 55
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Label1: TLabel
          Left = 46
          Top = 10
          Width = 48
          Height = 12
          Caption = '�̻�����'
        end
        object Label2: TLabel
          Left = 234
          Top = 10
          Width = 60
          Height = 12
          Caption = '����������'
        end
        object Label3: TLabel
          Left = 410
          Top = 10
          Width = 84
          Height = 12
          Caption = '������֤������'
        end
        object Label4: TLabel
          Left = 10
          Top = 34
          Width = 84
          Height = 12
          Caption = '������֤������'
        end
        object Label5: TLabel
          Left = 210
          Top = 34
          Width = 84
          Height = 12
          Caption = '��������ɱ���'
        end
        object Label12: TLabel
          Left = 446
          Top = 34
          Width = 48
          Height = 12
          Caption = '�̻�״̬'
        end
        object WVEdit1: TWVEdit
          Left = 100
          Top = 6
          Width = 100
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.�̻�����>'
          WorkView = WorkView
          FieldName = '��ѯ.�̻�����'
        end
        object WVEdit2: TWVEdit
          Left = 300
          Top = 6
          Width = 100
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.�̻�����������>'
          WorkView = WorkView
          FieldName = '��ѯ.�̻�����������'
        end
        object WVEdit4: TWVEdit
          Left = 100
          Top = 30
          Width = 100
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 2
          Text = '<��ѯ.�̻�֤������>'
          WorkView = WorkView
          FieldName = '��ѯ.�̻�֤������'
        end
        object WVDigitalEdit5: TWVDigitalEdit
          Left = 300
          Top = 30
          Width = 100
          Height = 20
          AllowPoint = True
          AllowNegative = True
          UserSeprator = True
          Precision = 2
          MaxIntLen = 10
          Color = clInfoBk
          ParentColor = False
          TabOrder = 3
          TabStop = True
          Text = '0'
          WorkView = WorkView
          FieldName = '��ѯ.�̻���ɱ���'
          SynchronizeByValue = True
        end
        object WVComboBox2: TWVComboBox
          Left = 499
          Top = 6
          Width = 105
          Height = 20
          Style = csDropDownList
          Color = clInfoBk
          ImeName = '�Ϲ�ƴ�����뷨'
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '��ѯ.�̻�֤������'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*87'
        end
        object cbbStatus: TWVComboBox
          Left = 499
          Top = 30
          Width = 105
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ImeName = '�Ϲ�ƴ�����뷨'
          ItemHeight = 12
          TabOrder = 5
          WorkView = WorkView
          FieldName = '��ѯ.�̻�״̬'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*15'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      object lblBusiNo: TLabel [0]
        Left = 70
        Top = 44
        Width = 36
        Height = 12
        Caption = '�̻���'
        Visible = False
      end
      object Label8: TLabel [1]
        Left = 58
        Top = 84
        Width = 48
        Height = 12
        Caption = '�̻�����'
      end
      object Label9: TLabel [2]
        Left = 46
        Top = 124
        Width = 60
        Height = 12
        Caption = '����������'
      end
      object Label10: TLabel [3]
        Left = 22
        Top = 164
        Width = 84
        Height = 12
        Caption = '������֤������'
      end
      object Label11: TLabel [4]
        Left = 22
        Top = 204
        Width = 84
        Height = 12
        Caption = '������֤������'
      end
      object Label6: TLabel [5]
        Left = 35
        Top = 244
        Width = 72
        Height = 12
        Caption = '�̻���ɱ���'
      end
      object Label7: TLabel [6]
        Left = 320
        Top = 244
        Width = 6
        Height = 12
        Caption = '%'
      end
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 677
        TabOrder = 4
        inherited btnOK: TBitBtn
          Left = 501
        end
        inherited btnCancel: TBitBtn
          Left = 589
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object edtBusiNo: TWVDigitalEdit
        Left = 118
        Top = 40
        Width = 100
        Height = 20
        AllowPoint = True
        AllowNegative = True
        UserSeprator = True
        Precision = 2
        MaxIntLen = 10
        Color = clInfoBk
        ParentColor = False
        TabOrder = 0
        TabStop = True
        Text = '0'
        Visible = False
        WorkView = WorkView
        FieldName = '�̻���'
        SynchronizeByValue = True
      end
      object WVEdit8: TWVEdit
        Left = 118
        Top = 80
        Width = 213
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 1
        Text = '<�̻�����>'
        WorkView = WorkView
        FieldName = '�̻�����'
        SynchronizeWhenExit = True
      end
      object WVEdit9: TWVEdit
        Left = 118
        Top = 120
        Width = 213
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 2
        Text = '<�̻�����������>'
        WorkView = WorkView
        FieldName = '�̻�����������'
        SynchronizeWhenExit = True
      end
      object WVEdit11: TWVEdit
        Left = 118
        Top = 200
        Width = 213
        Height = 20
        Color = clInfoBk
        ReadOnly = False
        TabOrder = 3
        Text = '<�̻�֤������>'
        WorkView = WorkView
        FieldName = '�̻�֤������'
        SynchronizeWhenExit = True
      end
      object WVComboBox1: TWVComboBox
        Left = 118
        Top = 158
        Width = 213
        Height = 20
        Style = csDropDownList
        Color = clInfoBk
        ImeName = '�Ϲ�ƴ�����뷨'
        ItemHeight = 12
        TabOrder = 5
        WorkView = WorkView
        FieldName = '�̻�֤������'
        DataPresentType = 'IDOBJECTS'
        SeperatedStr = '-'
        AutoDropDown = False
        ItemsDataEntry = '*87'
      end
      object WVDigitalEdit1: TWVDigitalEdit
        Left = 118
        Top = 240
        Width = 195
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
        FieldName = '�̻���ɱ���'
        SynchronizeByValue = True
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 236
    Top = 199
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
        Name = '��ѯ.�̻���'
        Caption = '��ѯ.�̻���'
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
        Name = '��ѯ.�̻�����'
        Caption = '��ѯ.�̻�����'
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
        Name = '��ѯ.�̻�����������'
        Caption = '��ѯ.�̻�����������'
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
        Name = '��ѯ.�̻�֤������'
        Caption = '��ѯ.�̻�֤������'
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
        Name = '��ѯ.�̻�֤������'
        Caption = '��ѯ.�̻�֤������'
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
        Name = '��ѯ.�̻���ɱ���'
        Caption = '��ѯ.�̻���ɱ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
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
        Name = '��ѯ.�̻�״̬'
        Caption = '��ѯ.�̻�״̬'
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
        Name = '�̻���'
        Caption = '�̻���'
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
        DataField = 'lvol0'
      end
      item
        Name = '�̻�����'
        Caption = '�̻�����'
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
        DataField = 'vsvarstr0'
      end
      item
        Name = '�̻�����������'
        Caption = '�̻�����������'
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
        DataField = 'sall_name'
      end
      item
        Name = '�̻�֤������'
        Caption = '�̻�֤������'
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
        DataField = 'lvol1'
      end
      item
        Name = '�̻�֤������'
        Caption = '�̻�֤������'
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
        DataField = 'snote'
      end
      item
        Name = '�̻���ɱ���'
        Caption = '�̻���ɱ���'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'damt0'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = 
          '|��ѯ.�̻�����|��ѯ.�̻�����������|��ѯ.�̻�֤������|��ѯ.�̻�֤' +
          '������|��ѯ.�̻���ɱ���|��ѯ.����Ա��|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = '|�̻���|�̻�����|�̻�����������|�̻�֤������|�̻�֤������|'
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 152
    Top = 160
  end
  inherited QueryRequest: TWVRequest
    ID = '��ֵ�̻���ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�̻�����'
        FieldName = '��ѯ.�̻�����'
      end
      item
        ParamName = '�̻�����������'
        FieldName = '��ѯ.�̻�����������'
      end
      item
        ParamName = '�̻�֤������'
        FieldName = '��ѯ.�̻�֤������'
      end
      item
        ParamName = '�̻�֤������'
        FieldName = '��ѯ.�̻�֤������'
      end
      item
        ParamName = '�̻���ɱ���'
        FieldName = '��ѯ.�̻���ɱ���'
      end
      item
        ParamName = '�̻���'
        FieldName = '��ѯ.�̻���'
      end
      item
        ParamName = '�̻�״̬'
        FieldName = '��ѯ.�̻�״̬'
      end>
    Left = 312
    Top = 160
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lvol1'
        WVFieldName = '֤������'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '87'
      end
      item
        FieldName = 'sstatus1'
        WVFieldName = '�̻�״̬'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '15'
      end>
    Left = 196
    Top = 199
  end
  inherited AddRequest: TWVRequest
    ID = '��ֵ�̻���Ϣ����'
    Bindings = <
      item
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '�̻�����������'
        FieldName = '�̻�����������'
      end
      item
        ParamName = '�̻�֤������'
        FieldName = '�̻�֤������'
      end
      item
        ParamName = '�̻�֤������'
        FieldName = '�̻�֤������'
      end
      item
        ParamName = '�̻���ɱ���'
        FieldName = '�̻���ɱ���'
      end>
    Left = 192
    Top = 160
  end
  inherited DeleteRequest: TWVRequest
    ID = '��ֵ�̻���Ϣ����ɾ��'
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
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '�̻�����������'
        FieldName = '�̻�����������'
      end
      item
        ParamName = '�̻�֤������'
        FieldName = '�̻�֤������'
      end
      item
        ParamName = '�̻�֤������'
        FieldName = '�̻�֤������'
      end
      item
        ParamName = '�̻���ɱ���'
        FieldName = '�̻���ɱ���'
      end>
    Left = 232
    Top = 160
  end
  inherited ChangeRequest: TWVRequest
    ID = '��ֵ�̻���Ϣ�����޸�'
    Bindings = <
      item
        ParamName = '�̻���'
        FieldName = '�̻���'
      end
      item
        ParamName = '�̻�����'
        FieldName = '�̻�����'
      end
      item
        ParamName = '�̻�����������'
        FieldName = '�̻�����������'
      end
      item
        ParamName = '�̻�֤������'
        FieldName = '�̻�֤������'
      end
      item
        ParamName = '�̻�֤������'
        FieldName = '�̻�֤������'
      end
      item
        ParamName = '�̻���ɱ���'
        FieldName = '�̻���ɱ���'
      end>
    Left = 272
    Top = 160
  end
  inherited WVDataSource: TWVDataSource
    Left = 316
    Top = 199
  end
  inherited alDatasetActions: TActionList
    Left = 276
    Top = 204
  end
end
