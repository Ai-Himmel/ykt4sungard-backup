object frmPhotoQuery: TfrmPhotoQuery
  Left = 157
  Top = 162
  BorderStyle = bsDialog
  Caption = #25293#29031#20449#24687#26597#35810
  ClientHeight = 483
  ClientWidth = 728
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object pnl1: TPanel
    Left = 0
    Top = 0
    Width = 728
    Height = 96
    Align = alTop
    BevelOuter = bvNone
    Color = 16053492
    TabOrder = 0
    object Label5: TLabel
      Left = 514
      Top = 13
      Width = 54
      Height = 15
      Caption = #24180'  '#32423':'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 76
      Top = 40
      Width = 68
      Height = 15
      AutoSize = False
      Caption = #20154#21592#31867#21035':'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 305
      Top = 40
      Width = 54
      Height = 15
      AutoSize = False
      Caption = #37096'  '#38376':'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 514
      Top = 40
      Width = 54
      Height = 15
      Caption = #19987'  '#19994':'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
    end
    object Label1: TLabel
      Left = 83
      Top = 13
      Width = 61
      Height = 15
      AutoSize = False
      Caption = #23398'/'#24037#21495':'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 305
      Top = 13
      Width = 54
      Height = 15
      AutoSize = False
      Caption = #22995'  '#21517':'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
    end
    object cbbType: TDBLookupComboboxEh
      Left = 146
      Top = 34
      Width = 144
      Height = 21
      DropDownBox.Rows = 15
      EditButtons = <>
      ListSource = dsType
      TabOrder = 4
      Visible = True
    end
    object cbbSpec: TDBLookupComboboxEh
      Left = 570
      Top = 34
      Width = 147
      Height = 21
      DropDownBox.Rows = 15
      EditButtons = <>
      ListSource = dsSpec
      TabOrder = 6
      Visible = True
    end
    object cbbDept: TDBLookupComboboxEh
      Left = 362
      Top = 34
      Width = 144
      Height = 21
      DropDownBox.Rows = 15
      EditButtons = <>
      ListSource = dsDept
      TabOrder = 5
      Visible = True
    end
    object edtStuEmpNo: TEdit
      Left = 146
      Top = 7
      Width = 143
      Height = 23
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object edtName: TEdit
      Left = 362
      Top = 7
      Width = 143
      Height = 23
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object rgPhoto: TRadioGroup
      Left = 82
      Top = 59
      Width = 209
      Height = 33
      Caption = #26159#21542#25293#29031
      Columns = 3
      ItemIndex = 2
      Items.Strings = (
        #26159
        #21542
        #20840#37096)
      TabOrder = 7
    end
    object btnOper: TBitBtn
      Left = 410
      Top = 67
      Width = 65
      Height = 25
      Caption = '&Q'#26597' '#35810
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 8
      OnClick = btnOperClick
    end
    object BitBtn2: TBitBtn
      Left = 490
      Top = 67
      Width = 65
      Height = 25
      Caption = #23548#20986#25968#25454
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 9
      OnClick = BitBtn2Click
    end
    object BitBtn1: TBitBtn
      Left = 650
      Top = 67
      Width = 65
      Height = 25
      Caption = '&X'#36864' '#20986
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 11
      OnClick = BitBtn1Click
    end
    object btnPhoto: TBitBtn
      Left = 570
      Top = 67
      Width = 65
      Height = 25
      Caption = '&P'#25293' '#29031
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 10
      OnClick = btnPhotoClick
    end
    object pnlPhoto: TPanel
      Left = 0
      Top = 0
      Width = 72
      Height = 96
      Align = alLeft
      BevelOuter = bvNone
      Color = 16053492
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object imgPhoto: TImage
        Left = 0
        Top = 0
        Width = 72
        Height = 96
        Align = alClient
        Stretch = True
      end
    end
    object cbb1: TComboBox
      Left = 570
      Top = 8
      Width = 147
      Height = 21
      ItemHeight = 13
      TabOrder = 3
    end
  end
  object dbgrdhDb: TDBGridEh
    Left = 0
    Top = 96
    Width = 728
    Height = 387
    Align = alClient
    Ctl3D = True
    DataSource = dsQuery
    Flat = True
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #23435#20307
    Font.Style = []
    FooterColor = clWindow
    FooterFont.Charset = ANSI_CHARSET
    FooterFont.Color = clNavy
    FooterFont.Height = -13
    FooterFont.Name = #23435#20307
    FooterFont.Style = []
    FooterRowCount = 1
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentCtl3D = False
    ParentFont = False
    ReadOnly = True
    RowLines = 1
    SumList.Active = True
    TabOrder = 1
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -15
    TitleFont.Name = #23435#20307
    TitleFont.Style = []
    OnCellClick = dbgrdhDbCellClick
    Columns = <
      item
        EditButtons = <>
        Footer.Value = #21512#35745#65306
        Footer.ValueType = fvtStaticText
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #20154#21592#32534#21495
        Width = 70
      end
      item
        EditButtons = <>
        Footer.ValueType = fvtCount
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #23398'/'#24037#21495
        Width = 100
      end
      item
        EditButtons = <>
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #22995#21517
        Width = 80
      end
      item
        EditButtons = <>
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #20154#21592#31867#21035
        Width = 100
      end
      item
        EditButtons = <>
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #19987#19994
        Width = 120
      end
      item
        EditButtons = <>
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #37096#38376
        Width = 120
      end
      item
        EditButtons = <>
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #36523#20221#35777#21495
        Width = 100
      end
      item
        EditButtons = <>
        Footers = <>
        Title.Caption = #37096#38376#32534#21495
        Width = 80
      end
      item
        EditButtons = <>
        Footers = <>
        Title.Caption = #19987#19994#32534#21495
        Width = 80
      end
      item
        EditButtons = <>
        Footers = <>
        Title.Caption = #20154#21592#31867#21035#32534#30721
        Width = 80
      end>
  end
  object qryType: TADOQuery
    Connection = frmdm.conn
    LockType = ltUnspecified
    Parameters = <>
    Left = 184
    Top = 200
  end
  object dsType: TDataSource
    DataSet = qryType
    Left = 224
    Top = 200
  end
  object dsDept: TDataSource
    DataSet = qryDept
    Left = 224
    Top = 248
  end
  object qryDept: TADOQuery
    Connection = frmdm.conn
    LockType = ltUnspecified
    Parameters = <>
    Left = 184
    Top = 248
  end
  object qryArea: TADOQuery
    Connection = frmdm.conn
    LockType = ltUnspecified
    Parameters = <>
    Left = 184
    Top = 296
  end
  object dsArea: TDataSource
    DataSet = qryArea
    Left = 224
    Top = 296
  end
  object qrySpec: TADOQuery
    Connection = frmdm.conn
    LockType = ltUnspecified
    Parameters = <>
    Left = 432
    Top = 200
  end
  object dsSpec: TDataSource
    DataSet = qrySpec
    Left = 472
    Top = 200
  end
  object dsQuery: TDataSource
    DataSet = qryQuery
    Left = 472
    Top = 248
  end
  object qryQuery: TADOQuery
    Connection = frmdm.conn
    LockType = ltUnspecified
    Parameters = <>
    Left = 432
    Top = 248
  end
  object SaveDialog1: TSaveDialog
    Filter = 'Excel'#26684#24335'|*.xls|'#32593#39029#26684#24335'|*.htm|Word'#26684#24335'|*.rtf|'#25991#26412#25991#20214'|*.txt'
    Left = 432
    Top = 297
  end
end
