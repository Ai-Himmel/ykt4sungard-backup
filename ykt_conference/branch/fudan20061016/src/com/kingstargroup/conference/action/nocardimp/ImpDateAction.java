package com.kingstargroup.conference.action.nocardimp;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.util.AttendeeUtil;
import com.kingstargroup.conference.util.ExcelReader;
import com.kingstargroup.conference.util.ExcelUtil;

public class ImpDateAction extends Action {
	

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		try {

			request.setCharacterEncoding("UTF-8");
			String servrfileName = request.getParameter("servrfileName");
			String cmd = request.getParameter("cmd");
			ExcelReader readExcel = new ExcelReader();
			List excelList = ExcelUtil.readExcel(servrfileName, readExcel);
			String confid = (String)request.getSession().getAttribute("confid");
			boolean impdate = AttendeeUtil.ImpExcelDate(excelList,Integer.parseInt(confid),cmd);
			if(impdate){
			  request.setAttribute("tipinfo", NoCardConstant.IMPSUCC);
			  return mapping.findForward("success");
			}else{
			  request.setAttribute("tipinfo", NoCardConstant.IMPFAIL);
			  return mapping.findForward("error");
			}
			
		} catch (Exception e) {
			e.printStackTrace();
			request.setAttribute("tipinfo", NoCardConstant.WRONG);
			return mapping.findForward("error");
		}
	}

	/*private boolean ImpExcelDate(List list,int confid)throws Exception {
		try {
			 
			
			
		} catch (Exception e) {
			e.printStackTrace();
			throw new Exception("文件上传失败");
		}
	}*/
}

