/**
 * 
 */
package com.kingstargroup.action.user;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;


import com.kingstargroup.commons.BaseAction;


/**<br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: RedirectAction.java<br>
 * Description: <br>
 * Modify History（或Change Log）:  <br>
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述<br>
 * 创建  				 2005-11-23  何林青    <br>
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
public class RedirectAction extends BaseAction {

	/**
	 * 
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String flag = request.getParameter("InstallFlag");
		if (flag != null && !"".equals(flag)) {
			response.sendRedirect(ErrorCode.SERVER_URL);
		}

		return null;
	}

}
