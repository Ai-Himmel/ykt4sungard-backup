/*
 * StartFuncsHolder.java  v1.00  2012-2-17
 * Peoject	smartcard-commons
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	StartFuncsHolder.java  v1.00 2012-2-17
 * Project	: 	smartcard-commons
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.util.holder;

import com.sungard.smartcard.bccsvr.FunctionInfo;
import org.springframework.stereotype.Component;

import java.util.HashMap;
import java.util.Map;

/**
 * 启动功能列表示意类.
 *
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-2-17
 */
@Component
public class StartFuncsHolder {

    private static Map<Integer, FunctionInfo> funcs;

    private StartFuncsHolder() {
        System.out.println("funcs = " + funcs);
    }

    public static Map<Integer, FunctionInfo> getFuncs() {
        if (funcs == null) {
            funcs = new HashMap<Integer, FunctionInfo>();
        }
        return funcs;
    }

    public static void setFuncs(Map<Integer, FunctionInfo> funcs) {
        StartFuncsHolder.funcs = funcs;
    }

    /**
     * 增加功能号信息.<br/>
     *
     * @param funInfo
     * @since v1.00
     */
    public static void addFunc(FunctionInfo funInfo) {
        getFuncs().put(funInfo.getFuncnum(), funInfo);
    }

    /**
     * 根据具体方法参加增加.<br/>
     *
     * @param funcnum
     * @param funcname
     * @param desc
     * @param classz
     * @since v1.00
     */
    public static void addFunc(int funcnum, String funcname, String desc, Class<?> classz) {
        addFunc(new FunctionInfo(funcnum, funcname, desc, classz));
    }

    /**
     * 移除功能信息.<br/>
     *
     * @param funcNum
     * @since v1.00
     */
    public static void removeFunc(int funcNum) {
        getFuncs().remove(funcNum);
    }

    /**
     * 返回特定功能的功能信息.<br/>
     *
     * @param funcNum
     * @return
     * @since v1.00
     */
    public static FunctionInfo getFunc(int funcNum) {

        if (getFuncs().containsKey(funcNum)) {
            return getFuncs().get(funcNum);
        }
        return null;
    }

}
