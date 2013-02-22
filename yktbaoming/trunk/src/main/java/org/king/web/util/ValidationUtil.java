/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.webapp.util.ValidationUtil.java
 * 创建日期： 2006-6-1 15:49:38
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-1 15:49:38      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.web.util;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.validator.Field;
import org.apache.commons.validator.GenericValidator;
import org.apache.commons.validator.ValidatorAction;
import org.apache.commons.validator.util.ValidatorUtils;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.validator.Resources;

/**
 * <p> ValidationUtil.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="ValidationUtil.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-1
 * 
 *
 */
public class ValidationUtil {
    //~ Methods ================================================================

    /**
     * Validates that two fields match.
     * @param bean
     * @param va
     * @param field
     * @param errors
     * @param request
     * @return boolean
     */
    public static boolean validateTwoFields(Object bean, ValidatorAction va,
                                            Field field, ActionMessages errors,
                                            HttpServletRequest request) {
        String value =
            ValidatorUtils.getValueAsString(bean, field.getProperty());
        String sProperty2 = field.getVarValue("secondProperty");
        String value2 = ValidatorUtils.getValueAsString(bean, sProperty2);

        if (!GenericValidator.isBlankOrNull(value)) {
            try {
                if (!value.equals(value2)) {
                    errors.add(field.getKey(),
                               Resources.getActionMessage(request, va, field));

                    return false;
                }
            } catch (Exception e) {
                errors.add(field.getKey(),
                           Resources.getActionMessage(request, va, field));

                return false;
            }
        }

        return true;
    }
	
}
