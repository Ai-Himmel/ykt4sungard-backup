package org.king.utils;

import org.apache.commons.beanutils.PropertyUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.SessionFactory;
import org.hibernate.metadata.ClassMetadata;
import org.king.framework.domain.BaseObject;

import java.beans.PropertyDescriptor;

/**
 * ������Ҫ���ڴ���struts actionform��ʵ��������Եı����Լ���ʾ.
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
     * �ж��������ʵ�������Ƿ���ڣ���������ڣ���ô���ù���ʵ����Ϊnull.
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
                    //��ù���ʵ���������
                    String identifierPropertyName = getIdentifierPropertyName(propertyValue.getClass());
                    //��ù���ʵ�������ֵ
                    Object identifiesPropertyValue = PropertyUtils.getProperty(propertyValue, identifierPropertyName);
                    //�������ʵ�������Ϊ�գ���ô���ù���ʵ����Ϊnull
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
     * ���ָ��������������
     *
     * @param clazz .
     * @return .
     */
    private static String getIdentifierPropertyName(Class clazz) {
        ClassMetadata classMetadata = sessionFactory.getClassMetadata(clazz);
        return classMetadata.getIdentifierPropertyName();
    }

    /**
     * ����������ֵΪnullʱ��������г�ʼ��
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
                //�����BaseObject�����࣬����ֵΪnull����ô������г�ʼ��
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
