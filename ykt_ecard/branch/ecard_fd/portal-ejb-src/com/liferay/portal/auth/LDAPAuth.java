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
					// ����liferay���û����ݿ�����Ƿ���ڵ�¼�û�
					List groups = UserLocalServiceUtil.getGroups(userId);
					Group adminGroup = GroupLocalServiceUtil.getGroupByName(
							companyId, EcardConstants.ADMIN_YKT_GROUP_NAME);
					// �жϵ�ǰ��¼�û��Ƿ����һ��ͨ����Ա���Ȩ��
					if (groups.contains(adminGroup)) {
						// �����������liferay�û����ݱ�����֤�˹���Ա�û�
						return SUCCESS;
					} else {
						int yktResult = authenticateInYKT(userId);
						for(int i=0;i<groups.size();i++){
							  UserLocalServiceUtil.deleteGroup(userId, (Group)groups.get(i));
						}
						//������û����ڣ����б���Ȩ�ޣ�ɾ��ԭ�ȵ�user_group,�����µ�groupΪ5
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
						// ��ʼ�������û�*/

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
						// ����Ϊ����Ҫͬ��ע��˵��
						newUser.setAgreedToTermsOfUse(true);
						newUser.setResolution(PropsUtil
								.get("default.user.layout.resolution"));
						UserUtil.update(newUser);
						//�����û�Ȩ��
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

	int authenticateInYKT(String stuempNo) throws Exception {
		// ���ǹ���Ա���
		TCifCustomer customer = CustomerUtil.getCustomerByStuempNo(stuempNo);
		if (null == customer) {
			return DNE;
		}
		boolean checkPwdResult = false;
		// ���һ��ͨ���ݿ��д��ڵ�¼�û�
		List cards = CardUtil.getAvailableCards(customer.getCutId().toString());
		/*
		 * ֻҪ�˿ͻ���ǰӵ�п��Ϳ���
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
