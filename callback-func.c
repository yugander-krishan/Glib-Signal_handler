//#include "example-person.h"
#include "callback-func.h"

 void dcv_client_connection_closed(GObject* self) {
  printf("inside dcv_client_connection_closed func. of example-person.c signal callback \n");

  //printf("name of the person is %s", self->name);
}

