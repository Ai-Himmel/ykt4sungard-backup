package com.kingstargroup.advquery.struts.actions;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO;
import com.kingstargroup.advquery.hibernate.util.ShopUtil;
import com.kingstargroup.advquery.util.ParamUtil;

public class ShopBusinessShopAction extends Action{

	public ActionForward execute( 
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		HttpSession session = request.getSession();
		String  operCode = (String)session.getAttribute("username");
		String ids = new GetQueryConListDAO().getShopIds(operCode);
		String beginDate = DateUtil.reFormatTime(ParamUtil.getString(request,"begindate"));
		String endDate = DateUtil.reFormatTime(ParamUtil.getString(request,"enddate"));
		//HttpSession session = request.getSession();
		session.setAttribute("begindate410d",ParamUtil.getString(request,"begindate"));
		session.setAttribute("enddate410d",ParamUtil.getString(request,"enddate"));
		List result = ShopUtil.getShopBusinessReportList(ids,beginDate,endDate); 
		if (result.isEmpty()){
			request.setAttribute("errorcont","没有你要查询的数据，请重新指定查询条件！");
			return mapping.findForward("errortest");			
		}
		request.setAttribute("result",result);
		return mapping.findForward("shopbusiness_queryresult");
	}

}
