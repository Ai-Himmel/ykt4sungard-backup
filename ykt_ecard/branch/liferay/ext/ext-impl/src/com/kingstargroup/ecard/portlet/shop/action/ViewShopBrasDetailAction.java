package com.kingstargroup.ecard.portlet.shop.action;

import java.util.List;
import java.util.Locale;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.exceptions.BccBgInfoException;
import com.kingstargroup.ecard.portlet.shop.service.ShopServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.DateUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.util.servlet.SessionErrors;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ViewRuleAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型 操作人 操作时间 操作内容<br>
 * ===================================<br>
 * 创建 Xiao Qi 2005-9-21 <br>
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class ViewShopBrasDetailAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {
		String datetime = DateUtil.getCurrentDate("yyyy/MM/dd", Locale.CHINA);
		datetime = com.kingstargroup.ecard.util.DateUtil.getOtherDate(datetime,
				"yyyy/MM/dd", -2);
//		aform.set("bras_begindate", datetime);
//		aform.set("bras_enddate", datetime);

		String begindate = "20090101";
		String enddate = datetime.substring(0,4)+datetime.substring(5,7)+datetime.substring(8,10);
		
		List result = null;
		try {
			result = ShopServiceUtil.getShopBrasDetailList(begindate, enddate,"","","", "", "","1","-");
		}catch (BccBgInfoException e) {
			SessionErrors.add(req,e.getClass().getName(),e);
		}
		catch (Exception e) {
			SessionErrors.add(req,e.getClass().getName(),e);		
			e.printStackTrace();
		}
		
		if(result!=null&&result.size()>0){
			SessionErrors.add(req, EcardConstants.NET_TRANS_ERROR_OCCURANCE);
		}
		req.setAttribute("shopbrasresult", result);
		return mapping.findForward("portlet.shopbrasdetail.view");
		

	}
}
