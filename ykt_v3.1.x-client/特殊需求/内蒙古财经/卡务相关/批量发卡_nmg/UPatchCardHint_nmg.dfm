object FrmPatchCardHint_nmg: TFrmPatchCardHint_nmg
  Left = 315
  Top = 118
  BorderIcons = [biMinimize, biMaximize]
  BorderStyle = bsDialog
  Caption = '����������ʾ'
  ClientHeight = 335
  ClientWidth = 436
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = '����'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 12
  object btnOk: TButton
    Left = 72
    Top = 296
    Width = 75
    Height = 25
    Caption = 'ȷ��(&O)'
    TabOrder = 3
    OnClick = btnOkClick
  end
  object btnCancle: TButton
    Left = 192
    Top = 296
    Width = 75
    Height = 25
    Caption = 'ȡ��(&C)'
    TabOrder = 4
    OnClick = btnCancleClick
  end
  object btnNext: TButton
    Left = 304
    Top = 296
    Width = 75
    Height = 25
    Caption = '��һ��(&N)'
    TabOrder = 5
    OnClick = btnNextClick
  end
  object RzGroupBox1: TRzGroupBox
    Left = 0
    Top = 0
    Width = 436
    Height = 49
    Align = alTop
    Caption = '��ǰ����С��'
    TabOrder = 0
    object RzLabGived: TRzLabel
      Left = 232
      Top = 15
      Width = 80
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      Blinking = True
      BlinkColor = clRed
      TextStyle = tsRaised
    end
    object RzLabel5: TRzLabel
      Left = 184
      Top = 15
      Width = 48
      Height = 12
      Caption = '�ѷ�����'
      BlinkColor = clRed
    end
    object RzLabSuccess: TRzLabel
      Left = 64
      Top = 32
      Width = 97
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      Blinking = True
      BlinkColor = clRed
      TextStyle = tsRaised
    end
    object RzLabel3: TRzLabel
      Left = 16
      Top = 34
      Width = 48
      Height = 12
      Caption = '�ѳɹ���'
      BlinkColor = clRed
    end
    object RzLabCount: TRzLabel
      Left = 104
      Top = 15
      Width = 57
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      Blinking = True
      BlinkColor = clRed
      TextStyle = tsRaised
    end
    object RzLabel1: TRzLabel
      Left = 16
      Top = 15
      Width = 84
      Height = 12
      Caption = '��������������'
      BlinkColor = clRed
    end
    object RzLabel7: TRzLabel
      Left = 184
      Top = 34
      Width = 48
      Height = 12
      Caption = '�Ѵ���'
      BlinkColor = clRed
    end
    object RzLabError: TRzLabel
      Left = 232
      Top = 32
      Width = 80
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      Blinking = True
      BlinkColor = clRed
      TextStyle = tsRaised
    end
  end
  object RzGroupBox2: TRzGroupBox
    Left = 0
    Top = 49
    Width = 436
    Height = 178
    Align = alTop
    Caption = '�����������˵�ժҪ��Ϣ'
    TabOrder = 1
    object Label1: TLabel
      Left = 24
      Top = 16
      Width = 42
      Height = 12
      Caption = 'ѧ/����'
    end
    object lblStuempNo: TLabel
      Left = 80
      Top = 16
      Width = 217
      Height = 13
      AutoSize = False
    end
    object Label2: TLabel
      Left = 40
      Top = 32
      Width = 24
      Height = 12
      Caption = '����'
    end
    object Label4: TLabel
      Left = 40
      Top = 48
      Width = 24
      Height = 12
      Caption = 'Ժϵ'
    end
    object Label5: TLabel
      Left = 40
      Top = 64
      Width = 24
      Height = 12
      Caption = 'רҵ'
    end
    object Label3: TLabel
      Left = 16
      Top = 80
      Width = 48
      Height = 12
      Caption = '�ͻ�����'
    end
    object lblCustType: TLabel
      Left = 80
      Top = 80
      Width = 217
      Height = 13
      AutoSize = False
    end
    object lblSpec: TLabel
      Left = 80
      Top = 64
      Width = 217
      Height = 13
      AutoSize = False
    end
    object lblDept: TLabel
      Left = 80
      Top = 48
      Width = 217
      Height = 13
      AutoSize = False
    end
    object lblName: TLabel
      Left = 80
      Top = 32
      Width = 217
      Height = 13
      AutoSize = False
    end
    object lblShowCardNo: TLabel
      Left = 16
      Top = 113
      Width = 48
      Height = 12
      Caption = '��ʾ��Ϣ'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object lbl2: TLabel
      Left = 16
      Top = 159
      Width = 48
      Height = 12
      Caption = '����Ч��'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object lblFormat: TLabel
      Left = 208
      Top = 159
      Width = 97
      Height = 12
      AutoSize = False
      Caption = '��ʽ��YYYYMMDD'
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = '����'
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 16
      Top = 96
      Width = 48
      Height = 12
      Caption = 'Ӧ�ս��'
    end
    object lblTotMoney: TLabel
      Left = 80
      Top = 96
      Width = 217
      Height = 13
      AutoSize = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = '����'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblTipInfo: TLabel
      Left = 80
      Top = 112
      Width = 345
      Height = 36
      AutoSize = False
      WordWrap = True
    end
    object edtEndDate: TRzEdit
      Left = 80
      Top = 153
      Width = 121
      Height = 20
      TabOrder = 0
    end
  end
  object RzGroupBox3: TRzGroupBox
    Left = 0
    Top = 227
    Width = 436
    Height = 56
    Align = alTop
    Caption = '������ʾ'
    TabOrder = 2
    object lblWarning: TLabel
      Left = 3
      Top = 16
      Width = 428
      Height = 33
      AutoSize = False
    end
  end
end
