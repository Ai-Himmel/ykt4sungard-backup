inherited dmCardLibrarytImp: TdmCardLibrarytImp
  OldCreateOrder = True
  Left = 245
  Top = 190
  Width = 590
  object cqsetCardType: TKCWVQuery
    ID = '������ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '��������'
        FieldName = 'Sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846101
    Left = 40
    Top = 10
  end
  object cpsetCardType: TKCWVProcessor
    ID = '���������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '��������'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = '�����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '���ɱ���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '���������'
        FieldName = 'sname'
      end
      item
        ParamName = '��;'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '�ܷ�����'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '�ܷ񲹰�'
        FieldName = 'sstatus2'
      end
      item
        ParamName = '�ܷ��ʧ'
        FieldName = 'sstatus3'
      end
      item
        ParamName = '�Ƿ�֧�ֶ�Ǯ��'
        FieldName = 'sstatus4'
      end
      item
        ParamName = 'ʹ��״̬'
        FieldName = 'smarket_code'
      end
      item
        ParamName = '��Ч����'
        FieldName = 'lvol2'
      end
      item
        ParamName = '���õ��շ����'
        FieldName = 'vsvarstr1'
      end
      item
        ParamName = 'Ĭ���շ����'
        FieldName = 'lvol5'
      end
      item
        ParamName = '�Ƿ�������'
        FieldName = 'smarket_code2'
      end
      item
        ParamName = '���������'
        FieldName = 'lvol3'
        DefaultValue = 0
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
    RequestType = 846101
    KCDataset = Dataset
    Left = 40
    Top = 58
  end
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 296
    Top = 8
  end
  object cqcardInfoQuery: TKCWVQuery
    ID = '��Ƭ��Ϣ��ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������'
        FieldName = 'lvol0'
      end
      item
        ParamName = 'ת�����Ա'
        FieldName = 'semp_no'
      end
      item
        ParamName = '��ʾ����'
        FieldName = 'scust_no'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '״̬'
        FieldName = 'Sstatus1'
      end
      item
        ParamName = 'ת������Ա'
        FieldName = 'semp_no2'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846106
    Left = 40
    Top = 106
  end
  object cqCardIn: TKCWVProcessor
    ID = '��Ƭ����'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��ʼ���'
        FieldName = 'scust_no'
      end
      item
        ParamName = '�������'
        FieldName = 'scust_no2'
      end
      item
        ParamName = 'ת�����Ա'
        FieldName = 'scust_limit2'
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
    RequestType = 846102
    KCDataset = Dataset
    Left = 40
    Top = 154
  end
  object cqCardOut: TKCWVProcessor
    ID = '��Ƭ�Ͻ�'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��ʼ���'
        FieldName = 'scust_no'
      end
      item
        ParamName = '�������'
        FieldName = 'scust_no2'
      end
      item
        ParamName = 'ת�����Ա'
        FieldName = 'scust_limit2'
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
    RequestType = 846103
    KCDataset = Dataset
    Left = 40
    Top = 202
  end
  object cqCardTrans: TKCWVProcessor
    ID = '��Ƭת��'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��ʼ���'
        FieldName = 'scust_no'
      end
      item
        ParamName = '�������'
        FieldName = 'scust_no2'
      end
      item
        ParamName = 'ת�����Ա'
        FieldName = 'scust_limit2'
      end
      item
        ParamName = 'ת������'
        FieldName = 'scust_limit'
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
    RequestType = 846104
    KCDataset = Dataset
    Left = 40
    Top = 250
  end
  object cqCardDestory: TKCWVProcessor
    ID = '��Ƭ����'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '������'
        FieldName = 'lvol0'
      end
      item
        ParamName = '��ʼ���'
        FieldName = 'scust_no'
      end
      item
        ParamName = 'ת�����Ա'
        FieldName = 'scust_limit2'
      end
      item
        ParamName = '���ϱ�־'
        FieldName = 'sstatus3'
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
    RequestType = 846105
    KCDataset = Dataset
    Left = 40
    Top = 298
  end
  object cqsetMoneyInfo: TKCWVQuery
    ID = 'Ǯ����ѯ'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '��������'
        FieldName = 'Sstatus0'
      end>
    OutputBindings = <
      item
        ParamName = '��ѯ�����'
        FieldName = '@Dataset'
      end
      item
        ParamName = '������'
        FieldName = '@Return'
      end
      item
        ParamName = '������Ϣ'
        FieldName = 'vsmess'
      end>
    RequestType = 846201
    Left = 160
    Top = 58
  end
  object cpsetMoneyInfo: TKCWVProcessor
    ID = 'Ǯ������'
    InputBindings = <
      item
        ParamName = '#Ӫҵ������'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '��������'
        FieldName = 'Sstatus0'
      end
      item
        ParamName = 'Ǯ������'
        FieldName = 'sname'
      end
      item
        ParamName = 'Ǯ����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '����ֵ��'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�Ƿ�ʹ��'
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
      end>
    RequestType = 846201
    KCDataset = Dataset
    Left = 160
    Top = 10
  end
end
