/**
 * 
 */
package com.liferay.portal.mycaptcha;

import com.octo.captcha.engine.image.gimpy.DefaultGimpyEngine;
import com.octo.captcha.engine.image.gimpy.DeformedBaffleListGimpyEngine;
import com.octo.captcha.service.captchastore.FastHashMapCaptchaStore;
import com.octo.captcha.service.image.DefaultManageableImageCaptchaService;
import com.octo.captcha.service.image.ImageCaptchaService;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. File
 * name:CaptchaServiceSingleton.java Description: Modify History（或Change Log）:
 * 操作类型（创建、修改等） 操作日期 操作者 操作内容简述 创建 2009-4-24 何林青
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */

public class CaptchaServiceSingleton {
	private static ImageCaptchaService instance = new DefaultManageableImageCaptchaService(
			new FastHashMapCaptchaStore(), new MyImageCaptchaEngine(), 180,
			100000, 75000);

	public static ImageCaptchaService getInstance() {
		return instance;
	}

}
