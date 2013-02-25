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
import java.lang.annotation.Annotation;
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
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

/**
 * bcc 传输工具类.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-30
 * 
 */
public class TransfersUtils {

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
    public static List<Field> getTransferFields(Class<?> c, Class<? extends Annotation> tt) {
        List<Field> list = new ArrayList<Field>();
        if (isAnnotationTransfersElements(c)) {
            // List<Field> list = new ArrayList<Field>();
            Field[] fields = c.getDeclaredFields();
            for (Field field : fields) {
                if (field.isAnnotationPresent(tt)) {
                    list.add(field);
                }
            }
            // return list.size() > 0 ? list : null;
        }
        return list;
    }

    /**
     * 获取参数xpack.
     * 
     * @param Class
     *            <?> c
     * @return Set
     * @since v1.00
     * @see com.sungard.smartcard.utils.drtp.TransfersNodeInfo
     */
    public static Set<TransfersNodeInfo> getTransfersNodeInfosIn(Class<?> c) {
        if (isAnnotationTransfersElements(c)) {
            Set<TransfersNodeInfo> trans = new HashSet<TransfersNodeInfo>();

            List<Field> listf = getTransferFields(c, TransfersNodeIn.class);
            for (Field field : listf) {
                if (field.isAnnotationPresent(TransfersNodeIn.class)) {
                    TransfersNodeIn trIn = field.getAnnotation(TransfersNodeIn.class);
                    TransfersNodeType n = trIn.value();
                    TransfersNodeInfo temp = new TransfersNodeInfo();
                    temp.setDesc(trIn.desc());
                    temp.setField(field);
                    temp.setName(n.getName());
                    temp.setMethodName(n.getOptMethodName());
                    trans.add(temp);
                }
            }
            return trans.size() > 0 ? trans : null;
        }
        return null;
    }

    /**
     * 
     * 获取参数值.
     * 
     * @param <T>
     * @param c
     * @param trnasFactory
     * @return
     * @since v1.00
     * @see T
     */
    public static <T> List<T> getTransfersInObjects(Class<T> c, Object trnasFactory) {
        try {
            Set<TransfersNodeInfo> trans = getTransfersNodeInfosIn(c);
            if (trans == null || trans.size() < 1) {
                return null;
            }
            int rowCount = (Integer) MethodUtils.invokeExactMethod(trnasFactory, "GetRecordCount", null);
            List<T> listT = new ArrayList<T>();
            for (int i = 0; i < rowCount; i++) {
                T t = c.newInstance();
                for (TransfersNodeInfo transNodeInfo : trans) {
                    try {
                        Object o = MethodUtils.invokeMethod(trnasFactory, "Get" + transNodeInfo.getMethodName(),
                                new Object[] { i, transNodeInfo.getName() });
                        if (o != null) {
                            Field field = transNodeInfo.getField();
                            field.setAccessible(true);
                            field.set(t, o);
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
                }
                listT.add(t);
            }
            return listT;
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        }

        return null;
    }

    /**
     * 获取传输信息.
     * 
     * @param Class
     *            <?> c
     * @return Set
     * @since v1.00
     * @see com.sungard.smartcard.utils.drtp.TransfersNodeInfo
     */
    public static Set<TransfersNodeInfo> getTransfersNodeInfosOut(Class<?> c) {
        if (isAnnotationTransfersElements(c)) {
            Set<TransfersNodeInfo> trans = new HashSet<TransfersNodeInfo>();
            PropertyDescriptor[] props = PropertyUtils.getPropertyDescriptors(c);

            List<Field> listf = getTransferFields(c, TransfersNodeOut.class);
            for (Field field : listf) {
                String fieldName = field.getName();
                for (PropertyDescriptor prop : props) {
                    if (prop.getName().equals(fieldName)) {
                        Method method = PropertyUtils.getReadMethod(prop);
                        TransfersNodeOut trOut = field.getAnnotation(TransfersNodeOut.class);
                        TransfersNodeType n = trOut.value();
                        TransfersNodeInfo temp = new TransfersNodeInfo();
                        temp.setDesc(trOut.desc());
                        temp.setField(field);
                        temp.setName(n.getName());
                        temp.setMethodName(n.getOptMethodName());
                        temp.setMethod(method);
                        trans.add(temp);
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
    public static boolean TransfersOneNode(Object trnasFactory, Object transObj, TransfersNodeInfo transNodeInfo) {

        try {
            Object o = transNodeInfo.getMethod().invoke(transObj);
            if (o != null) {
                MethodUtils.invokeMethod(trnasFactory, "Set" + transNodeInfo.getMethodName(), new Object[] {
                        transNodeInfo.getName(), o });
            }
            return true;
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

    /**
     * 传输单条数据.
     * 
     * @param trnasFactory
     *            传输工厂方法
     * @param transObj
     *            被传输对象
     * @param transOuts
     *            传输元数据集.
     * @return
     * @since v1.00
     * @see com.sungard.smartcard.utils.drtp.TransfersNodeInfo
     */
    public static boolean TransfersOneRow(Object trnasFactory, Object transObj, Set<TransfersNodeInfo> transOuts) {

        boolean flag = true;
        if (transOuts != null && transOuts.size() > 0) {
            for (TransfersNodeInfo transNodeInfo : transOuts) {

                // TransfersOneNode(trnasFactory, transObj, transNodeInfo);

                try {
                    Object o = transNodeInfo.getMethod().invoke(transObj);
                    if (o != null) {
                        MethodUtils.invokeMethod(trnasFactory, "Set" + transNodeInfo.getMethodName(), new Object[] {
                                transNodeInfo.getName(), o });
                    }
                } catch (IllegalArgumentException e) {
                    e.printStackTrace();
                    flag = false;
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                    flag = false;
                } catch (InvocationTargetException e) {
                    e.printStackTrace();
                    flag = false;
                } catch (NoSuchMethodException e) {
                    e.printStackTrace();
                    flag = false;
                }

            }
            if (flag) {
                try {
                    MethodUtils.invokeMethod(trnasFactory, "PutRow", 0);
                } catch (NoSuchMethodException e) {
                    e.printStackTrace();
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                } catch (InvocationTargetException e) {
                    e.printStackTrace();
                }
            }

        }

        return flag;
    }

    /**
     * 传输所有对象.
     * 
     * @param <T>
     * @param trnasFactory
     * @param list
     * @param c
     * @return
     * @since v1.00
     * @see T
     */
    public static <T> boolean TransfersAllRow(Object trnasFactory, List<T> list, Class<T> c) {

        if (list == null || list.size() < 0)
            return true;

        Set<TransfersNodeInfo> trans = getTransfersNodeInfosOut(c);
        // 无标识传输量,无需传输，直接返加true
        if (trans == null || trans.size() < 1) {
            return true;
        }
        try {
            MethodUtils.invokeExactMethod(trnasFactory, "ClearRow", null);
            // session.SetAPackMaxRows(10);
            for (T operator : list) {

                // TransfersOneRow(trnasFactory, operator, trans);

                for (TransfersNodeInfo transNodeInfo : trans) {
                    if (!TransfersOneNode(trnasFactory, operator, transNodeInfo)) {
                        System.out.println("传输错误" + operator);
                    }
                }

                MethodUtils.invokeMethod(trnasFactory, "PutRow", 0);
                // ((BccServerThread)trnasFactory).PutRow(0);
                // session.PutRow(0);
            }
            return true;
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        }

        return false;
    }

}
