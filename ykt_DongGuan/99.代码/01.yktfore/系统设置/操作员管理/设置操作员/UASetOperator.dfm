inherited faqhSetOperator: TfaqhSetOperator
  Width = 680
  Height = 477
  Caption = '���ò���Ա'
  inherited pcPages: TRzPageControl
    Width = 680
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 424
        Width = 676
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 415
          Enabled = False
        end
        inherited btnChange: TBitBtn [1]
          Left = 501
          Enabled = False
        end
        inherited btnQuery: TBitBtn [2]
        end
        inherited btnDelete: TBitBtn
          Left = 587
          Caption = 'ע��(&D)'
          Enabled = False
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 96
          Width = 169
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 676
        Align = alNone
        TabOrder = 1
      end
      inherited Grid: TRzDBGrid
        Top = 33
        Width = 676
        Height = 391
        ReadOnly = True
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'sstatus2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����Ա����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_no'
            PickList.Strings = ()
            Title.Caption = '����Ա����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname'
            PickList.Strings = ()
            Title.Caption = '����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type2'
            PickList.Strings = ()
            Title.Caption = '���������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'damt0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ֵ�޶�'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sphone'
            PickList.Strings = ()
            Title.Caption = '�绰'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sphone2'
            PickList.Strings = ()
            Title.Caption = '�ֻ�'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semail'
            PickList.Strings = ()
            Title.Caption = '�����ʼ�'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Caption = '��ַ'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'spost_code'
            PickList.Strings = ()
            Title.Caption = '�ʱ�'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus1'
            PickList.Strings = ()
            Title.Caption = '�Ƿ�����վ��'
            Width = 94
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sstatus2'
            PickList.Strings = ()
            Title.Caption = '�Ƿ����Ʒ���'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sstatus3'
            PickList.Strings = ()
            Title.Caption = '״̬'
            Width = 53
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lwithdraw_flag'
            PickList.Strings = ()
            Title.Caption = '��¼վ��'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Sstatus4'
            PickList.Strings = ()
            Title.Caption = '����Ա��¼״̬'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��ѯȨ��'
            Width = 80
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 676
        Height = 33
        Align = alTop
        ParentColor = True
        TabOrder = 0
        object Labeloper_code1: TLabel
          Left = 190
          Top = 10
          Width = 60
          Height = 12
          Caption = '����Ա����'
          Visible = False
        end
        object Label5: TLabel
          Left = 14
          Top = 10
          Width = 24
          Height = 12
          Caption = '״̬'
        end
        object WVComboBox1: TWVComboBox
          Left = 261
          Top = 5
          Width = 116
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          MaxLength = 8
          TabOrder = 0
          Text = '<��ѯ.����Ա����>'
          Visible = False
          WorkView = WorkView
          FieldName = '��ѯ.����Ա����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-30'
        end
        object WVComboBox3: TWVComboBox
          Left = 45
          Top = 5
          Width = 116
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 0
          MaxLength = 8
          TabOrder = 1
          Text = '<��ѯ.״̬>'
          WorkView = WorkView
          FieldName = '��ѯ.״̬'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*62'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 676
        TabOrder = 2
        inherited btnOK: TBitBtn
          Left = 500
        end
        inherited btnCancel: TBitBtn
          Left = 588
        end
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 436
        Height = 418
        Align = alLeft
        BevelOuter = bvNone
        ParentColor = True
        TabOrder = 0
        object Labelemail8: TLabel
          Left = 226
          Top = 188
          Width = 48
          Height = 12
          Caption = '�����ʼ�'
        end
        object Labeladdr6: TLabel
          Left = 249
          Top = 229
          Width = 24
          Height = 12
          Caption = '�ʱ�'
        end
        object Labelphone4: TLabel
          Left = 41
          Top = 189
          Width = 24
          Height = 12
          Caption = '�绰'
        end
        object lblpwd: TLabel
          Left = 41
          Top = 148
          Width = 24
          Height = 12
          Caption = '����'
        end
        object Labeloper_name3: TLabel
          Left = 41
          Top = 69
          Width = 24
          Height = 12
          Caption = '����'
        end
        object Labeloper_code2: TLabel
          Left = 5
          Top = 29
          Width = 60
          Height = 12
          Caption = '����Ա����'
        end
        object Labelif_station9: TLabel
          Left = 226
          Top = 70
          Width = 48
          Height = 12
          Caption = '����վ��'
        end
        object Labelif_access10: TLabel
          Left = 18
          Top = 307
          Width = 48
          Height = 12
          Caption = '��ѯȨ��'
        end
        object lblrepwd: TLabel
          Left = 226
          Top = 148
          Width = 48
          Height = 12
          Caption = '����У��'
        end
        object Labelmobile5: TLabel
          Left = 41
          Top = 229
          Width = 24
          Height = 12
          Caption = '�ֻ�'
        end
        object Label1: TLabel
          Left = 238
          Top = 109
          Width = 36
          Height = 12
          Caption = '�����'
        end
        object Label2: TLabel
          Left = 41
          Top = 109
          Width = 24
          Height = 12
          Caption = '����'
        end
        object Label3: TLabel
          Left = 26
          Top = 365
          Width = 48
          Height = 12
          Caption = '��ֵ�޶�'
          Visible = False
        end
        object Label4: TLabel
          Left = 41
          Top = 269
          Width = 24
          Height = 12
          Caption = '��ַ'
        end
        object Labelmenu_set14: TLabel
          Left = 226
          Top = 27
          Width = 48
          Height = 12
          Caption = '����ģ��'
        end
        object WVEditemail8: TWVEdit
          Left = 283
          Top = 185
          Width = 136
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 9
          Text = '<�����ʼ�>'
          WorkView = WorkView
          FieldName = '�����ʼ�'
          SynchronizeWhenExit = True
        end
        object WVEditaddr6: TWVEdit
          Left = 283
          Top = 225
          Width = 136
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 11
          Text = '<�ʱ�>'
          WorkView = WorkView
          FieldName = '�ʱ�'
          SynchronizeWhenExit = True
        end
        object WVEditphone4: TWVEdit
          Left = 72
          Top = 185
          Width = 126
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 8
          Text = '<�绰>'
          WorkView = WorkView
          FieldName = '�绰'
          SynchronizeWhenExit = True
        end
        object edtPwd: TWVEdit
          Left = 72
          Top = 144
          Width = 126
          Height = 20
          Color = clBtnHighlight
          MaxLength = 6
          PasswordChar = '*'
          ReadOnly = False
          TabOrder = 7
          SynchronizeWhenExit = True
        end
        object WVEditoper_name3: TWVEdit
          Left = 72
          Top = 65
          Width = 126
          Height = 20
          Hint = '��ĸ�����֣�����10λ������32λ'
          Color = clInfoBk
          MaxLength = 32
          ReadOnly = False
          TabOrder = 3
          Text = '<����Ա����>'
          WorkView = WorkView
          FieldName = '����Ա����'
          SynchronizeWhenExit = True
        end
        object WVEditoper_code2: TWVEdit
          Left = 72
          Top = 25
          Width = 126
          Height = 20
          Hint = '��ĸ�����֣�����10λ'
          Color = clInfoBk
          MaxLength = 11
          ReadOnly = False
          TabOrder = 1
          Text = '<����Ա����>'
          WorkView = WorkView
          FieldName = '����Ա����'
          SynchronizeWhenExit = True
        end
        object WVComboBoxif_station9: TWVComboBox
          Left = 283
          Top = 64
          Width = 136
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 2
          WorkView = WorkView
          FieldName = '�Ƿ����Ʒ���վ��'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '2'
        end
        object WVComboBoxif_access10: TWVComboBox
          Left = 72
          Top = 303
          Width = 126
          Height = 18
          Style = csOwnerDrawFixed
          Color = clWhite
          ItemHeight = 12
          TabOrder = 13
          WorkView = WorkView
          FieldName = '��ѯ����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*245'
        end
        object edtPwdCheck: TWVEdit
          Left = 283
          Top = 143
          Width = 136
          Height = 20
          Color = 14999516
          MaxLength = 6
          PasswordChar = '*'
          ReadOnly = False
          TabOrder = 6
          OnKeyDown = edtPwdCheckKeyDown
        end
        object WVEditmobile5: TWVEdit
          Left = 72
          Top = 225
          Width = 126
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 10
          Text = '<�ֻ�>'
          WorkView = WorkView
          FieldName = '�ֻ�'
          SynchronizeWhenExit = True
        end
        object cbbNetInfo: TWVComboBox
          Left = 283
          Top = 103
          Width = 136
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 5
          WorkView = WorkView
          FieldName = '�����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-2'
        end
        object cbbType: TWVComboBox
          Left = 72
          Top = 103
          Width = 126
          Height = 18
          Style = csOwnerDrawFixed
          Color = clInfoBk
          ItemHeight = 12
          TabOrder = 4
          WorkView = WorkView
          FieldName = '����Ա����'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*108'
        end
        object edtMoneyLimit: TWVDigitalEdit
          Left = 84
          Top = 360
          Width = 133
          Height = 20
          AllowPoint = True
          AllowNegative = True
          UserSeprator = True
          Precision = 0
          MaxIntLen = 10
          Color = clInfoBk
          ParentColor = False
          TabOrder = 14
          TabStop = True
          Text = '0'
          Visible = False
          WorkView = WorkView
          FieldName = '��ֵ�޶�'
          SynchronizeByValue = True
        end
        object WVEdit1: TWVEdit
          Left = 71
          Top = 265
          Width = 347
          Height = 20
          Color = clInfoBk
          ReadOnly = False
          TabOrder = 12
          Text = '<��ַ>'
          WorkView = WorkView
          FieldName = '��ַ'
          SynchronizeWhenExit = True
        end
        object WVComboBoxmenu_set14: TWVComboBox
          Left = 283
          Top = 23
          Width = 136
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = 'Ȩ��ģ��'
          DataPresentType = 'IDOBJECTS'
          SeperatedStr = '-'
          AutoDropDown = False
          ItemsDataEntry = '*-29'
        end
      end
      object Panel3: TPanel
        Left = 436
        Top = 0
        Width = 240
        Height = 418
        Align = alClient
        BevelOuter = bvNone
        Color = 16184303
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        inline faAuth1: TfaAuth
          Width = 240
          Height = 418
          Align = alClient
          inherited TreeView: TTreeView
            Width = 240
            Height = 418
          end
          inherited ImageList: TImageList
            Left = 200
            Top = 56
          end
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 148
    Top = 351
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
        DefaultValue = '3'
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
        DefaultValue = '2'
      end
      item
        Name = '��ѯ.����Ա����'
        Caption = '��ѯ.����Ա����'
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
        Checker.Required = False
        GetPrevChar = '*'
      end
      item
        Name = '��ѯ.״̬'
        Caption = '��ѯ.״̬'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'sstatus3'
      end
      item
        Name = '����Ա����'
        Caption = '����Ա����'
        FieldType = wftUndefined
        Features.Strings = ()
        Hint = '��ĸ�����֣�����10λ'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 1
        Checker.MaxLength = 11
        Checker.AcceptOther = False
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'scust_no'
      end
      item
        Name = '����Ա����'
        Caption = '����Ա����'
        FieldType = wftUndefined
        Features.Strings = ()
        Hint = '��ĸ�����֣�����10λ������32λ'
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 1
        Checker.MaxLength = 32
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'sname'
      end
      item
        Name = '�绰'
        Caption = '�绰'
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
        DataField = 'sphone'
      end
      item
        Name = '�ֻ�'
        Caption = '�ֻ�'
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
        DataField = 'sphone2'
      end
      item
        Name = '��ַ'
        Caption = '��ַ'
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
        DataField = 'scusttypes'
      end
      item
        Name = '�ʱ�'
        Caption = '�ʱ�'
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
        DataField = 'spost_code'
      end
      item
        Name = '�����ʼ�'
        Caption = '�����ʼ�'
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
        DataField = 'semail'
      end
      item
        Name = '�Ƿ����Ʒ���վ��'
        Caption = '�Ƿ����Ʒ���վ��'
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
        DataField = 'sstatus1'
      end
      item
        Name = '����Ա״̬'
        Caption = '����Ա״̬'
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
        DataField = 'sstatus3'
      end
      item
        Name = '����Ա����'
        Caption = '����Ա����'
        FieldType = wftUndefined
        DomainName = '����Ա����*'
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 8
        Checker.LowerCase = False
        Checker.UpperCase = False
        GetPrevChar = '*'
        GroupIndex = 1
        DataField = 'stx_pwd'
      end
      item
        Name = '����Ȩ��'
        Caption = '����Ȩ��'
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
        DataField = 'usset1'
      end
      item
        Name = '�˵�Ȩ��1'
        Caption = '�˵�Ȩ��1'
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
        Name = '�˵�Ȩ��2'
        Caption = '�˵�Ȩ��2'
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
        DataField = 'vsvarstr1'
      end
      item
        Name = '�˵�Ȩ��3'
        Caption = '�˵�Ȩ��3'
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
        DataField = 'vsvarstr2'
      end
      item
        Name = '�˵�Ȩ��4'
        Caption = '�˵�Ȩ��4'
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
        DataField = 'vsvarstr3'
      end
      item
        Name = '�������'
        Caption = '�������'
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
        DataField = 'sstatus0'
      end
      item
        Name = 'Ȩ��ģ������'
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
        Name = 'Ȩ��ģ��'
        Caption = 'Ȩ��ģ��'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        OnValueChanged = WorkViewWorkFields20ValueChanged
      end
      item
        Name = '�����'
        Caption = '�����'
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
        GroupIndex = 1
        DataField = 'lbank_acc_type2'
      end
      item
        Name = '����Ա����'
        Caption = '����Ա����'
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
        GroupIndex = 1
        DataField = 'sstatus2'
      end
      item
        Name = '��ֵ�޶�'
        Caption = '��ֵ�޶�'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Constrained = True
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
        DataField = 'damt0'
      end
      item
        Name = '��ѯ����'
        Caption = '��ѯ����'
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
        DataField = 'lvol1'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.����Ա����|'
        OnValueChanged = WorkViewFieldsMonitors0ValueChanged
      end
      item
        MonitorValueChangedFields = 
          '|����Ա����|����Ա����|�绰|�ֻ�|��ַ|�ʱ�|�����ʼ�|�Ƿ����Ʒ���' +
          'վ��|����Ա״̬|����Ȩ��|'
        GroupIndex = 1
        OnValueChanged = WorkViewFieldsMonitors1ValueChanged
      end>
    Left = 24
    Top = 16
  end
  inherited QueryRequest: TWVRequest
    ID = '����Ա��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '����Ա����'
        FieldName = '��ѯ.����Ա����'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '״̬'
        FieldName = '��ѯ.״̬'
      end>
    Left = 152
    Top = 16
  end
  inherited QueryBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'sstatus1'
        WVFieldName = '�Ƿ����Ʒ���վ��'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '2'
      end
      item
        FieldName = 'sstatus3'
        WVFieldName = '����Ա״̬'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '62'
      end
      item
        FieldName = 'lcert_code'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-2'
      end
      item
        FieldName = 'sstatus2'
        WVFieldName = '����Ա����'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '108'
      end
      item
        FieldName = 'lbank_acc_type2'
        WVFieldName = '��������'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-2'
      end
      item
        FieldName = 'sstatus4'
        WVFieldName = '����Ա��¼״̬'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '111'
      end
      item
        FieldName = 'lwithdraw_flag'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-33'
      end
      item
        FieldName = 'lvol1'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '245'
      end>
    Left = 116
    Top = 351
  end
  inherited AddRequest: TWVRequest
    ID = '���ò���Ա'
    Bindings = <
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
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
        ParamName = '��ַ'
        FieldName = '��ַ'
      end
      item
        ParamName = '�ʱ�'
        FieldName = '�ʱ�'
      end
      item
        ParamName = '�����ʼ�'
        FieldName = '�����ʼ�'
      end
      item
        ParamName = '�Ƿ����Ʒ���վ��'
        FieldName = '�Ƿ����Ʒ���վ��'
      end
      item
        ParamName = '����Ա״̬'
        FieldName = '����Ա״̬'
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end
      item
        ParamName = '����Ȩ��'
        FieldName = '����Ȩ��'
      end
      item
        ParamName = '�˵�Ȩ��1'
        FieldName = '�˵�Ȩ��1'
      end
      item
        ParamName = '�˵�Ȩ��2'
        FieldName = '�˵�Ȩ��2'
      end
      item
        ParamName = '�˵�Ȩ��3'
        FieldName = '�˵�Ȩ��3'
      end
      item
        ParamName = '�˵�Ȩ��4'
        FieldName = '�˵�Ȩ��4'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
        DefaultValue = '1'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end
      item
        ParamName = '��ֵ�޶�'
        FieldName = '��ֵ�޶�'
      end
      item
        ParamName = '��ѯ����'
        FieldName = '��ѯ����'
      end>
    Left = 56
    Top = 16
  end
  inherited DeleteRequest: TWVRequest
    ID = '���ò���Ա'
    Bindings = <
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
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
        ParamName = '��ַ'
        FieldName = '��ַ'
      end
      item
        ParamName = '�ʱ�'
        FieldName = '�ʱ�'
      end
      item
        ParamName = '�����ʼ�'
        FieldName = '�����ʼ�'
      end
      item
        ParamName = '�Ƿ����Ʒ���վ��'
        FieldName = '�Ƿ����Ʒ���վ��'
      end
      item
        ParamName = '����Ա״̬'
        FieldName = '����Ա״̬'
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end
      item
        ParamName = '����Ȩ��'
        FieldName = '����Ȩ��'
      end
      item
        ParamName = '�˵�Ȩ��1'
        FieldName = '�˵�Ȩ��1'
      end
      item
        ParamName = '�˵�Ȩ��2'
        FieldName = '�˵�Ȩ��2'
      end
      item
        ParamName = '�˵�Ȩ��3'
        FieldName = '�˵�Ȩ��3'
      end
      item
        ParamName = '�˵�Ȩ��4'
        FieldName = '�˵�Ȩ��4'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
        DefaultValue = '3'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end
      item
        ParamName = '��ֵ�޶�'
        FieldName = '��ֵ�޶�'
      end
      item
        ParamName = '��ѯ����'
        FieldName = '��ѯ����'
        DefaultValue = 0
      end>
    Left = 88
    Top = 16
  end
  inherited ChangeRequest: TWVRequest
    ID = '���ò���Ա'
    Bindings = <
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
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
        ParamName = '��ַ'
        FieldName = '��ַ'
      end
      item
        ParamName = '�ʱ�'
        FieldName = '�ʱ�'
      end
      item
        ParamName = '�����ʼ�'
        FieldName = '�����ʼ�'
      end
      item
        ParamName = '�Ƿ����Ʒ���վ��'
        FieldName = '�Ƿ����Ʒ���վ��'
      end
      item
        ParamName = '����Ա״̬'
        FieldName = '����Ա״̬'
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end
      item
        ParamName = '����Ȩ��'
        FieldName = '����Ȩ��'
      end
      item
        ParamName = '�˵�Ȩ��1'
        FieldName = '�˵�Ȩ��1'
      end
      item
        ParamName = '�˵�Ȩ��2'
        FieldName = '�˵�Ȩ��2'
      end
      item
        ParamName = '�˵�Ȩ��3'
        FieldName = '�˵�Ȩ��3'
      end
      item
        ParamName = '�˵�Ȩ��4'
        FieldName = '�˵�Ȩ��4'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
        DefaultValue = '2'
      end
      item
        ParamName = '�����'
        FieldName = '�����'
      end
      item
        ParamName = '��ֵ�޶�'
        FieldName = '��ֵ�޶�'
      end
      item
        ParamName = '����Ա����'
        FieldName = '����Ա����'
      end
      item
        ParamName = '��ѯ����'
        FieldName = '��ѯ����'
      end>
    Left = 120
    Top = 16
  end
  inherited WVDataSource: TWVDataSource
    Left = 420
    Top = 23
  end
  inherited alDatasetActions: TActionList
    Left = 180
    Top = 348
  end
  object QryModuleAuth: TWVRequest
    WorkView = WorkView
    ID = 'Ȩ��ģ���ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = 'Ȩ��ģ������'
        Direction = bdParam2Field
      end
      item
        ParamName = 'ģ�����'
        FieldName = 'Ȩ��ģ��'
      end>
    AfterExec = CheckReturnData
    Left = 464
    Top = 24
  end
  object DataSource1: TDataSource
    Left = 532
    Top = 23
  end
  object WVDBBinder1: TWVDBBinder
    DataSource = DataSource1
    WorkView = WorkView
    FieldName = 'Ȩ��ģ������'
    Bindings = <>
    HideUnbindingFields = False
    Left = 500
    Top = 23
  end
end
