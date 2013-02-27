package org.king.framework.exception;

public class BusinessException extends BaseException
{
  public BusinessException()
  {
  }

  public BusinessException(String s)
  {
    super(s);
  }

  public BusinessException(String s, Throwable e)
  {
    super(s, e);
  }

  public BusinessException(Throwable e)
  {
    super(e);
  }
}