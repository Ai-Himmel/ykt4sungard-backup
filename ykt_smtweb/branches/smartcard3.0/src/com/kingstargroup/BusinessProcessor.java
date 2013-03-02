package com.kingstargroup;

import java.util.HashMap;

import javax.servlet.http.HttpSession;

public abstract class BusinessProcessor {

	static public final String THIRD_PART_MESSAGE = "third_part_message";

	/**
	 * Method name:checkThirdpart Description: ��������·���,��ϢУ��
	 * 
	 * @param session
	 *            �û�����һЩ�첽��Ϣ��Ʃ�緵�ص�message��Ϣ
	 * @param personId
	 *            �û�id�� ѧ���ţ������ڵ������˺�У��Ϸ���
	 * @param personName
	 *            �û�����
	 * @param args
	 *            ҵ��������У���Ҫ����������ز�����
	 * @return boolean true��������ϵͳ����������false:������ϵͳ�����쳣
	 */
	public abstract boolean checkThirdpart(HttpSession session,
			String personId, String personName, String amount, HashMap args);

	/**
	 * Method name:getThirdpartInfo Description: ��������Ϣ���� ���û�ȷ�� Return:
	 * 
	 * @param session
	 *            �û�����һЩ�첽��Ϣ��Ʃ�緵�ص�message��Ϣ
	 * @param personId
	 *            �û�id�� ѧ���ţ������ڵ������˺�У��Ϸ���
	 * @param personName
	 *            �û�����
	 * @param amount
	 *            ���γ�ֵ�Ľ�
	 * @param args
	 *            ҵ��������У���Ҫ����������ز�����
	 * @return HashMap ������Ϣhash�� entityΪ��Ϣ��̧ͷ��valueΪ��Ϣ���ݣ�Ʃ��{�û���=abc};
	 */
	public abstract HashMap getThirdpartInfo(HttpSession session,
			String personId, String personName, String amount, HashMap args);

	/**
	 * Method name:businessProcess Description: ����ר���ֵ�ľ����ҵ����
	 * 
	 * @param session
	 *            �û�����һЩ�첽��Ϣ��Ʃ�緵�ص�message��Ϣ
	 * @param refno
	 *            ���ײο��ţ�˫����Ӧ����ˮ�ο��ţ��û�����
	 * @param personId
	 *            ��Ҫ���г�ֵ����ԱID�ţ���Ϊѧ�Ż�ְ���š�
	 * @param personName
	 *            ��Ҫ���г�ֵ����Ա��������
	 * @param amount
	 *            ���γ�ֵ�Ľ�
	 * @param args
	 *            ҵ��������У���Ҫ����������ز�����
	 * @return boolean ҵ�����Ƿ�ɹ��� true:ҵ����ɹ���false��ҵ����ʧ�ܡ�
	 */
	public abstract boolean businessProcess(HttpSession session, String refno,
			String personId, String personName, String amount, HashMap args);

	/**
	 * Method name:getProcessMessage Description: ������ϵͳ������Ϣ
	 * 
	 * @param session
	 *            ���ڱ�����Ϣ���õ�session keyΪTHIRD_PART_MESSAGE
	 * @return String ���ص�������Ϣ
	 */
	public abstract String getProcessMessage(HttpSession session);

	/**
	 * Method name:businessRollback Description:
	 * �Խ��г�ֵҵ��Ĵ���ɹ��󣬵���һ��ͨ���ʺŽ���ת��ʱ������ͨ�˷������г�ֵҵ��Ļ��ˡ�
	 * 
	 * @param session
	 *            �û�����һЩ�첽��Ϣ��Ʃ�緵�ص�message��Ϣ
	 * @param refno
	 *            ���ײο��ţ�˫����Ӧ����ˮ�ο��ţ��û�����
	 * @param personId
	 *            ��Ҫ���г�ֵ����ԱID�ţ���Ϊѧ�Ż�ְ���š�
	 * @param personName
	 *            ��Ҫ���г�ֵ����Ա��������
	 * @param amount
	 *            ���γ�ֵ�Ľ�
	 * @param args
	 *            ҵ��������У���Ҫ����������ز�����
	 * @return ҵ�����Ƿ�ɹ��� true:ҵ����ɹ���false��ҵ����ʧ�ܡ�
	 */
	public abstract boolean businessRollback(HttpSession session, String refno,
			String personId, String personName, String amount, HashMap args);

}
