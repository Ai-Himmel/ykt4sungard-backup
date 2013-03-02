package org.king.dictionary;

import java.util.Map;

/**
 * ϵͳ�ֵ�
 * @author cash
 *
 */
public interface YKTDictionEntry  {
	
	/**
	 * @return ����Ψһ�ֵ��ʶ
	 */
	abstract public String getKey();

	/**
	 * �����ֵ�����
	 * @return ���سɹ����� true , ʧ�ܷ��� false
	 */
	abstract public boolean loadDiction(Map dict);

	/**
	 * �ͷ��ֵ仺���е�����
	 * @return �ɹ����� true , ʧ�ܷ��� false
	 */
	abstract public boolean releaseDiction();

	/**
	 * ��ȡ�ֵ��е�ֵ
	 * @param key �ֵ�� key
	 * @return �����ֵ������, û���ҵ����� null
	 */
	abstract public Object getValue(Object key);

}