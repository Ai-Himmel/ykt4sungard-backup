object FrmDB: TFrmDB
  OldCreateOrder = False
  Left = 192
  Top = 160
  Height = 480
  Width = 696
  object SecureConnect: TADOConnection
    ConnectionString = 
      'Provider=IBMDADB2.1;User ID=db2inst4;Data Source=yktdemo;Locatio' +
      'n=10.108.0.222:50002;Mode=ReadWrite;Persist Security Info=False'
    LoginPrompt = False
    Provider = 'IBMDADB2.1'
    Left = 56
    Top = 56
  end
end
