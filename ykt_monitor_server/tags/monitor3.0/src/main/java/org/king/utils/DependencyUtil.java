package org.king.utils;

import org.apache.commons.beanutils.PropertyUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.SessionFactory;
import org.hibernate.metadata.ClassMetadata;
import org.king.framework.domain.BaseObject;

import java.beans.PropertyDescriptor;

/**
 * 该类主要用于处理struts actionform中实体关联属性的保存以及显示.
 * User: Yiming.You
 * Date: 2010-7-26
 */
public class DependencyUtil {
    private static final Log log = LogFactory.getLog(DependencyUtil.class);

    private static SessionFactory sessionFactory;

    public void setSessionFactory(SessionFactory sessionFactory) {
        DependencyUtil.sessionFactory = sessionFactory;
    }

    /**
     * 判断与关联的实体主键是否存在，如果不存在，那么将该关联实体置为null.
     *
     * @param baseObject .
     */
    public static void clearDependencyProperty(BaseObject baseObject) {
        try {
            PropertyDescriptor[] descriptors = PropertyUtils.getPropertyDescriptors(baseObject);
            for (int i = 0; i < descriptors.length; i++) {
                PropertyDescriptor propertyDescriptor = descriptors[i];
                String propertyName = propertyDescriptor.getName();
                Object propertyValue = PropertyUtils.getProperty(baseObject, propertyName);
                if (propertyValue != null && propertyValue instanceof BaseObject) {
                    //获得关联实体的主键名
                    String identifierPropertyName = getIdentifierPropertyName(propertyValue.getClass());
                    //获得关联实体的主键值
                    Object identifiesPropertyValue = PropertyUtils.getProperty(propertyValue, identifierPropertyName);
                    //如果关联实体的主键为空，那么将该关联实体置为null
                    if (null == identifiesPropertyValue) {
                        PropertyUtils.setProperty(baseObject, propertyName, null);
                    }
                }
            }
        } catch (Exception e) {
            log.error(e.getMessage());
        }
    }

    /**
     * 获得指定类主键属性名
     *
     * @param clazz .
     * @return .
     */
    private static String getIdentifierPropertyName(Class clazz) {
        ClassMetadata classMetadata = sessionFactory.getClassMetadata(clazz);
        return classMetadata.getIdentifierPropertyName();
    }

    /**
     * 当关联属性值为null时，对其进行初始化
     *
     * @param baseObject .
     */
    public static void initDependencyProperty(BaseObject baseObject) {
        try {
            PropertyDescriptor[] descriptors = PropertyUtils.getPropertyDescriptors(baseObject);
            for (int i = 0; i < descriptors.length; i++) {
                PropertyDescriptor propertyDescriptor = descriptors[i];
                String propertyName = propertyDescriptor.getName();

                Class type = PropertyUtils.getPropertyType(baseObject, propertyName);
                //如果是BaseObject的子类，并且值为null，那么对其进行初始化
                if (BaseObject.class.isAssignableFrom(type)) {
                    Object propertyValue = PropertyUtils.getProperty(baseObject, propertyName);
                    if (propertyValue == null) {
                        PropertyUtils.setProperty(baseObject, propertyName, type.newInstance());
                    }
                }
            }
        } catch (Exception e) {
            log.error(e.getMessage());
        }
    }
}
