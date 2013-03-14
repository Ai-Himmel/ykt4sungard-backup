unit UAGateBanManage;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  USMSetTreeParamsTemp, WorkViews, DBActns, ActnList, WVDBBinders,
  WVCmdReq, Db, DBCtrls, RzDBNav, Grids, DBGrids, RzDBGrid, ComCtrls,
  RzTreeVw, RzButton, RzRadChk, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  RzTabs, Mask, WVCtrls;

type
  TfaGateBanManage = class(TfaSMSetTreeParamsTemp)
    RzTreeView1: TRzTreeView;
    UIPanel3: TUIPanel;
    WVLabel1: TWVLabel;
    WVEdit1: TWVEdit;
    WVLabel2: TWVLabel;
    WVEdit2: TWVEdit;
    WVLabel3: TWVLabel;
    WVEdit3: TWVEdit;
    WVLabel4: TWVLabel;
    WVEdit4: TWVEdit;
    WVLabel5: TWVLabel;
    WVEdit5: TWVEdit;
    UIPanel4: TUIPanel;
    WVLabel6: TWVLabel;
    UIPanel5: TUIPanel;
    WVLabel7: TWVLabel;
    WVLabel8: TWVLabel;
    RzDBGrid1: TRzDBGrid;
    UIPanel6: TUIPanel;
    WVLabel9: TWVLabel;
    RzDBGrid2: TRzDBGrid;
    ImageButton1: TImageButton;
    ImageButton2: TImageButton;
    WVLabel10: TWVLabel;
    WVEdit6: TWVEdit;
    WVLabel11: TWVLabel;
    WVLabel12: TWVLabel;
    WVEdit7: TWVEdit;
    WVLabel13: TWVLabel;
    WVEdit8: TWVEdit;
    ImageButton3: TImageButton;
    WVLabel14: TWVLabel;
    WVEdit9: TWVEdit;
    WVLabel15: TWVLabel;
    WVEdit10: TWVEdit;
    WVLabel16: TWVLabel;
    WVEdit11: TWVEdit;
    WVLabel17: TWVLabel;
    WVEdit12: TWVEdit;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  faGateBanManage: TfaGateBanManage;

implementation
uses KsFrameworks;


{$R *.DFM}
initialization
  TUIStdClassFactory.Create('门禁机黑名单设置',TfaGateBanManage);

end.
