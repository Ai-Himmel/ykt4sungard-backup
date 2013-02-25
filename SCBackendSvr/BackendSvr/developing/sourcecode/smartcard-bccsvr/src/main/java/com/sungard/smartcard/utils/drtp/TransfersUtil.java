/*
 * TransfersUtil.java  v1.00  2011-12-30
 * Peoject	smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	TransfersUtil.java  v1.00 2011-12-30
 * Project	: 	smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.utils.drtp;

import java.beans.BeanInfo;
import java.beans.IntrospectionException;
import java.beans.Introspector;
import java.beans.PropertyDescriptor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import org.apache.commons.beanutils.MethodUtils;
import org.apache.commons.beanutils.PropertyUtils;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNode;

/**
 * bcc 传输工具类.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-30
 * 
 */
public class TransfersUtil {

    /**
     * 获取beanInfo.
     * 
     * @param Class
     *            <?> c
     * @return BeanInfo
     * @since v1.00
     * @see java.beans.BeanInfo
     */
    public static BeanInfo getBeanInfo(Class<?> c) {
        BeanInfo beanInfo = null;
        try {
            beanInfo = Introspector.getBeanInfo(c);
        } catch (IntrospectionException e) {
            e.printStackTrace();
        }

        return beanInfo;
    }

    /**
     * 是否被注解于drtp传输.
     * 
     * @param Class
     *            <?> c
     * @return boolean
     * @since v1.00
     * @see com.sungard.smartcard.annotation.TransfersElement
     */
    public static boolean isAnnotationTransfersElements(Class<?> c) {
        return c.isAnnotationPresent(TransfersElement.class);
    }

    /**
     * 返回带注解的field List.
     * 
     * @param Class
     *            <?> c
     * @return List<Field>
     * @since v1.00
     */
    public static List<Field> getTransferFields(Class<?> c) {
        if (isAnnotationTransfersElements(c)) {
            List<Field> list = new ArrayList<Field>();
            Field[] fields = c.getDeclaredFields();
            for (Field field : fields) {
                if (field.isAnnotationPresent(TransfersNode.class)) {
                    list.add(field);
                }
            }
            return list.size() > 0 ? list : null;
        }
        return null;
    }

    /**
     * 获取读取方法上的传输注解信息.如field及读取方法上都设置了以field上为准.
     * 
     * @param Class
     *            <?> c
     * @return Set
     * @since v1.00
     * @see com.sungard.smartcard.utils.drtp.TransfersNodeInfo
     */
    public static Set<TransfersNodeInfo> getTransfersNodeInfos(Class<?> c) {
        if (isAnnotationTransfersElements(c)) {
            Set<TransfersNodeInfo> trans = new HashSet<TransfersNodeInfo>();
            PropertyDescriptor[] props = PropertyUtils.getPropertyDescriptors(c);

            List<Field> listf = getTransferFields(c);
            for (Field field : listf) {
                String fieldName = field.getName();
                for (PropertyDescriptor prop : props) {
                    if (prop.getName().equals(fieldName)) {
                        Method method = PropertyUtils.getReadMethod(prop);
                        TransfersNode node = field.getAnnotation(TransfersNode.class);
                        trans.add(new TransfersNodeInfo(node.name(), method, method.getReturnType()));
                    }
                }
            }

            for (PropertyDescriptor prop : props) {
                Method method = PropertyUtils.getReadMethod(prop);
                if (method.isAnnotationPresent(TransfersNode.class)) {
                    TransfersNode node = method.getAnnotation(TransfersNode.class);
                    boolean flag = true;
                    for (TransfersNodeInfo tnf : trans) {
                        if (tnf.getMethod().equals(method)) {
                            flag = false;
                            break;
                        }
                    }
                    if (flag) {
                        trans.add(new TransfersNodeInfo(node.name(), method, method.getReturnType()));
                    }
                }
            }

            return trans.size() > 0 ? trans : null;
        }
        return null;
    }

    /**
     * 获取写入方法上的传输注解信息.如field及写入方法上都设置了以field上为准.
     * 
     * @param Class
     *            <?> c
     * @return Set
     * @since v1.00
     * @see com.sungard.smartcard.utils.drtp.TransfersNodeInfo
     */
    public static Set<TransfersNodeInfo> setTransfersNodeInfos(Class<?> c) {
        if (isAnnotationTransfersElements(c)) {
            Set<TransfersNodeInfo> trans = new HashSet<TransfersNodeInfo>();
            PropertyDescriptor[] props = PropertyUtils.getPropertyDescriptors(c);

            List<Field> listf = getTransferFields(c);
            for (Field field : listf) {
                String fieldName = field.getName();
                for (PropertyDescriptor prop : props) {
                    if (prop.getName().equals(fieldName)) {
                        Method method = PropertyUtils.getWriteMethod(prop);
                        TransfersNode node = field.getAnnotation(TransfersNode.class);
                        trans.add(new TransfersNodeInfo(node.name(), method, method.getReturnType()));
                    }
                }
            }

            for (PropertyDescriptor prop : props) {
                Method method = PropertyUtils.getWriteMethod(prop);
                if (method != null && method.isAnnotationPresent(TransfersNode.class)) {
                    TransfersNode node = method.getAnnotation(TransfersNode.class);
                    boolean flag = true;
                    for (TransfersNodeInfo tnf : trans) {
                        if (tnf.getMethod().equals(method)) {
                            flag = false;
                            break;
                        }
                    }
                    if (flag) {
                        trans.add(new TransfersNodeInfo(node.name(), method, method.getReturnType()));
                    }
                }
            }

            return trans.size() > 0 ? trans : null;
        }
        return null;
    }

    /**
     * 传输对象.
     * 
     * @param BccServerThread
     *            trnasFactory
     * @param transObj
     *            传输对象
     * @param transNodeInfo
     *            组织传输信息
     * @return boolean
     * @since v1.00
     * @see com.sungard.smartcard.bccsvr.BccServerThread
     */
    public static boolean TransfersRow(Object trnasFactory, Object transObj, TransfersNodeInfo transNodeInfo) {

        try {
            Object o;
            o = transNodeInfo.getMethod().invoke(transObj);
            if (o != null) {
                MethodUtils.invokeExactMethod(trnasFactory, transNodeInfo.getMethodName(), new Object[] {
                        transNodeInfo.getName(), transNodeInfo.getMethod().invoke(transObj) });
                return true;
            }
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }

        return false;
    }

    public static boolean TransfersAll() {

        return false;
    }

}
