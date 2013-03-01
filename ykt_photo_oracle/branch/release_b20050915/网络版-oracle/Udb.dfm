object dm: Tdm
  OldCreateOrder = False
  OnCreate = DataModuleCreate
  Left = 301
  Top = 269
  Height = 284
  Width = 400
  object ConnectPhoto: TADOConnection
    ConnectionString = 
      'Provider=MSDASQL.1;Password=dingsi;Persist Security Info=True;Us' +
      'er ID=System;Data Source=photo'
    LoginPrompt = False
    Provider = 'MSDASQL.1'
    Left = 64
    Top = 48
  end
end
