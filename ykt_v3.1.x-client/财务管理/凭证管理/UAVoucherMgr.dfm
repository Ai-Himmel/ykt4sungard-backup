inherited faqhVoucherMgr: TfaqhVoucherMgr
  Width = 795
  Height = 477
  Caption = '�������Ȩ��'
  inherited pcPages: TRzPageControl
    Width = 795
    Height = 477
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        Top = 418
        Width = 791
        Height = 36
        TabOrder = 3
        inherited btnAdd: TBitBtn [0]
          Left = 529
          Top = 5
          Enabled = False
          TabOrder = 1
        end
        inherited btnChange: TBitBtn [1]
          Left = 616
          Top = 5
          Enabled = False
          TabOrder = 2
        end
        inherited btnQuery: TBitBtn [2]
          Left = 444
          Top = 5
          TabOrder = 0
        end
        inherited btnDelete: TBitBtn
          Left = 702
          Top = 5
          Enabled = False
          TabOrder = 3
        end
        inherited btnViewDetail: TBitBtn
          Left = 14
          Top = 1000
          TabOrder = 4
          Visible = False
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 104
          Top = 1000
          Width = 169
        end
      end
      inherited UIPnlQueryCount: TUIPanel
        Width = 791
      end
      inherited Grid: TRzDBGrid
        Top = 97
        Width = 791
        Height = 321
        TabOrder = 2
        Columns = <
          item
            Expanded = False
            FieldName = 'lvol10'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'lvol11'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sorder0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ƾ֤����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lsafe_level'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ƾ֤����'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lserial0'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ƾ֤��'
            Width = 40
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol9'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���㷽ʽ'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'sname2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�������'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�к�'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'snote'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = 'ժҪ'
            Width = 120
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lsafe_level2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���״̬'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lvol5'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����״̬'
            Width = 60
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'lbank_acc_type2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�ֹ��ʱ�־'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scust_auth'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ŀ��'
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scusttypes'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��Ŀ����'
            Width = 100
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
            FieldName = 'sorder1'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Visible = False
          end
          item
            Expanded = False
            FieldName = 'sorder2'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '��������'
            Width = 70
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'semp_no'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '�Ƶ�'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'scheck_emp'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '���'
            Width = 80
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'schange_emp'
            PickList.Strings = ()
            Title.Alignment = taCenter
            Title.Caption = '����'
            Width = 80
            Visible = True
          end>
      end
      object Panel1: TPanel
        Left = 0
        Top = 18
        Width = 791
        Height = 79
        Align = alTop
        BevelOuter = bvNone
        Color = 16184303
        TabOrder = 1
        object Label1: TLabel
          Left = 18
          Top = 9
          Width = 72
          Height = 12
          Caption = '����ڼ�(��)'
        end
        object Label3: TLabel
          Left = 218
          Top = 9
          Width = 72
          Height = 12
          Caption = '����ڼ�(��)'
        end
        object Label4: TLabel
          Left = 418
          Top = 9
          Width = 72
          Height = 12
          Caption = 'ƾ֤��ʼ����'
        end
        object Label5: TLabel
          Left = 42
          Top = 33
          Width = 48
          Height = 12
          Caption = 'ƾ֤����'
        end
        object Label6: TLabel
          Left = 254
          Top = 33
          Width = 36
          Height = 12
          Caption = 'ƾ֤��'
        end
        object Label7: TLabel
          Left = 442
          Top = 33
          Width = 48
          Height = 12
          Caption = '��Ŀ����'
        end
        object Label8: TLabel
          Left = 42
          Top = 57
          Width = 48
          Height = 12
          Caption = '���״̬'
        end
        object Label9: TLabel
          Left = 230
          Top = 57
          Width = 60
          Height = 12
          Caption = '�Ƿ��ֹ���'
        end
        object Label14: TLabel
          Left = 442
          Top = 57
          Width = 48
          Height = 12
          Caption = '����״̬'
        end
        object Label16: TLabel
          Left = 610
          Top = 9
          Width = 72
          Height = 12
          Caption = 'ƾ֤��������'
        end
        object edtYear: TWVEdit
          Left = 100
          Top = 5
          Width = 100
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 0
          Text = '<��ѯ.����ڼ�(��)>'
          WorkView = wvVQuery
          FieldName = '��ѯ.����ڼ�(��)'
        end
        object edtMonth: TWVEdit
          Left = 300
          Top = 5
          Width = 100
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 1
          Text = '<��ѯ.����ڼ�(��)>'
          WorkView = wvVQuery
          FieldName = '��ѯ.����ڼ�(��)'
        end
        object edtQBDate: TWVEdit
          Left = 500
          Top = 5
          Width = 100
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 2
          Text = '<��ѯ.ƾ֤����>'
          WorkView = wvVQuery
          FieldName = '��ѯ.ƾ֤����'
        end
        object edtVoucherNo: TWVEdit
          Left = 300
          Top = 29
          Width = 100
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 5
          Text = '<��ѯ.ƾ֤��>'
          WorkView = wvVQuery
          FieldName = '��ѯ.ƾ֤��'
        end
        object WVEdit7: TWVEdit
          Left = 500
          Top = 29
          Width = 100
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 6
          Text = '<��ѯ.��Ŀ����>'
          WorkView = wvVQuery
          FieldName = '��ѯ.��Ŀ����'
        end
        object cbbVoucherType: TWVComboBox
          Left = 100
          Top = 29
          Width = 100
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 4
          WorkView = wvVQuery
          FieldName = '��ѯ.ƾ֤����'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*-61'
        end
        object cbbStatus: TWVComboBox
          Left = 100
          Top = 53
          Width = 100
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 8
          WorkView = wvVQuery
          FieldName = '��ѯ.״̬'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*160'
        end
        object cbbManual: TWVComboBox
          Left = 300
          Top = 53
          Width = 100
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 9
          WorkView = wvVQuery
          FieldName = '��ѯ.�Ƿ��ֹ���ƾ֤'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*162'
        end
        object cbbAccTypeQ: TWVComboBox
          Left = 500
          Top = 51
          Width = 100
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 7
          WorkView = wvVQuery
          FieldName = '��ѯ.����״̬'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*161'
        end
        object edtQEDate: TWVEdit
          Left = 684
          Top = 5
          Width = 100
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 3
          Text = '<ƾ֤��������>'
          WorkView = wvVQuery
          FieldName = 'ƾ֤��������'
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      inherited UIPanel2: TUIPanel
        Top = 418
        Width = 791
        TabOrder = 5
        inherited btnOK: TBitBtn
          Left = 530
          Top = 5
          TabOrder = 0
        end
        inherited btnCancel: TBitBtn
          Left = 701
          Top = 5
        end
        inherited DBNavigator: TRzDBNavigator
          Left = 34
          Top = 1000
          Hints.Strings = ()
          TabOrder = 3
          Visible = False
        end
        object btnPrintVoucher: TBitBtn
          Left = 616
          Top = 5
          Width = 79
          Height = 25
          Hint = 'ƾ֤��ӡ'
          Anchors = [akTop, akRight]
          Caption = '��ӡ(&P)'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          OnClick = btnPrintVoucherClick
          Glyph.Data = {
            36040000424D3604000000000000360000002800000010000000100000000100
            2000000000000004000000000000000000000000000000000000FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00B5B5B500FFFFFF00FFFFFF00FFFF
            FF009C9C9C009C9C9C00A5A5A500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00B5B5B500B5B5B500DEDEDE00ADADAD00525252006B6B
            6B00ADADAD00D6D6D600E7DEDE009C9C9C00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00B5B5B500B5B5B500FFFFFF00FFFFFF00E7DEDE00B5B5B5005A5A63003131
            3100313131004A4A4A00848484009C9C9C00A5A5A500FFFFFF00A5A5A500B5B5
            B500F7F7F700FFFFFF00F7F7F700D6D6D600B5B5B500A5A5A500ADADAD009C9C
            9C007B7B7B005252520031313900313131008C8C8C00FFFFFF00B5ADAD00EFEF
            EF00EFEFEF00CECECE00BDB5B500C6C6C600D6CECE00B5B5B500ADADAD00ADA5
            A500ADADAD00ADADAD00A5A5A500848484009C9C9C00FFFFFF00ADA5AD00BDBD
            BD00B5B5B500C6C6C600D6D6D600DEDEDE00F7F7F700F7F7F700E7E7E700D6D6
            D600BDBDBD00ADADAD00ADA5A500ADADAD00A5A5A500FFFFFF00A5A5A500C6BD
            C600D6D6D600DEDEDE00D6D6D600EFEFEF00DEDEDE00B5BDB500CECECE00D6DE
            DE00DEDEDE00DEDEDE00D6D6D600C6C6C600ADADAD00FFFFFF00FFFFFF00B5AD
            AD00DEDEDE00DEDEDE00E7E7E700D6D6D600C6C6C600BDDEBD00CED6CE00D6BD
            B500BDB5B500BDBDBD00C6C6C600D6CECE00BDBDBD00FFFFFF00FFFFFF00FFFF
            FF00B5ADAD00CECECE00C6BDBD00C6C6C600EFEFEF00FFF7F700F7F7F700F7EF
            E700E7E7E700DEDEDE00C6C6C600ADA5A500FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00B5ADAD00E7E7E700D6D6D600B5B5B500CECECE00DEDEE700DEE7
            E700DEDEDE00D6D6D600C6BDBD00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00FFEFEF00FFE7DE00EFD6CE00EFD6CE00EFDED600E7DE
            DE00DEDEDE00ADADAD00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00DEB5B500FFE7DE00FFDECE00FFD6C600FFCEB500FFC6
            AD00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00DEB5B500FFE7DE00FFDECE00FFD6C600FFCEB500FFBD
            AD00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00FFFFFF00DEB5B500FFE7DE00FFDECE00FFD6C600FFCEB500FFC6
            AD00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00DEB5B500FFE7DE00FFE7DE00FFDECE00FFD6C600FFCEB500FFBD
            AD00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
            FF00FFFFFF00DEB5B500DEB5B500DEB5B500DEB5B500F7BDB500F7BDB500FFFF
            FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00}
        end
      end
      object pnlTop: TPanel
        Left = 0
        Top = 0
        Width = 791
        Height = 57
        Align = alTop
        BevelOuter = bvNone
        Color = 15458000
        TabOrder = 0
        object lbl1: TLabel
          Left = 14
          Top = 37
          Width = 56
          Height = 14
          Caption = 'ƾ֤����'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label2: TLabel
          Left = 342
          Top = 37
          Width = 56
          Height = 14
          Caption = '��������'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label10: TLabel
          Left = 454
          Top = 37
          Width = 280
          Height = 14
          Caption = '��ʾ�����֧��4�ʷ�¼������4����ȡǰ�ı�'
          Font.Charset = GB2312_CHARSET
          Font.Color = clMaroon
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label11: TLabel
          Left = 190
          Top = 35
          Width = 56
          Height = 14
          Caption = 'ƾ֤����'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object pnl1: TPanel
          Left = 0
          Top = 0
          Width = 791
          Height = 33
          Align = alTop
          BevelOuter = bvNone
          Caption = '�� �� ƾ ֤'
          Color = 15458000
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlue
          Font.Height = -20
          Font.Name = '����'
          Font.Style = [fsBold, fsUnderline]
          ParentFont = False
          TabOrder = 0
        end
        object cbbVType: TWVComboBox
          Left = 76
          Top = 33
          Width = 109
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 1
          WorkView = WorkView
          FieldName = 'ƾ֤����'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '-61'
        end
        object edtDate: TWVEdit
          Left = 252
          Top = 33
          Width = 85
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 2
          Text = '<ƾ֤����>'
          WorkView = WorkView
          FieldName = 'ƾ֤����'
        end
        object edtNum: TWVEdit
          Left = 401
          Top = 33
          Width = 46
          Height = 20
          Color = clWhite
          MaxLength = 22
          ReadOnly = False
          TabOrder = 3
          Text = '<������>'
          WorkView = WorkView
          FieldName = '������'
        end
      end
      object dbgrdh1: TDBGridEh
        Left = 0
        Top = 57
        Width = 791
        Height = 313
        Align = alClient
        DataSource = DataSource1
        EvenRowColor = clActiveCaption
        FixedColor = clActiveCaption
        Flat = True
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = '����'
        Font.Style = []
        FooterColor = clActiveCaption
        FooterFont.Charset = GB2312_CHARSET
        FooterFont.Color = clWindowText
        FooterFont.Height = -16
        FooterFont.Name = '����'
        FooterFont.Style = []
        FooterRowCount = 1
        OddRowColor = clInfoBk
        Options = [dgEditing, dgTitles, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
        OptionsEh = [dghHighlightFocus, dghClearSelection, dghEnterAsTab, dghDialogFind]
        ParentFont = False
        SumList.Active = True
        TabOrder = 1
        TitleFont.Charset = GB2312_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -14
        TitleFont.Name = '����'
        TitleFont.Style = []
        UseMultiTitle = True
        OnColEnter = dbgrdh1ColEnter
        OnColExit = dbgrdh1ColExit
        OnDrawColumnCell = dbgrdh1DrawColumnCell
        OnKeyPress = dbgrdh1KeyPress
        Columns = <
          item
            EditButtons = <>
            FieldName = 'certificate'
            Footer.Alignment = taRightJustify
            Footer.FieldName = 'certificate'
            Footer.Value = '�ϼƣ�'
            Footer.ValueType = fvtStaticText
            Footers = <>
            Title.Caption = 'ժ  Ҫ'
            Width = 200
          end
          item
            EditButtons = <>
            FieldName = 'subjno'
            Footers = <>
            Title.Caption = '��Ŀ��'
            Width = 80
          end
          item
            EditButtons = <>
            FieldName = 'subjname'
            Footers = <>
            ReadOnly = True
            Title.Caption = '��Ŀ����'
            Width = 300
          end
          item
            EditButtons = <>
            FieldName = 'debit'
            Footer.FieldName = 'debit'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = '��    ��|��  ��'
            Width = 145
          end
          item
            EditButtons = <>
            FieldName = 'credit'
            Footer.FieldName = 'credit'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = '��    ��|��  ��'
            Width = 145
          end>
      end
      object rzpnlTot: TRzPanel
        Left = 0
        Top = 370
        Width = 791
        Height = 22
        Align = alBottom
        BorderInner = fsFlat
        BorderOuter = fsFlat
        Color = clScrollBar
        TabOrder = 3
        object lblUPCASE: TLabel
          Left = 77
          Top = 5
          Width = 473
          Height = 14
          AutoSize = False
          Caption = '��д���'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlue
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object lbl4: TLabel
          Left = 8
          Top = 5
          Width = 60
          Height = 14
          AutoSize = False
          Caption = '��д��'
          Font.Charset = GB2312_CHARSET
          Font.Color = clBlue
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
      end
      object edtMoney: TsncDBCurrencyEdit
        Left = 73
        Top = 240
        Width = 98
        Height = 18
        BorderStyle = bsNone
        Ctl3D = False
        CurrencySymbol = ' '
        DataSource = DataSource1
        DigitalNumber = 12
        FocusedColor = clWhite
        KilobitSeparatorColor = clBlue
        MoveOutAllowed = True
        NegativeFont.Charset = DEFAULT_CHARSET
        NegativeFont.Color = clWindowText
        NegativeFont.Height = -13
        NegativeFont.Name = 'MS Sans Serif'
        NegativeFont.Style = []
        ParentColor = False
        ParentCtl3D = False
        TabOrder = 2
        TabStop = True
        Visible = False
        OnMoveOut = edtMoneyMoveOut
        OnEnter = edtMoneyEnter
        OnExit = edtMoneyExit
        OnKeyPress = edtMoneyKeyPress
      end
      object pnl2: TPanel
        Left = 0
        Top = 392
        Width = 791
        Height = 26
        Align = alBottom
        BevelInner = bvRaised
        BevelOuter = bvLowered
        TabOrder = 4
        object lbl2: TLabel
          Left = 200
          Top = 6
          Width = 41
          Height = 14
          AutoSize = False
          Caption = '�Ƶ���'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object lblOperName: TLabel
          Left = 240
          Top = 6
          Width = 57
          Height = 14
          AutoSize = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label12: TLabel
          Left = 344
          Top = 6
          Width = 65
          Height = 14
          AutoSize = False
          Caption = '���㷽ʽ��'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label13: TLabel
          Left = 512
          Top = 6
          Width = 65
          Height = 14
          AutoSize = False
          Caption = '������룺'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object lbl3: TLabel
          Left = 8
          Top = 6
          Width = 41
          Height = 14
          AutoSize = False
          Caption = '���ˣ�'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object lblAccount: TLabel
          Left = 40
          Top = 6
          Width = 57
          Height = 14
          AutoSize = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object Label15: TLabel
          Left = 96
          Top = 6
          Width = 41
          Height = 14
          AutoSize = False
          Caption = '��ˣ�'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object lblCheck: TLabel
          Left = 136
          Top = 6
          Width = 57
          Height = 14
          AutoSize = False
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = '����'
          Font.Style = []
          ParentFont = False
        end
        object cbbAccType: TWVComboBox
          Left = 412
          Top = 2
          Width = 93
          Height = 20
          Style = csDropDownList
          Color = clWhite
          ItemHeight = 12
          TabOrder = 0
          WorkView = WorkView
          FieldName = '���㷽ʽ'
          DataPresentType = 'IDOBJECTS'
          AutoDropDown = False
          ItemsDataEntry = '*165'
        end
        object edtAccNo: TWVEdit
          Left = 580
          Top = 3
          Width = 85
          Height = 20
          Color = clWhite
          ReadOnly = False
          TabOrder = 1
          Text = '<�������>'
          WorkView = WorkView
          FieldName = '�������'
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 236
    Top = 335
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
        Name = '��־'
        Caption = '��־'
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
        Name = '��ѯ.����ڼ�(��)'
        Caption = '��ѯ.����ڼ�(��)'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ѯ.����ڼ�(��)'
        Caption = '��ѯ.����ڼ�(��)'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ѯ.ƾ֤����'
        Caption = '��ѯ.ƾ֤����'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ѯ.ƾ֤����'
        Caption = '��ѯ.ƾ֤����'
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
        Name = '��ѯ.ƾ֤��'
        Caption = '��ѯ.ƾ֤��'
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
        Name = '��ѯ.��Ŀ����'
        Caption = '��ѯ.��Ŀ����'
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
        Name = '��ѯ.״̬'
        Caption = '��ѯ.״̬'
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
        Name = '��ѯ.�Ƿ��ֹ���ƾ֤'
        Caption = '��ѯ.�Ƿ��ֹ���ƾ֤'
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
        Name = '��ѯ.����״̬'
        Caption = '��ѯ.����״̬'
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
        Name = '��¼������'
        Caption = '��¼������'
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
        Name = 'ƾ֤����'
        Caption = 'ƾ֤����'
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
        DataField = 'lsafe_level'
      end
      item
        Name = 'ƾ֤����'
        Caption = 'ƾ֤����'
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
        DataField = 'sorder0'
      end
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
        GroupIndex = 1
        DataField = 'lbank_acc_type'
      end
      item
        Name = '�к�1'
        Caption = '�к�1'
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
        Name = 'ժҪ1'
        Caption = 'ժҪ1'
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
        Name = '��Ŀ����1'
        Caption = '��Ŀ����1'
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
        Name = '�跽���1'
        Caption = '�跽���1'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�������1'
        Caption = '�������1'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�к�2'
        Caption = '�к�2'
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
        Name = 'ժҪ2'
        Caption = 'ժҪ2'
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
        Name = '��Ŀ����2'
        Caption = '��Ŀ����2'
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
        Name = '�跽���2'
        Caption = '�跽���2'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�������2'
        Caption = '�������2'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�к�3'
        Caption = '�к�3'
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
        Name = 'ժҪ3'
        Caption = 'ժҪ3'
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
        Name = '��Ŀ����3'
        Caption = '��Ŀ����3'
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
        Name = '�跽���3'
        Caption = '�跽���3'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�������3'
        Caption = '�������3'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�к�4'
        Caption = '�к�4'
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
        Name = 'ժҪ4'
        Caption = 'ժҪ4'
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
        Name = '��Ŀ����4'
        Caption = '��Ŀ����4'
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
        Name = '�跽���4'
        Caption = '�跽���4'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '�������4'
        Caption = '�������4'
        FieldType = wftUndefined
        Features.Strings = ()
        DataType = kdtFloat
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��'
        Caption = '��'
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
        Name = '��'
        Caption = '��'
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
        Name = 'ƾ֤��'
        Caption = 'ƾ֤��'
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
        Name = '���㷽ʽ'
        Caption = '���㷽ʽ'
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
        DataField = 'lvol9'
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
        GroupIndex = 1
        DataField = 'sname2'
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.רҵ����|'
      end
      item
        MonitorValueChangedFields = '|רҵ����|רҵ����|'
      end>
    Left = 71
    Top = 296
  end
  inherited QueryRequest: TWVRequest
    WorkView = wvVQuery
    ID = 'ƾ֤����.��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '����ڼ�(��)'
        FieldName = '��ѯ.����ڼ�(��)'
      end
      item
        ParamName = '����ڼ�(��)'
        FieldName = '��ѯ.����ڼ�(��)'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = '��ѯ.ƾ֤����'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = '��ѯ.ƾ֤����'
      end
      item
        ParamName = 'ƾ֤��'
        FieldName = '��ѯ.ƾ֤��'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��ѯ.��Ŀ����'
      end
      item
        ParamName = '״̬'
        FieldName = '��ѯ.״̬'
      end
      item
        ParamName = '�Ƿ��ֹ���ƾ֤'
        FieldName = '��ѯ.�Ƿ��ֹ���ƾ֤'
      end
      item
        ParamName = '����״̬'
        FieldName = '��ѯ.����״̬'
      end
      item
        ParamName = 'ƾ֤��������'
        FieldName = 'ƾ֤��������'
      end>
    Top = 328
  end
  inherited QueryBinder: TWVDBBinder
    WorkView = wvVQuery
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'lsafe_level2'
        DataPresentType = 'idobjects'
        DataPresentParam = '160'
      end
      item
        FieldName = 'lsafe_level'
        DataPresentType = 'idobjects'
        DataPresentParam = '-61'
      end
      item
        FieldName = 'semp_no'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'scheck_emp'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'schange_emp'
        DataPresentType = 'idobjects'
        DataPresentParam = '-30'
      end
      item
        FieldName = 'lvol9'
        DataPresentType = 'idobjects'
        DataPresentParam = '165'
      end
      item
        FieldName = 'lbank_acc_type2'
        DataPresentType = 'idobjects'
        DataPresentParam = '162'
      end
      item
        FieldName = 'lvol5'
        DataPresentType = 'idobjects'
        DataPresentParam = '161'
      end>
    Left = 136
    Top = 335
  end
  inherited AddRequest: TWVRequest
    ID = 'ƾ֤��Ŀ¼��'
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
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '��¼������'
        FieldName = '��¼������'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'ƾ֤����'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'ƾ֤����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��'
        FieldName = '��'
      end
      item
        ParamName = '��'
        FieldName = '��'
      end
      item
        ParamName = 'ƾ֤��'
        FieldName = 'ƾ֤��'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '���㷽ʽ'
        FieldName = '���㷽ʽ'
      end
      item
        ParamName = '�к�1'
        FieldName = '�к�1'
      end
      item
        ParamName = 'ժҪ1'
        FieldName = 'ժҪ1'
      end
      item
        ParamName = '��Ŀ����1'
        FieldName = '��Ŀ����1'
      end
      item
        ParamName = '�跽���1'
        FieldName = '�跽���1'
      end
      item
        ParamName = '�������1'
        FieldName = '�������1'
      end
      item
        ParamName = '�к�2'
        FieldName = '�к�2'
      end
      item
        ParamName = 'ժҪ2'
        FieldName = 'ժҪ2'
      end
      item
        ParamName = '��Ŀ����2'
        FieldName = '��Ŀ����2'
      end
      item
        ParamName = '�跽���2'
        FieldName = '�跽���2'
      end
      item
        ParamName = '�������2'
        FieldName = '�������2'
      end
      item
        ParamName = '�к�3'
        FieldName = '�к�3'
      end
      item
        ParamName = 'ժҪ3'
        FieldName = 'ժҪ3'
      end
      item
        ParamName = '��Ŀ����3'
        FieldName = '��Ŀ����3'
      end
      item
        ParamName = '�跽���3'
        FieldName = '�跽���3'
      end
      item
        ParamName = '�������3'
        FieldName = '�������3'
      end
      item
        ParamName = '�к�4'
        FieldName = '�к�4'
      end
      item
        ParamName = 'ժҪ4'
        FieldName = 'ժҪ4'
      end
      item
        ParamName = '��Ŀ����4'
        FieldName = '��Ŀ����4'
      end
      item
        ParamName = '�跽���4'
        FieldName = '�跽���4'
      end
      item
        ParamName = '�������4'
        FieldName = '�������4'
      end>
    Left = 104
    Top = 296
  end
  inherited DeleteRequest: TWVRequest
    ID = 'ƾ֤��Ŀ¼��'
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
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '��¼������'
        FieldName = '��¼������'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'ƾ֤����'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'ƾ֤����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��'
        FieldName = '��'
      end
      item
        ParamName = '��'
        FieldName = '��'
      end
      item
        ParamName = 'ƾ֤��'
        FieldName = 'ƾ֤��'
      end>
    Left = 136
    Top = 296
  end
  inherited ChangeRequest: TWVRequest
    ID = 'ƾ֤��Ŀ¼��'
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
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '��¼������'
        FieldName = '��¼������'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'ƾ֤����'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = 'ƾ֤����'
      end
      item
        ParamName = '������'
        FieldName = '������'
      end
      item
        ParamName = '��'
        FieldName = '��'
      end
      item
        ParamName = '��'
        FieldName = '��'
      end
      item
        ParamName = 'ƾ֤��'
        FieldName = 'ƾ֤��'
      end
      item
        ParamName = '�������'
        FieldName = '�������'
      end
      item
        ParamName = '���㷽ʽ'
        FieldName = '���㷽ʽ'
      end
      item
        ParamName = '�к�1'
        FieldName = '�к�1'
      end
      item
        ParamName = 'ժҪ1'
        FieldName = 'ժҪ1'
      end
      item
        ParamName = '��Ŀ����1'
        FieldName = '��Ŀ����1'
      end
      item
        ParamName = '�跽���1'
        FieldName = '�跽���1'
      end
      item
        ParamName = '�������1'
        FieldName = '�������1'
      end
      item
        ParamName = '�к�2'
        FieldName = '�к�2'
      end
      item
        ParamName = 'ժҪ2'
        FieldName = 'ժҪ2'
      end
      item
        ParamName = '��Ŀ����2'
        FieldName = '��Ŀ����2'
      end
      item
        ParamName = '�跽���2'
        FieldName = '�跽���2'
      end
      item
        ParamName = '�������2'
        FieldName = '�������2'
      end
      item
        ParamName = '�к�3'
        FieldName = '�к�3'
      end
      item
        ParamName = 'ժҪ3'
        FieldName = 'ժҪ3'
      end
      item
        ParamName = '��Ŀ����3'
        FieldName = '��Ŀ����3'
      end
      item
        ParamName = '�跽���3'
        FieldName = '�跽���3'
      end
      item
        ParamName = '�������3'
        FieldName = '�������3'
      end
      item
        ParamName = '�к�4'
        FieldName = '�к�4'
      end
      item
        ParamName = 'ժҪ4'
        FieldName = 'ժҪ4'
      end
      item
        ParamName = '��Ŀ����4'
        FieldName = '��Ŀ����4'
      end
      item
        ParamName = '�跽���4'
        FieldName = '�跽���4'
      end
      item
        ParamName = '�������4'
        FieldName = '�������4'
      end>
    Top = 296
  end
  inherited WVDataSource: TWVDataSource
    Left = 200
    Top = 335
  end
  inherited alDatasetActions: TActionList
    Left = 168
    Top = 335
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = 'ƾ֤��Ŀ��ѯ'
    Bindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '��ѯ�����'
        Direction = bdParam2Field
      end
      item
        ParamName = '�˺�'
        FieldName = '�˺�'
      end
      item
        ParamName = '����'
        FieldName = '����'
        Direction = bdParam2Field
      end
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
        ParamName = '��־'
        FieldName = '��־'
      end>
    Left = 104
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
        Name = '�˺�'
        Caption = '�˺�'
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
      end
      item
        Name = '����'
        Caption = '����'
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
        Name = '��־'
        Caption = '��־'
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
          '|�跽�˺�|�����˺�|�������|����վ��|����Ա��|���˲���Ա��|����' +
          '����Ա����|'
      end>
    Left = 68
    Top = 255
  end
  object DataSource1: TDataSource
    DataSet = ztblPZ
    OnDataChange = DataSourceDataChange
    Left = 144
    Top = 256
  end
  object ztblPZ: TZTable
    Connection = cmAccountMgrImp.conFB
    SortType = stDescending
    TableName = '"certificate"'
    Left = 184
    Top = 258
    object ztblPZcertificate: TStringField
      FieldName = 'certificate'
      Size = 300
    end
    object subjno: TStringField
      FieldName = 'subjno'
    end
    object ztblPZsubjname: TStringField
      FieldName = 'subjname'
      Size = 300
    end
    object ztblPZdebit: TFloatField
      FieldName = 'debit'
    end
    object ztblPZcredit: TFloatField
      FieldName = 'credit'
    end
  end
  object wvVoucherQ: TWorkView
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
        Name = '��־'
        Caption = '��־'
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
        Name = '��ѯ.����ڼ�(��)'
        Caption = '��ѯ.����ڼ�(��)'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ѯ.����ڼ�(��)'
        Caption = '��ѯ.����ڼ�(��)'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ѯ.ƾ֤����'
        Caption = '��ѯ.ƾ֤����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ѯ.ƾ֤����'
        Caption = '��ѯ.ƾ֤����'
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
        Name = '��ѯ.ƾ֤��'
        Caption = '��ѯ.ƾ֤��'
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
        Name = '��ѯ.��Ŀ����'
        Caption = '��ѯ.��Ŀ����'
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
        Name = '��ѯ.״̬'
        Caption = '��ѯ.״̬'
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
        MonitorValueChangedFields = '|��ѯ.רҵ����|'
      end
      item
        MonitorValueChangedFields = '|רҵ����|רҵ����|'
      end>
    Left = 71
    Top = 360
  end
  object wvrVoucherQ: TWVRequest
    WorkView = wvVoucherQ
    ID = 'ƾ֤����.��ѯ'
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
        ParamName = '��־'
        FieldName = '��־'
      end
      item
        ParamName = '����ڼ�(��)'
        FieldName = '��ѯ.����ڼ�(��)'
      end
      item
        ParamName = '����ڼ�(��)'
        FieldName = '��ѯ.����ڼ�(��)'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = '��ѯ.ƾ֤����'
      end
      item
        ParamName = 'ƾ֤����'
        FieldName = '��ѯ.ƾ֤����'
      end
      item
        ParamName = 'ƾ֤��'
        FieldName = '��ѯ.ƾ֤��'
      end
      item
        ParamName = '��Ŀ����'
        FieldName = '��ѯ.��Ŀ����'
      end
      item
        ParamName = '״̬'
        FieldName = '��ѯ.״̬'
      end>
    AfterExec = CheckReturnData
    Left = 104
    Top = 360
  end
  object wvVQuery: TWorkView
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
        Name = '��־'
        Caption = '��־'
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
        Name = '��ѯ.����ڼ�(��)'
        Caption = '��ѯ.����ڼ�(��)'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Max = 4
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ѯ.����ڼ�(��)'
        Caption = '��ѯ.����ڼ�(��)'
        FieldType = wftUndefined
        DataType = kdtInteger
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Max = 2
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ѯ.ƾ֤����'
        Caption = '��ѯ.ƾ֤����'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Max = 8
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end
      item
        Name = '��ѯ.ƾ֤����'
        Caption = '��ѯ.ƾ֤����'
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
        Name = '��ѯ.ƾ֤��'
        Caption = '��ѯ.ƾ֤��'
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
        Name = '��ѯ.��Ŀ����'
        Caption = '��ѯ.��Ŀ����'
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
        Name = '��ѯ.״̬'
        Caption = '��ѯ.״̬'
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
        Name = '��ѯ.�Ƿ��ֹ���ƾ֤'
        Caption = '��ѯ.�Ƿ��ֹ���ƾ֤'
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
        Name = '��ѯ.����״̬'
        Caption = '��ѯ.����״̬'
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
        Name = 'ƾ֤��������'
        Caption = 'ƾ֤��������'
        FieldType = wftUndefined
        DataType = kdtString
        OwnObject = False
        Visible = False
        Checker.MinLength = 0
        Checker.MaxLength = 0
        Checker.Max = 8
        Checker.DefaultValid = False
        Checker.AcceptAlphabet = False
        Checker.AcceptOther = False
        Checker.AcceptHigh = False
        Checker.LowerCase = False
        Checker.UpperCase = False
      end>
    WorkProcesses = <>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|��ѯ.רҵ����|'
      end
      item
        MonitorValueChangedFields = '|רҵ����|רҵ����|'
      end>
    Left = 71
    Top = 328
  end
  object rmDS1: TRMDBDataSet
    DataSet = ztblPZ
    Left = 260
    Top = 255
  end
  object rptQRpt: TRMReport
    InitialZoom = pzDefault
    PreviewButtons = [pbZoom, pbLoad, pbSave, pbPrint, pbFind, pbPageSetup, pbExit, pbSaveToXLS]
    DefaultCopies = 0
    DefaultCollate = False
    SaveReportOptions.RegistryPath = 'ReportMachine\ReportSettings\'
    Dataset = rmDS1
    Left = 220
    Top = 255
    ReportData = {}
  end
end
