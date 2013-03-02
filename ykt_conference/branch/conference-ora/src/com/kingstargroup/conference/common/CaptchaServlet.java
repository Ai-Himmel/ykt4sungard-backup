package com.kingstargroup.conference.common;

import java.io.IOException;

import javax.imageio.ImageIO;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.octo.captcha.image.ImageCaptcha;


/**
 * @author hjw
 *
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