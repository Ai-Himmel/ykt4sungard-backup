/**
 * WSRPServiceLocator.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.wsdl;

public class WSRPServiceLocator extends org.apache.axis.client.Service implements oasis.names.tc.wsrp.v1.wsdl.WSRPService {

    public WSRPServiceLocator() {
    }


    public WSRPServiceLocator(org.apache.axis.EngineConfiguration config) {
        super(config);
    }

    public WSRPServiceLocator(java.lang.String wsdlLoc, javax.xml.namespace.QName sName) throws javax.xml.rpc.ServiceException {
        super(wsdlLoc, sName);
    }

    // Use to get a proxy class for WSRPPortletManagementService
    private java.lang.String WSRPPortletManagementService_address = "http://localhost:8080/WSRPService";

    public java.lang.String getWSRPPortletManagementServiceAddress() {
        return WSRPPortletManagementService_address;
    }

    // The WSDD service name defaults to the port name.
    private java.lang.String WSRPPortletManagementServiceWSDDServiceName = "WSRPPortletManagementService";

    public java.lang.String getWSRPPortletManagementServiceWSDDServiceName() {
        return WSRPPortletManagementServiceWSDDServiceName;
    }

    public void setWSRPPortletManagementServiceWSDDServiceName(java.lang.String name) {
        WSRPPortletManagementServiceWSDDServiceName = name;
    }

    public oasis.names.tc.wsrp.v1.intf.WSRP_v1_PortletManagement_PortType getWSRPPortletManagementService() throws javax.xml.rpc.ServiceException {
       java.net.URL endpoint;
        try {
            endpoint = new java.net.URL(WSRPPortletManagementService_address);
        }
        catch (java.net.MalformedURLException e) {
            throw new javax.xml.rpc.ServiceException(e);
        }
        return getWSRPPortletManagementService(endpoint);
    }

    public oasis.names.tc.wsrp.v1.intf.WSRP_v1_PortletManagement_PortType getWSRPPortletManagementService(java.net.URL portAddress) throws javax.xml.rpc.ServiceException {
        try {
            oasis.names.tc.wsrp.v1.bind.WSRP_v1_PortletManagement_Binding_SOAPStub _stub = new oasis.names.tc.wsrp.v1.bind.WSRP_v1_PortletManagement_Binding_SOAPStub(portAddress, this);
            _stub.setPortName(getWSRPPortletManagementServiceWSDDServiceName());
            return _stub;
        }
        catch (org.apache.axis.AxisFault e) {
            return null;
        }
    }

    public void setWSRPPortletManagementServiceEndpointAddress(java.lang.String address) {
        WSRPPortletManagementService_address = address;
    }


    // Use to get a proxy class for WSRPRegistrationService
    private java.lang.String WSRPRegistrationService_address = "http://localhost:8080/WSRPService";

    public java.lang.String getWSRPRegistrationServiceAddress() {
        return WSRPRegistrationService_address;
    }

    // The WSDD service name defaults to the port name.
    private java.lang.String WSRPRegistrationServiceWSDDServiceName = "WSRPRegistrationService";

    public java.lang.String getWSRPRegistrationServiceWSDDServiceName() {
        return WSRPRegistrationServiceWSDDServiceName;
    }

    public void setWSRPRegistrationServiceWSDDServiceName(java.lang.String name) {
        WSRPRegistrationServiceWSDDServiceName = name;
    }

    public oasis.names.tc.wsrp.v1.intf.WSRP_v1_Registration_PortType getWSRPRegistrationService() throws javax.xml.rpc.ServiceException {
       java.net.URL endpoint;
        try {
            endpoint = new java.net.URL(WSRPRegistrationService_address);
        }
        catch (java.net.MalformedURLException e) {
            throw new javax.xml.rpc.ServiceException(e);
        }
        return getWSRPRegistrationService(endpoint);
    }

    public oasis.names.tc.wsrp.v1.intf.WSRP_v1_Registration_PortType getWSRPRegistrationService(java.net.URL portAddress) throws javax.xml.rpc.ServiceException {
        try {
            oasis.names.tc.wsrp.v1.bind.WSRP_v1_Registration_Binding_SOAPStub _stub = new oasis.names.tc.wsrp.v1.bind.WSRP_v1_Registration_Binding_SOAPStub(portAddress, this);
            _stub.setPortName(getWSRPRegistrationServiceWSDDServiceName());
            return _stub;
        }
        catch (org.apache.axis.AxisFault e) {
            return null;
        }
    }

    public void setWSRPRegistrationServiceEndpointAddress(java.lang.String address) {
        WSRPRegistrationService_address = address;
    }


    // Use to get a proxy class for WSRPBaseService
    private java.lang.String WSRPBaseService_address = "http://localhost:8080/WSRPService";

    public java.lang.String getWSRPBaseServiceAddress() {
        return WSRPBaseService_address;
    }

    // The WSDD service name defaults to the port name.
    private java.lang.String WSRPBaseServiceWSDDServiceName = "WSRPBaseService";

    public java.lang.String getWSRPBaseServiceWSDDServiceName() {
        return WSRPBaseServiceWSDDServiceName;
    }

    public void setWSRPBaseServiceWSDDServiceName(java.lang.String name) {
        WSRPBaseServiceWSDDServiceName = name;
    }

    public oasis.names.tc.wsrp.v1.intf.WSRP_v1_Markup_PortType getWSRPBaseService() throws javax.xml.rpc.ServiceException {
       java.net.URL endpoint;
        try {
            endpoint = new java.net.URL(WSRPBaseService_address);
        }
        catch (java.net.MalformedURLException e) {
            throw new javax.xml.rpc.ServiceException(e);
        }
        return getWSRPBaseService(endpoint);
    }

    public oasis.names.tc.wsrp.v1.intf.WSRP_v1_Markup_PortType getWSRPBaseService(java.net.URL portAddress) throws javax.xml.rpc.ServiceException {
        try {
            oasis.names.tc.wsrp.v1.bind.WSRP_v1_Markup_Binding_SOAPStub _stub = new oasis.names.tc.wsrp.v1.bind.WSRP_v1_Markup_Binding_SOAPStub(portAddress, this);
            _stub.setPortName(getWSRPBaseServiceWSDDServiceName());
            return _stub;
        }
        catch (org.apache.axis.AxisFault e) {
            return null;
        }
    }

    public void setWSRPBaseServiceEndpointAddress(java.lang.String address) {
        WSRPBaseService_address = address;
    }


    // Use to get a proxy class for WSRPServiceDescriptionService
    private java.lang.String WSRPServiceDescriptionService_address = "http://localhost:8080/WSRPService";

    public java.lang.String getWSRPServiceDescriptionServiceAddress() {
        return WSRPServiceDescriptionService_address;
    }

    // The WSDD service name defaults to the port name.
    private java.lang.String WSRPServiceDescriptionServiceWSDDServiceName = "WSRPServiceDescriptionService";

    public java.lang.String getWSRPServiceDescriptionServiceWSDDServiceName() {
        return WSRPServiceDescriptionServiceWSDDServiceName;
    }

    public void setWSRPServiceDescriptionServiceWSDDServiceName(java.lang.String name) {
        WSRPServiceDescriptionServiceWSDDServiceName = name;
    }

    public oasis.names.tc.wsrp.v1.intf.WSRP_v1_ServiceDescription_PortType getWSRPServiceDescriptionService() throws javax.xml.rpc.ServiceException {
       java.net.URL endpoint;
        try {
            endpoint = new java.net.URL(WSRPServiceDescriptionService_address);
        }
        catch (java.net.MalformedURLException e) {
            throw new javax.xml.rpc.ServiceException(e);
        }
        return getWSRPServiceDescriptionService(endpoint);
    }

    public oasis.names.tc.wsrp.v1.intf.WSRP_v1_ServiceDescription_PortType getWSRPServiceDescriptionService(java.net.URL portAddress) throws javax.xml.rpc.ServiceException {
        try {
            oasis.names.tc.wsrp.v1.bind.WSRP_v1_ServiceDescription_Binding_SOAPStub _stub = new oasis.names.tc.wsrp.v1.bind.WSRP_v1_ServiceDescription_Binding_SOAPStub(portAddress, this);
            _stub.setPortName(getWSRPServiceDescriptionServiceWSDDServiceName());
            return _stub;
        }
        catch (org.apache.axis.AxisFault e) {
            return null;
        }
    }

    public void setWSRPServiceDescriptionServiceEndpointAddress(java.lang.String address) {
        WSRPServiceDescriptionService_address = address;
    }

    /**
     * For the given interface, get the stub implementation.
     * If this service has no port for the given interface,
     * then ServiceException is thrown.
     */
    public java.rmi.Remote getPort(Class serviceEndpointInterface) throws javax.xml.rpc.ServiceException {
        try {
            if (oasis.names.tc.wsrp.v1.intf.WSRP_v1_PortletManagement_PortType.class.isAssignableFrom(serviceEndpointInterface)) {
                oasis.names.tc.wsrp.v1.bind.WSRP_v1_PortletManagement_Binding_SOAPStub _stub = new oasis.names.tc.wsrp.v1.bind.WSRP_v1_PortletManagement_Binding_SOAPStub(new java.net.URL(WSRPPortletManagementService_address), this);
                _stub.setPortName(getWSRPPortletManagementServiceWSDDServiceName());
                return _stub;
            }
            if (oasis.names.tc.wsrp.v1.intf.WSRP_v1_Registration_PortType.class.isAssignableFrom(serviceEndpointInterface)) {
                oasis.names.tc.wsrp.v1.bind.WSRP_v1_Registration_Binding_SOAPStub _stub = new oasis.names.tc.wsrp.v1.bind.WSRP_v1_Registration_Binding_SOAPStub(new java.net.URL(WSRPRegistrationService_address), this);
                _stub.setPortName(getWSRPRegistrationServiceWSDDServiceName());
                return _stub;
            }
            if (oasis.names.tc.wsrp.v1.intf.WSRP_v1_Markup_PortType.class.isAssignableFrom(serviceEndpointInterface)) {
                oasis.names.tc.wsrp.v1.bind.WSRP_v1_Markup_Binding_SOAPStub _stub = new oasis.names.tc.wsrp.v1.bind.WSRP_v1_Markup_Binding_SOAPStub(new java.net.URL(WSRPBaseService_address), this);
                _stub.setPortName(getWSRPBaseServiceWSDDServiceName());
                return _stub;
            }
            if (oasis.names.tc.wsrp.v1.intf.WSRP_v1_ServiceDescription_PortType.class.isAssignableFrom(serviceEndpointInterface)) {
                oasis.names.tc.wsrp.v1.bind.WSRP_v1_ServiceDescription_Binding_SOAPStub _stub = new oasis.names.tc.wsrp.v1.bind.WSRP_v1_ServiceDescription_Binding_SOAPStub(new java.net.URL(WSRPServiceDescriptionService_address), this);
                _stub.setPortName(getWSRPServiceDescriptionServiceWSDDServiceName());
                return _stub;
            }
        }
        catch (java.lang.Throwable t) {
            throw new javax.xml.rpc.ServiceException(t);
        }
        throw new javax.xml.rpc.ServiceException("There is no stub implementation for the interface:  " + (serviceEndpointInterface == null ? "null" : serviceEndpointInterface.getName()));
    }

    /**
     * For the given interface, get the stub implementation.
     * If this service has no port for the given interface,
     * then ServiceException is thrown.
     */
    public java.rmi.Remote getPort(javax.xml.namespace.QName portName, Class serviceEndpointInterface) throws javax.xml.rpc.ServiceException {
        if (portName == null) {
            return getPort(serviceEndpointInterface);
        }
        java.lang.String inputPortName = portName.getLocalPart();
        if ("WSRPPortletManagementService".equals(inputPortName)) {
            return getWSRPPortletManagementService();
        }
        else if ("WSRPRegistrationService".equals(inputPortName)) {
            return getWSRPRegistrationService();
        }
        else if ("WSRPBaseService".equals(inputPortName)) {
            return getWSRPBaseService();
        }
        else if ("WSRPServiceDescriptionService".equals(inputPortName)) {
            return getWSRPServiceDescriptionService();
        }
        else  {
            java.rmi.Remote _stub = getPort(serviceEndpointInterface);
            ((org.apache.axis.client.Stub) _stub).setPortName(portName);
            return _stub;
        }
    }

    public javax.xml.namespace.QName getServiceName() {
        return new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:wsdl", "WSRPService");
    }

    private java.util.HashSet ports = null;

    public java.util.Iterator getPorts() {
        if (ports == null) {
            ports = new java.util.HashSet();
            ports.add(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:wsdl", "WSRPPortletManagementService"));
            ports.add(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:wsdl", "WSRPRegistrationService"));
            ports.add(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:wsdl", "WSRPBaseService"));
            ports.add(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:wsdl", "WSRPServiceDescriptionService"));
        }
        return ports.iterator();
    }

    /**
    * Set the endpoint address for the specified port name.
    */
    public void setEndpointAddress(java.lang.String portName, java.lang.String address) throws javax.xml.rpc.ServiceException {
        if ("WSRPPortletManagementService".equals(portName)) {
            setWSRPPortletManagementServiceEndpointAddress(address);
        }
        if ("WSRPRegistrationService".equals(portName)) {
            setWSRPRegistrationServiceEndpointAddress(address);
        }
        if ("WSRPBaseService".equals(portName)) {
            setWSRPBaseServiceEndpointAddress(address);
        }
        if ("WSRPServiceDescriptionService".equals(portName)) {
            setWSRPServiceDescriptionServiceEndpointAddress(address);
        }
        else { // Unknown Port Name
            throw new javax.xml.rpc.ServiceException(" Cannot set Endpoint Address for Unknown Port" + portName);
        }
    }

    /**
    * Set the endpoint address for the specified port name.
    */
    public void setEndpointAddress(javax.xml.namespace.QName portName, java.lang.String address) throws javax.xml.rpc.ServiceException {
        setEndpointAddress(portName.getLocalPart(), address);
    }

}
