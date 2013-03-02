package com.kingstargroup.ecard.auth;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;

import com.kingstargroup.ecard.hibernate.card.TPifCard;
import com.kingstargroup.ecard.hibernate.customer.TCifCustomer;
import com.kingstargroup.ecard.hibernate.util.CardUtil;
import com.kingstargroup.ecard.hibernate.util.CustomerUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.PasswordUtil;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.auth.AuthException;
import com.liferay.portal.auth.Authenticator;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.User;
import com.liferay.portal.service.persistence.UserUtil;
import com.liferay.portal.service.spring.GroupLocalServiceUtil;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portal.util.PropsUtil;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: EcardUserAuth.java
 * Description: һ��ͨ�û���֤
 * Modify History: 
 * ��������   ������   ����ʱ��     ��������
 * ===================================
 *  ����    Xiao Qi  2005-9-1  
 * @author Xiao Qi
 * @version 1.0
 * @since 1.0
 */

public class EcardUserAuth implements Authenticator {
	/**
	 * Description:
	 * @param companyId
	 * @param emailAddress
	 * @param password
	 * @return
	 * @throws AuthException
	 * Modify History:
	 */

	public int authenticateByEmailAddress(
			String companyId, String emailAddress, String password)
		throws AuthException {
		return SUCCESS;
	}

	
	/**
	 * Description:ʹ���û�ID����֤��һ��ͨ��ͨ�û���ʹ��ѧ��������¼
	 * @param companyId ��˾ID
	 * @param userId �û�ID(����Աʹ������portal�ʺţ�һ��ͨ��ͨ�û�ʹ��ѧ���ŵ�¼)
	 * @param password �û�����
	 * @return
	 * @throws AuthException
	 * Modify History:
	 */

	public int authenticateByUserId(
			String companyId, String userId, String password)
		throws AuthException {
		try {						
			try {
				//����liferay���û����ݿ�����Ƿ���ڵ�¼�û�				
				List groups = UserLocalServiceUtil.getGroups(userId);
				Group adminGroup = GroupLocalServiceUtil.getGroupByName(companyId, EcardConstants.ADMIN_YKT_GROUP_NAME);
				//�жϵ�ǰ��¼�û��Ƿ����һ��ͨ����Ա���Ȩ��
				if (groups.contains(adminGroup)) {
					//�����������liferay�û����ݱ�����֤�˹���Ա�û�
					return SUCCESS;
				}
				else {
					int yktResult = authenticateInYKT(userId, password);
					if (yktResult == DNE) {//���һ��ͨ���ݿ��в����ڴ��û�������ɾ������
						UserUtil.remove(userId);
					}
					return yktResult;					
				}
			} catch (NoSuchUserException nsue) {
				int authenResult = authenticateInYKT(userId, password);
				if (authenResult == SUCCESS) {
					//��ʼ�������û�*/

					TCifCustomer customer = CustomerUtil.getCustomerById(userId);
					boolean autoUserId = false;
					boolean autoPassword = false;
					String password1 = password;
					String password2 = password;
					boolean passwordReset = false;
					String firstName = customer.getCutName();
					String middleName = "";
					String lastName = "";
					String nickName = "";
					boolean male = "1".equals(customer.getSex()) ? false : true;
					Date birthday = new Date();
					String emailAddress = "";
					//String emailAddress = userId + "@kingstargroup.com";
					Locale locale = Locale.CHINA;
					User newUser = UserLocalServiceUtil.addUser(
							companyId, autoUserId, userId, autoPassword, 
							password1, password2, passwordReset, firstName, 
							middleName, lastName, nickName, male, birthday, 
							emailAddress, locale);
					//����Ϊ����Ҫͬ��ע��˵��
					newUser.setAgreedToTermsOfUse(true);
					newUser.setResolution(PropsUtil.get("default.user.layout.resolution"));
					UserUtil.update(newUser);
					//�����û�Ȩ��
					Group group = GroupLocalServiceUtil.getGroupByName(companyId, EcardConstants.GENERAL_YKT_GROUP_NAME);
					List groupList = new ArrayList();
					groupList.add(group);
					UserLocalServiceUtil.setGroups(userId, groupList);					
					return SUCCESS;
				} else {
					return authenResult;
				}				
			}
		} catch (Exception e) {
			throw new AuthException(e);
		}		
	}
	
	/**
	 * Description: ���ݿͻ��ź�������һ��ͨ���ݿ�����֤���û��Ƿ���Ե�¼
	 * @param cutId �ͻ���
	 * @param password �ͻ���Ӧ����������
	 * @return int �������
	 * @throws Exception
	 * Modify History:
	 */

	int authenticateInYKT(String cutId, String password) throws Exception {
		//���ǹ���Ա���
		TCifCustomer customer = CustomerUtil.getCustomerById(cutId);
		if (null == customer) {
			return DNE;
		}
		boolean checkPwdResult = false;
		//���һ��ͨ���ݿ��д��ڵ�¼�û�
		List cards = CardUtil.getAvailableCards(cutId);
		String currentEncryptPwd = PasswordUtil.DESEnc(password);
		/*
		 * ֻҪ����Ŀ�������ϴ˿ͻ���ǰ��ӵ�еĿ��Ϳ���
		 */

		for (int i = 0; i < cards.size(); i++) {
			TPifCard card = (TPifCard) cards.get(i);
			String validPassword = card.getPassword();
			if (validPassword.equals(currentEncryptPwd)) {
				checkPwdResult = true;
				break;
			}
		}		
		if (!checkPwdResult) {
			return FAILURE;
		}
		return SUCCESS;
	}
}
