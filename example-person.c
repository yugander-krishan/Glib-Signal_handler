#include "example-person.h"

struct _ExamplePerson
{
  GObject parent_object;

  gchar *name;
};

/* This declares typedef struct _ExamplePerson ExamplePerson */
G_DEFINE_TYPE (ExamplePerson, example_person, G_TYPE_OBJECT);

enum
{
  PROP_0,
  PROP_NAME,
  PROP_LAST
};

enum
{
    TEST,
    LAST_SIGNAL
};

static guint signals[LAST_SIGNAL];

static void
example_person_get_property (GObject *object,
                             guint prop_id,
                             GValue *value,
                             GParamSpec *properties)
{
  ExamplePerson *self = (ExamplePerson *) object;

  switch (prop_id)
    {
    case PROP_NAME:
      g_value_set_string (value, example_person_get_name (self));
      break;
    }
}

static void
example_person_set_property (GObject *object,
                             guint prop_id,
                             const GValue *value,
                             GParamSpec *properties)
{
  ExamplePerson *self = (ExamplePerson *) object;

  switch (prop_id)
    {
    case PROP_NAME:
      example_person_set_name (self, g_value_get_string (value));
      break;
    }
}

static GParamSpec *properties [PROP_LAST];

//static void dcv_client_connection_closed(ExamplePerson* self) {
//  printf("inside dcv_client_connection_closed func. of example-person.c signal callback \n");

//  printf("name of the person is %s", self->name);
//}

/* class initializer, called only once */
static void
example_person_class_init (ExamplePersonClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->get_property = example_person_get_property;
  object_class->set_property = example_person_set_property;

  properties [PROP_NAME] =
    g_param_spec_string ("name",
                         "Name",
                         "Example Person's name",
                         NULL,
                         (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_properties (object_class, PROP_LAST, properties);

  //signals[TEST]= g_signal_newv ("test",
   //              G_TYPE_FROM_CLASS (klass),
   //              G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
   //              NULL /* closure */,
   //              NULL /* accumulator */,
   //              NULL /* accumulator data */,
   //              NULL /* C marshaller */,
   //              G_TYPE_NONE /* return_type */,
   //              0     /* n_params */,
   //              NULL  /* param_types */); 

   //GObjectClass *object_class = G_OBJECT_CLASS(klass);
   signals[TEST]= g_signal_new_class_handler("test",
                                   G_TYPE_FROM_CLASS(klass),
                                   G_SIGNAL_RUN_LAST,
                                   G_CALLBACK(dcv_client_connection_closed),
                                   NULL, NULL, NULL,
                                   G_TYPE_NONE, 0);
}

/* instance initializer */
static void
example_person_init (ExamplePerson *self)
{
  self->name = g_strdup ("");
}

const gchar *
example_person_get_name (ExamplePerson *self)
{
  return self->name;
}

void
example_person_set_name (ExamplePerson *self,
                         const gchar *name)
{
  if (g_strcmp0 (self->name, name) != 0)
    {
      g_free (self->name);
      self->name = g_strdup (name);
    }
}

static void test(ExamplePerson* self) {

   printf("inside test method \n");

   g_signal_emit (self, signals[TEST], 0 /* details */, 30);

   printf("coming out of test function \n");

}

int main(void) {
  printf("inside main function \n");
  ExamplePerson* ep = g_object_new(EXAMPLE_TYPE_PERSON, 
		                   "name", "yug",
		                   NULL ); 
  test(ep);
}
