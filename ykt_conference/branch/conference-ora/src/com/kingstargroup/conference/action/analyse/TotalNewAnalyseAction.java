/**
 * 
 */
package com.kingstargroup.conference.action.analyse;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.ajaxanywhere.AAUtils;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.GetterUtil;
import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.util.AnalyseUtil;
import com.kingstargroup.conference.util.ConferenceUtil;

public class TotalNewAnalyseAction extends Action {

	public ActionForward execute(
			ActionMapping mapping,
			ActionForm form,
			HttpServletRequest request,
			HttpServletResponse response) {
		String custno = ParamUtil.getString(request, "custno");
		String custname = ParamUtil.getString(request, "custname");
		String deptCode = ParamUtil.getString(request, "dept");
		String type = ParamUtil.getString(request,"type");
		String begindate = ParamUtil.getString(request, "begindate");
		String enddate = ParamUtil.getString(request, "enddate");
		String username = GetterUtil.get((String) request.getSession().getAttribute("username"), "");
		try {
			List result1 = ConferenceUtil.getConfList1(custno,custname,deptCode,type,begindate,enddate,username);
			List result2 = ConferenceUtil.getConfList2(custno,custname,deptCode,type,begindate,enddate,username);
			List result3 = ConferenceUtil.getConfList3(custno,custname,deptCode,type,begindate,enddate,username);
			List result4 = ConferenceUtil.getConfList4(custno,custname,deptCode,type,begindate,enddate,username);
			
			List confList = ConferenceUtil.getConfList5(custno,custname,deptCode,type,begindate,enddate,username);
			List deptCustList = ConferenceUtil.getConfList6(custno,custname,deptCode,type,begindate,enddate,username);
			List result7 = ConferenceUtil.getConfList7(custno,custname,deptCode,type,begindate,enddate,username);

			if (null == result1){
				request.setAttribute("tipinfo","没有你要查找的会议记录，请重新指定查询条件！");
				return mapping.findForward("error");
			}
			request.setAttribute("result1", result1);
			request.setAttribute("result2", result2);
			request.setAttribute("result3", result3);
			request.setAttribute("result4", result4);
			
			request.setAttribute("confList", confList);
			request.setAttribute("deptCustList", deptCustList); 
			request.setAttribute("result7", result7); 
			return mapping.findForward("totalnewreport");
			
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("error");
		}
		
	}
}