/**
 * 
 */
package com.kingstargroup.ecard.portlet.shop.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.portlet.shop.service.ShopServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.util.servlet.SessionErrors;

public class EditShopBindAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {
		String userid = ParamUtil.getString(req, "userid");
		String storeLimitString = ParamUtil.getString(req, "storeLimitString");

		try {
			if ("".equals(storeLimitString)) {
				SessionErrors.add(req, EcardConstants.USER_NOT_SELECTEDE);
				return mapping.findForward("portlet.shop_admin.view");
			}

			ShopServiceUtil.updateUser(userid, storeLimitString);
			SessionErrors.add(req, EcardConstants.SHOP_BIND_SUCCESS);
		} catch (PortalException pe) {
			SessionErrors.add(req, EcardConstants.SHOP_BIND_FAILUE);
		}
		return mapping.findForward("portlet.shop_admin.view");

	}
}
