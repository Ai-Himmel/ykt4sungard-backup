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
 * Description: 一卡通用户认证 Modify History: 操作类型 操作人 操作时间 操作内容
 * =================================== 创建 Xiao Qi 2005-9-1
 * 
 * @author Xiao Qi
 * @version 1.0
 * @since 1.0
 */

public class EcardUserAuth implements
		com.liferay.portal.security.auth.Authenticator {

	/**
	 * Description: 根据客户号和密码在一卡通数据库中验证此用户是否可以登录
	 * 
	 * @param stuempNo
	 *            学工号
	 * @param password
	 *            客户对应的主卡密码
	 * @return int 操作结果
	 * @throws Exception
	 *             Modify History:
	 */

	int authenticateLocal(User user, String password) throws Exception {
		boolean checkPwdResult = false;
		
		// 不是管理员身份
		if(user.isPasswordEncrypted()){
			// 如果一卡通数据库中存在登录用户

			String currentEncryptPwd = PwdEncryptor.encrypt(password);
			/*
			 * 只要输入的卡密码符合此客户当前所拥有的卡就可以
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
		// 不是管理员身份
		TCustomer customer = CustomerLocalServiceUtil
				.getCustomerByStuempno(stuempno);
		if (null == customer) {
			return DNE;
		}
		boolean checkPwdResult = false;
		// 如果一卡通数据库中存在登录用户
		List cards = CardServiceUtil.getAvailableCards(customer.getCustid()
				.toString());
		String currentEncryptPwd = PasswordUtil.DESEnc(password);
		/*
		 * 只要输入的卡密码符合此客户当前所拥有的卡就可以
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
				if (yktResult == DNE) {// 如果一卡通数据库中不存在此用户，进行删除操作
					UserLocalServiceUtil.deleteUser(myuser.getUserId());
				}
				return yktResult;
			} catch (NoSuchUserException nsue) {
				int authenResult = authenticateInYKT(screenName, password);
				if (authenResult == SUCCESS) {
					// 开始创建新用户*/

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

					// 设置为不需要同意注册说明
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
