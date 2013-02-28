package org.king.security.web.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.action.DynaActionForm;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.TEpayShopinfo;
import org.king.security.service.ShopService;

public class ShopAction extends BaseAction{
	
	private ShopService shopService;
	
	
	public void setShopService(ShopService shopService) {
		this.shopService = shopService;
	}


	/**
	 * 获取登陆用户的商户信息
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward loadShopInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String type = "update";
		HttpSession session = request.getSession(false);
		if (session == null) {
			session = request.getSession(true);
		}
		Long shopId = (Long) session.getAttribute("shopid");
		
		TEpayShopinfo tShopinfo = shopService.gettShopinfoByid(shopId);
		if(tShopinfo==null){
			tShopinfo = new TEpayShopinfo();
			tShopinfo.setShopid(shopId);
			type = "add";
		}
		((DynaActionForm) form).set("tShopinfo", tShopinfo);
		((DynaActionForm) form).set("type", type);
		return (mapping.findForward("success"));
	}
	
	public ActionForward eidtShopInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		TEpayShopinfo tShopinfo = (TEpayShopinfo)((DynaActionForm) form).get("tShopinfo");
		String type = (String)((DynaActionForm) form).get("type");
		ActionMessages errors = new ActionMessages();
	        try {
	        	if(tShopinfo.getIscheck()==null){
	        		tShopinfo.setIscheck(0);
	        	}
	        	shopService.saveOrUpdateShopinfo(tShopinfo,type);
	        } catch (Exception e) {
	        	e.printStackTrace();
	            errors.add("eidtShopInfo", new ActionMessage("errors.eidtshop"));
	            saveErrors(request, errors);
	            return mapping.findForward("result");
	        }
	        
	        errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("succes.eidtshop"));
		    saveErrors(request, errors);
	        return mapping.findForward("result");
	    }

}
