inherited dmSubSystemImp: TdmSubSystemImp
  OldCreateOrder = True
  Left = 444
  Top = 169
  Height = 581
  Width = 645
  object Dataset: TKCDataset
    MaxRows = 0
    AggregateFields = <>
    RequestType = 0
    Params = <>
    Left = 88
    Top = 16
  end
  object cqSetPOSInfo: TKCWVQuery
    ID = 'POS��Ϣά����ѯ'
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
        ParamName = '������־'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '�豸���'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�����̻���'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '�豸�ն˺�'
        FieldName = 'sname'
      end
      item
        ParamName = '�ն����к�'
        FieldName = 'sname2'
      end
      item
        ParamName = '�豸�ͺ�'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '�豸����'
        FieldName = 'spost_code'
      end
      item
        ParamName = '�豸����'
        FieldName = 'sbankname'
      end
      item
        ParamName = '��;'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '�豸״̬'
        FieldName = 'sstatus0'
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
    RequestType = 2005
    Left = 24
    Top = 18
  end
  object cpSetPOSInfo: TKCWVProcessor
    ID = 'POS��Ϣά��'
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
        ParamName = '������־'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '�豸�����'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�����̻���'
        FieldName = 'lvol1'
        DefaultValue = 0
      end
      item
        ParamName = '�豸�ն˺�'
        FieldName = 'sname'
      end
      item
        ParamName = '�ն����к�'
        FieldName = 'sname2'
      end
      item
        ParamName = '�豸�ͺ�'
        FieldName = 'lvol2'
        DefaultValue = 0
      end
      item
        ParamName = '�豸����'
        FieldName = 'spost_code'
      end
      item
        ParamName = '�豸����'
        FieldName = 'sbankname'
      end
      item
        ParamName = '��;'
        FieldName = 'lvol4'
        DefaultValue = 0
      end
      item
        ParamName = '�豸״̬'
        FieldName = 'sstatus0'
      end
      item
        ParamName = '��������'
        FieldName = 'sdate0'
      end
      item
        ParamName = 'ע������'
        FieldName = 'sdate1'
      end
      item
        ParamName = 'ɾ������'
        FieldName = 'sdate2'
      end
      item
        ParamName = '������ʱ��'
        FieldName = 'scard0'
      end
      item
        ParamName = '��ע'
        FieldName = 'vsvarstr0'
      end
      item
        ParamName = '��������'
        FieldName = 'sstock_code'
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
    RequestType = 2005
    KCDataset = Dataset
    Left = 24
    Top = 66
  end
  object cqDevRepair: TKCWVQuery
    ID = '�豸ά��'
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
        ParamName = '�豸���'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�豸״̬'
        FieldName = 'sstat_type'
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
    RequestType = 2012
    Left = 24
    Top = 114
  end
  object KCDevBusiBind: TKCWVProcessor
    ID = '�豸�̻���'
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
        ParamName = '��������'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '�̻����'
        FieldName = 'lvol0'
        DefaultValue = 0
      end
      item
        ParamName = '�豸���'
        FieldName = 'scert_no'
      end
      item
        ParamName = '���к�'
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
      end>
    RequestType = 2011
    KCDataset = Dataset
    Left = 24
    Top = 162
  end
  object KCDevBusiQ: TKCWVQuery
    ID = '�豸�̻���ѯ'
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
        ParamName = '�豸���'
        FieldName = 'scert_no'
      end
      item
        ParamName = '�̻����'
        FieldName = 'lvol0'
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
    RequestType = 2013
    Left = 24
    Top = 210
  end
  object cqSetBusiInfo: TKCWVQuery
    ID = '�̻���Ϣά��QQ'
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
        ParamName = '������־'
        FieldName = 'sstat_type'
      end
      item
        ParamName = '�̻����'
        FieldName = 'lvol0'
      end
      item
        ParamName = '�����̻���'
        FieldName = 'sname'
      end
      item
        ParamName = 'ʡ�̻����'
        FieldName = 'sname2'
      end
      item
        ParamName = '�̻�״̬'
        FieldName = 'sstatus1'
      end
      item
        ParamName = '�̻���'
        FieldName = 'snote'
      end
      item
        ParamName = '�̻�Ӣ������'
        FieldName = 'snote2'
      end
      item
        ParamName = '�̻����'
        FieldName = 'semail'
      end
      item
        ParamName = '�̻�����'
        FieldName = 'sbranch_code0'
      end
      item
        ParamName = '��ҵ����'
        FieldName = 'sbranch_code1'
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
    RequestType = 2004
    Left = 24
    Top = 258
  end
end
