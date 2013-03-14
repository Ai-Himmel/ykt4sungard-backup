unit UqhPreQuery;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  WorkViews, WVDBBinders, WVCmdReq, StdCtrls, WVCtrls, WVCmdTypeInfo,
  WVCmdProc, KCWVProcBinds,UCommData,DB;

type
  a = class(TObject)
  end;

procedure  qhPreQuery(Sender : TObject);

implementation

procedure  qhPreQuery(Sender : TObject);
var
  TmpWVCB : TWVComboBox;
  TmpDataSet : TDataSet;
begin
  TmpWVCB := Sender as TWVComboBox;
  if TmpWVCB.FieldName = '交易所' then
  begin
    dmCommData.rqGetExchKinds.SendCommand;
    tmpDataSet := TDataSet(dmCommData.WorkView.FieldByName('返回结果集').Data.AsObject);
       tmpDataSet.Open;
       tmpDataSet.First;

       TmpWVCB.Items.Clear;//清空品种
       //遍历结果集
       while not tmpDataSet.Eof do
       begin
            TmpWVCB.Items.Add(tmpDataSet.FieldByName('sstock_code').AsString);
           // +'-'+              tmpDataSet.FieldByName('sname2').AsString);
            tmpDataSet.Next;
       end;
  end;
  { TODO -o朱朋飞 -c待实现 : 根据Sender对象的参数来添加TWVRequest和TWVDBBinder,Tdataset,并且实现ComBox的备选项添加. }
end;

end.
