inherited faqhSetParamsTemp: TfaqhSetParamsTemp
  inherited pcPages: TRzPageControl
    FixedDimension = 19
    inherited tsQuery: TRzTabSheet
      inherited UIPanel1: TUIPanel
        inherited btnViewDetail: TBitBtn
          Left = 38
        end
        inherited ckAutoSetNewParams: TRzCheckBox
          Left = 120
        end
      end
    end
    inherited tsEdit: TRzTabSheet
      inherited UIPanel2: TUIPanel
        inherited DBNavigator: TRzDBNavigator
          Hints.Strings = ()
        end
      end
    end
  end
  inherited DataSource: TDataSource
    Left = 169
    Top = 287
  end
  inherited WorkView: TWorkView
    Top = 288
  end
  inherited QueryBinder: TWVDBBinder
    Left = 105
    Top = 287
  end
  inherited AddRequest: TWVRequest
    Left = 136
    Top = 320
  end
  inherited DeleteRequest: TWVRequest
    Left = 200
    Top = 320
  end
  inherited ChangeRequest: TWVRequest
    Left = 168
    Top = 320
  end
  inherited WVDataSource: TWVDataSource
    Left = 137
    Top = 287
  end
  inherited alDatasetActions: TActionList
    Left = 72
    Top = 321
  end
end
