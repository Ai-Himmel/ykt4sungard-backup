/**
 * 
 */
package com.kingstargroup.ecard.filters;

import java.io.IOException;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.kingstargroup.ecard.util.WebCountUtil;
import com.liferay.util.servlet.UploadServletRequest;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ThreatFilter.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-10-18  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ThreatFilter implements Filter {

	/**
	 * 
	 */
	public ThreatFilter() {
		super();
		// TODO Auto-generated constructor stub
	}

	/* (non-Javadoc)
	 * @see javax.servlet.Filter#init(javax.servlet.FilterConfig)
	 */
	public void init(FilterConfig arg0) throws ServletException {
		// TODO Auto-generated method stub

	}

	/* (non-Javadoc)
	 * @see javax.servlet.Filter#doFilter(javax.servlet.ServletRequest, javax.servlet.ServletResponse, javax.servlet.FilterChain)
	 */
	public void doFilter(ServletRequest req, ServletResponse res,
			FilterChain chain) throws IOException, ServletException {
		HttpServletRequest request = (HttpServletRequest)req;
		HttpServletResponse response = (HttpServletResponse)res;
		String contentType = request.getHeader("Content-Type");
		if ((contentType != null) &&
			(contentType.startsWith("multipart/form-data"))) {			
			String length = request.getHeader("content-length");								
			if (Integer.parseInt(length) > UploadServletRequest.DEFAULT_SIZE_MAX) {
				/*
				if (!response.isCommitted()) {
					response.setHeader("Connection","close");
					ServletOutputStream out = response.getOutputStream();
					out.write("Baddly File Upload Request!".getBytes());
					out.flush();
					return;
				}*/
				//response.setHeader("Connection","close");
				//response.sendRedirect("/html/common/upload_warning.jsp");				
			}
		}
		chain.doFilter(req, res);
	}

	/* (non-Javadoc)
	 * @see javax.servlet.Filter#destroy()
	 */
	public void destroy() {
		// TODO Auto-generated method stub

	}

}
