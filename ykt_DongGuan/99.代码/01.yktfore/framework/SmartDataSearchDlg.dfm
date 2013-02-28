object dlgSmartSearchDataset: TdlgSmartSearchDataset
  Left = 265
  Top = 188
  BorderStyle = bsDialog
  Caption = '在表格中查找数据'
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
    Font.Name = '宋体'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    StyleItemName = '对话框'
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
        Caption = '大小写区别'
        TabOrder = 3
      end
      object rgDirection: TRadioGroup
        Left = 12
        Top = 221
        Width = 221
        Height = 73
        Caption = '方向'
        Items.Strings = (
          '向后(&B)'
          '向前(&F)')
        TabOrder = 1
      end
      object rgOrigin: TRadioGroup
        Left = 280
        Top = 221
        Width = 201
        Height = 73
        Caption = '查询起址'
        Items.Strings = (
          '从光标处记录(&C)'
          '从第一条记录(&E)')
        TabOrder = 2
      end
      object GroupBox1: TGroupBox
        Left = 12
        Top = 8
        Width = 469
        Height = 209
        Caption = '查询条件'
        TabOrder = 0
        object Label1: TLabel
          Left = 12
          Top = 31
          Width = 36
          Height = 12
          Caption = '字段名'
        end
        object Label2: TLabel
          Left = 12
          Top = 58
          Width = 48
          Height = 12
          Caption = '字段文本'
        end
        object Label3: TLabel
          Left = 196
          Top = 31
          Width = 24
          Height = 12
          Caption = '条件'
        end
        object Label4: TLabel
          Left = 196
          Top = 55
          Width = 24
          Height = 12
          Caption = '关系'
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
            '等于'
            '大于'
            '小于'
            '不大于'
            '不小于'
            '不等于')
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
            '或者'
            '并且')
        end
      end
    end
    object ImageButton1: TBitBtn
      Left = 352
      Top = 328
      Width = 75
      Height = 25
      Hint = '确认操作'
      Caption = '&O 确认'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
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
      Hint = '关闭该界面，取消操作'
      Cancel = True
      Caption = '取消'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = '宋体'
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
      Caption = '刷新数据集'
      TabOrder = 4
    end
  end
end
