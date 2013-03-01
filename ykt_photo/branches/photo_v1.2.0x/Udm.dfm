object frmdm: Tfrmdm
  OldCreateOrder = False
  OnCreate = DataModuleCreate
  Left = 475
  Top = 357
  Height = 336
  Width = 469
  object conn: TADOConnection
    ConnectionString = 
      'Provider=MSDASQL.1;Password=kingstar;Persist Security Info=True;' +
      'User ID=ykt_cur;Data Source=yktdb'
    LoginPrompt = False
    Provider = 'MSDASQL.1'
    Left = 8
    Top = 8
  end
end
