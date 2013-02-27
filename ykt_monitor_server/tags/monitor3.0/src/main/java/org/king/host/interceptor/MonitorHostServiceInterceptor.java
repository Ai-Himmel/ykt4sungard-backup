package org.king.host.interceptor;

import org.aopalliance.intercept.MethodInterceptor;
import org.aopalliance.intercept.MethodInvocation;

public class MonitorHostServiceInterceptor implements MethodInterceptor {

	public Object invoke(MethodInvocation arg0) throws Throwable {
		try {
            
            if (arg0.getMethod().getName().equals("printUser"))
              //���ط����Ƿ���UserService�ӿڵ�printUser���� 
            {
                 Object[] args = arg0.getArguments();//�����صĲ���
                 System.out.println("user:"+args[0]);
                 arg0.getArguments()[0]="hello!" ;//�޸ı����صĲ���
                
                
            }
            
            System.out.println(arg0.getMethod().getName() + "---!");
                        return arg0.proceed();//����UserService�ӿڵ�printUser����

        } catch (Exception e) {
            throw e;
        }

	}

}
