package org.king.template.exception;

import org.king.framework.exception.BaseException;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-6
 */
public class TemplateAlreadyExistException extends BaseException {
    /**
     *
     */
    public TemplateAlreadyExistException() {
        super();
    }

    /**
     * @param s
     */
    public TemplateAlreadyExistException(String s) {
        super(s);
    }

    /**
     * @param s
     * @param e
     */
    public TemplateAlreadyExistException(String s, Throwable e) {
        super(s, e);
    }

    /**
     * @param e
     */
    public TemplateAlreadyExistException(Throwable e) {
        super(e);
    }
}
