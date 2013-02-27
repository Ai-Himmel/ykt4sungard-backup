package org.king.common.displaytag.decorator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.displaytag.decorator.DisplaytagColumnDecorator;
import org.displaytag.exception.DecoratorException;
import org.displaytag.properties.MediaTypeEnum;

import javax.servlet.jsp.PageContext;

/**
 * .获取指定实体的属性
 * User: Yiming.You
 * Date: 2010-7-15
 */
public class EntityDecorator implements DisplaytagColumnDecorator {
    private static final Log log = LogFactory.getLog(EntityDecorator.class);

    private PropertyCallback propertyCallback;

    public EntityDecorator(PropertyCallback propertyCallback) {
        this.propertyCallback = propertyCallback;
    }

    public Object decorate(Object columnValue, PageContext pageContext, MediaTypeEnum media) throws DecoratorException {
        String result = "";
        try {
            result = propertyCallback.getProperty(columnValue);
        } catch (Exception e) {
            log.error("Cannot get property from the given column value");
        }
        return result;
    }
}
