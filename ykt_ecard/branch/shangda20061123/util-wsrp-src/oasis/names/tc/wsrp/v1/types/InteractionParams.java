/**
 * InteractionParams.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class InteractionParams  implements java.io.Serializable {
    private oasis.names.tc.wsrp.v1.types.StateChange portletStateChange;
    private java.lang.String interactionState;
    private oasis.names.tc.wsrp.v1.types.NamedString[] formParameters;
    private oasis.names.tc.wsrp.v1.types.UploadContext[] uploadContexts;
    private oasis.names.tc.wsrp.v1.types.Extension[] extensions;

    public InteractionParams() {
    }

    public InteractionParams(
           oasis.names.tc.wsrp.v1.types.Extension[] extensions,
           oasis.names.tc.wsrp.v1.types.NamedString[] formParameters,
           java.lang.String interactionState,
           oasis.names.tc.wsrp.v1.types.StateChange portletStateChange,
           oasis.names.tc.wsrp.v1.types.UploadContext[] uploadContexts) {
           this.portletStateChange = portletStateChange;
           this.interactionState = interactionState;
           this.formParameters = formParameters;
           this.uploadContexts = uploadContexts;
           this.extensions = extensions;
    }


    /**
     * Gets the portletStateChange value for this InteractionParams.
     * 
     * @return portletStateChange
     */
    public oasis.names.tc.wsrp.v1.types.StateChange getPortletStateChange() {
        return portletStateChange;
    }


    /**
     * Sets the portletStateChange value for this InteractionParams.
     * 
     * @param portletStateChange
     */
    public void setPortletStateChange(oasis.names.tc.wsrp.v1.types.StateChange portletStateChange) {
        this.portletStateChange = portletStateChange;
    }


    /**
     * Gets the interactionState value for this InteractionParams.
     * 
     * @return interactionState
     */
    public java.lang.String getInteractionState() {
        return interactionState;
    }


    /**
     * Sets the interactionState value for this InteractionParams.
     * 
     * @param interactionState
     */
    public void setInteractionState(java.lang.String interactionState) {
        this.interactionState = interactionState;
    }


    /**
     * Gets the formParameters value for this InteractionParams.
     * 
     * @return formParameters
     */
    public oasis.names.tc.wsrp.v1.types.NamedString[] getFormParameters() {
        return formParameters;
    }


    /**
     * Sets the formParameters value for this InteractionParams.
     * 
     * @param formParameters
     */
    public void setFormParameters(oasis.names.tc.wsrp.v1.types.NamedString[] formParameters) {
        this.formParameters = formParameters;
    }

    public oasis.names.tc.wsrp.v1.types.NamedString getFormParameters(int i) {
        return this.formParameters[i];
    }

    public void setFormParameters(int i, oasis.names.tc.wsrp.v1.types.NamedString _value) {
        this.formParameters[i] = _value;
    }


    /**
     * Gets the uploadContexts value for this InteractionParams.
     * 
     * @return uploadContexts
     */
    public oasis.names.tc.wsrp.v1.types.UploadContext[] getUploadContexts() {
        return uploadContexts;
    }


    /**
     * Sets the uploadContexts value for this InteractionParams.
     * 
     * @param uploadContexts
     */
    public void setUploadContexts(oasis.names.tc.wsrp.v1.types.UploadContext[] uploadContexts) {
        this.uploadContexts = uploadContexts;
    }

    public oasis.names.tc.wsrp.v1.types.UploadContext getUploadContexts(int i) {
        return this.uploadContexts[i];
    }

    public void setUploadContexts(int i, oasis.names.tc.wsrp.v1.types.UploadContext _value) {
        this.uploadContexts[i] = _value;
    }


    /**
     * Gets the extensions value for this InteractionParams.
     * 
     * @return extensions
     */
    public oasis.names.tc.wsrp.v1.types.Extension[] getExtensions() {
        return extensions;
    }


    /**
     * Sets the extensions value for this InteractionParams.
     * 
     * @param extensions
     */
    public void setExtensions(oasis.names.tc.wsrp.v1.types.Extension[] extensions) {
        this.extensions = extensions;
    }

    public oasis.names.tc.wsrp.v1.types.Extension getExtensions(int i) {
        return this.extensions[i];
    }

    public void setExtensions(int i, oasis.names.tc.wsrp.v1.types.Extension _value) {
        this.extensions[i] = _value;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof InteractionParams)) return false;
        InteractionParams other = (InteractionParams) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.portletStateChange==null && other.getPortletStateChange()==null) || 
             (this.portletStateChange!=null &&
              this.portletStateChange.equals(other.getPortletStateChange()))) &&
            ((this.interactionState==null && other.getInteractionState()==null) || 
             (this.interactionState!=null &&
              this.interactionState.equals(other.getInteractionState()))) &&
            ((this.formParameters==null && other.getFormParameters()==null) || 
             (this.formParameters!=null &&
              java.util.Arrays.equals(this.formParameters, other.getFormParameters()))) &&
            ((this.uploadContexts==null && other.getUploadContexts()==null) || 
             (this.uploadContexts!=null &&
              java.util.Arrays.equals(this.uploadContexts, other.getUploadContexts()))) &&
            ((this.extensions==null && other.getExtensions()==null) || 
             (this.extensions!=null &&
              java.util.Arrays.equals(this.extensions, other.getExtensions())));
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
        if (getPortletStateChange() != null) {
            _hashCode += getPortletStateChange().hashCode();
        }
        if (getInteractionState() != null) {
            _hashCode += getInteractionState().hashCode();
        }
        if (getFormParameters() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getFormParameters());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getFormParameters(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getUploadContexts() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getUploadContexts());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getUploadContexts(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getExtensions() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getExtensions());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getExtensions(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(InteractionParams.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "InteractionParams"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("portletStateChange");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "portletStateChange"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "StateChange"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("interactionState");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "interactionState"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("formParameters");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "formParameters"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "NamedString"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("uploadContexts");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "uploadContexts"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "UploadContext"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("extensions");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "extensions"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "Extension"));
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
