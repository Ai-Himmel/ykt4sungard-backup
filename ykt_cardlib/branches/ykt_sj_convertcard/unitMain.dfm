object frmMain: TfrmMain
  Left = 230
  Top = 115
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #36716#21345#31243#24207'V3.04'
  ClientHeight = 469
  ClientWidth = 521
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object lblInfo: TRzLabel
    Left = 12
    Top = 408
    Width = 25
    Height = 50
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -50
    Font.Name = #26999#20307'_GB2312'
    Font.Style = []
    ParentFont = False
    LightTextStyle = True
    TextStyle = tsRaised
  end
  object btnInitCard: TBitBtn
    Left = 14
    Top = 326
    Width = 88
    Height = 33
    Caption = #25171#24320#35835#21345#22120'(&O)'
    TabOrder = 4
    OnClick = btnInitCardClick
  end
  object btnCloseCard: TBitBtn
    Left = 14
    Top = 366
    Width = 88
    Height = 33
    Caption = #20851#38381#35835#21345#22120'(&X)'
    TabOrder = 5
    OnClick = btnCloseCardClick
  end
  object btnCardUpdate: TBitBtn
    Left = 149
    Top = 325
    Width = 88
    Height = 33
    Hint = #24555#25463#38190#65306#31354#26684#38190
    Caption = #21345#29255#21319#32423'(&U)'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnClick = btnCardUpdateClick
  end
  object btnReadCard: TBitBtn
    Left = 284
    Top = 325
    Width = 88
    Height = 33
    Hint = #24555#25463#38190':'#22238#36710#38190
    Caption = #35835#21345#20449#24687'(&R)'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    OnClick = btnReadCardClick
  end
  object rzgrpbx1: TRzGroupBox
    Left = 13
    Top = 3
    Width = 495
    Height = 314
    Caption = #21345#29255#20449#24687
    TabOrder = 0
    object lbl1: TRzLabel
      Left = 23
      Top = 27
      Width = 57
      Height = 13
      AutoSize = False
      Caption = #21345#24207#21015#21495
    end
    object lbl2: TRzLabel
      Left = 23
      Top = 52
      Width = 40
      Height = 13
      AutoSize = False
      Caption = #22995#21517
    end
    object lbl3: TRzLabel
      Left = 272
      Top = 101
      Width = 57
      Height = 13
      AutoSize = False
      Caption = #24080#25143#20313#39069
    end
    object lbl4: TRzLabel
      Left = 23
      Top = 76
      Width = 66
      Height = 13
      AutoSize = False
      Caption = #23458#25143#21495
    end
    object lbl5: TRzLabel
      Left = 23
      Top = 126
      Width = 24
      Height = 13
      Caption = #23398#21495
    end
    object lbl6: TRzLabel
      Left = 23
      Top = 175
      Width = 39
      Height = 13
      AutoSize = False
      Caption = #37096#38376
    end
    object lbl7: TRzLabel
      Left = 23
      Top = 101
      Width = 58
      Height = 13
      AutoSize = False
      Caption = #23458#25143#31867#21035
    end
    object lbl8: TRzLabel
      Left = 272
      Top = 52
      Width = 53
      Height = 13
      AutoSize = False
      Caption = #25910#36153#31867#21035
    end
    object lbl9: TRzLabel
      Left = 272
      Top = 27
      Width = 34
      Height = 13
      AutoSize = False
      Caption = #21345#21495
    end
    object lbl10: TRzLabel
      Left = 272
      Top = 127
      Width = 45
      Height = 13
      AutoSize = False
      Caption = #21345#29366#24577
    end
    object lbl11: TRzLabel
      Left = 272
      Top = 152
      Width = 64
      Height = 13
      AutoSize = False
      Caption = #36807#26399#26085#26399
    end
    object lbl12: TRzLabel
      Left = 272
      Top = 77
      Width = 52
      Height = 13
      AutoSize = False
      Caption = #26174#31034#21345#21495
    end
    object lbl13: TRzLabel
      Left = 23
      Top = 200
      Width = 50
      Height = 13
      AutoSize = False
      Caption = #24615#21035
    end
    object lbl14: TRzLabel
      Left = 23
      Top = 151
      Width = 59
      Height = 13
      AutoSize = False
      Caption = #38498#26657#20195#30721
    end
    object lbl15: TRzLabel
      Left = 272
      Top = 177
      Width = 46
      Height = 13
      AutoSize = False
      Caption = #21345#23494#30721
    end
    object lbl16: TRzLabel
      Left = 23
      Top = 225
      Width = 50
      Height = 13
      AutoSize = False
      Caption = #32844#21153
    end
    object lbl18: TRzLabel
      Left = 23
      Top = 249
      Width = 59
      Height = 13
      AutoSize = False
      Caption = #35777#20214#31867#21035
    end
    object lbl19: TRzLabel
      Left = 272
      Top = 202
      Width = 58
      Height = 13
      AutoSize = False
      Caption = #35777#20214#21495#30721
    end
    object lbl17: TRzLabel
      Left = 23
      Top = 274
      Width = 54
      Height = 13
      AutoSize = False
      Caption = #22269#31821
    end
    object lbl21: TRzLabel
      Left = 272
      Top = 227
      Width = 54
      Height = 13
      AutoSize = False
      Caption = #27665#26063
    end
    object lbl22: TRzLabel
      Left = 467
      Top = 101
      Width = 12
      Height = 13
      Caption = #20998
    end
    object lbl23: TRzLabel
      Left = 272
      Top = 251
      Width = 54
      Height = 13
      AutoSize = False
      Caption = #20132#26131#27425#25968
    end
    object lblschool: TRzLabel
      Left = 272
      Top = 275
      Width = 54
      Height = 13
      AutoSize = False
      Caption = #36873#25321#23398#26657
    end
    object edtShowCardNo: TRzEdit
      Left = 344
      Top = 74
      Width = 119
      Height = 21
      TabOrder = 5
    end
    object edtCardNo: TRzEdit
      Left = 344
      Top = 25
      Width = 119
      Height = 21
      TabOrder = 0
    end
    object edtCardPhyID: TRzEdit
      Left = 84
      Top = 25
      Width = 119
      Height = 21
      MaxLength = 10
      TabOrder = 1
    end
    object edtCutID: TRzEdit
      Tag = 1
      Left = 84
      Top = 74
      Width = 119
      Height = 21
      MaxLength = 8
      TabOrder = 4
    end
    object edtName: TRzEdit
      Left = 84
      Top = 49
      Width = 119
      Height = 21
      TabOrder = 2
    end
    object edtCutType: TRzEdit
      Left = 84
      Top = 98
      Width = 119
      Height = 21
      TabOrder = 6
    end
    object edtFeeType: TRzEdit
      Left = 344
      Top = 49
      Width = 119
      Height = 21
      TabOrder = 3
    end
    object edtStuempNo: TRzEdit
      Left = 84
      Top = 123
      Width = 119
      Height = 21
      TabOrder = 8
    end
    object edtDept: TRzEdit
      Left = 84
      Top = 172
      Width = 119
      Height = 21
      TabOrder = 11
    end
    object edtCardStatus: TRzEdit
      Left = 344
      Top = 123
      Width = 119
      Height = 21
      TabOrder = 9
    end
    object edtEndDate: TRzEdit
      Left = 344
      Top = 147
      Width = 119
      Height = 21
      TabOrder = 12
    end
    object edtSex: TRzEdit
      Left = 84
      Top = 196
      Width = 119
      Height = 21
      TabOrder = 13
    end
    object edtSchoolCode: TRzEdit
      Left = 84
      Top = 147
      Width = 119
      Height = 21
      TabOrder = 10
    end
    object edtCardPwd: TRzEdit
      Left = 344
      Top = 172
      Width = 119
      Height = 21
      TabOrder = 14
    end
    object edtDuty: TRzEdit
      Left = 84
      Top = 221
      Width = 119
      Height = 21
      TabOrder = 15
    end
    object edtIDType: TRzEdit
      Left = 84
      Top = 245
      Width = 119
      Height = 21
      TabOrder = 17
    end
    object edtIDNo: TRzEdit
      Left = 344
      Top = 196
      Width = 119
      Height = 21
      TabOrder = 16
    end
    object edtBalance: TRzEdit
      Left = 344
      Top = 98
      Width = 119
      Height = 21
      Color = clInfoBk
      ReadOnly = True
      TabOrder = 7
    end
    object edtCountry: TRzEdit
      Left = 84
      Top = 270
      Width = 119
      Height = 21
      TabOrder = 19
    end
    object edtNation: TRzEdit
      Left = 344
      Top = 221
      Width = 119
      Height = 21
      TabOrder = 18
    end
    object editTxCnt: TRzEdit
      Left = 344
      Top = 245
      Width = 119
      Height = 21
      TabOrder = 20
    end
    object cbbSchool: TComboBox
      Left = 344
      Top = 272
      Width = 121
      Height = 21
      ItemHeight = 13
      TabOrder = 21
      Items.Strings = (
        #19996#21326#22823#23398
        #21326#19996#25919#27861#22823#23398
        #19978#28023#24037#31243#25216#26415#22823#23398
        #19978#28023#22806#22269#35821#22823#23398
        #19978#28023#23545#22806#36152#26131#23398#38498
        #19978#28023#31435#20449#20250#35745#23398#38498
        #22797#26086#35270#35273
        #20020#26102#21345
        #24037#34892#21345)
    end
  end
  object btnQueryCard: TBitBtn
    Left = 149
    Top = 366
    Width = 88
    Height = 33
    Caption = #35835#21345#26597#35810'(&Q)'
    TabOrder = 6
    OnClick = btnQueryCardClick
  end
  object btnQueryByCutID: TBitBtn
    Left = 148
    Top = 406
    Width = 88
    Height = 33
    Caption = #23458#25143#21495#26597#35810'(&P)'
    TabOrder = 7
    Visible = False
    OnClick = btnQueryByCutIDClick
  end
  object btnCLean: TBitBtn
    Left = 419
    Top = 325
    Width = 88
    Height = 33
    Caption = #28165#23631'(&C)'
    TabOrder = 3
    OnClick = btnCLeanClick
  end
  object btnReWriteCard: TBitBtn
    Left = 404
    Top = 422
    Width = 88
    Height = 33
    Caption = #37325#20889#21345#20449#24687'(&W)'
    TabOrder = 8
    Visible = False
    OnClick = btnReWriteCardClick
  end
  object btnRWCardInfo: TBitBtn
    Left = 299
    Top = 422
    Width = 88
    Height = 33
    Caption = #37325#20889#21345#32467#26500'(&T)'
    TabOrder = 9
    Visible = False
    OnClick = btnRWCardInfoClick
  end
  object btnShowInfo: TBitBtn
    Left = 420
    Top = 366
    Width = 88
    Height = 33
    Caption = #26174#31034#36716#21345#20449#24687'(&T)'
    TabOrder = 10
    OnClick = btnShowInfoClick
  end
  object btnUpdatePhyNo: TButton
    Left = 284
    Top = 366
    Width = 88
    Height = 33
    Caption = #26356#26032#29289#29702#21345#21495'(&Q)'
    TabOrder = 11
    OnClick = btnUpdatePhyNoClick
  end
  object con1: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=E:\gdykt\source\con' +
      'vertcard\convertcard.mdb;Persist Security Info=False'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 333
    Top = 407
  end
  object qry1: TADOQuery
    ConnectionString = 'FILE NAME=E:\gdykt\source\convertcard\connaccess.udl'
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from card')
    Left = 297
    Top = 403
  end
  object ds1: TDataSource
    DataSet = qry1
    Left = 255
    Top = 406
  end
end
