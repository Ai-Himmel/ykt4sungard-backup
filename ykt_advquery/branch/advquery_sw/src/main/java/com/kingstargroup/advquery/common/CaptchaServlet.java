package com.kingstargroup.advquery.common;

import java.io.IOException;

import javax.imageio.ImageIO;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.kingstargroup.advquery.util.WebKeys;
import com.octo.captcha.image.ImageCaptcha;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: CaptchaServlet.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-14  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class CaptchaServlet extends HttpServlet {

	public void init(ServletConfig sc) throws ServletException {
		synchronized (CaptchaServlet.class) {
			super.init(sc);

			try {
				
				_engine = new ValidCodeEngine();
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		HttpSession ses = req.getSession();

		ImageCaptcha captcha = (ImageCaptcha)ses.getAttribute(WebKeys.CAPTCHA);

		if (captcha == null) {
			captcha = _engine.getImageCaptchaFactory().getImageCaptcha();

			ses.setAttribute(WebKeys.CAPTCHA, captcha);
		}

		ServletOutputStream out = res.getOutputStream();

		ImageIO.write(
			captcha.getImageChallenge(), "jpeg", res.getOutputStream());

		out.flush();
	}

	private ValidCodeEngine _engine;

}