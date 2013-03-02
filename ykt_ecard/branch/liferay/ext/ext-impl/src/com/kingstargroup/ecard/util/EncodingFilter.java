package com.kingstargroup.ecard.util;

import java.io.IOException;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;

import org.apache.log4j.Logger;

public class EncodingFilter implements Filter {
	private static Logger log = Logger.getLogger(EncodingFilter.class);
	private String encode;

	public void destroy() {
		// TODO Auto-generated method stub

	}

	public void doFilter(ServletRequest request, ServletResponse response,
			FilterChain chain) throws IOException, ServletException {
		// TODO Auto-generated method stub
		if (null != encode) {
			request.setCharacterEncoding(encode);
			response.setContentType("text/html;charset=" + encode);
			response.setCharacterEncoding(encode);
			//log.info("fiter data success...");
		} else {
			request.setCharacterEncoding("UTF-8");
			response.setContentType("text/html;charset=UTF-8");
			response.setCharacterEncoding("UTF-8");
			//log.error("read web.xml init data failed....filter to default utf8");
		}
		chain.doFilter(request, response);
	}

	public void init(FilterConfig conf) throws ServletException {
		// TODO Auto-generated method stub
		encode = conf.getInitParameter("encode");
	}

}
