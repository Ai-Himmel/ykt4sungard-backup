/**
 * WSRPService.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.wsdl;

public interface WSRPService extends javax.xml.rpc.Service {
    public java.lang.String getWSRPPortletManagementServiceAddress();

    public oasis.names.tc.wsrp.v1.intf.WSRP_v1_PortletManagement_PortType getWSRPPortletManagementService() throws javax.xml.rpc.ServiceException;

    public oasis.names.tc.wsrp.v1.intf.WSRP_v1_PortletManagement_PortType getWSRPPortletManagementService(java.net.URL portAddress) throws javax.xml.rpc.ServiceException;
    public java.lang.String getWSRPRegistrationServiceAddress();

    public oasis.names.tc.wsrp.v1.intf.WSRP_v1_Registration_PortType getWSRPRegistrationService() throws javax.xml.rpc.ServiceException;

    public oasis.names.tc.wsrp.v1.intf.WSRP_v1_Registration_PortType getWSRPRegistrationService(java.net.URL portAddress) throws javax.xml.rpc.ServiceException;
    public java.lang.String getWSRPBaseServiceAddress();

    public oasis.names.tc.wsrp.v1.intf.WSRP_v1_Markup_PortType getWSRPBaseService() throws javax.xml.rpc.ServiceException;

    public oasis.names.tc.wsrp.v1.intf.WSRP_v1_Markup_PortType getWSRPBaseService(java.net.URL portAddress) throws javax.xml.rpc.ServiceException;
    public java.lang.String getWSRPServiceDescriptionServiceAddress();

    public oasis.names.tc.wsrp.v1.intf.WSRP_v1_ServiceDescription_PortType getWSRPServiceDescriptionService() throws javax.xml.rpc.ServiceException;

    public oasis.names.tc.wsrp.v1.intf.WSRP_v1_ServiceDescription_PortType getWSRPServiceDescriptionService(java.net.URL portAddress) throws javax.xml.rpc.ServiceException;
}
