inherited faqhUpdateCardInfo: TfaqhUpdateCardInfo
  Width = 789
  Height = 633
  inherited UIPanel1: TUIPanel
    Top = 610
    Width = 789
    Height = 23
    inherited btnQuery: TBitBtn
      Left = 181
      Top = 8
      Width = 83
      Enabled = False
      TabOrder = 1
      Visible = False
    end
    inherited btnPrint: TBitBtn
      Left = 267
      Top = 8
      TabOrder = 2
      Visible = False
    end
    object StatusBar: TRzStatusBar
      Left = 0
      Top = 2
      Width = 789
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
      TabOrder = 0
      object RzStatusPane1: TRzStatusPane
        Left = 0
        Top = 0
        Width = 789
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
    Width = 789
    Height = 16
    inherited Image1: TImage
      Width = 789
      Height = 16
    end
    inherited LabRecordCount: TLabel
      Visible = False
    end
  end
  inherited UIPanel2: TUIPanel
    Top = 16
    Width = 789
    Height = 594
    object imgPhoto: TImage [0]
      Left = 668
      Top = 74
      Width = 84
      Height = 112
      Stretch = True
    end
    inherited Grid: TRzDBGrid
      Left = 136
      Top = 328
      Width = 169
      Height = 33
      Align = alNone
      TabOrder = 2
      Visible = False
      Columns = <
        item
          Expanded = False
          FieldName = 'lvol0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���׿���'
          Width = 83
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ʾ����'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 74
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�Ա�'
          Width = 46
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ѧ/����'
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�շ����'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '�ͻ����'
          Width = 89
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Caption = '�������'
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '����'
          Width = 101
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ͼ��֤��'
          Width = 88
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '���֤��'
          Width = 111
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = 'ͼ��֤��'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '��ʹ�ý�ֹ����'
          Width = 79
          Visible = True
        end>
    end
    object btnReadCardQuery: TBitBtn
      Left = 454
      Top = 560
      Width = 98
      Height = 25
      Caption = '������Ϣ(&R)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnReadCardQueryClick
    end
    object btnOK: TBitBtn
      Left = 566
      Top = 560
      Width = 98
      Height = 25
      Hint = 'ȷ�ϲ���'
      Caption = 'ȷ�ϸ���(&O)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btnOKClick
    end
    object grpCardInfo: TGroupBox
      Left = 96
      Top = 56
      Width = 273
      Height = 497
      Caption = '��Ƭ��Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      object rzstspn1: TRzStatusPane
        Left = 11
        Top = 17
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '���׿���'
      end
      object RzStatusPane2: TRzStatusPane
        Left = 11
        Top = 42
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '������'
      end
      object RzStatusPane3: TRzStatusPane
        Left = 11
        Top = 67
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'ѧ/�� ��'
      end
      object RzStatusPane4: TRzStatusPane
        Left = 11
        Top = 91
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��    ��'
      end
      object RzStatusPane5: TRzStatusPane
        Left = 11
        Top = 265
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�� �� ��'
      end
      object RzStatusPane6: TRzStatusPane
        Left = 11
        Top = 365
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��ʾ����'
      end
      object RzStatusPane7: TRzStatusPane
        Left = 11
        Top = 439
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '����Ч��'
      end
      object RzStatusPane8: TRzStatusPane
        Left = 11
        Top = 240
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '֤������'
      end
      object RzStatusPane9: TRzStatusPane
        Left = 11
        Top = 23
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Visible = False
        Alignment = taRightJustify
        Caption = '�� �� ��'
      end
      object RzStatusPane20: TRzStatusPane
        Left = 11
        Top = 116
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�ͻ����'
      end
      object RzStatusPane21: TRzStatusPane
        Left = 11
        Top = 141
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�շ����'
      end
      object RzStatusPane22: TRzStatusPane
        Left = 11
        Top = 166
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '���Ŵ���'
      end
      object RzStatusPane23: TRzStatusPane
        Left = 11
        Top = 191
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�Ա����'
      end
      object RzStatusPane28: TRzStatusPane
        Left = 11
        Top = 290
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��ֵ����'
      end
      object RzStatusPane10: TRzStatusPane
        Left = 11
        Top = 340
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�������κ�'
      end
      object RzStatusPane31: TRzStatusPane
        Left = 11
        Top = 389
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�����޶�'
      end
      object RzStatusPane32: TRzStatusPane
        Left = 11
        Top = 414
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '���޶�'
      end
      object rzstspn2: TRzStatusPane
        Left = 11
        Top = 216
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '֤������'
      end
      object rzstspn4: TRzStatusPane
        Left = 11
        Top = 315
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '���Ѵ���'
      end
      object edtcCardNo: TRzEdit
        Left = 95
        Top = 18
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ParentFont = False
        TabOrder = 0
      end
      object edtcPhyId: TRzEdit
        Left = 95
        Top = 43
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ParentFont = False
        TabOrder = 1
      end
      object edtcStuempNo: TRzEdit
        Left = 95
        Top = 68
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 2
      end
      object edtcShowNo: TRzEdit
        Left = 95
        Top = 366
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 10
        ParentFont = False
        TabOrder = 14
        OnKeyPress = edtShowCardNoKeyPress
      end
      object edtcBalance: TRzEdit
        Left = 95
        Top = 266
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ParentFont = False
        TabOrder = 10
      end
      object edtcIdCard: TRzEdit
        Left = 95
        Top = 241
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 9
      end
      object edtcName: TRzEdit
        Left = 95
        Top = 92
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 3
      end
      object edtcEndDate: TRzEdit
        Left = 95
        Top = 440
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 17
      end
      object edtCCustType: TRzEdit
        Left = 95
        Top = 117
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 4
      end
      object edtCFeeType: TRzEdit
        Left = 95
        Top = 142
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 5
      end
      object edtCDept: TRzEdit
        Left = 95
        Top = 167
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 6
      end
      object edtCSex: TRzEdit
        Left = 95
        Top = 192
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 7
      end
      object edtCardDptNum: TRzEdit
        Left = 95
        Top = 291
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ParentFont = False
        TabOrder = 11
      end
      object edtCPatchNo: TRzEdit
        Left = 95
        Top = 341
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ParentFont = False
        TabOrder = 13
      end
      object edtMaxcPerCount: TRzEdit
        Left = 95
        Top = 390
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ParentFont = False
        TabOrder = 15
      end
      object edtcMaxPerDay: TRzEdit
        Left = 95
        Top = 415
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ParentFont = False
        TabOrder = 16
      end
      object edtCCertType: TRzEdit
        Left = 95
        Top = 217
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 8
      end
      object edtCPayCnt: TRzEdit
        Left = 95
        Top = 316
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ParentFont = False
        TabOrder = 12
      end
    end
    object grpLibInfo: TGroupBox
      Left = 392
      Top = 56
      Width = 273
      Height = 497
      Caption = '������Ϣ'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      object RzStatusPane11: TRzStatusPane
        Left = 11
        Top = 17
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '���׿���'
      end
      object RzStatusPane12: TRzStatusPane
        Left = 11
        Top = 42
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '������'
      end
      object RzStatusPane13: TRzStatusPane
        Left = 11
        Top = 67
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = 'ѧ/�� ��'
      end
      object RzStatusPane14: TRzStatusPane
        Left = 11
        Top = 91
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��    ��'
      end
      object RzStatusPane15: TRzStatusPane
        Left = 11
        Top = 265
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�� �� ��'
      end
      object RzStatusPane16: TRzStatusPane
        Left = 11
        Top = 365
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��ʾ����'
      end
      object RzStatusPane17: TRzStatusPane
        Left = 11
        Top = 439
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '����Ч��'
      end
      object RzStatusPane18: TRzStatusPane
        Left = 11
        Top = 240
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '֤������'
      end
      object RzStatusPane24: TRzStatusPane
        Left = 11
        Top = 116
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�ͻ����'
      end
      object RzStatusPane25: TRzStatusPane
        Left = 11
        Top = 141
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�շ����'
      end
      object RzStatusPane26: TRzStatusPane
        Left = 11
        Top = 166
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '���Ŵ���'
      end
      object RzStatusPane27: TRzStatusPane
        Left = 11
        Top = 191
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�Ա����'
      end
      object RzStatusPane19: TRzStatusPane
        Left = 11
        Top = 465
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��������'
      end
      object RzStatusPane29: TRzStatusPane
        Left = 11
        Top = 290
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '��ֵ����'
      end
      object RzStatusPane30: TRzStatusPane
        Left = 11
        Top = 340
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�������κ�'
      end
      object RzStatusPane33: TRzStatusPane
        Left = 11
        Top = 389
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '�����޶�'
      end
      object RzStatusPane34: TRzStatusPane
        Left = 11
        Top = 414
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '���޶�'
      end
      object rzstspn3: TRzStatusPane
        Left = 11
        Top = 216
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '֤������'
      end
      object rzstspn5: TRzStatusPane
        Left = 11
        Top = 315
        Width = 81
        Height = 22
        FillColor = 16184303
        FlatColor = clMenuText
        FrameStyle = fsStatus
        ParentFillColor = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '���Ѵ���'
      end
      object edtCardNo: TRzEdit
        Left = 95
        Top = 17
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
      end
      object edtPhyID: TRzEdit
        Left = 95
        Top = 42
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
      end
      object edtNo: TRzEdit
        Left = 95
        Top = 67
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 2
      end
      object edtIDCard: TRzEdit
        Left = 95
        Top = 241
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 9
      end
      object edtBalance: TRzEdit
        Left = 95
        Top = 266
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ParentFont = False
        TabOrder = 10
      end
      object edtShowCardNo: TRzEdit
        Left = 95
        Top = 365
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FocusColor = clWhite
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 10
        ParentFont = False
        TabOrder = 14
        OnKeyPress = edtShowCardNoKeyPress
      end
      object edtName: TRzEdit
        Left = 95
        Top = 92
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 3
      end
      object edtEndDate: TRzEdit
        Left = 95
        Top = 440
        Width = 154
        Height = 20
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 17
      end
      object edtCustType: TRzEdit
        Left = 95
        Top = 117
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 4
      end
      object edtFeeType: TRzEdit
        Left = 95
        Top = 141
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 5
      end
      object edtDept: TRzEdit
        Left = 95
        Top = 166
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 6
      end
      object edtSex: TRzEdit
        Left = 95
        Top = 191
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 7
      end
      object cbbRType: TWVComboBox
        Left = 95
        Top = 465
        Width = 155
        Height = 20
        Style = csDropDownList
        Color = clWhite
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = []
        ItemHeight = 12
        ParentFont = False
        TabOrder = 18
        OnChange = cbbRTypeChange
        DataPresentType = 'IDOBJECTS'
        AutoDropDown = False
        ItemsDataEntry = '131'
      end
      object edtDptCnt: TRzEdit
        Left = 95
        Top = 291
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ParentFont = False
        TabOrder = 11
      end
      object edtPatchNo: TRzEdit
        Left = 95
        Top = 340
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ParentFont = False
        TabOrder = 13
      end
      object edtMaxPercount: TRzEdit
        Left = 95
        Top = 390
        Width = 154
        Height = 20
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ParentFont = False
        TabOrder = 15
      end
      object edtMaxPerDay: TRzEdit
        Left = 95
        Top = 415
        Width = 154
        Height = 20
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ParentFont = False
        TabOrder = 16
      end
      object edtCertType: TRzEdit
        Left = 95
        Top = 216
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        ParentFont = False
        TabOrder = 8
      end
      object edtPayCnt: TRzEdit
        Left = 95
        Top = 316
        Width = 154
        Height = 20
        Enabled = False
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '����'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '���� (����) - ΢��ƴ��'
        MaxLength = 22
        ParentFont = False
        TabOrder = 12
      end
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '������'
        Caption = '������'
        FieldType = wftUndefined
        Features.Strings = ()
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
      end
      item
        Name = '��ʾ����'
        Caption = '��ʾ����'
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
        Name = '�ͻ����'
        Caption = '�ͻ����'
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
        Name = '�շ����'
        Caption = '�շ����'
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
        Name = 'ѧ����'
        Caption = 'ѧ����'
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
      end
      item
        Name = '���Ŵ���'
        Caption = '���Ŵ���'
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
        Name = '֤������'
        Caption = '֤������'
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
        Name = '�Ա�'
        Caption = '�Ա�'
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
        Name = '����������'
        Caption = '����������'
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
        Name = '�������κ�'
        Caption = '�������κ�'
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
        Name = '�����޶�'
        Caption = '�����޶�'
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
        Name = '���޶�'
        Caption = '���޶�'
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
        Name = '�뵥���޶�'
        Caption = '�뵥���޶�'
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
        Name = '�����޶�'
        Caption = '�����޶�'
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
        Name = '֤������'
        Caption = '֤������'
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
      end
      item
        Name = '����ʱ��'
        Caption = '����ʱ��'
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
      end>
    FieldsMonitors = <
      item
        MonitorValueChangedFields = '|����ʶ|'
      end>
    Left = 228
    Top = 31
  end
  inherited MainRequest: TWVRequest
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
      end
      item
        ParamName = '֤������'
        FieldName = '֤������'
        Direction = bdParam2Field
      end
      item
        ParamName = '����ʱ��'
        FieldName = '����ʱ��'
        Direction = bdParam2Field
      end
      item
        ParamName = '��������'
        FieldName = '��������'
        Direction = bdParam2Field
      end
      item
        ParamName = '��ֵ����'
        FieldName = '��ֵ����'
      end>
    Left = 264
    Top = 32
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '��ѯ�����'
    Bindings = <
      item
        FieldName = 'scust_type'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '39'
      end
      item
        FieldName = 'lvol0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-34'
      end
      item
        FieldName = 'sserial0'
        DataPresentType = 'IDOBJECTS'
        DataPresentParam = '-22'
      end>
    Left = 304
    Top = 32
  end
  inherited DataSource: TDataSource
    Left = 344
    Top = 32
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
      end
      item
        Name = '��״̬'
        Caption = '��״̬'
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
    Left = 404
    Top = 31
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
      end
      item
        ParamName = '��״̬'
        FieldName = '��״̬'
      end>
    AfterExec = MainRequestAfterExec
    Left = 440
    Top = 32
  end
end
