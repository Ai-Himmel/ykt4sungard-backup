package com.kingstargroup.ecard.portlet.advquery.action;


import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.util.servlet.SessionErrors;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;


public class QueryAccountDtlByCustIdAction extends Action {

    public ActionForward execute(
            ActionMapping mapping,
            ActionForm form,
            HttpServletRequest request,
            HttpServletResponse response) throws Exception {

        response.setCharacterEncoding("UTF-8");
        
        DynaActionForm  queryaccountdtlform = (DynaActionForm)form;
        
        String beginDate = queryaccountdtlform.getString("queryaccountdtl_begindate");
        String endDate = queryaccountdtlform.getString("queryaccountdtl_enddate");
        String custId = queryaccountdtlform.getString("custId");
        String stuempno = queryaccountdtlform.getString("stuempno");
        
		
        request.setAttribute("custId", custId);
        request.setAttribute("stuempno", stuempno);
        String dateRange = beginDate + "-" + endDate;
        if ("".equals(custId) && "".equals(stuempno)) {
            SessionErrors.add(request, EcardConstants.QUERYACCOUNTDTL_ERROR_EXIST, "������Ҫ��ѯ�Ŀͻ��Ż�ѧ���ţ�");

            return mapping.findForward("errortest");
        } else if (!"".equals(stuempno)) {
            custId = AdvqueryServiceUtil.getCustIdBystuempNo(stuempno);
        }

        /*
		if(!"".equals(stuempno)){
	          String 	temp_custId =  AdvqueryServiceUtil.getCustIdBystuempNo(stuempno);
	          if((!"".equals(custId))&&!temp_custId.equals(custId)){
	        	 
	        	  SessionErrors.add(request,EcardConstants.QUERYACCOUNTDTL_ERROR_EXIST,"�ͻ������ڣ����������룡");
				  return mapping.findForward("errortest");
	          }else{
	        	  custId = temp_custId;
	          }
		}
		*/

        List detail = AdvqueryServiceUtil.getOneAccountDetail(custId, beginDate, endDate);
        if (null == detail || detail.isEmpty()) {
            SessionErrors.add(request, EcardConstants.QUERYACCOUNTDTL_ERROR_EXIST, "û����Ҫ��ѯ�����ݣ�������ָ����ѯ������");
            return mapping.findForward("errortest");
        }
        request.setAttribute("title", "���˽��������ϸ[" + dateRange + "]");
        request.setAttribute("result", detail);
        return mapping.findForward("accounttransdtl_queryresult");

    }
}
