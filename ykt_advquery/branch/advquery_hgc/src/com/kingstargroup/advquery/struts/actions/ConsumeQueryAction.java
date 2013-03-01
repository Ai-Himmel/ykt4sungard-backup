/**
 * 
 */
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
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.tradeserial.TradeSerialDAO;

/**
 * 消费信息查询
 * 
 * @author Administrator
 * 
 */
public class ConsumeQueryAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		//String ss = request.getParameter("stuempNo");
		//String groupedlist = request.getParameter("groupedlist");
		// 开始日期
		String beginDate = request.getParameter("begindate").toString();
		// 结束日期
		String endDate = request.getParameter("enddate").toString();
		// 日期不能为空
		if (("".equals(beginDate)) || ("".equals(endDate))) {
			request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
					"bydate", beginDate, endDate));
			return mapping.findForward("errortest");
		}
		
		String deptNo = nullToString(request.getParameter("deptNo"));
		String specNo = nullToString(request.getParameter("specNo"));
		String classNo = nullToString(request.getParameter("classNo"));
		String sex = nullToString(request.getParameter("sex"));
		int custType = Integer.parseInt(nullToString(request.getParameter("custType")));
		int cardType = Integer.parseInt(nullToString(request.getParameter("cardType")));
		int shopId = Integer.parseInt(nullToString(request.getParameter("shopid")));
		String serialType = nullToString(request.getParameter("serialType"));
		String bStuempNo = nullToString(request.getParameter("bStuempNo"));
		String eStuempNo = nullToString(request.getParameter("eStuempNo"));
		float bconsumeRange = 0;
		float econsumeRange = 0;
		
		try {
			if (!"".equals(request.getParameter("bconsumeRange").toString())) {
				bconsumeRange = Float.parseFloat(request.getParameter("bconsumeRange").toString());
			}
			if (!"".equals(request.getParameter("econsumeRange").toString())) {
				econsumeRange = Float.parseFloat(request.getParameter("econsumeRange").toString());
			}
		} catch (Exception e) {
			request.setAttribute("errorcont", new String("金额输入有误，请重新输入！"));
			return mapping.findForward("errortest");
		}
				
		//如果开始值大于零，并且开始值大于结束值，提示错误信息
		if (bconsumeRange>0 && econsumeRange>0){
			if (bconsumeRange>econsumeRange){
				request.setAttribute("errorcont", new String(
				"开始金额不能大于结束金额，请重新输入！"));
				return mapping.findForward("errortest");				
			}
		}
		
		HttpSession session = request.getSession();
		session.setAttribute("bdate70",String.valueOf(beginDate));
		session.setAttribute("edate70",String.valueOf(endDate));
		session.setAttribute("deptNo",String.valueOf(deptNo));
		session.setAttribute("specNo",String.valueOf(specNo));
		session.setAttribute("classNo",String.valueOf(classNo));
		session.setAttribute("custType",String.valueOf(custType));
		session.setAttribute("shopid",String.valueOf(shopId));
		session.setAttribute("qserialType",String.valueOf(serialType));
		session.setAttribute("eStuempNo",String.valueOf(eStuempNo));
		session.setAttribute("bStuempNo",String.valueOf(bStuempNo));
		session.setAttribute("eStuempNo",String.valueOf(eStuempNo));
		session.setAttribute("sex",String.valueOf(sex));
		session.setAttribute("bqconsumeRange",String.valueOf(bconsumeRange));
		session.setAttribute("eqconsumeRange",String.valueOf(econsumeRange));
		//session.setAttribute("groupedlist",String.valueOf(groupedlist));
		
		beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
		endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
		
		List resultList = new TradeSerialDAO().consuemQuery(beginDate,endDate,deptNo,specNo,classNo,custType,
				cardType,serialType,bStuempNo,eStuempNo,bconsumeRange,econsumeRange,shopId,sex);
		if (null==resultList){
			request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
					"bydate", beginDate, endDate));
			return mapping.findForward("errortest");
		}
		request.setAttribute("resultList",resultList);
		//request.setAttribute("groupedlist",String.valueOf(groupedlist));
		
		request.setAttribute("specStatTip","消费信息查询");
		return mapping.findForward("consumequery_queryresult");
	}

	private String nullToString(Object o){
		if (o==null){
			return "";
		}else{
			return o.toString();
		}
	}
	
}
