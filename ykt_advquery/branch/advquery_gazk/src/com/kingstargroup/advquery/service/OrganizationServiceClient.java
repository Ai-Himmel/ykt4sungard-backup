
package com.kingstargroup.advquery.service;

import java.net.MalformedURLException;
import java.util.Collection;
import java.util.HashMap;

import javax.xml.namespace.QName;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.codehaus.xfire.XFireRuntimeException;
import org.codehaus.xfire.aegis.AegisBindingProvider;
import org.codehaus.xfire.annotations.AnnotationServiceFactory;
import org.codehaus.xfire.annotations.jsr181.Jsr181WebAnnotations;
import org.codehaus.xfire.client.XFireProxyFactory;
import org.codehaus.xfire.jaxb2.JaxbTypeRegistry;
import org.codehaus.xfire.service.Endpoint;
import org.codehaus.xfire.service.Service;
import org.codehaus.xfire.soap.AbstractSoapBinding;
import org.codehaus.xfire.transport.TransportManager;
import com.kingstargroup.advquery.util.GetPropertiesUtil;

import com.kingstargroup.advquery.util.TicketIdUtil;

public class OrganizationServiceClient {
    //10.14.158.96  ,222.66.165.27:8097
    private static XFireProxyFactory proxyFactory = new XFireProxyFactory();
    private HashMap endpoints = new HashMap();
    private Service service0;
    private String ip ="";
 
  

    public OrganizationServiceClient() {  
    	
    	PropertiesConfiguration config = GetPropertiesUtil.getInstance();
    	ip=config.getString("directpath");
        create0();
        Endpoint IOrganizationServiceLocalEndpointEP = service0 .addEndpoint(new QName("http://tempuri.org/", "IOrganizationServiceLocalEndpoint"), new QName("http://tempuri.org/", "IOrganizationServiceLocalBinding"), "xfire.local://OrganizationService");
        endpoints.put(new QName("http://tempuri.org/", "IOrganizationServiceLocalEndpoint"), IOrganizationServiceLocalEndpointEP);
        Endpoint BasicHttpBinding_IOrganizationServiceEP = service0 .addEndpoint(new QName("http://tempuri.org/", "BasicHttpBinding_IOrganizationService"), new QName("http://tempuri.org/", "BasicHttpBinding_IOrganizationService"), "http://"+ip+"/SAFF.Organization.Web/service/OrganizationService.svc");
        endpoints.put(new QName("http://tempuri.org/", "BasicHttpBinding_IOrganizationService"), BasicHttpBinding_IOrganizationServiceEP);
    }

    public Object getEndpoint(Endpoint endpoint) {
        try {
            return proxyFactory.create((endpoint).getBinding(), (endpoint).getUrl());
        } catch (MalformedURLException e) {
            throw new XFireRuntimeException("Invalid URL", e);
        }
    }

    public Object getEndpoint(QName name) {
        Endpoint endpoint = ((Endpoint) endpoints.get((name)));
        if ((endpoint) == null) {
            throw new IllegalStateException("No such endpoint!");
        }
        return getEndpoint((endpoint));
    }

    public Collection getEndpoints() {
        return endpoints.values();
    }

    private void create0() {
        TransportManager tm = (org.codehaus.xfire.XFireFactory.newInstance().getXFire().getTransportManager());
        HashMap props = new HashMap();
        props.put("annotations.allow.interface", true);
        AnnotationServiceFactory asf = new AnnotationServiceFactory(new Jsr181WebAnnotations(), tm, new AegisBindingProvider(new JaxbTypeRegistry()));
        asf.setBindingCreationEnabled(false);
        service0 = asf.create((IOrganizationService.class), props);
        {
            AbstractSoapBinding soapBinding = asf.createSoap11Binding(service0, new QName("http://tempuri.org/", "IOrganizationServiceLocalBinding"), "urn:xfire:transport:local");
        }
        {
            AbstractSoapBinding soapBinding = asf.createSoap11Binding(service0, new QName("http://tempuri.org/", "BasicHttpBinding_IOrganizationService"), "http://schemas.xmlsoap.org/soap/http");
        }
    }

    public IOrganizationService getIOrganizationServiceLocalEndpoint() {
        return ((IOrganizationService)(this).getEndpoint(new QName("http://tempuri.org/", "IOrganizationServiceLocalEndpoint")));
    }

    public IOrganizationService getIOrganizationServiceLocalEndpoint(String url) {
        IOrganizationService var = getIOrganizationServiceLocalEndpoint();
        org.codehaus.xfire.client.Client.getInstance(var).setUrl(url);
        return var;
    }

    public IOrganizationService getBasicHttpBinding_IOrganizationService() {
        return ((IOrganizationService)(this).getEndpoint(new QName("http://tempuri.org/", "BasicHttpBinding_IOrganizationService")));
    }

    public IOrganizationService getBasicHttpBinding_IOrganizationService(String url) {
        IOrganizationService var = getBasicHttpBinding_IOrganizationService();
        org.codehaus.xfire.client.Client.getInstance(var).setUrl(url);
        return var;
    }
    public static void main(String[] args) {

    	 OrganizationServiceClient client = new OrganizationServiceClient();
    	 
    	 IOrganizationService service = client.getBasicHttpBinding_IOrganizationService();
         //通过ticketid获取用户guid
    	/* ArrayOfguid   element = service.getSelectedUsersByTicketID("00fe9b82-90f3-45a9-bf27-3112bc3d6aeb");
    	                 
    	 List list  = element.getGuid();*/
    	 //通过ticketid获取部门guid
    	  System.out.println(TicketIdUtil.getSelectedUsersByTicketID("00fe9b82-90f3-45a9-bf27-3112bc3d6aeb"));
    	 
    	/* ArrayOfguid guids = service.getSelectedOrganizationalUnitsByTicketID("5a07f8df-b76a-4a7d-9c59-31232c712f3e");
    	 
    	 String guid = guids.getGuid().get(0);
    	 
    	 List  unit = service.getOrganizationalUnitsByIds(guids).getOrganizationalUnit();
    	 
    	 OrganizationalUnit  u = (OrganizationalUnit) unit.get(0);
  
    	 System.out.println(u.getName().getValue());    */	 
    	 
    	/* ArrayOfViewUserOrganizationalUnitRole  user =  service.getUsersByOrganizationalUnit("{9ca9fc32-8be2-408f-9e2c-518feed0f23f}", true, true);
    	 
    	 List list  = user.getViewUserOrganizationalUnitRole();
    	 
    	 ViewUserOrganizationalUnitRole  a  =  (ViewUserOrganizationalUnitRole)list.get(0);
    	 
    	 System.out.println(a.getUserName().getValue());
    	*/
    	// List list  = user.getOrganizationalUnit();
    	 
    	// System.out.print(((OrganizationalUnit)list.get(0)).getName());
    	// List list  = user.getViewUserOrganizationalUnitRole();
    	 
    	// System.out.println(list);
    	// System.out.println(list.size());
    	// System.out.println(((ViewUserOrganizationalUnitRole)(list.get(1))).getUserName());
    	 
    	 
    }

}
