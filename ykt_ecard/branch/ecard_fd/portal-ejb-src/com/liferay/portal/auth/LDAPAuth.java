/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.portal.auth;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;

import com.kingstargroup.ecard.LdapFromSunDS;
import com.kingstargroup.ecard.hibernate.customer.TCifCustomer;
import com.kingstargroup.ecard.hibernate.util.CardUtil;
import com.kingstargroup.ecard.hibernate.util.CustomerUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.PermissionUtil;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.User;
import com.liferay.portal.service.persistence.UserUtil;
import com.liferay.portal.service.spring.GroupLocalServiceUtil;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portal.util.PropsUtil;
import com.wiscom.is.IdentityFactory;
import com.wiscom.is.IdentityManager;
import com.wiscom.is.SSOToken;
/**
 * <a href="LDAPAuth.java.html"><b><i>View Source</i></b></a>
 * 
 * @author Brian Wing Shun Chan
 * @version $Revision: 1.16 $
 * 
 */
public class LDAPAuth implements Authenticator {

	public int authenticateByEmailAddress(String companyId,
			String emailAddress, String password) throws AuthException {

		try {

			// Check the LDAP server to ensure the company id, email address,
			// and password is valid

			boolean success = true;

			if (success) {

				// Make sure the user has a portal account

				// User user = null;

				// try {
				// user = UserLocalServiceUtil.getUserByEmailAddress(
				// companyId, emailAddress);
				// } catch (NoSuchUserException nsue) {

				// Grab attributes from LDAP

				// boolean autoUserId = true;
				// String userId = "";
				// boolean autoPassword = false;
				// String password1 = password;
				// String password2 = password;
				// boolean passwordReset = false;
				// String firstName = "";
				// String middleName = "";
				// String lastName = "";
				// String nickName = "";
				// boolean male = true;
				// Date birthday = new Date();
				// Locale locale = Locale.US;

				/*
				 * user = UserLocalServiceUtil.addUser( companyId, autoUserId,
				 * userId, autoPassword, password1, password2, passwordReset,
				 * firstName, middleName, lastName, nickName, male, birthday,
				 * emailAddress, locale);
				 */
				// }
				return SUCCESS;
			} else {
				return FAILURE;
			}
		} catch (Exception e) {
			throw new AuthException(e);
		}
	}

	public int authenticateByUserId(String companyId, String userId,
			String password) throws AuthException {

		try {
			boolean success = false;

			// Check the LDAP server to ensure the company id, user id,
			// and
			// password is valid
			LdapFromSunDS ldap = new LdapFromSunDS();

			ldap.init("");

			String is_config = ldap.getPreference("constant.ldap.path")
					+ "/client.properties";
			IdentityFactory factory = IdentityFactory.createFactory(is_config);
			IdentityManager im = factory.getIdentityManager();

			SSOToken token = im.createStoken(userId, password);
			if (token != null) {
				if (im.checkPassword(userId, password)) {
					success = true;
				}
			}
	       
			if (success) { 
				try {
					// 查找liferay的用户数据库表中是否存在登录用户
					List groups = UserLocalServiceUtil.getGroups(userId);
					Group adminGroup = GroupLocalServiceUtil.getGroupByName(
							companyId, EcardConstants.ADMIN_YKT_GROUP_NAME);
					// 判断当前登录用户是否具有一卡通管理员组的权限
					if (groups.contains(adminGroup)) {
						// 后续步骤会在liferay用户数据表中验证此管理员用户
						return SUCCESS;
					} else {
						int yktResult = authenticateInYKT(userId);
						for(int i=0;i<groups.size();i++){
							  UserLocalServiceUtil.deleteGroup(userId, (Group)groups.get(i));
						}
						//如果此用户存在，且有保修权限，删除原先的user_group,增加新的group为5
						if(PermissionUtil.isTeacherWorkUser(userId)){
							Group group = GroupLocalServiceUtil.getGroupByName(
									companyId,
									EcardConstants.TEACHER_WORK_NAME);
							List groupList = new ArrayList();
							groupList.add(group);
							UserLocalServiceUtil.setGroups(userId, groupList);
						}else{
							Group group = GroupLocalServiceUtil.getGroupByName(
									companyId,
									EcardConstants.GENERAL_YKT_GROUP_NAME);
							List groupList = new ArrayList();
							groupList.add(group);
							UserLocalServiceUtil.setGroups(userId, groupList);
						}
						return yktResult;
				    }
				} catch (NoSuchUserException nsue) {
					int authenResult = authenticateInYKT(userId);
					if (authenResult == LDAPSUCCESS) {
						// 开始创建新用户*/

						TCifCustomer customer = CustomerUtil
								.getCustomerByStuempNo(userId);
						boolean autoUserId = false;
						boolean autoPassword = false;
						String password1 = password;
						String password2 = password;
						boolean passwordReset = false;
						String firstName = customer.getCutName();
						String middleName = "";
						String lastName = "";
						String nickName = "";
						boolean male = customer.getSex().equals("1") ? false
								: true;
						Date birthday = new Date();
						String emailAddress = "";
						// String emailAddress = userId +
						// "@kingstargroup.com";
						Locale locale = Locale.CHINA;
						User newUser = UserLocalServiceUtil.addUser(companyId,
								autoUserId, userId, autoPassword, password1,
								password2, passwordReset, firstName,
								middleName, lastName, nickName, male, birthday,
								emailAddress, locale);
						// 设置为不需要同意注册说明
						newUser.setAgreedToTermsOfUse(true);
						newUser.setResolution(PropsUtil
								.get("default.user.layout.resolution"));
						UserUtil.update(newUser);
						//设置用户权限
						if(PermissionUtil.isTeacherWorkUser(userId)){
							Group group = GroupLocalServiceUtil.getGroupByName(
									companyId,
									EcardConstants.TEACHER_WORK_NAME);
							List groupList = new ArrayList();
							groupList.add(group);
							UserLocalServiceUtil.setGroups(userId, groupList);
						}
						else{
							Group group = GroupLocalServiceUtil.getGroupByName(
									companyId,
									EcardConstants.GENERAL_YKT_GROUP_NAME);
							List groupList = new ArrayList();
							groupList.add(group);
							UserLocalServiceUtil.setGroups(userId, groupList);
						}
						
						return LDAPSUCCESS;
					} else {
						return authenResult;
					}

				}
			} else {
				return FAILURE;
			}
		} catch (Exception e) {
			throw new AuthException(e);
		}
	}

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

	int authenticateInYKT(String stuempNo) throws Exception {
		// 不是管理员身份
		TCifCustomer customer = CustomerUtil.getCustomerByStuempNo(stuempNo);
		if (null == customer) {
			return DNE;
		}
		boolean checkPwdResult = false;
		// 如果一卡通数据库中存在登录用户
		List cards = CardUtil.getAvailableCards(customer.getCutId().toString());
		/*
		 * 只要此客户当前拥有卡就可以
		 */
		if (cards != null && cards.size() > 0) {
			checkPwdResult = true;
		}

		if (!checkPwdResult) {
			return FAILURE;
		}
		return LDAPSUCCESS;
	}

	
}
