inherited cmCPUWaterImp: TcmCPUWaterImp
  OldCreateOrder = True
  Left = 285
  object cpRollBack: TKCWVProcessor
    ID = 'ʧ����Ϣ_cqcsgl'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '���ײο���'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�����'
        FieldName = 'saddr'
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
    Top = 112
  end
  object cpWaterTrans: TKCWVProcessor
    ID = 'ˮ��ת��_cqcsgl'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�ն˺�'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '���ײο���'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�����'
        FieldName = 'saddr'
      end
      item
        ParamName = '��������'
        FieldName = 'sstation1'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�����'
        FieldName = 'lvol7'
      end
      item
        ParamName = '���״���'
        FieldName = 'lvol6'
      end
      item
        ParamName = 'СǮ�����'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = 'ת�˽��'
        FieldName = 'lvol5'
      end
      item
        ParamName = '֧������'
        FieldName = 'lcert_code'
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
        ParamName = '�ն���ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '����ʱ��'
        FieldName = 'stime3'
      end
      item
        ParamName = '����ֵ'
        FieldName = 'lvol8'
      end
      item
        ParamName = '�ۿ���'
        FieldName = 'lvol5'
      end
      item
        ParamName = '��д���'
        FieldName = 'lvol9'
      end
      item
        ParamName = 'СǮ�����'
        FieldName = 'lsafe_level'
      end>
    RequestType = 850010
    KCDataset = Dataset
    Left = 32
    Top = 64
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 365
    Top = 16
  end
  object cpTradeCode: TKCWVProcessor
    ID = '���ײο���_cqcsgl'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�ն˺�'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = 'ʱ���'
        FieldName = 'scust_auth'
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
        ParamName = '���ײο���'
        FieldName = 'sphone3'
      end
      item
        ParamName = '�����'
        FieldName = 'saddr'
      end>
    RequestType = 850000
    KCDataset = Dataset
    Left = 32
    Top = 8
  end
end
