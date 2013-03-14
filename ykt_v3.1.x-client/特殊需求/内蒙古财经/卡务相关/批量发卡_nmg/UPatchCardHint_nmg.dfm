object FrmPatchCardHint_nmg: TFrmPatchCardHint_nmg
  Left = 315
  Top = 118
  BorderIcons = [biMinimize, biMaximize]
  BorderStyle = bsDialog
  Caption = '批量发卡提示'
  ClientHeight = 335
  ClientWidth = 436
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = '宋体'
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
    Caption = '确定(&O)'
    TabOrder = 3
    OnClick = btnOkClick
  end
  object btnCancle: TButton
    Left = 192
    Top = 296
    Width = 75
    Height = 25
    Caption = '取消(&C)'
    TabOrder = 4
    OnClick = btnCancleClick
  end
  object btnNext: TButton
    Left = 304
    Top = 296
    Width = 75
    Height = 25
    Caption = '下一个(&N)'
    TabOrder = 5
    OnClick = btnNextClick
  end
  object RzGroupBox1: TRzGroupBox
    Left = 0
    Top = 0
    Width = 436
    Height = 49
    Align = alTop
    Caption = '当前发卡小结'
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
      Caption = '已放弃：'
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
      Caption = '已成功：'
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
      Caption = '批量发卡总数：'
      BlinkColor = clRed
    end
    object RzLabel7: TRzLabel
      Left = 184
      Top = 34
      Width = 48
      Height = 12
      Caption = '已错误：'
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
    Caption = '即将发卡的人的摘要信息'
    TabOrder = 1
    object Label1: TLabel
      Left = 24
      Top = 16
      Width = 42
      Height = 12
      Caption = '学/工号'
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
      Caption = '姓名'
    end
    object Label4: TLabel
      Left = 40
      Top = 48
      Width = 24
      Height = 12
      Caption = '院系'
    end
    object Label5: TLabel
      Left = 40
      Top = 64
      Width = 24
      Height = 12
      Caption = '专业'
    end
    object Label3: TLabel
      Left = 16
      Top = 80
      Width = 48
      Height = 12
      Caption = '客户类型'
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
      Caption = '提示信息'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object lbl2: TLabel
      Left = 16
      Top = 159
      Width = 48
      Height = 12
      Caption = '卡有效期'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object lblFormat: TLabel
      Left = 208
      Top = 159
      Width = 97
      Height = 12
      AutoSize = False
      Caption = '格式：YYYYMMDD'
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 16
      Top = 96
      Width = 48
      Height = 12
      Caption = '应收金额'
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
      Font.Name = '宋体'
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
    Caption = '操作提示'
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
