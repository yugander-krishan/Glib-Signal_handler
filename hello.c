#include <glib-object.h>
#include <stdio.h>

/* Interface: DmiDiag */
#define DMI_TYPE_DIAG dmi_diag_get_type()
G_DECLARE_INTERFACE(DmiDiag, dmi_diag, DMI, DIAG, GObject);

struct _DmiDiagInterface {
    GTypeInterface parent;

    int (*send_frame)(DmiDiag * self, int value);
};

G_DEFINE_INTERFACE(DmiDiag, dmi_diag, G_TYPE_OBJECT);

static void
dmi_diag_default_init(DmiDiagInterface* iface)
{
    /* Add properties and signals here. */
}

int send_frame(gpointer self, int value)
{
    DmiDiagInterface* iface;

    iface = DMI_DIAG_GET_IFACE(self);
    if(iface)
        return iface->send_frame((DmiDiag*)self, value);
    return -1;
}

/* Class: BaseDevice */
#define DMI_TYPE_BASE_DEVICE dmi_base_device_get_type()
G_DECLARE_DERIVABLE_TYPE(DmiBaseDevice, dmi_base_device, DMI, BASE_DEVICE,
                         GObject);

struct _DmiBaseDeviceClass {
    GObjectClass parent_class;

    const char* (*get_uid)(DmiBaseDevice* dev);
};

G_DEFINE_TYPE(DmiBaseDevice, dmi_base_device, G_TYPE_OBJECT);

enum
{
    TEST,
    LAST_SIGNAL
};

static guint signals[LAST_SIGNAL];

const char* get_uid(gpointer dev)
{
    if(DMI_IS_BASE_DEVICE(dev))
        return DMI_BASE_DEVICE_GET_CLASS(dev)->get_uid((DmiBaseDevice*)dev);
    return "(null)";
}

const char* dmi_base_device_get_uid(DmiBaseDevice* dev)
{
    return "UID";
}

void dmi_base_device_init(DmiBaseDevice* self)
{
    /* Add properties and signals here. */
    printf("inside init function \n");
}

static void base_dev_register_ifaces(void);

static void dcv_client_connection_closed() 
{
    printf("inside dcv_client_connection_closed func \n");
}


void dmi_base_device_class_init(DmiBaseDeviceClass *klass)
{
   // base_dev_register_ifaces();
   // klass->get_uid = dmi_base_device_get_uid;
   printf("inside class_init function \n");

   
   signals[TEST]= g_signal_newv ("test",
                 G_TYPE_FROM_CLASS (klass),
                 G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
                 NULL /* closure */,
                 NULL /* accumulator */,
                 NULL /* accumulator data */,
                 NULL /* C marshaller */,
                 G_TYPE_NONE /* return_type */,
                 0     /* n_params */,
                 NULL  /* param_types */); 
   
   GObjectClass *object_class = G_OBJECT_CLASS(klass); 
   //signals[TEST]= g_signal_new_class_handler("test",
   //                                G_TYPE_FROM_CLASS(klass),
   //                                G_SIGNAL_RUN_LAST,
   //                                G_CALLBACK(dcv_client_connection_closed),
   //                                NULL, NULL, NULL,
   //                                G_TYPE_NONE, 0); 


}

static int
base_device_send_frame(DmiDiag *self, int value)
{
    return 42;
}

static void
base_dev_dmi_diag_interface_init(gpointer g_iface,
                                 gpointer iface_data)
{
    DmiDiagInterface *iface = g_iface;
    iface->send_frame = base_device_send_frame;
}

static void base_dev_register_ifaces(void)
{
    static const GInterfaceInfo diag_info = {
        .interface_init = base_dev_dmi_diag_interface_init,
    };
    g_type_add_interface_static(DMI_TYPE_BASE_DEVICE, DMI_TYPE_DIAG,
                                &diag_info);
}

static void test(DmiBaseDevice* self) {
    
   printf("inside test method \n");
    
   g_signal_emit (self, signals[TEST], 0 /* details */);

   printf("coming out of test function \n");

}

int main(void)
{
    // base_dev_register_ifaces();
    DmiBaseDevice* dev = g_object_new(DMI_TYPE_BASE_DEVICE, NULL);
    // printf("%s %d\n", get_uid(dev), send_frame(dev, 46));
    
    g_signal_connect (dev, "test", (GCallback) dcv_client_connection_closed, NULL); 
    
    test(dev);

    //printf("testing\n");
    return 0;
}
