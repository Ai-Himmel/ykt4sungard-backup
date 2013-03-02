/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.check.web.CheckTotalAction.java
 * �������ڣ� 2006-6-13 13:48:18
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-13 13:48:18      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.check.web.action;

import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.extremecomponents.table.limit.Limit;
import org.king.check.service.CheckTotalService;
import org.king.check.service.WorkInfoService;
import org.king.framework.common.support.Page;
import org.king.framework.util.ExtremeTableUtil;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;

/**
 * <p>
 * CheckAction.java
 * </p>
 * <p>
 * {����˵��}
 * </p>
 * 
 * <p>
 * <a href="CheckTotalAction.java.html"><i>�鿴Դ����</i></a>
 * </p>
 * 
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-13
 * 
 * 
 */
public class CheckTotalAction extends BaseAction {
	
	private static final int defaultPageSize = 3;

	private CheckTotalService checkTotalService;
	
	
	
	public void setCheckTotalService(CheckTotalService checkTotalService) {
		this.checkTotalService = checkTotalService;
	}

	/**
	 * 
	 * װ�ؿ�����־��ѯ
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward load4CheckLogQuery(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		return mapping.findForward("input");
	}

	/**
	 * ��ѯ������־
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward checkLogQuery(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
	    Limit limit = ExtremeTableUtil.getLimit(request, defaultPageSize);
		Map filterMap = WebUtils.getParametersStartingWith(request, "search_");
		
		Page page = checkTotalService.findBy(filterMap,ExtremeTableUtil.getSort(limit),limit.getPage(),limit.getCurrentRowsDisplayed());

		request.setAttribute("workinfos",page.getResult());
		request.setAttribute("totalRows",new Integer(page.getTotalSize()));
		
		return mapping.findForward("success");
	}
	
	/**
	 * ������Ա��Ϣ��ѯ
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward load4clerkQuery(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		
		
		
		
		return mapping.findForward("input");
	}
	
	
	public ActionForward clerkQuery(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		
		
		
		return mapping.findForward("success");
	}
	
}
