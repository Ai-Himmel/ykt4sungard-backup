inherited cmWaterTransImp: TcmWaterTransImp
  OldCreateOrder = True
  Left = 285
  object cpRollBack: TKCWVProcessor
    ID = 'ʧ����Ϣ'
    InputBindings = <
      item
        ParamName = '������ˮ'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��ֵ��ˮ'
        FieldName = 'lvol2'
      end
      item
        ParamName = 'ʧ�ܱ�־'
        FieldName = 'lvol3'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 847302
    KCDataset = Dataset
    Left = 32
    Top = 56
  end
  object cpWaterTrans: TKCWVProcessor
    ID = 'ˮ��ת��11'
    InputBindings = <
      item
        ParamName = '���׿���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��ֵ���'
        FieldName = 'damt4'
      end
      item
        ParamName = '����Ա����'
        FieldName = 'scust_no'
      end
      item
        ParamName = '��Ǯ�����'
        FieldName = 'damt1'
      end
      item
        ParamName = '��Ǯ������'
        FieldName = 'lvol4'
      end
      item
        ParamName = 'СǮ������'
        FieldName = 'lvol5'
      end
      item
        ParamName = 'СǮ�����'
        FieldName = 'Damt3'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end>
    OutputBindings = <
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end
      item
        ParamName = '��̨��ˮ��'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��ˮ��̨��ˮ��'
        FieldName = 'lvol1'
      end
      item
        ParamName = '��ֵ���'
        FieldName = 'damt1'
      end
      item
        ParamName = '��Ǯ������'
        FieldName = 'Lvol9'
      end
      item
        ParamName = '��Ǯ�����'
        FieldName = 'Damt0'
      end
      item
        ParamName = 'СǮ������'
        FieldName = 'lvol5'
      end
      item
        ParamName = 'СǮ�����'
        FieldName = 'Damt2'
      end>
    RequestType = 847301
    KCDataset = Dataset
    Left = 32
    Top = 8
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 365
    Top = 16
  end
end
