package org.king.common.displaytag.decorator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.displaytag.decorator.DisplaytagColumnDecorator;
import org.displaytag.exception.DecoratorException;
import org.displaytag.properties.MediaTypeEnum;

import javax.servlet.jsp.PageContext;
import java.text.Format;

/**
 * .将指定字符串转换成日期形式的字符
 * User: Yiming.You
 * Date: 2010-7-14
 */
public class DateDecorator implements DisplaytagColumnDecorator {
    private static final Log log = LogFactory.getLog(DateDecorator.class);

    private Format format;

    public DateDecorator(Format format) {
        this.format = format;
    }

    public Object decorate(Object columnValue, PageContext pageContext, MediaTypeEnum media) throws DecoratorException {
        String result = "";
        try {
            String value = columnValue.toString();
            if (columnValue != null) {
                Object[] array = {value.substring(0, 4), value.substring(4, 6), value.substring(6, 8), value.substring(8, 10), value.substring(10, 12), value.substring(12, 14)};
                result = format.format(array);
            }
        } catch (Exception e) {
            log.error("Cannot format given Object");
        }
        return result;
    }
}
