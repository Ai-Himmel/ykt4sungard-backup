inherited dmSubsidyImp: TdmSubsidyImp
  OldCreateOrder = True
  Left = 284
  Top = 199
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 312
    Top = 40
  end
  object cqimportSublidyList: TKCWVProcessor
    ID = '������Ϣ����'
    InputBindings = <
      item
        ParamName = 'ѧ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'scust_limit2'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '˳���'
        FieldName = 'lvol1'
      end
      item
        ParamName = '�������'
        FieldName = 'damt0'
      end
      item
        ParamName = '��ֹ����'
        FieldName = 'sdate2'
      end
      item
        ParamName = '����Ա'
        FieldName = 'scust_no'
      end
      item
        ParamName = '�����־'
        FieldName = 'scust_type'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
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
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
      end>
    RequestType = 847130
    KCDataset = Dataset
    Left = 40
    Top = 10
  end
  object cqSublidySend: TKCWVProcessor
    ID = '�·�'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = 'ժҪ'
        FieldName = 'semail'
      end
      item
        ParamName = '���ʽ'
        FieldName = 'lvol9'
      end
      item
        ParamName = 'Ʊ�ݺ���'
        FieldName = 'scust_auth2'
      end
      item
        ParamName = '����������'
        FieldName = 'lvol3'
      end
      item
        ParamName = '�����ܽ��'
        FieldName = 'damt0'
      end
      item
        ParamName = '���������֤��'
        FieldName = 'sname'
      end
      item
        ParamName = '����������'
        FieldName = 'semail2'
      end
      item
        ParamName = '������־'
        FieldName = 'smain_flag'
      end
      item
        ParamName = '����'
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
    RequestType = 847132
    KCDataset = Dataset
    Left = 40
    Top = 58
  end
  object cqsetSubsidyInfo: TKCWVQuery
    ID = '������Ϣ��ѯ'
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
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '״̬'
        FieldName = 'sstatus1'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'lvol10'
      end
      item
        ParamName = '����'
        FieldName = 'lvol11'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate2'
      end
      item
        ParamName = '��ʼ����'
        FieldName = 'sdate1'
      end
      item
        ParamName = '����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '���״̬'
        FieldName = 'sstatus4'
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
    RequestType = 847131
    Left = 40
    Top = 114
  end
  object cpsetSubsidyInfo: TKCWVProcessor
    ID = '������Ϣ����'
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
        FieldName = 'sstatus0'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '˳���'
        FieldName = 'lvol1'
      end
      item
        ParamName = 'ѧ����'
        FieldName = 'scust_auth'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '����'
        FieldName = 'lvol11'
      end
      item
        ParamName = '������'
        FieldName = 'damt0'
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
    RequestType = 847131
    KCDataset = Dataset
    Left = 40
    Top = 162
  end
  object cpPatchdel: TKCWVProcessor
    ID = '��������ɾ��'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '#������ַ'
        FieldName = 'sstation0'
      end
      item
        ParamName = '���κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '������־'
        FieldName = 'lwithdraw_flag'
      end
      item
        ParamName = '״̬'
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
    RequestType = 847131
    KCDataset = Dataset
    Left = 40
    Top = 206
  end
  object cpCheck: TKCWVProcessor
    ID = '���'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '����'
        FieldName = 'scust_limit2'
      end
      item
        ParamName = '������־'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '˳���'
        FieldName = 'lvol1'
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
    RequestType = 847131
    KCDataset = Dataset
    Left = 40
    Top = 250
  end
  object kcSubsidyRcv: TKCWVProcessor
    ID = '��������'
    InputBindings = <
      item
        ParamName = '#ְ������'
        FieldName = 'semp'
      end
      item
        ParamName = '�������κ�'
        FieldName = 'scust_limit'
      end
      item
        ParamName = '�ͻ���'
        FieldName = 'lvol0'
      end
      item
        ParamName = '���'
        FieldName = 'damt0'
      end
      item
        ParamName = '˳���'
        FieldName = 'lvol1'
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
    RequestType = 847129
    KCDataset = Dataset
    Left = 40
    Top = 298
  end
end
