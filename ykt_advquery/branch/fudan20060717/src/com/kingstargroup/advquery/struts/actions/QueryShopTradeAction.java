package com.kingstargroup.advquery.struts.actions;

import java.util.Date;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.hibernate.util.ShopUtil;

public class QueryShopTradeAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		
		String stuempNo = request.getParameter("stuempNo");
		String name = request.getParameter("name");
		String begindate = request.getParameter("begindate");
		String enddate = request.getParameter("enddate");
		String posid = request.getParameter("posid");
		String posids = request.getParameter("posids");
		if("".equals(enddate)){
			enddate = DateUtil.getNowYMD();
		}
		request.getSession().setAttribute("stuempNo",stuempNo);
		request.getSession().setAttribute("name",name);
		request.getSession().setAttribute("begindate",begindate);
		request.getSession().setAttribute("enddate",enddate);
		request.getSession().setAttribute("posid",posid);
		if("".equals(begindate)){
			request.setAttribute("errorcont",new String("请指定查询日期,查询日期间隔不能大于1个月！"));
			return mapping.findForward("errortest");
		}
		if (DateUtil.getIntervalTime(DateUtil.reFormatTime(enddate),DateUtil.reFormatTime(begindate))>Long.valueOf("2678400000").longValue()){
			request.setAttribute("errorcont",new String("查询日期间隔不能大于1个月，请重新指定查询条件！"));
			return mapping.findForward("errortest");			
		}
		if (DateUtil.getIntervalTime(DateUtil.reFormatTime(enddate),DateUtil.reFormatTime(begindate))<Long.valueOf("0").longValue()){
			request.setAttribute("errorcont",new String("开始日期不能大于结束日期，请重新指定查询条件！"));
			return mapping.findForward("errortest");			
		}
		
		posids = posids.substring(0,posids.lastIndexOf(","));
		List result = ShopUtil.getShopTrade(stuempNo,name,begindate,enddate,posid,posids);
		
		
		request.setAttribute("result",result);
		return mapping.findForward("shoptrade_result");
		
	}

}
