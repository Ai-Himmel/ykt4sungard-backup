<#include "copyright.txt" parse="false">


package ${principalBeanPackage};

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.User;
import com.liferay.portal.security.auth.CompanyThreadLocal;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.security.auth.PrincipalThreadLocal;
import com.liferay.portal.security.permission.PermissionThreadLocal;
import com.liferay.portal.service.UserLocalServiceUtil;

/**
 * <a href="PrincipalBean.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PrincipalBean {

	public static final String JRUN_ANONYMOUS = "anonymus-guest";

	public static final String ORACLE_ANONYMOUS = "guest";

	public static final String SUN_ANONYMOUS = "ANONYMOUS";

	public static final String WEBLOGIC_ANONYMOUS = "<anonymous>";

	public static final String[] ANONYMOUS_NAMES = {
		JRUN_ANONYMOUS, ORACLE_ANONYMOUS, SUN_ANONYMOUS, WEBLOGIC_ANONYMOUS
	};

	public long getGuestOrUserId() throws PrincipalException {
		try {
			return getUserId();
		}
		catch (PrincipalException pe) {
			try {
				return UserLocalServiceUtil.getDefaultUserId(
					CompanyThreadLocal.getCompanyId());
			}
			catch (Exception e) {
				throw pe;
			}
		}
	}

	public User getUser() throws PortalException, SystemException {
		return UserLocalServiceUtil.getUserById(getUserId());
	}

	public long getUserId() throws PrincipalException {
		String name = PrincipalThreadLocal.getName();

		if (name == null) {
			throw new PrincipalException();
		}

		if (Validator.isNull(name)) {
			throw new PrincipalException("Principal cannot be null");
		}
		else {
			for (int i = 0; i < ANONYMOUS_NAMES.length; i++) {
				if (name.equalsIgnoreCase(ANONYMOUS_NAMES[i])) {
					throw new PrincipalException(
						"Principal cannot be " + ANONYMOUS_NAMES[i]);
				}
			}
		}

		return GetterUtil.getLong(name);
	}

	public PermissionChecker getPermissionChecker() throws PrincipalException {
		PermissionChecker permissionChecker =
			PermissionThreadLocal.getPermissionChecker();

		if (permissionChecker == null) {
			throw new PrincipalException("PermissionChecker not initialized");
		}

		return permissionChecker;
	}

}