inherited cmPubCardImp_nmg: TcmPubCardImp_nmg
  OldCreateOrder = True
  Left = 285
  object cpPubCard_nmg: TKCWVProcessor
    ID = '���п�nmg'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '������'
        FieldName = 'lsafe_level'
      end
      item
        ParamName = '��ʾ����'
        FieldName = 'sorder0'
      end
      item
        ParamName = '������'
        FieldName = 'sstation0'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�շѷ�ʽ'
        FieldName = 'lvol9'
      end
      item
        ParamName = '�շѽ��'
        FieldName = 'damt0'
      end
      item
        ParamName = 'Ʊ�ݺ���'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '�Ƿ񲻼�����'
        FieldName = 'sstatus1'
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
        ParamName = '��ʾ����'
        FieldName = 'sorder0'
      end
      item
        ParamName = '�ͻ����'
        FieldName = 'lsafe_level2'
      end
      item
        ParamName = '�շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '�ͻ�����'
        FieldName = 'sall_name'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'spager'
      end
      item
        ParamName = '���Ŵ���'
        FieldName = 'scert_no'
      end
      item
        ParamName = '֤������'
        FieldName = 'semail2'
      end
      item
        ParamName = '�Ա�'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '������'
        FieldName = 'stx_pwd'
      end
      item
        ParamName = '����ֵ'
        FieldName = 'lvol8'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '����Ա'
        FieldName = 'semp'
      end
      item
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '�����޶�'
        FieldName = 'lvol11'
      end
      item
        ParamName = '���޶�'
        FieldName = 'lvol12'
      end>
    RequestType = 846301
    KCDataset = Dataset
    Left = 14
    Top = 8
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 160
    Top = 8
  end
  object cqcashOperCancel: TKCWVProcessor
    ID = '��ֵ֧ȡ����nmg'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�ն˱��'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '��ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'sdate3'
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
    RequestType = 846324
    KCDataset = Dataset
    Left = 14
    Top = 104
  end
  object cpSetSmlMoney: TKCWVProcessor
    ID = 'СǮ����ֵnmg'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '������'
        FieldName = 'sstation1'
      end
      item
        ParamName = '�뿨���'
        FieldName = 'Lvol7'
      end
      item
        ParamName = '���״���'
        FieldName = 'lvol6'
      end
      item
        ParamName = '���'
        FieldName = 'damt0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol0'
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
        ParamName = '��ˮ��'
        FieldName = 'lserial1'
      end
      item
        ParamName = 'ҵ������'
        FieldName = 'sdate3'
      end
      item
        ParamName = '�������'
        FieldName = 'lvol8'
      end>
    RequestType = 846323
    KCDataset = Dataset
    Left = 14
    Top = 56
  end
end
