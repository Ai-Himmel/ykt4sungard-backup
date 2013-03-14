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
      Font.Name = '宋体'
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
        Font.Name = '宋体'
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
          Title.Caption = '交易卡号'
          Width = 83
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_no'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '显示卡号'
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '姓名'
          Width = 74
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_type'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '性别'
          Width = 46
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_limit'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '学/工号'
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'lvol5'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '收费类别'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'lvol1'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '客户类别'
          Width = 89
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damt0'
          PickList.Strings = ()
          Title.Caption = '卡库余额'
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sserial0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '部门'
          Width = 101
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'sname2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '图书证号'
          Width = 88
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth2'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '身份证号'
          Width = 111
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'scust_auth'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '图书证号'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'sdate0'
          PickList.Strings = ()
          Title.Alignment = taCenter
          Title.Caption = '卡使用截止日期'
          Width = 79
          Visible = True
        end>
    end
    object btnReadCardQuery: TBitBtn
      Left = 454
      Top = 560
      Width = 98
      Height = 25
      Caption = '读卡信息(&R)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
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
      Hint = '确认操作'
      Caption = '确认更新(&O)'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
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
      Caption = '卡片信息'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '交易卡号'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '物理卡号'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '学/工 号'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '姓    名'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '卡 余 额'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '显示卡号'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '卡有效期'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '证件号码'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Visible = False
        Alignment = taRightJustify
        Caption = '客 户 号'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '客户类别'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '收费类别'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '部门代码'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '性别代码'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '充值次数'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '补助批次号'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '单次限额'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '日限额'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '证件类型'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '消费次数'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
      Caption = '更新信息'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '交易卡号'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '物理卡号'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '学/工 号'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '姓    名'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '卡 余 额'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '显示卡号'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '卡有效期'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '证件号码'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '客户类别'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '收费类别'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '部门代码'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '性别代码'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '更新类型'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '充值次数'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '补助批次号'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '单次限额'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '日限额'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '证件类型'
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
        Font.Name = '宋体'
        Font.Style = []
        ParentFont = False
        Alignment = taRightJustify
        Caption = '消费次数'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FocusColor = clWhite
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
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
        Font.Name = '宋体'
        Font.Style = [fsBold]
        FrameVisible = True
        ImeName = '中文 (简体) - 微软拼音'
        MaxLength = 22
        ParentFont = False
        TabOrder = 12
      end
    end
  end
  inherited WorkView: TWorkView
    WorkFields = <
      item
        Name = '返回码'
        Caption = '返回码'
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
        Name = '返回信息'
        Caption = '返回信息'
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
        Name = '卡号'
        Caption = '卡号'
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
        Name = '物理卡号'
        Caption = '物理卡号'
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
        Name = '更新类型'
        Caption = '更新类型'
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
        Name = '显示卡号'
        Caption = '显示卡号'
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
        Name = '客户类别'
        Caption = '客户类别'
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
        Name = '收费类别'
        Caption = '收费类别'
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
        Name = '学工号'
        Caption = '学工号'
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
        Name = '姓名'
        Caption = '姓名'
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
        Name = '部门代码'
        Caption = '部门代码'
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
        Name = '证件号码'
        Caption = '证件号码'
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
        Name = '性别'
        Caption = '性别'
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
        Name = '卡到期日期'
        Caption = '卡到期日期'
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
        Name = '卡余额'
        Caption = '卡余额'
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
        Name = '交易次数'
        Caption = '交易次数'
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
        Name = '补助批次号'
        Caption = '补助批次号'
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
        Name = '卡密码'
        Caption = '卡密码'
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
        Name = '单次限额'
        Caption = '单次限额'
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
        Name = '日限额'
        Caption = '日限额'
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
        Name = '入单次限额'
        Caption = '入单次限额'
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
        Name = '入日限额'
        Caption = '入日限额'
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
        Name = '证件类型'
        Caption = '证件类型'
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
        Name = '交易日期'
        Caption = '交易日期'
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
        Name = '交易时间'
        Caption = '交易时间'
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
        Name = '充值次数'
        Caption = '充值次数'
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
        MonitorValueChangedFields = '|卡标识|'
      end>
    Left = 228
    Top = 31
  end
  inherited MainRequest: TWVRequest
    ID = '更新卡信息'
    Bindings = <
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
        Direction = bdBiDirection
      end
      item
        ParamName = '物理卡号'
        FieldName = '物理卡号'
      end
      item
        ParamName = '更新类型'
        FieldName = '更新类型'
      end
      item
        ParamName = '显示卡号'
        FieldName = '显示卡号'
        Direction = bdParam2Field
      end
      item
        ParamName = '客户类别'
        FieldName = '客户类别'
        Direction = bdParam2Field
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
        Direction = bdParam2Field
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
        Direction = bdParam2Field
      end
      item
        ParamName = '姓名'
        FieldName = '姓名'
        Direction = bdParam2Field
      end
      item
        ParamName = '部门代码'
        FieldName = '部门代码'
        Direction = bdParam2Field
      end
      item
        ParamName = '证件号码'
        FieldName = '证件号码'
        Direction = bdParam2Field
      end
      item
        ParamName = '性别'
        FieldName = '性别'
        Direction = bdParam2Field
      end
      item
        ParamName = '卡到期日期'
        FieldName = '卡到期日期'
        Direction = bdBiDirection
      end
      item
        ParamName = '卡余额'
        FieldName = '卡余额'
        Direction = bdBiDirection
      end
      item
        ParamName = '交易次数'
        FieldName = '交易次数'
        Direction = bdBiDirection
      end
      item
        ParamName = '补助批次号'
        FieldName = '补助批次号'
        Direction = bdParam2Field
      end
      item
        ParamName = '卡密码'
        FieldName = '卡密码'
        Direction = bdParam2Field
      end
      item
        ParamName = '单次限额'
        FieldName = '单次限额'
        Direction = bdParam2Field
      end
      item
        ParamName = '日限额'
        FieldName = '日限额'
        Direction = bdParam2Field
      end
      item
        ParamName = '入日限额'
        FieldName = '入日限额'
      end
      item
        ParamName = '入单次限额'
        FieldName = '入单次限额'
      end
      item
        ParamName = '证件类型'
        FieldName = '证件类型'
        Direction = bdParam2Field
      end
      item
        ParamName = '交易时间'
        FieldName = '交易时间'
        Direction = bdParam2Field
      end
      item
        ParamName = '交易日期'
        FieldName = '交易日期'
        Direction = bdParam2Field
      end
      item
        ParamName = '充值次数'
        FieldName = '充值次数'
      end>
    Left = 264
    Top = 32
  end
  inherited WVDBBinder: TWVDBBinder
    FieldName = '查询结果集'
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
        Name = '返回码'
        Caption = '返回码'
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
        Name = '返回信息'
        Caption = '返回信息'
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
        Name = '查询结果集'
        Caption = '查询结果集'
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
        Name = '客户号'
        Caption = '客户号'
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
        Name = '学工号'
        Caption = '学工号'
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
        Name = '客户姓名'
        Caption = '客户姓名'
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
        Name = '部门'
        Caption = '部门'
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
        Name = '证件类型'
        Caption = '证件类型'
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
        Name = '证件号码'
        Caption = '证件号码'
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
        Name = '客户类别'
        Caption = '客户类别'
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
        Name = '收费类别'
        Caption = '收费类别'
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
        Name = '所属区域'
        Caption = '所属区域'
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
        Name = '显示卡号'
        Caption = '显示卡号'
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
        Name = '导入批次号'
        Caption = '导入批次号'
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
        Name = '注销日期'
        Caption = '注销日期'
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
        Name = '卡号'
        Caption = '卡号'
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
        Name = '钱包号'
        Caption = '钱包号'
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
        Name = '物理卡号'
        Caption = '物理卡号'
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
        Name = '卡状态'
        Caption = '卡状态'
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
        MonitorValueChangedFields = '|客户号|学工号|卡号|姓名|身份证号|'
      end>
    Left = 404
    Top = 31
  end
  object WVRequest1: TWVRequest
    WorkView = WorkView1
    ID = '已开卡客户信息查询'
    Bindings = <
      item
        ParamName = '返回码'
        FieldName = '返回码'
        Direction = bdParam2Field
      end
      item
        ParamName = '返回信息'
        FieldName = '返回信息'
        Direction = bdParam2Field
      end
      item
        ParamName = '查询结果集'
        FieldName = '查询结果集'
        Direction = bdParam2Field
      end
      item
        ParamName = '客户号'
        FieldName = '客户号'
      end
      item
        ParamName = '部门'
        FieldName = '部门'
      end
      item
        ParamName = '导入批次号'
        FieldName = '导入批次号'
      end
      item
        ParamName = '客户类别'
        FieldName = '客户类别'
      end
      item
        ParamName = '客户姓名'
        FieldName = '客户姓名'
      end
      item
        ParamName = '收费类别'
        FieldName = '收费类别'
      end
      item
        ParamName = '所属区域'
        FieldName = '所属区域'
      end
      item
        ParamName = '学工号'
        FieldName = '学工号'
      end
      item
        ParamName = '证件号码'
        FieldName = '证件号码'
      end
      item
        ParamName = '证件类型'
        FieldName = '证件类型'
      end
      item
        ParamName = '注销日期'
        FieldName = '注销日期'
      end
      item
        ParamName = '显示卡号'
        FieldName = '显示卡号'
      end
      item
        ParamName = '卡号'
        FieldName = '卡号'
      end
      item
        ParamName = '钱包号'
        FieldName = '钱包号'
      end
      item
        ParamName = '物理卡号'
        FieldName = '物理卡号'
      end
      item
        ParamName = '卡状态'
        FieldName = '卡状态'
      end>
    AfterExec = MainRequestAfterExec
    Left = 440
    Top = 32
  end
end
