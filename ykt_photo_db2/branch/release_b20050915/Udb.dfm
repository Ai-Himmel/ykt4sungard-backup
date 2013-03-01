object dm: Tdm
  OldCreateOrder = False
  OnCreate = DataModuleCreate
  Left = 307
  Top = 199
  Height = 284
  Width = 400
  object ADOConnection1: TADOConnection
    LoginPrompt = False
    Mode = cmReadWrite
    Provider = 'IBMDADB2.1'
    Left = 80
    Top = 40
  end
end
