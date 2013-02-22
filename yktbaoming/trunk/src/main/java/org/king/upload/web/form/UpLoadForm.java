/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.upload.web.form.UpLoadForm.java
 * 创建日期： 2006-5-25 10:09:17
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-5-25 10:09:17      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.upload.web.form;

import javax.servlet.http.HttpServletRequest;

import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.upload.FormFile;
import org.apache.struts.upload.MultipartRequestHandler;

/**
 * <p> UpLoadForm.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="UpLoadForm.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-5-25
 * 
 *
 */
public class UpLoadForm extends ActionForm {

	  public static final String ERROR_PROPERTY_MAX_LENGTH_EXCEEDED = "org.apache.struts.webapp.upload.MaxLengthExceeded";
	  protected FormFile theFile;
	  public FormFile getTheFile() {
	      return theFile;
	  }
	  public void setTheFile(FormFile theFile) {
	      this.theFile = theFile;
	  }
	   public ActionErrors validate(
	        ActionMapping mapping,
	        HttpServletRequest request) {
	            
	        ActionErrors errors = null;
	        //has the maximum length been exceeded?
	        Boolean maxLengthExceeded =
	            (Boolean) request.getAttribute(
	                MultipartRequestHandler.ATTRIBUTE_MAX_LENGTH_EXCEEDED);
	                
	        if ((maxLengthExceeded != null) && (maxLengthExceeded.booleanValue())) {
	            errors = new ActionErrors();
	            errors.add(
	                ActionMessages.GLOBAL_MESSAGE ,
	                new ActionMessage("maxLengthExceeded"));
	            errors.add(
	                ActionMessages.GLOBAL_MESSAGE ,
	                new ActionMessage("maxLengthExplanation"));
	        }
	        return errors;

	    } 
}
