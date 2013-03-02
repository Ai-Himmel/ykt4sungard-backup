package com.kingstargroup.ecard.portlet.login.action;

import java.util.Calendar;
import java.util.List;
import java.util.Locale;
import java.util.Map;

import com.kingstargroup.ecard.hibernate.card.TCard;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;
import com.kingstargroup.ecard.hibernate.util.CustomerUtil;
import com.kingstargroup.ecard.portlet.card.service.CardServiceUtil;
import com.kingstargroup.ecard.portlet.distribution.service.CustomerLocalServiceUtil;
import com.kingstargroup.ecard.util.PasswordUtil;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.User;
import com.liferay.portal.security.auth.AuthException;
import com.liferay.portal.security.pwd.PwdEncryptor;
import com.liferay.portal.service.RoleServiceUtil;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.util.PropsUtil;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. File name: EcardUserAuth.java
 * Description: һ��ͨ�û���֤ Modify History: �������� ������ ����ʱ�� ��������
 * =================================== ���� Xiao Qi 2005-9-1
 * 
 * @author Xiao Qi
 * @version 1.0
 * @since 1.0
 */

public class EcardUserAuth implements
		com.liferay.portal.security.auth.Authenticator {

	/**
	 * Description: ���ݿͻ��ź�������һ��ͨ���ݿ�����֤���û��Ƿ���Ե�¼
	 * 
	 * @param stuempNo
	 *            ѧ����
	 * @param password
	 *            �ͻ���Ӧ����������
	 * @return int �������
	 * @throws Exception
	 *             Modify History:
	 */

	int authenticateLocal(User user, String password) throws Exception {
		boolean checkPwdResult = false;
		
		// ���ǹ���Ա���
		if(user.isPasswordEncrypted()){
			// ���һ��ͨ���ݿ��д��ڵ�¼�û�

			String currentEncryptPwd = PwdEncryptor.encrypt(password);
			/*
			 * ֻҪ����Ŀ�������ϴ˿ͻ���ǰ��ӵ�еĿ��Ϳ���
			 */
			String validPassword = user.getPassword();
			if (validPassword.equals(currentEncryptPwd)) {
				checkPwdResult = true;
			}
		}else{
			String validPassword = user.getPassword();
			if (validPassword.equals(password)) {
				checkPwdResult = true;
			}
		}
		
		if (!checkPwdResult) {
			return FAILURE;
		}
		return SUCCESS;
	}
	
	int authenticateInYKT(String stuempno, String password) throws Exception {
		// ���ǹ���Ա���
		TCustomer customer = CustomerLocalServiceUtil
				.getCustomerByStuempno(stuempno);
		if (null == customer) {
			return DNE;
		}
		boolean checkPwdResult = false;
		// ���һ��ͨ���ݿ��д��ڵ�¼�û�
		List cards = CardServiceUtil.getAvailableCards(customer.getCustid()
				.toString());
		String currentEncryptPwd = PasswordUtil.DESEnc(password);
		/*
		 * ֻҪ����Ŀ�������ϴ˿ͻ���ǰ��ӵ�еĿ��Ϳ���
		 */

		for (int i = 0; i < cards.size(); i++) {
			TCard card = (TCard) cards.get(i);
			String validPassword = card.getCardpwd();
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

	public int authenticateByEmailAddress(long companyId, String emailAddress,
			String password, Map headerMap, Map parameterMap)
			throws AuthException {
		// TODO Auto-generated method stub
		return 0;
	}

	public int authenticateByScreenName(long companyId, String screenName,
			String password, Map headerMap, Map parameterMap)
			throws AuthException {
		try {

			try {
				User myuser = UserLocalServiceUtil.getUserByScreenName(
						companyId, screenName);
				
				
				if(myuser!=null&&RoleServiceUtil.hasUserRole(myuser.getUserId(), companyId, "Administrator", true)){
					//Administrotor
					return authenticateLocal(myuser, password);					
				}
				int yktResult = authenticateInYKT(screenName, password);
				if (yktResult == DNE) {// ���һ��ͨ���ݿ��в����ڴ��û�������ɾ������
					UserLocalServiceUtil.deleteUser(myuser.getUserId());
				}
				return yktResult;
			} catch (NoSuchUserException nsue) {
				int authenResult = authenticateInYKT(screenName, password);
				if (authenResult == SUCCESS) {
					// ��ʼ�������û�*/

					TCustomer customer = CustomerUtil
							.getCustomerByStuempno(screenName);
					boolean autoPassword = false;
					String password1 = password;
					String password2 = password;
					String firstName = customer.getCustname();
					String middleName = "";
					String lastName = "";
					boolean male = "1".equals(customer.getSex()) ? false : true;
					String emailAddress = screenName+PropsUtil.get("default.email.suffix");
					Locale locale = Locale.CHINA;

					long creatorUserId = 0;
					boolean autoScreenName = false;
					long[] organizationIds = new long[0];
					int prefixId = 0;
					int suffixId = 0;
					int birthdayMonth = Calendar.JANUARY;
					int birthdayDay = 1;
					int birthdayYear = 1970;
					String jobTitle = StringPool.BLANK;

					User newUser = UserLocalServiceUtil.addUser(creatorUserId,
							companyId, autoPassword, password1, password2,
							autoScreenName, screenName, emailAddress, locale,
							firstName, middleName, lastName, prefixId,
							suffixId, male, birthdayMonth, birthdayDay,
							birthdayYear, jobTitle, organizationIds, false);

					// ����Ϊ����Ҫͬ��ע��˵��
					newUser.setAgreedToTermsOfUse(true);
					UserLocalServiceUtil.updateUser(newUser);
					return SUCCESS;
				} else {
					return authenResult;
				}

			}
		} catch (Exception e) {
			e.printStackTrace();
			throw new AuthException(e);
		}
	}

	public int authenticateByUserId(long companyId, long userId,
			String password, Map headerMap, Map parameterMap)
			throws AuthException {
		// TODO Auto-generated method stub
		return 0;
	}
}
