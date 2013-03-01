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

import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.tradeserial.TradeSerialDAO;

/**
 * 住训培训服务费查询
 * 
 * @author Administrator
 *  
 */
public class SerFeeQueryAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		// 班级
		String classNo = request.getParameter("classno").toString();
		// 批次号
		String patchNo = request.getParameter("patchno").toString();
		// 身份证号
		String certNo = request.getParameter("certno").toString();
		
		//String cutName= "";
		 //  request.getParameter("cutName").toString();
		
		String stuempNo= request.getParameter("stuempno").toString();
		
		
		
		HttpSession session = request.getSession();
		session.setAttribute("classno",classNo);
		session.setAttribute("patchno",patchNo);
		session.setAttribute("certno",certNo);
		session.setAttribute("stuempno",stuempNo);
		
		List result = new TradeSerialDAO().getSerFeeList(classNo,patchNo,certNo,stuempNo);
		
		if (null==result){
			request.setAttribute("errorcont", new ErrorInfo().getErrorTip2());
			return mapping.findForward("errortest");			
		}
		request.getSession().setAttribute("SerFeeQuery",result);
		request.setAttribute("titles","住训培训服务费查询");
		return mapping.findForward("serfee_queryresult");
	}
}
