object FrmDownloadProg: TFrmDownloadProg
  Left = 315
  Top = 396
  BorderStyle = bsDialog
  Caption = '��������'
  ClientHeight = 123
  ClientWidth = 412
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object lbl1: TLabel
    Left = 16
    Top = 16
    Width = 377
    Height = 33
    AutoSize = False
    Caption = 
      '��ʾ��Ҫ�������µĳ�����ܼ���ʹ�ã����<����>��ť���������³���' +
      '��<ȡ��>�˳���'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlue
    Font.Height = -15
    Font.Name = '����'
    Font.Style = [fsBold]
    ParentFont = False
    WordWrap = True
  end
  object pbPosi: TProgressBar
    Left = 16
    Top = 56
    Width = 369
    Height = 17
    Min = 0
    Max = 100
    TabOrder = 0
  end
  object btnDownLoad: TButton
    Left = 310
    Top = 80
    Width = 75
    Height = 25
    Caption = '�� ��'
    TabOrder = 1
    OnClick = btnDownLoadClick
  end
  object idhtp1: TIdHTTP
    MaxLineAction = maException
    OnWork = idhtp1Work
    OnWorkBegin = idhtp1WorkBegin
    AllowCookies = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.ContentRangeEnd = 0
    Request.ContentRangeStart = 0
    Request.Accept = 'text/html, */*'
    Request.BasicAuthentication = False
    Request.UserAgent = 'Mozilla/3.0 (compatible; Indy Library)'
    HTTPOptions = [hoForceEncodeParams]
  end
  object dlgSave1: TSaveDialog
    Filter = '��ִ�г���(*.exe)|*.exe'
    Title = 'ѡ�񱣴�Ŀ¼'
    Left = 32
  end
  object idntfrz1: TIdAntiFreeze
    Left = 64
  end
end
