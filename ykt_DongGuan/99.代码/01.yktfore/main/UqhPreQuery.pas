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
  if TmpWVCB.FieldName = '������' then
  begin
    dmCommData.rqGetExchKinds.SendCommand;
    tmpDataSet := TDataSet(dmCommData.WorkView.FieldByName('���ؽ����').Data.AsObject);
       tmpDataSet.Open;
       tmpDataSet.First;

       TmpWVCB.Items.Clear;//���Ʒ��
       //���������
       while not tmpDataSet.Eof do
       begin
            TmpWVCB.Items.Add(tmpDataSet.FieldByName('sstock_code').AsString);
           // +'-'+              tmpDataSet.FieldByName('sname2').AsString);
            tmpDataSet.Next;
       end;
  end;
  { TODO -o����� -c��ʵ�� : ����Sender����Ĳ��������TWVRequest��TWVDBBinder,Tdataset,����ʵ��ComBox�ı�ѡ�����. }
end;

end.
