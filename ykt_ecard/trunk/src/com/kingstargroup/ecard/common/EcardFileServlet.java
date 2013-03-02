/**
 * 
 */
package com.kingstargroup.ecard.common;

import java.io.IOException;
import java.net.URLEncoder;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.UploadFileUtil;
import com.liferay.util.servlet.ServletResponseUtil;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: EcardFileServlet.java
 * Description: 
 * Modify History: 
 * 操作类型   操作人   操作时间     操作内容
 * ===================================
 *  创建    Xiao Qi  2005-9-14  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class EcardFileServlet extends HttpServlet {

	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {
		try {
			_writeFile(req, res);
		} catch (PortalException pe) {
			_log.error(pe);
		}
	}
	
	private void _writeFile(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException, PortalException {
		String id = req.getParameter("id");
		byte[] bytes = UploadFileUtil.downloadFile(id);
		String fileName = UploadFileUtil.getFileName(id);
		ServletResponseUtil.sendFile(res, 
									fileName, 
									bytes);
	}

	private static final Log _log = LogFactory.getLog(EcardImageServlet.class);

}
