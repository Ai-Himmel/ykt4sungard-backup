object frmMain: TfrmMain
  Left = 263
  Top = 143
  BorderStyle = bsDialog
  Caption = '手持机测试Demo - 金仕达20051019'
  ClientHeight = 336
  ClientWidth = 666
  Color = clBtnFace
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = '宋体'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesktopCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 12
  object GroupBox1: TGroupBox
    Left = 8
    Top = 3
    Width = 209
    Height = 113
    TabOrder = 0
    object Label1: TLabel
      Left = 32
      Top = 24
      Width = 36
      Height = 12
      Alignment = taRightJustify
      Caption = '端口：'
    end
    object Label2: TLabel
      Left = 20
      Top = 48
      Width = 48
      Height = 12
      Alignment = taRightJustify
      Caption = '波特率：'
    end
    object cbbComPort: TComboBox
      Left = 73
      Top = 21
      Width = 112
      Height = 20
      Style = csDropDownList
      ItemHeight = 12
      TabOrder = 0
      Items.Strings = (
        'COM1'
        'COM2'
        'COM3'
        'COM4'
        'COM5'
        'COM6'
        'COM7'
        'COM8'
        'COM9'
        'COM10'
        'COM11'
        'COM12'
        'COM13'
        'COM14')
    end
    object cbbComBand: TComboBox
      Left = 73
      Top = 45
      Width = 112
      Height = 20
      Style = csDropDownList
      ItemHeight = 12
      TabOrder = 1
      Items.Strings = (
        '9600'
        '19200'
        '38400')
    end
    object btnCtrlCOM: TButton
      Left = 80
      Top = 72
      Width = 105
      Height = 25
      Caption = '打开串口'
      TabOrder = 2
      OnClick = btnCtrlCOMClick
    end
  end
  object btnExit: TButton
    Left = 544
    Top = 305
    Width = 113
    Height = 25
    Caption = '关闭'
    TabOrder = 7
    OnClick = btnExitClick
  end
  object Panel1: TPanel
    Left = 8
    Top = 123
    Width = 209
    Height = 206
    BevelOuter = bvLowered
    TabOrder = 1
    object Label3: TLabel
      Left = 16
      Top = 137
      Width = 24
      Height = 12
      Caption = '机号'
    end
    object lblPhyId: TLabel
      Left = 40
      Top = 13
      Width = 137
      Height = 12
      AutoSize = False
      Caption = '物理ID：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object lblVerDate: TLabel
      Left = 40
      Top = 40
      Width = 137
      Height = 12
      AutoSize = False
      Caption = '程序版本：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object lblTermType: TLabel
      Left = 40
      Top = 66
      Width = 137
      Height = 12
      AutoSize = False
      Caption = '机型：'
      Font.Charset = GB2312_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = '宋体'
      Font.Style = []
      ParentFont = False
    end
    object btnReadTerm: TButton
      Left = 40
      Top = 90
      Width = 121
      Height = 25
      Caption = '读取手持机信息'
      TabOrder = 0
      OnClick = btnReadTermClick
    end
    object edtTermNo: TEdit
      Left = 43
      Top = 133
      Width = 63
      Height = 20
      TabOrder = 1
    end
    object btnSetTermNo: TButton
      Left = 119
      Top = 131
      Width = 75
      Height = 25
      Caption = '设置机号'
      TabOrder = 2
      OnClick = btnSetTermNoClick
    end
    object btnEmptyFlash: TButton
      Left = 40
      Top = 168
      Width = 113
      Height = 25
      Caption = '初始化为出厂状态'
      TabOrder = 3
      OnClick = btnEmptyFlashClick
    end
  end
  object edtUserParam: TEdit
    Left = 226
    Top = 274
    Width = 430
    Height = 24
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Fixedsys'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    TabOrder = 5
  end
  object btnUpUserParam: TButton
    Left = 226
    Top = 305
    Width = 113
    Height = 25
    Caption = '上传设备主参数'
    TabOrder = 6
    OnClick = btnUpUserParamClick
  end
  object Panel2: TPanel
    Left = 225
    Top = 8
    Width = 433
    Height = 73
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 2
    object cbbWorkKeys: TComboBox
      Left = 9
      Top = 11
      Width = 165
      Height = 20
      ItemHeight = 12
      TabOrder = 0
    end
    object btnSetWorkKey: TButton
      Left = 202
      Top = 8
      Width = 97
      Height = 25
      Caption = '设置工作密钥'
      TabOrder = 1
      OnClick = btnSetWorkKeyClick
    end
    object edtCommision: TEdit
      Left = 9
      Top = 42
      Width = 165
      Height = 20
      CharCase = ecUpperCase
      MaxLength = 8
      TabOrder = 3
    end
    object btnSetComm: TButton
      Left = 202
      Top = 39
      Width = 97
      Height = 25
      Caption = '设置物理ID号'
      TabOrder = 4
      OnClick = btnSetCommClick
    end
    object btnDelAllBlack: TButton
      Left = 314
      Top = 8
      Width = 113
      Height = 25
      Caption = '删除所有黑名单'
      TabOrder = 2
      OnClick = btnDelAllBlackClick
    end
    object btnSetCommision: TButton
      Left = 314
      Top = 39
      Width = 113
      Height = 25
      Caption = '设置物理ID号'
      TabOrder = 5
      Visible = False
      OnClick = btnSetCommClick
    end
  end
  object Panel3: TPanel
    Left = 225
    Top = 87
    Width = 433
    Height = 108
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 3
    object edtBlkCardId: TEdit
      Left = 9
      Top = 13
      Width = 165
      Height = 20
      TabOrder = 0
    end
    object btnDownBlk: TButton
      Left = 202
      Top = 10
      Width = 97
      Height = 25
      Caption = '下传黑名单'
      TabOrder = 1
      OnClick = btnDownBlkClick
    end
    object btnDelBlk: TButton
      Left = 314
      Top = 10
      Width = 113
      Height = 25
      Caption = '删除黑名单'
      TabOrder = 2
      OnClick = btnDelBlkClick
    end
    object edtBlkVersion: TEdit
      Left = 9
      Top = 77
      Width = 165
      Height = 20
      MaxLength = 12
      TabOrder = 6
    end
    object btnUpBlkVer: TButton
      Left = 202
      Top = 74
      Width = 97
      Height = 25
      Caption = '上传黑名单版本'
      TabOrder = 7
      OnClick = btnUpBlkVerClick
    end
    object btnDownBlkVer: TButton
      Left = 314
      Top = 74
      Width = 113
      Height = 25
      Caption = '下传黑名单版本'
      TabOrder = 8
      OnClick = btnDownBlkVerClick
    end
    object edtBlkExpire: TEdit
      Left = 9
      Top = 45
      Width = 165
      Height = 20
      MaxLength = 12
      TabOrder = 3
    end
    object btnDownBlkExpire: TButton
      Left = 314
      Top = 41
      Width = 113
      Height = 25
      Caption = '下传有效期'
      TabOrder = 5
      OnClick = btnDownBlkExpireClick
    end
    object btnUpBlkExpire: TButton
      Left = 202
      Top = 42
      Width = 97
      Height = 25
      Caption = '上传有效期'
      TabOrder = 4
      OnClick = btnUpBlkExpireClick
    end
  end
  object pnl1: TPanel
    Left = 225
    Top = 200
    Width = 433
    Height = 69
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 4
    object btnUpRecord: TButton
      Left = 340
      Top = 6
      Width = 84
      Height = 25
      Caption = '上传流水'
      TabOrder = 1
      OnClick = btnUpRecordClick
    end
    object edtSerial: TEdit
      Left = 7
      Top = 8
      Width = 326
      Height = 20
      ReadOnly = True
      TabOrder = 0
    end
    object btnEndUpSerial: TButton
      Left = 200
      Top = 36
      Width = 97
      Height = 25
      Caption = '结束流水'
      TabOrder = 4
      OnClick = btnEndUpSerialClick
    end
    object btnViewLogDetail: TButton
      Left = 312
      Top = 36
      Width = 113
      Height = 25
      Caption = '查看流水详细信息'
      TabOrder = 5
      OnClick = btnViewLogDetailClick
    end
    object btnUpHisSerial: TButton
      Left = 97
      Top = 36
      Width = 97
      Height = 25
      Caption = '上传历史流水'
      TabOrder = 3
      OnClick = btnUpHisSerialClick
    end
    object edtSerialNo: TEdit
      Left = 7
      Top = 38
      Width = 81
      Height = 20
      TabOrder = 2
    end
  end
end
