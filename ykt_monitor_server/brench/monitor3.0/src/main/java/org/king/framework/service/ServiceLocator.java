package org.king.framework.service;

import org.springframework.beans.factory.config.ConfigurableListableBeanFactory;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.AbstractApplicationContext;

public class ServiceLocator
{
  private static ServiceLocator instance = new ServiceLocator();
  private ApplicationContext context;

  public static ServiceLocator getInstance()
  {
    return instance;
  }

  public Object getService(String service)
  {
    return context.getBean(service);
  }

  private ApplicationContext getContext() {
    return context;
  }

  public void setContext(ApplicationContext context) {
    this.context = context;
  }

  public void autowireService(Object bean) {
    ((AbstractApplicationContext)context).getBeanFactory().autowireBeanProperties(bean, 1, false);
  }
}