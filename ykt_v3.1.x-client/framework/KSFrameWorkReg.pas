unit KSFrameWorkReg;

interface

procedure Register;

implementation

uses Classes, DesignUtils, KSFrames, WVCommands, KSClientConsts, KSEdits
  ,DsgnIntf;

procedure Register;
begin
  RegisterEditModule(TKSFrame,', KSFrameWorks, KSFrames, KSClientConsts');
  RegisterContextParamName(svDepartNoName);
  RegisterContextParamName(svDepartNameName);
  RegisterContextParamName(svOperatorNoName);
  RegisterContextParamName(svOperatorNameName);
  RegisterContextParamName(svLoginStatusName);
  RegisterContextParamName(svMACAddressName);
  RegisterContextParamName(svOperatorPasswordName);
  RegisterContextParamName(svOperatorMenuAuthName);
  RegisterContextParamName(svSystemDateName);
  RegisterContextParamName(svProhibitMarketsName);
  RegisterContextParamName(svProhibitMoneyName);
  RegisterContextParamName(svCompanyNameName);
  RegisterComponents('Users', [TAccountInputMethods,TPasswordInputMethod]);
  RegisterComponents('UserCtrls', [TKSAccountEdit]);
  RegisterComponentEditor(TAccountInputMethods,TCollectionEditor);
end;

end.
