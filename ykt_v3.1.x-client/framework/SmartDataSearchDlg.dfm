object dlgSmartSearchDataset: TdlgSmartSearchDataset
  Left = 265
  Top = 188
  BorderStyle = bsDialog
  Caption = '�ڱ���в�������'
  ClientHeight = 363
  ClientWidth = 516
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
    Width = 516
    Height = 363
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
      Width = 519
      Height = 319
      ParentColor = True
      TabOrder = 0
      object cbIsUpperLowerCase: TCheckBox
        Left = 12
        Top = 297
        Width = 97
        Height = 17
        Caption = '��Сд����'
        TabOrder = 3
      end
      object rgDirection: TRadioGroup
        Left = 12
        Top = 221
        Width = 221
        Height = 73
        Caption = '����'
        Items.Strings = (
          '���(&B)'
          '��ǰ(&F)')
        TabOrder = 1
      end
      object rgOrigin: TRadioGroup
        Left = 280
        Top = 221
        Width = 201
        Height = 73
        Caption = '��ѯ��ַ'
        Items.Strings = (
          '�ӹ�괦��¼(&C)'
          '�ӵ�һ����¼(&E)')
        TabOrder = 2
      end
      object GroupBox1: TGroupBox
        Left = 12
        Top = 8
        Width = 469
        Height = 209
        Caption = '��ѯ����'
        TabOrder = 0
        object Label1: TLabel
          Left = 12
          Top = 31
          Width = 36
          Height = 12
          Caption = '�ֶ���'
        end
        object Label2: TLabel
          Left = 12
          Top = 58
          Width = 48
          Height = 12
          Caption = '�ֶ��ı�'
        end
        object Label3: TLabel
          Left = 196
          Top = 31
          Width = 24
          Height = 12
          Caption = '����'
        end
        object Label4: TLabel
          Left = 196
          Top = 55
          Width = 24
          Height = 12
          Caption = '��ϵ'
        end
        object edFieldValue: TEdit
          Left = 64
          Top = 56
          Width = 121
          Height = 20
          TabOrder = 1
        end
        object cbbFieldName: TComboBox
          Left = 64
          Top = 27
          Width = 121
          Height = 20
          Style = csDropDownList
          ItemHeight = 12
          TabOrder = 0
        end
        object ComboBox1: TComboBox
          Left = 248
          Top = 27
          Width = 121
          Height = 20
          Style = csDropDownList
          ItemHeight = 12
          TabOrder = 2
          Items.Strings = (
            '����'
            '����'
            'С��'
            '������'
            '��С��'
            '������')
        end
        object ComboBox2: TComboBox
          Left = 248
          Top = 51
          Width = 121
          Height = 20
          Style = csDropDownList
          ItemHeight = 12
          TabOrder = 3
          Items.Strings = (
            '����'
            '����')
        end
      end
    end
    object ImageButton1: TBitBtn
      Left = 352
      Top = 328
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
      Left = 432
      Top = 328
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
    object ImageButton3: TBitBtn
      Left = 248
      Top = 328
      Width = 75
      Height = 25
      Caption = 'ImageButton3'
      TabOrder = 3
    end
    object ImageButton4: TBitBtn
      Left = 136
      Top = 328
      Width = 75
      Height = 25
      Caption = 'ˢ�����ݼ�'
      TabOrder = 4
    end
  end
end
