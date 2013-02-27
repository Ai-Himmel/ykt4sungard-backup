package org.king.common.displaytag.decorator;

import org.displaytag.decorator.DisplaytagColumnDecorator;
import org.displaytag.exception.DecoratorException;
import org.displaytag.properties.MediaTypeEnum;

import java.util.Map;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-14
 */
public class StateDecorator implements DisplaytagColumnDecorator {
    private Map status;

    public StateDecorator(Map status) {
        this.status = status;
    }

    public Object decorate(Object columnValue, javax.servlet.jsp.PageContext pageContext, MediaTypeEnum media) throws DecoratorException {
        String result = "";
        if (columnValue != null) {
            result = (String) status.get(columnValue.toString());
        }
        return result;
    }
}
