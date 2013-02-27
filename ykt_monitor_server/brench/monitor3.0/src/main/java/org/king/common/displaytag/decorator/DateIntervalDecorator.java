package org.king.common.displaytag.decorator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.displaytag.decorator.DisplaytagColumnDecorator;
import org.displaytag.exception.DecoratorException;
import org.displaytag.properties.MediaTypeEnum;
import org.king.utils.DateUtil;

import javax.servlet.jsp.PageContext;

/**
 * .将指定字符串格式的日期与当前时间比较，得到时间差字符串
 * User: Yiming.You
 * Date: 2010-7-15
 */
public class DateIntervalDecorator implements DisplaytagColumnDecorator {
    private static final Log log = LogFactory.getLog(DateIntervalDecorator.class);

    public Object decorate(Object columnValue, PageContext pageContext, MediaTypeEnum media) throws DecoratorException {
        String result = "";
        try {
            String value = columnValue.toString();
            if (columnValue != null) {
                result = DateUtil.convertTime(value);
            }
        } catch (Exception e) {
            log.error("Cannot compare given time");
        }
        return result;
    }
}
