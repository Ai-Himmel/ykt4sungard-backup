object dm: Tdm
  OldCreateOrder = False
  OnCreate = DataModuleCreate
  Left = 307
  Top = 199
  Height = 284
  Width = 400
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=MSDASQL.1;Persist Security Info=False;Data Source=yktph' +
      'oto'
    LoginPrompt = False
    Mode = cmReadWrite
    Provider = 'MSDASQL.1'
    Left = 80
    Top = 40
  end
end
