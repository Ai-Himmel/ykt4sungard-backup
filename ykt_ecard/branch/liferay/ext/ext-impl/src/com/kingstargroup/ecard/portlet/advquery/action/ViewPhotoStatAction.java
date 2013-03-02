/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
/**
 * 拍照情况统计
 * @author Administrator
 *
 */
public class ViewPhotoStatAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		DynaActionForm photoform = (DynaActionForm)form;
		photoform.set("statType", "".equals(photoform.getString("statType"))?"bydate":photoform.getString("statType"));
		photoform.set("querytype", "".equals(photoform.getString("querytype"))?"":photoform.getString("querytype"));
		photoform.set("showType", "".equals(photoform.getString("showType"))?"line":photoform.getString("showType"));
		photoform.set("emptype", "".equals(photoform.getString("emptype"))?"all":photoform.getString("emptype"));
		String eddate = DateUtil.getNow("yyyy-MM-dd");
		String bgdate = DateUtil.getNewTimes(eddate, -2592000, "yyyy-MM-dd");
		photoform.set("photo_begindate", "".equals(photoform.getString("photo_begindate"))?bgdate:photoform.getString("photo_begindate"));
		photoform.set("photo_enddate", "".equals(photoform.getString("photo_enddate"))?eddate:photoform.getString("photo_enddate"));
		List typeList = AdvqueryServiceUtil.getEmpType();
		request.setAttribute("typeList", typeList);
		return mapping.findForward("portlet.advquery.photo.view");
	}

}
