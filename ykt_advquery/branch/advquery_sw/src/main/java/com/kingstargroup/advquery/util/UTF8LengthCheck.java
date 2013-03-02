/**
 * 
 */
package com.kingstargroup.advquery.util;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.validator.Field;
import org.apache.commons.validator.Validator;
import org.apache.commons.validator.ValidatorAction;
import org.apache.commons.validator.util.ValidatorUtils;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.validator.Resources;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: UTF8LengthCheck.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-7  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class UTF8LengthCheck {

	public static boolean validateMaxLength
		(Object bean, ValidatorAction va, Field field, ActionMessages errors,
				Validator validator, HttpServletRequest request) {
		String value = null;
		if (isString(bean))
		    value = (String) bean;
		else
		    value = ValidatorUtils.getValueAsString(bean, field.getProperty());
		if (value != null) {
		    try {
				int max = Integer.parseInt(field.getVarValue("maxlength"));
				if (!maxLength(value, max)) {
				    errors.add(field.getKey(),
					       Resources.getActionMessage(validator, request,
									  va, field));
				    return false;
				}
		    } catch (Exception e) {
				errors.add(field.getKey(),
					   Resources.getActionMessage(validator, request, va,
								      field));
			return false;
		    }
		}
		return true;
    }
	
	protected static boolean isString(Object o) {
		return o == null ? true : String.class.isInstance(o);
	}
	
	private static boolean maxLength(String value, int max) {
		try {
			byte bytes[] = value.getBytes("UTF-8");
			if (bytes.length <= max) {
				return true;
			}
		} catch (Exception ex) {
			
		}
		return false;
	}

}
