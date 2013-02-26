object datemngfrm: Tdatemngfrm
  Left = 235
  Top = 103
  Caption = 'VIP'#29992#25143#31649#29702
  ClientHeight = 555
  ClientWidth = 984
  Color = clBtnFace
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = #23435#20307
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 984
    Height = 555
    Align = alClient
    TabOrder = 0
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 982
      Height = 32
      Align = alTop
      TabOrder = 0
      object Label1: TLabel
        Left = 398
        Top = 4
        Width = 124
        Height = 23
        Caption = 'VIP'#29992#25143#31649#29702
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlue
        Font.Height = -21
        Font.Name = #21326#25991#23435#20307
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object Panel3: TPanel
      Left = 1
      Top = 33
      Width = 982
      Height = 435
      Align = alClient
      TabOrder = 1
      object Panel5: TPanel
        Left = 1
        Top = 1
        Width = 980
        Height = 433
        Align = alClient
        Caption = 'Panel5'
        TabOrder = 0
        object DBGrid1: TDBGrid
          Left = 1
          Top = 1
          Width = 978
          Height = 431
          Align = alClient
          DataSource = DataSource1
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
          ReadOnly = True
          TabOrder = 0
          TitleFont.Charset = GB2312_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -16
          TitleFont.Name = #23435#20307
          TitleFont.Style = []
          OnCellClick = DBGrid1CellClick
          Columns = <
            item
              Expanded = False
              FieldName = 'STUEMP_NO'
              Title.Caption = #23398#24037#21495
              Width = 79
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'TIMS'
              Title.Caption = #21487#29992#27425#25968
              Width = 127
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'OPERATOR'
              Title.Caption = #25805#20316#21592
              Width = 153
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'RESERVE'
              Title.Caption = #22791#27880
              Width = 302
              Visible = True
            end>
        end
      end
    end
    object Panel4: TPanel
      Left = 1
      Top = 468
      Width = 982
      Height = 86
      Align = alBottom
      TabOrder = 2
      object Label14: TLabel
        Left = 33
        Top = 31
        Width = 64
        Height = 16
        Caption = #23398#24037#21495#65306
      end
      object Label2: TLabel
        Left = 281
        Top = 31
        Width = 80
        Height = 16
        Caption = #21487#29992#27425#25968#65306
      end
      object datemod: TButton
        Left = 595
        Top = 31
        Width = 57
        Height = 25
        Caption = #20462#25913
        TabOrder = 0
        OnClick = datemodClick
      end
      object deldate: TButton
        Left = 667
        Top = 31
        Width = 55
        Height = 25
        Caption = #21024#38500
        TabOrder = 1
        OnClick = deldateClick
      end
      object datestr: TEdit
        Left = 108
        Top = 27
        Width = 157
        Height = 24
        TabOrder = 2
      end
      object dateadd: TButton
        Left = 524
        Top = 31
        Width = 58
        Height = 25
        Caption = #28155#21152
        TabOrder = 3
        OnClick = dateaddClick
      end
      object money: TEdit
        Left = 355
        Top = 29
        Width = 157
        Height = 24
        TabOrder = 4
      end
    end
  end
  object DataSource1: TDataSource
    Left = 169
    Top = 113
  end
  object SaveDialog1: TSaveDialog
    Filter = '.xls|excel '#25991#20214
    Left = 129
    Top = 113
  end
end
