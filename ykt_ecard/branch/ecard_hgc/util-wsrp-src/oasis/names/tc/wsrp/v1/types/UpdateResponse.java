/**
 * UpdateResponse.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class UpdateResponse  implements java.io.Serializable {
    private oasis.names.tc.wsrp.v1.types.SessionContext sessionContext;
    private oasis.names.tc.wsrp.v1.types.PortletContext portletContext;
    private oasis.names.tc.wsrp.v1.types.MarkupContext markupContext;
    private java.lang.String navigationalState;
    private java.lang.String newWindowState;
    private java.lang.String newMode;

    public UpdateResponse() {
    }

    public UpdateResponse(
           oasis.names.tc.wsrp.v1.types.MarkupContext markupContext,
           java.lang.String navigationalState,
           java.lang.String newMode,
           java.lang.String newWindowState,
           oasis.names.tc.wsrp.v1.types.PortletContext portletContext,
           oasis.names.tc.wsrp.v1.types.SessionContext sessionContext) {
           this.sessionContext = sessionContext;
           this.portletContext = portletContext;
           this.markupContext = markupContext;
           this.navigationalState = navigationalState;
           this.newWindowState = newWindowState;
           this.newMode = newMode;
    }


    /**
     * Gets the sessionContext value for this UpdateResponse.
     * 
     * @return sessionContext
     */
    public oasis.names.tc.wsrp.v1.types.SessionContext getSessionContext() {
        return sessionContext;
    }


    /**
     * Sets the sessionContext value for this UpdateResponse.
     * 
     * @param sessionContext
     */
    public void setSessionContext(oasis.names.tc.wsrp.v1.types.SessionContext sessionContext) {
        this.sessionContext = sessionContext;
    }


    /**
     * Gets the portletContext value for this UpdateResponse.
     * 
     * @return portletContext
     */
    public oasis.names.tc.wsrp.v1.types.PortletContext getPortletContext() {
        return portletContext;
    }


    /**
     * Sets the portletContext value for this UpdateResponse.
     * 
     * @param portletContext
     */
    public void setPortletContext(oasis.names.tc.wsrp.v1.types.PortletContext portletContext) {
        this.portletContext = portletContext;
    }


    /**
     * Gets the markupContext value for this UpdateResponse.
     * 
     * @return markupContext
     */
    public oasis.names.tc.wsrp.v1.types.MarkupContext getMarkupContext() {
        return markupContext;
    }


    /**
     * Sets the markupContext value for this UpdateResponse.
     * 
     * @param markupContext
     */
    public void setMarkupContext(oasis.names.tc.wsrp.v1.types.MarkupContext markupContext) {
        this.markupContext = markupContext;
    }


    /**
     * Gets the navigationalState value for this UpdateResponse.
     * 
     * @return navigationalState
     */
    public java.lang.String getNavigationalState() {
        return navigationalState;
    }


    /**
     * Sets the navigationalState value for this UpdateResponse.
     * 
     * @param navigationalState
     */
    public void setNavigationalState(java.lang.String navigationalState) {
        this.navigationalState = navigationalState;
    }


    /**
     * Gets the newWindowState value for this UpdateResponse.
     * 
     * @return newWindowState
     */
    public java.lang.String getNewWindowState() {
        return newWindowState;
    }


    /**
     * Sets the newWindowState value for this UpdateResponse.
     * 
     * @param newWindowState
     */
    public void setNewWindowState(java.lang.String newWindowState) {
        this.newWindowState = newWindowState;
    }


    /**
     * Gets the newMode value for this UpdateResponse.
     * 
     * @return newMode
     */
    public java.lang.String getNewMode() {
        return newMode;
    }


    /**
     * Sets the newMode value for this UpdateResponse.
     * 
     * @param newMode
     */
    public void setNewMode(java.lang.String newMode) {
        this.newMode = newMode;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof UpdateResponse)) return false;
        UpdateResponse other = (UpdateResponse) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.sessionContext==null && other.getSessionContext()==null) || 
             (this.sessionContext!=null &&
              this.sessionContext.equals(other.getSessionContext()))) &&
            ((this.portletContext==null && other.getPortletContext()==null) || 
             (this.portletContext!=null &&
              this.portletContext.equals(other.getPortletContext()))) &&
            ((this.markupContext==null && other.getMarkupContext()==null) || 
             (this.markupContext!=null &&
              this.markupContext.equals(other.getMarkupContext()))) &&
            ((this.navigationalState==null && other.getNavigationalState()==null) || 
             (this.navigationalState!=null &&
              this.navigationalState.equals(other.getNavigationalState()))) &&
            ((this.newWindowState==null && other.getNewWindowState()==null) || 
             (this.newWindowState!=null &&
              this.newWindowState.equals(other.getNewWindowState()))) &&
            ((this.newMode==null && other.getNewMode()==null) || 
             (this.newMode!=null &&
              this.newMode.equals(other.getNewMode())));
        __equalsCalc = null;
        return _equals;
    }

    private boolean __hashCodeCalc = false;
    public synchronized int hashCode() {
        if (__hashCodeCalc) {
            return 0;
        }
        __hashCodeCalc = true;
        int _hashCode = 1;
        if (getSessionContext() != null) {
            _hashCode += getSessionContext().hashCode();
        }
        if (getPortletContext() != null) {
            _hashCode += getPortletContext().hashCode();
        }
        if (getMarkupContext() != null) {
            _hashCode += getMarkupContext().hashCode();
        }
        if (getNavigationalState() != null) {
            _hashCode += getNavigationalState().hashCode();
        }
        if (getNewWindowState() != null) {
            _hashCode += getNewWindowState().hashCode();
        }
        if (getNewMode() != null) {
            _hashCode += getNewMode().hashCode();
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(UpdateResponse.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "UpdateResponse"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("sessionContext");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "sessionContext"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "SessionContext"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("portletContext");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "portletContext"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "PortletContext"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("markupContext");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "markupContext"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "MarkupContext"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("navigationalState");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "navigationalState"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("newWindowState");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "newWindowState"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("newMode");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "newMode"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
    }

    /**
     * Return type metadata object
     */
    public static org.apache.axis.description.TypeDesc getTypeDesc() {
        return typeDesc;
    }

    /**
     * Get Custom Serializer
     */
    public static org.apache.axis.encoding.Serializer getSerializer(
           java.lang.String mechType, 
           java.lang.Class _javaType,  
           javax.xml.namespace.QName _xmlType) {
        return 
          new  org.apache.axis.encoding.ser.BeanSerializer(
            _javaType, _xmlType, typeDesc);
    }

    /**
     * Get Custom Deserializer
     */
    public static org.apache.axis.encoding.Deserializer getDeserializer(
           java.lang.String mechType, 
           java.lang.Class _javaType,  
           javax.xml.namespace.QName _xmlType) {
        return 
          new  org.apache.axis.encoding.ser.BeanDeserializer(
            _javaType, _xmlType, typeDesc);
    }

}
