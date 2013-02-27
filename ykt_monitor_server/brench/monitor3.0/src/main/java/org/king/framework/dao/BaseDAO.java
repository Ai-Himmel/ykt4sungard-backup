package org.king.framework.dao;

import java.io.Serializable;
import java.util.List;

public abstract interface BaseDAO extends DAO
{
  public abstract List findEntity(MyQuery paramMyQuery);

  public abstract List findEntity(String paramString);

  public abstract Object getEntity(Class paramClass, Serializable paramSerializable);

  public abstract void saveEntity(Object paramObject);

  public abstract void updateEntity(Object paramObject);

  public abstract void removeEntity(Object paramObject);
}