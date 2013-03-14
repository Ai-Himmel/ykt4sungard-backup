object fmBranchMan: TfmBranchMan
  Left = 403
  Top = 174
  Width = 359
  Height = 411
  Caption = '营业部分支管理'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  inline faBranchMan: TfaBranchMan
    Width = 351
    Height = 384
    Align = alClient
    inherited TreeView: TTreeView
      Width = 351
      Height = 384
    end
    inherited ImageList: TImageList
      Top = 32
    end
  end
end
