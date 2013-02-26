object datreplistfrm: Tdatreplistfrm
  Left = 293
  Top = 122
  Width = 944
  Height = 634
  Caption = #26085#25253#34920#26597#35810
  Color = clBtnFace
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = #23435#20307
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 936
    Height = 600
    Align = alClient
    TabOrder = 0
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 934
      Height = 32
      Align = alTop
      TabOrder = 0
      object Label1: TLabel
        Left = 427
        Top = 8
        Width = 66
        Height = 16
        Caption = #26376#25253#34920#26597#35810
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object Panel3: TPanel
      Left = 1
      Top = 33
      Width = 934
      Height = 525
      Align = alClient
      TabOrder = 1
      object DBGrid1: TDBGrid
        Left = 1
        Top = 1
        Width = 932
        Height = 523
        Align = alClient
        TabOrder = 0
        TitleFont.Charset = GB2312_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -16
        TitleFont.Name = #23435#20307
        TitleFont.Style = []
        Columns = <
          item
            Expanded = False
            FieldName = 'trmonth'
            Title.Caption = #26376#24230
            Width = 52
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'OPERCODE'
            Title.Caption = #21307#29983#20195#30721
            Width = 66
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'stnumber'
            Title.Caption = #30475#30149#20154#25968
            Width = 85
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'OPERname'
            Title.Caption = #21307#29983#22995#21517
            Width = 63
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'totalmoney'
            Title.Caption = #25910#36153#37329#39069
            Width = 78
            Visible = True
          end>
      end
    end
    object Panel4: TPanel
      Left = 1
      Top = 558
      Width = 934
      Height = 41
      Align = alBottom
      TabOrder = 2
      object Label2: TLabel
        Left = 14
        Top = 14
        Width = 80
        Height = 16
        Caption = #21307#29983#20195#30721#65306
      end
      object Label4: TLabel
        Left = 252
        Top = 11
        Width = 48
        Height = 16
        Caption = #24180#24230#65306
      end
      object Button1: TButton
        Left = 565
        Top = 9
        Width = 65
        Height = 25
        Caption = #19978#19968#39029
        TabOrder = 0
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 635
        Top = 9
        Width = 73
        Height = 25
        Caption = #19979#19968#39029
        TabOrder = 1
        OnClick = Button2Click
      end
      object Button3: TButton
        Left = 792
        Top = 8
        Width = 65
        Height = 25
        Caption = #36820#22238
        TabOrder = 2
        OnClick = Button3Click
      end
      object doctor: TEdit
        Left = 82
        Top = 10
        Width = 153
        Height = 24
        TabOrder = 3
        Text = 'doctor'
      end
      object year: TEdit
        Left = 304
        Top = 8
        Width = 153
        Height = 24
        TabOrder = 4
      end
      object Button4: TButton
        Left = 477
        Top = 9
        Width = 80
        Height = 25
        Caption = #24180#24230#26597#35810
        TabOrder = 5
        OnClick = Button4Click
      end
      object outexcel: TButton
        Left = 712
        Top = 8
        Width = 73
        Height = 25
        Caption = #23548#20986'excel'
        TabOrder = 6
        OnClick = outexcelClick
      end
    end
  end
  object SaveDialog1: TSaveDialog
    Filter = '.xls|excel '#25991#20214
    Left = 129
    Top = 113
  end
end
