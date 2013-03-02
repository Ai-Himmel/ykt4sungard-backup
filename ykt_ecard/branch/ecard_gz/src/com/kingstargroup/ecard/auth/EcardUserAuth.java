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
 * Description: 一卡通用户认证
 * Modify History: 
 * 操作类型   操作人   操作时间     操作内容
 * ===================================
 *  创建    Xiao Qi  2005-9-1  
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
	 * Description:使用用户ID来认证，一卡通普通用户则使用学工号来登录
	 * @param companyId 公司ID
	 * @param userId 用户ID(管理员使用内置portal帐号，一卡通普通用户使用学工号登录)
	 * @param password 用户密码
	 * @return
	 * @throws AuthException
	 * Modify History:
	 */

	public int authenticateByUserId(
			String companyId, String userId, String password)
		throws AuthException {
		try {						
			try {
				//查找liferay的用户数据库表中是否存在登录用户				
				List groups = UserLocalServiceUtil.getGroups(userId);
				Group adminGroup = GroupLocalServiceUtil.getGroupByName(companyId, EcardConstants.ADMIN_YKT_GROUP_NAME);
				//判断当前登录用户是否具有一卡通管理员组的权限
				if (groups.contains(adminGroup)) {
					//后续步骤会在liferay用户数据表中验证此管理员用户
					return SUCCESS;
				}
				else {
					int yktResult = authenticateInYKT(userId, password);
					if (yktResult == DNE) {//如果一卡通数据库中不存在此用户，进行删除操作
						UserUtil.remove(userId);
					}
					return yktResult;					
				}
			} catch (NoSuchUserException nsue) {
				int authenResult = authenticateInYKT(userId, password);
				if (authenResult == SUCCESS) {
					//开始创建新用户*/

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
					//设置为不需要同意注册说明
					newUser.setAgreedToTermsOfUse(true);
					newUser.setResolution(PropsUtil.get("default.user.layout.resolution"));
					UserUtil.update(newUser);
					//设置用户权限
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
	 * Description: 根据客户号和密码在一卡通数据库中验证此用户是否可以登录
	 * @param cutId 客户号
	 * @param password 客户对应的主卡密码
	 * @return int 操作结果
	 * @throws Exception
	 * Modify History:
	 */

	int authenticateInYKT(String cutId, String password) throws Exception {
		//不是管理员身份
		TCifCustomer customer = CustomerUtil.getCustomerById(cutId);
		if (null == customer) {
			return DNE;
		}
		boolean checkPwdResult = false;
		//如果一卡通数据库中存在登录用户
		List cards = CardUtil.getAvailableCards(cutId);
		String currentEncryptPwd = PasswordUtil.DESEnc(password);
		/*
		 * 只要输入的卡密码符合此客户当前所拥有的卡就可以
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
