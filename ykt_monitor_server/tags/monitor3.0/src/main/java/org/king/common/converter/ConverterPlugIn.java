package org.king.common.converter;

import org.apache.commons.beanutils.ConvertUtils;
import org.apache.commons.beanutils.converters.DoubleConverter;
import org.apache.commons.beanutils.converters.IntegerConverter;
import org.apache.commons.beanutils.converters.LongConverter;
import org.apache.struts.action.ActionServlet;
import org.apache.struts.action.PlugIn;
import org.apache.struts.config.ModuleConfig;

import javax.servlet.ServletException;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-19
 */
public class ConverterPlugIn implements PlugIn {
    public void destroy() {
    }

    public void init(ActionServlet servlet, ModuleConfig config) throws ServletException {
        //向BeanUtils中注册Long类型的转换器
        ConvertUtils.register(new LongConverter(null), Long.class);
        ConvertUtils.register(new IntegerConverter(null), Integer.class);
        ConvertUtils.register(new DoubleConverter(null), Double.class);
    }
}
