object dlgSearchDataset: TdlgSearchDataset
  Left = 213
  Top = 200
  BorderStyle = bsDialog
  Caption = '�ڱ���в�������'
  ClientHeight = 259
  ClientWidth = 352
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object UIPanel1: TUIPanel
    Left = 0
    Top = 0
    Width = 352
    Height = 259
    Align = alClient
    BevelOuter = bvNone
    Color = 16184303
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = '����'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    StyleItemName = '�Ի���'
    object Panel1: TPanel
      Left = 2
      Top = 2
      Width = 351
      Height = 215
      ParentColor = True
      TabOrder = 0
      object rgDirection: TRadioGroup
        Left = 12
        Top = 109
        Width = 133
        Height = 73
        Caption = '����'
        Items.Strings = (
          '���(&B)'
          '��ǰ(&F)')
        TabOrder = 0
      end
      object rgOrigin: TRadioGroup
        Left = 176
        Top = 109
        Width = 161
        Height = 73
        Caption = '��ѯ��ַ'
        Items.Strings = (
          '�ӹ�괦��¼(&C)'
          '�ӵ�һ����¼(&E)')
        TabOrder = 1
      end
      object RzGroupBox1: TRzGroupBox
        Left = 12
        Top = 9
        Width = 324
        Height = 89
        Caption = '��ѯ����'
        TabOrder = 2
        Transparent = True
        object Label1: TLabel
          Left = 12
          Top = 31
          Width = 36
          Height = 12
          Caption = '�ֶ���'
          Transparent = True
        end
        object Label2: TLabel
          Left = 12
          Top = 58
          Width = 48
          Height = 12
          Caption = '�ֶ��ı�'
          Transparent = True
        end
        object cbbFieldName: TRzComboBox
          Left = 80
          Top = 24
          Width = 233
          Height = 20
          Ctl3D = False
          FrameHotTrack = True
          FrameVisible = True
          ItemHeight = 12
          ParentCtl3D = False
          TabOrder = 0
        end
        object edFieldValue: TRzEdit
          Left = 80
          Top = 56
          Width = 233
          Height = 20
          FrameHotTrack = True
          FrameVisible = True
          TabOrder = 1
        end
      end
      object cbIsUpperLowerCase: TRzCheckBox
        Left = 16
        Top = 192
        Width = 115
        Height = 17
        Caption = '��Сд����'
        FrameColor = 8409372
        HighlightColor = 2203937
        HotTrack = True
        HotTrackColor = 3983359
        HotTrackColorType = htctActual
        State = cbUnchecked
        TabOrder = 3
      end
    end
    object ImageButton1: TBitBtn
      Left = 184
      Top = 224
      Width = 75
      Height = 25
      Hint = 'ȷ�ϲ���'
      Caption = '&O ȷ��'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ModalResult = 6
      ParentFont = False
      TabOrder = 1
    end
    object ImageButton2: TBitBtn
      Left = 264
      Top = 224
      Width = 75
      Height = 25
      Hint = '�رոý��棬ȡ������'
      Cancel = True
      Caption = 'ȡ��'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '����'
      Font.Style = [fsBold]
      ModalResult = 2
      ParentFont = False
      TabOrder = 2
    end
  end
end
