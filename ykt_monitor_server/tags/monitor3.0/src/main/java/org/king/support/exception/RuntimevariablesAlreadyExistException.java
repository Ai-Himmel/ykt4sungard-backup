package org.king.support.exception;

import org.king.framework.exception.BaseException;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-9
 */
public class RuntimevariablesAlreadyExistException extends BaseException {
    /**
     *
     */
    public RuntimevariablesAlreadyExistException() {
        super();
    }

    /**
     * @param s
     */
    public RuntimevariablesAlreadyExistException(String s) {
        super(s);
    }

    /**
     * @param s
     * @param e
     */
    public RuntimevariablesAlreadyExistException(String s, Throwable e) {
        super(s, e);
    }

    /**
     * @param e
     */
    public RuntimevariablesAlreadyExistException(Throwable e) {
        super(e);
    }
}
